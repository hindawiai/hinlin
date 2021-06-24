<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Create शेष crypto algorithm instances.
 *
 * Copyright (c) 2006 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <linux/completion.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश "internal.h"

काष्ठा cryptomgr_param अणु
	काष्ठा rtattr *tb[CRYPTO_MAX_ATTRS + 2];

	काष्ठा अणु
		काष्ठा rtattr attr;
		काष्ठा crypto_attr_type data;
	पूर्ण type;

	जोड़ अणु
		काष्ठा rtattr attr;
		काष्ठा अणु
			काष्ठा rtattr attr;
			काष्ठा crypto_attr_alg data;
		पूर्ण alg;
		काष्ठा अणु
			काष्ठा rtattr attr;
			काष्ठा crypto_attr_u32 data;
		पूर्ण nu32;
	पूर्ण attrs[CRYPTO_MAX_ATTRS];

	अक्षर ढाँचा[CRYPTO_MAX_ALG_NAME];

	काष्ठा crypto_larval *larval;

	u32 otype;
	u32 omask;
पूर्ण;

काष्ठा crypto_test_param अणु
	अक्षर driver[CRYPTO_MAX_ALG_NAME];
	अक्षर alg[CRYPTO_MAX_ALG_NAME];
	u32 type;
पूर्ण;

अटल पूर्णांक cryptomgr_probe(व्योम *data)
अणु
	काष्ठा cryptomgr_param *param = data;
	काष्ठा crypto_ढाँचा *पंचांगpl;
	पूर्णांक err;

	पंचांगpl = crypto_lookup_ढाँचा(param->ढाँचा);
	अगर (!पंचांगpl)
		जाओ out;

	करो अणु
		err = पंचांगpl->create(पंचांगpl, param->tb);
	पूर्ण जबतक (err == -EAGAIN && !संकेत_pending(current));

	crypto_पंचांगpl_put(पंचांगpl);

out:
	complete_all(&param->larval->completion);
	crypto_alg_put(&param->larval->alg);
	kमुक्त(param);
	module_put_and_निकास(0);
पूर्ण

अटल पूर्णांक cryptomgr_schedule_probe(काष्ठा crypto_larval *larval)
अणु
	काष्ठा task_काष्ठा *thपढ़ो;
	काष्ठा cryptomgr_param *param;
	स्थिर अक्षर *name = larval->alg.cra_name;
	स्थिर अक्षर *p;
	अचिन्हित पूर्णांक len;
	पूर्णांक i;

	अगर (!try_module_get(THIS_MODULE))
		जाओ err;

	param = kzalloc(माप(*param), GFP_KERNEL);
	अगर (!param)
		जाओ err_put_module;

	क्रम (p = name; है_अक्षर_अंक(*p) || *p == '-' || *p == '_'; p++)
		;

	len = p - name;
	अगर (!len || *p != '(')
		जाओ err_मुक्त_param;

	स_नकल(param->ढाँचा, name, len);

	i = 0;
	क्रम (;;) अणु
		पूर्णांक notnum = 0;

		name = ++p;

		क्रम (; है_अक्षर_अंक(*p) || *p == '-' || *p == '_'; p++)
			notnum |= !है_अंक(*p);

		अगर (*p == '(') अणु
			पूर्णांक recursion = 0;

			क्रम (;;) अणु
				अगर (!*++p)
					जाओ err_मुक्त_param;
				अगर (*p == '(')
					recursion++;
				अन्यथा अगर (*p == ')' && !recursion--)
					अवरोध;
			पूर्ण

			notnum = 1;
			p++;
		पूर्ण

		len = p - name;
		अगर (!len)
			जाओ err_मुक्त_param;

		अगर (notnum) अणु
			param->attrs[i].alg.attr.rta_len =
				माप(param->attrs[i].alg);
			param->attrs[i].alg.attr.rta_type = CRYPTOA_ALG;
			स_नकल(param->attrs[i].alg.data.name, name, len);
		पूर्ण अन्यथा अणु
			param->attrs[i].nu32.attr.rta_len =
				माप(param->attrs[i].nu32);
			param->attrs[i].nu32.attr.rta_type = CRYPTOA_U32;
			param->attrs[i].nu32.data.num =
				simple_म_से_दीर्घ(name, शून्य, 0);
		पूर्ण

		param->tb[i + 1] = &param->attrs[i].attr;
		i++;

		अगर (i >= CRYPTO_MAX_ATTRS)
			जाओ err_मुक्त_param;

		अगर (*p == ')')
			अवरोध;

		अगर (*p != ',')
			जाओ err_मुक्त_param;
	पूर्ण

	अगर (!i)
		जाओ err_मुक्त_param;

	param->tb[i + 1] = शून्य;

	param->type.attr.rta_len = माप(param->type);
	param->type.attr.rta_type = CRYPTOA_TYPE;
	param->type.data.type = larval->alg.cra_flags & ~CRYPTO_ALG_TESTED;
	param->type.data.mask = larval->mask & ~CRYPTO_ALG_TESTED;
	param->tb[0] = &param->type.attr;

	param->otype = larval->alg.cra_flags;
	param->omask = larval->mask;

	crypto_alg_get(&larval->alg);
	param->larval = larval;

	thपढ़ो = kthपढ़ो_run(cryptomgr_probe, param, "cryptomgr_probe");
	अगर (IS_ERR(thपढ़ो))
		जाओ err_put_larval;

	वापस NOTIFY_STOP;

