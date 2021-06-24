<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Shared descriptors क्रम aead, skcipher algorithms
 *
 * Copyright 2016-2019 NXP
 */

#समावेश "compat.h"
#समावेश "desc_constr.h"
#समावेश "caamalg_desc.h"

/*
 * For aead functions, पढ़ो payload and ग_लिखो payload,
 * both of which are specअगरied in req->src and req->dst
 */
अटल अंतरभूत व्योम aead_append_src_dst(u32 *desc, u32 msg_type)
अणु
	append_seq_fअगरo_store(desc, 0, FIFOST_TYPE_MESSAGE_DATA | KEY_VLF);
	append_seq_fअगरo_load(desc, 0, FIFOLD_CLASS_BOTH |
			     KEY_VLF | msg_type | FIFOLD_TYPE_LASTBOTH);
पूर्ण

/* Set DK bit in class 1 operation अगर shared */
अटल अंतरभूत व्योम append_dec_op1(u32 *desc, u32 type)
अणु
	u32 *jump_cmd, *uncond_jump_cmd;

	/* DK bit is valid only क्रम AES */
	अगर ((type & OP_ALG_ALGSEL_MASK) != OP_ALG_ALGSEL_AES) अणु
		append_operation(desc, type | OP_ALG_AS_INITFINAL |
				 OP_ALG_DECRYPT);
		वापस;
	पूर्ण

	jump_cmd = append_jump(desc, JUMP_TEST_ALL | JUMP_COND_SHRD);
	append_operation(desc, type | OP_ALG_AS_INIT | OP_ALG_DECRYPT);
	uncond_jump_cmd = append_jump(desc, JUMP_TEST_ALL);
	set_jump_tgt_here(desc, jump_cmd);
	append_operation(desc, type | OP_ALG_AS_INIT | OP_ALG_DECRYPT |
			 OP_ALG_AAI_DK);
	set_jump_tgt_here(desc, uncond_jump_cmd);
पूर्ण

/**
 * cnstr_shdsc_aead_null_encap - IPSec ESP encapsulation shared descriptor
 *                               (non-protocol) with no (null) encryption.
 * @desc: poपूर्णांकer to buffer used क्रम descriptor स्थिरruction
 * @adata: poपूर्णांकer to authentication transक्रमm definitions.
 *         A split key is required क्रम SEC Era < 6; the size of the split key
 *         is specअगरied in this हाल. Valid algorithm values - one of
 *         OP_ALG_ALGSEL_अणुMD5, SHA1, SHA224, SHA256, SHA384, SHA512पूर्ण ANDed
 *         with OP_ALG_AAI_HMAC_PRECOMP.
 * @icvsize: पूर्णांकegrity check value (ICV) size (truncated or full)
 * @era: SEC Era
 */
व्योम cnstr_shdsc_aead_null_encap(u32 * स्थिर desc, काष्ठा alginfo *adata,
				 अचिन्हित पूर्णांक icvsize, पूर्णांक era)
अणु
	u32 *key_jump_cmd, *पढ़ो_move_cmd, *ग_लिखो_move_cmd;

	init_sh_desc(desc, HDR_SHARE_SERIAL);

	/* Skip अगर alपढ़ोy shared */
	key_jump_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
				   JUMP_COND_SHRD);
	अगर (era < 6) अणु
		अगर (adata->key_अंतरभूत)
			append_key_as_imm(desc, adata->key_virt,
					  adata->keylen_pad, adata->keylen,
					  CLASS_2 | KEY_DEST_MDHA_SPLIT |
					  KEY_ENC);
		अन्यथा
			append_key(desc, adata->key_dma, adata->keylen,
				   CLASS_2 | KEY_DEST_MDHA_SPLIT | KEY_ENC);
	पूर्ण अन्यथा अणु
		append_proto_dkp(desc, adata);
	पूर्ण
	set_jump_tgt_here(desc, key_jump_cmd);

	/* assoclen + cryptlen = seqinlen */
	append_math_sub(desc, REG3, SEQINLEN, REG0, CAAM_CMD_SZ);

	/* Prepare to पढ़ो and ग_लिखो cryptlen + assoclen bytes */
	append_math_add(desc, VARSEQINLEN, ZERO, REG3, CAAM_CMD_SZ);
	append_math_add(desc, VARSEQOUTLEN, ZERO, REG3, CAAM_CMD_SZ);

	/*
	 * MOVE_LEN opcode is not available in all SEC HW revisions,
	 * thus need to करो some magic, i.e. self-patch the descriptor
	 * buffer.
	 */
	पढ़ो_move_cmd = append_move(desc, MOVE_SRC_DESCBUF |
				    MOVE_DEST_MATH3 |
				    (0x6 << MOVE_LEN_SHIFT));
	ग_लिखो_move_cmd = append_move(desc, MOVE_SRC_MATH3 |
				     MOVE_DEST_DESCBUF |
				     MOVE_WAITCOMP |
				     (0x8 << MOVE_LEN_SHIFT));

	/* Class 2 operation */
	append_operation(desc, adata->algtype | OP_ALG_AS_INITFINAL |
			 OP_ALG_ENCRYPT);

	/* Read and ग_लिखो cryptlen bytes */
	aead_append_src_dst(desc, FIFOLD_TYPE_MSG | FIFOLD_TYPE_FLUSH1);

	set_move_tgt_here(desc, पढ़ो_move_cmd);
	set_move_tgt_here(desc, ग_लिखो_move_cmd);
	append_cmd(desc, CMD_LOAD | DISABLE_AUTO_INFO_FIFO);
	append_move(desc, MOVE_SRC_INFIFO_CL | MOVE_DEST_OUTFIFO |
		    MOVE_AUX_LS);

	/* Write ICV */
	append_seq_store(desc, icvsize, LDST_CLASS_2_CCB |
			 LDST_SRCDST_BYTE_CONTEXT);

	prपूर्णांक_hex_dump_debug("aead null enc shdesc@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);
पूर्ण
EXPORT_SYMBOL(cnstr_shdsc_aead_null_encap);

/**
 * cnstr_shdsc_aead_null_decap - IPSec ESP decapsulation shared descriptor
 *                               (non-protocol) with no (null) decryption.
 * @desc: poपूर्णांकer to buffer used क्रम descriptor स्थिरruction
 * @adata: poपूर्णांकer to authentication transक्रमm definitions.
 *         A split key is required क्रम SEC Era < 6; the size of the split key
 *         is specअगरied in this हाल. Valid algorithm values - one of
 *         OP_ALG_ALGSEL_अणुMD5, SHA1, SHA224, SHA256, SHA384, SHA512पूर्ण ANDed
 *         with OP_ALG_AAI_HMAC_PRECOMP.
 * @icvsize: पूर्णांकegrity check value (ICV) size (truncated or full)
 * @era: SEC Era
 */
व्योम cnstr_shdsc_aead_null_decap(u32 * स्थिर desc, काष्ठा alginfo *adata,
				 अचिन्हित पूर्णांक icvsize, पूर्णांक era)
अणु
	u32 *key_jump_cmd, *पढ़ो_move_cmd, *ग_लिखो_move_cmd, *jump_cmd;

	init_sh_desc(desc, HDR_SHARE_SERIAL);

	/* Skip अगर alपढ़ोy shared */
	key_jump_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
				   JUMP_COND_SHRD);
	अगर (era < 6) अणु
		अगर (adata->key_अंतरभूत)
			append_key_as_imm(desc, adata->key_virt,
					  adata->keylen_pad, adata->keylen,
					  CLASS_2 | KEY_DEST_MDHA_SPLIT |
					  KEY_ENC);
		अन्यथा
			append_key(desc, adata->key_dma, adata->keylen,
				   CLASS_2 | KEY_DEST_MDHA_SPLIT | KEY_ENC);
	पूर्ण अन्यथा अणु
		append_proto_dkp(desc, adata);
	पूर्ण
	set_jump_tgt_here(desc, key_jump_cmd);

	/* Class 2 operation */
	append_operation(desc, adata->algtype | OP_ALG_AS_INITFINAL |
			 OP_ALG_DECRYPT | OP_ALG_ICV_ON);

	/* assoclen + cryptlen = seqoutlen */
	append_math_sub(desc, REG2, SEQOUTLEN, REG0, CAAM_CMD_SZ);

	/* Prepare to पढ़ो and ग_लिखो cryptlen + assoclen bytes */
	append_math_add(desc, VARSEQINLEN, ZERO, REG2, CAAM_CMD_SZ);
	append_math_add(desc, VARSEQOUTLEN, ZERO, REG2, CAAM_CMD_SZ);

	/*
	 * MOVE_LEN opcode is not available in all SEC HW revisions,
	 * thus need to करो some magic, i.e. self-patch the descriptor
	 * buffer.
	 */
	पढ़ो_move_cmd = append_move(desc, MOVE_SRC_DESCBUF |
				    MOVE_DEST_MATH2 |
				    (0x6 << MOVE_LEN_SHIFT));
	ग_लिखो_move_cmd = append_move(desc, MOVE_SRC_MATH2 |
				     MOVE_DEST_DESCBUF |
				     MOVE_WAITCOMP |
				     (0x8 << MOVE_LEN_SHIFT));

	/* Read and ग_लिखो cryptlen bytes */
	aead_append_src_dst(desc, FIFOLD_TYPE_MSG | FIFOLD_TYPE_FLUSH1);

	/*
	 * Insert a NOP here, since we need at least 4 inकाष्ठाions between
	 * code patching the descriptor buffer and the location being patched.
	 */
	jump_cmd = append_jump(desc, JUMP_TEST_ALL);
	set_jump_tgt_here(desc, jump_cmd);

	set_move_tgt_here(desc, पढ़ो_move_cmd);
	set_move_tgt_here(desc, ग_लिखो_move_cmd);
	append_cmd(desc, CMD_LOAD | DISABLE_AUTO_INFO_FIFO);
	append_move(desc, MOVE_SRC_INFIFO_CL | MOVE_DEST_OUTFIFO |
		    MOVE_AUX_LS);
	append_cmd(desc, CMD_LOAD | ENABLE_AUTO_INFO_FIFO);

	/* Load ICV */
	append_seq_fअगरo_load(desc, icvsize, FIFOLD_CLASS_CLASS2 |
			     FIFOLD_TYPE_LAST2 | FIFOLD_TYPE_ICV);

	prपूर्णांक_hex_dump_debug("aead null dec shdesc@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);
पूर्ण
EXPORT_SYMBOL(cnstr_shdsc_aead_null_decap);

अटल व्योम init_sh_desc_key_aead(u32 * स्थिर desc,
				  काष्ठा alginfo * स्थिर cdata,
				  काष्ठा alginfo * स्थिर adata,
				  स्थिर bool is_rfc3686, u32 *nonce, पूर्णांक era)
अणु
	u32 *key_jump_cmd;
	अचिन्हित पूर्णांक enckeylen = cdata->keylen;

	/* Note: Context रेजिस्टरs are saved. */
	init_sh_desc(desc, HDR_SHARE_SERIAL | HDR_SAVECTX);

	/* Skip अगर alपढ़ोy shared */
	key_jump_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
				   JUMP_COND_SHRD);

	/*
	 * RFC3686 specअगरic:
	 *	| key = अणुAUTH_KEY, ENC_KEY, NONCEपूर्ण
	 *	| enckeylen = encryption key size + nonce size
	 */
	अगर (is_rfc3686)
		enckeylen -= CTR_RFC3686_NONCE_SIZE;

	अगर (era < 6) अणु
		अगर (adata->key_अंतरभूत)
			append_key_as_imm(desc, adata->key_virt,
					  adata->keylen_pad, adata->keylen,
					  CLASS_2 | KEY_DEST_MDHA_SPLIT |
					  KEY_ENC);
		अन्यथा
			append_key(desc, adata->key_dma, adata->keylen,
				   CLASS_2 | KEY_DEST_MDHA_SPLIT | KEY_ENC);
	पूर्ण अन्यथा अणु
		append_proto_dkp(desc, adata);
	पूर्ण

	अगर (cdata->key_अंतरभूत)
		append_key_as_imm(desc, cdata->key_virt, enckeylen,
				  enckeylen, CLASS_1 | KEY_DEST_CLASS_REG);
	अन्यथा
		append_key(desc, cdata->key_dma, enckeylen, CLASS_1 |
			   KEY_DEST_CLASS_REG);

	/* Load Counter पूर्णांकo CONTEXT1 reg */
	अगर (is_rfc3686) अणु
		append_load_as_imm(desc, nonce, CTR_RFC3686_NONCE_SIZE,
				   LDST_CLASS_IND_CCB |
				   LDST_SRCDST_BYTE_OUTFIFO | LDST_IMM);
		append_move(desc,
			    MOVE_SRC_OUTFIFO |
			    MOVE_DEST_CLASS1CTX |
			    (16 << MOVE_OFFSET_SHIFT) |
			    (CTR_RFC3686_NONCE_SIZE << MOVE_LEN_SHIFT));
	पूर्ण

	set_jump_tgt_here(desc, key_jump_cmd);
