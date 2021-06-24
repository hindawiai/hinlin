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

#अगर_अघोषित _TLS_OFFLOAD_H
#घोषणा _TLS_OFFLOAD_H

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/crypto.h>
#समावेश <linux/socket.h>
#समावेश <linux/tcp.h>
#समावेश <linux/skmsg.h>
#समावेश <linux/mutex.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rcupdate.h>

#समावेश <net/net_namespace.h>
#समावेश <net/tcp.h>
#समावेश <net/strparser.h>
#समावेश <crypto/aead.h>
#समावेश <uapi/linux/tls.h>


/* Maximum data size carried in a TLS record */
#घोषणा TLS_MAX_PAYLOAD_SIZE		((माप_प्रकार)1 << 14)

#घोषणा TLS_HEADER_SIZE			5
#घोषणा TLS_NONCE_OFFSET		TLS_HEADER_SIZE

#घोषणा TLS_CRYPTO_INFO_READY(info)	((info)->cipher_type)

#घोषणा TLS_RECORD_TYPE_DATA		0x17

#घोषणा TLS_AAD_SPACE_SIZE		13

#घोषणा MAX_IV_SIZE			16
#घोषणा TLS_MAX_REC_SEQ_SIZE		8

/* For AES-CCM, the full 16-bytes of IV is made of '4' fields of given sizes.
 *
 * IV[16] = b0[1] || implicit nonce[4] || explicit nonce[8] || length[3]
 *
 * The field 'length' is encoded in field 'b0' as '(length width - 1)'.
 * Hence b0 contains (3 - 1) = 2.
 */
#घोषणा TLS_AES_CCM_IV_B0_BYTE		2

#घोषणा __TLS_INC_STATS(net, field)				\
	__SNMP_INC_STATS((net)->mib.tls_statistics, field)
#घोषणा TLS_INC_STATS(net, field)				\
	SNMP_INC_STATS((net)->mib.tls_statistics, field)
#घोषणा __TLS_DEC_STATS(net, field)				\
	__SNMP_DEC_STATS((net)->mib.tls_statistics, field)
#घोषणा TLS_DEC_STATS(net, field)				\
	SNMP_DEC_STATS((net)->mib.tls_statistics, field)

क्रमागत अणु
	TLS_BASE,
	TLS_SW,
	TLS_HW,
	TLS_HW_RECORD,
	TLS_NUM_CONFIG,
पूर्ण;

/* TLS records are मुख्यtained in 'struct tls_rec'. It stores the memory pages
 * allocated or mapped क्रम each TLS record. After encryption, the records are
 * stores in a linked list.
 */
काष्ठा tls_rec अणु
	काष्ठा list_head list;
	पूर्णांक tx_पढ़ोy;
	पूर्णांक tx_flags;

	काष्ठा sk_msg msg_plaपूर्णांकext;
	काष्ठा sk_msg msg_encrypted;

	/* AAD | msg_plaपूर्णांकext.sg.data | sg_tag */
	काष्ठा scatterlist sg_aead_in[2];
	/* AAD | msg_encrypted.sg.data (data contains overhead क्रम hdr & iv & tag) */
	काष्ठा scatterlist sg_aead_out[2];

	अक्षर content_type;
	काष्ठा scatterlist sg_content_type;

	अक्षर aad_space[TLS_AAD_SPACE_SIZE];
	u8 iv_data[MAX_IV_SIZE];
	काष्ठा aead_request aead_req;
	u8 aead_req_ctx[];
पूर्ण;

काष्ठा tls_msg अणु
	काष्ठा strp_msg rxm;
	u8 control;
पूर्ण;

काष्ठा tx_work अणु
	काष्ठा delayed_work work;
	काष्ठा sock *sk;
पूर्ण;

काष्ठा tls_sw_context_tx अणु
	काष्ठा crypto_aead *aead_send;
	काष्ठा crypto_रुको async_रुको;
	काष्ठा tx_work tx_work;
	काष्ठा tls_rec *खोलो_rec;
	काष्ठा list_head tx_list;
	atomic_t encrypt_pending;
	/* protect crypto_रुको with encrypt_pending */
	spinlock_t encrypt_compl_lock;
	पूर्णांक async_notअगरy;
	u8 async_capable:1;

