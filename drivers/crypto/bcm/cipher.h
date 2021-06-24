<शैली गुरु>

/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2016 Broadcom
 */

#अगर_अघोषित _CIPHER_H
#घोषणा _CIPHER_H

#समावेश <linux/atomic.h>
#समावेश <linux/mailbox/brcm-message.h>
#समावेश <linux/mailbox_client.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/aead.h>
#समावेश <crypto/arc4.h>
#समावेश <crypto/gcm.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/sha3.h>

#समावेश "spu.h"
#समावेश "spum.h"
#समावेश "spu2.h"

/* Driver supports up to MAX_SPUS SPU blocks */
#घोषणा MAX_SPUS 16

#घोषणा ARC4_STATE_SIZE     4

#घोषणा CCM_AES_IV_SIZE    16
#घोषणा CCM_ESP_IV_SIZE     8
#घोषणा RFC4543_ICV_SIZE   16

#घोषणा MAX_KEY_SIZE	ARC4_MAX_KEY_SIZE
#घोषणा MAX_IV_SIZE	AES_BLOCK_SIZE
#घोषणा MAX_DIGEST_SIZE	SHA3_512_DIGEST_SIZE
#घोषणा MAX_ASSOC_SIZE	512

/* size of salt value क्रम AES-GCM-ESP and AES-CCM-ESP */
#घोषणा GCM_ESP_SALT_SIZE   4
#घोषणा CCM_ESP_SALT_SIZE   3
#घोषणा MAX_SALT_SIZE       GCM_ESP_SALT_SIZE
#घोषणा GCM_ESP_SALT_OFFSET 0
#घोषणा CCM_ESP_SALT_OFFSET 1

#घोषणा GCM_ESP_DIGESTSIZE 16

#घोषणा MAX_HASH_BLOCK_SIZE SHA512_BLOCK_SIZE

/*
 * Maximum number of bytes from a non-final hash request that can be deferred
 * until more data is available. With new crypto API framework, this
 * can be no more than one block of data.
 */
#घोषणा HASH_CARRY_MAX  MAX_HASH_BLOCK_SIZE

/* Force at least 4-byte alignment of all SPU message fields */
#घोषणा SPU_MSG_ALIGN  4

/* Number of बार to resend mailbox message अगर mb queue is full */
#घोषणा SPU_MB_RETRY_MAX  1000

/* op_counts[] indexes */
क्रमागत op_type अणु
	SPU_OP_CIPHER,
	SPU_OP_HASH,
	SPU_OP_HMAC,
	SPU_OP_AEAD,
	SPU_OP_NUM
पूर्ण;

क्रमागत spu_spu_type अणु
	SPU_TYPE_SPUM,
	SPU_TYPE_SPU2,
पूर्ण;

/*
 * SPUM_NS2 and SPUM_NSP are the SPU-M block on Northstar 2 and Northstar Plus,
 * respectively.
 */
क्रमागत spu_spu_subtype अणु
	SPU_SUBTYPE_SPUM_NS2,
	SPU_SUBTYPE_SPUM_NSP,
	SPU_SUBTYPE_SPU2_V1,
	SPU_SUBTYPE_SPU2_V2
पूर्ण;

काष्ठा spu_type_subtype अणु
	क्रमागत spu_spu_type type;
	क्रमागत spu_spu_subtype subtype;
पूर्ण;

काष्ठा cipher_op अणु
	क्रमागत spu_cipher_alg alg;
	क्रमागत spu_cipher_mode mode;
पूर्ण;

काष्ठा auth_op अणु
	क्रमागत hash_alg alg;
	क्रमागत hash_mode mode;
पूर्ण;

काष्ठा iproc_alg_s अणु
	u32 type;
	जोड़ अणु
		काष्ठा skcipher_alg skcipher;
		काष्ठा ahash_alg hash;
		काष्ठा aead_alg aead;
	पूर्ण alg;
	काष्ठा cipher_op cipher_info;
	काष्ठा auth_op auth_info;
	bool auth_first;
	bool रेजिस्टरed;
