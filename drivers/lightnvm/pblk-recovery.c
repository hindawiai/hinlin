<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2016 CNEX Lअसल
 * Initial: Javier Gonzalez <javier@cnexद_असल.com>
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
 * pblk-recovery.c - pblk's recovery path
 *
 * The L2P recovery path is single thपढ़ोed as the L2P table is updated in order
 * following the line sequence ID.
 */

#समावेश "pblk.h"
#समावेश "pblk-trace.h"

पूर्णांक pblk_recov_check_emeta(काष्ठा pblk *pblk, काष्ठा line_emeta *emeta_buf)
अणु
	u32 crc;

	crc = pblk_calc_emeta_crc(pblk, emeta_buf);
	अगर (le32_to_cpu(emeta_buf->crc) != crc)
		वापस 1;

	अगर (le32_to_cpu(emeta_buf->header.identअगरier) != PBLK_MAGIC)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक pblk_recov_l2p_from_emeta(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा pblk_emeta *emeta = line->emeta;
	काष्ठा line_emeta *emeta_buf = emeta->buf;
	__le64 *lba_list;
	u64 data_start, data_end;
	u64 nr_valid_lbas, nr_lbas = 0;
	u64 i;

	lba_list = emeta_to_lbas(pblk, emeta_buf);
	अगर (!lba_list)
		वापस 1;

	data_start = pblk_line_smeta_start(pblk, line) + lm->smeta_sec;
	data_end = line->emeta_ssec;
	nr_valid_lbas = le64_to_cpu(emeta_buf->nr_valid_lbas);

	क्रम (i = data_start; i < data_end; i++) अणु
		काष्ठा ppa_addr ppa;
		पूर्णांक pos;

		ppa = addr_to_gen_ppa(pblk, i, line->id);
		pos = pblk_ppa_to_pos(geo, ppa);

		/* Do not update bad blocks */
		अगर (test_bit(pos, line->blk_biपंचांगap))
			जारी;

		अगर (le64_to_cpu(lba_list[i]) == ADDR_EMPTY) अणु
			spin_lock(&line->lock);
			अगर (test_and_set_bit(i, line->invalid_biपंचांगap))
				WARN_ONCE(1, "pblk: rec. double invalidate:\n");
			अन्यथा
				le32_add_cpu(line->vsc, -1);
			spin_unlock(&line->lock);

			जारी;
		पूर्ण

		pblk_update_map(pblk, le64_to_cpu(lba_list[i]), ppa);
		nr_lbas++;
	पूर्ण

	अगर (nr_valid_lbas != nr_lbas)
		pblk_err(pblk, "line %d - inconsistent lba list(%llu/%llu)\n",
				line->id, nr_valid_lbas, nr_lbas);

	line->left_msecs = 0;

	वापस 0;
पूर्ण

अटल व्योम pblk_update_line_wp(काष्ठा pblk *pblk, काष्ठा pblk_line *line,
				u64 written_secs)
अणु
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	पूर्णांक i;

	क्रम (i = 0; i < written_secs; i += pblk->min_ग_लिखो_pgs)
		__pblk_alloc_page(pblk, line, pblk->min_ग_लिखो_pgs);

	spin_lock(&l_mg->मुक्त_lock);
	अगर (written_secs > line->left_msecs) अणु
		/*
		 * We have all data sectors written
		 * and some emeta sectors written too.
		 */
		line->left_msecs = 0;
	पूर्ण अन्यथा अणु
		/* We have only some data sectors written. */
		line->left_msecs -= written_secs;
	पूर्ण
	spin_unlock(&l_mg->मुक्त_lock);
पूर्ण

अटल u64 pblk_sec_in_खोलो_line(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	पूर्णांक nr_bb = biपंचांगap_weight(line->blk_biपंचांगap, lm->blk_per_line);
	u64 written_secs = 0;
	पूर्णांक valid_chunks = 0;
	पूर्णांक i;

	क्रम (i = 0; i < lm->blk_per_line; i++) अणु
		काष्ठा nvm_chk_meta *chunk = &line->chks[i];

		अगर (chunk->state & NVM_CHK_ST_OFFLINE)
			जारी;

		written_secs += chunk->wp;
		valid_chunks++;
	पूर्ण

	अगर (lm->blk_per_line - nr_bb != valid_chunks)
		pblk_err(pblk, "recovery line %d is bad\n", line->id);

	pblk_update_line_wp(pblk, line, written_secs - lm->smeta_sec);

	वापस written_secs;
पूर्ण

काष्ठा pblk_recov_alloc अणु
	काष्ठा ppa_addr *ppa_list;
	व्योम *meta_list;
	काष्ठा nvm_rq *rqd;
	व्योम *data;
	dma_addr_t dma_ppa_list;
	dma_addr_t dma_meta_list;
पूर्ण;

अटल व्योम pblk_recov_complete(काष्ठा kref *ref)
अणु
	काष्ठा pblk_pad_rq *pad_rq = container_of(ref, काष्ठा pblk_pad_rq, ref);

	complete(&pad_rq->रुको);
पूर्ण

अटल व्योम pblk_end_io_recov(काष्ठा nvm_rq *rqd)
अणु
	काष्ठा ppa_addr *ppa_list = nvm_rq_to_ppa_list(rqd);
	काष्ठा pblk_pad_rq *pad_rq = rqd->निजी;
	काष्ठा pblk *pblk = pad_rq->pblk;

	pblk_up_chunk(pblk, ppa_list[0]);

	pblk_मुक्त_rqd(pblk, rqd, PBLK_WRITE_INT);

	atomic_dec(&pblk->inflight_io);
	kref_put(&pad_rq->ref, pblk_recov_complete);
पूर्ण

/* pad line using line biपंचांगap.  */
अटल पूर्णांक pblk_recov_pad_line(काष्ठा pblk *pblk, काष्ठा pblk_line *line,
			       पूर्णांक left_ppas)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	व्योम *meta_list;
	काष्ठा pblk_pad_rq *pad_rq;
	काष्ठा nvm_rq *rqd;
	काष्ठा ppa_addr *ppa_list;
	व्योम *data;
	__le64 *lba_list = emeta_to_lbas(pblk, line->emeta->buf);
	u64 w_ptr = line->cur_sec;
	पूर्णांक left_line_ppas, rq_ppas;
	पूर्णांक i, j;
	पूर्णांक ret = 0;

	spin_lock(&line->lock);
	left_line_ppas = line->left_msecs;
	spin_unlock(&line->lock);

	pad_rq = kदो_स्मृति(माप(काष्ठा pblk_pad_rq), GFP_KERNEL);
	अगर (!pad_rq)
		वापस -ENOMEM;

	data = vzalloc(array_size(pblk->max_ग_लिखो_pgs, geo->csecs));
	अगर (!data) अणु
		ret = -ENOMEM;
		जाओ मुक्त_rq;
	पूर्ण

	pad_rq->pblk = pblk;
	init_completion(&pad_rq->रुको);
	kref_init(&pad_rq->ref);

next_pad_rq:
	rq_ppas = pblk_calc_secs(pblk, left_ppas, 0, false);
	अगर (rq_ppas < pblk->min_ग_लिखो_pgs) अणु
		pblk_err(pblk, "corrupted pad line %d\n", line->id);
		जाओ fail_complete;
	पूर्ण

	rqd = pblk_alloc_rqd(pblk, PBLK_WRITE_INT);

	ret = pblk_alloc_rqd_meta(pblk, rqd);
	अगर (ret) अणु
		pblk_मुक्त_rqd(pblk, rqd, PBLK_WRITE_INT);
		जाओ fail_complete;
	पूर्ण

	rqd->bio = शून्य;
	rqd->opcode = NVM_OP_PWRITE;
	rqd->is_seq = 1;
	rqd->nr_ppas = rq_ppas;
	rqd->end_io = pblk_end_io_recov;
	rqd->निजी = pad_rq;

	ppa_list = nvm_rq_to_ppa_list(rqd);
	meta_list = rqd->meta_list;

	क्रम (i = 0; i < rqd->nr_ppas; ) अणु
		काष्ठा ppa_addr ppa;
		पूर्णांक pos;

		w_ptr = pblk_alloc_page(pblk, line, pblk->min_ग_लिखो_pgs);
		ppa = addr_to_gen_ppa(pblk, w_ptr, line->id);
		pos = pblk_ppa_to_pos(geo, ppa);

		जबतक (test_bit(pos, line->blk_biपंचांगap)) अणु
			w_ptr += pblk->min_ग_लिखो_pgs;
			ppa = addr_to_gen_ppa(pblk, w_ptr, line->id);
			pos = pblk_ppa_to_pos(geo, ppa);
		पूर्ण

		क्रम (j = 0; j < pblk->min_ग_लिखो_pgs; j++, i++, w_ptr++) अणु
			काष्ठा ppa_addr dev_ppa;
			काष्ठा pblk_sec_meta *meta;
			__le64 addr_empty = cpu_to_le64(ADDR_EMPTY);

			dev_ppa = addr_to_gen_ppa(pblk, w_ptr, line->id);

			pblk_map_invalidate(pblk, dev_ppa);
			lba_list[w_ptr] = addr_empty;
			meta = pblk_get_meta(pblk, meta_list, i);
			meta->lba = addr_empty;
			ppa_list[i] = dev_ppa;
		पूर्ण
	पूर्ण

	kref_get(&pad_rq->ref);
	pblk_करोwn_chunk(pblk, ppa_list[0]);

	ret = pblk_submit_io(pblk, rqd, data);
	अगर (ret) अणु
		pblk_err(pblk, "I/O submission failed: %d\n", ret);
		pblk_up_chunk(pblk, ppa_list[0]);
		kref_put(&pad_rq->ref, pblk_recov_complete);
		pblk_मुक्त_rqd(pblk, rqd, PBLK_WRITE_INT);
		जाओ fail_complete;
	पूर्ण

	left_line_ppas -= rq_ppas;
	left_ppas -= rq_ppas;
	अगर (left_ppas && left_line_ppas)
		जाओ next_pad_rq;

fail_complete:
	kref_put(&pad_rq->ref, pblk_recov_complete);
	रुको_क्रम_completion(&pad_rq->रुको);

	अगर (!pblk_line_is_full(line))
		pblk_err(pblk, "corrupted padded line: %d\n", line->id);

	vमुक्त(data);
मुक्त_rq:
	kमुक्त(pad_rq);
	वापस ret;
पूर्ण

अटल पूर्णांक pblk_pad_distance(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	पूर्णांक distance = geo->mw_cunits * geo->all_luns * geo->ws_opt;

	वापस (distance > line->left_msecs) ? line->left_msecs : distance;
पूर्ण

/* Return a chunk beदीर्घing to a line by stripe(ग_लिखो order) index */
अटल काष्ठा nvm_chk_meta *pblk_get_stripe_chunk(काष्ठा pblk *pblk,
						  काष्ठा pblk_line *line,
						  पूर्णांक index)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा pblk_lun *rlun;
	काष्ठा ppa_addr ppa;
	पूर्णांक pos;

	rlun = &pblk->luns[index];
	ppa = rlun->bppa;
	pos = pblk_ppa_to_pos(geo, ppa);

	वापस &line->chks[pos];
पूर्ण

अटल पूर्णांक pblk_line_wps_are_unbalanced(काष्ठा pblk *pblk,
				      काष्ठा pblk_line *line)
अणु
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	पूर्णांक blk_in_line = lm->blk_per_line;
	काष्ठा nvm_chk_meta *chunk;
	u64 max_wp, min_wp;
	पूर्णांक i;

	i = find_first_zero_bit(line->blk_biपंचांगap, blk_in_line);

	/* If there is one or zero good chunks in the line,
	 * the ग_लिखो poपूर्णांकers can't be unbalanced.
	 */
	अगर (i >= (blk_in_line - 1))
		वापस 0;

	chunk = pblk_get_stripe_chunk(pblk, line, i);
	max_wp = chunk->wp;
	अगर (max_wp > pblk->max_ग_लिखो_pgs)
		min_wp = max_wp - pblk->max_ग_लिखो_pgs;
	अन्यथा
		min_wp = 0;

	i = find_next_zero_bit(line->blk_biपंचांगap, blk_in_line, i + 1);
	जबतक (i < blk_in_line) अणु
		chunk = pblk_get_stripe_chunk(pblk, line, i);
		अगर (chunk->wp > max_wp || chunk->wp < min_wp)
			वापस 1;

		i = find_next_zero_bit(line->blk_biपंचांगap, blk_in_line, i + 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pblk_recov_scan_oob(काष्ठा pblk *pblk, काष्ठा pblk_line *line,
			       काष्ठा pblk_recov_alloc p)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा ppa_addr *ppa_list;
	व्योम *meta_list;
	काष्ठा nvm_rq *rqd;
	व्योम *data;
	dma_addr_t dma_ppa_list, dma_meta_list;
	__le64 *lba_list;
	u64 paddr = pblk_line_smeta_start(pblk, line) + lm->smeta_sec;
	bool padded = false;
	पूर्णांक rq_ppas;
	पूर्णांक i, j;
	पूर्णांक ret;
	u64 left_ppas = pblk_sec_in_खोलो_line(pblk, line) - lm->smeta_sec;

	अगर (pblk_line_wps_are_unbalanced(pblk, line))
		pblk_warn(pblk, "recovering unbalanced line (%d)\n", line->id);

	ppa_list = p.ppa_list;
	meta_list = p.meta_list;
	rqd = p.rqd;
	data = p.data;
	dma_ppa_list = p.dma_ppa_list;
	dma_meta_list = p.dma_meta_list;

	lba_list = emeta_to_lbas(pblk, line->emeta->buf);

next_rq:
	स_रखो(rqd, 0, pblk_g_rq_size);

	rq_ppas = pblk_calc_secs(pblk, left_ppas, 0, false);
	अगर (!rq_ppas)
		rq_ppas = pblk->min_ग_लिखो_pgs;

retry_rq:
	rqd->bio = शून्य;
	rqd->opcode = NVM_OP_PREAD;
	rqd->meta_list = meta_list;
	rqd->nr_ppas = rq_ppas;
	rqd->ppa_list = ppa_list;
	rqd->dma_ppa_list = dma_ppa_list;
	rqd->dma_meta_list = dma_meta_list;
	ppa_list = nvm_rq_to_ppa_list(rqd);

	अगर (pblk_io_aligned(pblk, rq_ppas))
		rqd->is_seq = 1;

	क्रम (i = 0; i < rqd->nr_ppas; ) अणु
		काष्ठा ppa_addr ppa;
		पूर्णांक pos;

		ppa = addr_to_gen_ppa(pblk, paddr, line->id);
		pos = pblk_ppa_to_pos(geo, ppa);

		जबतक (test_bit(pos, line->blk_biपंचांगap)) अणु
			paddr += pblk->min_ग_लिखो_pgs;
			ppa = addr_to_gen_ppa(pblk, paddr, line->id);
			pos = pblk_ppa_to_pos(geo, ppa);
		पूर्ण

		क्रम (j = 0; j < pblk->min_ग_लिखो_pgs; j++, i++)
			ppa_list[i] =
				addr_to_gen_ppa(pblk, paddr + j, line->id);
	पूर्ण

	ret = pblk_submit_io_sync(pblk, rqd, data);
	अगर (ret) अणु
		pblk_err(pblk, "I/O submission failed: %d\n", ret);
		वापस ret;
	पूर्ण

	atomic_dec(&pblk->inflight_io);

	/* If a पढ़ो fails, करो a best efक्रमt by padding the line and retrying */
	अगर (rqd->error && rqd->error != NVM_RSP_WARN_HIGHECC) अणु
		पूर्णांक pad_distance, ret;

		अगर (padded) अणु
			pblk_log_पढ़ो_err(pblk, rqd);
			वापस -EINTR;
		पूर्ण

		pad_distance = pblk_pad_distance(pblk, line);
		ret = pblk_recov_pad_line(pblk, line, pad_distance);
		अगर (ret) अणु
			वापस ret;
		पूर्ण

		padded = true;
		जाओ retry_rq;
	पूर्ण

	pblk_get_packed_meta(pblk, rqd);

	क्रम (i = 0; i < rqd->nr_ppas; i++) अणु
		काष्ठा pblk_sec_meta *meta = pblk_get_meta(pblk, meta_list, i);
		u64 lba = le64_to_cpu(meta->lba);

		lba_list[paddr++] = cpu_to_le64(lba);

		अगर (lba == ADDR_EMPTY || lba >= pblk->capacity)
			जारी;

		line->nr_valid_lbas++;
		pblk_update_map(pblk, lba, ppa_list[i]);
	पूर्ण

	left_ppas -= rq_ppas;
	अगर (left_ppas > 0)
		जाओ next_rq;

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	WARN_ON(padded && !pblk_line_is_full(line));
#पूर्ण_अगर

	वापस 0;
पूर्ण

/* Scan line क्रम lbas on out of bound area */
अटल पूर्णांक pblk_recov_l2p_from_oob(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा nvm_rq *rqd;
	काष्ठा ppa_addr *ppa_list;
	व्योम *meta_list;
	काष्ठा pblk_recov_alloc p;
	व्योम *data;
	dma_addr_t dma_ppa_list, dma_meta_list;
	पूर्णांक ret = 0;

	meta_list = nvm_dev_dma_alloc(dev->parent, GFP_KERNEL, &dma_meta_list);
	अगर (!meta_list)
		वापस -ENOMEM;

	ppa_list = (व्योम *)(meta_list) + pblk_dma_meta_size(pblk);
	dma_ppa_list = dma_meta_list + pblk_dma_meta_size(pblk);

	data = kसुस्मृति(pblk->max_ग_लिखो_pgs, geo->csecs, GFP_KERNEL);
	अगर (!data) अणु
		ret = -ENOMEM;
		जाओ मुक्त_meta_list;
	पूर्ण

	rqd = mempool_alloc(&pblk->r_rq_pool, GFP_KERNEL);
	स_रखो(rqd, 0, pblk_g_rq_size);

	p.ppa_list = ppa_list;
	p.meta_list = meta_list;
	p.rqd = rqd;
	p.data = data;
	p.dma_ppa_list = dma_ppa_list;
	p.dma_meta_list = dma_meta_list;

	ret = pblk_recov_scan_oob(pblk, line, p);
	अगर (ret) अणु
		pblk_err(pblk, "could not recover L2P form OOB\n");
		जाओ out;
	पूर्ण

	अगर (pblk_line_is_full(line))
		pblk_line_recov_बंद(pblk, line);

out:
	mempool_मुक्त(rqd, &pblk->r_rq_pool);
	kमुक्त(data);
मुक्त_meta_list:
	nvm_dev_dma_मुक्त(dev->parent, meta_list, dma_meta_list);

	वापस ret;
पूर्ण

/* Insert lines ordered by sequence number (seq_num) on list */
अटल व्योम pblk_recov_line_add_ordered(काष्ठा list_head *head,
					काष्ठा pblk_line *line)
अणु
	काष्ठा pblk_line *t = शून्य;

	list_क्रम_each_entry(t, head, list)
		अगर (t->seq_nr > line->seq_nr)
			अवरोध;

	__list_add(&line->list, t->list.prev, &t->list);
पूर्ण

अटल u64 pblk_line_emeta_start(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	अचिन्हित पूर्णांक emeta_secs;
	u64 emeta_start;
	काष्ठा ppa_addr ppa;
	पूर्णांक pos;

	emeta_secs = lm->emeta_sec[0];
	emeta_start = lm->sec_per_line;

	जबतक (emeta_secs) अणु
		emeta_start--;
		ppa = addr_to_gen_ppa(pblk, emeta_start, line->id);
		pos = pblk_ppa_to_pos(geo, ppa);
		अगर (!test_bit(pos, line->blk_biपंचांगap))
			emeta_secs--;
	पूर्ण

	वापस emeta_start;
पूर्ण

अटल पूर्णांक pblk_recov_check_line_version(काष्ठा pblk *pblk,
					 काष्ठा line_emeta *emeta)
अणु
	काष्ठा line_header *header = &emeta->header;

	अगर (header->version_major != EMETA_VERSION_MAJOR) अणु
		pblk_err(pblk, "line major version mismatch: %d, expected: %d\n",
			 header->version_major, EMETA_VERSION_MAJOR);
		वापस 1;
	पूर्ण

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	अगर (header->version_minor > EMETA_VERSION_MINOR)
		pblk_info(pblk, "newer line minor version found: %d\n",
				header->version_minor);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम pblk_recov_wa_counters(काष्ठा pblk *pblk,
				   काष्ठा line_emeta *emeta)
अणु
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा line_header *header = &emeta->header;
	काष्ठा wa_counters *wa = emeta_to_wa(lm, emeta);

	/* WA counters were पूर्णांकroduced in emeta version 0.2 */
	अगर (header->version_major > 0 || header->version_minor >= 2) अणु
		u64 user = le64_to_cpu(wa->user);
		u64 pad = le64_to_cpu(wa->pad);
		u64 gc = le64_to_cpu(wa->gc);

		atomic64_set(&pblk->user_wa, user);
		atomic64_set(&pblk->pad_wa, pad);
		atomic64_set(&pblk->gc_wa, gc);

		pblk->user_rst_wa = user;
		pblk->pad_rst_wa = pad;
		pblk->gc_rst_wa = gc;
	पूर्ण
पूर्ण

अटल पूर्णांक pblk_line_was_written(काष्ठा pblk_line *line,
				 काष्ठा pblk *pblk)
अणु

	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा nvm_chk_meta *chunk;
	काष्ठा ppa_addr bppa;
	पूर्णांक smeta_blk;

	अगर (line->state == PBLK_LINESTATE_BAD)
		वापस 0;

	smeta_blk = find_first_zero_bit(line->blk_biपंचांगap, lm->blk_per_line);
	अगर (smeta_blk >= lm->blk_per_line)
		वापस 0;

	bppa = pblk->luns[smeta_blk].bppa;
	chunk = &line->chks[pblk_ppa_to_pos(geo, bppa)];

	अगर (chunk->state & NVM_CHK_ST_CLOSED ||
	    (chunk->state & NVM_CHK_ST_OPEN
	     && chunk->wp >= lm->smeta_sec))
		वापस 1;

	वापस 0;
पूर्ण

अटल bool pblk_line_is_खोलो(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	पूर्णांक i;

	क्रम (i = 0; i < lm->blk_per_line; i++)
		अगर (line->chks[i].state & NVM_CHK_ST_OPEN)
			वापस true;

	वापस false;
पूर्ण

काष्ठा pblk_line *pblk_recov_l2p(काष्ठा pblk *pblk)
अणु
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा pblk_line *line, *tline, *data_line = शून्य;
	काष्ठा pblk_smeta *smeta;
	काष्ठा pblk_emeta *emeta;
	काष्ठा line_smeta *smeta_buf;
	पूर्णांक found_lines = 0, recovered_lines = 0, खोलो_lines = 0;
	पूर्णांक is_next = 0;
	पूर्णांक meta_line;
	पूर्णांक i, valid_uuid = 0;
	LIST_HEAD(recov_list);

	/* TODO: Implement FTL snapshot */

	/* Scan recovery - takes place when FTL snapshot fails */
	spin_lock(&l_mg->मुक्त_lock);
	meta_line = find_first_zero_bit(&l_mg->meta_biपंचांगap, PBLK_DATA_LINES);
	set_bit(meta_line, &l_mg->meta_biपंचांगap);
	smeta = l_mg->sline_meta[meta_line];
	emeta = l_mg->eline_meta[meta_line];
	smeta_buf = (काष्ठा line_smeta *)smeta;
	spin_unlock(&l_mg->मुक्त_lock);

	/* Order data lines using their sequence number */
	क्रम (i = 0; i < l_mg->nr_lines; i++) अणु
		u32 crc;

		line = &pblk->lines[i];

		स_रखो(smeta, 0, lm->smeta_len);
		line->smeta = smeta;
		line->lun_biपंचांगap = ((व्योम *)(smeta_buf)) +
						माप(काष्ठा line_smeta);

		अगर (!pblk_line_was_written(line, pblk))
			जारी;

		/* Lines that cannot be पढ़ो are assumed as not written here */
		अगर (pblk_line_smeta_पढ़ो(pblk, line))
			जारी;

		crc = pblk_calc_smeta_crc(pblk, smeta_buf);
		अगर (le32_to_cpu(smeta_buf->crc) != crc)
			जारी;

		अगर (le32_to_cpu(smeta_buf->header.identअगरier) != PBLK_MAGIC)
			जारी;

		अगर (smeta_buf->header.version_major != SMETA_VERSION_MAJOR) अणु
			pblk_err(pblk, "found incompatible line version %u\n",
					smeta_buf->header.version_major);
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		/* The first valid instance uuid is used क्रम initialization */
		अगर (!valid_uuid) अणु
			import_guid(&pblk->instance_uuid, smeta_buf->header.uuid);
			valid_uuid = 1;
		पूर्ण

		अगर (!guid_equal(&pblk->instance_uuid,
				(guid_t *)&smeta_buf->header.uuid)) अणु
			pblk_debug(pblk, "ignore line %u due to uuid mismatch\n",
					i);
			जारी;
		पूर्ण

		/* Update line metadata */
		spin_lock(&line->lock);
		line->id = le32_to_cpu(smeta_buf->header.id);
		line->type = le16_to_cpu(smeta_buf->header.type);
		line->seq_nr = le64_to_cpu(smeta_buf->seq_nr);
		spin_unlock(&line->lock);

		/* Update general metadata */
		spin_lock(&l_mg->मुक्त_lock);
		अगर (line->seq_nr >= l_mg->d_seq_nr)
			l_mg->d_seq_nr = line->seq_nr + 1;
		l_mg->nr_मुक्त_lines--;
		spin_unlock(&l_mg->मुक्त_lock);

		अगर (pblk_line_recov_alloc(pblk, line))
			जाओ out;

		pblk_recov_line_add_ordered(&recov_list, line);
		found_lines++;
		pblk_debug(pblk, "recovering data line %d, seq:%llu\n",
						line->id, smeta_buf->seq_nr);
	पूर्ण

	अगर (!found_lines) अणु
		guid_gen(&pblk->instance_uuid);

		spin_lock(&l_mg->मुक्त_lock);
		WARN_ON_ONCE(!test_and_clear_bit(meta_line,
							&l_mg->meta_biपंचांगap));
		spin_unlock(&l_mg->मुक्त_lock);

		जाओ out;
	पूर्ण

	/* Verअगरy बंदd blocks and recover this portion of L2P table*/
	list_क्रम_each_entry_safe(line, tline, &recov_list, list) अणु
		recovered_lines++;

		line->emeta_ssec = pblk_line_emeta_start(pblk, line);
		line->emeta = emeta;
		स_रखो(line->emeta->buf, 0, lm->emeta_len[0]);

		अगर (pblk_line_is_खोलो(pblk, line)) अणु
			pblk_recov_l2p_from_oob(pblk, line);
			जाओ next;
		पूर्ण

		अगर (pblk_line_emeta_पढ़ो(pblk, line, line->emeta->buf)) अणु
			pblk_recov_l2p_from_oob(pblk, line);
			जाओ next;
		पूर्ण

		अगर (pblk_recov_check_emeta(pblk, line->emeta->buf)) अणु
			pblk_recov_l2p_from_oob(pblk, line);
			जाओ next;
		पूर्ण

		अगर (pblk_recov_check_line_version(pblk, line->emeta->buf))
			वापस ERR_PTR(-EINVAL);

		pblk_recov_wa_counters(pblk, line->emeta->buf);

		अगर (pblk_recov_l2p_from_emeta(pblk, line))
			pblk_recov_l2p_from_oob(pblk, line);

next:
		अगर (pblk_line_is_full(line)) अणु
			काष्ठा list_head *move_list;

			spin_lock(&line->lock);
			line->state = PBLK_LINESTATE_CLOSED;
			trace_pblk_line_state(pblk_disk_name(pblk), line->id,
					line->state);
			move_list = pblk_line_gc_list(pblk, line);
			spin_unlock(&line->lock);

			spin_lock(&l_mg->gc_lock);
			list_move_tail(&line->list, move_list);
			spin_unlock(&l_mg->gc_lock);

			mempool_मुक्त(line->map_biपंचांगap, l_mg->biपंचांगap_pool);
			line->map_biपंचांगap = शून्य;
			line->smeta = शून्य;
			line->emeta = शून्य;
		पूर्ण अन्यथा अणु
			spin_lock(&line->lock);
			line->state = PBLK_LINESTATE_OPEN;
			spin_unlock(&line->lock);

			line->emeta->mem = 0;
			atomic_set(&line->emeta->sync, 0);

			trace_pblk_line_state(pblk_disk_name(pblk), line->id,
					line->state);

			data_line = line;
			line->meta_line = meta_line;

			खोलो_lines++;
		पूर्ण
	पूर्ण

	अगर (!खोलो_lines) अणु
		spin_lock(&l_mg->मुक्त_lock);
		WARN_ON_ONCE(!test_and_clear_bit(meta_line,
							&l_mg->meta_biपंचांगap));
		spin_unlock(&l_mg->मुक्त_lock);
	पूर्ण अन्यथा अणु
		spin_lock(&l_mg->मुक्त_lock);
		l_mg->data_line = data_line;
		/* Allocate next line क्रम preparation */
		l_mg->data_next = pblk_line_get(pblk);
		अगर (l_mg->data_next) अणु
			l_mg->data_next->seq_nr = l_mg->d_seq_nr++;
			l_mg->data_next->type = PBLK_LINETYPE_DATA;
			is_next = 1;
		पूर्ण
		spin_unlock(&l_mg->मुक्त_lock);
	पूर्ण

	अगर (is_next)
		pblk_line_erase(pblk, l_mg->data_next);

out:
	अगर (found_lines != recovered_lines)
		pblk_err(pblk, "failed to recover all found lines %d/%d\n",
						found_lines, recovered_lines);

	वापस data_line;
पूर्ण

/*
 * Pad current line
 */
पूर्णांक pblk_recov_pad(काष्ठा pblk *pblk)
अणु
	काष्ठा pblk_line *line;
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	पूर्णांक left_msecs;
	पूर्णांक ret = 0;

	spin_lock(&l_mg->मुक्त_lock);
	line = l_mg->data_line;
	left_msecs = line->left_msecs;
	spin_unlock(&l_mg->मुक्त_lock);

	ret = pblk_recov_pad_line(pblk, line, left_msecs);
	अगर (ret) अणु
		pblk_err(pblk, "tear down padding failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	pblk_line_बंद_meta(pblk, line);
	वापस ret;
पूर्ण
