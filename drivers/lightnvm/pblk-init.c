<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 IT University of Cखोलोhagen (rrpc.c)
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
 * Implementation of a physical block-device target क्रम Open-channel SSDs.
 *
 * pblk-init.c - pblk's initialization.
 */

#समावेश "pblk.h"
#समावेश "pblk-trace.h"

अटल अचिन्हित पूर्णांक ग_लिखो_buffer_size;

module_param(ग_लिखो_buffer_size, uपूर्णांक, 0644);
MODULE_PARM_DESC(ग_लिखो_buffer_size, "number of entries in a write buffer");

काष्ठा pblk_global_caches अणु
	काष्ठा kmem_cache	*ws;
	काष्ठा kmem_cache	*rec;
	काष्ठा kmem_cache	*g_rq;
	काष्ठा kmem_cache	*w_rq;

	काष्ठा kref		kref;

	काष्ठा mutex		mutex; /* Ensures consistency between
					* caches and kref
					*/
पूर्ण;

अटल काष्ठा pblk_global_caches pblk_caches = अणु
	.mutex = __MUTEX_INITIALIZER(pblk_caches.mutex),
	.kref = KREF_INIT(0),
पूर्ण;

काष्ठा bio_set pblk_bio_set;

अटल blk_qc_t pblk_submit_bio(काष्ठा bio *bio)
अणु
	काष्ठा pblk *pblk = bio->bi_bdev->bd_disk->queue->queuedata;

	अगर (bio_op(bio) == REQ_OP_DISCARD) अणु
		pblk_discard(pblk, bio);
		अगर (!(bio->bi_opf & REQ_PREFLUSH)) अणु
			bio_endio(bio);
			वापस BLK_QC_T_NONE;
		पूर्ण
	पूर्ण

	/* Read requests must be <= 256kb due to NVMe's 64 bit completion biपंचांगap
	 * स्थिरraपूर्णांक. Writes can be of arbitrary size.
	 */
	अगर (bio_data_dir(bio) == READ) अणु
		blk_queue_split(&bio);
		pblk_submit_पढ़ो(pblk, bio);
	पूर्ण अन्यथा अणु
		/* Prevent deadlock in the हाल of a modest LUN configuration
		 * and large user I/Os. Unless stalled, the rate limiter
		 * leaves at least 256KB available क्रम user I/O.
		 */
		अगर (pblk_get_secs(bio) > pblk_rl_max_io(&pblk->rl))
			blk_queue_split(&bio);

		pblk_ग_लिखो_to_cache(pblk, bio, PBLK_IOTYPE_USER);
	पूर्ण

	वापस BLK_QC_T_NONE;
पूर्ण

अटल स्थिर काष्ठा block_device_operations pblk_bops = अणु
	.owner		= THIS_MODULE,
	.submit_bio	= pblk_submit_bio,
पूर्ण;


अटल माप_प्रकार pblk_trans_map_size(काष्ठा pblk *pblk)
अणु
	पूर्णांक entry_size = 8;

	अगर (pblk->addrf_len < 32)
		entry_size = 4;

	वापस entry_size * pblk->capacity;
पूर्ण

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
अटल u32 pblk_l2p_crc(काष्ठा pblk *pblk)
अणु
	माप_प्रकार map_size;
	u32 crc = ~(u32)0;

	map_size = pblk_trans_map_size(pblk);
	crc = crc32_le(crc, pblk->trans_map, map_size);
	वापस crc;
पूर्ण
#पूर्ण_अगर

अटल व्योम pblk_l2p_मुक्त(काष्ठा pblk *pblk)
अणु
	vमुक्त(pblk->trans_map);
पूर्ण

अटल पूर्णांक pblk_l2p_recover(काष्ठा pblk *pblk, bool factory_init)
अणु
	काष्ठा pblk_line *line = शून्य;

	अगर (factory_init) अणु
		guid_gen(&pblk->instance_uuid);
	पूर्ण अन्यथा अणु
		line = pblk_recov_l2p(pblk);
		अगर (IS_ERR(line)) अणु
			pblk_err(pblk, "could not recover l2p table\n");
			वापस -EFAULT;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	pblk_info(pblk, "init: L2P CRC: %x\n", pblk_l2p_crc(pblk));
#पूर्ण_अगर

	/* Free full lines directly as GC has not been started yet */
	pblk_gc_मुक्त_full_lines(pblk);

	अगर (!line) अणु
		/* Configure next line क्रम user data */
		line = pblk_line_get_first_data(pblk);
		अगर (!line)
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pblk_l2p_init(काष्ठा pblk *pblk, bool factory_init)
अणु
	sector_t i;
	काष्ठा ppa_addr ppa;
	माप_प्रकार map_size;
	पूर्णांक ret = 0;

	map_size = pblk_trans_map_size(pblk);
	pblk->trans_map = __vदो_स्मृति(map_size, GFP_KERNEL | __GFP_NOWARN |
				    __GFP_RETRY_MAYFAIL | __GFP_HIGHMEM);
	अगर (!pblk->trans_map) अणु
		pblk_err(pblk, "failed to allocate L2P (need %zu of memory)\n",
				map_size);
		वापस -ENOMEM;
	पूर्ण

	pblk_ppa_set_empty(&ppa);

	क्रम (i = 0; i < pblk->capacity; i++)
		pblk_trans_map_set(pblk, i, ppa);

	ret = pblk_l2p_recover(pblk, factory_init);
	अगर (ret)
		vमुक्त(pblk->trans_map);

	वापस ret;
पूर्ण

अटल व्योम pblk_rwb_मुक्त(काष्ठा pblk *pblk)
अणु
	अगर (pblk_rb_tear_करोwn_check(&pblk->rwb))
		pblk_err(pblk, "write buffer error on tear down\n");

	pblk_rb_मुक्त(&pblk->rwb);
पूर्ण

अटल पूर्णांक pblk_rwb_init(काष्ठा pblk *pblk)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	अचिन्हित दीर्घ buffer_size;
	पूर्णांक pgs_in_buffer, threshold;

	threshold = geo->mw_cunits * geo->all_luns;
	pgs_in_buffer = (max(geo->mw_cunits, geo->ws_opt) + geo->ws_opt)
								* geo->all_luns;

	अगर (ग_लिखो_buffer_size && (ग_लिखो_buffer_size > pgs_in_buffer))
		buffer_size = ग_लिखो_buffer_size;
	अन्यथा
		buffer_size = pgs_in_buffer;

	वापस pblk_rb_init(&pblk->rwb, buffer_size, threshold, geo->csecs);
