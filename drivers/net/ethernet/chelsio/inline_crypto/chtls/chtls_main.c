<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2018 Chelsio Communications, Inc.
 *
 * Written by: Atul Gupta (atul.gupta@chelsio.com)
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/socket.h>
#समावेश <linux/hash.h>
#समावेश <linux/in.h>
#समावेश <linux/net.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <net/ipv6.h>
#समावेश <net/transp_v6.h>
#समावेश <net/tcp.h>
#समावेश <net/tls.h>

#समावेश "chtls.h"
#समावेश "chtls_cm.h"

#घोषणा DRV_NAME "chtls"

/*
 * chtls device management
 * मुख्यtains a list of the chtls devices
 */
अटल LIST_HEAD(cdev_list);
अटल DEFINE_MUTEX(cdev_mutex);

अटल DEFINE_MUTEX(notअगरy_mutex);
अटल RAW_NOTIFIER_HEAD(listen_notअगरy_list);
अटल काष्ठा proto chtls_cpl_prot, chtls_cpl_protv6;
काष्ठा request_sock_ops chtls_rsk_ops, chtls_rsk_opsv6;
अटल uपूर्णांक send_page_order = (14 - PAGE_SHIFT < 0) ? 0 : 14 - PAGE_SHIFT;

अटल व्योम रेजिस्टर_listen_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	mutex_lock(&notअगरy_mutex);
	raw_notअगरier_chain_रेजिस्टर(&listen_notअगरy_list, nb);
	mutex_unlock(&notअगरy_mutex);
पूर्ण

अटल व्योम unरेजिस्टर_listen_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	mutex_lock(&notअगरy_mutex);
	raw_notअगरier_chain_unरेजिस्टर(&listen_notअगरy_list, nb);
	mutex_unlock(&notअगरy_mutex);
पूर्ण

