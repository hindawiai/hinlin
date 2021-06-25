<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Asynchronous Cryptographic Hash operations.
 *
 * This is the asynchronous version of hash.c with notअगरication of
 * completion via a callback.
 *
 * Copyright (c) 2008 Loc Ho <lho@amcc.com>
 */

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/cryptouser.h>
#समावेश <linux/compiler.h>
#समावेश <net/netlink.h>

#समावेश "internal.h"

अटल स्थिर काष्ठा crypto_type crypto_ahash_type;

काष्ठा ahash_request_priv अणु
	crypto_completion_t complete;
	व्योम *data;
	u8 *result;
	u32 flags;
	व्योम *ubuf[] CRYPTO_MINALIGN_ATTR;
पूर्ण;

अटल अंतरभूत काष्ठा ahash_alg *crypto_ahash_alg(काष्ठा crypto_ahash *hash)
अणु
	वापस container_of(crypto_hash_alg_common(hash), काष्ठा ahash_alg,
			    halg);
पूर्ण

अटल पूर्णांक hash_walk_next(काष्ठा crypto_hash_walk *walk)
अणु
	अचिन्हित पूर्णांक alignmask = walk->alignmask;
	अचिन्हित पूर्णांक offset = walk->offset;
	अचिन्हित पूर्णांक nbytes = min(walk->entrylen,
				  ((अचिन्हित पूर्णांक)(PAGE_SIZE)) - offset);

	walk->data = kmap_atomic(walk->pg);
	walk->data += offset;

	अगर (offset & alignmask) अणु
		अचिन्हित पूर्णांक unaligned = alignmask + 1 - (offset & alignmask);

		अगर (nbytes > unaligned)
			nbytes = unaligned;
	पूर्ण

	walk->entrylen -= nbytes;
	वापस nbytes;
पूर्ण

अटल पूर्णांक hash_walk_new_entry(काष्ठा crypto_hash_walk *walk)
अणु
	काष्ठा scatterlist *sg;

	sg = walk->sg;
	walk->offset = sg->offset;
	walk->pg = sg_page(walk->sg) + (walk->offset >> PAGE_SHIFT);
	walk->offset = offset_in_page(walk->offset);
	walk->entrylen = sg->length;

	अगर (walk->entrylen > walk->total)
		walk->entrylen = walk->total;
	walk->total -= walk->entrylen;

	वापस hash_walk_next(walk);
पूर्ण

पूर्णांक crypto_hash_walk_करोne(काष्ठा crypto_hash_walk *walk, पूर्णांक err)
अणु
	अचिन्हित पूर्णांक alignmask = walk->alignmask;

	walk->data -= walk->offset;

	अगर (walk->entrylen && (walk->offset & alignmask) && !err) अणु
		अचिन्हित पूर्णांक nbytes;

		walk->offset = ALIGN(walk->offset, alignmask + 1);
		nbytes = min(walk->entrylen,
			     (अचिन्हित पूर्णांक)(PAGE_SIZE - walk->offset));
		अगर (nbytes) अणु
			walk->entrylen -= nbytes;
			walk->data += walk->offset;
			वापस nbytes;
		पूर्ण
	पूर्ण

	kunmap_atomic(walk->data);
	crypto_yield(walk->flags);

	अगर (err)
		वापस err;

	अगर (walk->entrylen) अणु
		walk->offset = 0;
		walk->pg++;
		वापस hash_walk_next(walk);
	पूर्ण

	अगर (!walk->total)
		वापस 0;

	walk->sg = sg_next(walk->sg);

	वापस hash_walk_new_entry(walk);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_hash_walk_करोne);

पूर्णांक crypto_hash_walk_first(काष्ठा ahash_request *req,
			   काष्ठा crypto_hash_walk *walk)
अणु
	walk->total = req->nbytes;

	अगर (!walk->total) अणु
		walk->entrylen = 0;
		वापस 0;
	पूर्ण

	walk->alignmask = crypto_ahash_alignmask(crypto_ahash_reqtfm(req));
	walk->sg = req->src;
	walk->flags = req->base.flags;

	वापस hash_walk_new_entry(walk);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_hash_walk_first);

अटल पूर्णांक ahash_setkey_unaligned(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
				अचिन्हित पूर्णांक keylen)
