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
 * pblk-पढ़ो.c - pblk's पढ़ो path
 */

#समावेश "pblk.h"

/*
 * There is no guarantee that the value पढ़ो from cache has not been updated and
 * resides at another location in the cache. We guarantee though that अगर the
 * value is पढ़ो from the cache, it beदीर्घs to the mapped lba. In order to
 * guarantee and order between ग_लिखोs and पढ़ोs are ordered, a flush must be
 * issued.
 */
अटल पूर्णांक pblk_पढ़ो_from_cache(काष्ठा pblk *pblk, काष्ठा bio *bio,
				sector_t lba, काष्ठा ppa_addr ppa)
अणु
#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	/* Callers must ensure that the ppa poपूर्णांकs to a cache address */
	BUG_ON(pblk_ppa_empty(ppa));
	BUG_ON(!pblk_addr_in_cache(ppa));
#पूर्ण_अगर

	वापस pblk_rb_copy_to_bio(&pblk->rwb, bio, lba, ppa);
पूर्ण

अटल पूर्णांक pblk_पढ़ो_ppalist_rq(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd,
				 काष्ठा bio *bio, sector_t blba,
				 bool *from_cache)
अणु
	व्योम *meta_list = rqd->meta_list;
	पूर्णांक nr_secs, i;

retry:
	nr_secs = pblk_lookup_l2p_seq(pblk, rqd->ppa_list, blba, rqd->nr_ppas,
					from_cache);

	अगर (!*from_cache)
		जाओ end;

	क्रम (i = 0; i < nr_secs; i++) अणु
		काष्ठा pblk_sec_meta *meta = pblk_get_meta(pblk, meta_list, i);
		sector_t lba = blba + i;

		अगर (pblk_ppa_empty(rqd->ppa_list[i])) अणु
			__le64 addr_empty = cpu_to_le64(ADDR_EMPTY);

			meta->lba = addr_empty;
		पूर्ण अन्यथा अगर (pblk_addr_in_cache(rqd->ppa_list[i])) अणु
			/*
			 * Try to पढ़ो from ग_लिखो buffer. The address is later
			 * checked on the ग_लिखो buffer to prevent retrieving
			 * overwritten data.
			 */
			अगर (!pblk_पढ़ो_from_cache(pblk, bio, lba,
							rqd->ppa_list[i])) अणु
				अगर (i == 0) अणु
					/*
					 * We didn't call with bio_advance()
					 * yet, so we can just retry.
					 */
					जाओ retry;
				पूर्ण अन्यथा अणु
					/*
					 * We alपढ़ोy call bio_advance()
					 * so we cannot retry and we need
					 * to quit that function in order
					 * to allow caller to handle the bio
					 * splitting in the current sector
					 * position.
					 */
					nr_secs = i;
					जाओ end;
				पूर्ण
			पूर्ण
			meta->lba = cpu_to_le64(lba);
#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
			atomic_दीर्घ_inc(&pblk->cache_पढ़ोs);
#पूर्ण_अगर
		पूर्ण
		bio_advance(bio, PBLK_EXPOSED_PAGE_SIZE);
	पूर्ण

end:
	अगर (pblk_io_aligned(pblk, nr_secs))
		rqd->is_seq = 1;

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	atomic_दीर्घ_add(nr_secs, &pblk->inflight_पढ़ोs);
#पूर्ण_अगर

	वापस nr_secs;
पूर्ण


अटल व्योम pblk_पढ़ो_check_seq(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd,
				sector_t blba)
अणु
	व्योम *meta_list = rqd->meta_list;
	पूर्णांक nr_lbas = rqd->nr_ppas;
	पूर्णांक i;

	अगर (!pblk_is_oob_meta_supported(pblk))
		वापस;

	क्रम (i = 0; i < nr_lbas; i++) अणु
		काष्ठा pblk_sec_meta *meta = pblk_get_meta(pblk, meta_list, i);
		u64 lba = le64_to_cpu(meta->lba);

		अगर (lba == ADDR_EMPTY)
			जारी;

		अगर (lba != blba + i) अणु
#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
			काष्ठा ppa_addr *ppa_list = nvm_rq_to_ppa_list(rqd);

			prपूर्णांक_ppa(pblk, &ppa_list[i], "seq", i);
#पूर्ण_अगर
			pblk_err(pblk, "corrupted read LBA (%llu/%llu)\n",
							lba, (u64)blba + i);
			WARN_ON(1);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * There can be holes in the lba list.
 */
अटल व्योम pblk_पढ़ो_check_अक्रम(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd,
				 u64 *lba_list, पूर्णांक nr_lbas)