पूर्ण

अटल पूर्णांक pblk_set_addrf_12(काष्ठा pblk *pblk, काष्ठा nvm_geo *geo,
			     काष्ठा nvm_addrf_12 *dst)
अणु
	काष्ठा nvm_addrf_12 *src = (काष्ठा nvm_addrf_12 *)&geo->addrf;
	पूर्णांक घातer_len;

	/* Re-calculate channel and lun क्रमmat to adapt to configuration */
	घातer_len = get_count_order(geo->num_ch);
	अगर (1 << घातer_len != geo->num_ch) अणु
		pblk_err(pblk, "supports only power-of-two channel config.\n");
		वापस -EINVAL;
	पूर्ण
	dst->ch_len = घातer_len;

	घातer_len = get_count_order(geo->num_lun);
	अगर (1 << घातer_len != geo->num_lun) अणु
		pblk_err(pblk, "supports only power-of-two LUN config.\n");
		वापस -EINVAL;
	पूर्ण
	dst->lun_len = घातer_len;

	dst->blk_len = src->blk_len;
	dst->pg_len = src->pg_len;
	dst->pln_len = src->pln_len;
	dst->sec_len = src->sec_len;

	dst->sec_offset = 0;
	dst->pln_offset = dst->sec_len;
	dst->ch_offset = dst->pln_offset + dst->pln_len;
	dst->lun_offset = dst->ch_offset + dst->ch_len;
	dst->pg_offset = dst->lun_offset + dst->lun_len;
	dst->blk_offset = dst->pg_offset + dst->pg_len;

	dst->sec_mask = ((1ULL << dst->sec_len) - 1) << dst->sec_offset;
	dst->pln_mask = ((1ULL << dst->pln_len) - 1) << dst->pln_offset;
	dst->ch_mask = ((1ULL << dst->ch_len) - 1) << dst->ch_offset;
	dst->lun_mask = ((1ULL << dst->lun_len) - 1) << dst->lun_offset;
	dst->pg_mask = ((1ULL << dst->pg_len) - 1) << dst->pg_offset;
	dst->blk_mask = ((1ULL << dst->blk_len) - 1) << dst->blk_offset;

	वापस dst->blk_offset + src->blk_len;
पूर्ण

अटल पूर्णांक pblk_set_addrf_20(काष्ठा nvm_geo *geo, काष्ठा nvm_addrf *adst,
			     काष्ठा pblk_addrf *udst)
अणु
	काष्ठा nvm_addrf *src = &geo->addrf;

	adst->ch_len = get_count_order(geo->num_ch);
	adst->lun_len = get_count_order(geo->num_lun);
	adst->chk_len = src->chk_len;
	adst->sec_len = src->sec_len;

	adst->sec_offset = 0;
	adst->ch_offset = adst->sec_len;
	adst->lun_offset = adst->ch_offset + adst->ch_len;
	adst->chk_offset = adst->lun_offset + adst->lun_len;

	adst->sec_mask = ((1ULL << adst->sec_len) - 1) << adst->sec_offset;
	adst->chk_mask = ((1ULL << adst->chk_len) - 1) << adst->chk_offset;
	adst->lun_mask = ((1ULL << adst->lun_len) - 1) << adst->lun_offset;
	adst->ch_mask = ((1ULL << adst->ch_len) - 1) << adst->ch_offset;

	udst->sec_stripe = geo->ws_opt;
	udst->ch_stripe = geo->num_ch;
	udst->lun_stripe = geo->num_lun;

	udst->sec_lun_stripe = udst->sec_stripe * udst->ch_stripe;
	udst->sec_ws_stripe = udst->sec_lun_stripe * udst->lun_stripe;

	वापस adst->chk_offset + adst->chk_len;
पूर्ण

अटल पूर्णांक pblk_set_addrf(काष्ठा pblk *pblk)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	पूर्णांक mod;

	चयन (geo->version) अणु
	हाल NVM_OCSSD_SPEC_12:
		भाग_u64_rem(geo->clba, pblk->min_ग_लिखो_pgs, &mod);
		अगर (mod) अणु
			pblk_err(pblk, "bad configuration of sectors/pages\n");
			वापस -EINVAL;
		पूर्ण

		pblk->addrf_len = pblk_set_addrf_12(pblk, geo,
							(व्योम *)&pblk->addrf);
		अवरोध;
	हाल NVM_OCSSD_SPEC_20:
		pblk->addrf_len = pblk_set_addrf_20(geo, (व्योम *)&pblk->addrf,
							&pblk->uaddrf);
		अवरोध;
	शेष:
		pblk_err(pblk, "OCSSD revision not supported (%d)\n",
								geo->version);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pblk_create_global_caches(व्योम)
अणु

	pblk_caches.ws = kmem_cache_create("pblk_blk_ws",
				माप(काष्ठा pblk_line_ws), 0, 0, शून्य);
	अगर (!pblk_caches.ws)
		वापस -ENOMEM;

	pblk_caches.rec = kmem_cache_create("pblk_rec",
				माप(काष्ठा pblk_rec_ctx), 0, 0, शून्य);
	अगर (!pblk_caches.rec)
		जाओ fail_destroy_ws;

	pblk_caches.g_rq = kmem_cache_create("pblk_g_rq", pblk_g_rq_size,
				0, 0, शून्य);
	अगर (!pblk_caches.g_rq)
		जाओ fail_destroy_rec;

	pblk_caches.w_rq = kmem_cache_create("pblk_w_rq", pblk_w_rq_size,
				0, 0, शून्य);
	अगर (!pblk_caches.w_rq)
		जाओ fail_destroy_g_rq;

	वापस 0;

fail_destroy_g_rq:
	kmem_cache_destroy(pblk_caches.g_rq);
fail_destroy_rec:
	kmem_cache_destroy(pblk_caches.rec);
fail_destroy_ws:
	kmem_cache_destroy(pblk_caches.ws);

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक pblk_get_global_caches(व्योम)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&pblk_caches.mutex);

	अगर (kref_get_unless_zero(&pblk_caches.kref))
		जाओ out;

	ret = pblk_create_global_caches();
	अगर (!ret)
		kref_init(&pblk_caches.kref);

out:
	mutex_unlock(&pblk_caches.mutex);
	वापस ret;
पूर्ण

