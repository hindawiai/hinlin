<शैली गुरु>
/*
 * This file is part of the Chelsio T6 Crypto driver क्रम Linux.
 *
 * Copyright (c) 2003-2016 Chelsio Communications, Inc. All rights reserved.
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
 *
 * Written and Maपूर्णांकained by:
 *	Manoj Malviya (manojmalviya@chelsio.com)
 *	Atul Gupta (atul.gupta@chelsio.com)
 *	Jitendra Lulla (jlulla@chelsio.com)
 *	Yeshaswi M R Gowda (yeshaswi@chelsio.com)
 *	Harsh Jain (harsh@chelsio.com)
 */

#घोषणा pr_fmt(fmt) "chcr:" fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/crypto.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/scatterlist.h>

#समावेश <crypto/aes.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/gcm.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/authenc.h>
#समावेश <crypto/ctr.h>
#समावेश <crypto/gf128mul.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/null.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/aead.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/पूर्णांकernal/hash.h>

#समावेश "t4fw_api.h"
#समावेश "t4_msg.h"
#समावेश "chcr_core.h"
#समावेश "chcr_algo.h"
#समावेश "chcr_crypto.h"

#घोषणा IV AES_BLOCK_SIZE

अटल अचिन्हित पूर्णांक sgl_ent_len[] = अणु
	0, 0, 16, 24, 40, 48, 64, 72, 88,
	96, 112, 120, 136, 144, 160, 168, 184,
	192, 208, 216, 232, 240, 256, 264, 280,
	288, 304, 312, 328, 336, 352, 360, 376
पूर्ण;

अटल अचिन्हित पूर्णांक dsgl_ent_len[] = अणु
	0, 32, 32, 48, 48, 64, 64, 80, 80,
	112, 112, 128, 128, 144, 144, 160, 160,
	192, 192, 208, 208, 224, 224, 240, 240,
	272, 272, 288, 288, 304, 304, 320, 320
पूर्ण;

अटल u32 round_स्थिरant[11] = अणु
	0x01000000, 0x02000000, 0x04000000, 0x08000000,
	0x10000000, 0x20000000, 0x40000000, 0x80000000,
	0x1B000000, 0x36000000, 0x6C000000
पूर्ण;

अटल पूर्णांक chcr_handle_cipher_resp(काष्ठा skcipher_request *req,
				   अचिन्हित अक्षर *input, पूर्णांक err);

अटल अंतरभूत  काष्ठा chcr_aead_ctx *AEAD_CTX(काष्ठा chcr_context *ctx)
अणु
	वापस ctx->crypto_ctx->aeadctx;
पूर्ण

अटल अंतरभूत काष्ठा ablk_ctx *ABLK_CTX(काष्ठा chcr_context *ctx)
अणु
	वापस ctx->crypto_ctx->ablkctx;
पूर्ण

अटल अंतरभूत काष्ठा hmac_ctx *HMAC_CTX(काष्ठा chcr_context *ctx)
अणु
	वापस ctx->crypto_ctx->hmacctx;
पूर्ण

अटल अंतरभूत काष्ठा chcr_gcm_ctx *GCM_CTX(काष्ठा chcr_aead_ctx *gctx)
अणु
	वापस gctx->ctx->gcm;
पूर्ण

अटल अंतरभूत काष्ठा chcr_authenc_ctx *AUTHENC_CTX(काष्ठा chcr_aead_ctx *gctx)
अणु
	वापस gctx->ctx->authenc;
पूर्ण

अटल अंतरभूत काष्ठा uld_ctx *ULD_CTX(काष्ठा chcr_context *ctx)
अणु
	वापस container_of(ctx->dev, काष्ठा uld_ctx, dev);
पूर्ण

अटल अंतरभूत व्योम chcr_init_hctx_per_wr(काष्ठा chcr_ahash_req_ctx *reqctx)
अणु
	स_रखो(&reqctx->hctx_wr, 0, माप(काष्ठा chcr_hctx_per_wr));
पूर्ण

अटल पूर्णांक sg_nents_xlen(काष्ठा scatterlist *sg, अचिन्हित पूर्णांक reqlen,
			 अचिन्हित पूर्णांक entlen,
			 अचिन्हित पूर्णांक skip)
अणु
	पूर्णांक nents = 0;
	अचिन्हित पूर्णांक less;
	अचिन्हित पूर्णांक skip_len = 0;

	जबतक (sg && skip) अणु
		अगर (sg_dma_len(sg) <= skip) अणु
			skip -= sg_dma_len(sg);
			skip_len = 0;
			sg = sg_next(sg);
		पूर्ण अन्यथा अणु
			skip_len = skip;
			skip = 0;
		पूर्ण
	पूर्ण

	जबतक (sg && reqlen) अणु
		less = min(reqlen, sg_dma_len(sg) - skip_len);
		nents += DIV_ROUND_UP(less, entlen);
		reqlen -= less;
		skip_len = 0;
		sg = sg_next(sg);
	पूर्ण
	वापस nents;
पूर्ण

अटल अंतरभूत पूर्णांक get_aead_subtype(काष्ठा crypto_aead *aead)
अणु
	काष्ठा aead_alg *alg = crypto_aead_alg(aead);
	काष्ठा chcr_alg_ढाँचा *chcr_crypto_alg =
		container_of(alg, काष्ठा chcr_alg_ढाँचा, alg.aead);
	वापस chcr_crypto_alg->type & CRYPTO_ALG_SUB_TYPE_MASK;
पूर्ण

व्योम chcr_verअगरy_tag(काष्ठा aead_request *req, u8 *input, पूर्णांक *err)
अणु
	u8 temp[SHA512_DIGEST_SIZE];
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	पूर्णांक authsize = crypto_aead_authsize(tfm);
	काष्ठा cpl_fw6_pld *fw6_pld;
	पूर्णांक cmp = 0;

	fw6_pld = (काष्ठा cpl_fw6_pld *)input;
	अगर ((get_aead_subtype(tfm) == CRYPTO_ALG_SUB_TYPE_AEAD_RFC4106) ||
	    (get_aead_subtype(tfm) == CRYPTO_ALG_SUB_TYPE_AEAD_GCM)) अणु
		cmp = crypto_memneq(&fw6_pld->data[2], (fw6_pld + 1), authsize);
	पूर्ण अन्यथा अणु

		sg_pcopy_to_buffer(req->src, sg_nents(req->src), temp,
				authsize, req->assoclen +
				req->cryptlen - authsize);
		cmp = crypto_memneq(temp, (fw6_pld + 1), authsize);
	पूर्ण
	अगर (cmp)
		*err = -EBADMSG;
	अन्यथा
		*err = 0;
पूर्ण

अटल पूर्णांक chcr_inc_wrcount(काष्ठा chcr_dev *dev)
अणु
	अगर (dev->state == CHCR_DETACH)
		वापस 1;
	atomic_inc(&dev->inflight);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम chcr_dec_wrcount(काष्ठा chcr_dev *dev)
अणु
	atomic_dec(&dev->inflight);
पूर्ण

अटल अंतरभूत पूर्णांक chcr_handle_aead_resp(काष्ठा aead_request *req,
					 अचिन्हित अक्षर *input,
					 पूर्णांक err)
अणु
	काष्ठा chcr_aead_reqctx *reqctx = aead_request_ctx(req);
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा chcr_dev *dev = a_ctx(tfm)->dev;

	chcr_aead_common_निकास(req);
	अगर (reqctx->verअगरy == VERIFY_SW) अणु
		chcr_verअगरy_tag(req, input, &err);
		reqctx->verअगरy = VERIFY_HW;
	पूर्ण
	chcr_dec_wrcount(dev);
	req->base.complete(&req->base, err);

	वापस err;
पूर्ण

अटल व्योम get_aes_decrypt_key(अचिन्हित अक्षर *dec_key,
				       स्थिर अचिन्हित अक्षर *key,
				       अचिन्हित पूर्णांक keylength)
अणु
	u32 temp;
	u32 w_ring[MAX_NK];
	पूर्णांक i, j, k;
	u8  nr, nk;

	चयन (keylength) अणु
	हाल AES_KEYLENGTH_128BIT:
		nk = KEYLENGTH_4BYTES;
		nr = NUMBER_OF_ROUNDS_10;
		अवरोध;
	हाल AES_KEYLENGTH_192BIT:
		nk = KEYLENGTH_6BYTES;
		nr = NUMBER_OF_ROUNDS_12;
		अवरोध;
	हाल AES_KEYLENGTH_256BIT:
		nk = KEYLENGTH_8BYTES;
		nr = NUMBER_OF_ROUNDS_14;
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	क्रम (i = 0; i < nk; i++)
		w_ring[i] = get_unaligned_be32(&key[i * 4]);

	i = 0;
	temp = w_ring[nk - 1];
	जबतक (i + nk < (nr + 1) * 4) अणु
		अगर (!(i % nk)) अणु
			/* RotWord(temp) */
			temp = (temp << 8) | (temp >> 24);
			temp = aes_ks_subword(temp);
			temp ^= round_स्थिरant[i / nk];
		पूर्ण अन्यथा अगर (nk == 8 && (i % 4 == 0)) अणु
			temp = aes_ks_subword(temp);
		पूर्ण
		w_ring[i % nk] ^= temp;
		temp = w_ring[i % nk];
		i++;
	पूर्ण
	i--;
	क्रम (k = 0, j = i % nk; k < nk; k++) अणु
		put_unaligned_be32(w_ring[j], &dec_key[k * 4]);
		j--;
		अगर (j < 0)
			j += nk;
	पूर्ण
पूर्ण

अटल काष्ठा crypto_shash *chcr_alloc_shash(अचिन्हित पूर्णांक ds)
अणु
	काष्ठा crypto_shash *base_hash = ERR_PTR(-EINVAL);

	चयन (ds) अणु
	हाल SHA1_DIGEST_SIZE:
		base_hash = crypto_alloc_shash("sha1", 0, 0);
		अवरोध;
	हाल SHA224_DIGEST_SIZE:
		base_hash = crypto_alloc_shash("sha224", 0, 0);
		अवरोध;
	हाल SHA256_DIGEST_SIZE:
		base_hash = crypto_alloc_shash("sha256", 0, 0);
		अवरोध;
	हाल SHA384_DIGEST_SIZE:
		base_hash = crypto_alloc_shash("sha384", 0, 0);
		अवरोध;
	हाल SHA512_DIGEST_SIZE:
		base_hash = crypto_alloc_shash("sha512", 0, 0);
		अवरोध;
	पूर्ण

	वापस base_hash;
पूर्ण

अटल पूर्णांक chcr_compute_partial_hash(काष्ठा shash_desc *desc,
				     अक्षर *iopad, अक्षर *result_hash,
				     पूर्णांक digest_size)
अणु
	काष्ठा sha1_state sha1_st;
	काष्ठा sha256_state sha256_st;
	काष्ठा sha512_state sha512_st;
	पूर्णांक error;

	अगर (digest_size == SHA1_DIGEST_SIZE) अणु
		error = crypto_shash_init(desc) ?:
			crypto_shash_update(desc, iopad, SHA1_BLOCK_SIZE) ?:
			crypto_shash_export(desc, (व्योम *)&sha1_st);
		स_नकल(result_hash, sha1_st.state, SHA1_DIGEST_SIZE);
	पूर्ण अन्यथा अगर (digest_size == SHA224_DIGEST_SIZE) अणु
		error = crypto_shash_init(desc) ?:
			crypto_shash_update(desc, iopad, SHA256_BLOCK_SIZE) ?:
			crypto_shash_export(desc, (व्योम *)&sha256_st);
		स_नकल(result_hash, sha256_st.state, SHA256_DIGEST_SIZE);

	पूर्ण अन्यथा अगर (digest_size == SHA256_DIGEST_SIZE) अणु
		error = crypto_shash_init(desc) ?:
			crypto_shash_update(desc, iopad, SHA256_BLOCK_SIZE) ?:
			crypto_shash_export(desc, (व्योम *)&sha256_st);
		स_नकल(result_hash, sha256_st.state, SHA256_DIGEST_SIZE);

	पूर्ण अन्यथा अगर (digest_size == SHA384_DIGEST_SIZE) अणु
		error = crypto_shash_init(desc) ?:
			crypto_shash_update(desc, iopad, SHA512_BLOCK_SIZE) ?:
			crypto_shash_export(desc, (व्योम *)&sha512_st);
		स_नकल(result_hash, sha512_st.state, SHA512_DIGEST_SIZE);

	पूर्ण अन्यथा अगर (digest_size == SHA512_DIGEST_SIZE) अणु
		error = crypto_shash_init(desc) ?:
			crypto_shash_update(desc, iopad, SHA512_BLOCK_SIZE) ?:
			crypto_shash_export(desc, (व्योम *)&sha512_st);
		स_नकल(result_hash, sha512_st.state, SHA512_DIGEST_SIZE);
	पूर्ण अन्यथा अणु
		error = -EINVAL;
		pr_err("Unknown digest size %d\n", digest_size);
	पूर्ण
	वापस error;
पूर्ण

