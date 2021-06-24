<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011  Intel Corporation. All rights reserved.
 * Copyright (C) 2014 Marvell International Ltd.
 */

#घोषणा pr_fmt(fmt) "llcp: %s: " fmt, __func__

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/nfc.h>

#समावेश "nfc.h"
#समावेश "llcp.h"

अटल u8 llcp_magic[3] = अणु0x46, 0x66, 0x6dपूर्ण;

अटल LIST_HEAD(llcp_devices);

अटल व्योम nfc_llcp_rx_skb(काष्ठा nfc_llcp_local *local, काष्ठा sk_buff *skb);

व्योम nfc_llcp_sock_link(काष्ठा llcp_sock_list *l, काष्ठा sock *sk)
अणु
	ग_लिखो_lock(&l->lock);
	sk_add_node(sk, &l->head);
	ग_लिखो_unlock(&l->lock);
पूर्ण

व्योम nfc_llcp_sock_unlink(काष्ठा llcp_sock_list *l, काष्ठा sock *sk)
अणु
	ग_लिखो_lock(&l->lock);
	sk_del_node_init(sk);
	ग_लिखो_unlock(&l->lock);
पूर्ण

व्योम nfc_llcp_socket_remote_param_init(काष्ठा nfc_llcp_sock *sock)
अणु
	sock->remote_rw = LLCP_DEFAULT_RW;
	sock->remote_miu = LLCP_MAX_MIU + 1;
पूर्ण

अटल व्योम nfc_llcp_socket_purge(काष्ठा nfc_llcp_sock *sock)
अणु
	काष्ठा nfc_llcp_local *local = sock->local;
	काष्ठा sk_buff *s, *पंचांगp;

	pr_debug("%p\n", &sock->sk);

	skb_queue_purge(&sock->tx_queue);
	skb_queue_purge(&sock->tx_pending_queue);

	अगर (local == शून्य)
		वापस;

	/* Search क्रम local pending SKBs that are related to this socket */
	skb_queue_walk_safe(&local->tx_queue, s, पंचांगp) अणु
		अगर (s->sk != &sock->sk)
			जारी;

		skb_unlink(s, &local->tx_queue);
		kमुक्त_skb(s);
	पूर्ण
पूर्ण

अटल व्योम nfc_llcp_socket_release(काष्ठा nfc_llcp_local *local, bool device,
				    पूर्णांक err)
अणु
	काष्ठा sock *sk;
	काष्ठा hlist_node *पंचांगp;
	काष्ठा nfc_llcp_sock *llcp_sock;

	skb_queue_purge(&local->tx_queue);

	ग_लिखो_lock(&local->sockets.lock);

	sk_क्रम_each_safe(sk, पंचांगp, &local->sockets.head) अणु
		llcp_sock = nfc_llcp_sock(sk);

		bh_lock_sock(sk);

		nfc_llcp_socket_purge(llcp_sock);

		अगर (sk->sk_state == LLCP_CONNECTED)
			nfc_put_device(llcp_sock->dev);

		अगर (sk->sk_state == LLCP_LISTEN) अणु
			काष्ठा nfc_llcp_sock *lsk, *n;
			काष्ठा sock *accept_sk;

			list_क्रम_each_entry_safe(lsk, n,
						 &llcp_sock->accept_queue,
						 accept_queue) अणु
				accept_sk = &lsk->sk;
				bh_lock_sock(accept_sk);

				nfc_llcp_accept_unlink(accept_sk);

				अगर (err)
					accept_sk->sk_err = err;
				accept_sk->sk_state = LLCP_CLOSED;
				accept_sk->sk_state_change(sk);

				bh_unlock_sock(accept_sk);
			पूर्ण
		पूर्ण

		अगर (err)
			sk->sk_err = err;
		sk->sk_state = LLCP_CLOSED;
		sk->sk_state_change(sk);

		bh_unlock_sock(sk);

		sk_del_node_init(sk);
	पूर्ण

	ग_लिखो_unlock(&local->sockets.lock);

	/* If we still have a device, we keep the RAW sockets alive */
	अगर (device == true)
		वापस;

	ग_लिखो_lock(&local->raw_sockets.lock);

	sk_क्रम_each_safe(sk, पंचांगp, &local->raw_sockets.head) अणु
		llcp_sock = nfc_llcp_sock(sk);

		bh_lock_sock(sk);

		nfc_llcp_socket_purge(llcp_sock);

		अगर (err)
			sk->sk_err = err;
		sk->sk_state = LLCP_CLOSED;
		sk->sk_state_change(sk);

		bh_unlock_sock(sk);

		sk_del_node_init(sk);
	पूर्ण

	ग_लिखो_unlock(&local->raw_sockets.lock);
पूर्ण

काष्ठा nfc_llcp_local *nfc_llcp_local_get(काष्ठा nfc_llcp_local *local)
अणु
	kref_get(&local->ref);

	वापस local;
पूर्ण

अटल व्योम local_cleanup(काष्ठा nfc_llcp_local *local)
अणु
	nfc_llcp_socket_release(local, false, ENXIO);
	del_समयr_sync(&local->link_समयr);
	skb_queue_purge(&local->tx_queue);
	cancel_work_sync(&local->tx_work);
	cancel_work_sync(&local->rx_work);
	cancel_work_sync(&local->समयout_work);
	kमुक्त_skb(local->rx_pending);
	del_समयr_sync(&local->sdreq_समयr);
	cancel_work_sync(&local->sdreq_समयout_work);
	nfc_llcp_मुक्त_sdp_tlv_list(&local->pending_sdreqs);
पूर्ण

अटल व्योम local_release(काष्ठा kref *ref)
अणु
	काष्ठा nfc_llcp_local *local;

	local = container_of(ref, काष्ठा nfc_llcp_local, ref);

	list_del(&local->list);
	local_cleanup(local);
	kमुक्त(local);
पूर्ण

पूर्णांक nfc_llcp_local_put(काष्ठा nfc_llcp_local *local)
अणु
	अगर (local == शून्य)
		वापस 0;

	वापस kref_put(&local->ref, local_release);
पूर्ण

अटल काष्ठा nfc_llcp_sock *nfc_llcp_sock_get(काष्ठा nfc_llcp_local *local,
					       u8 ssap, u8 dsap)
अणु
	काष्ठा sock *sk;
	काष्ठा nfc_llcp_sock *llcp_sock, *पंचांगp_sock;

	pr_debug("ssap dsap %d %d\n", ssap, dsap);

	अगर (ssap == 0 && dsap == 0)
		वापस शून्य;

	पढ़ो_lock(&local->sockets.lock);

	llcp_sock = शून्य;

	sk_क्रम_each(sk, &local->sockets.head) अणु
		पंचांगp_sock = nfc_llcp_sock(sk);

		अगर (पंचांगp_sock->ssap == ssap && पंचांगp_sock->dsap == dsap) अणु
			llcp_sock = पंचांगp_sock;
			अवरोध;
		पूर्ण
	पूर्ण

	पढ़ो_unlock(&local->sockets.lock);

	अगर (llcp_sock == शून्य)
		वापस शून्य;

	sock_hold(&llcp_sock->sk);

	वापस llcp_sock;
