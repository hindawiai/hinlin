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
 * pblk-map.c - pblk's lba-ppa mapping strategy
 *
 */

#समावेश "pblk.h"

अटल पूर्णांक pblk_map_page_data(काष्ठा pblk *pblk, अचिन्हित पूर्णांक sentry,
			      काष्ठा ppa_addr *ppa_list,
			      अचिन्हित दीर्घ *lun_biपंचांगap,
			      व्योम *meta_list,
			      अचिन्हित पूर्णांक valid_secs)
अणु
	काष्ठा pblk_line *line = pblk_line_get_data(pblk);
	काष्ठा pblk_emeta *emeta;
	काष्ठा pblk_w_ctx *w_ctx;
	__le64 *lba_list;
	u64 paddr;
	पूर्णांक nr_secs = pblk->min_ग_लिखो_pgs;
	पूर्णांक i;

	अगर (!line)
		वापस -ENOSPC;

	अगर (pblk_line_is_full(line)) अणु
		काष्ठा pblk_line *prev_line = line;

		/* If we cannot allocate a new line, make sure to store metadata
		 * on current line and then fail
		 */
		line = pblk_line_replace_data(pblk);
		pblk_line_बंद_meta(pblk, prev_line);

		अगर (!line) अणु
			pblk_pipeline_stop(pblk);
			वापस -ENOSPC;
		पूर्ण

	पूर्ण

	emeta = line->emeta;
	lba_list = emeta_to_lbas(pblk, emeta->buf);

	paddr = pblk_alloc_page(pblk, line, nr_secs);

	क्रम (i = 0; i < nr_secs; i++, paddr++) अणु
		काष्ठा pblk_sec_meta *meta = pblk_get_meta(pblk, meta_list, i);
		__le64 addr_empty = cpu_to_le64(ADDR_EMPTY);

		/* ppa to be sent to the device */
		ppa_list[i] = addr_to_gen_ppa(pblk, paddr, line->id);

		/* Write context क्रम target bio completion on ग_लिखो buffer. Note
		 * that the ग_लिखो buffer is रक्षित by the sync backpoपूर्णांकer,
		 * and a single ग_लिखोr thपढ़ो have access to each specअगरic entry
		 * at a समय. Thus, it is safe to modअगरy the context क्रम the
		 * entry we are setting up क्रम submission without taking any
		 * lock or memory barrier.
		 */
		अगर (i < valid_secs) अणु
			kref_get(&line->ref);
			atomic_inc(&line->sec_to_update);
			w_ctx = pblk_rb_w_ctx(&pblk->rwb, sentry + i);
			w_ctx->ppa = ppa_list[i];
			meta->lba = cpu_to_le64(w_ctx->lba);
			lba_list[paddr] = cpu_to_le64(w_ctx->lba);
			अगर (lba_list[paddr] != addr_empty)
				line->nr_valid_lbas++;
			अन्यथा
				atomic64_inc(&pblk->pad_wa);
		पूर्ण अन्यथा अणु
			lba_list[paddr] = addr_empty;
			meta->lba = addr_empty;
			__pblk_map_invalidate(pblk, line, paddr);
		पूर्ण
	पूर्ण

	pblk_करोwn_rq(pblk, ppa_list[0], lun_biपंचांगap);
	वापस 0;
पूर्ण

पूर्णांक pblk_map_rq(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd, अचिन्हित पूर्णांक sentry,
		 अचिन्हित दीर्घ *lun_biपंचांगap, अचिन्हित पूर्णांक valid_secs,
		 अचिन्हित पूर्णांक off)
