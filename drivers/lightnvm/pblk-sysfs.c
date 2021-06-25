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
 * Implementation of a physical block-device target क्रम Open-channel SSDs.
 *
 * pblk-sysfs.c - pblk's sysfs
 *
 */

#समावेश "pblk.h"

अटल sमाप_प्रकार pblk_sysfs_luns_show(काष्ठा pblk *pblk, अक्षर *page)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा pblk_lun *rlun;
	sमाप_प्रकार sz = 0;
	पूर्णांक i;

	क्रम (i = 0; i < geo->all_luns; i++) अणु
		पूर्णांक active = 1;

		rlun = &pblk->luns[i];
		अगर (!करोwn_trylock(&rlun->wr_sem)) अणु
			active = 0;
			up(&rlun->wr_sem);
		पूर्ण
		sz += scnम_लिखो(page + sz, PAGE_SIZE - sz,
				"pblk: pos:%d, ch:%d, lun:%d - %d\n",
					i,
					rlun->bppa.a.ch,
					rlun->bppa.a.lun,
					active);
	पूर्ण

	वापस sz;
पूर्ण

अटल sमाप_प्रकार pblk_sysfs_rate_limiter(काष्ठा pblk *pblk, अक्षर *page)
अणु
	पूर्णांक मुक्त_blocks, मुक्त_user_blocks, total_blocks;
	पूर्णांक rb_user_max, rb_user_cnt;
	पूर्णांक rb_gc_max, rb_gc_cnt, rb_budget, rb_state;

	मुक्त_blocks = pblk_rl_nr_मुक्त_blks(&pblk->rl);
	मुक्त_user_blocks = pblk_rl_nr_user_मुक्त_blks(&pblk->rl);
	rb_user_max = pblk->rl.rb_user_max;
	rb_user_cnt = atomic_पढ़ो(&pblk->rl.rb_user_cnt);
	rb_gc_max = pblk->rl.rb_gc_max;
	rb_gc_cnt = atomic_पढ़ो(&pblk->rl.rb_gc_cnt);
	rb_budget = pblk->rl.rb_budget;
	rb_state = pblk->rl.rb_state;

	total_blocks = pblk->rl.total_blocks;

	वापस snम_लिखो(page, PAGE_SIZE,
		"u:%u/%u,gc:%u/%u(%u)(stop:<%u,full:>%u,free:%d/%d/%d)-%d\n",
				rb_user_cnt,
				rb_user_max,
				rb_gc_cnt,
				rb_gc_max,
				rb_state,
				rb_budget,
				pblk->rl.high,
				मुक्त_blocks,
				मुक्त_user_blocks,
				total_blocks,
				READ_ONCE(pblk->rl.rb_user_active));
पूर्ण

अटल sमाप_प्रकार pblk_sysfs_gc_state_show(काष्ठा pblk *pblk, अक्षर *page)
अणु
	पूर्णांक gc_enabled, gc_active;

	pblk_gc_sysfs_state_show(pblk, &gc_enabled, &gc_active);
	वापस snम_लिखो(page, PAGE_SIZE, "gc_enabled=%d, gc_active=%d\n",
					gc_enabled, gc_active);
पूर्ण

अटल sमाप_प्रकार pblk_sysfs_stats(काष्ठा pblk *pblk, अक्षर *page)
अणु
	sमाप_प्रकार sz;

	sz = snम_लिखो(page, PAGE_SIZE,
			"read_failed=%lu, read_high_ecc=%lu, read_empty=%lu, read_failed_gc=%lu, write_failed=%lu, erase_failed=%lu\n",
			atomic_दीर्घ_पढ़ो(&pblk->पढ़ो_failed),
			atomic_दीर्घ_पढ़ो(&pblk->पढ़ो_high_ecc),
			atomic_दीर्घ_पढ़ो(&pblk->पढ़ो_empty),
			atomic_दीर्घ_पढ़ो(&pblk->पढ़ो_failed_gc),
			atomic_दीर्घ_पढ़ो(&pblk->ग_लिखो_failed),
			atomic_दीर्घ_पढ़ो(&pblk->erase_failed));

	वापस sz;
