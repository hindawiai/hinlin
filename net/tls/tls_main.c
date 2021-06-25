<शैली गुरु>
/*
 * Copyright (c) 2016-2017, Mellanox Technologies. All rights reserved.
 * Copyright (c) 2016-2017, Dave Watson <davejwatson@fb.com>. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/module.h>

#समावेश <net/tcp.h>
#समावेश <net/inet_common.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/inetdevice.h>
#समावेश <linux/inet_diag.h>

#समावेश <net/snmp.h>
#समावेश <net/tls.h>
#समावेश <net/tls_toe.h>

MODULE_AUTHOR("Mellanox Technologies");
MODULE_DESCRIPTION("Transport Layer Security Support");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS_TCP_ULP("tls");

क्रमागत अणु
	TLSV4,
	TLSV6,
	TLS_NUM_PROTS,
पूर्ण;

अटल स्थिर काष्ठा proto *saved_tcpv6_prot;
अटल DEFINE_MUTEX(tcpv6_prot_mutex);
अटल स्थिर काष्ठा proto *saved_tcpv4_prot;
अटल DEFINE_MUTEX(tcpv4_prot_mutex);
अटल काष्ठा proto tls_prots[TLS_NUM_PROTS][TLS_NUM_CONFIG][TLS_NUM_CONFIG];
अटल काष्ठा proto_ops tls_sw_proto_ops;
अटल व्योम build_protos(काष्ठा proto prot[TLS_NUM_CONFIG][TLS_NUM_CONFIG],
			 स्थिर काष्ठा proto *base);

व्योम update_sk_prot(काष्ठा sock *sk, काष्ठा tls_context *ctx)
अणु
	पूर्णांक ip_ver = sk->sk_family == AF_INET6 ? TLSV6 : TLSV4;

	WRITE_ONCE(sk->sk_prot,
		   &tls_prots[ip_ver][ctx->tx_conf][ctx->rx_conf]);
पूर्ण

पूर्णांक रुको_on_pending_ग_लिखोr(काष्ठा sock *sk, दीर्घ *समयo)
अणु
	पूर्णांक rc = 0;
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);

	add_रुको_queue(sk_sleep(sk), &रुको);
	जबतक (1) अणु
		अगर (!*समयo) अणु
			rc = -EAGAIN;
			अवरोध;
		पूर्ण

		अगर (संकेत_pending(current)) अणु
			rc = sock_पूर्णांकr_त्रुटि_सं(*समयo);
			अवरोध;
		पूर्ण

		अगर (sk_रुको_event(sk, समयo, !sk->sk_ग_लिखो_pending, &रुको))
			अवरोध;
	पूर्ण
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);
	वापस rc;
पूर्ण

पूर्णांक tls_push_sg(काष्ठा sock *sk,
		काष्ठा tls_context *ctx,
		काष्ठा scatterlist *sg,
		u16 first_offset,
		पूर्णांक flags)
अणु
	पूर्णांक sendpage_flags = flags | MSG_SENDPAGE_NOTLAST;
	पूर्णांक ret = 0;
	काष्ठा page *p;
	माप_प्रकार size;
	पूर्णांक offset = first_offset;

	size = sg->length - offset;
	offset += sg->offset;

	ctx->in_tcp_sendpages = true;
	जबतक (1) अणु
		अगर (sg_is_last(sg))
			sendpage_flags = flags;

		/* is sending application-limited? */
		tcp_rate_check_app_limited(sk);
		p = sg_page(sg);
retry:
		ret = करो_tcp_sendpages(sk, p, offset, size, sendpage_flags);

		अगर (ret != size) अणु
			अगर (ret > 0) अणु
				offset += ret;
				size -= ret;
				जाओ retry;
			पूर्ण

			offset -= sg->offset;
			ctx->partially_sent_offset = offset;
			ctx->partially_sent_record = (व्योम *)sg;
			ctx->in_tcp_sendpages = false;
			वापस ret;
		पूर्ण

		put_page(p);
		sk_mem_unअक्षरge(sk, sg->length);
		sg = sg_next(sg);
		अगर (!sg)
			अवरोध;

		offset = sg->offset;
		size = sg->length;
	पूर्ण

	ctx->in_tcp_sendpages = false;

	वापस 0;