अटल व्योम chcr_change_order(अक्षर *buf, पूर्णांक ds)
अणु
	पूर्णांक i;

	अगर (ds == SHA512_DIGEST_SIZE) अणु
		क्रम (i = 0; i < (ds / माप(u64)); i++)
			*((__be64 *)buf + i) =
				cpu_to_be64(*((u64 *)buf + i));
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < (ds / माप(u32)); i++)
			*((__be32 *)buf + i) =
				cpu_to_be32(*((u32 *)buf + i));
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक is_hmac(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_alg *alg = tfm->__crt_alg;
	काष्ठा chcr_alg_ढाँचा *chcr_crypto_alg =
		container_of(__crypto_ahash_alg(alg), काष्ठा chcr_alg_ढाँचा,
			     alg.hash);
	अगर (chcr_crypto_alg->type == CRYPTO_ALG_TYPE_HMAC)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dsgl_walk_init(काष्ठा dsgl_walk *walk,
				   काष्ठा cpl_rx_phys_dsgl *dsgl)
अणु
	walk->dsgl = dsgl;
	walk->nents = 0;
	walk->to = (काष्ठा phys_sge_pairs *)(dsgl + 1);
पूर्ण

अटल अंतरभूत व्योम dsgl_walk_end(काष्ठा dsgl_walk *walk, अचिन्हित लघु qid,
				 पूर्णांक pci_chan_id)
अणु
	काष्ठा cpl_rx_phys_dsgl *phys_cpl;

	phys_cpl = walk->dsgl;

	phys_cpl->op_to_tid = htonl(CPL_RX_PHYS_DSGL_OPCODE_V(CPL_RX_PHYS_DSGL)
				    | CPL_RX_PHYS_DSGL_ISRDMA_V(0));
	phys_cpl->pcirlxorder_to_noofsgentr =
		htonl(CPL_RX_PHYS_DSGL_PCIRLXORDER_V(0) |
		      CPL_RX_PHYS_DSGL_PCINOSNOOP_V(0) |
		      CPL_RX_PHYS_DSGL_PCITPHNTENB_V(0) |
		      CPL_RX_PHYS_DSGL_PCITPHNT_V(0) |
		      CPL_RX_PHYS_DSGL_DCAID_V(0) |
		      CPL_RX_PHYS_DSGL_NOOFSGENTR_V(walk->nents));
	phys_cpl->rss_hdr_पूर्णांक.opcode = CPL_RX_PHYS_ADDR;
	phys_cpl->rss_hdr_पूर्णांक.qid = htons(qid);
	phys_cpl->rss_hdr_पूर्णांक.hash_val = 0;
	phys_cpl->rss_hdr_पूर्णांक.channel = pci_chan_id;
पूर्ण

अटल अंतरभूत व्योम dsgl_walk_add_page(काष्ठा dsgl_walk *walk,
					माप_प्रकार size,
					dma_addr_t addr)
अणु
	पूर्णांक j;

	अगर (!size)
		वापस;
	j = walk->nents;
	walk->to->len[j % 8] = htons(size);
	walk->to->addr[j % 8] = cpu_to_be64(addr);
	j++;
	अगर ((j % 8) == 0)
		walk->to++;
	walk->nents = j;
पूर्ण

अटल व्योम  dsgl_walk_add_sg(काष्ठा dsgl_walk *walk,
			   काष्ठा scatterlist *sg,
			      अचिन्हित पूर्णांक slen,
			      अचिन्हित पूर्णांक skip)
अणु
	पूर्णांक skip_len = 0;
	अचिन्हित पूर्णांक left_size = slen, len = 0;
	अचिन्हित पूर्णांक j = walk->nents;
	पूर्णांक offset, ent_len;

	अगर (!slen)
		वापस;
	जबतक (sg && skip) अणु
		अगर (sg_dma_len(sg) <= skip) अणु
			skip -= sg_dma_len(sg);
			skip_len = 0;
			sg = sg_next(sg);
		पूर्ण अन्यथा अणु
			skip_len = skip;
			skip = 0;
		पूर्ण
	पूर्ण

	जबतक (left_size && sg) अणु
		len = min_t(u32, left_size, sg_dma_len(sg) - skip_len);
		offset = 0;
		जबतक (len) अणु
			ent_len =  min_t(u32, len, CHCR_DST_SG_SIZE);
			walk->to->len[j % 8] = htons(ent_len);
			walk->to->addr[j % 8] = cpu_to_be64(sg_dma_address(sg) +
						      offset + skip_len);
			offset += ent_len;
			len -= ent_len;
			j++;
			अगर ((j % 8) == 0)
				walk->to++;
		पूर्ण
		walk->last_sg = sg;
		walk->last_sg_len = min_t(u32, left_size, sg_dma_len(sg) -
					  skip_len) + skip_len;
		left_size -= min_t(u32, left_size, sg_dma_len(sg) - skip_len);
		skip_len = 0;
		sg = sg_next(sg);
	पूर्ण
	walk->nents = j;
पूर्ण

अटल अंतरभूत व्योम ulptx_walk_init(काष्ठा ulptx_walk *walk,
				   काष्ठा ulptx_sgl *ulp)
अणु
	walk->sgl = ulp;
	walk->nents = 0;
	walk->pair_idx = 0;
	walk->pair = ulp->sge;
	walk->last_sg = शून्य;
	walk->last_sg_len = 0;
पूर्ण

अटल अंतरभूत व्योम ulptx_walk_end(काष्ठा ulptx_walk *walk)
अणु
	walk->sgl->cmd_nsge = htonl(ULPTX_CMD_V(ULP_TX_SC_DSGL) |
			      ULPTX_NSGE_V(walk->nents));
पूर्ण


अटल अंतरभूत व्योम ulptx_walk_add_page(काष्ठा ulptx_walk *walk,
					माप_प्रकार size,
					dma_addr_t addr)
अणु
	अगर (!size)
		वापस;

	अगर (walk->nents == 0) अणु
		walk->sgl->len0 = cpu_to_be32(size);
		walk->sgl->addr0 = cpu_to_be64(addr);
	पूर्ण अन्यथा अणु
		walk->pair->addr[walk->pair_idx] = cpu_to_be64(addr);
		walk->pair->len[walk->pair_idx] = cpu_to_be32(size);
		walk->pair_idx = !walk->pair_idx;
		अगर (!walk->pair_idx)
			walk->pair++;
	पूर्ण
	walk->nents++;
पूर्ण

अटल व्योम  ulptx_walk_add_sg(काष्ठा ulptx_walk *walk,
					काष्ठा scatterlist *sg,
			       अचिन्हित पूर्णांक len,
			       अचिन्हित पूर्णांक skip)
अणु
	पूर्णांक small;
	पूर्णांक skip_len = 0;
	अचिन्हित पूर्णांक sgmin;

	अगर (!len)
		वापस;
	जबतक (sg && skip) अणु
		अगर (sg_dma_len(sg) <= skip) अणु
			skip -= sg_dma_len(sg);
			skip_len = 0;
			sg = sg_next(sg);
		पूर्ण अन्यथा अणु
			skip_len = skip;
			skip = 0;
		पूर्ण
	पूर्ण
	WARN(!sg, "SG should not be null here\n");
	अगर (sg && (walk->nents == 0)) अणु
		small = min_t(अचिन्हित पूर्णांक, sg_dma_len(sg) - skip_len, len);
		sgmin = min_t(अचिन्हित पूर्णांक, small, CHCR_SRC_SG_SIZE);
		walk->sgl->len0 = cpu_to_be32(sgmin);
		walk->sgl->addr0 = cpu_to_be64(sg_dma_address(sg) + skip_len);
		walk->nents++;
		len -= sgmin;
		walk->last_sg = sg;
		walk->last_sg_len = sgmin + skip_len;
		skip_len += sgmin;
		अगर (sg_dma_len(sg) == skip_len) अणु
			sg = sg_next(sg);
			skip_len = 0;
		पूर्ण
	पूर्ण

	जबतक (sg && len) अणु
		small = min(sg_dma_len(sg) - skip_len, len);
		sgmin = min_t(अचिन्हित पूर्णांक, small, CHCR_SRC_SG_SIZE);
		walk->pair->len[walk->pair_idx] = cpu_to_be32(sgmin);
		walk->pair->addr[walk->pair_idx] =
			cpu_to_be64(sg_dma_address(sg) + skip_len);
		walk->pair_idx = !walk->pair_idx;
		walk->nents++;
		अगर (!walk->pair_idx)
			walk->pair++;
		len -= sgmin;
		skip_len += sgmin;
		walk->last_sg = sg;
		walk->last_sg_len = skip_len;
		अगर (sg_dma_len(sg) == skip_len) अणु
			sg = sg_next(sg);
			skip_len = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक get_cryptoalg_subtype(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(tfm);
	काष्ठा chcr_alg_ढाँचा *chcr_crypto_alg =
		container_of(alg, काष्ठा chcr_alg_ढाँचा, alg.skcipher);

	वापस chcr_crypto_alg->type & CRYPTO_ALG_SUB_TYPE_MASK;
पूर्ण

अटल पूर्णांक cxgb4_is_crypto_q_full(काष्ठा net_device *dev, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा sge_uld_txq_info *txq_info =
		adap->sge.uld_txq_info[CXGB4_TX_CRYPTO];
	काष्ठा sge_uld_txq *txq;
	पूर्णांक ret = 0;

	local_bh_disable();
	txq = &txq_info->uldtxq[idx];
	spin_lock(&txq->sendq.lock);
	अगर (txq->full)
		ret = -1;
	spin_unlock(&txq->sendq.lock);
	local_bh_enable();
	वापस ret;
पूर्ण

अटल पूर्णांक generate_copy_rrkey(काष्ठा ablk_ctx *ablkctx,
			       काष्ठा _key_ctx *key_ctx)
अणु
	अगर (ablkctx->ciph_mode == CHCR_SCMD_CIPHER_MODE_AES_CBC) अणु
		स_नकल(key_ctx->key, ablkctx->rrkey, ablkctx->enckey_len);
	पूर्ण अन्यथा अणु
		स_नकल(key_ctx->key,
		       ablkctx->key + (ablkctx->enckey_len >> 1),
		       ablkctx->enckey_len >> 1);
		स_नकल(key_ctx->key + (ablkctx->enckey_len >> 1),
		       ablkctx->rrkey, ablkctx->enckey_len >> 1);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक chcr_hash_ent_in_wr(काष्ठा scatterlist *src,
			     अचिन्हित पूर्णांक minsg,
			     अचिन्हित पूर्णांक space,
			     अचिन्हित पूर्णांक srcskip)
अणु
	पूर्णांक srclen = 0;
	पूर्णांक srcsg = minsg;
	पूर्णांक soffset = 0, sless;

	अगर (sg_dma_len(src) == srcskip) अणु
		src = sg_next(src);
		srcskip = 0;
	पूर्ण
	जबतक (src && space > (sgl_ent_len[srcsg + 1])) अणु
		sless = min_t(अचिन्हित पूर्णांक, sg_dma_len(src) - soffset -	srcskip,
							CHCR_SRC_SG_SIZE);
		srclen += sless;
		soffset += sless;
		srcsg++;
		अगर (sg_dma_len(src) == (soffset + srcskip)) अणु
			src = sg_next(src);
			soffset = 0;
			srcskip = 0;
		पूर्ण
	पूर्ण
	वापस srclen;
पूर्ण

अटल पूर्णांक chcr_sg_ent_in_wr(काष्ठा scatterlist *src,
			     काष्ठा scatterlist *dst,
			     अचिन्हित पूर्णांक minsg,
			     अचिन्हित पूर्णांक space,
			     अचिन्हित पूर्णांक srcskip,
			     अचिन्हित पूर्णांक dstskip)
अणु
	पूर्णांक srclen = 0, dstlen = 0;
	पूर्णांक srcsg = minsg, dstsg = minsg;
	पूर्णांक offset = 0, soffset = 0, less, sless = 0;

	अगर (sg_dma_len(src) == srcskip) अणु
		src = sg_next(src);
		srcskip = 0;
	पूर्ण
	अगर (sg_dma_len(dst) == dstskip) अणु
		dst = sg_next(dst);
		dstskip = 0;
	पूर्ण

	जबतक (src && dst &&
	       space > (sgl_ent_len[srcsg + 1] + dsgl_ent_len[dstsg])) अणु
		sless = min_t(अचिन्हित पूर्णांक, sg_dma_len(src) - srcskip - soffset,
				CHCR_SRC_SG_SIZE);
		srclen += sless;
		srcsg++;
		offset = 0;
		जबतक (dst && ((dstsg + 1) <= MAX_DSGL_ENT) &&
		       space > (sgl_ent_len[srcsg] + dsgl_ent_len[dstsg + 1])) अणु
			अगर (srclen <= dstlen)
				अवरोध;
			less = min_t(अचिन्हित पूर्णांक, sg_dma_len(dst) - offset -
				     dstskip, CHCR_DST_SG_SIZE);
			dstlen += less;
			offset += less;
			अगर ((offset + dstskip) == sg_dma_len(dst)) अणु
				dst = sg_next(dst);
				offset = 0;
			पूर्ण
			dstsg++;
			dstskip = 0;
		पूर्ण
		soffset += sless;
		अगर ((soffset + srcskip) == sg_dma_len(src)) अणु
			src = sg_next(src);
			srcskip = 0;
			soffset = 0;
		पूर्ण

	पूर्ण
	वापस min(srclen, dstlen);
पूर्ण

अटल पूर्णांक chcr_cipher_fallback(काष्ठा crypto_skcipher *cipher,
				काष्ठा skcipher_request *req,
				u8 *iv,
				अचिन्हित लघु op_type)
अणु
	काष्ठा chcr_skcipher_req_ctx *reqctx = skcipher_request_ctx(req);
	पूर्णांक err;

	skcipher_request_set_tfm(&reqctx->fallback_req, cipher);
	skcipher_request_set_callback(&reqctx->fallback_req, req->base.flags,
				      req->base.complete, req->base.data);
	skcipher_request_set_crypt(&reqctx->fallback_req, req->src, req->dst,
				   req->cryptlen, iv);

	err = op_type ? crypto_skcipher_decrypt(&reqctx->fallback_req) :
			crypto_skcipher_encrypt(&reqctx->fallback_req);

	वापस err;

पूर्ण

अटल अंतरभूत पूर्णांक get_qidxs(काष्ठा crypto_async_request *req,
			    अचिन्हित पूर्णांक *txqidx, अचिन्हित पूर्णांक *rxqidx)
अणु
	काष्ठा crypto_tfm *tfm = req->tfm;
	पूर्णांक ret = 0;

	चयन (tfm->__crt_alg->cra_flags & CRYPTO_ALG_TYPE_MASK) अणु
	हाल CRYPTO_ALG_TYPE_AEAD:
	अणु
		काष्ठा aead_request *aead_req =
			container_of(req, काष्ठा aead_request, base);
		काष्ठा chcr_aead_reqctx *reqctx = aead_request_ctx(aead_req);
		*txqidx = reqctx->txqidx;
		*rxqidx = reqctx->rxqidx;
		अवरोध;
	पूर्ण
	हाल CRYPTO_ALG_TYPE_SKCIPHER:
	अणु
		काष्ठा skcipher_request *sk_req =
			container_of(req, काष्ठा skcipher_request, base);
		काष्ठा chcr_skcipher_req_ctx *reqctx =
			skcipher_request_ctx(sk_req);
		*txqidx = reqctx->txqidx;
		*rxqidx = reqctx->rxqidx;
		अवरोध;
	पूर्ण
	हाल CRYPTO_ALG_TYPE_AHASH:
	अणु
		काष्ठा ahash_request *ahash_req =
			container_of(req, काष्ठा ahash_request, base);
		काष्ठा chcr_ahash_req_ctx *reqctx =
			ahash_request_ctx(ahash_req);
		*txqidx = reqctx->txqidx;
		*rxqidx = reqctx->rxqidx;
		अवरोध;
	पूर्ण
	शेष:
		ret = -EINVAL;
		/* should never get here */
		BUG();
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम create_wreq(काष्ठा chcr_context *ctx,
			       काष्ठा chcr_wr *chcr_req,
			       काष्ठा crypto_async_request *req,
			       अचिन्हित पूर्णांक imm,
			       पूर्णांक hash_sz,
			       अचिन्हित पूर्णांक len16,
			       अचिन्हित पूर्णांक sc_len,
			       अचिन्हित पूर्णांक lcb)
अणु
	काष्ठा uld_ctx *u_ctx = ULD_CTX(ctx);
	अचिन्हित पूर्णांक tx_channel_id, rx_channel_id;
	अचिन्हित पूर्णांक txqidx = 0, rxqidx = 0;
	अचिन्हित पूर्णांक qid, fid, portno;

	get_qidxs(req, &txqidx, &rxqidx);
	qid = u_ctx->lldi.rxq_ids[rxqidx];
	fid = u_ctx->lldi.rxq_ids[0];
	portno = rxqidx / ctx->rxq_perchan;
	tx_channel_id = txqidx / ctx->txq_perchan;
	rx_channel_id = cxgb4_port_e2cchan(u_ctx->lldi.ports[portno]);


	chcr_req->wreq.op_to_cctx_size = FILL_WR_OP_CCTX_SIZE;
	chcr_req->wreq.pld_size_hash_size =
		htonl(FW_CRYPTO_LOOKASIDE_WR_HASH_SIZE_V(hash_sz));
	chcr_req->wreq.len16_pkd =
		htonl(FW_CRYPTO_LOOKASIDE_WR_LEN16_V(DIV_ROUND_UP(len16, 16)));
	chcr_req->wreq.cookie = cpu_to_be64((uपूर्णांकptr_t)req);
	chcr_req->wreq.rx_chid_to_rx_q_id = FILL_WR_RX_Q_ID(rx_channel_id, qid,
							    !!lcb, txqidx);

	chcr_req->ulptx.cmd_dest = FILL_ULPTX_CMD_DEST(tx_channel_id, fid);
	chcr_req->ulptx.len = htonl((DIV_ROUND_UP(len16, 16) -
				((माप(chcr_req->wreq)) >> 4)));
	chcr_req->sc_imm.cmd_more = FILL_CMD_MORE(!imm);
	chcr_req->sc_imm.len = cpu_to_be32(माप(काष्ठा cpl_tx_sec_pdu) +
					   माप(chcr_req->key_ctx) + sc_len);
पूर्ण

/**
 *	create_cipher_wr - क्रमm the WR क्रम cipher operations
 *	@wrparam: Container क्रम create_cipher_wr()'s parameters
 */
अटल काष्ठा sk_buff *create_cipher_wr(काष्ठा cipher_wr_param *wrparam)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(wrparam->req);
	काष्ठा chcr_context *ctx = c_ctx(tfm);
	काष्ठा uld_ctx *u_ctx = ULD_CTX(ctx);
	काष्ठा ablk_ctx *ablkctx = ABLK_CTX(ctx);
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा chcr_wr *chcr_req;
	काष्ठा cpl_rx_phys_dsgl *phys_cpl;
	काष्ठा ulptx_sgl *ulptx;
	काष्ठा chcr_skcipher_req_ctx *reqctx =
		skcipher_request_ctx(wrparam->req);
	अचिन्हित पूर्णांक temp = 0, transhdr_len, dst_size;
	पूर्णांक error;
	पूर्णांक nents;
	अचिन्हित पूर्णांक kctx_len;
	gfp_t flags = wrparam->req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP ?
			GFP_KERNEL : GFP_ATOMIC;
	काष्ठा adapter *adap = padap(ctx->dev);
	अचिन्हित पूर्णांक rx_channel_id = reqctx->rxqidx / ctx->rxq_perchan;

	rx_channel_id = cxgb4_port_e2cchan(u_ctx->lldi.ports[rx_channel_id]);
	nents = sg_nents_xlen(reqctx->dstsg,  wrparam->bytes, CHCR_DST_SG_SIZE,
			      reqctx->dst_ofst);
	dst_size = get_space_क्रम_phys_dsgl(nents);
	kctx_len = roundup(ablkctx->enckey_len, 16);
	transhdr_len = CIPHER_TRANSHDR_SIZE(kctx_len, dst_size);
	nents = sg_nents_xlen(reqctx->srcsg, wrparam->bytes,
				  CHCR_SRC_SG_SIZE, reqctx->src_ofst);
	temp = reqctx->imm ? roundup(wrparam->bytes, 16) :
				     (sgl_len(nents) * 8);
	transhdr_len += temp;
	transhdr_len = roundup(transhdr_len, 16);
	skb = alloc_skb(SGE_MAX_WR_LEN, flags);
	अगर (!skb) अणु
		error = -ENOMEM;
		जाओ err;
	पूर्ण
	chcr_req = __skb_put_zero(skb, transhdr_len);
	chcr_req->sec_cpl.op_ivinsrtofst =
			FILL_SEC_CPL_OP_IVINSR(rx_channel_id, 2, 1);

	chcr_req->sec_cpl.pldlen = htonl(IV + wrparam->bytes);
	chcr_req->sec_cpl.aadstart_cipherstop_hi =
			FILL_SEC_CPL_CIPHERSTOP_HI(0, 0, IV + 1, 0);

	chcr_req->sec_cpl.cipherstop_lo_authinsert =
			FILL_SEC_CPL_AUTHINSERT(0, 0, 0, 0);
	chcr_req->sec_cpl.seqno_numivs = FILL_SEC_CPL_SCMD0_SEQNO(reqctx->op, 0,
							 ablkctx->ciph_mode,
							 0, 0, IV >> 1);
	chcr_req->sec_cpl.ivgen_hdrlen = FILL_SEC_CPL_IVGEN_HDRLEN(0, 0, 0,
							  0, 1, dst_size);

	chcr_req->key_ctx.ctx_hdr = ablkctx->key_ctx_hdr;
	अगर ((reqctx->op == CHCR_DECRYPT_OP) &&
	    (!(get_cryptoalg_subtype(tfm) ==
	       CRYPTO_ALG_SUB_TYPE_CTR)) &&
	    (!(get_cryptoalg_subtype(tfm) ==
	       CRYPTO_ALG_SUB_TYPE_CTR_RFC3686))) अणु
		generate_copy_rrkey(ablkctx, &chcr_req->key_ctx);
	पूर्ण अन्यथा अणु
		अगर ((ablkctx->ciph_mode == CHCR_SCMD_CIPHER_MODE_AES_CBC) ||
		    (ablkctx->ciph_mode == CHCR_SCMD_CIPHER_MODE_AES_CTR)) अणु
			स_नकल(chcr_req->key_ctx.key, ablkctx->key,
			       ablkctx->enckey_len);
		पूर्ण अन्यथा अणु
			स_नकल(chcr_req->key_ctx.key, ablkctx->key +
			       (ablkctx->enckey_len >> 1),
			       ablkctx->enckey_len >> 1);
			स_नकल(chcr_req->key_ctx.key +
			       (ablkctx->enckey_len >> 1),
			       ablkctx->key,
			       ablkctx->enckey_len >> 1);
		पूर्ण
	पूर्ण
	phys_cpl = (काष्ठा cpl_rx_phys_dsgl *)((u8 *)(chcr_req + 1) + kctx_len);
	ulptx = (काष्ठा ulptx_sgl *)((u8 *)(phys_cpl + 1) + dst_size);
	chcr_add_cipher_src_ent(wrparam->req, ulptx, wrparam);
	chcr_add_cipher_dst_ent(wrparam->req, phys_cpl, wrparam, wrparam->qid);

	atomic_inc(&adap->chcr_stats.cipher_rqst);
	temp = माप(काष्ठा cpl_rx_phys_dsgl) + dst_size + kctx_len + IV
		+ (reqctx->imm ? (wrparam->bytes) : 0);
	create_wreq(c_ctx(tfm), chcr_req, &(wrparam->req->base), reqctx->imm, 0,
		    transhdr_len, temp,
			ablkctx->ciph_mode == CHCR_SCMD_CIPHER_MODE_AES_CBC);
	reqctx->skb = skb;

	अगर (reqctx->op && (ablkctx->ciph_mode ==
			   CHCR_SCMD_CIPHER_MODE_AES_CBC))
		sg_pcopy_to_buffer(wrparam->req->src,
			sg_nents(wrparam->req->src), wrparam->req->iv, 16,
			reqctx->processed + wrparam->bytes - AES_BLOCK_SIZE);

	वापस skb;
err:
	वापस ERR_PTR(error);
पूर्ण

अटल अंतरभूत पूर्णांक chcr_keyctx_ck_size(अचिन्हित पूर्णांक keylen)
अणु
	पूर्णांक ck_size = 0;

	अगर (keylen == AES_KEYSIZE_128)
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_128;
	अन्यथा अगर (keylen == AES_KEYSIZE_192)
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_192;
	अन्यथा अगर (keylen == AES_KEYSIZE_256)
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_256;
	अन्यथा
		ck_size = 0;

	वापस ck_size;
पूर्ण
अटल पूर्णांक chcr_cipher_fallback_setkey(काष्ठा crypto_skcipher *cipher,
				       स्थिर u8 *key,
				       अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा ablk_ctx *ablkctx = ABLK_CTX(c_ctx(cipher));

	crypto_skcipher_clear_flags(ablkctx->sw_cipher,
				CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(ablkctx->sw_cipher,
				cipher->base.crt_flags & CRYPTO_TFM_REQ_MASK);
	वापस crypto_skcipher_setkey(ablkctx->sw_cipher, key, keylen);
पूर्ण

अटल पूर्णांक chcr_aes_cbc_setkey(काष्ठा crypto_skcipher *cipher,
			       स्थिर u8 *key,
			       अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा ablk_ctx *ablkctx = ABLK_CTX(c_ctx(cipher));
	अचिन्हित पूर्णांक ck_size, context_size;
	u16 alignment = 0;
	पूर्णांक err;

	err = chcr_cipher_fallback_setkey(cipher, key, keylen);
	अगर (err)
		जाओ badkey_err;

	ck_size = chcr_keyctx_ck_size(keylen);
	alignment = ck_size == CHCR_KEYCTX_CIPHER_KEY_SIZE_192 ? 8 : 0;
	स_नकल(ablkctx->key, key, keylen);
	ablkctx->enckey_len = keylen;
	get_aes_decrypt_key(ablkctx->rrkey, ablkctx->key, keylen << 3);
	context_size = (KEY_CONTEXT_HDR_SALT_AND_PAD +
			keylen + alignment) >> 4;

	ablkctx->key_ctx_hdr = FILL_KEY_CTX_HDR(ck_size, CHCR_KEYCTX_NO_KEY,
						0, 0, context_size);
	ablkctx->ciph_mode = CHCR_SCMD_CIPHER_MODE_AES_CBC;
	वापस 0;
badkey_err:
	ablkctx->enckey_len = 0;

	वापस err;
पूर्ण

अटल पूर्णांक chcr_aes_ctr_setkey(काष्ठा crypto_skcipher *cipher,
				   स्थिर u8 *key,
				   अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा ablk_ctx *ablkctx = ABLK_CTX(c_ctx(cipher));
	अचिन्हित पूर्णांक ck_size, context_size;
	u16 alignment = 0;
	पूर्णांक err;

	err = chcr_cipher_fallback_setkey(cipher, key, keylen);
	अगर (err)
		जाओ badkey_err;
	ck_size = chcr_keyctx_ck_size(keylen);
	alignment = (ck_size == CHCR_KEYCTX_CIPHER_KEY_SIZE_192) ? 8 : 0;
	स_नकल(ablkctx->key, key, keylen);
	ablkctx->enckey_len = keylen;
	context_size = (KEY_CONTEXT_HDR_SALT_AND_PAD +
			keylen + alignment) >> 4;

	ablkctx->key_ctx_hdr = FILL_KEY_CTX_HDR(ck_size, CHCR_KEYCTX_NO_KEY,
						0, 0, context_size);
	ablkctx->ciph_mode = CHCR_SCMD_CIPHER_MODE_AES_CTR;

	वापस 0;
badkey_err:
	ablkctx->enckey_len = 0;

	वापस err;
पूर्ण

अटल पूर्णांक chcr_aes_rfc3686_setkey(काष्ठा crypto_skcipher *cipher,
				   स्थिर u8 *key,
				   अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा ablk_ctx *ablkctx = ABLK_CTX(c_ctx(cipher));
	अचिन्हित पूर्णांक ck_size, context_size;
	u16 alignment = 0;
	पूर्णांक err;

	अगर (keylen < CTR_RFC3686_NONCE_SIZE)
		वापस -EINVAL;
	स_नकल(ablkctx->nonce, key + (keylen - CTR_RFC3686_NONCE_SIZE),
	       CTR_RFC3686_NONCE_SIZE);

	keylen -= CTR_RFC3686_NONCE_SIZE;
	err = chcr_cipher_fallback_setkey(cipher, key, keylen);
	अगर (err)
		जाओ badkey_err;

	ck_size = chcr_keyctx_ck_size(keylen);
	alignment = (ck_size == CHCR_KEYCTX_CIPHER_KEY_SIZE_192) ? 8 : 0;
	स_नकल(ablkctx->key, key, keylen);
	ablkctx->enckey_len = keylen;
	context_size = (KEY_CONTEXT_HDR_SALT_AND_PAD +
			keylen + alignment) >> 4;

	ablkctx->key_ctx_hdr = FILL_KEY_CTX_HDR(ck_size, CHCR_KEYCTX_NO_KEY,
						0, 0, context_size);
	ablkctx->ciph_mode = CHCR_SCMD_CIPHER_MODE_AES_CTR;

	वापस 0;
badkey_err:
	ablkctx->enckey_len = 0;

	वापस err;
पूर्ण
अटल व्योम ctr_add_iv(u8 *dstiv, u8 *srciv, u32 add)
अणु
	अचिन्हित पूर्णांक size = AES_BLOCK_SIZE;
	__be32 *b = (__be32 *)(dstiv + size);
	u32 c, prev;

	स_नकल(dstiv, srciv, AES_BLOCK_SIZE);
	क्रम (; size >= 4; size -= 4) अणु
		prev = be32_to_cpu(*--b);
		c = prev + add;
		*b = cpu_to_be32(c);
		अगर (prev < c)
			अवरोध;
		add = 1;
	पूर्ण

पूर्ण

अटल अचिन्हित पूर्णांक adjust_ctr_overflow(u8 *iv, u32 bytes)
अणु
	__be32 *b = (__be32 *)(iv + AES_BLOCK_SIZE);
	u64 c;
	u32 temp = be32_to_cpu(*--b);

	temp = ~temp;
	c = (u64)temp +  1; // No of block can processed without overflow
	अगर ((bytes / AES_BLOCK_SIZE) >= c)
		bytes = c * AES_BLOCK_SIZE;
	वापस bytes;
पूर्ण

अटल पूर्णांक chcr_update_tweak(काष्ठा skcipher_request *req, u8 *iv,
			     u32 isfinal)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा ablk_ctx *ablkctx = ABLK_CTX(c_ctx(tfm));
	काष्ठा chcr_skcipher_req_ctx *reqctx = skcipher_request_ctx(req);
	काष्ठा crypto_aes_ctx aes;
	पूर्णांक ret, i;
	u8 *key;
	अचिन्हित पूर्णांक keylen;
	पूर्णांक round = reqctx->last_req_len / AES_BLOCK_SIZE;
	पूर्णांक round8 = round / 8;

	स_नकल(iv, reqctx->iv, AES_BLOCK_SIZE);

	keylen = ablkctx->enckey_len / 2;
	key = ablkctx->key + keylen;
	/* For a 192 bit key हटाओ the padded zeroes which was
	 * added in chcr_xts_setkey
	 */
	अगर (KEY_CONTEXT_CK_SIZE_G(ntohl(ablkctx->key_ctx_hdr))
			== CHCR_KEYCTX_CIPHER_KEY_SIZE_192)
		ret = aes_expandkey(&aes, key, keylen - 8);
	अन्यथा
		ret = aes_expandkey(&aes, key, keylen);
	अगर (ret)
		वापस ret;
	aes_encrypt(&aes, iv, iv);
	क्रम (i = 0; i < round8; i++)
		gf128mul_x8_ble((le128 *)iv, (le128 *)iv);

	क्रम (i = 0; i < (round % 8); i++)
		gf128mul_x_ble((le128 *)iv, (le128 *)iv);

	अगर (!isfinal)
		aes_decrypt(&aes, iv, iv);

	memzero_explicit(&aes, माप(aes));
	वापस 0;
पूर्ण

अटल पूर्णांक chcr_update_cipher_iv(काष्ठा skcipher_request *req,
				   काष्ठा cpl_fw6_pld *fw6_pld, u8 *iv)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा chcr_skcipher_req_ctx *reqctx = skcipher_request_ctx(req);
	पूर्णांक subtype = get_cryptoalg_subtype(tfm);
	पूर्णांक ret = 0;

	अगर (subtype == CRYPTO_ALG_SUB_TYPE_CTR)
		ctr_add_iv(iv, req->iv, (reqctx->processed /
			   AES_BLOCK_SIZE));
	अन्यथा अगर (subtype == CRYPTO_ALG_SUB_TYPE_CTR_RFC3686)
		*(__be32 *)(reqctx->iv + CTR_RFC3686_NONCE_SIZE +
			CTR_RFC3686_IV_SIZE) = cpu_to_be32((reqctx->processed /
						AES_BLOCK_SIZE) + 1);
	अन्यथा अगर (subtype == CRYPTO_ALG_SUB_TYPE_XTS)
		ret = chcr_update_tweak(req, iv, 0);
	अन्यथा अगर (subtype == CRYPTO_ALG_SUB_TYPE_CBC) अणु
		अगर (reqctx->op)
			/*Updated beक्रमe sending last WR*/
			स_नकल(iv, req->iv, AES_BLOCK_SIZE);
		अन्यथा
			स_नकल(iv, &fw6_pld->data[2], AES_BLOCK_SIZE);
	पूर्ण

	वापस ret;

पूर्ण

/* We need separate function क्रम final iv because in rfc3686  Initial counter
 * starts from 1 and buffer size of iv is 8 byte only which reमुख्यs स्थिरant
 * क्रम subsequent update requests
 */

अटल पूर्णांक chcr_final_cipher_iv(काष्ठा skcipher_request *req,
				   काष्ठा cpl_fw6_pld *fw6_pld, u8 *iv)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा chcr_skcipher_req_ctx *reqctx = skcipher_request_ctx(req);
	पूर्णांक subtype = get_cryptoalg_subtype(tfm);
	पूर्णांक ret = 0;

	अगर (subtype == CRYPTO_ALG_SUB_TYPE_CTR)
		ctr_add_iv(iv, req->iv, DIV_ROUND_UP(reqctx->processed,
						       AES_BLOCK_SIZE));
	अन्यथा अगर (subtype == CRYPTO_ALG_SUB_TYPE_XTS) अणु
		अगर (!reqctx->partial_req)
			स_नकल(iv, reqctx->iv, AES_BLOCK_SIZE);
		अन्यथा
			ret = chcr_update_tweak(req, iv, 1);
	पूर्ण
	अन्यथा अगर (subtype == CRYPTO_ALG_SUB_TYPE_CBC) अणु
		/*Alपढ़ोy updated क्रम Decrypt*/
		अगर (!reqctx->op)
			स_नकल(iv, &fw6_pld->data[2], AES_BLOCK_SIZE);

	पूर्ण
	वापस ret;

पूर्ण

अटल पूर्णांक chcr_handle_cipher_resp(काष्ठा skcipher_request *req,
				   अचिन्हित अक्षर *input, पूर्णांक err)
अणु
	काष्ठा chcr_skcipher_req_ctx *reqctx = skcipher_request_ctx(req);
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा cpl_fw6_pld *fw6_pld = (काष्ठा cpl_fw6_pld *)input;
	काष्ठा ablk_ctx *ablkctx = ABLK_CTX(c_ctx(tfm));
	काष्ठा uld_ctx *u_ctx = ULD_CTX(c_ctx(tfm));
	काष्ठा chcr_dev *dev = c_ctx(tfm)->dev;
	काष्ठा chcr_context *ctx = c_ctx(tfm);
	काष्ठा adapter *adap = padap(ctx->dev);
	काष्ठा cipher_wr_param wrparam;
	काष्ठा sk_buff *skb;
	पूर्णांक bytes;

	अगर (err)
		जाओ unmap;
	अगर (req->cryptlen == reqctx->processed) अणु
		chcr_cipher_dma_unmap(&ULD_CTX(c_ctx(tfm))->lldi.pdev->dev,
				      req);
		err = chcr_final_cipher_iv(req, fw6_pld, req->iv);
		जाओ complete;
	पूर्ण

	अगर (!reqctx->imm) अणु
		bytes = chcr_sg_ent_in_wr(reqctx->srcsg, reqctx->dstsg, 0,
					  CIP_SPACE_LEFT(ablkctx->enckey_len),
					  reqctx->src_ofst, reqctx->dst_ofst);
		अगर ((bytes + reqctx->processed) >= req->cryptlen)
			bytes  = req->cryptlen - reqctx->processed;
		अन्यथा
			bytes = roundकरोwn(bytes, 16);
	पूर्ण अन्यथा अणु
		/*CTR mode counter overfloa*/
		bytes  = req->cryptlen - reqctx->processed;
	पूर्ण
	err = chcr_update_cipher_iv(req, fw6_pld, reqctx->iv);
	अगर (err)
		जाओ unmap;

	अगर (unlikely(bytes == 0)) अणु
		chcr_cipher_dma_unmap(&ULD_CTX(c_ctx(tfm))->lldi.pdev->dev,
				      req);
		स_नकल(req->iv, reqctx->init_iv, IV);
		atomic_inc(&adap->chcr_stats.fallback);
		err = chcr_cipher_fallback(ablkctx->sw_cipher, req, req->iv,
					   reqctx->op);
		जाओ complete;
	पूर्ण

	अगर (get_cryptoalg_subtype(tfm) ==
	    CRYPTO_ALG_SUB_TYPE_CTR)
		bytes = adjust_ctr_overflow(reqctx->iv, bytes);
	wrparam.qid = u_ctx->lldi.rxq_ids[reqctx->rxqidx];
	wrparam.req = req;
	wrparam.bytes = bytes;
	skb = create_cipher_wr(&wrparam);
	अगर (IS_ERR(skb)) अणु
		pr_err("%s : Failed to form WR. No memory\n", __func__);
		err = PTR_ERR(skb);
		जाओ unmap;
	पूर्ण
	skb->dev = u_ctx->lldi.ports[0];
	set_wr_txq(skb, CPL_PRIORITY_DATA, reqctx->txqidx);
	chcr_send_wr(skb);
	reqctx->last_req_len = bytes;
	reqctx->processed += bytes;
	अगर (get_cryptoalg_subtype(tfm) ==
		CRYPTO_ALG_SUB_TYPE_CBC && req->base.flags ==
			CRYPTO_TFM_REQ_MAY_SLEEP ) अणु
		complete(&ctx->cbc_aes_aio_करोne);
	पूर्ण
	वापस 0;
unmap:
	chcr_cipher_dma_unmap(&ULD_CTX(c_ctx(tfm))->lldi.pdev->dev, req);
complete:
	अगर (get_cryptoalg_subtype(tfm) ==
		CRYPTO_ALG_SUB_TYPE_CBC && req->base.flags ==
			CRYPTO_TFM_REQ_MAY_SLEEP ) अणु
		complete(&ctx->cbc_aes_aio_करोne);
	पूर्ण
	chcr_dec_wrcount(dev);
	req->base.complete(&req->base, err);
	वापस err;
पूर्ण

अटल पूर्णांक process_cipher(काष्ठा skcipher_request *req,
				  अचिन्हित लघु qid,
				  काष्ठा sk_buff **skb,
				  अचिन्हित लघु op_type)
अणु
	काष्ठा chcr_skcipher_req_ctx *reqctx = skcipher_request_ctx(req);
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	अचिन्हित पूर्णांक ivsize = crypto_skcipher_ivsize(tfm);
	काष्ठा ablk_ctx *ablkctx = ABLK_CTX(c_ctx(tfm));
	काष्ठा adapter *adap = padap(c_ctx(tfm)->dev);
	काष्ठा	cipher_wr_param wrparam;
	पूर्णांक bytes, err = -EINVAL;
	पूर्णांक subtype;

	reqctx->processed = 0;
	reqctx->partial_req = 0;
	अगर (!req->iv)
		जाओ error;
	subtype = get_cryptoalg_subtype(tfm);
	अगर ((ablkctx->enckey_len == 0) || (ivsize > AES_BLOCK_SIZE) ||
	    (req->cryptlen == 0) ||
	    (req->cryptlen % crypto_skcipher_blocksize(tfm))) अणु
		अगर (req->cryptlen == 0 && subtype != CRYPTO_ALG_SUB_TYPE_XTS)
			जाओ fallback;
		अन्यथा अगर (req->cryptlen % crypto_skcipher_blocksize(tfm) &&
			 subtype == CRYPTO_ALG_SUB_TYPE_XTS)
			जाओ fallback;
		pr_err("AES: Invalid value of Key Len %d nbytes %d IV Len %d\n",
		       ablkctx->enckey_len, req->cryptlen, ivsize);
		जाओ error;
	पूर्ण

	err = chcr_cipher_dma_map(&ULD_CTX(c_ctx(tfm))->lldi.pdev->dev, req);
	अगर (err)
		जाओ error;
	अगर (req->cryptlen < (SGE_MAX_WR_LEN - (माप(काष्ठा chcr_wr) +
					    AES_MIN_KEY_SIZE +
					    माप(काष्ठा cpl_rx_phys_dsgl) +
					/*Min dsgl size*/
					    32))) अणु
		/* Can be sent as Imm*/
		अचिन्हित पूर्णांक dnents = 0, transhdr_len, phys_dsgl, kctx_len;

		dnents = sg_nents_xlen(req->dst, req->cryptlen,
				       CHCR_DST_SG_SIZE, 0);
		phys_dsgl = get_space_क्रम_phys_dsgl(dnents);
		kctx_len = roundup(ablkctx->enckey_len, 16);
		transhdr_len = CIPHER_TRANSHDR_SIZE(kctx_len, phys_dsgl);
		reqctx->imm = (transhdr_len + IV + req->cryptlen) <=
			SGE_MAX_WR_LEN;
		bytes = IV + req->cryptlen;

	पूर्ण अन्यथा अणु
		reqctx->imm = 0;
	पूर्ण

	अगर (!reqctx->imm) अणु
		bytes = chcr_sg_ent_in_wr(req->src, req->dst, 0,
					  CIP_SPACE_LEFT(ablkctx->enckey_len),
					  0, 0);
		अगर ((bytes + reqctx->processed) >= req->cryptlen)
			bytes  = req->cryptlen - reqctx->processed;
		अन्यथा
			bytes = roundकरोwn(bytes, 16);
	पूर्ण अन्यथा अणु
		bytes = req->cryptlen;
	पूर्ण
	अगर (subtype == CRYPTO_ALG_SUB_TYPE_CTR) अणु
		bytes = adjust_ctr_overflow(req->iv, bytes);
	पूर्ण
	अगर (subtype == CRYPTO_ALG_SUB_TYPE_CTR_RFC3686) अणु
		स_नकल(reqctx->iv, ablkctx->nonce, CTR_RFC3686_NONCE_SIZE);
		स_नकल(reqctx->iv + CTR_RFC3686_NONCE_SIZE, req->iv,
				CTR_RFC3686_IV_SIZE);

		/* initialize counter portion of counter block */
		*(__be32 *)(reqctx->iv + CTR_RFC3686_NONCE_SIZE +
			CTR_RFC3686_IV_SIZE) = cpu_to_be32(1);
		स_नकल(reqctx->init_iv, reqctx->iv, IV);

	पूर्ण अन्यथा अणु

		स_नकल(reqctx->iv, req->iv, IV);
		स_नकल(reqctx->init_iv, req->iv, IV);
	पूर्ण
	अगर (unlikely(bytes == 0)) अणु
		chcr_cipher_dma_unmap(&ULD_CTX(c_ctx(tfm))->lldi.pdev->dev,
				      req);
fallback:       atomic_inc(&adap->chcr_stats.fallback);
		err = chcr_cipher_fallback(ablkctx->sw_cipher, req,
					   subtype ==
					   CRYPTO_ALG_SUB_TYPE_CTR_RFC3686 ?
					   reqctx->iv : req->iv,
					   op_type);
		जाओ error;
	पूर्ण
	reqctx->op = op_type;
	reqctx->srcsg = req->src;
	reqctx->dstsg = req->dst;
	reqctx->src_ofst = 0;
	reqctx->dst_ofst = 0;
	wrparam.qid = qid;
	wrparam.req = req;
	wrparam.bytes = bytes;
	*skb = create_cipher_wr(&wrparam);
	अगर (IS_ERR(*skb)) अणु
		err = PTR_ERR(*skb);
		जाओ unmap;
	पूर्ण
	reqctx->processed = bytes;
	reqctx->last_req_len = bytes;
	reqctx->partial_req = !!(req->cryptlen - reqctx->processed);

	वापस 0;
unmap:
	chcr_cipher_dma_unmap(&ULD_CTX(c_ctx(tfm))->lldi.pdev->dev, req);
error:
	वापस err;
पूर्ण

अटल पूर्णांक chcr_aes_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा chcr_skcipher_req_ctx *reqctx = skcipher_request_ctx(req);
	काष्ठा chcr_dev *dev = c_ctx(tfm)->dev;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक err;
	काष्ठा uld_ctx *u_ctx = ULD_CTX(c_ctx(tfm));
	काष्ठा chcr_context *ctx = c_ctx(tfm);
	अचिन्हित पूर्णांक cpu;

	cpu = get_cpu();
	reqctx->txqidx = cpu % ctx->ntxq;
	reqctx->rxqidx = cpu % ctx->nrxq;
	put_cpu();

	err = chcr_inc_wrcount(dev);
	अगर (err)
		वापस -ENXIO;
	अगर (unlikely(cxgb4_is_crypto_q_full(u_ctx->lldi.ports[0],
						reqctx->txqidx) &&
		(!(req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG)))) अणु
			err = -ENOSPC;
			जाओ error;
	पूर्ण

	err = process_cipher(req, u_ctx->lldi.rxq_ids[reqctx->rxqidx],
			     &skb, CHCR_ENCRYPT_OP);
	अगर (err || !skb)
		वापस  err;
	skb->dev = u_ctx->lldi.ports[0];
	set_wr_txq(skb, CPL_PRIORITY_DATA, reqctx->txqidx);
	chcr_send_wr(skb);
	अगर (get_cryptoalg_subtype(tfm) ==
		CRYPTO_ALG_SUB_TYPE_CBC && req->base.flags ==
			CRYPTO_TFM_REQ_MAY_SLEEP ) अणु
			reqctx->partial_req = 1;
			रुको_क्रम_completion(&ctx->cbc_aes_aio_करोne);
        पूर्ण
	वापस -EINPROGRESS;
error:
	chcr_dec_wrcount(dev);
	वापस err;
पूर्ण

अटल पूर्णांक chcr_aes_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा chcr_skcipher_req_ctx *reqctx = skcipher_request_ctx(req);
	काष्ठा uld_ctx *u_ctx = ULD_CTX(c_ctx(tfm));
	काष्ठा chcr_dev *dev = c_ctx(tfm)->dev;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक err;
	काष्ठा chcr_context *ctx = c_ctx(tfm);
	अचिन्हित पूर्णांक cpu;

	cpu = get_cpu();
	reqctx->txqidx = cpu % ctx->ntxq;
	reqctx->rxqidx = cpu % ctx->nrxq;
	put_cpu();

	err = chcr_inc_wrcount(dev);
	अगर (err)
		वापस -ENXIO;

	अगर (unlikely(cxgb4_is_crypto_q_full(u_ctx->lldi.ports[0],
						reqctx->txqidx) &&
		(!(req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG))))
			वापस -ENOSPC;
	err = process_cipher(req, u_ctx->lldi.rxq_ids[reqctx->rxqidx],
			     &skb, CHCR_DECRYPT_OP);
	अगर (err || !skb)
		वापस err;
	skb->dev = u_ctx->lldi.ports[0];
	set_wr_txq(skb, CPL_PRIORITY_DATA, reqctx->txqidx);
	chcr_send_wr(skb);
	वापस -EINPROGRESS;
पूर्ण
अटल पूर्णांक chcr_device_init(काष्ठा chcr_context *ctx)
अणु
	काष्ठा uld_ctx *u_ctx = शून्य;
	पूर्णांक txq_perchan, ntxq;
	पूर्णांक err = 0, rxq_perchan;

	अगर (!ctx->dev) अणु
		u_ctx = assign_chcr_device();
		अगर (!u_ctx) अणु
			err = -ENXIO;
			pr_err("chcr device assignment fails\n");
			जाओ out;
		पूर्ण
		ctx->dev = &u_ctx->dev;
		ntxq = u_ctx->lldi.ntxq;
		rxq_perchan = u_ctx->lldi.nrxq / u_ctx->lldi.nchan;
		txq_perchan = ntxq / u_ctx->lldi.nchan;
		ctx->ntxq = ntxq;
		ctx->nrxq = u_ctx->lldi.nrxq;
		ctx->rxq_perchan = rxq_perchan;
		ctx->txq_perchan = txq_perchan;
	पूर्ण
out:
	वापस err;
पूर्ण

अटल पूर्णांक chcr_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(tfm);
	काष्ठा chcr_context *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा ablk_ctx *ablkctx = ABLK_CTX(ctx);

	ablkctx->sw_cipher = crypto_alloc_skcipher(alg->base.cra_name, 0,
				CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(ablkctx->sw_cipher)) अणु
		pr_err("failed to allocate fallback for %s\n", alg->base.cra_name);
		वापस PTR_ERR(ablkctx->sw_cipher);
	पूर्ण
	init_completion(&ctx->cbc_aes_aio_करोne);
	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा chcr_skcipher_req_ctx) +
					 crypto_skcipher_reqsize(ablkctx->sw_cipher));

	वापस chcr_device_init(ctx);
पूर्ण

अटल पूर्णांक chcr_rfc3686_init(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(tfm);
	काष्ठा chcr_context *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा ablk_ctx *ablkctx = ABLK_CTX(ctx);

	/*RFC3686 initialises IV counter value to 1, rfc3686(ctr(aes))
	 * cannot be used as fallback in chcr_handle_cipher_response
	 */
	ablkctx->sw_cipher = crypto_alloc_skcipher("ctr(aes)", 0,
				CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(ablkctx->sw_cipher)) अणु
		pr_err("failed to allocate fallback for %s\n", alg->base.cra_name);
		वापस PTR_ERR(ablkctx->sw_cipher);
	पूर्ण
	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा chcr_skcipher_req_ctx) +
				    crypto_skcipher_reqsize(ablkctx->sw_cipher));
	वापस chcr_device_init(ctx);
पूर्ण


अटल व्योम chcr_निकास_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा chcr_context *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा ablk_ctx *ablkctx = ABLK_CTX(ctx);

	crypto_मुक्त_skcipher(ablkctx->sw_cipher);
पूर्ण

अटल पूर्णांक get_alg_config(काष्ठा algo_param *params,
			  अचिन्हित पूर्णांक auth_size)
अणु
	चयन (auth_size) अणु
	हाल SHA1_DIGEST_SIZE:
		params->mk_size = CHCR_KEYCTX_MAC_KEY_SIZE_160;
		params->auth_mode = CHCR_SCMD_AUTH_MODE_SHA1;
		params->result_size = SHA1_DIGEST_SIZE;
		अवरोध;
	हाल SHA224_DIGEST_SIZE:
		params->mk_size = CHCR_KEYCTX_MAC_KEY_SIZE_256;
		params->auth_mode = CHCR_SCMD_AUTH_MODE_SHA224;
		params->result_size = SHA256_DIGEST_SIZE;
		अवरोध;
	हाल SHA256_DIGEST_SIZE:
		params->mk_size = CHCR_KEYCTX_MAC_KEY_SIZE_256;
		params->auth_mode = CHCR_SCMD_AUTH_MODE_SHA256;
		params->result_size = SHA256_DIGEST_SIZE;
		अवरोध;
	हाल SHA384_DIGEST_SIZE:
		params->mk_size = CHCR_KEYCTX_MAC_KEY_SIZE_512;
		params->auth_mode = CHCR_SCMD_AUTH_MODE_SHA512_384;
		params->result_size = SHA512_DIGEST_SIZE;
		अवरोध;
	हाल SHA512_DIGEST_SIZE:
		params->mk_size = CHCR_KEYCTX_MAC_KEY_SIZE_512;
		params->auth_mode = CHCR_SCMD_AUTH_MODE_SHA512_512;
		params->result_size = SHA512_DIGEST_SIZE;
		अवरोध;
	शेष:
		pr_err("ERROR, unsupported digest size\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम chcr_मुक्त_shash(काष्ठा crypto_shash *base_hash)
अणु
		crypto_मुक्त_shash(base_hash);
पूर्ण

/**
 *	create_hash_wr - Create hash work request
 *	@req: Cipher req base
 *	@param: Container क्रम create_hash_wr()'s parameters
 */
अटल काष्ठा sk_buff *create_hash_wr(काष्ठा ahash_request *req,
				      काष्ठा hash_wr_param *param)
अणु
	काष्ठा chcr_ahash_req_ctx *req_ctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा chcr_context *ctx = h_ctx(tfm);
	काष्ठा hmac_ctx *hmacctx = HMAC_CTX(ctx);
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा uld_ctx *u_ctx = ULD_CTX(ctx);
	काष्ठा chcr_wr *chcr_req;
	काष्ठा ulptx_sgl *ulptx;
	अचिन्हित पूर्णांक nents = 0, transhdr_len;
	अचिन्हित पूर्णांक temp = 0;
	gfp_t flags = req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP ? GFP_KERNEL :
		GFP_ATOMIC;
	काष्ठा adapter *adap = padap(h_ctx(tfm)->dev);
	पूर्णांक error = 0;
	अचिन्हित पूर्णांक rx_channel_id = req_ctx->rxqidx / ctx->rxq_perchan;

	rx_channel_id = cxgb4_port_e2cchan(u_ctx->lldi.ports[rx_channel_id]);
	transhdr_len = HASH_TRANSHDR_SIZE(param->kctx_len);
	req_ctx->hctx_wr.imm = (transhdr_len + param->bfr_len +
				param->sg_len) <= SGE_MAX_WR_LEN;
	nents = sg_nents_xlen(req_ctx->hctx_wr.srcsg, param->sg_len,
		      CHCR_SRC_SG_SIZE, req_ctx->hctx_wr.src_ofst);
	nents += param->bfr_len ? 1 : 0;
	transhdr_len += req_ctx->hctx_wr.imm ? roundup(param->bfr_len +
				param->sg_len, 16) : (sgl_len(nents) * 8);
	transhdr_len = roundup(transhdr_len, 16);

	skb = alloc_skb(transhdr_len, flags);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);
	chcr_req = __skb_put_zero(skb, transhdr_len);

	chcr_req->sec_cpl.op_ivinsrtofst =
		FILL_SEC_CPL_OP_IVINSR(rx_channel_id, 2, 0);

	chcr_req->sec_cpl.pldlen = htonl(param->bfr_len + param->sg_len);

	chcr_req->sec_cpl.aadstart_cipherstop_hi =
		FILL_SEC_CPL_CIPHERSTOP_HI(0, 0, 0, 0);
	chcr_req->sec_cpl.cipherstop_lo_authinsert =
		FILL_SEC_CPL_AUTHINSERT(0, 1, 0, 0);
	chcr_req->sec_cpl.seqno_numivs =
		FILL_SEC_CPL_SCMD0_SEQNO(0, 0, 0, param->alg_prm.auth_mode,
					 param->opad_needed, 0);

	chcr_req->sec_cpl.ivgen_hdrlen =
		FILL_SEC_CPL_IVGEN_HDRLEN(param->last, param->more, 0, 1, 0, 0);

	स_नकल(chcr_req->key_ctx.key, req_ctx->partial_hash,
	       param->alg_prm.result_size);

	अगर (param->opad_needed)
		स_नकल(chcr_req->key_ctx.key +
		       ((param->alg_prm.result_size <= 32) ? 32 :
			CHCR_HASH_MAX_DIGEST_SIZE),
		       hmacctx->opad, param->alg_prm.result_size);

	chcr_req->key_ctx.ctx_hdr = FILL_KEY_CTX_HDR(CHCR_KEYCTX_NO_KEY,
					    param->alg_prm.mk_size, 0,
					    param->opad_needed,
					    ((param->kctx_len +
					     माप(chcr_req->key_ctx)) >> 4));
	chcr_req->sec_cpl.scmd1 = cpu_to_be64((u64)param->scmd1);
	ulptx = (काष्ठा ulptx_sgl *)((u8 *)(chcr_req + 1) + param->kctx_len +
				     DUMMY_BYTES);
	अगर (param->bfr_len != 0) अणु
		req_ctx->hctx_wr.dma_addr =
			dma_map_single(&u_ctx->lldi.pdev->dev, req_ctx->reqbfr,
				       param->bfr_len, DMA_TO_DEVICE);
		अगर (dma_mapping_error(&u_ctx->lldi.pdev->dev,
				       req_ctx->hctx_wr. dma_addr)) अणु
			error = -ENOMEM;
			जाओ err;
		पूर्ण
		req_ctx->hctx_wr.dma_len = param->bfr_len;
	पूर्ण अन्यथा अणु
		req_ctx->hctx_wr.dma_addr = 0;
	पूर्ण
	chcr_add_hash_src_ent(req, ulptx, param);
	/* Request upto max wr size */
	temp = param->kctx_len + DUMMY_BYTES + (req_ctx->hctx_wr.imm ?
				(param->sg_len + param->bfr_len) : 0);
	atomic_inc(&adap->chcr_stats.digest_rqst);
	create_wreq(h_ctx(tfm), chcr_req, &req->base, req_ctx->hctx_wr.imm,
		    param->hash_size, transhdr_len,
		    temp,  0);
	req_ctx->hctx_wr.skb = skb;
	वापस skb;
err:
	kमुक्त_skb(skb);
	वापस  ERR_PTR(error);
पूर्ण

अटल पूर्णांक chcr_ahash_update(काष्ठा ahash_request *req)
अणु
	काष्ठा chcr_ahash_req_ctx *req_ctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *rtfm = crypto_ahash_reqtfm(req);
	काष्ठा uld_ctx *u_ctx = ULD_CTX(h_ctx(rtfm));
	काष्ठा chcr_context *ctx = h_ctx(rtfm);
	काष्ठा chcr_dev *dev = h_ctx(rtfm)->dev;
	काष्ठा sk_buff *skb;
	u8 reमुख्यder = 0, bs;
	अचिन्हित पूर्णांक nbytes = req->nbytes;
	काष्ठा hash_wr_param params;
	पूर्णांक error;
	अचिन्हित पूर्णांक cpu;

	cpu = get_cpu();
	req_ctx->txqidx = cpu % ctx->ntxq;
	req_ctx->rxqidx = cpu % ctx->nrxq;
	put_cpu();

	bs = crypto_tfm_alg_blocksize(crypto_ahash_tfm(rtfm));

	अगर (nbytes + req_ctx->reqlen >= bs) अणु
		reमुख्यder = (nbytes + req_ctx->reqlen) % bs;
		nbytes = nbytes + req_ctx->reqlen - reमुख्यder;
	पूर्ण अन्यथा अणु
		sg_pcopy_to_buffer(req->src, sg_nents(req->src), req_ctx->reqbfr
				   + req_ctx->reqlen, nbytes, 0);
		req_ctx->reqlen += nbytes;
		वापस 0;
	पूर्ण
	error = chcr_inc_wrcount(dev);
	अगर (error)
		वापस -ENXIO;
	/* Detach state क्रम CHCR means lldi or padap is मुक्तd. Increasing
	 * inflight count क्रम dev guarantees that lldi and padap is valid
	 */
	अगर (unlikely(cxgb4_is_crypto_q_full(u_ctx->lldi.ports[0],
						req_ctx->txqidx) &&
		(!(req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG)))) अणु
			error = -ENOSPC;
			जाओ err;
	पूर्ण

	chcr_init_hctx_per_wr(req_ctx);
	error = chcr_hash_dma_map(&u_ctx->lldi.pdev->dev, req);
	अगर (error) अणु
		error = -ENOMEM;
		जाओ err;
	पूर्ण
	get_alg_config(&params.alg_prm, crypto_ahash_digestsize(rtfm));
	params.kctx_len = roundup(params.alg_prm.result_size, 16);
	params.sg_len = chcr_hash_ent_in_wr(req->src, !!req_ctx->reqlen,
				     HASH_SPACE_LEFT(params.kctx_len), 0);
	अगर (params.sg_len > req->nbytes)
		params.sg_len = req->nbytes;
	params.sg_len = roundकरोwn(params.sg_len + req_ctx->reqlen, bs) -
			req_ctx->reqlen;
	params.opad_needed = 0;
	params.more = 1;
	params.last = 0;
	params.bfr_len = req_ctx->reqlen;
	params.scmd1 = 0;
	req_ctx->hctx_wr.srcsg = req->src;

	params.hash_size = params.alg_prm.result_size;
	req_ctx->data_len += params.sg_len + params.bfr_len;
	skb = create_hash_wr(req, &params);
	अगर (IS_ERR(skb)) अणु
		error = PTR_ERR(skb);
		जाओ unmap;
	पूर्ण

	req_ctx->hctx_wr.processed += params.sg_len;
	अगर (reमुख्यder) अणु
		/* Swap buffers */
		swap(req_ctx->reqbfr, req_ctx->skbfr);
		sg_pcopy_to_buffer(req->src, sg_nents(req->src),
				   req_ctx->reqbfr, reमुख्यder, req->nbytes -
				   reमुख्यder);
	पूर्ण
	req_ctx->reqlen = reमुख्यder;
	skb->dev = u_ctx->lldi.ports[0];
	set_wr_txq(skb, CPL_PRIORITY_DATA, req_ctx->txqidx);
	chcr_send_wr(skb);
	वापस -EINPROGRESS;
unmap:
	chcr_hash_dma_unmap(&u_ctx->lldi.pdev->dev, req);
err:
	chcr_dec_wrcount(dev);
	वापस error;
पूर्ण

अटल व्योम create_last_hash_block(अक्षर *bfr_ptr, अचिन्हित पूर्णांक bs, u64 scmd1)
अणु
	स_रखो(bfr_ptr, 0, bs);
	*bfr_ptr = 0x80;
	अगर (bs == 64)
		*(__be64 *)(bfr_ptr + 56) = cpu_to_be64(scmd1  << 3);
	अन्यथा
		*(__be64 *)(bfr_ptr + 120) =  cpu_to_be64(scmd1  << 3);
पूर्ण

अटल पूर्णांक chcr_ahash_final(काष्ठा ahash_request *req)
अणु
	काष्ठा chcr_ahash_req_ctx *req_ctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *rtfm = crypto_ahash_reqtfm(req);
	काष्ठा chcr_dev *dev = h_ctx(rtfm)->dev;
	काष्ठा hash_wr_param params;
	काष्ठा sk_buff *skb;
	काष्ठा uld_ctx *u_ctx = ULD_CTX(h_ctx(rtfm));
	काष्ठा chcr_context *ctx = h_ctx(rtfm);
	u8 bs = crypto_tfm_alg_blocksize(crypto_ahash_tfm(rtfm));
	पूर्णांक error;
	अचिन्हित पूर्णांक cpu;

	cpu = get_cpu();
	req_ctx->txqidx = cpu % ctx->ntxq;
	req_ctx->rxqidx = cpu % ctx->nrxq;
	put_cpu();

	error = chcr_inc_wrcount(dev);
	अगर (error)
		वापस -ENXIO;

	chcr_init_hctx_per_wr(req_ctx);
	अगर (is_hmac(crypto_ahash_tfm(rtfm)))
		params.opad_needed = 1;
	अन्यथा
		params.opad_needed = 0;
	params.sg_len = 0;
	req_ctx->hctx_wr.isfinal = 1;
	get_alg_config(&params.alg_prm, crypto_ahash_digestsize(rtfm));
	params.kctx_len = roundup(params.alg_prm.result_size, 16);
	अगर (is_hmac(crypto_ahash_tfm(rtfm))) अणु
		params.opad_needed = 1;
		params.kctx_len *= 2;
	पूर्ण अन्यथा अणु
		params.opad_needed = 0;
	पूर्ण

	req_ctx->hctx_wr.result = 1;
	params.bfr_len = req_ctx->reqlen;
	req_ctx->data_len += params.bfr_len + params.sg_len;
	req_ctx->hctx_wr.srcsg = req->src;
	अगर (req_ctx->reqlen == 0) अणु
		create_last_hash_block(req_ctx->reqbfr, bs, req_ctx->data_len);
		params.last = 0;
		params.more = 1;
		params.scmd1 = 0;
		params.bfr_len = bs;

	पूर्ण अन्यथा अणु
		params.scmd1 = req_ctx->data_len;
		params.last = 1;
		params.more = 0;
	पूर्ण
	params.hash_size = crypto_ahash_digestsize(rtfm);
	skb = create_hash_wr(req, &params);
	अगर (IS_ERR(skb)) अणु
		error = PTR_ERR(skb);
		जाओ err;
	पूर्ण
	req_ctx->reqlen = 0;
	skb->dev = u_ctx->lldi.ports[0];
	set_wr_txq(skb, CPL_PRIORITY_DATA, req_ctx->txqidx);
	chcr_send_wr(skb);
	वापस -EINPROGRESS;
err:
	chcr_dec_wrcount(dev);
	वापस error;
पूर्ण

अटल पूर्णांक chcr_ahash_finup(काष्ठा ahash_request *req)
अणु
	काष्ठा chcr_ahash_req_ctx *req_ctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *rtfm = crypto_ahash_reqtfm(req);
	काष्ठा chcr_dev *dev = h_ctx(rtfm)->dev;
	काष्ठा uld_ctx *u_ctx = ULD_CTX(h_ctx(rtfm));
	काष्ठा chcr_context *ctx = h_ctx(rtfm);
	काष्ठा sk_buff *skb;
	काष्ठा hash_wr_param params;
	u8  bs;
	पूर्णांक error;
	अचिन्हित पूर्णांक cpu;

	cpu = get_cpu();
	req_ctx->txqidx = cpu % ctx->ntxq;
	req_ctx->rxqidx = cpu % ctx->nrxq;
	put_cpu();

	bs = crypto_tfm_alg_blocksize(crypto_ahash_tfm(rtfm));
	error = chcr_inc_wrcount(dev);
	अगर (error)
		वापस -ENXIO;

	अगर (unlikely(cxgb4_is_crypto_q_full(u_ctx->lldi.ports[0],
						req_ctx->txqidx) &&
		(!(req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG)))) अणु
			error = -ENOSPC;
			जाओ err;
	पूर्ण
	chcr_init_hctx_per_wr(req_ctx);
	error = chcr_hash_dma_map(&u_ctx->lldi.pdev->dev, req);
	अगर (error) अणु
		error = -ENOMEM;
		जाओ err;
	पूर्ण

	get_alg_config(&params.alg_prm, crypto_ahash_digestsize(rtfm));
	params.kctx_len = roundup(params.alg_prm.result_size, 16);
	अगर (is_hmac(crypto_ahash_tfm(rtfm))) अणु
		params.kctx_len *= 2;
		params.opad_needed = 1;
	पूर्ण अन्यथा अणु
		params.opad_needed = 0;
	पूर्ण

	params.sg_len = chcr_hash_ent_in_wr(req->src, !!req_ctx->reqlen,
				    HASH_SPACE_LEFT(params.kctx_len), 0);
	अगर (params.sg_len < req->nbytes) अणु
		अगर (is_hmac(crypto_ahash_tfm(rtfm))) अणु
			params.kctx_len /= 2;
			params.opad_needed = 0;
		पूर्ण
		params.last = 0;
		params.more = 1;
		params.sg_len = roundकरोwn(params.sg_len + req_ctx->reqlen, bs)
					- req_ctx->reqlen;
		params.hash_size = params.alg_prm.result_size;
		params.scmd1 = 0;
	पूर्ण अन्यथा अणु
		params.last = 1;
		params.more = 0;
		params.sg_len = req->nbytes;
		params.hash_size = crypto_ahash_digestsize(rtfm);
		params.scmd1 = req_ctx->data_len + req_ctx->reqlen +
				params.sg_len;
	पूर्ण
	params.bfr_len = req_ctx->reqlen;
	req_ctx->data_len += params.bfr_len + params.sg_len;
	req_ctx->hctx_wr.result = 1;
	req_ctx->hctx_wr.srcsg = req->src;
	अगर ((req_ctx->reqlen + req->nbytes) == 0) अणु
		create_last_hash_block(req_ctx->reqbfr, bs, req_ctx->data_len);
		params.last = 0;
		params.more = 1;
		params.scmd1 = 0;
		params.bfr_len = bs;
	पूर्ण
	skb = create_hash_wr(req, &params);
	अगर (IS_ERR(skb)) अणु
		error = PTR_ERR(skb);
		जाओ unmap;
	पूर्ण
	req_ctx->reqlen = 0;
	req_ctx->hctx_wr.processed += params.sg_len;
	skb->dev = u_ctx->lldi.ports[0];
	set_wr_txq(skb, CPL_PRIORITY_DATA, req_ctx->txqidx);
	chcr_send_wr(skb);
	वापस -EINPROGRESS;
unmap:
	chcr_hash_dma_unmap(&u_ctx->lldi.pdev->dev, req);
err:
	chcr_dec_wrcount(dev);
	वापस error;
पूर्ण

अटल पूर्णांक chcr_ahash_digest(काष्ठा ahash_request *req)
अणु
	काष्ठा chcr_ahash_req_ctx *req_ctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *rtfm = crypto_ahash_reqtfm(req);
	काष्ठा chcr_dev *dev = h_ctx(rtfm)->dev;
	काष्ठा uld_ctx *u_ctx = ULD_CTX(h_ctx(rtfm));
	काष्ठा chcr_context *ctx = h_ctx(rtfm);
	काष्ठा sk_buff *skb;
	काष्ठा hash_wr_param params;
	u8  bs;
	पूर्णांक error;
	अचिन्हित पूर्णांक cpu;

	cpu = get_cpu();
	req_ctx->txqidx = cpu % ctx->ntxq;
	req_ctx->rxqidx = cpu % ctx->nrxq;
	put_cpu();

	rtfm->init(req);
	bs = crypto_tfm_alg_blocksize(crypto_ahash_tfm(rtfm));
	error = chcr_inc_wrcount(dev);
	अगर (error)
		वापस -ENXIO;

	अगर (unlikely(cxgb4_is_crypto_q_full(u_ctx->lldi.ports[0],
						req_ctx->txqidx) &&
		(!(req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG)))) अणु
			error = -ENOSPC;
			जाओ err;
	पूर्ण

	chcr_init_hctx_per_wr(req_ctx);
	error = chcr_hash_dma_map(&u_ctx->lldi.pdev->dev, req);
	अगर (error) अणु
		error = -ENOMEM;
		जाओ err;
	पूर्ण

	get_alg_config(&params.alg_prm, crypto_ahash_digestsize(rtfm));
	params.kctx_len = roundup(params.alg_prm.result_size, 16);
	अगर (is_hmac(crypto_ahash_tfm(rtfm))) अणु
		params.kctx_len *= 2;
		params.opad_needed = 1;
	पूर्ण अन्यथा अणु
		params.opad_needed = 0;
	पूर्ण
	params.sg_len = chcr_hash_ent_in_wr(req->src, !!req_ctx->reqlen,
				HASH_SPACE_LEFT(params.kctx_len), 0);
	अगर (params.sg_len < req->nbytes) अणु
		अगर (is_hmac(crypto_ahash_tfm(rtfm))) अणु
			params.kctx_len /= 2;
			params.opad_needed = 0;
		पूर्ण
		params.last = 0;
		params.more = 1;
		params.scmd1 = 0;
		params.sg_len = roundकरोwn(params.sg_len, bs);
		params.hash_size = params.alg_prm.result_size;
	पूर्ण अन्यथा अणु
		params.sg_len = req->nbytes;
		params.hash_size = crypto_ahash_digestsize(rtfm);
		params.last = 1;
		params.more = 0;
		params.scmd1 = req->nbytes + req_ctx->data_len;

	पूर्ण
	params.bfr_len = 0;
	req_ctx->hctx_wr.result = 1;
	req_ctx->hctx_wr.srcsg = req->src;
	req_ctx->data_len += params.bfr_len + params.sg_len;

	अगर (req->nbytes == 0) अणु
		create_last_hash_block(req_ctx->reqbfr, bs, req_ctx->data_len);
		params.more = 1;
		params.bfr_len = bs;
	पूर्ण

	skb = create_hash_wr(req, &params);
	अगर (IS_ERR(skb)) अणु
		error = PTR_ERR(skb);
		जाओ unmap;
	पूर्ण
	req_ctx->hctx_wr.processed += params.sg_len;
	skb->dev = u_ctx->lldi.ports[0];
	set_wr_txq(skb, CPL_PRIORITY_DATA, req_ctx->txqidx);
	chcr_send_wr(skb);
	वापस -EINPROGRESS;
unmap:
	chcr_hash_dma_unmap(&u_ctx->lldi.pdev->dev, req);
err:
	chcr_dec_wrcount(dev);
	वापस error;
पूर्ण

अटल पूर्णांक chcr_ahash_जारी(काष्ठा ahash_request *req)
अणु
	काष्ठा chcr_ahash_req_ctx *reqctx = ahash_request_ctx(req);
	काष्ठा chcr_hctx_per_wr *hctx_wr = &reqctx->hctx_wr;
	काष्ठा crypto_ahash *rtfm = crypto_ahash_reqtfm(req);
	काष्ठा chcr_context *ctx = h_ctx(rtfm);
	काष्ठा uld_ctx *u_ctx = ULD_CTX(ctx);
	काष्ठा sk_buff *skb;
	काष्ठा hash_wr_param params;
	u8  bs;
	पूर्णांक error;
	अचिन्हित पूर्णांक cpu;

	cpu = get_cpu();
	reqctx->txqidx = cpu % ctx->ntxq;
	reqctx->rxqidx = cpu % ctx->nrxq;
	put_cpu();

	bs = crypto_tfm_alg_blocksize(crypto_ahash_tfm(rtfm));
	get_alg_config(&params.alg_prm, crypto_ahash_digestsize(rtfm));
	params.kctx_len = roundup(params.alg_prm.result_size, 16);
	अगर (is_hmac(crypto_ahash_tfm(rtfm))) अणु
		params.kctx_len *= 2;
		params.opad_needed = 1;
	पूर्ण अन्यथा अणु
		params.opad_needed = 0;
	पूर्ण
	params.sg_len = chcr_hash_ent_in_wr(hctx_wr->srcsg, 0,
					    HASH_SPACE_LEFT(params.kctx_len),
					    hctx_wr->src_ofst);
	अगर ((params.sg_len + hctx_wr->processed) > req->nbytes)
		params.sg_len = req->nbytes - hctx_wr->processed;
	अगर (!hctx_wr->result ||
	    ((params.sg_len + hctx_wr->processed) < req->nbytes)) अणु
		अगर (is_hmac(crypto_ahash_tfm(rtfm))) अणु
			params.kctx_len /= 2;
			params.opad_needed = 0;
		पूर्ण
		params.last = 0;
		params.more = 1;
		params.sg_len = roundकरोwn(params.sg_len, bs);
		params.hash_size = params.alg_prm.result_size;
		params.scmd1 = 0;
	पूर्ण अन्यथा अणु
		params.last = 1;
		params.more = 0;
		params.hash_size = crypto_ahash_digestsize(rtfm);
		params.scmd1 = reqctx->data_len + params.sg_len;
	पूर्ण
	params.bfr_len = 0;
	reqctx->data_len += params.sg_len;
	skb = create_hash_wr(req, &params);
	अगर (IS_ERR(skb)) अणु
		error = PTR_ERR(skb);
		जाओ err;
	पूर्ण
	hctx_wr->processed += params.sg_len;
	skb->dev = u_ctx->lldi.ports[0];
	set_wr_txq(skb, CPL_PRIORITY_DATA, reqctx->txqidx);
	chcr_send_wr(skb);
	वापस 0;
err:
	वापस error;
पूर्ण

अटल अंतरभूत व्योम chcr_handle_ahash_resp(काष्ठा ahash_request *req,
					  अचिन्हित अक्षर *input,
					  पूर्णांक err)
अणु
	काष्ठा chcr_ahash_req_ctx *reqctx = ahash_request_ctx(req);
	काष्ठा chcr_hctx_per_wr *hctx_wr = &reqctx->hctx_wr;
	पूर्णांक digestsize, updated_digestsize;
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा uld_ctx *u_ctx = ULD_CTX(h_ctx(tfm));
	काष्ठा chcr_dev *dev = h_ctx(tfm)->dev;

	अगर (input == शून्य)
		जाओ out;
	digestsize = crypto_ahash_digestsize(crypto_ahash_reqtfm(req));
	updated_digestsize = digestsize;
	अगर (digestsize == SHA224_DIGEST_SIZE)
		updated_digestsize = SHA256_DIGEST_SIZE;
	अन्यथा अगर (digestsize == SHA384_DIGEST_SIZE)
		updated_digestsize = SHA512_DIGEST_SIZE;

	अगर (hctx_wr->dma_addr) अणु
		dma_unmap_single(&u_ctx->lldi.pdev->dev, hctx_wr->dma_addr,
				 hctx_wr->dma_len, DMA_TO_DEVICE);
		hctx_wr->dma_addr = 0;
	पूर्ण
	अगर (hctx_wr->isfinal || ((hctx_wr->processed + reqctx->reqlen) ==
				 req->nbytes)) अणु
		अगर (hctx_wr->result == 1) अणु
			hctx_wr->result = 0;
			स_नकल(req->result, input + माप(काष्ठा cpl_fw6_pld),
			       digestsize);
		पूर्ण अन्यथा अणु
			स_नकल(reqctx->partial_hash,
			       input + माप(काष्ठा cpl_fw6_pld),
			       updated_digestsize);

		पूर्ण
		जाओ unmap;
	पूर्ण
	स_नकल(reqctx->partial_hash, input + माप(काष्ठा cpl_fw6_pld),
	       updated_digestsize);

	err = chcr_ahash_जारी(req);
	अगर (err)
		जाओ unmap;
	वापस;
unmap:
	अगर (hctx_wr->is_sg_map)
		chcr_hash_dma_unmap(&u_ctx->lldi.pdev->dev, req);


out:
	chcr_dec_wrcount(dev);
	req->base.complete(&req->base, err);
पूर्ण

/*
 *	chcr_handle_resp - Unmap the DMA buffers associated with the request
 *	@req: crypto request
 */
पूर्णांक chcr_handle_resp(काष्ठा crypto_async_request *req, अचिन्हित अक्षर *input,
			 पूर्णांक err)
अणु
	काष्ठा crypto_tfm *tfm = req->tfm;
	काष्ठा chcr_context *ctx = crypto_tfm_ctx(tfm);
	काष्ठा adapter *adap = padap(ctx->dev);

	चयन (tfm->__crt_alg->cra_flags & CRYPTO_ALG_TYPE_MASK) अणु
	हाल CRYPTO_ALG_TYPE_AEAD:
		err = chcr_handle_aead_resp(aead_request_cast(req), input, err);
		अवरोध;

	हाल CRYPTO_ALG_TYPE_SKCIPHER:
		 chcr_handle_cipher_resp(skcipher_request_cast(req),
					       input, err);
		अवरोध;
	हाल CRYPTO_ALG_TYPE_AHASH:
		chcr_handle_ahash_resp(ahash_request_cast(req), input, err);
		पूर्ण
	atomic_inc(&adap->chcr_stats.complete);
	वापस err;
पूर्ण
अटल पूर्णांक chcr_ahash_export(काष्ठा ahash_request *areq, व्योम *out)
अणु
	काष्ठा chcr_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);
	काष्ठा chcr_ahash_req_ctx *state = out;

	state->reqlen = req_ctx->reqlen;
	state->data_len = req_ctx->data_len;
	स_नकल(state->bfr1, req_ctx->reqbfr, req_ctx->reqlen);
	स_नकल(state->partial_hash, req_ctx->partial_hash,
	       CHCR_HASH_MAX_DIGEST_SIZE);
	chcr_init_hctx_per_wr(state);
	वापस 0;
पूर्ण

अटल पूर्णांक chcr_ahash_import(काष्ठा ahash_request *areq, स्थिर व्योम *in)
अणु
	काष्ठा chcr_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);
	काष्ठा chcr_ahash_req_ctx *state = (काष्ठा chcr_ahash_req_ctx *)in;

	req_ctx->reqlen = state->reqlen;
	req_ctx->data_len = state->data_len;
	req_ctx->reqbfr = req_ctx->bfr1;
	req_ctx->skbfr = req_ctx->bfr2;
	स_नकल(req_ctx->bfr1, state->bfr1, CHCR_HASH_MAX_BLOCK_SIZE_128);
	स_नकल(req_ctx->partial_hash, state->partial_hash,
	       CHCR_HASH_MAX_DIGEST_SIZE);
	chcr_init_hctx_per_wr(req_ctx);
	वापस 0;
पूर्ण

अटल पूर्णांक chcr_ahash_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
			     अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा hmac_ctx *hmacctx = HMAC_CTX(h_ctx(tfm));
	अचिन्हित पूर्णांक digestsize = crypto_ahash_digestsize(tfm);
	अचिन्हित पूर्णांक bs = crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));
	अचिन्हित पूर्णांक i, err = 0, updated_digestsize;

	SHASH_DESC_ON_STACK(shash, hmacctx->base_hash);

	/* use the key to calculate the ipad and opad. ipad will sent with the
	 * first request's data. opad will be sent with the final hash result
	 * ipad in hmacctx->ipad and opad in hmacctx->opad location
	 */
	shash->tfm = hmacctx->base_hash;
	अगर (keylen > bs) अणु
		err = crypto_shash_digest(shash, key, keylen,
					  hmacctx->ipad);
		अगर (err)
			जाओ out;
		keylen = digestsize;
	पूर्ण अन्यथा अणु
		स_नकल(hmacctx->ipad, key, keylen);
	पूर्ण
	स_रखो(hmacctx->ipad + keylen, 0, bs - keylen);
	स_नकल(hmacctx->opad, hmacctx->ipad, bs);

	क्रम (i = 0; i < bs / माप(पूर्णांक); i++) अणु
		*((अचिन्हित पूर्णांक *)(&hmacctx->ipad) + i) ^= IPAD_DATA;
		*((अचिन्हित पूर्णांक *)(&hmacctx->opad) + i) ^= OPAD_DATA;
	पूर्ण

	updated_digestsize = digestsize;
	अगर (digestsize == SHA224_DIGEST_SIZE)
		updated_digestsize = SHA256_DIGEST_SIZE;
	अन्यथा अगर (digestsize == SHA384_DIGEST_SIZE)
		updated_digestsize = SHA512_DIGEST_SIZE;
	err = chcr_compute_partial_hash(shash, hmacctx->ipad,
					hmacctx->ipad, digestsize);
	अगर (err)
		जाओ out;
	chcr_change_order(hmacctx->ipad, updated_digestsize);

	err = chcr_compute_partial_hash(shash, hmacctx->opad,
					hmacctx->opad, digestsize);
	अगर (err)
		जाओ out;
	chcr_change_order(hmacctx->opad, updated_digestsize);
out:
	वापस err;
पूर्ण

अटल पूर्णांक chcr_aes_xts_setkey(काष्ठा crypto_skcipher *cipher, स्थिर u8 *key,
			       अचिन्हित पूर्णांक key_len)
अणु
	काष्ठा ablk_ctx *ablkctx = ABLK_CTX(c_ctx(cipher));
	अचिन्हित लघु context_size = 0;
	पूर्णांक err;

	err = chcr_cipher_fallback_setkey(cipher, key, key_len);
	अगर (err)
		जाओ badkey_err;

	स_नकल(ablkctx->key, key, key_len);
	ablkctx->enckey_len = key_len;
	get_aes_decrypt_key(ablkctx->rrkey, ablkctx->key, key_len << 2);
	context_size = (KEY_CONTEXT_HDR_SALT_AND_PAD + key_len) >> 4;
	/* Both keys क्रम xts must be aligned to 16 byte boundary
	 * by padding with zeros. So क्रम 24 byte keys padding 8 zeroes.
	 */
	अगर (key_len == 48) अणु
		context_size = (KEY_CONTEXT_HDR_SALT_AND_PAD + key_len
				+ 16) >> 4;
		स_हटाओ(ablkctx->key + 32, ablkctx->key + 24, 24);
		स_रखो(ablkctx->key + 24, 0, 8);
		स_रखो(ablkctx->key + 56, 0, 8);
		ablkctx->enckey_len = 64;
		ablkctx->key_ctx_hdr =
			FILL_KEY_CTX_HDR(CHCR_KEYCTX_CIPHER_KEY_SIZE_192,
					 CHCR_KEYCTX_NO_KEY, 1,
					 0, context_size);
	पूर्ण अन्यथा अणु
		ablkctx->key_ctx_hdr =
		FILL_KEY_CTX_HDR((key_len == AES_KEYSIZE_256) ?
				 CHCR_KEYCTX_CIPHER_KEY_SIZE_128 :
				 CHCR_KEYCTX_CIPHER_KEY_SIZE_256,
				 CHCR_KEYCTX_NO_KEY, 1,
				 0, context_size);
	पूर्ण
	ablkctx->ciph_mode = CHCR_SCMD_CIPHER_MODE_AES_XTS;
	वापस 0;
badkey_err:
	ablkctx->enckey_len = 0;

	वापस err;
पूर्ण

अटल पूर्णांक chcr_sha_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा chcr_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	पूर्णांक digestsize =  crypto_ahash_digestsize(tfm);

	req_ctx->data_len = 0;
	req_ctx->reqlen = 0;
	req_ctx->reqbfr = req_ctx->bfr1;
	req_ctx->skbfr = req_ctx->bfr2;
	copy_hash_init_values(req_ctx->partial_hash, digestsize);

	वापस 0;
पूर्ण

अटल पूर्णांक chcr_sha_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा chcr_ahash_req_ctx));
	वापस chcr_device_init(crypto_tfm_ctx(tfm));