पूर्ण

अटल sमाप_प्रकार pblk_sysfs_ग_लिखो_buffer(काष्ठा pblk *pblk, अक्षर *page)
अणु
	वापस pblk_rb_sysfs(&pblk->rwb, page);
पूर्ण

अटल sमाप_प्रकार pblk_sysfs_ppaf(काष्ठा pblk *pblk, अक्षर *page)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	sमाप_प्रकार sz = 0;

	अगर (geo->version == NVM_OCSSD_SPEC_12) अणु
		काष्ठा nvm_addrf_12 *ppaf = (काष्ठा nvm_addrf_12 *)&pblk->addrf;
		काष्ठा nvm_addrf_12 *gppaf = (काष्ठा nvm_addrf_12 *)&geo->addrf;

		sz = scnम_लिखो(page, PAGE_SIZE,
			"g:(b:%d)blk:%d/%d,pg:%d/%d,lun:%d/%d,ch:%d/%d,pl:%d/%d,sec:%d/%d\n",
			pblk->addrf_len,
			ppaf->blk_offset, ppaf->blk_len,
			ppaf->pg_offset, ppaf->pg_len,
			ppaf->lun_offset, ppaf->lun_len,
			ppaf->ch_offset, ppaf->ch_len,
			ppaf->pln_offset, ppaf->pln_len,
			ppaf->sec_offset, ppaf->sec_len);

		sz += scnम_लिखो(page + sz, PAGE_SIZE - sz,
			"d:blk:%d/%d,pg:%d/%d,lun:%d/%d,ch:%d/%d,pl:%d/%d,sec:%d/%d\n",
			gppaf->blk_offset, gppaf->blk_len,
			gppaf->pg_offset, gppaf->pg_len,
			gppaf->lun_offset, gppaf->lun_len,
			gppaf->ch_offset, gppaf->ch_len,
			gppaf->pln_offset, gppaf->pln_len,
			gppaf->sec_offset, gppaf->sec_len);
	पूर्ण अन्यथा अणु
		काष्ठा nvm_addrf *ppaf = &pblk->addrf;
		काष्ठा nvm_addrf *gppaf = &geo->addrf;

		sz = scnम_लिखो(page, PAGE_SIZE,
			"pblk:(s:%d)ch:%d/%d,lun:%d/%d,chk:%d/%d/sec:%d/%d\n",
			pblk->addrf_len,
			ppaf->ch_offset, ppaf->ch_len,
			ppaf->lun_offset, ppaf->lun_len,
			ppaf->chk_offset, ppaf->chk_len,
			ppaf->sec_offset, ppaf->sec_len);

		sz += scnम_लिखो(page + sz, PAGE_SIZE - sz,
			"device:ch:%d/%d,lun:%d/%d,chk:%d/%d,sec:%d/%d\n",
			gppaf->ch_offset, gppaf->ch_len,
			gppaf->lun_offset, gppaf->lun_len,
			gppaf->chk_offset, gppaf->chk_len,
			gppaf->sec_offset, gppaf->sec_len);
	पूर्ण

	वापस sz;
पूर्ण