अटल व्योम pblk_destroy_global_caches(काष्ठा kref *ref)
अणु
	काष्ठा pblk_global_caches *c;

	c = container_of(ref, काष्ठा pblk_global_caches, kref);

	kmem_cache_destroy(c->ws);
	kmem_cache_destroy(c->rec);
	kmem_cache_destroy(c->g_rq);
	kmem_cache_destroy(c->w_rq);
पूर्ण

अटल व्योम pblk_put_global_caches(व्योम)
अणु
	mutex_lock(&pblk_caches.mutex);
	kref_put(&pblk_caches.kref, pblk_destroy_global_caches);
	mutex_unlock(&pblk_caches.mutex);
पूर्ण

अटल पूर्णांक pblk_core_init(काष्ठा pblk *pblk)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	पूर्णांक ret, max_ग_लिखो_ppas;

	atomic64_set(&pblk->user_wa, 0);
	atomic64_set(&pblk->pad_wa, 0);
	atomic64_set(&pblk->gc_wa, 0);
	pblk->user_rst_wa = 0;
	pblk->pad_rst_wa = 0;
	pblk->gc_rst_wa = 0;

	atomic64_set(&pblk->nr_flush, 0);
	pblk->nr_flush_rst = 0;

	pblk->min_ग_लिखो_pgs = geo->ws_opt;
	pblk->min_ग_लिखो_pgs_data = pblk->min_ग_लिखो_pgs;
	max_ग_लिखो_ppas = pblk->min_ग_लिखो_pgs * geo->all_luns;
	pblk->max_ग_लिखो_pgs = min_t(पूर्णांक, max_ग_लिखो_ppas, NVM_MAX_VLBA);
	pblk->max_ग_लिखो_pgs = min_t(पूर्णांक, pblk->max_ग_लिखो_pgs,
		queue_max_hw_sectors(dev->q) / (geo->csecs >> SECTOR_SHIFT));
	pblk_set_sec_per_ग_लिखो(pblk, pblk->min_ग_लिखो_pgs);

	pblk->oob_meta_size = geo->sos;
	अगर (!pblk_is_oob_meta_supported(pblk)) अणु
		/* For drives which करोes not have OOB metadata feature
		 * in order to support recovery feature we need to use
		 * so called packed metadata. Packed metada will store
		 * the same inक्रमmation as OOB metadata (l2p table mapping,
		 * but in the क्रमm of the single page at the end of
		 * every ग_लिखो request.
		 */
		अगर (pblk->min_ग_लिखो_pgs
			* माप(काष्ठा pblk_sec_meta) > PAGE_SIZE) अणु
			/* We want to keep all the packed metadata on single
			 * page per ग_लिखो requests. So we need to ensure that
			 * it will fit.
			 *
			 * This is more like sanity check, since there is
			 * no device with such a big minimal ग_लिखो size
			 * (above 1 metabytes).
			 */
			pblk_err(pblk, "Not supported min write size\n");
			वापस -EINVAL;
		पूर्ण
		/* For packed meta approach we करो some simplअगरication.
		 * On पढ़ो path we always issue requests which size
		 * equal to max_ग_लिखो_pgs, with all pages filled with
		 * user payload except of last one page which will be
		 * filled with packed metadata.
		 */
		pblk->max_ग_लिखो_pgs = pblk->min_ग_लिखो_pgs;
		pblk->min_ग_लिखो_pgs_data = pblk->min_ग_लिखो_pgs - 1;
	पूर्ण

	pblk->pad_dist = kसुस्मृति(pblk->min_ग_लिखो_pgs - 1, माप(atomic64_t),
								GFP_KERNEL);
	अगर (!pblk->pad_dist)
		वापस -ENOMEM;

	अगर (pblk_get_global_caches())
		जाओ fail_मुक्त_pad_dist;

	/* Internal bios can be at most the sectors संकेतed by the device. */
	ret = mempool_init_page_pool(&pblk->page_bio_pool, NVM_MAX_VLBA, 0);
	अगर (ret)
		जाओ मुक्त_global_caches;

	ret = mempool_init_slab_pool(&pblk->gen_ws_pool, PBLK_GEN_WS_POOL_SIZE,
				     pblk_caches.ws);
	अगर (ret)
		जाओ मुक्त_page_bio_pool;

	ret = mempool_init_slab_pool(&pblk->rec_pool, geo->all_luns,
				     pblk_caches.rec);
	अगर (ret)
		जाओ मुक्त_gen_ws_pool;

	ret = mempool_init_slab_pool(&pblk->r_rq_pool, geo->all_luns,
				     pblk_caches.g_rq);
	अगर (ret)
		जाओ मुक्त_rec_pool;

	ret = mempool_init_slab_pool(&pblk->e_rq_pool, geo->all_luns,
				     pblk_caches.g_rq);
	अगर (ret)
		जाओ मुक्त_r_rq_pool;

	ret = mempool_init_slab_pool(&pblk->w_rq_pool, geo->all_luns,
				     pblk_caches.w_rq);
	अगर (ret)
		जाओ मुक्त_e_rq_pool;

	pblk->बंद_wq = alloc_workqueue("pblk-close-wq",
			WQ_MEM_RECLAIM | WQ_UNBOUND, PBLK_NR_CLOSE_JOBS);
	अगर (!pblk->बंद_wq)
		जाओ मुक्त_w_rq_pool;

	pblk->bb_wq = alloc_workqueue("pblk-bb-wq",
			WQ_MEM_RECLAIM | WQ_UNBOUND, 0);
	अगर (!pblk->bb_wq)
		जाओ मुक्त_बंद_wq;

	pblk->r_end_wq = alloc_workqueue("pblk-read-end-wq",
			WQ_MEM_RECLAIM | WQ_UNBOUND, 0);
	अगर (!pblk->r_end_wq)
		जाओ मुक्त_bb_wq;

	अगर (pblk_set_addrf(pblk))
		जाओ मुक्त_r_end_wq;

	INIT_LIST_HEAD(&pblk->compl_list);
	INIT_LIST_HEAD(&pblk->resubmit_list);

	वापस 0;

मुक्त_r_end_wq:
	destroy_workqueue(pblk->r_end_wq);
मुक्त_bb_wq:
	destroy_workqueue(pblk->bb_wq);
मुक्त_बंद_wq:
	destroy_workqueue(pblk->बंद_wq);
मुक्त_w_rq_pool:
	mempool_निकास(&pblk->w_rq_pool);
मुक्त_e_rq_pool:
	mempool_निकास(&pblk->e_rq_pool);
मुक्त_r_rq_pool:
	mempool_निकास(&pblk->r_rq_pool);
