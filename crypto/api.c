<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Scatterlist Cryptographic API.
 *
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 * Copyright (c) 2002 David S. Miller (davem@redhat.com)
 * Copyright (c) 2005 Herbert Xu <herbert@gonकरोr.apana.org.au>
 *
 * Portions derived from Cryptoapi, by Alexander Kjeldaas <astor@fast.no>
 * and Nettle, by Niels Mथघller.
 */

#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kmod.h>
#समावेश <linux/module.h>
#समावेश <linux/param.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/completion.h>
#समावेश "internal.h"

LIST_HEAD(crypto_alg_list);
EXPORT_SYMBOL_GPL(crypto_alg_list);
DECLARE_RWSEM(crypto_alg_sem);
EXPORT_SYMBOL_GPL(crypto_alg_sem);

BLOCKING_NOTIFIER_HEAD(crypto_chain);
EXPORT_SYMBOL_GPL(crypto_chain);

अटल काष्ठा crypto_alg *crypto_larval_रुको(काष्ठा crypto_alg *alg);

काष्ठा crypto_alg *crypto_mod_get(काष्ठा crypto_alg *alg)
अणु
	वापस try_module_get(alg->cra_module) ? crypto_alg_get(alg) : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_mod_get);

व्योम crypto_mod_put(काष्ठा crypto_alg *alg)
अणु
	काष्ठा module *module = alg->cra_module;

	crypto_alg_put(alg);
	module_put(module);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_mod_put);

अटल अंतरभूत पूर्णांक crypto_is_test_larval(काष्ठा crypto_larval *larval)
अणु
	वापस larval->alg.cra_driver_name[0];
पूर्ण

अटल काष्ठा crypto_alg *__crypto_alg_lookup(स्थिर अक्षर *name, u32 type,
					      u32 mask)
अणु
	काष्ठा crypto_alg *q, *alg = शून्य;
	पूर्णांक best = -2;

	list_क्रम_each_entry(q, &crypto_alg_list, cra_list) अणु
		पूर्णांक exact, fuzzy;

		अगर (crypto_is_moribund(q))
			जारी;

		अगर ((q->cra_flags ^ type) & mask)
			जारी;

		अगर (crypto_is_larval(q) &&
		    !crypto_is_test_larval((काष्ठा crypto_larval *)q) &&
		    ((काष्ठा crypto_larval *)q)->mask != mask)
			जारी;

		exact = !म_भेद(q->cra_driver_name, name);
		fuzzy = !म_भेद(q->cra_name, name);
		अगर (!exact && !(fuzzy && q->cra_priority > best))
			जारी;

		अगर (unlikely(!crypto_mod_get(q)))
			जारी;

		best = q->cra_priority;
		अगर (alg)
			crypto_mod_put(alg);
		alg = q;

		अगर (exact)
			अवरोध;
	पूर्ण

	वापस alg;
पूर्ण

अटल व्योम crypto_larval_destroy(काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_larval *larval = (व्योम *)alg;

	BUG_ON(!crypto_is_larval(alg));
	अगर (!IS_ERR_OR_शून्य(larval->adult))
		crypto_mod_put(larval->adult);
	kमुक्त(larval);
पूर्ण

काष्ठा crypto_larval *crypto_larval_alloc(स्थिर अक्षर *name, u32 type, u32 mask)
अणु
	काष्ठा crypto_larval *larval;

	larval = kzalloc(माप(*larval), GFP_KERNEL);
	अगर (!larval)
		वापस ERR_PTR(-ENOMEM);

	larval->mask = mask;
	larval->alg.cra_flags = CRYPTO_ALG_LARVAL | type;
	larval->alg.cra_priority = -1;
	larval->alg.cra_destroy = crypto_larval_destroy;

	strlcpy(larval->alg.cra_name, name, CRYPTO_MAX_ALG_NAME);
	init_completion(&larval->completion);

	वापस larval;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_larval_alloc);

अटल काष्ठा crypto_alg *crypto_larval_add(स्थिर अक्षर *name, u32 type,
					    u32 mask)
