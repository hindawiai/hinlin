<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * kernel/घातer/wakelock.c
 *
 * User space wakeup sources support.
 *
 * Copyright (C) 2012 Rafael J. Wysocki <rjw@sisk.pl>
 *
 * This code is based on the analogous पूर्णांकerface allowing user space to
 * manipulate wakelocks on Android.
 */

#समावेश <linux/capability.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/list.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

#समावेश "power.h"

अटल DEFINE_MUTEX(wakelocks_lock);

काष्ठा wakelock अणु
	अक्षर			*name;
	काष्ठा rb_node		node;
	काष्ठा wakeup_source	*ws;
#अगर_घोषित CONFIG_PM_WAKELOCKS_GC
	काष्ठा list_head	lru;
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा rb_root wakelocks_tree = RB_ROOT;

sमाप_प्रकार pm_show_wakelocks(अक्षर *buf, bool show_active)
अणु
	काष्ठा rb_node *node;
	काष्ठा wakelock *wl;
	अक्षर *str = buf;
	अक्षर *end = buf + PAGE_SIZE;

	mutex_lock(&wakelocks_lock);

	क्रम (node = rb_first(&wakelocks_tree); node; node = rb_next(node)) अणु
		wl = rb_entry(node, काष्ठा wakelock, node);
		अगर (wl->ws->active == show_active)
			str += scnम_लिखो(str, end - str, "%s ", wl->name);
	पूर्ण
	अगर (str > buf)
		str--;

	str += scnम_लिखो(str, end - str, "\n");

	mutex_unlock(&wakelocks_lock);
	वापस (str - buf);
पूर्ण

#अगर CONFIG_PM_WAKELOCKS_LIMIT > 0
अटल अचिन्हित पूर्णांक number_of_wakelocks;

अटल अंतरभूत bool wakelocks_limit_exceeded(व्योम)
अणु
	वापस number_of_wakelocks > CONFIG_PM_WAKELOCKS_LIMIT;
पूर्ण

अटल अंतरभूत व्योम increment_wakelocks_number(व्योम)
अणु
	number_of_wakelocks++;
पूर्ण

अटल अंतरभूत व्योम decrement_wakelocks_number(व्योम)
अणु
	number_of_wakelocks--;
