<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2016 Broadcom
 */

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>

#समावेश "util.h"
#समावेश "spu.h"
#समावेश "spum.h"
#समावेश "cipher.h"

अक्षर *hash_alg_name[] = अणु "None", "md5", "sha1", "sha224", "sha256", "aes",
	"sha384", "sha512", "sha3_224", "sha3_256", "sha3_384", "sha3_512" पूर्ण;

अक्षर *aead_alg_name[] = अणु "ccm(aes)", "gcm(aes)", "authenc" पूर्ण;

/* Assumes SPU-M messages are in big endian */
व्योम spum_dump_msg_hdr(u8 *buf, अचिन्हित पूर्णांक buf_len)
अणु
	u8 *ptr = buf;
	काष्ठा SPUHEADER *spuh = (काष्ठा SPUHEADER *)buf;
	अचिन्हित पूर्णांक hash_key_len = 0;
	अचिन्हित पूर्णांक hash_state_len = 0;
	अचिन्हित पूर्णांक cipher_key_len = 0;
	अचिन्हित पूर्णांक iv_len;
	u32 pflags;
	u32 cflags;
	u32 ecf;
	u32 cipher_alg;
	u32 cipher_mode;
	u32 cipher_type;
	u32 hash_alg;
	u32 hash_mode;
	u32 hash_type;
	u32 sctx_size;   /* SCTX length in words */
	u32 sctx_pl_len; /* SCTX payload length in bytes */

	packet_log("\n");
	packet_log("SPU Message header %p len: %u\n", buf, buf_len);

	/* ========== Decode MH ========== */
	packet_log("  MH 0x%08x\n", be32_to_cpup((__be32 *)ptr));
	अगर (spuh->mh.flags & MH_SCTX_PRES)
		packet_log("    SCTX  present\n");
	अगर (spuh->mh.flags & MH_BDESC_PRES)
		packet_log("    BDESC present\n");
	अगर (spuh->mh.flags & MH_MFM_PRES)
		packet_log("    MFM   present\n");
	अगर (spuh->mh.flags & MH_BD_PRES)
		packet_log("    BD    present\n");
	अगर (spuh->mh.flags & MH_HASH_PRES)
		packet_log("    HASH  present\n");
	अगर (spuh->mh.flags & MH_SUPDT_PRES)
		packet_log("    SUPDT present\n");
	packet_log("    Opcode 0x%02x\n", spuh->mh.op_code);

	ptr += माप(spuh->mh) + माप(spuh->emh);  /* skip emh. unused */

	/* ========== Decode SCTX ========== */
	अगर (spuh->mh.flags & MH_SCTX_PRES) अणु
		pflags = be32_to_cpu(spuh->sa.proto_flags);
		packet_log("  SCTX[0] 0x%08x\n", pflags);
		sctx_size = pflags & SCTX_SIZE;
		packet_log("    Size %u words\n", sctx_size);

		cflags = be32_to_cpu(spuh->sa.cipher_flags);
		packet_log("  SCTX[1] 0x%08x\n", cflags);
		packet_log("    Inbound:%lu (1:decrypt/vrfy 0:encrypt/auth)\n",
			   (cflags & CIPHER_INBOUND) >> CIPHER_INBOUND_SHIFT);
		packet_log("    Order:%lu (1:AuthFirst 0:EncFirst)\n",
			   (cflags & CIPHER_ORDER) >> CIPHER_ORDER_SHIFT);
		packet_log("    ICV_IS_512:%lx\n",
			   (cflags & ICV_IS_512) >> ICV_IS_512_SHIFT);
		cipher_alg = (cflags & CIPHER_ALG) >> CIPHER_ALG_SHIFT;
		cipher_mode = (cflags & CIPHER_MODE) >> CIPHER_MODE_SHIFT;
		cipher_type = (cflags & CIPHER_TYPE) >> CIPHER_TYPE_SHIFT;
		packet_log("    Crypto Alg:%u Mode:%u Type:%u\n",
			   cipher_alg, cipher_mode, cipher_type);
		hash_alg = (cflags & HASH_ALG) >> HASH_ALG_SHIFT;
		hash_mode = (cflags & HASH_MODE) >> HASH_MODE_SHIFT;
		hash_type = (cflags & HASH_TYPE) >> HASH_TYPE_SHIFT;
		packet_log("    Hash   Alg:%x Mode:%x Type:%x\n",
			   hash_alg, hash_mode, hash_type);
		packet_log("    UPDT_Offset:%u\n", cflags & UPDT_OFST);

		ecf = be32_to_cpu(spuh->sa.ecf);
		packet_log("  SCTX[2] 0x%08x\n", ecf);
		packet_log("    WriteICV:%lu CheckICV:%lu ICV_SIZE:%u ",
			   (ecf & INSERT_ICV) >> INSERT_ICV_SHIFT,
			   (ecf & CHECK_ICV) >> CHECK_ICV_SHIFT,
			   (ecf & ICV_SIZE) >> ICV_SIZE_SHIFT);
		packet_log("BD_SUPPRESS:%lu\n",
			   (ecf & BD_SUPPRESS) >> BD_SUPPRESS_SHIFT);
		packet_log("    SCTX_IV:%lu ExplicitIV:%lu GenIV:%lu ",
			   (ecf & SCTX_IV) >> SCTX_IV_SHIFT,
			   (ecf & EXPLICIT_IV) >> EXPLICIT_IV_SHIFT,
			   (ecf & GEN_IV) >> GEN_IV_SHIFT);
		packet_log("IV_OV_OFST:%lu EXP_IV_SIZE:%u\n",
			   (ecf & IV_OFFSET) >> IV_OFFSET_SHIFT,
			   ecf & EXP_IV_SIZE);

		ptr += माप(काष्ठा SCTX);

		अगर (hash_alg && hash_mode) अणु
			अक्षर *name = "NONE";

			चयन (hash_alg) अणु
			हाल HASH_ALG_MD5:
				hash_key_len = 16;
				name = "MD5";
				अवरोध;
			हाल HASH_ALG_SHA1:
				hash_key_len = 20;
				name = "SHA1";
				अवरोध;
			हाल HASH_ALG_SHA224:
				hash_key_len = 28;
				name = "SHA224";
				अवरोध;
			हाल HASH_ALG_SHA256:
				hash_key_len = 32;
				name = "SHA256";
				अवरोध;
			हाल HASH_ALG_SHA384:
				hash_key_len = 48;
				name = "SHA384";
				अवरोध;
			हाल HASH_ALG_SHA512:
				hash_key_len = 64;
				name = "SHA512";
				अवरोध;
			हाल HASH_ALG_AES:
				hash_key_len = 0;
				name = "AES";
				अवरोध;
			हाल HASH_ALG_NONE:
				अवरोध;
			पूर्ण

			packet_log("    Auth Key Type:%s Length:%u Bytes\n",
				   name, hash_key_len);
			packet_dump("    KEY: ", ptr, hash_key_len);
			ptr += hash_key_len;
		पूर्ण अन्यथा अगर ((hash_alg == HASH_ALG_AES) &&
			   (hash_mode == HASH_MODE_XCBC)) अणु
			अक्षर *name = "NONE";

			चयन (cipher_type) अणु
			हाल CIPHER_TYPE_AES128:
				hash_key_len = 16;
				name = "AES128-XCBC";
				अवरोध;
			हाल CIPHER_TYPE_AES192:
				hash_key_len = 24;
				name = "AES192-XCBC";
				अवरोध;
			हाल CIPHER_TYPE_AES256:
				hash_key_len = 32;
				name = "AES256-XCBC";
				अवरोध;
			पूर्ण
			packet_log("    Auth Key Type:%s Length:%u Bytes\n",
				   name, hash_key_len);
			packet_dump("    KEY: ", ptr, hash_key_len);
			ptr += hash_key_len;
		पूर्ण

		अगर (hash_alg && (hash_mode == HASH_MODE_NONE) &&
		    (hash_type == HASH_TYPE_UPDT)) अणु
			अक्षर *name = "NONE";

			चयन (hash_alg) अणु
			हाल HASH_ALG_MD5:
				hash_state_len = 16;
				name = "MD5";
				अवरोध;
			हाल HASH_ALG_SHA1:
				hash_state_len = 20;
				name = "SHA1";
				अवरोध;
			हाल HASH_ALG_SHA224:
				hash_state_len = 32;
				name = "SHA224";
				अवरोध;
			हाल HASH_ALG_SHA256:
				hash_state_len = 32;
				name = "SHA256";
				अवरोध;
			हाल HASH_ALG_SHA384:
				hash_state_len = 48;
				name = "SHA384";
				अवरोध;
			हाल HASH_ALG_SHA512:
				hash_state_len = 64;
				name = "SHA512";
				अवरोध;
			हाल HASH_ALG_AES:
				hash_state_len = 0;
				name = "AES";
				अवरोध;
			हाल HASH_ALG_NONE:
				अवरोध;
			पूर्ण

			packet_log("    Auth State Type:%s Length:%u Bytes\n",
				   name, hash_state_len);
			packet_dump("    State: ", ptr, hash_state_len);
			ptr += hash_state_len;
		पूर्ण

		अगर (cipher_alg) अणु
			अक्षर *name = "NONE";

			चयन (cipher_alg) अणु
			हाल CIPHER_ALG_DES:
				cipher_key_len = 8;
				name = "DES";
				अवरोध;
			हाल CIPHER_ALG_3DES:
				cipher_key_len = 24;
				name = "3DES";
				अवरोध;
			हाल CIPHER_ALG_AES:
				चयन (cipher_type) अणु
				हाल CIPHER_TYPE_AES128:
					cipher_key_len = 16;
					name = "AES128";
					अवरोध;
				हाल CIPHER_TYPE_AES192:
					cipher_key_len = 24;
					name = "AES192";
					अवरोध;
				हाल CIPHER_TYPE_AES256:
					cipher_key_len = 32;
					name = "AES256";
					अवरोध;
				पूर्ण
				अवरोध;
			हाल CIPHER_ALG_NONE:
				अवरोध;
			पूर्ण

			packet_log("    Cipher Key Type:%s Length:%u Bytes\n",
				   name, cipher_key_len);

			/* XTS has two keys */
			अगर (cipher_mode == CIPHER_MODE_XTS) अणु
				packet_dump("    KEY2: ", ptr, cipher_key_len);
				ptr += cipher_key_len;
				packet_dump("    KEY1: ", ptr, cipher_key_len);
				ptr += cipher_key_len;

				cipher_key_len *= 2;
			पूर्ण अन्यथा अणु
				packet_dump("    KEY: ", ptr, cipher_key_len);
				ptr += cipher_key_len;
			पूर्ण

			अगर (ecf & SCTX_IV) अणु
				sctx_pl_len = sctx_size * माप(u32) -
					माप(काष्ठा SCTX);
				iv_len = sctx_pl_len -
					(hash_key_len + hash_state_len +
					 cipher_key_len);
				packet_log("    IV Length:%u Bytes\n", iv_len);
				packet_dump("    IV: ", ptr, iv_len);
				ptr += iv_len;
			पूर्ण
		पूर्ण
	पूर्ण

	/* ========== Decode BDESC ========== */
	अगर (spuh->mh.flags & MH_BDESC_PRES) अणु
		काष्ठा BDESC_HEADER *bdesc = (काष्ठा BDESC_HEADER *)ptr;

		packet_log("  BDESC[0] 0x%08x\n", be32_to_cpup((__be32 *)ptr));
		packet_log("    OffsetMAC:%u LengthMAC:%u\n",
			   be16_to_cpu(bdesc->offset_mac),
			   be16_to_cpu(bdesc->length_mac));
		ptr += माप(u32);

		packet_log("  BDESC[1] 0x%08x\n", be32_to_cpup((__be32 *)ptr));
		packet_log("    OffsetCrypto:%u LengthCrypto:%u\n",
			   be16_to_cpu(bdesc->offset_crypto),
			   be16_to_cpu(bdesc->length_crypto));
		ptr += माप(u32);

		packet_log("  BDESC[2] 0x%08x\n", be32_to_cpup((__be32 *)ptr));
		packet_log("    OffsetICV:%u OffsetIV:%u\n",
			   be16_to_cpu(bdesc->offset_icv),
			   be16_to_cpu(bdesc->offset_iv));
		ptr += माप(u32);
	पूर्ण

	/* ========== Decode BD ========== */
	अगर (spuh->mh.flags & MH_BD_PRES) अणु
		काष्ठा BD_HEADER *bd = (काष्ठा BD_HEADER *)ptr;

		packet_log("  BD[0] 0x%08x\n", be32_to_cpup((__be32 *)ptr));
		packet_log("    Size:%ubytes PrevLength:%u\n",
			   be16_to_cpu(bd->size), be16_to_cpu(bd->prev_length));
		ptr += 4;
	पूर्ण

	/* Double check sanity */
	अगर (buf + buf_len != ptr) अणु
		packet_log(" Packet parsed incorrectly. ");
		packet_log("buf:%p buf_len:%u buf+buf_len:%p ptr:%p\n",
			   buf, buf_len, buf + buf_len, ptr);
	पूर्ण

	packet_log("\n");
