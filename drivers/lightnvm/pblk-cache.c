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
 * pblk-cache.c - pblk's ग_लिखो cache
 */

#समावेश "pblk.h"

व्योम pblk_ग_लिखो_to_cache(काष्ठा pblk *pblk, काष्ठा bio *bio,
				अचिन्हित दीर्घ flags)
अणु
	काष्ठा pblk_w_ctx w_ctx;
	sector_t lba = pblk_get_lba(bio);
	अचिन्हित दीर्घ start_समय;
	अचिन्हित पूर्णांक bpos, pos;
	पूर्णांक nr_entries = pblk_get_secs(bio);
	पूर्णांक i, ret;

	start_समय = bio_start_io_acct(bio);

	/* Update the ग_लिखो buffer head (mem) with the entries that we can
	 * ग_लिखो. The ग_लिखो in itself cannot fail, so there is no need to
	 * rollback from here on.
	 */
retry:
	ret = pblk_rb_may_ग_लिखो_user(&pblk->rwb, bio, nr_entries, &bpos);
	चयन (ret) अणु
	हाल NVM_IO_REQUEUE:
		io_schedule();
		जाओ retry;
	हाल NVM_IO_ERR:
		pblk_pipeline_stop(pblk);
		bio_io_error(bio);
		जाओ out;
	पूर्ण

	pblk_ppa_set_empty(&w_ctx.ppa);
	w_ctx.flags = flags;
	अगर (bio->bi_opf & REQ_PREFLUSH) अणु
		w_ctx.flags |= PBLK_FLUSH_ENTRY;
		pblk_ग_लिखो_kick(pblk);
	पूर्ण

	अगर (unlikely(!bio_has_data(bio)))
		जाओ out;

	क्रम (i = 0; i < nr_entries; i++) अणु
		व्योम *data = bio_data(bio);

		w_ctx.lba = lba + i;

		pos = pblk_rb_wrap_pos(&pblk->rwb, bpos + i);
		pblk_rb_ग_लिखो_entry_user(&pblk->rwb, data, w_ctx, pos);

		bio_advance(bio, PBLK_EXPOSED_PAGE_SIZE);
	पूर्ण

	atomic64_add(nr_entries, &pblk->user_wa);

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	atomic_दीर्घ_add(nr_entries, &pblk->inflight_ग_लिखोs);
	atomic_दीर्घ_add(nr_entries, &pblk->req_ग_लिखोs);
#पूर्ण_अगर

	pblk_rl_inserted(&pblk->rl, nr_entries);

out:
	bio_end_io_acct(bio, start_समय);
	pblk_ग_लिखो_should_kick(pblk);

	अगर (ret == NVM_IO_DONE)
		bio_endio(bio);
पूर्ण

/*
 * On GC the incoming lbas are not necessarily sequential. Also, some of the
 * lbas might not be valid entries, which are marked as empty by the GC thपढ़ो
 */
पूर्णांक pblk_ग_लिखो_gc_to_cache(काष्ठा pblk *pblk, काष्ठा pblk_gc_rq *gc_rq)
अणु
	काष्ठा pblk_w_ctx w_ctx;
	अचिन्हित पूर्णांक bpos, pos;
	व्योम *data = gc_rq->data;
	पूर्णांक i, valid_entries;

	/* Update the ग_लिखो buffer head (mem) with the entries that we can
	 * ग_लिखो. The ग_लिखो in itself cannot fail, so there is no need to
	 * rollback from here on.
	 */
retry:
	अगर (!pblk_rb_may_ग_लिखो_gc(&pblk->rwb, gc_rq->secs_to_gc, &bpos)) अणु
		io_schedule();
		जाओ retry;
	पूर्ण

	w_ctx.flags = PBLK_IOTYPE_GC;
	pblk_ppa_set_empty(&w_ctx.ppa);

	क्रम (i = 0, valid_entries = 0; i < gc_rq->nr_secs; i++) अणु
		अगर (gc_rq->lba_list[i] == ADDR_EMPTY)
			जारी;

		w_ctx.lba = gc_rq->lba_list[i];

		pos = pblk_rb_wrap_pos(&pblk->rwb, bpos + valid_entries);
		pblk_rb_ग_लिखो_entry_gc(&pblk->rwb, data, w_ctx, gc_rq->line,
						gc_rq->paddr_list[i], pos);

		data += PBLK_EXPOSED_PAGE_SIZE;
		valid_entries++;
	पूर्ण

	WARN_ONCE(gc_rq->secs_to_gc != valid_entries,
					"pblk: inconsistent GC write\n");

	atomic64_add(valid_entries, &pblk->gc_wa);

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	atomic_दीर्घ_add(valid_entries, &pblk->inflight_ग_लिखोs);
	atomic_दीर्घ_add(valid_entries, &pblk->recov_gc_ग_लिखोs);
#पूर्ण_अगर

	pblk_ग_लिखो_should_kick(pblk);
	वापस NVM_IO_OK;
पूर्ण