पूर्ण;

/*
 * Buffers क्रम a SPU request/reply message pair. All part of one काष्ठाure to
 * allow a single alloc per request.
 */
काष्ठा spu_msg_buf अणु
	/* Request message fragments */

	/*
	 * SPU request message header. For SPU-M, holds MH, EMH, SCTX, BDESC,
	 * and BD header. For SPU2, holds FMD, OMD.
	 */
	u8 bcm_spu_req_hdr[ALIGN(SPU2_HEADER_ALLOC_LEN, SPU_MSG_ALIGN)];

	/* IV or counter. Size to include salt. Also used क्रम XTS tweek. */
	u8 iv_ctr[ALIGN(2 * AES_BLOCK_SIZE, SPU_MSG_ALIGN)];

	/* Hash digest. request and response. */
	u8 digest[ALIGN(MAX_DIGEST_SIZE, SPU_MSG_ALIGN)];

	/* SPU request message padding */
	u8 spu_req_pad[ALIGN(SPU_PAD_LEN_MAX, SPU_MSG_ALIGN)];

	/* SPU-M request message STATUS field */
	u8 tx_stat[ALIGN(SPU_TX_STATUS_LEN, SPU_MSG_ALIGN)];

	/* Response message fragments */

	/* SPU response message header */
	u8 spu_resp_hdr[ALIGN(SPU2_HEADER_ALLOC_LEN, SPU_MSG_ALIGN)];

	/* SPU response message STATUS field padding */
	u8 rx_stat_pad[ALIGN(SPU_STAT_PAD_MAX, SPU_MSG_ALIGN)];

	/* SPU response message STATUS field */
	u8 rx_stat[ALIGN(SPU_RX_STATUS_LEN, SPU_MSG_ALIGN)];

	जोड़ अणु
		/* Buffers only used क्रम skcipher */
		काष्ठा अणु
			/*
			 * Field used क्रम either SUPDT when RC4 is used
			 * -OR- tweak value when XTS/AES is used
			 */
			u8 supdt_tweak[ALIGN(SPU_SUPDT_LEN, SPU_MSG_ALIGN)];
		पूर्ण c;

		/* Buffers only used क्रम aead */
		काष्ठा अणु
			/* SPU response pad क्रम GCM data */
			u8 gcmpad[ALIGN(AES_BLOCK_SIZE, SPU_MSG_ALIGN)];

			/* SPU request msg padding क्रम GCM AAD */
			u8 req_aad_pad[ALIGN(SPU_PAD_LEN_MAX, SPU_MSG_ALIGN)];

			/* SPU response data to be discarded */
			u8 resp_aad[ALIGN(MAX_ASSOC_SIZE + MAX_IV_SIZE,
					  SPU_MSG_ALIGN)];
		पूर्ण a;
	पूर्ण;
पूर्ण;