पूर्ण

/**
 * cnstr_shdsc_aead_encap - IPSec ESP encapsulation shared descriptor
 *                          (non-protocol).
 * @desc: poपूर्णांकer to buffer used क्रम descriptor स्थिरruction
 * @cdata: poपूर्णांकer to block cipher transक्रमm definitions
 *         Valid algorithm values - one of OP_ALG_ALGSEL_अणुAES, DES, 3DESपूर्ण ANDed
 *         with OP_ALG_AAI_CBC or OP_ALG_AAI_CTR_MOD128.
 * @adata: poपूर्णांकer to authentication transक्रमm definitions.
 *         A split key is required क्रम SEC Era < 6; the size of the split key
 *         is specअगरied in this हाल. Valid algorithm values - one of
 *         OP_ALG_ALGSEL_अणुMD5, SHA1, SHA224, SHA256, SHA384, SHA512पूर्ण ANDed
 *         with OP_ALG_AAI_HMAC_PRECOMP.
 * @ivsize: initialization vector size
 * @icvsize: पूर्णांकegrity check value (ICV) size (truncated or full)
 * @is_rfc3686: true when ctr(aes) is wrapped by rfc3686 ढाँचा
 * @nonce: poपूर्णांकer to rfc3686 nonce
 * @ctx1_iv_off: IV offset in CONTEXT1 रेजिस्टर
 * @is_qi: true when called from caam/qi
 * @era: SEC Era
 */
व्योम cnstr_shdsc_aead_encap(u32 * स्थिर desc, काष्ठा alginfo *cdata,
			    काष्ठा alginfo *adata, अचिन्हित पूर्णांक ivsize,
			    अचिन्हित पूर्णांक icvsize, स्थिर bool is_rfc3686,
			    u32 *nonce, स्थिर u32 ctx1_iv_off, स्थिर bool is_qi,
			    पूर्णांक era)