पूर्ण

अटल पूर्णांक chcr_hmac_init(काष्ठा ahash_request *areq)
अणु
	काष्ठा chcr_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);
	काष्ठा crypto_ahash *rtfm = crypto_ahash_reqtfm(areq);
	काष्ठा hmac_ctx *hmacctx = HMAC_CTX(h_ctx(rtfm));
	अचिन्हित पूर्णांक digestsize = crypto_ahash_digestsize(rtfm);
	अचिन्हित पूर्णांक bs = crypto_tfm_alg_blocksize(crypto_ahash_tfm(rtfm));

	chcr_sha_init(areq);
	req_ctx->data_len = bs;
	अगर (is_hmac(crypto_ahash_tfm(rtfm))) अणु
		अगर (digestsize == SHA224_DIGEST_SIZE)
			स_नकल(req_ctx->partial_hash, hmacctx->ipad,
			       SHA256_DIGEST_SIZE);
		अन्यथा अगर (digestsize == SHA384_DIGEST_SIZE)
			स_नकल(req_ctx->partial_hash, hmacctx->ipad,
			       SHA512_DIGEST_SIZE);
		अन्यथा
			स_नकल(req_ctx->partial_hash, hmacctx->ipad,
			       digestsize);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक chcr_hmac_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा chcr_context *ctx = crypto_tfm_ctx(tfm);
	काष्ठा hmac_ctx *hmacctx = HMAC_CTX(ctx);
	अचिन्हित पूर्णांक digestsize =
		crypto_ahash_digestsize(__crypto_ahash_cast(tfm));

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा chcr_ahash_req_ctx));
	hmacctx->base_hash = chcr_alloc_shash(digestsize);
	अगर (IS_ERR(hmacctx->base_hash))
		वापस PTR_ERR(hmacctx->base_hash);
	वापस chcr_device_init(crypto_tfm_ctx(tfm));
