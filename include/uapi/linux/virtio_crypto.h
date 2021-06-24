<शैली गुरु>
#अगर_अघोषित _VIRTIO_CRYPTO_H
#घोषणा _VIRTIO_CRYPTO_H
/* This header is BSD licensed so anyone can use the definitions to implement
 * compatible drivers/servers.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of IBM nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL IBM OR
 * CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#समावेश <linux/types.h>
#समावेश <linux/virtio_types.h>
#समावेश <linux/virtio_ids.h>
#समावेश <linux/virtio_config.h>


#घोषणा VIRTIO_CRYPTO_SERVICE_CIPHER 0
#घोषणा VIRTIO_CRYPTO_SERVICE_HASH   1
#घोषणा VIRTIO_CRYPTO_SERVICE_MAC    2
#घोषणा VIRTIO_CRYPTO_SERVICE_AEAD   3

#घोषणा VIRTIO_CRYPTO_OPCODE(service, op)   (((service) << 8) | (op))

काष्ठा virtio_crypto_ctrl_header अणु
#घोषणा VIRTIO_CRYPTO_CIPHER_CREATE_SESSION \
	   VIRTIO_CRYPTO_OPCODE(VIRTIO_CRYPTO_SERVICE_CIPHER, 0x02)
#घोषणा VIRTIO_CRYPTO_CIPHER_DESTROY_SESSION \
	   VIRTIO_CRYPTO_OPCODE(VIRTIO_CRYPTO_SERVICE_CIPHER, 0x03)
#घोषणा VIRTIO_CRYPTO_HASH_CREATE_SESSION \
	   VIRTIO_CRYPTO_OPCODE(VIRTIO_CRYPTO_SERVICE_HASH, 0x02)
#घोषणा VIRTIO_CRYPTO_HASH_DESTROY_SESSION \
	   VIRTIO_CRYPTO_OPCODE(VIRTIO_CRYPTO_SERVICE_HASH, 0x03)
#घोषणा VIRTIO_CRYPTO_MAC_CREATE_SESSION \
	   VIRTIO_CRYPTO_OPCODE(VIRTIO_CRYPTO_SERVICE_MAC, 0x02)
#घोषणा VIRTIO_CRYPTO_MAC_DESTROY_SESSION \
	   VIRTIO_CRYPTO_OPCODE(VIRTIO_CRYPTO_SERVICE_MAC, 0x03)
#घोषणा VIRTIO_CRYPTO_AEAD_CREATE_SESSION \
	   VIRTIO_CRYPTO_OPCODE(VIRTIO_CRYPTO_SERVICE_AEAD, 0x02)
#घोषणा VIRTIO_CRYPTO_AEAD_DESTROY_SESSION \
	   VIRTIO_CRYPTO_OPCODE(VIRTIO_CRYPTO_SERVICE_AEAD, 0x03)
	__le32 opcode;
	__le32 algo;
	__le32 flag;
	/* data virtqueue id */
	__le32 queue_id;
पूर्ण;

काष्ठा virtio_crypto_cipher_session_para अणु
#घोषणा VIRTIO_CRYPTO_NO_CIPHER                 0
#घोषणा VIRTIO_CRYPTO_CIPHER_ARC4               1
#घोषणा VIRTIO_CRYPTO_CIPHER_AES_ECB            2
#घोषणा VIRTIO_CRYPTO_CIPHER_AES_CBC            3
#घोषणा VIRTIO_CRYPTO_CIPHER_AES_CTR            4
#घोषणा VIRTIO_CRYPTO_CIPHER_DES_ECB            5
#घोषणा VIRTIO_CRYPTO_CIPHER_DES_CBC            6
#घोषणा VIRTIO_CRYPTO_CIPHER_3DES_ECB           7
#घोषणा VIRTIO_CRYPTO_CIPHER_3DES_CBC           8
#घोषणा VIRTIO_CRYPTO_CIPHER_3DES_CTR           9
#घोषणा VIRTIO_CRYPTO_CIPHER_KASUMI_F8          10
#घोषणा VIRTIO_CRYPTO_CIPHER_SNOW3G_UEA2        11
#घोषणा VIRTIO_CRYPTO_CIPHER_AES_F8             12
#घोषणा VIRTIO_CRYPTO_CIPHER_AES_XTS            13
#घोषणा VIRTIO_CRYPTO_CIPHER_ZUC_EEA3           14
	__le32 algo;
	/* length of key */
	__le32 keylen;