पूर्ण

अटल पूर्णांक tls_handle_खोलो_record(काष्ठा sock *sk, पूर्णांक flags)
अणु
	काष्ठा tls_context *ctx = tls_get_ctx(sk);

	अगर (tls_is_pending_खोलो_record(ctx))
		वापस ctx->push_pending_record(sk, flags);

	वापस 0;
पूर्ण

पूर्णांक tls_proccess_cmsg(काष्ठा sock *sk, काष्ठा msghdr *msg,
		      अचिन्हित अक्षर *record_type)
अणु
	काष्ठा cmsghdr *cmsg;
	पूर्णांक rc = -EINVAL;

	क्रम_each_cmsghdr(cmsg, msg) अणु
		अगर (!CMSG_OK(msg, cmsg))
			वापस -EINVAL;
		अगर (cmsg->cmsg_level != SOL_TLS)
			जारी;

		चयन (cmsg->cmsg_type) अणु
		हाल TLS_SET_RECORD_TYPE:
			अगर (cmsg->cmsg_len < CMSG_LEN(माप(*record_type)))
				वापस -EINVAL;

			अगर (msg->msg_flags & MSG_MORE)
				वापस -EINVAL;

			rc = tls_handle_खोलो_record(sk, msg->msg_flags);
			अगर (rc)
				वापस rc;

			*record_type = *(अचिन्हित अक्षर *)CMSG_DATA(cmsg);
			rc = 0;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक tls_push_partial_record(काष्ठा sock *sk, काष्ठा tls_context *ctx,
			    पूर्णांक flags)
अणु
	काष्ठा scatterlist *sg;
	u16 offset;

	sg = ctx->partially_sent_record;
	offset = ctx->partially_sent_offset;

	ctx->partially_sent_record = शून्य;
	वापस tls_push_sg(sk, ctx, sg, offset, flags);
पूर्ण

व्योम tls_मुक्त_partial_record(काष्ठा sock *sk, काष्ठा tls_context *ctx)
अणु
	काष्ठा scatterlist *sg;

	क्रम (sg = ctx->partially_sent_record; sg; sg = sg_next(sg)) अणु
		put_page(sg_page(sg));
		sk_mem_unअक्षरge(sk, sg->length);
	पूर्ण
	ctx->partially_sent_record = शून्य;
पूर्ण

अटल व्योम tls_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा tls_context *ctx = tls_get_ctx(sk);

	/* If in_tcp_sendpages call lower protocol ग_लिखो space handler
	 * to ensure we wake up any रुकोing operations there. For example
	 * अगर करो_tcp_sendpages where to call sk_रुको_event.
	 */
	अगर (ctx->in_tcp_sendpages) अणु
		ctx->sk_ग_लिखो_space(sk);
		वापस;
	पूर्ण

#अगर_घोषित CONFIG_TLS_DEVICE
	अगर (ctx->tx_conf == TLS_HW)
		tls_device_ग_लिखो_space(sk, ctx);
	अन्यथा
#पूर्ण_अगर
		tls_sw_ग_लिखो_space(sk, ctx);

	ctx->sk_ग_लिखो_space(sk);
पूर्ण

/**
 * tls_ctx_मुक्त() - मुक्त TLS ULP context
 * @sk:  socket to with @ctx is attached
 * @ctx: TLS context काष्ठाure
 *
 * Free TLS context. If @sk is %शून्य caller guarantees that the socket
 * to which @ctx was attached has no outstanding references.
 */
व्योम tls_ctx_मुक्त(काष्ठा sock *sk, काष्ठा tls_context *ctx)
अणु
	अगर (!ctx)
		वापस;

	memzero_explicit(&ctx->crypto_send, माप(ctx->crypto_send));
	memzero_explicit(&ctx->crypto_recv, माप(ctx->crypto_recv));
	mutex_destroy(&ctx->tx_lock);

	अगर (sk)
		kमुक्त_rcu(ctx, rcu);
	अन्यथा
		kमुक्त(ctx);
पूर्ण

