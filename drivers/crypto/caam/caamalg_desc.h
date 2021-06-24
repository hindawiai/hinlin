<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Shared descriptors क्रम aead, skcipher algorithms
 *
 * Copyright 2016 NXP
 */

#अगर_अघोषित _CAAMALG_DESC_H_
#घोषणा _CAAMALG_DESC_H_

/* length of descriptors text */
#घोषणा DESC_AEAD_BASE			(4 * CAAM_CMD_SZ)
#घोषणा DESC_AEAD_ENC_LEN		(DESC_AEAD_BASE + 11 * CAAM_CMD_SZ)
#घोषणा DESC_AEAD_DEC_LEN		(DESC_AEAD_BASE + 15 * CAAM_CMD_SZ)
#घोषणा DESC_AEAD_GIVENC_LEN		(DESC_AEAD_ENC_LEN + 8 * CAAM_CMD_SZ)
#घोषणा DESC_QI_AEAD_ENC_LEN		(DESC_AEAD_ENC_LEN + 3 * CAAM_CMD_SZ)
#घोषणा DESC_QI_AEAD_DEC_LEN		(DESC_AEAD_DEC_LEN + 3 * CAAM_CMD_SZ)
#घोषणा DESC_QI_AEAD_GIVENC_LEN		(DESC_AEAD_GIVENC_LEN + 3 * CAAM_CMD_SZ)

/* Note: Nonce is counted in cdata.keylen */
#घोषणा DESC_AEAD_CTR_RFC3686_LEN	(4 * CAAM_CMD_SZ)

#घोषणा DESC_AEAD_शून्य_BASE		(3 * CAAM_CMD_SZ)
#घोषणा DESC_AEAD_शून्य_ENC_LEN		(DESC_AEAD_शून्य_BASE + 11 * CAAM_CMD_SZ)
#घोषणा DESC_AEAD_शून्य_DEC_LEN		(DESC_AEAD_शून्य_BASE + 13 * CAAM_CMD_SZ)

#घोषणा DESC_GCM_BASE			(3 * CAAM_CMD_SZ)
#घोषणा DESC_GCM_ENC_LEN		(DESC_GCM_BASE + 16 * CAAM_CMD_SZ)
#घोषणा DESC_GCM_DEC_LEN		(DESC_GCM_BASE + 12 * CAAM_CMD_SZ)
#घोषणा DESC_QI_GCM_ENC_LEN		(DESC_GCM_ENC_LEN + 6 * CAAM_CMD_SZ)
#घोषणा DESC_QI_GCM_DEC_LEN		(DESC_GCM_DEC_LEN + 3 * CAAM_CMD_SZ)

#घोषणा DESC_RFC4106_BASE		(3 * CAAM_CMD_SZ)
#घोषणा DESC_RFC4106_ENC_LEN		(DESC_RFC4106_BASE + 16 * CAAM_CMD_SZ)
#घोषणा DESC_RFC4106_DEC_LEN		(DESC_RFC4106_BASE + 13 * CAAM_CMD_SZ)
#घोषणा DESC_QI_RFC4106_ENC_LEN		(DESC_RFC4106_ENC_LEN + 5 * CAAM_CMD_SZ)
#घोषणा DESC_QI_RFC4106_DEC_LEN		(DESC_RFC4106_DEC_LEN + 5 * CAAM_CMD_SZ)

#घोषणा DESC_RFC4543_BASE		(3 * CAAM_CMD_SZ)
#घोषणा DESC_RFC4543_ENC_LEN		(DESC_RFC4543_BASE + 11 * CAAM_CMD_SZ)
#घोषणा DESC_RFC4543_DEC_LEN		(DESC_RFC4543_BASE + 12 * CAAM_CMD_SZ)
#घोषणा DESC_QI_RFC4543_ENC_LEN		(DESC_RFC4543_ENC_LEN + 4 * CAAM_CMD_SZ)
#घोषणा DESC_QI_RFC4543_DEC_LEN		(DESC_RFC4543_DEC_LEN + 4 * CAAM_CMD_SZ)

#घोषणा DESC_SKCIPHER_BASE		(3 * CAAM_CMD_SZ)
#घोषणा DESC_SKCIPHER_ENC_LEN		(DESC_SKCIPHER_BASE + \
					 21 * CAAM_CMD_SZ)
#घोषणा DESC_SKCIPHER_DEC_LEN		(DESC_SKCIPHER_BASE + \
					 16 * CAAM_CMD_SZ)