अणु
	काष्ठा crypto_alg *alg;
	काष्ठा crypto_larval *larval;

	larval = crypto_larval_alloc(name, type, mask);
	अगर (IS_ERR(larval))
		वापस ERR_CAST(larval);

	refcount_set(&larval->alg.cra_refcnt, 2);

	करोwn_ग_लिखो(&crypto_alg_sem);
	alg = __crypto_alg_lookup(name, type, mask);
	अगर (!alg) अणु
		alg = &larval->alg;
		list_add(&alg->cra_list, &crypto_alg_list);
	पूर्ण
	up_ग_लिखो(&crypto_alg_sem);

	अगर (alg != &larval->alg) अणु
		kमुक्त(larval);
		अगर (crypto_is_larval(alg))
			alg = crypto_larval_रुको(alg);
	पूर्ण

	वापस alg;
पूर्ण

व्योम crypto_larval_समाप्त(काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_larval *larval = (व्योम *)alg;

	करोwn_ग_लिखो(&crypto_alg_sem);
	list_del(&alg->cra_list);
	up_ग_लिखो(&crypto_alg_sem);
	complete_all(&larval->completion);
	crypto_alg_put(alg);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_larval_समाप्त);

अटल काष्ठा crypto_alg *crypto_larval_रुको(काष्ठा crypto_alg *alg)
अणु
	काष्ठा crypto_larval *larval = (व्योम *)alg;
	दीर्घ समयout;

	समयout = रुको_क्रम_completion_समाप्तable_समयout(
		&larval->completion, 60 * HZ);

	alg = larval->adult;
	अगर (समयout < 0)
		alg = ERR_PTR(-EINTR);
	अन्यथा अगर (!समयout)
		alg = ERR_PTR(-ETIMEDOUT);
	अन्यथा अगर (!alg)
		alg = ERR_PTR(-ENOENT);
	अन्यथा अगर (IS_ERR(alg))
		;
	अन्यथा अगर (crypto_is_test_larval(larval) &&
		 !(alg->cra_flags & CRYPTO_ALG_TESTED))
		alg = ERR_PTR(-EAGAIN);
	अन्यथा अगर (!crypto_mod_get(alg))
		alg = ERR_PTR(-EAGAIN);
	crypto_mod_put(&larval->alg);

	वापस alg;
पूर्ण

अटल काष्ठा crypto_alg *crypto_alg_lookup(स्थिर अक्षर *name, u32 type,
					    u32 mask)
अणु
	काष्ठा crypto_alg *alg;
	u32 test = 0;

	अगर (!((type | mask) & CRYPTO_ALG_TESTED))
		test |= CRYPTO_ALG_TESTED;

	करोwn_पढ़ो(&crypto_alg_sem);
	alg = __crypto_alg_lookup(name, type | test, mask | test);
	अगर (!alg && test) अणु
		alg = __crypto_alg_lookup(name, type, mask);
		अगर (alg && !crypto_is_larval(alg)) अणु
			/* Test failed */
			crypto_mod_put(alg);
			alg = ERR_PTR(-ELIBBAD);
		पूर्ण
	पूर्ण
	up_पढ़ो(&crypto_alg_sem);

	वापस alg;
पूर्ण

अटल काष्ठा crypto_alg *crypto_larval_lookup(स्थिर अक्षर *name, u32 type,
					       u32 mask)
अणु
	काष्ठा crypto_alg *alg;

	अगर (!name)
		वापस ERR_PTR(-ENOENT);

	type &= ~(CRYPTO_ALG_LARVAL | CRYPTO_ALG_DEAD);
	mask &= ~(CRYPTO_ALG_LARVAL | CRYPTO_ALG_DEAD);

	alg = crypto_alg_lookup(name, type, mask);
	अगर (!alg && !(mask & CRYPTO_NOLOAD)) अणु
		request_module("crypto-%s", name);

		अगर (!((type ^ CRYPTO_ALG_NEED_FALLBACK) & mask &
		      CRYPTO_ALG_NEED_FALLBACK))
			request_module("crypto-%s-all", name);

		alg = crypto_alg_lookup(name, type, mask);
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(alg) && crypto_is_larval(alg))
		alg = crypto_larval_रुको(alg);
	अन्यथा अगर (!alg)
		alg = crypto_larval_add(name, type, mask);

	वापस alg;