अटल व्योम tls_sk_proto_cleanup(काष्ठा sock *sk,
				 काष्ठा tls_context *ctx, दीर्घ समयo)
अणु
	अगर (unlikely(sk->sk_ग_लिखो_pending) &&
	    !रुको_on_pending_ग_लिखोr(sk, &समयo))
		tls_handle_खोलो_record(sk, 0);

	/* We need these क्रम tls_sw_fallback handling of other packets */
	अगर (ctx->tx_conf == TLS_SW) अणु
		kमुक्त(ctx->tx.rec_seq);
		kमुक्त(ctx->tx.iv);
		tls_sw_release_resources_tx(sk);
		TLS_DEC_STATS(sock_net(sk), LINUX_MIB_TLSCURRTXSW);
	पूर्ण अन्यथा अगर (ctx->tx_conf == TLS_HW) अणु
		tls_device_मुक्त_resources_tx(sk);
		TLS_DEC_STATS(sock_net(sk), LINUX_MIB_TLSCURRTXDEVICE);
	पूर्ण

	अगर (ctx->rx_conf == TLS_SW) अणु
		tls_sw_release_resources_rx(sk);
		TLS_DEC_STATS(sock_net(sk), LINUX_MIB_TLSCURRRXSW);
	पूर्ण अन्यथा अगर (ctx->rx_conf == TLS_HW) अणु
		tls_device_offload_cleanup_rx(sk);
		TLS_DEC_STATS(sock_net(sk), LINUX_MIB_TLSCURRRXDEVICE);
	पूर्ण
पूर्ण

अटल व्योम tls_sk_proto_बंद(काष्ठा sock *sk, दीर्घ समयout)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tls_context *ctx = tls_get_ctx(sk);
	दीर्घ समयo = sock_sndसमयo(sk, 0);
	bool मुक्त_ctx;

	अगर (ctx->tx_conf == TLS_SW)
		tls_sw_cancel_work_tx(ctx);

	lock_sock(sk);
	मुक्त_ctx = ctx->tx_conf != TLS_HW && ctx->rx_conf != TLS_HW;

	अगर (ctx->tx_conf != TLS_BASE || ctx->rx_conf != TLS_BASE)
		tls_sk_proto_cleanup(sk, ctx, समयo);

	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	अगर (मुक्त_ctx)
		rcu_assign_poपूर्णांकer(icsk->icsk_ulp_data, शून्य);
	WRITE_ONCE(sk->sk_prot, ctx->sk_proto);
	अगर (sk->sk_ग_लिखो_space == tls_ग_लिखो_space)
		sk->sk_ग_लिखो_space = ctx->sk_ग_लिखो_space;
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);
	release_sock(sk);
	अगर (ctx->tx_conf == TLS_SW)
		tls_sw_मुक्त_ctx_tx(ctx);
	अगर (ctx->rx_conf == TLS_SW || ctx->rx_conf == TLS_HW)
		tls_sw_strparser_करोne(ctx);
	अगर (ctx->rx_conf == TLS_SW)
		tls_sw_मुक्त_ctx_rx(ctx);
	ctx->sk_proto->बंद(sk, समयout);

	अगर (मुक्त_ctx)
		tls_ctx_मुक्त(sk, ctx);
पूर्ण

अटल पूर्णांक करो_tls_माला_लोockopt_conf(काष्ठा sock *sk, अक्षर __user *optval,
				  पूर्णांक __user *optlen, पूर्णांक tx)
