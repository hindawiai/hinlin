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
 * pblk-core.c - pblk's core functionality
 *
 */

#घोषणा CREATE_TRACE_POINTS

#समावेश "pblk.h"
#समावेश "pblk-trace.h"

अटल व्योम pblk_line_mark_bb(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pblk_line_ws *line_ws = container_of(work, काष्ठा pblk_line_ws,
									ws);
	काष्ठा pblk *pblk = line_ws->pblk;
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा ppa_addr *ppa = line_ws->priv;
	पूर्णांक ret;

	ret = nvm_set_chunk_meta(dev, ppa, 1, NVM_BLK_T_GRWN_BAD);
	अगर (ret) अणु
		काष्ठा pblk_line *line;
		पूर्णांक pos;

		line = pblk_ppa_to_line(pblk, *ppa);
		pos = pblk_ppa_to_pos(&dev->geo, *ppa);

		pblk_err(pblk, "failed to mark bb, line:%d, pos:%d\n",
				line->id, pos);
	पूर्ण

	kमुक्त(ppa);
	mempool_मुक्त(line_ws, &pblk->gen_ws_pool);
पूर्ण

अटल व्योम pblk_mark_bb(काष्ठा pblk *pblk, काष्ठा pblk_line *line,
			 काष्ठा ppa_addr ppa_addr)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा ppa_addr *ppa;
	पूर्णांक pos = pblk_ppa_to_pos(geo, ppa_addr);

	pblk_debug(pblk, "erase failed: line:%d, pos:%d\n", line->id, pos);
	atomic_दीर्घ_inc(&pblk->erase_failed);

	atomic_dec(&line->blk_in_line);
	अगर (test_and_set_bit(pos, line->blk_biपंचांगap))
		pblk_err(pblk, "attempted to erase bb: line:%d, pos:%d\n",
							line->id, pos);

	/* Not necessary to mark bad blocks on 2.0 spec. */
	अगर (geo->version == NVM_OCSSD_SPEC_20)
		वापस;

	ppa = kदो_स्मृति(माप(काष्ठा ppa_addr), GFP_ATOMIC);
	अगर (!ppa)
		वापस;

	*ppa = ppa_addr;
	pblk_gen_run_ws(pblk, शून्य, ppa, pblk_line_mark_bb,
						GFP_ATOMIC, pblk->bb_wq);
पूर्ण

अटल व्योम __pblk_end_io_erase(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा nvm_chk_meta *chunk;
	काष्ठा pblk_line *line;
	पूर्णांक pos;

	line = pblk_ppa_to_line(pblk, rqd->ppa_addr);
	pos = pblk_ppa_to_pos(geo, rqd->ppa_addr);
	chunk = &line->chks[pos];

	atomic_dec(&line->left_seblks);

	अगर (rqd->error) अणु
		trace_pblk_chunk_reset(pblk_disk_name(pblk),
				&rqd->ppa_addr, PBLK_CHUNK_RESET_FAILED);

		chunk->state = NVM_CHK_ST_OFFLINE;
		pblk_mark_bb(pblk, line, rqd->ppa_addr);
	पूर्ण अन्यथा अणु
		trace_pblk_chunk_reset(pblk_disk_name(pblk),
				&rqd->ppa_addr, PBLK_CHUNK_RESET_DONE);

		chunk->state = NVM_CHK_ST_FREE;
	पूर्ण

	trace_pblk_chunk_state(pblk_disk_name(pblk), &rqd->ppa_addr,
				chunk->state);

	atomic_dec(&pblk->inflight_io);
पूर्ण

/* Erase completion assumes that only one block is erased at the समय */
अटल व्योम pblk_end_io_erase(काष्ठा nvm_rq *rqd)
अणु
	काष्ठा pblk *pblk = rqd->निजी;

	__pblk_end_io_erase(pblk, rqd);
	mempool_मुक्त(rqd, &pblk->e_rq_pool);
पूर्ण

/*
 * Get inक्रमmation क्रम all chunks from the device.
 *
 * The caller is responsible क्रम मुक्तing (vदो_स्मृति) the वापसed काष्ठाure
 */
काष्ठा nvm_chk_meta *pblk_get_chunk_meta(काष्ठा pblk *pblk)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा nvm_chk_meta *meta;
	काष्ठा ppa_addr ppa;
	अचिन्हित दीर्घ len;
	पूर्णांक ret;

	ppa.ppa = 0;

	len = geo->all_chunks * माप(*meta);
	meta = vzalloc(len);
	अगर (!meta)
		वापस ERR_PTR(-ENOMEM);

	ret = nvm_get_chunk_meta(dev, ppa, geo->all_chunks, meta);
	अगर (ret) अणु
		vमुक्त(meta);
		वापस ERR_PTR(-EIO);
	पूर्ण

	वापस meta;
पूर्ण

काष्ठा nvm_chk_meta *pblk_chunk_get_off(काष्ठा pblk *pblk,
					      काष्ठा nvm_chk_meta *meta,
					      काष्ठा ppa_addr ppa)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	पूर्णांक ch_off = ppa.m.grp * geo->num_chk * geo->num_lun;
	पूर्णांक lun_off = ppa.m.pu * geo->num_chk;
	पूर्णांक chk_off = ppa.m.chk;

	वापस meta + ch_off + lun_off + chk_off;
पूर्ण

व्योम __pblk_map_invalidate(काष्ठा pblk *pblk, काष्ठा pblk_line *line,
			   u64 paddr)
अणु
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा list_head *move_list = शून्य;

	/* Lines being reclaimed (GC'ed) cannot be invalidated. Beक्रमe the L2P
	 * table is modअगरied with reclaimed sectors, a check is करोne to endure
	 * that newer updates are not overwritten.
	 */
	spin_lock(&line->lock);
	WARN_ON(line->state == PBLK_LINESTATE_FREE);

	अगर (test_and_set_bit(paddr, line->invalid_biपंचांगap)) अणु
		WARN_ONCE(1, "pblk: double invalidate\n");
		spin_unlock(&line->lock);
		वापस;
	पूर्ण
	le32_add_cpu(line->vsc, -1);

	अगर (line->state == PBLK_LINESTATE_CLOSED)
		move_list = pblk_line_gc_list(pblk, line);
	spin_unlock(&line->lock);

	अगर (move_list) अणु
		spin_lock(&l_mg->gc_lock);
		spin_lock(&line->lock);
		/* Prevent moving a line that has just been chosen क्रम GC */
		अगर (line->state == PBLK_LINESTATE_GC) अणु
			spin_unlock(&line->lock);
			spin_unlock(&l_mg->gc_lock);
			वापस;
		पूर्ण
		spin_unlock(&line->lock);

		list_move_tail(&line->list, move_list);
		spin_unlock(&l_mg->gc_lock);
	पूर्ण
पूर्ण

व्योम pblk_map_invalidate(काष्ठा pblk *pblk, काष्ठा ppa_addr ppa)
अणु
	काष्ठा pblk_line *line;
	u64 paddr;

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	/* Callers must ensure that the ppa poपूर्णांकs to a device address */
	BUG_ON(pblk_addr_in_cache(ppa));
	BUG_ON(pblk_ppa_empty(ppa));
#पूर्ण_अगर

	line = pblk_ppa_to_line(pblk, ppa);
	paddr = pblk_dev_ppa_to_line_addr(pblk, ppa);

	__pblk_map_invalidate(pblk, line, paddr);
पूर्ण

अटल व्योम pblk_invalidate_range(काष्ठा pblk *pblk, sector_t slba,
				  अचिन्हित पूर्णांक nr_secs)
अणु
	sector_t lba;

	spin_lock(&pblk->trans_lock);
	क्रम (lba = slba; lba < slba + nr_secs; lba++) अणु
		काष्ठा ppa_addr ppa;

		ppa = pblk_trans_map_get(pblk, lba);

		अगर (!pblk_addr_in_cache(ppa) && !pblk_ppa_empty(ppa))
			pblk_map_invalidate(pblk, ppa);

		pblk_ppa_set_empty(&ppa);
		pblk_trans_map_set(pblk, lba, ppa);
	पूर्ण
	spin_unlock(&pblk->trans_lock);
पूर्ण

पूर्णांक pblk_alloc_rqd_meta(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;

	rqd->meta_list = nvm_dev_dma_alloc(dev->parent, GFP_KERNEL,
							&rqd->dma_meta_list);
	अगर (!rqd->meta_list)
		वापस -ENOMEM;

	अगर (rqd->nr_ppas == 1)
		वापस 0;

	rqd->ppa_list = rqd->meta_list + pblk_dma_meta_size(pblk);
	rqd->dma_ppa_list = rqd->dma_meta_list + pblk_dma_meta_size(pblk);

	वापस 0;
पूर्ण

व्योम pblk_मुक्त_rqd_meta(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;

	अगर (rqd->meta_list)
		nvm_dev_dma_मुक्त(dev->parent, rqd->meta_list,
				rqd->dma_meta_list);
पूर्ण

/* Caller must guarantee that the request is a valid type */
काष्ठा nvm_rq *pblk_alloc_rqd(काष्ठा pblk *pblk, पूर्णांक type)
अणु
	mempool_t *pool;
	काष्ठा nvm_rq *rqd;
	पूर्णांक rq_size;

	चयन (type) अणु
	हाल PBLK_WRITE:
	हाल PBLK_WRITE_INT:
		pool = &pblk->w_rq_pool;
		rq_size = pblk_w_rq_size;
		अवरोध;
	हाल PBLK_READ:
		pool = &pblk->r_rq_pool;
		rq_size = pblk_g_rq_size;
		अवरोध;
	शेष:
		pool = &pblk->e_rq_pool;
		rq_size = pblk_g_rq_size;
	पूर्ण

	rqd = mempool_alloc(pool, GFP_KERNEL);
	स_रखो(rqd, 0, rq_size);

	वापस rqd;
पूर्ण

/* Typically used on completion path. Cannot guarantee request consistency */
व्योम pblk_मुक्त_rqd(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd, पूर्णांक type)
अणु
	mempool_t *pool;

	चयन (type) अणु
	हाल PBLK_WRITE:
		kमुक्त(((काष्ठा pblk_c_ctx *)nvm_rq_to_pdu(rqd))->lun_biपंचांगap);
		fallthrough;
	हाल PBLK_WRITE_INT:
		pool = &pblk->w_rq_pool;
		अवरोध;
	हाल PBLK_READ:
		pool = &pblk->r_rq_pool;
		अवरोध;
	हाल PBLK_ERASE:
		pool = &pblk->e_rq_pool;
		अवरोध;
	शेष:
		pblk_err(pblk, "trying to free unknown rqd type\n");
		वापस;
	पूर्ण

	pblk_मुक्त_rqd_meta(pblk, rqd);
	mempool_मुक्त(rqd, pool);
पूर्ण

व्योम pblk_bio_मुक्त_pages(काष्ठा pblk *pblk, काष्ठा bio *bio, पूर्णांक off,
			 पूर्णांक nr_pages)
अणु
	काष्ठा bio_vec *bv;
	काष्ठा page *page;
	पूर्णांक i, e, nbv = 0;

	क्रम (i = 0; i < bio->bi_vcnt; i++) अणु
		bv = &bio->bi_io_vec[i];
		page = bv->bv_page;
		क्रम (e = 0; e < bv->bv_len; e += PBLK_EXPOSED_PAGE_SIZE, nbv++)
			अगर (nbv >= off)
				mempool_मुक्त(page++, &pblk->page_bio_pool);
	पूर्ण
पूर्ण

पूर्णांक pblk_bio_add_pages(काष्ठा pblk *pblk, काष्ठा bio *bio, gfp_t flags,
		       पूर्णांक nr_pages)
अणु
	काष्ठा request_queue *q = pblk->dev->q;
	काष्ठा page *page;
	पूर्णांक i, ret;

	क्रम (i = 0; i < nr_pages; i++) अणु
		page = mempool_alloc(&pblk->page_bio_pool, flags);

		ret = bio_add_pc_page(q, bio, page, PBLK_EXPOSED_PAGE_SIZE, 0);
		अगर (ret != PBLK_EXPOSED_PAGE_SIZE) अणु
			pblk_err(pblk, "could not add page to bio\n");
			mempool_मुक्त(page, &pblk->page_bio_pool);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;
err:
	pblk_bio_मुक्त_pages(pblk, bio, (bio->bi_vcnt - i), i);
	वापस -1;
पूर्ण

व्योम pblk_ग_लिखो_kick(काष्ठा pblk *pblk)
अणु
	wake_up_process(pblk->ग_लिखोr_ts);
	mod_समयr(&pblk->wसमयr, jअगरfies + msecs_to_jअगरfies(1000));
पूर्ण

व्योम pblk_ग_लिखो_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा pblk *pblk = from_समयr(pblk, t, wसमयr);

	/* kick the ग_लिखो thपढ़ो every tick to flush outstanding data */
	pblk_ग_लिखो_kick(pblk);
पूर्ण

व्योम pblk_ग_लिखो_should_kick(काष्ठा pblk *pblk)
अणु
	अचिन्हित पूर्णांक secs_avail = pblk_rb_पढ़ो_count(&pblk->rwb);

	अगर (secs_avail >= pblk->min_ग_लिखो_pgs_data)
		pblk_ग_लिखो_kick(pblk);
पूर्ण

अटल व्योम pblk_रुको_क्रम_meta(काष्ठा pblk *pblk)
अणु
	करो अणु
		अगर (!atomic_पढ़ो(&pblk->inflight_io))
			अवरोध;

		schedule();
	पूर्ण जबतक (1);
पूर्ण

अटल व्योम pblk_flush_ग_लिखोr(काष्ठा pblk *pblk)
अणु
	pblk_rb_flush(&pblk->rwb);
	करो अणु
		अगर (!pblk_rb_sync_count(&pblk->rwb))
			अवरोध;

		pblk_ग_लिखो_kick(pblk);
		schedule();
	पूर्ण जबतक (1);
पूर्ण

काष्ठा list_head *pblk_line_gc_list(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा list_head *move_list = शून्य;
	पूर्णांक packed_meta = (le32_to_cpu(*line->vsc) / pblk->min_ग_लिखो_pgs_data)
			* (pblk->min_ग_लिखो_pgs - pblk->min_ग_लिखो_pgs_data);
	पूर्णांक vsc = le32_to_cpu(*line->vsc) + packed_meta;

	lockdep_निश्चित_held(&line->lock);

	अगर (line->w_err_gc->has_ग_लिखो_err) अणु
		अगर (line->gc_group != PBLK_LINEGC_WERR) अणु
			line->gc_group = PBLK_LINEGC_WERR;
			move_list = &l_mg->gc_werr_list;
			pblk_rl_werr_line_in(&pblk->rl);
		पूर्ण
	पूर्ण अन्यथा अगर (!vsc) अणु
		अगर (line->gc_group != PBLK_LINEGC_FULL) अणु
			line->gc_group = PBLK_LINEGC_FULL;
			move_list = &l_mg->gc_full_list;
		पूर्ण
	पूर्ण अन्यथा अगर (vsc < lm->high_thrs) अणु
		अगर (line->gc_group != PBLK_LINEGC_HIGH) अणु
			line->gc_group = PBLK_LINEGC_HIGH;
			move_list = &l_mg->gc_high_list;
		पूर्ण
	पूर्ण अन्यथा अगर (vsc < lm->mid_thrs) अणु
		अगर (line->gc_group != PBLK_LINEGC_MID) अणु
			line->gc_group = PBLK_LINEGC_MID;
			move_list = &l_mg->gc_mid_list;
		पूर्ण
	पूर्ण अन्यथा अगर (vsc < line->sec_in_line) अणु
		अगर (line->gc_group != PBLK_LINEGC_LOW) अणु
			line->gc_group = PBLK_LINEGC_LOW;
			move_list = &l_mg->gc_low_list;
		पूर्ण
	पूर्ण अन्यथा अगर (vsc == line->sec_in_line) अणु
		अगर (line->gc_group != PBLK_LINEGC_EMPTY) अणु
			line->gc_group = PBLK_LINEGC_EMPTY;
			move_list = &l_mg->gc_empty_list;
		पूर्ण
	पूर्ण अन्यथा अणु
		line->state = PBLK_LINESTATE_CORRUPT;
		trace_pblk_line_state(pblk_disk_name(pblk), line->id,
					line->state);

		line->gc_group = PBLK_LINEGC_NONE;
		move_list =  &l_mg->corrupt_list;
		pblk_err(pblk, "corrupted vsc for line %d, vsc:%d (%d/%d/%d)\n",
						line->id, vsc,
						line->sec_in_line,
						lm->high_thrs, lm->mid_thrs);
	पूर्ण

	वापस move_list;
पूर्ण

व्योम pblk_discard(काष्ठा pblk *pblk, काष्ठा bio *bio)
अणु
	sector_t slba = pblk_get_lba(bio);
	sector_t nr_secs = pblk_get_secs(bio);

	pblk_invalidate_range(pblk, slba, nr_secs);
पूर्ण

व्योम pblk_log_ग_लिखो_err(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd)
अणु
	atomic_दीर्घ_inc(&pblk->ग_लिखो_failed);
#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	pblk_prपूर्णांक_failed_rqd(pblk, rqd, rqd->error);
#पूर्ण_अगर
पूर्ण

व्योम pblk_log_पढ़ो_err(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd)
अणु
	/* Empty page पढ़ो is not necessarily an error (e.g., L2P recovery) */
	अगर (rqd->error == NVM_RSP_ERR_EMPTYPAGE) अणु
		atomic_दीर्घ_inc(&pblk->पढ़ो_empty);
		वापस;
	पूर्ण

	चयन (rqd->error) अणु
	हाल NVM_RSP_WARN_HIGHECC:
		atomic_दीर्घ_inc(&pblk->पढ़ो_high_ecc);
		अवरोध;
	हाल NVM_RSP_ERR_FAILECC:
	हाल NVM_RSP_ERR_FAILCRC:
		atomic_दीर्घ_inc(&pblk->पढ़ो_failed);
		अवरोध;
	शेष:
		pblk_err(pblk, "unknown read error:%d\n", rqd->error);
	पूर्ण
#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	pblk_prपूर्णांक_failed_rqd(pblk, rqd, rqd->error);
#पूर्ण_अगर
पूर्ण

व्योम pblk_set_sec_per_ग_लिखो(काष्ठा pblk *pblk, पूर्णांक sec_per_ग_लिखो)
अणु
	pblk->sec_per_ग_लिखो = sec_per_ग_लिखो;
पूर्ण

पूर्णांक pblk_submit_io(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd, व्योम *buf)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;

	atomic_inc(&pblk->inflight_io);

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	अगर (pblk_check_io(pblk, rqd))
		वापस NVM_IO_ERR;
#पूर्ण_अगर

	वापस nvm_submit_io(dev, rqd, buf);
पूर्ण

व्योम pblk_check_chunk_state_update(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd)
अणु
	काष्ठा ppa_addr *ppa_list = nvm_rq_to_ppa_list(rqd);

	पूर्णांक i;

	क्रम (i = 0; i < rqd->nr_ppas; i++) अणु
		काष्ठा ppa_addr *ppa = &ppa_list[i];
		काष्ठा nvm_chk_meta *chunk = pblk_dev_ppa_to_chunk(pblk, *ppa);
		u64 caddr = pblk_dev_ppa_to_chunk_addr(pblk, *ppa);

		अगर (caddr == 0)
			trace_pblk_chunk_state(pblk_disk_name(pblk),
							ppa, NVM_CHK_ST_OPEN);
		अन्यथा अगर (caddr == (chunk->cnlb - 1))
			trace_pblk_chunk_state(pblk_disk_name(pblk),
							ppa, NVM_CHK_ST_CLOSED);
	पूर्ण
पूर्ण

पूर्णांक pblk_submit_io_sync(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd, व्योम *buf)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	पूर्णांक ret;

	atomic_inc(&pblk->inflight_io);

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	अगर (pblk_check_io(pblk, rqd))
		वापस NVM_IO_ERR;
#पूर्ण_अगर

	ret = nvm_submit_io_sync(dev, rqd, buf);

	अगर (trace_pblk_chunk_state_enabled() && !ret &&
	    rqd->opcode == NVM_OP_PWRITE)
		pblk_check_chunk_state_update(pblk, rqd);

	वापस ret;
पूर्ण

अटल पूर्णांक pblk_submit_io_sync_sem(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd,
				   व्योम *buf)
अणु
	काष्ठा ppa_addr *ppa_list = nvm_rq_to_ppa_list(rqd);
	पूर्णांक ret;

	pblk_करोwn_chunk(pblk, ppa_list[0]);
	ret = pblk_submit_io_sync(pblk, rqd, buf);
	pblk_up_chunk(pblk, ppa_list[0]);

	वापस ret;
पूर्ण

पूर्णांक pblk_calc_secs(काष्ठा pblk *pblk, अचिन्हित दीर्घ secs_avail,
		   अचिन्हित दीर्घ secs_to_flush, bool skip_meta)
अणु
	पूर्णांक max = pblk->sec_per_ग_लिखो;
	पूर्णांक min = pblk->min_ग_लिखो_pgs;
	पूर्णांक secs_to_sync = 0;

	अगर (skip_meta && pblk->min_ग_लिखो_pgs_data != pblk->min_ग_लिखो_pgs)
		min = max = pblk->min_ग_लिखो_pgs_data;

	अगर (secs_avail >= max)
		secs_to_sync = max;
	अन्यथा अगर (secs_avail >= min)
		secs_to_sync = min * (secs_avail / min);
	अन्यथा अगर (secs_to_flush)
		secs_to_sync = min;

	वापस secs_to_sync;
पूर्ण

व्योम pblk_dealloc_page(काष्ठा pblk *pblk, काष्ठा pblk_line *line, पूर्णांक nr_secs)
अणु
	u64 addr;
	पूर्णांक i;

	spin_lock(&line->lock);
	addr = find_next_zero_bit(line->map_biपंचांगap,
					pblk->lm.sec_per_line, line->cur_sec);
	line->cur_sec = addr - nr_secs;

	क्रम (i = 0; i < nr_secs; i++, line->cur_sec--)
		WARN_ON(!test_and_clear_bit(line->cur_sec, line->map_biपंचांगap));
	spin_unlock(&line->lock);
पूर्ण

u64 __pblk_alloc_page(काष्ठा pblk *pblk, काष्ठा pblk_line *line, पूर्णांक nr_secs)
अणु
	u64 addr;
	पूर्णांक i;

	lockdep_निश्चित_held(&line->lock);

	/* logic error: ppa out-of-bounds. Prevent generating bad address */
	अगर (line->cur_sec + nr_secs > pblk->lm.sec_per_line) अणु
		WARN(1, "pblk: page allocation out of bounds\n");
		nr_secs = pblk->lm.sec_per_line - line->cur_sec;
	पूर्ण

	line->cur_sec = addr = find_next_zero_bit(line->map_biपंचांगap,
					pblk->lm.sec_per_line, line->cur_sec);
	क्रम (i = 0; i < nr_secs; i++, line->cur_sec++)
		WARN_ON(test_and_set_bit(line->cur_sec, line->map_biपंचांगap));

	वापस addr;
पूर्ण

u64 pblk_alloc_page(काष्ठा pblk *pblk, काष्ठा pblk_line *line, पूर्णांक nr_secs)
अणु
	u64 addr;

	/* Lock needed in हाल a ग_लिखो fails and a recovery needs to remap
	 * failed ग_लिखो buffer entries
	 */
	spin_lock(&line->lock);
	addr = __pblk_alloc_page(pblk, line, nr_secs);
	line->left_msecs -= nr_secs;
	WARN(line->left_msecs < 0, "pblk: page allocation out of bounds\n");
	spin_unlock(&line->lock);

	वापस addr;
पूर्ण

u64 pblk_lookup_page(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	u64 paddr;

	spin_lock(&line->lock);
	paddr = find_next_zero_bit(line->map_biपंचांगap,
					pblk->lm.sec_per_line, line->cur_sec);
	spin_unlock(&line->lock);

	वापस paddr;
पूर्ण

u64 pblk_line_smeta_start(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	पूर्णांक bit;

	/* This usually only happens on bad lines */
	bit = find_first_zero_bit(line->blk_biपंचांगap, lm->blk_per_line);
	अगर (bit >= lm->blk_per_line)
		वापस -1;

	वापस bit * geo->ws_opt;
पूर्ण

पूर्णांक pblk_line_smeta_पढ़ो(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा ppa_addr *ppa_list;
	काष्ठा nvm_rq rqd;
	u64 paddr = pblk_line_smeta_start(pblk, line);
	पूर्णांक i, ret;

	स_रखो(&rqd, 0, माप(काष्ठा nvm_rq));

	ret = pblk_alloc_rqd_meta(pblk, &rqd);
	अगर (ret)
		वापस ret;

	rqd.opcode = NVM_OP_PREAD;
	rqd.nr_ppas = lm->smeta_sec;
	rqd.is_seq = 1;
	ppa_list = nvm_rq_to_ppa_list(&rqd);

	क्रम (i = 0; i < lm->smeta_sec; i++, paddr++)
		ppa_list[i] = addr_to_gen_ppa(pblk, paddr, line->id);

	ret = pblk_submit_io_sync(pblk, &rqd, line->smeta);
	अगर (ret) अणु
		pblk_err(pblk, "smeta I/O submission failed: %d\n", ret);
		जाओ clear_rqd;
	पूर्ण

	atomic_dec(&pblk->inflight_io);

	अगर (rqd.error && rqd.error != NVM_RSP_WARN_HIGHECC) अणु
		pblk_log_पढ़ो_err(pblk, &rqd);
		ret = -EIO;
	पूर्ण

clear_rqd:
	pblk_मुक्त_rqd_meta(pblk, &rqd);
	वापस ret;
पूर्ण

अटल पूर्णांक pblk_line_smeta_ग_लिखो(काष्ठा pblk *pblk, काष्ठा pblk_line *line,
				 u64 paddr)
अणु
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा ppa_addr *ppa_list;
	काष्ठा nvm_rq rqd;
	__le64 *lba_list = emeta_to_lbas(pblk, line->emeta->buf);
	__le64 addr_empty = cpu_to_le64(ADDR_EMPTY);
	पूर्णांक i, ret;

	स_रखो(&rqd, 0, माप(काष्ठा nvm_rq));

	ret = pblk_alloc_rqd_meta(pblk, &rqd);
	अगर (ret)
		वापस ret;

	rqd.opcode = NVM_OP_PWRITE;
	rqd.nr_ppas = lm->smeta_sec;
	rqd.is_seq = 1;
	ppa_list = nvm_rq_to_ppa_list(&rqd);

	क्रम (i = 0; i < lm->smeta_sec; i++, paddr++) अणु
		काष्ठा pblk_sec_meta *meta = pblk_get_meta(pblk,
							   rqd.meta_list, i);

		ppa_list[i] = addr_to_gen_ppa(pblk, paddr, line->id);
		meta->lba = lba_list[paddr] = addr_empty;
	पूर्ण

	ret = pblk_submit_io_sync_sem(pblk, &rqd, line->smeta);
	अगर (ret) अणु
		pblk_err(pblk, "smeta I/O submission failed: %d\n", ret);
		जाओ clear_rqd;
	पूर्ण

	atomic_dec(&pblk->inflight_io);

	अगर (rqd.error) अणु
		pblk_log_ग_लिखो_err(pblk, &rqd);
		ret = -EIO;
	पूर्ण

clear_rqd:
	pblk_मुक्त_rqd_meta(pblk, &rqd);
	वापस ret;
पूर्ण

पूर्णांक pblk_line_emeta_पढ़ो(काष्ठा pblk *pblk, काष्ठा pblk_line *line,
			 व्योम *emeta_buf)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	व्योम *ppa_list_buf, *meta_list;
	काष्ठा ppa_addr *ppa_list;
	काष्ठा nvm_rq rqd;
	u64 paddr = line->emeta_ssec;
	dma_addr_t dma_ppa_list, dma_meta_list;
	पूर्णांक min = pblk->min_ग_लिखो_pgs;
	पूर्णांक left_ppas = lm->emeta_sec[0];
	पूर्णांक line_id = line->id;
	पूर्णांक rq_ppas, rq_len;
	पूर्णांक i, j;
	पूर्णांक ret;

	meta_list = nvm_dev_dma_alloc(dev->parent, GFP_KERNEL,
							&dma_meta_list);
	अगर (!meta_list)
		वापस -ENOMEM;

	ppa_list_buf = meta_list + pblk_dma_meta_size(pblk);
	dma_ppa_list = dma_meta_list + pblk_dma_meta_size(pblk);

next_rq:
	स_रखो(&rqd, 0, माप(काष्ठा nvm_rq));

	rq_ppas = pblk_calc_secs(pblk, left_ppas, 0, false);
	rq_len = rq_ppas * geo->csecs;

	rqd.meta_list = meta_list;
	rqd.ppa_list = ppa_list_buf;
	rqd.dma_meta_list = dma_meta_list;
	rqd.dma_ppa_list = dma_ppa_list;
	rqd.opcode = NVM_OP_PREAD;
	rqd.nr_ppas = rq_ppas;
	ppa_list = nvm_rq_to_ppa_list(&rqd);

	क्रम (i = 0; i < rqd.nr_ppas; ) अणु
		काष्ठा ppa_addr ppa = addr_to_gen_ppa(pblk, paddr, line_id);
		पूर्णांक pos = pblk_ppa_to_pos(geo, ppa);

		अगर (pblk_io_aligned(pblk, rq_ppas))
			rqd.is_seq = 1;

		जबतक (test_bit(pos, line->blk_biपंचांगap)) अणु
			paddr += min;
			अगर (pblk_boundary_paddr_checks(pblk, paddr)) अणु
				ret = -EINTR;
				जाओ मुक्त_rqd_dma;
			पूर्ण

			ppa = addr_to_gen_ppa(pblk, paddr, line_id);
			pos = pblk_ppa_to_pos(geo, ppa);
		पूर्ण

		अगर (pblk_boundary_paddr_checks(pblk, paddr + min)) अणु
			ret = -EINTR;
			जाओ मुक्त_rqd_dma;
		पूर्ण

		क्रम (j = 0; j < min; j++, i++, paddr++)
			ppa_list[i] = addr_to_gen_ppa(pblk, paddr, line_id);
	पूर्ण

	ret = pblk_submit_io_sync(pblk, &rqd, emeta_buf);
	अगर (ret) अणु
		pblk_err(pblk, "emeta I/O submission failed: %d\n", ret);
		जाओ मुक्त_rqd_dma;
	पूर्ण

	atomic_dec(&pblk->inflight_io);

	अगर (rqd.error && rqd.error != NVM_RSP_WARN_HIGHECC) अणु
		pblk_log_पढ़ो_err(pblk, &rqd);
		ret = -EIO;
		जाओ मुक्त_rqd_dma;
	पूर्ण

	emeta_buf += rq_len;
	left_ppas -= rq_ppas;
	अगर (left_ppas)
		जाओ next_rq;

मुक्त_rqd_dma:
	nvm_dev_dma_मुक्त(dev->parent, rqd.meta_list, rqd.dma_meta_list);
	वापस ret;
पूर्ण

अटल व्योम pblk_setup_e_rq(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd,
			    काष्ठा ppa_addr ppa)
अणु
	rqd->opcode = NVM_OP_ERASE;
	rqd->ppa_addr = ppa;
	rqd->nr_ppas = 1;
	rqd->is_seq = 1;
	rqd->bio = शून्य;
पूर्ण

अटल पूर्णांक pblk_blk_erase_sync(काष्ठा pblk *pblk, काष्ठा ppa_addr ppa)
अणु
	काष्ठा nvm_rq rqd = अणुशून्यपूर्ण;
	पूर्णांक ret;

	trace_pblk_chunk_reset(pblk_disk_name(pblk), &ppa,
				PBLK_CHUNK_RESET_START);

	pblk_setup_e_rq(pblk, &rqd, ppa);

	/* The ग_लिखो thपढ़ो schedules erases so that it minimizes disturbances
	 * with ग_लिखोs. Thus, there is no need to take the LUN semaphore.
	 */
	ret = pblk_submit_io_sync(pblk, &rqd, शून्य);
	rqd.निजी = pblk;
	__pblk_end_io_erase(pblk, &rqd);

	वापस ret;
पूर्ण

पूर्णांक pblk_line_erase(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा ppa_addr ppa;
	पूर्णांक ret, bit = -1;

	/* Erase only good blocks, one at a समय */
	करो अणु
		spin_lock(&line->lock);
		bit = find_next_zero_bit(line->erase_biपंचांगap, lm->blk_per_line,
								bit + 1);
		अगर (bit >= lm->blk_per_line) अणु
			spin_unlock(&line->lock);
			अवरोध;
		पूर्ण

		ppa = pblk->luns[bit].bppa; /* set ch and lun */
		ppa.a.blk = line->id;

		atomic_dec(&line->left_eblks);
		WARN_ON(test_and_set_bit(bit, line->erase_biपंचांगap));
		spin_unlock(&line->lock);

		ret = pblk_blk_erase_sync(pblk, ppa);
		अगर (ret) अणु
			pblk_err(pblk, "failed to erase line %d\n", line->id);
			वापस ret;
		पूर्ण
	पूर्ण जबतक (1);

	वापस 0;
पूर्ण

अटल व्योम pblk_line_setup_metadata(काष्ठा pblk_line *line,
				     काष्ठा pblk_line_mgmt *l_mg,
				     काष्ठा pblk_line_meta *lm)
अणु
	पूर्णांक meta_line;

	lockdep_निश्चित_held(&l_mg->मुक्त_lock);

retry_meta:
	meta_line = find_first_zero_bit(&l_mg->meta_biपंचांगap, PBLK_DATA_LINES);
	अगर (meta_line == PBLK_DATA_LINES) अणु
		spin_unlock(&l_mg->मुक्त_lock);
		io_schedule();
		spin_lock(&l_mg->मुक्त_lock);
		जाओ retry_meta;
	पूर्ण

	set_bit(meta_line, &l_mg->meta_biपंचांगap);
	line->meta_line = meta_line;

	line->smeta = l_mg->sline_meta[meta_line];
	line->emeta = l_mg->eline_meta[meta_line];

	स_रखो(line->smeta, 0, lm->smeta_len);
	स_रखो(line->emeta->buf, 0, lm->emeta_len[0]);

	line->emeta->mem = 0;
	atomic_set(&line->emeta->sync, 0);
पूर्ण

/* For now lines are always assumed full lines. Thus, smeta क्रमmer and current
 * lun biपंचांगaps are omitted.
 */
अटल पूर्णांक pblk_line_init_metadata(काष्ठा pblk *pblk, काष्ठा pblk_line *line,
				  काष्ठा pblk_line *cur)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा pblk_emeta *emeta = line->emeta;
	काष्ठा line_emeta *emeta_buf = emeta->buf;
	काष्ठा line_smeta *smeta_buf = (काष्ठा line_smeta *)line->smeta;
	पूर्णांक nr_blk_line;

	/* After erasing the line, new bad blocks might appear and we risk
	 * having an invalid line
	 */
	nr_blk_line = lm->blk_per_line -
			biपंचांगap_weight(line->blk_biपंचांगap, lm->blk_per_line);
	अगर (nr_blk_line < lm->min_blk_line) अणु
		spin_lock(&l_mg->मुक्त_lock);
		spin_lock(&line->lock);
		line->state = PBLK_LINESTATE_BAD;
		trace_pblk_line_state(pblk_disk_name(pblk), line->id,
					line->state);
		spin_unlock(&line->lock);

		list_add_tail(&line->list, &l_mg->bad_list);
		spin_unlock(&l_mg->मुक्त_lock);

		pblk_debug(pblk, "line %d is bad\n", line->id);

		वापस 0;
	पूर्ण

	/* Run-समय metadata */
	line->lun_biपंचांगap = ((व्योम *)(smeta_buf)) + माप(काष्ठा line_smeta);

	/* Mark LUNs allocated in this line (all क्रम now) */
	biपंचांगap_set(line->lun_biपंचांगap, 0, lm->lun_biपंचांगap_len);

	smeta_buf->header.identअगरier = cpu_to_le32(PBLK_MAGIC);
	export_guid(smeta_buf->header.uuid, &pblk->instance_uuid);
	smeta_buf->header.id = cpu_to_le32(line->id);
	smeta_buf->header.type = cpu_to_le16(line->type);
	smeta_buf->header.version_major = SMETA_VERSION_MAJOR;
	smeta_buf->header.version_minor = SMETA_VERSION_MINOR;

	/* Start metadata */
	smeta_buf->seq_nr = cpu_to_le64(line->seq_nr);
	smeta_buf->winकरोw_wr_lun = cpu_to_le32(geo->all_luns);

	/* Fill metadata among lines */
	अगर (cur) अणु
		स_नकल(line->lun_biपंचांगap, cur->lun_biपंचांगap, lm->lun_biपंचांगap_len);
		smeta_buf->prev_id = cpu_to_le32(cur->id);
		cur->emeta->buf->next_id = cpu_to_le32(line->id);
	पूर्ण अन्यथा अणु
		smeta_buf->prev_id = cpu_to_le32(PBLK_LINE_EMPTY);
	पूर्ण

	/* All smeta must be set at this poपूर्णांक */
	smeta_buf->header.crc = cpu_to_le32(
			pblk_calc_meta_header_crc(pblk, &smeta_buf->header));
	smeta_buf->crc = cpu_to_le32(pblk_calc_smeta_crc(pblk, smeta_buf));

	/* End metadata */
	स_नकल(&emeta_buf->header, &smeta_buf->header,
						माप(काष्ठा line_header));

	emeta_buf->header.version_major = EMETA_VERSION_MAJOR;
	emeta_buf->header.version_minor = EMETA_VERSION_MINOR;
	emeta_buf->header.crc = cpu_to_le32(
			pblk_calc_meta_header_crc(pblk, &emeta_buf->header));

	emeta_buf->seq_nr = cpu_to_le64(line->seq_nr);
	emeta_buf->nr_lbas = cpu_to_le64(line->sec_in_line);
	emeta_buf->nr_valid_lbas = cpu_to_le64(0);
	emeta_buf->next_id = cpu_to_le32(PBLK_LINE_EMPTY);
	emeta_buf->crc = cpu_to_le32(0);
	emeta_buf->prev_id = smeta_buf->prev_id;

	वापस 1;
पूर्ण

अटल पूर्णांक pblk_line_alloc_biपंचांगaps(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;

	line->map_biपंचांगap = mempool_alloc(l_mg->biपंचांगap_pool, GFP_KERNEL);
	अगर (!line->map_biपंचांगap)
		वापस -ENOMEM;

	स_रखो(line->map_biपंचांगap, 0, lm->sec_biपंचांगap_len);

	/* will be initialized using bb info from map_biपंचांगap */
	line->invalid_biपंचांगap = mempool_alloc(l_mg->biपंचांगap_pool, GFP_KERNEL);
	अगर (!line->invalid_biपंचांगap) अणु
		mempool_मुक्त(line->map_biपंचांगap, l_mg->biपंचांगap_pool);
		line->map_biपंचांगap = शून्य;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/* For now lines are always assumed full lines. Thus, smeta क्रमmer and current
 * lun biपंचांगaps are omitted.
 */
अटल पूर्णांक pblk_line_init_bb(काष्ठा pblk *pblk, काष्ठा pblk_line *line,
			     पूर्णांक init)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	u64 off;
	पूर्णांक bit = -1;
	पूर्णांक emeta_secs;

	line->sec_in_line = lm->sec_per_line;

	/* Capture bad block inक्रमmation on line mapping biपंचांगaps */
	जबतक ((bit = find_next_bit(line->blk_biपंचांगap, lm->blk_per_line,
					bit + 1)) < lm->blk_per_line) अणु
		off = bit * geo->ws_opt;
		biपंचांगap_shअगरt_left(l_mg->bb_aux, l_mg->bb_ढाँचा, off,
							lm->sec_per_line);
		biपंचांगap_or(line->map_biपंचांगap, line->map_biपंचांगap, l_mg->bb_aux,
							lm->sec_per_line);
		line->sec_in_line -= geo->clba;
	पूर्ण

	/* Mark smeta metadata sectors as bad sectors */
	bit = find_first_zero_bit(line->blk_biपंचांगap, lm->blk_per_line);
	off = bit * geo->ws_opt;
	biपंचांगap_set(line->map_biपंचांगap, off, lm->smeta_sec);
	line->sec_in_line -= lm->smeta_sec;
	line->cur_sec = off + lm->smeta_sec;

	अगर (init && pblk_line_smeta_ग_लिखो(pblk, line, off)) अणु
		pblk_debug(pblk, "line smeta I/O failed. Retry\n");
		वापस 0;
	पूर्ण

	biपंचांगap_copy(line->invalid_biपंचांगap, line->map_biपंचांगap, lm->sec_per_line);

	/* Mark emeta metadata sectors as bad sectors. We need to consider bad
	 * blocks to make sure that there are enough sectors to store emeta
	 */
	emeta_secs = lm->emeta_sec[0];
	off = lm->sec_per_line;
	जबतक (emeta_secs) अणु
		off -= geo->ws_opt;
		अगर (!test_bit(off, line->invalid_biपंचांगap)) अणु
			biपंचांगap_set(line->invalid_biपंचांगap, off, geo->ws_opt);
			emeta_secs -= geo->ws_opt;
		पूर्ण
	पूर्ण

	line->emeta_ssec = off;
	line->sec_in_line -= lm->emeta_sec[0];
	line->nr_valid_lbas = 0;
	line->left_msecs = line->sec_in_line;
	*line->vsc = cpu_to_le32(line->sec_in_line);

	अगर (lm->sec_per_line - line->sec_in_line !=
		biपंचांगap_weight(line->invalid_biपंचांगap, lm->sec_per_line)) अणु
		spin_lock(&line->lock);
		line->state = PBLK_LINESTATE_BAD;
		trace_pblk_line_state(pblk_disk_name(pblk), line->id,
					line->state);
		spin_unlock(&line->lock);

		list_add_tail(&line->list, &l_mg->bad_list);
		pblk_err(pblk, "unexpected line %d is bad\n", line->id);

		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक pblk_prepare_new_line(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	पूर्णांक blk_to_erase = atomic_पढ़ो(&line->blk_in_line);
	पूर्णांक i;

	क्रम (i = 0; i < lm->blk_per_line; i++) अणु
		काष्ठा pblk_lun *rlun = &pblk->luns[i];
		पूर्णांक pos = pblk_ppa_to_pos(geo, rlun->bppa);
		पूर्णांक state = line->chks[pos].state;

		/* Free chunks should not be erased */
		अगर (state & NVM_CHK_ST_FREE) अणु
			set_bit(pblk_ppa_to_pos(geo, rlun->bppa),
							line->erase_biपंचांगap);
			blk_to_erase--;
		पूर्ण
	पूर्ण

	वापस blk_to_erase;
पूर्ण

अटल पूर्णांक pblk_line_prepare(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	पूर्णांक blk_in_line = atomic_पढ़ो(&line->blk_in_line);
	पूर्णांक blk_to_erase;

	/* Bad blocks करो not need to be erased */
	biपंचांगap_copy(line->erase_biपंचांगap, line->blk_biपंचांगap, lm->blk_per_line);

	spin_lock(&line->lock);

	/* If we have not written to this line, we need to mark up मुक्त chunks
	 * as alपढ़ोy erased
	 */
	अगर (line->state == PBLK_LINESTATE_NEW) अणु
		blk_to_erase = pblk_prepare_new_line(pblk, line);
		line->state = PBLK_LINESTATE_FREE;
		trace_pblk_line_state(pblk_disk_name(pblk), line->id,
					line->state);
	पूर्ण अन्यथा अणु
		blk_to_erase = blk_in_line;
	पूर्ण

	अगर (blk_in_line < lm->min_blk_line) अणु
		spin_unlock(&line->lock);
		वापस -EAGAIN;
	पूर्ण

	अगर (line->state != PBLK_LINESTATE_FREE) अणु
		WARN(1, "pblk: corrupted line %d, state %d\n",
							line->id, line->state);
		spin_unlock(&line->lock);
		वापस -EINTR;
	पूर्ण

	line->state = PBLK_LINESTATE_OPEN;
	trace_pblk_line_state(pblk_disk_name(pblk), line->id,
				line->state);

	atomic_set(&line->left_eblks, blk_to_erase);
	atomic_set(&line->left_seblks, blk_to_erase);

	line->meta_distance = lm->meta_distance;
	spin_unlock(&line->lock);

	kref_init(&line->ref);
	atomic_set(&line->sec_to_update, 0);

	वापस 0;
पूर्ण

/* Line allocations in the recovery path are always single thपढ़ोed */
पूर्णांक pblk_line_recov_alloc(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	पूर्णांक ret;

	spin_lock(&l_mg->मुक्त_lock);
	l_mg->data_line = line;
	list_del(&line->list);

	ret = pblk_line_prepare(pblk, line);
	अगर (ret) अणु
		list_add(&line->list, &l_mg->मुक्त_list);
		spin_unlock(&l_mg->मुक्त_lock);
		वापस ret;
	पूर्ण
	spin_unlock(&l_mg->मुक्त_lock);

	ret = pblk_line_alloc_biपंचांगaps(pblk, line);
	अगर (ret)
		जाओ fail;

	अगर (!pblk_line_init_bb(pblk, line, 0)) अणु
		ret = -EINTR;
		जाओ fail;
	पूर्ण

	pblk_rl_मुक्त_lines_dec(&pblk->rl, line, true);
	वापस 0;

fail:
	spin_lock(&l_mg->मुक्त_lock);
	list_add(&line->list, &l_mg->मुक्त_list);
	spin_unlock(&l_mg->मुक्त_lock);

	वापस ret;
पूर्ण

व्योम pblk_line_recov_बंद(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;

	mempool_मुक्त(line->map_biपंचांगap, l_mg->biपंचांगap_pool);
	line->map_biपंचांगap = शून्य;
	line->smeta = शून्य;
	line->emeta = शून्य;
पूर्ण

अटल व्योम pblk_line_reinit(काष्ठा pblk_line *line)
अणु
	*line->vsc = cpu_to_le32(EMPTY_ENTRY);

	line->map_biपंचांगap = शून्य;
	line->invalid_biपंचांगap = शून्य;
	line->smeta = शून्य;
	line->emeta = शून्य;
पूर्ण

व्योम pblk_line_मुक्त(काष्ठा pblk_line *line)
अणु
	काष्ठा pblk *pblk = line->pblk;
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;

	mempool_मुक्त(line->map_biपंचांगap, l_mg->biपंचांगap_pool);
	mempool_मुक्त(line->invalid_biपंचांगap, l_mg->biपंचांगap_pool);

	pblk_line_reinit(line);
पूर्ण

काष्ठा pblk_line *pblk_line_get(काष्ठा pblk *pblk)
अणु
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा pblk_line *line;
	पूर्णांक ret, bit;

	lockdep_निश्चित_held(&l_mg->मुक्त_lock);

retry:
	अगर (list_empty(&l_mg->मुक्त_list)) अणु
		pblk_err(pblk, "no free lines\n");
		वापस शून्य;
	पूर्ण

	line = list_first_entry(&l_mg->मुक्त_list, काष्ठा pblk_line, list);
	list_del(&line->list);
	l_mg->nr_मुक्त_lines--;

	bit = find_first_zero_bit(line->blk_biपंचांगap, lm->blk_per_line);
	अगर (unlikely(bit >= lm->blk_per_line)) अणु
		spin_lock(&line->lock);
		line->state = PBLK_LINESTATE_BAD;
		trace_pblk_line_state(pblk_disk_name(pblk), line->id,
					line->state);
		spin_unlock(&line->lock);

		list_add_tail(&line->list, &l_mg->bad_list);

		pblk_debug(pblk, "line %d is bad\n", line->id);
		जाओ retry;
	पूर्ण

	ret = pblk_line_prepare(pblk, line);
	अगर (ret) अणु
		चयन (ret) अणु
		हाल -EAGAIN:
			list_add(&line->list, &l_mg->bad_list);
			जाओ retry;
		हाल -EINTR:
			list_add(&line->list, &l_mg->corrupt_list);
			जाओ retry;
		शेष:
			pblk_err(pblk, "failed to prepare line %d\n", line->id);
			list_add(&line->list, &l_mg->मुक्त_list);
			l_mg->nr_मुक्त_lines++;
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस line;
पूर्ण

अटल काष्ठा pblk_line *pblk_line_retry(काष्ठा pblk *pblk,
					 काष्ठा pblk_line *line)
अणु
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा pblk_line *retry_line;

retry:
	spin_lock(&l_mg->मुक्त_lock);
	retry_line = pblk_line_get(pblk);
	अगर (!retry_line) अणु
		l_mg->data_line = शून्य;
		spin_unlock(&l_mg->मुक्त_lock);
		वापस शून्य;
	पूर्ण

	retry_line->map_biपंचांगap = line->map_biपंचांगap;
	retry_line->invalid_biपंचांगap = line->invalid_biपंचांगap;
	retry_line->smeta = line->smeta;
	retry_line->emeta = line->emeta;
	retry_line->meta_line = line->meta_line;

	pblk_line_reinit(line);

	l_mg->data_line = retry_line;
	spin_unlock(&l_mg->मुक्त_lock);

	pblk_rl_मुक्त_lines_dec(&pblk->rl, line, false);

	अगर (pblk_line_erase(pblk, retry_line))
		जाओ retry;

	वापस retry_line;
पूर्ण

अटल व्योम pblk_set_space_limit(काष्ठा pblk *pblk)
अणु
	काष्ठा pblk_rl *rl = &pblk->rl;

	atomic_set(&rl->rb_space, 0);
पूर्ण

काष्ठा pblk_line *pblk_line_get_first_data(काष्ठा pblk *pblk)
अणु
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा pblk_line *line;

	spin_lock(&l_mg->मुक्त_lock);
	line = pblk_line_get(pblk);
	अगर (!line) अणु
		spin_unlock(&l_mg->मुक्त_lock);
		वापस शून्य;
	पूर्ण

	line->seq_nr = l_mg->d_seq_nr++;
	line->type = PBLK_LINETYPE_DATA;
	l_mg->data_line = line;

	pblk_line_setup_metadata(line, l_mg, &pblk->lm);

	/* Allocate next line क्रम preparation */
	l_mg->data_next = pblk_line_get(pblk);
	अगर (!l_mg->data_next) अणु
		/* If we cannot get a new line, we need to stop the pipeline.
		 * Only allow as many ग_लिखोs in as we can store safely and then
		 * fail gracefully
		 */
		pblk_set_space_limit(pblk);

		l_mg->data_next = शून्य;
	पूर्ण अन्यथा अणु
		l_mg->data_next->seq_nr = l_mg->d_seq_nr++;
		l_mg->data_next->type = PBLK_LINETYPE_DATA;
	पूर्ण
	spin_unlock(&l_mg->मुक्त_lock);

	अगर (pblk_line_alloc_biपंचांगaps(pblk, line))
		वापस शून्य;

	अगर (pblk_line_erase(pblk, line)) अणु
		line = pblk_line_retry(pblk, line);
		अगर (!line)
			वापस शून्य;
	पूर्ण

retry_setup:
	अगर (!pblk_line_init_metadata(pblk, line, शून्य)) अणु
		line = pblk_line_retry(pblk, line);
		अगर (!line)
			वापस शून्य;

		जाओ retry_setup;
	पूर्ण

	अगर (!pblk_line_init_bb(pblk, line, 1)) अणु
		line = pblk_line_retry(pblk, line);
		अगर (!line)
			वापस शून्य;

		जाओ retry_setup;
	पूर्ण

	pblk_rl_मुक्त_lines_dec(&pblk->rl, line, true);

	वापस line;
पूर्ण

व्योम pblk_ppa_to_line_put(काष्ठा pblk *pblk, काष्ठा ppa_addr ppa)
अणु
	काष्ठा pblk_line *line;

	line = pblk_ppa_to_line(pblk, ppa);
	kref_put(&line->ref, pblk_line_put_wq);
पूर्ण

व्योम pblk_rq_to_line_put(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd)
अणु
	काष्ठा ppa_addr *ppa_list = nvm_rq_to_ppa_list(rqd);
	पूर्णांक i;

	क्रम (i = 0; i < rqd->nr_ppas; i++)
		pblk_ppa_to_line_put(pblk, ppa_list[i]);
पूर्ण

अटल व्योम pblk_stop_ग_लिखोs(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	lockdep_निश्चित_held(&pblk->l_mg.मुक्त_lock);

	pblk_set_space_limit(pblk);
	pblk->state = PBLK_STATE_STOPPING;
	trace_pblk_state(pblk_disk_name(pblk), pblk->state);
पूर्ण

अटल व्योम pblk_line_बंद_meta_sync(काष्ठा pblk *pblk)
अणु
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा pblk_line *line, *tline;
	LIST_HEAD(list);

	spin_lock(&l_mg->बंद_lock);
	अगर (list_empty(&l_mg->emeta_list)) अणु
		spin_unlock(&l_mg->बंद_lock);
		वापस;
	पूर्ण

	list_cut_position(&list, &l_mg->emeta_list, l_mg->emeta_list.prev);
	spin_unlock(&l_mg->बंद_lock);

	list_क्रम_each_entry_safe(line, tline, &list, list) अणु
		काष्ठा pblk_emeta *emeta = line->emeta;

		जबतक (emeta->mem < lm->emeta_len[0]) अणु
			पूर्णांक ret;

			ret = pblk_submit_meta_io(pblk, line);
			अगर (ret) अणु
				pblk_err(pblk, "sync meta line %d failed (%d)\n",
							line->id, ret);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	pblk_रुको_क्रम_meta(pblk);
	flush_workqueue(pblk->बंद_wq);
पूर्ण

व्योम __pblk_pipeline_flush(काष्ठा pblk *pblk)
अणु
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	पूर्णांक ret;

	spin_lock(&l_mg->मुक्त_lock);
	अगर (pblk->state == PBLK_STATE_RECOVERING ||
					pblk->state == PBLK_STATE_STOPPED) अणु
		spin_unlock(&l_mg->मुक्त_lock);
		वापस;
	पूर्ण
	pblk->state = PBLK_STATE_RECOVERING;
	trace_pblk_state(pblk_disk_name(pblk), pblk->state);
	spin_unlock(&l_mg->मुक्त_lock);

	pblk_flush_ग_लिखोr(pblk);
	pblk_रुको_क्रम_meta(pblk);

	ret = pblk_recov_pad(pblk);
	अगर (ret) अणु
		pblk_err(pblk, "could not close data on teardown(%d)\n", ret);
		वापस;
	पूर्ण

	flush_workqueue(pblk->bb_wq);
	pblk_line_बंद_meta_sync(pblk);
पूर्ण

व्योम __pblk_pipeline_stop(काष्ठा pblk *pblk)
अणु
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;

	spin_lock(&l_mg->मुक्त_lock);
	pblk->state = PBLK_STATE_STOPPED;
	trace_pblk_state(pblk_disk_name(pblk), pblk->state);
	l_mg->data_line = शून्य;
	l_mg->data_next = शून्य;
	spin_unlock(&l_mg->मुक्त_lock);
पूर्ण

व्योम pblk_pipeline_stop(काष्ठा pblk *pblk)
अणु
	__pblk_pipeline_flush(pblk);
	__pblk_pipeline_stop(pblk);
पूर्ण

काष्ठा pblk_line *pblk_line_replace_data(काष्ठा pblk *pblk)
अणु
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा pblk_line *cur, *new = शून्य;
	अचिन्हित पूर्णांक left_seblks;

	new = l_mg->data_next;
	अगर (!new)
		जाओ out;

	spin_lock(&l_mg->मुक्त_lock);
	cur = l_mg->data_line;
	l_mg->data_line = new;

	pblk_line_setup_metadata(new, l_mg, &pblk->lm);
	spin_unlock(&l_mg->मुक्त_lock);

retry_erase:
	left_seblks = atomic_पढ़ो(&new->left_seblks);
	अगर (left_seblks) अणु
		/* If line is not fully erased, erase it */
		अगर (atomic_पढ़ो(&new->left_eblks)) अणु
			अगर (pblk_line_erase(pblk, new))
				जाओ out;
		पूर्ण अन्यथा अणु
			io_schedule();
		पूर्ण
		जाओ retry_erase;
	पूर्ण

	अगर (pblk_line_alloc_biपंचांगaps(pblk, new))
		वापस शून्य;

retry_setup:
	अगर (!pblk_line_init_metadata(pblk, new, cur)) अणु
		new = pblk_line_retry(pblk, new);
		अगर (!new)
			जाओ out;

		जाओ retry_setup;
	पूर्ण

	अगर (!pblk_line_init_bb(pblk, new, 1)) अणु
		new = pblk_line_retry(pblk, new);
		अगर (!new)
			जाओ out;

		जाओ retry_setup;
	पूर्ण

	pblk_rl_मुक्त_lines_dec(&pblk->rl, new, true);

	/* Allocate next line क्रम preparation */
	spin_lock(&l_mg->मुक्त_lock);
	l_mg->data_next = pblk_line_get(pblk);
	अगर (!l_mg->data_next) अणु
		/* If we cannot get a new line, we need to stop the pipeline.
		 * Only allow as many ग_लिखोs in as we can store safely and then
		 * fail gracefully
		 */
		pblk_stop_ग_लिखोs(pblk, new);
		l_mg->data_next = शून्य;
	पूर्ण अन्यथा अणु
		l_mg->data_next->seq_nr = l_mg->d_seq_nr++;
		l_mg->data_next->type = PBLK_LINETYPE_DATA;
	पूर्ण
	spin_unlock(&l_mg->मुक्त_lock);

out:
	वापस new;
पूर्ण

अटल व्योम __pblk_line_put(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा pblk_gc *gc = &pblk->gc;

	spin_lock(&line->lock);
	WARN_ON(line->state != PBLK_LINESTATE_GC);
	अगर (line->w_err_gc->has_gc_err) अणु
		spin_unlock(&line->lock);
		pblk_err(pblk, "line %d had errors during GC\n", line->id);
		pblk_put_line_back(pblk, line);
		line->w_err_gc->has_gc_err = 0;
		वापस;
	पूर्ण

	line->state = PBLK_LINESTATE_FREE;
	trace_pblk_line_state(pblk_disk_name(pblk), line->id,
					line->state);
	line->gc_group = PBLK_LINEGC_NONE;
	pblk_line_मुक्त(line);

	अगर (line->w_err_gc->has_ग_लिखो_err) अणु
		pblk_rl_werr_line_out(&pblk->rl);
		line->w_err_gc->has_ग_लिखो_err = 0;
	पूर्ण

	spin_unlock(&line->lock);
	atomic_dec(&gc->pipeline_gc);

	spin_lock(&l_mg->मुक्त_lock);
	list_add_tail(&line->list, &l_mg->मुक्त_list);
	l_mg->nr_मुक्त_lines++;
	spin_unlock(&l_mg->मुक्त_lock);

	pblk_rl_मुक्त_lines_inc(&pblk->rl, line);
पूर्ण

अटल व्योम pblk_line_put_ws(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pblk_line_ws *line_put_ws = container_of(work,
						काष्ठा pblk_line_ws, ws);
	काष्ठा pblk *pblk = line_put_ws->pblk;
	काष्ठा pblk_line *line = line_put_ws->line;

	__pblk_line_put(pblk, line);
	mempool_मुक्त(line_put_ws, &pblk->gen_ws_pool);
पूर्ण

व्योम pblk_line_put(काष्ठा kref *ref)
अणु
	काष्ठा pblk_line *line = container_of(ref, काष्ठा pblk_line, ref);
	काष्ठा pblk *pblk = line->pblk;

	__pblk_line_put(pblk, line);
पूर्ण

व्योम pblk_line_put_wq(काष्ठा kref *ref)
अणु
	काष्ठा pblk_line *line = container_of(ref, काष्ठा pblk_line, ref);
	काष्ठा pblk *pblk = line->pblk;
	काष्ठा pblk_line_ws *line_put_ws;

	line_put_ws = mempool_alloc(&pblk->gen_ws_pool, GFP_ATOMIC);
	अगर (!line_put_ws)
		वापस;

	line_put_ws->pblk = pblk;
	line_put_ws->line = line;
	line_put_ws->priv = शून्य;

	INIT_WORK(&line_put_ws->ws, pblk_line_put_ws);
	queue_work(pblk->r_end_wq, &line_put_ws->ws);
पूर्ण

पूर्णांक pblk_blk_erase_async(काष्ठा pblk *pblk, काष्ठा ppa_addr ppa)
अणु
	काष्ठा nvm_rq *rqd;
	पूर्णांक err;

	rqd = pblk_alloc_rqd(pblk, PBLK_ERASE);

	pblk_setup_e_rq(pblk, rqd, ppa);

	rqd->end_io = pblk_end_io_erase;
	rqd->निजी = pblk;

	trace_pblk_chunk_reset(pblk_disk_name(pblk),
				&ppa, PBLK_CHUNK_RESET_START);

	/* The ग_लिखो thपढ़ो schedules erases so that it minimizes disturbances
	 * with ग_लिखोs. Thus, there is no need to take the LUN semaphore.
	 */
	err = pblk_submit_io(pblk, rqd, शून्य);
	अगर (err) अणु
		काष्ठा nvm_tgt_dev *dev = pblk->dev;
		काष्ठा nvm_geo *geo = &dev->geo;

		pblk_err(pblk, "could not async erase line:%d,blk:%d\n",
					pblk_ppa_to_line_id(ppa),
					pblk_ppa_to_pos(geo, ppa));
	पूर्ण

	वापस err;
पूर्ण

काष्ठा pblk_line *pblk_line_get_data(काष्ठा pblk *pblk)
अणु
	वापस pblk->l_mg.data_line;
पूर्ण

/* For now, always erase next line */
काष्ठा pblk_line *pblk_line_get_erase(काष्ठा pblk *pblk)
अणु
	वापस pblk->l_mg.data_next;
पूर्ण

पूर्णांक pblk_line_is_full(काष्ठा pblk_line *line)
अणु
	वापस (line->left_msecs == 0);
पूर्ण

अटल व्योम pblk_line_should_sync_meta(काष्ठा pblk *pblk)
अणु
	अगर (pblk_rl_is_limit(&pblk->rl))
		pblk_line_बंद_meta_sync(pblk);
पूर्ण

व्योम pblk_line_बंद(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा list_head *move_list;
	पूर्णांक i;

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	WARN(!biपंचांगap_full(line->map_biपंचांगap, lm->sec_per_line),
				"pblk: corrupt closed line %d\n", line->id);
#पूर्ण_अगर

	spin_lock(&l_mg->मुक्त_lock);
	WARN_ON(!test_and_clear_bit(line->meta_line, &l_mg->meta_biपंचांगap));
	spin_unlock(&l_mg->मुक्त_lock);

	spin_lock(&l_mg->gc_lock);
	spin_lock(&line->lock);
	WARN_ON(line->state != PBLK_LINESTATE_OPEN);
	line->state = PBLK_LINESTATE_CLOSED;
	move_list = pblk_line_gc_list(pblk, line);
	list_add_tail(&line->list, move_list);

	mempool_मुक्त(line->map_biपंचांगap, l_mg->biपंचांगap_pool);
	line->map_biपंचांगap = शून्य;
	line->smeta = शून्य;
	line->emeta = शून्य;

	क्रम (i = 0; i < lm->blk_per_line; i++) अणु
		काष्ठा pblk_lun *rlun = &pblk->luns[i];
		पूर्णांक pos = pblk_ppa_to_pos(geo, rlun->bppa);
		पूर्णांक state = line->chks[pos].state;

		अगर (!(state & NVM_CHK_ST_OFFLINE))
			state = NVM_CHK_ST_CLOSED;
	पूर्ण

	spin_unlock(&line->lock);
	spin_unlock(&l_mg->gc_lock);

	trace_pblk_line_state(pblk_disk_name(pblk), line->id,
					line->state);
पूर्ण

व्योम pblk_line_बंद_meta(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा pblk_emeta *emeta = line->emeta;
	काष्ठा line_emeta *emeta_buf = emeta->buf;
	काष्ठा wa_counters *wa = emeta_to_wa(lm, emeta_buf);

	/* No need क्रम exact vsc value; aव्योम a big line lock and take aprox. */
	स_नकल(emeta_to_vsc(pblk, emeta_buf), l_mg->vsc_list, lm->vsc_list_len);
	स_नकल(emeta_to_bb(emeta_buf), line->blk_biपंचांगap, lm->blk_biपंचांगap_len);

	wa->user = cpu_to_le64(atomic64_पढ़ो(&pblk->user_wa));
	wa->pad = cpu_to_le64(atomic64_पढ़ो(&pblk->pad_wa));
	wa->gc = cpu_to_le64(atomic64_पढ़ो(&pblk->gc_wa));

	अगर (le32_to_cpu(emeta_buf->header.identअगरier) != PBLK_MAGIC) अणु
		emeta_buf->header.identअगरier = cpu_to_le32(PBLK_MAGIC);
		export_guid(emeta_buf->header.uuid, &pblk->instance_uuid);
		emeta_buf->header.id = cpu_to_le32(line->id);
		emeta_buf->header.type = cpu_to_le16(line->type);
		emeta_buf->header.version_major = EMETA_VERSION_MAJOR;
		emeta_buf->header.version_minor = EMETA_VERSION_MINOR;
		emeta_buf->header.crc = cpu_to_le32(
			pblk_calc_meta_header_crc(pblk, &emeta_buf->header));
	पूर्ण

	emeta_buf->nr_valid_lbas = cpu_to_le64(line->nr_valid_lbas);
	emeta_buf->crc = cpu_to_le32(pblk_calc_emeta_crc(pblk, emeta_buf));

	spin_lock(&l_mg->बंद_lock);
	spin_lock(&line->lock);

	/* Update the in-memory start address क्रम emeta, in हाल it has
	 * shअगरted due to ग_लिखो errors
	 */
	अगर (line->emeta_ssec != line->cur_sec)
		line->emeta_ssec = line->cur_sec;

	list_add_tail(&line->list, &l_mg->emeta_list);
	spin_unlock(&line->lock);
	spin_unlock(&l_mg->बंद_lock);

	pblk_line_should_sync_meta(pblk);
पूर्ण

अटल व्योम pblk_save_lba_list(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	अचिन्हित पूर्णांक lba_list_size = lm->emeta_len[2];
	काष्ठा pblk_w_err_gc *w_err_gc = line->w_err_gc;
	काष्ठा pblk_emeta *emeta = line->emeta;

	w_err_gc->lba_list = kvदो_स्मृति(lba_list_size, GFP_KERNEL);
	स_नकल(w_err_gc->lba_list, emeta_to_lbas(pblk, emeta->buf),
				lba_list_size);
पूर्ण

व्योम pblk_line_बंद_ws(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pblk_line_ws *line_ws = container_of(work, काष्ठा pblk_line_ws,
									ws);
	काष्ठा pblk *pblk = line_ws->pblk;
	काष्ठा pblk_line *line = line_ws->line;
	काष्ठा pblk_w_err_gc *w_err_gc = line->w_err_gc;

	/* Write errors makes the emeta start address stored in smeta invalid,
	 * so keep a copy of the lba list until we've gc'd the line
	 */
	अगर (w_err_gc->has_ग_लिखो_err)
		pblk_save_lba_list(pblk, line);

	pblk_line_बंद(pblk, line);
	mempool_मुक्त(line_ws, &pblk->gen_ws_pool);
पूर्ण

व्योम pblk_gen_run_ws(काष्ठा pblk *pblk, काष्ठा pblk_line *line, व्योम *priv,
		      व्योम (*work)(काष्ठा work_काष्ठा *), gfp_t gfp_mask,
		      काष्ठा workqueue_काष्ठा *wq)
अणु
	काष्ठा pblk_line_ws *line_ws;

	line_ws = mempool_alloc(&pblk->gen_ws_pool, gfp_mask);
	अगर (!line_ws) अणु
		pblk_err(pblk, "pblk: could not allocate memory\n");
		वापस;
	पूर्ण

	line_ws->pblk = pblk;
	line_ws->line = line;
	line_ws->priv = priv;

	INIT_WORK(&line_ws->ws, work);
	queue_work(wq, &line_ws->ws);
पूर्ण

अटल व्योम __pblk_करोwn_chunk(काष्ठा pblk *pblk, पूर्णांक pos)
अणु
	काष्ठा pblk_lun *rlun = &pblk->luns[pos];
	पूर्णांक ret;

	/*
	 * Only send one inflight I/O per LUN. Since we map at a page
	 * granurality, all ppas in the I/O will map to the same LUN
	 */

	ret = करोwn_समयout(&rlun->wr_sem, msecs_to_jअगरfies(30000));
	अगर (ret == -ETIME || ret == -EINTR)
		pblk_err(pblk, "taking lun semaphore timed out: err %d\n",
				-ret);
पूर्ण

व्योम pblk_करोwn_chunk(काष्ठा pblk *pblk, काष्ठा ppa_addr ppa)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	पूर्णांक pos = pblk_ppa_to_pos(geo, ppa);

	__pblk_करोwn_chunk(pblk, pos);
पूर्ण

व्योम pblk_करोwn_rq(काष्ठा pblk *pblk, काष्ठा ppa_addr ppa,
		  अचिन्हित दीर्घ *lun_biपंचांगap)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	पूर्णांक pos = pblk_ppa_to_pos(geo, ppa);

	/* If the LUN has been locked क्रम this same request, करो no attempt to
	 * lock it again
	 */
	अगर (test_and_set_bit(pos, lun_biपंचांगap))
		वापस;

	__pblk_करोwn_chunk(pblk, pos);
पूर्ण

व्योम pblk_up_chunk(काष्ठा pblk *pblk, काष्ठा ppa_addr ppa)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा pblk_lun *rlun;
	पूर्णांक pos = pblk_ppa_to_pos(geo, ppa);

	rlun = &pblk->luns[pos];
	up(&rlun->wr_sem);
पूर्ण

व्योम pblk_up_rq(काष्ठा pblk *pblk, अचिन्हित दीर्घ *lun_biपंचांगap)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा pblk_lun *rlun;
	पूर्णांक num_lun = geo->all_luns;
	पूर्णांक bit = -1;

	जबतक ((bit = find_next_bit(lun_biपंचांगap, num_lun, bit + 1)) < num_lun) अणु
		rlun = &pblk->luns[bit];
		up(&rlun->wr_sem);
	पूर्ण
पूर्ण

व्योम pblk_update_map(काष्ठा pblk *pblk, sector_t lba, काष्ठा ppa_addr ppa)
अणु
	काष्ठा ppa_addr ppa_l2p;

	/* logic error: lba out-of-bounds. Ignore update */
	अगर (!(lba < pblk->capacity)) अणु
		WARN(1, "pblk: corrupted L2P map request\n");
		वापस;
	पूर्ण

	spin_lock(&pblk->trans_lock);
	ppa_l2p = pblk_trans_map_get(pblk, lba);

	अगर (!pblk_addr_in_cache(ppa_l2p) && !pblk_ppa_empty(ppa_l2p))
		pblk_map_invalidate(pblk, ppa_l2p);

	pblk_trans_map_set(pblk, lba, ppa);
	spin_unlock(&pblk->trans_lock);
पूर्ण

व्योम pblk_update_map_cache(काष्ठा pblk *pblk, sector_t lba, काष्ठा ppa_addr ppa)
अणु

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	/* Callers must ensure that the ppa poपूर्णांकs to a cache address */
	BUG_ON(!pblk_addr_in_cache(ppa));
	BUG_ON(pblk_rb_pos_oob(&pblk->rwb, pblk_addr_to_cacheline(ppa)));
#पूर्ण_अगर

	pblk_update_map(pblk, lba, ppa);
पूर्ण

पूर्णांक pblk_update_map_gc(काष्ठा pblk *pblk, sector_t lba, काष्ठा ppa_addr ppa_new,
		       काष्ठा pblk_line *gc_line, u64 paddr_gc)
अणु
	काष्ठा ppa_addr ppa_l2p, ppa_gc;
	पूर्णांक ret = 1;

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	/* Callers must ensure that the ppa poपूर्णांकs to a cache address */
	BUG_ON(!pblk_addr_in_cache(ppa_new));
	BUG_ON(pblk_rb_pos_oob(&pblk->rwb, pblk_addr_to_cacheline(ppa_new)));
#पूर्ण_अगर

	/* logic error: lba out-of-bounds. Ignore update */
	अगर (!(lba < pblk->capacity)) अणु
		WARN(1, "pblk: corrupted L2P map request\n");
		वापस 0;
	पूर्ण

	spin_lock(&pblk->trans_lock);
	ppa_l2p = pblk_trans_map_get(pblk, lba);
	ppa_gc = addr_to_gen_ppa(pblk, paddr_gc, gc_line->id);

	अगर (!pblk_ppa_comp(ppa_l2p, ppa_gc)) अणु
		spin_lock(&gc_line->lock);
		WARN(!test_bit(paddr_gc, gc_line->invalid_biपंचांगap),
						"pblk: corrupted GC update");
		spin_unlock(&gc_line->lock);

		ret = 0;
		जाओ out;
	पूर्ण

	pblk_trans_map_set(pblk, lba, ppa_new);
out:
	spin_unlock(&pblk->trans_lock);
	वापस ret;
पूर्ण

व्योम pblk_update_map_dev(काष्ठा pblk *pblk, sector_t lba,
			 काष्ठा ppa_addr ppa_mapped, काष्ठा ppa_addr ppa_cache)
अणु
	काष्ठा ppa_addr ppa_l2p;

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	/* Callers must ensure that the ppa poपूर्णांकs to a device address */
	BUG_ON(pblk_addr_in_cache(ppa_mapped));
#पूर्ण_अगर
	/* Invalidate and discard padded entries */
	अगर (lba == ADDR_EMPTY) अणु
		atomic64_inc(&pblk->pad_wa);
#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
		atomic_दीर्घ_inc(&pblk->padded_wb);
#पूर्ण_अगर
		अगर (!pblk_ppa_empty(ppa_mapped))
			pblk_map_invalidate(pblk, ppa_mapped);
		वापस;
	पूर्ण

	/* logic error: lba out-of-bounds. Ignore update */
	अगर (!(lba < pblk->capacity)) अणु
		WARN(1, "pblk: corrupted L2P map request\n");
		वापस;
	पूर्ण

	spin_lock(&pblk->trans_lock);
	ppa_l2p = pblk_trans_map_get(pblk, lba);

	/* Do not update L2P अगर the cacheline has been updated. In this हाल,
	 * the mapped ppa must be invalidated
	 */
	अगर (!pblk_ppa_comp(ppa_l2p, ppa_cache)) अणु
		अगर (!pblk_ppa_empty(ppa_mapped))
			pblk_map_invalidate(pblk, ppa_mapped);
		जाओ out;
	पूर्ण

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	WARN_ON(!pblk_addr_in_cache(ppa_l2p) && !pblk_ppa_empty(ppa_l2p));
#पूर्ण_अगर

	pblk_trans_map_set(pblk, lba, ppa_mapped);
out:
	spin_unlock(&pblk->trans_lock);
पूर्ण

पूर्णांक pblk_lookup_l2p_seq(काष्ठा pblk *pblk, काष्ठा ppa_addr *ppas,
			 sector_t blba, पूर्णांक nr_secs, bool *from_cache)
अणु
	पूर्णांक i;

	spin_lock(&pblk->trans_lock);
	क्रम (i = 0; i < nr_secs; i++) अणु
		काष्ठा ppa_addr ppa;

		ppa = ppas[i] = pblk_trans_map_get(pblk, blba + i);

		/* If the L2P entry maps to a line, the reference is valid */
		अगर (!pblk_ppa_empty(ppa) && !pblk_addr_in_cache(ppa)) अणु
			काष्ठा pblk_line *line = pblk_ppa_to_line(pblk, ppa);

			अगर (i > 0 && *from_cache)
				अवरोध;
			*from_cache = false;

			kref_get(&line->ref);
		पूर्ण अन्यथा अणु
			अगर (i > 0 && !*from_cache)
				अवरोध;
			*from_cache = true;
		पूर्ण
	पूर्ण
	spin_unlock(&pblk->trans_lock);
	वापस i;
पूर्ण

व्योम pblk_lookup_l2p_अक्रम(काष्ठा pblk *pblk, काष्ठा ppa_addr *ppas,
			  u64 *lba_list, पूर्णांक nr_secs)
अणु
	u64 lba;
	पूर्णांक i;

	spin_lock(&pblk->trans_lock);
	क्रम (i = 0; i < nr_secs; i++) अणु
		lba = lba_list[i];
		अगर (lba != ADDR_EMPTY) अणु
			/* logic error: lba out-of-bounds. Ignore update */
			अगर (!(lba < pblk->capacity)) अणु
				WARN(1, "pblk: corrupted L2P map request\n");
				जारी;
			पूर्ण
			ppas[i] = pblk_trans_map_get(pblk, lba);
		पूर्ण
	पूर्ण
	spin_unlock(&pblk->trans_lock);
पूर्ण

व्योम *pblk_get_meta_क्रम_ग_लिखोs(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd)
अणु
	व्योम *buffer;

	अगर (pblk_is_oob_meta_supported(pblk)) अणु
		/* Just use OOB metadata buffer as always */
		buffer = rqd->meta_list;
	पूर्ण अन्यथा अणु
		/* We need to reuse last page of request (packed metadata)
		 * in similar way as traditional oob metadata
		 */
		buffer = page_to_virt(
			rqd->bio->bi_io_vec[rqd->bio->bi_vcnt - 1].bv_page);
	पूर्ण

	वापस buffer;
पूर्ण

व्योम pblk_get_packed_meta(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd)
अणु
	व्योम *meta_list = rqd->meta_list;
	व्योम *page;
	पूर्णांक i = 0;

	अगर (pblk_is_oob_meta_supported(pblk))
		वापस;

	page = page_to_virt(rqd->bio->bi_io_vec[rqd->bio->bi_vcnt - 1].bv_page);
	/* We need to fill oob meta buffer with data from packed metadata */
	क्रम (; i < rqd->nr_ppas; i++)
		स_नकल(pblk_get_meta(pblk, meta_list, i),
			page + (i * माप(काष्ठा pblk_sec_meta)),
			माप(काष्ठा pblk_sec_meta));
पूर्ण