अटल पूर्णांक listen_notअगरy_handler(काष्ठा notअगरier_block *this,
				 अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा chtls_listen *clisten;
	पूर्णांक ret = NOTIFY_DONE;

	clisten = (काष्ठा chtls_listen *)data;

	चयन (event) अणु
	हाल CHTLS_LISTEN_START:
		ret = chtls_listen_start(clisten->cdev, clisten->sk);
		kमुक्त(clisten);
		अवरोध;
	हाल CHTLS_LISTEN_STOP:
		chtls_listen_stop(clisten->cdev, clisten->sk);
		kमुक्त(clisten);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा notअगरier_block listen_notअगरier = अणु
	.notअगरier_call = listen_notअगरy_handler
पूर्ण;

अटल पूर्णांक listen_backlog_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	अगर (likely(skb_transport_header(skb) != skb_network_header(skb)))
		वापस tcp_v4_करो_rcv(sk, skb);
	BLOG_SKB_CB(skb)->backlog_rcv(sk, skb);
	वापस 0;
पूर्ण

अटल पूर्णांक chtls_start_listen(काष्ठा chtls_dev *cdev, काष्ठा sock *sk)
अणु
	काष्ठा chtls_listen *clisten;

	अगर (sk->sk_protocol != IPPROTO_TCP)
		वापस -EPROTONOSUPPORT;

	अगर (sk->sk_family == PF_INET &&
	    LOOPBACK(inet_sk(sk)->inet_rcv_saddr))
		वापस -EADDRNOTAVAIL;

	sk->sk_backlog_rcv = listen_backlog_rcv;
	clisten = kदो_स्मृति(माप(*clisten), GFP_KERNEL);
	अगर (!clisten)
		वापस -ENOMEM;
	clisten->cdev = cdev;
	clisten->sk = sk;
	mutex_lock(&notअगरy_mutex);
	raw_notअगरier_call_chain(&listen_notअगरy_list,
				      CHTLS_LISTEN_START, clisten);
	mutex_unlock(&notअगरy_mutex);
	वापस 0;
पूर्ण

अटल व्योम chtls_stop_listen(काष्ठा chtls_dev *cdev, काष्ठा sock *sk)
अणु
	काष्ठा chtls_listen *clisten;

	अगर (sk->sk_protocol != IPPROTO_TCP)
		वापस;

	clisten = kदो_स्मृति(माप(*clisten), GFP_KERNEL);
	अगर (!clisten)
		वापस;
	clisten->cdev = cdev;
	clisten->sk = sk;
	mutex_lock(&notअगरy_mutex);
	raw_notअगरier_call_chain(&listen_notअगरy_list,
				CHTLS_LISTEN_STOP, clisten);
	mutex_unlock(&notअगरy_mutex);
पूर्ण

अटल पूर्णांक chtls_अंतरभूत_feature(काष्ठा tls_toe_device *dev)
अणु
	काष्ठा net_device *netdev;
	काष्ठा chtls_dev *cdev;
	पूर्णांक i;

	cdev = to_chtls_dev(dev);

	क्रम (i = 0; i < cdev->lldi->nports; i++) अणु
		netdev = cdev->ports[i];
		अगर (netdev->features & NETIF_F_HW_TLS_RECORD)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक chtls_create_hash(काष्ठा tls_toe_device *dev, काष्ठा sock *sk)
अणु
	काष्ठा chtls_dev *cdev = to_chtls_dev(dev);

	अगर (sk->sk_state == TCP_LISTEN)
		वापस chtls_start_listen(cdev, sk);
	वापस 0;
पूर्ण

अटल व्योम chtls_destroy_hash(काष्ठा tls_toe_device *dev, काष्ठा sock *sk)
अणु
	काष्ठा chtls_dev *cdev = to_chtls_dev(dev);

	अगर (sk->sk_state == TCP_LISTEN)
		chtls_stop_listen(cdev, sk);
पूर्ण

अटल व्योम chtls_मुक्त_uld(काष्ठा chtls_dev *cdev)
अणु
	पूर्णांक i;

	tls_toe_unरेजिस्टर_device(&cdev->tlsdev);
	kvमुक्त(cdev->kmap.addr);
	idr_destroy(&cdev->hwtid_idr);
	क्रम (i = 0; i < (1 << RSPQ_HASH_BITS); i++)
		kमुक्त_skb(cdev->rspq_skb_cache[i]);
	kमुक्त(cdev->lldi);
	kमुक्त_skb(cdev->askb);
	kमुक्त(cdev);
पूर्ण

अटल अंतरभूत व्योम chtls_dev_release(काष्ठा kref *kref)
अणु
	काष्ठा tls_toe_device *dev;
	काष्ठा chtls_dev *cdev;
	काष्ठा adapter *adap;

	dev = container_of(kref, काष्ठा tls_toe_device, kref);
	cdev = to_chtls_dev(dev);

	/* Reset tls rx/tx stats */
	adap = pci_get_drvdata(cdev->pdev);
	atomic_set(&adap->chcr_stats.tls_pdu_tx, 0);
	atomic_set(&adap->chcr_stats.tls_pdu_rx, 0);

	chtls_मुक्त_uld(cdev);
पूर्ण

अटल व्योम chtls_रेजिस्टर_dev(काष्ठा chtls_dev *cdev)
अणु
	काष्ठा tls_toe_device *tlsdev = &cdev->tlsdev;

	strlcpy(tlsdev->name, "chtls", TLS_TOE_DEVICE_NAME_MAX);
	strlcat(tlsdev->name, cdev->lldi->ports[0]->name,
		TLS_TOE_DEVICE_NAME_MAX);
	tlsdev->feature = chtls_अंतरभूत_feature;
	tlsdev->hash = chtls_create_hash;
	tlsdev->unhash = chtls_destroy_hash;
	tlsdev->release = chtls_dev_release;
	kref_init(&tlsdev->kref);
	tls_toe_रेजिस्टर_device(tlsdev);
	cdev->cdev_state = CHTLS_CDEV_STATE_UP;
पूर्ण

अटल व्योम process_deferq(काष्ठा work_काष्ठा *task_param)
अणु
	काष्ठा chtls_dev *cdev = container_of(task_param,
				काष्ठा chtls_dev, deferq_task);
	काष्ठा sk_buff *skb;

	spin_lock_bh(&cdev->deferq.lock);
	जबतक ((skb = __skb_dequeue(&cdev->deferq)) != शून्य) अणु
		spin_unlock_bh(&cdev->deferq.lock);
		DEFERRED_SKB_CB(skb)->handler(cdev, skb);
		spin_lock_bh(&cdev->deferq.lock);
	पूर्ण
	spin_unlock_bh(&cdev->deferq.lock);
पूर्ण

अटल पूर्णांक chtls_get_skb(काष्ठा chtls_dev *cdev)
अणु
	cdev->askb = alloc_skb(माप(काष्ठा tcphdr), GFP_KERNEL);
	अगर (!cdev->askb)
		वापस -ENOMEM;

	skb_put(cdev->askb, माप(काष्ठा tcphdr));
	skb_reset_transport_header(cdev->askb);
	स_रखो(cdev->askb->data, 0, cdev->askb->len);
	वापस 0;
पूर्ण

अटल व्योम *chtls_uld_add(स्थिर काष्ठा cxgb4_lld_info *info)
अणु
	काष्ठा cxgb4_lld_info *lldi;
	काष्ठा chtls_dev *cdev;
	पूर्णांक i, j;

	cdev = kzalloc(माप(*cdev), GFP_KERNEL);
	अगर (!cdev)
		जाओ out;

	lldi = kzalloc(माप(*lldi), GFP_KERNEL);
	अगर (!lldi)
		जाओ out_lldi;

	अगर (chtls_get_skb(cdev))
		जाओ out_skb;

	*lldi = *info;
	cdev->lldi = lldi;
	cdev->pdev = lldi->pdev;
	cdev->tids = lldi->tids;
	cdev->ports = lldi->ports;
	cdev->mtus = lldi->mtus;
	cdev->tids = lldi->tids;
	cdev->pfvf = FW_VIID_PFN_G(cxgb4_port_viid(lldi->ports[0]))
			<< FW_VIID_PFN_S;

	क्रम (i = 0; i < (1 << RSPQ_HASH_BITS); i++) अणु
		अचिन्हित पूर्णांक size = 64 - माप(काष्ठा rsp_ctrl) - 8;

		cdev->rspq_skb_cache[i] = __alloc_skb(size,
						      gfp_any(), 0,
						      lldi->nodeid);
		अगर (unlikely(!cdev->rspq_skb_cache[i]))
			जाओ out_rspq_skb;
	पूर्ण

	idr_init(&cdev->hwtid_idr);
	INIT_WORK(&cdev->deferq_task, process_deferq);
	spin_lock_init(&cdev->listen_lock);
	spin_lock_init(&cdev->idr_lock);
	cdev->send_page_order = min_t(uपूर्णांक, get_order(32768),
				      send_page_order);
	cdev->max_host_sndbuf = 48 * 1024;

	अगर (lldi->vr->key.size)
		अगर (chtls_init_kmap(cdev, lldi))
			जाओ out_rspq_skb;

	mutex_lock(&cdev_mutex);
	list_add_tail(&cdev->list, &cdev_list);
	mutex_unlock(&cdev_mutex);

	वापस cdev;
out_rspq_skb:
	क्रम (j = 0; j < i; j++)
		kमुक्त_skb(cdev->rspq_skb_cache[j]);
	kमुक्त_skb(cdev->askb);
out_skb:
	kमुक्त(lldi);
out_lldi:
	kमुक्त(cdev);
out:
	वापस शून्य;
पूर्ण

अटल व्योम chtls_मुक्त_all_uld(व्योम)
अणु
	काष्ठा chtls_dev *cdev, *पंचांगp;

	mutex_lock(&cdev_mutex);
	list_क्रम_each_entry_safe(cdev, पंचांगp, &cdev_list, list) अणु
		अगर (cdev->cdev_state == CHTLS_CDEV_STATE_UP) अणु
			list_del(&cdev->list);
			kref_put(&cdev->tlsdev.kref, cdev->tlsdev.release);
		पूर्ण
	पूर्ण
	mutex_unlock(&cdev_mutex);
पूर्ण

अटल पूर्णांक chtls_uld_state_change(व्योम *handle, क्रमागत cxgb4_state new_state)
अणु
	काष्ठा chtls_dev *cdev = handle;

	चयन (new_state) अणु
	हाल CXGB4_STATE_UP:
		chtls_रेजिस्टर_dev(cdev);
		अवरोध;
	हाल CXGB4_STATE_DOWN:
		अवरोध;
	हाल CXGB4_STATE_START_RECOVERY:
		अवरोध;
	हाल CXGB4_STATE_DETACH:
		mutex_lock(&cdev_mutex);
		list_del(&cdev->list);
		mutex_unlock(&cdev_mutex);
		kref_put(&cdev->tlsdev.kref, cdev->tlsdev.release);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *copy_gl_to_skb_pkt(स्थिर काष्ठा pkt_gl *gl,
					  स्थिर __be64 *rsp,
					  u32 pktshअगरt)
अणु
	काष्ठा sk_buff *skb;

	/* Allocate space क्रम cpl_pass_accpet_req which will be synthesized by
	 * driver. Once driver synthesizes cpl_pass_accpet_req the skb will go
	 * through the regular cpl_pass_accept_req processing in TOM.
	 */
	skb = alloc_skb(gl->tot_len + माप(काष्ठा cpl_pass_accept_req)
			- pktshअगरt, GFP_ATOMIC);
	अगर (unlikely(!skb))
		वापस शून्य;
	__skb_put(skb, gl->tot_len + माप(काष्ठा cpl_pass_accept_req)
		   - pktshअगरt);
	/* For now we will copy  cpl_rx_pkt in the skb */
	skb_copy_to_linear_data(skb, rsp, माप(काष्ठा cpl_rx_pkt));
	skb_copy_to_linear_data_offset(skb, माप(काष्ठा cpl_pass_accept_req)
				       , gl->va + pktshअगरt,
				       gl->tot_len - pktshअगरt);

	वापस skb;
पूर्ण

अटल पूर्णांक chtls_recv_packet(काष्ठा chtls_dev *cdev,
			     स्थिर काष्ठा pkt_gl *gl, स्थिर __be64 *rsp)
अणु
	अचिन्हित पूर्णांक opcode = *(u8 *)rsp;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = copy_gl_to_skb_pkt(gl, rsp, cdev->lldi->sge_pktshअगरt);
	अगर (!skb)
		वापस -ENOMEM;

	ret = chtls_handlers[opcode](cdev, skb);
	अगर (ret & CPL_RET_BUF_DONE)
		kमुक्त_skb(skb);

	वापस 0;
पूर्ण

अटल पूर्णांक chtls_recv_rsp(काष्ठा chtls_dev *cdev, स्थिर __be64 *rsp)
अणु
	अचिन्हित दीर्घ rspq_bin;
	अचिन्हित पूर्णांक opcode;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक len;
	पूर्णांक ret;

	len = 64 - माप(काष्ठा rsp_ctrl) - 8;
	opcode = *(u8 *)rsp;

	rspq_bin = hash_ptr((व्योम *)rsp, RSPQ_HASH_BITS);
	skb = cdev->rspq_skb_cache[rspq_bin];
	अगर (skb && !skb_is_nonlinear(skb) &&
	    !skb_shared(skb) && !skb_cloned(skb)) अणु
		refcount_inc(&skb->users);
		अगर (refcount_पढ़ो(&skb->users) == 2) अणु
			__skb_trim(skb, 0);
			अगर (skb_tailroom(skb) >= len)
				जाओ copy_out;
		पूर्ण
		refcount_dec(&skb->users);
	पूर्ण
	skb = alloc_skb(len, GFP_ATOMIC);
	अगर (unlikely(!skb))
		वापस -ENOMEM;

copy_out:
	__skb_put(skb, len);
	skb_copy_to_linear_data(skb, rsp, len);
	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);
	ret = chtls_handlers[opcode](cdev, skb);

	अगर (ret & CPL_RET_BUF_DONE)
		kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल व्योम chtls_recv(काष्ठा chtls_dev *cdev,
		       काष्ठा sk_buff **skbs, स्थिर __be64 *rsp)