पूर्ण

अटल व्योम chcr_hmac_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा chcr_context *ctx = crypto_tfm_ctx(tfm);
	काष्ठा hmac_ctx *hmacctx = HMAC_CTX(ctx);

	अगर (hmacctx->base_hash) अणु
		chcr_मुक्त_shash(hmacctx->base_hash);
		hmacctx->base_hash = शून्य;
	पूर्ण
पूर्ण

अंतरभूत व्योम chcr_aead_common_निकास(काष्ठा aead_request *req)
अणु
	काष्ठा chcr_aead_reqctx  *reqctx = aead_request_ctx(req);
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा uld_ctx *u_ctx = ULD_CTX(a_ctx(tfm));

	chcr_aead_dma_unmap(&u_ctx->lldi.pdev->dev, req, reqctx->op);
पूर्ण

अटल पूर्णांक chcr_aead_common_init(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));
	काष्ठा chcr_aead_reqctx  *reqctx = aead_request_ctx(req);
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(tfm);
	पूर्णांक error = -EINVAL;

	/* validate key size */
	अगर (aeadctx->enckey_len == 0)
		जाओ err;
	अगर (reqctx->op && req->cryptlen < authsize)
		जाओ err;
	अगर (reqctx->b0_len)
		reqctx->scratch_pad = reqctx->iv + IV;
	अन्यथा
		reqctx->scratch_pad = शून्य;

	error = chcr_aead_dma_map(&ULD_CTX(a_ctx(tfm))->lldi.pdev->dev, req,
				  reqctx->op);
	अगर (error) अणु
		error = -ENOMEM;
		जाओ err;
	पूर्ण

	वापस 0;
