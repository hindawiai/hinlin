<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Host AP crypto routines
 *
 * Copyright (c) 2002-2003, Jouni Malinen <jkmaline@cc.hut.fi>
 * Portions Copyright (C) 2004, Intel Corporation <jketreno@linux.पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>

#समावेश "ieee80211.h"

MODULE_AUTHOR("Jouni Malinen");
MODULE_DESCRIPTION("HostAP crypto");
MODULE_LICENSE("GPL");

काष्ठा ieee80211_crypto_alg अणु
	काष्ठा list_head list;
	काष्ठा ieee80211_crypto_ops *ops;
पूर्ण;


काष्ठा ieee80211_crypto अणु
	काष्ठा list_head algs;
	spinlock_t lock;
पूर्ण;

अटल काष्ठा ieee80211_crypto *hcrypt;

व्योम ieee80211_crypt_deinit_entries(काष्ठा ieee80211_device *ieee,
					   पूर्णांक क्रमce)
अणु
	काष्ठा list_head *ptr, *n;
	काष्ठा ieee80211_crypt_data *entry;

	क्रम (ptr = ieee->crypt_deinit_list.next, n = ptr->next;
	     ptr != &ieee->crypt_deinit_list; ptr = n, n = ptr->next) अणु
		entry = list_entry(ptr, काष्ठा ieee80211_crypt_data, list);

		अगर (atomic_पढ़ो(&entry->refcnt) != 0 && !क्रमce)
			जारी;

		list_del(ptr);

		अगर (entry->ops)
			entry->ops->deinit(entry->priv);
		kमुक्त(entry);
	पूर्ण
पूर्ण

व्योम ieee80211_crypt_deinit_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा ieee80211_device *ieee = from_समयr(ieee, t, crypt_deinit_समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ieee->lock, flags);
	ieee80211_crypt_deinit_entries(ieee, 0);
	अगर (!list_empty(&ieee->crypt_deinit_list)) अणु
		netdev_dbg(ieee->dev, "%s: entries remaining in delayed crypt deletion list\n",
				ieee->dev->name);
		ieee->crypt_deinit_समयr.expires = jअगरfies + HZ;
		add_समयr(&ieee->crypt_deinit_समयr);
	पूर्ण
	spin_unlock_irqrestore(&ieee->lock, flags);

पूर्ण

व्योम ieee80211_crypt_delayed_deinit(काष्ठा ieee80211_device *ieee,
				    काष्ठा ieee80211_crypt_data **crypt)
अणु
	काष्ठा ieee80211_crypt_data *पंचांगp;
	अचिन्हित दीर्घ flags;

	अगर (!(*crypt))
		वापस;

	पंचांगp = *crypt;
	*crypt = शून्य;

	/* must not run ops->deinit() जबतक there may be pending encrypt or
	 * decrypt operations. Use a list of delayed deinits to aव्योम needing
	 * locking.
	 */

	spin_lock_irqsave(&ieee->lock, flags);
	list_add(&पंचांगp->list, &ieee->crypt_deinit_list);
	अगर (!समयr_pending(&ieee->crypt_deinit_समयr)) अणु
		ieee->crypt_deinit_समयr.expires = jअगरfies + HZ;
		add_समयr(&ieee->crypt_deinit_समयr);
	पूर्ण
	spin_unlock_irqrestore(&ieee->lock, flags);
पूर्ण

पूर्णांक ieee80211_रेजिस्टर_crypto_ops(काष्ठा ieee80211_crypto_ops *ops)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ieee80211_crypto_alg *alg;

	अगर (!hcrypt)
		वापस -1;

	alg = kzalloc(माप(*alg), GFP_KERNEL);
	अगर (!alg)
		वापस -ENOMEM;

	alg->ops = ops;

	spin_lock_irqsave(&hcrypt->lock, flags);
	list_add(&alg->list, &hcrypt->algs);
	spin_unlock_irqrestore(&hcrypt->lock, flags);

	pr_debug("ieee80211_crypt: registered algorithm '%s'\n",
	       ops->name);

	वापस 0;
