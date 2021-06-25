<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AEAD: Authenticated Encryption with Associated Data
 *
 * This file provides API support क्रम AEAD algorithms.
 *
 * Copyright (c) 2007-2015 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/cryptouser.h>
#समावेश <net/netlink.h>

#समावेश "internal.h"

अटल पूर्णांक setkey_unaligned(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
			    अचिन्हित पूर्णांक keylen)
अणु
	अचिन्हित दीर्घ alignmask = crypto_aead_alignmask(tfm);
	पूर्णांक ret;
	u8 *buffer, *alignbuffer;
	अचिन्हित दीर्घ असलize;

	असलize = keylen + alignmask;
	buffer = kदो_स्मृति(असलize, GFP_ATOMIC);
	अगर (!buffer)
		वापस -ENOMEM;

	alignbuffer = (u8 *)ALIGN((अचिन्हित दीर्घ)buffer, alignmask + 1);
	स_नकल(alignbuffer, key, keylen);
	ret = crypto_aead_alg(tfm)->setkey(tfm, alignbuffer, keylen);
	स_रखो(alignbuffer, 0, keylen);
	kमुक्त(buffer);
	वापस ret;
पूर्ण

पूर्णांक crypto_aead_setkey(काष्ठा crypto_aead *tfm,
		       स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	अचिन्हित दीर्घ alignmask = crypto_aead_alignmask(tfm);
	पूर्णांक err;

	अगर ((अचिन्हित दीर्घ)key & alignmask)
		err = setkey_unaligned(tfm, key, keylen);
	अन्यथा
		err = crypto_aead_alg(tfm)->setkey(tfm, key, keylen);

	अगर (unlikely(err)) अणु
		crypto_aead_set_flags(tfm, CRYPTO_TFM_NEED_KEY);
		वापस err;
	पूर्ण

	crypto_aead_clear_flags(tfm, CRYPTO_TFM_NEED_KEY);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_aead_setkey);

पूर्णांक crypto_aead_setauthsize(काष्ठा crypto_aead *tfm, अचिन्हित पूर्णांक authsize)
अणु
	पूर्णांक err;

	अगर ((!authsize && crypto_aead_maxauthsize(tfm)) ||
	    authsize > crypto_aead_maxauthsize(tfm))
		वापस -EINVAL;

	अगर (crypto_aead_alg(tfm)->setauthsize) अणु
		err = crypto_aead_alg(tfm)->setauthsize(tfm, authsize);
		अगर (err)
			वापस err;
	पूर्ण

	tfm->authsize = authsize;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_aead_setauthsize);

पूर्णांक crypto_aead_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा crypto_alg *alg = aead->base.__crt_alg;
	अचिन्हित पूर्णांक cryptlen = req->cryptlen;
	पूर्णांक ret;

	crypto_stats_get(alg);
	अगर (crypto_aead_get_flags(aead) & CRYPTO_TFM_NEED_KEY)
		ret = -ENOKEY;
	अन्यथा
		ret = crypto_aead_alg(aead)->encrypt(req);
	crypto_stats_aead_encrypt(cryptlen, alg, ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_aead_encrypt);

पूर्णांक crypto_aead_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा crypto_alg *alg = aead->base.__crt_alg;
	अचिन्हित पूर्णांक cryptlen = req->cryptlen;
	पूर्णांक ret;

	crypto_stats_get(alg);
	अगर (crypto_aead_get_flags(aead) & CRYPTO_TFM_NEED_KEY)
		ret = -ENOKEY;
	अन्यथा अगर (req->cryptlen < crypto_aead_authsize(aead))
		ret = -EINVAL;
	अन्यथा
		ret = crypto_aead_alg(aead)->decrypt(req);
	crypto_stats_aead_decrypt(cryptlen, alg, ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_aead_decrypt);

अटल व्योम crypto_aead_निकास_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_aead *aead = __crypto_aead_cast(tfm);
	काष्ठा aead_alg *alg = crypto_aead_alg(aead);

	alg->निकास(aead);
पूर्ण

अटल पूर्णांक crypto_aead_init_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_aead *aead = __crypto_aead_cast(tfm);
	काष्ठा aead_alg *alg = crypto_aead_alg(aead);

	crypto_aead_set_flags(aead, CRYPTO_TFM_NEED_KEY);

	aead->authsize = alg->maxauthsize;

	अगर (alg->निकास)
		aead->base.निकास = crypto_aead_निकास_tfm;

	अगर (alg->init)
		वापस alg->init(aead);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NET