err:
	वापस error;
पूर्ण

अटल पूर्णांक chcr_aead_need_fallback(काष्ठा aead_request *req, पूर्णांक dst_nents,
				   पूर्णांक aadmax, पूर्णांक wrlen,
				   अचिन्हित लघु op_type)
अणु
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(crypto_aead_reqtfm(req));

	अगर (((req->cryptlen - (op_type ? authsize : 0)) == 0) ||
	    dst_nents > MAX_DSGL_ENT ||
	    (req->assoclen > aadmax) ||
	    (wrlen > SGE_MAX_WR_LEN))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक chcr_aead_fallback(काष्ठा aead_request *req, अचिन्हित लघु op_type)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));
	काष्ठा aead_request *subreq = aead_request_ctx(req);

	aead_request_set_tfm(subreq, aeadctx->sw_cipher);
	aead_request_set_callback(subreq, req->base.flags,
				  req->base.complete, req->base.data);
	aead_request_set_crypt(subreq, req->src, req->dst, req->cryptlen,
				 req->iv);
	aead_request_set_ad(subreq, req->assoclen);
	वापस op_type ? crypto_aead_decrypt(subreq) :
		crypto_aead_encrypt(subreq);
पूर्ण

अटल काष्ठा sk_buff *create_authenc_wr(काष्ठा aead_request *req,
					 अचिन्हित लघु qid,
					 पूर्णांक size)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा chcr_context *ctx = a_ctx(tfm);
	काष्ठा uld_ctx *u_ctx = ULD_CTX(ctx);
	काष्ठा chcr_aead_ctx *aeadctx = AEAD_CTX(ctx);
	काष्ठा chcr_authenc_ctx *actx = AUTHENC_CTX(aeadctx);
	काष्ठा chcr_aead_reqctx *reqctx = aead_request_ctx(req);
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा chcr_wr *chcr_req;
	काष्ठा cpl_rx_phys_dsgl *phys_cpl;
	काष्ठा ulptx_sgl *ulptx;
	अचिन्हित पूर्णांक transhdr_len;
	अचिन्हित पूर्णांक dst_size = 0, temp, subtype = get_aead_subtype(tfm);
	अचिन्हित पूर्णांक   kctx_len = 0, dnents, snents;
	अचिन्हित पूर्णांक  authsize = crypto_aead_authsize(tfm);
	पूर्णांक error = -EINVAL;
	u8 *ivptr;
	पूर्णांक null = 0;
	gfp_t flags = req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP ? GFP_KERNEL :
		GFP_ATOMIC;
	काष्ठा adapter *adap = padap(ctx->dev);
	अचिन्हित पूर्णांक rx_channel_id = reqctx->rxqidx / ctx->rxq_perchan;

	rx_channel_id = cxgb4_port_e2cchan(u_ctx->lldi.ports[rx_channel_id]);
	अगर (req->cryptlen == 0)
		वापस शून्य;

	reqctx->b0_len = 0;
	error = chcr_aead_common_init(req);
	अगर (error)
		वापस ERR_PTR(error);

	अगर (subtype == CRYPTO_ALG_SUB_TYPE_CBC_शून्य ||
		subtype == CRYPTO_ALG_SUB_TYPE_CTR_शून्य) अणु
		null = 1;
	पूर्ण
	dnents = sg_nents_xlen(req->dst, req->assoclen + req->cryptlen +
		(reqctx->op ? -authsize : authsize), CHCR_DST_SG_SIZE, 0);
	dnents += MIN_AUTH_SG; // For IV
	snents = sg_nents_xlen(req->src, req->assoclen + req->cryptlen,
			       CHCR_SRC_SG_SIZE, 0);
	dst_size = get_space_क्रम_phys_dsgl(dnents);
	kctx_len = (KEY_CONTEXT_CTX_LEN_G(ntohl(aeadctx->key_ctx_hdr)) << 4)
		- माप(chcr_req->key_ctx);
	transhdr_len = CIPHER_TRANSHDR_SIZE(kctx_len, dst_size);
	reqctx->imm = (transhdr_len + req->assoclen + req->cryptlen) <
			SGE_MAX_WR_LEN;
	temp = reqctx->imm ? roundup(req->assoclen + req->cryptlen, 16)
			: (sgl_len(snents) * 8);
	transhdr_len += temp;
	transhdr_len = roundup(transhdr_len, 16);

	अगर (chcr_aead_need_fallback(req, dnents, T6_MAX_AAD_SIZE,
				    transhdr_len, reqctx->op)) अणु
		atomic_inc(&adap->chcr_stats.fallback);
		chcr_aead_common_निकास(req);
		वापस ERR_PTR(chcr_aead_fallback(req, reqctx->op));
	पूर्ण
	skb = alloc_skb(transhdr_len, flags);
	अगर (!skb) अणु
		error = -ENOMEM;
		जाओ err;
	पूर्ण

	chcr_req = __skb_put_zero(skb, transhdr_len);

	temp  = (reqctx->op == CHCR_ENCRYPT_OP) ? 0 : authsize;

	/*
	 * Input order	is AAD,IV and Payload. where IV should be included as
	 * the part of authdata. All other fields should be filled according
	 * to the hardware spec
	 */
	chcr_req->sec_cpl.op_ivinsrtofst =
				FILL_SEC_CPL_OP_IVINSR(rx_channel_id, 2, 1);
	chcr_req->sec_cpl.pldlen = htonl(req->assoclen + IV + req->cryptlen);
	chcr_req->sec_cpl.aadstart_cipherstop_hi = FILL_SEC_CPL_CIPHERSTOP_HI(
					null ? 0 : 1 + IV,
					null ? 0 : IV + req->assoclen,
					req->assoclen + IV + 1,
					(temp & 0x1F0) >> 4);
	chcr_req->sec_cpl.cipherstop_lo_authinsert = FILL_SEC_CPL_AUTHINSERT(
					temp & 0xF,
					null ? 0 : req->assoclen + IV + 1,
					temp, temp);
	अगर (subtype == CRYPTO_ALG_SUB_TYPE_CTR_शून्य ||
	    subtype == CRYPTO_ALG_SUB_TYPE_CTR_SHA)
		temp = CHCR_SCMD_CIPHER_MODE_AES_CTR;
	अन्यथा
		temp = CHCR_SCMD_CIPHER_MODE_AES_CBC;
	chcr_req->sec_cpl.seqno_numivs = FILL_SEC_CPL_SCMD0_SEQNO(reqctx->op,
					(reqctx->op == CHCR_ENCRYPT_OP) ? 1 : 0,
					temp,
					actx->auth_mode, aeadctx->hmac_ctrl,
					IV >> 1);
	chcr_req->sec_cpl.ivgen_hdrlen =  FILL_SEC_CPL_IVGEN_HDRLEN(0, 0, 1,
					 0, 0, dst_size);

	chcr_req->key_ctx.ctx_hdr = aeadctx->key_ctx_hdr;
	अगर (reqctx->op == CHCR_ENCRYPT_OP ||
		subtype == CRYPTO_ALG_SUB_TYPE_CTR_SHA ||
		subtype == CRYPTO_ALG_SUB_TYPE_CTR_शून्य)
		स_नकल(chcr_req->key_ctx.key, aeadctx->key,
		       aeadctx->enckey_len);
	अन्यथा
		स_नकल(chcr_req->key_ctx.key, actx->dec_rrkey,
		       aeadctx->enckey_len);

	स_नकल(chcr_req->key_ctx.key + roundup(aeadctx->enckey_len, 16),
	       actx->h_iopad, kctx_len - roundup(aeadctx->enckey_len, 16));
	phys_cpl = (काष्ठा cpl_rx_phys_dsgl *)((u8 *)(chcr_req + 1) + kctx_len);
	ivptr = (u8 *)(phys_cpl + 1) + dst_size;
	ulptx = (काष्ठा ulptx_sgl *)(ivptr + IV);
	अगर (subtype == CRYPTO_ALG_SUB_TYPE_CTR_SHA ||
	    subtype == CRYPTO_ALG_SUB_TYPE_CTR_शून्य) अणु
		स_नकल(ivptr, aeadctx->nonce, CTR_RFC3686_NONCE_SIZE);
		स_नकल(ivptr + CTR_RFC3686_NONCE_SIZE, req->iv,
				CTR_RFC3686_IV_SIZE);
		*(__be32 *)(ivptr + CTR_RFC3686_NONCE_SIZE +
			CTR_RFC3686_IV_SIZE) = cpu_to_be32(1);
	पूर्ण अन्यथा अणु
		स_नकल(ivptr, req->iv, IV);
	पूर्ण
	chcr_add_aead_dst_ent(req, phys_cpl, qid);
	chcr_add_aead_src_ent(req, ulptx);
	atomic_inc(&adap->chcr_stats.cipher_rqst);
	temp = माप(काष्ठा cpl_rx_phys_dsgl) + dst_size + IV +
		kctx_len + (reqctx->imm ? (req->assoclen + req->cryptlen) : 0);
	create_wreq(a_ctx(tfm), chcr_req, &req->base, reqctx->imm, size,
		   transhdr_len, temp, 0);
	reqctx->skb = skb;

	वापस skb;
err:
	chcr_aead_common_निकास(req);

	वापस ERR_PTR(error);
पूर्ण

पूर्णांक chcr_aead_dma_map(काष्ठा device *dev,
		      काष्ठा aead_request *req,
		      अचिन्हित लघु op_type)
अणु
	पूर्णांक error;
	काष्ठा chcr_aead_reqctx  *reqctx = aead_request_ctx(req);
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(tfm);
	पूर्णांक src_len, dst_len;

	/* calculate and handle src and dst sg length separately
	 * क्रम inplace and out-of place operations
	 */
	अगर (req->src == req->dst) अणु
		src_len = req->assoclen + req->cryptlen + (op_type ?
							0 : authsize);
		dst_len = src_len;
	पूर्ण अन्यथा अणु
		src_len = req->assoclen + req->cryptlen;
		dst_len = req->assoclen + req->cryptlen + (op_type ?
							-authsize : authsize);
	पूर्ण

	अगर (!req->cryptlen || !src_len || !dst_len)
		वापस 0;
	reqctx->iv_dma = dma_map_single(dev, reqctx->iv, (IV + reqctx->b0_len),
					DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, reqctx->iv_dma))
		वापस -ENOMEM;
	अगर (reqctx->b0_len)
		reqctx->b0_dma = reqctx->iv_dma + IV;
	अन्यथा
		reqctx->b0_dma = 0;
	अगर (req->src == req->dst) अणु
		error = dma_map_sg(dev, req->src,
				sg_nents_क्रम_len(req->src, src_len),
					DMA_BIसूचीECTIONAL);
		अगर (!error)
			जाओ err;
	पूर्ण अन्यथा अणु
		error = dma_map_sg(dev, req->src,
				   sg_nents_क्रम_len(req->src, src_len),
				   DMA_TO_DEVICE);
		अगर (!error)
			जाओ err;
		error = dma_map_sg(dev, req->dst,
				   sg_nents_क्रम_len(req->dst, dst_len),
				   DMA_FROM_DEVICE);
		अगर (!error) अणु
			dma_unmap_sg(dev, req->src,
				     sg_nents_क्रम_len(req->src, src_len),
				     DMA_TO_DEVICE);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;
err:
	dma_unmap_single(dev, reqctx->iv_dma, IV, DMA_BIसूचीECTIONAL);
	वापस -ENOMEM;
पूर्ण

व्योम chcr_aead_dma_unmap(काष्ठा device *dev,
			 काष्ठा aead_request *req,
			 अचिन्हित लघु op_type)
अणु
	काष्ठा chcr_aead_reqctx  *reqctx = aead_request_ctx(req);
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(tfm);
	पूर्णांक src_len, dst_len;

	/* calculate and handle src and dst sg length separately
	 * क्रम inplace and out-of place operations
	 */
	अगर (req->src == req->dst) अणु
		src_len = req->assoclen + req->cryptlen + (op_type ?
							0 : authsize);
		dst_len = src_len;
	पूर्ण अन्यथा अणु
		src_len = req->assoclen + req->cryptlen;
		dst_len = req->assoclen + req->cryptlen + (op_type ?
						-authsize : authsize);
	पूर्ण

	अगर (!req->cryptlen || !src_len || !dst_len)
		वापस;

	dma_unmap_single(dev, reqctx->iv_dma, (IV + reqctx->b0_len),
					DMA_BIसूचीECTIONAL);
	अगर (req->src == req->dst) अणु
		dma_unmap_sg(dev, req->src,
			     sg_nents_क्रम_len(req->src, src_len),
			     DMA_BIसूचीECTIONAL);
	पूर्ण अन्यथा अणु
		dma_unmap_sg(dev, req->src,
			     sg_nents_क्रम_len(req->src, src_len),
			     DMA_TO_DEVICE);
		dma_unmap_sg(dev, req->dst,
			     sg_nents_क्रम_len(req->dst, dst_len),
			     DMA_FROM_DEVICE);
	पूर्ण
पूर्ण

व्योम chcr_add_aead_src_ent(काष्ठा aead_request *req,
			   काष्ठा ulptx_sgl *ulptx)
अणु
	काष्ठा ulptx_walk ulp_walk;
	काष्ठा chcr_aead_reqctx  *reqctx = aead_request_ctx(req);

	अगर (reqctx->imm) अणु
		u8 *buf = (u8 *)ulptx;

		अगर (reqctx->b0_len) अणु
			स_नकल(buf, reqctx->scratch_pad, reqctx->b0_len);
			buf += reqctx->b0_len;
		पूर्ण
		sg_pcopy_to_buffer(req->src, sg_nents(req->src),
				   buf, req->cryptlen + req->assoclen, 0);
	पूर्ण अन्यथा अणु
		ulptx_walk_init(&ulp_walk, ulptx);
		अगर (reqctx->b0_len)
			ulptx_walk_add_page(&ulp_walk, reqctx->b0_len,
					    reqctx->b0_dma);
		ulptx_walk_add_sg(&ulp_walk, req->src, req->cryptlen +
				  req->assoclen,  0);
		ulptx_walk_end(&ulp_walk);
	पूर्ण
पूर्ण

व्योम chcr_add_aead_dst_ent(काष्ठा aead_request *req,
			   काष्ठा cpl_rx_phys_dsgl *phys_cpl,
			   अचिन्हित लघु qid)
अणु
	काष्ठा chcr_aead_reqctx  *reqctx = aead_request_ctx(req);
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा dsgl_walk dsgl_walk;
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(tfm);
	काष्ठा chcr_context *ctx = a_ctx(tfm);
	काष्ठा uld_ctx *u_ctx = ULD_CTX(ctx);
	u32 temp;
	अचिन्हित पूर्णांक rx_channel_id = reqctx->rxqidx / ctx->rxq_perchan;

	rx_channel_id = cxgb4_port_e2cchan(u_ctx->lldi.ports[rx_channel_id]);
	dsgl_walk_init(&dsgl_walk, phys_cpl);
	dsgl_walk_add_page(&dsgl_walk, IV + reqctx->b0_len, reqctx->iv_dma);
	temp = req->assoclen + req->cryptlen +
		(reqctx->op ? -authsize : authsize);
	dsgl_walk_add_sg(&dsgl_walk, req->dst, temp, 0);
	dsgl_walk_end(&dsgl_walk, qid, rx_channel_id);
पूर्ण

व्योम chcr_add_cipher_src_ent(काष्ठा skcipher_request *req,
			     व्योम *ulptx,
			     काष्ठा  cipher_wr_param *wrparam)
अणु
	काष्ठा ulptx_walk ulp_walk;
	काष्ठा chcr_skcipher_req_ctx *reqctx = skcipher_request_ctx(req);
	u8 *buf = ulptx;

	स_नकल(buf, reqctx->iv, IV);
	buf += IV;
	अगर (reqctx->imm) अणु
		sg_pcopy_to_buffer(req->src, sg_nents(req->src),
				   buf, wrparam->bytes, reqctx->processed);
	पूर्ण अन्यथा अणु
		ulptx_walk_init(&ulp_walk, (काष्ठा ulptx_sgl *)buf);
		ulptx_walk_add_sg(&ulp_walk, reqctx->srcsg, wrparam->bytes,
				  reqctx->src_ofst);
		reqctx->srcsg = ulp_walk.last_sg;
		reqctx->src_ofst = ulp_walk.last_sg_len;
		ulptx_walk_end(&ulp_walk);
	पूर्ण
पूर्ण

व्योम chcr_add_cipher_dst_ent(काष्ठा skcipher_request *req,
			     काष्ठा cpl_rx_phys_dsgl *phys_cpl,
			     काष्ठा  cipher_wr_param *wrparam,
			     अचिन्हित लघु qid)
अणु
	काष्ठा chcr_skcipher_req_ctx *reqctx = skcipher_request_ctx(req);
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(wrparam->req);
	काष्ठा chcr_context *ctx = c_ctx(tfm);
	काष्ठा uld_ctx *u_ctx = ULD_CTX(ctx);
	काष्ठा dsgl_walk dsgl_walk;
	अचिन्हित पूर्णांक rx_channel_id = reqctx->rxqidx / ctx->rxq_perchan;

	rx_channel_id = cxgb4_port_e2cchan(u_ctx->lldi.ports[rx_channel_id]);
	dsgl_walk_init(&dsgl_walk, phys_cpl);
	dsgl_walk_add_sg(&dsgl_walk, reqctx->dstsg, wrparam->bytes,
			 reqctx->dst_ofst);
	reqctx->dstsg = dsgl_walk.last_sg;
	reqctx->dst_ofst = dsgl_walk.last_sg_len;
	dsgl_walk_end(&dsgl_walk, qid, rx_channel_id);
पूर्ण

व्योम chcr_add_hash_src_ent(काष्ठा ahash_request *req,
			   काष्ठा ulptx_sgl *ulptx,
			   काष्ठा hash_wr_param *param)
अणु
	काष्ठा ulptx_walk ulp_walk;
	काष्ठा chcr_ahash_req_ctx *reqctx = ahash_request_ctx(req);

	अगर (reqctx->hctx_wr.imm) अणु
		u8 *buf = (u8 *)ulptx;

		अगर (param->bfr_len) अणु
			स_नकल(buf, reqctx->reqbfr, param->bfr_len);
			buf += param->bfr_len;
		पूर्ण

		sg_pcopy_to_buffer(reqctx->hctx_wr.srcsg,
				   sg_nents(reqctx->hctx_wr.srcsg), buf,
				   param->sg_len, 0);
	पूर्ण अन्यथा अणु
		ulptx_walk_init(&ulp_walk, ulptx);
		अगर (param->bfr_len)
			ulptx_walk_add_page(&ulp_walk, param->bfr_len,
					    reqctx->hctx_wr.dma_addr);
		ulptx_walk_add_sg(&ulp_walk, reqctx->hctx_wr.srcsg,
				  param->sg_len, reqctx->hctx_wr.src_ofst);
		reqctx->hctx_wr.srcsg = ulp_walk.last_sg;
		reqctx->hctx_wr.src_ofst = ulp_walk.last_sg_len;
		ulptx_walk_end(&ulp_walk);
	पूर्ण
