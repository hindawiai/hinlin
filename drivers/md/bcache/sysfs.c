<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * bcache sysfs पूर्णांकerfaces
 *
 * Copyright 2010, 2011 Kent Overstreet <kent.overstreet@gmail.com>
 * Copyright 2012 Google, Inc.
 */

#समावेश "bcache.h"
#समावेश "sysfs.h"
#समावेश "btree.h"
#समावेश "request.h"
#समावेश "writeback.h"
#समावेश "features.h"

#समावेश <linux/blkdev.h>
#समावेश <linux/sort.h>
#समावेश <linux/sched/घड़ी.h>

बाह्य bool bcache_is_reboot;

/* Default is 0 ("writethrough") */
अटल स्थिर अक्षर * स्थिर bch_cache_modes[] = अणु
	"writethrough",
	"writeback",
	"writearound",
	"none",
	शून्य
पूर्ण;

अटल स्थिर अक्षर * स्थिर bch_पढ़ोa_cache_policies[] = अणु
	"all",
	"meta-only",
	शून्य
पूर्ण;

/* Default is 0 ("auto") */
अटल स्थिर अक्षर * स्थिर bch_stop_on_failure_modes[] = अणु
	"auto",
	"always",
	शून्य
पूर्ण;

अटल स्थिर अक्षर * स्थिर cache_replacement_policies[] = अणु
	"lru",
	"fifo",
	"random",
	शून्य
पूर्ण;

अटल स्थिर अक्षर * स्थिर error_actions[] = अणु
	"unregister",
	"panic",
	शून्य
पूर्ण;

ग_लिखो_attribute(attach);
ग_लिखो_attribute(detach);
ग_लिखो_attribute(unरेजिस्टर);
ग_लिखो_attribute(stop);
ग_लिखो_attribute(clear_stats);
ग_लिखो_attribute(trigger_gc);
ग_लिखो_attribute(prune_cache);
ग_लिखो_attribute(flash_vol_create);

पढ़ो_attribute(bucket_size);
पढ़ो_attribute(block_size);
पढ़ो_attribute(nbuckets);
पढ़ो_attribute(tree_depth);
पढ़ो_attribute(root_usage_percent);
पढ़ो_attribute(priority_stats);
पढ़ो_attribute(btree_cache_size);
पढ़ो_attribute(btree_cache_max_chain);
पढ़ो_attribute(cache_available_percent);
पढ़ो_attribute(written);
पढ़ो_attribute(btree_written);
पढ़ो_attribute(metadata_written);
पढ़ो_attribute(active_journal_entries);
पढ़ो_attribute(backing_dev_name);
पढ़ो_attribute(backing_dev_uuid);

sysfs_समय_stats_attribute(btree_gc,	sec, ms);
sysfs_समय_stats_attribute(btree_split, sec, us);
sysfs_समय_stats_attribute(btree_sort,	ms,  us);
sysfs_समय_stats_attribute(btree_पढ़ो,	ms,  us);

पढ़ो_attribute(btree_nodes);
पढ़ो_attribute(btree_used_percent);
पढ़ो_attribute(average_key_size);
पढ़ो_attribute(dirty_data);
पढ़ो_attribute(bset_tree_stats);
पढ़ो_attribute(feature_compat);
पढ़ो_attribute(feature_ro_compat);
पढ़ो_attribute(feature_incompat);

पढ़ो_attribute(state);
पढ़ो_attribute(cache_पढ़ो_races);
पढ़ो_attribute(reclaim);
पढ़ो_attribute(reclaimed_journal_buckets);
पढ़ो_attribute(flush_ग_लिखो);
पढ़ो_attribute(ग_लिखोback_keys_करोne);
पढ़ो_attribute(ग_लिखोback_keys_failed);
पढ़ो_attribute(io_errors);
पढ़ो_attribute(congested);
पढ़ो_attribute(cutoff_ग_लिखोback);
पढ़ो_attribute(cutoff_ग_लिखोback_sync);
rw_attribute(congested_पढ़ो_threshold_us);
rw_attribute(congested_ग_लिखो_threshold_us);

rw_attribute(sequential_cutoff);
rw_attribute(data_csum);
rw_attribute(cache_mode);
rw_attribute(पढ़ोahead_cache_policy);
rw_attribute(stop_when_cache_set_failed);
rw_attribute(ग_लिखोback_metadata);
rw_attribute(ग_लिखोback_running);
rw_attribute(ग_लिखोback_percent);
rw_attribute(ग_लिखोback_delay);
rw_attribute(ग_लिखोback_rate);
rw_attribute(ग_लिखोback_consider_fragment);

rw_attribute(ग_लिखोback_rate_update_seconds);
rw_attribute(ग_लिखोback_rate_i_term_inverse);
rw_attribute(ग_लिखोback_rate_p_term_inverse);
rw_attribute(ग_लिखोback_rate_fp_term_low);
rw_attribute(ग_लिखोback_rate_fp_term_mid);
rw_attribute(ग_लिखोback_rate_fp_term_high);
rw_attribute(ग_लिखोback_rate_minimum);
पढ़ो_attribute(ग_लिखोback_rate_debug);

पढ़ो_attribute(stripe_size);
पढ़ो_attribute(partial_stripes_expensive);

rw_attribute(synchronous);
rw_attribute(journal_delay_ms);
rw_attribute(io_disable);
rw_attribute(discard);
rw_attribute(running);
rw_attribute(label);
rw_attribute(errors);
rw_attribute(io_error_limit);
rw_attribute(io_error_halflअगरe);
rw_attribute(verअगरy);
rw_attribute(bypass_torture_test);
rw_attribute(key_merging_disabled);
rw_attribute(gc_always_reग_लिखो);
rw_attribute(expensive_debug_checks);
rw_attribute(cache_replacement_policy);
rw_attribute(btree_shrinker_disabled);
rw_attribute(copy_gc_enabled);
rw_attribute(idle_max_ग_लिखोback_rate);
rw_attribute(gc_after_ग_लिखोback);
rw_attribute(size);

अटल sमाप_प्रकार bch_snprपूर्णांक_string_list(अक्षर *buf,
				       माप_प्रकार size,
				       स्थिर अक्षर * स्थिर list[],
				       माप_प्रकार selected)
अणु
	अक्षर *out = buf;
	माप_प्रकार i;

	क्रम (i = 0; list[i]; i++)
		out += scnम_लिखो(out, buf + size - out,
				i == selected ? "[%s] " : "%s ", list[i]);

	out[-1] = '\n';
	वापस out - buf;
