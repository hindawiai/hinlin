<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Public Key Encryption
 *
 * Copyright (c) 2015, Intel Corporation
 * Authors: Tadeusz Struk <tadeusz.struk@पूर्णांकel.com>
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/crypto.h>
#समावेश <linux/compiler.h>
#समावेश <crypto/algapi.h>
#समावेश <linux/cryptouser.h>
#समावेश <net/netlink.h>
#समावेश <crypto/akcipher.h>
#समावेश <crypto/पूर्णांकernal/akcipher.h>
#समावेश "internal.h"

#अगर_घोषित CONFIG_NET
अटल पूर्णांक crypto_akcipher_report(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_report_akcipher rakcipher;

	स_रखो(&rakcipher, 0, माप(rakcipher));

	strscpy(rakcipher.type, "akcipher", माप(rakcipher.type));

	वापस nla_put(skb, CRYPTOCFGA_REPORT_AKCIPHER,
		       माप(rakcipher), &rakcipher);
पूर्ण
#अन्यथा
अटल पूर्णांक crypto_akcipher_report(काष्ठा sk_buff *skb, काष्ठा crypto_alg *alg)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर

अटल व्योम crypto_akcipher_show(काष्ठा seq_file *m, काष्ठा crypto_alg *alg)
	__maybe_unused;

अटल व्योम crypto_akcipher_show(काष्ठा seq_file *m, काष्ठा crypto_alg *alg)
अणु
	seq_माला_दो(m, "type         : akcipher\n");
पूर्ण

अटल व्योम crypto_akcipher_निकास_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_akcipher *akcipher = __crypto_akcipher_tfm(tfm);
	काष्ठा akcipher_alg *alg = crypto_akcipher_alg(akcipher);

	alg->निकास(akcipher);
पूर्ण

अटल पूर्णांक crypto_akcipher_init_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_akcipher *akcipher = __crypto_akcipher_tfm(tfm);
	काष्ठा akcipher_alg *alg = crypto_akcipher_alg(akcipher);

	अगर (alg->निकास)
		akcipher->base.निकास = crypto_akcipher_निकास_tfm;

	अगर (alg->init)
		वापस alg->init(akcipher);

	वापस 0;
पूर्ण

अटल व्योम crypto_akcipher_मुक्त_instance(काष्ठा crypto_instance *inst)
अणु
	काष्ठा akcipher_instance *akcipher = akcipher_instance(inst);

	akcipher->मुक्त(akcipher);
पूर्ण

अटल स्थिर काष्ठा crypto_type crypto_akcipher_type = अणु
	.extsize = crypto_alg_extsize,
	.init_tfm = crypto_akcipher_init_tfm,
	.मुक्त = crypto_akcipher_मुक्त_instance,
#अगर_घोषित CONFIG_PROC_FS
	.show = crypto_akcipher_show,
#पूर्ण_अगर
	.report = crypto_akcipher_report,
	.maskclear = ~CRYPTO_ALG_TYPE_MASK,
	.maskset = CRYPTO_ALG_TYPE_MASK,
	.type = CRYPTO_ALG_TYPE_AKCIPHER,
	.tfmsize = दुरत्व(काष्ठा crypto_akcipher, base),
पूर्ण;

पूर्णांक crypto_grab_akcipher(काष्ठा crypto_akcipher_spawn *spawn,
			 काष्ठा crypto_instance *inst,
			 स्थिर अक्षर *name, u32 type, u32 mask)
अणु
	spawn->base.frontend = &crypto_akcipher_type;
	वापस crypto_grab_spawn(&spawn->base, inst, name, type, mask);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_grab_akcipher);

काष्ठा crypto_akcipher *crypto_alloc_akcipher(स्थिर अक्षर *alg_name, u32 type,
					      u32 mask)
अणु
	वापस crypto_alloc_tfm(alg_name, &crypto_akcipher_type, type, mask);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_alloc_akcipher);

अटल व्योम akcipher_prepare_alg(काष्ठा akcipher_alg *alg)
अणु
	काष्ठा crypto_alg *base = &alg->base;

	base->cra_type = &crypto_akcipher_type;
	base->cra_flags &= ~CRYPTO_ALG_TYPE_MASK;
	base->cra_flags |= CRYPTO_ALG_TYPE_AKCIPHER;
पूर्ण

अटल पूर्णांक akcipher_शेष_op(काष्ठा akcipher_request *req)
अणु
	वापस -ENOSYS;
पूर्ण

पूर्णांक crypto_रेजिस्टर_akcipher(काष्ठा akcipher_alg *alg)
अणु
	काष्ठा crypto_alg *base = &alg->base;

	अगर (!alg->sign)
		alg->sign = akcipher_शेष_op;
	अगर (!alg->verअगरy)
		alg->verअगरy = akcipher_शेष_op;
	अगर (!alg->encrypt)
		alg->encrypt = akcipher_शेष_op;
	अगर (!alg->decrypt)
		alg->decrypt = akcipher_शेष_op;

	akcipher_prepare_alg(alg);
	वापस crypto_रेजिस्टर_alg(base);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_रेजिस्टर_akcipher);

व्योम crypto_unरेजिस्टर_akcipher(काष्ठा akcipher_alg *alg)
अणु
	crypto_unरेजिस्टर_alg(&alg->base);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_unरेजिस्टर_akcipher);

पूर्णांक akcipher_रेजिस्टर_instance(काष्ठा crypto_ढाँचा *पंचांगpl,
			       काष्ठा akcipher_instance *inst)
अणु
	अगर (WARN_ON(!inst->मुक्त))
		वापस -EINVAL;
	akcipher_prepare_alg(&inst->alg);
	वापस crypto_रेजिस्टर_instance(पंचांगpl, akcipher_crypto_instance(inst));
पूर्ण
EXPORT_SYMBOL_GPL(akcipher_रेजिस्टर_instance);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Generic public key cipher type");