अणु
	काष्ठा sk_buff *skb = *skbs;
	अचिन्हित पूर्णांक opcode;
	पूर्णांक ret;

	opcode = *(u8 *)rsp;

	__skb_push(skb, माप(काष्ठा rss_header));
	skb_copy_to_linear_data(skb, rsp, माप(काष्ठा rss_header));

	ret = chtls_handlers[opcode](cdev, skb);
	अगर (ret & CPL_RET_BUF_DONE)
		kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक chtls_uld_rx_handler(व्योम *handle, स्थिर __be64 *rsp,
				स्थिर काष्ठा pkt_gl *gl)
अणु
	काष्ठा chtls_dev *cdev = handle;
	अचिन्हित पूर्णांक opcode;
	काष्ठा sk_buff *skb;

	opcode = *(u8 *)rsp;

	अगर (unlikely(opcode == CPL_RX_PKT)) अणु
		अगर (chtls_recv_packet(cdev, gl, rsp) < 0)
			जाओ nomem;
		वापस 0;
	पूर्ण

	अगर (!gl)
		वापस chtls_recv_rsp(cdev, rsp);

#घोषणा RX_PULL_LEN 128
	skb = cxgb4_pktgl_to_skb(gl, RX_PULL_LEN, RX_PULL_LEN);
	अगर (unlikely(!skb))
		जाओ nomem;
	chtls_recv(cdev, &skb, rsp);
	वापस 0;