#घोषणा BIT_TX_SCHEDULED	0
#घोषणा BIT_TX_CLOSING		1
	अचिन्हित दीर्घ tx_biपंचांगask;
पूर्ण;

काष्ठा tls_sw_context_rx अणु
	काष्ठा crypto_aead *aead_recv;
	काष्ठा crypto_रुको async_रुको;
	काष्ठा strparser strp;
	काष्ठा sk_buff_head rx_list;	/* list of decrypted 'data' records */
	व्योम (*saved_data_पढ़ोy)(काष्ठा sock *sk);

	काष्ठा sk_buff *recv_pkt;
	u8 control;
	u8 async_capable:1;
	u8 decrypted:1;
	atomic_t decrypt_pending;
	/* protect crypto_रुको with decrypt_pending*/
	spinlock_t decrypt_compl_lock;
	bool async_notअगरy;
पूर्ण;

काष्ठा tls_record_info अणु
	काष्ठा list_head list;
	u32 end_seq;
	पूर्णांक len;
	पूर्णांक num_frags;
	skb_frag_t frags[MAX_SKB_FRAGS];
पूर्ण;

काष्ठा tls_offload_context_tx अणु
	काष्ठा crypto_aead *aead_send;
	spinlock_t lock;	/* protects records list */
	काष्ठा list_head records_list;
	काष्ठा tls_record_info *खोलो_record;
	काष्ठा tls_record_info *retransmit_hपूर्णांक;
	u64 hपूर्णांक_record_sn;
	u64 unacked_record_sn;

	काष्ठा scatterlist sg_tx_data[MAX_SKB_FRAGS];
	व्योम (*sk_deकाष्ठा)(काष्ठा sock *sk);
	u8 driver_state[] __aligned(8);
	/* The TLS layer reserves room क्रम driver specअगरic state
	 * Currently the belief is that there is not enough
	 * driver specअगरic state to justअगरy another layer of indirection
	 */
#घोषणा TLS_DRIVER_STATE_SIZE_TX	16
पूर्ण;

#घोषणा TLS_OFFLOAD_CONTEXT_SIZE_TX                                            \
	(माप(काष्ठा tls_offload_context_tx) + TLS_DRIVER_STATE_SIZE_TX)

क्रमागत tls_context_flags अणु
	/* tls_device_करोwn was called after the netdev went करोwn, device state
	 * was released, and kTLS works in software, even though rx_conf is
	 * still TLS_HW (needed क्रम transition).
	 */
	TLS_RX_DEV_DEGRADED = 0,
	/* Unlike RX where resync is driven entirely by the core in TX only
	 * the driver knows when things went out of sync, so we need the flag
	 * to be atomic.
	 */
	TLS_TX_SYNC_SCHED = 1,
	/* tls_dev_del was called क्रम the RX side, device state was released,
	 * but tls_ctx->netdev might still be kept, because TX-side driver
	 * resources might not be released yet. Used to prevent the second
	 * tls_dev_del call in tls_device_करोwn अगर it happens simultaneously.
	 */
	TLS_RX_DEV_CLOSED = 2,
पूर्ण;

काष्ठा cipher_context अणु
	अक्षर *iv;
	अक्षर *rec_seq;
पूर्ण;

जोड़ tls_crypto_context अणु
	काष्ठा tls_crypto_info info;
	जोड़ अणु
		काष्ठा tls12_crypto_info_aes_gcm_128 aes_gcm_128;
		काष्ठा tls12_crypto_info_aes_gcm_256 aes_gcm_256;
		काष्ठा tls12_crypto_info_chacha20_poly1305 chacha20_poly1305;
	पूर्ण;
पूर्ण;

