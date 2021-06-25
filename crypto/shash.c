<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Synchronous Cryptographic Hash operations.
 *
 * Copyright (c) 2008 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/cryptouser.h>
#समावेश <net/netlink.h>
#समावेश <linux/compiler.h>

#समावेश "internal.h"

अटल स्थिर काष्ठा crypto_type crypto_shash_type;

पूर्णांक shash_no_setkey(काष्ठा crypto_shash *tfm, स्थिर u8 *key,
		    अचिन्हित पूर्णांक keylen)
अणु
	वापस -ENOSYS;
पूर्ण
EXPORT_SYMBOL_GPL(shash_no_setkey);

अटल पूर्णांक shash_setkey_unaligned(काष्ठा crypto_shash *tfm, स्थिर u8 *key,
				  अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा shash_alg *shash = crypto_shash_alg(tfm);
	अचिन्हित दीर्घ alignmask = crypto_shash_alignmask(tfm);
	अचिन्हित दीर्घ असलize;
	u8 *buffer, *alignbuffer;
	पूर्णांक err;

	असलize = keylen + (alignmask & ~(crypto_tfm_ctx_alignment() - 1));
	buffer = kदो_स्मृति(असलize, GFP_ATOMIC);
	अगर (!buffer)
		वापस -ENOMEM;

	alignbuffer = (u8 *)ALIGN((अचिन्हित दीर्घ)buffer, alignmask + 1);
	स_नकल(alignbuffer, key, keylen);
	err = shash->setkey(tfm, alignbuffer, keylen);
	kमुक्त_sensitive(buffer);
	वापस err;
पूर्ण

अटल व्योम shash_set_needkey(काष्ठा crypto_shash *tfm, काष्ठा shash_alg *alg)
अणु
	अगर (crypto_shash_alg_needs_key(alg))
		crypto_shash_set_flags(tfm, CRYPTO_TFM_NEED_KEY);
पूर्ण

पूर्णांक crypto_shash_setkey(काष्ठा crypto_shash *tfm, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा shash_alg *shash = crypto_shash_alg(tfm);
	अचिन्हित दीर्घ alignmask = crypto_shash_alignmask(tfm);
	पूर्णांक err;

	अगर ((अचिन्हित दीर्घ)key & alignmask)
		err = shash_setkey_unaligned(tfm, key, keylen);
	अन्यथा
		err = shash->setkey(tfm, key, keylen);

	अगर (unlikely(err)) अणु
		shash_set_needkey(tfm, shash);
		वापस err;
	पूर्ण

	crypto_shash_clear_flags(tfm, CRYPTO_TFM_NEED_KEY);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_shash_setkey);

अटल पूर्णांक shash_update_unaligned(काष्ठा shash_desc *desc, स्थिर u8 *data,
				  अचिन्हित पूर्णांक len)
अणु
	काष्ठा crypto_shash *tfm = desc->tfm;
	काष्ठा shash_alg *shash = crypto_shash_alg(tfm);
	अचिन्हित दीर्घ alignmask = crypto_shash_alignmask(tfm);
	अचिन्हित पूर्णांक unaligned_len = alignmask + 1 -
				     ((अचिन्हित दीर्घ)data & alignmask);
	/*
	 * We cannot count on __aligned() working क्रम large values:
	 * https://patchwork.kernel.org/patch/9507697/
	 */
	u8 ubuf[MAX_ALGAPI_ALIGNMASK * 2];
	u8 *buf = PTR_ALIGN(&ubuf[0], alignmask + 1);
	पूर्णांक err;

	अगर (WARN_ON(buf + unaligned_len > ubuf + माप(ubuf)))
		वापस -EINVAL;

	अगर (unaligned_len > len)
		unaligned_len = len;

	स_नकल(buf, data, unaligned_len);
	err = shash->update(desc, buf, unaligned_len);
	स_रखो(buf, 0, unaligned_len);

	वापस err ?:
	       shash->update(desc, data + unaligned_len, len - unaligned_len);
पूर्ण

पूर्णांक crypto_shash_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			अचिन्हित पूर्णांक len)
अणु
	काष्ठा crypto_shash *tfm = desc->tfm;
	काष्ठा shash_alg *shash = crypto_shash_alg(tfm);
	अचिन्हित दीर्घ alignmask = crypto_shash_alignmask(tfm);

	अगर ((अचिन्हित दीर्घ)data & alignmask)
		वापस shash_update_unaligned(desc, data, len);

	वापस shash->update(desc, data, len);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_shash_update);

