<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NITROX_REQ_H
#घोषणा __NITROX_REQ_H

#समावेश <linux/dma-mapping.h>
#समावेश <crypto/aes.h>

#समावेश "nitrox_dev.h"

#घोषणा PENDING_SIG	0xFFFFFFFFFFFFFFFFUL
#घोषणा PRIO 4001

प्रकार व्योम (*sereq_completion_t)(व्योम *req, पूर्णांक err);

/**
 * काष्ठा gphdr - General purpose Header
 * @param0: first parameter.
 * @param1: second parameter.
 * @param2: third parameter.
 * @param3: fourth parameter.
 *
 * Params tell the iv and enc/dec data offsets.
 */
काष्ठा gphdr अणु
	__be16 param0;
	__be16 param1;
	__be16 param2;
	__be16 param3;
पूर्ण;

/**
 * काष्ठा se_req_ctrl - SE request inक्रमmation.
 * @arg: Minor number of the opcode
 * @ctxc: Context control.
 * @unca: Uncertainity enabled.
 * @info: Additional inक्रमmation क्रम SE cores.
 * @ctxl: Context length in bytes.
 * @uddl: User defined data length
 */
जोड़ se_req_ctrl अणु
	u64 value;
	काष्ठा अणु
		u64 raz	: 22;
		u64 arg	: 8;
		u64 ctxc : 2;
		u64 unca : 1;
		u64 info : 3;
		u64 unc : 8;
		u64 ctxl : 12;
		u64 uddl : 8;
	पूर्ण s;
पूर्ण;

#घोषणा MAX_IV_LEN 16

/**
 * काष्ठा se_crypto_request - SE crypto request काष्ठाure.
 * @opcode: Request opcode (enc/dec)
 * @flags: flags from crypto subप्रणाली
 * @ctx_handle: Crypto context handle.
 * @gph: GP Header
 * @ctrl: Request Inक्रमmation.
 * @orh: ORH address
 * @comp: completion address
 * @src: Input sglist
 * @dst: Output sglist
 */
काष्ठा se_crypto_request अणु
	u8 opcode;
	gfp_t gfp;
	u32 flags;
	u64 ctx_handle;

	काष्ठा gphdr gph;
	जोड़ se_req_ctrl ctrl;
	u64 *orh;
	u64 *comp;

	काष्ठा scatterlist *src;
	काष्ठा scatterlist *dst;
पूर्ण;

/* Crypto opcodes */
#घोषणा FLEXI_CRYPTO_ENCRYPT_HMAC	0x33
#घोषणा ENCRYPT	0
#घोषणा DECRYPT 1

/* IV from context */
#घोषणा IV_FROM_CTX	0
/* IV from Input data */
#घोषणा IV_FROM_DPTR	1

/**
 * cipher opcodes क्रम firmware
 */
क्रमागत flexi_cipher अणु
	CIPHER_शून्य = 0,
	CIPHER_3DES_CBC,
	CIPHER_3DES_ECB,
	CIPHER_AES_CBC,
	CIPHER_AES_ECB,
	CIPHER_AES_CFB,
	CIPHER_AES_CTR,
	CIPHER_AES_GCM,
	CIPHER_AES_XTS,
	CIPHER_AES_CCM,
	CIPHER_AES_CBC_CTS,
	CIPHER_AES_ECB_CTS,
	CIPHER_INVALID
पूर्ण;

क्रमागत flexi_auth अणु
	AUTH_शून्य = 0,
	AUTH_MD5,
	AUTH_SHA1,
	AUTH_SHA2_SHA224,
	AUTH_SHA2_SHA256,
	AUTH_SHA2_SHA384,
	AUTH_SHA2_SHA512,
	AUTH_GMAC,
	AUTH_INVALID
पूर्ण;

/**
 * काष्ठा crypto_keys - Crypto keys
 * @key: Encryption key or KEY1 क्रम AES-XTS
 * @iv: Encryption IV or Tweak क्रम AES-XTS
 */
काष्ठा crypto_keys अणु
	जोड़ अणु
		u8 key[AES_MAX_KEY_SIZE];
		u8 key1[AES_MAX_KEY_SIZE];
	पूर्ण u;
	u8 iv[AES_BLOCK_SIZE];