काष्ठा tls_prot_info अणु
	u16 version;
	u16 cipher_type;
	u16 prepend_size;
	u16 tag_size;
	u16 overhead_size;
	u16 iv_size;
	u16 salt_size;
	u16 rec_seq_size;
	u16 aad_size;
	u16 tail_size;
पूर्ण;

काष्ठा tls_context अणु
	/* पढ़ो-only cache line */
	काष्ठा tls_prot_info prot_info;

	u8 tx_conf:3;
	u8 rx_conf:3;

	पूर्णांक (*push_pending_record)(काष्ठा sock *sk, पूर्णांक flags);
	व्योम (*sk_ग_लिखो_space)(काष्ठा sock *sk);

	व्योम *priv_ctx_tx;
	व्योम *priv_ctx_rx;

	काष्ठा net_device *netdev;

	/* rw cache line */
	काष्ठा cipher_context tx;
	काष्ठा cipher_context rx;

	काष्ठा scatterlist *partially_sent_record;
	u16 partially_sent_offset;

	bool in_tcp_sendpages;
	bool pending_खोलो_record_frags;

	काष्ठा mutex tx_lock; /* protects partially_sent_* fields and
			       * per-type TX fields
			       */
	अचिन्हित दीर्घ flags;

	/* cache cold stuff */
	काष्ठा proto *sk_proto;
	काष्ठा sock *sk;

	व्योम (*sk_deकाष्ठा)(काष्ठा sock *sk);

	जोड़ tls_crypto_context crypto_send;
	जोड़ tls_crypto_context crypto_recv;

	काष्ठा list_head list;
	refcount_t refcount;
	काष्ठा rcu_head rcu;
पूर्ण;

क्रमागत tls_offload_ctx_dir अणु
	TLS_OFFLOAD_CTX_सूची_RX,
	TLS_OFFLOAD_CTX_सूची_TX,
पूर्ण;

काष्ठा tlsdev_ops अणु
	पूर्णांक (*tls_dev_add)(काष्ठा net_device *netdev, काष्ठा sock *sk,
			   क्रमागत tls_offload_ctx_dir direction,
			   काष्ठा tls_crypto_info *crypto_info,
			   u32 start_offload_tcp_sn);
	व्योम (*tls_dev_del)(काष्ठा net_device *netdev,
			    काष्ठा tls_context *ctx,
			    क्रमागत tls_offload_ctx_dir direction);
	पूर्णांक (*tls_dev_resync)(काष्ठा net_device *netdev,
			      काष्ठा sock *sk, u32 seq, u8 *rcd_sn,
			      क्रमागत tls_offload_ctx_dir direction);
पूर्ण;

क्रमागत tls_offload_sync_type अणु
	TLS_OFFLOAD_SYNC_TYPE_DRIVER_REQ = 0,
	TLS_OFFLOAD_SYNC_TYPE_CORE_NEXT_HINT = 1,
	TLS_OFFLOAD_SYNC_TYPE_DRIVER_REQ_ASYNC = 2,
पूर्ण;

#घोषणा TLS_DEVICE_RESYNC_NH_START_IVAL		2
#घोषणा TLS_DEVICE_RESYNC_NH_MAX_IVAL		128

#घोषणा TLS_DEVICE_RESYNC_ASYNC_LOGMAX		13
काष्ठा tls_offload_resync_async अणु
	atomic64_t req;
	u16 loglen;
	u16 rcd_delta;
	u32 log[TLS_DEVICE_RESYNC_ASYNC_LOGMAX];
पूर्ण;

