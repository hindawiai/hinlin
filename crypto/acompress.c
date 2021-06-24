<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Asynchronous Compression operations
 *
 * Copyright (c) 2016, Intel Corporation
 * Authors: Weigang Li <weigang.li@पूर्णांकel.com>
 *          Giovanni Cabiddu <giovanni.cabiddu@पूर्णांकel.com>
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/crypto.h>
#समावेश <crypto/algapi.h>
#समावेश <linux/cryptouser.h>
#समावेश <linux/compiler.h>
#समावेश <net/netlink.h>
#समावेश <crypto/पूर्णांकernal/acompress.h>
#समावेश <crypto/पूर्णांकernal/scompress.h>
#समावेश "internal.h"

अटल स्थिर काष्ठा crypto_type crypto_acomp_type;

#अगर_घोषित CONFIG_NET
अटल पूर्णांक crypto_acomp_report(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_report_acomp racomp;

	स_रखो(&racomp, 0, माप(racomp));

	strscpy(racomp.type, "acomp", माप(racomp.type));

	वापस nla_put(skb, CRYPTOCFGA_REPORT_ACOMP, माप(racomp), &racomp);
पूर्ण
#अन्यथा
अटल पूर्णांक crypto_acomp_report(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर

अटल व्योम crypto_acomp_show(काष्ठा seq_file *m, काष्ठा crypto_alg *alg)
	__maybe_unused;

अटल व्योम crypto_acomp_show(काष्ठा seq_file *m, काष्ठा crypto_alg *alg)
अणु
	seq_माला_दो(m, "type         : acomp\n");
पूर्ण

अटल व्योम crypto_acomp_निकास_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_acomp *acomp = __crypto_acomp_tfm(tfm);
	काष्ठा acomp_alg *alg = crypto_acomp_alg(acomp);

	alg->निकास(acomp);
पूर्ण

अटल पूर्णांक crypto_acomp_init_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_acomp *acomp = __crypto_acomp_tfm(tfm);
	काष्ठा acomp_alg *alg = crypto_acomp_alg(acomp);

	अगर (tfm->__crt_alg->cra_type != &crypto_acomp_type)
		वापस crypto_init_scomp_ops_async(tfm);

	acomp->compress = alg->compress;
	acomp->decompress = alg->decompress;
	acomp->dst_मुक्त = alg->dst_मुक्त;
	acomp->reqsize = alg->reqsize;

	अगर (alg->निकास)
		acomp->base.निकास = crypto_acomp_निकास_tfm;

	अगर (alg->init)
		वापस alg->init(acomp);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक crypto_acomp_extsize(काष्ठा crypto_alg *alg)
अणु
	पूर्णांक extsize = crypto_alg_extsize(alg);

	अगर (alg->cra_type != &crypto_acomp_type)
		extsize += माप(काष्ठा crypto_scomp *);

	वापस extsize;
पूर्ण

अटल स्थिर काष्ठा crypto_type crypto_acomp_type = अणु
	.extsize = crypto_acomp_extsize,
	.init_tfm = crypto_acomp_init_tfm,
#अगर_घोषित CONFIG_PROC_FS
	.show = crypto_acomp_show,
#पूर्ण_अगर
	.report = crypto_acomp_report,
	.maskclear = ~CRYPTO_ALG_TYPE_MASK,
	.maskset = CRYPTO_ALG_TYPE_ACOMPRESS_MASK,
	.type = CRYPTO_ALG_TYPE_ACOMPRESS,
	.tfmsize = दुरत्व(काष्ठा crypto_acomp, base),
पूर्ण;

काष्ठा crypto_acomp *crypto_alloc_acomp(स्थिर अक्षर *alg_name, u32 type,
					u32 mask)
अणु
	वापस crypto_alloc_tfm(alg_name, &crypto_acomp_type, type, mask);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_alloc_acomp);

काष्ठा crypto_acomp *crypto_alloc_acomp_node(स्थिर अक्षर *alg_name, u32 type,
					u32 mask, पूर्णांक node)
अणु
	वापस crypto_alloc_tfm_node(alg_name, &crypto_acomp_type, type, mask,
				node);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_alloc_acomp_node);

काष्ठा acomp_req *acomp_request_alloc(काष्ठा crypto_acomp *acomp)
अणु
	काष्ठा crypto_tfm *tfm = crypto_acomp_tfm(acomp);
	काष्ठा acomp_req *req;

	req = __acomp_request_alloc(acomp);
	अगर (req && (tfm->__crt_alg->cra_type != &crypto_acomp_type))
		वापस crypto_acomp_scomp_alloc_ctx(req);

	वापस req;
पूर्ण
EXPORT_SYMBOL_GPL(acomp_request_alloc);

व्योम acomp_request_मुक्त(काष्ठा acomp_req *req)
अणु
	काष्ठा crypto_acomp *acomp = crypto_acomp_reqtfm(req);
	काष्ठा crypto_tfm *tfm = crypto_acomp_tfm(acomp);

	अगर (tfm->__crt_alg->cra_type != &crypto_acomp_type)
		crypto_acomp_scomp_मुक्त_ctx(req);

	अगर (req->flags & CRYPTO_ACOMP_ALLOC_OUTPUT) अणु
		acomp->dst_मुक्त(req->dst);
		req->dst = शून्य;
	पूर्ण

	__acomp_request_मुक्त(req);
पूर्ण
EXPORT_SYMBOL_GPL(acomp_request_मुक्त);

पूर्णांक crypto_रेजिस्टर_acomp(काष्ठा acomp_alg *alg)
अणु
	काष्ठा crypto_alg *base = &alg->base;

	base->cra_type = &crypto_acomp_type;
	base->cra_flags &= ~CRYPTO_ALG_TYPE_MASK;
	base->cra_flags |= CRYPTO_ALG_TYPE_ACOMPRESS;

	वापस crypto_रेजिस्टर_alg(base);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_रेजिस्टर_acomp);

व्योम crypto_unरेजिस्टर_acomp(काष्ठा acomp_alg *alg)
अणु
	crypto_unरेजिस्टर_alg(&alg->base);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_unरेजिस्टर_acomp);

पूर्णांक crypto_रेजिस्टर_acomps(काष्ठा acomp_alg *algs, पूर्णांक count)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < count; i++) अणु
		ret = crypto_रेजिस्टर_acomp(&algs[i]);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	क्रम (--i; i >= 0; --i)
		crypto_unरेजिस्टर_acomp(&algs[i]);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_रेजिस्टर_acomps);

व्योम crypto_unरेजिस्टर_acomps(काष्ठा acomp_alg *algs, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = count - 1; i >= 0; --i)
		crypto_unरेजिस्टर_acomp(&algs[i]);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_unरेजिस्टर_acomps);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Asynchronous compression type");
