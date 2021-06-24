<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2016 CNEX Lअसल
 * Initial release: Javier Gonzalez <javier@cnexद_असल.com>
 *                  Matias Bjorling <matias@cnexद_असल.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * pblk-gc.c - pblk's garbage collector
 */

#समावेश "pblk.h"
#समावेश "pblk-trace.h"
#समावेश <linux/delay.h>


अटल व्योम pblk_gc_मुक्त_gc_rq(काष्ठा pblk_gc_rq *gc_rq)
अणु
	vमुक्त(gc_rq->data);
	kमुक्त(gc_rq);
पूर्ण

अटल पूर्णांक pblk_gc_ग_लिखो(काष्ठा pblk *pblk)
अणु
	काष्ठा pblk_gc *gc = &pblk->gc;
	काष्ठा pblk_gc_rq *gc_rq, *tgc_rq;
	LIST_HEAD(w_list);

	spin_lock(&gc->w_lock);
	अगर (list_empty(&gc->w_list)) अणु
		spin_unlock(&gc->w_lock);
		वापस 1;
	पूर्ण

	list_cut_position(&w_list, &gc->w_list, gc->w_list.prev);
	gc->w_entries = 0;
	spin_unlock(&gc->w_lock);

	list_क्रम_each_entry_safe(gc_rq, tgc_rq, &w_list, list) अणु
		pblk_ग_लिखो_gc_to_cache(pblk, gc_rq);
		list_del(&gc_rq->list);
		kref_put(&gc_rq->line->ref, pblk_line_put);
		pblk_gc_मुक्त_gc_rq(gc_rq);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pblk_gc_ग_लिखोr_kick(काष्ठा pblk_gc *gc)
अणु
	wake_up_process(gc->gc_ग_लिखोr_ts);
पूर्ण