पूर्ण

पूर्णांक chcr_hash_dma_map(काष्ठा device *dev,
		      काष्ठा ahash_request *req)
अणु
	काष्ठा chcr_ahash_req_ctx *req_ctx = ahash_request_ctx(req);
	पूर्णांक error = 0;

	अगर (!req->nbytes)
		वापस 0;
	error = dma_map_sg(dev, req->src, sg_nents(req->src),
			   DMA_TO_DEVICE);
	अगर (!error)
		वापस -ENOMEM;
	req_ctx->hctx_wr.is_sg_map = 1;
	वापस 0;
पूर्ण

व्योम chcr_hash_dma_unmap(काष्ठा device *dev,
			 काष्ठा ahash_request *req)
अणु
	काष्ठा chcr_ahash_req_ctx *req_ctx = ahash_request_ctx(req);

	अगर (!req->nbytes)
		वापस;

	dma_unmap_sg(dev, req->src, sg_nents(req->src),
			   DMA_TO_DEVICE);
	req_ctx->hctx_wr.is_sg_map = 0;

पूर्ण

पूर्णांक chcr_cipher_dma_map(काष्ठा device *dev,
			काष्ठा skcipher_request *req)
अणु
	पूर्णांक error;

	अगर (req->src == req->dst) अणु
		error = dma_map_sg(dev, req->src, sg_nents(req->src),
				   DMA_BIसूचीECTIONAL);
		अगर (!error)
			जाओ err;
	पूर्ण अन्यथा अणु
		error = dma_map_sg(dev, req->src, sg_nents(req->src),
				   DMA_TO_DEVICE);
		अगर (!error)
			जाओ err;
		error = dma_map_sg(dev, req->dst, sg_nents(req->dst),
				   DMA_FROM_DEVICE);
		अगर (!error) अणु
			dma_unmap_sg(dev, req->src, sg_nents(req->src),
				   DMA_TO_DEVICE);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;
err:
	वापस -ENOMEM;
पूर्ण

व्योम chcr_cipher_dma_unmap(काष्ठा device *dev,
			   काष्ठा skcipher_request *req)
अणु
	अगर (req->src == req->dst) अणु
		dma_unmap_sg(dev, req->src, sg_nents(req->src),
				   DMA_BIसूचीECTIONAL);
	पूर्ण अन्यथा अणु
		dma_unmap_sg(dev, req->src, sg_nents(req->src),
				   DMA_TO_DEVICE);
		dma_unmap_sg(dev, req->dst, sg_nents(req->dst),
				   DMA_FROM_DEVICE);
	पूर्ण
पूर्ण

अटल पूर्णांक set_msg_len(u8 *block, अचिन्हित पूर्णांक msglen, पूर्णांक csize)
अणु
	__be32 data;

	स_रखो(block, 0, csize);
	block += csize;

	अगर (csize >= 4)
		csize = 4;
	अन्यथा अगर (msglen > (अचिन्हित पूर्णांक)(1 << (8 * csize)))
		वापस -EOVERFLOW;

	data = cpu_to_be32(msglen);
	स_नकल(block - csize, (u8 *)&data + 4 - csize, csize);

	वापस 0;
पूर्ण

अटल पूर्णांक generate_b0(काष्ठा aead_request *req, u8 *ivptr,
			अचिन्हित लघु op_type)
अणु
	अचिन्हित पूर्णांक l, lp, m;
	पूर्णांक rc;
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा chcr_aead_reqctx *reqctx = aead_request_ctx(req);
	u8 *b0 = reqctx->scratch_pad;

	m = crypto_aead_authsize(aead);

	स_नकल(b0, ivptr, 16);

	lp = b0[0];
	l = lp + 1;

	/* set m, bits 3-5 */
	*b0 |= (8 * ((m - 2) / 2));

	/* set adata, bit 6, अगर associated data is used */
	अगर (req->assoclen)
		*b0 |= 64;
	rc = set_msg_len(b0 + 16 - l,
			 (op_type == CHCR_DECRYPT_OP) ?
			 req->cryptlen - m : req->cryptlen, l);

	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक crypto_ccm_check_iv(स्थिर u8 *iv)
अणु
	/* 2 <= L <= 8, so 1 <= L' <= 7. */
	अगर (iv[0] < 1 || iv[0] > 7)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक ccm_क्रमmat_packet(काष्ठा aead_request *req,
			     u8 *ivptr,
			     अचिन्हित पूर्णांक sub_type,
			     अचिन्हित लघु op_type,
			     अचिन्हित पूर्णांक assoclen)
अणु
	काष्ठा chcr_aead_reqctx *reqctx = aead_request_ctx(req);
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));
	पूर्णांक rc = 0;

	अगर (sub_type == CRYPTO_ALG_SUB_TYPE_AEAD_RFC4309) अणु
		ivptr[0] = 3;
		स_नकल(ivptr + 1, &aeadctx->salt[0], 3);
		स_नकल(ivptr + 4, req->iv, 8);
		स_रखो(ivptr + 12, 0, 4);
	पूर्ण अन्यथा अणु
		स_नकल(ivptr, req->iv, 16);
	पूर्ण
	अगर (assoclen)
		put_unaligned_be16(assoclen, &reqctx->scratch_pad[16]);

	rc = generate_b0(req, ivptr, op_type);
	/* zero the ctr value */
	स_रखो(ivptr + 15 - ivptr[0], 0, ivptr[0] + 1);
	वापस rc;
पूर्ण

अटल व्योम fill_sec_cpl_क्रम_aead(काष्ठा cpl_tx_sec_pdu *sec_cpl,
				  अचिन्हित पूर्णांक dst_size,
				  काष्ठा aead_request *req,
				  अचिन्हित लघु op_type)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा chcr_context *ctx = a_ctx(tfm);
	काष्ठा uld_ctx *u_ctx = ULD_CTX(ctx);
	काष्ठा chcr_aead_ctx *aeadctx = AEAD_CTX(ctx);
	काष्ठा chcr_aead_reqctx *reqctx = aead_request_ctx(req);
	अचिन्हित पूर्णांक cipher_mode = CHCR_SCMD_CIPHER_MODE_AES_CCM;
	अचिन्हित पूर्णांक mac_mode = CHCR_SCMD_AUTH_MODE_CBCMAC;
	अचिन्हित पूर्णांक rx_channel_id = reqctx->rxqidx / ctx->rxq_perchan;
	अचिन्हित पूर्णांक ccm_xtra;
	अचिन्हित पूर्णांक tag_offset = 0, auth_offset = 0;
	अचिन्हित पूर्णांक assoclen;

	rx_channel_id = cxgb4_port_e2cchan(u_ctx->lldi.ports[rx_channel_id]);

	अगर (get_aead_subtype(tfm) == CRYPTO_ALG_SUB_TYPE_AEAD_RFC4309)
		assoclen = req->assoclen - 8;
	अन्यथा
		assoclen = req->assoclen;
	ccm_xtra = CCM_B0_SIZE +
		((assoclen) ? CCM_AAD_FIELD_SIZE : 0);

	auth_offset = req->cryptlen ?
		(req->assoclen + IV + 1 + ccm_xtra) : 0;
	अगर (op_type == CHCR_DECRYPT_OP) अणु
		अगर (crypto_aead_authsize(tfm) != req->cryptlen)
			tag_offset = crypto_aead_authsize(tfm);
		अन्यथा
			auth_offset = 0;
	पूर्ण

	sec_cpl->op_ivinsrtofst = FILL_SEC_CPL_OP_IVINSR(rx_channel_id, 2, 1);
	sec_cpl->pldlen =
		htonl(req->assoclen + IV + req->cryptlen + ccm_xtra);
	/* For CCM there wil be b0 always. So AAD start will be 1 always */
	sec_cpl->aadstart_cipherstop_hi = FILL_SEC_CPL_CIPHERSTOP_HI(
				1 + IV,	IV + assoclen + ccm_xtra,
				req->assoclen + IV + 1 + ccm_xtra, 0);

	sec_cpl->cipherstop_lo_authinsert = FILL_SEC_CPL_AUTHINSERT(0,
					auth_offset, tag_offset,
					(op_type == CHCR_ENCRYPT_OP) ? 0 :
					crypto_aead_authsize(tfm));
	sec_cpl->seqno_numivs =  FILL_SEC_CPL_SCMD0_SEQNO(op_type,
					(op_type == CHCR_ENCRYPT_OP) ? 0 : 1,
					cipher_mode, mac_mode,
					aeadctx->hmac_ctrl, IV >> 1);

	sec_cpl->ivgen_hdrlen = FILL_SEC_CPL_IVGEN_HDRLEN(0, 0, 1, 0,
					0, dst_size);
पूर्ण

अटल पूर्णांक aead_ccm_validate_input(अचिन्हित लघु op_type,
				   काष्ठा aead_request *req,
				   काष्ठा chcr_aead_ctx *aeadctx,
				   अचिन्हित पूर्णांक sub_type)
अणु
	अगर (sub_type != CRYPTO_ALG_SUB_TYPE_AEAD_RFC4309) अणु
		अगर (crypto_ccm_check_iv(req->iv)) अणु
			pr_err("CCM: IV check fails\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (req->assoclen != 16 && req->assoclen != 20) अणु
			pr_err("RFC4309: Invalid AAD length %d\n",
			       req->assoclen);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *create_aead_ccm_wr(काष्ठा aead_request *req,
					  अचिन्हित लघु qid,
					  पूर्णांक size)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));
	काष्ठा chcr_aead_reqctx *reqctx = aead_request_ctx(req);
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा chcr_wr *chcr_req;
	काष्ठा cpl_rx_phys_dsgl *phys_cpl;
	काष्ठा ulptx_sgl *ulptx;
	अचिन्हित पूर्णांक transhdr_len;
	अचिन्हित पूर्णांक dst_size = 0, kctx_len, dnents, temp, snents;
	अचिन्हित पूर्णांक sub_type, assoclen = req->assoclen;
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(tfm);
	पूर्णांक error = -EINVAL;
	u8 *ivptr;
	gfp_t flags = req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP ? GFP_KERNEL :
		GFP_ATOMIC;
	काष्ठा adapter *adap = padap(a_ctx(tfm)->dev);

	sub_type = get_aead_subtype(tfm);
	अगर (sub_type == CRYPTO_ALG_SUB_TYPE_AEAD_RFC4309)
		assoclen -= 8;
	reqctx->b0_len = CCM_B0_SIZE + (assoclen ? CCM_AAD_FIELD_SIZE : 0);
	error = chcr_aead_common_init(req);
	अगर (error)
		वापस ERR_PTR(error);

	error = aead_ccm_validate_input(reqctx->op, req, aeadctx, sub_type);
	अगर (error)
		जाओ err;
	dnents = sg_nents_xlen(req->dst, req->assoclen + req->cryptlen
			+ (reqctx->op ? -authsize : authsize),
			CHCR_DST_SG_SIZE, 0);
	dnents += MIN_CCM_SG; // For IV and B0
	dst_size = get_space_क्रम_phys_dsgl(dnents);
	snents = sg_nents_xlen(req->src, req->assoclen + req->cryptlen,
			       CHCR_SRC_SG_SIZE, 0);
	snents += MIN_CCM_SG; //For B0
	kctx_len = roundup(aeadctx->enckey_len, 16) * 2;
	transhdr_len = CIPHER_TRANSHDR_SIZE(kctx_len, dst_size);
	reqctx->imm = (transhdr_len + req->assoclen + req->cryptlen +
		       reqctx->b0_len) <= SGE_MAX_WR_LEN;
	temp = reqctx->imm ? roundup(req->assoclen + req->cryptlen +
				     reqctx->b0_len, 16) :
		(sgl_len(snents) *  8);
	transhdr_len += temp;
	transhdr_len = roundup(transhdr_len, 16);

	अगर (chcr_aead_need_fallback(req, dnents, T6_MAX_AAD_SIZE -
				reqctx->b0_len, transhdr_len, reqctx->op)) अणु
		atomic_inc(&adap->chcr_stats.fallback);
		chcr_aead_common_निकास(req);
		वापस ERR_PTR(chcr_aead_fallback(req, reqctx->op));
	पूर्ण
	skb = alloc_skb(transhdr_len,  flags);

	अगर (!skb) अणु
		error = -ENOMEM;
		जाओ err;
	पूर्ण

	chcr_req = __skb_put_zero(skb, transhdr_len);

	fill_sec_cpl_क्रम_aead(&chcr_req->sec_cpl, dst_size, req, reqctx->op);

	chcr_req->key_ctx.ctx_hdr = aeadctx->key_ctx_hdr;
	स_नकल(chcr_req->key_ctx.key, aeadctx->key, aeadctx->enckey_len);
	स_नकल(chcr_req->key_ctx.key + roundup(aeadctx->enckey_len, 16),
			aeadctx->key, aeadctx->enckey_len);

	phys_cpl = (काष्ठा cpl_rx_phys_dsgl *)((u8 *)(chcr_req + 1) + kctx_len);
	ivptr = (u8 *)(phys_cpl + 1) + dst_size;
	ulptx = (काष्ठा ulptx_sgl *)(ivptr + IV);
	error = ccm_क्रमmat_packet(req, ivptr, sub_type, reqctx->op, assoclen);
	अगर (error)
		जाओ dsपंचांगap_fail;
	chcr_add_aead_dst_ent(req, phys_cpl, qid);
	chcr_add_aead_src_ent(req, ulptx);

	atomic_inc(&adap->chcr_stats.aead_rqst);
	temp = माप(काष्ठा cpl_rx_phys_dsgl) + dst_size + IV +
		kctx_len + (reqctx->imm ? (req->assoclen + req->cryptlen +
		reqctx->b0_len) : 0);
	create_wreq(a_ctx(tfm), chcr_req, &req->base, reqctx->imm, 0,
		    transhdr_len, temp, 0);
	reqctx->skb = skb;

	वापस skb;
dsपंचांगap_fail:
	kमुक्त_skb(skb);
err:
	chcr_aead_common_निकास(req);
	वापस ERR_PTR(error);
पूर्ण

अटल काष्ठा sk_buff *create_gcm_wr(काष्ठा aead_request *req,
				     अचिन्हित लघु qid,
				     पूर्णांक size)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा chcr_context *ctx = a_ctx(tfm);
	काष्ठा uld_ctx *u_ctx = ULD_CTX(ctx);
	काष्ठा chcr_aead_ctx *aeadctx = AEAD_CTX(ctx);
	काष्ठा chcr_aead_reqctx  *reqctx = aead_request_ctx(req);
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा chcr_wr *chcr_req;
	काष्ठा cpl_rx_phys_dsgl *phys_cpl;
	काष्ठा ulptx_sgl *ulptx;
	अचिन्हित पूर्णांक transhdr_len, dnents = 0, snents;
	अचिन्हित पूर्णांक dst_size = 0, temp = 0, kctx_len, assoclen = req->assoclen;
	अचिन्हित पूर्णांक authsize = crypto_aead_authsize(tfm);
	पूर्णांक error = -EINVAL;
	u8 *ivptr;
	gfp_t flags = req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP ? GFP_KERNEL :
		GFP_ATOMIC;
	काष्ठा adapter *adap = padap(ctx->dev);
	अचिन्हित पूर्णांक rx_channel_id = reqctx->rxqidx / ctx->rxq_perchan;

	rx_channel_id = cxgb4_port_e2cchan(u_ctx->lldi.ports[rx_channel_id]);
	अगर (get_aead_subtype(tfm) == CRYPTO_ALG_SUB_TYPE_AEAD_RFC4106)
		assoclen = req->assoclen - 8;

	reqctx->b0_len = 0;
	error = chcr_aead_common_init(req);
	अगर (error)
		वापस ERR_PTR(error);
	dnents = sg_nents_xlen(req->dst, req->assoclen + req->cryptlen +
				(reqctx->op ? -authsize : authsize),
				CHCR_DST_SG_SIZE, 0);
	snents = sg_nents_xlen(req->src, req->assoclen + req->cryptlen,
			       CHCR_SRC_SG_SIZE, 0);
	dnents += MIN_GCM_SG; // For IV
	dst_size = get_space_क्रम_phys_dsgl(dnents);
	kctx_len = roundup(aeadctx->enckey_len, 16) + AEAD_H_SIZE;
	transhdr_len = CIPHER_TRANSHDR_SIZE(kctx_len, dst_size);
	reqctx->imm = (transhdr_len + req->assoclen + req->cryptlen) <=
			SGE_MAX_WR_LEN;
	temp = reqctx->imm ? roundup(req->assoclen + req->cryptlen, 16) :
		(sgl_len(snents) * 8);
	transhdr_len += temp;
	transhdr_len = roundup(transhdr_len, 16);
	अगर (chcr_aead_need_fallback(req, dnents, T6_MAX_AAD_SIZE,
			    transhdr_len, reqctx->op)) अणु

		atomic_inc(&adap->chcr_stats.fallback);
		chcr_aead_common_निकास(req);
		वापस ERR_PTR(chcr_aead_fallback(req, reqctx->op));
	पूर्ण
	skb = alloc_skb(transhdr_len, flags);
	अगर (!skb) अणु
		error = -ENOMEM;
		जाओ err;
	पूर्ण

	chcr_req = __skb_put_zero(skb, transhdr_len);

	//Offset of tag from end
	temp = (reqctx->op == CHCR_ENCRYPT_OP) ? 0 : authsize;
	chcr_req->sec_cpl.op_ivinsrtofst = FILL_SEC_CPL_OP_IVINSR(
						rx_channel_id, 2, 1);
	chcr_req->sec_cpl.pldlen =
		htonl(req->assoclen + IV + req->cryptlen);
	chcr_req->sec_cpl.aadstart_cipherstop_hi = FILL_SEC_CPL_CIPHERSTOP_HI(
					assoclen ? 1 + IV : 0,
					assoclen ? IV + assoclen : 0,
					req->assoclen + IV + 1, 0);
	chcr_req->sec_cpl.cipherstop_lo_authinsert =
			FILL_SEC_CPL_AUTHINSERT(0, req->assoclen + IV + 1,
						temp, temp);
	chcr_req->sec_cpl.seqno_numivs =
			FILL_SEC_CPL_SCMD0_SEQNO(reqctx->op, (reqctx->op ==
					CHCR_ENCRYPT_OP) ? 1 : 0,
					CHCR_SCMD_CIPHER_MODE_AES_GCM,
					CHCR_SCMD_AUTH_MODE_GHASH,
					aeadctx->hmac_ctrl, IV >> 1);
	chcr_req->sec_cpl.ivgen_hdrlen =  FILL_SEC_CPL_IVGEN_HDRLEN(0, 0, 1,
					0, 0, dst_size);
	chcr_req->key_ctx.ctx_hdr = aeadctx->key_ctx_hdr;
	स_नकल(chcr_req->key_ctx.key, aeadctx->key, aeadctx->enckey_len);
	स_नकल(chcr_req->key_ctx.key + roundup(aeadctx->enckey_len, 16),
	       GCM_CTX(aeadctx)->ghash_h, AEAD_H_SIZE);

	phys_cpl = (काष्ठा cpl_rx_phys_dsgl *)((u8 *)(chcr_req + 1) + kctx_len);
	ivptr = (u8 *)(phys_cpl + 1) + dst_size;
	/* prepare a 16 byte iv */
	/* S   A   L  T |  IV | 0x00000001 */
	अगर (get_aead_subtype(tfm) ==
	    CRYPTO_ALG_SUB_TYPE_AEAD_RFC4106) अणु
		स_नकल(ivptr, aeadctx->salt, 4);
		स_नकल(ivptr + 4, req->iv, GCM_RFC4106_IV_SIZE);
	पूर्ण अन्यथा अणु
		स_नकल(ivptr, req->iv, GCM_AES_IV_SIZE);
	पूर्ण
	put_unaligned_be32(0x01, &ivptr[12]);
	ulptx = (काष्ठा ulptx_sgl *)(ivptr + 16);

	chcr_add_aead_dst_ent(req, phys_cpl, qid);
	chcr_add_aead_src_ent(req, ulptx);
	atomic_inc(&adap->chcr_stats.aead_rqst);
	temp = माप(काष्ठा cpl_rx_phys_dsgl) + dst_size + IV +
		kctx_len + (reqctx->imm ? (req->assoclen + req->cryptlen) : 0);
	create_wreq(a_ctx(tfm), chcr_req, &req->base, reqctx->imm, size,
		    transhdr_len, temp, reqctx->verअगरy);
	reqctx->skb = skb;
	वापस skb;

err:
	chcr_aead_common_निकास(req);
	वापस ERR_PTR(error);
पूर्ण



अटल पूर्णांक chcr_aead_cra_init(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));
	काष्ठा aead_alg *alg = crypto_aead_alg(tfm);

	aeadctx->sw_cipher = crypto_alloc_aead(alg->base.cra_name, 0,
					       CRYPTO_ALG_NEED_FALLBACK |
					       CRYPTO_ALG_ASYNC);
	अगर  (IS_ERR(aeadctx->sw_cipher))
		वापस PTR_ERR(aeadctx->sw_cipher);
	crypto_aead_set_reqsize(tfm, max(माप(काष्ठा chcr_aead_reqctx),
				 माप(काष्ठा aead_request) +
				 crypto_aead_reqsize(aeadctx->sw_cipher)));
	वापस chcr_device_init(a_ctx(tfm));
पूर्ण

अटल व्योम chcr_aead_cra_निकास(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));

	crypto_मुक्त_aead(aeadctx->sw_cipher);
पूर्ण

अटल पूर्णांक chcr_authenc_null_setauthsize(काष्ठा crypto_aead *tfm,
					अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));

	aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_NOP;
	aeadctx->mayverअगरy = VERIFY_HW;
	वापस crypto_aead_setauthsize(aeadctx->sw_cipher, authsize);
पूर्ण
अटल पूर्णांक chcr_authenc_setauthsize(काष्ठा crypto_aead *tfm,
				    अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));
	u32 maxauth = crypto_aead_maxauthsize(tfm);

	/*SHA1 authsize in ipsec is 12 instead of 10 i.e maxauthsize / 2 is not
	 * true क्रम sha1. authsize == 12 condition should be beक्रमe
	 * authsize == (maxauth >> 1)
	 */
	अगर (authsize == ICV_4) अणु
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_PL1;
		aeadctx->mayverअगरy = VERIFY_HW;
	पूर्ण अन्यथा अगर (authsize == ICV_6) अणु
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_PL2;
		aeadctx->mayverअगरy = VERIFY_HW;
	पूर्ण अन्यथा अगर (authsize == ICV_10) अणु
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_TRUNC_RFC4366;
		aeadctx->mayverअगरy = VERIFY_HW;
	पूर्ण अन्यथा अगर (authsize == ICV_12) अणु
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_IPSEC_96BIT;
		aeadctx->mayverअगरy = VERIFY_HW;
	पूर्ण अन्यथा अगर (authsize == ICV_14) अणु
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_PL3;
		aeadctx->mayverअगरy = VERIFY_HW;
	पूर्ण अन्यथा अगर (authsize == (maxauth >> 1)) अणु
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_DIV2;
		aeadctx->mayverअगरy = VERIFY_HW;
	पूर्ण अन्यथा अगर (authsize == maxauth) अणु
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_NO_TRUNC;
		aeadctx->mayverअगरy = VERIFY_HW;
	पूर्ण अन्यथा अणु
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_NO_TRUNC;
		aeadctx->mayverअगरy = VERIFY_SW;
	पूर्ण
	वापस crypto_aead_setauthsize(aeadctx->sw_cipher, authsize);
पूर्ण