पूर्ण

पूर्णांक crypto_probing_notअगरy(अचिन्हित दीर्घ val, व्योम *v)
अणु
	पूर्णांक ok;

	ok = blocking_notअगरier_call_chain(&crypto_chain, val, v);
	अगर (ok == NOTIFY_DONE) अणु
		request_module("cryptomgr");
		ok = blocking_notअगरier_call_chain(&crypto_chain, val, v);
	पूर्ण

	वापस ok;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_probing_notअगरy);

काष्ठा crypto_alg *crypto_alg_mod_lookup(स्थिर अक्षर *name, u32 type, u32 mask)
अणु
	काष्ठा crypto_alg *alg;
	काष्ठा crypto_alg *larval;
	पूर्णांक ok;

	/*
	 * If the पूर्णांकernal flag is set क्रम a cipher, require a caller to
	 * to invoke the cipher with the पूर्णांकernal flag to use that cipher.
	 * Also, अगर a caller wants to allocate a cipher that may or may
	 * not be an पूर्णांकernal cipher, use type | CRYPTO_ALG_INTERNAL and
	 * !(mask & CRYPTO_ALG_INTERNAL).
	 */
	अगर (!((type | mask) & CRYPTO_ALG_INTERNAL))
		mask |= CRYPTO_ALG_INTERNAL;

	larval = crypto_larval_lookup(name, type, mask);
	अगर (IS_ERR(larval) || !crypto_is_larval(larval))
		वापस larval;

	ok = crypto_probing_notअगरy(CRYPTO_MSG_ALG_REQUEST, larval);

	अगर (ok == NOTIFY_STOP)
		alg = crypto_larval_रुको(larval);
	अन्यथा अणु
		crypto_mod_put(larval);
		alg = ERR_PTR(-ENOENT);
	पूर्ण
	crypto_larval_समाप्त(larval);
	वापस alg;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_alg_mod_lookup);

अटल पूर्णांक crypto_init_ops(काष्ठा crypto_tfm *tfm, u32 type, u32 mask)
अणु
	स्थिर काष्ठा crypto_type *type_obj = tfm->__crt_alg->cra_type;

	अगर (type_obj)
		वापस type_obj->init(tfm, type, mask);
	वापस 0;
पूर्ण

अटल व्योम crypto_निकास_ops(काष्ठा crypto_tfm *tfm)
अणु
	स्थिर काष्ठा crypto_type *type = tfm->__crt_alg->cra_type;

	अगर (type && tfm->निकास)
		tfm->निकास(tfm);
पूर्ण

अटल अचिन्हित पूर्णांक crypto_ctxsize(काष्ठा crypto_alg *alg, u32 type, u32 mask)
अणु
	स्थिर काष्ठा crypto_type *type_obj = alg->cra_type;
	अचिन्हित पूर्णांक len;

	len = alg->cra_alignmask & ~(crypto_tfm_ctx_alignment() - 1);
	अगर (type_obj)
		वापस len + type_obj->ctxsize(alg, type, mask);

	चयन (alg->cra_flags & CRYPTO_ALG_TYPE_MASK) अणु
	शेष:
		BUG();

	हाल CRYPTO_ALG_TYPE_CIPHER:
		len += crypto_cipher_ctxsize(alg);
		अवरोध;

	हाल CRYPTO_ALG_TYPE_COMPRESS:
		len += crypto_compress_ctxsize(alg);
		अवरोध;
	पूर्ण

	वापस len;
पूर्ण

व्योम crypto_shoot_alg(काष्ठा crypto_alg *alg)
अणु
	करोwn_ग_लिखो(&crypto_alg_sem);
	alg->cra_flags |= CRYPTO_ALG_DYING;
	up_ग_लिखो(&crypto_alg_sem);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_shoot_alg);

काष्ठा crypto_tfm *__crypto_alloc_tfm(काष्ठा crypto_alg *alg, u32 type,
				      u32 mask)