#घोषणा VIRTIO_CRYPTO_OP_ENCRYPT  1
#घोषणा VIRTIO_CRYPTO_OP_DECRYPT  2
	/* encrypt or decrypt */
	__le32 op;
	__le32 padding;
पूर्ण;

काष्ठा virtio_crypto_session_input अणु
	/* Device-writable part */
	__le64 session_id;
	__le32 status;
	__le32 padding;
पूर्ण;

काष्ठा virtio_crypto_cipher_session_req अणु
	काष्ठा virtio_crypto_cipher_session_para para;
	__u8 padding[32];
पूर्ण;

काष्ठा virtio_crypto_hash_session_para अणु
#घोषणा VIRTIO_CRYPTO_NO_HASH            0
#घोषणा VIRTIO_CRYPTO_HASH_MD5           1
#घोषणा VIRTIO_CRYPTO_HASH_SHA1          2
#घोषणा VIRTIO_CRYPTO_HASH_SHA_224       3
#घोषणा VIRTIO_CRYPTO_HASH_SHA_256       4
#घोषणा VIRTIO_CRYPTO_HASH_SHA_384       5
#घोषणा VIRTIO_CRYPTO_HASH_SHA_512       6
#घोषणा VIRTIO_CRYPTO_HASH_SHA3_224      7
#घोषणा VIRTIO_CRYPTO_HASH_SHA3_256      8
#घोषणा VIRTIO_CRYPTO_HASH_SHA3_384      9
#घोषणा VIRTIO_CRYPTO_HASH_SHA3_512      10
#घोषणा VIRTIO_CRYPTO_HASH_SHA3_SHAKE128      11
#घोषणा VIRTIO_CRYPTO_HASH_SHA3_SHAKE256      12
	__le32 algo;
	/* hash result length */
	__le32 hash_result_len;
	__u8 padding[8];
पूर्ण;

काष्ठा virtio_crypto_hash_create_session_req अणु
	काष्ठा virtio_crypto_hash_session_para para;
	__u8 padding[40];
पूर्ण;

काष्ठा virtio_crypto_mac_session_para अणु
#घोषणा VIRTIO_CRYPTO_NO_MAC                       0
#घोषणा VIRTIO_CRYPTO_MAC_HMAC_MD5                 1
#घोषणा VIRTIO_CRYPTO_MAC_HMAC_SHA1                2
#घोषणा VIRTIO_CRYPTO_MAC_HMAC_SHA_224             3
#घोषणा VIRTIO_CRYPTO_MAC_HMAC_SHA_256             4
#घोषणा VIRTIO_CRYPTO_MAC_HMAC_SHA_384             5
#घोषणा VIRTIO_CRYPTO_MAC_HMAC_SHA_512             6
#घोषणा VIRTIO_CRYPTO_MAC_CMAC_3DES                25
#घोषणा VIRTIO_CRYPTO_MAC_CMAC_AES                 26
#घोषणा VIRTIO_CRYPTO_MAC_KASUMI_F9                27
#घोषणा VIRTIO_CRYPTO_MAC_SNOW3G_UIA2              28
#घोषणा VIRTIO_CRYPTO_MAC_GMAC_AES                 41
#घोषणा VIRTIO_CRYPTO_MAC_GMAC_TWOFISH             42
#घोषणा VIRTIO_CRYPTO_MAC_CBCMAC_AES               49
#घोषणा VIRTIO_CRYPTO_MAC_CBCMAC_KASUMI_F9         50
#घोषणा VIRTIO_CRYPTO_MAC_XCBC_AES                 53
	__le32 algo;
	/* hash result length */
	__le32 hash_result_len;
	/* length of authenticated key */
	__le32 auth_key_len;
	__le32 padding;