पूर्ण

/**
 * spum_ns2_ctx_max_payload() - Determine the max length of the payload क्रम a
 * SPU message क्रम a given cipher and hash alg context.
 * @cipher_alg:		The cipher algorithm
 * @cipher_mode:	The cipher mode
 * @blocksize:		The size of a block of data क्रम this algo
 *
 * The max payload must be a multiple of the blocksize so that अगर a request is
 * too large to fit in a single SPU message, the request can be broken पूर्णांकo
 * max_payload sized chunks. Each chunk must be a multiple of blocksize.
 *
 * Return: Max payload length in bytes
 */
u32 spum_ns2_ctx_max_payload(क्रमागत spu_cipher_alg cipher_alg,
			     क्रमागत spu_cipher_mode cipher_mode,
			     अचिन्हित पूर्णांक blocksize)
अणु
	u32 max_payload = SPUM_NS2_MAX_PAYLOAD;
	u32 excess;

	/* In XTS on SPU-M, we'll need to insert tweak beक्रमe input data */
	अगर (cipher_mode == CIPHER_MODE_XTS)
		max_payload -= SPU_XTS_TWEAK_SIZE;

	excess = max_payload % blocksize;

	वापस max_payload - excess;
पूर्ण

/**
 * spum_nsp_ctx_max_payload() - Determine the max length of the payload क्रम a
 * SPU message क्रम a given cipher and hash alg context.
 * @cipher_alg:		The cipher algorithm
 * @cipher_mode:	The cipher mode
 * @blocksize:		The size of a block of data क्रम this algo
 *
 * The max payload must be a multiple of the blocksize so that अगर a request is
 * too large to fit in a single SPU message, the request can be broken पूर्णांकo
 * max_payload sized chunks. Each chunk must be a multiple of blocksize.
 *
 * Return: Max payload length in bytes
 */
