<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/fs.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/export.h>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र/debug.h>

अटल पूर्णांक ss_get(व्योम *data, u64 *val)
अणु
	kसमय_प्रकार start, finish;
	पूर्णांक loops;
	पूर्णांक cont;
	DEFINE_RAW_SPINLOCK(ss_spin);

	loops = 1000000;
	cont = 1;

	start = kसमय_get();

	जबतक (cont) अणु
		raw_spin_lock(&ss_spin);
		loops--;
		अगर (loops == 0)
			cont = 0;
		raw_spin_unlock(&ss_spin);
	पूर्ण

	finish = kसमय_get();

	*val = kसमय_us_delta(finish, start);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_ss, ss_get, शून्य, "%llu\n");



काष्ठा spin_multi_state अणु
	raw_spinlock_t lock;
	atomic_t start_रुको;
	atomic_t enter_रुको;
	atomic_t निकास_रुको;
	पूर्णांक loops;
पूर्ण;

काष्ठा spin_multi_per_thपढ़ो अणु
	काष्ठा spin_multi_state *state;
	kसमय_प्रकार start;
पूर्ण;

अटल पूर्णांक multi_other(व्योम *data)
अणु
	पूर्णांक loops;
	पूर्णांक cont;
	काष्ठा spin_multi_per_thपढ़ो *pt = data;
	काष्ठा spin_multi_state *s = pt->state;

	loops = s->loops;
	cont = 1;

	atomic_dec(&s->enter_रुको);

	जबतक (atomic_पढ़ो(&s->enter_रुको))
		; /* spin */

	pt->start = kसमय_get();

	atomic_dec(&s->start_रुको);

	जबतक (atomic_पढ़ो(&s->start_रुको))
		; /* spin */

	जबतक (cont) अणु
		raw_spin_lock(&s->lock);
		loops--;
		अगर (loops == 0)
			cont = 0;
		raw_spin_unlock(&s->lock);
	पूर्ण

	atomic_dec(&s->निकास_रुको);
	जबतक (atomic_पढ़ो(&s->निकास_रुको))
		; /* spin */
	वापस 0;
पूर्ण

अटल पूर्णांक multi_get(व्योम *data, u64 *val)
अणु
	kसमय_प्रकार finish;
	काष्ठा spin_multi_state ms;
	काष्ठा spin_multi_per_thपढ़ो t1, t2;

	ms.lock = __RAW_SPIN_LOCK_UNLOCKED("multi_get");
	ms.loops = 1000000;

	atomic_set(&ms.start_रुको, 2);
	atomic_set(&ms.enter_रुको, 2);
	atomic_set(&ms.निकास_रुको, 2);
	t1.state = &ms;
	t2.state = &ms;

	kthपढ़ो_run(multi_other, &t2, "multi_get");

	multi_other(&t1);

	finish = kसमय_get();

	*val = kसमय_us_delta(finish, t1.start);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_multi, multi_get, शून्य, "%llu\n");

अटल पूर्णांक __init spinlock_test(व्योम)
अणु
	debugfs_create_file_unsafe("spin_single", S_IRUGO, mips_debugfs_dir, शून्य,
			    &fops_ss);
	debugfs_create_file_unsafe("spin_multi", S_IRUGO, mips_debugfs_dir, शून्य,
			    &fops_multi);
	वापस 0;
पूर्ण
device_initcall(spinlock_test);