अटल पूर्णांक chcr_gcm_setauthsize(काष्ठा crypto_aead *tfm, अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));

	चयन (authsize) अणु
	हाल ICV_4:
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_PL1;
		aeadctx->mayverअगरy = VERIFY_HW;
		अवरोध;
	हाल ICV_8:
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_DIV2;
		aeadctx->mayverअगरy = VERIFY_HW;
		अवरोध;
	हाल ICV_12:
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_IPSEC_96BIT;
		aeadctx->mayverअगरy = VERIFY_HW;
		अवरोध;
	हाल ICV_14:
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_PL3;
		aeadctx->mayverअगरy = VERIFY_HW;
		अवरोध;
	हाल ICV_16:
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_NO_TRUNC;
		aeadctx->mayverअगरy = VERIFY_HW;
		अवरोध;
	हाल ICV_13:
	हाल ICV_15:
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_NO_TRUNC;
		aeadctx->mayverअगरy = VERIFY_SW;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस crypto_aead_setauthsize(aeadctx->sw_cipher, authsize);
पूर्ण

अटल पूर्णांक chcr_4106_4309_setauthsize(काष्ठा crypto_aead *tfm,
					  अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));

	चयन (authsize) अणु
	हाल ICV_8:
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_DIV2;
		aeadctx->mayverअगरy = VERIFY_HW;
		अवरोध;
	हाल ICV_12:
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_IPSEC_96BIT;
		aeadctx->mayverअगरy = VERIFY_HW;
		अवरोध;
	हाल ICV_16:
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_NO_TRUNC;
		aeadctx->mayverअगरy = VERIFY_HW;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस crypto_aead_setauthsize(aeadctx->sw_cipher, authsize);
पूर्ण

अटल पूर्णांक chcr_ccm_setauthsize(काष्ठा crypto_aead *tfm,
				अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));

	चयन (authsize) अणु
	हाल ICV_4:
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_PL1;
		aeadctx->mayverअगरy = VERIFY_HW;
		अवरोध;
	हाल ICV_6:
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_PL2;
		aeadctx->mayverअगरy = VERIFY_HW;
		अवरोध;
	हाल ICV_8:
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_DIV2;
		aeadctx->mayverअगरy = VERIFY_HW;
		अवरोध;
	हाल ICV_10:
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_TRUNC_RFC4366;
		aeadctx->mayverअगरy = VERIFY_HW;
		अवरोध;
	हाल ICV_12:
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_IPSEC_96BIT;
		aeadctx->mayverअगरy = VERIFY_HW;
		अवरोध;
	हाल ICV_14:
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_PL3;
		aeadctx->mayverअगरy = VERIFY_HW;
		अवरोध;
	हाल ICV_16:
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_NO_TRUNC;
		aeadctx->mayverअगरy = VERIFY_HW;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस crypto_aead_setauthsize(aeadctx->sw_cipher, authsize);
पूर्ण

अटल पूर्णांक chcr_ccm_common_setkey(काष्ठा crypto_aead *aead,
				स्थिर u8 *key,
				अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(aead));
	अचिन्हित अक्षर ck_size, mk_size;
	पूर्णांक key_ctx_size = 0;

	key_ctx_size = माप(काष्ठा _key_ctx) + roundup(keylen, 16) * 2;
	अगर (keylen == AES_KEYSIZE_128) अणु
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_128;
		mk_size = CHCR_KEYCTX_MAC_KEY_SIZE_128;
	पूर्ण अन्यथा अगर (keylen == AES_KEYSIZE_192) अणु
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_192;
		mk_size = CHCR_KEYCTX_MAC_KEY_SIZE_192;
	पूर्ण अन्यथा अगर (keylen == AES_KEYSIZE_256) अणु
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_256;
		mk_size = CHCR_KEYCTX_MAC_KEY_SIZE_256;
	पूर्ण अन्यथा अणु
		aeadctx->enckey_len = 0;
		वापस	-EINVAL;
	पूर्ण
	aeadctx->key_ctx_hdr = FILL_KEY_CTX_HDR(ck_size, mk_size, 0, 0,
						key_ctx_size >> 4);
	स_नकल(aeadctx->key, key, keylen);
	aeadctx->enckey_len = keylen;

	वापस 0;
पूर्ण

अटल पूर्णांक chcr_aead_ccm_setkey(काष्ठा crypto_aead *aead,
				स्थिर u8 *key,
				अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(aead));
	पूर्णांक error;

	crypto_aead_clear_flags(aeadctx->sw_cipher, CRYPTO_TFM_REQ_MASK);
	crypto_aead_set_flags(aeadctx->sw_cipher, crypto_aead_get_flags(aead) &
			      CRYPTO_TFM_REQ_MASK);
	error = crypto_aead_setkey(aeadctx->sw_cipher, key, keylen);
	अगर (error)
		वापस error;
	वापस chcr_ccm_common_setkey(aead, key, keylen);
पूर्ण

अटल पूर्णांक chcr_aead_rfc4309_setkey(काष्ठा crypto_aead *aead, स्थिर u8 *key,
				    अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(aead));
	पूर्णांक error;

	अगर (keylen < 3) अणु
		aeadctx->enckey_len = 0;
		वापस	-EINVAL;
	पूर्ण
	crypto_aead_clear_flags(aeadctx->sw_cipher, CRYPTO_TFM_REQ_MASK);
	crypto_aead_set_flags(aeadctx->sw_cipher, crypto_aead_get_flags(aead) &
			      CRYPTO_TFM_REQ_MASK);
	error = crypto_aead_setkey(aeadctx->sw_cipher, key, keylen);
	अगर (error)
		वापस error;
	keylen -= 3;
	स_नकल(aeadctx->salt, key + keylen, 3);
	वापस chcr_ccm_common_setkey(aead, key, keylen);
पूर्ण

अटल पूर्णांक chcr_gcm_setkey(काष्ठा crypto_aead *aead, स्थिर u8 *key,
			   अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(aead));
	काष्ठा chcr_gcm_ctx *gctx = GCM_CTX(aeadctx);
	अचिन्हित पूर्णांक ck_size;
	पूर्णांक ret = 0, key_ctx_size = 0;
	काष्ठा crypto_aes_ctx aes;

	aeadctx->enckey_len = 0;
	crypto_aead_clear_flags(aeadctx->sw_cipher, CRYPTO_TFM_REQ_MASK);
	crypto_aead_set_flags(aeadctx->sw_cipher, crypto_aead_get_flags(aead)
			      & CRYPTO_TFM_REQ_MASK);
	ret = crypto_aead_setkey(aeadctx->sw_cipher, key, keylen);
	अगर (ret)
		जाओ out;

	अगर (get_aead_subtype(aead) == CRYPTO_ALG_SUB_TYPE_AEAD_RFC4106 &&
	    keylen > 3) अणु
		keylen -= 4;  /* nonce/salt is present in the last 4 bytes */
		स_नकल(aeadctx->salt, key + keylen, 4);
	पूर्ण
	अगर (keylen == AES_KEYSIZE_128) अणु
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_128;
	पूर्ण अन्यथा अगर (keylen == AES_KEYSIZE_192) अणु
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_192;
	पूर्ण अन्यथा अगर (keylen == AES_KEYSIZE_256) अणु
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_256;
	पूर्ण अन्यथा अणु
		pr_err("GCM: Invalid key length %d\n", keylen);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	स_नकल(aeadctx->key, key, keylen);
	aeadctx->enckey_len = keylen;
	key_ctx_size = माप(काष्ठा _key_ctx) + roundup(keylen, 16) +
		AEAD_H_SIZE;
	aeadctx->key_ctx_hdr = FILL_KEY_CTX_HDR(ck_size,
						CHCR_KEYCTX_MAC_KEY_SIZE_128,
						0, 0,
						key_ctx_size >> 4);
	/* Calculate the H = CIPH(K, 0 repeated 16 बार).
	 * It will go in key context
	 */
	ret = aes_expandkey(&aes, key, keylen);
	अगर (ret) अणु
		aeadctx->enckey_len = 0;
		जाओ out;
	पूर्ण
	स_रखो(gctx->ghash_h, 0, AEAD_H_SIZE);
	aes_encrypt(&aes, gctx->ghash_h, gctx->ghash_h);
	memzero_explicit(&aes, माप(aes));

out:
	वापस ret;
पूर्ण

अटल पूर्णांक chcr_authenc_setkey(काष्ठा crypto_aead *authenc, स्थिर u8 *key,
				   अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(authenc));
	काष्ठा chcr_authenc_ctx *actx = AUTHENC_CTX(aeadctx);
	/* it contains auth and cipher key both*/
	काष्ठा crypto_authenc_keys keys;
	अचिन्हित पूर्णांक bs, subtype;
	अचिन्हित पूर्णांक max_authsize = crypto_aead_alg(authenc)->maxauthsize;
	पूर्णांक err = 0, i, key_ctx_len = 0;
	अचिन्हित अक्षर ck_size = 0;
	अचिन्हित अक्षर pad[CHCR_HASH_MAX_BLOCK_SIZE_128] = अणु 0 पूर्ण;
	काष्ठा crypto_shash *base_hash = ERR_PTR(-EINVAL);
	काष्ठा algo_param param;
	पूर्णांक align;
	u8 *o_ptr = शून्य;

	crypto_aead_clear_flags(aeadctx->sw_cipher, CRYPTO_TFM_REQ_MASK);
	crypto_aead_set_flags(aeadctx->sw_cipher, crypto_aead_get_flags(authenc)
			      & CRYPTO_TFM_REQ_MASK);
	err = crypto_aead_setkey(aeadctx->sw_cipher, key, keylen);
	अगर (err)
		जाओ out;

	अगर (crypto_authenc_extractkeys(&keys, key, keylen) != 0)
		जाओ out;

	अगर (get_alg_config(&param, max_authsize)) अणु
		pr_err("Unsupported digest size\n");
		जाओ out;
	पूर्ण
	subtype = get_aead_subtype(authenc);
	अगर (subtype == CRYPTO_ALG_SUB_TYPE_CTR_SHA ||
		subtype == CRYPTO_ALG_SUB_TYPE_CTR_शून्य) अणु
		अगर (keys.enckeylen < CTR_RFC3686_NONCE_SIZE)
			जाओ out;
		स_नकल(aeadctx->nonce, keys.enckey + (keys.enckeylen
		- CTR_RFC3686_NONCE_SIZE), CTR_RFC3686_NONCE_SIZE);
		keys.enckeylen -= CTR_RFC3686_NONCE_SIZE;
	पूर्ण
	अगर (keys.enckeylen == AES_KEYSIZE_128) अणु
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_128;
	पूर्ण अन्यथा अगर (keys.enckeylen == AES_KEYSIZE_192) अणु
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_192;
	पूर्ण अन्यथा अगर (keys.enckeylen == AES_KEYSIZE_256) अणु
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_256;
	पूर्ण अन्यथा अणु
		pr_err("Unsupported cipher key\n");
		जाओ out;
	पूर्ण

	/* Copy only encryption key. We use authkey to generate h(ipad) and
	 * h(opad) so authkey is not needed again. authkeylen size have the
	 * size of the hash digest size.
	 */
	स_नकल(aeadctx->key, keys.enckey, keys.enckeylen);
	aeadctx->enckey_len = keys.enckeylen;
	अगर (subtype == CRYPTO_ALG_SUB_TYPE_CBC_SHA ||
		subtype == CRYPTO_ALG_SUB_TYPE_CBC_शून्य) अणु

		get_aes_decrypt_key(actx->dec_rrkey, aeadctx->key,
			    aeadctx->enckey_len << 3);
	पूर्ण
	base_hash  = chcr_alloc_shash(max_authsize);
	अगर (IS_ERR(base_hash)) अणु
		pr_err("Base driver cannot be loaded\n");
		जाओ out;
	पूर्ण
	अणु
		SHASH_DESC_ON_STACK(shash, base_hash);

		shash->tfm = base_hash;
		bs = crypto_shash_blocksize(base_hash);
		align = KEYCTX_ALIGN_PAD(max_authsize);
		o_ptr =  actx->h_iopad + param.result_size + align;

		अगर (keys.authkeylen > bs) अणु
			err = crypto_shash_digest(shash, keys.authkey,
						  keys.authkeylen,
						  o_ptr);
			अगर (err) अणु
				pr_err("Base driver cannot be loaded\n");
				जाओ out;
			पूर्ण
			keys.authkeylen = max_authsize;
		पूर्ण अन्यथा
			स_नकल(o_ptr, keys.authkey, keys.authkeylen);

		/* Compute the ipad-digest*/
		स_रखो(pad + keys.authkeylen, 0, bs - keys.authkeylen);
		स_नकल(pad, o_ptr, keys.authkeylen);
		क्रम (i = 0; i < bs >> 2; i++)
			*((अचिन्हित पूर्णांक *)pad + i) ^= IPAD_DATA;

		अगर (chcr_compute_partial_hash(shash, pad, actx->h_iopad,
					      max_authsize))
			जाओ out;
		/* Compute the opad-digest */
		स_रखो(pad + keys.authkeylen, 0, bs - keys.authkeylen);
		स_नकल(pad, o_ptr, keys.authkeylen);
		क्रम (i = 0; i < bs >> 2; i++)
			*((अचिन्हित पूर्णांक *)pad + i) ^= OPAD_DATA;

		अगर (chcr_compute_partial_hash(shash, pad, o_ptr, max_authsize))
			जाओ out;

		/* convert the ipad and opad digest to network order */
		chcr_change_order(actx->h_iopad, param.result_size);
		chcr_change_order(o_ptr, param.result_size);
		key_ctx_len = माप(काष्ठा _key_ctx) +
			roundup(keys.enckeylen, 16) +
			(param.result_size + align) * 2;
		aeadctx->key_ctx_hdr = FILL_KEY_CTX_HDR(ck_size, param.mk_size,
						0, 1, key_ctx_len >> 4);
		actx->auth_mode = param.auth_mode;
		chcr_मुक्त_shash(base_hash);

		memzero_explicit(&keys, माप(keys));
		वापस 0;
	पूर्ण
out:
	aeadctx->enckey_len = 0;
	memzero_explicit(&keys, माप(keys));
	अगर (!IS_ERR(base_hash))
		chcr_मुक्त_shash(base_hash);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक chcr_aead_digest_null_setkey(काष्ठा crypto_aead *authenc,
					स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(authenc));
	काष्ठा chcr_authenc_ctx *actx = AUTHENC_CTX(aeadctx);
	काष्ठा crypto_authenc_keys keys;
	पूर्णांक err;
	/* it contains auth and cipher key both*/
	अचिन्हित पूर्णांक subtype;
	पूर्णांक key_ctx_len = 0;
	अचिन्हित अक्षर ck_size = 0;

	crypto_aead_clear_flags(aeadctx->sw_cipher, CRYPTO_TFM_REQ_MASK);
	crypto_aead_set_flags(aeadctx->sw_cipher, crypto_aead_get_flags(authenc)
			      & CRYPTO_TFM_REQ_MASK);
	err = crypto_aead_setkey(aeadctx->sw_cipher, key, keylen);
	अगर (err)
		जाओ out;

	अगर (crypto_authenc_extractkeys(&keys, key, keylen) != 0)
		जाओ out;

	subtype = get_aead_subtype(authenc);
	अगर (subtype == CRYPTO_ALG_SUB_TYPE_CTR_SHA ||
	    subtype == CRYPTO_ALG_SUB_TYPE_CTR_शून्य) अणु
		अगर (keys.enckeylen < CTR_RFC3686_NONCE_SIZE)
			जाओ out;
		स_नकल(aeadctx->nonce, keys.enckey + (keys.enckeylen
			- CTR_RFC3686_NONCE_SIZE), CTR_RFC3686_NONCE_SIZE);
		keys.enckeylen -= CTR_RFC3686_NONCE_SIZE;
	पूर्ण
	अगर (keys.enckeylen == AES_KEYSIZE_128) अणु
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_128;
	पूर्ण अन्यथा अगर (keys.enckeylen == AES_KEYSIZE_192) अणु
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_192;
	पूर्ण अन्यथा अगर (keys.enckeylen == AES_KEYSIZE_256) अणु
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_256;
	पूर्ण अन्यथा अणु
		pr_err("Unsupported cipher key %d\n", keys.enckeylen);
		जाओ out;
	पूर्ण
	स_नकल(aeadctx->key, keys.enckey, keys.enckeylen);
	aeadctx->enckey_len = keys.enckeylen;
	अगर (subtype == CRYPTO_ALG_SUB_TYPE_CBC_SHA ||
	    subtype == CRYPTO_ALG_SUB_TYPE_CBC_शून्य) अणु
		get_aes_decrypt_key(actx->dec_rrkey, aeadctx->key,
				aeadctx->enckey_len << 3);
	पूर्ण
	key_ctx_len =  माप(काष्ठा _key_ctx) + roundup(keys.enckeylen, 16);

	aeadctx->key_ctx_hdr = FILL_KEY_CTX_HDR(ck_size, CHCR_KEYCTX_NO_KEY, 0,
						0, key_ctx_len >> 4);
	actx->auth_mode = CHCR_SCMD_AUTH_MODE_NOP;
	memzero_explicit(&keys, माप(keys));
	वापस 0;
out:
	aeadctx->enckey_len = 0;
	memzero_explicit(&keys, माप(keys));
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक chcr_aead_op(काष्ठा aead_request *req,
			पूर्णांक size,
			create_wr_t create_wr_fn)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा chcr_aead_reqctx  *reqctx = aead_request_ctx(req);
	काष्ठा chcr_context *ctx = a_ctx(tfm);
	काष्ठा uld_ctx *u_ctx = ULD_CTX(ctx);
	काष्ठा sk_buff *skb;
	काष्ठा chcr_dev *cdev;

	cdev = a_ctx(tfm)->dev;
	अगर (!cdev) अणु
		pr_err("%s : No crypto device.\n", __func__);
		वापस -ENXIO;
	पूर्ण

	अगर (chcr_inc_wrcount(cdev)) अणु
	/* Detach state क्रम CHCR means lldi or padap is मुक्तd.
	 * We cannot increment fallback here.
	 */
		वापस chcr_aead_fallback(req, reqctx->op);
	पूर्ण

	अगर (cxgb4_is_crypto_q_full(u_ctx->lldi.ports[0],
					reqctx->txqidx) &&
		(!(req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG))) अणु
			chcr_dec_wrcount(cdev);
			वापस -ENOSPC;
	पूर्ण

	अगर (get_aead_subtype(tfm) == CRYPTO_ALG_SUB_TYPE_AEAD_RFC4106 &&
	    crypto_ipsec_check_assoclen(req->assoclen) != 0) अणु
		pr_err("RFC4106: Invalid value of assoclen %d\n",
		       req->assoclen);
		वापस -EINVAL;
	पूर्ण

	/* Form a WR from req */
	skb = create_wr_fn(req, u_ctx->lldi.rxq_ids[reqctx->rxqidx], size);

	अगर (IS_ERR_OR_शून्य(skb)) अणु
		chcr_dec_wrcount(cdev);
		वापस PTR_ERR_OR_ZERO(skb);
	पूर्ण

	skb->dev = u_ctx->lldi.ports[0];
	set_wr_txq(skb, CPL_PRIORITY_DATA, reqctx->txqidx);
	chcr_send_wr(skb);
	वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक chcr_aead_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा chcr_aead_reqctx *reqctx = aead_request_ctx(req);
	काष्ठा chcr_context *ctx = a_ctx(tfm);
	अचिन्हित पूर्णांक cpu;

	cpu = get_cpu();
	reqctx->txqidx = cpu % ctx->ntxq;
	reqctx->rxqidx = cpu % ctx->nrxq;
	put_cpu();

	reqctx->verअगरy = VERIFY_HW;
	reqctx->op = CHCR_ENCRYPT_OP;

	चयन (get_aead_subtype(tfm)) अणु
	हाल CRYPTO_ALG_SUB_TYPE_CTR_SHA:
	हाल CRYPTO_ALG_SUB_TYPE_CBC_SHA:
	हाल CRYPTO_ALG_SUB_TYPE_CBC_शून्य:
	हाल CRYPTO_ALG_SUB_TYPE_CTR_शून्य:
		वापस chcr_aead_op(req, 0, create_authenc_wr);
	हाल CRYPTO_ALG_SUB_TYPE_AEAD_CCM:
	हाल CRYPTO_ALG_SUB_TYPE_AEAD_RFC4309:
		वापस chcr_aead_op(req, 0, create_aead_ccm_wr);
	शेष:
		वापस chcr_aead_op(req, 0, create_gcm_wr);
	पूर्ण
पूर्ण

अटल पूर्णांक chcr_aead_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा chcr_context *ctx = a_ctx(tfm);
	काष्ठा chcr_aead_ctx *aeadctx = AEAD_CTX(ctx);
	काष्ठा chcr_aead_reqctx *reqctx = aead_request_ctx(req);
	पूर्णांक size;
	अचिन्हित पूर्णांक cpu;

	cpu = get_cpu();
	reqctx->txqidx = cpu % ctx->ntxq;
	reqctx->rxqidx = cpu % ctx->nrxq;
	put_cpu();

	अगर (aeadctx->mayverअगरy == VERIFY_SW) अणु
		size = crypto_aead_maxauthsize(tfm);
		reqctx->verअगरy = VERIFY_SW;
	पूर्ण अन्यथा अणु
		size = 0;
		reqctx->verअगरy = VERIFY_HW;
	पूर्ण
	reqctx->op = CHCR_DECRYPT_OP;
	चयन (get_aead_subtype(tfm)) अणु
	हाल CRYPTO_ALG_SUB_TYPE_CBC_SHA:
	हाल CRYPTO_ALG_SUB_TYPE_CTR_SHA:
	हाल CRYPTO_ALG_SUB_TYPE_CBC_शून्य:
	हाल CRYPTO_ALG_SUB_TYPE_CTR_शून्य:
		वापस chcr_aead_op(req, size, create_authenc_wr);
	हाल CRYPTO_ALG_SUB_TYPE_AEAD_CCM:
	हाल CRYPTO_ALG_SUB_TYPE_AEAD_RFC4309:
		वापस chcr_aead_op(req, size, create_aead_ccm_wr);
	शेष:
		वापस chcr_aead_op(req, size, create_gcm_wr);
	पूर्ण
पूर्ण