अणु
	व्योम *meta_list = pblk_get_meta_क्रम_ग_लिखोs(pblk, rqd);
	व्योम *meta_buffer;
	काष्ठा ppa_addr *ppa_list = nvm_rq_to_ppa_list(rqd);
	अचिन्हित पूर्णांक map_secs;
	पूर्णांक min = pblk->min_ग_लिखो_pgs;
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = off; i < rqd->nr_ppas; i += min) अणु
		map_secs = (i + min > valid_secs) ? (valid_secs % min) : min;
		meta_buffer = pblk_get_meta(pblk, meta_list, i);

		ret = pblk_map_page_data(pblk, sentry + i, &ppa_list[i],
					lun_biपंचांगap, meta_buffer, map_secs);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* only अगर erase_ppa is set, acquire erase semaphore */
पूर्णांक pblk_map_erase_rq(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd,
		       अचिन्हित पूर्णांक sentry, अचिन्हित दीर्घ *lun_biपंचांगap,
		       अचिन्हित पूर्णांक valid_secs, काष्ठा ppa_addr *erase_ppa)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	व्योम *meta_list = pblk_get_meta_क्रम_ग_लिखोs(pblk, rqd);
	व्योम *meta_buffer;
	काष्ठा ppa_addr *ppa_list = nvm_rq_to_ppa_list(rqd);
	काष्ठा pblk_line *e_line, *d_line;
	अचिन्हित पूर्णांक map_secs;
	पूर्णांक min = pblk->min_ग_लिखो_pgs;
	पूर्णांक i, erase_lun;
	पूर्णांक ret;


	क्रम (i = 0; i < rqd->nr_ppas; i += min) अणु
		map_secs = (i + min > valid_secs) ? (valid_secs % min) : min;
		meta_buffer = pblk_get_meta(pblk, meta_list, i);

		ret = pblk_map_page_data(pblk, sentry + i, &ppa_list[i],
					lun_biपंचांगap, meta_buffer, map_secs);
		अगर (ret)
			वापस ret;

		erase_lun = pblk_ppa_to_pos(geo, ppa_list[i]);

		/* line can change after page map. We might also be writing the
		 * last line.
		 */
		e_line = pblk_line_get_erase(pblk);
		अगर (!e_line)
			वापस pblk_map_rq(pblk, rqd, sentry, lun_biपंचांगap,
							valid_secs, i + min);

		spin_lock(&e_line->lock);
		अगर (!test_bit(erase_lun, e_line->erase_biपंचांगap)) अणु
			set_bit(erase_lun, e_line->erase_biपंचांगap);
			atomic_dec(&e_line->left_eblks);

			*erase_ppa = ppa_list[i];
			erase_ppa->a.blk = e_line->id;
			erase_ppa->a.reserved = 0;

			spin_unlock(&e_line->lock);

			/* Aव्योम evaluating e_line->left_eblks */
			वापस pblk_map_rq(pblk, rqd, sentry, lun_biपंचांगap,
							valid_secs, i + min);
		पूर्ण
		spin_unlock(&e_line->lock);
	पूर्ण

	d_line = pblk_line_get_data(pblk);

	/* line can change after page map. We might also be writing the
	 * last line.
	 */
	e_line = pblk_line_get_erase(pblk);
	अगर (!e_line)
		वापस -ENOSPC;

	/* Erase blocks that are bad in this line but might not be in next */
	अगर (unlikely(pblk_ppa_empty(*erase_ppa)) &&
			biपंचांगap_weight(d_line->blk_biपंचांगap, lm->blk_per_line)) अणु
		पूर्णांक bit = -1;

retry:
		bit = find_next_bit(d_line->blk_biपंचांगap,
						lm->blk_per_line, bit + 1);
		अगर (bit >= lm->blk_per_line)
			वापस 0;

		spin_lock(&e_line->lock);
		अगर (test_bit(bit, e_line->erase_biपंचांगap)) अणु
			spin_unlock(&e_line->lock);
			जाओ retry;
		पूर्ण
		spin_unlock(&e_line->lock);

		set_bit(bit, e_line->erase_biपंचांगap);
		atomic_dec(&e_line->left_eblks);
		*erase_ppa = pblk->luns[bit].bppa; /* set ch and lun */
		erase_ppa->a.blk = e_line->id;
	पूर्ण

	वापस 0;
पूर्ण