अणु
	/* Note: Context रेजिस्टरs are saved. */
	init_sh_desc_key_aead(desc, cdata, adata, is_rfc3686, nonce, era);

	/* Class 2 operation */
	append_operation(desc, adata->algtype | OP_ALG_AS_INITFINAL |
			 OP_ALG_ENCRYPT);

	अगर (is_qi) अणु
		u32 *रुको_load_cmd;

		/* REG3 = assoclen */
		append_seq_load(desc, 4, LDST_CLASS_DECO |
				LDST_SRCDST_WORD_DECO_MATH3 |
				(4 << LDST_OFFSET_SHIFT));

		रुको_load_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
					    JUMP_COND_CALM | JUMP_COND_NCP |
					    JUMP_COND_NOP | JUMP_COND_NIP |
					    JUMP_COND_NIFP);
		set_jump_tgt_here(desc, रुको_load_cmd);

		append_seq_load(desc, ivsize, LDST_CLASS_1_CCB |
				LDST_SRCDST_BYTE_CONTEXT |
				(ctx1_iv_off << LDST_OFFSET_SHIFT));
	पूर्ण

	/* Read and ग_लिखो assoclen bytes */
	अगर (is_qi || era < 3) अणु
		append_math_add(desc, VARSEQINLEN, ZERO, REG3, CAAM_CMD_SZ);
		append_math_add(desc, VARSEQOUTLEN, ZERO, REG3, CAAM_CMD_SZ);
	पूर्ण अन्यथा अणु
		append_math_add(desc, VARSEQINLEN, ZERO, DPOVRD, CAAM_CMD_SZ);
		append_math_add(desc, VARSEQOUTLEN, ZERO, DPOVRD, CAAM_CMD_SZ);
	पूर्ण

	/* Skip assoc data */
	append_seq_fअगरo_store(desc, 0, FIFOST_TYPE_SKIP | FIFOLDST_VLF);

	/* पढ़ो assoc beक्रमe पढ़ोing payload */
	append_seq_fअगरo_load(desc, 0, FIFOLD_CLASS_CLASS2 | FIFOLD_TYPE_MSG |
				      FIFOLDST_VLF);

	/* Load Counter पूर्णांकo CONTEXT1 reg */
	अगर (is_rfc3686)
		append_load_imm_be32(desc, 1, LDST_IMM | LDST_CLASS_1_CCB |
				     LDST_SRCDST_BYTE_CONTEXT |
				     ((ctx1_iv_off + CTR_RFC3686_IV_SIZE) <<
				      LDST_OFFSET_SHIFT));

	/* Class 1 operation */
	append_operation(desc, cdata->algtype | OP_ALG_AS_INITFINAL |
			 OP_ALG_ENCRYPT);

	/* Read and ग_लिखो cryptlen bytes */
	append_math_add(desc, VARSEQINLEN, SEQINLEN, REG0, CAAM_CMD_SZ);
	append_math_add(desc, VARSEQOUTLEN, SEQINLEN, REG0, CAAM_CMD_SZ);
	aead_append_src_dst(desc, FIFOLD_TYPE_MSG1OUT2);

	/* Write ICV */
	append_seq_store(desc, icvsize, LDST_CLASS_2_CCB |
			 LDST_SRCDST_BYTE_CONTEXT);

	prपूर्णांक_hex_dump_debug("aead enc shdesc@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);
पूर्ण
EXPORT_SYMBOL(cnstr_shdsc_aead_encap);

/**
 * cnstr_shdsc_aead_decap - IPSec ESP decapsulation shared descriptor
 *                          (non-protocol).
 * @desc: poपूर्णांकer to buffer used क्रम descriptor स्थिरruction
 * @cdata: poपूर्णांकer to block cipher transक्रमm definitions
 *         Valid algorithm values - one of OP_ALG_ALGSEL_अणुAES, DES, 3DESपूर्ण ANDed
 *         with OP_ALG_AAI_CBC or OP_ALG_AAI_CTR_MOD128.
 * @adata: poपूर्णांकer to authentication transक्रमm definitions.
 *         A split key is required क्रम SEC Era < 6; the size of the split key
 *         is specअगरied in this हाल. Valid algorithm values - one of
 *         OP_ALG_ALGSEL_अणुMD5, SHA1, SHA224, SHA256, SHA384, SHA512पूर्ण ANDed
 *         with OP_ALG_AAI_HMAC_PRECOMP.
 * @ivsize: initialization vector size
 * @icvsize: पूर्णांकegrity check value (ICV) size (truncated or full)
 * @geniv: whether to generate Encrypted Chain IV
 * @is_rfc3686: true when ctr(aes) is wrapped by rfc3686 ढाँचा
 * @nonce: poपूर्णांकer to rfc3686 nonce
 * @ctx1_iv_off: IV offset in CONTEXT1 रेजिस्टर
 * @is_qi: true when called from caam/qi
 * @era: SEC Era
 */
व्योम cnstr_shdsc_aead_decap(u32 * स्थिर desc, काष्ठा alginfo *cdata,
			    काष्ठा alginfo *adata, अचिन्हित पूर्णांक ivsize,
			    अचिन्हित पूर्णांक icvsize, स्थिर bool geniv,
			    स्थिर bool is_rfc3686, u32 *nonce,
			    स्थिर u32 ctx1_iv_off, स्थिर bool is_qi, पूर्णांक era)
अणु
	/* Note: Context रेजिस्टरs are saved. */
	init_sh_desc_key_aead(desc, cdata, adata, is_rfc3686, nonce, era);

	/* Class 2 operation */
	append_operation(desc, adata->algtype | OP_ALG_AS_INITFINAL |
			 OP_ALG_DECRYPT | OP_ALG_ICV_ON);

	अगर (is_qi) अणु
		u32 *रुको_load_cmd;

		/* REG3 = assoclen */
		append_seq_load(desc, 4, LDST_CLASS_DECO |
				LDST_SRCDST_WORD_DECO_MATH3 |
				(4 << LDST_OFFSET_SHIFT));

		रुको_load_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
					    JUMP_COND_CALM | JUMP_COND_NCP |
					    JUMP_COND_NOP | JUMP_COND_NIP |
					    JUMP_COND_NIFP);
		set_jump_tgt_here(desc, रुको_load_cmd);

		अगर (!geniv)
			append_seq_load(desc, ivsize, LDST_CLASS_1_CCB |
					LDST_SRCDST_BYTE_CONTEXT |
					(ctx1_iv_off << LDST_OFFSET_SHIFT));
	पूर्ण

	/* Read and ग_लिखो assoclen bytes */
	अगर (is_qi || era < 3) अणु
		append_math_add(desc, VARSEQINLEN, ZERO, REG3, CAAM_CMD_SZ);
		अगर (geniv)
			append_math_add_imm_u32(desc, VARSEQOUTLEN, REG3, IMM,
						ivsize);
		अन्यथा
			append_math_add(desc, VARSEQOUTLEN, ZERO, REG3,
					CAAM_CMD_SZ);
	पूर्ण अन्यथा अणु
		append_math_add(desc, VARSEQINLEN, ZERO, DPOVRD, CAAM_CMD_SZ);
		अगर (geniv)
			append_math_add_imm_u32(desc, VARSEQOUTLEN, DPOVRD, IMM,
						ivsize);
		अन्यथा
			append_math_add(desc, VARSEQOUTLEN, ZERO, DPOVRD,
					CAAM_CMD_SZ);
	पूर्ण

	/* Skip assoc data */
	append_seq_fअगरo_store(desc, 0, FIFOST_TYPE_SKIP | FIFOLDST_VLF);

	/* पढ़ो assoc beक्रमe पढ़ोing payload */
	append_seq_fअगरo_load(desc, 0, FIFOLD_CLASS_CLASS2 | FIFOLD_TYPE_MSG |
			     KEY_VLF);

	अगर (geniv) अणु
		append_seq_load(desc, ivsize, LDST_CLASS_1_CCB |
				LDST_SRCDST_BYTE_CONTEXT |
				(ctx1_iv_off << LDST_OFFSET_SHIFT));
		append_move(desc, MOVE_SRC_CLASS1CTX | MOVE_DEST_CLASS2INFIFO |
			    (ctx1_iv_off << MOVE_OFFSET_SHIFT) | ivsize);
	पूर्ण

	/* Load Counter पूर्णांकo CONTEXT1 reg */
	अगर (is_rfc3686)
		append_load_imm_be32(desc, 1, LDST_IMM | LDST_CLASS_1_CCB |
				     LDST_SRCDST_BYTE_CONTEXT |
				     ((ctx1_iv_off + CTR_RFC3686_IV_SIZE) <<
				      LDST_OFFSET_SHIFT));

	/* Choose operation */
	अगर (ctx1_iv_off)
		append_operation(desc, cdata->algtype | OP_ALG_AS_INITFINAL |
				 OP_ALG_DECRYPT);
	अन्यथा
		append_dec_op1(desc, cdata->algtype);

	/* Read and ग_लिखो cryptlen bytes */
	append_math_add(desc, VARSEQINLEN, SEQOUTLEN, REG0, CAAM_CMD_SZ);
	append_math_add(desc, VARSEQOUTLEN, SEQOUTLEN, REG0, CAAM_CMD_SZ);
	aead_append_src_dst(desc, FIFOLD_TYPE_MSG);

	/* Load ICV */
	append_seq_fअगरo_load(desc, icvsize, FIFOLD_CLASS_CLASS2 |
			     FIFOLD_TYPE_LAST2 | FIFOLD_TYPE_ICV);

	prपूर्णांक_hex_dump_debug("aead dec shdesc@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);
पूर्ण
EXPORT_SYMBOL(cnstr_shdsc_aead_decap);

/**
 * cnstr_shdsc_aead_givencap - IPSec ESP encapsulation shared descriptor
 *                             (non-protocol) with HW-generated initialization
 *                             vector.
 * @desc: poपूर्णांकer to buffer used क्रम descriptor स्थिरruction
 * @cdata: poपूर्णांकer to block cipher transक्रमm definitions
 *         Valid algorithm values - one of OP_ALG_ALGSEL_अणुAES, DES, 3DESपूर्ण ANDed
 *         with OP_ALG_AAI_CBC or OP_ALG_AAI_CTR_MOD128.
 * @adata: poपूर्णांकer to authentication transक्रमm definitions.
 *         A split key is required क्रम SEC Era < 6; the size of the split key
 *         is specअगरied in this हाल. Valid algorithm values - one of
 *         OP_ALG_ALGSEL_अणुMD5, SHA1, SHA224, SHA256, SHA384, SHA512पूर्ण ANDed
 *         with OP_ALG_AAI_HMAC_PRECOMP.
 * @ivsize: initialization vector size
 * @icvsize: पूर्णांकegrity check value (ICV) size (truncated or full)
 * @is_rfc3686: true when ctr(aes) is wrapped by rfc3686 ढाँचा
 * @nonce: poपूर्णांकer to rfc3686 nonce
 * @ctx1_iv_off: IV offset in CONTEXT1 रेजिस्टर
 * @is_qi: true when called from caam/qi
 * @era: SEC Era
 */
व्योम cnstr_shdsc_aead_givencap(u32 * स्थिर desc, काष्ठा alginfo *cdata,
			       काष्ठा alginfo *adata, अचिन्हित पूर्णांक ivsize,
			       अचिन्हित पूर्णांक icvsize, स्थिर bool is_rfc3686,
			       u32 *nonce, स्थिर u32 ctx1_iv_off,
			       स्थिर bool is_qi, पूर्णांक era)
अणु
	u32 geniv, moveiv;
	u32 *रुको_cmd;

	/* Note: Context रेजिस्टरs are saved. */
	init_sh_desc_key_aead(desc, cdata, adata, is_rfc3686, nonce, era);

	अगर (is_qi) अणु
		u32 *रुको_load_cmd;

		/* REG3 = assoclen */
		append_seq_load(desc, 4, LDST_CLASS_DECO |
				LDST_SRCDST_WORD_DECO_MATH3 |
				(4 << LDST_OFFSET_SHIFT));

		रुको_load_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
					    JUMP_COND_CALM | JUMP_COND_NCP |
					    JUMP_COND_NOP | JUMP_COND_NIP |
					    JUMP_COND_NIFP);
		set_jump_tgt_here(desc, रुको_load_cmd);
	पूर्ण

	अगर (is_rfc3686) अणु
		अगर (is_qi)
			append_seq_load(desc, ivsize, LDST_CLASS_1_CCB |
					LDST_SRCDST_BYTE_CONTEXT |
					(ctx1_iv_off << LDST_OFFSET_SHIFT));

		जाओ copy_iv;
	पूर्ण

	/* Generate IV */
	geniv = NFIFOENTRY_STYPE_PAD | NFIFOENTRY_DEST_DECO |
		NFIFOENTRY_DTYPE_MSG | NFIFOENTRY_LC1 |
		NFIFOENTRY_PTYPE_RND | (ivsize << NFIFOENTRY_DLEN_SHIFT);
	append_load_imm_u32(desc, geniv, LDST_CLASS_IND_CCB |
			    LDST_SRCDST_WORD_INFO_FIFO | LDST_IMM);
	append_cmd(desc, CMD_LOAD | DISABLE_AUTO_INFO_FIFO);
	append_move(desc, MOVE_WAITCOMP |
		    MOVE_SRC_INFIFO | MOVE_DEST_CLASS1CTX |
		    (ctx1_iv_off << MOVE_OFFSET_SHIFT) |
		    (ivsize << MOVE_LEN_SHIFT));
	append_cmd(desc, CMD_LOAD | ENABLE_AUTO_INFO_FIFO);