काष्ठा tls_offload_context_rx अणु
	/* sw must be the first member of tls_offload_context_rx */
	काष्ठा tls_sw_context_rx sw;
	क्रमागत tls_offload_sync_type resync_type;
	/* this member is set regardless of resync_type, to aव्योम branches */
	u8 resync_nh_reset:1;
	/* CORE_NEXT_HINT-only member, but use the hole here */
	u8 resync_nh_करो_now:1;
	जोड़ अणु
		/* TLS_OFFLOAD_SYNC_TYPE_DRIVER_REQ */
		काष्ठा अणु
			atomic64_t resync_req;
		पूर्ण;
		/* TLS_OFFLOAD_SYNC_TYPE_CORE_NEXT_HINT */
		काष्ठा अणु
			u32 decrypted_failed;
			u32 decrypted_tgt;
		पूर्ण resync_nh;
		/* TLS_OFFLOAD_SYNC_TYPE_DRIVER_REQ_ASYNC */
		काष्ठा अणु
			काष्ठा tls_offload_resync_async *resync_async;
		पूर्ण;
	पूर्ण;
	u8 driver_state[] __aligned(8);
	/* The TLS layer reserves room क्रम driver specअगरic state
	 * Currently the belief is that there is not enough
	 * driver specअगरic state to justअगरy another layer of indirection
	 */
#घोषणा TLS_DRIVER_STATE_SIZE_RX	8
पूर्ण;

#घोषणा TLS_OFFLOAD_CONTEXT_SIZE_RX					\
	(माप(काष्ठा tls_offload_context_rx) + TLS_DRIVER_STATE_SIZE_RX)

काष्ठा tls_context *tls_ctx_create(काष्ठा sock *sk);
व्योम tls_ctx_मुक्त(काष्ठा sock *sk, काष्ठा tls_context *ctx);
व्योम update_sk_prot(काष्ठा sock *sk, काष्ठा tls_context *ctx);

पूर्णांक रुको_on_pending_ग_लिखोr(काष्ठा sock *sk, दीर्घ *समयo);
पूर्णांक tls_sk_query(काष्ठा sock *sk, पूर्णांक optname, अक्षर __user *optval,
		पूर्णांक __user *optlen);
पूर्णांक tls_sk_attach(काष्ठा sock *sk, पूर्णांक optname, अक्षर __user *optval,
		  अचिन्हित पूर्णांक optlen);

पूर्णांक tls_set_sw_offload(काष्ठा sock *sk, काष्ठा tls_context *ctx, पूर्णांक tx);
व्योम tls_sw_strparser_arm(काष्ठा sock *sk, काष्ठा tls_context *ctx);
व्योम tls_sw_strparser_करोne(काष्ठा tls_context *tls_ctx);
पूर्णांक tls_sw_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार size);
पूर्णांक tls_sw_sendpage_locked(काष्ठा sock *sk, काष्ठा page *page,
			   पूर्णांक offset, माप_प्रकार size, पूर्णांक flags);
पूर्णांक tls_sw_sendpage(काष्ठा sock *sk, काष्ठा page *page,
		    पूर्णांक offset, माप_प्रकार size, पूर्णांक flags);
व्योम tls_sw_cancel_work_tx(काष्ठा tls_context *tls_ctx);
व्योम tls_sw_release_resources_tx(काष्ठा sock *sk);
व्योम tls_sw_मुक्त_ctx_tx(काष्ठा tls_context *tls_ctx);
व्योम tls_sw_मुक्त_resources_rx(काष्ठा sock *sk);
व्योम tls_sw_release_resources_rx(काष्ठा sock *sk);
व्योम tls_sw_मुक्त_ctx_rx(काष्ठा tls_context *tls_ctx);
पूर्णांक tls_sw_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len,
		   पूर्णांक nonblock, पूर्णांक flags, पूर्णांक *addr_len);
bool tls_sw_stream_पढ़ो(स्थिर काष्ठा sock *sk);
sमाप_प्रकार tls_sw_splice_पढ़ो(काष्ठा socket *sock, loff_t *ppos,
			   काष्ठा pipe_inode_info *pipe,
			   माप_प्रकार len, अचिन्हित पूर्णांक flags);

पूर्णांक tls_device_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार size);
पूर्णांक tls_device_sendpage(काष्ठा sock *sk, काष्ठा page *page,
			पूर्णांक offset, माप_प्रकार size, पूर्णांक flags);
पूर्णांक tls_tx_records(काष्ठा sock *sk, पूर्णांक flags);

काष्ठा tls_record_info *tls_get_record(काष्ठा tls_offload_context_tx *context,
				       u32 seq, u64 *p_record_sn);