मुक्त_rec_pool:
	mempool_निकास(&pblk->rec_pool);
मुक्त_gen_ws_pool:
	mempool_निकास(&pblk->gen_ws_pool);
मुक्त_page_bio_pool:
	mempool_निकास(&pblk->page_bio_pool);
मुक्त_global_caches:
	pblk_put_global_caches();
fail_मुक्त_pad_dist:
	kमुक्त(pblk->pad_dist);
	वापस -ENOMEM;
पूर्ण

अटल व्योम pblk_core_मुक्त(काष्ठा pblk *pblk)
अणु
	अगर (pblk->बंद_wq)
		destroy_workqueue(pblk->बंद_wq);

	अगर (pblk->r_end_wq)
		destroy_workqueue(pblk->r_end_wq);

	अगर (pblk->bb_wq)
		destroy_workqueue(pblk->bb_wq);

	mempool_निकास(&pblk->page_bio_pool);
	mempool_निकास(&pblk->gen_ws_pool);
	mempool_निकास(&pblk->rec_pool);
	mempool_निकास(&pblk->r_rq_pool);
	mempool_निकास(&pblk->e_rq_pool);
	mempool_निकास(&pblk->w_rq_pool);

	pblk_put_global_caches();
	kमुक्त(pblk->pad_dist);
पूर्ण

अटल व्योम pblk_line_mg_मुक्त(काष्ठा pblk *pblk)
अणु
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	पूर्णांक i;

	kमुक्त(l_mg->bb_ढाँचा);
	kमुक्त(l_mg->bb_aux);
	kमुक्त(l_mg->vsc_list);

	क्रम (i = 0; i < PBLK_DATA_LINES; i++) अणु
		kमुक्त(l_mg->sline_meta[i]);
		kvमुक्त(l_mg->eline_meta[i]->buf);
		kमुक्त(l_mg->eline_meta[i]);
	पूर्ण

	mempool_destroy(l_mg->biपंचांगap_pool);
	kmem_cache_destroy(l_mg->biपंचांगap_cache);
पूर्ण

अटल व्योम pblk_line_meta_मुक्त(काष्ठा pblk_line_mgmt *l_mg,
				काष्ठा pblk_line *line)
अणु
	काष्ठा pblk_w_err_gc *w_err_gc = line->w_err_gc;

	kमुक्त(line->blk_biपंचांगap);
	kमुक्त(line->erase_biपंचांगap);
	kमुक्त(line->chks);

	kvमुक्त(w_err_gc->lba_list);
	kमुक्त(w_err_gc);
पूर्ण

अटल व्योम pblk_lines_मुक्त(काष्ठा pblk *pblk)
अणु
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा pblk_line *line;
	पूर्णांक i;

	क्रम (i = 0; i < l_mg->nr_lines; i++) अणु
		line = &pblk->lines[i];

		pblk_line_मुक्त(line);
		pblk_line_meta_मुक्त(l_mg, line);
	पूर्ण

	pblk_line_mg_मुक्त(pblk);

	kमुक्त(pblk->luns);
	kमुक्त(pblk->lines);
पूर्ण

अटल पूर्णांक pblk_luns_init(काष्ठा pblk *pblk)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा pblk_lun *rlun;
	पूर्णांक i;

	/* TODO: Implement unbalanced LUN support */
	अगर (geo->num_lun < 0) अणु
		pblk_err(pblk, "unbalanced LUN config.\n");
		वापस -EINVAL;
	पूर्ण

	pblk->luns = kसुस्मृति(geo->all_luns, माप(काष्ठा pblk_lun),
								GFP_KERNEL);
	अगर (!pblk->luns)
		वापस -ENOMEM;

	क्रम (i = 0; i < geo->all_luns; i++) अणु
		/* Stripe across channels */
		पूर्णांक ch = i % geo->num_ch;
		पूर्णांक lun_raw = i / geo->num_ch;
		पूर्णांक lunid = lun_raw + ch * geo->num_lun;

		rlun = &pblk->luns[i];
		rlun->bppa = dev->luns[lunid];

		sema_init(&rlun->wr_sem, 1);
	पूर्ण

	वापस 0;
पूर्ण

/* See comment over काष्ठा line_emeta definition */
अटल अचिन्हित पूर्णांक calc_emeta_len(काष्ठा pblk *pblk)
अणु
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;

	/* Round to sector size so that lba_list starts on its own sector */
	lm->emeta_sec[1] = DIV_ROUND_UP(
			माप(काष्ठा line_emeta) + lm->blk_biपंचांगap_len +
			माप(काष्ठा wa_counters), geo->csecs);
	lm->emeta_len[1] = lm->emeta_sec[1] * geo->csecs;

	/* Round to sector size so that vsc_list starts on its own sector */
	lm->dsec_per_line = lm->sec_per_line - lm->emeta_sec[0];
	lm->emeta_sec[2] = DIV_ROUND_UP(lm->dsec_per_line * माप(u64),
			geo->csecs);
	lm->emeta_len[2] = lm->emeta_sec[2] * geo->csecs;

	lm->emeta_sec[3] = DIV_ROUND_UP(l_mg->nr_lines * माप(u32),
			geo->csecs);
	lm->emeta_len[3] = lm->emeta_sec[3] * geo->csecs;

	lm->vsc_list_len = l_mg->nr_lines * माप(u32);

	वापस (lm->emeta_len[1] + lm->emeta_len[2] + lm->emeta_len[3]);
पूर्ण