पूर्ण

SHOW(__bch_cached_dev)
अणु
	काष्ठा cached_dev *dc = container_of(kobj, काष्ठा cached_dev,
					     disk.kobj);
	अक्षर स्थिर *states[] = अणु "no cache", "clean", "dirty", "inconsistent" पूर्ण;
	पूर्णांक wb = dc->ग_लिखोback_running;

#घोषणा var(stat)		(dc->stat)

	अगर (attr == &sysfs_cache_mode)
		वापस bch_snprपूर्णांक_string_list(buf, PAGE_SIZE,
					       bch_cache_modes,
					       BDEV_CACHE_MODE(&dc->sb));

	अगर (attr == &sysfs_पढ़ोahead_cache_policy)
		वापस bch_snprपूर्णांक_string_list(buf, PAGE_SIZE,
					      bch_पढ़ोa_cache_policies,
					      dc->cache_पढ़ोahead_policy);

	अगर (attr == &sysfs_stop_when_cache_set_failed)
		वापस bch_snprपूर्णांक_string_list(buf, PAGE_SIZE,
					       bch_stop_on_failure_modes,
					       dc->stop_when_cache_set_failed);


	sysfs_म_लिखो(data_csum,		"%i", dc->disk.data_csum);
	var_म_लिखो(verअगरy,		"%i");
	var_म_लिखो(bypass_torture_test,	"%i");
	var_म_लिखो(ग_लिखोback_metadata,	"%i");
	var_म_लिखो(ग_लिखोback_running,	"%i");
	var_म_लिखो(ग_लिखोback_consider_fragment,	"%i");
	var_prपूर्णांक(ग_लिखोback_delay);
	var_prपूर्णांक(ग_लिखोback_percent);
	sysfs_hprपूर्णांक(ग_लिखोback_rate,
		     wb ? atomic_दीर्घ_पढ़ो(&dc->ग_लिखोback_rate.rate) << 9 : 0);
	sysfs_म_लिखो(io_errors,		"%i", atomic_पढ़ो(&dc->io_errors));
	sysfs_म_लिखो(io_error_limit,	"%i", dc->error_limit);
	sysfs_म_लिखो(io_disable,	"%i", dc->io_disable);
	var_prपूर्णांक(ग_लिखोback_rate_update_seconds);
	var_prपूर्णांक(ग_लिखोback_rate_i_term_inverse);
	var_prपूर्णांक(ग_लिखोback_rate_p_term_inverse);
	var_prपूर्णांक(ग_लिखोback_rate_fp_term_low);
	var_prपूर्णांक(ग_लिखोback_rate_fp_term_mid);
	var_prपूर्णांक(ग_लिखोback_rate_fp_term_high);
	var_prपूर्णांक(ग_लिखोback_rate_minimum);

	अगर (attr == &sysfs_ग_लिखोback_rate_debug) अणु
		अक्षर rate[20];
		अक्षर dirty[20];
		अक्षर target[20];
		अक्षर proportional[20];
		अक्षर पूर्णांकegral[20];
		अक्षर change[20];
		s64 next_io;

		/*
		 * Except क्रम dirty and target, other values should
		 * be 0 अगर ग_लिखोback is not running.
		 */
		bch_hprपूर्णांक(rate,
			   wb ? atomic_दीर्घ_पढ़ो(&dc->ग_लिखोback_rate.rate) << 9
			      : 0);
		bch_hprपूर्णांक(dirty, bcache_dev_sectors_dirty(&dc->disk) << 9);
		bch_hprपूर्णांक(target, dc->ग_लिखोback_rate_target << 9);
		bch_hprपूर्णांक(proportional,
			   wb ? dc->ग_लिखोback_rate_proportional << 9 : 0);
		bch_hprपूर्णांक(पूर्णांकegral,
			   wb ? dc->ग_लिखोback_rate_पूर्णांकegral_scaled << 9 : 0);
		bch_hprपूर्णांक(change, wb ? dc->ग_लिखोback_rate_change << 9 : 0);
		next_io = wb ? भाग64_s64(dc->ग_लिखोback_rate.next-local_घड़ी(),
					 NSEC_PER_MSEC) : 0;

		वापस प्र_लिखो(buf,
			       "rate:\t\t%s/sec\n"
			       "dirty:\t\t%s\n"
			       "target:\t\t%s\n"
			       "proportional:\t%s\n"
			       "integral:\t%s\n"
			       "change:\t\t%s/sec\n"
			       "next io:\t%llims\n",
			       rate, dirty, target, proportional,
			       पूर्णांकegral, change, next_io);
	पूर्ण

	sysfs_hprपूर्णांक(dirty_data,
		     bcache_dev_sectors_dirty(&dc->disk) << 9);

	sysfs_hprपूर्णांक(stripe_size,	 ((uपूर्णांक64_t)dc->disk.stripe_size) << 9);
	var_म_लिखो(partial_stripes_expensive,	"%u");

	var_hprपूर्णांक(sequential_cutoff);

	sysfs_prपूर्णांक(running,		atomic_पढ़ो(&dc->running));
	sysfs_prपूर्णांक(state,		states[BDEV_STATE(&dc->sb)]);

	अगर (attr == &sysfs_label) अणु
		स_नकल(buf, dc->sb.label, SB_LABEL_SIZE);
		buf[SB_LABEL_SIZE + 1] = '\0';
		म_जोड़ो(buf, "\n");
		वापस म_माप(buf);
	पूर्ण

	अगर (attr == &sysfs_backing_dev_name) अणु
		snम_लिखो(buf, BDEVNAME_SIZE + 1, "%s", dc->backing_dev_name);
		म_जोड़ो(buf, "\n");
		वापस म_माप(buf);
	पूर्ण

	अगर (attr == &sysfs_backing_dev_uuid) अणु
		/* convert binary uuid पूर्णांकo 36-byte string plus '\0' */
		snम_लिखो(buf, 36+1, "%pU", dc->sb.uuid);
		म_जोड़ो(buf, "\n");
		वापस म_माप(buf);
	पूर्ण

#अघोषित var
	वापस 0;
पूर्ण
SHOW_LOCKED(bch_cached_dev)

STORE(__cached_dev)
अणु
	काष्ठा cached_dev *dc = container_of(kobj, काष्ठा cached_dev,
					     disk.kobj);
	sमाप_प्रकार v;
	काष्ठा cache_set *c;
	काष्ठा kobj_uevent_env *env;

	/* no user space access अगर प्रणाली is rebooting */
	अगर (bcache_is_reboot)
		वापस -EBUSY;

