<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * lib80211 -- common bits क्रम IEEE802.11 drivers
 *
 * Copyright(c) 2008 John W. Linville <linville@tuxdriver.com>
 *
 * Portions copied from old ieee80211 component, w/ original copyright
 * notices below:
 *
 * Host AP crypto routines
 *
 * Copyright (c) 2002-2003, Jouni Malinen <j@w1.fi>
 * Portions Copyright (C) 2004, Intel Corporation <jketreno@linux.पूर्णांकel.com>
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/ieee80211.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश <net/lib80211.h>

#घोषणा DRV_DESCRIPTION	"common routines for IEEE802.11 drivers"

MODULE_DESCRIPTION(DRV_DESCRIPTION);
MODULE_AUTHOR("John W. Linville <linville@tuxdriver.com>");
MODULE_LICENSE("GPL");

काष्ठा lib80211_crypto_alg अणु
	काष्ठा list_head list;
	काष्ठा lib80211_crypto_ops *ops;
पूर्ण;

अटल LIST_HEAD(lib80211_crypto_algs);
अटल DEFINE_SPINLOCK(lib80211_crypto_lock);

अटल व्योम lib80211_crypt_deinit_entries(काष्ठा lib80211_crypt_info *info,
					  पूर्णांक क्रमce);
अटल व्योम lib80211_crypt_quiescing(काष्ठा lib80211_crypt_info *info);
अटल व्योम lib80211_crypt_deinit_handler(काष्ठा समयr_list *t);

पूर्णांक lib80211_crypt_info_init(काष्ठा lib80211_crypt_info *info, अक्षर *name,
				spinlock_t *lock)
अणु
	स_रखो(info, 0, माप(*info));

	info->name = name;
	info->lock = lock;

	INIT_LIST_HEAD(&info->crypt_deinit_list);
	समयr_setup(&info->crypt_deinit_समयr, lib80211_crypt_deinit_handler,
		    0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(lib80211_crypt_info_init);

व्योम lib80211_crypt_info_मुक्त(काष्ठा lib80211_crypt_info *info)
अणु
	पूर्णांक i;

        lib80211_crypt_quiescing(info);
        del_समयr_sync(&info->crypt_deinit_समयr);
        lib80211_crypt_deinit_entries(info, 1);

        क्रम (i = 0; i < NUM_WEP_KEYS; i++) अणु
                काष्ठा lib80211_crypt_data *crypt = info->crypt[i];
                अगर (crypt) अणु
                        अगर (crypt->ops) अणु
                                crypt->ops->deinit(crypt->priv);
                                module_put(crypt->ops->owner);
                        पूर्ण
                        kमुक्त(crypt);
                        info->crypt[i] = शून्य;
                पूर्ण
        पूर्ण
पूर्ण
EXPORT_SYMBOL(lib80211_crypt_info_मुक्त);

अटल व्योम lib80211_crypt_deinit_entries(काष्ठा lib80211_crypt_info *info,
					  पूर्णांक क्रमce)
अणु
	काष्ठा lib80211_crypt_data *entry, *next;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(info->lock, flags);
	list_क्रम_each_entry_safe(entry, next, &info->crypt_deinit_list, list) अणु
		अगर (atomic_पढ़ो(&entry->refcnt) != 0 && !क्रमce)
			जारी;

		list_del(&entry->list);

		अगर (entry->ops) अणु
			entry->ops->deinit(entry->priv);
			module_put(entry->ops->owner);
		पूर्ण
		kमुक्त(entry);
	पूर्ण
	spin_unlock_irqrestore(info->lock, flags);
पूर्ण

/* After this, crypt_deinit_list won't accept new members */
अटल व्योम lib80211_crypt_quiescing(काष्ठा lib80211_crypt_info *info)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(info->lock, flags);
	info->crypt_quiesced = 1;
	spin_unlock_irqrestore(info->lock, flags);
पूर्ण

अटल व्योम lib80211_crypt_deinit_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा lib80211_crypt_info *info = from_समयr(info, t,
						      crypt_deinit_समयr);
	अचिन्हित दीर्घ flags;

	lib80211_crypt_deinit_entries(info, 0);

	spin_lock_irqsave(info->lock, flags);
	अगर (!list_empty(&info->crypt_deinit_list) && !info->crypt_quiesced) अणु
		prपूर्णांकk(KERN_DEBUG "%s: entries remaining in delayed crypt "
		       "deletion list\n", info->name);
		info->crypt_deinit_समयr.expires = jअगरfies + HZ;
		add_समयr(&info->crypt_deinit_समयr);
	पूर्ण
	spin_unlock_irqrestore(info->lock, flags);
पूर्ण

व्योम lib80211_crypt_delayed_deinit(काष्ठा lib80211_crypt_info *info,
				    काष्ठा lib80211_crypt_data **crypt)
अणु
	काष्ठा lib80211_crypt_data *पंचांगp;
	अचिन्हित दीर्घ flags;

	अगर (*crypt == शून्य)
		वापस;

	पंचांगp = *crypt;
	*crypt = शून्य;

	/* must not run ops->deinit() जबतक there may be pending encrypt or
	 * decrypt operations. Use a list of delayed deinits to aव्योम needing
	 * locking. */

	spin_lock_irqsave(info->lock, flags);
	अगर (!info->crypt_quiesced) अणु
		list_add(&पंचांगp->list, &info->crypt_deinit_list);
		अगर (!समयr_pending(&info->crypt_deinit_समयr)) अणु
			info->crypt_deinit_समयr.expires = jअगरfies + HZ;
			add_समयr(&info->crypt_deinit_समयr);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(info->lock, flags);
पूर्ण
EXPORT_SYMBOL(lib80211_crypt_delayed_deinit);

पूर्णांक lib80211_रेजिस्टर_crypto_ops(काष्ठा lib80211_crypto_ops *ops)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा lib80211_crypto_alg *alg;

	alg = kzalloc(माप(*alg), GFP_KERNEL);
	अगर (alg == शून्य)
		वापस -ENOMEM;

	alg->ops = ops;

	spin_lock_irqsave(&lib80211_crypto_lock, flags);
	list_add(&alg->list, &lib80211_crypto_algs);
	spin_unlock_irqrestore(&lib80211_crypto_lock, flags);

	prपूर्णांकk(KERN_DEBUG "lib80211_crypt: registered algorithm '%s'\n",
	       ops->name);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(lib80211_रेजिस्टर_crypto_ops);

पूर्णांक lib80211_unरेजिस्टर_crypto_ops(काष्ठा lib80211_crypto_ops *ops)
अणु
	काष्ठा lib80211_crypto_alg *alg;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&lib80211_crypto_lock, flags);
	list_क्रम_each_entry(alg, &lib80211_crypto_algs, list) अणु
		अगर (alg->ops == ops)
			जाओ found;
	पूर्ण
	spin_unlock_irqrestore(&lib80211_crypto_lock, flags);
	वापस -EINVAL;

      found:
	prपूर्णांकk(KERN_DEBUG "lib80211_crypt: unregistered algorithm '%s'\n",
	       ops->name);
	list_del(&alg->list);
	spin_unlock_irqrestore(&lib80211_crypto_lock, flags);
	kमुक्त(alg);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(lib80211_unरेजिस्टर_crypto_ops);