अटल पूर्णांक shash_final_unaligned(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा crypto_shash *tfm = desc->tfm;
	अचिन्हित दीर्घ alignmask = crypto_shash_alignmask(tfm);
	काष्ठा shash_alg *shash = crypto_shash_alg(tfm);
	अचिन्हित पूर्णांक ds = crypto_shash_digestsize(tfm);
	/*
	 * We cannot count on __aligned() working क्रम large values:
	 * https://patchwork.kernel.org/patch/9507697/
	 */
	u8 ubuf[MAX_ALGAPI_ALIGNMASK + HASH_MAX_DIGESTSIZE];
	u8 *buf = PTR_ALIGN(&ubuf[0], alignmask + 1);
	पूर्णांक err;

	अगर (WARN_ON(buf + ds > ubuf + माप(ubuf)))
		वापस -EINVAL;

	err = shash->final(desc, buf);
	अगर (err)
		जाओ out;

	स_नकल(out, buf, ds);

out:
	स_रखो(buf, 0, ds);
	वापस err;
पूर्ण

पूर्णांक crypto_shash_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा crypto_shash *tfm = desc->tfm;
	काष्ठा shash_alg *shash = crypto_shash_alg(tfm);
	अचिन्हित दीर्घ alignmask = crypto_shash_alignmask(tfm);

	अगर ((अचिन्हित दीर्घ)out & alignmask)
		वापस shash_final_unaligned(desc, out);

	वापस shash->final(desc, out);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_shash_final);

अटल पूर्णांक shash_finup_unaligned(काष्ठा shash_desc *desc, स्थिर u8 *data,
				 अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस crypto_shash_update(desc, data, len) ?:
	       crypto_shash_final(desc, out);
पूर्ण

पूर्णांक crypto_shash_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
		       अचिन्हित पूर्णांक len, u8 *out)
अणु
	काष्ठा crypto_shash *tfm = desc->tfm;
	काष्ठा shash_alg *shash = crypto_shash_alg(tfm);
	अचिन्हित दीर्घ alignmask = crypto_shash_alignmask(tfm);

	अगर (((अचिन्हित दीर्घ)data | (अचिन्हित दीर्घ)out) & alignmask)
		वापस shash_finup_unaligned(desc, data, len, out);

	वापस shash->finup(desc, data, len, out);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_shash_finup);

अटल पूर्णांक shash_digest_unaligned(काष्ठा shash_desc *desc, स्थिर u8 *data,
				  अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस crypto_shash_init(desc) ?:
	       crypto_shash_finup(desc, data, len, out);
पूर्ण

पूर्णांक crypto_shash_digest(काष्ठा shash_desc *desc, स्थिर u8 *data,
			अचिन्हित पूर्णांक len, u8 *out)
अणु
	काष्ठा crypto_shash *tfm = desc->tfm;
	काष्ठा shash_alg *shash = crypto_shash_alg(tfm);
	अचिन्हित दीर्घ alignmask = crypto_shash_alignmask(tfm);

	अगर (crypto_shash_get_flags(tfm) & CRYPTO_TFM_NEED_KEY)
		वापस -ENOKEY;

	अगर (((अचिन्हित दीर्घ)data | (अचिन्हित दीर्घ)out) & alignmask)
		वापस shash_digest_unaligned(desc, data, len, out);

	वापस shash->digest(desc, data, len, out);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_shash_digest);

पूर्णांक crypto_shash_tfm_digest(काष्ठा crypto_shash *tfm, स्थिर u8 *data,
			    अचिन्हित पूर्णांक len, u8 *out)
अणु
	SHASH_DESC_ON_STACK(desc, tfm);
	पूर्णांक err;

	desc->tfm = tfm;

	err = crypto_shash_digest(desc, data, len, out);

	shash_desc_zero(desc);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_shash_tfm_digest);

अटल पूर्णांक shash_शेष_export(काष्ठा shash_desc *desc, व्योम *out)
अणु
	स_नकल(out, shash_desc_ctx(desc), crypto_shash_descsize(desc->tfm));
	वापस 0;