अणु
	अचिन्हित दीर्घ alignmask = crypto_ahash_alignmask(tfm);
	पूर्णांक ret;
	u8 *buffer, *alignbuffer;
	अचिन्हित दीर्घ असलize;

	असलize = keylen + alignmask;
	buffer = kदो_स्मृति(असलize, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	alignbuffer = (u8 *)ALIGN((अचिन्हित दीर्घ)buffer, alignmask + 1);
	स_नकल(alignbuffer, key, keylen);
	ret = tfm->setkey(tfm, alignbuffer, keylen);
	kमुक्त_sensitive(buffer);
	वापस ret;
पूर्ण

अटल पूर्णांक ahash_nosetkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
			  अचिन्हित पूर्णांक keylen)
अणु
	वापस -ENOSYS;
पूर्ण

अटल व्योम ahash_set_needkey(काष्ठा crypto_ahash *tfm)
अणु
	स्थिर काष्ठा hash_alg_common *alg = crypto_hash_alg_common(tfm);

	अगर (tfm->setkey != ahash_nosetkey &&
	    !(alg->base.cra_flags & CRYPTO_ALG_OPTIONAL_KEY))
		crypto_ahash_set_flags(tfm, CRYPTO_TFM_NEED_KEY);
पूर्ण

पूर्णांक crypto_ahash_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen)
अणु
	अचिन्हित दीर्घ alignmask = crypto_ahash_alignmask(tfm);
	पूर्णांक err;

	अगर ((अचिन्हित दीर्घ)key & alignmask)
		err = ahash_setkey_unaligned(tfm, key, keylen);
	अन्यथा
		err = tfm->setkey(tfm, key, keylen);

	अगर (unlikely(err)) अणु
		ahash_set_needkey(tfm);
		वापस err;
	पूर्ण

	crypto_ahash_clear_flags(tfm, CRYPTO_TFM_NEED_KEY);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_ahash_setkey);

अटल अंतरभूत अचिन्हित पूर्णांक ahash_align_buffer_size(अचिन्हित len,
						   अचिन्हित दीर्घ mask)
अणु
	वापस len + (mask & ~(crypto_tfm_ctx_alignment() - 1));
पूर्ण