err_put_larval:
	crypto_alg_put(&larval->alg);
err_मुक्त_param:
	kमुक्त(param);
err_put_module:
	module_put(THIS_MODULE);
err:
	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक cryptomgr_test(व्योम *data)
अणु
	काष्ठा crypto_test_param *param = data;
	u32 type = param->type;
	पूर्णांक err = 0;

#अगर_घोषित CONFIG_CRYPTO_MANAGER_DISABLE_TESTS
	जाओ skiptest;
#पूर्ण_अगर

	अगर (type & CRYPTO_ALG_TESTED)
		जाओ skiptest;

	err = alg_test(param->driver, param->alg, type, CRYPTO_ALG_TESTED);

skiptest:
	crypto_alg_tested(param->driver, err);

	kमुक्त(param);
	module_put_and_निकास(0);
पूर्ण

अटल पूर्णांक cryptomgr_schedule_test(काष्ठा crypto_alg *alg)
अणु
	काष्ठा task_काष्ठा *thपढ़ो;
	काष्ठा crypto_test_param *param;
	u32 type;

	अगर (!try_module_get(THIS_MODULE))
		जाओ err;

	param = kzalloc(माप(*param), GFP_KERNEL);
	अगर (!param)
		जाओ err_put_module;

	स_नकल(param->driver, alg->cra_driver_name, माप(param->driver));
	स_नकल(param->alg, alg->cra_name, माप(param->alg));
	type = alg->cra_flags;

	/* Do not test पूर्णांकernal algorithms. */
	अगर (type & CRYPTO_ALG_INTERNAL)
		type |= CRYPTO_ALG_TESTED;

	param->type = type;

	thपढ़ो = kthपढ़ो_run(cryptomgr_test, param, "cryptomgr_test");
	अगर (IS_ERR(thपढ़ो))
		जाओ err_मुक्त_param;

	वापस NOTIFY_STOP;

err_मुक्त_param:
	kमुक्त(param);
err_put_module:
	module_put(THIS_MODULE);
err:
	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक cryptomgr_notअगरy(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ msg,
			    व्योम *data)
अणु
	चयन (msg) अणु
	हाल CRYPTO_MSG_ALG_REQUEST:
		वापस cryptomgr_schedule_probe(data);
	हाल CRYPTO_MSG_ALG_REGISTER:
		वापस cryptomgr_schedule_test(data);
	हाल CRYPTO_MSG_ALG_LOADED:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block cryptomgr_notअगरier = अणु
	.notअगरier_call = cryptomgr_notअगरy,
पूर्ण;

अटल पूर्णांक __init cryptomgr_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_notअगरier(&cryptomgr_notअगरier);
पूर्ण

अटल व्योम __निकास cryptomgr_निकास(व्योम)
अणु
	पूर्णांक err = crypto_unरेजिस्टर_notअगरier(&cryptomgr_notअगरier);
	BUG_ON(err);
पूर्ण

/*
 * This is arch_initcall() so that the crypto self-tests are run on algorithms
 * रेजिस्टरed early by subsys_initcall().  subsys_initcall() is needed क्रम
 * generic implementations so that they're available क्रम comparison tests when
 * other implementations are रेजिस्टरed later by module_init().
 */
arch_initcall(cryptomgr_init);
module_निकास(cryptomgr_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Crypto Algorithm Manager");