अटल अंतरभूत bool tls_record_is_start_marker(काष्ठा tls_record_info *rec)
अणु
	वापस rec->len == 0;
पूर्ण

अटल अंतरभूत u32 tls_record_start_seq(काष्ठा tls_record_info *rec)
अणु
	वापस rec->end_seq - rec->len;
पूर्ण

पूर्णांक tls_push_sg(काष्ठा sock *sk, काष्ठा tls_context *ctx,
		काष्ठा scatterlist *sg, u16 first_offset,
		पूर्णांक flags);
पूर्णांक tls_push_partial_record(काष्ठा sock *sk, काष्ठा tls_context *ctx,
			    पूर्णांक flags);
व्योम tls_मुक्त_partial_record(काष्ठा sock *sk, काष्ठा tls_context *ctx);

अटल अंतरभूत काष्ठा tls_msg *tls_msg(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा tls_msg *)strp_msg(skb);
पूर्ण

अटल अंतरभूत bool tls_is_partially_sent_record(काष्ठा tls_context *ctx)
अणु
	वापस !!ctx->partially_sent_record;
पूर्ण

अटल अंतरभूत bool tls_is_pending_खोलो_record(काष्ठा tls_context *tls_ctx)
अणु
	वापस tls_ctx->pending_खोलो_record_frags;
पूर्ण

अटल अंतरभूत bool is_tx_पढ़ोy(काष्ठा tls_sw_context_tx *ctx)
अणु
	काष्ठा tls_rec *rec;

	rec = list_first_entry(&ctx->tx_list, काष्ठा tls_rec, list);
	अगर (!rec)
		वापस false;

	वापस READ_ONCE(rec->tx_पढ़ोy);
पूर्ण

अटल अंतरभूत u16 tls_user_config(काष्ठा tls_context *ctx, bool tx)
अणु
	u16 config = tx ? ctx->tx_conf : ctx->rx_conf;

	चयन (config) अणु
	हाल TLS_BASE:
		वापस TLS_CONF_BASE;
	हाल TLS_SW:
		वापस TLS_CONF_SW;
	हाल TLS_HW:
		वापस TLS_CONF_HW;
	हाल TLS_HW_RECORD:
		वापस TLS_CONF_HW_RECORD;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा sk_buff *
tls_validate_xmit_skb(काष्ठा sock *sk, काष्ठा net_device *dev,
		      काष्ठा sk_buff *skb);
काष्ठा sk_buff *
tls_validate_xmit_skb_sw(काष्ठा sock *sk, काष्ठा net_device *dev,
			 काष्ठा sk_buff *skb);

अटल अंतरभूत bool tls_is_sk_tx_device_offloaded(काष्ठा sock *sk)
अणु
#अगर_घोषित CONFIG_SOCK_VALIDATE_XMIT
	वापस sk_fullsock(sk) &&
	       (smp_load_acquire(&sk->sk_validate_xmit_skb) ==
	       &tls_validate_xmit_skb);
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम tls_err_पात(काष्ठा sock *sk, पूर्णांक err)
अणु
	sk->sk_err = err;
	sk->sk_error_report(sk);
पूर्ण

अटल अंतरभूत bool tls_bigपूर्णांक_increment(अचिन्हित अक्षर *seq, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = len - 1; i >= 0; i--) अणु
		++seq[i];
		अगर (seq[i] != 0)
			अवरोध;
	पूर्ण

	वापस (i == -1);
पूर्ण

अटल अंतरभूत व्योम tls_bigपूर्णांक_subtract(अचिन्हित अक्षर *seq, पूर्णांक  n)
अणु
	u64 rcd_sn;
	__be64 *p;

	BUILD_BUG_ON(TLS_MAX_REC_SEQ_SIZE != 8);

	p = (__be64 *)seq;
	rcd_sn = be64_to_cpu(*p);
	*p = cpu_to_be64(rcd_sn - n);
पूर्ण

