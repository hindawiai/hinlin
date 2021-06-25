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
 * pblk-ग_लिखो.c - pblk's ग_लिखो path from ग_लिखो buffer to media
 */

#समावेश "pblk.h"
#समावेश "pblk-trace.h"

अटल अचिन्हित दीर्घ pblk_end_w_bio(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd,
				    काष्ठा pblk_c_ctx *c_ctx)
अणु
	काष्ठा bio *original_bio;
	काष्ठा pblk_rb *rwb = &pblk->rwb;
	अचिन्हित दीर्घ ret;
	पूर्णांक i;

	क्रम (i = 0; i < c_ctx->nr_valid; i++) अणु
		काष्ठा pblk_w_ctx *w_ctx;
		पूर्णांक pos = c_ctx->sentry + i;
		पूर्णांक flags;

		w_ctx = pblk_rb_w_ctx(rwb, pos);
		flags = READ_ONCE(w_ctx->flags);

		अगर (flags & PBLK_FLUSH_ENTRY) अणु
			flags &= ~PBLK_FLUSH_ENTRY;
			/* Release flags on context. Protect from ग_लिखोs */
			smp_store_release(&w_ctx->flags, flags);

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
			atomic_dec(&rwb->inflight_flush_poपूर्णांक);
#पूर्ण_अगर
		पूर्ण

		जबतक ((original_bio = bio_list_pop(&w_ctx->bios)))
			bio_endio(original_bio);
	पूर्ण

	अगर (c_ctx->nr_padded)
		pblk_bio_मुक्त_pages(pblk, rqd->bio, c_ctx->nr_valid,
							c_ctx->nr_padded);

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	atomic_दीर्घ_add(rqd->nr_ppas, &pblk->sync_ग_लिखोs);
#पूर्ण_अगर

	ret = pblk_rb_sync_advance(&pblk->rwb, c_ctx->nr_valid);

	bio_put(rqd->bio);
	pblk_मुक्त_rqd(pblk, rqd, PBLK_WRITE);

	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ pblk_end_queued_w_bio(काष्ठा pblk *pblk,
					   काष्ठा nvm_rq *rqd,
					   काष्ठा pblk_c_ctx *c_ctx)
अणु
	list_del(&c_ctx->list);
	वापस pblk_end_w_bio(pblk, rqd, c_ctx);
पूर्ण

अटल व्योम pblk_complete_ग_लिखो(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd,
				काष्ठा pblk_c_ctx *c_ctx)
अणु
	काष्ठा pblk_c_ctx *c, *r;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ pos;

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	atomic_दीर्घ_sub(c_ctx->nr_valid, &pblk->inflight_ग_लिखोs);
#पूर्ण_अगर
	pblk_up_rq(pblk, c_ctx->lun_biपंचांगap);

	pos = pblk_rb_sync_init(&pblk->rwb, &flags);
	अगर (pos == c_ctx->sentry) अणु
		pos = pblk_end_w_bio(pblk, rqd, c_ctx);

retry:
		list_क्रम_each_entry_safe(c, r, &pblk->compl_list, list) अणु
			rqd = nvm_rq_from_c_ctx(c);
			अगर (c->sentry == pos) अणु
				pos = pblk_end_queued_w_bio(pblk, rqd, c);
				जाओ retry;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		WARN_ON(nvm_rq_from_c_ctx(c_ctx) != rqd);
		list_add_tail(&c_ctx->list, &pblk->compl_list);
	पूर्ण
	pblk_rb_sync_end(&pblk->rwb, &flags);
पूर्ण

/* Map reमुख्यing sectors in chunk, starting from ppa */
अटल व्योम pblk_map_reमुख्यing(काष्ठा pblk *pblk, काष्ठा ppa_addr *ppa,
		पूर्णांक rqd_ppas)