अणु
	व्योम *meta_lba_list = rqd->meta_list;
	पूर्णांक i, j;

	अगर (!pblk_is_oob_meta_supported(pblk))
		वापस;

	क्रम (i = 0, j = 0; i < nr_lbas; i++) अणु
		काष्ठा pblk_sec_meta *meta = pblk_get_meta(pblk,
							   meta_lba_list, j);
		u64 lba = lba_list[i];
		u64 meta_lba;

		अगर (lba == ADDR_EMPTY)
			जारी;

		meta_lba = le64_to_cpu(meta->lba);

		अगर (lba != meta_lba) अणु
#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
			काष्ठा ppa_addr *ppa_list = nvm_rq_to_ppa_list(rqd);

			prपूर्णांक_ppa(pblk, &ppa_list[j], "rnd", j);
#पूर्ण_अगर
			pblk_err(pblk, "corrupted read LBA (%llu/%llu)\n",
							meta_lba, lba);
			WARN_ON(1);
		पूर्ण

		j++;
	पूर्ण

	WARN_ONCE(j != rqd->nr_ppas, "pblk: corrupted random request\n");
पूर्ण

अटल व्योम pblk_end_user_पढ़ो(काष्ठा bio *bio, पूर्णांक error)
अणु
	अगर (error && error != NVM_RSP_WARN_HIGHECC)
		bio_io_error(bio);
	अन्यथा
		bio_endio(bio);
पूर्ण

अटल व्योम __pblk_end_io_पढ़ो(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd,
			       bool put_line)
अणु
	काष्ठा pblk_g_ctx *r_ctx = nvm_rq_to_pdu(rqd);
	काष्ठा bio *पूर्णांक_bio = rqd->bio;
	अचिन्हित दीर्घ start_समय = r_ctx->start_समय;

	bio_end_io_acct(पूर्णांक_bio, start_समय);

	अगर (rqd->error)
		pblk_log_पढ़ो_err(pblk, rqd);

	pblk_पढ़ो_check_seq(pblk, rqd, r_ctx->lba);
	bio_put(पूर्णांक_bio);

	अगर (put_line)
		pblk_rq_to_line_put(pblk, rqd);

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	atomic_दीर्घ_add(rqd->nr_ppas, &pblk->sync_पढ़ोs);
	atomic_दीर्घ_sub(rqd->nr_ppas, &pblk->inflight_पढ़ोs);
#पूर्ण_अगर

	pblk_मुक्त_rqd(pblk, rqd, PBLK_READ);
	atomic_dec(&pblk->inflight_io);
पूर्ण

अटल व्योम pblk_end_io_पढ़ो(काष्ठा nvm_rq *rqd)
अणु
	काष्ठा pblk *pblk = rqd->निजी;
	काष्ठा pblk_g_ctx *r_ctx = nvm_rq_to_pdu(rqd);
	काष्ठा bio *bio = (काष्ठा bio *)r_ctx->निजी;

	pblk_end_user_पढ़ो(bio, rqd->error);
	__pblk_end_io_पढ़ो(pblk, rqd, true);
पूर्ण

अटल व्योम pblk_पढ़ो_rq(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd, काष्ठा bio *bio,
			 sector_t lba, bool *from_cache)
अणु
	काष्ठा pblk_sec_meta *meta = pblk_get_meta(pblk, rqd->meta_list, 0);
	काष्ठा ppa_addr ppa;

	pblk_lookup_l2p_seq(pblk, &ppa, lba, 1, from_cache);

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	atomic_दीर्घ_inc(&pblk->inflight_पढ़ोs);
#पूर्ण_अगर

retry:
	अगर (pblk_ppa_empty(ppa)) अणु
		__le64 addr_empty = cpu_to_le64(ADDR_EMPTY);

		meta->lba = addr_empty;
		वापस;
	पूर्ण

	/* Try to पढ़ो from ग_लिखो buffer. The address is later checked on the
	 * ग_लिखो buffer to prevent retrieving overwritten data.
	 */
	अगर (pblk_addr_in_cache(ppa)) अणु
		अगर (!pblk_पढ़ो_from_cache(pblk, bio, lba, ppa)) अणु
			pblk_lookup_l2p_seq(pblk, &ppa, lba, 1, from_cache);
			जाओ retry;
		पूर्ण

		meta->lba = cpu_to_le64(lba);

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
		atomic_दीर्घ_inc(&pblk->cache_पढ़ोs);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		rqd->ppa_addr = ppa;
	पूर्ण
पूर्ण