काष्ठा lib80211_crypto_ops *lib80211_get_crypto_ops(स्थिर अक्षर *name)
अणु
	काष्ठा lib80211_crypto_alg *alg;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&lib80211_crypto_lock, flags);
	list_क्रम_each_entry(alg, &lib80211_crypto_algs, list) अणु
		अगर (म_भेद(alg->ops->name, name) == 0)
			जाओ found;
	पूर्ण
	spin_unlock_irqrestore(&lib80211_crypto_lock, flags);
	वापस शून्य;

      found:
	spin_unlock_irqrestore(&lib80211_crypto_lock, flags);
	वापस alg->ops;
पूर्ण
EXPORT_SYMBOL(lib80211_get_crypto_ops);

अटल व्योम *lib80211_crypt_null_init(पूर्णांक keyidx)
अणु
	वापस (व्योम *)1;
पूर्ण

अटल व्योम lib80211_crypt_null_deinit(व्योम *priv)
अणु
पूर्ण

अटल काष्ठा lib80211_crypto_ops lib80211_crypt_null = अणु
	.name = "NULL",
	.init = lib80211_crypt_null_init,
	.deinit = lib80211_crypt_null_deinit,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init lib80211_init(व्योम)
अणु
	pr_info(DRV_DESCRIPTION "\n");
	वापस lib80211_रेजिस्टर_crypto_ops(&lib80211_crypt_null);
पूर्ण

अटल व्योम __निकास lib80211_निकास(व्योम)
अणु
	lib80211_unरेजिस्टर_crypto_ops(&lib80211_crypt_null);
	BUG_ON(!list_empty(&lib80211_crypto_algs));
पूर्ण

module_init(lib80211_init);
module_निकास(lib80211_निकास);
