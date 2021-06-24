<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _RAID5_LOG_H
#घोषणा _RAID5_LOG_H

बाह्य पूर्णांक r5l_init_log(काष्ठा r5conf *conf, काष्ठा md_rdev *rdev);
बाह्य व्योम r5l_निकास_log(काष्ठा r5conf *conf);
बाह्य पूर्णांक r5l_ग_लिखो_stripe(काष्ठा r5l_log *log, काष्ठा stripe_head *head_sh);
बाह्य व्योम r5l_ग_लिखो_stripe_run(काष्ठा r5l_log *log);
बाह्य व्योम r5l_flush_stripe_to_raid(काष्ठा r5l_log *log);
बाह्य व्योम r5l_stripe_ग_लिखो_finished(काष्ठा stripe_head *sh);
बाह्य पूर्णांक r5l_handle_flush_request(काष्ठा r5l_log *log, काष्ठा bio *bio);
बाह्य व्योम r5l_quiesce(काष्ठा r5l_log *log, पूर्णांक quiesce);
बाह्य bool r5l_log_disk_error(काष्ठा r5conf *conf);
बाह्य bool r5c_is_ग_लिखोback(काष्ठा r5l_log *log);
बाह्य पूर्णांक
r5c_try_caching_ग_लिखो(काष्ठा r5conf *conf, काष्ठा stripe_head *sh,
		      काष्ठा stripe_head_state *s, पूर्णांक disks);
बाह्य व्योम
r5c_finish_stripe_ग_लिखो_out(काष्ठा r5conf *conf, काष्ठा stripe_head *sh,
			    काष्ठा stripe_head_state *s);
बाह्य व्योम r5c_release_extra_page(काष्ठा stripe_head *sh);
बाह्य व्योम r5c_use_extra_page(काष्ठा stripe_head *sh);
बाह्य व्योम r5l_wake_reclaim(काष्ठा r5l_log *log, sector_t space);
बाह्य व्योम r5c_handle_cached_data_endio(काष्ठा r5conf *conf,
	काष्ठा stripe_head *sh, पूर्णांक disks);
बाह्य पूर्णांक r5c_cache_data(काष्ठा r5l_log *log, काष्ठा stripe_head *sh);
बाह्य व्योम r5c_make_stripe_ग_लिखो_out(काष्ठा stripe_head *sh);
बाह्य व्योम r5c_flush_cache(काष्ठा r5conf *conf, पूर्णांक num);
बाह्य व्योम r5c_check_stripe_cache_usage(काष्ठा r5conf *conf);
बाह्य व्योम r5c_check_cached_full_stripe(काष्ठा r5conf *conf);
बाह्य काष्ठा md_sysfs_entry r5c_journal_mode;
बाह्य व्योम r5c_update_on_rdev_error(काष्ठा mddev *mddev,
				     काष्ठा md_rdev *rdev);
बाह्य bool r5c_big_stripe_cached(काष्ठा r5conf *conf, sector_t sect);
बाह्य पूर्णांक r5l_start(काष्ठा r5l_log *log);

बाह्य काष्ठा dma_async_tx_descriptor *
ops_run_partial_parity(काष्ठा stripe_head *sh, काष्ठा raid5_percpu *percpu,
		       काष्ठा dma_async_tx_descriptor *tx);
बाह्य पूर्णांक ppl_init_log(काष्ठा r5conf *conf);
बाह्य व्योम ppl_निकास_log(काष्ठा r5conf *conf);
बाह्य पूर्णांक ppl_ग_लिखो_stripe(काष्ठा r5conf *conf, काष्ठा stripe_head *sh);
बाह्य व्योम ppl_ग_लिखो_stripe_run(काष्ठा r5conf *conf);
बाह्य व्योम ppl_stripe_ग_लिखो_finished(काष्ठा stripe_head *sh);
बाह्य पूर्णांक ppl_modअगरy_log(काष्ठा r5conf *conf, काष्ठा md_rdev *rdev, bool add);
बाह्य व्योम ppl_quiesce(काष्ठा r5conf *conf, पूर्णांक quiesce);
बाह्य पूर्णांक ppl_handle_flush_request(काष्ठा r5l_log *log, काष्ठा bio *bio);
बाह्य काष्ठा md_sysfs_entry ppl_ग_लिखो_hपूर्णांक;