व्योम pblk_submit_पढ़ो(काष्ठा pblk *pblk, काष्ठा bio *bio)
अणु
	sector_t blba = pblk_get_lba(bio);
	अचिन्हित पूर्णांक nr_secs = pblk_get_secs(bio);
	bool from_cache;
	काष्ठा pblk_g_ctx *r_ctx;
	काष्ठा nvm_rq *rqd;
	काष्ठा bio *पूर्णांक_bio, *split_bio;
	अचिन्हित दीर्घ start_समय;

	start_समय = bio_start_io_acct(bio);

	rqd = pblk_alloc_rqd(pblk, PBLK_READ);

	rqd->opcode = NVM_OP_PREAD;
	rqd->nr_ppas = nr_secs;
	rqd->निजी = pblk;
	rqd->end_io = pblk_end_io_पढ़ो;

	r_ctx = nvm_rq_to_pdu(rqd);
	r_ctx->start_समय = start_समय;
	r_ctx->lba = blba;

	अगर (pblk_alloc_rqd_meta(pblk, rqd)) अणु
		bio_io_error(bio);
		pblk_मुक्त_rqd(pblk, rqd, PBLK_READ);
		वापस;
	पूर्ण

	/* Clone पढ़ो bio to deal पूर्णांकernally with:
	 * -पढ़ो errors when पढ़ोing from drive
	 * -bio_advance() calls during cache पढ़ोs
	 */
	पूर्णांक_bio = bio_clone_fast(bio, GFP_KERNEL, &pblk_bio_set);

	अगर (nr_secs > 1)
		nr_secs = pblk_पढ़ो_ppalist_rq(pblk, rqd, पूर्णांक_bio, blba,
						&from_cache);
	अन्यथा
		pblk_पढ़ो_rq(pblk, rqd, पूर्णांक_bio, blba, &from_cache);

split_retry:
	r_ctx->निजी = bio; /* original bio */
	rqd->bio = पूर्णांक_bio; /* पूर्णांकernal bio */

	अगर (from_cache && nr_secs == rqd->nr_ppas) अणु
		/* All data was पढ़ो from cache, we can complete the IO. */
		pblk_end_user_पढ़ो(bio, 0);
		atomic_inc(&pblk->inflight_io);
		__pblk_end_io_पढ़ो(pblk, rqd, false);
	पूर्ण अन्यथा अगर (nr_secs != rqd->nr_ppas) अणु
		/* The पढ़ो bio request could be partially filled by the ग_लिखो
		 * buffer, but there are some holes that need to be पढ़ो from
		 * the drive. In order to handle this, we will use block layer
		 * mechanism to split this request in to smaller ones and make
		 * a chain of it.
		 */
		split_bio = bio_split(bio, nr_secs * NR_PHY_IN_LOG, GFP_KERNEL,
					&pblk_bio_set);
		bio_chain(split_bio, bio);
		submit_bio_noacct(bio);

		/* New bio contains first N sectors of the previous one, so
		 * we can जारी to use existing rqd, but we need to shrink
		 * the number of PPAs in it. New bio is also guaranteed that
		 * it contains only either data from cache or from drive, newer
		 * mix of them.
		 */
		bio = split_bio;
		rqd->nr_ppas = nr_secs;
		अगर (rqd->nr_ppas == 1)
			rqd->ppa_addr = rqd->ppa_list[0];

		/* Recreate पूर्णांक_bio - existing might have some needed पूर्णांकernal
		 * fields modअगरied alपढ़ोy.
		 */
		bio_put(पूर्णांक_bio);
		पूर्णांक_bio = bio_clone_fast(bio, GFP_KERNEL, &pblk_bio_set);
		जाओ split_retry;
	पूर्ण अन्यथा अगर (pblk_submit_io(pblk, rqd, शून्य)) अणु
		/* Submitting IO to drive failed, let's report an error */
		rqd->error = -ENODEV;
		pblk_end_io_पढ़ो(rqd);
	पूर्ण
पूर्ण

अटल पूर्णांक पढ़ो_ppalist_rq_gc(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd,
			      काष्ठा pblk_line *line, u64 *lba_list,
			      u64 *paddr_list_gc, अचिन्हित पूर्णांक nr_secs)