copy_iv:
	/* Copy IV to class 1 context */
	append_move(desc, MOVE_SRC_CLASS1CTX | MOVE_DEST_OUTFIFO |
		    (ctx1_iv_off << MOVE_OFFSET_SHIFT) |
		    (ivsize << MOVE_LEN_SHIFT));

	/* Return to encryption */
	append_operation(desc, adata->algtype | OP_ALG_AS_INITFINAL |
			 OP_ALG_ENCRYPT);

	/* Read and ग_लिखो assoclen bytes */
	अगर (is_qi || era < 3) अणु
		append_math_add(desc, VARSEQINLEN, ZERO, REG3, CAAM_CMD_SZ);
		append_math_add(desc, VARSEQOUTLEN, ZERO, REG3, CAAM_CMD_SZ);
	पूर्ण अन्यथा अणु
		append_math_add(desc, VARSEQINLEN, ZERO, DPOVRD, CAAM_CMD_SZ);
		append_math_add(desc, VARSEQOUTLEN, ZERO, DPOVRD, CAAM_CMD_SZ);
	पूर्ण

	/* Skip assoc data */
	append_seq_fअगरo_store(desc, 0, FIFOST_TYPE_SKIP | FIFOLDST_VLF);

	/* पढ़ो assoc beक्रमe पढ़ोing payload */
	append_seq_fअगरo_load(desc, 0, FIFOLD_CLASS_CLASS2 | FIFOLD_TYPE_MSG |
			     KEY_VLF);

	/* Copy iv from outfअगरo to class 2 fअगरo */
	moveiv = NFIFOENTRY_STYPE_OFIFO | NFIFOENTRY_DEST_CLASS2 |
		 NFIFOENTRY_DTYPE_MSG | (ivsize << NFIFOENTRY_DLEN_SHIFT);
	append_load_imm_u32(desc, moveiv, LDST_CLASS_IND_CCB |
			    LDST_SRCDST_WORD_INFO_FIFO | LDST_IMM);
	append_load_imm_u32(desc, ivsize, LDST_CLASS_2_CCB |
			    LDST_SRCDST_WORD_DATASZ_REG | LDST_IMM);

	/* Load Counter पूर्णांकo CONTEXT1 reg */
	अगर (is_rfc3686)
		append_load_imm_be32(desc, 1, LDST_IMM | LDST_CLASS_1_CCB |
				     LDST_SRCDST_BYTE_CONTEXT |
				     ((ctx1_iv_off + CTR_RFC3686_IV_SIZE) <<
				      LDST_OFFSET_SHIFT));

	/* Class 1 operation */
	append_operation(desc, cdata->algtype | OP_ALG_AS_INITFINAL |
			 OP_ALG_ENCRYPT);

	/* Will ग_लिखो ivsize + cryptlen */
	append_math_add(desc, VARSEQOUTLEN, SEQINLEN, REG0, CAAM_CMD_SZ);

	/* Not need to reload iv */
	append_seq_fअगरo_load(desc, ivsize,
			     FIFOLD_CLASS_SKIP);

	/* Will पढ़ो cryptlen */
	append_math_add(desc, VARSEQINLEN, SEQINLEN, REG0, CAAM_CMD_SZ);

	/*
	 * Wait क्रम IV transfer (ofअगरo -> class2) to finish beक्रमe starting
	 * ciphertext transfer (ofअगरo -> बाह्यal memory).
	 */
	रुको_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL | JUMP_COND_NIFP);
	set_jump_tgt_here(desc, रुको_cmd);

	append_seq_fअगरo_load(desc, 0, FIFOLD_CLASS_BOTH | KEY_VLF |
			     FIFOLD_TYPE_MSG1OUT2 | FIFOLD_TYPE_LASTBOTH);
	append_seq_fअगरo_store(desc, 0, FIFOST_TYPE_MESSAGE_DATA | KEY_VLF);

	/* Write ICV */
	append_seq_store(desc, icvsize, LDST_CLASS_2_CCB |
			 LDST_SRCDST_BYTE_CONTEXT);

	prपूर्णांक_hex_dump_debug("aead givenc shdesc@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);
पूर्ण
EXPORT_SYMBOL(cnstr_shdsc_aead_givencap);

/**
 * cnstr_shdsc_gcm_encap - gcm encapsulation shared descriptor
 * @desc: poपूर्णांकer to buffer used क्रम descriptor स्थिरruction
 * @cdata: poपूर्णांकer to block cipher transक्रमm definitions
 *         Valid algorithm values - OP_ALG_ALGSEL_AES ANDed with OP_ALG_AAI_GCM.
 * @ivsize: initialization vector size
 * @icvsize: पूर्णांकegrity check value (ICV) size (truncated or full)
 * @is_qi: true when called from caam/qi
 */
व्योम cnstr_shdsc_gcm_encap(u32 * स्थिर desc, काष्ठा alginfo *cdata,
			   अचिन्हित पूर्णांक ivsize, अचिन्हित पूर्णांक icvsize,
			   स्थिर bool is_qi)
अणु
	u32 *key_jump_cmd, *zero_payload_jump_cmd, *zero_assoc_jump_cmd1,
	    *zero_assoc_jump_cmd2;

	init_sh_desc(desc, HDR_SHARE_SERIAL);

	/* skip key loading अगर they are loaded due to sharing */
	key_jump_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
				   JUMP_COND_SHRD);
	अगर (cdata->key_अंतरभूत)
		append_key_as_imm(desc, cdata->key_virt, cdata->keylen,
				  cdata->keylen, CLASS_1 | KEY_DEST_CLASS_REG);
	अन्यथा
		append_key(desc, cdata->key_dma, cdata->keylen, CLASS_1 |
			   KEY_DEST_CLASS_REG);
	set_jump_tgt_here(desc, key_jump_cmd);

	/* class 1 operation */
	append_operation(desc, cdata->algtype | OP_ALG_AS_INITFINAL |
			 OP_ALG_ENCRYPT);

	अगर (is_qi) अणु
		u32 *रुको_load_cmd;

		/* REG3 = assoclen */
		append_seq_load(desc, 4, LDST_CLASS_DECO |
				LDST_SRCDST_WORD_DECO_MATH3 |
				(4 << LDST_OFFSET_SHIFT));

		रुको_load_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
					    JUMP_COND_CALM | JUMP_COND_NCP |
					    JUMP_COND_NOP | JUMP_COND_NIP |
					    JUMP_COND_NIFP);
		set_jump_tgt_here(desc, रुको_load_cmd);

		append_math_sub_imm_u32(desc, VARSEQOUTLEN, SEQINLEN, IMM,
					ivsize);
	पूर्ण अन्यथा अणु
		append_math_sub(desc, VARSEQOUTLEN, SEQINLEN, REG0,
				CAAM_CMD_SZ);
	पूर्ण

	/* अगर assoclen + cryptlen is ZERO, skip to ICV ग_लिखो */
	zero_assoc_jump_cmd2 = append_jump(desc, JUMP_TEST_ALL |
						 JUMP_COND_MATH_Z);

	अगर (is_qi)
		append_seq_fअगरo_load(desc, ivsize, FIFOLD_CLASS_CLASS1 |
				     FIFOLD_TYPE_IV | FIFOLD_TYPE_FLUSH1);

	/* अगर assoclen is ZERO, skip पढ़ोing the assoc data */
	append_math_add(desc, VARSEQINLEN, ZERO, REG3, CAAM_CMD_SZ);
	zero_assoc_jump_cmd1 = append_jump(desc, JUMP_TEST_ALL |
					   JUMP_COND_MATH_Z);

	append_math_add(desc, VARSEQOUTLEN, ZERO, REG3, CAAM_CMD_SZ);

	/* skip assoc data */
	append_seq_fअगरo_store(desc, 0, FIFOST_TYPE_SKIP | FIFOLDST_VLF);

	/* cryptlen = seqinlen - assoclen */
	append_math_sub(desc, VARSEQOUTLEN, SEQINLEN, REG3, CAAM_CMD_SZ);

	/* अगर cryptlen is ZERO jump to zero-payload commands */
	zero_payload_jump_cmd = append_jump(desc, JUMP_TEST_ALL |
					    JUMP_COND_MATH_Z);

	/* पढ़ो assoc data */
	append_seq_fअगरo_load(desc, 0, FIFOLD_CLASS_CLASS1 | FIFOLDST_VLF |
			     FIFOLD_TYPE_AAD | FIFOLD_TYPE_FLUSH1);
	set_jump_tgt_here(desc, zero_assoc_jump_cmd1);

	append_math_sub(desc, VARSEQINLEN, SEQINLEN, REG0, CAAM_CMD_SZ);

	/* ग_लिखो encrypted data */
	append_seq_fअगरo_store(desc, 0, FIFOST_TYPE_MESSAGE_DATA | FIFOLDST_VLF);

	/* पढ़ो payload data */
	append_seq_fअगरo_load(desc, 0, FIFOLD_CLASS_CLASS1 | FIFOLDST_VLF |
			     FIFOLD_TYPE_MSG | FIFOLD_TYPE_LAST1);

	/* jump to ICV writing */
	अगर (is_qi)
		append_jump(desc, JUMP_TEST_ALL | 4);
	अन्यथा
		append_jump(desc, JUMP_TEST_ALL | 2);

	/* zero-payload commands */
	set_jump_tgt_here(desc, zero_payload_jump_cmd);

	/* पढ़ो assoc data */
	append_seq_fअगरo_load(desc, 0, FIFOLD_CLASS_CLASS1 | FIFOLDST_VLF |
			     FIFOLD_TYPE_AAD | FIFOLD_TYPE_LAST1);
	अगर (is_qi)
		/* jump to ICV writing */
		append_jump(desc, JUMP_TEST_ALL | 2);

	/* There is no input data */
	set_jump_tgt_here(desc, zero_assoc_jump_cmd2);

	अगर (is_qi)
		append_seq_fअगरo_load(desc, ivsize, FIFOLD_CLASS_CLASS1 |
				     FIFOLD_TYPE_IV | FIFOLD_TYPE_FLUSH1 |
				     FIFOLD_TYPE_LAST1);

	/* ग_लिखो ICV */
	append_seq_store(desc, icvsize, LDST_CLASS_1_CCB |
			 LDST_SRCDST_BYTE_CONTEXT);

	prपूर्णांक_hex_dump_debug("gcm enc shdesc@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);
पूर्ण
EXPORT_SYMBOL(cnstr_shdsc_gcm_encap);

/**
 * cnstr_shdsc_gcm_decap - gcm decapsulation shared descriptor
 * @desc: poपूर्णांकer to buffer used क्रम descriptor स्थिरruction
 * @cdata: poपूर्णांकer to block cipher transक्रमm definitions
 *         Valid algorithm values - OP_ALG_ALGSEL_AES ANDed with OP_ALG_AAI_GCM.
 * @ivsize: initialization vector size
 * @icvsize: पूर्णांकegrity check value (ICV) size (truncated or full)
 * @is_qi: true when called from caam/qi
 */
व्योम cnstr_shdsc_gcm_decap(u32 * स्थिर desc, काष्ठा alginfo *cdata,
			   अचिन्हित पूर्णांक ivsize, अचिन्हित पूर्णांक icvsize,
			   स्थिर bool is_qi)
अणु
	u32 *key_jump_cmd, *zero_payload_jump_cmd, *zero_assoc_jump_cmd1;

	init_sh_desc(desc, HDR_SHARE_SERIAL);

	/* skip key loading अगर they are loaded due to sharing */
	key_jump_cmd = append_jump(desc, JUMP_JSL |
				   JUMP_TEST_ALL | JUMP_COND_SHRD);
	अगर (cdata->key_अंतरभूत)
		append_key_as_imm(desc, cdata->key_virt, cdata->keylen,
				  cdata->keylen, CLASS_1 | KEY_DEST_CLASS_REG);
	अन्यथा
		append_key(desc, cdata->key_dma, cdata->keylen, CLASS_1 |
			   KEY_DEST_CLASS_REG);
	set_jump_tgt_here(desc, key_jump_cmd);

	/* class 1 operation */
	append_operation(desc, cdata->algtype | OP_ALG_AS_INITFINAL |
			 OP_ALG_DECRYPT | OP_ALG_ICV_ON);

	अगर (is_qi) अणु
		u32 *रुको_load_cmd;

		/* REG3 = assoclen */
		append_seq_load(desc, 4, LDST_CLASS_DECO |
				LDST_SRCDST_WORD_DECO_MATH3 |
				(4 << LDST_OFFSET_SHIFT));

		रुको_load_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
					    JUMP_COND_CALM | JUMP_COND_NCP |
					    JUMP_COND_NOP | JUMP_COND_NIP |
					    JUMP_COND_NIFP);
		set_jump_tgt_here(desc, रुको_load_cmd);

		append_seq_fअगरo_load(desc, ivsize, FIFOLD_CLASS_CLASS1 |
				     FIFOLD_TYPE_IV | FIFOLD_TYPE_FLUSH1);
	पूर्ण

	/* अगर assoclen is ZERO, skip पढ़ोing the assoc data */
	append_math_add(desc, VARSEQINLEN, ZERO, REG3, CAAM_CMD_SZ);
	zero_assoc_jump_cmd1 = append_jump(desc, JUMP_TEST_ALL |
						 JUMP_COND_MATH_Z);

	append_math_add(desc, VARSEQOUTLEN, ZERO, REG3, CAAM_CMD_SZ);

	/* skip assoc data */
	append_seq_fअगरo_store(desc, 0, FIFOST_TYPE_SKIP | FIFOLDST_VLF);

	/* पढ़ो assoc data */
	append_seq_fअगरo_load(desc, 0, FIFOLD_CLASS_CLASS1 | FIFOLDST_VLF |
			     FIFOLD_TYPE_AAD | FIFOLD_TYPE_FLUSH1);

	set_jump_tgt_here(desc, zero_assoc_jump_cmd1);

	/* cryptlen = seqoutlen - assoclen */
	append_math_sub(desc, VARSEQINLEN, SEQOUTLEN, REG0, CAAM_CMD_SZ);

	/* jump to zero-payload command अगर cryptlen is zero */
	zero_payload_jump_cmd = append_jump(desc, JUMP_TEST_ALL |
					    JUMP_COND_MATH_Z);

	append_math_sub(desc, VARSEQOUTLEN, SEQOUTLEN, REG0, CAAM_CMD_SZ);

	/* store encrypted data */
	append_seq_fअगरo_store(desc, 0, FIFOST_TYPE_MESSAGE_DATA | FIFOLDST_VLF);

	/* पढ़ो payload data */
	append_seq_fअगरo_load(desc, 0, FIFOLD_CLASS_CLASS1 | FIFOLDST_VLF |
			     FIFOLD_TYPE_MSG | FIFOLD_TYPE_FLUSH1);

	/* zero-payload command */
	set_jump_tgt_here(desc, zero_payload_jump_cmd);

	/* पढ़ो ICV */
	append_seq_fअगरo_load(desc, icvsize, FIFOLD_CLASS_CLASS1 |
			     FIFOLD_TYPE_ICV | FIFOLD_TYPE_LAST1);

	prपूर्णांक_hex_dump_debug("gcm dec shdesc@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);
पूर्ण
EXPORT_SYMBOL(cnstr_shdsc_gcm_decap);

/**
 * cnstr_shdsc_rfc4106_encap - IPSec ESP gcm encapsulation shared descriptor
 *                             (non-protocol).
 * @desc: poपूर्णांकer to buffer used क्रम descriptor स्थिरruction
 * @cdata: poपूर्णांकer to block cipher transक्रमm definitions
 *         Valid algorithm values - OP_ALG_ALGSEL_AES ANDed with OP_ALG_AAI_GCM.
 * @ivsize: initialization vector size
 * @icvsize: पूर्णांकegrity check value (ICV) size (truncated or full)
 * @is_qi: true when called from caam/qi
 *
 * Input sequence: AAD | PTXT
 * Output sequence: AAD | CTXT | ICV
 * AAD length (assoclen), which includes the IV length, is available in Math3.
 */
व्योम cnstr_shdsc_rfc4106_encap(u32 * स्थिर desc, काष्ठा alginfo *cdata,
			       अचिन्हित पूर्णांक ivsize, अचिन्हित पूर्णांक icvsize,
			       स्थिर bool is_qi)
अणु
	u32 *key_jump_cmd, *zero_cryptlen_jump_cmd, *skip_inकाष्ठाions;
	init_sh_desc(desc, HDR_SHARE_SERIAL);

	/* Skip key loading अगर it is loaded due to sharing */
	key_jump_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
				   JUMP_COND_SHRD);
	अगर (cdata->key_अंतरभूत)
		append_key_as_imm(desc, cdata->key_virt, cdata->keylen,
				  cdata->keylen, CLASS_1 | KEY_DEST_CLASS_REG);
	अन्यथा
		append_key(desc, cdata->key_dma, cdata->keylen, CLASS_1 |
			   KEY_DEST_CLASS_REG);
	set_jump_tgt_here(desc, key_jump_cmd);

	/* Class 1 operation */
	append_operation(desc, cdata->algtype | OP_ALG_AS_INITFINAL |
			 OP_ALG_ENCRYPT);

	अगर (is_qi) अणु
		u32 *रुको_load_cmd;

		/* REG3 = assoclen */
		append_seq_load(desc, 4, LDST_CLASS_DECO |
				LDST_SRCDST_WORD_DECO_MATH3 |
				(4 << LDST_OFFSET_SHIFT));

		रुको_load_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
					    JUMP_COND_CALM | JUMP_COND_NCP |
					    JUMP_COND_NOP | JUMP_COND_NIP |
					    JUMP_COND_NIFP);
		set_jump_tgt_here(desc, रुको_load_cmd);

		/* Read salt and IV */
		append_fअगरo_load_as_imm(desc, (व्योम *)(cdata->key_virt +
					cdata->keylen), 4, FIFOLD_CLASS_CLASS1 |
					FIFOLD_TYPE_IV);
		append_seq_fअगरo_load(desc, ivsize, FIFOLD_CLASS_CLASS1 |
				     FIFOLD_TYPE_IV | FIFOLD_TYPE_FLUSH1);
	पूर्ण

	append_math_sub_imm_u32(desc, VARSEQINLEN, REG3, IMM, ivsize);
	append_math_add(desc, VARSEQOUTLEN, ZERO, REG3, CAAM_CMD_SZ);

	/* Skip AAD */
	append_seq_fअगरo_store(desc, 0, FIFOST_TYPE_SKIP | FIFOLDST_VLF);

	/* Read cryptlen and set this value पूर्णांकo VARSEQOUTLEN */
	append_math_sub(desc, VARSEQOUTLEN, SEQINLEN, REG3, CAAM_CMD_SZ);

	/* If cryptlen is ZERO jump to AAD command */
	zero_cryptlen_jump_cmd = append_jump(desc, JUMP_TEST_ALL |
					    JUMP_COND_MATH_Z);

	/* Read AAD data */
	append_seq_fअगरo_load(desc, 0, FIFOLD_CLASS_CLASS1 | FIFOLDST_VLF |
			     FIFOLD_TYPE_AAD | FIFOLD_TYPE_FLUSH1);

	/* Workaround क्रम erratum A-005473 (simultaneous SEQ FIFO skips) */
	append_seq_fअगरo_store(desc, 0, FIFOST_TYPE_MESSAGE_DATA);

	/* Skip IV */
	append_seq_fअगरo_load(desc, ivsize, FIFOLD_CLASS_SKIP);
	append_math_add(desc, VARSEQINLEN, VARSEQOUTLEN, REG0, CAAM_CMD_SZ);

	/* Write encrypted data */
	append_seq_fअगरo_store(desc, 0, FIFOST_TYPE_MESSAGE_DATA | FIFOLDST_VLF);

	/* Read payload data */
	append_seq_fअगरo_load(desc, 0, FIFOLD_CLASS_CLASS1 | FIFOLDST_VLF |
			     FIFOLD_TYPE_MSG | FIFOLD_TYPE_LAST1);

	/* Jump inकाष्ठाions to aव्योम द्विगुन पढ़ोing of AAD */
	skip_inकाष्ठाions = append_jump(desc, JUMP_TEST_ALL);

	/* There is no input data, cryptlen = 0 */
	set_jump_tgt_here(desc, zero_cryptlen_jump_cmd);

	/* Read AAD */
	append_seq_fअगरo_load(desc, 0, FIFOLD_CLASS_CLASS1 | FIFOLDST_VLF |
			     FIFOLD_TYPE_AAD | FIFOLD_TYPE_LAST1);

	set_jump_tgt_here(desc, skip_inकाष्ठाions);

	/* Write ICV */
	append_seq_store(desc, icvsize, LDST_CLASS_1_CCB |
			 LDST_SRCDST_BYTE_CONTEXT);

	prपूर्णांक_hex_dump_debug("rfc4106 enc shdesc@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);
पूर्ण
EXPORT_SYMBOL(cnstr_shdsc_rfc4106_encap);

/**
 * cnstr_shdsc_rfc4106_decap - IPSec ESP gcm decapsulation shared descriptor
 *                             (non-protocol).
 * @desc: poपूर्णांकer to buffer used क्रम descriptor स्थिरruction
 * @cdata: poपूर्णांकer to block cipher transक्रमm definitions
 *         Valid algorithm values - OP_ALG_ALGSEL_AES ANDed with OP_ALG_AAI_GCM.
 * @ivsize: initialization vector size
 * @icvsize: पूर्णांकegrity check value (ICV) size (truncated or full)
 * @is_qi: true when called from caam/qi
 */
व्योम cnstr_shdsc_rfc4106_decap(u32 * स्थिर desc, काष्ठा alginfo *cdata,
			       अचिन्हित पूर्णांक ivsize, अचिन्हित पूर्णांक icvsize,
			       स्थिर bool is_qi)
अणु
	u32 *key_jump_cmd;

	init_sh_desc(desc, HDR_SHARE_SERIAL);

	/* Skip key loading अगर it is loaded due to sharing */
	key_jump_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
				   JUMP_COND_SHRD);
	अगर (cdata->key_अंतरभूत)
		append_key_as_imm(desc, cdata->key_virt, cdata->keylen,
				  cdata->keylen, CLASS_1 |
				  KEY_DEST_CLASS_REG);
	अन्यथा
		append_key(desc, cdata->key_dma, cdata->keylen, CLASS_1 |
			   KEY_DEST_CLASS_REG);
	set_jump_tgt_here(desc, key_jump_cmd);

	/* Class 1 operation */
	append_operation(desc, cdata->algtype | OP_ALG_AS_INITFINAL |
			 OP_ALG_DECRYPT | OP_ALG_ICV_ON);

	अगर (is_qi) अणु
		u32 *रुको_load_cmd;

		/* REG3 = assoclen */
		append_seq_load(desc, 4, LDST_CLASS_DECO |
				LDST_SRCDST_WORD_DECO_MATH3 |
				(4 << LDST_OFFSET_SHIFT));

		रुको_load_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
					    JUMP_COND_CALM | JUMP_COND_NCP |
					    JUMP_COND_NOP | JUMP_COND_NIP |
					    JUMP_COND_NIFP);
		set_jump_tgt_here(desc, रुको_load_cmd);

		/* Read salt and IV */
		append_fअगरo_load_as_imm(desc, (व्योम *)(cdata->key_virt +
					cdata->keylen), 4, FIFOLD_CLASS_CLASS1 |
					FIFOLD_TYPE_IV);
		append_seq_fअगरo_load(desc, ivsize, FIFOLD_CLASS_CLASS1 |
				     FIFOLD_TYPE_IV | FIFOLD_TYPE_FLUSH1);
	पूर्ण

	append_math_sub_imm_u32(desc, VARSEQINLEN, REG3, IMM, ivsize);
	append_math_add(desc, VARSEQOUTLEN, ZERO, REG3, CAAM_CMD_SZ);

	/* Read assoc data */
	append_seq_fअगरo_load(desc, 0, FIFOLD_CLASS_CLASS1 | FIFOLDST_VLF |
			     FIFOLD_TYPE_AAD | FIFOLD_TYPE_FLUSH1);

	/* Skip IV */
	append_seq_fअगरo_load(desc, ivsize, FIFOLD_CLASS_SKIP);

	/* Will पढ़ो cryptlen bytes */
	append_math_sub(desc, VARSEQINLEN, SEQOUTLEN, REG3, CAAM_CMD_SZ);

	/* Workaround क्रम erratum A-005473 (simultaneous SEQ FIFO skips) */
	append_seq_fअगरo_load(desc, 0, FIFOLD_CLASS_CLASS1 | FIFOLD_TYPE_MSG);

	/* Skip assoc data */
	append_seq_fअगरo_store(desc, 0, FIFOST_TYPE_SKIP | FIFOLDST_VLF);

	/* Will ग_लिखो cryptlen bytes */
	append_math_sub(desc, VARSEQOUTLEN, SEQOUTLEN, REG0, CAAM_CMD_SZ);

	/* Store payload data */
	append_seq_fअगरo_store(desc, 0, FIFOST_TYPE_MESSAGE_DATA | FIFOLDST_VLF);

	/* Read encrypted data */
	append_seq_fअगरo_load(desc, 0, FIFOLD_CLASS_CLASS1 | FIFOLDST_VLF |
			     FIFOLD_TYPE_MSG | FIFOLD_TYPE_FLUSH1);

	/* Read ICV */
	append_seq_fअगरo_load(desc, icvsize, FIFOLD_CLASS_CLASS1 |
			     FIFOLD_TYPE_ICV | FIFOLD_TYPE_LAST1);

	prपूर्णांक_hex_dump_debug("rfc4106 dec shdesc@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);
पूर्ण
EXPORT_SYMBOL(cnstr_shdsc_rfc4106_decap);

/**
 * cnstr_shdsc_rfc4543_encap - IPSec ESP gmac encapsulation shared descriptor
 *                             (non-protocol).
 * @desc: poपूर्णांकer to buffer used क्रम descriptor स्थिरruction
 * @cdata: poपूर्णांकer to block cipher transक्रमm definitions
 *         Valid algorithm values - OP_ALG_ALGSEL_AES ANDed with OP_ALG_AAI_GCM.
 * @ivsize: initialization vector size
 * @icvsize: पूर्णांकegrity check value (ICV) size (truncated or full)
 * @is_qi: true when called from caam/qi
 */
व्योम cnstr_shdsc_rfc4543_encap(u32 * स्थिर desc, काष्ठा alginfo *cdata,
			       अचिन्हित पूर्णांक ivsize, अचिन्हित पूर्णांक icvsize,
			       स्थिर bool is_qi)
अणु
	u32 *key_jump_cmd, *पढ़ो_move_cmd, *ग_लिखो_move_cmd;

	init_sh_desc(desc, HDR_SHARE_SERIAL);

	/* Skip key loading अगर it is loaded due to sharing */
	key_jump_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
				   JUMP_COND_SHRD);
	अगर (cdata->key_अंतरभूत)
		append_key_as_imm(desc, cdata->key_virt, cdata->keylen,
				  cdata->keylen, CLASS_1 | KEY_DEST_CLASS_REG);
	अन्यथा
		append_key(desc, cdata->key_dma, cdata->keylen, CLASS_1 |
			   KEY_DEST_CLASS_REG);
	set_jump_tgt_here(desc, key_jump_cmd);

	/* Class 1 operation */
	append_operation(desc, cdata->algtype | OP_ALG_AS_INITFINAL |
			 OP_ALG_ENCRYPT);

	अगर (is_qi) अणु
		/* assoclen is not needed, skip it */
		append_seq_fअगरo_load(desc, 4, FIFOLD_CLASS_SKIP);

		/* Read salt and IV */
		append_fअगरo_load_as_imm(desc, (व्योम *)(cdata->key_virt +
					cdata->keylen), 4, FIFOLD_CLASS_CLASS1 |
					FIFOLD_TYPE_IV);
		append_seq_fअगरo_load(desc, ivsize, FIFOLD_CLASS_CLASS1 |
				     FIFOLD_TYPE_IV | FIFOLD_TYPE_FLUSH1);
	पूर्ण

	/* assoclen + cryptlen = seqinlen */
	append_math_sub(desc, REG3, SEQINLEN, REG0, CAAM_CMD_SZ);

	/*
	 * MOVE_LEN opcode is not available in all SEC HW revisions,
	 * thus need to करो some magic, i.e. self-patch the descriptor
	 * buffer.
	 */
	पढ़ो_move_cmd = append_move(desc, MOVE_SRC_DESCBUF | MOVE_DEST_MATH3 |
				    (0x6 << MOVE_LEN_SHIFT));
	ग_लिखो_move_cmd = append_move(desc, MOVE_SRC_MATH3 | MOVE_DEST_DESCBUF |
				     (0x8 << MOVE_LEN_SHIFT) | MOVE_WAITCOMP);

	/* Will पढ़ो assoclen + cryptlen bytes */
	append_math_sub(desc, VARSEQINLEN, SEQINLEN, REG0, CAAM_CMD_SZ);

	/* Will ग_लिखो assoclen + cryptlen bytes */
	append_math_sub(desc, VARSEQOUTLEN, SEQINLEN, REG0, CAAM_CMD_SZ);

	/* Read and ग_लिखो assoclen + cryptlen bytes */
	aead_append_src_dst(desc, FIFOLD_TYPE_AAD);

	set_move_tgt_here(desc, पढ़ो_move_cmd);
	set_move_tgt_here(desc, ग_लिखो_move_cmd);
	append_cmd(desc, CMD_LOAD | DISABLE_AUTO_INFO_FIFO);
	/* Move payload data to OFIFO */
	append_move(desc, MOVE_SRC_INFIFO_CL | MOVE_DEST_OUTFIFO);

	/* Write ICV */
	append_seq_store(desc, icvsize, LDST_CLASS_1_CCB |
			 LDST_SRCDST_BYTE_CONTEXT);

	prपूर्णांक_hex_dump_debug("rfc4543 enc shdesc@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);
पूर्ण
EXPORT_SYMBOL(cnstr_shdsc_rfc4543_encap);

/**
 * cnstr_shdsc_rfc4543_decap - IPSec ESP gmac decapsulation shared descriptor
 *                             (non-protocol).
 * @desc: poपूर्णांकer to buffer used क्रम descriptor स्थिरruction
 * @cdata: poपूर्णांकer to block cipher transक्रमm definitions
 *         Valid algorithm values - OP_ALG_ALGSEL_AES ANDed with OP_ALG_AAI_GCM.
 * @ivsize: initialization vector size
 * @icvsize: पूर्णांकegrity check value (ICV) size (truncated or full)
 * @is_qi: true when called from caam/qi
 */
व्योम cnstr_shdsc_rfc4543_decap(u32 * स्थिर desc, काष्ठा alginfo *cdata,
			       अचिन्हित पूर्णांक ivsize, अचिन्हित पूर्णांक icvsize,
			       स्थिर bool is_qi)
अणु
	u32 *key_jump_cmd, *पढ़ो_move_cmd, *ग_लिखो_move_cmd;

	init_sh_desc(desc, HDR_SHARE_SERIAL);

	/* Skip key loading अगर it is loaded due to sharing */
	key_jump_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
				   JUMP_COND_SHRD);
	अगर (cdata->key_अंतरभूत)
		append_key_as_imm(desc, cdata->key_virt, cdata->keylen,
				  cdata->keylen, CLASS_1 | KEY_DEST_CLASS_REG);
	अन्यथा
		append_key(desc, cdata->key_dma, cdata->keylen, CLASS_1 |
			   KEY_DEST_CLASS_REG);
	set_jump_tgt_here(desc, key_jump_cmd);

	/* Class 1 operation */
	append_operation(desc, cdata->algtype | OP_ALG_AS_INITFINAL |
			 OP_ALG_DECRYPT | OP_ALG_ICV_ON);

	अगर (is_qi) अणु
		/* assoclen is not needed, skip it */
		append_seq_fअगरo_load(desc, 4, FIFOLD_CLASS_SKIP);

		/* Read salt and IV */
		append_fअगरo_load_as_imm(desc, (व्योम *)(cdata->key_virt +
					cdata->keylen), 4, FIFOLD_CLASS_CLASS1 |
					FIFOLD_TYPE_IV);
		append_seq_fअगरo_load(desc, ivsize, FIFOLD_CLASS_CLASS1 |
				     FIFOLD_TYPE_IV | FIFOLD_TYPE_FLUSH1);
	पूर्ण

	/* assoclen + cryptlen = seqoutlen */
	append_math_sub(desc, REG3, SEQOUTLEN, REG0, CAAM_CMD_SZ);

	/*
	 * MOVE_LEN opcode is not available in all SEC HW revisions,
	 * thus need to करो some magic, i.e. self-patch the descriptor
	 * buffer.
	 */
	पढ़ो_move_cmd = append_move(desc, MOVE_SRC_DESCBUF | MOVE_DEST_MATH3 |
				    (0x6 << MOVE_LEN_SHIFT));
	ग_लिखो_move_cmd = append_move(desc, MOVE_SRC_MATH3 | MOVE_DEST_DESCBUF |
				     (0x8 << MOVE_LEN_SHIFT) | MOVE_WAITCOMP);

	/* Will पढ़ो assoclen + cryptlen bytes */
	append_math_sub(desc, VARSEQINLEN, SEQOUTLEN, REG0, CAAM_CMD_SZ);

	/* Will ग_लिखो assoclen + cryptlen bytes */
	append_math_sub(desc, VARSEQOUTLEN, SEQOUTLEN, REG0, CAAM_CMD_SZ);

	/* Store payload data */
	append_seq_fअगरo_store(desc, 0, FIFOST_TYPE_MESSAGE_DATA | FIFOLDST_VLF);

	/* In-snoop assoclen + cryptlen data */
	append_seq_fअगरo_load(desc, 0, FIFOLD_CLASS_BOTH | FIFOLDST_VLF |
			     FIFOLD_TYPE_AAD | FIFOLD_TYPE_LAST2FLUSH1);

	set_move_tgt_here(desc, पढ़ो_move_cmd);
	set_move_tgt_here(desc, ग_लिखो_move_cmd);
	append_cmd(desc, CMD_LOAD | DISABLE_AUTO_INFO_FIFO);
	/* Move payload data to OFIFO */
	append_move(desc, MOVE_SRC_INFIFO_CL | MOVE_DEST_OUTFIFO);
	append_cmd(desc, CMD_LOAD | ENABLE_AUTO_INFO_FIFO);

	/* Read ICV */
	append_seq_fअगरo_load(desc, icvsize, FIFOLD_CLASS_CLASS1 |
			     FIFOLD_TYPE_ICV | FIFOLD_TYPE_LAST1);

	prपूर्णांक_hex_dump_debug("rfc4543 dec shdesc@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);
पूर्ण
EXPORT_SYMBOL(cnstr_shdsc_rfc4543_decap);

/**
 * cnstr_shdsc_chachapoly - Chacha20 + Poly1305 generic AEAD (rfc7539) and
 *                          IPsec ESP (rfc7634, a.k.a. rfc7539esp) shared
 *                          descriptor (non-protocol).
 * @desc: poपूर्णांकer to buffer used क्रम descriptor स्थिरruction
 * @cdata: poपूर्णांकer to block cipher transक्रमm definitions
 *         Valid algorithm values - OP_ALG_ALGSEL_CHACHA20 ANDed with
 *         OP_ALG_AAI_AEAD.
 * @adata: poपूर्णांकer to authentication transक्रमm definitions
 *         Valid algorithm values - OP_ALG_ALGSEL_POLY1305 ANDed with
 *         OP_ALG_AAI_AEAD.
 * @ivsize: initialization vector size
 * @icvsize: पूर्णांकegrity check value (ICV) size (truncated or full)
 * @encap: true अगर encapsulation, false अगर decapsulation
 * @is_qi: true when called from caam/qi
 */
व्योम cnstr_shdsc_chachapoly(u32 * स्थिर desc, काष्ठा alginfo *cdata,
			    काष्ठा alginfo *adata, अचिन्हित पूर्णांक ivsize,
			    अचिन्हित पूर्णांक icvsize, स्थिर bool encap,
			    स्थिर bool is_qi)
अणु
	u32 *key_jump_cmd, *रुको_cmd;
	u32 nfअगरo;
	स्थिर bool is_ipsec = (ivsize != CHACHAPOLY_IV_SIZE);

	/* Note: Context रेजिस्टरs are saved. */
	init_sh_desc(desc, HDR_SHARE_SERIAL | HDR_SAVECTX);

	/* skip key loading अगर they are loaded due to sharing */
	key_jump_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
				   JUMP_COND_SHRD);

	append_key_as_imm(desc, cdata->key_virt, cdata->keylen, cdata->keylen,
			  CLASS_1 | KEY_DEST_CLASS_REG);

	/* For IPsec load the salt from keymat in the context रेजिस्टर */
	अगर (is_ipsec)
		append_load_as_imm(desc, cdata->key_virt + cdata->keylen, 4,
				   LDST_CLASS_1_CCB | LDST_SRCDST_BYTE_CONTEXT |
				   4 << LDST_OFFSET_SHIFT);

	set_jump_tgt_here(desc, key_jump_cmd);

	/* Class 2 and 1 operations: Poly & ChaCha */
	अगर (encap) अणु
		append_operation(desc, adata->algtype | OP_ALG_AS_INITFINAL |
				 OP_ALG_ENCRYPT);
		append_operation(desc, cdata->algtype | OP_ALG_AS_INITFINAL |
				 OP_ALG_ENCRYPT);
	पूर्ण अन्यथा अणु
		append_operation(desc, adata->algtype | OP_ALG_AS_INITFINAL |
				 OP_ALG_DECRYPT | OP_ALG_ICV_ON);
		append_operation(desc, cdata->algtype | OP_ALG_AS_INITFINAL |
				 OP_ALG_DECRYPT);
	पूर्ण

	अगर (is_qi) अणु
		u32 *रुको_load_cmd;
		u32 ctx1_iv_off = is_ipsec ? 8 : 4;

		/* REG3 = assoclen */
		append_seq_load(desc, 4, LDST_CLASS_DECO |
				LDST_SRCDST_WORD_DECO_MATH3 |
				4 << LDST_OFFSET_SHIFT);

		रुको_load_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
					    JUMP_COND_CALM | JUMP_COND_NCP |
					    JUMP_COND_NOP | JUMP_COND_NIP |
					    JUMP_COND_NIFP);
		set_jump_tgt_here(desc, रुको_load_cmd);

		append_seq_load(desc, ivsize, LDST_CLASS_1_CCB |
				LDST_SRCDST_BYTE_CONTEXT |
				ctx1_iv_off << LDST_OFFSET_SHIFT);
	पूर्ण

	/*
	 * MAGIC with NFIFO
	 * Read associated data from the input and send them to class1 and
	 * class2 alignment blocks. From class1 send data to output fअगरo and
	 * then ग_लिखो it to memory since we करोn't need to encrypt AD.
	 */
	nfअगरo = NFIFOENTRY_DEST_BOTH | NFIFOENTRY_FC1 | NFIFOENTRY_FC2 |
		NFIFOENTRY_DTYPE_POLY | NFIFOENTRY_BND;
	append_load_imm_u32(desc, nfअगरo, LDST_CLASS_IND_CCB |
			    LDST_SRCDST_WORD_INFO_FIFO_SM | LDLEN_MATH3);

	append_math_add(desc, VARSEQINLEN, ZERO, REG3, CAAM_CMD_SZ);
	append_math_add(desc, VARSEQOUTLEN, ZERO, REG3, CAAM_CMD_SZ);
	append_seq_fअगरo_load(desc, 0, FIFOLD_TYPE_NOINFOFIFO |
			     FIFOLD_CLASS_CLASS1 | LDST_VLF);
	append_move_len(desc, MOVE_AUX_LS | MOVE_SRC_AUX_ABLK |
			MOVE_DEST_OUTFIFO | MOVELEN_MRSEL_MATH3);
	append_seq_fअगरo_store(desc, 0, FIFOST_TYPE_MESSAGE_DATA | LDST_VLF);

	/* IPsec - copy IV at the output */
	अगर (is_ipsec)
		append_seq_fअगरo_store(desc, ivsize, FIFOST_TYPE_METADATA |
				      0x2 << 25);

	रुको_cmd = append_jump(desc, JUMP_JSL | JUMP_TYPE_LOCAL |
			       JUMP_COND_NOP | JUMP_TEST_ALL);
	set_jump_tgt_here(desc, रुको_cmd);

	अगर (encap) अणु
		/* Read and ग_लिखो cryptlen bytes */
		append_math_add(desc, VARSEQINLEN, SEQINLEN, REG0, CAAM_CMD_SZ);
		append_math_add(desc, VARSEQOUTLEN, SEQINLEN, REG0,
				CAAM_CMD_SZ);
		aead_append_src_dst(desc, FIFOLD_TYPE_MSG1OUT2);

		/* Write ICV */
		append_seq_store(desc, icvsize, LDST_CLASS_2_CCB |
				 LDST_SRCDST_BYTE_CONTEXT);
	पूर्ण अन्यथा अणु
		/* Read and ग_लिखो cryptlen bytes */
		append_math_add(desc, VARSEQINLEN, SEQOUTLEN, REG0,
				CAAM_CMD_SZ);
		append_math_add(desc, VARSEQOUTLEN, SEQOUTLEN, REG0,
				CAAM_CMD_SZ);
		aead_append_src_dst(desc, FIFOLD_TYPE_MSG);

		/* Load ICV क्रम verअगरication */
		append_seq_fअगरo_load(desc, icvsize, FIFOLD_CLASS_CLASS2 |
				     FIFOLD_TYPE_LAST2 | FIFOLD_TYPE_ICV);
	पूर्ण

	prपूर्णांक_hex_dump_debug("chachapoly shdesc@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);
पूर्ण
EXPORT_SYMBOL(cnstr_shdsc_chachapoly);

/* For skcipher encrypt and decrypt, पढ़ो from req->src and ग_लिखो to req->dst */
अटल अंतरभूत व्योम skcipher_append_src_dst(u32 *desc)
अणु
	append_math_add(desc, VARSEQOUTLEN, SEQINLEN, REG0, CAAM_CMD_SZ);
	append_math_add(desc, VARSEQINLEN, SEQINLEN, REG0, CAAM_CMD_SZ);
	append_seq_fअगरo_load(desc, 0, FIFOLD_CLASS_CLASS1 |
			     KEY_VLF | FIFOLD_TYPE_MSG | FIFOLD_TYPE_LAST1);
	append_seq_fअगरo_store(desc, 0, FIFOST_TYPE_MESSAGE_DATA | KEY_VLF);
पूर्ण

/**
 * cnstr_shdsc_skcipher_encap - skcipher encapsulation shared descriptor
 * @desc: poपूर्णांकer to buffer used क्रम descriptor स्थिरruction
 * @cdata: poपूर्णांकer to block cipher transक्रमm definitions
 *         Valid algorithm values - one of OP_ALG_ALGSEL_अणुAES, DES, 3DESपूर्ण ANDed
 *         with OP_ALG_AAI_CBC or OP_ALG_AAI_CTR_MOD128
 *                                - OP_ALG_ALGSEL_CHACHA20
 * @ivsize: initialization vector size
 * @is_rfc3686: true when ctr(aes) is wrapped by rfc3686 ढाँचा
 * @ctx1_iv_off: IV offset in CONTEXT1 रेजिस्टर
 */
व्योम cnstr_shdsc_skcipher_encap(u32 * स्थिर desc, काष्ठा alginfo *cdata,
				अचिन्हित पूर्णांक ivsize, स्थिर bool is_rfc3686,
				स्थिर u32 ctx1_iv_off)
अणु
	u32 *key_jump_cmd;
	u32 options = cdata->algtype | OP_ALG_AS_INIT | OP_ALG_ENCRYPT;
	bool is_chacha20 = ((cdata->algtype & OP_ALG_ALGSEL_MASK) ==
			    OP_ALG_ALGSEL_CHACHA20);

	init_sh_desc(desc, HDR_SHARE_SERIAL | HDR_SAVECTX);
	/* Skip अगर alपढ़ोy shared */
	key_jump_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
				   JUMP_COND_SHRD);

	/* Load class1 key only */
	append_key_as_imm(desc, cdata->key_virt, cdata->keylen,
			  cdata->keylen, CLASS_1 | KEY_DEST_CLASS_REG);

	/* Load nonce पूर्णांकo CONTEXT1 reg */
	अगर (is_rfc3686) अणु
		स्थिर u8 *nonce = cdata->key_virt + cdata->keylen;

		append_load_as_imm(desc, nonce, CTR_RFC3686_NONCE_SIZE,
				   LDST_CLASS_IND_CCB |
				   LDST_SRCDST_BYTE_OUTFIFO | LDST_IMM);
		append_move(desc, MOVE_WAITCOMP | MOVE_SRC_OUTFIFO |
			    MOVE_DEST_CLASS1CTX | (16 << MOVE_OFFSET_SHIFT) |
			    (CTR_RFC3686_NONCE_SIZE << MOVE_LEN_SHIFT));
	पूर्ण

	set_jump_tgt_here(desc, key_jump_cmd);

	/* Load IV, अगर there is one */
	अगर (ivsize)
		append_seq_load(desc, ivsize, LDST_SRCDST_BYTE_CONTEXT |
				LDST_CLASS_1_CCB | (ctx1_iv_off <<
				LDST_OFFSET_SHIFT));

	/* Load counter पूर्णांकo CONTEXT1 reg */
	अगर (is_rfc3686)
		append_load_imm_be32(desc, 1, LDST_IMM | LDST_CLASS_1_CCB |
				     LDST_SRCDST_BYTE_CONTEXT |
				     ((ctx1_iv_off + CTR_RFC3686_IV_SIZE) <<
				      LDST_OFFSET_SHIFT));

	/* Load operation */
	अगर (is_chacha20)
		options |= OP_ALG_AS_FINALIZE;
	append_operation(desc, options);

	/* Perक्रमm operation */
	skcipher_append_src_dst(desc);

	/* Store IV */
	अगर (!is_chacha20 && ivsize)
		append_seq_store(desc, ivsize, LDST_SRCDST_BYTE_CONTEXT |
				 LDST_CLASS_1_CCB | (ctx1_iv_off <<
				 LDST_OFFSET_SHIFT));

	prपूर्णांक_hex_dump_debug("skcipher enc shdesc@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);
पूर्ण
EXPORT_SYMBOL(cnstr_shdsc_skcipher_encap);

/**
 * cnstr_shdsc_skcipher_decap - skcipher decapsulation shared descriptor
 * @desc: poपूर्णांकer to buffer used क्रम descriptor स्थिरruction
 * @cdata: poपूर्णांकer to block cipher transक्रमm definitions
 *         Valid algorithm values - one of OP_ALG_ALGSEL_अणुAES, DES, 3DESपूर्ण ANDed
 *         with OP_ALG_AAI_CBC or OP_ALG_AAI_CTR_MOD128
 *                                - OP_ALG_ALGSEL_CHACHA20
 * @ivsize: initialization vector size
 * @is_rfc3686: true when ctr(aes) is wrapped by rfc3686 ढाँचा
 * @ctx1_iv_off: IV offset in CONTEXT1 रेजिस्टर
 */
व्योम cnstr_shdsc_skcipher_decap(u32 * स्थिर desc, काष्ठा alginfo *cdata,
				अचिन्हित पूर्णांक ivsize, स्थिर bool is_rfc3686,
				स्थिर u32 ctx1_iv_off)
अणु
	u32 *key_jump_cmd;
	bool is_chacha20 = ((cdata->algtype & OP_ALG_ALGSEL_MASK) ==
			    OP_ALG_ALGSEL_CHACHA20);

	init_sh_desc(desc, HDR_SHARE_SERIAL | HDR_SAVECTX);
	/* Skip अगर alपढ़ोy shared */
	key_jump_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
				   JUMP_COND_SHRD);

	/* Load class1 key only */
	append_key_as_imm(desc, cdata->key_virt, cdata->keylen,
			  cdata->keylen, CLASS_1 | KEY_DEST_CLASS_REG);

	/* Load nonce पूर्णांकo CONTEXT1 reg */
	अगर (is_rfc3686) अणु
		स्थिर u8 *nonce = cdata->key_virt + cdata->keylen;

		append_load_as_imm(desc, nonce, CTR_RFC3686_NONCE_SIZE,
				   LDST_CLASS_IND_CCB |
				   LDST_SRCDST_BYTE_OUTFIFO | LDST_IMM);
		append_move(desc, MOVE_WAITCOMP | MOVE_SRC_OUTFIFO |
			    MOVE_DEST_CLASS1CTX | (16 << MOVE_OFFSET_SHIFT) |
			    (CTR_RFC3686_NONCE_SIZE << MOVE_LEN_SHIFT));
	पूर्ण

	set_jump_tgt_here(desc, key_jump_cmd);

	/* Load IV, अगर there is one */
	अगर (ivsize)
		append_seq_load(desc, ivsize, LDST_SRCDST_BYTE_CONTEXT |
				LDST_CLASS_1_CCB | (ctx1_iv_off <<
				LDST_OFFSET_SHIFT));

	/* Load counter पूर्णांकo CONTEXT1 reg */
	अगर (is_rfc3686)
		append_load_imm_be32(desc, 1, LDST_IMM | LDST_CLASS_1_CCB |
				     LDST_SRCDST_BYTE_CONTEXT |
				     ((ctx1_iv_off + CTR_RFC3686_IV_SIZE) <<
				      LDST_OFFSET_SHIFT));

	/* Choose operation */
	अगर (ctx1_iv_off)
		append_operation(desc, cdata->algtype | OP_ALG_AS_INIT |
				 OP_ALG_DECRYPT);
	अन्यथा
		append_dec_op1(desc, cdata->algtype);

	/* Perक्रमm operation */
	skcipher_append_src_dst(desc);

	/* Store IV */
	अगर (!is_chacha20 && ivsize)
		append_seq_store(desc, ivsize, LDST_SRCDST_BYTE_CONTEXT |
				 LDST_CLASS_1_CCB | (ctx1_iv_off <<
				 LDST_OFFSET_SHIFT));

	prपूर्णांक_hex_dump_debug("skcipher dec shdesc@" __stringअगरy(__LINE__)": ",
			     DUMP_PREFIX_ADDRESS, 16, 4, desc, desc_bytes(desc),
			     1);