पूर्ण;

काष्ठा virtio_crypto_mac_create_session_req अणु
	काष्ठा virtio_crypto_mac_session_para para;
	__u8 padding[40];
पूर्ण;

काष्ठा virtio_crypto_aead_session_para अणु
#घोषणा VIRTIO_CRYPTO_NO_AEAD     0
#घोषणा VIRTIO_CRYPTO_AEAD_GCM    1
#घोषणा VIRTIO_CRYPTO_AEAD_CCM    2
#घोषणा VIRTIO_CRYPTO_AEAD_CHACHA20_POLY1305  3
	__le32 algo;
	/* length of key */
	__le32 key_len;
	/* hash result length */
	__le32 hash_result_len;
	/* length of the additional authenticated data (AAD) in bytes */
	__le32 aad_len;
	/* encrypt or decrypt, See above VIRTIO_CRYPTO_OP_* */
	__le32 op;
	__le32 padding;
पूर्ण;

काष्ठा virtio_crypto_aead_create_session_req अणु
	काष्ठा virtio_crypto_aead_session_para para;
	__u8 padding[32];
पूर्ण;

काष्ठा virtio_crypto_alg_chain_session_para अणु
#घोषणा VIRTIO_CRYPTO_SYM_ALG_CHAIN_ORDER_HASH_THEN_CIPHER  1
#घोषणा VIRTIO_CRYPTO_SYM_ALG_CHAIN_ORDER_CIPHER_THEN_HASH  2
	__le32 alg_chain_order;
/* Plain hash */
#घोषणा VIRTIO_CRYPTO_SYM_HASH_MODE_PLAIN    1
/* Authenticated hash (mac) */
#घोषणा VIRTIO_CRYPTO_SYM_HASH_MODE_AUTH     2
/* Nested hash */
#घोषणा VIRTIO_CRYPTO_SYM_HASH_MODE_NESTED   3
	__le32 hash_mode;
	काष्ठा virtio_crypto_cipher_session_para cipher_param;
	जोड़ अणु
		काष्ठा virtio_crypto_hash_session_para hash_param;
		काष्ठा virtio_crypto_mac_session_para mac_param;
		__u8 padding[16];
	पूर्ण u;
	/* length of the additional authenticated data (AAD) in bytes */
	__le32 aad_len;
	__le32 padding;
पूर्ण;

काष्ठा virtio_crypto_alg_chain_session_req अणु
	काष्ठा virtio_crypto_alg_chain_session_para para;
पूर्ण;

काष्ठा virtio_crypto_sym_create_session_req अणु
	जोड़ अणु
		काष्ठा virtio_crypto_cipher_session_req cipher;
		काष्ठा virtio_crypto_alg_chain_session_req chain;
		__u8 padding[48];
	पूर्ण u;

	/* Device-पढ़ोable part */

/* No operation */
#घोषणा VIRTIO_CRYPTO_SYM_OP_NONE  0
/* Cipher only operation on the data */
#घोषणा VIRTIO_CRYPTO_SYM_OP_CIPHER  1
/*
 * Chain any cipher with any hash or mac operation. The order
 * depends on the value of alg_chain_order param
 */
#घोषणा VIRTIO_CRYPTO_SYM_OP_ALGORITHM_CHAINING  2
	__le32 op_type;
	__le32 padding;
पूर्ण;

काष्ठा virtio_crypto_destroy_session_req अणु
	/* Device-पढ़ोable part */
	__le64  session_id;
	__u8 padding[48];
पूर्ण;

/* The request of the control virtqueue's packet */
काष्ठा virtio_crypto_op_ctrl_req अणु
	काष्ठा virtio_crypto_ctrl_header header;

	जोड़ अणु
		काष्ठा virtio_crypto_sym_create_session_req
			sym_create_session;
		काष्ठा virtio_crypto_hash_create_session_req
			hash_create_session;
		काष्ठा virtio_crypto_mac_create_session_req
			mac_create_session;
		काष्ठा virtio_crypto_aead_create_session_req
			aead_create_session;
		काष्ठा virtio_crypto_destroy_session_req
			destroy_session;
		__u8 padding[56];
	पूर्ण u;