पूर्ण;

/**
 * काष्ठा auth_keys - Authentication keys
 * @ipad: IPAD or KEY2 क्रम AES-XTS
 * @opad: OPAD or AUTH KEY अगर auth_input_type = 1
 */
काष्ठा auth_keys अणु
	जोड़ अणु
		u8 ipad[64];
		u8 key2[64];
	पूर्ण u;
	u8 opad[64];
पूर्ण;

जोड़ fc_ctx_flags अणु
	__be64 f;
	u64 fu;
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 cipher_type	: 4;
		u64 reserved_59	: 1;
		u64 aes_keylen : 2;
		u64 iv_source : 1;
		u64 hash_type : 4;
		u64 reserved_49_51 : 3;
		u64 auth_input_type: 1;
		u64 mac_len : 8;
		u64 reserved_0_39 : 40;
#अन्यथा
		u64 reserved_0_39 : 40;
		u64 mac_len : 8;
		u64 auth_input_type: 1;
		u64 reserved_49_51 : 3;
		u64 hash_type : 4;
		u64 iv_source : 1;
		u64 aes_keylen : 2;
		u64 reserved_59	: 1;
		u64 cipher_type	: 4;
#पूर्ण_अगर
	पूर्ण w0;
पूर्ण;
/**
 * काष्ठा flexi_crypto_context - Crypto context
 * @cipher_type: Encryption cipher type
 * @aes_keylen: AES key length
 * @iv_source: Encryption IV source
 * @hash_type: Authentication type
 * @auth_input_type: Authentication input type
 *   1 - Authentication IV and KEY, microcode calculates OPAD/IPAD
 *   0 - Authentication OPAD/IPAD
 * @mac_len: mac length
 * @crypto: Crypto keys
 * @auth: Authentication keys
 */
काष्ठा flexi_crypto_context अणु
	जोड़ fc_ctx_flags flags;
	काष्ठा crypto_keys crypto;
	काष्ठा auth_keys auth;
पूर्ण;

काष्ठा crypto_ctx_hdr अणु
	काष्ठा dma_pool *pool;
	dma_addr_t dma;
	व्योम *vaddr;
पूर्ण;

काष्ठा nitrox_crypto_ctx अणु
	काष्ठा nitrox_device *ndev;
	जोड़ अणु
		u64 ctx_handle;
		काष्ठा flexi_crypto_context *fctx;
	पूर्ण u;
	काष्ठा crypto_ctx_hdr *chdr;
	sereq_completion_t callback;
पूर्ण;

काष्ठा nitrox_kcrypt_request अणु
	काष्ठा se_crypto_request creq;
	u8 *src;
	u8 *dst;
	u8 *iv_out;
पूर्ण;

/**
 * काष्ठा nitrox_aead_rctx - AEAD request context
 * @nkreq: Base request context
 * @cryptlen: Encryption/Decryption data length
 * @assoclen: AAD length
 * @srclen: Input buffer length
 * @dstlen: Output buffer length
 * @iv: IV data
 * @ivsize: IV data length
 * @flags: AEAD req flags
 * @ctx_handle: Device context handle
 * @src: Source sglist
 * @dst: Destination sglist
 * @ctrl_arg: Identअगरies the request type (ENCRYPT/DECRYPT)
 */
काष्ठा nitrox_aead_rctx अणु
	काष्ठा nitrox_kcrypt_request nkreq;
	अचिन्हित पूर्णांक cryptlen;
	अचिन्हित पूर्णांक assoclen;
	अचिन्हित पूर्णांक srclen;
	अचिन्हित पूर्णांक dstlen;
	u8 *iv;
	पूर्णांक ivsize;
	u32 flags;
	u64 ctx_handle;
	काष्ठा scatterlist *src;
	काष्ठा scatterlist *dst;
	u8 ctrl_arg;
पूर्ण;

/**
 * काष्ठा nitrox_rfc4106_rctx - rfc4106 cipher request context
 * @base: AEAD request context
 * @src: Source sglist
 * @dst: Destination sglist
 * @assoc: AAD
 */
काष्ठा nitrox_rfc4106_rctx अणु
	काष्ठा nitrox_aead_rctx base;
	काष्ठा scatterlist src[3];
	काष्ठा scatterlist dst[3];
	u8 assoc[20];