पूर्ण
EXPORT_SYMBOL(cnstr_shdsc_skcipher_decap);

/**
 * cnstr_shdsc_xts_skcipher_encap - xts skcipher encapsulation shared descriptor
 * @desc: poपूर्णांकer to buffer used क्रम descriptor स्थिरruction
 * @cdata: poपूर्णांकer to block cipher transक्रमm definitions
 *         Valid algorithm values - OP_ALG_ALGSEL_AES ANDed with OP_ALG_AAI_XTS.
 */
व्योम cnstr_shdsc_xts_skcipher_encap(u32 * स्थिर desc, काष्ठा alginfo *cdata)
अणु
	/*
	 * Set sector size to a big value, practically disabling
	 * sector size segmentation in xts implementation. We cannot
	 * take full advantage of this HW feature with existing
	 * crypto API / dm-crypt SW architecture.
	 */
	__be64 sector_size = cpu_to_be64(BIT(15));
	u32 *key_jump_cmd;

	init_sh_desc(desc, HDR_SHARE_SERIAL | HDR_SAVECTX);
	/* Skip अगर alपढ़ोy shared */
	key_jump_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
				   JUMP_COND_SHRD);

	/* Load class1 keys only */
	append_key_as_imm(desc, cdata->key_virt, cdata->keylen,
			  cdata->keylen, CLASS_1 | KEY_DEST_CLASS_REG);

	/* Load sector size with index 40 bytes (0x28) */
	append_load_as_imm(desc, (व्योम *)&sector_size, 8, LDST_CLASS_1_CCB |
			   LDST_SRCDST_BYTE_CONTEXT |
			   (0x28 << LDST_OFFSET_SHIFT));

	set_jump_tgt_here(desc, key_jump_cmd);

	/*
	 * create sequence क्रम loading the sector index / 16B tweak value
	 * Lower 8B of IV - sector index / tweak lower half
	 * Upper 8B of IV - upper half of 16B tweak
	 */
	append_seq_load(desc, 8, LDST_SRCDST_BYTE_CONTEXT | LDST_CLASS_1_CCB |
			(0x20 << LDST_OFFSET_SHIFT));
	append_seq_load(desc, 8, LDST_SRCDST_BYTE_CONTEXT | LDST_CLASS_1_CCB |
			(0x30 << LDST_OFFSET_SHIFT));

	/* Load operation */
	append_operation(desc, cdata->algtype | OP_ALG_AS_INITFINAL |
			 OP_ALG_ENCRYPT);

	/* Perक्रमm operation */
	skcipher_append_src_dst(desc);

	/* Store lower 8B and upper 8B of IV */
	append_seq_store(desc, 8, LDST_SRCDST_BYTE_CONTEXT | LDST_CLASS_1_CCB |
			 (0x20 << LDST_OFFSET_SHIFT));
	append_seq_store(desc, 8, LDST_SRCDST_BYTE_CONTEXT | LDST_CLASS_1_CCB |
			 (0x30 << LDST_OFFSET_SHIFT));

	prपूर्णांक_hex_dump_debug("xts skcipher enc shdesc@" __stringअगरy(__LINE__)
			     ": ", DUMP_PREFIX_ADDRESS, 16, 4,
			     desc, desc_bytes(desc), 1);