#घोषणा d_म_से_अदीर्घ(var)		sysfs_म_से_अदीर्घ(var, dc->var)
#घोषणा d_म_से_अदीर्घ_nonzero(var)	sysfs_म_से_अदीर्घ_clamp(var, dc->var, 1, पूर्णांक_उच्च)
#घोषणा d_strtoi_h(var)		sysfs_hम_से_प(var, dc->var)

	sysfs_म_से_अदीर्घ(data_csum,	dc->disk.data_csum);
	d_म_से_अदीर्घ(verअगरy);
	sysfs_म_से_अदीर्घ_bool(bypass_torture_test, dc->bypass_torture_test);
	sysfs_म_से_अदीर्घ_bool(ग_लिखोback_metadata, dc->ग_लिखोback_metadata);
	sysfs_म_से_अदीर्घ_bool(ग_लिखोback_running, dc->ग_लिखोback_running);
	sysfs_म_से_अदीर्घ_bool(ग_लिखोback_consider_fragment, dc->ग_लिखोback_consider_fragment);
	sysfs_म_से_अदीर्घ_clamp(ग_लिखोback_delay, dc->ग_लिखोback_delay, 0, अच_पूर्णांक_उच्च);

	sysfs_म_से_अदीर्घ_clamp(ग_लिखोback_percent, dc->ग_लिखोback_percent,
			    0, bch_cutoff_ग_लिखोback);

	अगर (attr == &sysfs_ग_लिखोback_rate) अणु
		sमाप_प्रकार ret;
		दीर्घ पूर्णांक v = atomic_दीर्घ_पढ़ो(&dc->ग_लिखोback_rate.rate);

		ret = म_से_अदीर्घ_safe_clamp(buf, v, 1, पूर्णांक_उच्च);

		अगर (!ret) अणु
			atomic_दीर्घ_set(&dc->ग_लिखोback_rate.rate, v);
			ret = size;
		पूर्ण

		वापस ret;
	पूर्ण

	sysfs_म_से_अदीर्घ_clamp(ग_लिखोback_rate_update_seconds,
			    dc->ग_लिखोback_rate_update_seconds,
			    1, WRITEBACK_RATE_UPDATE_SECS_MAX);
	sysfs_म_से_अदीर्घ_clamp(ग_लिखोback_rate_i_term_inverse,
			    dc->ग_लिखोback_rate_i_term_inverse,
			    1, अच_पूर्णांक_उच्च);
	sysfs_म_से_अदीर्घ_clamp(ग_लिखोback_rate_p_term_inverse,
			    dc->ग_लिखोback_rate_p_term_inverse,
			    1, अच_पूर्णांक_उच्च);
	sysfs_म_से_अदीर्घ_clamp(ग_लिखोback_rate_fp_term_low,
			    dc->ग_लिखोback_rate_fp_term_low,
			    1, dc->ग_लिखोback_rate_fp_term_mid - 1);
	sysfs_म_से_अदीर्घ_clamp(ग_लिखोback_rate_fp_term_mid,
			    dc->ग_लिखोback_rate_fp_term_mid,
			    dc->ग_लिखोback_rate_fp_term_low + 1,
			    dc->ग_लिखोback_rate_fp_term_high - 1);
	sysfs_म_से_अदीर्घ_clamp(ग_लिखोback_rate_fp_term_high,
			    dc->ग_लिखोback_rate_fp_term_high,
			    dc->ग_लिखोback_rate_fp_term_mid + 1, अच_पूर्णांक_उच्च);
	sysfs_म_से_अदीर्घ_clamp(ग_लिखोback_rate_minimum,
			    dc->ग_लिखोback_rate_minimum,
			    1, अच_पूर्णांक_उच्च);

	sysfs_म_से_अदीर्घ_clamp(io_error_limit, dc->error_limit, 0, पूर्णांक_उच्च);

	अगर (attr == &sysfs_io_disable) अणु
		पूर्णांक v = म_से_अदीर्घ_or_वापस(buf);

		dc->io_disable = v ? 1 : 0;
	पूर्ण

	sysfs_म_से_अदीर्घ_clamp(sequential_cutoff,
			    dc->sequential_cutoff,
			    0, अच_पूर्णांक_उच्च);

	अगर (attr == &sysfs_clear_stats)
		bch_cache_accounting_clear(&dc->accounting);

	अगर (attr == &sysfs_running &&
	    म_से_अदीर्घ_or_वापस(buf)) अणु
		v = bch_cached_dev_run(dc);
		अगर (v)
			वापस v;
	पूर्ण

	अगर (attr == &sysfs_cache_mode) अणु
		v = __sysfs_match_string(bch_cache_modes, -1, buf);
		अगर (v < 0)
			वापस v;

		अगर ((अचिन्हित पूर्णांक) v != BDEV_CACHE_MODE(&dc->sb)) अणु
			SET_BDEV_CACHE_MODE(&dc->sb, v);
			bch_ग_लिखो_bdev_super(dc, शून्य);
		पूर्ण
	पूर्ण

	अगर (attr == &sysfs_पढ़ोahead_cache_policy) अणु
		v = __sysfs_match_string(bch_पढ़ोa_cache_policies, -1, buf);
		अगर (v < 0)
			वापस v;

		अगर ((अचिन्हित पूर्णांक) v != dc->cache_पढ़ोahead_policy)
			dc->cache_पढ़ोahead_policy = v;
	पूर्ण

	अगर (attr == &sysfs_stop_when_cache_set_failed) अणु
		v = __sysfs_match_string(bch_stop_on_failure_modes, -1, buf);
		अगर (v < 0)
			वापस v;

		dc->stop_when_cache_set_failed = v;
	पूर्ण

	अगर (attr == &sysfs_label) अणु
		अगर (size > SB_LABEL_SIZE)
			वापस -EINVAL;
		स_नकल(dc->sb.label, buf, size);
		अगर (size < SB_LABEL_SIZE)
			dc->sb.label[size] = '\0';
		अगर (size && dc->sb.label[size - 1] == '\n')
			dc->sb.label[size - 1] = '\0';
		bch_ग_लिखो_bdev_super(dc, शून्य);
		अगर (dc->disk.c) अणु
			स_नकल(dc->disk.c->uuids[dc->disk.id].label,
			       buf, SB_LABEL_SIZE);
			bch_uuid_ग_लिखो(dc->disk.c);
		पूर्ण
		env = kzalloc(माप(काष्ठा kobj_uevent_env), GFP_KERNEL);
		अगर (!env)
			वापस -ENOMEM;
		add_uevent_var(env, "DRIVER=bcache");
		add_uevent_var(env, "CACHED_UUID=%pU", dc->sb.uuid);
		add_uevent_var(env, "CACHED_LABEL=%s", buf);
		kobject_uevent_env(&disk_to_dev(dc->disk.disk)->kobj,
				   KOBJ_CHANGE,
				   env->envp);
		kमुक्त(env);
	पूर्ण

	अगर (attr == &sysfs_attach) अणु
		uपूर्णांक8_t		set_uuid[16];

		अगर (bch_parse_uuid(buf, set_uuid) < 16)
			वापस -EINVAL;

		v = -ENOENT;
		list_क्रम_each_entry(c, &bch_cache_sets, list) अणु
			v = bch_cached_dev_attach(dc, c, set_uuid);
			अगर (!v)
				वापस size;
		पूर्ण
		अगर (v == -ENOENT)
			pr_err("Can't attach %s: cache set not found\n", buf);
		वापस v;
	पूर्ण

	अगर (attr == &sysfs_detach && dc->disk.c)
		bch_cached_dev_detach(dc);

	अगर (attr == &sysfs_stop)
		bcache_device_stop(&dc->disk);

	वापस size;