अणु
	पूर्णांक rc = 0;
	काष्ठा tls_context *ctx = tls_get_ctx(sk);
	काष्ठा tls_crypto_info *crypto_info;
	काष्ठा cipher_context *cctx;
	पूर्णांक len;

	अगर (get_user(len, optlen))
		वापस -EFAULT;

	अगर (!optval || (len < माप(*crypto_info))) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!ctx) अणु
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	/* get user crypto info */
	अगर (tx) अणु
		crypto_info = &ctx->crypto_send.info;
		cctx = &ctx->tx;
	पूर्ण अन्यथा अणु
		crypto_info = &ctx->crypto_recv.info;
		cctx = &ctx->rx;
	पूर्ण

	अगर (!TLS_CRYPTO_INFO_READY(crypto_info)) अणु
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (len == माप(*crypto_info)) अणु
		अगर (copy_to_user(optval, crypto_info, माप(*crypto_info)))
			rc = -EFAULT;
		जाओ out;
	पूर्ण

	चयन (crypto_info->cipher_type) अणु
	हाल TLS_CIPHER_AES_GCM_128: अणु
		काष्ठा tls12_crypto_info_aes_gcm_128 *
		  crypto_info_aes_gcm_128 =
		  container_of(crypto_info,
			       काष्ठा tls12_crypto_info_aes_gcm_128,
			       info);

		अगर (len != माप(*crypto_info_aes_gcm_128)) अणु
			rc = -EINVAL;
			जाओ out;
		पूर्ण
		lock_sock(sk);
		स_नकल(crypto_info_aes_gcm_128->iv,
		       cctx->iv + TLS_CIPHER_AES_GCM_128_SALT_SIZE,
		       TLS_CIPHER_AES_GCM_128_IV_SIZE);
		स_नकल(crypto_info_aes_gcm_128->rec_seq, cctx->rec_seq,
		       TLS_CIPHER_AES_GCM_128_REC_SEQ_SIZE);
		release_sock(sk);
		अगर (copy_to_user(optval,
				 crypto_info_aes_gcm_128,
				 माप(*crypto_info_aes_gcm_128)))
			rc = -EFAULT;
		अवरोध;
	पूर्ण
	हाल TLS_CIPHER_AES_GCM_256: अणु
		काष्ठा tls12_crypto_info_aes_gcm_256 *
		  crypto_info_aes_gcm_256 =
		  container_of(crypto_info,
			       काष्ठा tls12_crypto_info_aes_gcm_256,
			       info);

		अगर (len != माप(*crypto_info_aes_gcm_256)) अणु
			rc = -EINVAL;
			जाओ out;
		पूर्ण
		lock_sock(sk);
		स_नकल(crypto_info_aes_gcm_256->iv,
		       cctx->iv + TLS_CIPHER_AES_GCM_256_SALT_SIZE,
		       TLS_CIPHER_AES_GCM_256_IV_SIZE);
		स_नकल(crypto_info_aes_gcm_256->rec_seq, cctx->rec_seq,
		       TLS_CIPHER_AES_GCM_256_REC_SEQ_SIZE);
		release_sock(sk);
		अगर (copy_to_user(optval,
				 crypto_info_aes_gcm_256,
				 माप(*crypto_info_aes_gcm_256)))
			rc = -EFAULT;
		अवरोध;
	पूर्ण
	शेष:
		rc = -EINVAL;
	पूर्ण

out:
	वापस rc;
पूर्ण