अटल पूर्णांक crypto_aead_report(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_report_aead raead;
	काष्ठा aead_alg *aead = container_of(alg, काष्ठा aead_alg, base);

	स_रखो(&raead, 0, माप(raead));

	strscpy(raead.type, "aead", माप(raead.type));
	strscpy(raead.geniv, "<none>", माप(raead.geniv));

	raead.blocksize = alg->cra_blocksize;
	raead.maxauthsize = aead->maxauthsize;
	raead.ivsize = aead->ivsize;

	वापस nla_put(skb, CRYPTOCFGA_REPORT_AEAD, माप(raead), &raead);
पूर्ण
#अन्यथा
अटल पूर्णांक crypto_aead_report(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर

अटल व्योम crypto_aead_show(काष्ठा seq_file *m, काष्ठा crypto_alg *alg)
	__maybe_unused;
अटल व्योम crypto_aead_show(काष्ठा seq_file *m, काष्ठा crypto_alg *alg)
अणु
	काष्ठा aead_alg *aead = container_of(alg, काष्ठा aead_alg, base);

	seq_म_लिखो(m, "type         : aead\n");
	seq_म_लिखो(m, "async        : %s\n", alg->cra_flags & CRYPTO_ALG_ASYNC ?
					     "yes" : "no");
	seq_म_लिखो(m, "blocksize    : %u\n", alg->cra_blocksize);
	seq_म_लिखो(m, "ivsize       : %u\n", aead->ivsize);
	seq_म_लिखो(m, "maxauthsize  : %u\n", aead->maxauthsize);
	seq_म_लिखो(m, "geniv        : <none>\n");
पूर्ण

अटल व्योम crypto_aead_मुक्त_instance(काष्ठा crypto_instance *inst)
अणु
	काष्ठा aead_instance *aead = aead_instance(inst);

	aead->मुक्त(aead);
पूर्ण

अटल स्थिर काष्ठा crypto_type crypto_aead_type = अणु
	.extsize = crypto_alg_extsize,
	.init_tfm = crypto_aead_init_tfm,
	.मुक्त = crypto_aead_मुक्त_instance,
#अगर_घोषित CONFIG_PROC_FS
	.show = crypto_aead_show,
#पूर्ण_अगर
	.report = crypto_aead_report,
	.maskclear = ~CRYPTO_ALG_TYPE_MASK,
	.maskset = CRYPTO_ALG_TYPE_MASK,
	.type = CRYPTO_ALG_TYPE_AEAD,
	.tfmsize = दुरत्व(काष्ठा crypto_aead, base),
पूर्ण;

पूर्णांक crypto_grab_aead(काष्ठा crypto_aead_spawn *spawn,
		     काष्ठा crypto_instance *inst,
		     स्थिर अक्षर *name, u32 type, u32 mask)
अणु
	spawn->base.frontend = &crypto_aead_type;
	वापस crypto_grab_spawn(&spawn->base, inst, name, type, mask);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_grab_aead);

काष्ठा crypto_aead *crypto_alloc_aead(स्थिर अक्षर *alg_name, u32 type, u32 mask)
अणु
	वापस crypto_alloc_tfm(alg_name, &crypto_aead_type, type, mask);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_alloc_aead);

अटल पूर्णांक aead_prepare_alg(काष्ठा aead_alg *alg)
अणु
	काष्ठा crypto_alg *base = &alg->base;

	अगर (max3(alg->maxauthsize, alg->ivsize, alg->chunksize) >
	    PAGE_SIZE / 8)
		वापस -EINVAL;

	अगर (!alg->chunksize)
		alg->chunksize = base->cra_blocksize;

	base->cra_type = &crypto_aead_type;
	base->cra_flags &= ~CRYPTO_ALG_TYPE_MASK;
	base->cra_flags |= CRYPTO_ALG_TYPE_AEAD;

	वापस 0;
पूर्ण

पूर्णांक crypto_रेजिस्टर_aead(काष्ठा aead_alg *alg)
अणु
	काष्ठा crypto_alg *base = &alg->base;
	पूर्णांक err;

	err = aead_prepare_alg(alg);
	अगर (err)
		वापस err;

	वापस crypto_रेजिस्टर_alg(base);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_रेजिस्टर_aead);

व्योम crypto_unरेजिस्टर_aead(काष्ठा aead_alg *alg)
अणु
	crypto_unरेजिस्टर_alg(&alg->base);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_unरेजिस्टर_aead);

पूर्णांक crypto_रेजिस्टर_aeads(काष्ठा aead_alg *algs, पूर्णांक count)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < count; i++) अणु
		ret = crypto_रेजिस्टर_aead(&algs[i]);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	क्रम (--i; i >= 0; --i)
		crypto_unरेजिस्टर_aead(&algs[i]);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_रेजिस्टर_aeads);

व्योम crypto_unरेजिस्टर_aeads(काष्ठा aead_alg *algs, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = count - 1; i >= 0; --i)
		crypto_unरेजिस्टर_aead(&algs[i]);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_unरेजिस्टर_aeads);

पूर्णांक aead_रेजिस्टर_instance(काष्ठा crypto_ढाँचा *पंचांगpl,
			   काष्ठा aead_instance *inst)
अणु
	पूर्णांक err;

	अगर (WARN_ON(!inst->मुक्त))
		वापस -EINVAL;

	err = aead_prepare_alg(&inst->alg);
	अगर (err)
		वापस err;

	वापस crypto_रेजिस्टर_instance(पंचांगpl, aead_crypto_instance(inst));
पूर्ण
EXPORT_SYMBOL_GPL(aead_रेजिस्टर_instance);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Authenticated Encryption with Associated Data (AEAD)");
