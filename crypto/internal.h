<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Cryptographic API.
 *
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 * Copyright (c) 2005 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */
#अगर_अघोषित _CRYPTO_INTERNAL_H
#घोषणा _CRYPTO_INTERNAL_H

#समावेश <crypto/algapi.h>
#समावेश <linux/completion.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/numa.h>
#समावेश <linux/refcount.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>

काष्ठा crypto_instance;
काष्ठा crypto_ढाँचा;

काष्ठा crypto_larval अणु
	काष्ठा crypto_alg alg;
	काष्ठा crypto_alg *adult;
	काष्ठा completion completion;
	u32 mask;
पूर्ण;

बाह्य काष्ठा list_head crypto_alg_list;
बाह्य काष्ठा rw_semaphore crypto_alg_sem;
बाह्य काष्ठा blocking_notअगरier_head crypto_chain;

#अगर_घोषित CONFIG_PROC_FS
व्योम __init crypto_init_proc(व्योम);
व्योम __निकास crypto_निकास_proc(व्योम);
#अन्यथा
अटल अंतरभूत व्योम crypto_init_proc(व्योम)
अणु पूर्ण
अटल अंतरभूत व्योम crypto_निकास_proc(व्योम)
अणु पूर्ण
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित पूर्णांक crypto_cipher_ctxsize(काष्ठा crypto_alg *alg)
अणु
	वापस alg->cra_ctxsize;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक crypto_compress_ctxsize(काष्ठा crypto_alg *alg)
अणु
	वापस alg->cra_ctxsize;
पूर्ण

काष्ठा crypto_alg *crypto_mod_get(काष्ठा crypto_alg *alg);
काष्ठा crypto_alg *crypto_alg_mod_lookup(स्थिर अक्षर *name, u32 type, u32 mask);

काष्ठा crypto_larval *crypto_larval_alloc(स्थिर अक्षर *name, u32 type, u32 mask);
व्योम crypto_larval_समाप्त(काष्ठा crypto_alg *alg);
व्योम crypto_alg_tested(स्थिर अक्षर *name, पूर्णांक err);

व्योम crypto_हटाओ_spawns(काष्ठा crypto_alg *alg, काष्ठा list_head *list,
			  काष्ठा crypto_alg *nalg);
व्योम crypto_हटाओ_final(काष्ठा list_head *list);
व्योम crypto_shoot_alg(काष्ठा crypto_alg *alg);
काष्ठा crypto_tfm *__crypto_alloc_tfm(काष्ठा crypto_alg *alg, u32 type,
				      u32 mask);
व्योम *crypto_create_tfm_node(काष्ठा crypto_alg *alg,
			स्थिर काष्ठा crypto_type *frontend, पूर्णांक node);

अटल अंतरभूत व्योम *crypto_create_tfm(काष्ठा crypto_alg *alg,
			स्थिर काष्ठा crypto_type *frontend)
अणु
	वापस crypto_create_tfm_node(alg, frontend, NUMA_NO_NODE);
पूर्ण

काष्ठा crypto_alg *crypto_find_alg(स्थिर अक्षर *alg_name,
				   स्थिर काष्ठा crypto_type *frontend,
				   u32 type, u32 mask);

व्योम *crypto_alloc_tfm_node(स्थिर अक्षर *alg_name,
		       स्थिर काष्ठा crypto_type *frontend, u32 type, u32 mask,
		       पूर्णांक node);

अटल अंतरभूत व्योम *crypto_alloc_tfm(स्थिर अक्षर *alg_name,
		       स्थिर काष्ठा crypto_type *frontend, u32 type, u32 mask)
अणु
	वापस crypto_alloc_tfm_node(alg_name, frontend, type, mask, NUMA_NO_NODE);
पूर्ण

पूर्णांक crypto_probing_notअगरy(अचिन्हित दीर्घ val, व्योम *v);

अचिन्हित पूर्णांक crypto_alg_extsize(काष्ठा crypto_alg *alg);

पूर्णांक crypto_type_has_alg(स्थिर अक्षर *name, स्थिर काष्ठा crypto_type *frontend,
			u32 type, u32 mask);

अटल अंतरभूत काष्ठा crypto_alg *crypto_alg_get(काष्ठा crypto_alg *alg)
अणु
	refcount_inc(&alg->cra_refcnt);
	वापस alg;
पूर्ण

अटल अंतरभूत व्योम crypto_alg_put(काष्ठा crypto_alg *alg)
अणु
	अगर (refcount_dec_and_test(&alg->cra_refcnt) && alg->cra_destroy)
		alg->cra_destroy(alg);
पूर्ण

अटल अंतरभूत पूर्णांक crypto_पंचांगpl_get(काष्ठा crypto_ढाँचा *पंचांगpl)
अणु
	वापस try_module_get(पंचांगpl->module);
पूर्ण

अटल अंतरभूत व्योम crypto_पंचांगpl_put(काष्ठा crypto_ढाँचा *पंचांगpl)
अणु
	module_put(पंचांगpl->module);
पूर्ण

अटल अंतरभूत पूर्णांक crypto_is_larval(काष्ठा crypto_alg *alg)
अणु
	वापस alg->cra_flags & CRYPTO_ALG_LARVAL;
पूर्ण

अटल अंतरभूत पूर्णांक crypto_is_dead(काष्ठा crypto_alg *alg)
अणु
	वापस alg->cra_flags & CRYPTO_ALG_DEAD;
पूर्ण

अटल अंतरभूत पूर्णांक crypto_is_moribund(काष्ठा crypto_alg *alg)
अणु
	वापस alg->cra_flags & (CRYPTO_ALG_DEAD | CRYPTO_ALG_DYING);
पूर्ण

अटल अंतरभूत व्योम crypto_notअगरy(अचिन्हित दीर्घ val, व्योम *v)
अणु
	blocking_notअगरier_call_chain(&crypto_chain, val, v);
पूर्ण

अटल अंतरभूत व्योम crypto_yield(u32 flags)
अणु
	अगर (flags & CRYPTO_TFM_REQ_MAY_SLEEP)
		cond_resched();
पूर्ण

#पूर्ण_अगर	/* _CRYPTO_INTERNAL_H */

