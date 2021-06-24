<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/*
 * Shared descriptors क्रम ahash algorithms
 *
 * Copyright 2017 NXP
 */

#अगर_अघोषित _CAAMHASH_DESC_H_
#घोषणा _CAAMHASH_DESC_H_

/* length of descriptors text */
#घोषणा DESC_AHASH_BASE			(3 * CAAM_CMD_SZ)
#घोषणा DESC_AHASH_UPDATE_LEN		(6 * CAAM_CMD_SZ)
#घोषणा DESC_AHASH_UPDATE_FIRST_LEN	(DESC_AHASH_BASE + 4 * CAAM_CMD_SZ)
#घोषणा DESC_AHASH_FINAL_LEN		(DESC_AHASH_BASE + 5 * CAAM_CMD_SZ)
#घोषणा DESC_AHASH_DIGEST_LEN		(DESC_AHASH_BASE + 4 * CAAM_CMD_SZ)

अटल अंतरभूत bool is_xcbc_aes(u32 algtype)
अणु
	वापस (algtype & (OP_ALG_ALGSEL_MASK | OP_ALG_AAI_MASK)) ==
	       (OP_ALG_ALGSEL_AES | OP_ALG_AAI_XCBC_MAC);
पूर्ण

व्योम cnstr_shdsc_ahash(u32 * स्थिर desc, काष्ठा alginfo *adata, u32 state,
		       पूर्णांक digestsize, पूर्णांक ctx_len, bool import_ctx, पूर्णांक era);

व्योम cnstr_shdsc_sk_hash(u32 * स्थिर desc, काष्ठा alginfo *adata, u32 state,
			 पूर्णांक digestsize, पूर्णांक ctx_len);
#पूर्ण_अगर /* _CAAMHASH_DESC_H_ */