व्योम pblk_put_line_back(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा list_head *move_list;

	spin_lock(&l_mg->gc_lock);
	spin_lock(&line->lock);
	WARN_ON(line->state != PBLK_LINESTATE_GC);
	line->state = PBLK_LINESTATE_CLOSED;
	trace_pblk_line_state(pblk_disk_name(pblk), line->id,
					line->state);

	/* We need to reset gc_group in order to ensure that
	 * pblk_line_gc_list will वापस proper move_list
	 * since right now current line is not on any of the
	 * gc lists.
	 */
	line->gc_group = PBLK_LINEGC_NONE;
	move_list = pblk_line_gc_list(pblk, line);
	spin_unlock(&line->lock);
	list_add_tail(&line->list, move_list);
	spin_unlock(&l_mg->gc_lock);
पूर्ण

अटल व्योम pblk_gc_line_ws(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pblk_line_ws *gc_rq_ws = container_of(work,
						काष्ठा pblk_line_ws, ws);
	काष्ठा pblk *pblk = gc_rq_ws->pblk;
	काष्ठा pblk_gc *gc = &pblk->gc;
	काष्ठा pblk_line *line = gc_rq_ws->line;
	काष्ठा pblk_gc_rq *gc_rq = gc_rq_ws->priv;
	पूर्णांक ret;

	up(&gc->gc_sem);

	/* Read from GC victim block */
	ret = pblk_submit_पढ़ो_gc(pblk, gc_rq);
	अगर (ret) अणु
		line->w_err_gc->has_gc_err = 1;
		जाओ out;
	पूर्ण

	अगर (!gc_rq->secs_to_gc)
		जाओ out;

retry:
	spin_lock(&gc->w_lock);
	अगर (gc->w_entries >= PBLK_GC_RQ_QD) अणु
		spin_unlock(&gc->w_lock);
		pblk_gc_ग_लिखोr_kick(&pblk->gc);
		usleep_range(128, 256);
		जाओ retry;
	पूर्ण
	gc->w_entries++;
	list_add_tail(&gc_rq->list, &gc->w_list);
	spin_unlock(&gc->w_lock);

	pblk_gc_ग_लिखोr_kick(&pblk->gc);

	kमुक्त(gc_rq_ws);
	वापस;

out:
	pblk_gc_मुक्त_gc_rq(gc_rq);
	kref_put(&line->ref, pblk_line_put);
	kमुक्त(gc_rq_ws);
पूर्ण

अटल __le64 *get_lba_list_from_emeta(काष्ठा pblk *pblk,
				       काष्ठा pblk_line *line)
अणु
	काष्ठा line_emeta *emeta_buf;
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	अचिन्हित पूर्णांक lba_list_size = lm->emeta_len[2];
	__le64 *lba_list;
	पूर्णांक ret;

	emeta_buf = kvदो_स्मृति(lm->emeta_len[0], GFP_KERNEL);
	अगर (!emeta_buf)
		वापस शून्य;

	ret = pblk_line_emeta_पढ़ो(pblk, line, emeta_buf);
	अगर (ret) अणु
		pblk_err(pblk, "line %d read emeta failed (%d)\n",
				line->id, ret);
		kvमुक्त(emeta_buf);
		वापस शून्य;
	पूर्ण

	/* If this पढ़ो fails, it means that emeta is corrupted.
	 * For now, leave the line untouched.
	 * TODO: Implement a recovery routine that scans and moves
	 * all sectors on the line.
	 */

	ret = pblk_recov_check_emeta(pblk, emeta_buf);
	अगर (ret) अणु
		pblk_err(pblk, "inconsistent emeta (line %d)\n",
				line->id);
		kvमुक्त(emeta_buf);
		वापस शून्य;
	पूर्ण

	lba_list = kvदो_स्मृति(lba_list_size, GFP_KERNEL);

	अगर (lba_list)
		स_नकल(lba_list, emeta_to_lbas(pblk, emeta_buf), lba_list_size);

	kvमुक्त(emeta_buf);

	वापस lba_list;
पूर्ण

अटल व्योम pblk_gc_line_prepare_ws(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pblk_line_ws *line_ws = container_of(work, काष्ठा pblk_line_ws,
									ws);
	काष्ठा pblk *pblk = line_ws->pblk;
	काष्ठा pblk_line *line = line_ws->line;
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा pblk_gc *gc = &pblk->gc;
	काष्ठा pblk_line_ws *gc_rq_ws;
	काष्ठा pblk_gc_rq *gc_rq;
	__le64 *lba_list;
	अचिन्हित दीर्घ *invalid_biपंचांगap;
	पूर्णांक sec_left, nr_secs, bit;

	invalid_biपंचांगap = kदो_स्मृति(lm->sec_biपंचांगap_len, GFP_KERNEL);
	अगर (!invalid_biपंचांगap)
		जाओ fail_मुक्त_ws;

	अगर (line->w_err_gc->has_ग_लिखो_err) अणु
		lba_list = line->w_err_gc->lba_list;
		line->w_err_gc->lba_list = शून्य;
	पूर्ण अन्यथा अणु
		lba_list = get_lba_list_from_emeta(pblk, line);
		अगर (!lba_list) अणु
			pblk_err(pblk, "could not interpret emeta (line %d)\n",
					line->id);
			जाओ fail_मुक्त_invalid_biपंचांगap;
		पूर्ण
	पूर्ण

	spin_lock(&line->lock);
	biपंचांगap_copy(invalid_biपंचांगap, line->invalid_biपंचांगap, lm->sec_per_line);
	sec_left = pblk_line_vsc(line);
	spin_unlock(&line->lock);

	अगर (sec_left < 0) अणु
		pblk_err(pblk, "corrupted GC line (%d)\n", line->id);
		जाओ fail_मुक्त_lba_list;
	पूर्ण

	bit = -1;
next_rq:
	gc_rq = kदो_स्मृति(माप(काष्ठा pblk_gc_rq), GFP_KERNEL);
	अगर (!gc_rq)
		जाओ fail_मुक्त_lba_list;

	nr_secs = 0;
	करो अणु
		bit = find_next_zero_bit(invalid_biपंचांगap, lm->sec_per_line,
								bit + 1);
		अगर (bit > line->emeta_ssec)
			अवरोध;

		gc_rq->paddr_list[nr_secs] = bit;
		gc_rq->lba_list[nr_secs++] = le64_to_cpu(lba_list[bit]);
	पूर्ण जबतक (nr_secs < pblk->max_ग_लिखो_pgs);

	अगर (unlikely(!nr_secs)) अणु
		kमुक्त(gc_rq);
		जाओ out;
	पूर्ण

	gc_rq->nr_secs = nr_secs;
	gc_rq->line = line;

	gc_rq->data = vदो_स्मृति(array_size(gc_rq->nr_secs, geo->csecs));
	अगर (!gc_rq->data)
		जाओ fail_मुक्त_gc_rq;

	gc_rq_ws = kदो_स्मृति(माप(काष्ठा pblk_line_ws), GFP_KERNEL);
	अगर (!gc_rq_ws)
		जाओ fail_मुक्त_gc_data;

	gc_rq_ws->pblk = pblk;
	gc_rq_ws->line = line;
	gc_rq_ws->priv = gc_rq;

	/* The ग_लिखो GC path can be much slower than the पढ़ो GC one due to
	 * the budget imposed by the rate-limiter. Balance in हाल that we get
	 * back pressure from the ग_लिखो GC path.
	 */
	जबतक (करोwn_समयout(&gc->gc_sem, msecs_to_jअगरfies(30000)))
		io_schedule();

	kref_get(&line->ref);

	INIT_WORK(&gc_rq_ws->ws, pblk_gc_line_ws);
	queue_work(gc->gc_line_पढ़ोer_wq, &gc_rq_ws->ws);

	sec_left -= nr_secs;
	अगर (sec_left > 0)
		जाओ next_rq;

out:
	kvमुक्त(lba_list);
	kमुक्त(line_ws);
	kमुक्त(invalid_biपंचांगap);

	kref_put(&line->ref, pblk_line_put);
	atomic_dec(&gc->पढ़ो_inflight_gc);

	वापस;

fail_मुक्त_gc_data:
	vमुक्त(gc_rq->data);
fail_मुक्त_gc_rq:
	kमुक्त(gc_rq);
fail_मुक्त_lba_list:
	kvमुक्त(lba_list);
fail_मुक्त_invalid_biपंचांगap:
	kमुक्त(invalid_biपंचांगap);
fail_मुक्त_ws:
	kमुक्त(line_ws);

	/* Line goes back to बंदd state, so we cannot release additional
	 * reference क्रम line, since we करो that only when we want to करो
	 * gc to मुक्त line state transition.
	 */
	pblk_put_line_back(pblk, line);
	atomic_dec(&gc->पढ़ो_inflight_gc);

	pblk_err(pblk, "failed to GC line %d\n", line->id);
पूर्ण

अटल पूर्णांक pblk_gc_line(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	काष्ठा pblk_gc *gc = &pblk->gc;
	काष्ठा pblk_line_ws *line_ws;

	pblk_debug(pblk, "line '%d' being reclaimed for GC\n", line->id);

	line_ws = kदो_स्मृति(माप(काष्ठा pblk_line_ws), GFP_KERNEL);
	अगर (!line_ws)
		वापस -ENOMEM;

	line_ws->pblk = pblk;
	line_ws->line = line;

	atomic_inc(&gc->pipeline_gc);
	INIT_WORK(&line_ws->ws, pblk_gc_line_prepare_ws);
	queue_work(gc->gc_पढ़ोer_wq, &line_ws->ws);

	वापस 0;
पूर्ण

अटल व्योम pblk_gc_पढ़ोer_kick(काष्ठा pblk_gc *gc)
अणु
	wake_up_process(gc->gc_पढ़ोer_ts);
पूर्ण

अटल व्योम pblk_gc_kick(काष्ठा pblk *pblk)
अणु
	काष्ठा pblk_gc *gc = &pblk->gc;

	pblk_gc_ग_लिखोr_kick(gc);
	pblk_gc_पढ़ोer_kick(gc);

	/* If we're shutting down GC, let's not start it up again */
	अगर (gc->gc_enabled) अणु
		wake_up_process(gc->gc_ts);
		mod_समयr(&gc->gc_समयr,
			  jअगरfies + msecs_to_jअगरfies(GC_TIME_MSECS));
	पूर्ण
पूर्ण

अटल पूर्णांक pblk_gc_पढ़ो(काष्ठा pblk *pblk)
अणु
	काष्ठा pblk_gc *gc = &pblk->gc;
	काष्ठा pblk_line *line;

	spin_lock(&gc->r_lock);
	अगर (list_empty(&gc->r_list)) अणु
		spin_unlock(&gc->r_lock);
		वापस 1;
	पूर्ण

	line = list_first_entry(&gc->r_list, काष्ठा pblk_line, list);
	list_del(&line->list);
	spin_unlock(&gc->r_lock);

	pblk_gc_kick(pblk);

	अगर (pblk_gc_line(pblk, line)) अणु
		pblk_err(pblk, "failed to GC line %d\n", line->id);
		/* rollback */
		spin_lock(&gc->r_lock);
		list_add_tail(&line->list, &gc->r_list);
		spin_unlock(&gc->r_lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा pblk_line *pblk_gc_get_victim_line(काष्ठा pblk *pblk,
						 काष्ठा list_head *group_list)
अणु
	काष्ठा pblk_line *line, *victim;
	अचिन्हित पूर्णांक line_vsc = ~0x0L, victim_vsc = ~0x0L;

	victim = list_first_entry(group_list, काष्ठा pblk_line, list);

	list_क्रम_each_entry(line, group_list, list) अणु
		अगर (!atomic_पढ़ो(&line->sec_to_update))
			line_vsc = le32_to_cpu(*line->vsc);
		अगर (line_vsc < victim_vsc) अणु
			victim = line;
			victim_vsc = le32_to_cpu(*victim->vsc);
		पूर्ण
	पूर्ण

	अगर (victim_vsc == ~0x0)
		वापस शून्य;

	वापस victim;
पूर्ण

अटल bool pblk_gc_should_run(काष्ठा pblk_gc *gc, काष्ठा pblk_rl *rl)
अणु
	अचिन्हित पूर्णांक nr_blocks_मुक्त, nr_blocks_need;
	अचिन्हित पूर्णांक werr_lines = atomic_पढ़ो(&rl->werr_lines);

	nr_blocks_need = pblk_rl_high_thrs(rl);
	nr_blocks_मुक्त = pblk_rl_nr_मुक्त_blks(rl);

	/* This is not critical, no need to take lock here */
	वापस ((werr_lines > 0) ||
		((gc->gc_active) && (nr_blocks_need > nr_blocks_मुक्त)));
पूर्ण

व्योम pblk_gc_मुक्त_full_lines(काष्ठा pblk *pblk)
अणु
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा pblk_gc *gc = &pblk->gc;
	काष्ठा pblk_line *line;

	करो अणु
		spin_lock(&l_mg->gc_lock);
		अगर (list_empty(&l_mg->gc_full_list)) अणु
			spin_unlock(&l_mg->gc_lock);
			वापस;
		पूर्ण

		line = list_first_entry(&l_mg->gc_full_list,
							काष्ठा pblk_line, list);

		spin_lock(&line->lock);
		WARN_ON(line->state != PBLK_LINESTATE_CLOSED);
		line->state = PBLK_LINESTATE_GC;
		trace_pblk_line_state(pblk_disk_name(pblk), line->id,
					line->state);
		spin_unlock(&line->lock);

		list_del(&line->list);
		spin_unlock(&l_mg->gc_lock);

		atomic_inc(&gc->pipeline_gc);
		kref_put(&line->ref, pblk_line_put);
	पूर्ण जबतक (1);
पूर्ण

/*
 * Lines with no valid sectors will be वापसed to the मुक्त list immediately. If
 * GC is activated - either because the मुक्त block count is under the determined
 * threshold, or because it is being क्रमced from user space - only lines with a
 * high count of invalid sectors will be recycled.
 */
अटल व्योम pblk_gc_run(काष्ठा pblk *pblk)
अणु
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा pblk_gc *gc = &pblk->gc;
	काष्ठा pblk_line *line;
	काष्ठा list_head *group_list;
	bool run_gc;
	पूर्णांक पढ़ो_inflight_gc, gc_group = 0, prev_group = 0;

	pblk_gc_मुक्त_full_lines(pblk);

	run_gc = pblk_gc_should_run(&pblk->gc, &pblk->rl);
	अगर (!run_gc || (atomic_पढ़ो(&gc->पढ़ो_inflight_gc) >= PBLK_GC_L_QD))
		वापस;

next_gc_group:
	group_list = l_mg->gc_lists[gc_group++];

	करो अणु
		spin_lock(&l_mg->gc_lock);

		line = pblk_gc_get_victim_line(pblk, group_list);
		अगर (!line) अणु
			spin_unlock(&l_mg->gc_lock);
			अवरोध;
		पूर्ण

		spin_lock(&line->lock);
		WARN_ON(line->state != PBLK_LINESTATE_CLOSED);
		line->state = PBLK_LINESTATE_GC;
		trace_pblk_line_state(pblk_disk_name(pblk), line->id,
					line->state);
		spin_unlock(&line->lock);

		list_del(&line->list);
		spin_unlock(&l_mg->gc_lock);

		spin_lock(&gc->r_lock);
		list_add_tail(&line->list, &gc->r_list);
		spin_unlock(&gc->r_lock);

		पढ़ो_inflight_gc = atomic_inc_वापस(&gc->पढ़ो_inflight_gc);
		pblk_gc_पढ़ोer_kick(gc);

		prev_group = 1;

		/* No need to queue up more GC lines than we can handle */
		run_gc = pblk_gc_should_run(&pblk->gc, &pblk->rl);
		अगर (!run_gc || पढ़ो_inflight_gc >= PBLK_GC_L_QD)
			अवरोध;
	पूर्ण जबतक (1);

	अगर (!prev_group && pblk->rl.rb_state > gc_group &&
						gc_group < PBLK_GC_NR_LISTS)
		जाओ next_gc_group;
पूर्ण

अटल व्योम pblk_gc_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा pblk *pblk = from_समयr(pblk, t, gc.gc_समयr);

	pblk_gc_kick(pblk);
पूर्ण

अटल पूर्णांक pblk_gc_ts(व्योम *data)
अणु
	काष्ठा pblk *pblk = data;

	जबतक (!kthपढ़ो_should_stop()) अणु
		pblk_gc_run(pblk);
		set_current_state(TASK_INTERRUPTIBLE);
		io_schedule();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pblk_gc_ग_लिखोr_ts(व्योम *data)
अणु
	काष्ठा pblk *pblk = data;

	जबतक (!kthपढ़ो_should_stop()) अणु
		अगर (!pblk_gc_ग_लिखो(pblk))
			जारी;
		set_current_state(TASK_INTERRUPTIBLE);
		io_schedule();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pblk_gc_पढ़ोer_ts(व्योम *data)
अणु
	काष्ठा pblk *pblk = data;
	काष्ठा pblk_gc *gc = &pblk->gc;

	जबतक (!kthपढ़ो_should_stop()) अणु
		अगर (!pblk_gc_पढ़ो(pblk))
			जारी;
		set_current_state(TASK_INTERRUPTIBLE);
		io_schedule();
	पूर्ण

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	pblk_info(pblk, "flushing gc pipeline, %d lines left\n",
		atomic_पढ़ो(&gc->pipeline_gc));
#पूर्ण_अगर

	करो अणु
		अगर (!atomic_पढ़ो(&gc->pipeline_gc))
			अवरोध;

		schedule();
	पूर्ण जबतक (1);

	वापस 0;
पूर्ण

अटल व्योम pblk_gc_start(काष्ठा pblk *pblk)
अणु
	pblk->gc.gc_active = 1;
	pblk_debug(pblk, "gc start\n");
पूर्ण

व्योम pblk_gc_should_start(काष्ठा pblk *pblk)
अणु
	काष्ठा pblk_gc *gc = &pblk->gc;

	अगर (gc->gc_enabled && !gc->gc_active) अणु
		pblk_gc_start(pblk);
		pblk_gc_kick(pblk);
	पूर्ण
पूर्ण

व्योम pblk_gc_should_stop(काष्ठा pblk *pblk)
अणु
	काष्ठा pblk_gc *gc = &pblk->gc;

	अगर (gc->gc_active && !gc->gc_क्रमced)
		gc->gc_active = 0;
पूर्ण

व्योम pblk_gc_should_kick(काष्ठा pblk *pblk)
अणु
	pblk_rl_update_rates(&pblk->rl);
पूर्ण

व्योम pblk_gc_sysfs_state_show(काष्ठा pblk *pblk, पूर्णांक *gc_enabled,
			      पूर्णांक *gc_active)
अणु
	काष्ठा pblk_gc *gc = &pblk->gc;

	spin_lock(&gc->lock);
	*gc_enabled = gc->gc_enabled;
	*gc_active = gc->gc_active;
	spin_unlock(&gc->lock);
पूर्ण

पूर्णांक pblk_gc_sysfs_क्रमce(काष्ठा pblk *pblk, पूर्णांक क्रमce)
अणु
	काष्ठा pblk_gc *gc = &pblk->gc;

	अगर (क्रमce < 0 || क्रमce > 1)
		वापस -EINVAL;

	spin_lock(&gc->lock);
	gc->gc_क्रमced = क्रमce;

	अगर (क्रमce)
		gc->gc_enabled = 1;
	अन्यथा
		gc->gc_enabled = 0;
	spin_unlock(&gc->lock);

	pblk_gc_should_start(pblk);

	वापस 0;
पूर्ण

पूर्णांक pblk_gc_init(काष्ठा pblk *pblk)
अणु
	काष्ठा pblk_gc *gc = &pblk->gc;
	पूर्णांक ret;

	gc->gc_ts = kthपढ़ो_create(pblk_gc_ts, pblk, "pblk-gc-ts");
	अगर (IS_ERR(gc->gc_ts)) अणु
		pblk_err(pblk, "could not allocate GC main kthread\n");
		वापस PTR_ERR(gc->gc_ts);
	पूर्ण

	gc->gc_ग_लिखोr_ts = kthपढ़ो_create(pblk_gc_ग_लिखोr_ts, pblk,
							"pblk-gc-writer-ts");
	अगर (IS_ERR(gc->gc_ग_लिखोr_ts)) अणु
		pblk_err(pblk, "could not allocate GC writer kthread\n");
		ret = PTR_ERR(gc->gc_ग_लिखोr_ts);
		जाओ fail_मुक्त_मुख्य_kthपढ़ो;
	पूर्ण

	gc->gc_पढ़ोer_ts = kthपढ़ो_create(pblk_gc_पढ़ोer_ts, pblk,
							"pblk-gc-reader-ts");
	अगर (IS_ERR(gc->gc_पढ़ोer_ts)) अणु
		pblk_err(pblk, "could not allocate GC reader kthread\n");
		ret = PTR_ERR(gc->gc_पढ़ोer_ts);
		जाओ fail_मुक्त_ग_लिखोr_kthपढ़ो;
	पूर्ण

	समयr_setup(&gc->gc_समयr, pblk_gc_समयr, 0);
	mod_समयr(&gc->gc_समयr, jअगरfies + msecs_to_jअगरfies(GC_TIME_MSECS));

	gc->gc_active = 0;
	gc->gc_क्रमced = 0;
	gc->gc_enabled = 1;
	gc->w_entries = 0;
	atomic_set(&gc->पढ़ो_inflight_gc, 0);
	atomic_set(&gc->pipeline_gc, 0);

	/* Workqueue that पढ़ोs valid sectors from a line and submit them to the
	 * GC ग_लिखोr to be recycled.
	 */
	gc->gc_line_पढ़ोer_wq = alloc_workqueue("pblk-gc-line-reader-wq",
			WQ_MEM_RECLAIM | WQ_UNBOUND, PBLK_GC_MAX_READERS);
	अगर (!gc->gc_line_पढ़ोer_wq) अणु
		pblk_err(pblk, "could not allocate GC line reader workqueue\n");
		ret = -ENOMEM;
		जाओ fail_मुक्त_पढ़ोer_kthपढ़ो;
	पूर्ण

	/* Workqueue that prepare lines क्रम GC */
	gc->gc_पढ़ोer_wq = alloc_workqueue("pblk-gc-line_wq",
					WQ_MEM_RECLAIM | WQ_UNBOUND, 1);
	अगर (!gc->gc_पढ़ोer_wq) अणु
		pblk_err(pblk, "could not allocate GC reader workqueue\n");
		ret = -ENOMEM;
		जाओ fail_मुक्त_पढ़ोer_line_wq;
	पूर्ण

	spin_lock_init(&gc->lock);
	spin_lock_init(&gc->w_lock);
	spin_lock_init(&gc->r_lock);

	sema_init(&gc->gc_sem, PBLK_GC_RQ_QD);

	INIT_LIST_HEAD(&gc->w_list);
	INIT_LIST_HEAD(&gc->r_list);

	वापस 0;

fail_मुक्त_पढ़ोer_line_wq:
	destroy_workqueue(gc->gc_line_पढ़ोer_wq);
fail_मुक्त_पढ़ोer_kthपढ़ो:
	kthपढ़ो_stop(gc->gc_पढ़ोer_ts);
fail_मुक्त_ग_लिखोr_kthपढ़ो:
	kthपढ़ो_stop(gc->gc_ग_लिखोr_ts);
fail_मुक्त_मुख्य_kthपढ़ो:
	kthपढ़ो_stop(gc->gc_ts);

	वापस ret;
पूर्ण

व्योम pblk_gc_निकास(काष्ठा pblk *pblk, bool graceful)
अणु
	काष्ठा pblk_gc *gc = &pblk->gc;

	gc->gc_enabled = 0;
	del_समयr_sync(&gc->gc_समयr);
	gc->gc_active = 0;

	अगर (gc->gc_ts)
		kthपढ़ो_stop(gc->gc_ts);

	अगर (gc->gc_पढ़ोer_ts)
		kthपढ़ो_stop(gc->gc_पढ़ोer_ts);

	अगर (graceful) अणु
		flush_workqueue(gc->gc_पढ़ोer_wq);
		flush_workqueue(gc->gc_line_पढ़ोer_wq);
	पूर्ण

	destroy_workqueue(gc->gc_पढ़ोer_wq);
	destroy_workqueue(gc->gc_line_पढ़ोer_wq);

	अगर (gc->gc_ग_लिखोr_ts)
		kthपढ़ो_stop(gc->gc_ग_लिखोr_ts);
पूर्ण
