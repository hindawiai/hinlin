<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * T10 Data Integrity Field CRC16 calculation
 *
 * Copyright (c) 2007 Oracle Corporation.  All rights reserved.
 * Written by Martin K. Petersen <martin.petersen@oracle.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/crc-t10dअगर.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/algapi.h>
#समावेश <linux/अटल_key.h>
#समावेश <linux/notअगरier.h>

अटल काष्ठा crypto_shash __rcu *crct10dअगर_tfm;
अटल DEFINE_STATIC_KEY_TRUE(crct10dअगर_fallback);
अटल DEFINE_MUTEX(crc_t10dअगर_mutex);
अटल काष्ठा work_काष्ठा crct10dअगर_rehash_work;

अटल पूर्णांक crc_t10dअगर_notअगरy(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा crypto_alg *alg = data;

	अगर (val != CRYPTO_MSG_ALG_LOADED ||
	    म_भेद(alg->cra_name, CRC_T10DIF_STRING))
		वापस NOTIFY_DONE;

	schedule_work(&crct10dअगर_rehash_work);
	वापस NOTIFY_OK;
पूर्ण

अटल व्योम crc_t10dअगर_rehash(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा crypto_shash *new, *old;

	mutex_lock(&crc_t10dअगर_mutex);
	old = rcu_dereference_रक्षित(crct10dअगर_tfm,
					lockdep_is_held(&crc_t10dअगर_mutex));
	new = crypto_alloc_shash(CRC_T10DIF_STRING, 0, 0);
	अगर (IS_ERR(new)) अणु
		mutex_unlock(&crc_t10dअगर_mutex);
		वापस;
	पूर्ण
	rcu_assign_poपूर्णांकer(crct10dअगर_tfm, new);
	mutex_unlock(&crc_t10dअगर_mutex);

	अगर (old) अणु
		synchronize_rcu();
		crypto_मुक्त_shash(old);
	पूर्ण अन्यथा अणु
		अटल_branch_disable(&crct10dअगर_fallback);
	पूर्ण
पूर्ण

अटल काष्ठा notअगरier_block crc_t10dअगर_nb = अणु
	.notअगरier_call = crc_t10dअगर_notअगरy,
पूर्ण;

__u16 crc_t10dअगर_update(__u16 crc, स्थिर अचिन्हित अक्षर *buffer, माप_प्रकार len)
अणु
	काष्ठा अणु
		काष्ठा shash_desc shash;
		__u16 crc;
	पूर्ण desc;
	पूर्णांक err;

	अगर (अटल_branch_unlikely(&crct10dअगर_fallback))
		वापस crc_t10dअगर_generic(crc, buffer, len);

	rcu_पढ़ो_lock();
	desc.shash.tfm = rcu_dereference(crct10dअगर_tfm);
	desc.crc = crc;
	err = crypto_shash_update(&desc.shash, buffer, len);
	rcu_पढ़ो_unlock();

	BUG_ON(err);

	वापस desc.crc;
पूर्ण
EXPORT_SYMBOL(crc_t10dअगर_update);

__u16 crc_t10dअगर(स्थिर अचिन्हित अक्षर *buffer, माप_प्रकार len)
अणु
	वापस crc_t10dअगर_update(0, buffer, len);
पूर्ण
EXPORT_SYMBOL(crc_t10dअगर);

अटल पूर्णांक __init crc_t10dअगर_mod_init(व्योम)
अणु
	INIT_WORK(&crct10dअगर_rehash_work, crc_t10dअगर_rehash);
	crypto_रेजिस्टर_notअगरier(&crc_t10dअगर_nb);
	crc_t10dअगर_rehash(&crct10dअगर_rehash_work);
	वापस 0;
पूर्ण

अटल व्योम __निकास crc_t10dअगर_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_notअगरier(&crc_t10dअगर_nb);
	cancel_work_sync(&crct10dअगर_rehash_work);
	crypto_मुक्त_shash(rcu_dereference_रक्षित(crct10dअगर_tfm, 1));
पूर्ण

module_init(crc_t10dअगर_mod_init);
module_निकास(crc_t10dअगर_mod_fini);

अटल पूर्णांक crc_t10dअगर_transक्रमm_show(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	काष्ठा crypto_shash *tfm;
	पूर्णांक len;

	अगर (अटल_branch_unlikely(&crct10dअगर_fallback))
		वापस प्र_लिखो(buffer, "fallback\n");

	rcu_पढ़ो_lock();
	tfm = rcu_dereference(crct10dअगर_tfm);
	len = snम_लिखो(buffer, PAGE_SIZE, "%s\n",
		       crypto_shash_driver_name(tfm));
	rcu_पढ़ो_unlock();

	वापस len;
पूर्ण

module_param_call(transक्रमm, शून्य, crc_t10dअगर_transक्रमm_show, शून्य, 0444);

MODULE_DESCRIPTION("T10 DIF CRC calculation (library API)");
MODULE_LICENSE("GPL");
MODULE_SOFTDEP("pre: crct10dif");