काष्ठा iproc_ctx_s अणु
	u8 enckey[MAX_KEY_SIZE + ARC4_STATE_SIZE];
	अचिन्हित पूर्णांक enckeylen;

	u8 authkey[MAX_KEY_SIZE + ARC4_STATE_SIZE];
	अचिन्हित पूर्णांक authkeylen;

	u8 salt[MAX_SALT_SIZE];
	अचिन्हित पूर्णांक salt_len;
	अचिन्हित पूर्णांक salt_offset;
	u8 iv[MAX_IV_SIZE];

	अचिन्हित पूर्णांक digestsize;

	काष्ठा iproc_alg_s *alg;
	bool is_esp;

	काष्ठा cipher_op cipher;
	क्रमागत spu_cipher_type cipher_type;

	काष्ठा auth_op auth;
	bool auth_first;

	/*
	 * The maximum length in bytes of the payload in a SPU message क्रम this
	 * context. For SPU-M, the payload is the combination of AAD and data.
	 * For SPU2, the payload is just data. A value of SPU_MAX_PAYLOAD_INF
	 * indicates that there is no limit to the length of the SPU message
	 * payload.
	 */
	अचिन्हित पूर्णांक max_payload;

	काष्ठा crypto_aead *fallback_cipher;

	/* auth_type is determined during processing of request */

	u8 ipad[MAX_HASH_BLOCK_SIZE];
	u8 opad[MAX_HASH_BLOCK_SIZE];

	/*
	 * Buffer to hold SPU message header ढाँचा. Template is created at
	 * setkey समय क्रम skcipher requests, since most of the fields in the
	 * header are known at that समय. At request समय, just fill in a few
	 * missing pieces related to length of data in the request and IVs, etc.
	 */
	u8 bcm_spu_req_hdr[ALIGN(SPU2_HEADER_ALLOC_LEN, SPU_MSG_ALIGN)];

	/* Length of SPU request header */
	u16 spu_req_hdr_len;

	/* Expected length of SPU response header */
	u16 spu_resp_hdr_len;

	/*
	 * shash descriptor - needed to perक्रमm incremental hashing in
	 * in software, when hw करोesn't support it.
	 */
	काष्ठा shash_desc *shash;

	bool is_rfc4543;	/* RFC 4543 style of GMAC */
पूर्ण;

/* state from iproc_reqctx_s necessary क्रम hash state export/import */
काष्ठा spu_hash_export_s अणु
	अचिन्हित पूर्णांक total_toकरो;
	अचिन्हित पूर्णांक total_sent;
	u8 hash_carry[HASH_CARRY_MAX];
	अचिन्हित पूर्णांक hash_carry_len;
	u8 incr_hash[MAX_DIGEST_SIZE];
	bool is_sw_hmac;
पूर्ण;

काष्ठा iproc_reqctx_s अणु
	/* general context */
	काष्ठा crypto_async_request *parent;

	/* only valid after enqueue() */
	काष्ठा iproc_ctx_s *ctx;

	u8 chan_idx;   /* Mailbox channel to be used to submit this request */

	/* total toकरो, rx'd, and sent क्रम this request */
	अचिन्हित पूर्णांक total_toकरो;
	अचिन्हित पूर्णांक total_received;	/* only valid क्रम skcipher */
	अचिन्हित पूर्णांक total_sent;

	/*
	 * num bytes sent to hw from the src sg in this request. This can dअगरfer
	 * from total_sent क्रम incremental hashing. total_sent includes previous
	 * init() and update() data. src_sent करोes not.
	 */
	अचिन्हित पूर्णांक src_sent;

	/*
	 * For AEAD requests, start of associated data. This will typically
	 * poपूर्णांक to the beginning of the src scatterlist from the request,
	 * since assoc data is at the beginning of the src scatterlist rather
	 * than in its own sg.
	 */
	काष्ठा scatterlist *assoc;

	/*
	 * scatterlist entry and offset to start of data क्रम next chunk. Crypto
	 * API src scatterlist क्रम AEAD starts with AAD, अगर present. For first
	 * chunk, src_sg is sg entry at beginning of input data (after AAD).
	 * src_skip begins at the offset in that sg entry where data begins.
	 */
	काष्ठा scatterlist *src_sg;
	पूर्णांक src_nents;		/* Number of src entries with data */
	u32 src_skip;		/* bytes of current sg entry alपढ़ोy used */

	/*
	 * Same क्रम destination. For AEAD, अगर there is AAD, output data must
	 * be written at offset following AAD.
	 */
	काष्ठा scatterlist *dst_sg;
	पूर्णांक dst_nents;		/* Number of dst entries with data */
	u32 dst_skip;		/* bytes of current sg entry alपढ़ोy written */

	/* Mailbox message used to send this request to PDC driver */
	काष्ठा brcm_message mb_mssg;

	bool bd_suppress;	/* suppress BD field in SPU response? */

	/* cipher context */
	bool is_encrypt;

	/*
	 * CBC mode: IV.  CTR mode: counter.  Else empty. Used as a DMA
	 * buffer क्रम AEAD requests. So allocate as DMAable memory. If IV
	 * concatenated with salt, includes the salt.
	 */
	u8 *iv_ctr;
	/* Length of IV or counter, in bytes */
	अचिन्हित पूर्णांक iv_ctr_len;

	/*
	 * Hash requests can be of any size, whether initial, update, or final.
	 * A non-final request must be submitted to the SPU as an पूर्णांकegral
	 * number of blocks. This may leave data at the end of the request
	 * that is not a full block. Since the request is non-final, it cannot
	 * be padded. So, we ग_लिखो the reमुख्यder to this hash_carry buffer and
	 * hold it until the next request arrives. The carry data is then
	 * submitted at the beginning of the data in the next SPU msg.
	 * hash_carry_len is the number of bytes currently in hash_carry. These
	 * fields are only used क्रम ahash requests.
	 */
	u8 hash_carry[HASH_CARRY_MAX];
	अचिन्हित पूर्णांक hash_carry_len;
	अचिन्हित पूर्णांक is_final;	/* is this the final क्रम the hash op? */

	/*
	 * Digest from incremental hash is saved here to include in next hash
	 * operation. Cannot be stored in req->result क्रम truncated hashes,
	 * since result may be sized क्रम final digest. Cannot be saved in
	 * msg_buf because that माला_लो deleted between incremental hash ops
	 * and is not saved as part of export().
	 */
	u8 incr_hash[MAX_DIGEST_SIZE];

	/* hmac context */
	bool is_sw_hmac;

	/* aead context */
	काष्ठा crypto_tfm *old_tfm;
	crypto_completion_t old_complete;
	व्योम *old_data;

	gfp_t gfp;

	/* Buffers used to build SPU request and response messages */
	काष्ठा spu_msg_buf msg_buf;