अटल अंतरभूत bool raid5_has_log(काष्ठा r5conf *conf)
अणु
	वापस test_bit(MD_HAS_JOURNAL, &conf->mddev->flags);
पूर्ण

अटल अंतरभूत bool raid5_has_ppl(काष्ठा r5conf *conf)
अणु
	वापस test_bit(MD_HAS_PPL, &conf->mddev->flags);
पूर्ण

अटल अंतरभूत पूर्णांक log_stripe(काष्ठा stripe_head *sh, काष्ठा stripe_head_state *s)
अणु
	काष्ठा r5conf *conf = sh->raid_conf;

	अगर (conf->log) अणु
		अगर (!test_bit(STRIPE_R5C_CACHING, &sh->state)) अणु
			/* writing out phase */
			अगर (s->रुकोing_extra_page)
				वापस 0;
			वापस r5l_ग_लिखो_stripe(conf->log, sh);
		पूर्ण अन्यथा अगर (test_bit(STRIPE_LOG_TRAPPED, &sh->state)) अणु
			/* caching phase */
			वापस r5c_cache_data(conf->log, sh);
		पूर्ण
	पूर्ण अन्यथा अगर (raid5_has_ppl(conf)) अणु
		वापस ppl_ग_लिखो_stripe(conf, sh);
	पूर्ण

	वापस -EAGAIN;
पूर्ण

अटल अंतरभूत व्योम log_stripe_ग_लिखो_finished(काष्ठा stripe_head *sh)
अणु
	काष्ठा r5conf *conf = sh->raid_conf;

	अगर (conf->log)
		r5l_stripe_ग_लिखो_finished(sh);
	अन्यथा अगर (raid5_has_ppl(conf))
		ppl_stripe_ग_लिखो_finished(sh);
पूर्ण

अटल अंतरभूत व्योम log_ग_लिखो_stripe_run(काष्ठा r5conf *conf)
अणु
	अगर (conf->log)
		r5l_ग_लिखो_stripe_run(conf->log);
	अन्यथा अगर (raid5_has_ppl(conf))
		ppl_ग_लिखो_stripe_run(conf);
पूर्ण

अटल अंतरभूत व्योम log_flush_stripe_to_raid(काष्ठा r5conf *conf)
अणु
	अगर (conf->log)
		r5l_flush_stripe_to_raid(conf->log);
	अन्यथा अगर (raid5_has_ppl(conf))
		ppl_ग_लिखो_stripe_run(conf);
पूर्ण

अटल अंतरभूत पूर्णांक log_handle_flush_request(काष्ठा r5conf *conf, काष्ठा bio *bio)
अणु
	पूर्णांक ret = -ENODEV;

	अगर (conf->log)
		ret = r5l_handle_flush_request(conf->log, bio);
	अन्यथा अगर (raid5_has_ppl(conf))
		ret = ppl_handle_flush_request(conf->log, bio);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम log_quiesce(काष्ठा r5conf *conf, पूर्णांक quiesce)
अणु
	अगर (conf->log)
		r5l_quiesce(conf->log, quiesce);
	अन्यथा अगर (raid5_has_ppl(conf))
		ppl_quiesce(conf, quiesce);
पूर्ण

अटल अंतरभूत व्योम log_निकास(काष्ठा r5conf *conf)
अणु
	अगर (conf->log)
		r5l_निकास_log(conf);
	अन्यथा अगर (raid5_has_ppl(conf))
		ppl_निकास_log(conf);
पूर्ण

अटल अंतरभूत पूर्णांक log_init(काष्ठा r5conf *conf, काष्ठा md_rdev *journal_dev,
			   bool ppl)
अणु
	अगर (journal_dev)
		वापस r5l_init_log(conf, journal_dev);
	अन्यथा अगर (ppl)
		वापस ppl_init_log(conf);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक log_modअगरy(काष्ठा r5conf *conf, काष्ठा md_rdev *rdev, bool add)
अणु
	अगर (raid5_has_ppl(conf))
		वापस ppl_modअगरy_log(conf, rdev, add);

	वापस 0;
पूर्ण

#पूर्ण_अगर
