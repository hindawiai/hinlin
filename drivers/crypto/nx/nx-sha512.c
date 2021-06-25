<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SHA-512 routines supporting the Power 7+ Nest Accelerators driver
 *
 * Copyright (C) 2011-2012 International Business Machines Inc.
 *
 * Author: Kent Yoder <yoder1@us.ibm.com>
 */

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/sha2.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/vपन.स>

#समावेश "nx_csbcpb.h"
#समावेश "nx.h"


अटल पूर्णांक nx_crypto_ctx_sha512_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_tfm_ctx(tfm);
	पूर्णांक err;

	err = nx_crypto_ctx_sha_init(tfm);
	अगर (err)
		वापस err;

	nx_ctx_init(nx_ctx, HCOP_FC_SHA);

	nx_ctx->ap = &nx_ctx->props[NX_PROPS_SHA512];

	NX_CPB_SET_DIGEST_SIZE(nx_ctx->csbcpb, NX_DS_SHA512);

	वापस 0;
पूर्ण

अटल पूर्णांक nx_sha512_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा sha512_state *sctx = shash_desc_ctx(desc);

	स_रखो(sctx, 0, माप *sctx);

	sctx->state[0] = __cpu_to_be64(SHA512_H0);
	sctx->state[1] = __cpu_to_be64(SHA512_H1);
	sctx->state[2] = __cpu_to_be64(SHA512_H2);
	sctx->state[3] = __cpu_to_be64(SHA512_H3);
	sctx->state[4] = __cpu_to_be64(SHA512_H4);
	sctx->state[5] = __cpu_to_be64(SHA512_H5);
	sctx->state[6] = __cpu_to_be64(SHA512_H6);
	sctx->state[7] = __cpu_to_be64(SHA512_H7);
	sctx->count[0] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक nx_sha512_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			    अचिन्हित पूर्णांक len)
अणु
	काष्ठा sha512_state *sctx = shash_desc_ctx(desc);
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_tfm_ctx(&desc->tfm->base);
	काष्ठा nx_csbcpb *csbcpb = (काष्ठा nx_csbcpb *)nx_ctx->csbcpb;
	काष्ठा nx_sg *out_sg;
	u64 to_process, leftover = 0, total;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक rc = 0;
	पूर्णांक data_len;
	u32 max_sg_len;
	u64 buf_len = (sctx->count[0] % SHA512_BLOCK_SIZE);

	spin_lock_irqsave(&nx_ctx->lock, irq_flags);

	/* 2 हालs क्रम total data len:
	 *  1: < SHA512_BLOCK_SIZE: copy पूर्णांकo state, वापस 0
	 *  2: >= SHA512_BLOCK_SIZE: process X blocks, copy in leftover
	 */
	total = (sctx->count[0] % SHA512_BLOCK_SIZE) + len;
	अगर (total < SHA512_BLOCK_SIZE) अणु
		स_नकल(sctx->buf + buf_len, data, len);
		sctx->count[0] += len;
		जाओ out;
	पूर्ण

	स_नकल(csbcpb->cpb.sha512.message_digest, sctx->state, SHA512_DIGEST_SIZE);
	NX_CPB_FDM(csbcpb) |= NX_FDM_INTERMEDIATE;
	NX_CPB_FDM(csbcpb) |= NX_FDM_CONTINUATION;

	max_sg_len = min_t(u64, nx_ctx->ap->sglen,
			nx_driver.of.max_sg_len/माप(काष्ठा nx_sg));
	max_sg_len = min_t(u64, max_sg_len,
			nx_ctx->ap->databytelen/NX_PAGE_SIZE);

	data_len = SHA512_DIGEST_SIZE;
	out_sg = nx_build_sg_list(nx_ctx->out_sg, (u8 *)sctx->state,
				  &data_len, max_sg_len);
	nx_ctx->op.outlen = (nx_ctx->out_sg - out_sg) * माप(काष्ठा nx_sg);

	अगर (data_len != SHA512_DIGEST_SIZE) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	करो अणु
		पूर्णांक used_sgs = 0;
		काष्ठा nx_sg *in_sg = nx_ctx->in_sg;

		अगर (buf_len) अणु
			data_len = buf_len;
			in_sg = nx_build_sg_list(in_sg,
						 (u8 *) sctx->buf,
						 &data_len, max_sg_len);

			अगर (data_len != buf_len) अणु
				rc = -EINVAL;
				जाओ out;
			पूर्ण
			used_sgs = in_sg - nx_ctx->in_sg;
		पूर्ण

		/* to_process: SHA512_BLOCK_SIZE aligned chunk to be
		 * processed in this iteration. This value is restricted
		 * by sg list limits and number of sgs we alपढ़ोy used
		 * क्रम leftover data. (see above)
		 * In ideal हाल, we could allow NX_PAGE_SIZE * max_sg_len,
		 * but because data may not be aligned, we need to account
		 * क्रम that too. */
		to_process = min_t(u64, total,
			(max_sg_len - 1 - used_sgs) * NX_PAGE_SIZE);
		to_process = to_process & ~(SHA512_BLOCK_SIZE - 1);

		data_len = to_process - buf_len;
		in_sg = nx_build_sg_list(in_sg, (u8 *) data,
					 &data_len, max_sg_len);

		nx_ctx->op.inlen = (nx_ctx->in_sg - in_sg) * माप(काष्ठा nx_sg);

		अगर (data_len != (to_process - buf_len)) अणु
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		to_process = data_len + buf_len;
		leftover = total - to_process;

		/*
		 * we've hit the nx chip previously and we're updating
		 * again, so copy over the partial digest.
		 */
		स_नकल(csbcpb->cpb.sha512.input_partial_digest,
			       csbcpb->cpb.sha512.message_digest,
			       SHA512_DIGEST_SIZE);

		अगर (!nx_ctx->op.inlen || !nx_ctx->op.outlen) अणु
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		rc = nx_hcall_sync(nx_ctx, &nx_ctx->op, 0);
		अगर (rc)
			जाओ out;

		atomic_inc(&(nx_ctx->stats->sha512_ops));

		total -= to_process;
		data += to_process - buf_len;
		buf_len = 0;

	पूर्ण जबतक (leftover >= SHA512_BLOCK_SIZE);

	/* copy the leftover back पूर्णांकo the state काष्ठा */
	अगर (leftover)
		स_नकल(sctx->buf, data, leftover);
	sctx->count[0] += len;
	स_नकल(sctx->state, csbcpb->cpb.sha512.message_digest, SHA512_DIGEST_SIZE);