पूर्ण

अटल पूर्णांक shash_शेष_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	स_नकल(shash_desc_ctx(desc), in, crypto_shash_descsize(desc->tfm));
	वापस 0;
पूर्ण

अटल पूर्णांक shash_async_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
			      अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_shash **ctx = crypto_ahash_ctx(tfm);

	वापस crypto_shash_setkey(*ctx, key, keylen);
पूर्ण

अटल पूर्णांक shash_async_init(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_shash **ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(req));
	काष्ठा shash_desc *desc = ahash_request_ctx(req);

	desc->tfm = *ctx;

	वापस crypto_shash_init(desc);
पूर्ण

पूर्णांक shash_ahash_update(काष्ठा ahash_request *req, काष्ठा shash_desc *desc)
अणु
	काष्ठा crypto_hash_walk walk;
	पूर्णांक nbytes;

	क्रम (nbytes = crypto_hash_walk_first(req, &walk); nbytes > 0;
	     nbytes = crypto_hash_walk_करोne(&walk, nbytes))
		nbytes = crypto_shash_update(desc, walk.data, nbytes);

	वापस nbytes;
पूर्ण
EXPORT_SYMBOL_GPL(shash_ahash_update);

अटल पूर्णांक shash_async_update(काष्ठा ahash_request *req)
अणु
	वापस shash_ahash_update(req, ahash_request_ctx(req));
पूर्ण

अटल पूर्णांक shash_async_final(काष्ठा ahash_request *req)
अणु
	वापस crypto_shash_final(ahash_request_ctx(req), req->result);
पूर्ण

पूर्णांक shash_ahash_finup(काष्ठा ahash_request *req, काष्ठा shash_desc *desc)
अणु
	काष्ठा crypto_hash_walk walk;
	पूर्णांक nbytes;

	nbytes = crypto_hash_walk_first(req, &walk);
	अगर (!nbytes)
		वापस crypto_shash_final(desc, req->result);

	करो अणु
		nbytes = crypto_hash_walk_last(&walk) ?
			 crypto_shash_finup(desc, walk.data, nbytes,
					    req->result) :
			 crypto_shash_update(desc, walk.data, nbytes);
		nbytes = crypto_hash_walk_करोne(&walk, nbytes);
	पूर्ण जबतक (nbytes > 0);

	वापस nbytes;
पूर्ण
EXPORT_SYMBOL_GPL(shash_ahash_finup);

अटल पूर्णांक shash_async_finup(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_shash **ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(req));
	काष्ठा shash_desc *desc = ahash_request_ctx(req);

	desc->tfm = *ctx;

	वापस shash_ahash_finup(req, desc);
पूर्ण

पूर्णांक shash_ahash_digest(काष्ठा ahash_request *req, काष्ठा shash_desc *desc)
अणु
	अचिन्हित पूर्णांक nbytes = req->nbytes;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक offset;
	पूर्णांक err;

	अगर (nbytes &&
	    (sg = req->src, offset = sg->offset,
	     nbytes <= min(sg->length, ((अचिन्हित पूर्णांक)(PAGE_SIZE)) - offset))) अणु
		व्योम *data;

		data = kmap_atomic(sg_page(sg));
		err = crypto_shash_digest(desc, data + offset, nbytes,
					  req->result);
		kunmap_atomic(data);
	पूर्ण अन्यथा
		err = crypto_shash_init(desc) ?:
		      shash_ahash_finup(req, desc);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(shash_ahash_digest);

अटल पूर्णांक shash_async_digest(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_shash **ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(req));
	काष्ठा shash_desc *desc = ahash_request_ctx(req);

	desc->tfm = *ctx;

	वापस shash_ahash_digest(req, desc);
पूर्ण

अटल पूर्णांक shash_async_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	वापस crypto_shash_export(ahash_request_ctx(req), out);
पूर्ण

अटल पूर्णांक shash_async_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	काष्ठा crypto_shash **ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(req));
	काष्ठा shash_desc *desc = ahash_request_ctx(req);

	desc->tfm = *ctx;

	वापस crypto_shash_import(desc, in);
पूर्ण