u32 spum_nsp_ctx_max_payload(क्रमागत spu_cipher_alg cipher_alg,
			     क्रमागत spu_cipher_mode cipher_mode,
			     अचिन्हित पूर्णांक blocksize)
अणु
	u32 max_payload = SPUM_NSP_MAX_PAYLOAD;
	u32 excess;

	/* In XTS on SPU-M, we'll need to insert tweak beक्रमe input data */
	अगर (cipher_mode == CIPHER_MODE_XTS)
		max_payload -= SPU_XTS_TWEAK_SIZE;

	excess = max_payload % blocksize;

	वापस max_payload - excess;
पूर्ण

/** spum_payload_length() - Given a SPU-M message header, extract the payload
 * length.
 * @spu_hdr:	Start of SPU header
 *
 * Assumes just MH, EMH, BD (no SCTX, BDESC. Works क्रम response frames.
 *
 * Return: payload length in bytes
 */
u32 spum_payload_length(u8 *spu_hdr)
अणु
	काष्ठा BD_HEADER *bd;
	u32 pl_len;

	/* Find BD header.  skip MH, EMH */
	bd = (काष्ठा BD_HEADER *)(spu_hdr + 8);
	pl_len = be16_to_cpu(bd->size);

	वापस pl_len;
पूर्ण

/**
 * spum_response_hdr_len() - Given the length of the hash key and encryption
 * key, determine the expected length of a SPU response header.
 * @auth_key_len:	authentication key length (bytes)
 * @enc_key_len:	encryption key length (bytes)
 * @is_hash:		true अगर response message is क्रम a hash operation
 *
 * Return: length of SPU response header (bytes)
 */
u16 spum_response_hdr_len(u16 auth_key_len, u16 enc_key_len, bool is_hash)
अणु
	अगर (is_hash)
		वापस SPU_HASH_RESP_HDR_LEN;
	अन्यथा
		वापस SPU_RESP_HDR_LEN;
पूर्ण

/**
 * spum_hash_pad_len() - Calculate the length of hash padding required to extend
 * data to a full block size.
 * @hash_alg:   hash algorithm
 * @hash_mode:       hash mode
 * @chunksize:  length of data, in bytes
 * @hash_block_size:  size of a block of data क्रम hash algorithm
 *
 * Reserve space क्रम 1 byte (0x80) start of pad and the total length as u64
 *
 * Return:  length of hash pad in bytes
 */
u16 spum_hash_pad_len(क्रमागत hash_alg hash_alg, क्रमागत hash_mode hash_mode,
		      u32 chunksize, u16 hash_block_size)
अणु
	अचिन्हित पूर्णांक length_len;
	अचिन्हित पूर्णांक used_space_last_block;
	पूर्णांक hash_pad_len;

	/* AES-XCBC hash requires just padding to next block boundary */
	अगर ((hash_alg == HASH_ALG_AES) && (hash_mode == HASH_MODE_XCBC)) अणु
		used_space_last_block = chunksize % hash_block_size;
		hash_pad_len = hash_block_size - used_space_last_block;
		अगर (hash_pad_len >= hash_block_size)
			hash_pad_len -= hash_block_size;
		वापस hash_pad_len;
	पूर्ण

	used_space_last_block = chunksize % hash_block_size + 1;
	अगर ((hash_alg == HASH_ALG_SHA384) || (hash_alg == HASH_ALG_SHA512))
		length_len = 2 * माप(u64);
	अन्यथा
		length_len = माप(u64);

	used_space_last_block += length_len;
	hash_pad_len = hash_block_size - used_space_last_block;
	अगर (hash_pad_len < 0)
		hash_pad_len += hash_block_size;

	hash_pad_len += 1 + length_len;
	वापस hash_pad_len;
पूर्ण

/**
 * spum_gcm_ccm_pad_len() - Determine the required length of GCM or CCM padding.
 * @cipher_mode:	Algo type
 * @data_size:		Length of plaपूर्णांकext (bytes)
 *
 * Return: Length of padding, in bytes
 */
u32 spum_gcm_ccm_pad_len(क्रमागत spu_cipher_mode cipher_mode,
			 अचिन्हित पूर्णांक data_size)