पूर्ण

STORE(bch_cached_dev)
अणु
	काष्ठा cached_dev *dc = container_of(kobj, काष्ठा cached_dev,
					     disk.kobj);

	/* no user space access अगर प्रणाली is rebooting */
	अगर (bcache_is_reboot)
		वापस -EBUSY;

	mutex_lock(&bch_रेजिस्टर_lock);
	size = __cached_dev_store(kobj, attr, buf, size);

	अगर (attr == &sysfs_ग_लिखोback_running) अणु
		/* dc->ग_लिखोback_running changed in __cached_dev_store() */
		अगर (IS_ERR_OR_शून्य(dc->ग_लिखोback_thपढ़ो)) अणु
			/*
			 * reject setting it to 1 via sysfs अगर ग_लिखोback
			 * kthपढ़ो is not created yet.
			 */
			अगर (dc->ग_लिखोback_running) अणु
				dc->ग_लिखोback_running = false;
				pr_err("%s: failed to run non-existent writeback thread\n",
						dc->disk.disk->disk_name);
			पूर्ण
		पूर्ण अन्यथा
			/*
			 * ग_लिखोback kthपढ़ो will check अगर dc->ग_लिखोback_running
			 * is true or false.
			 */
			bch_ग_लिखोback_queue(dc);
	पूर्ण

	/*
	 * Only set BCACHE_DEV_WB_RUNNING when cached device attached to
	 * a cache set, otherwise it करोesn't make sense.
	 */
	अगर (attr == &sysfs_ग_लिखोback_percent)
		अगर ((dc->disk.c != शून्य) &&
		    (!test_and_set_bit(BCACHE_DEV_WB_RUNNING, &dc->disk.flags)))
			schedule_delayed_work(&dc->ग_लिखोback_rate_update,
				      dc->ग_लिखोback_rate_update_seconds * HZ);

	mutex_unlock(&bch_रेजिस्टर_lock);
	वापस size;
पूर्ण

अटल काष्ठा attribute *bch_cached_dev_files[] = अणु
	&sysfs_attach,
	&sysfs_detach,
	&sysfs_stop,
#अगर 0
	&sysfs_data_csum,
#पूर्ण_अगर
	&sysfs_cache_mode,
	&sysfs_पढ़ोahead_cache_policy,
	&sysfs_stop_when_cache_set_failed,
	&sysfs_ग_लिखोback_metadata,
	&sysfs_ग_लिखोback_running,
	&sysfs_ग_लिखोback_delay,
	&sysfs_ग_लिखोback_percent,
	&sysfs_ग_लिखोback_rate,
	&sysfs_ग_लिखोback_consider_fragment,
	&sysfs_ग_लिखोback_rate_update_seconds,
	&sysfs_ग_लिखोback_rate_i_term_inverse,
	&sysfs_ग_लिखोback_rate_p_term_inverse,
	&sysfs_ग_लिखोback_rate_fp_term_low,
	&sysfs_ग_लिखोback_rate_fp_term_mid,
	&sysfs_ग_लिखोback_rate_fp_term_high,
	&sysfs_ग_लिखोback_rate_minimum,
	&sysfs_ग_लिखोback_rate_debug,
	&sysfs_io_errors,
	&sysfs_io_error_limit,
	&sysfs_io_disable,
	&sysfs_dirty_data,
	&sysfs_stripe_size,
	&sysfs_partial_stripes_expensive,
	&sysfs_sequential_cutoff,
	&sysfs_clear_stats,
	&sysfs_running,
	&sysfs_state,
	&sysfs_label,
#अगर_घोषित CONFIG_BCACHE_DEBUG
	&sysfs_verअगरy,
	&sysfs_bypass_torture_test,
#पूर्ण_अगर
	&sysfs_backing_dev_name,
	&sysfs_backing_dev_uuid,
	शून्य
पूर्ण;
KTYPE(bch_cached_dev);

SHOW(bch_flash_dev)
अणु
	काष्ठा bcache_device *d = container_of(kobj, काष्ठा bcache_device,
					       kobj);
	काष्ठा uuid_entry *u = &d->c->uuids[d->id];

	sysfs_म_लिखो(data_csum,	"%i", d->data_csum);
	sysfs_hprपूर्णांक(size,	u->sectors << 9);

	अगर (attr == &sysfs_label) अणु
		स_नकल(buf, u->label, SB_LABEL_SIZE);
		buf[SB_LABEL_SIZE + 1] = '\0';
		म_जोड़ो(buf, "\n");
		वापस म_माप(buf);
	पूर्ण

	वापस 0;
पूर्ण

