<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2004 Evgeniy Polyakov <zbr@ioremap.net>
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>

#समावेश "w1_internal.h"

DEFINE_SPINLOCK(w1_flock);
अटल LIST_HEAD(w1_families);

/**
 * w1_रेजिस्टर_family() - रेजिस्टर a device family driver
 * @newf:	family to रेजिस्टर
 */
पूर्णांक w1_रेजिस्टर_family(काष्ठा w1_family *newf)
अणु
	काष्ठा list_head *ent, *n;
	काष्ठा w1_family *f;
	पूर्णांक ret = 0;

	spin_lock(&w1_flock);
	list_क्रम_each_safe(ent, n, &w1_families) अणु
		f = list_entry(ent, काष्ठा w1_family, family_entry);

		अगर (f->fid == newf->fid) अणु
			ret = -EEXIST;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!ret) अणु
		atomic_set(&newf->refcnt, 0);
		list_add_tail(&newf->family_entry, &w1_families);
	पूर्ण
	spin_unlock(&w1_flock);

	/* check शेष devices against the new set of drivers */
	w1_reconnect_slaves(newf, 1);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(w1_रेजिस्टर_family);

/**
 * w1_unरेजिस्टर_family() - unरेजिस्टर a device family driver
 * @fent:	family to unरेजिस्टर
 */
व्योम w1_unरेजिस्टर_family(काष्ठा w1_family *fent)
अणु
	काष्ठा list_head *ent, *n;
	काष्ठा w1_family *f;

	spin_lock(&w1_flock);
	list_क्रम_each_safe(ent, n, &w1_families) अणु
		f = list_entry(ent, काष्ठा w1_family, family_entry);

		अगर (f->fid == fent->fid) अणु
			list_del(&fent->family_entry);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&w1_flock);

	/* deatch devices using this family code */
	w1_reconnect_slaves(fent, 0);

	जबतक (atomic_पढ़ो(&fent->refcnt)) अणु
		pr_info("Waiting for family %u to become free: refcnt=%d.\n",
				fent->fid, atomic_पढ़ो(&fent->refcnt));

		अगर (msleep_पूर्णांकerruptible(1000))
			flush_संकेतs(current);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(w1_unरेजिस्टर_family);

/*
 * Should be called under w1_flock held.
 */
काष्ठा w1_family * w1_family_रेजिस्टरed(u8 fid)
अणु
	काष्ठा list_head *ent, *n;
	काष्ठा w1_family *f = शून्य;
	पूर्णांक ret = 0;

	list_क्रम_each_safe(ent, n, &w1_families) अणु
		f = list_entry(ent, काष्ठा w1_family, family_entry);

		अगर (f->fid == fid) अणु
			ret = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस (ret) ? f : शून्य;
पूर्ण

अटल व्योम __w1_family_put(काष्ठा w1_family *f)
अणु
	atomic_dec(&f->refcnt);
पूर्ण

व्योम w1_family_put(काष्ठा w1_family *f)
अणु
	spin_lock(&w1_flock);
	__w1_family_put(f);
	spin_unlock(&w1_flock);
पूर्ण

#अगर 0
व्योम w1_family_get(काष्ठा w1_family *f)
अणु
	spin_lock(&w1_flock);
	__w1_family_get(f);
	spin_unlock(&w1_flock);
पूर्ण
#पूर्ण_अगर  /*  0  */

व्योम __w1_family_get(काष्ठा w1_family *f)
अणु
	smp_mb__beक्रमe_atomic();
	atomic_inc(&f->refcnt);
	smp_mb__after_atomic();
पूर्ण