अणु
	u32 pad_len = 0;
	u32 m1 = SPU_GCM_CCM_ALIGN - 1;

	अगर ((cipher_mode == CIPHER_MODE_GCM) ||
	    (cipher_mode == CIPHER_MODE_CCM))
		pad_len = ((data_size + m1) & ~m1) - data_size;

	वापस pad_len;
पूर्ण

/**
 * spum_assoc_resp_len() - Determine the size of the receive buffer required to
 * catch associated data.
 * @cipher_mode:	cipher mode
 * @assoc_len:		length of associated data (bytes)
 * @iv_len:		length of IV (bytes)
 * @is_encrypt:		true अगर encrypting. false अगर decrypting.
 *
 * Return: length of associated data in response message (bytes)
 */
u32 spum_assoc_resp_len(क्रमागत spu_cipher_mode cipher_mode,
			अचिन्हित पूर्णांक assoc_len, अचिन्हित पूर्णांक iv_len,
			bool is_encrypt)
अणु
	u32 buflen = 0;
	u32 pad;

	अगर (assoc_len)
		buflen = assoc_len;

	अगर (cipher_mode == CIPHER_MODE_GCM) अणु
		/* AAD needs to be padded in responses too */
		pad = spum_gcm_ccm_pad_len(cipher_mode, buflen);
		buflen += pad;
	पूर्ण
	अगर (cipher_mode == CIPHER_MODE_CCM) अणु
		/*
		 * AAD needs to be padded in responses too
		 * क्रम CCM, len + 2 needs to be 128-bit aligned.
		 */
		pad = spum_gcm_ccm_pad_len(cipher_mode, buflen + 2);
		buflen += pad;
	पूर्ण

	वापस buflen;
पूर्ण

/**
 * spum_aead_ivlen() - Calculate the length of the AEAD IV to be included
 * in a SPU request after the AAD and beक्रमe the payload.
 * @cipher_mode:  cipher mode
 * @iv_len:   initialization vector length in bytes
 *
 * In Linux ~4.2 and later, the assoc_data sg includes the IV. So no need
 * to include the IV as a separate field in the SPU request msg.
 *
 * Return: Length of AEAD IV in bytes
 */
u8 spum_aead_ivlen(क्रमागत spu_cipher_mode cipher_mode, u16 iv_len)
अणु
	वापस 0;
पूर्ण

/**
 * spum_hash_type() - Determine the type of hash operation.
 * @src_sent:  The number of bytes in the current request that have alपढ़ोy
 *             been sent to the SPU to be hashed.
 *
 * We करो not use HASH_TYPE_FULL क्रम requests that fit in a single SPU message.
 * Using FULL causes failures (such as when the string to be hashed is empty).
 * For similar reasons, we never use HASH_TYPE_FIN. Instead, submit messages
 * as INIT or UPDT and करो the hash padding in sw.
 */
क्रमागत hash_type spum_hash_type(u32 src_sent)
अणु
	वापस src_sent ? HASH_TYPE_UPDT : HASH_TYPE_INIT;
पूर्ण

/**
 * spum_digest_size() - Determine the size of a hash digest to expect the SPU to
 * वापस.
 * @alg_digest_size: Number of bytes in the final digest क्रम the given algo
 * @alg:             The hash algorithm
 * @htype:           Type of hash operation (init, update, full, etc)
 *
 * When करोing incremental hashing क्रम an algorithm with a truncated hash
 * (e.g., SHA224), the SPU वापसs the full digest so that it can be fed back as
 * a partial result क्रम the next chunk.
 */
u32 spum_digest_size(u32 alg_digest_size, क्रमागत hash_alg alg,
		     क्रमागत hash_type htype)
अणु
	u32 digestsize = alg_digest_size;

	/* SPU वापसs complete digest when करोing incremental hash and truncated
	 * hash algo.
	 */
	अगर ((htype == HASH_TYPE_INIT) || (htype == HASH_TYPE_UPDT)) अणु
		अगर (alg == HASH_ALG_SHA224)
			digestsize = SHA256_DIGEST_SIZE;
		अन्यथा अगर (alg == HASH_ALG_SHA384)
			digestsize = SHA512_DIGEST_SIZE;
	पूर्ण
	वापस digestsize;
पूर्ण

/**
 * spum_create_request() - Build a SPU request message header, up to and
 * including the BD header. Conकाष्ठा the message starting at spu_hdr. Caller
 * should allocate this buffer in DMA-able memory at least SPU_HEADER_ALLOC_LEN
 * bytes दीर्घ.
 * @spu_hdr: Start of buffer where SPU request header is to be written
 * @req_opts: SPU request message options
 * @cipher_parms: Parameters related to cipher algorithm
 * @hash_parms:   Parameters related to hash algorithm
 * @aead_parms:   Parameters related to AEAD operation
 * @data_size:    Length of data to be encrypted or authenticated. If AEAD, करोes
 *		  not include length of AAD.
 *
 * Return: the length of the SPU header in bytes. 0 अगर an error occurs.
 */
u32 spum_create_request(u8 *spu_hdr,
			काष्ठा spu_request_opts *req_opts,
			काष्ठा spu_cipher_parms *cipher_parms,
			काष्ठा spu_hash_parms *hash_parms,
			काष्ठा spu_aead_parms *aead_parms,
			अचिन्हित पूर्णांक data_size)
