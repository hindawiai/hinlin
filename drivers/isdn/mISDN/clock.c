<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2008  by Andreas Eversberg <andreas@eversberg.eu>
 *
 * Quick API description:
 *
 * A घड़ी source रेजिस्टरs using mISDN_रेजिस्टर_घड़ी:
 *	name = text string to name घड़ी source
 *	priority = value to priorize घड़ी sources (0 = शेष)
 *	ctl = callback function to enable/disable घड़ी source
 *	priv = निजी poपूर्णांकer of घड़ी source
 *	वापस = poपूर्णांकer to घड़ी source काष्ठाure;
 *
 * Note: Callback 'ctl' can be called beक्रमe mISDN_रेजिस्टर_घड़ी वापसs!
 *       Also it can be called during mISDN_unरेजिस्टर_घड़ी.
 *
 * A घड़ी source calls mISDN_घड़ी_update with given samples elapsed, अगर
 * enabled. If function call is delayed, tv must be set with the बारtamp
 * of the actual event.
 *
 * A घड़ी source unरेजिस्टरs using mISDN_unरेजिस्टर_घड़ी.
 *
 * To get current घड़ी, call mISDN_घड़ी_get. The चिन्हित लघु value
 * counts the number of samples since. Time since last घड़ी event is added.
 */

#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/mISDNअगर.h>
#समावेश <linux/export.h>
#समावेश "core.h"

अटल u_पूर्णांक *debug;
अटल LIST_HEAD(iघड़ी_list);
अटल DEFINE_RWLOCK(iघड़ी_lock);
अटल u16 iघड़ी_count;		/* counter of last घड़ी */
अटल kसमय_प्रकार iघड़ी_प्रकारimestamp;	/* समय stamp of last घड़ी */
अटल पूर्णांक iघड़ी_प्रकारimestamp_valid;	/* alपढ़ोy received one बारtamp */
अटल काष्ठा mISDNघड़ी *iघड़ी_current;

व्योम
mISDN_init_घड़ी(u_पूर्णांक *dp)
अणु
	debug = dp;
	iघड़ी_प्रकारimestamp = kसमय_get();
पूर्ण

अटल व्योम
select_iघड़ी(व्योम)
अणु
	काष्ठा mISDNघड़ी *iघड़ी, *bestघड़ी = शून्य, *lastघड़ी = शून्य;
	पूर्णांक pri = -128;

	list_क्रम_each_entry(iघड़ी, &iघड़ी_list, list) अणु
		अगर (iघड़ी->pri > pri) अणु
			pri = iघड़ी->pri;
			bestघड़ी = iघड़ी;
		पूर्ण
		अगर (iघड़ी_current == iघड़ी)
			lastघड़ी = iघड़ी;
	पूर्ण
	अगर (lastघड़ी && bestघड़ी != lastघड़ी) अणु
		/* last used घड़ी source still exists but changes, disable */
		अगर (*debug & DEBUG_CLOCK)
			prपूर्णांकk(KERN_DEBUG "Old clock source '%s' disable.\n",
			       lastघड़ी->name);
		lastघड़ी->ctl(lastघड़ी->priv, 0);
	पूर्ण
	अगर (bestघड़ी && bestघड़ी != iघड़ी_current) अणु
		/* new घड़ी source selected, enable */
		अगर (*debug & DEBUG_CLOCK)
			prपूर्णांकk(KERN_DEBUG "New clock source '%s' enable.\n",
			       bestघड़ी->name);
		bestघड़ी->ctl(bestघड़ी->priv, 1);
	पूर्ण
	अगर (bestघड़ी != iघड़ी_current) अणु
		/* no घड़ी received yet */
		iघड़ी_प्रकारimestamp_valid = 0;
	पूर्ण
	iघड़ी_current = bestघड़ी;
पूर्ण

काष्ठा mISDNघड़ी
*mISDN_रेजिस्टर_घड़ी(अक्षर *name, पूर्णांक pri, घड़ीctl_func_t *ctl, व्योम *priv)
अणु
	u_दीर्घ			flags;
	काष्ठा mISDNघड़ी	*iघड़ी;

	अगर (*debug & (DEBUG_CORE | DEBUG_CLOCK))
		prपूर्णांकk(KERN_DEBUG "%s: %s %d\n", __func__, name, pri);
	iघड़ी = kzalloc(माप(काष्ठा mISDNघड़ी), GFP_ATOMIC);
	अगर (!iघड़ी) अणु
		prपूर्णांकk(KERN_ERR "%s: No memory for clock entry.\n", __func__);
		वापस शून्य;
	पूर्ण
	म_नकलन(iघड़ी->name, name, माप(iघड़ी->name) - 1);
	iघड़ी->pri = pri;
	iघड़ी->priv = priv;
	iघड़ी->ctl = ctl;
	ग_लिखो_lock_irqsave(&iघड़ी_lock, flags);
	list_add_tail(&iघड़ी->list, &iघड़ी_list);
	select_iघड़ी();
	ग_लिखो_unlock_irqrestore(&iघड़ी_lock, flags);
	वापस iघड़ी;