पूर्ण

पूर्णांक ieee80211_unरेजिस्टर_crypto_ops(काष्ठा ieee80211_crypto_ops *ops)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *ptr;
	काष्ठा ieee80211_crypto_alg *del_alg = शून्य;

	अगर (!hcrypt)
		वापस -1;

	spin_lock_irqsave(&hcrypt->lock, flags);
	क्रम (ptr = hcrypt->algs.next; ptr != &hcrypt->algs; ptr = ptr->next) अणु
		काष्ठा ieee80211_crypto_alg *alg =
			(काष्ठा ieee80211_crypto_alg *)ptr;
		अगर (alg->ops == ops) अणु
			list_del(&alg->list);
			del_alg = alg;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&hcrypt->lock, flags);

	अगर (del_alg) अणु
		pr_debug("ieee80211_crypt: unregistered algorithm '%s'\n",
				ops->name);
		kमुक्त(del_alg);
	पूर्ण

	वापस del_alg ? 0 : -1;
पूर्ण


काष्ठा ieee80211_crypto_ops *ieee80211_get_crypto_ops(स्थिर अक्षर *name)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *ptr;
	काष्ठा ieee80211_crypto_alg *found_alg = शून्य;

	अगर (!hcrypt)
		वापस शून्य;

	spin_lock_irqsave(&hcrypt->lock, flags);
	क्रम (ptr = hcrypt->algs.next; ptr != &hcrypt->algs; ptr = ptr->next) अणु
		काष्ठा ieee80211_crypto_alg *alg =
			(काष्ठा ieee80211_crypto_alg *)ptr;
		अगर (म_भेद(alg->ops->name, name) == 0) अणु
			found_alg = alg;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&hcrypt->lock, flags);

	अगर (found_alg)
		वापस found_alg->ops;
	वापस शून्य;
पूर्ण


अटल व्योम *ieee80211_crypt_null_init(पूर्णांक keyidx) अणु वापस (व्योम *)1; पूर्ण
अटल व्योम ieee80211_crypt_null_deinit(व्योम *priv) अणुपूर्ण

अटल काष्ठा ieee80211_crypto_ops ieee80211_crypt_null = अणु
	.name			= "NULL",
	.init			= ieee80211_crypt_null_init,
	.deinit			= ieee80211_crypt_null_deinit,
	.encrypt_mpdu		= शून्य,
	.decrypt_mpdu		= शून्य,
	.encrypt_msdu		= शून्य,
	.decrypt_msdu		= शून्य,
	.set_key		= शून्य,
	.get_key		= शून्य,
	.extra_prefix_len	= 0,
	.extra_postfix_len	= 0,
	.owner			= THIS_MODULE,
पूर्ण;

पूर्णांक __init ieee80211_crypto_init(व्योम)
अणु
	पूर्णांक ret = -ENOMEM;

	hcrypt = kzalloc(माप(*hcrypt), GFP_KERNEL);
	अगर (!hcrypt)
		जाओ out;

	INIT_LIST_HEAD(&hcrypt->algs);
	spin_lock_init(&hcrypt->lock);

	ret = ieee80211_रेजिस्टर_crypto_ops(&ieee80211_crypt_null);
	अगर (ret < 0) अणु
		kमुक्त(hcrypt);
		hcrypt = शून्य;
	पूर्ण
out:
	वापस ret;
पूर्ण

व्योम __निकास ieee80211_crypto_deinit(व्योम)
अणु
	काष्ठा list_head *ptr, *n;

	अगर (!hcrypt)
		वापस;

	क्रम (ptr = hcrypt->algs.next, n = ptr->next; ptr != &hcrypt->algs;
	     ptr = n, n = ptr->next) अणु
		काष्ठा ieee80211_crypto_alg *alg =
			(काष्ठा ieee80211_crypto_alg *)ptr;
		list_del(ptr);
		pr_debug("ieee80211_crypt: unregistered algorithm '%s' (deinit)\n",
				alg->ops->name);
		kमुक्त(alg);
	पूर्ण

	kमुक्त(hcrypt);
पूर्ण
