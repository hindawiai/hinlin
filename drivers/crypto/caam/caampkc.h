<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * caam - Freescale FSL CAAM support क्रम Public Key Cryptography descriptors
 *
 * Copyright 2016 Freescale Semiconductor, Inc.
 *
 * There is no Shared Descriptor क्रम PKC so that the Job Descriptor must carry
 * all the desired key parameters, input and output poपूर्णांकers.
 */

#अगर_अघोषित _PKC_DESC_H_
#घोषणा _PKC_DESC_H_
#समावेश "compat.h"
#समावेश "pdb.h"
#समावेश <crypto/engine.h>

/**
 * caam_priv_key_क्रमm - CAAM RSA निजी key representation
 * CAAM RSA निजी key may have either of three क्रमms.
 *
 * 1. The first representation consists of the pair (n, d), where the
 *    components have the following meanings:
 *        n      the RSA modulus
 *        d      the RSA निजी exponent
 *
 * 2. The second representation consists of the triplet (p, q, d), where the
 *    components have the following meanings:
 *        p      the first prime factor of the RSA modulus n
 *        q      the second prime factor of the RSA modulus n
 *        d      the RSA निजी exponent
 *
 * 3. The third representation consists of the quपूर्णांकuple (p, q, dP, dQ, qInv),
 *    where the components have the following meanings:
 *        p      the first prime factor of the RSA modulus n
 *        q      the second prime factor of the RSA modulus n
 *        dP     the first factors's CRT exponent
 *        dQ     the second factors's CRT exponent
 *        qInv   the (first) CRT coefficient
 *
 * The benefit of using the third or the second key क्रमm is lower computational
 * cost क्रम the decryption and signature operations.
 */
क्रमागत caam_priv_key_क्रमm अणु
	FORM1,
	FORM2,
	FORM3
पूर्ण;

/**
 * caam_rsa_key - CAAM RSA key काष्ठाure. Keys are allocated in DMA zone.
 * @n           : RSA modulus raw byte stream
 * @e           : RSA खुला exponent raw byte stream
 * @d           : RSA निजी exponent raw byte stream
 * @p           : RSA prime factor p of RSA modulus n
 * @q           : RSA prime factor q of RSA modulus n
 * @dp          : RSA CRT exponent of p
 * @dp          : RSA CRT exponent of q
 * @qinv        : RSA CRT coefficient
 * @पंचांगp1        : CAAM uses this temporary buffer as पूर्णांकernal state buffer.
 *                It is assumed to be as दीर्घ as p.
 * @पंचांगp2        : CAAM uses this temporary buffer as पूर्णांकernal state buffer.
 *                It is assumed to be as दीर्घ as q.
 * @n_sz        : length in bytes of RSA modulus n
 * @e_sz        : length in bytes of RSA खुला exponent
 * @d_sz        : length in bytes of RSA निजी exponent
 * @p_sz        : length in bytes of RSA prime factor p of RSA modulus n
 * @q_sz        : length in bytes of RSA prime factor q of RSA modulus n
 * @priv_क्रमm   : CAAM RSA निजी key representation
 */
काष्ठा caam_rsa_key अणु
	u8 *n;
	u8 *e;
	u8 *d;
	u8 *p;
	u8 *q;
	u8 *dp;
	u8 *dq;
	u8 *qinv;
	u8 *पंचांगp1;
	u8 *पंचांगp2;
	माप_प्रकार n_sz;
	माप_प्रकार e_sz;
	माप_प्रकार d_sz;
	माप_प्रकार p_sz;
	माप_प्रकार q_sz;
	क्रमागत caam_priv_key_क्रमm priv_क्रमm;
पूर्ण;

/**
 * caam_rsa_ctx - per session context.
 * @enginectx   : crypto engine context
 * @key         : RSA key in DMA zone
 * @dev         : device काष्ठाure
 * @padding_dma : dma address of padding, क्रम adding it to the input
 */
काष्ठा caam_rsa_ctx अणु
	काष्ठा crypto_engine_ctx enginectx;
	काष्ठा caam_rsa_key key;
	काष्ठा device *dev;
	dma_addr_t padding_dma;

पूर्ण;

/**
 * caam_rsa_req_ctx - per request context.
 * @src           : input scatterlist (stripped of leading zeros)
 * @fixup_src     : input scatterlist (that might be stripped of leading zeros)
 * @fixup_src_len : length of the fixup_src input scatterlist
 * @edesc         : s/w-extended rsa descriptor
 * @akcipher_op_करोne : callback used when operation is करोne
 */
काष्ठा caam_rsa_req_ctx अणु
	काष्ठा scatterlist src[2];
	काष्ठा scatterlist *fixup_src;
	अचिन्हित पूर्णांक fixup_src_len;
	काष्ठा rsa_edesc *edesc;
	व्योम (*akcipher_op_करोne)(काष्ठा device *jrdev, u32 *desc, u32 err,
				 व्योम *context);
पूर्ण;

/**
 * rsa_edesc - s/w-extended rsa descriptor
 * @src_nents     : number of segments in input s/w scatterlist
 * @dst_nents     : number of segments in output s/w scatterlist
 * @mapped_src_nents: number of segments in input h/w link table
 * @mapped_dst_nents: number of segments in output h/w link table
 * @sec4_sg_bytes : length of h/w link table
 * @bklog         : stored to determine अगर the request needs backlog
 * @sec4_sg_dma   : dma address of h/w link table
 * @sec4_sg       : poपूर्णांकer to h/w link table
 * @pdb           : specअगरic RSA Protocol Data Block (PDB)
 * @hw_desc       : descriptor followed by link tables अगर any
 */
काष्ठा rsa_edesc अणु
	पूर्णांक src_nents;
	पूर्णांक dst_nents;
	पूर्णांक mapped_src_nents;
	पूर्णांक mapped_dst_nents;
	पूर्णांक sec4_sg_bytes;
	bool bklog;
	dma_addr_t sec4_sg_dma;
	काष्ठा sec4_sg_entry *sec4_sg;
	जोड़ अणु
		काष्ठा rsa_pub_pdb pub;
		काष्ठा rsa_priv_f1_pdb priv_f1;
		काष्ठा rsa_priv_f2_pdb priv_f2;
		काष्ठा rsa_priv_f3_pdb priv_f3;
	पूर्ण pdb;
	u32 hw_desc[];
पूर्ण;

/* Descriptor स्थिरruction primitives. */
व्योम init_rsa_pub_desc(u32 *desc, काष्ठा rsa_pub_pdb *pdb);
व्योम init_rsa_priv_f1_desc(u32 *desc, काष्ठा rsa_priv_f1_pdb *pdb);
व्योम init_rsa_priv_f2_desc(u32 *desc, काष्ठा rsa_priv_f2_pdb *pdb);
व्योम init_rsa_priv_f3_desc(u32 *desc, काष्ठा rsa_priv_f3_pdb *pdb);

#पूर्ण_अगर