अटल व्योम crypto_निकास_shash_ops_async(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_shash **ctx = crypto_tfm_ctx(tfm);

	crypto_मुक्त_shash(*ctx);
पूर्ण

पूर्णांक crypto_init_shash_ops_async(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_alg *calg = tfm->__crt_alg;
	काष्ठा shash_alg *alg = __crypto_shash_alg(calg);
	काष्ठा crypto_ahash *crt = __crypto_ahash_cast(tfm);
	काष्ठा crypto_shash **ctx = crypto_tfm_ctx(tfm);
	काष्ठा crypto_shash *shash;

	अगर (!crypto_mod_get(calg))
		वापस -EAGAIN;

	shash = crypto_create_tfm(calg, &crypto_shash_type);
	अगर (IS_ERR(shash)) अणु
		crypto_mod_put(calg);
		वापस PTR_ERR(shash);
	पूर्ण

	*ctx = shash;
	tfm->निकास = crypto_निकास_shash_ops_async;

	crt->init = shash_async_init;
	crt->update = shash_async_update;
	crt->final = shash_async_final;
	crt->finup = shash_async_finup;
	crt->digest = shash_async_digest;
	अगर (crypto_shash_alg_has_setkey(alg))
		crt->setkey = shash_async_setkey;

	crypto_ahash_set_flags(crt, crypto_shash_get_flags(shash) &
				    CRYPTO_TFM_NEED_KEY);

	crt->export = shash_async_export;
	crt->import = shash_async_import;

	crt->reqsize = माप(काष्ठा shash_desc) + crypto_shash_descsize(shash);

	वापस 0;
पूर्ण

अटल व्योम crypto_shash_निकास_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_shash *hash = __crypto_shash_cast(tfm);
	काष्ठा shash_alg *alg = crypto_shash_alg(hash);

	alg->निकास_tfm(hash);
पूर्ण

अटल पूर्णांक crypto_shash_init_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_shash *hash = __crypto_shash_cast(tfm);
	काष्ठा shash_alg *alg = crypto_shash_alg(hash);
	पूर्णांक err;

	hash->descsize = alg->descsize;

	shash_set_needkey(hash, alg);

	अगर (alg->निकास_tfm)
		tfm->निकास = crypto_shash_निकास_tfm;

	अगर (!alg->init_tfm)
		वापस 0;

	err = alg->init_tfm(hash);
	अगर (err)
		वापस err;

	/* ->init_tfm() may have increased the descsize. */
	अगर (WARN_ON_ONCE(hash->descsize > HASH_MAX_DESCSIZE)) अणु
		अगर (alg->निकास_tfm)
			alg->निकास_tfm(hash);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम crypto_shash_मुक्त_instance(काष्ठा crypto_instance *inst)
अणु
	काष्ठा shash_instance *shash = shash_instance(inst);

	shash->मुक्त(shash);
पूर्ण

#अगर_घोषित CONFIG_NET
अटल पूर्णांक crypto_shash_report(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_report_hash rhash;
	काष्ठा shash_alg *salg = __crypto_shash_alg(alg);

	स_रखो(&rhash, 0, माप(rhash));

	strscpy(rhash.type, "shash", माप(rhash.type));

	rhash.blocksize = alg->cra_blocksize;
	rhash.digestsize = salg->digestsize;

	वापस nla_put(skb, CRYPTOCFGA_REPORT_HASH, माप(rhash), &rhash);
पूर्ण
#अन्यथा
अटल पूर्णांक crypto_shash_report(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर

अटल व्योम crypto_shash_show(काष्ठा seq_file *m, काष्ठा crypto_alg *alg)
	__maybe_unused;
अटल व्योम crypto_shash_show(काष्ठा seq_file *m, काष्ठा crypto_alg *alg)
अणु
	काष्ठा shash_alg *salg = __crypto_shash_alg(alg);

	seq_म_लिखो(m, "type         : shash\n");
	seq_म_लिखो(m, "blocksize    : %u\n", alg->cra_blocksize);
	seq_म_लिखो(m, "digestsize   : %u\n", salg->digestsize);
पूर्ण

अटल स्थिर काष्ठा crypto_type crypto_shash_type = अणु
	.extsize = crypto_alg_extsize,
	.init_tfm = crypto_shash_init_tfm,
	.मुक्त = crypto_shash_मुक्त_instance,
#अगर_घोषित CONFIG_PROC_FS
	.show = crypto_shash_show,
#पूर्ण_अगर
	.report = crypto_shash_report,
	.maskclear = ~CRYPTO_ALG_TYPE_MASK,
	.maskset = CRYPTO_ALG_TYPE_MASK,
	.type = CRYPTO_ALG_TYPE_SHASH,
	.tfmsize = दुरत्व(काष्ठा crypto_shash, base),
पूर्ण;

पूर्णांक crypto_grab_shash(काष्ठा crypto_shash_spawn *spawn,
		      काष्ठा crypto_instance *inst,
		      स्थिर अक्षर *name, u32 type, u32 mask)
अणु
	spawn->base.frontend = &crypto_shash_type;
	वापस crypto_grab_spawn(&spawn->base, inst, name, type, mask);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_grab_shash);

काष्ठा crypto_shash *crypto_alloc_shash(स्थिर अक्षर *alg_name, u32 type,
					u32 mask)
अणु
	वापस crypto_alloc_tfm(alg_name, &crypto_shash_type, type, mask);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_alloc_shash);

अटल पूर्णांक shash_prepare_alg(काष्ठा shash_alg *alg)
अणु
	काष्ठा crypto_alg *base = &alg->base;

	अगर (alg->digestsize > HASH_MAX_DIGESTSIZE ||
	    alg->descsize > HASH_MAX_DESCSIZE ||
	    alg->statesize > HASH_MAX_STATESIZE)
		वापस -EINVAL;

	अगर ((alg->export && !alg->import) || (alg->import && !alg->export))
		वापस -EINVAL;

	base->cra_type = &crypto_shash_type;
	base->cra_flags &= ~CRYPTO_ALG_TYPE_MASK;
	base->cra_flags |= CRYPTO_ALG_TYPE_SHASH;

	अगर (!alg->finup)
		alg->finup = shash_finup_unaligned;
	अगर (!alg->digest)
		alg->digest = shash_digest_unaligned;
	अगर (!alg->export) अणु
		alg->export = shash_शेष_export;
		alg->import = shash_शेष_import;
		alg->statesize = alg->descsize;
	पूर्ण
	अगर (!alg->setkey)
		alg->setkey = shash_no_setkey;

	वापस 0;
पूर्ण

पूर्णांक crypto_रेजिस्टर_shash(काष्ठा shash_alg *alg)
अणु
	काष्ठा crypto_alg *base = &alg->base;
	पूर्णांक err;

	err = shash_prepare_alg(alg);
	अगर (err)
		वापस err;

	वापस crypto_रेजिस्टर_alg(base);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_रेजिस्टर_shash);

व्योम crypto_unरेजिस्टर_shash(काष्ठा shash_alg *alg)
अणु
	crypto_unरेजिस्टर_alg(&alg->base);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_unरेजिस्टर_shash);