अणु
	काष्ठा SPUHEADER *spuh;
	काष्ठा BDESC_HEADER *bdesc;
	काष्ठा BD_HEADER *bd;

	u8 *ptr;
	u32 protocol_bits = 0;
	u32 cipher_bits = 0;
	u32 ecf_bits = 0;
	u8 sctx_words = 0;
	अचिन्हित पूर्णांक buf_len = 0;

	/* size of the cipher payload */
	अचिन्हित पूर्णांक cipher_len = hash_parms->prebuf_len + data_size +
				hash_parms->pad_len;

	/* offset of prebuf or data from end of BD header */
	अचिन्हित पूर्णांक cipher_offset = aead_parms->assoc_size +
		aead_parms->iv_len + aead_parms->aad_pad_len;

	/* total size of the DB data (without STAT word padding) */
	अचिन्हित पूर्णांक real_db_size = spu_real_db_size(aead_parms->assoc_size,
						 aead_parms->iv_len,
						 hash_parms->prebuf_len,
						 data_size,
						 aead_parms->aad_pad_len,
						 aead_parms->data_pad_len,
						 hash_parms->pad_len);

	अचिन्हित पूर्णांक auth_offset = 0;
	अचिन्हित पूर्णांक offset_iv = 0;

	/* size/offset of the auth payload */
	अचिन्हित पूर्णांक auth_len;

	auth_len = real_db_size;

	अगर (req_opts->is_aead && req_opts->is_inbound)
		cipher_len -= hash_parms->digestsize;

	अगर (req_opts->is_aead && req_opts->is_inbound)
		auth_len -= hash_parms->digestsize;

	अगर ((hash_parms->alg == HASH_ALG_AES) &&
	    (hash_parms->mode == HASH_MODE_XCBC)) अणु
		auth_len -= hash_parms->pad_len;
		cipher_len -= hash_parms->pad_len;
	पूर्ण

	flow_log("%s()\n", __func__);
	flow_log("  in:%u authFirst:%u\n",
		 req_opts->is_inbound, req_opts->auth_first);
	flow_log("  %s. cipher alg:%u mode:%u type %u\n",
		 spu_alg_name(cipher_parms->alg, cipher_parms->mode),
		 cipher_parms->alg, cipher_parms->mode, cipher_parms->type);
	flow_log("    key: %d\n", cipher_parms->key_len);
	flow_dump("    key: ", cipher_parms->key_buf, cipher_parms->key_len);
	flow_log("    iv: %d\n", cipher_parms->iv_len);
	flow_dump("    iv: ", cipher_parms->iv_buf, cipher_parms->iv_len);
	flow_log("  auth alg:%u mode:%u type %u\n",
		 hash_parms->alg, hash_parms->mode, hash_parms->type);
	flow_log("  digestsize: %u\n", hash_parms->digestsize);
	flow_log("  authkey: %d\n", hash_parms->key_len);
	flow_dump("  authkey: ", hash_parms->key_buf, hash_parms->key_len);
	flow_log("  assoc_size:%u\n", aead_parms->assoc_size);
	flow_log("  prebuf_len:%u\n", hash_parms->prebuf_len);
	flow_log("  data_size:%u\n", data_size);
	flow_log("  hash_pad_len:%u\n", hash_parms->pad_len);
	flow_log("  real_db_size:%u\n", real_db_size);
	flow_log(" auth_offset:%u auth_len:%u cipher_offset:%u cipher_len:%u\n",
		 auth_offset, auth_len, cipher_offset, cipher_len);
	flow_log("  aead_iv: %u\n", aead_parms->iv_len);

	/* starting out: zero the header (plus some) */
	ptr = spu_hdr;
	स_रखो(ptr, 0, माप(काष्ठा SPUHEADER));

	/* क्रमmat master header word */
	/* Do not set the next bit even though the datasheet says to */
	spuh = (काष्ठा SPUHEADER *)ptr;
	ptr += माप(काष्ठा SPUHEADER);
	buf_len += माप(काष्ठा SPUHEADER);

	spuh->mh.op_code = SPU_CRYPTO_OPERATION_GENERIC;
	spuh->mh.flags |= (MH_SCTX_PRES | MH_BDESC_PRES | MH_BD_PRES);

	/* Format sctx word 0 (protocol_bits) */
	sctx_words = 3;		/* size in words */

	/* Format sctx word 1 (cipher_bits) */
	अगर (req_opts->is_inbound)
		cipher_bits |= CIPHER_INBOUND;
	अगर (req_opts->auth_first)
		cipher_bits |= CIPHER_ORDER;

	/* Set the crypto parameters in the cipher.flags */
	cipher_bits |= cipher_parms->alg << CIPHER_ALG_SHIFT;
	cipher_bits |= cipher_parms->mode << CIPHER_MODE_SHIFT;
	cipher_bits |= cipher_parms->type << CIPHER_TYPE_SHIFT;

	/* Set the auth parameters in the cipher.flags */
	cipher_bits |= hash_parms->alg << HASH_ALG_SHIFT;
	cipher_bits |= hash_parms->mode << HASH_MODE_SHIFT;
	cipher_bits |= hash_parms->type << HASH_TYPE_SHIFT;

	/*
	 * Format sctx extensions अगर required, and update मुख्य fields अगर
	 * required)
	 */
	अगर (hash_parms->alg) अणु
		/* Write the authentication key material अगर present */
		अगर (hash_parms->key_len) अणु
			स_नकल(ptr, hash_parms->key_buf, hash_parms->key_len);
			ptr += hash_parms->key_len;
			buf_len += hash_parms->key_len;
			sctx_words += hash_parms->key_len / 4;
		पूर्ण

		अगर ((cipher_parms->mode == CIPHER_MODE_GCM) ||
		    (cipher_parms->mode == CIPHER_MODE_CCM))
			/* unpadded length */
			offset_iv = aead_parms->assoc_size;

		/* अगर GCM/CCM we need to ग_लिखो ICV पूर्णांकo the payload */
		अगर (!req_opts->is_inbound) अणु
			अगर ((cipher_parms->mode == CIPHER_MODE_GCM) ||
			    (cipher_parms->mode == CIPHER_MODE_CCM))
				ecf_bits |= 1 << INSERT_ICV_SHIFT;
		पूर्ण अन्यथा अणु
			ecf_bits |= CHECK_ICV;
		पूर्ण

		/* Inक्रमm the SPU of the ICV size (in words) */
		अगर (hash_parms->digestsize == 64)
			cipher_bits |= ICV_IS_512;
		अन्यथा
			ecf_bits |=
			(hash_parms->digestsize / 4) << ICV_SIZE_SHIFT;
	पूर्ण

	अगर (req_opts->bd_suppress)
		ecf_bits |= BD_SUPPRESS;

	/* copy the encryption keys in the SAD entry */
	अगर (cipher_parms->alg) अणु
		अगर (cipher_parms->key_len) अणु
			स_नकल(ptr, cipher_parms->key_buf,
			       cipher_parms->key_len);
			ptr += cipher_parms->key_len;
			buf_len += cipher_parms->key_len;
			sctx_words += cipher_parms->key_len / 4;
		पूर्ण

		/*
		 * अगर encrypting then set IV size, use SCTX IV unless no IV
		 * given here
		 */
		अगर (cipher_parms->iv_buf && cipher_parms->iv_len) अणु
			/* Use SCTX IV */
			ecf_bits |= SCTX_IV;

			/* cipher iv provided so put it in here */
			स_नकल(ptr, cipher_parms->iv_buf, cipher_parms->iv_len);

			ptr += cipher_parms->iv_len;
			buf_len += cipher_parms->iv_len;
			sctx_words += cipher_parms->iv_len / 4;
		पूर्ण
	पूर्ण

	/*
	 * RFC4543 (GMAC/ESP) requires data to be sent as part of AAD
	 * so we need to override the BDESC parameters.
	 */
	अगर (req_opts->is_rfc4543) अणु
		अगर (req_opts->is_inbound)
			data_size -= hash_parms->digestsize;
		offset_iv = aead_parms->assoc_size + data_size;
		cipher_len = 0;
		cipher_offset = offset_iv;
		auth_len = cipher_offset + aead_parms->data_pad_len;
	पूर्ण

	/* ग_लिखो in the total sctx length now that we know it */
	protocol_bits |= sctx_words;

	/* Endian adjust the SCTX */
	spuh->sa.proto_flags = cpu_to_be32(protocol_bits);
	spuh->sa.cipher_flags = cpu_to_be32(cipher_bits);
	spuh->sa.ecf = cpu_to_be32(ecf_bits);

	/* === create the BDESC section === */
	bdesc = (काष्ठा BDESC_HEADER *)ptr;

	bdesc->offset_mac = cpu_to_be16(auth_offset);
	bdesc->length_mac = cpu_to_be16(auth_len);
	bdesc->offset_crypto = cpu_to_be16(cipher_offset);
	bdesc->length_crypto = cpu_to_be16(cipher_len);

	/*
	 * CCM in SPU-M requires that ICV not be in same 32-bit word as data or
	 * padding.  So account क्रम padding as necessary.
	 */
	अगर (cipher_parms->mode == CIPHER_MODE_CCM)
		auth_len += spum_wordalign_padlen(auth_len);

	bdesc->offset_icv = cpu_to_be16(auth_len);
	bdesc->offset_iv = cpu_to_be16(offset_iv);

	ptr += माप(काष्ठा BDESC_HEADER);
	buf_len += माप(काष्ठा BDESC_HEADER);

	/* === no MFM section === */

	/* === create the BD section === */

	/* add the BD header */
	bd = (काष्ठा BD_HEADER *)ptr;
	bd->size = cpu_to_be16(real_db_size);
	bd->prev_length = 0;

	ptr += माप(काष्ठा BD_HEADER);
	buf_len += माप(काष्ठा BD_HEADER);

	packet_dump("  SPU request header: ", spu_hdr, buf_len);

	वापस buf_len;
