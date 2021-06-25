<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * Shared descriptors क्रम ahash algorithms
 *
 * Copyright 2017-2019 NXP
 */

#समावेश "compat.h"
#समावेश "desc_constr.h"
#समावेश "caamhash_desc.h"

/**
 * cnstr_shdsc_ahash - ahash shared descriptor
 * @desc: poपूर्णांकer to buffer used क्रम descriptor स्थिरruction
 * @adata: poपूर्णांकer to authentication transक्रमm definitions.
 *         A split key is required क्रम SEC Era < 6; the size of the split key
 *         is specअगरied in this हाल.
 *         Valid algorithm values - one of OP_ALG_ALGSEL_अणुMD5, SHA1, SHA224,
 *         SHA256, SHA384, SHA512पूर्ण.
 * @state: algorithm state OP_ALG_AS_अणुINIT, FINALIZE, INITFINALIZE, UPDATEपूर्ण
 * @digestsize: algorithm's digest size
 * @ctx_len: size of Context Register
 * @import_ctx: true अगर previous Context Register needs to be restored
 *              must be true क्रम ahash update and final
 *              must be false क्रम क्रम ahash first and digest
 * @era: SEC Era
 */
व्योम cnstr_shdsc_ahash(u32 * स्थिर desc, काष्ठा alginfo *adata, u32 state,
		       पूर्णांक digestsize, पूर्णांक ctx_len, bool import_ctx, पूर्णांक era)
अणु
	u32 op = adata->algtype;

	init_sh_desc(desc, HDR_SHARE_SERIAL);

	/* Append key अगर it has been set; ahash update excluded */
	अगर (state != OP_ALG_AS_UPDATE && adata->keylen) अणु
		u32 *skip_key_load;

		/* Skip key loading अगर alपढ़ोy shared */
		skip_key_load = append_jump(desc, JUMP_JSL | JUMP_TEST_ALL |
					    JUMP_COND_SHRD);

		अगर (era < 6)
			append_key_as_imm(desc, adata->key_virt,
					  adata->keylen_pad,
					  adata->keylen, CLASS_2 |
					  KEY_DEST_MDHA_SPLIT | KEY_ENC);
		अन्यथा
			append_proto_dkp(desc, adata);

		set_jump_tgt_here(desc, skip_key_load);

		op |= OP_ALG_AAI_HMAC_PRECOMP;
	पूर्ण

	/* If needed, import context from software */
	अगर (import_ctx)
		append_seq_load(desc, ctx_len, LDST_CLASS_2_CCB |
				LDST_SRCDST_BYTE_CONTEXT);

	/* Class 2 operation */
	append_operation(desc, op | state | OP_ALG_ENCRYPT);

	/*
	 * Load from buf and/or src and ग_लिखो to req->result or state->context
	 * Calculate reमुख्यing bytes to पढ़ो
	 */
	append_math_add(desc, VARSEQINLEN, SEQINLEN, REG0, CAAM_CMD_SZ);
	/* Read reमुख्यing bytes */
	append_seq_fअगरo_load(desc, 0, FIFOLD_CLASS_CLASS2 | FIFOLD_TYPE_LAST2 |
			     FIFOLD_TYPE_MSG | KEY_VLF);
	/* Store class2 context bytes */
	append_seq_store(desc, digestsize, LDST_CLASS_2_CCB |
			 LDST_SRCDST_BYTE_CONTEXT);
पूर्ण
EXPORT_SYMBOL(cnstr_shdsc_ahash);

/**
 * cnstr_shdsc_sk_hash - shared descriptor क्रम symmetric key cipher-based
 *                       hash algorithms
 * @desc: poपूर्णांकer to buffer used क्रम descriptor स्थिरruction
 * @adata: poपूर्णांकer to authentication transक्रमm definitions.
 * @state: algorithm state OP_ALG_AS_अणुINIT, FINALIZE, INITFINALIZE, UPDATEपूर्ण
 * @digestsize: algorithm's digest size
 * @ctx_len: size of Context Register
 */
व्योम cnstr_shdsc_sk_hash(u32 * स्थिर desc, काष्ठा alginfo *adata, u32 state,
			 पूर्णांक digestsize, पूर्णांक ctx_len)
अणु
	u32 *skip_key_load;

	init_sh_desc(desc, HDR_SHARE_SERIAL | HDR_SAVECTX);

	/* Skip loading of key, context अगर alपढ़ोy shared */
	skip_key_load = append_jump(desc, JUMP_TEST_ALL | JUMP_COND_SHRD);

	अगर (state == OP_ALG_AS_INIT || state == OP_ALG_AS_INITFINAL) अणु
		append_key_as_imm(desc, adata->key_virt, adata->keylen,
				  adata->keylen, CLASS_1 | KEY_DEST_CLASS_REG);
	पूर्ण अन्यथा अणु /* UPDATE, FINALIZE */
		अगर (is_xcbc_aes(adata->algtype))
			/* Load K1 */
			append_key(desc, adata->key_dma, adata->keylen,
				   CLASS_1 | KEY_DEST_CLASS_REG | KEY_ENC);
		अन्यथा /* CMAC */
			append_key_as_imm(desc, adata->key_virt, adata->keylen,
					  adata->keylen, CLASS_1 |
					  KEY_DEST_CLASS_REG);
		/* Restore context */
		append_seq_load(desc, ctx_len, LDST_CLASS_1_CCB |
				LDST_SRCDST_BYTE_CONTEXT);
	पूर्ण

	set_jump_tgt_here(desc, skip_key_load);

	/* Class 1 operation */
	append_operation(desc, adata->algtype | state | OP_ALG_ENCRYPT);

	/*
	 * Load from buf and/or src and ग_लिखो to req->result or state->context
	 * Calculate reमुख्यing bytes to पढ़ो
	 */
	append_math_add(desc, VARSEQINLEN, SEQINLEN, REG0, CAAM_CMD_SZ);

	/* Read reमुख्यing bytes */
	append_seq_fअगरo_load(desc, 0, FIFOLD_CLASS_CLASS1 | FIFOLD_TYPE_LAST1 |
			     FIFOLD_TYPE_MSG | FIFOLDST_VLF);

	/*
	 * Save context:
	 * - xcbc: partial hash, keys K2 and K3
	 * - cmac: partial hash, स्थिरant L = E(K,0)
	 */
	append_seq_store(desc, digestsize, LDST_CLASS_1_CCB |
			 LDST_SRCDST_BYTE_CONTEXT);
	अगर (is_xcbc_aes(adata->algtype) && state == OP_ALG_AS_INIT)
		/* Save K1 */
		append_fअगरo_store(desc, adata->key_dma, adata->keylen,
				  LDST_CLASS_1_CCB | FIFOST_TYPE_KEY_KEK);
पूर्ण
EXPORT_SYMBOL(cnstr_shdsc_sk_hash);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("FSL CAAM ahash descriptors support");
MODULE_AUTHOR("NXP Semiconductors");