out:
	spin_unlock_irqrestore(&nx_ctx->lock, irq_flags);
	वापस rc;
पूर्ण

अटल पूर्णांक nx_sha512_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा sha512_state *sctx = shash_desc_ctx(desc);
	काष्ठा nx_crypto_ctx *nx_ctx = crypto_tfm_ctx(&desc->tfm->base);
	काष्ठा nx_csbcpb *csbcpb = (काष्ठा nx_csbcpb *)nx_ctx->csbcpb;
	काष्ठा nx_sg *in_sg, *out_sg;
	u32 max_sg_len;
	u64 count0;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक rc = 0;
	पूर्णांक len;

	spin_lock_irqsave(&nx_ctx->lock, irq_flags);

	max_sg_len = min_t(u64, nx_ctx->ap->sglen,
			nx_driver.of.max_sg_len/माप(काष्ठा nx_sg));
	max_sg_len = min_t(u64, max_sg_len,
			nx_ctx->ap->databytelen/NX_PAGE_SIZE);

	/* final is represented by continuing the operation and indicating that
	 * this is not an पूर्णांकermediate operation */
	अगर (sctx->count[0] >= SHA512_BLOCK_SIZE) अणु
		/* we've hit the nx chip previously, now we're finalizing,
		 * so copy over the partial digest */
		स_नकल(csbcpb->cpb.sha512.input_partial_digest, sctx->state,
							SHA512_DIGEST_SIZE);
		NX_CPB_FDM(csbcpb) &= ~NX_FDM_INTERMEDIATE;
		NX_CPB_FDM(csbcpb) |= NX_FDM_CONTINUATION;
	पूर्ण अन्यथा अणु
		NX_CPB_FDM(csbcpb) &= ~NX_FDM_INTERMEDIATE;
		NX_CPB_FDM(csbcpb) &= ~NX_FDM_CONTINUATION;
	पूर्ण

	NX_CPB_FDM(csbcpb) &= ~NX_FDM_INTERMEDIATE;

	count0 = sctx->count[0] * 8;

	csbcpb->cpb.sha512.message_bit_length_lo = count0;

	len = sctx->count[0] & (SHA512_BLOCK_SIZE - 1);
	in_sg = nx_build_sg_list(nx_ctx->in_sg, sctx->buf, &len,
				 max_sg_len);

	अगर (len != (sctx->count[0] & (SHA512_BLOCK_SIZE - 1))) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	len = SHA512_DIGEST_SIZE;
	out_sg = nx_build_sg_list(nx_ctx->out_sg, out, &len,
				 max_sg_len);

	nx_ctx->op.inlen = (nx_ctx->in_sg - in_sg) * माप(काष्ठा nx_sg);
	nx_ctx->op.outlen = (nx_ctx->out_sg - out_sg) * माप(काष्ठा nx_sg);

	अगर (!nx_ctx->op.outlen) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	rc = nx_hcall_sync(nx_ctx, &nx_ctx->op, 0);
	अगर (rc)
		जाओ out;

	atomic_inc(&(nx_ctx->stats->sha512_ops));
	atomic64_add(sctx->count[0], &(nx_ctx->stats->sha512_bytes));

	स_नकल(out, csbcpb->cpb.sha512.message_digest, SHA512_DIGEST_SIZE);
out:
	spin_unlock_irqrestore(&nx_ctx->lock, irq_flags);
	वापस rc;
पूर्ण

अटल पूर्णांक nx_sha512_export(काष्ठा shash_desc *desc, व्योम *out)
अणु
	काष्ठा sha512_state *sctx = shash_desc_ctx(desc);

	स_नकल(out, sctx, माप(*sctx));

	वापस 0;
पूर्ण

अटल पूर्णांक nx_sha512_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	काष्ठा sha512_state *sctx = shash_desc_ctx(desc);

	स_नकल(sctx, in, माप(*sctx));

	वापस 0;
पूर्ण

काष्ठा shash_alg nx_shash_sha512_alg = अणु
	.digestsize = SHA512_DIGEST_SIZE,
	.init       = nx_sha512_init,
	.update     = nx_sha512_update,
	.final      = nx_sha512_final,
	.export     = nx_sha512_export,
	.import     = nx_sha512_import,
	.descsize   = माप(काष्ठा sha512_state),
	.statesize  = माप(काष्ठा sha512_state),
	.base       = अणु
		.cra_name        = "sha512",
		.cra_driver_name = "sha512-nx",
		.cra_priority    = 300,
		.cra_blocksize   = SHA512_BLOCK_SIZE,
		.cra_module      = THIS_MODULE,
		.cra_ctxsize     = माप(काष्ठा nx_crypto_ctx),
		.cra_init        = nx_crypto_ctx_sha512_init,
		.cra_निकास        = nx_crypto_ctx_निकास,
	पूर्ण
पूर्ण;