अणु
	काष्ठा ppa_addr ppa_list_l2p[NVM_MAX_VLBA];
	काष्ठा ppa_addr ppa_gc;
	पूर्णांक valid_secs = 0;
	पूर्णांक i;

	pblk_lookup_l2p_अक्रम(pblk, ppa_list_l2p, lba_list, nr_secs);

	क्रम (i = 0; i < nr_secs; i++) अणु
		अगर (lba_list[i] == ADDR_EMPTY)
			जारी;

		ppa_gc = addr_to_gen_ppa(pblk, paddr_list_gc[i], line->id);
		अगर (!pblk_ppa_comp(ppa_list_l2p[i], ppa_gc)) अणु
			paddr_list_gc[i] = lba_list[i] = ADDR_EMPTY;
			जारी;
		पूर्ण

		rqd->ppa_list[valid_secs++] = ppa_list_l2p[i];
	पूर्ण

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	atomic_दीर्घ_add(valid_secs, &pblk->inflight_पढ़ोs);
#पूर्ण_अगर

	वापस valid_secs;
पूर्ण

अटल पूर्णांक पढ़ो_rq_gc(काष्ठा pblk *pblk, काष्ठा nvm_rq *rqd,
		      काष्ठा pblk_line *line, sector_t lba,
		      u64 paddr_gc)
अणु
	काष्ठा ppa_addr ppa_l2p, ppa_gc;
	पूर्णांक valid_secs = 0;

	अगर (lba == ADDR_EMPTY)
		जाओ out;

	/* logic error: lba out-of-bounds */
	अगर (lba >= pblk->capacity) अणु
		WARN(1, "pblk: read lba out of bounds\n");
		जाओ out;
	पूर्ण

	spin_lock(&pblk->trans_lock);
	ppa_l2p = pblk_trans_map_get(pblk, lba);
	spin_unlock(&pblk->trans_lock);

	ppa_gc = addr_to_gen_ppa(pblk, paddr_gc, line->id);
	अगर (!pblk_ppa_comp(ppa_l2p, ppa_gc))
		जाओ out;

	rqd->ppa_addr = ppa_l2p;
	valid_secs = 1;

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	atomic_दीर्घ_inc(&pblk->inflight_पढ़ोs);
#पूर्ण_अगर

out:
	वापस valid_secs;
पूर्ण

पूर्णांक pblk_submit_पढ़ो_gc(काष्ठा pblk *pblk, काष्ठा pblk_gc_rq *gc_rq)
अणु
	काष्ठा nvm_rq rqd;
	पूर्णांक ret = NVM_IO_OK;

	स_रखो(&rqd, 0, माप(काष्ठा nvm_rq));

	ret = pblk_alloc_rqd_meta(pblk, &rqd);
	अगर (ret)
		वापस ret;

	अगर (gc_rq->nr_secs > 1) अणु
		gc_rq->secs_to_gc = पढ़ो_ppalist_rq_gc(pblk, &rqd, gc_rq->line,
							gc_rq->lba_list,
							gc_rq->paddr_list,
							gc_rq->nr_secs);
		अगर (gc_rq->secs_to_gc == 1)
			rqd.ppa_addr = rqd.ppa_list[0];
	पूर्ण अन्यथा अणु
		gc_rq->secs_to_gc = पढ़ो_rq_gc(pblk, &rqd, gc_rq->line,
							gc_rq->lba_list[0],
							gc_rq->paddr_list[0]);
	पूर्ण

	अगर (!(gc_rq->secs_to_gc))
		जाओ out;

	rqd.opcode = NVM_OP_PREAD;
	rqd.nr_ppas = gc_rq->secs_to_gc;

	अगर (pblk_submit_io_sync(pblk, &rqd, gc_rq->data)) अणु
		ret = -EIO;
		जाओ err_मुक्त_dma;
	पूर्ण

	pblk_पढ़ो_check_अक्रम(pblk, &rqd, gc_rq->lba_list, gc_rq->nr_secs);

	atomic_dec(&pblk->inflight_io);

	अगर (rqd.error) अणु
		atomic_दीर्घ_inc(&pblk->पढ़ो_failed_gc);
#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
		pblk_prपूर्णांक_failed_rqd(pblk, &rqd, rqd.error);
#पूर्ण_अगर
	पूर्ण

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	atomic_दीर्घ_add(gc_rq->secs_to_gc, &pblk->sync_पढ़ोs);
	atomic_दीर्घ_add(gc_rq->secs_to_gc, &pblk->recov_gc_पढ़ोs);
	atomic_दीर्घ_sub(gc_rq->secs_to_gc, &pblk->inflight_पढ़ोs);
#पूर्ण_अगर

out:
	pblk_मुक्त_rqd_meta(pblk, &rqd);
	वापस ret;

err_मुक्त_dma:
	pblk_मुक्त_rqd_meta(pblk, &rqd);
	वापस ret;
पूर्ण