पूर्ण;

काष्ठा virtio_crypto_op_header अणु
#घोषणा VIRTIO_CRYPTO_CIPHER_ENCRYPT \
	VIRTIO_CRYPTO_OPCODE(VIRTIO_CRYPTO_SERVICE_CIPHER, 0x00)
#घोषणा VIRTIO_CRYPTO_CIPHER_DECRYPT \
	VIRTIO_CRYPTO_OPCODE(VIRTIO_CRYPTO_SERVICE_CIPHER, 0x01)
#घोषणा VIRTIO_CRYPTO_HASH \
	VIRTIO_CRYPTO_OPCODE(VIRTIO_CRYPTO_SERVICE_HASH, 0x00)
#घोषणा VIRTIO_CRYPTO_MAC \
	VIRTIO_CRYPTO_OPCODE(VIRTIO_CRYPTO_SERVICE_MAC, 0x00)
#घोषणा VIRTIO_CRYPTO_AEAD_ENCRYPT \
	VIRTIO_CRYPTO_OPCODE(VIRTIO_CRYPTO_SERVICE_AEAD, 0x00)
#घोषणा VIRTIO_CRYPTO_AEAD_DECRYPT \
	VIRTIO_CRYPTO_OPCODE(VIRTIO_CRYPTO_SERVICE_AEAD, 0x01)
	__le32 opcode;
	/* algo should be service-specअगरic algorithms */
	__le32 algo;
	/* session_id should be service-specअगरic algorithms */
	__le64 session_id;
	/* control flag to control the request */
	__le32 flag;
	__le32 padding;
पूर्ण;

काष्ठा virtio_crypto_cipher_para अणु
	/*
	 * Byte Length of valid IV/Counter
	 *
	 * For block ciphers in CBC or F8 mode, or क्रम Kasumi in F8 mode, or क्रम
	 *   SNOW3G in UEA2 mode, this is the length of the IV (which
	 *   must be the same as the block length of the cipher).
	 * For block ciphers in CTR mode, this is the length of the counter
	 *   (which must be the same as the block length of the cipher).
	 * For AES-XTS, this is the 128bit tweak, i, from IEEE Std 1619-2007.
	 *
	 * The IV/Counter will be updated after every partial cryptographic
	 * operation.
	 */
	__le32 iv_len;
	/* length of source data */
	__le32 src_data_len;
	/* length of dst data */
	__le32 dst_data_len;
	__le32 padding;
पूर्ण;

काष्ठा virtio_crypto_hash_para अणु
	/* length of source data */
	__le32 src_data_len;
	/* hash result length */
	__le32 hash_result_len;
पूर्ण;

काष्ठा virtio_crypto_mac_para अणु
	काष्ठा virtio_crypto_hash_para hash;
पूर्ण;

काष्ठा virtio_crypto_aead_para अणु
	/*
	 * Byte Length of valid IV data poपूर्णांकed to by the below iv_addr
	 * parameter.
	 *
	 * For GCM mode, this is either 12 (क्रम 96-bit IVs) or 16, in which
	 *   हाल iv_addr poपूर्णांकs to J0.
	 * For CCM mode, this is the length of the nonce, which can be in the
	 *   range 7 to 13 inclusive.
	 */
	__le32 iv_len;
	/* length of additional auth data */
	__le32 aad_len;
	/* length of source data */
	__le32 src_data_len;
	/* length of dst data */
	__le32 dst_data_len;
पूर्ण;

काष्ठा virtio_crypto_cipher_data_req अणु
	/* Device-पढ़ोable part */
	काष्ठा virtio_crypto_cipher_para para;
	__u8 padding[24];
पूर्ण;

काष्ठा virtio_crypto_hash_data_req अणु
	/* Device-पढ़ोable part */
	काष्ठा virtio_crypto_hash_para para;
	__u8 padding[40];
