<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PERCPU_COUNTER_H
#घोषणा _LINUX_PERCPU_COUNTER_H
/*
 * A simple "approximate counter" क्रम use in ext2 and ext3 superblocks.
 *
 * WARNING: these things are HUGE.  4 kbytes per counter on 32-way P4.
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/smp.h>
#समावेश <linux/list.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/percpu.h>
#समावेश <linux/types.h>
#समावेश <linux/gfp.h>

#अगर_घोषित CONFIG_SMP

काष्ठा percpu_counter अणु
	raw_spinlock_t lock;
	s64 count;
#अगर_घोषित CONFIG_HOTPLUG_CPU
	काष्ठा list_head list;	/* All percpu_counters are on a list */
#पूर्ण_अगर
	s32 __percpu *counters;
पूर्ण;

बाह्य पूर्णांक percpu_counter_batch;

पूर्णांक __percpu_counter_init(काष्ठा percpu_counter *fbc, s64 amount, gfp_t gfp,
			  काष्ठा lock_class_key *key);

#घोषणा percpu_counter_init(fbc, value, gfp)				\
	(अणु								\
		अटल काष्ठा lock_class_key __key;			\
									\
		__percpu_counter_init(fbc, value, gfp, &__key);		\
	पूर्ण)

व्योम percpu_counter_destroy(काष्ठा percpu_counter *fbc);
व्योम percpu_counter_set(काष्ठा percpu_counter *fbc, s64 amount);
व्योम percpu_counter_add_batch(काष्ठा percpu_counter *fbc, s64 amount,
			      s32 batch);
s64 __percpu_counter_sum(काष्ठा percpu_counter *fbc);
पूर्णांक __percpu_counter_compare(काष्ठा percpu_counter *fbc, s64 rhs, s32 batch);
व्योम percpu_counter_sync(काष्ठा percpu_counter *fbc);

अटल अंतरभूत पूर्णांक percpu_counter_compare(काष्ठा percpu_counter *fbc, s64 rhs)
अणु
	वापस __percpu_counter_compare(fbc, rhs, percpu_counter_batch);
पूर्ण

अटल अंतरभूत व्योम percpu_counter_add(काष्ठा percpu_counter *fbc, s64 amount)
अणु
	percpu_counter_add_batch(fbc, amount, percpu_counter_batch);
पूर्ण

अटल अंतरभूत s64 percpu_counter_sum_positive(काष्ठा percpu_counter *fbc)
अणु
	s64 ret = __percpu_counter_sum(fbc);
	वापस ret < 0 ? 0 : ret;
पूर्ण

अटल अंतरभूत s64 percpu_counter_sum(काष्ठा percpu_counter *fbc)
अणु
	वापस __percpu_counter_sum(fbc);
पूर्ण

अटल अंतरभूत s64 percpu_counter_पढ़ो(काष्ठा percpu_counter *fbc)
अणु
	वापस fbc->count;
पूर्ण

/*
 * It is possible क्रम the percpu_counter_पढ़ो() to वापस a small negative
 * number क्रम some counter which should never be negative.
 *
 */
अटल अंतरभूत s64 percpu_counter_पढ़ो_positive(काष्ठा percpu_counter *fbc)
अणु
	/* Prevent reloads of fbc->count */
	s64 ret = READ_ONCE(fbc->count);

	अगर (ret >= 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल अंतरभूत bool percpu_counter_initialized(काष्ठा percpu_counter *fbc)
अणु
	वापस (fbc->counters != शून्य);
पूर्ण

#अन्यथा /* !CONFIG_SMP */

काष्ठा percpu_counter अणु
	s64 count;
पूर्ण;

अटल अंतरभूत पूर्णांक percpu_counter_init(काष्ठा percpu_counter *fbc, s64 amount,
				      gfp_t gfp)
अणु
	fbc->count = amount;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम percpu_counter_destroy(काष्ठा percpu_counter *fbc)
अणु
पूर्ण

अटल अंतरभूत व्योम percpu_counter_set(काष्ठा percpu_counter *fbc, s64 amount)
अणु
	fbc->count = amount;
पूर्ण

अटल अंतरभूत पूर्णांक percpu_counter_compare(काष्ठा percpu_counter *fbc, s64 rhs)
अणु
	अगर (fbc->count > rhs)
		वापस 1;
	अन्यथा अगर (fbc->count < rhs)
		वापस -1;
	अन्यथा
		वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
__percpu_counter_compare(काष्ठा percpu_counter *fbc, s64 rhs, s32 batch)
अणु
	वापस percpu_counter_compare(fbc, rhs);
पूर्ण

अटल अंतरभूत व्योम
percpu_counter_add(काष्ठा percpu_counter *fbc, s64 amount)
अणु
	preempt_disable();
	fbc->count += amount;
	preempt_enable();
पूर्ण

अटल अंतरभूत व्योम
percpu_counter_add_batch(काष्ठा percpu_counter *fbc, s64 amount, s32 batch)
अणु
	percpu_counter_add(fbc, amount);
पूर्ण

अटल अंतरभूत s64 percpu_counter_पढ़ो(काष्ठा percpu_counter *fbc)
अणु
	वापस fbc->count;
पूर्ण

/*
 * percpu_counter is पूर्णांकended to track positive numbers. In the UP हाल the
 * number should never be negative.
 */
अटल अंतरभूत s64 percpu_counter_पढ़ो_positive(काष्ठा percpu_counter *fbc)
अणु
	वापस fbc->count;
पूर्ण

अटल अंतरभूत s64 percpu_counter_sum_positive(काष्ठा percpu_counter *fbc)
अणु
	वापस percpu_counter_पढ़ो_positive(fbc);
पूर्ण

अटल अंतरभूत s64 percpu_counter_sum(काष्ठा percpu_counter *fbc)
अणु
	वापस percpu_counter_पढ़ो(fbc);
पूर्ण

अटल अंतरभूत bool percpu_counter_initialized(काष्ठा percpu_counter *fbc)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत व्योम percpu_counter_sync(काष्ठा percpu_counter *fbc)
अणु
पूर्ण
#पूर्ण_अगर	/* CONFIG_SMP */

अटल अंतरभूत व्योम percpu_counter_inc(काष्ठा percpu_counter *fbc)
अणु
	percpu_counter_add(fbc, 1);
पूर्ण

अटल अंतरभूत व्योम percpu_counter_dec(काष्ठा percpu_counter *fbc)
अणु
	percpu_counter_add(fbc, -1);
पूर्ण

अटल अंतरभूत व्योम percpu_counter_sub(काष्ठा percpu_counter *fbc, s64 amount)
अणु
	percpu_counter_add(fbc, -amount);
पूर्ण

#पूर्ण_अगर /* _LINUX_PERCPU_COUNTER_H */