अटल sमाप_प्रकार pblk_sysfs_lines(काष्ठा pblk *pblk, अक्षर *page)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	काष्ठा pblk_line_mgmt *l_mg = &pblk->l_mg;
	काष्ठा pblk_line *line;
	sमाप_प्रकार sz = 0;
	पूर्णांक nr_मुक्त_lines;
	पूर्णांक cur_data, cur_log;
	पूर्णांक मुक्त_line_cnt = 0, बंदd_line_cnt = 0, emeta_line_cnt = 0;
	पूर्णांक d_line_cnt = 0, l_line_cnt = 0;
	पूर्णांक gc_full = 0, gc_high = 0, gc_mid = 0, gc_low = 0, gc_empty = 0;
	पूर्णांक gc_werr = 0;

	पूर्णांक bad = 0, cor = 0;
	पूर्णांक msecs = 0, cur_sec = 0, vsc = 0, sec_in_line = 0;
	पूर्णांक map_weight = 0, meta_weight = 0;

	spin_lock(&l_mg->मुक्त_lock);
	cur_data = (l_mg->data_line) ? l_mg->data_line->id : -1;
	cur_log = (l_mg->log_line) ? l_mg->log_line->id : -1;
	nr_मुक्त_lines = l_mg->nr_मुक्त_lines;

	list_क्रम_each_entry(line, &l_mg->मुक्त_list, list)
		मुक्त_line_cnt++;
	spin_unlock(&l_mg->मुक्त_lock);

	spin_lock(&l_mg->बंद_lock);
	list_क्रम_each_entry(line, &l_mg->emeta_list, list)
		emeta_line_cnt++;
	spin_unlock(&l_mg->बंद_lock);

	spin_lock(&l_mg->gc_lock);
	list_क्रम_each_entry(line, &l_mg->gc_full_list, list) अणु
		अगर (line->type == PBLK_LINETYPE_DATA)
			d_line_cnt++;
		अन्यथा अगर (line->type == PBLK_LINETYPE_LOG)
			l_line_cnt++;
		बंदd_line_cnt++;
		gc_full++;
	पूर्ण

	list_क्रम_each_entry(line, &l_mg->gc_high_list, list) अणु
		अगर (line->type == PBLK_LINETYPE_DATA)
			d_line_cnt++;
		अन्यथा अगर (line->type == PBLK_LINETYPE_LOG)
			l_line_cnt++;
		बंदd_line_cnt++;
		gc_high++;
	पूर्ण

	list_क्रम_each_entry(line, &l_mg->gc_mid_list, list) अणु
		अगर (line->type == PBLK_LINETYPE_DATA)
			d_line_cnt++;
		अन्यथा अगर (line->type == PBLK_LINETYPE_LOG)
			l_line_cnt++;
		बंदd_line_cnt++;
		gc_mid++;
	पूर्ण

	list_क्रम_each_entry(line, &l_mg->gc_low_list, list) अणु
		अगर (line->type == PBLK_LINETYPE_DATA)
			d_line_cnt++;
		अन्यथा अगर (line->type == PBLK_LINETYPE_LOG)
			l_line_cnt++;
		बंदd_line_cnt++;
		gc_low++;
	पूर्ण

	list_क्रम_each_entry(line, &l_mg->gc_empty_list, list) अणु
		अगर (line->type == PBLK_LINETYPE_DATA)
			d_line_cnt++;
		अन्यथा अगर (line->type == PBLK_LINETYPE_LOG)
			l_line_cnt++;
		बंदd_line_cnt++;
		gc_empty++;
	पूर्ण

	list_क्रम_each_entry(line, &l_mg->gc_werr_list, list) अणु
		अगर (line->type == PBLK_LINETYPE_DATA)
			d_line_cnt++;
		अन्यथा अगर (line->type == PBLK_LINETYPE_LOG)
			l_line_cnt++;
		बंदd_line_cnt++;
		gc_werr++;
	पूर्ण

	list_क्रम_each_entry(line, &l_mg->bad_list, list)
		bad++;
	list_क्रम_each_entry(line, &l_mg->corrupt_list, list)
		cor++;
	spin_unlock(&l_mg->gc_lock);

	spin_lock(&l_mg->मुक्त_lock);
	अगर (l_mg->data_line) अणु
		cur_sec = l_mg->data_line->cur_sec;
		msecs = l_mg->data_line->left_msecs;
		vsc = le32_to_cpu(*l_mg->data_line->vsc);
		sec_in_line = l_mg->data_line->sec_in_line;
		meta_weight = biपंचांगap_weight(&l_mg->meta_biपंचांगap,
							PBLK_DATA_LINES);

		spin_lock(&l_mg->data_line->lock);
		अगर (l_mg->data_line->map_biपंचांगap)
			map_weight = biपंचांगap_weight(l_mg->data_line->map_biपंचांगap,
							lm->sec_per_line);
		अन्यथा
			map_weight = 0;
		spin_unlock(&l_mg->data_line->lock);
	पूर्ण
	spin_unlock(&l_mg->मुक्त_lock);

	अगर (nr_मुक्त_lines != मुक्त_line_cnt)
		pblk_err(pblk, "corrupted free line list:%d/%d\n",
						nr_मुक्त_lines, मुक्त_line_cnt);

	sz = scnम_लिखो(page, PAGE_SIZE - sz,
		"line: nluns:%d, nblks:%d, nsecs:%d\n",
		geo->all_luns, lm->blk_per_line, lm->sec_per_line);

	sz += scnम_लिखो(page + sz, PAGE_SIZE - sz,
		"lines:d:%d,l:%d-f:%d,m:%d/%d,c:%d,b:%d,co:%d(d:%d,l:%d)t:%d\n",
					cur_data, cur_log,
					nr_मुक्त_lines,
					emeta_line_cnt, meta_weight,
					बंदd_line_cnt,
					bad, cor,
					d_line_cnt, l_line_cnt,
					l_mg->nr_lines);

	sz += scnम_लिखो(page + sz, PAGE_SIZE - sz,
		"GC: full:%d, high:%d, mid:%d, low:%d, empty:%d, werr: %d, queue:%d\n",
			gc_full, gc_high, gc_mid, gc_low, gc_empty, gc_werr,
			atomic_पढ़ो(&pblk->gc.पढ़ो_inflight_gc));

	sz += scnम_लिखो(page + sz, PAGE_SIZE - sz,
		"data (%d) cur:%d, left:%d, vsc:%d, s:%d, map:%d/%d (%d)\n",
			cur_data, cur_sec, msecs, vsc, sec_in_line,
			map_weight, lm->sec_per_line,
			atomic_पढ़ो(&pblk->inflight_io));

	वापस sz;