nomem:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक करो_chtls_माला_लोockopt(काष्ठा sock *sk, अक्षर __user *optval,
			       पूर्णांक __user *optlen)
अणु
	काष्ठा tls_crypto_info crypto_info = अणु 0 पूर्ण;

	crypto_info.version = TLS_1_2_VERSION;
	अगर (copy_to_user(optval, &crypto_info, माप(काष्ठा tls_crypto_info)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक chtls_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			    अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा tls_context *ctx = tls_get_ctx(sk);

	अगर (level != SOL_TLS)
		वापस ctx->sk_proto->माला_लोockopt(sk, level,
						 optname, optval, optlen);

	वापस करो_chtls_माला_लोockopt(sk, optval, optlen);
पूर्ण

अटल पूर्णांक करो_chtls_setsockopt(काष्ठा sock *sk, पूर्णांक optname,
			       sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा tls_crypto_info *crypto_info, पंचांगp_crypto_info;
	काष्ठा chtls_sock *csk;
	पूर्णांक keylen;
	पूर्णांक cipher_type;
	पूर्णांक rc = 0;

	csk = rcu_dereference_sk_user_data(sk);

	अगर (sockptr_is_null(optval) || optlen < माप(*crypto_info)) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	rc = copy_from_sockptr(&पंचांगp_crypto_info, optval, माप(*crypto_info));
	अगर (rc) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	/* check version */
	अगर (पंचांगp_crypto_info.version != TLS_1_2_VERSION) अणु
		rc = -ENOTSUPP;
		जाओ out;
	पूर्ण

	crypto_info = (काष्ठा tls_crypto_info *)&csk->tlshws.crypto_info;

	/* GCM mode of AES supports 128 and 256 bit encryption, so
	 * copy keys from user based on GCM cipher type.
	 */
	चयन (पंचांगp_crypto_info.cipher_type) अणु
	हाल TLS_CIPHER_AES_GCM_128: अणु
		/* Obtain version and type from previous copy */
		crypto_info[0] = पंचांगp_crypto_info;
		/* Now copy the following data */
		rc = copy_from_sockptr_offset((अक्षर *)crypto_info +
				माप(*crypto_info),
				optval, माप(*crypto_info),
				माप(काष्ठा tls12_crypto_info_aes_gcm_128)
				- माप(*crypto_info));

		अगर (rc) अणु
			rc = -EFAULT;
			जाओ out;
		पूर्ण

		keylen = TLS_CIPHER_AES_GCM_128_KEY_SIZE;
		cipher_type = TLS_CIPHER_AES_GCM_128;
		अवरोध;
	पूर्ण
	हाल TLS_CIPHER_AES_GCM_256: अणु
		crypto_info[0] = पंचांगp_crypto_info;
		rc = copy_from_sockptr_offset((अक्षर *)crypto_info +
				माप(*crypto_info),
				optval, माप(*crypto_info),
				माप(काष्ठा tls12_crypto_info_aes_gcm_256)
				- माप(*crypto_info));

		अगर (rc) अणु
			rc = -EFAULT;
			जाओ out;
		पूर्ण

		keylen = TLS_CIPHER_AES_GCM_256_KEY_SIZE;
		cipher_type = TLS_CIPHER_AES_GCM_256;
		अवरोध;
	पूर्ण
	शेष:
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	rc = chtls_setkey(csk, keylen, optname, cipher_type);
out:
	वापस rc;
पूर्ण

अटल पूर्णांक chtls_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			    sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा tls_context *ctx = tls_get_ctx(sk);

	अगर (level != SOL_TLS)
		वापस ctx->sk_proto->setsockopt(sk, level,
						 optname, optval, optlen);

	वापस करो_chtls_setsockopt(sk, optname, optval, optlen);
पूर्ण

अटल काष्ठा cxgb4_uld_info chtls_uld_info = अणु
	.name = DRV_NAME,
	.nrxq = MAX_ULD_QSETS,
	.ntxq = MAX_ULD_QSETS,
	.rxq_size = 1024,
	.add = chtls_uld_add,
	.state_change = chtls_uld_state_change,
	.rx_handler = chtls_uld_rx_handler,
पूर्ण;

व्योम chtls_install_cpl_ops(काष्ठा sock *sk)
अणु
	अगर (sk->sk_family == AF_INET)
		sk->sk_prot = &chtls_cpl_prot;
	अन्यथा
		sk->sk_prot = &chtls_cpl_protv6;
पूर्ण

अटल व्योम __init chtls_init_ulp_ops(व्योम)
अणु
	chtls_cpl_prot			= tcp_prot;
	chtls_init_rsk_ops(&chtls_cpl_prot, &chtls_rsk_ops,
			   &tcp_prot, PF_INET);
	chtls_cpl_prot.बंद		= chtls_बंद;
	chtls_cpl_prot.disconnect	= chtls_disconnect;
	chtls_cpl_prot.destroy		= chtls_destroy_sock;
	chtls_cpl_prot.shutकरोwn		= chtls_shutकरोwn;
	chtls_cpl_prot.sendmsg		= chtls_sendmsg;
	chtls_cpl_prot.sendpage		= chtls_sendpage;
	chtls_cpl_prot.recvmsg		= chtls_recvmsg;
	chtls_cpl_prot.setsockopt	= chtls_setsockopt;
	chtls_cpl_prot.माला_लोockopt	= chtls_माला_लोockopt;
#अगर IS_ENABLED(CONFIG_IPV6)
	chtls_cpl_protv6		= chtls_cpl_prot;
	chtls_init_rsk_ops(&chtls_cpl_protv6, &chtls_rsk_opsv6,
			   &tcpv6_prot, PF_INET6);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __init chtls_रेजिस्टर(व्योम)
अणु
	chtls_init_ulp_ops();
	रेजिस्टर_listen_notअगरier(&listen_notअगरier);
	cxgb4_रेजिस्टर_uld(CXGB4_ULD_TLS, &chtls_uld_info);
	वापस 0;
पूर्ण

अटल व्योम __निकास chtls_unरेजिस्टर(व्योम)
अणु
	unरेजिस्टर_listen_notअगरier(&listen_notअगरier);
	chtls_मुक्त_all_uld();
	cxgb4_unरेजिस्टर_uld(CXGB4_ULD_TLS);
पूर्ण

module_init(chtls_रेजिस्टर);
module_निकास(chtls_unरेजिस्टर);

MODULE_DESCRIPTION("Chelsio TLS Inline driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chelsio Communications");
MODULE_VERSION(CHTLS_DRV_VERSION);
