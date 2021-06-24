<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/f2fs/gc.c
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 */
#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/init.h>
#समावेश <linux/f2fs_fs.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/delay.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/sched/संकेत.स>

#समावेश "f2fs.h"
#समावेश "node.h"
#समावेश "segment.h"
#समावेश "gc.h"
#समावेश <trace/events/f2fs.h>

अटल काष्ठा kmem_cache *victim_entry_slab;

अटल अचिन्हित पूर्णांक count_bits(स्थिर अचिन्हित दीर्घ *addr,
				अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक len);

अटल पूर्णांक gc_thपढ़ो_func(व्योम *data)
अणु
	काष्ठा f2fs_sb_info *sbi = data;
	काष्ठा f2fs_gc_kthपढ़ो *gc_th = sbi->gc_thपढ़ो;
	रुको_queue_head_t *wq = &sbi->gc_thपढ़ो->gc_रुको_queue_head;
	रुको_queue_head_t *fggc_wq = &sbi->gc_thपढ़ो->fggc_wq;
	अचिन्हित पूर्णांक रुको_ms;

	रुको_ms = gc_th->min_sleep_समय;

	set_मुक्तzable();
	करो अणु
		bool sync_mode, क्रमeground = false;

		रुको_event_पूर्णांकerruptible_समयout(*wq,
				kthपढ़ो_should_stop() || मुक्तzing(current) ||
				रुकोqueue_active(fggc_wq) ||
				gc_th->gc_wake,
				msecs_to_jअगरfies(रुको_ms));

		अगर (test_opt(sbi, GC_MERGE) && रुकोqueue_active(fggc_wq))
			क्रमeground = true;

		/* give it a try one समय */
		अगर (gc_th->gc_wake)
			gc_th->gc_wake = 0;

		अगर (try_to_मुक्तze()) अणु
			stat_other_skip_bggc_count(sbi);
			जारी;
		पूर्ण
		अगर (kthपढ़ो_should_stop())
			अवरोध;

		अगर (sbi->sb->s_ग_लिखोrs.frozen >= SB_FREEZE_WRITE) अणु
			increase_sleep_समय(gc_th, &रुको_ms);
			stat_other_skip_bggc_count(sbi);
			जारी;
		पूर्ण

		अगर (समय_प्रकारo_inject(sbi, FAULT_CHECKPOINT)) अणु
			f2fs_show_injection_info(sbi, FAULT_CHECKPOINT);
			f2fs_stop_checkpoपूर्णांक(sbi, false);
		पूर्ण

		अगर (!sb_start_ग_लिखो_trylock(sbi->sb)) अणु
			stat_other_skip_bggc_count(sbi);
			जारी;
		पूर्ण

		/*
		 * [GC triggering condition]
		 * 0. GC is not conducted currently.
		 * 1. There are enough dirty segments.
		 * 2. IO subप्रणाली is idle by checking the # of ग_लिखोback pages.
		 * 3. IO subप्रणाली is idle by checking the # of requests in
		 *    bdev's request list.
		 *
		 * Note) We have to aव्योम triggering GCs frequently.
		 * Because it is possible that some segments can be
		 * invalidated soon after by user update or deletion.
		 * So, I'd like to रुको some समय to collect dirty segments.
		 */
		अगर (sbi->gc_mode == GC_URGENT_HIGH) अणु
			रुको_ms = gc_th->urgent_sleep_समय;
			करोwn_ग_लिखो(&sbi->gc_lock);
			जाओ करो_gc;
		पूर्ण

		अगर (क्रमeground) अणु
			करोwn_ग_लिखो(&sbi->gc_lock);
			जाओ करो_gc;
		पूर्ण अन्यथा अगर (!करोwn_ग_लिखो_trylock(&sbi->gc_lock)) अणु
			stat_other_skip_bggc_count(sbi);
			जाओ next;
		पूर्ण

		अगर (!is_idle(sbi, GC_TIME)) अणु
			increase_sleep_समय(gc_th, &रुको_ms);
			up_ग_लिखो(&sbi->gc_lock);
			stat_io_skip_bggc_count(sbi);
			जाओ next;
		पूर्ण

		अगर (has_enough_invalid_blocks(sbi))
			decrease_sleep_समय(gc_th, &रुको_ms);
		अन्यथा
			increase_sleep_समय(gc_th, &रुको_ms);
करो_gc:
		अगर (!क्रमeground)
			stat_inc_bggc_count(sbi->stat_info);

		sync_mode = F2FS_OPTION(sbi).bggc_mode == BGGC_MODE_SYNC;

		/* क्रमeground GC was been triggered via f2fs_balance_fs() */
		अगर (क्रमeground)
			sync_mode = false;

		/* अगर वापस value is not zero, no victim was selected */
		अगर (f2fs_gc(sbi, sync_mode, !क्रमeground, false, शून्य_SEGNO))
			रुको_ms = gc_th->no_gc_sleep_समय;

		अगर (क्रमeground)
			wake_up_all(&gc_th->fggc_wq);

		trace_f2fs_background_gc(sbi->sb, रुको_ms,
				preमुक्त_segments(sbi), मुक्त_segments(sbi));

		/* balancing f2fs's metadata periodically */
		f2fs_balance_fs_bg(sbi, true);
next:
		sb_end_ग_लिखो(sbi->sb);

	पूर्ण जबतक (!kthपढ़ो_should_stop());
	वापस 0;
पूर्ण