पूर्ण;

/**
 * काष्ठा pkt_instr_hdr - Packet Inकाष्ठाion Header
 * @g: Gather used
 *   When [G] is set and [GSZ] != 0, the inकाष्ठाion is
 *   indirect gather inकाष्ठाion.
 *   When [G] is set and [GSZ] = 0, the inकाष्ठाion is
 *   direct gather inकाष्ठाion.
 * @gsz: Number of poपूर्णांकers in the indirect gather list
 * @ihi: When set hardware duplicates the 1st 8 bytes of pkt_instr_hdr
 *   and adds them to the packet after the pkt_instr_hdr but beक्रमe any UDD
 * @ssz: Not used by the input hardware. But can become slc_store_पूर्णांक[SSZ]
 *   when [IHI] is set.
 * @fsz: The number of front data bytes directly included in the
 *   PCIe inकाष्ठाion.
 * @tlen: The length of the input packet in bytes, include:
 *   - 16B pkt_hdr
 *   - Inline context bytes अगर any,
 *   - UDD अगर any,
 *   - packet payload bytes
 */
जोड़ pkt_instr_hdr अणु
	__be64 bev;
	u64 value;
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 raz_48_63 : 16;
		u64 g : 1;
		u64 gsz	: 7;
		u64 ihi	: 1;
		u64 ssz	: 7;
		u64 raz_30_31 : 2;
		u64 fsz	: 6;
		u64 raz_16_23 : 8;
		u64 tlen : 16;
#अन्यथा
		u64 tlen : 16;
		u64 raz_16_23 : 8;
		u64 fsz	: 6;
		u64 raz_30_31 : 2;
		u64 ssz	: 7;
		u64 ihi	: 1;
		u64 gsz	: 7;
		u64 g : 1;
		u64 raz_48_63 : 16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा pkt_hdr - Packet Input Header
 * @opcode: Request opcode (Major)
 * @arg: Request opcode (Minor)
 * @ctxc: Context control.
 * @unca: When set [UNC] is the uncertaपूर्णांकy count क्रम an input packet.
 *        The hardware uses uncertaपूर्णांकy counts to predict
 *        output buffer use and aव्योम deadlock.
 * @info: Not used by input hardware. Available क्रम use
 *        during SE processing.
 * @destport: The expected destination port/ring/channel क्रम the packet.
 * @unc: Uncertaपूर्णांकy count क्रम an input packet.
 * @grp: SE group that will process the input packet.
 * @ctxl: Context Length in 64-bit words.
 * @uddl: User-defined data (UDD) length in bytes.
 * @ctxp: Context poपूर्णांकer. CTXP<63,2:0> must be zero in all हालs.
 */
जोड़ pkt_hdr अणु
	__be64 bev[2];
	u64 value[2];
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 opcode : 8;
		u64 arg	: 8;
		u64 ctxc : 2;
		u64 unca : 1;
		u64 raz_44 : 1;
		u64 info : 3;
		u64 destport : 9;
		u64 unc	: 8;
		u64 raz_19_23 : 5;
		u64 grp	: 3;
		u64 raz_15 : 1;
		u64 ctxl : 7;
		u64 uddl : 8;
#अन्यथा
		u64 uddl : 8;
		u64 ctxl : 7;
		u64 raz_15 : 1;
		u64 grp	: 3;
		u64 raz_19_23 : 5;
		u64 unc	: 8;
		u64 destport : 9;
		u64 info : 3;
		u64 raz_44 : 1;
		u64 unca : 1;
		u64 ctxc : 2;
		u64 arg	: 8;
		u64 opcode : 8;
#पूर्ण_अगर
		__be64 ctxp;
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा slc_store_info - Solicited Paceket Output Store Inक्रमmation.
 * @ssz: The number of scatterlist poपूर्णांकers क्रम the solicited output port
 *       packet.
 * @rptr: The result poपूर्णांकer क्रम the solicited output port packet.
 *        If [SSZ]=0, [RPTR] must poपूर्णांक directly to a buffer on the remote
 *        host that is large enough to hold the entire output packet.
 *        If [SSZ]!=0, [RPTR] must poपूर्णांक to an array of ([SSZ]+3)/4
 *        sglist components at [RPTR] on the remote host.
 */