पूर्ण;

काष्ठा virtio_crypto_mac_data_req अणु
	/* Device-पढ़ोable part */
	काष्ठा virtio_crypto_mac_para para;
	__u8 padding[40];
पूर्ण;

काष्ठा virtio_crypto_alg_chain_data_para अणु
	__le32 iv_len;
	/* Length of source data */
	__le32 src_data_len;
	/* Length of destination data */
	__le32 dst_data_len;
	/* Starting poपूर्णांक क्रम cipher processing in source data */
	__le32 cipher_start_src_offset;
	/* Length of the source data that the cipher will be computed on */
	__le32 len_to_cipher;
	/* Starting poपूर्णांक क्रम hash processing in source data */
	__le32 hash_start_src_offset;
	/* Length of the source data that the hash will be computed on */
	__le32 len_to_hash;
	/* Length of the additional auth data */
	__le32 aad_len;
	/* Length of the hash result */
	__le32 hash_result_len;
	__le32 reserved;
पूर्ण;

काष्ठा virtio_crypto_alg_chain_data_req अणु
	/* Device-पढ़ोable part */
	काष्ठा virtio_crypto_alg_chain_data_para para;
पूर्ण;

काष्ठा virtio_crypto_sym_data_req अणु
	जोड़ अणु
		काष्ठा virtio_crypto_cipher_data_req cipher;
		काष्ठा virtio_crypto_alg_chain_data_req chain;
		__u8 padding[40];
	पूर्ण u;

	/* See above VIRTIO_CRYPTO_SYM_OP_* */
	__le32 op_type;
	__le32 padding;
पूर्ण;

काष्ठा virtio_crypto_aead_data_req अणु
	/* Device-पढ़ोable part */
	काष्ठा virtio_crypto_aead_para para;
	__u8 padding[32];
पूर्ण;

/* The request of the data virtqueue's packet */
काष्ठा virtio_crypto_op_data_req अणु
	काष्ठा virtio_crypto_op_header header;

	जोड़ अणु
		काष्ठा virtio_crypto_sym_data_req  sym_req;
		काष्ठा virtio_crypto_hash_data_req hash_req;
		काष्ठा virtio_crypto_mac_data_req mac_req;
		काष्ठा virtio_crypto_aead_data_req aead_req;
		__u8 padding[48];
	पूर्ण u;
पूर्ण;

#घोषणा VIRTIO_CRYPTO_OK        0
#घोषणा VIRTIO_CRYPTO_ERR       1
#घोषणा VIRTIO_CRYPTO_BADMSG    2
#घोषणा VIRTIO_CRYPTO_NOTSUPP   3
#घोषणा VIRTIO_CRYPTO_INVSESS   4 /* Invalid session id */

/* The accelerator hardware is पढ़ोy */
#घोषणा VIRTIO_CRYPTO_S_HW_READY  (1 << 0)

काष्ठा virtio_crypto_config अणु
	/* See VIRTIO_CRYPTO_OP_* above */
	__le32  status;

	/*
	 * Maximum number of data queue
	 */
	__le32  max_dataqueues;

	/*
	 * Specअगरies the services mask which the device support,
	 * see VIRTIO_CRYPTO_SERVICE_* above
	 */
	__le32 crypto_services;

	/* Detailed algorithms mask */
	__le32 cipher_algo_l;
	__le32 cipher_algo_h;
	__le32 hash_algo;
	__le32 mac_algo_l;
	__le32 mac_algo_h;
	__le32 aead_algo;
	/* Maximum length of cipher key */
	__le32 max_cipher_key_len;
	/* Maximum length of authenticated key */
	__le32 max_auth_key_len;
	__le32 reserve;
	/* Maximum size of each crypto request's content */
	__le64 max_size;
पूर्ण;

काष्ठा virtio_crypto_inhdr अणु
	/* See VIRTIO_CRYPTO_* above */
	__u8 status;
पूर्ण;
#पूर्ण_अगर