अटल पूर्णांक pblk_set_provision(काष्ठा pblk *pblk, पूर्णांक nr_मुक्त_chks)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा nvm_geo *geo = &dev->geo;
	sector_t provisioned;
	पूर्णांक sec_meta, blk_meta, clba;
	पूर्णांक minimum;

	अगर (geo->op == NVM_TARGET_DEFAULT_OP)
		pblk->op = PBLK_DEFAULT_OP;
	अन्यथा
		pblk->op = geo->op;

	minimum = pblk_get_min_chks(pblk);
	provisioned = nr_मुक्त_chks;
	provisioned *= (100 - pblk->op);
	sector_भाग(provisioned, 100);

	अगर ((nr_मुक्त_chks - provisioned) < minimum) अणु
		अगर (geo->op != NVM_TARGET_DEFAULT_OP) अणु
			pblk_err(pblk, "OP too small to create a sane instance\n");
			वापस -EINTR;
		पूर्ण

		/* If the user did not specअगरy an OP value, and PBLK_DEFAULT_OP
		 * is not enough, calculate and set sane value
		 */

		provisioned = nr_मुक्त_chks - minimum;
		pblk->op =  (100 * minimum) / nr_मुक्त_chks;
		pblk_info(pblk, "Default OP insufficient, adjusting OP to %d\n",
				pblk->op);
	पूर्ण

	pblk->op_blks = nr_मुक्त_chks - provisioned;

	/* Internally pblk manages all मुक्त blocks, but all calculations based
	 * on user capacity consider only provisioned blocks
	 */
	pblk->rl.total_blocks = nr_मुक्त_chks;

	/* Consider sectors used क्रम metadata */
	sec_meta = (lm->smeta_sec + lm->emeta_sec[0]) * l_mg->nr_मुक्त_lines;
	blk_meta = DIV_ROUND_UP(sec_meta, geo->clba);

	clba = (geo->clba / pblk->min_ग_लिखो_pgs) * pblk->min_ग_लिखो_pgs_data;
	pblk->capacity = (provisioned - blk_meta) * clba;

	atomic_set(&pblk->rl.मुक्त_blocks, nr_मुक्त_chks);
	atomic_set(&pblk->rl.मुक्त_user_blocks, nr_मुक्त_chks);

	वापस 0;
पूर्ण

अटल पूर्णांक pblk_setup_line_meta_chk(काष्ठा pblk *pblk, काष्ठा pblk_line *line,
				   काष्ठा nvm_chk_meta *meta)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	पूर्णांक i, nr_bad_chks = 0;

	क्रम (i = 0; i < lm->blk_per_line; i++) अणु
		काष्ठा pblk_lun *rlun = &pblk->luns[i];
		काष्ठा nvm_chk_meta *chunk;
		काष्ठा nvm_chk_meta *chunk_meta;
		काष्ठा ppa_addr ppa;
		पूर्णांक pos;

		ppa = rlun->bppa;
		pos = pblk_ppa_to_pos(geo, ppa);
		chunk = &line->chks[pos];

		ppa.m.chk = line->id;
		chunk_meta = pblk_chunk_get_off(pblk, meta, ppa);

		chunk->state = chunk_meta->state;
		chunk->type = chunk_meta->type;
		chunk->wi = chunk_meta->wi;
		chunk->slba = chunk_meta->slba;
		chunk->cnlb = chunk_meta->cnlb;
		chunk->wp = chunk_meta->wp;

		trace_pblk_chunk_state(pblk_disk_name(pblk), &ppa,
					chunk->state);

		अगर (chunk->type & NVM_CHK_TP_SZ_SPEC) अणु
			WARN_ONCE(1, "pblk: custom-sized chunks unsupported\n");
			जारी;
		पूर्ण

		अगर (!(chunk->state & NVM_CHK_ST_OFFLINE))
			जारी;

		set_bit(pos, line->blk_biपंचांगap);
		nr_bad_chks++;
	पूर्ण

	वापस nr_bad_chks;
पूर्ण

अटल दीर्घ pblk_setup_line_meta(काष्ठा pblk *pblk, काष्ठा pblk_line *line,
				 व्योम *chunk_meta, पूर्णांक line_id)
अणु
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	दीर्घ nr_bad_chks, chk_in_line;

	line->pblk = pblk;
	line->id = line_id;
	line->type = PBLK_LINETYPE_FREE;
	line->state = PBLK_LINESTATE_NEW;
	line->gc_group = PBLK_LINEGC_NONE;
	line->vsc = &l_mg->vsc_list[line_id];
	spin_lock_init(&line->lock);

	nr_bad_chks = pblk_setup_line_meta_chk(pblk, line, chunk_meta);

	chk_in_line = lm->blk_per_line - nr_bad_chks;
	अगर (nr_bad_chks < 0 || nr_bad_chks > lm->blk_per_line ||
					chk_in_line < lm->min_blk_line) अणु
		line->state = PBLK_LINESTATE_BAD;
		list_add_tail(&line->list, &l_mg->bad_list);
		वापस 0;
	पूर्ण

	atomic_set(&line->blk_in_line, chk_in_line);
	list_add_tail(&line->list, &l_mg->मुक्त_list);
	l_mg->nr_मुक्त_lines++;

	वापस chk_in_line;
पूर्ण

अटल पूर्णांक pblk_alloc_line_meta(काष्ठा pblk *pblk, काष्ठा pblk_line *line)
अणु
	काष्ठा pblk_line_meta *lm = &pblk->lm;

	line->blk_biपंचांगap = kzalloc(lm->blk_biपंचांगap_len, GFP_KERNEL);
	अगर (!line->blk_biपंचांगap)
		वापस -ENOMEM;

	line->erase_biपंचांगap = kzalloc(lm->blk_biपंचांगap_len, GFP_KERNEL);
	अगर (!line->erase_biपंचांगap)
		जाओ मुक्त_blk_biपंचांगap;


	line->chks = kदो_स्मृति_array(lm->blk_per_line,
				   माप(काष्ठा nvm_chk_meta), GFP_KERNEL);
	अगर (!line->chks)
		जाओ मुक्त_erase_biपंचांगap;

	line->w_err_gc = kzalloc(माप(काष्ठा pblk_w_err_gc), GFP_KERNEL);
	अगर (!line->w_err_gc)
		जाओ मुक्त_chks;

	वापस 0;

मुक्त_chks:
	kमुक्त(line->chks);
मुक्त_erase_biपंचांगap:
	kमुक्त(line->erase_biपंचांगap);