STORE(__bch_flash_dev)
अणु
	काष्ठा bcache_device *d = container_of(kobj, काष्ठा bcache_device,
					       kobj);
	काष्ठा uuid_entry *u = &d->c->uuids[d->id];

	/* no user space access अगर प्रणाली is rebooting */
	अगर (bcache_is_reboot)
		वापस -EBUSY;

	sysfs_म_से_अदीर्घ(data_csum,	d->data_csum);

	अगर (attr == &sysfs_size) अणु
		uपूर्णांक64_t v;

		strtoi_h_or_वापस(buf, v);

		u->sectors = v >> 9;
		bch_uuid_ग_लिखो(d->c);
		set_capacity(d->disk, u->sectors);
	पूर्ण

	अगर (attr == &sysfs_label) अणु
		स_नकल(u->label, buf, SB_LABEL_SIZE);
		bch_uuid_ग_लिखो(d->c);
	पूर्ण

	अगर (attr == &sysfs_unरेजिस्टर) अणु
		set_bit(BCACHE_DEV_DETACHING, &d->flags);
		bcache_device_stop(d);
	पूर्ण

	वापस size;
पूर्ण
STORE_LOCKED(bch_flash_dev)

अटल काष्ठा attribute *bch_flash_dev_files[] = अणु
	&sysfs_unरेजिस्टर,
#अगर 0
	&sysfs_data_csum,
#पूर्ण_अगर
	&sysfs_label,
	&sysfs_size,
	शून्य
पूर्ण;
KTYPE(bch_flash_dev);

काष्ठा bset_stats_op अणु
	काष्ठा btree_op op;
	माप_प्रकार nodes;
	काष्ठा bset_stats stats;
पूर्ण;

अटल पूर्णांक bch_btree_bset_stats(काष्ठा btree_op *b_op, काष्ठा btree *b)
अणु
	काष्ठा bset_stats_op *op = container_of(b_op, काष्ठा bset_stats_op, op);

	op->nodes++;
	bch_btree_keys_stats(&b->keys, &op->stats);

	वापस MAP_CONTINUE;
पूर्ण

अटल पूर्णांक bch_bset_prपूर्णांक_stats(काष्ठा cache_set *c, अक्षर *buf)
अणु
	काष्ठा bset_stats_op op;
	पूर्णांक ret;

	स_रखो(&op, 0, माप(op));
	bch_btree_op_init(&op.op, -1);

	ret = bch_btree_map_nodes(&op.op, c, &ZERO_KEY, bch_btree_bset_stats);
	अगर (ret < 0)
		वापस ret;

	वापस snम_लिखो(buf, PAGE_SIZE,
			"btree nodes:		%zu\n"
			"written sets:		%zu\n"
			"unwritten sets:		%zu\n"
			"written key bytes:	%zu\n"
			"unwritten key bytes:	%zu\n"
			"floats:			%zu\n"
			"failed:			%zu\n",
			op.nodes,
			op.stats.sets_written, op.stats.sets_unwritten,
			op.stats.bytes_written, op.stats.bytes_unwritten,
			op.stats.भग्नs, op.stats.failed);
पूर्ण

अटल अचिन्हित पूर्णांक bch_root_usage(काष्ठा cache_set *c)
अणु
	अचिन्हित पूर्णांक bytes = 0;
	काष्ठा bkey *k;
	काष्ठा btree *b;
	काष्ठा btree_iter iter;

	जाओ lock_root;

	करो अणु
		rw_unlock(false, b);
lock_root:
		b = c->root;
		rw_lock(false, b, b->level);
	पूर्ण जबतक (b != c->root);

	क्रम_each_key_filter(&b->keys, k, &iter, bch_ptr_bad)
		bytes += bkey_bytes(k);

	rw_unlock(false, b);

	वापस (bytes * 100) / btree_bytes(c);
पूर्ण

अटल माप_प्रकार bch_cache_size(काष्ठा cache_set *c)
अणु
	माप_प्रकार ret = 0;
	काष्ठा btree *b;

	mutex_lock(&c->bucket_lock);
	list_क्रम_each_entry(b, &c->btree_cache, list)
		ret += 1 << (b->keys.page_order + PAGE_SHIFT);

	mutex_unlock(&c->bucket_lock);
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक bch_cache_max_chain(काष्ठा cache_set *c)
अणु
	अचिन्हित पूर्णांक ret = 0;
	काष्ठा hlist_head *h;

	mutex_lock(&c->bucket_lock);

	क्रम (h = c->bucket_hash;
	     h < c->bucket_hash + (1 << BUCKET_HASH_BITS);
	     h++) अणु
		अचिन्हित पूर्णांक i = 0;
		काष्ठा hlist_node *p;

		hlist_क्रम_each(p, h)
			i++;

		ret = max(ret, i);
	पूर्ण

	mutex_unlock(&c->bucket_lock);
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक bch_btree_used(काष्ठा cache_set *c)
अणु
	वापस भाग64_u64(c->gc_stats.key_bytes * 100,
			 (c->gc_stats.nodes ?: 1) * btree_bytes(c));
पूर्ण

अटल अचिन्हित पूर्णांक bch_average_key_size(काष्ठा cache_set *c)
अणु
	वापस c->gc_stats.nkeys
		? भाग64_u64(c->gc_stats.data, c->gc_stats.nkeys)
		: 0;
पूर्ण