व्योम cnstr_shdsc_aead_null_encap(u32 * स्थिर desc, काष्ठा alginfo *adata,
				 अचिन्हित पूर्णांक icvsize, पूर्णांक era);

व्योम cnstr_shdsc_aead_null_decap(u32 * स्थिर desc, काष्ठा alginfo *adata,
				 अचिन्हित पूर्णांक icvsize, पूर्णांक era);

व्योम cnstr_shdsc_aead_encap(u32 * स्थिर desc, काष्ठा alginfo *cdata,
			    काष्ठा alginfo *adata, अचिन्हित पूर्णांक ivsize,
			    अचिन्हित पूर्णांक icvsize, स्थिर bool is_rfc3686,
			    u32 *nonce, स्थिर u32 ctx1_iv_off,
			    स्थिर bool is_qi, पूर्णांक era);

व्योम cnstr_shdsc_aead_decap(u32 * स्थिर desc, काष्ठा alginfo *cdata,
			    काष्ठा alginfo *adata, अचिन्हित पूर्णांक ivsize,
			    अचिन्हित पूर्णांक icvsize, स्थिर bool geniv,
			    स्थिर bool is_rfc3686, u32 *nonce,
			    स्थिर u32 ctx1_iv_off, स्थिर bool is_qi, पूर्णांक era);

व्योम cnstr_shdsc_aead_givencap(u32 * स्थिर desc, काष्ठा alginfo *cdata,
			       काष्ठा alginfo *adata, अचिन्हित पूर्णांक ivsize,
			       अचिन्हित पूर्णांक icvsize, स्थिर bool is_rfc3686,
			       u32 *nonce, स्थिर u32 ctx1_iv_off,
			       स्थिर bool is_qi, पूर्णांक era);

व्योम cnstr_shdsc_gcm_encap(u32 * स्थिर desc, काष्ठा alginfo *cdata,
			   अचिन्हित पूर्णांक ivsize, अचिन्हित पूर्णांक icvsize,
			   स्थिर bool is_qi);

व्योम cnstr_shdsc_gcm_decap(u32 * स्थिर desc, काष्ठा alginfo *cdata,
			   अचिन्हित पूर्णांक ivsize, अचिन्हित पूर्णांक icvsize,
			   स्थिर bool is_qi);

व्योम cnstr_shdsc_rfc4106_encap(u32 * स्थिर desc, काष्ठा alginfo *cdata,
			       अचिन्हित पूर्णांक ivsize, अचिन्हित पूर्णांक icvsize,
			       स्थिर bool is_qi);

व्योम cnstr_shdsc_rfc4106_decap(u32 * स्थिर desc, काष्ठा alginfo *cdata,
			       अचिन्हित पूर्णांक ivsize, अचिन्हित पूर्णांक icvsize,
			       स्थिर bool is_qi);

व्योम cnstr_shdsc_rfc4543_encap(u32 * स्थिर desc, काष्ठा alginfo *cdata,
			       अचिन्हित पूर्णांक ivsize, अचिन्हित पूर्णांक icvsize,
			       स्थिर bool is_qi);

व्योम cnstr_shdsc_rfc4543_decap(u32 * स्थिर desc, काष्ठा alginfo *cdata,
			       अचिन्हित पूर्णांक ivsize, अचिन्हित पूर्णांक icvsize,
			       स्थिर bool is_qi);

व्योम cnstr_shdsc_chachapoly(u32 * स्थिर desc, काष्ठा alginfo *cdata,
			    काष्ठा alginfo *adata, अचिन्हित पूर्णांक ivsize,
			    अचिन्हित पूर्णांक icvsize, स्थिर bool encap,
			    स्थिर bool is_qi);

व्योम cnstr_shdsc_skcipher_encap(u32 * स्थिर desc, काष्ठा alginfo *cdata,
				अचिन्हित पूर्णांक ivsize, स्थिर bool is_rfc3686,
				स्थिर u32 ctx1_iv_off);

व्योम cnstr_shdsc_skcipher_decap(u32 * स्थिर desc, काष्ठा alginfo *cdata,
				अचिन्हित पूर्णांक ivsize, स्थिर bool is_rfc3686,
				स्थिर u32 ctx1_iv_off);

व्योम cnstr_shdsc_xts_skcipher_encap(u32 * स्थिर desc, काष्ठा alginfo *cdata);

व्योम cnstr_shdsc_xts_skcipher_decap(u32 * स्थिर desc, काष्ठा alginfo *cdata);

#पूर्ण_अगर /* _CAAMALG_DESC_H_ */