मुक्त_blk_biपंचांगap:
	kमुक्त(line->blk_biपंचांगap);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक pblk_line_mg_init(काष्ठा pblk *pblk)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	पूर्णांक i, bb_distance;

	l_mg->nr_lines = geo->num_chk;
	l_mg->log_line = l_mg->data_line = शून्य;
	l_mg->l_seq_nr = l_mg->d_seq_nr = 0;
	l_mg->nr_मुक्त_lines = 0;
	biपंचांगap_zero(&l_mg->meta_biपंचांगap, PBLK_DATA_LINES);

	INIT_LIST_HEAD(&l_mg->मुक्त_list);
	INIT_LIST_HEAD(&l_mg->corrupt_list);
	INIT_LIST_HEAD(&l_mg->bad_list);
	INIT_LIST_HEAD(&l_mg->gc_full_list);
	INIT_LIST_HEAD(&l_mg->gc_high_list);
	INIT_LIST_HEAD(&l_mg->gc_mid_list);
	INIT_LIST_HEAD(&l_mg->gc_low_list);
	INIT_LIST_HEAD(&l_mg->gc_empty_list);
	INIT_LIST_HEAD(&l_mg->gc_werr_list);

	INIT_LIST_HEAD(&l_mg->emeta_list);

	l_mg->gc_lists[0] = &l_mg->gc_werr_list;
	l_mg->gc_lists[1] = &l_mg->gc_high_list;
	l_mg->gc_lists[2] = &l_mg->gc_mid_list;
	l_mg->gc_lists[3] = &l_mg->gc_low_list;

	spin_lock_init(&l_mg->मुक्त_lock);
	spin_lock_init(&l_mg->बंद_lock);
	spin_lock_init(&l_mg->gc_lock);

	l_mg->vsc_list = kसुस्मृति(l_mg->nr_lines, माप(__le32), GFP_KERNEL);
	अगर (!l_mg->vsc_list)
		जाओ fail;

	l_mg->bb_ढाँचा = kzalloc(lm->sec_biपंचांगap_len, GFP_KERNEL);
	अगर (!l_mg->bb_ढाँचा)
		जाओ fail_मुक्त_vsc_list;

	l_mg->bb_aux = kzalloc(lm->sec_biपंचांगap_len, GFP_KERNEL);
	अगर (!l_mg->bb_aux)
		जाओ fail_मुक्त_bb_ढाँचा;

	/* smeta is always small enough to fit on a kदो_स्मृति memory allocation,
	 * emeta depends on the number of LUNs allocated to the pblk instance
	 */
	क्रम (i = 0; i < PBLK_DATA_LINES; i++) अणु
		l_mg->sline_meta[i] = kदो_स्मृति(lm->smeta_len, GFP_KERNEL);
		अगर (!l_mg->sline_meta[i])
			जाओ fail_मुक्त_smeta;
	पूर्ण

	l_mg->biपंचांगap_cache = kmem_cache_create("pblk_lm_bitmap",
			lm->sec_biपंचांगap_len, 0, 0, शून्य);
	अगर (!l_mg->biपंचांगap_cache)
		जाओ fail_मुक्त_smeta;

	/* the biपंचांगap pool is used क्रम both valid and map biपंचांगaps */
	l_mg->biपंचांगap_pool = mempool_create_slab_pool(PBLK_DATA_LINES * 2,
				l_mg->biपंचांगap_cache);
	अगर (!l_mg->biपंचांगap_pool)
		जाओ fail_destroy_biपंचांगap_cache;

	/* emeta allocates three dअगरferent buffers क्रम managing metadata with
	 * in-memory and in-media layouts
	 */
	क्रम (i = 0; i < PBLK_DATA_LINES; i++) अणु
		काष्ठा pblk_emeta *emeta;

		emeta = kदो_स्मृति(माप(काष्ठा pblk_emeta), GFP_KERNEL);
		अगर (!emeta)
			जाओ fail_मुक्त_emeta;

		emeta->buf = kvदो_स्मृति(lm->emeta_len[0], GFP_KERNEL);
		अगर (!emeta->buf) अणु
			kमुक्त(emeta);
			जाओ fail_मुक्त_emeta;
		पूर्ण

		emeta->nr_entries = lm->emeta_sec[0];
		l_mg->eline_meta[i] = emeta;
	पूर्ण

	क्रम (i = 0; i < l_mg->nr_lines; i++)
		l_mg->vsc_list[i] = cpu_to_le32(EMPTY_ENTRY);

	bb_distance = (geo->all_luns) * geo->ws_opt;
	क्रम (i = 0; i < lm->sec_per_line; i += bb_distance)
		biपंचांगap_set(l_mg->bb_ढाँचा, i, geo->ws_opt);

	वापस 0;

fail_मुक्त_emeta:
	जबतक (--i >= 0) अणु
		kvमुक्त(l_mg->eline_meta[i]->buf);
		kमुक्त(l_mg->eline_meta[i]);
	पूर्ण

	mempool_destroy(l_mg->biपंचांगap_pool);
fail_destroy_biपंचांगap_cache:
	kmem_cache_destroy(l_mg->biपंचांगap_cache);
fail_मुक्त_smeta:
	क्रम (i = 0; i < PBLK_DATA_LINES; i++)
		kमुक्त(l_mg->sline_meta[i]);
	kमुक्त(l_mg->bb_aux);
fail_मुक्त_bb_ढाँचा:
	kमुक्त(l_mg->bb_ढाँचा);
fail_मुक्त_vsc_list:
	kमुक्त(l_mg->vsc_list);
fail:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक pblk_line_meta_init(काष्ठा pblk *pblk)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	अचिन्हित पूर्णांक smeta_len, emeta_len;
	पूर्णांक i;

	lm->sec_per_line = geo->clba * geo->all_luns;
	lm->blk_per_line = geo->all_luns;
	lm->blk_biपंचांगap_len = BITS_TO_LONGS(geo->all_luns) * माप(दीर्घ);
	lm->sec_biपंचांगap_len = BITS_TO_LONGS(lm->sec_per_line) * माप(दीर्घ);
	lm->lun_biपंचांगap_len = BITS_TO_LONGS(geo->all_luns) * माप(दीर्घ);
	lm->mid_thrs = lm->sec_per_line / 2;
	lm->high_thrs = lm->sec_per_line / 4;
	lm->meta_distance = (geo->all_luns / 2) * pblk->min_ग_लिखो_pgs;

	/* Calculate necessary pages क्रम smeta. See comment over काष्ठा
	 * line_smeta definition
	 */
	i = 1;
add_smeta_page:
	lm->smeta_sec = i * geo->ws_opt;
	lm->smeta_len = lm->smeta_sec * geo->csecs;

	smeta_len = माप(काष्ठा line_smeta) + lm->lun_biपंचांगap_len;
	अगर (smeta_len > lm->smeta_len) अणु
		i++;
		जाओ add_smeta_page;
	पूर्ण

	/* Calculate necessary pages क्रम emeta. See comment over काष्ठा
	 * line_emeta definition
	 */
	i = 1;
add_emeta_page:
	lm->emeta_sec[0] = i * geo->ws_opt;
	lm->emeta_len[0] = lm->emeta_sec[0] * geo->csecs;

	emeta_len = calc_emeta_len(pblk);
	अगर (emeta_len > lm->emeta_len[0]) अणु
		i++;
		जाओ add_emeta_page;
	पूर्ण

	lm->emeta_bb = geo->all_luns > i ? geo->all_luns - i : 0;

	lm->min_blk_line = 1;
	अगर (geo->all_luns > 1)
		lm->min_blk_line += DIV_ROUND_UP(lm->smeta_sec +
					lm->emeta_sec[0], geo->clba);

	अगर (lm->min_blk_line > lm->blk_per_line) अणु
		pblk_err(pblk, "config. not supported. Min. LUN in line:%d\n",
							lm->blk_per_line);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pblk_lines_init(काष्ठा pblk *pblk)