जोड़ slc_store_info अणु
	__be64 bev[2];
	u64 value[2];
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 raz_39_63 : 25;
		u64 ssz	: 7;
		u64 raz_0_31 : 32;
#अन्यथा
		u64 raz_0_31 : 32;
		u64 ssz	: 7;
		u64 raz_39_63 : 25;
#पूर्ण_अगर
		__be64 rptr;
	पूर्ण s;
पूर्ण;

/**
 * काष्ठा nps_pkt_instr - NPS Packet Inकाष्ठाion of SE cores.
 * @dptr0 : Input poपूर्णांकer poपूर्णांकs to buffer in remote host.
 * @ih: Packet Inकाष्ठाion Header (8 bytes)
 * @irh: Packet Input Header (16 bytes)
 * @slc: Solicited Packet Output Store Inक्रमmation (16 bytes)
 * @fdata: Front data
 *
 * 64-Byte Inकाष्ठाion Format
 */
काष्ठा nps_pkt_instr अणु
	__be64 dptr0;
	जोड़ pkt_instr_hdr ih;
	जोड़ pkt_hdr irh;
	जोड़ slc_store_info slc;
	u64 fdata[2];
पूर्ण;

/**
 * काष्ठा aqmq_command_s - The 32 byte command क्रम AE processing.
 * @opcode: Request opcode
 * @param1: Request control parameter 1
 * @param2: Request control parameter 2
 * @dlen: Input length
 * @dptr: Input poपूर्णांकer poपूर्णांकs to buffer in remote host
 * @rptr: Result poपूर्णांकer poपूर्णांकs to buffer in remote host
 * @grp: AQM Group (0..7)
 * @cptr: Context poपूर्णांकer
 */
काष्ठा aqmq_command_s अणु
	__be16 opcode;
	__be16 param1;
	__be16 param2;
	__be16 dlen;
	__be64 dptr;
	__be64 rptr;
	जोड़ अणु
		__be64 word3;
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 grp : 3;
		u64 cptr : 61;
#अन्यथा
		u64 cptr : 61;
		u64 grp : 3;
#पूर्ण_अगर
	पूर्ण;
पूर्ण;

/**
 * काष्ठा ctx_hdr - Book keeping data about the crypto context
 * @pool: Pool used to allocate crypto context
 * @dma: Base DMA address of the cypto context
 * @ctx_dma: Actual usable crypto context क्रम NITROX
 */
काष्ठा ctx_hdr अणु
	काष्ठा dma_pool *pool;
	dma_addr_t dma;
	dma_addr_t ctx_dma;
पूर्ण;

/*
 * काष्ठा sglist_component - SG list component क्रमmat
 * @len0: The number of bytes at [PTR0] on the remote host.
 * @len1: The number of bytes at [PTR1] on the remote host.
 * @len2: The number of bytes at [PTR2] on the remote host.
 * @len3: The number of bytes at [PTR3] on the remote host.
 * @dma0: First poपूर्णांकer poपूर्णांक to buffer in remote host.
 * @dma1: Second poपूर्णांकer poपूर्णांक to buffer in remote host.
 * @dma2: Third poपूर्णांकer poपूर्णांक to buffer in remote host.
 * @dma3: Fourth poपूर्णांकer poपूर्णांक to buffer in remote host.
 */
काष्ठा nitrox_sgcomp अणु
	__be16 len[4];
	__be64 dma[4];
पूर्ण;

/*
 * strutct nitrox_sgtable - SG list inक्रमmation
 * @sgmap_cnt: Number of buffers mapped
 * @total_bytes: Total bytes in sglist.
 * @sgcomp_len: Total sglist components length.
 * @sgcomp_dma: DMA address of sglist component.
 * @sg: crypto request buffer.
 * @sgcomp: sglist component क्रम NITROX.
 */
काष्ठा nitrox_sgtable अणु
	u8 sgmap_cnt;
	u16 total_bytes;
	u32 sgcomp_len;
	dma_addr_t sgcomp_dma;
	काष्ठा scatterlist *sg;
	काष्ठा nitrox_sgcomp *sgcomp;
पूर्ण;