अटल अंतरभूत काष्ठा tls_context *tls_get_ctx(स्थिर काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	/* Use RCU on icsk_ulp_data only क्रम sock diag code,
	 * TLS data path करोesn't need rcu_dereference().
	 */
	वापस (__क्रमce व्योम *)icsk->icsk_ulp_data;
पूर्ण

अटल अंतरभूत व्योम tls_advance_record_sn(काष्ठा sock *sk,
					 काष्ठा tls_prot_info *prot,
					 काष्ठा cipher_context *ctx)
अणु
	अगर (tls_bigपूर्णांक_increment(ctx->rec_seq, prot->rec_seq_size))
		tls_err_पात(sk, EBADMSG);

	अगर (prot->version != TLS_1_3_VERSION &&
	    prot->cipher_type != TLS_CIPHER_CHACHA20_POLY1305)
		tls_bigपूर्णांक_increment(ctx->iv + prot->salt_size,
				     prot->iv_size);
पूर्ण

अटल अंतरभूत व्योम tls_fill_prepend(काष्ठा tls_context *ctx,
			     अक्षर *buf,
			     माप_प्रकार plaपूर्णांकext_len,
			     अचिन्हित अक्षर record_type)
अणु
	काष्ठा tls_prot_info *prot = &ctx->prot_info;
	माप_प्रकार pkt_len, iv_size = prot->iv_size;

	pkt_len = plaपूर्णांकext_len + prot->tag_size;
	अगर (prot->version != TLS_1_3_VERSION &&
	    prot->cipher_type != TLS_CIPHER_CHACHA20_POLY1305) अणु
		pkt_len += iv_size;

		स_नकल(buf + TLS_NONCE_OFFSET,
		       ctx->tx.iv + prot->salt_size, iv_size);
	पूर्ण

	/* we cover nonce explicit here as well, so buf should be of
	 * size KTLS_DTLS_HEADER_SIZE + KTLS_DTLS_NONCE_EXPLICIT_SIZE
	 */
	buf[0] = prot->version == TLS_1_3_VERSION ?
		   TLS_RECORD_TYPE_DATA : record_type;
	/* Note that VERSION must be TLS_1_2 क्रम both TLS1.2 and TLS1.3 */
	buf[1] = TLS_1_2_VERSION_MINOR;
	buf[2] = TLS_1_2_VERSION_MAJOR;
	/* we can use IV क्रम nonce explicit according to spec */
	buf[3] = pkt_len >> 8;
	buf[4] = pkt_len & 0xFF;
पूर्ण

अटल अंतरभूत व्योम tls_make_aad(अक्षर *buf,
				माप_प्रकार size,
				अक्षर *record_sequence,
				अचिन्हित अक्षर record_type,
				काष्ठा tls_prot_info *prot)
अणु
	अगर (prot->version != TLS_1_3_VERSION) अणु
		स_नकल(buf, record_sequence, prot->rec_seq_size);
		buf += 8;
	पूर्ण अन्यथा अणु
		size += prot->tag_size;
	पूर्ण

	buf[0] = prot->version == TLS_1_3_VERSION ?
		  TLS_RECORD_TYPE_DATA : record_type;
	buf[1] = TLS_1_2_VERSION_MAJOR;
	buf[2] = TLS_1_2_VERSION_MINOR;
	buf[3] = size >> 8;
	buf[4] = size & 0xFF;
पूर्ण

अटल अंतरभूत व्योम xor_iv_with_seq(काष्ठा tls_prot_info *prot, अक्षर *iv, अक्षर *seq)
अणु
	पूर्णांक i;

	अगर (prot->version == TLS_1_3_VERSION ||
	    prot->cipher_type == TLS_CIPHER_CHACHA20_POLY1305) अणु
		क्रम (i = 0; i < 8; i++)
			iv[i + 4] ^= seq[i];
	पूर्ण
पूर्ण


अटल अंतरभूत काष्ठा tls_sw_context_rx *tls_sw_ctx_rx(
		स्थिर काष्ठा tls_context *tls_ctx)
अणु
	वापस (काष्ठा tls_sw_context_rx *)tls_ctx->priv_ctx_rx;
पूर्ण

अटल अंतरभूत काष्ठा tls_sw_context_tx *tls_sw_ctx_tx(
		स्थिर काष्ठा tls_context *tls_ctx)
अणु
	वापस (काष्ठा tls_sw_context_tx *)tls_ctx->priv_ctx_tx;
पूर्ण

अटल अंतरभूत काष्ठा tls_offload_context_tx *
tls_offload_ctx_tx(स्थिर काष्ठा tls_context *tls_ctx)
अणु
	वापस (काष्ठा tls_offload_context_tx *)tls_ctx->priv_ctx_tx;
पूर्ण

अटल अंतरभूत bool tls_sw_has_ctx_tx(स्थिर काष्ठा sock *sk)
अणु
	काष्ठा tls_context *ctx = tls_get_ctx(sk);

	अगर (!ctx)
		वापस false;
	वापस !!tls_sw_ctx_tx(ctx);
पूर्ण

अटल अंतरभूत bool tls_sw_has_ctx_rx(स्थिर काष्ठा sock *sk)
अणु
	काष्ठा tls_context *ctx = tls_get_ctx(sk);

	अगर (!ctx)
		वापस false;
	वापस !!tls_sw_ctx_rx(ctx);
पूर्ण

व्योम tls_sw_ग_लिखो_space(काष्ठा sock *sk, काष्ठा tls_context *ctx);
व्योम tls_device_ग_लिखो_space(काष्ठा sock *sk, काष्ठा tls_context *ctx);

अटल अंतरभूत काष्ठा tls_offload_context_rx *
tls_offload_ctx_rx(स्थिर काष्ठा tls_context *tls_ctx)
अणु
	वापस (काष्ठा tls_offload_context_rx *)tls_ctx->priv_ctx_rx;
पूर्ण

#अगर IS_ENABLED(CONFIG_TLS_DEVICE)
अटल अंतरभूत व्योम *__tls_driver_ctx(काष्ठा tls_context *tls_ctx,
				     क्रमागत tls_offload_ctx_dir direction)
अणु
	अगर (direction == TLS_OFFLOAD_CTX_सूची_TX)
		वापस tls_offload_ctx_tx(tls_ctx)->driver_state;
	अन्यथा
		वापस tls_offload_ctx_rx(tls_ctx)->driver_state;
पूर्ण

अटल अंतरभूत व्योम *
tls_driver_ctx(स्थिर काष्ठा sock *sk, क्रमागत tls_offload_ctx_dir direction)
अणु
	वापस __tls_driver_ctx(tls_get_ctx(sk), direction);
पूर्ण
#पूर्ण_अगर

#घोषणा RESYNC_REQ BIT(0)
#घोषणा RESYNC_REQ_ASYNC BIT(1)
/* The TLS context is valid until sk_deकाष्ठा is called */
अटल अंतरभूत व्योम tls_offload_rx_resync_request(काष्ठा sock *sk, __be32 seq)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_offload_context_rx *rx_ctx = tls_offload_ctx_rx(tls_ctx);

	atomic64_set(&rx_ctx->resync_req, ((u64)ntohl(seq) << 32) | RESYNC_REQ);
पूर्ण

/* Log all TLS record header TCP sequences in [seq, seq+len] */
अटल अंतरभूत व्योम
tls_offload_rx_resync_async_request_start(काष्ठा sock *sk, __be32 seq, u16 len)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_offload_context_rx *rx_ctx = tls_offload_ctx_rx(tls_ctx);

	atomic64_set(&rx_ctx->resync_async->req, ((u64)ntohl(seq) << 32) |
		     ((u64)len << 16) | RESYNC_REQ | RESYNC_REQ_ASYNC);
	rx_ctx->resync_async->loglen = 0;
	rx_ctx->resync_async->rcd_delta = 0;
पूर्ण

अटल अंतरभूत व्योम
tls_offload_rx_resync_async_request_end(काष्ठा sock *sk, __be32 seq)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_offload_context_rx *rx_ctx = tls_offload_ctx_rx(tls_ctx);

	atomic64_set(&rx_ctx->resync_async->req,
		     ((u64)ntohl(seq) << 32) | RESYNC_REQ);
पूर्ण

अटल अंतरभूत व्योम
tls_offload_rx_resync_set_type(काष्ठा sock *sk, क्रमागत tls_offload_sync_type type)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);

	tls_offload_ctx_rx(tls_ctx)->resync_type = type;