SHOW(__bch_cache_set)
अणु
	काष्ठा cache_set *c = container_of(kobj, काष्ठा cache_set, kobj);

	sysfs_prपूर्णांक(synchronous,		CACHE_SYNC(&c->cache->sb));
	sysfs_prपूर्णांक(journal_delay_ms,		c->journal_delay_ms);
	sysfs_hprपूर्णांक(bucket_size,		bucket_bytes(c->cache));
	sysfs_hprपूर्णांक(block_size,		block_bytes(c->cache));
	sysfs_prपूर्णांक(tree_depth,			c->root->level);
	sysfs_prपूर्णांक(root_usage_percent,		bch_root_usage(c));

	sysfs_hprपूर्णांक(btree_cache_size,		bch_cache_size(c));
	sysfs_prपूर्णांक(btree_cache_max_chain,	bch_cache_max_chain(c));
	sysfs_prपूर्णांक(cache_available_percent,	100 - c->gc_stats.in_use);

	sysfs_prपूर्णांक_समय_stats(&c->btree_gc_समय,	btree_gc, sec, ms);
	sysfs_prपूर्णांक_समय_stats(&c->btree_split_समय,	btree_split, sec, us);
	sysfs_prपूर्णांक_समय_stats(&c->sort.समय,		btree_sort, ms, us);
	sysfs_prपूर्णांक_समय_stats(&c->btree_पढ़ो_समय,	btree_पढ़ो, ms, us);

	sysfs_prपूर्णांक(btree_used_percent,	bch_btree_used(c));
	sysfs_prपूर्णांक(btree_nodes,	c->gc_stats.nodes);
	sysfs_hprपूर्णांक(average_key_size,	bch_average_key_size(c));

	sysfs_prपूर्णांक(cache_पढ़ो_races,
		    atomic_दीर्घ_पढ़ो(&c->cache_पढ़ो_races));

	sysfs_prपूर्णांक(reclaim,
		    atomic_दीर्घ_पढ़ो(&c->reclaim));

	sysfs_prपूर्णांक(reclaimed_journal_buckets,
		    atomic_दीर्घ_पढ़ो(&c->reclaimed_journal_buckets));

	sysfs_prपूर्णांक(flush_ग_लिखो,
		    atomic_दीर्घ_पढ़ो(&c->flush_ग_लिखो));

	sysfs_prपूर्णांक(ग_लिखोback_keys_करोne,
		    atomic_दीर्घ_पढ़ो(&c->ग_लिखोback_keys_करोne));
	sysfs_prपूर्णांक(ग_लिखोback_keys_failed,
		    atomic_दीर्घ_पढ़ो(&c->ग_लिखोback_keys_failed));

	अगर (attr == &sysfs_errors)
		वापस bch_snprपूर्णांक_string_list(buf, PAGE_SIZE, error_actions,
					       c->on_error);

	/* See count_io_errors क्रम why 88 */
	sysfs_prपूर्णांक(io_error_halflअगरe,	c->error_decay * 88);
	sysfs_prपूर्णांक(io_error_limit,	c->error_limit);

	sysfs_hprपूर्णांक(congested,
		     ((uपूर्णांक64_t) bch_get_congested(c)) << 9);
	sysfs_prपूर्णांक(congested_पढ़ो_threshold_us,
		    c->congested_पढ़ो_threshold_us);
	sysfs_prपूर्णांक(congested_ग_लिखो_threshold_us,
		    c->congested_ग_लिखो_threshold_us);

	sysfs_prपूर्णांक(cutoff_ग_लिखोback, bch_cutoff_ग_लिखोback);
	sysfs_prपूर्णांक(cutoff_ग_लिखोback_sync, bch_cutoff_ग_लिखोback_sync);

	sysfs_prपूर्णांक(active_journal_entries,	fअगरo_used(&c->journal.pin));
	sysfs_म_लिखो(verअगरy,			"%i", c->verअगरy);
	sysfs_म_लिखो(key_merging_disabled,	"%i", c->key_merging_disabled);
	sysfs_म_लिखो(expensive_debug_checks,
		     "%i", c->expensive_debug_checks);
	sysfs_म_लिखो(gc_always_reग_लिखो,		"%i", c->gc_always_reग_लिखो);
	sysfs_म_लिखो(btree_shrinker_disabled,	"%i", c->shrinker_disabled);
	sysfs_म_लिखो(copy_gc_enabled,		"%i", c->copy_gc_enabled);
	sysfs_म_लिखो(idle_max_ग_लिखोback_rate,	"%i",
		     c->idle_max_ग_लिखोback_rate_enabled);
	sysfs_म_लिखो(gc_after_ग_लिखोback,	"%i", c->gc_after_ग_लिखोback);
	sysfs_म_लिखो(io_disable,		"%i",
		     test_bit(CACHE_SET_IO_DISABLE, &c->flags));

	अगर (attr == &sysfs_bset_tree_stats)
		वापस bch_bset_prपूर्णांक_stats(c, buf);

	अगर (attr == &sysfs_feature_compat)
		वापस bch_prपूर्णांक_cache_set_feature_compat(c, buf, PAGE_SIZE);
	अगर (attr == &sysfs_feature_ro_compat)
		वापस bch_prपूर्णांक_cache_set_feature_ro_compat(c, buf, PAGE_SIZE);
	अगर (attr == &sysfs_feature_incompat)
		वापस bch_prपूर्णांक_cache_set_feature_incompat(c, buf, PAGE_SIZE);

	वापस 0;
पूर्ण
SHOW_LOCKED(bch_cache_set)

STORE(__bch_cache_set)
अणु
	काष्ठा cache_set *c = container_of(kobj, काष्ठा cache_set, kobj);
	sमाप_प्रकार v;

	/* no user space access अगर प्रणाली is rebooting */
	अगर (bcache_is_reboot)
		वापस -EBUSY;

	अगर (attr == &sysfs_unरेजिस्टर)
		bch_cache_set_unरेजिस्टर(c);

	अगर (attr == &sysfs_stop)
		bch_cache_set_stop(c);

	अगर (attr == &sysfs_synchronous) अणु
		bool sync = म_से_अदीर्घ_or_वापस(buf);

		अगर (sync != CACHE_SYNC(&c->cache->sb)) अणु
			SET_CACHE_SYNC(&c->cache->sb, sync);
			bcache_ग_लिखो_super(c);
		पूर्ण
	पूर्ण

	अगर (attr == &sysfs_flash_vol_create) अणु
		पूर्णांक r;
		uपूर्णांक64_t v;

		strtoi_h_or_वापस(buf, v);

		r = bch_flash_dev_create(c, v);
		अगर (r)
			वापस r;
	पूर्ण

	अगर (attr == &sysfs_clear_stats) अणु
		atomic_दीर्घ_set(&c->ग_लिखोback_keys_करोne,	0);
		atomic_दीर्घ_set(&c->ग_लिखोback_keys_failed,	0);

		स_रखो(&c->gc_stats, 0, माप(काष्ठा gc_stat));
		bch_cache_accounting_clear(&c->accounting);
	पूर्ण

	अगर (attr == &sysfs_trigger_gc)
		क्रमce_wake_up_gc(c);

	अगर (attr == &sysfs_prune_cache) अणु
		काष्ठा shrink_control sc;

		sc.gfp_mask = GFP_KERNEL;
		sc.nr_to_scan = म_से_अदीर्घ_or_वापस(buf);
		c->shrink.scan_objects(&c->shrink, &sc);
	पूर्ण

	sysfs_म_से_अदीर्घ_clamp(congested_पढ़ो_threshold_us,
			    c->congested_पढ़ो_threshold_us,
			    0, अच_पूर्णांक_उच्च);
	sysfs_म_से_अदीर्घ_clamp(congested_ग_लिखो_threshold_us,
			    c->congested_ग_लिखो_threshold_us,
			    0, अच_पूर्णांक_उच्च);

	अगर (attr == &sysfs_errors) अणु
		v = __sysfs_match_string(error_actions, -1, buf);
		अगर (v < 0)
			वापस v;

		c->on_error = v;
	पूर्ण

	sysfs_म_से_अदीर्घ_clamp(io_error_limit, c->error_limit, 0, अच_पूर्णांक_उच्च);

	/* See count_io_errors() क्रम why 88 */
	अगर (attr == &sysfs_io_error_halflअगरe) अणु
		अचिन्हित दीर्घ v = 0;
		sमाप_प्रकार ret;

		ret = म_से_अदीर्घ_safe_clamp(buf, v, 0, अच_पूर्णांक_उच्च);
		अगर (!ret) अणु
			c->error_decay = v / 88;
			वापस size;
		पूर्ण
		वापस ret;
	पूर्ण

	अगर (attr == &sysfs_io_disable) अणु
		v = म_से_अदीर्घ_or_वापस(buf);
		अगर (v) अणु
			अगर (test_and_set_bit(CACHE_SET_IO_DISABLE,
					     &c->flags))
				pr_warn("CACHE_SET_IO_DISABLE already set\n");
		पूर्ण अन्यथा अणु
			अगर (!test_and_clear_bit(CACHE_SET_IO_DISABLE,
						&c->flags))
				pr_warn("CACHE_SET_IO_DISABLE already cleared\n");
		पूर्ण
	पूर्ण

	sysfs_म_से_अदीर्घ_clamp(journal_delay_ms,
			    c->journal_delay_ms,
			    0, अच_लघु_उच्च);
	sysfs_म_से_अदीर्घ_bool(verअगरy,		c->verअगरy);
	sysfs_म_से_अदीर्घ_bool(key_merging_disabled, c->key_merging_disabled);
	sysfs_म_से_अदीर्घ(expensive_debug_checks,	c->expensive_debug_checks);
	sysfs_म_से_अदीर्घ_bool(gc_always_reग_लिखो,	c->gc_always_reग_लिखो);
	sysfs_म_से_अदीर्घ_bool(btree_shrinker_disabled, c->shrinker_disabled);
	sysfs_म_से_अदीर्घ_bool(copy_gc_enabled,	c->copy_gc_enabled);
	sysfs_म_से_अदीर्घ_bool(idle_max_ग_लिखोback_rate,
			   c->idle_max_ग_लिखोback_rate_enabled);

	/*
	 * ग_लिखो gc_after_ग_लिखोback here may overग_लिखो an alपढ़ोy set
	 * BCH_DO_AUTO_GC, it करोesn't matter because this flag will be
	 * set in next chance.
	 */
	sysfs_म_से_अदीर्घ_clamp(gc_after_ग_लिखोback, c->gc_after_ग_लिखोback, 0, 1);

	वापस size;