अटल पूर्णांक ahash_save_req(काष्ठा ahash_request *req, crypto_completion_t cplt)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	अचिन्हित दीर्घ alignmask = crypto_ahash_alignmask(tfm);
	अचिन्हित पूर्णांक ds = crypto_ahash_digestsize(tfm);
	काष्ठा ahash_request_priv *priv;

	priv = kदो_स्मृति(माप(*priv) + ahash_align_buffer_size(ds, alignmask),
		       (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		       GFP_KERNEL : GFP_ATOMIC);
	अगर (!priv)
		वापस -ENOMEM;

	/*
	 * WARNING: Vooकरोo programming below!
	 *
	 * The code below is obscure and hard to understand, thus explanation
	 * is necessary. See include/crypto/hash.h and include/linux/crypto.h
	 * to understand the layout of काष्ठाures used here!
	 *
	 * The code here will replace portions of the ORIGINAL request with
	 * poपूर्णांकers to new code and buffers so the hashing operation can store
	 * the result in aligned buffer. We will call the modअगरied request
	 * an ADJUSTED request.
	 *
	 * The newly mangled request will look as such:
	 *
	 * req अणु
	 *   .result        = ADJUSTED[new aligned buffer]
	 *   .base.complete = ADJUSTED[poपूर्णांकer to completion function]
	 *   .base.data     = ADJUSTED[*req (poपूर्णांकer to self)]
	 *   .priv          = ADJUSTED[new priv] अणु
	 *           .result   = ORIGINAL(result)
	 *           .complete = ORIGINAL(base.complete)
	 *           .data     = ORIGINAL(base.data)
	 *   पूर्ण
	 */

	priv->result = req->result;
	priv->complete = req->base.complete;
	priv->data = req->base.data;
	priv->flags = req->base.flags;

	/*
	 * WARNING: We करो not backup req->priv here! The req->priv
	 *          is क्रम पूर्णांकernal use of the Crypto API and the
	 *          user must _NOT_ _EVER_ depend on it's content!
	 */

	req->result = PTR_ALIGN((u8 *)priv->ubuf, alignmask + 1);
	req->base.complete = cplt;
	req->base.data = req;
	req->priv = priv;

	वापस 0;
पूर्ण

अटल व्योम ahash_restore_req(काष्ठा ahash_request *req, पूर्णांक err)
अणु
	काष्ठा ahash_request_priv *priv = req->priv;

	अगर (!err)
		स_नकल(priv->result, req->result,
		       crypto_ahash_digestsize(crypto_ahash_reqtfm(req)));

	/* Restore the original crypto request. */
	req->result = priv->result;

	ahash_request_set_callback(req, priv->flags,
				   priv->complete, priv->data);
	req->priv = शून्य;

	/* Free the req->priv.priv from the ADJUSTED request. */
	kमुक्त_sensitive(priv);
पूर्ण

अटल व्योम ahash_notअगरy_einprogress(काष्ठा ahash_request *req)
अणु
	काष्ठा ahash_request_priv *priv = req->priv;
	काष्ठा crypto_async_request oreq;

	oreq.data = priv->data;

	priv->complete(&oreq, -EINPROGRESS);
पूर्ण

अटल व्योम ahash_op_unaligned_करोne(काष्ठा crypto_async_request *req, पूर्णांक err)
अणु
	काष्ठा ahash_request *areq = req->data;

	अगर (err == -EINPROGRESS) अणु
		ahash_notअगरy_einprogress(areq);
		वापस;
	पूर्ण

	/*
	 * Restore the original request, see ahash_op_unaligned() क्रम what
	 * goes where.
	 *
	 * The "struct ahash_request *req" here is in fact the "req.base"
	 * from the ADJUSTED request from ahash_op_unaligned(), thus as it
	 * is a poपूर्णांकer to self, it is also the ADJUSTED "req" .
	 */

	/* First copy req->result पूर्णांकo req->priv.result */
	ahash_restore_req(areq, err);

	/* Complete the ORIGINAL request. */
	areq->base.complete(&areq->base, err);
पूर्ण

अटल पूर्णांक ahash_op_unaligned(काष्ठा ahash_request *req,
			      पूर्णांक (*op)(काष्ठा ahash_request *))
अणु
	पूर्णांक err;

	err = ahash_save_req(req, ahash_op_unaligned_करोne);
	अगर (err)
		वापस err;

	err = op(req);
	अगर (err == -EINPROGRESS || err == -EBUSY)
		वापस err;

	ahash_restore_req(req, err);

	वापस err;
पूर्ण

अटल पूर्णांक crypto_ahash_op(काष्ठा ahash_request *req,
			   पूर्णांक (*op)(काष्ठा ahash_request *))
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	अचिन्हित दीर्घ alignmask = crypto_ahash_alignmask(tfm);

	अगर ((अचिन्हित दीर्घ)req->result & alignmask)
		वापस ahash_op_unaligned(req, op);

	वापस op(req);
पूर्ण

पूर्णांक crypto_ahash_final(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा crypto_alg *alg = tfm->base.__crt_alg;
	अचिन्हित पूर्णांक nbytes = req->nbytes;
	पूर्णांक ret;

	crypto_stats_get(alg);
	ret = crypto_ahash_op(req, crypto_ahash_reqtfm(req)->final);
	crypto_stats_ahash_final(nbytes, ret, alg);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_ahash_final);

पूर्णांक crypto_ahash_finup(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा crypto_alg *alg = tfm->base.__crt_alg;
	अचिन्हित पूर्णांक nbytes = req->nbytes;
	पूर्णांक ret;

	crypto_stats_get(alg);
	ret = crypto_ahash_op(req, crypto_ahash_reqtfm(req)->finup);
	crypto_stats_ahash_final(nbytes, ret, alg);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_ahash_finup);

पूर्णांक crypto_ahash_digest(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा crypto_alg *alg = tfm->base.__crt_alg;
	अचिन्हित पूर्णांक nbytes = req->nbytes;
	पूर्णांक ret;

	crypto_stats_get(alg);
	अगर (crypto_ahash_get_flags(tfm) & CRYPTO_TFM_NEED_KEY)
		ret = -ENOKEY;
	अन्यथा
		ret = crypto_ahash_op(req, tfm->digest);
	crypto_stats_ahash_final(nbytes, ret, alg);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_ahash_digest);

अटल व्योम ahash_def_finup_करोne2(काष्ठा crypto_async_request *req, पूर्णांक err)
अणु
	काष्ठा ahash_request *areq = req->data;

	अगर (err == -EINPROGRESS)
		वापस;

	ahash_restore_req(areq, err);

	areq->base.complete(&areq->base, err);
पूर्ण

अटल पूर्णांक ahash_def_finup_finish1(काष्ठा ahash_request *req, पूर्णांक err)
अणु
	अगर (err)
		जाओ out;

	req->base.complete = ahash_def_finup_करोne2;

	err = crypto_ahash_reqtfm(req)->final(req);
	अगर (err == -EINPROGRESS || err == -EBUSY)
		वापस err;

out:
	ahash_restore_req(req, err);
	वापस err;
पूर्ण

अटल व्योम ahash_def_finup_करोne1(काष्ठा crypto_async_request *req, पूर्णांक err)
अणु
	काष्ठा ahash_request *areq = req->data;

	अगर (err == -EINPROGRESS) अणु
		ahash_notअगरy_einprogress(areq);
		वापस;
	पूर्ण

	areq->base.flags &= ~CRYPTO_TFM_REQ_MAY_SLEEP;

	err = ahash_def_finup_finish1(areq, err);
	अगर (areq->priv)
		वापस;

	areq->base.complete(&areq->base, err);
पूर्ण

अटल पूर्णांक ahash_def_finup(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	पूर्णांक err;

	err = ahash_save_req(req, ahash_def_finup_करोne1);
	अगर (err)
		वापस err;

	err = tfm->update(req);
	अगर (err == -EINPROGRESS || err == -EBUSY)
		वापस err;

	वापस ahash_def_finup_finish1(req, err);
पूर्ण

अटल व्योम crypto_ahash_निकास_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_ahash *hash = __crypto_ahash_cast(tfm);
	काष्ठा ahash_alg *alg = crypto_ahash_alg(hash);

	alg->निकास_tfm(hash);
पूर्ण

अटल पूर्णांक crypto_ahash_init_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_ahash *hash = __crypto_ahash_cast(tfm);
	काष्ठा ahash_alg *alg = crypto_ahash_alg(hash);

	hash->setkey = ahash_nosetkey;

	अगर (tfm->__crt_alg->cra_type != &crypto_ahash_type)
		वापस crypto_init_shash_ops_async(tfm);

	hash->init = alg->init;
	hash->update = alg->update;
	hash->final = alg->final;
	hash->finup = alg->finup ?: ahash_def_finup;
	hash->digest = alg->digest;
	hash->export = alg->export;
	hash->import = alg->import;

	अगर (alg->setkey) अणु
		hash->setkey = alg->setkey;
		ahash_set_needkey(hash);
	पूर्ण

	अगर (alg->निकास_tfm)
		tfm->निकास = crypto_ahash_निकास_tfm;

	वापस alg->init_tfm ? alg->init_tfm(hash) : 0;
पूर्ण

अटल अचिन्हित पूर्णांक crypto_ahash_extsize(काष्ठा crypto_alg *alg)
अणु
	अगर (alg->cra_type != &crypto_ahash_type)
		वापस माप(काष्ठा crypto_shash *);

	वापस crypto_alg_extsize(alg);
पूर्ण

अटल व्योम crypto_ahash_मुक्त_instance(काष्ठा crypto_instance *inst)
अणु
	काष्ठा ahash_instance *ahash = ahash_instance(inst);

	ahash->मुक्त(ahash);
पूर्ण

#अगर_घोषित CONFIG_NET
अटल पूर्णांक crypto_ahash_report(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_report_hash rhash;

	स_रखो(&rhash, 0, माप(rhash));

	strscpy(rhash.type, "ahash", माप(rhash.type));

	rhash.blocksize = alg->cra_blocksize;
	rhash.digestsize = __crypto_hash_alg_common(alg)->digestsize;

	वापस nla_put(skb, CRYPTOCFGA_REPORT_HASH, माप(rhash), &rhash);
पूर्ण
#अन्यथा
अटल पूर्णांक crypto_ahash_report(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर

अटल व्योम crypto_ahash_show(काष्ठा seq_file *m, काष्ठा crypto_alg *alg)
	__maybe_unused;
अटल व्योम crypto_ahash_show(काष्ठा seq_file *m, काष्ठा crypto_alg *alg)
अणु
	seq_म_लिखो(m, "type         : ahash\n");
	seq_म_लिखो(m, "async        : %s\n", alg->cra_flags & CRYPTO_ALG_ASYNC ?
					     "yes" : "no");
	seq_म_लिखो(m, "blocksize    : %u\n", alg->cra_blocksize);
	seq_म_लिखो(m, "digestsize   : %u\n",
		   __crypto_hash_alg_common(alg)->digestsize);
पूर्ण

अटल स्थिर काष्ठा crypto_type crypto_ahash_type = अणु
	.extsize = crypto_ahash_extsize,
	.init_tfm = crypto_ahash_init_tfm,
	.मुक्त = crypto_ahash_मुक्त_instance,
#अगर_घोषित CONFIG_PROC_FS
	.show = crypto_ahash_show,
#पूर्ण_अगर
	.report = crypto_ahash_report,
	.maskclear = ~CRYPTO_ALG_TYPE_MASK,
	.maskset = CRYPTO_ALG_TYPE_AHASH_MASK,
	.type = CRYPTO_ALG_TYPE_AHASH,
	.tfmsize = दुरत्व(काष्ठा crypto_ahash, base),
पूर्ण;

पूर्णांक crypto_grab_ahash(काष्ठा crypto_ahash_spawn *spawn,
		      काष्ठा crypto_instance *inst,
		      स्थिर अक्षर *name, u32 type, u32 mask)
अणु
	spawn->base.frontend = &crypto_ahash_type;
	वापस crypto_grab_spawn(&spawn->base, inst, name, type, mask);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_grab_ahash);

काष्ठा crypto_ahash *crypto_alloc_ahash(स्थिर अक्षर *alg_name, u32 type,
					u32 mask)
अणु
	वापस crypto_alloc_tfm(alg_name, &crypto_ahash_type, type, mask);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_alloc_ahash);

पूर्णांक crypto_has_ahash(स्थिर अक्षर *alg_name, u32 type, u32 mask)
अणु
	वापस crypto_type_has_alg(alg_name, &crypto_ahash_type, type, mask);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_has_ahash);

अटल पूर्णांक ahash_prepare_alg(काष्ठा ahash_alg *alg)
अणु
	काष्ठा crypto_alg *base = &alg->halg.base;

	अगर (alg->halg.digestsize > HASH_MAX_DIGESTSIZE ||
	    alg->halg.statesize > HASH_MAX_STATESIZE ||
	    alg->halg.statesize == 0)
		वापस -EINVAL;

	base->cra_type = &crypto_ahash_type;
	base->cra_flags &= ~CRYPTO_ALG_TYPE_MASK;
	base->cra_flags |= CRYPTO_ALG_TYPE_AHASH;

	वापस 0;
पूर्ण

पूर्णांक crypto_रेजिस्टर_ahash(काष्ठा ahash_alg *alg)
अणु
	काष्ठा crypto_alg *base = &alg->halg.base;
	पूर्णांक err;

	err = ahash_prepare_alg(alg);
	अगर (err)
		वापस err;

	वापस crypto_रेजिस्टर_alg(base);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_रेजिस्टर_ahash);