अणु
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा pblk_line *line;
	व्योम *chunk_meta;
	पूर्णांक nr_मुक्त_chks = 0;
	पूर्णांक i, ret;

	ret = pblk_line_meta_init(pblk);
	अगर (ret)
		वापस ret;

	ret = pblk_line_mg_init(pblk);
	अगर (ret)
		वापस ret;

	ret = pblk_luns_init(pblk);
	अगर (ret)
		जाओ fail_मुक्त_meta;

	chunk_meta = pblk_get_chunk_meta(pblk);
	अगर (IS_ERR(chunk_meta)) अणु
		ret = PTR_ERR(chunk_meta);
		जाओ fail_मुक्त_luns;
	पूर्ण

	pblk->lines = kसुस्मृति(l_mg->nr_lines, माप(काष्ठा pblk_line),
								GFP_KERNEL);
	अगर (!pblk->lines) अणु
		ret = -ENOMEM;
		जाओ fail_मुक्त_chunk_meta;
	पूर्ण

	क्रम (i = 0; i < l_mg->nr_lines; i++) अणु
		line = &pblk->lines[i];

		ret = pblk_alloc_line_meta(pblk, line);
		अगर (ret)
			जाओ fail_मुक्त_lines;

		nr_मुक्त_chks += pblk_setup_line_meta(pblk, line, chunk_meta, i);

		trace_pblk_line_state(pblk_disk_name(pblk), line->id,
								line->state);
	पूर्ण

	अगर (!nr_मुक्त_chks) अणु
		pblk_err(pblk, "too many bad blocks prevent for sane instance\n");
		ret = -EINTR;
		जाओ fail_मुक्त_lines;
	पूर्ण

	ret = pblk_set_provision(pblk, nr_मुक्त_chks);
	अगर (ret)
		जाओ fail_मुक्त_lines;

	vमुक्त(chunk_meta);
	वापस 0;

fail_मुक्त_lines:
	जबतक (--i >= 0)
		pblk_line_meta_मुक्त(l_mg, &pblk->lines[i]);
	kमुक्त(pblk->lines);
fail_मुक्त_chunk_meta:
	vमुक्त(chunk_meta);
fail_मुक्त_luns:
	kमुक्त(pblk->luns);
fail_मुक्त_meta:
	pblk_line_mg_मुक्त(pblk);

	वापस ret;
पूर्ण

अटल पूर्णांक pblk_ग_लिखोr_init(काष्ठा pblk *pblk)
अणु
	pblk->ग_लिखोr_ts = kthपढ़ो_create(pblk_ग_लिखो_ts, pblk, "pblk-writer-t");
	अगर (IS_ERR(pblk->ग_लिखोr_ts)) अणु
		पूर्णांक err = PTR_ERR(pblk->ग_लिखोr_ts);

		अगर (err != -EINTR)
			pblk_err(pblk, "could not allocate writer kthread (%d)\n",
					err);
		वापस err;
	पूर्ण

	समयr_setup(&pblk->wसमयr, pblk_ग_लिखो_समयr_fn, 0);
	mod_समयr(&pblk->wसमयr, jअगरfies + msecs_to_jअगरfies(100));

	वापस 0;
पूर्ण

अटल व्योम pblk_ग_लिखोr_stop(काष्ठा pblk *pblk)
अणु
	/* The pipeline must be stopped and the ग_लिखो buffer emptied beक्रमe the
	 * ग_लिखो thपढ़ो is stopped
	 */
	WARN(pblk_rb_पढ़ो_count(&pblk->rwb),
			"Stopping not fully persisted write buffer\n");

	WARN(pblk_rb_sync_count(&pblk->rwb),
			"Stopping not fully synced write buffer\n");

	del_समयr_sync(&pblk->wसमयr);
	अगर (pblk->ग_लिखोr_ts)
		kthपढ़ो_stop(pblk->ग_लिखोr_ts);
पूर्ण

अटल व्योम pblk_मुक्त(काष्ठा pblk *pblk)
अणु
	pblk_lines_मुक्त(pblk);
	pblk_l2p_मुक्त(pblk);
	pblk_rwb_मुक्त(pblk);
	pblk_core_मुक्त(pblk);

	kमुक्त(pblk);
पूर्ण

अटल व्योम pblk_tear_करोwn(काष्ठा pblk *pblk, bool graceful)
अणु
	अगर (graceful)
		__pblk_pipeline_flush(pblk);
	__pblk_pipeline_stop(pblk);
	pblk_ग_लिखोr_stop(pblk);
	pblk_rb_sync_l2p(&pblk->rwb);
	pblk_rl_मुक्त(&pblk->rl);

	pblk_debug(pblk, "consistent tear down (graceful:%d)\n", graceful);
पूर्ण

अटल व्योम pblk_निकास(व्योम *निजी, bool graceful)
अणु
	काष्ठा pblk *pblk = निजी;

	pblk_gc_निकास(pblk, graceful);
	pblk_tear_करोwn(pblk, graceful);

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	pblk_info(pblk, "exit: L2P CRC: %x\n", pblk_l2p_crc(pblk));
#पूर्ण_अगर

	pblk_मुक्त(pblk);
पूर्ण

अटल sector_t pblk_capacity(व्योम *निजी)
अणु
	काष्ठा pblk *pblk = निजी;

	वापस pblk->capacity * NR_PHY_IN_LOG;
पूर्ण

अटल व्योम *pblk_init(काष्ठा nvm_tgt_dev *dev, काष्ठा gendisk *tdisk,
		       पूर्णांक flags)