पूर्ण

अटल व्योम nfc_llcp_sock_put(काष्ठा nfc_llcp_sock *sock)
अणु
	sock_put(&sock->sk);
पूर्ण

अटल व्योम nfc_llcp_समयout_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nfc_llcp_local *local = container_of(work, काष्ठा nfc_llcp_local,
						    समयout_work);

	nfc_dep_link_करोwn(local->dev);
पूर्ण

अटल व्योम nfc_llcp_symm_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा nfc_llcp_local *local = from_समयr(local, t, link_समयr);

	pr_err("SYMM timeout\n");

	schedule_work(&local->समयout_work);
पूर्ण

अटल व्योम nfc_llcp_sdreq_समयout_work(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ समय;
	HLIST_HEAD(nl_sdres_list);
	काष्ठा hlist_node *n;
	काष्ठा nfc_llcp_sdp_tlv *sdp;
	काष्ठा nfc_llcp_local *local = container_of(work, काष्ठा nfc_llcp_local,
						    sdreq_समयout_work);

	mutex_lock(&local->sdreq_lock);

	समय = jअगरfies - msecs_to_jअगरfies(3 * local->remote_lto);

	hlist_क्रम_each_entry_safe(sdp, n, &local->pending_sdreqs, node) अणु
		अगर (समय_after(sdp->समय, समय))
			जारी;

		sdp->sap = LLCP_SDP_UNBOUND;

		hlist_del(&sdp->node);

		hlist_add_head(&sdp->node, &nl_sdres_list);
	पूर्ण

	अगर (!hlist_empty(&local->pending_sdreqs))
		mod_समयr(&local->sdreq_समयr,
			  jअगरfies + msecs_to_jअगरfies(3 * local->remote_lto));

	mutex_unlock(&local->sdreq_lock);

	अगर (!hlist_empty(&nl_sdres_list))
		nfc_genl_llc_send_sdres(local->dev, &nl_sdres_list);
पूर्ण

अटल व्योम nfc_llcp_sdreq_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा nfc_llcp_local *local = from_समयr(local, t, sdreq_समयr);

	schedule_work(&local->sdreq_समयout_work);
पूर्ण

काष्ठा nfc_llcp_local *nfc_llcp_find_local(काष्ठा nfc_dev *dev)
अणु
	काष्ठा nfc_llcp_local *local;

	list_क्रम_each_entry(local, &llcp_devices, list)
		अगर (local->dev == dev)
			वापस local;

	pr_debug("No device found\n");

	वापस शून्य;
पूर्ण

अटल अक्षर *wks[] = अणु
	शून्य,
	शून्य, /* SDP */
	"urn:nfc:sn:ip",
	"urn:nfc:sn:obex",
	"urn:nfc:sn:snep",
पूर्ण;

अटल पूर्णांक nfc_llcp_wks_sap(अक्षर *service_name, माप_प्रकार service_name_len)
अणु
	पूर्णांक sap, num_wks;

	pr_debug("%s\n", service_name);

	अगर (service_name == शून्य)
		वापस -EINVAL;

	num_wks = ARRAY_SIZE(wks);

	क्रम (sap = 0; sap < num_wks; sap++) अणु
		अगर (wks[sap] == शून्य)
			जारी;

		अगर (म_भेदन(wks[sap], service_name, service_name_len) == 0)
			वापस sap;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल
काष्ठा nfc_llcp_sock *nfc_llcp_sock_from_sn(काष्ठा nfc_llcp_local *local,
					    u8 *sn, माप_प्रकार sn_len)
अणु
	काष्ठा sock *sk;
	काष्ठा nfc_llcp_sock *llcp_sock, *पंचांगp_sock;

	pr_debug("sn %zd %p\n", sn_len, sn);

	अगर (sn == शून्य || sn_len == 0)
		वापस शून्य;

	पढ़ो_lock(&local->sockets.lock);

	llcp_sock = शून्य;

	sk_क्रम_each(sk, &local->sockets.head) अणु
		पंचांगp_sock = nfc_llcp_sock(sk);

		pr_debug("llcp sock %p\n", पंचांगp_sock);

		अगर (पंचांगp_sock->sk.sk_type == SOCK_STREAM &&
		    पंचांगp_sock->sk.sk_state != LLCP_LISTEN)
			जारी;

		अगर (पंचांगp_sock->sk.sk_type == SOCK_DGRAM &&
		    पंचांगp_sock->sk.sk_state != LLCP_BOUND)
			जारी;

		अगर (पंचांगp_sock->service_name == शून्य ||
		    पंचांगp_sock->service_name_len == 0)
			जारी;

		अगर (पंचांगp_sock->service_name_len != sn_len)
			जारी;

		अगर (स_भेद(sn, पंचांगp_sock->service_name, sn_len) == 0) अणु
			llcp_sock = पंचांगp_sock;
			अवरोध;
		पूर्ण
	पूर्ण

	पढ़ो_unlock(&local->sockets.lock);

	pr_debug("Found llcp sock %p\n", llcp_sock);

	वापस llcp_sock;
पूर्ण

u8 nfc_llcp_get_sdp_ssap(काष्ठा nfc_llcp_local *local,
			 काष्ठा nfc_llcp_sock *sock)
अणु
	mutex_lock(&local->sdp_lock);

	अगर (sock->service_name != शून्य && sock->service_name_len > 0) अणु
		पूर्णांक ssap = nfc_llcp_wks_sap(sock->service_name,
					    sock->service_name_len);

		अगर (ssap > 0) अणु
			pr_debug("WKS %d\n", ssap);

			/* This is a WKS, let's check if it's मुक्त */
			अगर (local->local_wks & BIT(ssap)) अणु
				mutex_unlock(&local->sdp_lock);

				वापस LLCP_SAP_MAX;
			पूर्ण

			set_bit(ssap, &local->local_wks);
			mutex_unlock(&local->sdp_lock);

			वापस ssap;
		पूर्ण

		/*
		 * Check अगर there alपढ़ोy is a non WKS socket bound
		 * to this service name.
		 */
		अगर (nfc_llcp_sock_from_sn(local, sock->service_name,
					  sock->service_name_len) != शून्य) अणु
			mutex_unlock(&local->sdp_lock);

			वापस LLCP_SAP_MAX;
		पूर्ण

		mutex_unlock(&local->sdp_lock);

		वापस LLCP_SDP_UNBOUND;

	पूर्ण अन्यथा अगर (sock->ssap != 0 && sock->ssap < LLCP_WKS_NUM_SAP) अणु
		अगर (!test_bit(sock->ssap, &local->local_wks)) अणु
			set_bit(sock->ssap, &local->local_wks);
			mutex_unlock(&local->sdp_lock);

			वापस sock->ssap;
		पूर्ण
	पूर्ण

	mutex_unlock(&local->sdp_lock);

	वापस LLCP_SAP_MAX;
पूर्ण

u8 nfc_llcp_get_local_ssap(काष्ठा nfc_llcp_local *local)
अणु
	u8 local_ssap;

	mutex_lock(&local->sdp_lock);

	local_ssap = find_first_zero_bit(&local->local_sap, LLCP_LOCAL_NUM_SAP);
	अगर (local_ssap == LLCP_LOCAL_NUM_SAP) अणु
		mutex_unlock(&local->sdp_lock);
		वापस LLCP_SAP_MAX;
	पूर्ण

	set_bit(local_ssap, &local->local_sap);

	mutex_unlock(&local->sdp_lock);

	वापस local_ssap + LLCP_LOCAL_SAP_OFFSET;
पूर्ण

व्योम nfc_llcp_put_ssap(काष्ठा nfc_llcp_local *local, u8 ssap)
अणु
	u8 local_ssap;
	अचिन्हित दीर्घ *sdp;

	अगर (ssap < LLCP_WKS_NUM_SAP) अणु
		local_ssap = ssap;
		sdp = &local->local_wks;
	पूर्ण अन्यथा अगर (ssap < LLCP_LOCAL_NUM_SAP) अणु
		atomic_t *client_cnt;

		local_ssap = ssap - LLCP_WKS_NUM_SAP;
		sdp = &local->local_sdp;
		client_cnt = &local->local_sdp_cnt[local_ssap];

		pr_debug("%d clients\n", atomic_पढ़ो(client_cnt));

		mutex_lock(&local->sdp_lock);

		अगर (atomic_dec_and_test(client_cnt)) अणु
			काष्ठा nfc_llcp_sock *l_sock;

			pr_debug("No more clients for SAP %d\n", ssap);

			clear_bit(local_ssap, sdp);

			/* Find the listening sock and set it back to UNBOUND */
			l_sock = nfc_llcp_sock_get(local, ssap, LLCP_SAP_SDP);
			अगर (l_sock) अणु
				l_sock->ssap = LLCP_SDP_UNBOUND;
				nfc_llcp_sock_put(l_sock);
			पूर्ण
		पूर्ण

		mutex_unlock(&local->sdp_lock);

		वापस;
	पूर्ण अन्यथा अगर (ssap < LLCP_MAX_SAP) अणु
		local_ssap = ssap - LLCP_LOCAL_NUM_SAP;
		sdp = &local->local_sap;
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	mutex_lock(&local->sdp_lock);

	clear_bit(local_ssap, sdp);

	mutex_unlock(&local->sdp_lock);
पूर्ण

अटल u8 nfc_llcp_reserve_sdp_ssap(काष्ठा nfc_llcp_local *local)
अणु
	u8 ssap;

	mutex_lock(&local->sdp_lock);

	ssap = find_first_zero_bit(&local->local_sdp, LLCP_SDP_NUM_SAP);
	अगर (ssap == LLCP_SDP_NUM_SAP) अणु
		mutex_unlock(&local->sdp_lock);

		वापस LLCP_SAP_MAX;
	पूर्ण

	pr_debug("SDP ssap %d\n", LLCP_WKS_NUM_SAP + ssap);

	set_bit(ssap, &local->local_sdp);

	mutex_unlock(&local->sdp_lock);

	वापस LLCP_WKS_NUM_SAP + ssap;
पूर्ण

अटल पूर्णांक nfc_llcp_build_gb(काष्ठा nfc_llcp_local *local)
अणु
	u8 *gb_cur, version, version_length;
	u8 lto_length, wks_length, miux_length;
	u8 *version_tlv = शून्य, *lto_tlv = शून्य,
	   *wks_tlv = शून्य, *miux_tlv = शून्य;
	__be16 wks = cpu_to_be16(local->local_wks);
	u8 gb_len = 0;
	पूर्णांक ret = 0;

	version = LLCP_VERSION_11;
	version_tlv = nfc_llcp_build_tlv(LLCP_TLV_VERSION, &version,
					 1, &version_length);
	अगर (!version_tlv) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	gb_len += version_length;

	lto_tlv = nfc_llcp_build_tlv(LLCP_TLV_LTO, &local->lto, 1, &lto_length);
	अगर (!lto_tlv) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	gb_len += lto_length;

	pr_debug("Local wks 0x%lx\n", local->local_wks);
	wks_tlv = nfc_llcp_build_tlv(LLCP_TLV_WKS, (u8 *)&wks, 2, &wks_length);
	अगर (!wks_tlv) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	gb_len += wks_length;

	miux_tlv = nfc_llcp_build_tlv(LLCP_TLV_MIUX, (u8 *)&local->miux, 0,
				      &miux_length);
	अगर (!miux_tlv) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	gb_len += miux_length;

	gb_len += ARRAY_SIZE(llcp_magic);

	अगर (gb_len > NFC_MAX_GT_LEN) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	gb_cur = local->gb;

	स_नकल(gb_cur, llcp_magic, ARRAY_SIZE(llcp_magic));
	gb_cur += ARRAY_SIZE(llcp_magic);

	स_नकल(gb_cur, version_tlv, version_length);
	gb_cur += version_length;

	स_नकल(gb_cur, lto_tlv, lto_length);
	gb_cur += lto_length;

	स_नकल(gb_cur, wks_tlv, wks_length);
	gb_cur += wks_length;

	स_नकल(gb_cur, miux_tlv, miux_length);
	gb_cur += miux_length;

	local->gb_len = gb_len;

out:
	kमुक्त(version_tlv);
	kमुक्त(lto_tlv);
	kमुक्त(wks_tlv);
	kमुक्त(miux_tlv);

	वापस ret;
पूर्ण

u8 *nfc_llcp_general_bytes(काष्ठा nfc_dev *dev, माप_प्रकार *general_bytes_len)
अणु
	काष्ठा nfc_llcp_local *local;

	local = nfc_llcp_find_local(dev);
	अगर (local == शून्य) अणु
		*general_bytes_len = 0;
		वापस शून्य;
	पूर्ण

	nfc_llcp_build_gb(local);

	*general_bytes_len = local->gb_len;

	वापस local->gb;
पूर्ण

पूर्णांक nfc_llcp_set_remote_gb(काष्ठा nfc_dev *dev, u8 *gb, u8 gb_len)
अणु
	काष्ठा nfc_llcp_local *local;

	अगर (gb_len < 3 || gb_len > NFC_MAX_GT_LEN)
		वापस -EINVAL;

	local = nfc_llcp_find_local(dev);
	अगर (local == शून्य) अणु
		pr_err("No LLCP device\n");
		वापस -ENODEV;
	पूर्ण

	स_रखो(local->remote_gb, 0, NFC_MAX_GT_LEN);
	स_नकल(local->remote_gb, gb, gb_len);
	local->remote_gb_len = gb_len;

	अगर (स_भेद(local->remote_gb, llcp_magic, 3)) अणु
		pr_err("MAC does not support LLCP\n");
		वापस -EINVAL;
	पूर्ण

	वापस nfc_llcp_parse_gb_tlv(local,
				     &local->remote_gb[3],
				     local->remote_gb_len - 3);
पूर्ण

अटल u8 nfc_llcp_dsap(काष्ठा sk_buff *pdu)
अणु
	वापस (pdu->data[0] & 0xfc) >> 2;
पूर्ण

अटल u8 nfc_llcp_ptype(काष्ठा sk_buff *pdu)
अणु
	वापस ((pdu->data[0] & 0x03) << 2) | ((pdu->data[1] & 0xc0) >> 6);
पूर्ण

अटल u8 nfc_llcp_ssap(काष्ठा sk_buff *pdu)
अणु
	वापस pdu->data[1] & 0x3f;
पूर्ण

अटल u8 nfc_llcp_ns(काष्ठा sk_buff *pdu)
अणु
	वापस pdu->data[2] >> 4;
पूर्ण

अटल u8 nfc_llcp_nr(काष्ठा sk_buff *pdu)
अणु
	वापस pdu->data[2] & 0xf;
पूर्ण

अटल व्योम nfc_llcp_set_nrns(काष्ठा nfc_llcp_sock *sock, काष्ठा sk_buff *pdu)
अणु
	pdu->data[2] = (sock->send_n << 4) | (sock->recv_n);
	sock->send_n = (sock->send_n + 1) % 16;
	sock->recv_ack_n = (sock->recv_n - 1) % 16;
पूर्ण

व्योम nfc_llcp_send_to_raw_sock(काष्ठा nfc_llcp_local *local,
			       काष्ठा sk_buff *skb, u8 direction)
अणु
	काष्ठा sk_buff *skb_copy = शून्य, *nskb;
	काष्ठा sock *sk;
	u8 *data;

	पढ़ो_lock(&local->raw_sockets.lock);

	sk_क्रम_each(sk, &local->raw_sockets.head) अणु
		अगर (sk->sk_state != LLCP_BOUND)
			जारी;

		अगर (skb_copy == शून्य) अणु
			skb_copy = __pskb_copy_fclone(skb, NFC_RAW_HEADER_SIZE,
						      GFP_ATOMIC, true);

			अगर (skb_copy == शून्य)
				जारी;

			data = skb_push(skb_copy, NFC_RAW_HEADER_SIZE);

			data[0] = local->dev ? local->dev->idx : 0xFF;
			data[1] = direction & 0x01;
			data[1] |= (RAW_PAYLOAD_LLCP << 1);
		पूर्ण

		nskb = skb_clone(skb_copy, GFP_ATOMIC);
		अगर (!nskb)
			जारी;

		अगर (sock_queue_rcv_skb(sk, nskb))
			kमुक्त_skb(nskb);
	पूर्ण

	पढ़ो_unlock(&local->raw_sockets.lock);

	kमुक्त_skb(skb_copy);
पूर्ण

अटल व्योम nfc_llcp_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nfc_llcp_local *local = container_of(work, काष्ठा nfc_llcp_local,
						    tx_work);
	काष्ठा sk_buff *skb;
	काष्ठा sock *sk;
	काष्ठा nfc_llcp_sock *llcp_sock;

	skb = skb_dequeue(&local->tx_queue);
	अगर (skb != शून्य) अणु
		sk = skb->sk;
		llcp_sock = nfc_llcp_sock(sk);

		अगर (llcp_sock == शून्य && nfc_llcp_ptype(skb) == LLCP_PDU_I) अणु
			kमुक्त_skb(skb);
			nfc_llcp_send_symm(local->dev);
		पूर्ण अन्यथा अगर (llcp_sock && !llcp_sock->remote_पढ़ोy) अणु
			skb_queue_head(&local->tx_queue, skb);
			nfc_llcp_send_symm(local->dev);
		पूर्ण अन्यथा अणु
			काष्ठा sk_buff *copy_skb = शून्य;
			u8 ptype = nfc_llcp_ptype(skb);
			पूर्णांक ret;

			pr_debug("Sending pending skb\n");
			prपूर्णांक_hex_dump_debug("LLCP Tx: ", DUMP_PREFIX_OFFSET,
					     16, 1, skb->data, skb->len, true);

			अगर (ptype == LLCP_PDU_DISC && sk != शून्य &&
			    sk->sk_state == LLCP_DISCONNECTING) अणु
				nfc_llcp_sock_unlink(&local->sockets, sk);
				sock_orphan(sk);
				sock_put(sk);
			पूर्ण

			अगर (ptype == LLCP_PDU_I)
				copy_skb = skb_copy(skb, GFP_ATOMIC);

			__net_बारtamp(skb);

			nfc_llcp_send_to_raw_sock(local, skb,
						  NFC_सूचीECTION_TX);

			ret = nfc_data_exchange(local->dev, local->target_idx,
						skb, nfc_llcp_recv, local);

			अगर (ret) अणु
				kमुक्त_skb(copy_skb);
				जाओ out;
			पूर्ण

			अगर (ptype == LLCP_PDU_I && copy_skb)
				skb_queue_tail(&llcp_sock->tx_pending_queue,
					       copy_skb);
		पूर्ण
	पूर्ण अन्यथा अणु
		nfc_llcp_send_symm(local->dev);
	पूर्ण

out:
	mod_समयr(&local->link_समयr,
		  jअगरfies + msecs_to_jअगरfies(2 * local->remote_lto));
पूर्ण

अटल काष्ठा nfc_llcp_sock *nfc_llcp_connecting_sock_get(काष्ठा nfc_llcp_local *local,
							  u8 ssap)
अणु
	काष्ठा sock *sk;
	काष्ठा nfc_llcp_sock *llcp_sock;

	पढ़ो_lock(&local->connecting_sockets.lock);

	sk_क्रम_each(sk, &local->connecting_sockets.head) अणु
		llcp_sock = nfc_llcp_sock(sk);

		अगर (llcp_sock->ssap == ssap) अणु
			sock_hold(&llcp_sock->sk);
			जाओ out;
		पूर्ण
	पूर्ण

	llcp_sock = शून्य;

out:
	पढ़ो_unlock(&local->connecting_sockets.lock);

	वापस llcp_sock;
पूर्ण

अटल काष्ठा nfc_llcp_sock *nfc_llcp_sock_get_sn(काष्ठा nfc_llcp_local *local,
						  u8 *sn, माप_प्रकार sn_len)
अणु
	काष्ठा nfc_llcp_sock *llcp_sock;

	llcp_sock = nfc_llcp_sock_from_sn(local, sn, sn_len);

	अगर (llcp_sock == शून्य)
		वापस शून्य;

	sock_hold(&llcp_sock->sk);

	वापस llcp_sock;
पूर्ण

अटल u8 *nfc_llcp_connect_sn(काष्ठा sk_buff *skb, माप_प्रकार *sn_len)
अणु
	u8 *tlv = &skb->data[2], type, length;
	माप_प्रकार tlv_array_len = skb->len - LLCP_HEADER_SIZE, offset = 0;

	जबतक (offset < tlv_array_len) अणु
		type = tlv[0];
		length = tlv[1];

		pr_debug("type 0x%x length %d\n", type, length);

		अगर (type == LLCP_TLV_SN) अणु
			*sn_len = length;
			वापस &tlv[2];
		पूर्ण

		offset += length + 2;
		tlv += length + 2;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम nfc_llcp_recv_ui(काष्ठा nfc_llcp_local *local,
			     काष्ठा sk_buff *skb)
अणु
	काष्ठा nfc_llcp_sock *llcp_sock;
	काष्ठा nfc_llcp_ui_cb *ui_cb;
	u8 dsap, ssap;

	dsap = nfc_llcp_dsap(skb);
	ssap = nfc_llcp_ssap(skb);

	ui_cb = nfc_llcp_ui_skb_cb(skb);
	ui_cb->dsap = dsap;
	ui_cb->ssap = ssap;

	pr_debug("%d %d\n", dsap, ssap);

	/* We're looking क्रम a bound socket, not a client one */
	llcp_sock = nfc_llcp_sock_get(local, dsap, LLCP_SAP_SDP);
	अगर (llcp_sock == शून्य || llcp_sock->sk.sk_type != SOCK_DGRAM)
		वापस;

	/* There is no sequence with UI frames */
	skb_pull(skb, LLCP_HEADER_SIZE);
	अगर (!sock_queue_rcv_skb(&llcp_sock->sk, skb)) अणु
		/*
		 * UI frames will be मुक्तd from the socket layer, so we
		 * need to keep them alive until someone receives them.
		 */
		skb_get(skb);
	पूर्ण अन्यथा अणु
		pr_err("Receive queue is full\n");
	पूर्ण

	nfc_llcp_sock_put(llcp_sock);
पूर्ण

अटल व्योम nfc_llcp_recv_connect(काष्ठा nfc_llcp_local *local,
				  काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *new_sk, *parent;
	काष्ठा nfc_llcp_sock *sock, *new_sock;
	u8 dsap, ssap, reason;

	dsap = nfc_llcp_dsap(skb);
	ssap = nfc_llcp_ssap(skb);

	pr_debug("%d %d\n", dsap, ssap);

	अगर (dsap != LLCP_SAP_SDP) अणु
		sock = nfc_llcp_sock_get(local, dsap, LLCP_SAP_SDP);
		अगर (sock == शून्य || sock->sk.sk_state != LLCP_LISTEN) अणु
			reason = LLCP_DM_NOBOUND;
			जाओ fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		u8 *sn;
		माप_प्रकार sn_len;

		sn = nfc_llcp_connect_sn(skb, &sn_len);
		अगर (sn == शून्य) अणु
			reason = LLCP_DM_NOBOUND;
			जाओ fail;
		पूर्ण

		pr_debug("Service name length %zu\n", sn_len);

		sock = nfc_llcp_sock_get_sn(local, sn, sn_len);
		अगर (sock == शून्य) अणु
			reason = LLCP_DM_NOBOUND;
			जाओ fail;
		पूर्ण
	पूर्ण

	lock_sock(&sock->sk);

	parent = &sock->sk;

	अगर (sk_acceptq_is_full(parent)) अणु
		reason = LLCP_DM_REJ;
		release_sock(&sock->sk);
		sock_put(&sock->sk);
		जाओ fail;
	पूर्ण

	अगर (sock->ssap == LLCP_SDP_UNBOUND) अणु
		u8 ssap = nfc_llcp_reserve_sdp_ssap(local);

		pr_debug("First client, reserving %d\n", ssap);

		अगर (ssap == LLCP_SAP_MAX) अणु
			reason = LLCP_DM_REJ;
			release_sock(&sock->sk);
			sock_put(&sock->sk);
			जाओ fail;
		पूर्ण

		sock->ssap = ssap;
	पूर्ण

	new_sk = nfc_llcp_sock_alloc(शून्य, parent->sk_type, GFP_ATOMIC, 0);
	अगर (new_sk == शून्य) अणु
		reason = LLCP_DM_REJ;
		release_sock(&sock->sk);
		sock_put(&sock->sk);
		जाओ fail;
	पूर्ण

	new_sock = nfc_llcp_sock(new_sk);
	new_sock->dev = local->dev;
	new_sock->local = nfc_llcp_local_get(local);
	new_sock->rw = sock->rw;
	new_sock->miux = sock->miux;
	new_sock->nfc_protocol = sock->nfc_protocol;
	new_sock->dsap = ssap;
	new_sock->target_idx = local->target_idx;
	new_sock->parent = parent;
	new_sock->ssap = sock->ssap;
	अगर (sock->ssap < LLCP_LOCAL_NUM_SAP && sock->ssap >= LLCP_WKS_NUM_SAP) अणु
		atomic_t *client_count;

		pr_debug("reserved_ssap %d for %p\n", sock->ssap, new_sock);

		client_count =
			&local->local_sdp_cnt[sock->ssap - LLCP_WKS_NUM_SAP];

		atomic_inc(client_count);
		new_sock->reserved_ssap = sock->ssap;
	पूर्ण

	nfc_llcp_parse_connection_tlv(new_sock, &skb->data[LLCP_HEADER_SIZE],
				      skb->len - LLCP_HEADER_SIZE);

	pr_debug("new sock %p sk %p\n", new_sock, &new_sock->sk);

	nfc_llcp_sock_link(&local->sockets, new_sk);

	nfc_llcp_accept_enqueue(&sock->sk, new_sk);

	nfc_get_device(local->dev->idx);

	new_sk->sk_state = LLCP_CONNECTED;

	/* Wake the listening processes */
	parent->sk_data_पढ़ोy(parent);

	/* Send CC */
	nfc_llcp_send_cc(new_sock);

	release_sock(&sock->sk);
	sock_put(&sock->sk);

	वापस;

fail:
	/* Send DM */
	nfc_llcp_send_dm(local, dsap, ssap, reason);
पूर्ण

पूर्णांक nfc_llcp_queue_i_frames(काष्ठा nfc_llcp_sock *sock)
अणु
	पूर्णांक nr_frames = 0;
	काष्ठा nfc_llcp_local *local = sock->local;

	pr_debug("Remote ready %d tx queue len %d remote rw %d",
		 sock->remote_पढ़ोy, skb_queue_len(&sock->tx_pending_queue),
		 sock->remote_rw);

	/* Try to queue some I frames क्रम transmission */
	जबतक (sock->remote_पढ़ोy &&
	       skb_queue_len(&sock->tx_pending_queue) < sock->remote_rw) अणु
		काष्ठा sk_buff *pdu;

		pdu = skb_dequeue(&sock->tx_queue);
		अगर (pdu == शून्य)
			अवरोध;

		/* Update N(S)/N(R) */
		nfc_llcp_set_nrns(sock, pdu);

		skb_queue_tail(&local->tx_queue, pdu);
		nr_frames++;
	पूर्ण

	वापस nr_frames;
पूर्ण

अटल व्योम nfc_llcp_recv_hdlc(काष्ठा nfc_llcp_local *local,
			       काष्ठा sk_buff *skb)
अणु
	काष्ठा nfc_llcp_sock *llcp_sock;
	काष्ठा sock *sk;
	u8 dsap, ssap, ptype, ns, nr;

	ptype = nfc_llcp_ptype(skb);
	dsap = nfc_llcp_dsap(skb);
	ssap = nfc_llcp_ssap(skb);
	ns = nfc_llcp_ns(skb);
	nr = nfc_llcp_nr(skb);

	pr_debug("%d %d R %d S %d\n", dsap, ssap, nr, ns);

	llcp_sock = nfc_llcp_sock_get(local, dsap, ssap);
	अगर (llcp_sock == शून्य) अणु
		nfc_llcp_send_dm(local, dsap, ssap, LLCP_DM_NOCONN);
		वापस;
	पूर्ण

	sk = &llcp_sock->sk;
	lock_sock(sk);
	अगर (sk->sk_state == LLCP_CLOSED) अणु
		release_sock(sk);
		nfc_llcp_sock_put(llcp_sock);
	पूर्ण

	/* Pass the payload upstream */
	अगर (ptype == LLCP_PDU_I) अणु
		pr_debug("I frame, queueing on %p\n", &llcp_sock->sk);

		अगर (ns == llcp_sock->recv_n)
			llcp_sock->recv_n = (llcp_sock->recv_n + 1) % 16;
		अन्यथा
			pr_err("Received out of sequence I PDU\n");

		skb_pull(skb, LLCP_HEADER_SIZE + LLCP_SEQUENCE_SIZE);
		अगर (!sock_queue_rcv_skb(&llcp_sock->sk, skb)) अणु
			/*
			 * I frames will be मुक्तd from the socket layer, so we
			 * need to keep them alive until someone receives them.
			 */
			skb_get(skb);
		पूर्ण अन्यथा अणु
			pr_err("Receive queue is full\n");
		पूर्ण
	पूर्ण

	/* Remove skbs from the pending queue */
	अगर (llcp_sock->send_ack_n != nr) अणु
		काष्ठा sk_buff *s, *पंचांगp;
		u8 n;

		llcp_sock->send_ack_n = nr;

		/* Remove and मुक्त all skbs until ns == nr */
		skb_queue_walk_safe(&llcp_sock->tx_pending_queue, s, पंचांगp) अणु
			n = nfc_llcp_ns(s);

			skb_unlink(s, &llcp_sock->tx_pending_queue);
			kमुक्त_skb(s);

			अगर (n == nr)
				अवरोध;
		पूर्ण

		/* Re-queue the reमुख्यing skbs क्रम transmission */
		skb_queue_reverse_walk_safe(&llcp_sock->tx_pending_queue,
					    s, पंचांगp) अणु
			skb_unlink(s, &llcp_sock->tx_pending_queue);
			skb_queue_head(&local->tx_queue, s);
		पूर्ण
	पूर्ण

	अगर (ptype == LLCP_PDU_RR)
		llcp_sock->remote_पढ़ोy = true;
	अन्यथा अगर (ptype == LLCP_PDU_RNR)
		llcp_sock->remote_पढ़ोy = false;

	अगर (nfc_llcp_queue_i_frames(llcp_sock) == 0 && ptype == LLCP_PDU_I)
		nfc_llcp_send_rr(llcp_sock);

	release_sock(sk);
	nfc_llcp_sock_put(llcp_sock);
पूर्ण

अटल व्योम nfc_llcp_recv_disc(काष्ठा nfc_llcp_local *local,
			       काष्ठा sk_buff *skb)
अणु
	काष्ठा nfc_llcp_sock *llcp_sock;
	काष्ठा sock *sk;
	u8 dsap, ssap;

	dsap = nfc_llcp_dsap(skb);
	ssap = nfc_llcp_ssap(skb);

	अगर ((dsap == 0) && (ssap == 0)) अणु
		pr_debug("Connection termination");
		nfc_dep_link_करोwn(local->dev);
		वापस;
	पूर्ण

	llcp_sock = nfc_llcp_sock_get(local, dsap, ssap);
	अगर (llcp_sock == शून्य) अणु
		nfc_llcp_send_dm(local, dsap, ssap, LLCP_DM_NOCONN);
		वापस;
	पूर्ण

	sk = &llcp_sock->sk;
	lock_sock(sk);

	nfc_llcp_socket_purge(llcp_sock);

	अगर (sk->sk_state == LLCP_CLOSED) अणु
		release_sock(sk);
		nfc_llcp_sock_put(llcp_sock);
	पूर्ण

	अगर (sk->sk_state == LLCP_CONNECTED) अणु
		nfc_put_device(local->dev);
		sk->sk_state = LLCP_CLOSED;
		sk->sk_state_change(sk);
	पूर्ण

	nfc_llcp_send_dm(local, dsap, ssap, LLCP_DM_DISC);

	release_sock(sk);
	nfc_llcp_sock_put(llcp_sock);
पूर्ण

अटल व्योम nfc_llcp_recv_cc(काष्ठा nfc_llcp_local *local, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfc_llcp_sock *llcp_sock;
	काष्ठा sock *sk;
	u8 dsap, ssap;

	dsap = nfc_llcp_dsap(skb);
	ssap = nfc_llcp_ssap(skb);

	llcp_sock = nfc_llcp_connecting_sock_get(local, dsap);
	अगर (llcp_sock == शून्य) अणु
		pr_err("Invalid CC\n");
		nfc_llcp_send_dm(local, dsap, ssap, LLCP_DM_NOCONN);

		वापस;
	पूर्ण

	sk = &llcp_sock->sk;

	/* Unlink from connecting and link to the client array */
	nfc_llcp_sock_unlink(&local->connecting_sockets, sk);
	nfc_llcp_sock_link(&local->sockets, sk);
	llcp_sock->dsap = ssap;

	nfc_llcp_parse_connection_tlv(llcp_sock, &skb->data[LLCP_HEADER_SIZE],
				      skb->len - LLCP_HEADER_SIZE);

	sk->sk_state = LLCP_CONNECTED;
	sk->sk_state_change(sk);

	nfc_llcp_sock_put(llcp_sock);
पूर्ण

अटल व्योम nfc_llcp_recv_dm(काष्ठा nfc_llcp_local *local, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfc_llcp_sock *llcp_sock;
	काष्ठा sock *sk;
	u8 dsap, ssap, reason;

	dsap = nfc_llcp_dsap(skb);
	ssap = nfc_llcp_ssap(skb);
	reason = skb->data[2];

	pr_debug("%d %d reason %d\n", ssap, dsap, reason);

	चयन (reason) अणु
	हाल LLCP_DM_NOBOUND:
	हाल LLCP_DM_REJ:
		llcp_sock = nfc_llcp_connecting_sock_get(local, dsap);
		अवरोध;

	शेष:
		llcp_sock = nfc_llcp_sock_get(local, dsap, ssap);
		अवरोध;
	पूर्ण

	अगर (llcp_sock == शून्य) अणु
		pr_debug("Already closed\n");
		वापस;
	पूर्ण

	sk = &llcp_sock->sk;

	sk->sk_err = ENXIO;
	sk->sk_state = LLCP_CLOSED;
	sk->sk_state_change(sk);

	nfc_llcp_sock_put(llcp_sock);
पूर्ण

अटल व्योम nfc_llcp_recv_snl(काष्ठा nfc_llcp_local *local,
			      काष्ठा sk_buff *skb)
अणु
	काष्ठा nfc_llcp_sock *llcp_sock;
	u8 dsap, ssap, *tlv, type, length, tid, sap;
	u16 tlv_len, offset;
	अक्षर *service_name;
	माप_प्रकार service_name_len;
	काष्ठा nfc_llcp_sdp_tlv *sdp;
	HLIST_HEAD(llc_sdres_list);
	माप_प्रकार sdres_tlvs_len;
	HLIST_HEAD(nl_sdres_list);

	dsap = nfc_llcp_dsap(skb);
	ssap = nfc_llcp_ssap(skb);

	pr_debug("%d %d\n", dsap, ssap);

	अगर (dsap != LLCP_SAP_SDP || ssap != LLCP_SAP_SDP) अणु
		pr_err("Wrong SNL SAP\n");
		वापस;
	पूर्ण

	tlv = &skb->data[LLCP_HEADER_SIZE];
	tlv_len = skb->len - LLCP_HEADER_SIZE;
	offset = 0;
	sdres_tlvs_len = 0;

	जबतक (offset < tlv_len) अणु
		type = tlv[0];
		length = tlv[1];

		चयन (type) अणु
		हाल LLCP_TLV_SDREQ:
			tid = tlv[2];
			service_name = (अक्षर *) &tlv[3];
			service_name_len = length - 1;

			pr_debug("Looking for %.16s\n", service_name);

			अगर (service_name_len == म_माप("urn:nfc:sn:sdp") &&
			    !म_भेदन(service_name, "urn:nfc:sn:sdp",
				     service_name_len)) अणु
				sap = 1;
				जाओ add_snl;
			पूर्ण

			llcp_sock = nfc_llcp_sock_from_sn(local, service_name,
							  service_name_len);
			अगर (!llcp_sock) अणु
				sap = 0;
				जाओ add_snl;
			पूर्ण

			/*
			 * We found a socket but its ssap has not been reserved
			 * yet. We need to assign it क्रम good and send a reply.
			 * The ssap will be मुक्तd when the socket is बंदd.
			 */
			अगर (llcp_sock->ssap == LLCP_SDP_UNBOUND) अणु
				atomic_t *client_count;

				sap = nfc_llcp_reserve_sdp_ssap(local);

				pr_debug("Reserving %d\n", sap);

				अगर (sap == LLCP_SAP_MAX) अणु
					sap = 0;
					जाओ add_snl;
				पूर्ण

				client_count =
					&local->local_sdp_cnt[sap -
							      LLCP_WKS_NUM_SAP];

				atomic_inc(client_count);

				llcp_sock->ssap = sap;
				llcp_sock->reserved_ssap = sap;
			पूर्ण अन्यथा अणु
				sap = llcp_sock->ssap;
			पूर्ण

			pr_debug("%p %d\n", llcp_sock, sap);

add_snl:
			sdp = nfc_llcp_build_sdres_tlv(tid, sap);
			अगर (sdp == शून्य)
				जाओ निकास;

			sdres_tlvs_len += sdp->tlv_len;
			hlist_add_head(&sdp->node, &llc_sdres_list);
			अवरोध;

		हाल LLCP_TLV_SDRES:
			mutex_lock(&local->sdreq_lock);

			pr_debug("LLCP_TLV_SDRES: searching tid %d\n", tlv[2]);

			hlist_क्रम_each_entry(sdp, &local->pending_sdreqs, node) अणु
				अगर (sdp->tid != tlv[2])
					जारी;

				sdp->sap = tlv[3];

				pr_debug("Found: uri=%s, sap=%d\n",
					 sdp->uri, sdp->sap);

				hlist_del(&sdp->node);

				hlist_add_head(&sdp->node, &nl_sdres_list);

				अवरोध;
			पूर्ण

			mutex_unlock(&local->sdreq_lock);
			अवरोध;

		शेष:
			pr_err("Invalid SNL tlv value 0x%x\n", type);
			अवरोध;
		पूर्ण

		offset += length + 2;
		tlv += length + 2;
	पूर्ण

निकास:
	अगर (!hlist_empty(&nl_sdres_list))
		nfc_genl_llc_send_sdres(local->dev, &nl_sdres_list);

	अगर (!hlist_empty(&llc_sdres_list))
		nfc_llcp_send_snl_sdres(local, &llc_sdres_list, sdres_tlvs_len);
पूर्ण

अटल व्योम nfc_llcp_recv_agf(काष्ठा nfc_llcp_local *local, काष्ठा sk_buff *skb)
अणु
	u8 ptype;
	u16 pdu_len;
	काष्ठा sk_buff *new_skb;

	अगर (skb->len <= LLCP_HEADER_SIZE) अणु
		pr_err("Malformed AGF PDU\n");
		वापस;
	पूर्ण

	skb_pull(skb, LLCP_HEADER_SIZE);

	जबतक (skb->len > LLCP_AGF_PDU_HEADER_SIZE) अणु
		pdu_len = skb->data[0] << 8 | skb->data[1];

		skb_pull(skb, LLCP_AGF_PDU_HEADER_SIZE);

		अगर (pdu_len < LLCP_HEADER_SIZE || pdu_len > skb->len) अणु
			pr_err("Malformed AGF PDU\n");
			वापस;
		पूर्ण

		ptype = nfc_llcp_ptype(skb);

		अगर (ptype == LLCP_PDU_SYMM || ptype == LLCP_PDU_AGF)
			जाओ next;

		new_skb = nfc_alloc_recv_skb(pdu_len, GFP_KERNEL);
		अगर (new_skb == शून्य) अणु
			pr_err("Could not allocate PDU\n");
			वापस;
		पूर्ण

		skb_put_data(new_skb, skb->data, pdu_len);

		nfc_llcp_rx_skb(local, new_skb);

		kमुक्त_skb(new_skb);
next:
		skb_pull(skb, pdu_len);
	पूर्ण
पूर्ण

अटल व्योम nfc_llcp_rx_skb(काष्ठा nfc_llcp_local *local, काष्ठा sk_buff *skb)
अणु
	u8 dsap, ssap, ptype;

	ptype = nfc_llcp_ptype(skb);
	dsap = nfc_llcp_dsap(skb);
	ssap = nfc_llcp_ssap(skb);

	pr_debug("ptype 0x%x dsap 0x%x ssap 0x%x\n", ptype, dsap, ssap);

	अगर (ptype != LLCP_PDU_SYMM)
		prपूर्णांक_hex_dump_debug("LLCP Rx: ", DUMP_PREFIX_OFFSET, 16, 1,
				     skb->data, skb->len, true);

	चयन (ptype) अणु
	हाल LLCP_PDU_SYMM:
		pr_debug("SYMM\n");
		अवरोध;

	हाल LLCP_PDU_UI:
		pr_debug("UI\n");
		nfc_llcp_recv_ui(local, skb);
		अवरोध;

	हाल LLCP_PDU_CONNECT:
		pr_debug("CONNECT\n");
		nfc_llcp_recv_connect(local, skb);
		अवरोध;

	हाल LLCP_PDU_DISC:
		pr_debug("DISC\n");
		nfc_llcp_recv_disc(local, skb);
		अवरोध;

	हाल LLCP_PDU_CC:
		pr_debug("CC\n");
		nfc_llcp_recv_cc(local, skb);
		अवरोध;

	हाल LLCP_PDU_DM:
		pr_debug("DM\n");
		nfc_llcp_recv_dm(local, skb);
		अवरोध;

	हाल LLCP_PDU_SNL:
		pr_debug("SNL\n");
		nfc_llcp_recv_snl(local, skb);
		अवरोध;

	हाल LLCP_PDU_I:
	हाल LLCP_PDU_RR:
	हाल LLCP_PDU_RNR:
		pr_debug("I frame\n");
		nfc_llcp_recv_hdlc(local, skb);
		अवरोध;

	हाल LLCP_PDU_AGF:
		pr_debug("AGF frame\n");
		nfc_llcp_recv_agf(local, skb);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम nfc_llcp_rx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nfc_llcp_local *local = container_of(work, काष्ठा nfc_llcp_local,
						    rx_work);
	काष्ठा sk_buff *skb;

	skb = local->rx_pending;
	अगर (skb == शून्य) अणु
		pr_debug("No pending SKB\n");
		वापस;
	पूर्ण

	__net_बारtamp(skb);

	nfc_llcp_send_to_raw_sock(local, skb, NFC_सूचीECTION_RX);

	nfc_llcp_rx_skb(local, skb);

	schedule_work(&local->tx_work);
	kमुक्त_skb(local->rx_pending);
	local->rx_pending = शून्य;
पूर्ण

अटल व्योम __nfc_llcp_recv(काष्ठा nfc_llcp_local *local, काष्ठा sk_buff *skb)
अणु
	local->rx_pending = skb;
	del_समयr(&local->link_समयr);
	schedule_work(&local->rx_work);
पूर्ण

व्योम nfc_llcp_recv(व्योम *data, काष्ठा sk_buff *skb, पूर्णांक err)
अणु
	काष्ठा nfc_llcp_local *local = (काष्ठा nfc_llcp_local *) data;

	pr_debug("Received an LLCP PDU\n");
	अगर (err < 0) अणु
		pr_err("err %d\n", err);
		वापस;
	पूर्ण

	__nfc_llcp_recv(local, skb);
पूर्ण

पूर्णांक nfc_llcp_data_received(काष्ठा nfc_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfc_llcp_local *local;

	local = nfc_llcp_find_local(dev);
	अगर (local == शून्य) अणु
		kमुक्त_skb(skb);
		वापस -ENODEV;
	पूर्ण

	__nfc_llcp_recv(local, skb);

	वापस 0;
पूर्ण

व्योम nfc_llcp_mac_is_करोwn(काष्ठा nfc_dev *dev)
अणु
	काष्ठा nfc_llcp_local *local;

	local = nfc_llcp_find_local(dev);
	अगर (local == शून्य)
		वापस;

	local->remote_miu = LLCP_DEFAULT_MIU;
	local->remote_lto = LLCP_DEFAULT_LTO;

	/* Close and purge all existing sockets */
	nfc_llcp_socket_release(local, true, 0);
पूर्ण

व्योम nfc_llcp_mac_is_up(काष्ठा nfc_dev *dev, u32 target_idx,
			u8 comm_mode, u8 rf_mode)
अणु
	काष्ठा nfc_llcp_local *local;

	pr_debug("rf mode %d\n", rf_mode);

	local = nfc_llcp_find_local(dev);
	अगर (local == शून्य)
		वापस;

	local->target_idx = target_idx;
	local->comm_mode = comm_mode;
	local->rf_mode = rf_mode;

	अगर (rf_mode == NFC_RF_INITIATOR) अणु
		pr_debug("Queueing Tx work\n");

		schedule_work(&local->tx_work);
	पूर्ण अन्यथा अणु
		mod_समयr(&local->link_समयr,
			  jअगरfies + msecs_to_jअगरfies(local->remote_lto));
	पूर्ण
पूर्ण

पूर्णांक nfc_llcp_रेजिस्टर_device(काष्ठा nfc_dev *ndev)
अणु
	काष्ठा nfc_llcp_local *local;

	local = kzalloc(माप(काष्ठा nfc_llcp_local), GFP_KERNEL);
	अगर (local == शून्य)
		वापस -ENOMEM;

	local->dev = ndev;
	INIT_LIST_HEAD(&local->list);
	kref_init(&local->ref);
	mutex_init(&local->sdp_lock);
	समयr_setup(&local->link_समयr, nfc_llcp_symm_समयr, 0);

	skb_queue_head_init(&local->tx_queue);
	INIT_WORK(&local->tx_work, nfc_llcp_tx_work);

	local->rx_pending = शून्य;
	INIT_WORK(&local->rx_work, nfc_llcp_rx_work);

	INIT_WORK(&local->समयout_work, nfc_llcp_समयout_work);

	rwlock_init(&local->sockets.lock);
	rwlock_init(&local->connecting_sockets.lock);
	rwlock_init(&local->raw_sockets.lock);

	local->lto = 150; /* 1500 ms */
	local->rw = LLCP_MAX_RW;
	local->miux = cpu_to_be16(LLCP_MAX_MIUX);
	local->local_wks = 0x1; /* LLC Link Management */

	nfc_llcp_build_gb(local);

	local->remote_miu = LLCP_DEFAULT_MIU;
	local->remote_lto = LLCP_DEFAULT_LTO;

	mutex_init(&local->sdreq_lock);
	INIT_HLIST_HEAD(&local->pending_sdreqs);
	समयr_setup(&local->sdreq_समयr, nfc_llcp_sdreq_समयr, 0);
	INIT_WORK(&local->sdreq_समयout_work, nfc_llcp_sdreq_समयout_work);

	list_add(&local->list, &llcp_devices);

	वापस 0;
पूर्ण

व्योम nfc_llcp_unरेजिस्टर_device(काष्ठा nfc_dev *dev)
अणु
	काष्ठा nfc_llcp_local *local = nfc_llcp_find_local(dev);

	अगर (local == शून्य) अणु
		pr_debug("No such device\n");
		वापस;
	पूर्ण

	local_cleanup(local);

	nfc_llcp_local_put(local);
पूर्ण

पूर्णांक __init nfc_llcp_init(व्योम)
अणु
	वापस nfc_llcp_sock_init();
पूर्ण

व्योम nfc_llcp_निकास(व्योम)
अणु
	nfc_llcp_sock_निकास();
पूर्ण
