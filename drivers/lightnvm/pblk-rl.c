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
 * pblk-rl.c - pblk's rate limiter क्रम user I/O
 *
 */

#समावेश "pblk.h"

अटल व्योम pblk_rl_kick_u_समयr(काष्ठा pblk_rl *rl)
अणु
	mod_समयr(&rl->u_समयr, jअगरfies + msecs_to_jअगरfies(5000));
पूर्ण

पूर्णांक pblk_rl_is_limit(काष्ठा pblk_rl *rl)
अणु
	पूर्णांक rb_space;

	rb_space = atomic_पढ़ो(&rl->rb_space);

	वापस (rb_space == 0);
पूर्ण

पूर्णांक pblk_rl_user_may_insert(काष्ठा pblk_rl *rl, पूर्णांक nr_entries)
अणु
	पूर्णांक rb_user_cnt = atomic_पढ़ो(&rl->rb_user_cnt);
	पूर्णांक rb_space = atomic_पढ़ो(&rl->rb_space);

	अगर (unlikely(rb_space >= 0) && (rb_space - nr_entries < 0))
		वापस NVM_IO_ERR;

	अगर (rb_user_cnt >= rl->rb_user_max)
		वापस NVM_IO_REQUEUE;

	वापस NVM_IO_OK;
पूर्ण

व्योम pblk_rl_inserted(काष्ठा pblk_rl *rl, पूर्णांक nr_entries)
अणु
	पूर्णांक rb_space = atomic_पढ़ो(&rl->rb_space);

	अगर (unlikely(rb_space >= 0))
		atomic_sub(nr_entries, &rl->rb_space);
पूर्ण

पूर्णांक pblk_rl_gc_may_insert(काष्ठा pblk_rl *rl, पूर्णांक nr_entries)
अणु
	पूर्णांक rb_gc_cnt = atomic_पढ़ो(&rl->rb_gc_cnt);
	पूर्णांक rb_user_active;

	/* If there is no user I/O let GC take over space on the ग_लिखो buffer */
	rb_user_active = READ_ONCE(rl->rb_user_active);
	वापस (!(rb_gc_cnt >= rl->rb_gc_max && rb_user_active));
पूर्ण

व्योम pblk_rl_user_in(काष्ठा pblk_rl *rl, पूर्णांक nr_entries)
अणु
	atomic_add(nr_entries, &rl->rb_user_cnt);

	/* Release user I/O state. Protect from GC */
	smp_store_release(&rl->rb_user_active, 1);
	pblk_rl_kick_u_समयr(rl);
पूर्ण

व्योम pblk_rl_werr_line_in(काष्ठा pblk_rl *rl)
अणु
	atomic_inc(&rl->werr_lines);
पूर्ण

व्योम pblk_rl_werr_line_out(काष्ठा pblk_rl *rl)
अणु
	atomic_dec(&rl->werr_lines);
पूर्ण

व्योम pblk_rl_gc_in(काष्ठा pblk_rl *rl, पूर्णांक nr_entries)
अणु
	atomic_add(nr_entries, &rl->rb_gc_cnt);
पूर्ण

व्योम pblk_rl_out(काष्ठा pblk_rl *rl, पूर्णांक nr_user, पूर्णांक nr_gc)
अणु
	atomic_sub(nr_user, &rl->rb_user_cnt);
	atomic_sub(nr_gc, &rl->rb_gc_cnt);
पूर्ण

अचिन्हित दीर्घ pblk_rl_nr_मुक्त_blks(काष्ठा pblk_rl *rl)
अणु
	वापस atomic_पढ़ो(&rl->मुक्त_blocks);
पूर्ण

अचिन्हित दीर्घ pblk_rl_nr_user_मुक्त_blks(काष्ठा pblk_rl *rl)
अणु
	वापस atomic_पढ़ो(&rl->मुक्त_user_blocks);
पूर्ण

अटल व्योम __pblk_rl_update_rates(काष्ठा pblk_rl *rl,
				   अचिन्हित दीर्घ मुक्त_blocks)
अणु
	काष्ठा pblk *pblk = container_of(rl, काष्ठा pblk, rl);
	पूर्णांक max = rl->rb_budget;
	पूर्णांक werr_gc_needed = atomic_पढ़ो(&rl->werr_lines);

	अगर (मुक्त_blocks >= rl->high) अणु
		अगर (werr_gc_needed) अणु
			/* Allocate a small budget क्रम recovering
			 * lines with ग_लिखो errors
			 */
			rl->rb_gc_max = 1 << rl->rb_winकरोws_pw;
			rl->rb_user_max = max - rl->rb_gc_max;
			rl->rb_state = PBLK_RL_WERR;
		पूर्ण अन्यथा अणु
			rl->rb_user_max = max;
			rl->rb_gc_max = 0;
			rl->rb_state = PBLK_RL_OFF;
		पूर्ण
	पूर्ण अन्यथा अगर (मुक्त_blocks < rl->high) अणु
		पूर्णांक shअगरt = rl->high_pw - rl->rb_winकरोws_pw;
		पूर्णांक user_winकरोws = मुक्त_blocks >> shअगरt;
		पूर्णांक user_max = user_winकरोws << ilog2(NVM_MAX_VLBA);

		rl->rb_user_max = user_max;
		rl->rb_gc_max = max - user_max;

		अगर (मुक्त_blocks <= rl->rsv_blocks) अणु
			rl->rb_user_max = 0;
			rl->rb_gc_max = max;
		पूर्ण

		/* In the worst हाल, we will need to GC lines in the low list
		 * (high valid sector count). If there are lines to GC on high
		 * or mid lists, these will be prioritized
		 */
		rl->rb_state = PBLK_RL_LOW;
	पूर्ण

	अगर (rl->rb_state != PBLK_RL_OFF)
		pblk_gc_should_start(pblk);
	अन्यथा
		pblk_gc_should_stop(pblk);