पूर्ण

/**
 * spum_cipher_req_init() - Build a SPU request message header, up to and
 * including the BD header.
 * @spu_hdr:      Start of SPU request header (MH)
 * @cipher_parms: Parameters that describe the cipher request
 *
 * Conकाष्ठा the message starting at spu_hdr. Caller should allocate this buffer
 * in DMA-able memory at least SPU_HEADER_ALLOC_LEN bytes दीर्घ.
 *
 * Return: the length of the SPU header in bytes. 0 अगर an error occurs.
 */
u16 spum_cipher_req_init(u8 *spu_hdr, काष्ठा spu_cipher_parms *cipher_parms)
अणु
	काष्ठा SPUHEADER *spuh;
	u32 protocol_bits = 0;
	u32 cipher_bits = 0;
	u32 ecf_bits = 0;
	u8 sctx_words = 0;
	u8 *ptr = spu_hdr;

	flow_log("%s()\n", __func__);
	flow_log("  cipher alg:%u mode:%u type %u\n", cipher_parms->alg,
		 cipher_parms->mode, cipher_parms->type);
	flow_log("  cipher_iv_len: %u\n", cipher_parms->iv_len);
	flow_log("    key: %d\n", cipher_parms->key_len);
	flow_dump("    key: ", cipher_parms->key_buf, cipher_parms->key_len);

	/* starting out: zero the header (plus some) */
	स_रखो(spu_hdr, 0, माप(काष्ठा SPUHEADER));
	ptr += माप(काष्ठा SPUHEADER);

	/* क्रमmat master header word */
	/* Do not set the next bit even though the datasheet says to */
	spuh = (काष्ठा SPUHEADER *)spu_hdr;

	spuh->mh.op_code = SPU_CRYPTO_OPERATION_GENERIC;
	spuh->mh.flags |= (MH_SCTX_PRES | MH_BDESC_PRES | MH_BD_PRES);

	/* Format sctx word 0 (protocol_bits) */
	sctx_words = 3;		/* size in words */

	/* copy the encryption keys in the SAD entry */
	अगर (cipher_parms->alg) अणु
		अगर (cipher_parms->key_len) अणु
			ptr += cipher_parms->key_len;
			sctx_words += cipher_parms->key_len / 4;
		पूर्ण

		/*
		 * अगर encrypting then set IV size, use SCTX IV unless no IV
		 * given here
		 */
		अगर (cipher_parms->iv_len) अणु
			/* Use SCTX IV */
			ecf_bits |= SCTX_IV;
			ptr += cipher_parms->iv_len;
			sctx_words += cipher_parms->iv_len / 4;
		पूर्ण
	पूर्ण

	/* Set the crypto parameters in the cipher.flags */
	cipher_bits |= cipher_parms->alg << CIPHER_ALG_SHIFT;
	cipher_bits |= cipher_parms->mode << CIPHER_MODE_SHIFT;
	cipher_bits |= cipher_parms->type << CIPHER_TYPE_SHIFT;

	/* copy the encryption keys in the SAD entry */
	अगर (cipher_parms->alg && cipher_parms->key_len)
		स_नकल(spuh + 1, cipher_parms->key_buf, cipher_parms->key_len);

	/* ग_लिखो in the total sctx length now that we know it */
	protocol_bits |= sctx_words;

	/* Endian adjust the SCTX */
	spuh->sa.proto_flags = cpu_to_be32(protocol_bits);

	/* Endian adjust the SCTX */
	spuh->sa.cipher_flags = cpu_to_be32(cipher_bits);
	spuh->sa.ecf = cpu_to_be32(ecf_bits);

	packet_dump("  SPU request header: ", spu_hdr,
		    माप(काष्ठा SPUHEADER));

	वापस माप(काष्ठा SPUHEADER) + cipher_parms->key_len +
		cipher_parms->iv_len + माप(काष्ठा BDESC_HEADER) +
		माप(काष्ठा BD_HEADER);
पूर्ण