अणु
	काष्ठा crypto_tfm *tfm = शून्य;
	अचिन्हित पूर्णांक tfm_size;
	पूर्णांक err = -ENOMEM;

	tfm_size = माप(*tfm) + crypto_ctxsize(alg, type, mask);
	tfm = kzalloc(tfm_size, GFP_KERNEL);
	अगर (tfm == शून्य)
		जाओ out_err;

	tfm->__crt_alg = alg;

	err = crypto_init_ops(tfm, type, mask);
	अगर (err)
		जाओ out_मुक्त_tfm;

	अगर (!tfm->निकास && alg->cra_init && (err = alg->cra_init(tfm)))
		जाओ cra_init_failed;

	जाओ out;

cra_init_failed:
	crypto_निकास_ops(tfm);
out_मुक्त_tfm:
	अगर (err == -EAGAIN)
		crypto_shoot_alg(alg);
	kमुक्त(tfm);
out_err:
	tfm = ERR_PTR(err);
out:
	वापस tfm;
पूर्ण
EXPORT_SYMBOL_GPL(__crypto_alloc_tfm);

/*
 *	crypto_alloc_base - Locate algorithm and allocate transक्रमm
 *	@alg_name: Name of algorithm
 *	@type: Type of algorithm
 *	@mask: Mask क्रम type comparison
 *
 *	This function should not be used by new algorithm types.
 *	Please use crypto_alloc_tfm instead.
 *
 *	crypto_alloc_base() will first attempt to locate an alपढ़ोy loaded
 *	algorithm.  If that fails and the kernel supports dynamically loadable
 *	modules, it will then attempt to load a module of the same name or
 *	alias.  If that fails it will send a query to any loaded crypto manager
 *	to स्थिरruct an algorithm on the fly.  A refcount is grabbed on the
 *	algorithm which is then associated with the new transक्रमm.
 *
 *	The वापसed transक्रमm is of a non-determinate type.  Most people
 *	should use one of the more specअगरic allocation functions such as
 *	crypto_alloc_skcipher().
 *
 *	In हाल of error the वापस value is an error poपूर्णांकer.
 */
काष्ठा crypto_tfm *crypto_alloc_base(स्थिर अक्षर *alg_name, u32 type, u32 mask)
अणु
	काष्ठा crypto_tfm *tfm;
	पूर्णांक err;

	क्रम (;;) अणु
		काष्ठा crypto_alg *alg;

		alg = crypto_alg_mod_lookup(alg_name, type, mask);
		अगर (IS_ERR(alg)) अणु
			err = PTR_ERR(alg);
			जाओ err;
		पूर्ण

		tfm = __crypto_alloc_tfm(alg, type, mask);
		अगर (!IS_ERR(tfm))
			वापस tfm;

		crypto_mod_put(alg);
		err = PTR_ERR(tfm);

err:
		अगर (err != -EAGAIN)
			अवरोध;
		अगर (fatal_संकेत_pending(current)) अणु
			err = -EINTR;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_alloc_base);

व्योम *crypto_create_tfm_node(काष्ठा crypto_alg *alg,
			स्थिर काष्ठा crypto_type *frontend,
			पूर्णांक node)
अणु
	अक्षर *mem;
	काष्ठा crypto_tfm *tfm = शून्य;
	अचिन्हित पूर्णांक tfmsize;
	अचिन्हित पूर्णांक total;
	पूर्णांक err = -ENOMEM;

	tfmsize = frontend->tfmsize;
	total = tfmsize + माप(*tfm) + frontend->extsize(alg);

	mem = kzalloc_node(total, GFP_KERNEL, node);
	अगर (mem == शून्य)
		जाओ out_err;

	tfm = (काष्ठा crypto_tfm *)(mem + tfmsize);
	tfm->__crt_alg = alg;
	tfm->node = node;

	err = frontend->init_tfm(tfm);
	अगर (err)
		जाओ out_मुक्त_tfm;

	अगर (!tfm->निकास && alg->cra_init && (err = alg->cra_init(tfm)))
		जाओ cra_init_failed;

	जाओ out;

cra_init_failed:
	crypto_निकास_ops(tfm);
out_मुक्त_tfm:
	अगर (err == -EAGAIN)
		crypto_shoot_alg(alg);
	kमुक्त(mem);
out_err:
	mem = ERR_PTR(err);
