<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015-2016 Mentor Graphics
 */

#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/watchकरोg.h>

#समावेश "watchdog_pretimeout.h"

/* Default watchकरोg preसमयout governor */
अटल काष्ठा watchकरोg_governor *शेष_gov;

/* The spinlock protects शेष_gov, wdd->gov and preसमयout_list */
अटल DEFINE_SPINLOCK(preसमयout_lock);

/* List of watchकरोg devices, which can generate a preसमयout event */
अटल LIST_HEAD(preसमयout_list);

काष्ठा watchकरोg_preसमयout अणु
	काष्ठा watchकरोg_device		*wdd;
	काष्ठा list_head		entry;
पूर्ण;

/* The mutex protects governor list and serializes बाह्यal पूर्णांकerfaces */
अटल DEFINE_MUTEX(governor_lock);

/* List of the रेजिस्टरed watchकरोg preसमयout governors */
अटल LIST_HEAD(governor_list);

काष्ठा governor_priv अणु
	काष्ठा watchकरोg_governor	*gov;
	काष्ठा list_head		entry;
पूर्ण;

अटल काष्ठा governor_priv *find_governor_by_name(स्थिर अक्षर *gov_name)
अणु
	काष्ठा governor_priv *priv;

	list_क्रम_each_entry(priv, &governor_list, entry)
		अगर (sysfs_streq(gov_name, priv->gov->name))
			वापस priv;

	वापस शून्य;
पूर्ण

पूर्णांक watchकरोg_preसमयout_available_governors_get(अक्षर *buf)
अणु
	काष्ठा governor_priv *priv;
	पूर्णांक count = 0;

	mutex_lock(&governor_lock);

	list_क्रम_each_entry(priv, &governor_list, entry)
		count += प्र_लिखो(buf + count, "%s\n", priv->gov->name);

	mutex_unlock(&governor_lock);

	वापस count;
पूर्ण

पूर्णांक watchकरोg_preसमयout_governor_get(काष्ठा watchकरोg_device *wdd, अक्षर *buf)
अणु
	पूर्णांक count = 0;

	spin_lock_irq(&preसमयout_lock);
	अगर (wdd->gov)
		count = प्र_लिखो(buf, "%s\n", wdd->gov->name);
	spin_unlock_irq(&preसमयout_lock);

	वापस count;
पूर्ण

पूर्णांक watchकरोg_preसमयout_governor_set(काष्ठा watchकरोg_device *wdd,
				     स्थिर अक्षर *buf)
अणु
	काष्ठा governor_priv *priv;

	mutex_lock(&governor_lock);

	priv = find_governor_by_name(buf);
	अगर (!priv) अणु
		mutex_unlock(&governor_lock);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irq(&preसमयout_lock);
	wdd->gov = priv->gov;
	spin_unlock_irq(&preसमयout_lock);

	mutex_unlock(&governor_lock);

	वापस 0;
पूर्ण

व्योम watchकरोg_notअगरy_preसमयout(काष्ठा watchकरोg_device *wdd)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&preसमयout_lock, flags);
	अगर (!wdd->gov) अणु
		spin_unlock_irqrestore(&preसमयout_lock, flags);
		वापस;
	पूर्ण

	wdd->gov->preसमयout(wdd);
	spin_unlock_irqrestore(&preसमयout_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(watchकरोg_notअगरy_preसमयout);

पूर्णांक watchकरोg_रेजिस्टर_governor(काष्ठा watchकरोg_governor *gov)
अणु
	काष्ठा watchकरोg_preसमयout *p;
	काष्ठा governor_priv *priv;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	mutex_lock(&governor_lock);

	अगर (find_governor_by_name(gov->name)) अणु
		mutex_unlock(&governor_lock);
		kमुक्त(priv);
		वापस -EBUSY;
	पूर्ण

	priv->gov = gov;
	list_add(&priv->entry, &governor_list);

	अगर (!म_भेदन(gov->name, WATCHDOG_PRETIMEOUT_DEFAULT_GOV,
		     WATCHDOG_GOV_NAME_MAXLEN)) अणु
		spin_lock_irq(&preसमयout_lock);
		शेष_gov = gov;

		list_क्रम_each_entry(p, &preसमयout_list, entry)
			अगर (!p->wdd->gov)
				p->wdd->gov = शेष_gov;
		spin_unlock_irq(&preसमयout_lock);
	पूर्ण

	mutex_unlock(&governor_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(watchकरोg_रेजिस्टर_governor);

व्योम watchकरोg_unरेजिस्टर_governor(काष्ठा watchकरोg_governor *gov)
अणु
	काष्ठा watchकरोg_preसमयout *p;
	काष्ठा governor_priv *priv, *t;

	mutex_lock(&governor_lock);

	list_क्रम_each_entry_safe(priv, t, &governor_list, entry) अणु
		अगर (priv->gov == gov) अणु
			list_del(&priv->entry);
			kमुक्त(priv);
			अवरोध;
		पूर्ण
	पूर्ण

	spin_lock_irq(&preसमयout_lock);
	list_क्रम_each_entry(p, &preसमयout_list, entry)
		अगर (p->wdd->gov == gov)
			p->wdd->gov = शेष_gov;
	spin_unlock_irq(&preसमयout_lock);

	mutex_unlock(&governor_lock);
पूर्ण
EXPORT_SYMBOL(watchकरोg_unरेजिस्टर_governor);

पूर्णांक watchकरोg_रेजिस्टर_preसमयout(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा watchकरोg_preसमयout *p;

	अगर (!(wdd->info->options & WDIOF_PRETIMEOUT))
		वापस 0;

	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	spin_lock_irq(&preसमयout_lock);
	list_add(&p->entry, &preसमयout_list);
	p->wdd = wdd;
	wdd->gov = शेष_gov;
	spin_unlock_irq(&preसमयout_lock);

	वापस 0;
पूर्ण

व्योम watchकरोg_unरेजिस्टर_preसमयout(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा watchकरोg_preसमयout *p, *t;

	अगर (!(wdd->info->options & WDIOF_PRETIMEOUT))
		वापस;

	spin_lock_irq(&preसमयout_lock);
	wdd->gov = शून्य;

	list_क्रम_each_entry_safe(p, t, &preसमयout_list, entry) अणु
		अगर (p->wdd == wdd) अणु
			list_del(&p->entry);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&preसमयout_lock);

	kमुक्त(p);
पूर्ण