/**
 * spum_cipher_req_finish() - Finish building a SPU request message header क्रम a
 * block cipher request. Assumes much of the header was alपढ़ोy filled in at
 * setkey() समय in spu_cipher_req_init().
 * @spu_hdr:         Start of the request message header (MH field)
 * @spu_req_hdr_len: Length in bytes of the SPU request header
 * @is_inbound:      0 encrypt, 1 decrypt
 * @cipher_parms:    Parameters describing cipher operation to be perक्रमmed
 * @data_size:       Length of the data in the BD field
 *
 * Assumes much of the header was alपढ़ोy filled in at setkey() समय in
 * spum_cipher_req_init().
 * spum_cipher_req_init() fills in the encryption key.
 */
व्योम spum_cipher_req_finish(u8 *spu_hdr,
			    u16 spu_req_hdr_len,
			    अचिन्हित पूर्णांक is_inbound,
			    काष्ठा spu_cipher_parms *cipher_parms,
			    अचिन्हित पूर्णांक data_size)
अणु
	काष्ठा SPUHEADER *spuh;
	काष्ठा BDESC_HEADER *bdesc;
	काष्ठा BD_HEADER *bd;
	u8 *bdesc_ptr = spu_hdr + spu_req_hdr_len -
	    (माप(काष्ठा BD_HEADER) + माप(काष्ठा BDESC_HEADER));

	u32 cipher_bits;

	flow_log("%s()\n", __func__);
	flow_log(" in: %u\n", is_inbound);
	flow_log(" cipher alg: %u, cipher_type: %u\n", cipher_parms->alg,
		 cipher_parms->type);

	/*
	 * In XTS mode, API माला_दो "i" parameter (block tweak) in IV.  For
	 * SPU-M, should be in start of the BD; tx_sg_create() copies it there.
	 * IV in SPU msg क्रम SPU-M should be 0, since that's the "j" parameter
	 * (block ctr within larger data unit) - given we can send entire disk
	 * block (<= 4KB) in 1 SPU msg, करोn't need to use this parameter.
	 */
	अगर (cipher_parms->mode == CIPHER_MODE_XTS)
		स_रखो(cipher_parms->iv_buf, 0, cipher_parms->iv_len);

	flow_log(" iv len: %d\n", cipher_parms->iv_len);
	flow_dump("    iv: ", cipher_parms->iv_buf, cipher_parms->iv_len);
	flow_log(" data_size: %u\n", data_size);

	/* क्रमmat master header word */
	/* Do not set the next bit even though the datasheet says to */
	spuh = (काष्ठा SPUHEADER *)spu_hdr;

	/* cipher_bits was initialized at setkey समय */
	cipher_bits = be32_to_cpu(spuh->sa.cipher_flags);

	/* Format sctx word 1 (cipher_bits) */
	अगर (is_inbound)
		cipher_bits |= CIPHER_INBOUND;
	अन्यथा
		cipher_bits &= ~CIPHER_INBOUND;

	अगर (cipher_parms->alg && cipher_parms->iv_buf && cipher_parms->iv_len)
		/* cipher iv provided so put it in here */
		स_नकल(bdesc_ptr - cipher_parms->iv_len, cipher_parms->iv_buf,
		       cipher_parms->iv_len);

	spuh->sa.cipher_flags = cpu_to_be32(cipher_bits);

	/* === create the BDESC section === */
	bdesc = (काष्ठा BDESC_HEADER *)bdesc_ptr;
	bdesc->offset_mac = 0;
	bdesc->length_mac = 0;
	bdesc->offset_crypto = 0;

	/* XTS mode, data_size needs to include tweak parameter */
	अगर (cipher_parms->mode == CIPHER_MODE_XTS)
		bdesc->length_crypto = cpu_to_be16(data_size +
						  SPU_XTS_TWEAK_SIZE);
	अन्यथा
		bdesc->length_crypto = cpu_to_be16(data_size);

	bdesc->offset_icv = 0;
	bdesc->offset_iv = 0;

	/* === no MFM section === */

	/* === create the BD section === */
	/* add the BD header */
	bd = (काष्ठा BD_HEADER *)(bdesc_ptr + माप(काष्ठा BDESC_HEADER));
	bd->size = cpu_to_be16(data_size);

	/* XTS mode, data_size needs to include tweak parameter */
	अगर (cipher_parms->mode == CIPHER_MODE_XTS)
		bd->size = cpu_to_be16(data_size + SPU_XTS_TWEAK_SIZE);
	अन्यथा
		bd->size = cpu_to_be16(data_size);

	bd->prev_length = 0;

	packet_dump("  SPU request header: ", spu_hdr, spu_req_hdr_len);
पूर्ण

/**
 * spum_request_pad() - Create pad bytes at the end of the data.
 * @pad_start:		Start of buffer where pad bytes are to be written
 * @gcm_ccm_padding:	length of GCM/CCM padding, in bytes
 * @hash_pad_len:	Number of bytes of padding extend data to full block
 * @auth_alg:		authentication algorithm
 * @auth_mode:		authentication mode
 * @total_sent:		length inserted at end of hash pad
 * @status_padding:	Number of bytes of padding to align STATUS word
 *
 * There may be three क्रमms of pad:
 *  1. GCM/CCM pad - क्रम GCM/CCM mode ciphers, pad to 16-byte alignment
 *  2. hash pad - pad to a block length, with 0x80 data terminator and
 *                size at the end
 *  3. STAT pad - to ensure the STAT field is 4-byte aligned
 */
व्योम spum_request_pad(u8 *pad_start,
		      u32 gcm_ccm_padding,
		      u32 hash_pad_len,
		      क्रमागत hash_alg auth_alg,
		      क्रमागत hash_mode auth_mode,
		      अचिन्हित पूर्णांक total_sent, u32 status_padding)
अणु
	u8 *ptr = pad_start;

	/* fix data alignent क्रम GCM/CCM */
	अगर (gcm_ccm_padding > 0) अणु
		flow_log("  GCM: padding to 16 byte alignment: %u bytes\n",
			 gcm_ccm_padding);
		स_रखो(ptr, 0, gcm_ccm_padding);
		ptr += gcm_ccm_padding;
	पूर्ण

	अगर (hash_pad_len > 0) अणु
		/* clear the padding section */
		स_रखो(ptr, 0, hash_pad_len);

		अगर ((auth_alg == HASH_ALG_AES) &&
		    (auth_mode == HASH_MODE_XCBC)) अणु
			/* AES/XCBC just requires padding to be 0s */
			ptr += hash_pad_len;
		पूर्ण अन्यथा अणु
			/* terminate the data */
			*ptr = 0x80;
			ptr += (hash_pad_len - माप(u64));

			/* add the size at the end as required per alg */
			अगर (auth_alg == HASH_ALG_MD5)
				*(__le64 *)ptr = cpu_to_le64(total_sent * 8ull);
			अन्यथा		/* SHA1, SHA2-224, SHA2-256 */
				*(__be64 *)ptr = cpu_to_be64(total_sent * 8ull);
			ptr += माप(u64);
		पूर्ण
	पूर्ण

	/* pad to a 4byte alignment क्रम STAT */
	अगर (status_padding > 0) अणु
		flow_log("  STAT: padding to 4 byte alignment: %u bytes\n",
			 status_padding);

		स_रखो(ptr, 0, status_padding);
		ptr += status_padding;
	पूर्ण
