<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Synchronous Compression operations
 *
 * Copyright 2015 LG Electronics Inc.
 * Copyright (c) 2016, Intel Corporation
 * Author: Giovanni Cabiddu <giovanni.cabiddu@पूर्णांकel.com>
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/crypto.h>
#समावेश <linux/compiler.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <crypto/algapi.h>
#समावेश <linux/cryptouser.h>
#समावेश <net/netlink.h>
#समावेश <linux/scatterlist.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/पूर्णांकernal/acompress.h>
#समावेश <crypto/पूर्णांकernal/scompress.h>
#समावेश "internal.h"

काष्ठा scomp_scratch अणु
	spinlock_t	lock;
	व्योम		*src;
	व्योम		*dst;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा scomp_scratch, scomp_scratch) = अणु
	.lock = __SPIN_LOCK_UNLOCKED(scomp_scratch.lock),
पूर्ण;

अटल स्थिर काष्ठा crypto_type crypto_scomp_type;
अटल पूर्णांक scomp_scratch_users;
अटल DEFINE_MUTEX(scomp_lock);

#अगर_घोषित CONFIG_NET
अटल पूर्णांक crypto_scomp_report(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_report_comp rscomp;

	स_रखो(&rscomp, 0, माप(rscomp));

	strscpy(rscomp.type, "scomp", माप(rscomp.type));

	वापस nla_put(skb, CRYPTOCFGA_REPORT_COMPRESS,
		       माप(rscomp), &rscomp);
पूर्ण
#अन्यथा
अटल पूर्णांक crypto_scomp_report(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर

अटल व्योम crypto_scomp_show(काष्ठा seq_file *m, काष्ठा crypto_alg *alg)
	__maybe_unused;

अटल व्योम crypto_scomp_show(काष्ठा seq_file *m, काष्ठा crypto_alg *alg)
अणु
	seq_माला_दो(m, "type         : scomp\n");
पूर्ण

अटल व्योम crypto_scomp_मुक्त_scratches(व्योम)
अणु
	काष्ठा scomp_scratch *scratch;
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		scratch = per_cpu_ptr(&scomp_scratch, i);

		vमुक्त(scratch->src);
		vमुक्त(scratch->dst);
		scratch->src = शून्य;
		scratch->dst = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक crypto_scomp_alloc_scratches(व्योम)
अणु
	काष्ठा scomp_scratch *scratch;
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		व्योम *mem;

		scratch = per_cpu_ptr(&scomp_scratch, i);

		mem = vदो_स्मृति_node(SCOMP_SCRATCH_SIZE, cpu_to_node(i));
		अगर (!mem)
			जाओ error;
		scratch->src = mem;
		mem = vदो_स्मृति_node(SCOMP_SCRATCH_SIZE, cpu_to_node(i));
		अगर (!mem)
			जाओ error;
		scratch->dst = mem;
	पूर्ण
	वापस 0;
error:
	crypto_scomp_मुक्त_scratches();
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक crypto_scomp_init_tfm(काष्ठा crypto_tfm *tfm)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&scomp_lock);
	अगर (!scomp_scratch_users++)
		ret = crypto_scomp_alloc_scratches();
	mutex_unlock(&scomp_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक scomp_acomp_comp_decomp(काष्ठा acomp_req *req, पूर्णांक dir)
अणु
	काष्ठा crypto_acomp *tfm = crypto_acomp_reqtfm(req);
	व्योम **tfm_ctx = acomp_tfm_ctx(tfm);
	काष्ठा crypto_scomp *scomp = *tfm_ctx;
	व्योम **ctx = acomp_request_ctx(req);
	काष्ठा scomp_scratch *scratch;
	पूर्णांक ret;

	अगर (!req->src || !req->slen || req->slen > SCOMP_SCRATCH_SIZE)
		वापस -EINVAL;

	अगर (req->dst && !req->dlen)
		वापस -EINVAL;

	अगर (!req->dlen || req->dlen > SCOMP_SCRATCH_SIZE)
		req->dlen = SCOMP_SCRATCH_SIZE;

	scratch = raw_cpu_ptr(&scomp_scratch);
	spin_lock(&scratch->lock);

	scatterwalk_map_and_copy(scratch->src, req->src, 0, req->slen, 0);
	अगर (dir)
		ret = crypto_scomp_compress(scomp, scratch->src, req->slen,
					    scratch->dst, &req->dlen, *ctx);
	अन्यथा
		ret = crypto_scomp_decompress(scomp, scratch->src, req->slen,
					      scratch->dst, &req->dlen, *ctx);
	अगर (!ret) अणु
		अगर (!req->dst) अणु
			req->dst = sgl_alloc(req->dlen, GFP_ATOMIC, शून्य);
			अगर (!req->dst) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
		पूर्ण
		scatterwalk_map_and_copy(scratch->dst, req->dst, 0, req->dlen,
					 1);
	पूर्ण
out:
	spin_unlock(&scratch->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक scomp_acomp_compress(काष्ठा acomp_req *req)
अणु
	वापस scomp_acomp_comp_decomp(req, 1);
पूर्ण

अटल पूर्णांक scomp_acomp_decompress(काष्ठा acomp_req *req)
अणु
	वापस scomp_acomp_comp_decomp(req, 0);
पूर्ण

अटल व्योम crypto_निकास_scomp_ops_async(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_scomp **ctx = crypto_tfm_ctx(tfm);

	crypto_मुक्त_scomp(*ctx);

	mutex_lock(&scomp_lock);
	अगर (!--scomp_scratch_users)
		crypto_scomp_मुक्त_scratches();
	mutex_unlock(&scomp_lock);
पूर्ण

पूर्णांक crypto_init_scomp_ops_async(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_alg *calg = tfm->__crt_alg;
	काष्ठा crypto_acomp *crt = __crypto_acomp_tfm(tfm);
	काष्ठा crypto_scomp **ctx = crypto_tfm_ctx(tfm);
	काष्ठा crypto_scomp *scomp;

	अगर (!crypto_mod_get(calg))
		वापस -EAGAIN;

	scomp = crypto_create_tfm(calg, &crypto_scomp_type);
	अगर (IS_ERR(scomp)) अणु
		crypto_mod_put(calg);
		वापस PTR_ERR(scomp);
	पूर्ण

	*ctx = scomp;
	tfm->निकास = crypto_निकास_scomp_ops_async;

	crt->compress = scomp_acomp_compress;
	crt->decompress = scomp_acomp_decompress;
	crt->dst_मुक्त = sgl_मुक्त;
	crt->reqsize = माप(व्योम *);

	वापस 0;
पूर्ण

काष्ठा acomp_req *crypto_acomp_scomp_alloc_ctx(काष्ठा acomp_req *req)
अणु
	काष्ठा crypto_acomp *acomp = crypto_acomp_reqtfm(req);
	काष्ठा crypto_tfm *tfm = crypto_acomp_tfm(acomp);
	काष्ठा crypto_scomp **tfm_ctx = crypto_tfm_ctx(tfm);
	काष्ठा crypto_scomp *scomp = *tfm_ctx;
	व्योम *ctx;

	ctx = crypto_scomp_alloc_ctx(scomp);
	अगर (IS_ERR(ctx)) अणु
		kमुक्त(req);
		वापस शून्य;
	पूर्ण

	*req->__ctx = ctx;

	वापस req;
पूर्ण

व्योम crypto_acomp_scomp_मुक्त_ctx(काष्ठा acomp_req *req)
अणु
	काष्ठा crypto_acomp *acomp = crypto_acomp_reqtfm(req);
	काष्ठा crypto_tfm *tfm = crypto_acomp_tfm(acomp);
	काष्ठा crypto_scomp **tfm_ctx = crypto_tfm_ctx(tfm);
	काष्ठा crypto_scomp *scomp = *tfm_ctx;
	व्योम *ctx = *req->__ctx;

	अगर (ctx)
		crypto_scomp_मुक्त_ctx(scomp, ctx);
पूर्ण

अटल स्थिर काष्ठा crypto_type crypto_scomp_type = अणु
	.extsize = crypto_alg_extsize,
	.init_tfm = crypto_scomp_init_tfm,
#अगर_घोषित CONFIG_PROC_FS
	.show = crypto_scomp_show,
#पूर्ण_अगर
	.report = crypto_scomp_report,
	.maskclear = ~CRYPTO_ALG_TYPE_MASK,
	.maskset = CRYPTO_ALG_TYPE_MASK,
	.type = CRYPTO_ALG_TYPE_SCOMPRESS,
	.tfmsize = दुरत्व(काष्ठा crypto_scomp, base),
पूर्ण;

पूर्णांक crypto_रेजिस्टर_scomp(काष्ठा scomp_alg *alg)
अणु
	काष्ठा crypto_alg *base = &alg->base;

	base->cra_type = &crypto_scomp_type;
	base->cra_flags &= ~CRYPTO_ALG_TYPE_MASK;
	base->cra_flags |= CRYPTO_ALG_TYPE_SCOMPRESS;

	वापस crypto_रेजिस्टर_alg(base);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_रेजिस्टर_scomp);

व्योम crypto_unरेजिस्टर_scomp(काष्ठा scomp_alg *alg)
अणु
	crypto_unरेजिस्टर_alg(&alg->base);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_unरेजिस्टर_scomp);

पूर्णांक crypto_रेजिस्टर_scomps(काष्ठा scomp_alg *algs, पूर्णांक count)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < count; i++) अणु
		ret = crypto_रेजिस्टर_scomp(&algs[i]);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	क्रम (--i; i >= 0; --i)
		crypto_unरेजिस्टर_scomp(&algs[i]);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_रेजिस्टर_scomps);

व्योम crypto_unरेजिस्टर_scomps(काष्ठा scomp_alg *algs, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = count - 1; i >= 0; --i)
		crypto_unरेजिस्टर_scomp(&algs[i]);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_unरेजिस्टर_scomps);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Synchronous compression type");