पूर्ण

व्योम pblk_rl_update_rates(काष्ठा pblk_rl *rl)
अणु
	__pblk_rl_update_rates(rl, pblk_rl_nr_user_मुक्त_blks(rl));
पूर्ण

व्योम pblk_rl_मुक्त_lines_inc(काष्ठा pblk_rl *rl, काष्ठा pblk_line *line)
अणु
	पूर्णांक blk_in_line = atomic_पढ़ो(&line->blk_in_line);
	पूर्णांक मुक्त_blocks;

	atomic_add(blk_in_line, &rl->मुक्त_blocks);
	मुक्त_blocks = atomic_add_वापस(blk_in_line, &rl->मुक्त_user_blocks);

	__pblk_rl_update_rates(rl, मुक्त_blocks);
पूर्ण

व्योम pblk_rl_मुक्त_lines_dec(काष्ठा pblk_rl *rl, काष्ठा pblk_line *line,
			    bool used)
अणु
	पूर्णांक blk_in_line = atomic_पढ़ो(&line->blk_in_line);
	पूर्णांक मुक्त_blocks;

	atomic_sub(blk_in_line, &rl->मुक्त_blocks);

	अगर (used)
		मुक्त_blocks = atomic_sub_वापस(blk_in_line,
							&rl->मुक्त_user_blocks);
	अन्यथा
		मुक्त_blocks = atomic_पढ़ो(&rl->मुक्त_user_blocks);

	__pblk_rl_update_rates(rl, मुक्त_blocks);
पूर्ण

पूर्णांक pblk_rl_high_thrs(काष्ठा pblk_rl *rl)
अणु
	वापस rl->high;
पूर्ण

पूर्णांक pblk_rl_max_io(काष्ठा pblk_rl *rl)
अणु
	वापस rl->rb_max_io;
पूर्ण

अटल व्योम pblk_rl_u_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा pblk_rl *rl = from_समयr(rl, t, u_समयr);

	/* Release user I/O state. Protect from GC */
	smp_store_release(&rl->rb_user_active, 0);
पूर्ण

व्योम pblk_rl_मुक्त(काष्ठा pblk_rl *rl)
अणु
	del_समयr(&rl->u_समयr);
पूर्ण

व्योम pblk_rl_init(काष्ठा pblk_rl *rl, पूर्णांक budget, पूर्णांक threshold)
अणु
	काष्ठा pblk *pblk = container_of(rl, काष्ठा pblk, rl);
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	पूर्णांक sec_meta, blk_meta;
	अचिन्हित पूर्णांक rb_winकरोws;

	/* Consider sectors used क्रम metadata */
	sec_meta = (lm->smeta_sec + lm->emeta_sec[0]) * l_mg->nr_मुक्त_lines;
	blk_meta = DIV_ROUND_UP(sec_meta, geo->clba);

	rl->high = pblk->op_blks - blk_meta - lm->blk_per_line;
	rl->high_pw = get_count_order(rl->high);

	rl->rsv_blocks = pblk_get_min_chks(pblk);

	/* This will always be a घातer-of-2 */
	rb_winकरोws = budget / NVM_MAX_VLBA;
	rl->rb_winकरोws_pw = get_count_order(rb_winकरोws);

	/* To start with, all buffer is available to user I/O ग_लिखोrs */
	rl->rb_budget = budget;
	rl->rb_user_max = budget;
	rl->rb_gc_max = 0;
	rl->rb_state = PBLK_RL_HIGH;

	/* Maximize I/O size and ansure that back threshold is respected */
	अगर (threshold)
		rl->rb_max_io = budget - pblk->min_ग_लिखो_pgs_data - threshold;
	अन्यथा
		rl->rb_max_io = budget - pblk->min_ग_लिखो_pgs_data - 1;

	atomic_set(&rl->rb_user_cnt, 0);
	atomic_set(&rl->rb_gc_cnt, 0);
	atomic_set(&rl->rb_space, -1);
	atomic_set(&rl->werr_lines, 0);

	समयr_setup(&rl->u_समयr, pblk_rl_u_समयr, 0);

	rl->rb_user_active = 0;
	rl->rb_gc_active = 0;
पूर्ण