/* Response Header Length */
#घोषणा ORH_HLEN	8
/* Completion bytes Length */
#घोषणा COMP_HLEN	8

काष्ठा resp_hdr अणु
	u64 *orh;
	u64 *completion;
पूर्ण;

प्रकार व्योम (*completion_t)(व्योम *arg, पूर्णांक err);

/**
 * काष्ठा nitrox_softreq - Represents the NIROX Request.
 * @response: response list entry
 * @backlog: Backlog list entry
 * @ndev: Device used to submit the request
 * @cmdq: Command queue क्रम submission
 * @resp: Response headers
 * @instr: 64B inकाष्ठाion
 * @in: SG table क्रम input
 * @out SG table क्रम output
 * @tstamp: Request submitted समय in jअगरfies
 * @callback: callback after request completion/समयout
 * @cb_arg: callback argument
 */
काष्ठा nitrox_softreq अणु
	काष्ठा list_head response;
	काष्ठा list_head backlog;

	u32 flags;
	gfp_t gfp;
	atomic_t status;

	काष्ठा nitrox_device *ndev;
	काष्ठा nitrox_cmdq *cmdq;

	काष्ठा nps_pkt_instr instr;
	काष्ठा resp_hdr resp;
	काष्ठा nitrox_sgtable in;
	काष्ठा nitrox_sgtable out;

	अचिन्हित दीर्घ tstamp;

	completion_t callback;
	व्योम *cb_arg;
पूर्ण;

अटल अंतरभूत पूर्णांक flexi_aes_keylen(पूर्णांक keylen)
अणु
	पूर्णांक aes_keylen;

	चयन (keylen) अणु
	हाल AES_KEYSIZE_128:
		aes_keylen = 1;
		अवरोध;
	हाल AES_KEYSIZE_192:
		aes_keylen = 2;
		अवरोध;
	हाल AES_KEYSIZE_256:
		aes_keylen = 3;
		अवरोध;
	शेष:
		aes_keylen = -EINVAL;
		अवरोध;
	पूर्ण
	वापस aes_keylen;
पूर्ण

अटल अंतरभूत व्योम *alloc_req_buf(पूर्णांक nents, पूर्णांक extralen, gfp_t gfp)
अणु
	माप_प्रकार size;

	size = माप(काष्ठा scatterlist) * nents;
	size += extralen;

	वापस kzalloc(size, gfp);
पूर्ण

/**
 * create_single_sg - Poपूर्णांक SG entry to the data
 * @sg:		Destination SG list
 * @buf:	Data
 * @buflen:	Data length
 *
 * Returns next मुक्त entry in the destination SG list
 **/
अटल अंतरभूत काष्ठा scatterlist *create_single_sg(काष्ठा scatterlist *sg,
						   व्योम *buf, पूर्णांक buflen)
अणु
	sg_set_buf(sg, buf, buflen);
	sg++;
	वापस sg;
पूर्ण

/**
 * create_multi_sg - Create multiple sg entries with buflen data length from
 *		     source sglist
 * @to_sg:	Destination SG list
 * @from_sg:	Source SG list
 * @buflen:	Data length
 *
 * Returns next मुक्त entry in the destination SG list
 **/
अटल अंतरभूत काष्ठा scatterlist *create_multi_sg(काष्ठा scatterlist *to_sg,
						  काष्ठा scatterlist *from_sg,
						  पूर्णांक buflen)
अणु
	काष्ठा scatterlist *sg = to_sg;
	अचिन्हित पूर्णांक sglen;

	क्रम (; buflen && from_sg; buflen -= sglen) अणु
		sglen = from_sg->length;
		अगर (sglen > buflen)
			sglen = buflen;

		sg_set_buf(sg, sg_virt(from_sg), sglen);
		from_sg = sg_next(from_sg);
		sg++;
	पूर्ण

	वापस sg;
पूर्ण

अटल अंतरभूत व्योम set_orh_value(u64 *orh)
अणु
	WRITE_ONCE(*orh, PENDING_SIG);
पूर्ण

अटल अंतरभूत व्योम set_comp_value(u64 *comp)
अणु
	WRITE_ONCE(*comp, PENDING_SIG);
पूर्ण