पूर्ण

अटल sमाप_प्रकार pblk_sysfs_lines_info(काष्ठा pblk *pblk, अक्षर *page)
अणु
	काष्ठा nvm_tgt_dev *dev = pblk->dev;
	काष्ठा nvm_geo *geo = &dev->geo;
	काष्ठा pblk_line_meta *lm = &pblk->lm;
	sमाप_प्रकार sz = 0;

	sz = scnम_लिखो(page, PAGE_SIZE - sz,
				"smeta - len:%d, secs:%d\n",
					lm->smeta_len, lm->smeta_sec);
	sz += scnम_लिखो(page + sz, PAGE_SIZE - sz,
				"emeta - len:%d, sec:%d, bb_start:%d\n",
					lm->emeta_len[0], lm->emeta_sec[0],
					lm->emeta_bb);
	sz += scnम_लिखो(page + sz, PAGE_SIZE - sz,
				"bitmap lengths: sec:%d, blk:%d, lun:%d\n",
					lm->sec_biपंचांगap_len,
					lm->blk_biपंचांगap_len,
					lm->lun_biपंचांगap_len);
	sz += scnम_लिखो(page + sz, PAGE_SIZE - sz,
				"blk_line:%d, sec_line:%d, sec_blk:%d\n",
					lm->blk_per_line,
					lm->sec_per_line,
					geo->clba);

	वापस sz;
पूर्ण