अटल पूर्णांक करो_tls_माला_लोockopt(काष्ठा sock *sk, पूर्णांक optname,
			     अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	पूर्णांक rc = 0;

	चयन (optname) अणु
	हाल TLS_TX:
	हाल TLS_RX:
		rc = करो_tls_माला_लोockopt_conf(sk, optval, optlen,
					    optname == TLS_TX);
		अवरोध;
	शेष:
		rc = -ENOPROTOOPT;
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक tls_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			  अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा tls_context *ctx = tls_get_ctx(sk);

	अगर (level != SOL_TLS)
		वापस ctx->sk_proto->माला_लोockopt(sk, level,
						 optname, optval, optlen);

	वापस करो_tls_माला_लोockopt(sk, optname, optval, optlen);
पूर्ण

अटल पूर्णांक करो_tls_setsockopt_conf(काष्ठा sock *sk, sockptr_t optval,
				  अचिन्हित पूर्णांक optlen, पूर्णांक tx)
अणु
	काष्ठा tls_crypto_info *crypto_info;
	काष्ठा tls_crypto_info *alt_crypto_info;
	काष्ठा tls_context *ctx = tls_get_ctx(sk);
	माप_प्रकार optsize;
	पूर्णांक rc = 0;
	पूर्णांक conf;

	अगर (sockptr_is_null(optval) || (optlen < माप(*crypto_info))) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (tx) अणु
		crypto_info = &ctx->crypto_send.info;
		alt_crypto_info = &ctx->crypto_recv.info;
	पूर्ण अन्यथा अणु
		crypto_info = &ctx->crypto_recv.info;
		alt_crypto_info = &ctx->crypto_send.info;
	पूर्ण

	/* Currently we करोn't support set crypto info more than one समय */
	अगर (TLS_CRYPTO_INFO_READY(crypto_info)) अणु
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	rc = copy_from_sockptr(crypto_info, optval, माप(*crypto_info));
	अगर (rc) अणु
		rc = -EFAULT;
		जाओ err_crypto_info;
	पूर्ण

	/* check version */
	अगर (crypto_info->version != TLS_1_2_VERSION &&
	    crypto_info->version != TLS_1_3_VERSION) अणु
		rc = -EINVAL;
		जाओ err_crypto_info;
	पूर्ण

	/* Ensure that TLS version and ciphers are same in both directions */
	अगर (TLS_CRYPTO_INFO_READY(alt_crypto_info)) अणु
		अगर (alt_crypto_info->version != crypto_info->version ||
		    alt_crypto_info->cipher_type != crypto_info->cipher_type) अणु
			rc = -EINVAL;
			जाओ err_crypto_info;
		पूर्ण
	पूर्ण

	चयन (crypto_info->cipher_type) अणु
	हाल TLS_CIPHER_AES_GCM_128:
		optsize = माप(काष्ठा tls12_crypto_info_aes_gcm_128);
		अवरोध;
	हाल TLS_CIPHER_AES_GCM_256: अणु
		optsize = माप(काष्ठा tls12_crypto_info_aes_gcm_256);
		अवरोध;
	पूर्ण
	हाल TLS_CIPHER_AES_CCM_128:
		optsize = माप(काष्ठा tls12_crypto_info_aes_ccm_128);
		अवरोध;
	हाल TLS_CIPHER_CHACHA20_POLY1305:
		optsize = माप(काष्ठा tls12_crypto_info_chacha20_poly1305);
		अवरोध;
	शेष:
		rc = -EINVAL;
		जाओ err_crypto_info;
	पूर्ण

	अगर (optlen != optsize) अणु
		rc = -EINVAL;
		जाओ err_crypto_info;
	पूर्ण

	rc = copy_from_sockptr_offset(crypto_info + 1, optval,
				      माप(*crypto_info),
				      optlen - माप(*crypto_info));
	अगर (rc) अणु
		rc = -EFAULT;
		जाओ err_crypto_info;
	पूर्ण

	अगर (tx) अणु
		rc = tls_set_device_offload(sk, ctx);
		conf = TLS_HW;
		अगर (!rc) अणु
			TLS_INC_STATS(sock_net(sk), LINUX_MIB_TLSTXDEVICE);
			TLS_INC_STATS(sock_net(sk), LINUX_MIB_TLSCURRTXDEVICE);
		पूर्ण अन्यथा अणु
			rc = tls_set_sw_offload(sk, ctx, 1);
			अगर (rc)
				जाओ err_crypto_info;
			TLS_INC_STATS(sock_net(sk), LINUX_MIB_TLSTXSW);
			TLS_INC_STATS(sock_net(sk), LINUX_MIB_TLSCURRTXSW);
			conf = TLS_SW;
		पूर्ण
	पूर्ण अन्यथा अणु
		rc = tls_set_device_offload_rx(sk, ctx);
		conf = TLS_HW;
		अगर (!rc) अणु
			TLS_INC_STATS(sock_net(sk), LINUX_MIB_TLSRXDEVICE);
			TLS_INC_STATS(sock_net(sk), LINUX_MIB_TLSCURRRXDEVICE);
		पूर्ण अन्यथा अणु
			rc = tls_set_sw_offload(sk, ctx, 0);
			अगर (rc)
				जाओ err_crypto_info;
			TLS_INC_STATS(sock_net(sk), LINUX_MIB_TLSRXSW);
			TLS_INC_STATS(sock_net(sk), LINUX_MIB_TLSCURRRXSW);
			conf = TLS_SW;
		पूर्ण
		tls_sw_strparser_arm(sk, ctx);
	पूर्ण

	अगर (tx)
		ctx->tx_conf = conf;
	अन्यथा
		ctx->rx_conf = conf;
	update_sk_prot(sk, ctx);
	अगर (tx) अणु
		ctx->sk_ग_लिखो_space = sk->sk_ग_लिखो_space;
		sk->sk_ग_लिखो_space = tls_ग_लिखो_space;
	पूर्ण अन्यथा अणु
		sk->sk_socket->ops = &tls_sw_proto_ops;
	पूर्ण
	जाओ out;

err_crypto_info:
	memzero_explicit(crypto_info, माप(जोड़ tls_crypto_context));
out:
	वापस rc;
पूर्ण

अटल पूर्णांक करो_tls_setsockopt(काष्ठा sock *sk, पूर्णांक optname, sockptr_t optval,
			     अचिन्हित पूर्णांक optlen)
अणु
	पूर्णांक rc = 0;

	चयन (optname) अणु
	हाल TLS_TX:
	हाल TLS_RX:
		lock_sock(sk);
		rc = करो_tls_setsockopt_conf(sk, optval, optlen,
					    optname == TLS_TX);
		release_sock(sk);
		अवरोध;
	शेष:
		rc = -ENOPROTOOPT;
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक tls_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			  sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा tls_context *ctx = tls_get_ctx(sk);

	अगर (level != SOL_TLS)
		वापस ctx->sk_proto->setsockopt(sk, level, optname, optval,
						 optlen);

	वापस करो_tls_setsockopt(sk, optname, optval, optlen);
पूर्ण

काष्ठा tls_context *tls_ctx_create(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tls_context *ctx;

	ctx = kzalloc(माप(*ctx), GFP_ATOMIC);
	अगर (!ctx)
		वापस शून्य;

	mutex_init(&ctx->tx_lock);
	rcu_assign_poपूर्णांकer(icsk->icsk_ulp_data, ctx);
	ctx->sk_proto = READ_ONCE(sk->sk_prot);
	ctx->sk = sk;
	वापस ctx;
पूर्ण

अटल व्योम tls_build_proto(काष्ठा sock *sk)
अणु
	पूर्णांक ip_ver = sk->sk_family == AF_INET6 ? TLSV6 : TLSV4;
	काष्ठा proto *prot = READ_ONCE(sk->sk_prot);

	/* Build IPv6 TLS whenever the address of tcpv6 _prot changes */
	अगर (ip_ver == TLSV6 &&
	    unlikely(prot != smp_load_acquire(&saved_tcpv6_prot))) अणु
		mutex_lock(&tcpv6_prot_mutex);
		अगर (likely(prot != saved_tcpv6_prot)) अणु
			build_protos(tls_prots[TLSV6], prot);
			smp_store_release(&saved_tcpv6_prot, prot);
		पूर्ण
		mutex_unlock(&tcpv6_prot_mutex);
	पूर्ण

	अगर (ip_ver == TLSV4 &&
	    unlikely(prot != smp_load_acquire(&saved_tcpv4_prot))) अणु
		mutex_lock(&tcpv4_prot_mutex);
		अगर (likely(prot != saved_tcpv4_prot)) अणु
			build_protos(tls_prots[TLSV4], prot);
			smp_store_release(&saved_tcpv4_prot, prot);
		पूर्ण
		mutex_unlock(&tcpv4_prot_mutex);
	पूर्ण
पूर्ण

अटल व्योम build_protos(काष्ठा proto prot[TLS_NUM_CONFIG][TLS_NUM_CONFIG],
			 स्थिर काष्ठा proto *base)
अणु
	prot[TLS_BASE][TLS_BASE] = *base;
	prot[TLS_BASE][TLS_BASE].setsockopt	= tls_setsockopt;
	prot[TLS_BASE][TLS_BASE].माला_लोockopt	= tls_माला_लोockopt;
	prot[TLS_BASE][TLS_BASE].बंद		= tls_sk_proto_बंद;

	prot[TLS_SW][TLS_BASE] = prot[TLS_BASE][TLS_BASE];
	prot[TLS_SW][TLS_BASE].sendmsg		= tls_sw_sendmsg;
	prot[TLS_SW][TLS_BASE].sendpage		= tls_sw_sendpage;

	prot[TLS_BASE][TLS_SW] = prot[TLS_BASE][TLS_BASE];
	prot[TLS_BASE][TLS_SW].recvmsg		  = tls_sw_recvmsg;
	prot[TLS_BASE][TLS_SW].stream_memory_पढ़ो = tls_sw_stream_पढ़ो;
	prot[TLS_BASE][TLS_SW].बंद		  = tls_sk_proto_बंद;

	prot[TLS_SW][TLS_SW] = prot[TLS_SW][TLS_BASE];
	prot[TLS_SW][TLS_SW].recvmsg		= tls_sw_recvmsg;
	prot[TLS_SW][TLS_SW].stream_memory_पढ़ो	= tls_sw_stream_पढ़ो;
	prot[TLS_SW][TLS_SW].बंद		= tls_sk_proto_बंद;

#अगर_घोषित CONFIG_TLS_DEVICE
	prot[TLS_HW][TLS_BASE] = prot[TLS_BASE][TLS_BASE];
	prot[TLS_HW][TLS_BASE].sendmsg		= tls_device_sendmsg;
	prot[TLS_HW][TLS_BASE].sendpage		= tls_device_sendpage;

	prot[TLS_HW][TLS_SW] = prot[TLS_BASE][TLS_SW];
	prot[TLS_HW][TLS_SW].sendmsg		= tls_device_sendmsg;
	prot[TLS_HW][TLS_SW].sendpage		= tls_device_sendpage;

	prot[TLS_BASE][TLS_HW] = prot[TLS_BASE][TLS_SW];

	prot[TLS_SW][TLS_HW] = prot[TLS_SW][TLS_SW];

	prot[TLS_HW][TLS_HW] = prot[TLS_HW][TLS_SW];
#पूर्ण_अगर
#अगर_घोषित CONFIG_TLS_TOE
	prot[TLS_HW_RECORD][TLS_HW_RECORD] = *base;
	prot[TLS_HW_RECORD][TLS_HW_RECORD].hash		= tls_toe_hash;
	prot[TLS_HW_RECORD][TLS_HW_RECORD].unhash	= tls_toe_unhash;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक tls_init(काष्ठा sock *sk)
अणु
	काष्ठा tls_context *ctx;
	पूर्णांक rc = 0;

	tls_build_proto(sk);

#अगर_घोषित CONFIG_TLS_TOE
	अगर (tls_toe_bypass(sk))
		वापस 0;
#पूर्ण_अगर

	/* The TLS ulp is currently supported only क्रम TCP sockets
	 * in ESTABLISHED state.
	 * Supporting sockets in LISTEN state will require us
	 * to modअगरy the accept implementation to clone rather then
	 * share the ulp context.
	 */
	अगर (sk->sk_state != TCP_ESTABLISHED)
		वापस -ENOTCONN;

	/* allocate tls context */
	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	ctx = tls_ctx_create(sk);
	अगर (!ctx) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	ctx->tx_conf = TLS_BASE;
	ctx->rx_conf = TLS_BASE;
	update_sk_prot(sk, ctx);
out:
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);
	वापस rc;
पूर्ण

अटल व्योम tls_update(काष्ठा sock *sk, काष्ठा proto *p,
		       व्योम (*ग_लिखो_space)(काष्ठा sock *sk))
अणु
	काष्ठा tls_context *ctx;

	ctx = tls_get_ctx(sk);
	अगर (likely(ctx)) अणु
		ctx->sk_ग_लिखो_space = ग_लिखो_space;
		ctx->sk_proto = p;
	पूर्ण अन्यथा अणु
		/* Pairs with lockless पढ़ो in sk_clone_lock(). */
		WRITE_ONCE(sk->sk_prot, p);
		sk->sk_ग_लिखो_space = ग_लिखो_space;
	पूर्ण
पूर्ण

अटल पूर्णांक tls_get_info(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	u16 version, cipher_type;
	काष्ठा tls_context *ctx;
	काष्ठा nlattr *start;
	पूर्णांक err;

	start = nla_nest_start_noflag(skb, INET_ULP_INFO_TLS);
	अगर (!start)
		वापस -EMSGSIZE;

	rcu_पढ़ो_lock();
	ctx = rcu_dereference(inet_csk(sk)->icsk_ulp_data);
	अगर (!ctx) अणु
		err = 0;
		जाओ nla_failure;
	पूर्ण
	version = ctx->prot_info.version;
	अगर (version) अणु
		err = nla_put_u16(skb, TLS_INFO_VERSION, version);
		अगर (err)
			जाओ nla_failure;
	पूर्ण
	cipher_type = ctx->prot_info.cipher_type;
	अगर (cipher_type) अणु
		err = nla_put_u16(skb, TLS_INFO_CIPHER, cipher_type);
		अगर (err)
			जाओ nla_failure;
	पूर्ण
	err = nla_put_u16(skb, TLS_INFO_TXCONF, tls_user_config(ctx, true));
	अगर (err)
		जाओ nla_failure;

	err = nla_put_u16(skb, TLS_INFO_RXCONF, tls_user_config(ctx, false));
	अगर (err)
		जाओ nla_failure;

	rcu_पढ़ो_unlock();
	nla_nest_end(skb, start);
	वापस 0;

nla_failure:
	rcu_पढ़ो_unlock();
	nla_nest_cancel(skb, start);
	वापस err;
पूर्ण

अटल माप_प्रकार tls_get_info_size(स्थिर काष्ठा sock *sk)
अणु
	माप_प्रकार size = 0;

	size += nla_total_size(0) +		/* INET_ULP_INFO_TLS */
		nla_total_size(माप(u16)) +	/* TLS_INFO_VERSION */
		nla_total_size(माप(u16)) +	/* TLS_INFO_CIPHER */
		nla_total_size(माप(u16)) +	/* TLS_INFO_RXCONF */
		nla_total_size(माप(u16)) +	/* TLS_INFO_TXCONF */
		0;

	वापस size;
पूर्ण

अटल पूर्णांक __net_init tls_init_net(काष्ठा net *net)
अणु
	पूर्णांक err;

	net->mib.tls_statistics = alloc_percpu(काष्ठा linux_tls_mib);
	अगर (!net->mib.tls_statistics)
		वापस -ENOMEM;

	err = tls_proc_init(net);
	अगर (err)
		जाओ err_मुक्त_stats;

	वापस 0;
err_मुक्त_stats:
	मुक्त_percpu(net->mib.tls_statistics);
	वापस err;
पूर्ण

अटल व्योम __net_निकास tls_निकास_net(काष्ठा net *net)
अणु
	tls_proc_fini(net);
	मुक्त_percpu(net->mib.tls_statistics);
पूर्ण

अटल काष्ठा pernet_operations tls_proc_ops = अणु
	.init = tls_init_net,
	.निकास = tls_निकास_net,
पूर्ण;

अटल काष्ठा tcp_ulp_ops tcp_tls_ulp_ops __पढ़ो_mostly = अणु
	.name			= "tls",
	.owner			= THIS_MODULE,
	.init			= tls_init,
	.update			= tls_update,
	.get_info		= tls_get_info,
	.get_info_size		= tls_get_info_size,
पूर्ण;

अटल पूर्णांक __init tls_रेजिस्टर(व्योम)
अणु
	पूर्णांक err;

	err = रेजिस्टर_pernet_subsys(&tls_proc_ops);
	अगर (err)
		वापस err;

	tls_sw_proto_ops = inet_stream_ops;
	tls_sw_proto_ops.splice_पढ़ो = tls_sw_splice_पढ़ो;
	tls_sw_proto_ops.sendpage_locked   = tls_sw_sendpage_locked;

	tls_device_init();
	tcp_रेजिस्टर_ulp(&tcp_tls_ulp_ops);

	वापस 0;
पूर्ण

अटल व्योम __निकास tls_unरेजिस्टर(व्योम)
अणु
	tcp_unरेजिस्टर_ulp(&tcp_tls_ulp_ops);
	tls_device_cleanup();
	unरेजिस्टर_pernet_subsys(&tls_proc_ops);
पूर्ण

module_init(tls_रेजिस्टर);
module_निकास(tls_unरेजिस्टर);