पूर्णांक f2fs_start_gc_thपढ़ो(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_gc_kthपढ़ो *gc_th;
	dev_t dev = sbi->sb->s_bdev->bd_dev;
	पूर्णांक err = 0;

	gc_th = f2fs_kदो_स्मृति(sbi, माप(काष्ठा f2fs_gc_kthपढ़ो), GFP_KERNEL);
	अगर (!gc_th) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	gc_th->urgent_sleep_समय = DEF_GC_THREAD_URGENT_SLEEP_TIME;
	gc_th->min_sleep_समय = DEF_GC_THREAD_MIN_SLEEP_TIME;
	gc_th->max_sleep_समय = DEF_GC_THREAD_MAX_SLEEP_TIME;
	gc_th->no_gc_sleep_समय = DEF_GC_THREAD_NOGC_SLEEP_TIME;

	gc_th->gc_wake = 0;

	sbi->gc_thपढ़ो = gc_th;
	init_रुकोqueue_head(&sbi->gc_thपढ़ो->gc_रुको_queue_head);
	init_रुकोqueue_head(&sbi->gc_thपढ़ो->fggc_wq);
	sbi->gc_thपढ़ो->f2fs_gc_task = kthपढ़ो_run(gc_thपढ़ो_func, sbi,
			"f2fs_gc-%u:%u", MAJOR(dev), MINOR(dev));
	अगर (IS_ERR(gc_th->f2fs_gc_task)) अणु
		err = PTR_ERR(gc_th->f2fs_gc_task);
		kमुक्त(gc_th);
		sbi->gc_thपढ़ो = शून्य;
	पूर्ण
out:
	वापस err;
पूर्ण

व्योम f2fs_stop_gc_thपढ़ो(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा f2fs_gc_kthपढ़ो *gc_th = sbi->gc_thपढ़ो;

	अगर (!gc_th)
		वापस;
	kthपढ़ो_stop(gc_th->f2fs_gc_task);
	wake_up_all(&gc_th->fggc_wq);
	kमुक्त(gc_th);
	sbi->gc_thपढ़ो = शून्य;
पूर्ण

अटल पूर्णांक select_gc_type(काष्ठा f2fs_sb_info *sbi, पूर्णांक gc_type)
अणु
	पूर्णांक gc_mode;

	अगर (gc_type == BG_GC) अणु
		अगर (sbi->am.atgc_enabled)
			gc_mode = GC_AT;
		अन्यथा
			gc_mode = GC_CB;
	पूर्ण अन्यथा अणु
		gc_mode = GC_GREEDY;
	पूर्ण

	चयन (sbi->gc_mode) अणु
	हाल GC_IDLE_CB:
		gc_mode = GC_CB;
		अवरोध;
	हाल GC_IDLE_GREEDY:
	हाल GC_URGENT_HIGH:
		gc_mode = GC_GREEDY;
		अवरोध;
	हाल GC_IDLE_AT:
		gc_mode = GC_AT;
		अवरोध;
	पूर्ण

	वापस gc_mode;
पूर्ण

अटल व्योम select_policy(काष्ठा f2fs_sb_info *sbi, पूर्णांक gc_type,
			पूर्णांक type, काष्ठा victim_sel_policy *p)
अणु
	काष्ठा dirty_seglist_info *dirty_i = सूचीTY_I(sbi);

	अगर (p->alloc_mode == SSR) अणु
		p->gc_mode = GC_GREEDY;
		p->dirty_biपंचांगap = dirty_i->dirty_segmap[type];
		p->max_search = dirty_i->nr_dirty[type];
		p->ofs_unit = 1;
	पूर्ण अन्यथा अगर (p->alloc_mode == AT_SSR) अणु
		p->gc_mode = GC_GREEDY;
		p->dirty_biपंचांगap = dirty_i->dirty_segmap[type];
		p->max_search = dirty_i->nr_dirty[type];
		p->ofs_unit = 1;
	पूर्ण अन्यथा अणु
		p->gc_mode = select_gc_type(sbi, gc_type);
		p->ofs_unit = sbi->segs_per_sec;
		अगर (__is_large_section(sbi)) अणु
			p->dirty_biपंचांगap = dirty_i->dirty_secmap;
			p->max_search = count_bits(p->dirty_biपंचांगap,
						0, MAIN_SECS(sbi));
		पूर्ण अन्यथा अणु
			p->dirty_biपंचांगap = dirty_i->dirty_segmap[सूचीTY];
			p->max_search = dirty_i->nr_dirty[सूचीTY];
		पूर्ण
	पूर्ण

	/*
	 * adjust candidates range, should select all dirty segments क्रम
	 * क्रमeground GC and urgent GC हालs.
	 */
	अगर (gc_type != FG_GC &&
			(sbi->gc_mode != GC_URGENT_HIGH) &&
			(p->gc_mode != GC_AT && p->alloc_mode != AT_SSR) &&
			p->max_search > sbi->max_victim_search)
		p->max_search = sbi->max_victim_search;

	/* let's select beginning hot/small space first in no_heap mode*/
	अगर (test_opt(sbi, NOHEAP) &&
		(type == CURSEG_HOT_DATA || IS_NODESEG(type)))
		p->offset = 0;
	अन्यथा
		p->offset = SIT_I(sbi)->last_victim[p->gc_mode];
पूर्ण

अटल अचिन्हित पूर्णांक get_max_cost(काष्ठा f2fs_sb_info *sbi,
				काष्ठा victim_sel_policy *p)
अणु
	/* SSR allocates in a segment unit */
	अगर (p->alloc_mode == SSR)
		वापस sbi->blocks_per_seg;
	अन्यथा अगर (p->alloc_mode == AT_SSR)
		वापस अच_पूर्णांक_उच्च;

	/* LFS */
	अगर (p->gc_mode == GC_GREEDY)
		वापस 2 * sbi->blocks_per_seg * p->ofs_unit;
	अन्यथा अगर (p->gc_mode == GC_CB)
		वापस अच_पूर्णांक_उच्च;
	अन्यथा अगर (p->gc_mode == GC_AT)
		वापस अच_पूर्णांक_उच्च;
	अन्यथा /* No other gc_mode */
		वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक check_bg_victims(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा dirty_seglist_info *dirty_i = सूचीTY_I(sbi);
	अचिन्हित पूर्णांक secno;

	/*
	 * If the gc_type is FG_GC, we can select victim segments
	 * selected by background GC beक्रमe.
	 * Those segments guarantee they have small valid blocks.
	 */
	क्रम_each_set_bit(secno, dirty_i->victim_secmap, MAIN_SECS(sbi)) अणु
		अगर (sec_usage_check(sbi, secno))
			जारी;
		clear_bit(secno, dirty_i->victim_secmap);
		वापस GET_SEG_FROM_SEC(sbi, secno);
	पूर्ण
	वापस शून्य_SEGNO;
पूर्ण

अटल अचिन्हित पूर्णांक get_cb_cost(काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक segno)
अणु
	काष्ठा sit_info *sit_i = SIT_I(sbi);
	अचिन्हित पूर्णांक secno = GET_SEC_FROM_SEG(sbi, segno);
	अचिन्हित पूर्णांक start = GET_SEG_FROM_SEC(sbi, secno);
	अचिन्हित दीर्घ दीर्घ mसमय = 0;
	अचिन्हित पूर्णांक vblocks;
	अचिन्हित अक्षर age = 0;
	अचिन्हित अक्षर u;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक usable_segs_per_sec = f2fs_usable_segs_in_sec(sbi, segno);

	क्रम (i = 0; i < usable_segs_per_sec; i++)
		mसमय += get_seg_entry(sbi, start + i)->mसमय;
	vblocks = get_valid_blocks(sbi, segno, true);

	mसमय = भाग_u64(mसमय, usable_segs_per_sec);
	vblocks = भाग_u64(vblocks, usable_segs_per_sec);

	u = (vblocks * 100) >> sbi->log_blocks_per_seg;

	/* Handle अगर the प्रणाली समय has changed by the user */
	अगर (mसमय < sit_i->min_mसमय)
		sit_i->min_mसमय = mसमय;
	अगर (mसमय > sit_i->max_mसमय)
		sit_i->max_mसमय = mसमय;
	अगर (sit_i->max_mसमय != sit_i->min_mसमय)
		age = 100 - भाग64_u64(100 * (mसमय - sit_i->min_mसमय),
				sit_i->max_mसमय - sit_i->min_mसमय);

	वापस अच_पूर्णांक_उच्च - ((100 * (100 - u) * age) / (100 + u));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_gc_cost(काष्ठा f2fs_sb_info *sbi,
			अचिन्हित पूर्णांक segno, काष्ठा victim_sel_policy *p)
अणु
	अगर (p->alloc_mode == SSR)
		वापस get_seg_entry(sbi, segno)->ckpt_valid_blocks;

	/* alloc_mode == LFS */
	अगर (p->gc_mode == GC_GREEDY)
		वापस get_valid_blocks(sbi, segno, true);
	अन्यथा अगर (p->gc_mode == GC_CB)
		वापस get_cb_cost(sbi, segno);

	f2fs_bug_on(sbi, 1);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक count_bits(स्थिर अचिन्हित दीर्घ *addr,
				अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक end = offset + len, sum = 0;

	जबतक (offset < end) अणु
		अगर (test_bit(offset++, addr))
			++sum;
	पूर्ण
	वापस sum;
पूर्ण

अटल काष्ठा victim_entry *attach_victim_entry(काष्ठा f2fs_sb_info *sbi,
				अचिन्हित दीर्घ दीर्घ mसमय, अचिन्हित पूर्णांक segno,
				काष्ठा rb_node *parent, काष्ठा rb_node **p,
				bool left_most)
अणु
	काष्ठा atgc_management *am = &sbi->am;
	काष्ठा victim_entry *ve;

	ve =  f2fs_kmem_cache_alloc(victim_entry_slab, GFP_NOFS);

	ve->mसमय = mसमय;
	ve->segno = segno;

	rb_link_node(&ve->rb_node, parent, p);
	rb_insert_color_cached(&ve->rb_node, &am->root, left_most);

	list_add_tail(&ve->list, &am->victim_list);

	am->victim_count++;

	वापस ve;
पूर्ण

अटल व्योम insert_victim_entry(काष्ठा f2fs_sb_info *sbi,
				अचिन्हित दीर्घ दीर्घ mसमय, अचिन्हित पूर्णांक segno)
अणु
	काष्ठा atgc_management *am = &sbi->am;
	काष्ठा rb_node **p;
	काष्ठा rb_node *parent = शून्य;
	bool left_most = true;

	p = f2fs_lookup_rb_tree_ext(sbi, &am->root, &parent, mसमय, &left_most);
	attach_victim_entry(sbi, mसमय, segno, parent, p, left_most);
पूर्ण

अटल व्योम add_victim_entry(काष्ठा f2fs_sb_info *sbi,
				काष्ठा victim_sel_policy *p, अचिन्हित पूर्णांक segno)
अणु
	काष्ठा sit_info *sit_i = SIT_I(sbi);
	अचिन्हित पूर्णांक secno = GET_SEC_FROM_SEG(sbi, segno);
	अचिन्हित पूर्णांक start = GET_SEG_FROM_SEC(sbi, secno);
	अचिन्हित दीर्घ दीर्घ mसमय = 0;
	अचिन्हित पूर्णांक i;

	अगर (unlikely(is_sbi_flag_set(sbi, SBI_CP_DISABLED))) अणु
		अगर (p->gc_mode == GC_AT &&
			get_valid_blocks(sbi, segno, true) == 0)
			वापस;
	पूर्ण

	क्रम (i = 0; i < sbi->segs_per_sec; i++)
		mसमय += get_seg_entry(sbi, start + i)->mसमय;
	mसमय = भाग_u64(mसमय, sbi->segs_per_sec);

	/* Handle अगर the प्रणाली समय has changed by the user */
	अगर (mसमय < sit_i->min_mसमय)
		sit_i->min_mसमय = mसमय;
	अगर (mसमय > sit_i->max_mसमय)
		sit_i->max_mसमय = mसमय;
	अगर (mसमय < sit_i->dirty_min_mसमय)
		sit_i->dirty_min_mसमय = mसमय;
	अगर (mसमय > sit_i->dirty_max_mसमय)
		sit_i->dirty_max_mसमय = mसमय;

	/* करोn't choose young section as candidate */
	अगर (sit_i->dirty_max_mसमय - mसमय < p->age_threshold)
		वापस;

	insert_victim_entry(sbi, mसमय, segno);
पूर्ण

अटल काष्ठा rb_node *lookup_central_victim(काष्ठा f2fs_sb_info *sbi,
						काष्ठा victim_sel_policy *p)
अणु
	काष्ठा atgc_management *am = &sbi->am;
	काष्ठा rb_node *parent = शून्य;
	bool left_most;

	f2fs_lookup_rb_tree_ext(sbi, &am->root, &parent, p->age, &left_most);

	वापस parent;
पूर्ण

अटल व्योम atgc_lookup_victim(काष्ठा f2fs_sb_info *sbi,
						काष्ठा victim_sel_policy *p)
अणु
	काष्ठा sit_info *sit_i = SIT_I(sbi);
	काष्ठा atgc_management *am = &sbi->am;
	काष्ठा rb_root_cached *root = &am->root;
	काष्ठा rb_node *node;
	काष्ठा rb_entry *re;
	काष्ठा victim_entry *ve;
	अचिन्हित दीर्घ दीर्घ total_समय;
	अचिन्हित दीर्घ दीर्घ age, u, accu;
	अचिन्हित दीर्घ दीर्घ max_mसमय = sit_i->dirty_max_mसमय;
	अचिन्हित दीर्घ दीर्घ min_mसमय = sit_i->dirty_min_mसमय;
	अचिन्हित पूर्णांक sec_blocks = BLKS_PER_SEC(sbi);
	अचिन्हित पूर्णांक vblocks;
	अचिन्हित पूर्णांक dirty_threshold = max(am->max_candidate_count,
					am->candidate_ratio *
					am->victim_count / 100);
	अचिन्हित पूर्णांक age_weight = am->age_weight;
	अचिन्हित पूर्णांक cost;
	अचिन्हित पूर्णांक iter = 0;

	अगर (max_mसमय < min_mसमय)
		वापस;

	max_mसमय += 1;
	total_समय = max_mसमय - min_mसमय;

	accu = भाग64_u64(ULदीर्घ_उच्च, total_समय);
	accu = min_t(अचिन्हित दीर्घ दीर्घ, भाग_u64(accu, 100),
					DEFAULT_ACCURACY_CLASS);

	node = rb_first_cached(root);
next:
	re = rb_entry_safe(node, काष्ठा rb_entry, rb_node);
	अगर (!re)
		वापस;

	ve = (काष्ठा victim_entry *)re;

	अगर (ve->mसमय >= max_mसमय || ve->mसमय < min_mसमय)
		जाओ skip;

	/* age = 10000 * x% * 60 */
	age = भाग64_u64(accu * (max_mसमय - ve->mसमय), total_समय) *
								age_weight;

	vblocks = get_valid_blocks(sbi, ve->segno, true);
	f2fs_bug_on(sbi, !vblocks || vblocks == sec_blocks);

	/* u = 10000 * x% * 40 */
	u = भाग64_u64(accu * (sec_blocks - vblocks), sec_blocks) *
							(100 - age_weight);

	f2fs_bug_on(sbi, age + u >= अच_पूर्णांक_उच्च);

	cost = अच_पूर्णांक_उच्च - (age + u);
	iter++;

	अगर (cost < p->min_cost ||
			(cost == p->min_cost && age > p->oldest_age)) अणु
		p->min_cost = cost;
		p->oldest_age = age;
		p->min_segno = ve->segno;
	पूर्ण
skip:
	अगर (iter < dirty_threshold) अणु
		node = rb_next(node);
		जाओ next;
	पूर्ण
पूर्ण

/*
 * select candidates around source section in range of
 * [target - dirty_threshold, target + dirty_threshold]
 */
अटल व्योम atssr_lookup_victim(काष्ठा f2fs_sb_info *sbi,
						काष्ठा victim_sel_policy *p)
अणु
	काष्ठा sit_info *sit_i = SIT_I(sbi);
	काष्ठा atgc_management *am = &sbi->am;
	काष्ठा rb_node *node;
	काष्ठा rb_entry *re;
	काष्ठा victim_entry *ve;
	अचिन्हित दीर्घ दीर्घ age;
	अचिन्हित दीर्घ दीर्घ max_mसमय = sit_i->dirty_max_mसमय;
	अचिन्हित दीर्घ दीर्घ min_mसमय = sit_i->dirty_min_mसमय;
	अचिन्हित पूर्णांक seg_blocks = sbi->blocks_per_seg;
	अचिन्हित पूर्णांक vblocks;
	अचिन्हित पूर्णांक dirty_threshold = max(am->max_candidate_count,
					am->candidate_ratio *
					am->victim_count / 100);
	अचिन्हित पूर्णांक cost;
	अचिन्हित पूर्णांक iter = 0;
	पूर्णांक stage = 0;

	अगर (max_mसमय < min_mसमय)
		वापस;
	max_mसमय += 1;
next_stage:
	node = lookup_central_victim(sbi, p);
next_node:
	re = rb_entry_safe(node, काष्ठा rb_entry, rb_node);
	अगर (!re) अणु
		अगर (stage == 0)
			जाओ skip_stage;
		वापस;
	पूर्ण

	ve = (काष्ठा victim_entry *)re;

	अगर (ve->mसमय >= max_mसमय || ve->mसमय < min_mसमय)
		जाओ skip_node;

	age = max_mसमय - ve->mसमय;

	vblocks = get_seg_entry(sbi, ve->segno)->ckpt_valid_blocks;
	f2fs_bug_on(sbi, !vblocks);

	/* rare हाल */
	अगर (vblocks == seg_blocks)
		जाओ skip_node;

	iter++;

	age = max_mसमय - असल(p->age - age);
	cost = अच_पूर्णांक_उच्च - vblocks;

	अगर (cost < p->min_cost ||
			(cost == p->min_cost && age > p->oldest_age)) अणु
		p->min_cost = cost;
		p->oldest_age = age;
		p->min_segno = ve->segno;
	पूर्ण
skip_node:
	अगर (iter < dirty_threshold) अणु
		अगर (stage == 0)
			node = rb_prev(node);
		अन्यथा अगर (stage == 1)
			node = rb_next(node);
		जाओ next_node;
	पूर्ण
skip_stage:
	अगर (stage < 1) अणु
		stage++;
		iter = 0;
		जाओ next_stage;
	पूर्ण
पूर्ण
अटल व्योम lookup_victim_by_age(काष्ठा f2fs_sb_info *sbi,
						काष्ठा victim_sel_policy *p)
अणु
	f2fs_bug_on(sbi, !f2fs_check_rb_tree_consistence(sbi,
						&sbi->am.root, true));

	अगर (p->gc_mode == GC_AT)
		atgc_lookup_victim(sbi, p);
	अन्यथा अगर (p->alloc_mode == AT_SSR)
		atssr_lookup_victim(sbi, p);
	अन्यथा
		f2fs_bug_on(sbi, 1);
पूर्ण

अटल व्योम release_victim_entry(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा atgc_management *am = &sbi->am;
	काष्ठा victim_entry *ve, *पंचांगp;

	list_क्रम_each_entry_safe(ve, पंचांगp, &am->victim_list, list) अणु
		list_del(&ve->list);
		kmem_cache_मुक्त(victim_entry_slab, ve);
		am->victim_count--;
	पूर्ण

	am->root = RB_ROOT_CACHED;

	f2fs_bug_on(sbi, am->victim_count);
	f2fs_bug_on(sbi, !list_empty(&am->victim_list));
पूर्ण

/*
 * This function is called from two paths.
 * One is garbage collection and the other is SSR segment selection.
 * When it is called during GC, it just माला_लो a victim segment
 * and it करोes not हटाओ it from dirty seglist.
 * When it is called from SSR segment selection, it finds a segment
 * which has minimum valid blocks and हटाओs it from dirty seglist.
 */
अटल पूर्णांक get_victim_by_शेष(काष्ठा f2fs_sb_info *sbi,
			अचिन्हित पूर्णांक *result, पूर्णांक gc_type, पूर्णांक type,
			अक्षर alloc_mode, अचिन्हित दीर्घ दीर्घ age)
अणु
	काष्ठा dirty_seglist_info *dirty_i = सूचीTY_I(sbi);
	काष्ठा sit_info *sm = SIT_I(sbi);
	काष्ठा victim_sel_policy p;
	अचिन्हित पूर्णांक secno, last_victim;
	अचिन्हित पूर्णांक last_segment;
	अचिन्हित पूर्णांक nsearched;
	bool is_atgc;
	पूर्णांक ret = 0;

	mutex_lock(&dirty_i->seglist_lock);
	last_segment = MAIN_SECS(sbi) * sbi->segs_per_sec;

	p.alloc_mode = alloc_mode;
	p.age = age;
	p.age_threshold = sbi->am.age_threshold;

retry:
	select_policy(sbi, gc_type, type, &p);
	p.min_segno = शून्य_SEGNO;
	p.oldest_age = 0;
	p.min_cost = get_max_cost(sbi, &p);

	is_atgc = (p.gc_mode == GC_AT || p.alloc_mode == AT_SSR);
	nsearched = 0;

	अगर (is_atgc)
		SIT_I(sbi)->dirty_min_mसमय = ULदीर्घ_उच्च;

	अगर (*result != शून्य_SEGNO) अणु
		अगर (!get_valid_blocks(sbi, *result, false)) अणु
			ret = -ENODATA;
			जाओ out;
		पूर्ण

		अगर (sec_usage_check(sbi, GET_SEC_FROM_SEG(sbi, *result)))
			ret = -EBUSY;
		अन्यथा
			p.min_segno = *result;
		जाओ out;
	पूर्ण

	ret = -ENODATA;
	अगर (p.max_search == 0)
		जाओ out;

	अगर (__is_large_section(sbi) && p.alloc_mode == LFS) अणु
		अगर (sbi->next_victim_seg[BG_GC] != शून्य_SEGNO) अणु
			p.min_segno = sbi->next_victim_seg[BG_GC];
			*result = p.min_segno;
			sbi->next_victim_seg[BG_GC] = शून्य_SEGNO;
			जाओ got_result;
		पूर्ण
		अगर (gc_type == FG_GC &&
				sbi->next_victim_seg[FG_GC] != शून्य_SEGNO) अणु
			p.min_segno = sbi->next_victim_seg[FG_GC];
			*result = p.min_segno;
			sbi->next_victim_seg[FG_GC] = शून्य_SEGNO;
			जाओ got_result;
		पूर्ण
	पूर्ण

	last_victim = sm->last_victim[p.gc_mode];
	अगर (p.alloc_mode == LFS && gc_type == FG_GC) अणु
		p.min_segno = check_bg_victims(sbi);
		अगर (p.min_segno != शून्य_SEGNO)
			जाओ got_it;
	पूर्ण

	जबतक (1) अणु
		अचिन्हित दीर्घ cost, *dirty_biपंचांगap;
		अचिन्हित पूर्णांक unit_no, segno;

		dirty_biपंचांगap = p.dirty_biपंचांगap;
		unit_no = find_next_bit(dirty_biपंचांगap,
				last_segment / p.ofs_unit,
				p.offset / p.ofs_unit);
		segno = unit_no * p.ofs_unit;
		अगर (segno >= last_segment) अणु
			अगर (sm->last_victim[p.gc_mode]) अणु
				last_segment =
					sm->last_victim[p.gc_mode];
				sm->last_victim[p.gc_mode] = 0;
				p.offset = 0;
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण

		p.offset = segno + p.ofs_unit;
		nsearched++;

#अगर_घोषित CONFIG_F2FS_CHECK_FS
		/*
		 * skip selecting the invalid segno (that is failed due to block
		 * validity check failure during GC) to aव्योम endless GC loop in
		 * such हालs.
		 */
		अगर (test_bit(segno, sm->invalid_segmap))
			जाओ next;
#पूर्ण_अगर

		secno = GET_SEC_FROM_SEG(sbi, segno);

		अगर (sec_usage_check(sbi, secno))
			जाओ next;

		/* Don't touch checkpoपूर्णांकed data */
		अगर (unlikely(is_sbi_flag_set(sbi, SBI_CP_DISABLED))) अणु
			अगर (p.alloc_mode == LFS) अणु
				/*
				 * LFS is set to find source section during GC.
				 * The victim should have no checkpoपूर्णांकed data.
				 */
				अगर (get_ckpt_valid_blocks(sbi, segno, true))
					जाओ next;
			पूर्ण अन्यथा अणु
				/*
				 * SSR | AT_SSR are set to find target segment
				 * क्रम ग_लिखोs which can be full by checkpoपूर्णांकed
				 * and newly written blocks.
				 */
				अगर (!f2fs_segment_has_मुक्त_slot(sbi, segno))
					जाओ next;
			पूर्ण
		पूर्ण

		अगर (gc_type == BG_GC && test_bit(secno, dirty_i->victim_secmap))
			जाओ next;

		अगर (is_atgc) अणु
			add_victim_entry(sbi, &p, segno);
			जाओ next;
		पूर्ण

		cost = get_gc_cost(sbi, segno, &p);

		अगर (p.min_cost > cost) अणु
			p.min_segno = segno;
			p.min_cost = cost;
		पूर्ण
next:
		अगर (nsearched >= p.max_search) अणु
			अगर (!sm->last_victim[p.gc_mode] && segno <= last_victim)
				sm->last_victim[p.gc_mode] =
					last_victim + p.ofs_unit;
			अन्यथा
				sm->last_victim[p.gc_mode] = segno + p.ofs_unit;
			sm->last_victim[p.gc_mode] %=
				(MAIN_SECS(sbi) * sbi->segs_per_sec);
			अवरोध;
		पूर्ण
	पूर्ण

	/* get victim क्रम GC_AT/AT_SSR */
	अगर (is_atgc) अणु
		lookup_victim_by_age(sbi, &p);
		release_victim_entry(sbi);
	पूर्ण

	अगर (is_atgc && p.min_segno == शून्य_SEGNO &&
			sm->elapsed_समय < p.age_threshold) अणु
		p.age_threshold = 0;
		जाओ retry;
	पूर्ण

	अगर (p.min_segno != शून्य_SEGNO) अणु
got_it:
		*result = (p.min_segno / p.ofs_unit) * p.ofs_unit;
got_result:
		अगर (p.alloc_mode == LFS) अणु
			secno = GET_SEC_FROM_SEG(sbi, p.min_segno);
			अगर (gc_type == FG_GC)
				sbi->cur_victim_sec = secno;
			अन्यथा
				set_bit(secno, dirty_i->victim_secmap);
		पूर्ण
		ret = 0;

	पूर्ण
out:
	अगर (p.min_segno != शून्य_SEGNO)
		trace_f2fs_get_victim(sbi->sb, type, gc_type, &p,
				sbi->cur_victim_sec,
				preमुक्त_segments(sbi), मुक्त_segments(sbi));
	mutex_unlock(&dirty_i->seglist_lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा victim_selection शेष_v_ops = अणु
	.get_victim = get_victim_by_शेष,
पूर्ण;

अटल काष्ठा inode *find_gc_inode(काष्ठा gc_inode_list *gc_list, nid_t ino)
अणु
	काष्ठा inode_entry *ie;

	ie = radix_tree_lookup(&gc_list->iroot, ino);
	अगर (ie)
		वापस ie->inode;
	वापस शून्य;
पूर्ण

अटल व्योम add_gc_inode(काष्ठा gc_inode_list *gc_list, काष्ठा inode *inode)
अणु
	काष्ठा inode_entry *new_ie;

	अगर (inode == find_gc_inode(gc_list, inode->i_ino)) अणु
		iput(inode);
		वापस;
	पूर्ण
	new_ie = f2fs_kmem_cache_alloc(f2fs_inode_entry_slab, GFP_NOFS);
	new_ie->inode = inode;

	f2fs_radix_tree_insert(&gc_list->iroot, inode->i_ino, new_ie);
	list_add_tail(&new_ie->list, &gc_list->ilist);
पूर्ण

अटल व्योम put_gc_inode(काष्ठा gc_inode_list *gc_list)
अणु
	काष्ठा inode_entry *ie, *next_ie;

	list_क्रम_each_entry_safe(ie, next_ie, &gc_list->ilist, list) अणु
		radix_tree_delete(&gc_list->iroot, ie->inode->i_ino);
		iput(ie->inode);
		list_del(&ie->list);
		kmem_cache_मुक्त(f2fs_inode_entry_slab, ie);
	पूर्ण
पूर्ण

अटल पूर्णांक check_valid_map(काष्ठा f2fs_sb_info *sbi,
				अचिन्हित पूर्णांक segno, पूर्णांक offset)
अणु
	काष्ठा sit_info *sit_i = SIT_I(sbi);
	काष्ठा seg_entry *sentry;
	पूर्णांक ret;

	करोwn_पढ़ो(&sit_i->sentry_lock);
	sentry = get_seg_entry(sbi, segno);
	ret = f2fs_test_bit(offset, sentry->cur_valid_map);
	up_पढ़ो(&sit_i->sentry_lock);
	वापस ret;
पूर्ण

/*
 * This function compares node address got in summary with that in NAT.
 * On validity, copy that node with cold status, otherwise (invalid node)
 * ignore that.
 */
अटल पूर्णांक gc_node_segment(काष्ठा f2fs_sb_info *sbi,
		काष्ठा f2fs_summary *sum, अचिन्हित पूर्णांक segno, पूर्णांक gc_type)
अणु
	काष्ठा f2fs_summary *entry;
	block_t start_addr;
	पूर्णांक off;
	पूर्णांक phase = 0;
	bool fggc = (gc_type == FG_GC);
	पूर्णांक submitted = 0;
	अचिन्हित पूर्णांक usable_blks_in_seg = f2fs_usable_blks_in_seg(sbi, segno);

	start_addr = START_BLOCK(sbi, segno);

next_step:
	entry = sum;

	अगर (fggc && phase == 2)
		atomic_inc(&sbi->wb_sync_req[NODE]);

	क्रम (off = 0; off < usable_blks_in_seg; off++, entry++) अणु
		nid_t nid = le32_to_cpu(entry->nid);
		काष्ठा page *node_page;
		काष्ठा node_info ni;
		पूर्णांक err;

		/* stop BG_GC अगर there is not enough मुक्त sections. */
		अगर (gc_type == BG_GC && has_not_enough_मुक्त_secs(sbi, 0, 0))
			वापस submitted;

		अगर (check_valid_map(sbi, segno, off) == 0)
			जारी;

		अगर (phase == 0) अणु
			f2fs_ra_meta_pages(sbi, NAT_BLOCK_OFFSET(nid), 1,
							META_NAT, true);
			जारी;
		पूर्ण

		अगर (phase == 1) अणु
			f2fs_ra_node_page(sbi, nid);
			जारी;
		पूर्ण

		/* phase == 2 */
		node_page = f2fs_get_node_page(sbi, nid);
		अगर (IS_ERR(node_page))
			जारी;

		/* block may become invalid during f2fs_get_node_page */
		अगर (check_valid_map(sbi, segno, off) == 0) अणु
			f2fs_put_page(node_page, 1);
			जारी;
		पूर्ण

		अगर (f2fs_get_node_info(sbi, nid, &ni)) अणु
			f2fs_put_page(node_page, 1);
			जारी;
		पूर्ण

		अगर (ni.blk_addr != start_addr + off) अणु
			f2fs_put_page(node_page, 1);
			जारी;
		पूर्ण

		err = f2fs_move_node_page(node_page, gc_type);
		अगर (!err && gc_type == FG_GC)
			submitted++;
		stat_inc_node_blk_count(sbi, 1, gc_type);
	पूर्ण

	अगर (++phase < 3)
		जाओ next_step;

	अगर (fggc)
		atomic_dec(&sbi->wb_sync_req[NODE]);
	वापस submitted;
पूर्ण

/*
 * Calculate start block index indicating the given node offset.
 * Be careful, caller should give this node offset only indicating direct node
 * blocks. If any node offsets, which poपूर्णांक the other types of node blocks such
 * as indirect or द्विगुन indirect node blocks, are given, it must be a caller's
 * bug.
 */
block_t f2fs_start_bidx_of_node(अचिन्हित पूर्णांक node_ofs, काष्ठा inode *inode)
अणु
	अचिन्हित पूर्णांक indirect_blks = 2 * NIDS_PER_BLOCK + 4;
	अचिन्हित पूर्णांक bidx;

	अगर (node_ofs == 0)
		वापस 0;

	अगर (node_ofs <= 2) अणु
		bidx = node_ofs - 1;
	पूर्ण अन्यथा अगर (node_ofs <= indirect_blks) अणु
		पूर्णांक dec = (node_ofs - 4) / (NIDS_PER_BLOCK + 1);

		bidx = node_ofs - 2 - dec;
	पूर्ण अन्यथा अणु
		पूर्णांक dec = (node_ofs - indirect_blks - 3) / (NIDS_PER_BLOCK + 1);

		bidx = node_ofs - 5 - dec;
	पूर्ण
	वापस bidx * ADDRS_PER_BLOCK(inode) + ADDRS_PER_INODE(inode);
पूर्ण

अटल bool is_alive(काष्ठा f2fs_sb_info *sbi, काष्ठा f2fs_summary *sum,
		काष्ठा node_info *dni, block_t blkaddr, अचिन्हित पूर्णांक *nofs)
अणु
	काष्ठा page *node_page;
	nid_t nid;
	अचिन्हित पूर्णांक ofs_in_node;
	block_t source_blkaddr;

	nid = le32_to_cpu(sum->nid);
	ofs_in_node = le16_to_cpu(sum->ofs_in_node);

	node_page = f2fs_get_node_page(sbi, nid);
	अगर (IS_ERR(node_page))
		वापस false;

	अगर (f2fs_get_node_info(sbi, nid, dni)) अणु
		f2fs_put_page(node_page, 1);
		वापस false;
	पूर्ण

	अगर (sum->version != dni->version) अणु
		f2fs_warn(sbi, "%s: valid data with mismatched node version.",
			  __func__);
		set_sbi_flag(sbi, SBI_NEED_FSCK);
	पूर्ण

	*nofs = ofs_of_node(node_page);
	source_blkaddr = data_blkaddr(शून्य, node_page, ofs_in_node);
	f2fs_put_page(node_page, 1);

	अगर (source_blkaddr != blkaddr) अणु
#अगर_घोषित CONFIG_F2FS_CHECK_FS
		अचिन्हित पूर्णांक segno = GET_SEGNO(sbi, blkaddr);
		अचिन्हित दीर्घ offset = GET_BLKOFF_FROM_SEG0(sbi, blkaddr);

		अगर (unlikely(check_valid_map(sbi, segno, offset))) अणु
			अगर (!test_and_set_bit(segno, SIT_I(sbi)->invalid_segmap)) अणु
				f2fs_err(sbi, "mismatched blkaddr %u (source_blkaddr %u) in seg %u\n",
						blkaddr, source_blkaddr, segno);
				f2fs_bug_on(sbi, 1);
			पूर्ण
		पूर्ण
#पूर्ण_अगर
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक ra_data_block(काष्ठा inode *inode, pgoff_t index)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा dnode_of_data dn;
	काष्ठा page *page;
	काष्ठा extent_info ei = अणु0, 0, 0पूर्ण;
	काष्ठा f2fs_io_info fio = अणु
		.sbi = sbi,
		.ino = inode->i_ino,
		.type = DATA,
		.temp = COLD,
		.op = REQ_OP_READ,
		.op_flags = 0,
		.encrypted_page = शून्य,
		.in_list = false,
		.retry = false,
	पूर्ण;
	पूर्णांक err;

	page = f2fs_grab_cache_page(mapping, index, true);
	अगर (!page)
		वापस -ENOMEM;

	अगर (f2fs_lookup_extent_cache(inode, index, &ei)) अणु
		dn.data_blkaddr = ei.blk + index - ei.fofs;
		अगर (unlikely(!f2fs_is_valid_blkaddr(sbi, dn.data_blkaddr,
						DATA_GENERIC_ENHANCE_READ))) अणु
			err = -EFSCORRUPTED;
			जाओ put_page;
		पूर्ण
		जाओ got_it;
	पूर्ण

	set_new_dnode(&dn, inode, शून्य, शून्य, 0);
	err = f2fs_get_dnode_of_data(&dn, index, LOOKUP_NODE);
	अगर (err)
		जाओ put_page;
	f2fs_put_dnode(&dn);

	अगर (!__is_valid_data_blkaddr(dn.data_blkaddr)) अणु
		err = -ENOENT;
		जाओ put_page;
	पूर्ण
	अगर (unlikely(!f2fs_is_valid_blkaddr(sbi, dn.data_blkaddr,
						DATA_GENERIC_ENHANCE))) अणु
		err = -EFSCORRUPTED;
		जाओ put_page;
	पूर्ण
got_it:
	/* पढ़ो page */
	fio.page = page;
	fio.new_blkaddr = fio.old_blkaddr = dn.data_blkaddr;

	/*
	 * करोn't cache encrypted data पूर्णांकo meta inode until previous dirty
	 * data were ग_लिखोbacked to aव्योम racing between GC and flush.
	 */
	f2fs_रुको_on_page_ग_लिखोback(page, DATA, true, true);

	f2fs_रुको_on_block_ग_लिखोback(inode, dn.data_blkaddr);

	fio.encrypted_page = f2fs_pagecache_get_page(META_MAPPING(sbi),
					dn.data_blkaddr,
					FGP_LOCK | FGP_CREAT, GFP_NOFS);
	अगर (!fio.encrypted_page) अणु
		err = -ENOMEM;
		जाओ put_page;
	पूर्ण

	err = f2fs_submit_page_bio(&fio);
	अगर (err)
		जाओ put_encrypted_page;
	f2fs_put_page(fio.encrypted_page, 0);
	f2fs_put_page(page, 1);

	f2fs_update_iostat(sbi, FS_DATA_READ_IO, F2FS_BLKSIZE);
	f2fs_update_iostat(sbi, FS_GDATA_READ_IO, F2FS_BLKSIZE);

	वापस 0;
put_encrypted_page:
	f2fs_put_page(fio.encrypted_page, 1);
put_page:
	f2fs_put_page(page, 1);
	वापस err;
पूर्ण

/*
 * Move data block via META_MAPPING जबतक keeping locked data page.
 * This can be used to move blocks, aka LBAs, directly on disk.
 */
अटल पूर्णांक move_data_block(काष्ठा inode *inode, block_t bidx,
				पूर्णांक gc_type, अचिन्हित पूर्णांक segno, पूर्णांक off)
अणु
	काष्ठा f2fs_io_info fio = अणु
		.sbi = F2FS_I_SB(inode),
		.ino = inode->i_ino,
		.type = DATA,
		.temp = COLD,
		.op = REQ_OP_READ,
		.op_flags = 0,
		.encrypted_page = शून्य,
		.in_list = false,
		.retry = false,
	पूर्ण;
	काष्ठा dnode_of_data dn;
	काष्ठा f2fs_summary sum;
	काष्ठा node_info ni;
	काष्ठा page *page, *mpage;
	block_t newaddr;
	पूर्णांक err = 0;
	bool lfs_mode = f2fs_lfs_mode(fio.sbi);
	पूर्णांक type = fio.sbi->am.atgc_enabled && (gc_type == BG_GC) &&
				(fio.sbi->gc_mode != GC_URGENT_HIGH) ?
				CURSEG_ALL_DATA_ATGC : CURSEG_COLD_DATA;

	/* करो not पढ़ो out */
	page = f2fs_grab_cache_page(inode->i_mapping, bidx, false);
	अगर (!page)
		वापस -ENOMEM;

	अगर (!check_valid_map(F2FS_I_SB(inode), segno, off)) अणु
		err = -ENOENT;
		जाओ out;
	पूर्ण

	अगर (f2fs_is_atomic_file(inode)) अणु
		F2FS_I(inode)->i_gc_failures[GC_FAILURE_ATOMIC]++;
		F2FS_I_SB(inode)->skipped_atomic_files[gc_type]++;
		err = -EAGAIN;
		जाओ out;
	पूर्ण

	अगर (f2fs_is_pinned_file(inode)) अणु
		f2fs_pin_file_control(inode, true);
		err = -EAGAIN;
		जाओ out;
	पूर्ण

	set_new_dnode(&dn, inode, शून्य, शून्य, 0);
	err = f2fs_get_dnode_of_data(&dn, bidx, LOOKUP_NODE);
	अगर (err)
		जाओ out;

	अगर (unlikely(dn.data_blkaddr == शून्य_ADDR)) अणु
		ClearPageUptodate(page);
		err = -ENOENT;
		जाओ put_out;
	पूर्ण

	/*
	 * करोn't cache encrypted data पूर्णांकo meta inode until previous dirty
	 * data were ग_लिखोbacked to aव्योम racing between GC and flush.
	 */
	f2fs_रुको_on_page_ग_लिखोback(page, DATA, true, true);

	f2fs_रुको_on_block_ग_लिखोback(inode, dn.data_blkaddr);

	err = f2fs_get_node_info(fio.sbi, dn.nid, &ni);
	अगर (err)
		जाओ put_out;

	/* पढ़ो page */
	fio.page = page;
	fio.new_blkaddr = fio.old_blkaddr = dn.data_blkaddr;

	अगर (lfs_mode)
		करोwn_ग_लिखो(&fio.sbi->io_order_lock);

	mpage = f2fs_grab_cache_page(META_MAPPING(fio.sbi),
					fio.old_blkaddr, false);
	अगर (!mpage) अणु
		err = -ENOMEM;
		जाओ up_out;
	पूर्ण

	fio.encrypted_page = mpage;

	/* पढ़ो source block in mpage */
	अगर (!PageUptodate(mpage)) अणु
		err = f2fs_submit_page_bio(&fio);
		अगर (err) अणु
			f2fs_put_page(mpage, 1);
			जाओ up_out;
		पूर्ण

		f2fs_update_iostat(fio.sbi, FS_DATA_READ_IO, F2FS_BLKSIZE);
		f2fs_update_iostat(fio.sbi, FS_GDATA_READ_IO, F2FS_BLKSIZE);

		lock_page(mpage);
		अगर (unlikely(mpage->mapping != META_MAPPING(fio.sbi) ||
						!PageUptodate(mpage))) अणु
			err = -EIO;
			f2fs_put_page(mpage, 1);
			जाओ up_out;
		पूर्ण
	पूर्ण

	set_summary(&sum, dn.nid, dn.ofs_in_node, ni.version);

	/* allocate block address */
	f2fs_allocate_data_block(fio.sbi, शून्य, fio.old_blkaddr, &newaddr,
				&sum, type, शून्य);

	fio.encrypted_page = f2fs_pagecache_get_page(META_MAPPING(fio.sbi),
				newaddr, FGP_LOCK | FGP_CREAT, GFP_NOFS);
	अगर (!fio.encrypted_page) अणु
		err = -ENOMEM;
		f2fs_put_page(mpage, 1);
		जाओ recover_block;
	पूर्ण

	/* ग_लिखो target block */
	f2fs_रुको_on_page_ग_लिखोback(fio.encrypted_page, DATA, true, true);
	स_नकल(page_address(fio.encrypted_page),
				page_address(mpage), PAGE_SIZE);
	f2fs_put_page(mpage, 1);
	invalidate_mapping_pages(META_MAPPING(fio.sbi),
				fio.old_blkaddr, fio.old_blkaddr);

	set_page_dirty(fio.encrypted_page);
	अगर (clear_page_dirty_क्रम_io(fio.encrypted_page))
		dec_page_count(fio.sbi, F2FS_सूचीTY_META);

	set_page_ग_लिखोback(fio.encrypted_page);
	ClearPageError(page);

	fio.op = REQ_OP_WRITE;
	fio.op_flags = REQ_SYNC;
	fio.new_blkaddr = newaddr;
	f2fs_submit_page_ग_लिखो(&fio);
	अगर (fio.retry) अणु
		err = -EAGAIN;
		अगर (PageWriteback(fio.encrypted_page))
			end_page_ग_लिखोback(fio.encrypted_page);
		जाओ put_page_out;
	पूर्ण

	f2fs_update_iostat(fio.sbi, FS_GC_DATA_IO, F2FS_BLKSIZE);

	f2fs_update_data_blkaddr(&dn, newaddr);
	set_inode_flag(inode, FI_APPEND_WRITE);
	अगर (page->index == 0)
		set_inode_flag(inode, FI_FIRST_BLOCK_WRITTEN);
put_page_out:
	f2fs_put_page(fio.encrypted_page, 1);
recover_block:
	अगर (err)
		f2fs_करो_replace_block(fio.sbi, &sum, newaddr, fio.old_blkaddr,
							true, true, true);
up_out:
	अगर (lfs_mode)
		up_ग_लिखो(&fio.sbi->io_order_lock);
put_out:
	f2fs_put_dnode(&dn);
out:
	f2fs_put_page(page, 1);
	वापस err;
पूर्ण

अटल पूर्णांक move_data_page(काष्ठा inode *inode, block_t bidx, पूर्णांक gc_type,
							अचिन्हित पूर्णांक segno, पूर्णांक off)
अणु
	काष्ठा page *page;
	पूर्णांक err = 0;

	page = f2fs_get_lock_data_page(inode, bidx, true);
	अगर (IS_ERR(page))
		वापस PTR_ERR(page);

	अगर (!check_valid_map(F2FS_I_SB(inode), segno, off)) अणु
		err = -ENOENT;
		जाओ out;
	पूर्ण

	अगर (f2fs_is_atomic_file(inode)) अणु
		F2FS_I(inode)->i_gc_failures[GC_FAILURE_ATOMIC]++;
		F2FS_I_SB(inode)->skipped_atomic_files[gc_type]++;
		err = -EAGAIN;
		जाओ out;
	पूर्ण
	अगर (f2fs_is_pinned_file(inode)) अणु
		अगर (gc_type == FG_GC)
			f2fs_pin_file_control(inode, true);
		err = -EAGAIN;
		जाओ out;
	पूर्ण

	अगर (gc_type == BG_GC) अणु
		अगर (PageWriteback(page)) अणु
			err = -EAGAIN;
			जाओ out;
		पूर्ण
		set_page_dirty(page);
		set_cold_data(page);
	पूर्ण अन्यथा अणु
		काष्ठा f2fs_io_info fio = अणु
			.sbi = F2FS_I_SB(inode),
			.ino = inode->i_ino,
			.type = DATA,
			.temp = COLD,
			.op = REQ_OP_WRITE,
			.op_flags = REQ_SYNC,
			.old_blkaddr = शून्य_ADDR,
			.page = page,
			.encrypted_page = शून्य,
			.need_lock = LOCK_REQ,
			.io_type = FS_GC_DATA_IO,
		पूर्ण;
		bool is_dirty = PageDirty(page);

retry:
		f2fs_रुको_on_page_ग_लिखोback(page, DATA, true, true);

		set_page_dirty(page);
		अगर (clear_page_dirty_क्रम_io(page)) अणु
			inode_dec_dirty_pages(inode);
			f2fs_हटाओ_dirty_inode(inode);
		पूर्ण

		set_cold_data(page);

		err = f2fs_करो_ग_लिखो_data_page(&fio);
		अगर (err) अणु
			clear_cold_data(page);
			अगर (err == -ENOMEM) अणु
				congestion_रुको(BLK_RW_ASYNC,
						DEFAULT_IO_TIMEOUT);
				जाओ retry;
			पूर्ण
			अगर (is_dirty)
				set_page_dirty(page);
		पूर्ण
	पूर्ण
out:
	f2fs_put_page(page, 1);
	वापस err;
पूर्ण

/*
 * This function tries to get parent node of victim data block, and identअगरies
 * data block validity. If the block is valid, copy that with cold status and
 * modअगरy parent node.
 * If the parent node is not valid or the data block address is dअगरferent,
 * the victim data block is ignored.
 */
अटल पूर्णांक gc_data_segment(काष्ठा f2fs_sb_info *sbi, काष्ठा f2fs_summary *sum,
		काष्ठा gc_inode_list *gc_list, अचिन्हित पूर्णांक segno, पूर्णांक gc_type,
		bool क्रमce_migrate)
अणु
	काष्ठा super_block *sb = sbi->sb;
	काष्ठा f2fs_summary *entry;
	block_t start_addr;
	पूर्णांक off;
	पूर्णांक phase = 0;
	पूर्णांक submitted = 0;
	अचिन्हित पूर्णांक usable_blks_in_seg = f2fs_usable_blks_in_seg(sbi, segno);

	start_addr = START_BLOCK(sbi, segno);

next_step:
	entry = sum;

	क्रम (off = 0; off < usable_blks_in_seg; off++, entry++) अणु
		काष्ठा page *data_page;
		काष्ठा inode *inode;
		काष्ठा node_info dni; /* dnode info क्रम the data */
		अचिन्हित पूर्णांक ofs_in_node, nofs;
		block_t start_bidx;
		nid_t nid = le32_to_cpu(entry->nid);

		/*
		 * stop BG_GC अगर there is not enough मुक्त sections.
		 * Or, stop GC अगर the segment becomes fully valid caused by
		 * race condition aदीर्घ with SSR block allocation.
		 */
		अगर ((gc_type == BG_GC && has_not_enough_मुक्त_secs(sbi, 0, 0)) ||
			(!क्रमce_migrate && get_valid_blocks(sbi, segno, true) ==
							BLKS_PER_SEC(sbi)))
			वापस submitted;

		अगर (check_valid_map(sbi, segno, off) == 0)
			जारी;

		अगर (phase == 0) अणु
			f2fs_ra_meta_pages(sbi, NAT_BLOCK_OFFSET(nid), 1,
							META_NAT, true);
			जारी;
		पूर्ण

		अगर (phase == 1) अणु
			f2fs_ra_node_page(sbi, nid);
			जारी;
		पूर्ण

		/* Get an inode by ino with checking validity */
		अगर (!is_alive(sbi, entry, &dni, start_addr + off, &nofs))
			जारी;

		अगर (phase == 2) अणु
			f2fs_ra_node_page(sbi, dni.ino);
			जारी;
		पूर्ण

		ofs_in_node = le16_to_cpu(entry->ofs_in_node);

		अगर (phase == 3) अणु
			inode = f2fs_iget(sb, dni.ino);
			अगर (IS_ERR(inode) || is_bad_inode(inode)) अणु
				set_sbi_flag(sbi, SBI_NEED_FSCK);
				जारी;
			पूर्ण

			अगर (!करोwn_ग_लिखो_trylock(
				&F2FS_I(inode)->i_gc_rwsem[WRITE])) अणु
				iput(inode);
				sbi->skipped_gc_rwsem++;
				जारी;
			पूर्ण

			start_bidx = f2fs_start_bidx_of_node(nofs, inode) +
								ofs_in_node;

			अगर (f2fs_post_पढ़ो_required(inode)) अणु
				पूर्णांक err = ra_data_block(inode, start_bidx);

				up_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
				अगर (err) अणु
					iput(inode);
					जारी;
				पूर्ण
				add_gc_inode(gc_list, inode);
				जारी;
			पूर्ण

			data_page = f2fs_get_पढ़ो_data_page(inode,
						start_bidx, REQ_RAHEAD, true);
			up_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
			अगर (IS_ERR(data_page)) अणु
				iput(inode);
				जारी;
			पूर्ण

			f2fs_put_page(data_page, 0);
			add_gc_inode(gc_list, inode);
			जारी;
		पूर्ण

		/* phase 4 */
		inode = find_gc_inode(gc_list, dni.ino);
		अगर (inode) अणु
			काष्ठा f2fs_inode_info *fi = F2FS_I(inode);
			bool locked = false;
			पूर्णांक err;

			अगर (S_ISREG(inode->i_mode)) अणु
				अगर (!करोwn_ग_लिखो_trylock(&fi->i_gc_rwsem[READ]))
					जारी;
				अगर (!करोwn_ग_लिखो_trylock(
						&fi->i_gc_rwsem[WRITE])) अणु
					sbi->skipped_gc_rwsem++;
					up_ग_लिखो(&fi->i_gc_rwsem[READ]);
					जारी;
				पूर्ण
				locked = true;

				/* रुको क्रम all inflight aio data */
				inode_dio_रुको(inode);
			पूर्ण

			start_bidx = f2fs_start_bidx_of_node(nofs, inode)
								+ ofs_in_node;
			अगर (f2fs_post_पढ़ो_required(inode))
				err = move_data_block(inode, start_bidx,
							gc_type, segno, off);
			अन्यथा
				err = move_data_page(inode, start_bidx, gc_type,
								segno, off);

			अगर (!err && (gc_type == FG_GC ||
					f2fs_post_पढ़ो_required(inode)))
				submitted++;

			अगर (locked) अणु
				up_ग_लिखो(&fi->i_gc_rwsem[WRITE]);
				up_ग_लिखो(&fi->i_gc_rwsem[READ]);
			पूर्ण

			stat_inc_data_blk_count(sbi, 1, gc_type);
		पूर्ण
	पूर्ण

	अगर (++phase < 5)
		जाओ next_step;

	वापस submitted;
पूर्ण

अटल पूर्णांक __get_victim(काष्ठा f2fs_sb_info *sbi, अचिन्हित पूर्णांक *victim,
			पूर्णांक gc_type)
अणु
	काष्ठा sit_info *sit_i = SIT_I(sbi);
	पूर्णांक ret;

	करोwn_ग_लिखो(&sit_i->sentry_lock);
	ret = सूचीTY_I(sbi)->v_ops->get_victim(sbi, victim, gc_type,
					      NO_CHECK_TYPE, LFS, 0);
	up_ग_लिखो(&sit_i->sentry_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक करो_garbage_collect(काष्ठा f2fs_sb_info *sbi,
				अचिन्हित पूर्णांक start_segno,
				काष्ठा gc_inode_list *gc_list, पूर्णांक gc_type,
				bool क्रमce_migrate)
अणु
	काष्ठा page *sum_page;
	काष्ठा f2fs_summary_block *sum;
	काष्ठा blk_plug plug;
	अचिन्हित पूर्णांक segno = start_segno;
	अचिन्हित पूर्णांक end_segno = start_segno + sbi->segs_per_sec;
	पूर्णांक seg_मुक्तd = 0, migrated = 0;
	अचिन्हित अक्षर type = IS_DATASEG(get_seg_entry(sbi, segno)->type) ?
						SUM_TYPE_DATA : SUM_TYPE_NODE;
	पूर्णांक submitted = 0;

	अगर (__is_large_section(sbi))
		end_segno = roundकरोwn(end_segno, sbi->segs_per_sec);

	/*
	 * zone-capacity can be less than zone-size in zoned devices,
	 * resulting in less than expected usable segments in the zone,
	 * calculate the end segno in the zone which can be garbage collected
	 */
	अगर (f2fs_sb_has_blkzoned(sbi))
		end_segno -= sbi->segs_per_sec -
					f2fs_usable_segs_in_sec(sbi, segno);

	sanity_check_seg_type(sbi, get_seg_entry(sbi, segno)->type);

	/* पढ़ोahead multi ssa blocks those have contiguous address */
	अगर (__is_large_section(sbi))
		f2fs_ra_meta_pages(sbi, GET_SUM_BLOCK(sbi, segno),
					end_segno - segno, META_SSA, true);

	/* reference all summary page */
	जबतक (segno < end_segno) अणु
		sum_page = f2fs_get_sum_page(sbi, segno++);
		अगर (IS_ERR(sum_page)) अणु
			पूर्णांक err = PTR_ERR(sum_page);

			end_segno = segno - 1;
			क्रम (segno = start_segno; segno < end_segno; segno++) अणु
				sum_page = find_get_page(META_MAPPING(sbi),
						GET_SUM_BLOCK(sbi, segno));
				f2fs_put_page(sum_page, 0);
				f2fs_put_page(sum_page, 0);
			पूर्ण
			वापस err;
		पूर्ण
		unlock_page(sum_page);
	पूर्ण

	blk_start_plug(&plug);

	क्रम (segno = start_segno; segno < end_segno; segno++) अणु

		/* find segment summary of victim */
		sum_page = find_get_page(META_MAPPING(sbi),
					GET_SUM_BLOCK(sbi, segno));
		f2fs_put_page(sum_page, 0);

		अगर (get_valid_blocks(sbi, segno, false) == 0)
			जाओ मुक्तd;
		अगर (gc_type == BG_GC && __is_large_section(sbi) &&
				migrated >= sbi->migration_granularity)
			जाओ skip;
		अगर (!PageUptodate(sum_page) || unlikely(f2fs_cp_error(sbi)))
			जाओ skip;

		sum = page_address(sum_page);
		अगर (type != GET_SUM_TYPE((&sum->footer))) अणु
			f2fs_err(sbi, "Inconsistent segment (%u) type [%d, %d] in SSA and SIT",
				 segno, type, GET_SUM_TYPE((&sum->footer)));
			set_sbi_flag(sbi, SBI_NEED_FSCK);
			f2fs_stop_checkpoपूर्णांक(sbi, false);
			जाओ skip;
		पूर्ण

		/*
		 * this is to aव्योम deadlock:
		 * - lock_page(sum_page)         - f2fs_replace_block
		 *  - check_valid_map()            - करोwn_ग_लिखो(sentry_lock)
		 *   - करोwn_पढ़ो(sentry_lock)     - change_curseg()
		 *                                  - lock_page(sum_page)
		 */
		अगर (type == SUM_TYPE_NODE)
			submitted += gc_node_segment(sbi, sum->entries, segno,
								gc_type);
		अन्यथा
			submitted += gc_data_segment(sbi, sum->entries, gc_list,
							segno, gc_type,
							क्रमce_migrate);

		stat_inc_seg_count(sbi, type, gc_type);
		migrated++;

मुक्तd:
		अगर (gc_type == FG_GC &&
				get_valid_blocks(sbi, segno, false) == 0)
			seg_मुक्तd++;

		अगर (__is_large_section(sbi) && segno + 1 < end_segno)
			sbi->next_victim_seg[gc_type] = segno + 1;
skip:
		f2fs_put_page(sum_page, 0);
	पूर्ण

	अगर (submitted)
		f2fs_submit_merged_ग_लिखो(sbi,
				(type == SUM_TYPE_NODE) ? NODE : DATA);

	blk_finish_plug(&plug);

	stat_inc_call_count(sbi->stat_info);

	वापस seg_मुक्तd;
पूर्ण

पूर्णांक f2fs_gc(काष्ठा f2fs_sb_info *sbi, bool sync,
			bool background, bool क्रमce, अचिन्हित पूर्णांक segno)
अणु
	पूर्णांक gc_type = sync ? FG_GC : BG_GC;
	पूर्णांक sec_मुक्तd = 0, seg_मुक्तd = 0, total_मुक्तd = 0;
	पूर्णांक ret = 0;
	काष्ठा cp_control cpc;
	अचिन्हित पूर्णांक init_segno = segno;
	काष्ठा gc_inode_list gc_list = अणु
		.ilist = LIST_HEAD_INIT(gc_list.ilist),
		.iroot = RADIX_TREE_INIT(gc_list.iroot, GFP_NOFS),
	पूर्ण;
	अचिन्हित दीर्घ दीर्घ last_skipped = sbi->skipped_atomic_files[FG_GC];
	अचिन्हित दीर्घ दीर्घ first_skipped;
	अचिन्हित पूर्णांक skipped_round = 0, round = 0;

	trace_f2fs_gc_begin(sbi->sb, sync, background,
				get_pages(sbi, F2FS_सूचीTY_NODES),
				get_pages(sbi, F2FS_सूचीTY_DENTS),
				get_pages(sbi, F2FS_सूचीTY_IMETA),
				मुक्त_sections(sbi),
				मुक्त_segments(sbi),
				reserved_segments(sbi),
				preमुक्त_segments(sbi));

	cpc.reason = __get_cp_reason(sbi);
	sbi->skipped_gc_rwsem = 0;
	first_skipped = last_skipped;
gc_more:
	अगर (unlikely(!(sbi->sb->s_flags & SB_ACTIVE))) अणु
		ret = -EINVAL;
		जाओ stop;
	पूर्ण
	अगर (unlikely(f2fs_cp_error(sbi))) अणु
		ret = -EIO;
		जाओ stop;
	पूर्ण

	अगर (gc_type == BG_GC && has_not_enough_मुक्त_secs(sbi, 0, 0)) अणु
		/*
		 * For example, अगर there are many preमुक्त_segments below given
		 * threshold, we can make them मुक्त by checkpoपूर्णांक. Then, we
		 * secure मुक्त segments which करोesn't need fggc any more.
		 */
		अगर (preमुक्त_segments(sbi) &&
				!is_sbi_flag_set(sbi, SBI_CP_DISABLED)) अणु
			ret = f2fs_ग_लिखो_checkpoपूर्णांक(sbi, &cpc);
			अगर (ret)
				जाओ stop;
		पूर्ण
		अगर (has_not_enough_मुक्त_secs(sbi, 0, 0))
			gc_type = FG_GC;
	पूर्ण

	/* f2fs_balance_fs करोesn't need to करो BG_GC in critical path. */
	अगर (gc_type == BG_GC && !background) अणु
		ret = -EINVAL;
		जाओ stop;
	पूर्ण
	ret = __get_victim(sbi, &segno, gc_type);
	अगर (ret)
		जाओ stop;

	seg_मुक्तd = करो_garbage_collect(sbi, segno, &gc_list, gc_type, क्रमce);
	अगर (gc_type == FG_GC &&
		seg_मुक्तd == f2fs_usable_segs_in_sec(sbi, segno))
		sec_मुक्तd++;
	total_मुक्तd += seg_मुक्तd;

	अगर (gc_type == FG_GC) अणु
		अगर (sbi->skipped_atomic_files[FG_GC] > last_skipped ||
						sbi->skipped_gc_rwsem)
			skipped_round++;
		last_skipped = sbi->skipped_atomic_files[FG_GC];
		round++;
	पूर्ण

	अगर (gc_type == FG_GC && seg_मुक्तd)
		sbi->cur_victim_sec = शून्य_SEGNO;

	अगर (sync)
		जाओ stop;

	अगर (has_not_enough_मुक्त_secs(sbi, sec_मुक्तd, 0)) अणु
		अगर (skipped_round <= MAX_SKIP_GC_COUNT ||
					skipped_round * 2 < round) अणु
			segno = शून्य_SEGNO;
			जाओ gc_more;
		पूर्ण

		अगर (first_skipped < last_skipped &&
				(last_skipped - first_skipped) >
						sbi->skipped_gc_rwsem) अणु
			f2fs_drop_inmem_pages_all(sbi, true);
			segno = शून्य_SEGNO;
			जाओ gc_more;
		पूर्ण
		अगर (gc_type == FG_GC && !is_sbi_flag_set(sbi, SBI_CP_DISABLED))
			ret = f2fs_ग_लिखो_checkpoपूर्णांक(sbi, &cpc);
	पूर्ण
stop:
	SIT_I(sbi)->last_victim[ALLOC_NEXT] = 0;
	SIT_I(sbi)->last_victim[FLUSH_DEVICE] = init_segno;

	trace_f2fs_gc_end(sbi->sb, ret, total_मुक्तd, sec_मुक्तd,
				get_pages(sbi, F2FS_सूचीTY_NODES),
				get_pages(sbi, F2FS_सूचीTY_DENTS),
				get_pages(sbi, F2FS_सूचीTY_IMETA),
				मुक्त_sections(sbi),
				मुक्त_segments(sbi),
				reserved_segments(sbi),
				preमुक्त_segments(sbi));

	up_ग_लिखो(&sbi->gc_lock);

	put_gc_inode(&gc_list);

	अगर (sync && !ret)
		ret = sec_मुक्तd ? 0 : -EAGAIN;
	वापस ret;
पूर्ण

पूर्णांक __init f2fs_create_garbage_collection_cache(व्योम)
अणु
	victim_entry_slab = f2fs_kmem_cache_create("f2fs_victim_entry",
					माप(काष्ठा victim_entry));
	अगर (!victim_entry_slab)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम f2fs_destroy_garbage_collection_cache(व्योम)
अणु
	kmem_cache_destroy(victim_entry_slab);
पूर्ण

अटल व्योम init_atgc_management(काष्ठा f2fs_sb_info *sbi)
अणु
	काष्ठा atgc_management *am = &sbi->am;

	अगर (test_opt(sbi, ATGC) &&
		SIT_I(sbi)->elapsed_समय >= DEF_GC_THREAD_AGE_THRESHOLD)
		am->atgc_enabled = true;

	am->root = RB_ROOT_CACHED;
	INIT_LIST_HEAD(&am->victim_list);
	am->victim_count = 0;

	am->candidate_ratio = DEF_GC_THREAD_CANDIDATE_RATIO;
	am->max_candidate_count = DEF_GC_THREAD_MAX_CANDIDATE_COUNT;
	am->age_weight = DEF_GC_THREAD_AGE_WEIGHT;
पूर्ण

व्योम f2fs_build_gc_manager(काष्ठा f2fs_sb_info *sbi)
अणु
	सूचीTY_I(sbi)->v_ops = &शेष_v_ops;

	sbi->gc_pin_file_threshold = DEF_GC_FAILED_PINNED_खाताS;

	/* give warm/cold data area from slower device */
	अगर (f2fs_is_multi_device(sbi) && !__is_large_section(sbi))
		SIT_I(sbi)->last_victim[ALLOC_NEXT] =
				GET_SEGNO(sbi, FDEV(0).end_blk) + 1;

	init_atgc_management(sbi);
पूर्ण

अटल पूर्णांक मुक्त_segment_range(काष्ठा f2fs_sb_info *sbi,
				अचिन्हित पूर्णांक secs, bool gc_only)
अणु
	अचिन्हित पूर्णांक segno, next_inuse, start, end;
	काष्ठा cp_control cpc = अणु CP_RESIZE, 0, 0, 0 पूर्ण;
	पूर्णांक gc_mode, gc_type;
	पूर्णांक err = 0;
	पूर्णांक type;

	/* Force block allocation क्रम GC */
	MAIN_SECS(sbi) -= secs;
	start = MAIN_SECS(sbi) * sbi->segs_per_sec;
	end = MAIN_SEGS(sbi) - 1;

	mutex_lock(&सूचीTY_I(sbi)->seglist_lock);
	क्रम (gc_mode = 0; gc_mode < MAX_GC_POLICY; gc_mode++)
		अगर (SIT_I(sbi)->last_victim[gc_mode] >= start)
			SIT_I(sbi)->last_victim[gc_mode] = 0;

	क्रम (gc_type = BG_GC; gc_type <= FG_GC; gc_type++)
		अगर (sbi->next_victim_seg[gc_type] >= start)
			sbi->next_victim_seg[gc_type] = शून्य_SEGNO;
	mutex_unlock(&सूचीTY_I(sbi)->seglist_lock);

	/* Move out cursegs from the target range */
	क्रम (type = CURSEG_HOT_DATA; type < NR_CURSEG_PERSIST_TYPE; type++)
		f2fs_allocate_segment_क्रम_resize(sbi, type, start, end);

	/* करो GC to move out valid blocks in the range */
	क्रम (segno = start; segno <= end; segno += sbi->segs_per_sec) अणु
		काष्ठा gc_inode_list gc_list = अणु
			.ilist = LIST_HEAD_INIT(gc_list.ilist),
			.iroot = RADIX_TREE_INIT(gc_list.iroot, GFP_NOFS),
		पूर्ण;

		करो_garbage_collect(sbi, segno, &gc_list, FG_GC, true);
		put_gc_inode(&gc_list);

		अगर (!gc_only && get_valid_blocks(sbi, segno, true)) अणु
			err = -EAGAIN;
			जाओ out;
		पूर्ण
		अगर (fatal_संकेत_pending(current)) अणु
			err = -ERESTARTSYS;
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (gc_only)
		जाओ out;

	err = f2fs_ग_लिखो_checkpoपूर्णांक(sbi, &cpc);
	अगर (err)
		जाओ out;

	next_inuse = find_next_inuse(FREE_I(sbi), end + 1, start);
	अगर (next_inuse <= end) अणु
		f2fs_err(sbi, "segno %u should be free but still inuse!",
			 next_inuse);
		f2fs_bug_on(sbi, 1);
	पूर्ण
out:
	MAIN_SECS(sbi) += secs;
	वापस err;
पूर्ण

अटल व्योम update_sb_metadata(काष्ठा f2fs_sb_info *sbi, पूर्णांक secs)
अणु
	काष्ठा f2fs_super_block *raw_sb = F2FS_RAW_SUPER(sbi);
	पूर्णांक section_count;
	पूर्णांक segment_count;
	पूर्णांक segment_count_मुख्य;
	दीर्घ दीर्घ block_count;
	पूर्णांक segs = secs * sbi->segs_per_sec;

	करोwn_ग_लिखो(&sbi->sb_lock);

	section_count = le32_to_cpu(raw_sb->section_count);
	segment_count = le32_to_cpu(raw_sb->segment_count);
	segment_count_मुख्य = le32_to_cpu(raw_sb->segment_count_मुख्य);
	block_count = le64_to_cpu(raw_sb->block_count);

	raw_sb->section_count = cpu_to_le32(section_count + secs);
	raw_sb->segment_count = cpu_to_le32(segment_count + segs);
	raw_sb->segment_count_मुख्य = cpu_to_le32(segment_count_मुख्य + segs);
	raw_sb->block_count = cpu_to_le64(block_count +
					(दीर्घ दीर्घ)segs * sbi->blocks_per_seg);
	अगर (f2fs_is_multi_device(sbi)) अणु
		पूर्णांक last_dev = sbi->s_ndevs - 1;
		पूर्णांक dev_segs =
			le32_to_cpu(raw_sb->devs[last_dev].total_segments);

		raw_sb->devs[last_dev].total_segments =
						cpu_to_le32(dev_segs + segs);
	पूर्ण

	up_ग_लिखो(&sbi->sb_lock);
पूर्ण

अटल व्योम update_fs_metadata(काष्ठा f2fs_sb_info *sbi, पूर्णांक secs)
अणु
	पूर्णांक segs = secs * sbi->segs_per_sec;
	दीर्घ दीर्घ blks = (दीर्घ दीर्घ)segs * sbi->blocks_per_seg;
	दीर्घ दीर्घ user_block_count =
				le64_to_cpu(F2FS_CKPT(sbi)->user_block_count);

	SM_I(sbi)->segment_count = (पूर्णांक)SM_I(sbi)->segment_count + segs;
	MAIN_SEGS(sbi) = (पूर्णांक)MAIN_SEGS(sbi) + segs;
	MAIN_SECS(sbi) += secs;
	FREE_I(sbi)->मुक्त_sections = (पूर्णांक)FREE_I(sbi)->मुक्त_sections + secs;
	FREE_I(sbi)->मुक्त_segments = (पूर्णांक)FREE_I(sbi)->मुक्त_segments + segs;
	F2FS_CKPT(sbi)->user_block_count = cpu_to_le64(user_block_count + blks);

	अगर (f2fs_is_multi_device(sbi)) अणु
		पूर्णांक last_dev = sbi->s_ndevs - 1;

		FDEV(last_dev).total_segments =
				(पूर्णांक)FDEV(last_dev).total_segments + segs;
		FDEV(last_dev).end_blk =
				(दीर्घ दीर्घ)FDEV(last_dev).end_blk + blks;
#अगर_घोषित CONFIG_BLK_DEV_ZONED
		FDEV(last_dev).nr_blkz = (पूर्णांक)FDEV(last_dev).nr_blkz +
					(पूर्णांक)(blks >> sbi->log_blocks_per_blkz);
#पूर्ण_अगर
	पूर्ण
पूर्ण

पूर्णांक f2fs_resize_fs(काष्ठा f2fs_sb_info *sbi, __u64 block_count)
अणु
	__u64 old_block_count, shrunk_blocks;
	काष्ठा cp_control cpc = अणु CP_RESIZE, 0, 0, 0 पूर्ण;
	अचिन्हित पूर्णांक secs;
	पूर्णांक err = 0;
	__u32 rem;

	old_block_count = le64_to_cpu(F2FS_RAW_SUPER(sbi)->block_count);
	अगर (block_count > old_block_count)
		वापस -EINVAL;

	अगर (f2fs_is_multi_device(sbi)) अणु
		पूर्णांक last_dev = sbi->s_ndevs - 1;
		__u64 last_segs = FDEV(last_dev).total_segments;

		अगर (block_count + last_segs * sbi->blocks_per_seg <=
								old_block_count)
			वापस -EINVAL;
	पूर्ण

	/* new fs size should align to section size */
	भाग_u64_rem(block_count, BLKS_PER_SEC(sbi), &rem);
	अगर (rem)
		वापस -EINVAL;

	अगर (block_count == old_block_count)
		वापस 0;

	अगर (is_sbi_flag_set(sbi, SBI_NEED_FSCK)) अणु
		f2fs_err(sbi, "Should run fsck to repair first.");
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर (test_opt(sbi, DISABLE_CHECKPOINT)) अणु
		f2fs_err(sbi, "Checkpoint should be enabled.");
		वापस -EINVAL;
	पूर्ण

	shrunk_blocks = old_block_count - block_count;
	secs = भाग_u64(shrunk_blocks, BLKS_PER_SEC(sbi));

	/* stop other GC */
	अगर (!करोwn_ग_लिखो_trylock(&sbi->gc_lock))
		वापस -EAGAIN;

	/* stop CP to protect MAIN_SEC in मुक्त_segment_range */
	f2fs_lock_op(sbi);

	spin_lock(&sbi->stat_lock);
	अगर (shrunk_blocks + valid_user_blocks(sbi) +
		sbi->current_reserved_blocks + sbi->unusable_block_count +
		F2FS_OPTION(sbi).root_reserved_blocks > sbi->user_block_count)
		err = -ENOSPC;
	spin_unlock(&sbi->stat_lock);

	अगर (err)
		जाओ out_unlock;

	err = मुक्त_segment_range(sbi, secs, true);

out_unlock:
	f2fs_unlock_op(sbi);
	up_ग_लिखो(&sbi->gc_lock);
	अगर (err)
		वापस err;

	set_sbi_flag(sbi, SBI_IS_RESIZEFS);

	मुक्तze_super(sbi->sb);
	करोwn_ग_लिखो(&sbi->gc_lock);
	करोwn_ग_लिखो(&sbi->cp_global_sem);

	spin_lock(&sbi->stat_lock);
	अगर (shrunk_blocks + valid_user_blocks(sbi) +
		sbi->current_reserved_blocks + sbi->unusable_block_count +
		F2FS_OPTION(sbi).root_reserved_blocks > sbi->user_block_count)
		err = -ENOSPC;
	अन्यथा
		sbi->user_block_count -= shrunk_blocks;
	spin_unlock(&sbi->stat_lock);
	अगर (err)
		जाओ out_err;

	err = मुक्त_segment_range(sbi, secs, false);
	अगर (err)
		जाओ recover_out;

	update_sb_metadata(sbi, -secs);

	err = f2fs_commit_super(sbi, false);
	अगर (err) अणु
		update_sb_metadata(sbi, secs);
		जाओ recover_out;
	पूर्ण

	update_fs_metadata(sbi, -secs);
	clear_sbi_flag(sbi, SBI_IS_RESIZEFS);
	set_sbi_flag(sbi, SBI_IS_सूचीTY);

	err = f2fs_ग_लिखो_checkpoपूर्णांक(sbi, &cpc);
	अगर (err) अणु
		update_fs_metadata(sbi, secs);
		update_sb_metadata(sbi, secs);
		f2fs_commit_super(sbi, false);
	पूर्ण
recover_out:
	अगर (err) अणु
		set_sbi_flag(sbi, SBI_NEED_FSCK);
		f2fs_err(sbi, "resize_fs failed, should run fsck to repair!");

		spin_lock(&sbi->stat_lock);
		sbi->user_block_count += shrunk_blocks;
		spin_unlock(&sbi->stat_lock);
	पूर्ण
out_err:
	up_ग_लिखो(&sbi->cp_global_sem);
	up_ग_लिखो(&sbi->gc_lock);
	thaw_super(sbi->sb);
	clear_sbi_flag(sbi, SBI_IS_RESIZEFS);
	वापस err;
पूर्ण