पूर्ण
STORE_LOCKED(bch_cache_set)

SHOW(bch_cache_set_पूर्णांकernal)
अणु
	काष्ठा cache_set *c = container_of(kobj, काष्ठा cache_set, पूर्णांकernal);

	वापस bch_cache_set_show(&c->kobj, attr, buf);
पूर्ण

STORE(bch_cache_set_पूर्णांकernal)
अणु
	काष्ठा cache_set *c = container_of(kobj, काष्ठा cache_set, पूर्णांकernal);

	/* no user space access अगर प्रणाली is rebooting */
	अगर (bcache_is_reboot)
		वापस -EBUSY;

	वापस bch_cache_set_store(&c->kobj, attr, buf, size);
पूर्ण

अटल व्योम bch_cache_set_पूर्णांकernal_release(काष्ठा kobject *k)
अणु
पूर्ण

अटल काष्ठा attribute *bch_cache_set_files[] = अणु
	&sysfs_unरेजिस्टर,
	&sysfs_stop,
	&sysfs_synchronous,
	&sysfs_journal_delay_ms,
	&sysfs_flash_vol_create,

	&sysfs_bucket_size,
	&sysfs_block_size,
	&sysfs_tree_depth,
	&sysfs_root_usage_percent,
	&sysfs_btree_cache_size,
	&sysfs_cache_available_percent,

	&sysfs_average_key_size,

	&sysfs_errors,
	&sysfs_io_error_limit,
	&sysfs_io_error_halflअगरe,
	&sysfs_congested,
	&sysfs_congested_पढ़ो_threshold_us,
	&sysfs_congested_ग_लिखो_threshold_us,
	&sysfs_clear_stats,
	शून्य
पूर्ण;
KTYPE(bch_cache_set);

अटल काष्ठा attribute *bch_cache_set_पूर्णांकernal_files[] = अणु
	&sysfs_active_journal_entries,

	sysfs_समय_stats_attribute_list(btree_gc, sec, ms)
	sysfs_समय_stats_attribute_list(btree_split, sec, us)
	sysfs_समय_stats_attribute_list(btree_sort, ms, us)
	sysfs_समय_stats_attribute_list(btree_पढ़ो, ms, us)

	&sysfs_btree_nodes,
	&sysfs_btree_used_percent,
	&sysfs_btree_cache_max_chain,

	&sysfs_bset_tree_stats,
	&sysfs_cache_पढ़ो_races,
	&sysfs_reclaim,
	&sysfs_reclaimed_journal_buckets,
	&sysfs_flush_ग_लिखो,
	&sysfs_ग_लिखोback_keys_करोne,
	&sysfs_ग_लिखोback_keys_failed,

	&sysfs_trigger_gc,
	&sysfs_prune_cache,
#अगर_घोषित CONFIG_BCACHE_DEBUG
	&sysfs_verअगरy,
	&sysfs_key_merging_disabled,
	&sysfs_expensive_debug_checks,
#पूर्ण_अगर
	&sysfs_gc_always_reग_लिखो,
	&sysfs_btree_shrinker_disabled,
	&sysfs_copy_gc_enabled,
	&sysfs_idle_max_ग_लिखोback_rate,
	&sysfs_gc_after_ग_लिखोback,
	&sysfs_io_disable,
	&sysfs_cutoff_ग_लिखोback,
	&sysfs_cutoff_ग_लिखोback_sync,
	&sysfs_feature_compat,
	&sysfs_feature_ro_compat,
	&sysfs_feature_incompat,
	शून्य
पूर्ण;
KTYPE(bch_cache_set_पूर्णांकernal);

अटल पूर्णांक __bch_cache_cmp(स्थिर व्योम *l, स्थिर व्योम *r)
अणु
	cond_resched();
	वापस *((uपूर्णांक16_t *)r) - *((uपूर्णांक16_t *)l);
पूर्ण