पूर्ण
EXPORT_SYMBOL(cnstr_shdsc_xts_skcipher_encap);

/**
 * cnstr_shdsc_xts_skcipher_decap - xts skcipher decapsulation shared descriptor
 * @desc: poपूर्णांकer to buffer used क्रम descriptor स्थिरruction
 * @cdata: poपूर्णांकer to block cipher transक्रमm definitions
 *         Valid algorithm values - OP_ALG_ALGSEL_AES ANDed with OP_ALG_AAI_XTS.
 */
व्योम cnstr_shdsc_xts_skcipher_decap(u32 * स्थिर desc, काष्ठा alginfo *cdata)
अणु
	/*
	 * Set sector size to a big value, practically disabling
	 * sector size segmentation in xts implementation. We cannot
	 * take full advantage of this HW feature with existing
	 * crypto API / dm-crypt SW architecture.
	 */
	__be64 sector_size = cpu_to_be64(BIT(15));
	u32 *key_jump_cmd;

	init_sh_desc(desc, HDR_SHARE_SERIAL | HDR_SAVECTX);
	/* Skip अगर alपढ़ोy shared */
	key_jump_cmd = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
				   JUMP_COND_SHRD);

	/* Load class1 key only */
	append_key_as_imm(desc, cdata->key_virt, cdata->keylen,
			  cdata->keylen, CLASS_1 | KEY_DEST_CLASS_REG);

	/* Load sector size with index 40 bytes (0x28) */
	append_load_as_imm(desc, (व्योम *)&sector_size, 8, LDST_CLASS_1_CCB |
			   LDST_SRCDST_BYTE_CONTEXT |
			   (0x28 << LDST_OFFSET_SHIFT));

	set_jump_tgt_here(desc, key_jump_cmd);

	/*
	 * create sequence क्रम loading the sector index / 16B tweak value
	 * Lower 8B of IV - sector index / tweak lower half
	 * Upper 8B of IV - upper half of 16B tweak
	 */
	append_seq_load(desc, 8, LDST_SRCDST_BYTE_CONTEXT | LDST_CLASS_1_CCB |
			(0x20 << LDST_OFFSET_SHIFT));
	append_seq_load(desc, 8, LDST_SRCDST_BYTE_CONTEXT | LDST_CLASS_1_CCB |
			(0x30 << LDST_OFFSET_SHIFT));
	/* Load operation */
	append_dec_op1(desc, cdata->algtype);

	/* Perक्रमm operation */
	skcipher_append_src_dst(desc);

	/* Store lower 8B and upper 8B of IV */
	append_seq_store(desc, 8, LDST_SRCDST_BYTE_CONTEXT | LDST_CLASS_1_CCB |
			 (0x20 << LDST_OFFSET_SHIFT));
	append_seq_store(desc, 8, LDST_SRCDST_BYTE_CONTEXT | LDST_CLASS_1_CCB |
			 (0x30 << LDST_OFFSET_SHIFT));

	prपूर्णांक_hex_dump_debug("xts skcipher dec shdesc@" __stringअगरy(__LINE__)
			     ": ", DUMP_PREFIX_ADDRESS, 16, 4, desc,
			     desc_bytes(desc), 1);
पूर्ण
EXPORT_SYMBOL(cnstr_shdsc_xts_skcipher_decap);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("FSL CAAM descriptor support");
MODULE_AUTHOR("Freescale Semiconductor - NMG/STC");
