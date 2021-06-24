<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Key-agreement Protocol Primitives (KPP)
 *
 * Copyright (c) 2016, Intel Corporation
 * Authors: Salvatore Benedetto <salvatore.benedetto@पूर्णांकel.com>
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
#समावेश <crypto/kpp.h>
#समावेश <crypto/पूर्णांकernal/kpp.h>
#समावेश "internal.h"

#अगर_घोषित CONFIG_NET
अटल पूर्णांक crypto_kpp_report(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_report_kpp rkpp;

	स_रखो(&rkpp, 0, माप(rkpp));

	strscpy(rkpp.type, "kpp", माप(rkpp.type));

	वापस nla_put(skb, CRYPTOCFGA_REPORT_KPP, माप(rkpp), &rkpp);
पूर्ण
#अन्यथा
अटल पूर्णांक crypto_kpp_report(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर

अटल व्योम crypto_kpp_show(काष्ठा seq_file *m, काष्ठा crypto_alg *alg)
	__maybe_unused;

अटल व्योम crypto_kpp_show(काष्ठा seq_file *m, काष्ठा crypto_alg *alg)
अणु
	seq_माला_दो(m, "type         : kpp\n");
पूर्ण

अटल व्योम crypto_kpp_निकास_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_kpp *kpp = __crypto_kpp_tfm(tfm);
	काष्ठा kpp_alg *alg = crypto_kpp_alg(kpp);

	alg->निकास(kpp);
पूर्ण

अटल पूर्णांक crypto_kpp_init_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_kpp *kpp = __crypto_kpp_tfm(tfm);
	काष्ठा kpp_alg *alg = crypto_kpp_alg(kpp);

	अगर (alg->निकास)
		kpp->base.निकास = crypto_kpp_निकास_tfm;

	अगर (alg->init)
		वापस alg->init(kpp);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा crypto_type crypto_kpp_type = अणु
	.extsize = crypto_alg_extsize,
	.init_tfm = crypto_kpp_init_tfm,
#अगर_घोषित CONFIG_PROC_FS
	.show = crypto_kpp_show,
#पूर्ण_अगर
	.report = crypto_kpp_report,
	.maskclear = ~CRYPTO_ALG_TYPE_MASK,
	.maskset = CRYPTO_ALG_TYPE_MASK,
	.type = CRYPTO_ALG_TYPE_KPP,
	.tfmsize = दुरत्व(काष्ठा crypto_kpp, base),
पूर्ण;

काष्ठा crypto_kpp *crypto_alloc_kpp(स्थिर अक्षर *alg_name, u32 type, u32 mask)
अणु
	वापस crypto_alloc_tfm(alg_name, &crypto_kpp_type, type, mask);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_alloc_kpp);

अटल व्योम kpp_prepare_alg(काष्ठा kpp_alg *alg)
अणु
	काष्ठा crypto_alg *base = &alg->base;

	base->cra_type = &crypto_kpp_type;
	base->cra_flags &= ~CRYPTO_ALG_TYPE_MASK;
	base->cra_flags |= CRYPTO_ALG_TYPE_KPP;
पूर्ण

पूर्णांक crypto_रेजिस्टर_kpp(काष्ठा kpp_alg *alg)
अणु
	काष्ठा crypto_alg *base = &alg->base;

	kpp_prepare_alg(alg);
	वापस crypto_रेजिस्टर_alg(base);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_रेजिस्टर_kpp);

व्योम crypto_unरेजिस्टर_kpp(काष्ठा kpp_alg *alg)
अणु
	crypto_unरेजिस्टर_alg(&alg->base);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_unरेजिस्टर_kpp);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Key-agreement Protocol Primitives");