अणु
	काष्ठा pblk_line *line;
	काष्ठा ppa_addr map_ppa = *ppa;
	__le64 addr_empty = cpu_to_le64(ADDR_EMPTY);
	__le64 *lba_list;
	u64 paddr;
	पूर्णांक करोne = 0;
	पूर्णांक n = 0;

	line = pblk_ppa_to_line(pblk, *ppa);
	lba_list = emeta_to_lbas(pblk, line->emeta->buf);

	spin_lock(&line->lock);

	जबतक (!करोne)  अणु
		paddr = pblk_dev_ppa_to_line_addr(pblk, map_ppa);

		अगर (!test_and_set_bit(paddr, line->map_biपंचांगap))
			line->left_msecs--;

		अगर (n < rqd_ppas && lba_list[paddr] != addr_empty)
			line->nr_valid_lbas--;

		lba_list[paddr] = addr_empty;

		अगर (!test_and_set_bit(paddr, line->invalid_biपंचांगap))
			le32_add_cpu(line->vsc, -1);

		करोne = nvm_next_ppa_in_chk(pblk->dev, &map_ppa);

		n++;
	पूर्ण

	line->w_err_gc->has_ग_लिखो_err = 1;
	spin_unlock(&line->lock);
पूर्ण

अटल व्योम pblk_prepare_resubmit(काष्ठा pblk *pblk, अचिन्हित पूर्णांक sentry,
				  अचिन्हित पूर्णांक nr_entries)
अणु
	काष्ठा pblk_rb *rb = &pblk->rwb;
	काष्ठा pblk_rb_entry *entry;
	काष्ठा pblk_line *line;
	काष्ठा pblk_w_ctx *w_ctx;
	काष्ठा ppa_addr ppa_l2p;
	पूर्णांक flags;
	अचिन्हित पूर्णांक i;

	spin_lock(&pblk->trans_lock);
	क्रम (i = 0; i < nr_entries; i++) अणु
		entry = &rb->entries[pblk_rb_ptr_wrap(rb, sentry, i)];
		w_ctx = &entry->w_ctx;

		/* Check अगर the lba has been overwritten */
		अगर (w_ctx->lba != ADDR_EMPTY) अणु
			ppa_l2p = pblk_trans_map_get(pblk, w_ctx->lba);
			अगर (!pblk_ppa_comp(ppa_l2p, entry->cacheline))
				w_ctx->lba = ADDR_EMPTY;
		पूर्ण

		/* Mark up the entry as submittable again */
		flags = READ_ONCE(w_ctx->flags);
		flags |= PBLK_WRITTEN_DATA;
		/* Release flags on ग_लिखो context. Protect from ग_लिखोs */
		smp_store_release(&w_ctx->flags, flags);

		/* Decrease the reference count to the line as we will
		 * re-map these entries
		 */
		line = pblk_ppa_to_line(pblk, w_ctx->ppa);
		atomic_dec(&line->sec_to_update);
		kref_put(&line->ref, pblk_line_put);
	पूर्ण
	spin_unlock(&pblk->trans_lock);
पूर्ण

अटल व्योम pblk_queue_resubmit(काष्ठा pblk *pblk, काष्ठा pblk_c_ctx *c_ctx)
अणु
	काष्ठा pblk_c_ctx *r_ctx;

	r_ctx = kzalloc(माप(काष्ठा pblk_c_ctx), GFP_KERNEL);
	अगर (!r_ctx)
		वापस;

	r_ctx->lun_biपंचांगap = शून्य;
	r_ctx->sentry = c_ctx->sentry;
	r_ctx->nr_valid = c_ctx->nr_valid;
	r_ctx->nr_padded = c_ctx->nr_padded;

	spin_lock(&pblk->resubmit_lock);
	list_add_tail(&r_ctx->list, &pblk->resubmit_list);
	spin_unlock(&pblk->resubmit_lock);

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	atomic_दीर्घ_add(c_ctx->nr_valid, &pblk->recov_ग_लिखोs);
#पूर्ण_अगर
पूर्ण

