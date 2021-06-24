<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Legacy blkg rwstat helpers enabled by CONFIG_BLK_CGROUP_RWSTAT.
 * Do not use in new code.
 */
#अगर_अघोषित _BLK_CGROUP_RWSTAT_H
#घोषणा _BLK_CGROUP_RWSTAT_H

#समावेश <linux/blk-cgroup.h>

क्रमागत blkg_rwstat_type अणु
	BLKG_RWSTAT_READ,
	BLKG_RWSTAT_WRITE,
	BLKG_RWSTAT_SYNC,
	BLKG_RWSTAT_ASYNC,
	BLKG_RWSTAT_DISCARD,

	BLKG_RWSTAT_NR,
	BLKG_RWSTAT_TOTAL = BLKG_RWSTAT_NR,
पूर्ण;

/*
 * blkg_[rw]stat->aux_cnt is excluded क्रम local stats but included क्रम
 * recursive.  Used to carry stats of dead children.
 */
काष्ठा blkg_rwstat अणु
	काष्ठा percpu_counter		cpu_cnt[BLKG_RWSTAT_NR];
	atomic64_t			aux_cnt[BLKG_RWSTAT_NR];
पूर्ण;

काष्ठा blkg_rwstat_sample अणु
	u64				cnt[BLKG_RWSTAT_NR];
पूर्ण;

अटल अंतरभूत u64 blkg_rwstat_पढ़ो_counter(काष्ठा blkg_rwstat *rwstat,
		अचिन्हित पूर्णांक idx)
अणु
	वापस atomic64_पढ़ो(&rwstat->aux_cnt[idx]) +
		percpu_counter_sum_positive(&rwstat->cpu_cnt[idx]);
पूर्ण

पूर्णांक blkg_rwstat_init(काष्ठा blkg_rwstat *rwstat, gfp_t gfp);
व्योम blkg_rwstat_निकास(काष्ठा blkg_rwstat *rwstat);
u64 __blkg_prfill_rwstat(काष्ठा seq_file *sf, काष्ठा blkg_policy_data *pd,
			 स्थिर काष्ठा blkg_rwstat_sample *rwstat);
u64 blkg_prfill_rwstat(काष्ठा seq_file *sf, काष्ठा blkg_policy_data *pd,
		       पूर्णांक off);
व्योम blkg_rwstat_recursive_sum(काष्ठा blkcg_gq *blkg, काष्ठा blkcg_policy *pol,
		पूर्णांक off, काष्ठा blkg_rwstat_sample *sum);


/**
 * blkg_rwstat_add - add a value to a blkg_rwstat
 * @rwstat: target blkg_rwstat
 * @op: REQ_OP and flags
 * @val: value to add
 *
 * Add @val to @rwstat.  The counters are chosen according to @rw.  The
 * caller is responsible क्रम synchronizing calls to this function.
 */
अटल अंतरभूत व्योम blkg_rwstat_add(काष्ठा blkg_rwstat *rwstat,
				   अचिन्हित पूर्णांक op, uपूर्णांक64_t val)
अणु
	काष्ठा percpu_counter *cnt;

	अगर (op_is_discard(op))
		cnt = &rwstat->cpu_cnt[BLKG_RWSTAT_DISCARD];
	अन्यथा अगर (op_is_ग_लिखो(op))
		cnt = &rwstat->cpu_cnt[BLKG_RWSTAT_WRITE];
	अन्यथा
		cnt = &rwstat->cpu_cnt[BLKG_RWSTAT_READ];

	percpu_counter_add_batch(cnt, val, BLKG_STAT_CPU_BATCH);

	अगर (op_is_sync(op))
		cnt = &rwstat->cpu_cnt[BLKG_RWSTAT_SYNC];
	अन्यथा
		cnt = &rwstat->cpu_cnt[BLKG_RWSTAT_ASYNC];

	percpu_counter_add_batch(cnt, val, BLKG_STAT_CPU_BATCH);
पूर्ण

/**
 * blkg_rwstat_पढ़ो - पढ़ो the current values of a blkg_rwstat
 * @rwstat: blkg_rwstat to पढ़ो
 *
 * Read the current snapshot of @rwstat and वापस it in the aux counts.
 */
अटल अंतरभूत व्योम blkg_rwstat_पढ़ो(काष्ठा blkg_rwstat *rwstat,
		काष्ठा blkg_rwstat_sample *result)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BLKG_RWSTAT_NR; i++)
		result->cnt[i] =
			percpu_counter_sum_positive(&rwstat->cpu_cnt[i]);
पूर्ण

/**
 * blkg_rwstat_total - पढ़ो the total count of a blkg_rwstat
 * @rwstat: blkg_rwstat to पढ़ो
 *
 * Return the total count of @rwstat regardless of the IO direction.  This
 * function can be called without synchronization and takes care of u64
 * atomicity.
 */
अटल अंतरभूत uपूर्णांक64_t blkg_rwstat_total(काष्ठा blkg_rwstat *rwstat)
अणु
	काष्ठा blkg_rwstat_sample पंचांगp = अणु पूर्ण;

	blkg_rwstat_पढ़ो(rwstat, &पंचांगp);
	वापस पंचांगp.cnt[BLKG_RWSTAT_READ] + पंचांगp.cnt[BLKG_RWSTAT_WRITE];
पूर्ण

/**
 * blkg_rwstat_reset - reset a blkg_rwstat
 * @rwstat: blkg_rwstat to reset
 */
अटल अंतरभूत व्योम blkg_rwstat_reset(काष्ठा blkg_rwstat *rwstat)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BLKG_RWSTAT_NR; i++) अणु
		percpu_counter_set(&rwstat->cpu_cnt[i], 0);
		atomic64_set(&rwstat->aux_cnt[i], 0);
	पूर्ण
पूर्ण

/**
 * blkg_rwstat_add_aux - add a blkg_rwstat पूर्णांकo another's aux count
 * @to: the destination blkg_rwstat
 * @from: the source
 *
 * Add @from's count including the aux one to @to's aux count.
 */
अटल अंतरभूत व्योम blkg_rwstat_add_aux(काष्ठा blkg_rwstat *to,
				       काष्ठा blkg_rwstat *from)
अणु
	u64 sum[BLKG_RWSTAT_NR];
	पूर्णांक i;

	क्रम (i = 0; i < BLKG_RWSTAT_NR; i++)
		sum[i] = percpu_counter_sum_positive(&from->cpu_cnt[i]);

	क्रम (i = 0; i < BLKG_RWSTAT_NR; i++)
		atomic64_add(sum[i] + atomic64_पढ़ो(&from->aux_cnt[i]),
			     &to->aux_cnt[i]);
पूर्ण
#पूर्ण_अगर	/* _BLK_CGROUP_RWSTAT_H */