व्योम crypto_unरेजिस्टर_ahash(काष्ठा ahash_alg *alg)
अणु
	crypto_unरेजिस्टर_alg(&alg->halg.base);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_unरेजिस्टर_ahash);

पूर्णांक crypto_रेजिस्टर_ahashes(काष्ठा ahash_alg *algs, पूर्णांक count)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < count; i++) अणु
		ret = crypto_रेजिस्टर_ahash(&algs[i]);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	क्रम (--i; i >= 0; --i)
		crypto_unरेजिस्टर_ahash(&algs[i]);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_रेजिस्टर_ahashes);

व्योम crypto_unरेजिस्टर_ahashes(काष्ठा ahash_alg *algs, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = count - 1; i >= 0; --i)
		crypto_unरेजिस्टर_ahash(&algs[i]);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_unरेजिस्टर_ahashes);

पूर्णांक ahash_रेजिस्टर_instance(काष्ठा crypto_ढाँचा *पंचांगpl,
			    काष्ठा ahash_instance *inst)
अणु
	पूर्णांक err;

	अगर (WARN_ON(!inst->मुक्त))
		वापस -EINVAL;

	err = ahash_prepare_alg(&inst->alg);
	अगर (err)
		वापस err;

	वापस crypto_रेजिस्टर_instance(पंचांगpl, ahash_crypto_instance(inst));
पूर्ण
EXPORT_SYMBOL_GPL(ahash_रेजिस्टर_instance);

bool crypto_hash_alg_has_setkey(काष्ठा hash_alg_common *halg)
अणु
	काष्ठा crypto_alg *alg = &halg->base;

	अगर (alg->cra_type != &crypto_ahash_type)
		वापस crypto_shash_alg_has_setkey(__crypto_shash_alg(alg));

	वापस __crypto_ahash_alg(alg)->setkey != शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_hash_alg_has_setkey);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Asynchronous cryptographic hash type");