अटल व्योम pblk_submit_rec(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pblk_rec_ctx *recovery =
			container_of(work, काष्ठा pblk_rec_ctx, ws_rec);
	काष्ठा pblk *pblk = recovery->pblk;
	काष्ठा nvm_rq *rqd = recovery->rqd;
	काष्ठा pblk_c_ctx *c_ctx = nvm_rq_to_pdu(rqd);
	काष्ठा ppa_addr *ppa_list = nvm_rq_to_ppa_list(rqd);

	pblk_log_ग_लिखो_err(pblk, rqd);

	pblk_map_reमुख्यing(pblk, ppa_list, rqd->nr_ppas);
	pblk_queue_resubmit(pblk, c_ctx);

	pblk_up_rq(pblk, c_ctx->lun_biपंचांगap);
	अगर (c_ctx->nr_padded)
		pblk_bio_मुक्त_pages(pblk, rqd->bio, c_ctx->nr_valid,
							c_ctx->nr_padded);
	bio_put(rqd->bio);
	pblk_मुक्त_rqd(pblk, rqd, PBLK_WRITE);
	mempool_मुक्त(recovery, &pblk->rec_pool);

	atomic_dec(&pblk->inflight_io);
	pblk_ग_लिखो_kick(pblk);
पूर्ण


अटल व्योम pblk_end_w_fail(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd)
अणु
	काष्ठा pblk_rec_ctx *recovery;

	recovery = mempool_alloc(&pblk->rec_pool, GFP_ATOMIC);
	अगर (!recovery) अणु
		pblk_err(pblk, "could not allocate recovery work\n");
		वापस;
	पूर्ण

	recovery->pblk = pblk;
	recovery->rqd = rqd;

	INIT_WORK(&recovery->ws_rec, pblk_submit_rec);
	queue_work(pblk->बंद_wq, &recovery->ws_rec);
पूर्ण

अटल व्योम pblk_end_io_ग_लिखो(काष्ठा nvm_rq *rqd)
अणु
	काष्ठा pblk *pblk = rqd->निजी;
	काष्ठा pblk_c_ctx *c_ctx = nvm_rq_to_pdu(rqd);

	अगर (rqd->error) अणु
		pblk_end_w_fail(pblk, rqd);
		वापस;
	पूर्ण अन्यथा अणु
		अगर (trace_pblk_chunk_state_enabled())
			pblk_check_chunk_state_update(pblk, rqd);
#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
		WARN_ONCE(rqd->bio->bi_status, "pblk: corrupted write error\n");
#पूर्ण_अगर
	पूर्ण

	pblk_complete_ग_लिखो(pblk, rqd, c_ctx);
	atomic_dec(&pblk->inflight_io);
पूर्ण

अटल व्योम pblk_end_io_ग_लिखो_meta(काष्ठा nvm_rq *rqd)
अणु
	काष्ठा pblk *pblk = rqd->निजी;
	काष्ठा pblk_g_ctx *m_ctx = nvm_rq_to_pdu(rqd);
	काष्ठा pblk_line *line = m_ctx->निजी;
	काष्ठा pblk_emeta *emeta = line->emeta;
	काष्ठा ppa_addr *ppa_list = nvm_rq_to_ppa_list(rqd);
	पूर्णांक sync;

	pblk_up_chunk(pblk, ppa_list[0]);

	अगर (rqd->error) अणु
		pblk_log_ग_लिखो_err(pblk, rqd);
		pblk_err(pblk, "metadata I/O failed. Line %d\n", line->id);
		line->w_err_gc->has_ग_लिखो_err = 1;
	पूर्ण अन्यथा अणु
		अगर (trace_pblk_chunk_state_enabled())
			pblk_check_chunk_state_update(pblk, rqd);
	पूर्ण

	sync = atomic_add_वापस(rqd->nr_ppas, &emeta->sync);
	अगर (sync == emeta->nr_entries)
		pblk_gen_run_ws(pblk, line, शून्य, pblk_line_बंद_ws,
						GFP_ATOMIC, pblk->बंद_wq);

	pblk_मुक्त_rqd(pblk, rqd, PBLK_WRITE_INT);

	atomic_dec(&pblk->inflight_io);
पूर्ण

अटल पूर्णांक pblk_alloc_w_rq(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd,
			   अचिन्हित पूर्णांक nr_secs, nvm_end_io_fn(*end_io))
अणु
	/* Setup ग_लिखो request */
	rqd->opcode = NVM_OP_PWRITE;
	rqd->nr_ppas = nr_secs;
	rqd->is_seq = 1;
	rqd->निजी = pblk;
	rqd->end_io = end_io;

	वापस pblk_alloc_rqd_meta(pblk, rqd);
पूर्ण

अटल पूर्णांक pblk_setup_w_rq(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd,
			   काष्ठा ppa_addr *erase_ppa)
अणु
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा pblk_line *e_line = pblk_line_get_erase(pblk);
	काष्ठा pblk_c_ctx *c_ctx = nvm_rq_to_pdu(rqd);
	अचिन्हित पूर्णांक valid = c_ctx->nr_valid;
	अचिन्हित पूर्णांक padded = c_ctx->nr_padded;
	अचिन्हित पूर्णांक nr_secs = valid + padded;
	अचिन्हित दीर्घ *lun_biपंचांगap;
	पूर्णांक ret;

	lun_biपंचांगap = kzalloc(lm->lun_biपंचांगap_len, GFP_KERNEL);
	अगर (!lun_biपंचांगap)
		वापस -ENOMEM;
	c_ctx->lun_biपंचांगap = lun_biपंचांगap;

	ret = pblk_alloc_w_rq(pblk, rqd, nr_secs, pblk_end_io_ग_लिखो);
	अगर (ret) अणु
		kमुक्त(lun_biपंचांगap);
		वापस ret;
	पूर्ण

	अगर (likely(!e_line || !atomic_पढ़ो(&e_line->left_eblks)))
		ret = pblk_map_rq(pblk, rqd, c_ctx->sentry, lun_biपंचांगap,
							valid, 0);
	अन्यथा
		ret = pblk_map_erase_rq(pblk, rqd, c_ctx->sentry, lun_biपंचांगap,
							valid, erase_ppa);

	वापस ret;
पूर्ण

अटल पूर्णांक pblk_calc_secs_to_sync(काष्ठा pblk *pblk, अचिन्हित पूर्णांक secs_avail,
				  अचिन्हित पूर्णांक secs_to_flush)
अणु
	पूर्णांक secs_to_sync;

	secs_to_sync = pblk_calc_secs(pblk, secs_avail, secs_to_flush, true);

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	अगर ((!secs_to_sync && secs_to_flush)
			|| (secs_to_sync < 0)
			|| (secs_to_sync > secs_avail && !secs_to_flush)) अणु
		pblk_err(pblk, "bad sector calculation (a:%d,s:%d,f:%d)\n",
				secs_avail, secs_to_sync, secs_to_flush);
	पूर्ण
#पूर्ण_अगर

	वापस secs_to_sync;
पूर्ण

पूर्णांक pblk_submit_meta_io(काष्ठा pblk *pblk, काष्ठा pblk_line *meta_line)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा pblk_emeta *emeta = meta_line->emeta;
	काष्ठा ppa_addr *ppa_list;
	काष्ठा pblk_g_ctx *m_ctx;
	काष्ठा nvm_rq *rqd;
	व्योम *data;
	u64 paddr;
	पूर्णांक rq_ppas = pblk->min_ग_लिखो_pgs;
	पूर्णांक id = meta_line->id;
	पूर्णांक rq_len;
	पूर्णांक i, j;
	पूर्णांक ret;

	rqd = pblk_alloc_rqd(pblk, PBLK_WRITE_INT);

	m_ctx = nvm_rq_to_pdu(rqd);
	m_ctx->निजी = meta_line;

	rq_len = rq_ppas * geo->csecs;
	data = ((व्योम *)emeta->buf) + emeta->mem;

	ret = pblk_alloc_w_rq(pblk, rqd, rq_ppas, pblk_end_io_ग_लिखो_meta);
	अगर (ret)
		जाओ fail_मुक्त_rqd;

	ppa_list = nvm_rq_to_ppa_list(rqd);
	क्रम (i = 0; i < rqd->nr_ppas; ) अणु
		spin_lock(&meta_line->lock);
		paddr = __pblk_alloc_page(pblk, meta_line, rq_ppas);
		spin_unlock(&meta_line->lock);
		क्रम (j = 0; j < rq_ppas; j++, i++, paddr++)
			ppa_list[i] = addr_to_gen_ppa(pblk, paddr, id);
	पूर्ण

	spin_lock(&l_mg->बंद_lock);
	emeta->mem += rq_len;
	अगर (emeta->mem >= lm->emeta_len[0])
		list_del(&meta_line->list);
	spin_unlock(&l_mg->बंद_lock);

	pblk_करोwn_chunk(pblk, ppa_list[0]);

	ret = pblk_submit_io(pblk, rqd, data);
	अगर (ret) अणु
		pblk_err(pblk, "emeta I/O submission failed: %d\n", ret);
		जाओ fail_rollback;
	पूर्ण

	वापस NVM_IO_OK;

fail_rollback:
	pblk_up_chunk(pblk, ppa_list[0]);
	spin_lock(&l_mg->बंद_lock);
	pblk_dealloc_page(pblk, meta_line, rq_ppas);
	list_add(&meta_line->list, &meta_line->list);
	spin_unlock(&l_mg->बंद_lock);
fail_मुक्त_rqd:
	pblk_मुक्त_rqd(pblk, rqd, PBLK_WRITE_INT);
	वापस ret;
पूर्ण

अटल अंतरभूत bool pblk_valid_meta_ppa(काष्ठा pblk *pblk,
				       काष्ठा pblk_line *meta_line,
				       काष्ठा nvm_rq *data_rqd)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा pblk_c_ctx *data_c_ctx = nvm_rq_to_pdu(data_rqd);
	काष्ठा pblk_line *data_line = pblk_line_get_data(pblk);
	काष्ठा ppa_addr ppa, ppa_opt;
	u64 paddr;
	पूर्णांक pos_opt;

	/* Schedule a metadata I/O that is half the distance from the data I/O
	 * with regards to the number of LUNs क्रमming the pblk instance. This
	 * balances LUN conflicts across every I/O.
	 *
	 * When the LUN configuration changes (e.g., due to GC), this distance
	 * can align, which would result on metadata and data I/Os colliding. In
	 * this हाल, modअगरy the distance to not be optimal, but move the
	 * optimal in the right direction.
	 */
	paddr = pblk_lookup_page(pblk, meta_line);
	ppa = addr_to_gen_ppa(pblk, paddr, 0);
	ppa_opt = addr_to_gen_ppa(pblk, paddr + data_line->meta_distance, 0);
	pos_opt = pblk_ppa_to_pos(geo, ppa_opt);

	अगर (test_bit(pos_opt, data_c_ctx->lun_biपंचांगap) ||
				test_bit(pos_opt, data_line->blk_biपंचांगap))
		वापस true;

	अगर (unlikely(pblk_ppa_comp(ppa_opt, ppa)))
		data_line->meta_distance--;

	वापस false;
पूर्ण

अटल काष्ठा pblk_line *pblk_should_submit_meta_io(काष्ठा pblk *pblk,
						    काष्ठा nvm_rq *data_rqd)
अणु
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा pblk_line *meta_line;

	spin_lock(&l_mg->बंद_lock);
	अगर (list_empty(&l_mg->emeta_list)) अणु
		spin_unlock(&l_mg->बंद_lock);
		वापस शून्य;
	पूर्ण
	meta_line = list_first_entry(&l_mg->emeta_list, काष्ठा pblk_line, list);
	अगर (meta_line->emeta->mem >= lm->emeta_len[0]) अणु
		spin_unlock(&l_mg->बंद_lock);
		वापस शून्य;
	पूर्ण
	spin_unlock(&l_mg->बंद_lock);

	अगर (!pblk_valid_meta_ppa(pblk, meta_line, data_rqd))
		वापस शून्य;

	वापस meta_line;
पूर्ण

अटल पूर्णांक pblk_submit_io_set(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd)
अणु
	काष्ठा ppa_addr erase_ppa;
	काष्ठा pblk_line *meta_line;
	पूर्णांक err;

	pblk_ppa_set_empty(&erase_ppa);

	/* Assign lbas to ppas and populate request काष्ठाure */
	err = pblk_setup_w_rq(pblk, rqd, &erase_ppa);
	अगर (err) अणु
		pblk_err(pblk, "could not setup write request: %d\n", err);
		वापस NVM_IO_ERR;
	पूर्ण

	meta_line = pblk_should_submit_meta_io(pblk, rqd);

	/* Submit data ग_लिखो क्रम current data line */
	err = pblk_submit_io(pblk, rqd, शून्य);
	अगर (err) अणु
		pblk_err(pblk, "data I/O submission failed: %d\n", err);
		वापस NVM_IO_ERR;
	पूर्ण

	अगर (!pblk_ppa_empty(erase_ppa)) अणु
		/* Submit erase क्रम next data line */
		अगर (pblk_blk_erase_async(pblk, erase_ppa)) अणु
			काष्ठा pblk_line *e_line = pblk_line_get_erase(pblk);
			काष्ठा nvm_tgt_dev *dev = pblk->dev;
			काष्ठा nvm_geo *geo = &dev->geo;
			पूर्णांक bit;

			atomic_inc(&e_line->left_eblks);
			bit = pblk_ppa_to_pos(geo, erase_ppa);
			WARN_ON(!test_and_clear_bit(bit, e_line->erase_biपंचांगap));
		पूर्ण
	पूर्ण

	अगर (meta_line) अणु
		/* Submit metadata ग_लिखो क्रम previous data line */
		err = pblk_submit_meta_io(pblk, meta_line);
		अगर (err) अणु
			pblk_err(pblk, "metadata I/O submission failed: %d",
					err);
			वापस NVM_IO_ERR;
		पूर्ण
	पूर्ण

	वापस NVM_IO_OK;
पूर्ण

अटल व्योम pblk_मुक्त_ग_लिखो_rqd(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd)
अणु
	काष्ठा pblk_c_ctx *c_ctx = nvm_rq_to_pdu(rqd);
	काष्ठा bio *bio = rqd->bio;

	अगर (c_ctx->nr_padded)
		pblk_bio_मुक्त_pages(pblk, bio, c_ctx->nr_valid,
							c_ctx->nr_padded);
पूर्ण

अटल पूर्णांक pblk_submit_ग_लिखो(काष्ठा pblk *pblk, पूर्णांक *secs_left)
अणु
	काष्ठा bio *bio;
	काष्ठा nvm_rq *rqd;
	अचिन्हित पूर्णांक secs_avail, secs_to_sync, secs_to_com;
	अचिन्हित पूर्णांक secs_to_flush, packed_meta_pgs;
	अचिन्हित दीर्घ pos;
	अचिन्हित पूर्णांक resubmit;

	*secs_left = 0;

	spin_lock(&pblk->resubmit_lock);
	resubmit = !list_empty(&pblk->resubmit_list);
	spin_unlock(&pblk->resubmit_lock);

	/* Resubmit failed ग_लिखोs first */
	अगर (resubmit) अणु
		काष्ठा pblk_c_ctx *r_ctx;

		spin_lock(&pblk->resubmit_lock);
		r_ctx = list_first_entry(&pblk->resubmit_list,
					काष्ठा pblk_c_ctx, list);
		list_del(&r_ctx->list);
		spin_unlock(&pblk->resubmit_lock);

		secs_avail = r_ctx->nr_valid;
		pos = r_ctx->sentry;

		pblk_prepare_resubmit(pblk, pos, secs_avail);
		secs_to_sync = pblk_calc_secs_to_sync(pblk, secs_avail,
				secs_avail);

		kमुक्त(r_ctx);
	पूर्ण अन्यथा अणु
		/* If there are no sectors in the cache,
		 * flushes (bios without data) will be cleared on
		 * the cache thपढ़ोs
		 */
		secs_avail = pblk_rb_पढ़ो_count(&pblk->rwb);
		अगर (!secs_avail)
			वापस 0;

		secs_to_flush = pblk_rb_flush_poपूर्णांक_count(&pblk->rwb);
		अगर (!secs_to_flush && secs_avail < pblk->min_ग_लिखो_pgs_data)
			वापस 0;

		secs_to_sync = pblk_calc_secs_to_sync(pblk, secs_avail,
					secs_to_flush);
		अगर (secs_to_sync > pblk->max_ग_लिखो_pgs) अणु
			pblk_err(pblk, "bad buffer sync calculation\n");
			वापस 0;
		पूर्ण

		secs_to_com = (secs_to_sync > secs_avail) ?
			secs_avail : secs_to_sync;
		pos = pblk_rb_पढ़ो_commit(&pblk->rwb, secs_to_com);
	पूर्ण

	packed_meta_pgs = (pblk->min_ग_लिखो_pgs - pblk->min_ग_लिखो_pgs_data);
	bio = bio_alloc(GFP_KERNEL, secs_to_sync + packed_meta_pgs);

	bio->bi_iter.bi_sector = 0; /* पूर्णांकernal bio */
	bio_set_op_attrs(bio, REQ_OP_WRITE, 0);

	rqd = pblk_alloc_rqd(pblk, PBLK_WRITE);
	rqd->bio = bio;

	अगर (pblk_rb_पढ़ो_to_bio(&pblk->rwb, rqd, pos, secs_to_sync,
								secs_avail)) अणु
		pblk_err(pblk, "corrupted write bio\n");
		जाओ fail_put_bio;
	पूर्ण

	अगर (pblk_submit_io_set(pblk, rqd))
		जाओ fail_मुक्त_bio;

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	atomic_दीर्घ_add(secs_to_sync, &pblk->sub_ग_लिखोs);
#पूर्ण_अगर

	*secs_left = 1;
	वापस 0;

fail_मुक्त_bio:
	pblk_मुक्त_ग_लिखो_rqd(pblk, rqd);
fail_put_bio:
	bio_put(bio);
	pblk_मुक्त_rqd(pblk, rqd, PBLK_WRITE);

	वापस -EINTR;
पूर्ण

पूर्णांक pblk_ग_लिखो_ts(व्योम *data)
अणु
	काष्ठा pblk *pblk = data;
	पूर्णांक secs_left;
	पूर्णांक ग_लिखो_failure = 0;

	जबतक (!kthपढ़ो_should_stop()) अणु
		अगर (!ग_लिखो_failure) अणु
			ग_लिखो_failure = pblk_submit_ग_लिखो(pblk, &secs_left);

			अगर (secs_left)
				जारी;
		पूर्ण
		set_current_state(TASK_INTERRUPTIBLE);
		io_schedule();
	पूर्ण

	वापस 0;
पूर्ण