पूर्ण

/**
 * spum_xts_tweak_in_payload() - Indicate that SPUM DOES place the XTS tweak
 * field in the packet payload (rather than using IV)
 *
 * Return: 1
 */
u8 spum_xts_tweak_in_payload(व्योम)
अणु
	वापस 1;
पूर्ण

/**
 * spum_tx_status_len() - Return the length of the STATUS field in a SPU
 * response message.
 *
 * Return: Length of STATUS field in bytes.
 */
u8 spum_tx_status_len(व्योम)
अणु
	वापस SPU_TX_STATUS_LEN;
पूर्ण

/**
 * spum_rx_status_len() - Return the length of the STATUS field in a SPU
 * response message.
 *
 * Return: Length of STATUS field in bytes.
 */
u8 spum_rx_status_len(व्योम)
अणु
	वापस SPU_RX_STATUS_LEN;
पूर्ण

/**
 * spum_status_process() - Process the status from a SPU response message.
 * @statp:  start of STATUS word
 * Return:
 *   0 - अगर status is good and response should be processed
 *   !0 - status indicates an error and response is invalid
 */
पूर्णांक spum_status_process(u8 *statp)
अणु
	u32 status;

	status = __be32_to_cpu(*(__be32 *)statp);
	flow_log("SPU response STATUS %#08x\n", status);
	अगर (status & SPU_STATUS_ERROR_FLAG) अणु
		pr_err("%s() Warning: Error result from SPU: %#08x\n",
		       __func__, status);
		अगर (status & SPU_STATUS_INVALID_ICV)
			वापस SPU_INVALID_ICV;
		वापस -EBADMSG;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * spum_ccm_update_iv() - Update the IV as per the requirements क्रम CCM mode.
 *
 * @digestsize:		Digest size of this request
 * @cipher_parms:	(poपूर्णांकer to) cipher parmaeters, includes IV buf & IV len
 * @assoclen:		Length of AAD data
 * @chunksize:		length of input data to be sent in this req
 * @is_encrypt:		true अगर this is an output/encrypt operation
 * @is_esp:		true अगर this is an ESP / RFC4309 operation
 *
 */
व्योम spum_ccm_update_iv(अचिन्हित पूर्णांक digestsize,
			काष्ठा spu_cipher_parms *cipher_parms,
			अचिन्हित पूर्णांक assoclen,
			अचिन्हित पूर्णांक chunksize,
			bool is_encrypt,
			bool is_esp)
अणु
	u8 L;		/* L from CCM algorithm, length of plaपूर्णांकext data */
	u8 mprime;	/* M' from CCM algo, (M - 2) / 2, where M=authsize */
	u8 adata;

	अगर (cipher_parms->iv_len != CCM_AES_IV_SIZE) अणु
		pr_err("%s(): Invalid IV len %d for CCM mode, should be %d\n",
		       __func__, cipher_parms->iv_len, CCM_AES_IV_SIZE);
		वापस;
	पूर्ण

	/*
	 * IV needs to be क्रमmatted as follows:
	 *
	 * |          Byte 0               | Bytes 1 - N | Bytes (N+1) - 15 |
	 * | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | Bits 7 - 0  |    Bits 7 - 0    |
	 * | 0 |Ad?|(M - 2) / 2|   L - 1   |    Nonce    | Plaपूर्णांकext Length |
	 *
	 * Ad? = 1 अगर AAD present, 0 अगर not present
	 * M = size of auth field, 8, 12, or 16 bytes (SPU-M) -or-
	 *                         4, 6, 8, 10, 12, 14, 16 bytes (SPU2)
	 * L = Size of Plaपूर्णांकext Length field; Nonce size = 15 - L
	 *
	 * It appears that the crypto API alपढ़ोy expects the L-1 portion
	 * to be set in the first byte of the IV, which implicitly determines
	 * the nonce size, and also fills in the nonce.  But the other bits
	 * in byte 0 as well as the plaपूर्णांकext length need to be filled in.
	 *
	 * In rfc4309/esp mode, L is not alपढ़ोy in the supplied IV and
	 * we need to fill it in, as well as move the IV data to be after
	 * the salt
	 */
	अगर (is_esp) अणु
		L = CCM_ESP_L_VALUE;	/* RFC4309 has fixed L */
	पूर्ण अन्यथा अणु
		/* L' = plaintext length - 1 so Plaintext length is L' + 1 */
		L = ((cipher_parms->iv_buf[0] & CCM_B0_L_PRIME) >>
		      CCM_B0_L_PRIME_SHIFT) + 1;
	पूर्ण

	mprime = (digestsize - 2) >> 1;  /* M' = (M - 2) / 2 */
	adata = (assoclen > 0);  /* adata = 1 अगर any associated data */

	cipher_parms->iv_buf[0] = (adata << CCM_B0_ADATA_SHIFT) |
				  (mprime << CCM_B0_M_PRIME_SHIFT) |
				  ((L - 1) << CCM_B0_L_PRIME_SHIFT);

	/* Nonce is alपढ़ोy filled in by crypto API, and is 15 - L bytes */

	/* Don't include digest in plaपूर्णांकext size when decrypting */
	अगर (!is_encrypt)
		chunksize -= digestsize;

	/* Fill in length of plaपूर्णांकext, क्रमmatted to be L bytes दीर्घ */
	क्रमmat_value_ccm(chunksize, &cipher_parms->iv_buf[15 - L + 1], L);
पूर्ण

/**
 * spum_wordalign_padlen() - Given the length of a data field, determine the
 * padding required to align the data following this field on a 4-byte boundary.
 * @data_size: length of data field in bytes
 *
 * Return: length of status field padding, in bytes
 */
u32 spum_wordalign_padlen(u32 data_size)
अणु
	वापस ((data_size + 3) & ~3) - data_size;
पूर्ण
