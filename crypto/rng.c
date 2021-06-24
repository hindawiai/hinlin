<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cryptographic API.
 *
 * RNG operations.
 *
 * Copyright (c) 2008 Neil Horman <nhorman@tuxdriver.com>
 * Copyright (c) 2015 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <linux/atomic.h>
#समावेश <crypto/पूर्णांकernal/rng.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/cryptouser.h>
#समावेश <linux/compiler.h>
#समावेश <net/netlink.h>

#समावेश "internal.h"

अटल DEFINE_MUTEX(crypto_शेष_rng_lock);
काष्ठा crypto_rng *crypto_शेष_rng;
EXPORT_SYMBOL_GPL(crypto_शेष_rng);
अटल पूर्णांक crypto_शेष_rng_refcnt;

पूर्णांक crypto_rng_reset(काष्ठा crypto_rng *tfm, स्थिर u8 *seed, अचिन्हित पूर्णांक slen)
अणु
	काष्ठा crypto_alg *alg = tfm->base.__crt_alg;
	u8 *buf = शून्य;
	पूर्णांक err;

	अगर (!seed && slen) अणु
		buf = kदो_स्मृति(slen, GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;

		err = get_अक्रमom_bytes_रुको(buf, slen);
		अगर (err)
			जाओ out;
		seed = buf;
	पूर्ण

	crypto_stats_get(alg);
	err = crypto_rng_alg(tfm)->seed(tfm, seed, slen);
	crypto_stats_rng_seed(alg, err);
out:
	kमुक्त_sensitive(buf);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_rng_reset);

अटल पूर्णांक crypto_rng_init_tfm(काष्ठा crypto_tfm *tfm)
अणु
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक seedsize(काष्ठा crypto_alg *alg)
अणु
	काष्ठा rng_alg *ralg = container_of(alg, काष्ठा rng_alg, base);

	वापस ralg->seedsize;
पूर्ण

#अगर_घोषित CONFIG_NET
अटल पूर्णांक crypto_rng_report(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_report_rng rrng;

	स_रखो(&rrng, 0, माप(rrng));

	strscpy(rrng.type, "rng", माप(rrng.type));

	rrng.seedsize = seedsize(alg);

	वापस nla_put(skb, CRYPTOCFGA_REPORT_RNG, माप(rrng), &rrng);
पूर्ण
#अन्यथा
अटल पूर्णांक crypto_rng_report(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर

अटल व्योम crypto_rng_show(काष्ठा seq_file *m, काष्ठा crypto_alg *alg)
	__maybe_unused;
अटल व्योम crypto_rng_show(काष्ठा seq_file *m, काष्ठा crypto_alg *alg)
अणु
	seq_म_लिखो(m, "type         : rng\n");
	seq_म_लिखो(m, "seedsize     : %u\n", seedsize(alg));
पूर्ण

अटल स्थिर काष्ठा crypto_type crypto_rng_type = अणु
	.extsize = crypto_alg_extsize,
	.init_tfm = crypto_rng_init_tfm,
#अगर_घोषित CONFIG_PROC_FS
	.show = crypto_rng_show,
#पूर्ण_अगर
	.report = crypto_rng_report,
	.maskclear = ~CRYPTO_ALG_TYPE_MASK,
	.maskset = CRYPTO_ALG_TYPE_MASK,
	.type = CRYPTO_ALG_TYPE_RNG,
	.tfmsize = दुरत्व(काष्ठा crypto_rng, base),
पूर्ण;

काष्ठा crypto_rng *crypto_alloc_rng(स्थिर अक्षर *alg_name, u32 type, u32 mask)
अणु
	वापस crypto_alloc_tfm(alg_name, &crypto_rng_type, type, mask);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_alloc_rng);

पूर्णांक crypto_get_शेष_rng(व्योम)
अणु
	काष्ठा crypto_rng *rng;
	पूर्णांक err;

	mutex_lock(&crypto_शेष_rng_lock);
	अगर (!crypto_शेष_rng) अणु
		rng = crypto_alloc_rng("stdrng", 0, 0);
		err = PTR_ERR(rng);
		अगर (IS_ERR(rng))
			जाओ unlock;

		err = crypto_rng_reset(rng, शून्य, crypto_rng_seedsize(rng));
		अगर (err) अणु
			crypto_मुक्त_rng(rng);
			जाओ unlock;
		पूर्ण

		crypto_शेष_rng = rng;
	पूर्ण

	crypto_शेष_rng_refcnt++;
	err = 0;

unlock:
	mutex_unlock(&crypto_शेष_rng_lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_get_शेष_rng);

व्योम crypto_put_शेष_rng(व्योम)
अणु
	mutex_lock(&crypto_शेष_rng_lock);
	crypto_शेष_rng_refcnt--;
	mutex_unlock(&crypto_शेष_rng_lock);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_put_शेष_rng);

#अगर defined(CONFIG_CRYPTO_RNG) || defined(CONFIG_CRYPTO_RNG_MODULE)
पूर्णांक crypto_del_शेष_rng(व्योम)
अणु
	पूर्णांक err = -EBUSY;

	mutex_lock(&crypto_शेष_rng_lock);
	अगर (crypto_शेष_rng_refcnt)
		जाओ out;

	crypto_मुक्त_rng(crypto_शेष_rng);
	crypto_शेष_rng = शून्य;

	err = 0;

out:
	mutex_unlock(&crypto_शेष_rng_lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_del_शेष_rng);
#पूर्ण_अगर

पूर्णांक crypto_रेजिस्टर_rng(काष्ठा rng_alg *alg)
अणु
	काष्ठा crypto_alg *base = &alg->base;

	अगर (alg->seedsize > PAGE_SIZE / 8)
		वापस -EINVAL;

	base->cra_type = &crypto_rng_type;
	base->cra_flags &= ~CRYPTO_ALG_TYPE_MASK;
	base->cra_flags |= CRYPTO_ALG_TYPE_RNG;

	वापस crypto_रेजिस्टर_alg(base);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_रेजिस्टर_rng);

व्योम crypto_unरेजिस्टर_rng(काष्ठा rng_alg *alg)
अणु
	crypto_unरेजिस्टर_alg(&alg->base);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_unरेजिस्टर_rng);

पूर्णांक crypto_रेजिस्टर_rngs(काष्ठा rng_alg *algs, पूर्णांक count)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < count; i++) अणु
		ret = crypto_रेजिस्टर_rng(algs + i);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	क्रम (--i; i >= 0; --i)
		crypto_unरेजिस्टर_rng(algs + i);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_रेजिस्टर_rngs);

व्योम crypto_unरेजिस्टर_rngs(काष्ठा rng_alg *algs, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = count - 1; i >= 0; --i)
		crypto_unरेजिस्टर_rng(algs + i);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_unरेजिस्टर_rngs);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Random Number Generator");