पूर्ण

/* Driver's seq tracking has to be disabled until resync succeeded */
अटल अंतरभूत bool tls_offload_tx_resync_pending(काष्ठा sock *sk)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	bool ret;

	ret = test_bit(TLS_TX_SYNC_SCHED, &tls_ctx->flags);
	smp_mb__after_atomic();
	वापस ret;
पूर्ण

पूर्णांक __net_init tls_proc_init(काष्ठा net *net);
व्योम __net_निकास tls_proc_fini(काष्ठा net *net);

पूर्णांक tls_proccess_cmsg(काष्ठा sock *sk, काष्ठा msghdr *msg,
		      अचिन्हित अक्षर *record_type);
पूर्णांक decrypt_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb,
		काष्ठा scatterlist *sgout);
काष्ठा sk_buff *tls_encrypt_skb(काष्ठा sk_buff *skb);

पूर्णांक tls_sw_fallback_init(काष्ठा sock *sk,
			 काष्ठा tls_offload_context_tx *offload_ctx,
			 काष्ठा tls_crypto_info *crypto_info);

#अगर_घोषित CONFIG_TLS_DEVICE
व्योम tls_device_init(व्योम);
व्योम tls_device_cleanup(व्योम);
व्योम tls_device_sk_deकाष्ठा(काष्ठा sock *sk);
पूर्णांक tls_set_device_offload(काष्ठा sock *sk, काष्ठा tls_context *ctx);
व्योम tls_device_मुक्त_resources_tx(काष्ठा sock *sk);
पूर्णांक tls_set_device_offload_rx(काष्ठा sock *sk, काष्ठा tls_context *ctx);
व्योम tls_device_offload_cleanup_rx(काष्ठा sock *sk);
व्योम tls_device_rx_resync_new_rec(काष्ठा sock *sk, u32 rcd_len, u32 seq);
व्योम tls_offload_tx_resync_request(काष्ठा sock *sk, u32 got_seq, u32 exp_seq);
पूर्णांक tls_device_decrypted(काष्ठा sock *sk, काष्ठा tls_context *tls_ctx,
			 काष्ठा sk_buff *skb, काष्ठा strp_msg *rxm);

