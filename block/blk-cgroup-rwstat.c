<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Legacy blkg rwstat helpers enabled by CONFIG_BLK_CGROUP_RWSTAT.
 * Do not use in new code.
 */
#समावेश "blk-cgroup-rwstat.h"

पूर्णांक blkg_rwstat_init(काष्ठा blkg_rwstat *rwstat, gfp_t gfp)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < BLKG_RWSTAT_NR; i++) अणु
		ret = percpu_counter_init(&rwstat->cpu_cnt[i], 0, gfp);
		अगर (ret) अणु
			जबतक (--i >= 0)
				percpu_counter_destroy(&rwstat->cpu_cnt[i]);
			वापस ret;
		पूर्ण
		atomic64_set(&rwstat->aux_cnt[i], 0);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(blkg_rwstat_init);

व्योम blkg_rwstat_निकास(काष्ठा blkg_rwstat *rwstat)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BLKG_RWSTAT_NR; i++)
		percpu_counter_destroy(&rwstat->cpu_cnt[i]);
पूर्ण
EXPORT_SYMBOL_GPL(blkg_rwstat_निकास);

/**
 * __blkg_prfill_rwstat - prfill helper क्रम a blkg_rwstat
 * @sf: seq_file to prपूर्णांक to
 * @pd: policy निजी data of पूर्णांकerest
 * @rwstat: rwstat to prपूर्णांक
 *
 * Prपूर्णांक @rwstat to @sf क्रम the device assocaited with @pd.
 */
u64 __blkg_prfill_rwstat(काष्ठा seq_file *sf, काष्ठा blkg_policy_data *pd,
			 स्थिर काष्ठा blkg_rwstat_sample *rwstat)
अणु
	अटल स्थिर अक्षर *rwstr[] = अणु
		[BLKG_RWSTAT_READ]	= "Read",
		[BLKG_RWSTAT_WRITE]	= "Write",
		[BLKG_RWSTAT_SYNC]	= "Sync",
		[BLKG_RWSTAT_ASYNC]	= "Async",
		[BLKG_RWSTAT_DISCARD]	= "Discard",
	पूर्ण;
	स्थिर अक्षर *dname = blkg_dev_name(pd->blkg);
	u64 v;
	पूर्णांक i;

	अगर (!dname)
		वापस 0;

	क्रम (i = 0; i < BLKG_RWSTAT_NR; i++)
		seq_म_लिखो(sf, "%s %s %llu\n", dname, rwstr[i],
			   rwstat->cnt[i]);

	v = rwstat->cnt[BLKG_RWSTAT_READ] +
		rwstat->cnt[BLKG_RWSTAT_WRITE] +
		rwstat->cnt[BLKG_RWSTAT_DISCARD];
	seq_म_लिखो(sf, "%s Total %llu\n", dname, v);
	वापस v;
पूर्ण
EXPORT_SYMBOL_GPL(__blkg_prfill_rwstat);

/**
 * blkg_prfill_rwstat - prfill callback क्रम blkg_rwstat
 * @sf: seq_file to prपूर्णांक to
 * @pd: policy निजी data of पूर्णांकerest
 * @off: offset to the blkg_rwstat in @pd
 *
 * prfill callback क्रम prपूर्णांकing a blkg_rwstat.
 */
u64 blkg_prfill_rwstat(काष्ठा seq_file *sf, काष्ठा blkg_policy_data *pd,
		       पूर्णांक off)
अणु
	काष्ठा blkg_rwstat_sample rwstat = अणु पूर्ण;

	blkg_rwstat_पढ़ो((व्योम *)pd + off, &rwstat);
	वापस __blkg_prfill_rwstat(sf, pd, &rwstat);
पूर्ण
EXPORT_SYMBOL_GPL(blkg_prfill_rwstat);

/**
 * blkg_rwstat_recursive_sum - collect hierarchical blkg_rwstat
 * @blkg: blkg of पूर्णांकerest
 * @pol: blkcg_policy which contains the blkg_rwstat
 * @off: offset to the blkg_rwstat in blkg_policy_data or @blkg
 * @sum: blkg_rwstat_sample काष्ठाure containing the results
 *
 * Collect the blkg_rwstat specअगरied by @blkg, @pol and @off and all its
 * online descendants and their aux counts.  The caller must be holding the
 * queue lock क्रम online tests.
 *
 * If @pol is शून्य, blkg_rwstat is at @off bytes पूर्णांकo @blkg; otherwise, it
 * is at @off bytes पूर्णांकo @blkg's blkg_policy_data of the policy.
 */
व्योम blkg_rwstat_recursive_sum(काष्ठा blkcg_gq *blkg, काष्ठा blkcg_policy *pol,
		पूर्णांक off, काष्ठा blkg_rwstat_sample *sum)
अणु
	काष्ठा blkcg_gq *pos_blkg;
	काष्ठा cgroup_subsys_state *pos_css;
	अचिन्हित पूर्णांक i;

	lockdep_निश्चित_held(&blkg->q->queue_lock);

	स_रखो(sum, 0, माप(*sum));
	rcu_पढ़ो_lock();
	blkg_क्रम_each_descendant_pre(pos_blkg, pos_css, blkg) अणु
		काष्ठा blkg_rwstat *rwstat;

		अगर (!pos_blkg->online)
			जारी;

		अगर (pol)
			rwstat = (व्योम *)blkg_to_pd(pos_blkg, pol) + off;
		अन्यथा
			rwstat = (व्योम *)pos_blkg + off;

		क्रम (i = 0; i < BLKG_RWSTAT_NR; i++)
			sum->cnt[i] += blkg_rwstat_पढ़ो_counter(rwstat, i);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(blkg_rwstat_recursive_sum);