अणु
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा request_queue *bqueue = dev->q;
	काष्ठा request_queue *tqueue = tdisk->queue;
	काष्ठा pblk *pblk;
	पूर्णांक ret;

	pblk = kzalloc(माप(काष्ठा pblk), GFP_KERNEL);
	अगर (!pblk)
		वापस ERR_PTR(-ENOMEM);

	pblk->dev = dev;
	pblk->disk = tdisk;
	pblk->state = PBLK_STATE_RUNNING;
	trace_pblk_state(pblk_disk_name(pblk), pblk->state);
	pblk->gc.gc_enabled = 0;

	अगर (!(geo->version == NVM_OCSSD_SPEC_12 ||
					geo->version == NVM_OCSSD_SPEC_20)) अणु
		pblk_err(pblk, "OCSSD version not supported (%u)\n",
							geo->version);
		kमुक्त(pblk);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (geo->ext) अणु
		pblk_err(pblk, "extended metadata not supported\n");
		kमुक्त(pblk);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	spin_lock_init(&pblk->resubmit_lock);
	spin_lock_init(&pblk->trans_lock);
	spin_lock_init(&pblk->lock);

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	atomic_दीर्घ_set(&pblk->inflight_ग_लिखोs, 0);
	atomic_दीर्घ_set(&pblk->padded_ग_लिखोs, 0);
	atomic_दीर्घ_set(&pblk->padded_wb, 0);
	atomic_दीर्घ_set(&pblk->req_ग_लिखोs, 0);
	atomic_दीर्घ_set(&pblk->sub_ग_लिखोs, 0);
	atomic_दीर्घ_set(&pblk->sync_ग_लिखोs, 0);
	atomic_दीर्घ_set(&pblk->inflight_पढ़ोs, 0);
	atomic_दीर्घ_set(&pblk->cache_पढ़ोs, 0);
	atomic_दीर्घ_set(&pblk->sync_पढ़ोs, 0);
	atomic_दीर्घ_set(&pblk->recov_ग_लिखोs, 0);
	atomic_दीर्घ_set(&pblk->recov_ग_लिखोs, 0);
	atomic_दीर्घ_set(&pblk->recov_gc_ग_लिखोs, 0);
	atomic_दीर्घ_set(&pblk->recov_gc_पढ़ोs, 0);
#पूर्ण_अगर

	atomic_दीर्घ_set(&pblk->पढ़ो_failed, 0);
	atomic_दीर्घ_set(&pblk->पढ़ो_empty, 0);
	atomic_दीर्घ_set(&pblk->पढ़ो_high_ecc, 0);
	atomic_दीर्घ_set(&pblk->पढ़ो_failed_gc, 0);
	atomic_दीर्घ_set(&pblk->ग_लिखो_failed, 0);
	atomic_दीर्घ_set(&pblk->erase_failed, 0);

	ret = pblk_core_init(pblk);
	अगर (ret) अणु
		pblk_err(pblk, "could not initialize core\n");
		जाओ fail;
	पूर्ण

	ret = pblk_lines_init(pblk);
	अगर (ret) अणु
		pblk_err(pblk, "could not initialize lines\n");
		जाओ fail_मुक्त_core;
	पूर्ण

	ret = pblk_rwb_init(pblk);
	अगर (ret) अणु
		pblk_err(pblk, "could not initialize write buffer\n");
		जाओ fail_मुक्त_lines;
	पूर्ण

	ret = pblk_l2p_init(pblk, flags & NVM_TARGET_FACTORY);
	अगर (ret) अणु
		pblk_err(pblk, "could not initialize maps\n");
		जाओ fail_मुक्त_rwb;
	पूर्ण

	ret = pblk_ग_लिखोr_init(pblk);
	अगर (ret) अणु
		अगर (ret != -EINTR)
			pblk_err(pblk, "could not initialize write thread\n");
		जाओ fail_मुक्त_l2p;
	पूर्ण

	ret = pblk_gc_init(pblk);
	अगर (ret) अणु
		pblk_err(pblk, "could not initialize gc\n");
		जाओ fail_stop_ग_लिखोr;
	पूर्ण

	/* inherit the size from the underlying device */
	blk_queue_logical_block_size(tqueue, queue_physical_block_size(bqueue));
	blk_queue_max_hw_sectors(tqueue, queue_max_hw_sectors(bqueue));

	blk_queue_ग_लिखो_cache(tqueue, true, false);

	tqueue->limits.discard_granularity = geo->clba * geo->csecs;
	tqueue->limits.discard_alignment = 0;
	blk_queue_max_discard_sectors(tqueue, अच_पूर्णांक_उच्च >> 9);
	blk_queue_flag_set(QUEUE_FLAG_DISCARD, tqueue);

	pblk_info(pblk, "luns:%u, lines:%d, secs:%llu, buf entries:%u\n",
			geo->all_luns, pblk->l_mg.nr_lines,
			(अचिन्हित दीर्घ दीर्घ)pblk->capacity,
			pblk->rwb.nr_entries);

	wake_up_process(pblk->ग_लिखोr_ts);

	/* Check अगर we need to start GC */
	pblk_gc_should_kick(pblk);

	वापस pblk;

fail_stop_ग_लिखोr:
	pblk_ग_लिखोr_stop(pblk);
fail_मुक्त_l2p:
	pblk_l2p_मुक्त(pblk);
fail_मुक्त_rwb:
	pblk_rwb_मुक्त(pblk);
fail_मुक्त_lines:
	pblk_lines_मुक्त(pblk);
fail_मुक्त_core:
	pblk_core_मुक्त(pblk);
fail:
	kमुक्त(pblk);
	वापस ERR_PTR(ret);
पूर्ण

/* physical block device target */
अटल काष्ठा nvm_tgt_type tt_pblk = अणु
	.name		= "pblk",
	.version	= अणु1, 0, 0पूर्ण,

	.bops		= &pblk_bops,
	.capacity	= pblk_capacity,

	.init		= pblk_init,
	.निकास		= pblk_निकास,

	.sysfs_init	= pblk_sysfs_init,
	.sysfs_निकास	= pblk_sysfs_निकास,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init pblk_module_init(व्योम)
अणु
	पूर्णांक ret;

	ret = bioset_init(&pblk_bio_set, BIO_POOL_SIZE, 0, 0);
	अगर (ret)
		वापस ret;
	ret = nvm_रेजिस्टर_tgt_type(&tt_pblk);
	अगर (ret)
		bioset_निकास(&pblk_bio_set);
	वापस ret;
पूर्ण

अटल व्योम pblk_module_निकास(व्योम)
अणु
	bioset_निकास(&pblk_bio_set);
	nvm_unरेजिस्टर_tgt_type(&tt_pblk);
पूर्ण

module_init(pblk_module_init);
module_निकास(pblk_module_निकास);
MODULE_AUTHOR("Javier Gonzalez <javier@cnexlabs.com>");
MODULE_AUTHOR("Matias Bjorling <matias@cnexlabs.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Physical Block-Device for Open-Channel SSDs");