पूर्ण;

/*
 * Structure encapsulates a set of function poपूर्णांकers specअगरic to the type of
 * SPU hardware running. These functions handling creation and parsing of
 * SPU request messages and SPU response messages. Includes hardware-specअगरic
 * values पढ़ो from device tree.
 */
काष्ठा spu_hw अणु
	व्योम (*spu_dump_msg_hdr)(u8 *buf, अचिन्हित पूर्णांक buf_len);
	u32 (*spu_ctx_max_payload)(क्रमागत spu_cipher_alg cipher_alg,
				   क्रमागत spu_cipher_mode cipher_mode,
				   अचिन्हित पूर्णांक blocksize);
	u32 (*spu_payload_length)(u8 *spu_hdr);
	u16 (*spu_response_hdr_len)(u16 auth_key_len, u16 enc_key_len,
				    bool is_hash);
	u16 (*spu_hash_pad_len)(क्रमागत hash_alg hash_alg,
				क्रमागत hash_mode hash_mode, u32 chunksize,
				u16 hash_block_size);
	u32 (*spu_gcm_ccm_pad_len)(क्रमागत spu_cipher_mode cipher_mode,
				   अचिन्हित पूर्णांक data_size);
	u32 (*spu_assoc_resp_len)(क्रमागत spu_cipher_mode cipher_mode,
				  अचिन्हित पूर्णांक assoc_len,
				  अचिन्हित पूर्णांक iv_len, bool is_encrypt);
	u8 (*spu_aead_ivlen)(क्रमागत spu_cipher_mode cipher_mode,
			     u16 iv_len);
	क्रमागत hash_type (*spu_hash_type)(u32 src_sent);
	u32 (*spu_digest_size)(u32 digest_size, क्रमागत hash_alg alg,
			       क्रमागत hash_type);
	u32 (*spu_create_request)(u8 *spu_hdr,
				  काष्ठा spu_request_opts *req_opts,
				  काष्ठा spu_cipher_parms *cipher_parms,
				  काष्ठा spu_hash_parms *hash_parms,
				  काष्ठा spu_aead_parms *aead_parms,
				  अचिन्हित पूर्णांक data_size);
	u16 (*spu_cipher_req_init)(u8 *spu_hdr,
				   काष्ठा spu_cipher_parms *cipher_parms);
	व्योम (*spu_cipher_req_finish)(u8 *spu_hdr,
				      u16 spu_req_hdr_len,
				      अचिन्हित पूर्णांक is_inbound,
				      काष्ठा spu_cipher_parms *cipher_parms,
				      अचिन्हित पूर्णांक data_size);
	व्योम (*spu_request_pad)(u8 *pad_start, u32 gcm_padding,
				u32 hash_pad_len, क्रमागत hash_alg auth_alg,
				क्रमागत hash_mode auth_mode,
				अचिन्हित पूर्णांक total_sent, u32 status_padding);
	u8 (*spu_xts_tweak_in_payload)(व्योम);
	u8 (*spu_tx_status_len)(व्योम);
	u8 (*spu_rx_status_len)(व्योम);
	पूर्णांक (*spu_status_process)(u8 *statp);
	व्योम (*spu_ccm_update_iv)(अचिन्हित पूर्णांक digestsize,
				  काष्ठा spu_cipher_parms *cipher_parms,
				  अचिन्हित पूर्णांक assoclen, अचिन्हित पूर्णांक chunksize,
				  bool is_encrypt, bool is_esp);
	u32 (*spu_wordalign_padlen)(u32 data_size);

	/* The base भव address of the SPU hw रेजिस्टरs */
	व्योम __iomem *reg_vbase[MAX_SPUS];

	/* Version of the SPU hardware */
	क्रमागत spu_spu_type spu_type;

	/* Sub-version of the SPU hardware */
	क्रमागत spu_spu_subtype spu_subtype;

	/* The number of SPUs on this platक्रमm */
	u32 num_spu;

	/* The number of SPU channels on this platक्रमm */
	u32 num_chan;