SHOW(__bch_cache)
अणु
	काष्ठा cache *ca = container_of(kobj, काष्ठा cache, kobj);

	sysfs_hprपूर्णांक(bucket_size,	bucket_bytes(ca));
	sysfs_hprपूर्णांक(block_size,	block_bytes(ca));
	sysfs_prपूर्णांक(nbuckets,		ca->sb.nbuckets);
	sysfs_prपूर्णांक(discard,		ca->discard);
	sysfs_hprपूर्णांक(written, atomic_दीर्घ_पढ़ो(&ca->sectors_written) << 9);
	sysfs_hprपूर्णांक(btree_written,
		     atomic_दीर्घ_पढ़ो(&ca->btree_sectors_written) << 9);
	sysfs_hprपूर्णांक(metadata_written,
		     (atomic_दीर्घ_पढ़ो(&ca->meta_sectors_written) +
		      atomic_दीर्घ_पढ़ो(&ca->btree_sectors_written)) << 9);

	sysfs_prपूर्णांक(io_errors,
		    atomic_पढ़ो(&ca->io_errors) >> IO_ERROR_SHIFT);

	अगर (attr == &sysfs_cache_replacement_policy)
		वापस bch_snprपूर्णांक_string_list(buf, PAGE_SIZE,
					       cache_replacement_policies,
					       CACHE_REPLACEMENT(&ca->sb));

	अगर (attr == &sysfs_priority_stats) अणु
		काष्ठा bucket *b;
		माप_प्रकार n = ca->sb.nbuckets, i;
		माप_प्रकार unused = 0, available = 0, dirty = 0, meta = 0;
		uपूर्णांक64_t sum = 0;
		/* Compute 31 quantiles */
		uपूर्णांक16_t q[31], *p, *cached;
		sमाप_प्रकार ret;

		cached = p = vदो_स्मृति(array_size(माप(uपूर्णांक16_t),
						ca->sb.nbuckets));
		अगर (!p)
			वापस -ENOMEM;

		mutex_lock(&ca->set->bucket_lock);
		क्रम_each_bucket(b, ca) अणु
			अगर (!GC_SECTORS_USED(b))
				unused++;
			अगर (GC_MARK(b) == GC_MARK_RECLAIMABLE)
				available++;
			अगर (GC_MARK(b) == GC_MARK_सूचीTY)
				dirty++;
			अगर (GC_MARK(b) == GC_MARK_METADATA)
				meta++;
		पूर्ण

		क्रम (i = ca->sb.first_bucket; i < n; i++)
			p[i] = ca->buckets[i].prio;
		mutex_unlock(&ca->set->bucket_lock);

		sort(p, n, माप(uपूर्णांक16_t), __bch_cache_cmp, शून्य);

		जबतक (n &&
		       !cached[n - 1])
			--n;

		जबतक (cached < p + n &&
		       *cached == BTREE_PRIO) अणु
			cached++;
			n--;
		पूर्ण

		क्रम (i = 0; i < n; i++)
			sum += INITIAL_PRIO - cached[i];

		अगर (n)
			करो_भाग(sum, n);

		क्रम (i = 0; i < ARRAY_SIZE(q); i++)
			q[i] = INITIAL_PRIO - cached[n * (i + 1) /
				(ARRAY_SIZE(q) + 1)];

		vमुक्त(p);

		ret = scnम_लिखो(buf, PAGE_SIZE,
				"Unused:		%zu%%\n"
				"Clean:		%zu%%\n"
				"Dirty:		%zu%%\n"
				"Metadata:	%zu%%\n"
				"Average:	%llu\n"
				"Sectors per Q:	%zu\n"
				"Quantiles:	[",
				unused * 100 / (माप_प्रकार) ca->sb.nbuckets,
				available * 100 / (माप_प्रकार) ca->sb.nbuckets,
				dirty * 100 / (माप_प्रकार) ca->sb.nbuckets,
				meta * 100 / (माप_प्रकार) ca->sb.nbuckets, sum,
				n * ca->sb.bucket_size / (ARRAY_SIZE(q) + 1));

		क्रम (i = 0; i < ARRAY_SIZE(q); i++)
			ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret,
					 "%u ", q[i]);
		ret--;

		ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret, "]\n");

		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
SHOW_LOCKED(bch_cache)

STORE(__bch_cache)
अणु
	काष्ठा cache *ca = container_of(kobj, काष्ठा cache, kobj);
	sमाप_प्रकार v;

	/* no user space access अगर प्रणाली is rebooting */
	अगर (bcache_is_reboot)
		वापस -EBUSY;

	अगर (attr == &sysfs_discard) अणु
		bool v = म_से_अदीर्घ_or_वापस(buf);

		अगर (blk_queue_discard(bdev_get_queue(ca->bdev)))
			ca->discard = v;

		अगर (v != CACHE_DISCARD(&ca->sb)) अणु
			SET_CACHE_DISCARD(&ca->sb, v);
			bcache_ग_लिखो_super(ca->set);
		पूर्ण
	पूर्ण

	अगर (attr == &sysfs_cache_replacement_policy) अणु
		v = __sysfs_match_string(cache_replacement_policies, -1, buf);
		अगर (v < 0)
			वापस v;

		अगर ((अचिन्हित पूर्णांक) v != CACHE_REPLACEMENT(&ca->sb)) अणु
			mutex_lock(&ca->set->bucket_lock);
			SET_CACHE_REPLACEMENT(&ca->sb, v);
			mutex_unlock(&ca->set->bucket_lock);

			bcache_ग_लिखो_super(ca->set);
		पूर्ण
	पूर्ण

	अगर (attr == &sysfs_clear_stats) अणु
		atomic_दीर्घ_set(&ca->sectors_written, 0);
		atomic_दीर्घ_set(&ca->btree_sectors_written, 0);
		atomic_दीर्घ_set(&ca->meta_sectors_written, 0);
		atomic_set(&ca->io_count, 0);
		atomic_set(&ca->io_errors, 0);
	पूर्ण

	वापस size;
पूर्ण
STORE_LOCKED(bch_cache)

अटल काष्ठा attribute *bch_cache_files[] = अणु
	&sysfs_bucket_size,
	&sysfs_block_size,
	&sysfs_nbuckets,
	&sysfs_priority_stats,
	&sysfs_discard,
	&sysfs_written,
	&sysfs_btree_written,
	&sysfs_metadata_written,
	&sysfs_io_errors,
	&sysfs_clear_stats,
	&sysfs_cache_replacement_policy,
	शून्य
पूर्ण;
KTYPE(bch_cache);