अटल काष्ठा chcr_alg_ढाँचा driver_algs[] = अणु
	/* AES-CBC */
	अणु
		.type = CRYPTO_ALG_TYPE_SKCIPHER | CRYPTO_ALG_SUB_TYPE_CBC,
		.is_रेजिस्टरed = 0,
		.alg.skcipher = अणु
			.base.cra_name		= "cbc(aes)",
			.base.cra_driver_name	= "cbc-aes-chcr",
			.base.cra_blocksize	= AES_BLOCK_SIZE,

			.init			= chcr_init_tfm,
			.निकास			= chcr_निकास_tfm,
			.min_keysize		= AES_MIN_KEY_SIZE,
			.max_keysize		= AES_MAX_KEY_SIZE,
			.ivsize			= AES_BLOCK_SIZE,
			.setkey			= chcr_aes_cbc_setkey,
			.encrypt		= chcr_aes_encrypt,
			.decrypt		= chcr_aes_decrypt,
			पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_SKCIPHER | CRYPTO_ALG_SUB_TYPE_XTS,
		.is_रेजिस्टरed = 0,
		.alg.skcipher = अणु
			.base.cra_name		= "xts(aes)",
			.base.cra_driver_name	= "xts-aes-chcr",
			.base.cra_blocksize	= AES_BLOCK_SIZE,

			.init			= chcr_init_tfm,
			.निकास			= chcr_निकास_tfm,
			.min_keysize		= 2 * AES_MIN_KEY_SIZE,
			.max_keysize		= 2 * AES_MAX_KEY_SIZE,
			.ivsize			= AES_BLOCK_SIZE,
			.setkey			= chcr_aes_xts_setkey,
			.encrypt		= chcr_aes_encrypt,
			.decrypt		= chcr_aes_decrypt,
			पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_SKCIPHER | CRYPTO_ALG_SUB_TYPE_CTR,
		.is_रेजिस्टरed = 0,
		.alg.skcipher = अणु
			.base.cra_name		= "ctr(aes)",
			.base.cra_driver_name	= "ctr-aes-chcr",
			.base.cra_blocksize	= 1,

			.init			= chcr_init_tfm,
			.निकास			= chcr_निकास_tfm,
			.min_keysize		= AES_MIN_KEY_SIZE,
			.max_keysize		= AES_MAX_KEY_SIZE,
			.ivsize			= AES_BLOCK_SIZE,
			.setkey			= chcr_aes_ctr_setkey,
			.encrypt		= chcr_aes_encrypt,
			.decrypt		= chcr_aes_decrypt,
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_SKCIPHER |
			CRYPTO_ALG_SUB_TYPE_CTR_RFC3686,
		.is_रेजिस्टरed = 0,
		.alg.skcipher = अणु
			.base.cra_name		= "rfc3686(ctr(aes))",
			.base.cra_driver_name	= "rfc3686-ctr-aes-chcr",
			.base.cra_blocksize	= 1,

			.init			= chcr_rfc3686_init,
			.निकास			= chcr_निकास_tfm,
			.min_keysize		= AES_MIN_KEY_SIZE + CTR_RFC3686_NONCE_SIZE,
			.max_keysize		= AES_MAX_KEY_SIZE + CTR_RFC3686_NONCE_SIZE,
			.ivsize			= CTR_RFC3686_IV_SIZE,
			.setkey			= chcr_aes_rfc3686_setkey,
			.encrypt		= chcr_aes_encrypt,
			.decrypt		= chcr_aes_decrypt,
		पूर्ण
	पूर्ण,
	/* SHA */
	अणु
		.type = CRYPTO_ALG_TYPE_AHASH,
		.is_रेजिस्टरed = 0,
		.alg.hash = अणु
			.halg.digestsize = SHA1_DIGEST_SIZE,
			.halg.base = अणु
				.cra_name = "sha1",
				.cra_driver_name = "sha1-chcr",
				.cra_blocksize = SHA1_BLOCK_SIZE,
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_AHASH,
		.is_रेजिस्टरed = 0,
		.alg.hash = अणु
			.halg.digestsize = SHA256_DIGEST_SIZE,
			.halg.base = अणु
				.cra_name = "sha256",
				.cra_driver_name = "sha256-chcr",
				.cra_blocksize = SHA256_BLOCK_SIZE,
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_AHASH,
		.is_रेजिस्टरed = 0,
		.alg.hash = अणु
			.halg.digestsize = SHA224_DIGEST_SIZE,
			.halg.base = अणु
				.cra_name = "sha224",
				.cra_driver_name = "sha224-chcr",
				.cra_blocksize = SHA224_BLOCK_SIZE,
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_AHASH,
		.is_रेजिस्टरed = 0,
		.alg.hash = अणु
			.halg.digestsize = SHA384_DIGEST_SIZE,
			.halg.base = अणु
				.cra_name = "sha384",
				.cra_driver_name = "sha384-chcr",
				.cra_blocksize = SHA384_BLOCK_SIZE,
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_AHASH,
		.is_रेजिस्टरed = 0,
		.alg.hash = अणु
			.halg.digestsize = SHA512_DIGEST_SIZE,
			.halg.base = अणु
				.cra_name = "sha512",
				.cra_driver_name = "sha512-chcr",
				.cra_blocksize = SHA512_BLOCK_SIZE,
			पूर्ण
		पूर्ण
	पूर्ण,
	/* HMAC */
	अणु
		.type = CRYPTO_ALG_TYPE_HMAC,
		.is_रेजिस्टरed = 0,
		.alg.hash = अणु
			.halg.digestsize = SHA1_DIGEST_SIZE,
			.halg.base = अणु
				.cra_name = "hmac(sha1)",
				.cra_driver_name = "hmac-sha1-chcr",
				.cra_blocksize = SHA1_BLOCK_SIZE,
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_HMAC,
		.is_रेजिस्टरed = 0,
		.alg.hash = अणु
			.halg.digestsize = SHA224_DIGEST_SIZE,
			.halg.base = अणु
				.cra_name = "hmac(sha224)",
				.cra_driver_name = "hmac-sha224-chcr",
				.cra_blocksize = SHA224_BLOCK_SIZE,
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_HMAC,
		.is_रेजिस्टरed = 0,
		.alg.hash = अणु
			.halg.digestsize = SHA256_DIGEST_SIZE,
			.halg.base = अणु
				.cra_name = "hmac(sha256)",
				.cra_driver_name = "hmac-sha256-chcr",
				.cra_blocksize = SHA256_BLOCK_SIZE,
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_HMAC,
		.is_रेजिस्टरed = 0,
		.alg.hash = अणु
			.halg.digestsize = SHA384_DIGEST_SIZE,
			.halg.base = अणु
				.cra_name = "hmac(sha384)",
				.cra_driver_name = "hmac-sha384-chcr",
				.cra_blocksize = SHA384_BLOCK_SIZE,
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_HMAC,
		.is_रेजिस्टरed = 0,
		.alg.hash = अणु
			.halg.digestsize = SHA512_DIGEST_SIZE,
			.halg.base = अणु
				.cra_name = "hmac(sha512)",
				.cra_driver_name = "hmac-sha512-chcr",
				.cra_blocksize = SHA512_BLOCK_SIZE,
			पूर्ण
		पूर्ण
	पूर्ण,
	/* Add AEAD Algorithms */
	अणु
		.type = CRYPTO_ALG_TYPE_AEAD | CRYPTO_ALG_SUB_TYPE_AEAD_GCM,
		.is_रेजिस्टरed = 0,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "gcm(aes)",
				.cra_driver_name = "gcm-aes-chcr",
				.cra_blocksize	= 1,
				.cra_priority = CHCR_AEAD_PRIORITY,
				.cra_ctxsize =	माप(काष्ठा chcr_context) +
						माप(काष्ठा chcr_aead_ctx) +
						माप(काष्ठा chcr_gcm_ctx),
			पूर्ण,
			.ivsize = GCM_AES_IV_SIZE,
			.maxauthsize = GHASH_DIGEST_SIZE,
			.setkey = chcr_gcm_setkey,
			.setauthsize = chcr_gcm_setauthsize,
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_AEAD | CRYPTO_ALG_SUB_TYPE_AEAD_RFC4106,
		.is_रेजिस्टरed = 0,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "rfc4106(gcm(aes))",
				.cra_driver_name = "rfc4106-gcm-aes-chcr",
				.cra_blocksize	 = 1,
				.cra_priority = CHCR_AEAD_PRIORITY + 1,
				.cra_ctxsize =	माप(काष्ठा chcr_context) +
						माप(काष्ठा chcr_aead_ctx) +
						माप(काष्ठा chcr_gcm_ctx),

			पूर्ण,
			.ivsize = GCM_RFC4106_IV_SIZE,
			.maxauthsize	= GHASH_DIGEST_SIZE,
			.setkey = chcr_gcm_setkey,
			.setauthsize	= chcr_4106_4309_setauthsize,
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_AEAD | CRYPTO_ALG_SUB_TYPE_AEAD_CCM,
		.is_रेजिस्टरed = 0,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "ccm(aes)",
				.cra_driver_name = "ccm-aes-chcr",
				.cra_blocksize	 = 1,
				.cra_priority = CHCR_AEAD_PRIORITY,
				.cra_ctxsize =	माप(काष्ठा chcr_context) +
						माप(काष्ठा chcr_aead_ctx),

			पूर्ण,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize	= GHASH_DIGEST_SIZE,
			.setkey = chcr_aead_ccm_setkey,
			.setauthsize	= chcr_ccm_setauthsize,
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_AEAD | CRYPTO_ALG_SUB_TYPE_AEAD_RFC4309,
		.is_रेजिस्टरed = 0,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "rfc4309(ccm(aes))",
				.cra_driver_name = "rfc4309-ccm-aes-chcr",
				.cra_blocksize	 = 1,
				.cra_priority = CHCR_AEAD_PRIORITY + 1,
				.cra_ctxsize =	माप(काष्ठा chcr_context) +
						माप(काष्ठा chcr_aead_ctx),

			पूर्ण,
			.ivsize = 8,
			.maxauthsize	= GHASH_DIGEST_SIZE,
			.setkey = chcr_aead_rfc4309_setkey,
			.setauthsize = chcr_4106_4309_setauthsize,
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_AEAD | CRYPTO_ALG_SUB_TYPE_CBC_SHA,
		.is_रेजिस्टरed = 0,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha1),cbc(aes))",
				.cra_driver_name =
					"authenc-hmac-sha1-cbc-aes-chcr",
				.cra_blocksize	 = AES_BLOCK_SIZE,
				.cra_priority = CHCR_AEAD_PRIORITY,
				.cra_ctxsize =	माप(काष्ठा chcr_context) +
						माप(काष्ठा chcr_aead_ctx) +
						माप(काष्ठा chcr_authenc_ctx),

			पूर्ण,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
			.setkey = chcr_authenc_setkey,
			.setauthsize = chcr_authenc_setauthsize,
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_AEAD | CRYPTO_ALG_SUB_TYPE_CBC_SHA,
		.is_रेजिस्टरed = 0,
		.alg.aead = अणु
			.base = अणु

				.cra_name = "authenc(hmac(sha256),cbc(aes))",
				.cra_driver_name =
					"authenc-hmac-sha256-cbc-aes-chcr",
				.cra_blocksize	 = AES_BLOCK_SIZE,
				.cra_priority = CHCR_AEAD_PRIORITY,
				.cra_ctxsize =	माप(काष्ठा chcr_context) +
						माप(काष्ठा chcr_aead_ctx) +
						माप(काष्ठा chcr_authenc_ctx),

			पूर्ण,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize	= SHA256_DIGEST_SIZE,
			.setkey = chcr_authenc_setkey,
			.setauthsize = chcr_authenc_setauthsize,
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_AEAD | CRYPTO_ALG_SUB_TYPE_CBC_SHA,
		.is_रेजिस्टरed = 0,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha224),cbc(aes))",
				.cra_driver_name =
					"authenc-hmac-sha224-cbc-aes-chcr",
				.cra_blocksize	 = AES_BLOCK_SIZE,
				.cra_priority = CHCR_AEAD_PRIORITY,
				.cra_ctxsize =	माप(काष्ठा chcr_context) +
						माप(काष्ठा chcr_aead_ctx) +
						माप(काष्ठा chcr_authenc_ctx),
			पूर्ण,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA224_DIGEST_SIZE,
			.setkey = chcr_authenc_setkey,
			.setauthsize = chcr_authenc_setauthsize,
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_AEAD | CRYPTO_ALG_SUB_TYPE_CBC_SHA,
		.is_रेजिस्टरed = 0,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha384),cbc(aes))",
				.cra_driver_name =
					"authenc-hmac-sha384-cbc-aes-chcr",
				.cra_blocksize	 = AES_BLOCK_SIZE,
				.cra_priority = CHCR_AEAD_PRIORITY,
				.cra_ctxsize =	माप(काष्ठा chcr_context) +
						माप(काष्ठा chcr_aead_ctx) +
						माप(काष्ठा chcr_authenc_ctx),

			पूर्ण,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA384_DIGEST_SIZE,
			.setkey = chcr_authenc_setkey,
			.setauthsize = chcr_authenc_setauthsize,
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_AEAD | CRYPTO_ALG_SUB_TYPE_CBC_SHA,
		.is_रेजिस्टरed = 0,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha512),cbc(aes))",
				.cra_driver_name =
					"authenc-hmac-sha512-cbc-aes-chcr",
				.cra_blocksize	 = AES_BLOCK_SIZE,
				.cra_priority = CHCR_AEAD_PRIORITY,
				.cra_ctxsize =	माप(काष्ठा chcr_context) +
						माप(काष्ठा chcr_aead_ctx) +
						माप(काष्ठा chcr_authenc_ctx),

			पूर्ण,
			.ivsize = AES_BLOCK_SIZE,
			.maxauthsize = SHA512_DIGEST_SIZE,
			.setkey = chcr_authenc_setkey,
			.setauthsize = chcr_authenc_setauthsize,
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_AEAD | CRYPTO_ALG_SUB_TYPE_CBC_शून्य,
		.is_रेजिस्टरed = 0,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(digest_null,cbc(aes))",
				.cra_driver_name =
					"authenc-digest_null-cbc-aes-chcr",
				.cra_blocksize	 = AES_BLOCK_SIZE,
				.cra_priority = CHCR_AEAD_PRIORITY,
				.cra_ctxsize =	माप(काष्ठा chcr_context) +
						माप(काष्ठा chcr_aead_ctx) +
						माप(काष्ठा chcr_authenc_ctx),

			पूर्ण,
			.ivsize  = AES_BLOCK_SIZE,
			.maxauthsize = 0,
			.setkey  = chcr_aead_digest_null_setkey,
			.setauthsize = chcr_authenc_null_setauthsize,
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_AEAD | CRYPTO_ALG_SUB_TYPE_CTR_SHA,
		.is_रेजिस्टरed = 0,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha1),rfc3686(ctr(aes)))",
				.cra_driver_name =
				"authenc-hmac-sha1-rfc3686-ctr-aes-chcr",
				.cra_blocksize	 = 1,
				.cra_priority = CHCR_AEAD_PRIORITY,
				.cra_ctxsize =	माप(काष्ठा chcr_context) +
						माप(काष्ठा chcr_aead_ctx) +
						माप(काष्ठा chcr_authenc_ctx),

			पूर्ण,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.maxauthsize = SHA1_DIGEST_SIZE,
			.setkey = chcr_authenc_setkey,
			.setauthsize = chcr_authenc_setauthsize,
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_AEAD | CRYPTO_ALG_SUB_TYPE_CTR_SHA,
		.is_रेजिस्टरed = 0,
		.alg.aead = अणु
			.base = अणु

				.cra_name = "authenc(hmac(sha256),rfc3686(ctr(aes)))",
				.cra_driver_name =
				"authenc-hmac-sha256-rfc3686-ctr-aes-chcr",
				.cra_blocksize	 = 1,
				.cra_priority = CHCR_AEAD_PRIORITY,
				.cra_ctxsize =	माप(काष्ठा chcr_context) +
						माप(काष्ठा chcr_aead_ctx) +
						माप(काष्ठा chcr_authenc_ctx),

			पूर्ण,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.maxauthsize	= SHA256_DIGEST_SIZE,
			.setkey = chcr_authenc_setkey,
			.setauthsize = chcr_authenc_setauthsize,
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_AEAD | CRYPTO_ALG_SUB_TYPE_CTR_SHA,
		.is_रेजिस्टरed = 0,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha224),rfc3686(ctr(aes)))",
				.cra_driver_name =
				"authenc-hmac-sha224-rfc3686-ctr-aes-chcr",
				.cra_blocksize	 = 1,
				.cra_priority = CHCR_AEAD_PRIORITY,
				.cra_ctxsize =	माप(काष्ठा chcr_context) +
						माप(काष्ठा chcr_aead_ctx) +
						माप(काष्ठा chcr_authenc_ctx),
			पूर्ण,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.maxauthsize = SHA224_DIGEST_SIZE,
			.setkey = chcr_authenc_setkey,
			.setauthsize = chcr_authenc_setauthsize,
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_AEAD | CRYPTO_ALG_SUB_TYPE_CTR_SHA,
		.is_रेजिस्टरed = 0,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha384),rfc3686(ctr(aes)))",
				.cra_driver_name =
				"authenc-hmac-sha384-rfc3686-ctr-aes-chcr",
				.cra_blocksize	 = 1,
				.cra_priority = CHCR_AEAD_PRIORITY,
				.cra_ctxsize =	माप(काष्ठा chcr_context) +
						माप(काष्ठा chcr_aead_ctx) +
						माप(काष्ठा chcr_authenc_ctx),

			पूर्ण,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.maxauthsize = SHA384_DIGEST_SIZE,
			.setkey = chcr_authenc_setkey,
			.setauthsize = chcr_authenc_setauthsize,
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_AEAD | CRYPTO_ALG_SUB_TYPE_CTR_SHA,
		.is_रेजिस्टरed = 0,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(hmac(sha512),rfc3686(ctr(aes)))",
				.cra_driver_name =
				"authenc-hmac-sha512-rfc3686-ctr-aes-chcr",
				.cra_blocksize	 = 1,
				.cra_priority = CHCR_AEAD_PRIORITY,
				.cra_ctxsize =	माप(काष्ठा chcr_context) +
						माप(काष्ठा chcr_aead_ctx) +
						माप(काष्ठा chcr_authenc_ctx),

			पूर्ण,
			.ivsize = CTR_RFC3686_IV_SIZE,
			.maxauthsize = SHA512_DIGEST_SIZE,
			.setkey = chcr_authenc_setkey,
			.setauthsize = chcr_authenc_setauthsize,
		पूर्ण
	पूर्ण,
	अणु
		.type = CRYPTO_ALG_TYPE_AEAD | CRYPTO_ALG_SUB_TYPE_CTR_शून्य,
		.is_रेजिस्टरed = 0,
		.alg.aead = अणु
			.base = अणु
				.cra_name = "authenc(digest_null,rfc3686(ctr(aes)))",
				.cra_driver_name =
				"authenc-digest_null-rfc3686-ctr-aes-chcr",
				.cra_blocksize	 = 1,
				.cra_priority = CHCR_AEAD_PRIORITY,
				.cra_ctxsize =	माप(काष्ठा chcr_context) +
						माप(काष्ठा chcr_aead_ctx) +
						माप(काष्ठा chcr_authenc_ctx),

			पूर्ण,
			.ivsize  = CTR_RFC3686_IV_SIZE,
			.maxauthsize = 0,
			.setkey  = chcr_aead_digest_null_setkey,
			.setauthsize = chcr_authenc_null_setauthsize,
		पूर्ण
	पूर्ण,
पूर्ण;

/*
 *	chcr_unरेजिस्टर_alg - Deरेजिस्टर crypto algorithms with
 *	kernel framework.
 */
अटल पूर्णांक chcr_unरेजिस्टर_alg(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(driver_algs); i++) अणु
		चयन (driver_algs[i].type & CRYPTO_ALG_TYPE_MASK) अणु
		हाल CRYPTO_ALG_TYPE_SKCIPHER:
			अगर (driver_algs[i].is_रेजिस्टरed && refcount_पढ़ो(
			    &driver_algs[i].alg.skcipher.base.cra_refcnt)
			    == 1) अणु
				crypto_unरेजिस्टर_skcipher(
						&driver_algs[i].alg.skcipher);
				driver_algs[i].is_रेजिस्टरed = 0;
			पूर्ण
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AEAD:
			अगर (driver_algs[i].is_रेजिस्टरed && refcount_पढ़ो(
			    &driver_algs[i].alg.aead.base.cra_refcnt) == 1) अणु
				crypto_unरेजिस्टर_aead(
						&driver_algs[i].alg.aead);
				driver_algs[i].is_रेजिस्टरed = 0;
			पूर्ण
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AHASH:
			अगर (driver_algs[i].is_रेजिस्टरed && refcount_पढ़ो(
			    &driver_algs[i].alg.hash.halg.base.cra_refcnt)
			    == 1) अणु
				crypto_unरेजिस्टर_ahash(
						&driver_algs[i].alg.hash);
				driver_algs[i].is_रेजिस्टरed = 0;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा SZ_AHASH_CTX माप(काष्ठा chcr_context)
#घोषणा SZ_AHASH_H_CTX (माप(काष्ठा chcr_context) + माप(काष्ठा hmac_ctx))
#घोषणा SZ_AHASH_REQ_CTX माप(काष्ठा chcr_ahash_req_ctx)

/*
 *	chcr_रेजिस्टर_alg - Register crypto algorithms with kernel framework.
 */
अटल पूर्णांक chcr_रेजिस्टर_alg(व्योम)
अणु
	काष्ठा crypto_alg ai;
	काष्ठा ahash_alg *a_hash;
	पूर्णांक err = 0, i;
	अक्षर *name = शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(driver_algs); i++) अणु
		अगर (driver_algs[i].is_रेजिस्टरed)
			जारी;
		चयन (driver_algs[i].type & CRYPTO_ALG_TYPE_MASK) अणु
		हाल CRYPTO_ALG_TYPE_SKCIPHER:
			driver_algs[i].alg.skcipher.base.cra_priority =
				CHCR_CRA_PRIORITY;
			driver_algs[i].alg.skcipher.base.cra_module = THIS_MODULE;
			driver_algs[i].alg.skcipher.base.cra_flags =
				CRYPTO_ALG_TYPE_SKCIPHER | CRYPTO_ALG_ASYNC |
				CRYPTO_ALG_ALLOCATES_MEMORY |
				CRYPTO_ALG_NEED_FALLBACK;
			driver_algs[i].alg.skcipher.base.cra_ctxsize =
				माप(काष्ठा chcr_context) +
				माप(काष्ठा ablk_ctx);
			driver_algs[i].alg.skcipher.base.cra_alignmask = 0;

			err = crypto_रेजिस्टर_skcipher(&driver_algs[i].alg.skcipher);
			name = driver_algs[i].alg.skcipher.base.cra_driver_name;
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AEAD:
			driver_algs[i].alg.aead.base.cra_flags =
				CRYPTO_ALG_ASYNC | CRYPTO_ALG_NEED_FALLBACK |
				CRYPTO_ALG_ALLOCATES_MEMORY;
			driver_algs[i].alg.aead.encrypt = chcr_aead_encrypt;
			driver_algs[i].alg.aead.decrypt = chcr_aead_decrypt;
			driver_algs[i].alg.aead.init = chcr_aead_cra_init;
			driver_algs[i].alg.aead.निकास = chcr_aead_cra_निकास;
			driver_algs[i].alg.aead.base.cra_module = THIS_MODULE;
			err = crypto_रेजिस्टर_aead(&driver_algs[i].alg.aead);
			name = driver_algs[i].alg.aead.base.cra_driver_name;
			अवरोध;
		हाल CRYPTO_ALG_TYPE_AHASH:
			a_hash = &driver_algs[i].alg.hash;
			a_hash->update = chcr_ahash_update;
			a_hash->final = chcr_ahash_final;
			a_hash->finup = chcr_ahash_finup;
			a_hash->digest = chcr_ahash_digest;
			a_hash->export = chcr_ahash_export;
			a_hash->import = chcr_ahash_import;
			a_hash->halg.statesize = SZ_AHASH_REQ_CTX;
			a_hash->halg.base.cra_priority = CHCR_CRA_PRIORITY;
			a_hash->halg.base.cra_module = THIS_MODULE;
			a_hash->halg.base.cra_flags =
				CRYPTO_ALG_ASYNC | CRYPTO_ALG_ALLOCATES_MEMORY;
			a_hash->halg.base.cra_alignmask = 0;
			a_hash->halg.base.cra_निकास = शून्य;

			अगर (driver_algs[i].type == CRYPTO_ALG_TYPE_HMAC) अणु
				a_hash->halg.base.cra_init = chcr_hmac_cra_init;
				a_hash->halg.base.cra_निकास = chcr_hmac_cra_निकास;
				a_hash->init = chcr_hmac_init;
				a_hash->setkey = chcr_ahash_setkey;
				a_hash->halg.base.cra_ctxsize = SZ_AHASH_H_CTX;
			पूर्ण अन्यथा अणु
				a_hash->init = chcr_sha_init;
				a_hash->halg.base.cra_ctxsize = SZ_AHASH_CTX;
				a_hash->halg.base.cra_init = chcr_sha_cra_init;
			पूर्ण
			err = crypto_रेजिस्टर_ahash(&driver_algs[i].alg.hash);
			ai = driver_algs[i].alg.hash.halg.base;
			name = ai.cra_driver_name;
			अवरोध;
		पूर्ण
		अगर (err) अणु
			pr_err("%s : Algorithm registration failed\n", name);
			जाओ रेजिस्टर_err;
		पूर्ण अन्यथा अणु
			driver_algs[i].is_रेजिस्टरed = 1;
		पूर्ण
	पूर्ण
	वापस 0;

रेजिस्टर_err:
	chcr_unरेजिस्टर_alg();
	वापस err;
पूर्ण

/*
 *	start_crypto - Register the crypto algorithms.
 *	This should called once when the first device comesup. After this
 *	kernel will start calling driver APIs क्रम crypto operations.
 */
पूर्णांक start_crypto(व्योम)
अणु
	वापस chcr_रेजिस्टर_alg();
पूर्ण

/*
 *	stop_crypto - Deरेजिस्टर all the crypto algorithms with kernel.
 *	This should be called once when the last device goes करोwn. After this
 *	kernel will not call the driver API क्रम crypto operations.
 */
पूर्णांक stop_crypto(व्योम)
अणु
	chcr_unरेजिस्टर_alg();
	वापस 0;
पूर्ण