पूर्ण;

काष्ठा bcm_device_निजी अणु
	काष्ठा platक्रमm_device *pdev;

	काष्ठा spu_hw spu;

	atomic_t session_count;	/* number of streams active */
	atomic_t stream_count;	/* monotonic counter क्रम streamID's */

	/* Length of BCM header. Set to 0 when hw करोes not expect BCM HEADER. */
	u8 bcm_hdr_len;

	/* The index of the channel to use क्रम the next crypto request */
	atomic_t next_chan;

	काष्ठा dentry *debugfs_dir;
	काष्ठा dentry *debugfs_stats;

	/* Number of request bytes processed and result bytes वापसed */
	atomic64_t bytes_in;
	atomic64_t bytes_out;

	/* Number of operations of each type */
	atomic_t op_counts[SPU_OP_NUM];

	atomic_t cipher_cnt[CIPHER_ALG_LAST][CIPHER_MODE_LAST];
	atomic_t hash_cnt[HASH_ALG_LAST];
	atomic_t hmac_cnt[HASH_ALG_LAST];
	atomic_t aead_cnt[AEAD_TYPE_LAST];

	/* Number of calls to setkey() क्रम each operation type */
	atomic_t setkey_cnt[SPU_OP_NUM];

	/* Number of बार request was resubmitted because mb was full */
	atomic_t mb_no_spc;

	/* Number of mailbox send failures */
	atomic_t mb_send_fail;

	/* Number of ICV check failures क्रम AEAD messages */
	atomic_t bad_icv;

	काष्ठा mbox_client mcl;

	/* Array of mailbox channel poपूर्णांकers, one क्रम each channel */
	काष्ठा mbox_chan **mbox;
पूर्ण;

बाह्य काष्ठा bcm_device_निजी iproc_priv;

#पूर्ण_अगर