पूर्णांक crypto_रेजिस्टर_shashes(काष्ठा shash_alg *algs, पूर्णांक count)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < count; i++) अणु
		ret = crypto_रेजिस्टर_shash(&algs[i]);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	क्रम (--i; i >= 0; --i)
		crypto_unरेजिस्टर_shash(&algs[i]);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_रेजिस्टर_shashes);

व्योम crypto_unरेजिस्टर_shashes(काष्ठा shash_alg *algs, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = count - 1; i >= 0; --i)
		crypto_unरेजिस्टर_shash(&algs[i]);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_unरेजिस्टर_shashes);

पूर्णांक shash_रेजिस्टर_instance(काष्ठा crypto_ढाँचा *पंचांगpl,
			    काष्ठा shash_instance *inst)
अणु
	पूर्णांक err;

	अगर (WARN_ON(!inst->मुक्त))
		वापस -EINVAL;

	err = shash_prepare_alg(&inst->alg);
	अगर (err)
		वापस err;

	वापस crypto_रेजिस्टर_instance(पंचांगpl, shash_crypto_instance(inst));
पूर्ण
EXPORT_SYMBOL_GPL(shash_रेजिस्टर_instance);

व्योम shash_मुक्त_singlespawn_instance(काष्ठा shash_instance *inst)
अणु
	crypto_drop_spawn(shash_instance_ctx(inst));
	kमुक्त(inst);
पूर्ण
EXPORT_SYMBOL_GPL(shash_मुक्त_singlespawn_instance);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Synchronous cryptographic hash type");