पूर्ण
EXPORT_SYMBOL(mISDN_रेजिस्टर_घड़ी);

व्योम
mISDN_unरेजिस्टर_घड़ी(काष्ठा mISDNघड़ी *iघड़ी)
अणु
	u_दीर्घ	flags;

	अगर (*debug & (DEBUG_CORE | DEBUG_CLOCK))
		prपूर्णांकk(KERN_DEBUG "%s: %s %d\n", __func__, iघड़ी->name,
		       iघड़ी->pri);
	ग_लिखो_lock_irqsave(&iघड़ी_lock, flags);
	अगर (iघड़ी_current == iघड़ी) अणु
		अगर (*debug & DEBUG_CLOCK)
			prपूर्णांकk(KERN_DEBUG
			       "Current clock source '%s' unregisters.\n",
			       iघड़ी->name);
		iघड़ी->ctl(iघड़ी->priv, 0);
	पूर्ण
	list_del(&iघड़ी->list);
	select_iघड़ी();
	ग_लिखो_unlock_irqrestore(&iघड़ी_lock, flags);
पूर्ण
EXPORT_SYMBOL(mISDN_unरेजिस्टर_घड़ी);

व्योम
mISDN_घड़ी_update(काष्ठा mISDNघड़ी *iघड़ी, पूर्णांक samples, kसमय_प्रकार *बारtamp)
अणु
	u_दीर्घ		flags;
	kसमय_प्रकार		बारtamp_now;
	u16		delta;

	ग_लिखो_lock_irqsave(&iघड़ी_lock, flags);
	अगर (iघड़ी_current != iघड़ी) अणु
		prपूर्णांकk(KERN_ERR "%s: '%s' sends us clock updates, but we do "
		       "listen to '%s'. This is a bug!\n", __func__,
		       iघड़ी->name,
		       iघड़ी_current ? iघड़ी_current->name : "nothing");
		iघड़ी->ctl(iघड़ी->priv, 0);
		ग_लिखो_unlock_irqrestore(&iघड़ी_lock, flags);
		वापस;
	पूर्ण
	अगर (iघड़ी_प्रकारimestamp_valid) अणु
		/* increment sample counter by given samples */
		iघड़ी_count += samples;
		अगर (बारtamp) अणु /* बारtamp must be set, अगर function call is delayed */
			iघड़ी_प्रकारimestamp = *बारtamp;
		पूर्ण अन्यथा	अणु
			iघड़ी_प्रकारimestamp = kसमय_get();
		पूर्ण
	पूर्ण अन्यथा अणु
		/* calc elapsed समय by प्रणाली घड़ी */
		अगर (बारtamp) अणु /* बारtamp must be set, अगर function call is delayed */
			बारtamp_now = *बारtamp;
		पूर्ण अन्यथा अणु
			बारtamp_now = kसमय_get();
		पूर्ण
		delta = kसमय_भागns(kसमय_sub(बारtamp_now, iघड़ी_प्रकारimestamp),
				(NSEC_PER_SEC / 8000));
		/* add elapsed समय to counter and set new बारtamp */
		iघड़ी_count += delta;
		iघड़ी_प्रकारimestamp = बारtamp_now;
		iघड़ी_प्रकारimestamp_valid = 1;
		अगर (*debug & DEBUG_CLOCK)
			prपूर्णांकk("Received first clock from source '%s'.\n",
			       iघड़ी_current ? iघड़ी_current->name : "nothing");
	पूर्ण
	ग_लिखो_unlock_irqrestore(&iघड़ी_lock, flags);
पूर्ण
EXPORT_SYMBOL(mISDN_घड़ी_update);

अचिन्हित लघु
mISDN_घड़ी_get(व्योम)
अणु
	u_दीर्घ		flags;
	kसमय_प्रकार		बारtamp_now;
	u16		delta;
	u16		count;

	पढ़ो_lock_irqsave(&iघड़ी_lock, flags);
	/* calc elapsed समय by प्रणाली घड़ी */
	बारtamp_now = kसमय_get();
	delta = kसमय_भागns(kसमय_sub(बारtamp_now, iघड़ी_प्रकारimestamp),
			(NSEC_PER_SEC / 8000));
	/* add elapsed समय to counter */
	count =	iघड़ी_count + delta;
	पढ़ो_unlock_irqrestore(&iघड़ी_lock, flags);
	वापस count;
पूर्ण
EXPORT_SYMBOL(mISDN_घड़ी_get);