अटल अंतरभूत पूर्णांक alloc_src_req_buf(काष्ठा nitrox_kcrypt_request *nkreq,
				    पूर्णांक nents, पूर्णांक ivsize)
अणु
	काष्ठा se_crypto_request *creq = &nkreq->creq;

	nkreq->src = alloc_req_buf(nents, ivsize, creq->gfp);
	अगर (!nkreq->src)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम nitrox_creq_copy_iv(अक्षर *dst, अक्षर *src, पूर्णांक size)
अणु
	स_नकल(dst, src, size);
पूर्ण

अटल अंतरभूत काष्ठा scatterlist *nitrox_creq_src_sg(अक्षर *iv, पूर्णांक ivsize)
अणु
	वापस (काष्ठा scatterlist *)(iv + ivsize);
पूर्ण

अटल अंतरभूत व्योम nitrox_creq_set_src_sg(काष्ठा nitrox_kcrypt_request *nkreq,
					  पूर्णांक nents, पूर्णांक ivsize,
					  काष्ठा scatterlist *src, पूर्णांक buflen)
अणु
	अक्षर *iv = nkreq->src;
	काष्ठा scatterlist *sg;
	काष्ठा se_crypto_request *creq = &nkreq->creq;

	creq->src = nitrox_creq_src_sg(iv, ivsize);
	sg = creq->src;
	sg_init_table(sg, nents);

	/* Input क्रमmat:
	 * +----+----------------+
	 * | IV | SRC sg entries |
	 * +----+----------------+
	 */

	/* IV */
	sg = create_single_sg(sg, iv, ivsize);
	/* SRC entries */
	create_multi_sg(sg, src, buflen);
पूर्ण

अटल अंतरभूत पूर्णांक alloc_dst_req_buf(काष्ठा nitrox_kcrypt_request *nkreq,
				    पूर्णांक nents)
अणु
	पूर्णांक extralen = ORH_HLEN + COMP_HLEN;
	काष्ठा se_crypto_request *creq = &nkreq->creq;

	nkreq->dst = alloc_req_buf(nents, extralen, creq->gfp);
	अगर (!nkreq->dst)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम nitrox_creq_set_orh(काष्ठा nitrox_kcrypt_request *nkreq)
अणु
	काष्ठा se_crypto_request *creq = &nkreq->creq;

	creq->orh = (u64 *)(nkreq->dst);
	set_orh_value(creq->orh);
पूर्ण

अटल अंतरभूत व्योम nitrox_creq_set_comp(काष्ठा nitrox_kcrypt_request *nkreq)
अणु
	काष्ठा se_crypto_request *creq = &nkreq->creq;

	creq->comp = (u64 *)(nkreq->dst + ORH_HLEN);
	set_comp_value(creq->comp);
पूर्ण

अटल अंतरभूत काष्ठा scatterlist *nitrox_creq_dst_sg(अक्षर *dst)
अणु
	वापस (काष्ठा scatterlist *)(dst + ORH_HLEN + COMP_HLEN);
पूर्ण

अटल अंतरभूत व्योम nitrox_creq_set_dst_sg(काष्ठा nitrox_kcrypt_request *nkreq,
					  पूर्णांक nents, पूर्णांक ivsize,
					  काष्ठा scatterlist *dst, पूर्णांक buflen)
अणु
	काष्ठा se_crypto_request *creq = &nkreq->creq;
	काष्ठा scatterlist *sg;
	अक्षर *iv = nkreq->src;

	creq->dst = nitrox_creq_dst_sg(nkreq->dst);
	sg = creq->dst;
	sg_init_table(sg, nents);

	/* Output क्रमmat:
	 * +-----+----+----------------+-----------------+
	 * | ORH | IV | DST sg entries | COMPLETION Bytes|
	 * +-----+----+----------------+-----------------+
	 */

	/* ORH */
	sg = create_single_sg(sg, creq->orh, ORH_HLEN);
	/* IV */
	sg = create_single_sg(sg, iv, ivsize);
	/* DST entries */
	sg = create_multi_sg(sg, dst, buflen);
	/* COMPLETION Bytes */
	create_single_sg(sg, creq->comp, COMP_HLEN);
पूर्ण

#पूर्ण_अगर /* __NITROX_REQ_H */