पूर्ण
#अन्यथा /* CONFIG_PM_WAKELOCKS_LIMIT = 0 */
अटल अंतरभूत bool wakelocks_limit_exceeded(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम increment_wakelocks_number(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम decrement_wakelocks_number(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_PM_WAKELOCKS_LIMIT */

#अगर_घोषित CONFIG_PM_WAKELOCKS_GC
#घोषणा WL_GC_COUNT_MAX	100
#घोषणा WL_GC_TIME_SEC	300

अटल व्योम __wakelocks_gc(काष्ठा work_काष्ठा *work);
अटल LIST_HEAD(wakelocks_lru_list);
अटल DECLARE_WORK(wakelock_work, __wakelocks_gc);
अटल अचिन्हित पूर्णांक wakelocks_gc_count;

अटल अंतरभूत व्योम wakelocks_lru_add(काष्ठा wakelock *wl)
अणु
	list_add(&wl->lru, &wakelocks_lru_list);
पूर्ण

अटल अंतरभूत व्योम wakelocks_lru_most_recent(काष्ठा wakelock *wl)
अणु
	list_move(&wl->lru, &wakelocks_lru_list);
पूर्ण

अटल व्योम __wakelocks_gc(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wakelock *wl, *aux;
	kसमय_प्रकार now;

	mutex_lock(&wakelocks_lock);

	now = kसमय_get();
	list_क्रम_each_entry_safe_reverse(wl, aux, &wakelocks_lru_list, lru) अणु
		u64 idle_समय_ns;
		bool active;

		spin_lock_irq(&wl->ws->lock);
		idle_समय_ns = kसमय_प्रकारo_ns(kसमय_sub(now, wl->ws->last_समय));
		active = wl->ws->active;
		spin_unlock_irq(&wl->ws->lock);

		अगर (idle_समय_ns < ((u64)WL_GC_TIME_SEC * NSEC_PER_SEC))
			अवरोध;

		अगर (!active) अणु
			wakeup_source_unरेजिस्टर(wl->ws);
			rb_erase(&wl->node, &wakelocks_tree);
			list_del(&wl->lru);
			kमुक्त(wl->name);
			kमुक्त(wl);
			decrement_wakelocks_number();
		पूर्ण
	पूर्ण
	wakelocks_gc_count = 0;

	mutex_unlock(&wakelocks_lock);
पूर्ण

अटल व्योम wakelocks_gc(व्योम)
अणु
	अगर (++wakelocks_gc_count <= WL_GC_COUNT_MAX)
		वापस;

	schedule_work(&wakelock_work);
पूर्ण
#अन्यथा /* !CONFIG_PM_WAKELOCKS_GC */
अटल अंतरभूत व्योम wakelocks_lru_add(काष्ठा wakelock *wl) अणुपूर्ण
अटल अंतरभूत व्योम wakelocks_lru_most_recent(काष्ठा wakelock *wl) अणुपूर्ण
अटल अंतरभूत व्योम wakelocks_gc(व्योम) अणुपूर्ण
#पूर्ण_अगर /* !CONFIG_PM_WAKELOCKS_GC */

अटल काष्ठा wakelock *wakelock_lookup_add(स्थिर अक्षर *name, माप_प्रकार len,
					    bool add_अगर_not_found)
अणु
	काष्ठा rb_node **node = &wakelocks_tree.rb_node;
	काष्ठा rb_node *parent = *node;
	काष्ठा wakelock *wl;

	जबतक (*node) अणु
		पूर्णांक dअगरf;

		parent = *node;
		wl = rb_entry(*node, काष्ठा wakelock, node);
		dअगरf = म_भेदन(name, wl->name, len);
		अगर (dअगरf == 0) अणु
			अगर (wl->name[len])
				dअगरf = -1;
			अन्यथा
				वापस wl;
		पूर्ण
		अगर (dअगरf < 0)
			node = &(*node)->rb_left;
		अन्यथा
			node = &(*node)->rb_right;
	पूर्ण
	अगर (!add_अगर_not_found)
		वापस ERR_PTR(-EINVAL);

	अगर (wakelocks_limit_exceeded())
		वापस ERR_PTR(-ENOSPC);

	/* Not found, we have to add a new one. */
	wl = kzalloc(माप(*wl), GFP_KERNEL);
	अगर (!wl)
		वापस ERR_PTR(-ENOMEM);

	wl->name = kstrndup(name, len, GFP_KERNEL);
	अगर (!wl->name) अणु
		kमुक्त(wl);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	wl->ws = wakeup_source_रेजिस्टर(शून्य, wl->name);
	अगर (!wl->ws) अणु
		kमुक्त(wl->name);
		kमुक्त(wl);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	wl->ws->last_समय = kसमय_get();

	rb_link_node(&wl->node, parent, node);
	rb_insert_color(&wl->node, &wakelocks_tree);
	wakelocks_lru_add(wl);
	increment_wakelocks_number();
	वापस wl;
पूर्ण

पूर्णांक pm_wake_lock(स्थिर अक्षर *buf)
अणु
	स्थिर अक्षर *str = buf;
	काष्ठा wakelock *wl;
	u64 समयout_ns = 0;
	माप_प्रकार len;
	पूर्णांक ret = 0;

	अगर (!capable(CAP_BLOCK_SUSPEND))
		वापस -EPERM;

	जबतक (*str && !है_खाली(*str))
		str++;

	len = str - buf;
	अगर (!len)
		वापस -EINVAL;

	अगर (*str && *str != '\n') अणु
		/* Find out अगर there's a valid समयout string appended. */
		ret = kstrtou64(skip_spaces(str), 10, &समयout_ns);
		अगर (ret)
			वापस -EINVAL;
	पूर्ण

	mutex_lock(&wakelocks_lock);

	wl = wakelock_lookup_add(buf, len, true);
	अगर (IS_ERR(wl)) अणु
		ret = PTR_ERR(wl);
		जाओ out;
	पूर्ण
	अगर (समयout_ns) अणु
		u64 समयout_ms = समयout_ns + NSEC_PER_MSEC - 1;

		करो_भाग(समयout_ms, NSEC_PER_MSEC);
		__pm_wakeup_event(wl->ws, समयout_ms);
	पूर्ण अन्यथा अणु
		__pm_stay_awake(wl->ws);
	पूर्ण

	wakelocks_lru_most_recent(wl);

 out:
	mutex_unlock(&wakelocks_lock);
	वापस ret;
पूर्ण

पूर्णांक pm_wake_unlock(स्थिर अक्षर *buf)
अणु
	काष्ठा wakelock *wl;
	माप_प्रकार len;
	पूर्णांक ret = 0;

	अगर (!capable(CAP_BLOCK_SUSPEND))
		वापस -EPERM;

	len = म_माप(buf);
	अगर (!len)
		वापस -EINVAL;

	अगर (buf[len-1] == '\n')
		len--;

	अगर (!len)
		वापस -EINVAL;

	mutex_lock(&wakelocks_lock);

	wl = wakelock_lookup_add(buf, len, false);
	अगर (IS_ERR(wl)) अणु
		ret = PTR_ERR(wl);
		जाओ out;
	पूर्ण
	__pm_relax(wl->ws);

	wakelocks_lru_most_recent(wl);
	wakelocks_gc();

 out:
	mutex_unlock(&wakelocks_lock);
	वापस ret;
पूर्ण