अटल अंतरभूत bool tls_is_sk_rx_device_offloaded(काष्ठा sock *sk)
अणु
	अगर (!sk_fullsock(sk) ||
	    smp_load_acquire(&sk->sk_deकाष्ठा) != tls_device_sk_deकाष्ठा)
		वापस false;
	वापस tls_get_ctx(sk)->rx_conf == TLS_HW;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम tls_device_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम tls_device_cleanup(व्योम) अणुपूर्ण

अटल अंतरभूत पूर्णांक
tls_set_device_offload(काष्ठा sock *sk, काष्ठा tls_context *ctx)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम tls_device_मुक्त_resources_tx(काष्ठा sock *sk) अणुपूर्ण

अटल अंतरभूत पूर्णांक
tls_set_device_offload_rx(काष्ठा sock *sk, काष्ठा tls_context *ctx)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम tls_device_offload_cleanup_rx(काष्ठा sock *sk) अणुपूर्ण
अटल अंतरभूत व्योम
tls_device_rx_resync_new_rec(काष्ठा sock *sk, u32 rcd_len, u32 seq) अणुपूर्ण

अटल अंतरभूत पूर्णांक
tls_device_decrypted(काष्ठा sock *sk, काष्ठा tls_context *tls_ctx,
		     काष्ठा sk_buff *skb, काष्ठा strp_msg *rxm)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* _TLS_OFFLOAD_H */