out:
	वापस mem;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_create_tfm_node);

काष्ठा crypto_alg *crypto_find_alg(स्थिर अक्षर *alg_name,
				   स्थिर काष्ठा crypto_type *frontend,
				   u32 type, u32 mask)
अणु
	अगर (frontend) अणु
		type &= frontend->maskclear;
		mask &= frontend->maskclear;
		type |= frontend->type;
		mask |= frontend->maskset;
	पूर्ण

	वापस crypto_alg_mod_lookup(alg_name, type, mask);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_find_alg);

/*
 *	crypto_alloc_tfm_node - Locate algorithm and allocate transक्रमm
 *	@alg_name: Name of algorithm
 *	@frontend: Frontend algorithm type
 *	@type: Type of algorithm
 *	@mask: Mask क्रम type comparison
 *	@node: NUMA node in which users desire to put requests, अगर node is
 *		NUMA_NO_NODE, it means users have no special requirement.
 *
 *	crypto_alloc_tfm() will first attempt to locate an alपढ़ोy loaded
 *	algorithm.  If that fails and the kernel supports dynamically loadable
 *	modules, it will then attempt to load a module of the same name or
 *	alias.  If that fails it will send a query to any loaded crypto manager
 *	to स्थिरruct an algorithm on the fly.  A refcount is grabbed on the
 *	algorithm which is then associated with the new transक्रमm.
 *
 *	The वापसed transक्रमm is of a non-determinate type.  Most people
 *	should use one of the more specअगरic allocation functions such as
 *	crypto_alloc_skcipher().
 *
 *	In हाल of error the वापस value is an error poपूर्णांकer.
 */

व्योम *crypto_alloc_tfm_node(स्थिर अक्षर *alg_name,
		       स्थिर काष्ठा crypto_type *frontend, u32 type, u32 mask,
		       पूर्णांक node)
अणु
	व्योम *tfm;
	पूर्णांक err;

	क्रम (;;) अणु
		काष्ठा crypto_alg *alg;

		alg = crypto_find_alg(alg_name, frontend, type, mask);
		अगर (IS_ERR(alg)) अणु
			err = PTR_ERR(alg);
			जाओ err;
		पूर्ण

		tfm = crypto_create_tfm_node(alg, frontend, node);
		अगर (!IS_ERR(tfm))
			वापस tfm;

		crypto_mod_put(alg);
		err = PTR_ERR(tfm);

err:
		अगर (err != -EAGAIN)
			अवरोध;
		अगर (fatal_संकेत_pending(current)) अणु
			err = -EINTR;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_alloc_tfm_node);

/*
 *	crypto_destroy_tfm - Free crypto transक्रमm
 *	@mem: Start of tfm slab
 *	@tfm: Transक्रमm to मुक्त
 *
 *	This function मुक्तs up the transक्रमm and any associated resources,
 *	then drops the refcount on the associated algorithm.
 */
व्योम crypto_destroy_tfm(व्योम *mem, काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_alg *alg;

	अगर (IS_ERR_OR_शून्य(mem))
		वापस;

	alg = tfm->__crt_alg;

	अगर (!tfm->निकास && alg->cra_निकास)
		alg->cra_निकास(tfm);
	crypto_निकास_ops(tfm);
	crypto_mod_put(alg);
	kमुक्त_sensitive(mem);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_destroy_tfm);

पूर्णांक crypto_has_alg(स्थिर अक्षर *name, u32 type, u32 mask)
अणु
	पूर्णांक ret = 0;
	काष्ठा crypto_alg *alg = crypto_alg_mod_lookup(name, type, mask);

	अगर (!IS_ERR(alg)) अणु
		crypto_mod_put(alg);
		ret = 1;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_has_alg);

व्योम crypto_req_करोne(काष्ठा crypto_async_request *req, पूर्णांक err)
अणु
	काष्ठा crypto_रुको *रुको = req->data;

	अगर (err == -EINPROGRESS)
		वापस;

	रुको->err = err;
	complete(&रुको->completion);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_req_करोne);

MODULE_DESCRIPTION("Cryptographic core API");
MODULE_LICENSE("GPL");
MODULE_SOFTDEP("pre: cryptomgr");