अटल sमाप_प्रकार pblk_sysfs_get_sec_per_ग_लिखो(काष्ठा pblk *pblk, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%d\n", pblk->sec_per_ग_लिखो);
पूर्ण

अटल sमाप_प्रकार pblk_get_ग_लिखो_amp(u64 user, u64 gc, u64 pad,
				  अक्षर *page)
अणु
	पूर्णांक sz;

	sz = scnम_लिखो(page, PAGE_SIZE,
			"user:%lld gc:%lld pad:%lld WA:",
			user, gc, pad);

	अगर (!user) अणु
		sz += scnम_लिखो(page + sz, PAGE_SIZE - sz, "NaN\n");
	पूर्ण अन्यथा अणु
		u64 wa_पूर्णांक;
		u32 wa_frac;

		wa_पूर्णांक = (user + gc + pad) * 100000;
		wa_पूर्णांक = भाग64_u64(wa_पूर्णांक, user);
		wa_पूर्णांक = भाग_u64_rem(wa_पूर्णांक, 100000, &wa_frac);

		sz += scnम_लिखो(page + sz, PAGE_SIZE - sz, "%llu.%05u\n",
							wa_पूर्णांक, wa_frac);
	पूर्ण

	वापस sz;
पूर्ण

अटल sमाप_प्रकार pblk_sysfs_get_ग_लिखो_amp_mileage(काष्ठा pblk *pblk, अक्षर *page)
अणु
	वापस pblk_get_ग_लिखो_amp(atomic64_पढ़ो(&pblk->user_wa),
		atomic64_पढ़ो(&pblk->gc_wa), atomic64_पढ़ो(&pblk->pad_wa),
		page);
पूर्ण

अटल sमाप_प्रकार pblk_sysfs_get_ग_लिखो_amp_trip(काष्ठा pblk *pblk, अक्षर *page)
अणु
	वापस pblk_get_ग_लिखो_amp(
		atomic64_पढ़ो(&pblk->user_wa) - pblk->user_rst_wa,
		atomic64_पढ़ो(&pblk->gc_wa) - pblk->gc_rst_wa,
		atomic64_पढ़ो(&pblk->pad_wa) - pblk->pad_rst_wa, page);
पूर्ण

अटल दीर्घ दीर्घ bucket_percentage(अचिन्हित दीर्घ दीर्घ bucket,
				   अचिन्हित दीर्घ दीर्घ total)
अणु
	पूर्णांक p = bucket * 100;

	p = भाग_u64(p, total);

	वापस p;
पूर्ण

अटल sमाप_प्रकार pblk_sysfs_get_padding_dist(काष्ठा pblk *pblk, अक्षर *page)
अणु
	पूर्णांक sz = 0;
	अचिन्हित दीर्घ दीर्घ total;
	अचिन्हित दीर्घ दीर्घ total_buckets = 0;
	पूर्णांक buckets = pblk->min_ग_लिखो_pgs - 1;
	पूर्णांक i;

	total = atomic64_पढ़ो(&pblk->nr_flush) - pblk->nr_flush_rst;
	अगर (!total) अणु
		क्रम (i = 0; i < (buckets + 1); i++)
			sz += scnम_लिखो(page + sz, PAGE_SIZE - sz,
				"%d:0 ", i);
		sz += scnम_लिखो(page + sz, PAGE_SIZE - sz, "\n");

		वापस sz;
	पूर्ण

	क्रम (i = 0; i < buckets; i++)
		total_buckets += atomic64_पढ़ो(&pblk->pad_dist[i]);

	sz += scnम_लिखो(page + sz, PAGE_SIZE - sz, "0:%lld%% ",
		bucket_percentage(total - total_buckets, total));

	क्रम (i = 0; i < buckets; i++) अणु
		अचिन्हित दीर्घ दीर्घ p;

		p = bucket_percentage(atomic64_पढ़ो(&pblk->pad_dist[i]),
					  total);
		sz += scnम_लिखो(page + sz, PAGE_SIZE - sz, "%d:%lld%% ",
				i + 1, p);
	पूर्ण
	sz += scnम_लिखो(page + sz, PAGE_SIZE - sz, "\n");

	वापस sz;
पूर्ण

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
अटल sमाप_प्रकार pblk_sysfs_stats_debug(काष्ठा pblk *pblk, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE,
		"%lu\t%lu\t%ld\t%llu\t%ld\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\n",
			atomic_दीर्घ_पढ़ो(&pblk->inflight_ग_लिखोs),
			atomic_दीर्घ_पढ़ो(&pblk->inflight_पढ़ोs),
			atomic_दीर्घ_पढ़ो(&pblk->req_ग_लिखोs),
			(u64)atomic64_पढ़ो(&pblk->nr_flush),
			atomic_दीर्घ_पढ़ो(&pblk->padded_ग_लिखोs),
			atomic_दीर्घ_पढ़ो(&pblk->padded_wb),
			atomic_दीर्घ_पढ़ो(&pblk->sub_ग_लिखोs),
			atomic_दीर्घ_पढ़ो(&pblk->sync_ग_लिखोs),
			atomic_दीर्घ_पढ़ो(&pblk->recov_ग_लिखोs),
			atomic_दीर्घ_पढ़ो(&pblk->recov_gc_ग_लिखोs),
			atomic_दीर्घ_पढ़ो(&pblk->recov_gc_पढ़ोs),
			atomic_दीर्घ_पढ़ो(&pblk->cache_पढ़ोs),
			atomic_दीर्घ_पढ़ो(&pblk->sync_पढ़ोs));
पूर्ण
#पूर्ण_अगर

अटल sमाप_प्रकार pblk_sysfs_gc_क्रमce(काष्ठा pblk *pblk, स्थिर अक्षर *page,
				   माप_प्रकार len)
अणु
	माप_प्रकार c_len;
	पूर्णांक क्रमce;

	c_len = म_खोज(page, "\n");
	अगर (c_len >= len)
		वापस -EINVAL;

	अगर (kstrtouपूर्णांक(page, 0, &क्रमce))
		वापस -EINVAL;

	pblk_gc_sysfs_क्रमce(pblk, क्रमce);

	वापस len;
पूर्ण

अटल sमाप_प्रकार pblk_sysfs_set_sec_per_ग_लिखो(काष्ठा pblk *pblk,
					     स्थिर अक्षर *page, माप_प्रकार len)
अणु
	माप_प्रकार c_len;
	पूर्णांक sec_per_ग_लिखो;

	c_len = म_खोज(page, "\n");
	अगर (c_len >= len)
		वापस -EINVAL;

	अगर (kstrtouपूर्णांक(page, 0, &sec_per_ग_लिखो))
		वापस -EINVAL;

	अगर (!pblk_is_oob_meta_supported(pblk)) अणु
		/* For packed metadata हाल it is
		 * not allowed to change sec_per_ग_लिखो.
		 */
		वापस -EINVAL;
	पूर्ण

	अगर (sec_per_ग_लिखो < pblk->min_ग_लिखो_pgs
				|| sec_per_ग_लिखो > pblk->max_ग_लिखो_pgs
				|| sec_per_ग_लिखो % pblk->min_ग_लिखो_pgs != 0)
		वापस -EINVAL;

	pblk_set_sec_per_ग_लिखो(pblk, sec_per_ग_लिखो);

	वापस len;
पूर्ण

अटल sमाप_प्रकार pblk_sysfs_set_ग_लिखो_amp_trip(काष्ठा pblk *pblk,
			स्थिर अक्षर *page, माप_प्रकार len)
अणु
	माप_प्रकार c_len;
	पूर्णांक reset_value;

	c_len = म_खोज(page, "\n");
	अगर (c_len >= len)
		वापस -EINVAL;

	अगर (kstrtouपूर्णांक(page, 0, &reset_value))
		वापस -EINVAL;

	अगर (reset_value !=  0)
		वापस -EINVAL;

	pblk->user_rst_wa = atomic64_पढ़ो(&pblk->user_wa);
	pblk->pad_rst_wa = atomic64_पढ़ो(&pblk->pad_wa);
	pblk->gc_rst_wa = atomic64_पढ़ो(&pblk->gc_wa);

	वापस len;
पूर्ण


अटल sमाप_प्रकार pblk_sysfs_set_padding_dist(काष्ठा pblk *pblk,
			स्थिर अक्षर *page, माप_प्रकार len)
अणु
	माप_प्रकार c_len;
	पूर्णांक reset_value;
	पूर्णांक buckets = pblk->min_ग_लिखो_pgs - 1;
	पूर्णांक i;

	c_len = म_खोज(page, "\n");
	अगर (c_len >= len)
		वापस -EINVAL;

	अगर (kstrtouपूर्णांक(page, 0, &reset_value))
		वापस -EINVAL;

	अगर (reset_value !=  0)
		वापस -EINVAL;

	क्रम (i = 0; i < buckets; i++)
		atomic64_set(&pblk->pad_dist[i], 0);

	pblk->nr_flush_rst = atomic64_पढ़ो(&pblk->nr_flush);

	वापस len;
पूर्ण

अटल काष्ठा attribute sys_ग_लिखो_luns = अणु
	.name = "write_luns",
	.mode = 0444,
पूर्ण;

अटल काष्ठा attribute sys_rate_limiter_attr = अणु
	.name = "rate_limiter",
	.mode = 0444,
पूर्ण;

अटल काष्ठा attribute sys_gc_state = अणु
	.name = "gc_state",
	.mode = 0444,
पूर्ण;

अटल काष्ठा attribute sys_errors_attr = अणु
	.name = "errors",
	.mode = 0444,
पूर्ण;

अटल काष्ठा attribute sys_rb_attr = अणु
	.name = "write_buffer",
	.mode = 0444,
पूर्ण;

अटल काष्ठा attribute sys_stats_ppaf_attr = अणु
	.name = "ppa_format",
	.mode = 0444,
पूर्ण;

अटल काष्ठा attribute sys_lines_attr = अणु
	.name = "lines",
	.mode = 0444,
पूर्ण;

अटल काष्ठा attribute sys_lines_info_attr = अणु
	.name = "lines_info",
	.mode = 0444,
पूर्ण;

अटल काष्ठा attribute sys_gc_क्रमce = अणु
	.name = "gc_force",
	.mode = 0200,
पूर्ण;

अटल काष्ठा attribute sys_max_sec_per_ग_लिखो = अणु
	.name = "max_sec_per_write",
	.mode = 0644,
पूर्ण;

अटल काष्ठा attribute sys_ग_लिखो_amp_mileage = अणु
	.name = "write_amp_mileage",
	.mode = 0444,
पूर्ण;

अटल काष्ठा attribute sys_ग_लिखो_amp_trip = अणु
	.name = "write_amp_trip",
	.mode = 0644,
पूर्ण;

अटल काष्ठा attribute sys_padding_dist = अणु
	.name = "padding_dist",
	.mode = 0644,
पूर्ण;

#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
अटल काष्ठा attribute sys_stats_debug_attr = अणु
	.name = "stats",
	.mode = 0444,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा attribute *pblk_attrs[] = अणु
	&sys_ग_लिखो_luns,
	&sys_rate_limiter_attr,
	&sys_errors_attr,
	&sys_gc_state,
	&sys_gc_क्रमce,
	&sys_max_sec_per_ग_लिखो,
	&sys_rb_attr,
	&sys_stats_ppaf_attr,
	&sys_lines_attr,
	&sys_lines_info_attr,
	&sys_ग_लिखो_amp_mileage,
	&sys_ग_लिखो_amp_trip,
	&sys_padding_dist,
#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	&sys_stats_debug_attr,
#पूर्ण_अगर
	शून्य,
पूर्ण;

अटल sमाप_प्रकार pblk_sysfs_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा pblk *pblk = container_of(kobj, काष्ठा pblk, kobj);

	अगर (म_भेद(attr->name, "rate_limiter") == 0)
		वापस pblk_sysfs_rate_limiter(pblk, buf);
	अन्यथा अगर (म_भेद(attr->name, "write_luns") == 0)
		वापस pblk_sysfs_luns_show(pblk, buf);
	अन्यथा अगर (म_भेद(attr->name, "gc_state") == 0)
		वापस pblk_sysfs_gc_state_show(pblk, buf);
	अन्यथा अगर (म_भेद(attr->name, "errors") == 0)
		वापस pblk_sysfs_stats(pblk, buf);
	अन्यथा अगर (म_भेद(attr->name, "write_buffer") == 0)
		वापस pblk_sysfs_ग_लिखो_buffer(pblk, buf);
	अन्यथा अगर (म_भेद(attr->name, "ppa_format") == 0)
		वापस pblk_sysfs_ppaf(pblk, buf);
	अन्यथा अगर (म_भेद(attr->name, "lines") == 0)
		वापस pblk_sysfs_lines(pblk, buf);
	अन्यथा अगर (म_भेद(attr->name, "lines_info") == 0)
		वापस pblk_sysfs_lines_info(pblk, buf);
	अन्यथा अगर (म_भेद(attr->name, "max_sec_per_write") == 0)
		वापस pblk_sysfs_get_sec_per_ग_लिखो(pblk, buf);
	अन्यथा अगर (म_भेद(attr->name, "write_amp_mileage") == 0)
		वापस pblk_sysfs_get_ग_लिखो_amp_mileage(pblk, buf);
	अन्यथा अगर (म_भेद(attr->name, "write_amp_trip") == 0)
		वापस pblk_sysfs_get_ग_लिखो_amp_trip(pblk, buf);
	अन्यथा अगर (म_भेद(attr->name, "padding_dist") == 0)
		वापस pblk_sysfs_get_padding_dist(pblk, buf);
#अगर_घोषित CONFIG_NVM_PBLK_DEBUG
	अन्यथा अगर (म_भेद(attr->name, "stats") == 0)
		वापस pblk_sysfs_stats_debug(pblk, buf);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल sमाप_प्रकार pblk_sysfs_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा pblk *pblk = container_of(kobj, काष्ठा pblk, kobj);

	अगर (म_भेद(attr->name, "gc_force") == 0)
		वापस pblk_sysfs_gc_क्रमce(pblk, buf, len);
	अन्यथा अगर (म_भेद(attr->name, "max_sec_per_write") == 0)
		वापस pblk_sysfs_set_sec_per_ग_लिखो(pblk, buf, len);
	अन्यथा अगर (म_भेद(attr->name, "write_amp_trip") == 0)
		वापस pblk_sysfs_set_ग_लिखो_amp_trip(pblk, buf, len);
	अन्यथा अगर (म_भेद(attr->name, "padding_dist") == 0)
		वापस pblk_sysfs_set_padding_dist(pblk, buf, len);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops pblk_sysfs_ops = अणु
	.show = pblk_sysfs_show,
	.store = pblk_sysfs_store,
पूर्ण;

अटल काष्ठा kobj_type pblk_ktype = अणु
	.sysfs_ops	= &pblk_sysfs_ops,
	.शेष_attrs	= pblk_attrs,
पूर्ण;

पूर्णांक pblk_sysfs_init(काष्ठा gendisk *tdisk)
अणु
	काष्ठा pblk *pblk = tdisk->निजी_data;
	काष्ठा device *parent_dev = disk_to_dev(pblk->disk);
	पूर्णांक ret;

	ret = kobject_init_and_add(&pblk->kobj, &pblk_ktype,
					kobject_get(&parent_dev->kobj),
					"%s", "pblk");
	अगर (ret) अणु
		pblk_err(pblk, "could not register\n");
		वापस ret;
	पूर्ण

	kobject_uevent(&pblk->kobj, KOBJ_ADD);
	वापस 0;
पूर्ण

व्योम pblk_sysfs_निकास(काष्ठा gendisk *tdisk)
अणु
	काष्ठा pblk *pblk = tdisk->निजी_data;

	kobject_uevent(&pblk->kobj, KOBJ_REMOVE);
	kobject_del(&pblk->kobj);
	kobject_put(&pblk->kobj);
पूर्ण
