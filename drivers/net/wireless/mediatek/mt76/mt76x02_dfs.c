<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#समावेश "mt76x02.h"

#घोषणा RADAR_SPEC(m, len, el, eh, wl, wh,		\
		   w_tolerance, tl, th, t_tolerance,	\
		   bl, bh, event_exp, घातer_jmp)	\
अणु							\
	.mode = m,					\
	.avg_len = len,					\
	.e_low = el,					\
	.e_high = eh,					\
	.w_low = wl,					\
	.w_high = wh,					\
	.w_margin = w_tolerance,			\
	.t_low = tl,					\
	.t_high = th,					\
	.t_margin = t_tolerance,			\
	.b_low = bl,					\
	.b_high = bh,					\
	.event_expiration = event_exp,			\
	.pwr_jmp = घातer_jmp				\
पूर्ण

अटल स्थिर काष्ठा mt76x02_radar_specs etsi_radar_specs[] = अणु
	/* 20MHz */
	RADAR_SPEC(0, 8, 2, 15, 106, 150, 10, 4900, 100096, 10, 0,
		   0x7fffffff, 0x155cc0, 0x19cc),
	RADAR_SPEC(0, 40, 4, 59, 96, 380, 150, 4900, 100096, 40, 0,
		   0x7fffffff, 0x155cc0, 0x19cc),
	RADAR_SPEC(3, 60, 20, 46, 300, 640, 80, 4900, 10100, 80, 0,
		   0x7fffffff, 0x155cc0, 0x19dd),
	RADAR_SPEC(8, 8, 2, 9, 106, 150, 32, 4900, 296704, 32, 0,
		   0x7fffffff, 0x2191c0, 0x15cc),
	/* 40MHz */
	RADAR_SPEC(0, 8, 2, 15, 106, 150, 10, 4900, 100096, 10, 0,
		   0x7fffffff, 0x155cc0, 0x19cc),
	RADAR_SPEC(0, 40, 4, 59, 96, 380, 150, 4900, 100096, 40, 0,
		   0x7fffffff, 0x155cc0, 0x19cc),
	RADAR_SPEC(3, 60, 20, 46, 300, 640, 80, 4900, 10100, 80, 0,
		   0x7fffffff, 0x155cc0, 0x19dd),
	RADAR_SPEC(8, 8, 2, 9, 106, 150, 32, 4900, 296704, 32, 0,
		   0x7fffffff, 0x2191c0, 0x15cc),
	/* 80MHz */
	RADAR_SPEC(0, 8, 2, 15, 106, 150, 10, 4900, 100096, 10, 0,
		   0x7fffffff, 0x155cc0, 0x19cc),
	RADAR_SPEC(0, 40, 4, 59, 96, 380, 150, 4900, 100096, 40, 0,
		   0x7fffffff, 0x155cc0, 0x19cc),
	RADAR_SPEC(3, 60, 20, 46, 300, 640, 80, 4900, 10100, 80, 0,
		   0x7fffffff, 0x155cc0, 0x19dd),
	RADAR_SPEC(8, 8, 2, 9, 106, 150, 32, 4900, 296704, 32, 0,
		   0x7fffffff, 0x2191c0, 0x15cc)
पूर्ण;

अटल स्थिर काष्ठा mt76x02_radar_specs fcc_radar_specs[] = अणु
	/* 20MHz */
	RADAR_SPEC(0, 8, 2, 12, 106, 150, 5, 2900, 80100, 5, 0,
		   0x7fffffff, 0xfe808, 0x13dc),
	RADAR_SPEC(0, 8, 2, 7, 106, 140, 5, 27600, 27900, 5, 0,
		   0x7fffffff, 0xfe808, 0x19dd),
	RADAR_SPEC(0, 40, 4, 54, 96, 480, 150, 2900, 80100, 40, 0,
		   0x7fffffff, 0xfe808, 0x12cc),
	RADAR_SPEC(2, 60, 15, 63, 640, 2080, 32, 19600, 40200, 32, 0,
		   0x3938700, 0x57bcf00, 0x1289),
	/* 40MHz */
	RADAR_SPEC(0, 8, 2, 12, 106, 150, 5, 2900, 80100, 5, 0,
		   0x7fffffff, 0xfe808, 0x13dc),
	RADAR_SPEC(0, 8, 2, 7, 106, 140, 5, 27600, 27900, 5, 0,
		   0x7fffffff, 0xfe808, 0x19dd),
	RADAR_SPEC(0, 40, 4, 54, 96, 480, 150, 2900, 80100, 40, 0,
		   0x7fffffff, 0xfe808, 0x12cc),
	RADAR_SPEC(2, 60, 15, 63, 640, 2080, 32, 19600, 40200, 32, 0,
		   0x3938700, 0x57bcf00, 0x1289),
	/* 80MHz */
	RADAR_SPEC(0, 8, 2, 14, 106, 150, 15, 2900, 80100, 15, 0,
		   0x7fffffff, 0xfe808, 0x16cc),
	RADAR_SPEC(0, 8, 2, 7, 106, 140, 5, 27600, 27900, 5, 0,
		   0x7fffffff, 0xfe808, 0x19dd),
	RADAR_SPEC(0, 40, 4, 54, 96, 480, 150, 2900, 80100, 40, 0,
		   0x7fffffff, 0xfe808, 0x12cc),
	RADAR_SPEC(2, 60, 15, 63, 640, 2080, 32, 19600, 40200, 32, 0,
		   0x3938700, 0x57bcf00, 0x1289)
पूर्ण;

अटल स्थिर काष्ठा mt76x02_radar_specs jp_w56_radar_specs[] = अणु
	/* 20MHz */
	RADAR_SPEC(0, 8, 2, 7, 106, 150, 5, 2900, 80100, 5, 0,
		   0x7fffffff, 0x14c080, 0x13dc),
	RADAR_SPEC(0, 8, 2, 7, 106, 140, 5, 27600, 27900, 5, 0,
		   0x7fffffff, 0x14c080, 0x19dd),
	RADAR_SPEC(0, 40, 4, 44, 96, 480, 150, 2900, 80100, 40, 0,
		   0x7fffffff, 0x14c080, 0x12cc),
	RADAR_SPEC(2, 60, 15, 48, 940, 2080, 32, 19600, 40200, 32, 0,
		   0x3938700, 0X57bcf00, 0x1289),
	/* 40MHz */
	RADAR_SPEC(0, 8, 2, 7, 106, 150, 5, 2900, 80100, 5, 0,
		   0x7fffffff, 0x14c080, 0x13dc),
	RADAR_SPEC(0, 8, 2, 7, 106, 140, 5, 27600, 27900, 5, 0,
		   0x7fffffff, 0x14c080, 0x19dd),
	RADAR_SPEC(0, 40, 4, 44, 96, 480, 150, 2900, 80100, 40, 0,
		   0x7fffffff, 0x14c080, 0x12cc),
	RADAR_SPEC(2, 60, 15, 48, 940, 2080, 32, 19600, 40200, 32, 0,
		   0x3938700, 0X57bcf00, 0x1289),
	/* 80MHz */
	RADAR_SPEC(0, 8, 2, 9, 106, 150, 15, 2900, 80100, 15, 0,
		   0x7fffffff, 0x14c080, 0x16cc),
	RADAR_SPEC(0, 8, 2, 7, 106, 140, 5, 27600, 27900, 5, 0,
		   0x7fffffff, 0x14c080, 0x19dd),
	RADAR_SPEC(0, 40, 4, 44, 96, 480, 150, 2900, 80100, 40, 0,
		   0x7fffffff, 0x14c080, 0x12cc),
	RADAR_SPEC(2, 60, 15, 48, 940, 2080, 32, 19600, 40200, 32, 0,
		   0x3938700, 0X57bcf00, 0x1289)
पूर्ण;

अटल स्थिर काष्ठा mt76x02_radar_specs jp_w53_radar_specs[] = अणु
	/* 20MHz */
	RADAR_SPEC(0, 8, 2, 9, 106, 150, 20, 28400, 77000, 20, 0,
		   0x7fffffff, 0x14c080, 0x16cc),
	अणु 0 पूर्ण,
	RADAR_SPEC(0, 40, 4, 44, 96, 200, 150, 28400, 77000, 60, 0,
		   0x7fffffff, 0x14c080, 0x16cc),
	अणु 0 पूर्ण,
	/* 40MHz */
	RADAR_SPEC(0, 8, 2, 9, 106, 150, 20, 28400, 77000, 20, 0,
		   0x7fffffff, 0x14c080, 0x16cc),
	अणु 0 पूर्ण,
	RADAR_SPEC(0, 40, 4, 44, 96, 200, 150, 28400, 77000, 60, 0,
		   0x7fffffff, 0x14c080, 0x16cc),
	अणु 0 पूर्ण,
	/* 80MHz */
	RADAR_SPEC(0, 8, 2, 9, 106, 150, 20, 28400, 77000, 20, 0,
		   0x7fffffff, 0x14c080, 0x16cc),
	अणु 0 पूर्ण,
	RADAR_SPEC(0, 40, 4, 44, 96, 200, 150, 28400, 77000, 60, 0,
		   0x7fffffff, 0x14c080, 0x16cc),
	अणु 0 पूर्ण
पूर्ण;

अटल व्योम
mt76x02_dfs_set_capture_mode_ctrl(काष्ठा mt76x02_dev *dev, u8 enable)
अणु
	u32 data;

	data = (1 << 1) | enable;
	mt76_wr(dev, MT_BBP(DFS, 36), data);
पूर्ण

अटल व्योम mt76x02_dfs_seq_pool_put(काष्ठा mt76x02_dev *dev,
				     काष्ठा mt76x02_dfs_sequence *seq)
अणु
	काष्ठा mt76x02_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;

	list_add(&seq->head, &dfs_pd->seq_pool);

	dfs_pd->seq_stats.seq_pool_len++;
	dfs_pd->seq_stats.seq_len--;
पूर्ण

अटल काष्ठा mt76x02_dfs_sequence *
mt76x02_dfs_seq_pool_get(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा mt76x02_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;
	काष्ठा mt76x02_dfs_sequence *seq;

	अगर (list_empty(&dfs_pd->seq_pool)) अणु
		seq = devm_kzalloc(dev->mt76.dev, माप(*seq), GFP_ATOMIC);
	पूर्ण अन्यथा अणु
		seq = list_first_entry(&dfs_pd->seq_pool,
				       काष्ठा mt76x02_dfs_sequence,
				       head);
		list_del(&seq->head);
		dfs_pd->seq_stats.seq_pool_len--;
	पूर्ण
	अगर (seq)
		dfs_pd->seq_stats.seq_len++;

	वापस seq;
पूर्ण

अटल पूर्णांक mt76x02_dfs_get_multiple(पूर्णांक val, पूर्णांक frac, पूर्णांक margin)
अणु
	पूर्णांक reमुख्यder, factor;

	अगर (!frac)
		वापस 0;

	अगर (असल(val - frac) <= margin)
		वापस 1;

	factor = val / frac;
	reमुख्यder = val % frac;

	अगर (reमुख्यder > margin) अणु
		अगर ((frac - reमुख्यder) <= margin)
			factor++;
		अन्यथा
			factor = 0;
	पूर्ण
	वापस factor;
पूर्ण

अटल व्योम mt76x02_dfs_detector_reset(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा mt76x02_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;
	काष्ठा mt76x02_dfs_sequence *seq, *पंचांगp_seq;
	पूर्णांक i;

	/* reset hw detector */
	mt76_wr(dev, MT_BBP(DFS, 1), 0xf);

	/* reset sw detector */
	क्रम (i = 0; i < ARRAY_SIZE(dfs_pd->event_rb); i++) अणु
		dfs_pd->event_rb[i].h_rb = 0;
		dfs_pd->event_rb[i].t_rb = 0;
	पूर्ण

	list_क्रम_each_entry_safe(seq, पंचांगp_seq, &dfs_pd->sequences, head) अणु
		list_del_init(&seq->head);
		mt76x02_dfs_seq_pool_put(dev, seq);
	पूर्ण
पूर्ण

अटल bool mt76x02_dfs_check_chirp(काष्ठा mt76x02_dev *dev)
अणु
	bool ret = false;
	u32 current_ts, delta_ts;
	काष्ठा mt76x02_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;

	current_ts = mt76_rr(dev, MT_PBF_LIFE_TIMER);
	delta_ts = current_ts - dfs_pd->chirp_pulse_ts;
	dfs_pd->chirp_pulse_ts = current_ts;

	/* 12 sec */
	अगर (delta_ts <= (12 * (1 << 20))) अणु
		अगर (++dfs_pd->chirp_pulse_cnt > 8)
			ret = true;
	पूर्ण अन्यथा अणु
		dfs_pd->chirp_pulse_cnt = 1;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम mt76x02_dfs_get_hw_pulse(काष्ठा mt76x02_dev *dev,
				     काष्ठा mt76x02_dfs_hw_pulse *pulse)
अणु
	u32 data;

	/* select channel */
	data = (MT_DFS_CH_EN << 16) | pulse->engine;
	mt76_wr(dev, MT_BBP(DFS, 0), data);

	/* reported period */
	pulse->period = mt76_rr(dev, MT_BBP(DFS, 19));

	/* reported width */
	pulse->w1 = mt76_rr(dev, MT_BBP(DFS, 20));
	pulse->w2 = mt76_rr(dev, MT_BBP(DFS, 23));

	/* reported burst number */
	pulse->burst = mt76_rr(dev, MT_BBP(DFS, 22));
पूर्ण

अटल bool mt76x02_dfs_check_hw_pulse(काष्ठा mt76x02_dev *dev,
				       काष्ठा mt76x02_dfs_hw_pulse *pulse)
अणु
	bool ret = false;

	अगर (!pulse->period || !pulse->w1)
		वापस false;

	चयन (dev->mt76.region) अणु
	हाल NL80211_DFS_FCC:
		अगर (pulse->engine > 3)
			अवरोध;

		अगर (pulse->engine == 3) अणु
			ret = mt76x02_dfs_check_chirp(dev);
			अवरोध;
		पूर्ण

		/* check लघु pulse*/
		अगर (pulse->w1 < 120)
			ret = (pulse->period >= 2900 &&
			       (pulse->period <= 4700 ||
				pulse->period >= 6400) &&
			       (pulse->period <= 6800 ||
				pulse->period >= 10200) &&
			       pulse->period <= 61600);
		अन्यथा अगर (pulse->w1 < 130) /* 120 - 130 */
			ret = (pulse->period >= 2900 &&
			       pulse->period <= 61600);
		अन्यथा
			ret = (pulse->period >= 3500 &&
			       pulse->period <= 10100);
		अवरोध;
	हाल NL80211_DFS_ETSI:
		अगर (pulse->engine >= 3)
			अवरोध;

		ret = (pulse->period >= 4900 &&
		       (pulse->period <= 10200 ||
			pulse->period >= 12400) &&
		       pulse->period <= 100100);
		अवरोध;
	हाल NL80211_DFS_JP:
		अगर (dev->mphy.chandef.chan->center_freq >= 5250 &&
		    dev->mphy.chandef.chan->center_freq <= 5350) अणु
			/* JPW53 */
			अगर (pulse->w1 <= 130)
				ret = (pulse->period >= 28360 &&
				       (pulse->period <= 28700 ||
					pulse->period >= 76900) &&
				       pulse->period <= 76940);
			अवरोध;
		पूर्ण

		अगर (pulse->engine > 3)
			अवरोध;

		अगर (pulse->engine == 3) अणु
			ret = mt76x02_dfs_check_chirp(dev);
			अवरोध;
		पूर्ण

		/* check लघु pulse*/
		अगर (pulse->w1 < 120)
			ret = (pulse->period >= 2900 &&
			       (pulse->period <= 4700 ||
				pulse->period >= 6400) &&
			       (pulse->period <= 6800 ||
				pulse->period >= 27560) &&
			       (pulse->period <= 27960 ||
				pulse->period >= 28360) &&
			       (pulse->period <= 28700 ||
				pulse->period >= 79900) &&
			       pulse->period <= 80100);
		अन्यथा अगर (pulse->w1 < 130) /* 120 - 130 */
			ret = (pulse->period >= 2900 &&
			       (pulse->period <= 10100 ||
				pulse->period >= 27560) &&
			       (pulse->period <= 27960 ||
				pulse->period >= 28360) &&
			       (pulse->period <= 28700 ||
				pulse->period >= 79900) &&
			       pulse->period <= 80100);
		अन्यथा
			ret = (pulse->period >= 3900 &&
			       pulse->period <= 10100);
		अवरोध;
	हाल NL80211_DFS_UNSET:
	शेष:
		वापस false;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool mt76x02_dfs_fetch_event(काष्ठा mt76x02_dev *dev,
				    काष्ठा mt76x02_dfs_event *event)
अणु
	u32 data;

	/* 1st: DFS_R37[31]: 0 (engine 0) - 1 (engine 2)
	 * 2nd: DFS_R37[21:0]: pulse समय
	 * 3rd: DFS_R37[11:0]: pulse width
	 * 3rd: DFS_R37[25:16]: phase
	 * 4th: DFS_R37[12:0]: current pwr
	 * 4th: DFS_R37[21:16]: pwr stable counter
	 *
	 * 1st: DFS_R37[31:0] set to 0xffffffff means no event detected
	 */
	data = mt76_rr(dev, MT_BBP(DFS, 37));
	अगर (!MT_DFS_CHECK_EVENT(data))
		वापस false;

	event->engine = MT_DFS_EVENT_ENGINE(data);
	data = mt76_rr(dev, MT_BBP(DFS, 37));
	event->ts = MT_DFS_EVENT_TIMESTAMP(data);
	data = mt76_rr(dev, MT_BBP(DFS, 37));
	event->width = MT_DFS_EVENT_WIDTH(data);

	वापस true;
पूर्ण

अटल bool mt76x02_dfs_check_event(काष्ठा mt76x02_dev *dev,
				    काष्ठा mt76x02_dfs_event *event)
अणु
	अगर (event->engine == 2) अणु
		काष्ठा mt76x02_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;
		काष्ठा mt76x02_dfs_event_rb *event_buff = &dfs_pd->event_rb[1];
		u16 last_event_idx;
		u32 delta_ts;

		last_event_idx = mt76_decr(event_buff->t_rb,
					   MT_DFS_EVENT_BUFLEN);
		delta_ts = event->ts - event_buff->data[last_event_idx].ts;
		अगर (delta_ts < MT_DFS_EVENT_TIME_MARGIN &&
		    event_buff->data[last_event_idx].width >= 200)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम mt76x02_dfs_queue_event(काष्ठा mt76x02_dev *dev,
				    काष्ठा mt76x02_dfs_event *event)
अणु
	काष्ठा mt76x02_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;
	काष्ठा mt76x02_dfs_event_rb *event_buff;

	/* add radar event to ring buffer */
	event_buff = event->engine == 2 ? &dfs_pd->event_rb[1]
					: &dfs_pd->event_rb[0];
	event_buff->data[event_buff->t_rb] = *event;
	event_buff->data[event_buff->t_rb].fetch_ts = jअगरfies;

	event_buff->t_rb = mt76_incr(event_buff->t_rb, MT_DFS_EVENT_BUFLEN);
	अगर (event_buff->t_rb == event_buff->h_rb)
		event_buff->h_rb = mt76_incr(event_buff->h_rb,
					     MT_DFS_EVENT_BUFLEN);
पूर्ण

अटल पूर्णांक mt76x02_dfs_create_sequence(काष्ठा mt76x02_dev *dev,
				       काष्ठा mt76x02_dfs_event *event,
				       u16 cur_len)
अणु
	काष्ठा mt76x02_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;
	काष्ठा mt76x02_dfs_sw_detector_params *sw_params;
	u32 width_delta, with_sum;
	काष्ठा mt76x02_dfs_sequence seq, *seq_p;
	काष्ठा mt76x02_dfs_event_rb *event_rb;
	काष्ठा mt76x02_dfs_event *cur_event;
	पूर्णांक i, j, end, pri, factor, cur_pri;

	event_rb = event->engine == 2 ? &dfs_pd->event_rb[1]
				      : &dfs_pd->event_rb[0];

	i = mt76_decr(event_rb->t_rb, MT_DFS_EVENT_BUFLEN);
	end = mt76_decr(event_rb->h_rb, MT_DFS_EVENT_BUFLEN);

	जबतक (i != end) अणु
		cur_event = &event_rb->data[i];
		with_sum = event->width + cur_event->width;

		sw_params = &dfs_pd->sw_dpd_params;
		चयन (dev->mt76.region) अणु
		हाल NL80211_DFS_FCC:
		हाल NL80211_DFS_JP:
			अगर (with_sum < 600)
				width_delta = 8;
			अन्यथा
				width_delta = with_sum >> 3;
			अवरोध;
		हाल NL80211_DFS_ETSI:
			अगर (event->engine == 2)
				width_delta = with_sum >> 6;
			अन्यथा अगर (with_sum < 620)
				width_delta = 24;
			अन्यथा
				width_delta = 8;
			अवरोध;
		हाल NL80211_DFS_UNSET:
		शेष:
			वापस -EINVAL;
		पूर्ण

		pri = event->ts - cur_event->ts;
		अगर (असल(event->width - cur_event->width) > width_delta ||
		    pri < sw_params->min_pri)
			जाओ next;

		अगर (pri > sw_params->max_pri)
			अवरोध;

		seq.pri = event->ts - cur_event->ts;
		seq.first_ts = cur_event->ts;
		seq.last_ts = event->ts;
		seq.engine = event->engine;
		seq.count = 2;

		j = mt76_decr(i, MT_DFS_EVENT_BUFLEN);
		जबतक (j != end) अणु
			cur_event = &event_rb->data[j];
			cur_pri = event->ts - cur_event->ts;
			factor = mt76x02_dfs_get_multiple(cur_pri, seq.pri,
						sw_params->pri_margin);
			अगर (factor > 0) अणु
				seq.first_ts = cur_event->ts;
				seq.count++;
			पूर्ण

			j = mt76_decr(j, MT_DFS_EVENT_BUFLEN);
		पूर्ण
		अगर (seq.count <= cur_len)
			जाओ next;

		seq_p = mt76x02_dfs_seq_pool_get(dev);
		अगर (!seq_p)
			वापस -ENOMEM;

		*seq_p = seq;
		INIT_LIST_HEAD(&seq_p->head);
		list_add(&seq_p->head, &dfs_pd->sequences);
next:
		i = mt76_decr(i, MT_DFS_EVENT_BUFLEN);
	पूर्ण
	वापस 0;
पूर्ण

अटल u16 mt76x02_dfs_add_event_to_sequence(काष्ठा mt76x02_dev *dev,
					     काष्ठा mt76x02_dfs_event *event)
अणु
	काष्ठा mt76x02_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;
	काष्ठा mt76x02_dfs_sw_detector_params *sw_params;
	काष्ठा mt76x02_dfs_sequence *seq, *पंचांगp_seq;
	u16 max_seq_len = 0;
	पूर्णांक factor, pri;

	sw_params = &dfs_pd->sw_dpd_params;
	list_क्रम_each_entry_safe(seq, पंचांगp_seq, &dfs_pd->sequences, head) अणु
		अगर (event->ts > seq->first_ts + MT_DFS_SEQUENCE_WINDOW) अणु
			list_del_init(&seq->head);
			mt76x02_dfs_seq_pool_put(dev, seq);
			जारी;
		पूर्ण

		अगर (event->engine != seq->engine)
			जारी;

		pri = event->ts - seq->last_ts;
		factor = mt76x02_dfs_get_multiple(pri, seq->pri,
						  sw_params->pri_margin);
		अगर (factor > 0) अणु
			seq->last_ts = event->ts;
			seq->count++;
			max_seq_len = max_t(u16, max_seq_len, seq->count);
		पूर्ण
	पूर्ण
	वापस max_seq_len;
पूर्ण

अटल bool mt76x02_dfs_check_detection(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा mt76x02_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;
	काष्ठा mt76x02_dfs_sequence *seq;

	अगर (list_empty(&dfs_pd->sequences))
		वापस false;

	list_क्रम_each_entry(seq, &dfs_pd->sequences, head) अणु
		अगर (seq->count > MT_DFS_SEQUENCE_TH) अणु
			dfs_pd->stats[seq->engine].sw_pattern++;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम mt76x02_dfs_add_events(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा mt76x02_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;
	काष्ठा mt76x02_dfs_event event;
	पूर्णांक i, seq_len;

	/* disable debug mode */
	mt76x02_dfs_set_capture_mode_ctrl(dev, false);
	क्रम (i = 0; i < MT_DFS_EVENT_LOOP; i++) अणु
		अगर (!mt76x02_dfs_fetch_event(dev, &event))
			अवरोध;

		अगर (dfs_pd->last_event_ts > event.ts)
			mt76x02_dfs_detector_reset(dev);
		dfs_pd->last_event_ts = event.ts;

		अगर (!mt76x02_dfs_check_event(dev, &event))
			जारी;

		seq_len = mt76x02_dfs_add_event_to_sequence(dev, &event);
		mt76x02_dfs_create_sequence(dev, &event, seq_len);

		mt76x02_dfs_queue_event(dev, &event);
	पूर्ण
	mt76x02_dfs_set_capture_mode_ctrl(dev, true);
पूर्ण

अटल व्योम mt76x02_dfs_check_event_winकरोw(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा mt76x02_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;
	काष्ठा mt76x02_dfs_event_rb *event_buff;
	काष्ठा mt76x02_dfs_event *event;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dfs_pd->event_rb); i++) अणु
		event_buff = &dfs_pd->event_rb[i];

		जबतक (event_buff->h_rb != event_buff->t_rb) अणु
			event = &event_buff->data[event_buff->h_rb];

			/* sorted list */
			अगर (समय_is_after_jअगरfies(event->fetch_ts +
						  MT_DFS_EVENT_WINDOW))
				अवरोध;
			event_buff->h_rb = mt76_incr(event_buff->h_rb,
						     MT_DFS_EVENT_BUFLEN);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mt76x02_dfs_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा mt76x02_dfs_pattern_detector *dfs_pd = from_tasklet(dfs_pd, t,
								   dfs_tasklet);
	काष्ठा mt76x02_dev *dev = container_of(dfs_pd, typeof(*dev), dfs_pd);
	u32 engine_mask;
	पूर्णांक i;

	अगर (test_bit(MT76_SCANNING, &dev->mphy.state))
		जाओ out;

	अगर (समय_is_beक्रमe_jअगरfies(dfs_pd->last_sw_check +
				   MT_DFS_SW_TIMEOUT)) अणु
		bool radar_detected;

		dfs_pd->last_sw_check = jअगरfies;

		mt76x02_dfs_add_events(dev);
		radar_detected = mt76x02_dfs_check_detection(dev);
		अगर (radar_detected) अणु
			/* sw detector rx radar pattern */
			ieee80211_radar_detected(dev->mt76.hw);
			mt76x02_dfs_detector_reset(dev);

			वापस;
		पूर्ण
		mt76x02_dfs_check_event_winकरोw(dev);
	पूर्ण

	engine_mask = mt76_rr(dev, MT_BBP(DFS, 1));
	अगर (!(engine_mask & 0xf))
		जाओ out;

	क्रम (i = 0; i < MT_DFS_NUM_ENGINES; i++) अणु
		काष्ठा mt76x02_dfs_hw_pulse pulse;

		अगर (!(engine_mask & (1 << i)))
			जारी;

		pulse.engine = i;
		mt76x02_dfs_get_hw_pulse(dev, &pulse);

		अगर (!mt76x02_dfs_check_hw_pulse(dev, &pulse)) अणु
			dfs_pd->stats[i].hw_pulse_discarded++;
			जारी;
		पूर्ण

		/* hw detector rx radar pattern */
		dfs_pd->stats[i].hw_pattern++;
		ieee80211_radar_detected(dev->mt76.hw);
		mt76x02_dfs_detector_reset(dev);

		वापस;
	पूर्ण

	/* reset hw detector */
	mt76_wr(dev, MT_BBP(DFS, 1), 0xf);

out:
	mt76x02_irq_enable(dev, MT_INT_GPTIMER);
पूर्ण

अटल व्योम mt76x02_dfs_init_sw_detector(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा mt76x02_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;

	चयन (dev->mt76.region) अणु
	हाल NL80211_DFS_FCC:
		dfs_pd->sw_dpd_params.max_pri = MT_DFS_FCC_MAX_PRI;
		dfs_pd->sw_dpd_params.min_pri = MT_DFS_FCC_MIN_PRI;
		dfs_pd->sw_dpd_params.pri_margin = MT_DFS_PRI_MARGIN;
		अवरोध;
	हाल NL80211_DFS_ETSI:
		dfs_pd->sw_dpd_params.max_pri = MT_DFS_ETSI_MAX_PRI;
		dfs_pd->sw_dpd_params.min_pri = MT_DFS_ETSI_MIN_PRI;
		dfs_pd->sw_dpd_params.pri_margin = MT_DFS_PRI_MARGIN << 2;
		अवरोध;
	हाल NL80211_DFS_JP:
		dfs_pd->sw_dpd_params.max_pri = MT_DFS_JP_MAX_PRI;
		dfs_pd->sw_dpd_params.min_pri = MT_DFS_JP_MIN_PRI;
		dfs_pd->sw_dpd_params.pri_margin = MT_DFS_PRI_MARGIN;
		अवरोध;
	हाल NL80211_DFS_UNSET:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mt76x02_dfs_set_bbp_params(काष्ठा mt76x02_dev *dev)
अणु
	स्थिर काष्ठा mt76x02_radar_specs *radar_specs;
	u8 i, shअगरt;
	u32 data;

	चयन (dev->mphy.chandef.width) अणु
	हाल NL80211_CHAN_WIDTH_40:
		shअगरt = MT_DFS_NUM_ENGINES;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
		shअगरt = 2 * MT_DFS_NUM_ENGINES;
		अवरोध;
	शेष:
		shअगरt = 0;
		अवरोध;
	पूर्ण

	चयन (dev->mt76.region) अणु
	हाल NL80211_DFS_FCC:
		radar_specs = &fcc_radar_specs[shअगरt];
		अवरोध;
	हाल NL80211_DFS_ETSI:
		radar_specs = &etsi_radar_specs[shअगरt];
		अवरोध;
	हाल NL80211_DFS_JP:
		अगर (dev->mphy.chandef.chan->center_freq >= 5250 &&
		    dev->mphy.chandef.chan->center_freq <= 5350)
			radar_specs = &jp_w53_radar_specs[shअगरt];
		अन्यथा
			radar_specs = &jp_w56_radar_specs[shअगरt];
		अवरोध;
	हाल NL80211_DFS_UNSET:
	शेष:
		वापस;
	पूर्ण

	data = (MT_DFS_VGA_MASK << 16) |
	       (MT_DFS_PWR_GAIN_OFFSET << 12) |
	       (MT_DFS_PWR_DOWN_TIME << 8) |
	       (MT_DFS_SYM_ROUND << 4) |
	       (MT_DFS_DELTA_DELAY & 0xf);
	mt76_wr(dev, MT_BBP(DFS, 2), data);

	data = (MT_DFS_RX_PE_MASK << 16) | MT_DFS_PKT_END_MASK;
	mt76_wr(dev, MT_BBP(DFS, 3), data);

	क्रम (i = 0; i < MT_DFS_NUM_ENGINES; i++) अणु
		/* configure engine */
		mt76_wr(dev, MT_BBP(DFS, 0), i);

		/* detection mode + avg_len */
		data = ((radar_specs[i].avg_len & 0x1ff) << 16) |
		       (radar_specs[i].mode & 0xf);
		mt76_wr(dev, MT_BBP(DFS, 4), data);

		/* dfs energy */
		data = ((radar_specs[i].e_high & 0x0fff) << 16) |
		       (radar_specs[i].e_low & 0x0fff);
		mt76_wr(dev, MT_BBP(DFS, 5), data);

		/* dfs period */
		mt76_wr(dev, MT_BBP(DFS, 7), radar_specs[i].t_low);
		mt76_wr(dev, MT_BBP(DFS, 9), radar_specs[i].t_high);

		/* dfs burst */
		mt76_wr(dev, MT_BBP(DFS, 11), radar_specs[i].b_low);
		mt76_wr(dev, MT_BBP(DFS, 13), radar_specs[i].b_high);

		/* dfs width */
		data = ((radar_specs[i].w_high & 0x0fff) << 16) |
		       (radar_specs[i].w_low & 0x0fff);
		mt76_wr(dev, MT_BBP(DFS, 14), data);

		/* dfs margins */
		data = (radar_specs[i].w_margin << 16) |
		       radar_specs[i].t_margin;
		mt76_wr(dev, MT_BBP(DFS, 15), data);

		/* dfs event expiration */
		mt76_wr(dev, MT_BBP(DFS, 17), radar_specs[i].event_expiration);

		/* dfs pwr adj */
		mt76_wr(dev, MT_BBP(DFS, 30), radar_specs[i].pwr_jmp);
	पूर्ण

	/* reset status */
	mt76_wr(dev, MT_BBP(DFS, 1), 0xf);
	mt76_wr(dev, MT_BBP(DFS, 36), 0x3);

	/* enable detection*/
	mt76_wr(dev, MT_BBP(DFS, 0), MT_DFS_CH_EN << 16);
	mt76_wr(dev, MT_BBP(IBI, 11), 0x0c350001);
पूर्ण

व्योम mt76x02_phy_dfs_adjust_agc(काष्ठा mt76x02_dev *dev)
अणु
	u32 agc_r8, agc_r4, val_r8, val_r4, dfs_r31;

	agc_r8 = mt76_rr(dev, MT_BBP(AGC, 8));
	agc_r4 = mt76_rr(dev, MT_BBP(AGC, 4));

	val_r8 = (agc_r8 & 0x00007e00) >> 9;
	val_r4 = agc_r4 & ~0x1f000000;
	val_r4 += (((val_r8 + 1) >> 1) << 24);
	mt76_wr(dev, MT_BBP(AGC, 4), val_r4);

	dfs_r31 = FIELD_GET(MT_BBP_AGC_LNA_HIGH_GAIN, val_r4);
	dfs_r31 += val_r8;
	dfs_r31 -= (agc_r8 & 0x00000038) >> 3;
	dfs_r31 = (dfs_r31 << 16) | 0x00000307;
	mt76_wr(dev, MT_BBP(DFS, 31), dfs_r31);

	अगर (is_mt76x2(dev)) अणु
		mt76_wr(dev, MT_BBP(DFS, 32), 0x00040071);
	पूर्ण अन्यथा अणु
		/* disable hw detector */
		mt76_wr(dev, MT_BBP(DFS, 0), 0);
		/* enable hw detector */
		mt76_wr(dev, MT_BBP(DFS, 0), MT_DFS_CH_EN << 16);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_phy_dfs_adjust_agc);

व्योम mt76x02_dfs_init_params(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा cfg80211_chan_def *chandef = &dev->mphy.chandef;

	अगर ((chandef->chan->flags & IEEE80211_CHAN_RADAR) &&
	    dev->mt76.region != NL80211_DFS_UNSET) अणु
		mt76x02_dfs_init_sw_detector(dev);
		mt76x02_dfs_set_bbp_params(dev);
		/* enable debug mode */
		mt76x02_dfs_set_capture_mode_ctrl(dev, true);

		mt76x02_irq_enable(dev, MT_INT_GPTIMER);
		mt76_rmw_field(dev, MT_INT_TIMER_EN,
			       MT_INT_TIMER_EN_GP_TIMER_EN, 1);
	पूर्ण अन्यथा अणु
		/* disable hw detector */
		mt76_wr(dev, MT_BBP(DFS, 0), 0);
		/* clear detector status */
		mt76_wr(dev, MT_BBP(DFS, 1), 0xf);
		अगर (mt76_chip(&dev->mt76) == 0x7610 ||
		    mt76_chip(&dev->mt76) == 0x7630)
			mt76_wr(dev, MT_BBP(IBI, 11), 0xfde8081);
		अन्यथा
			mt76_wr(dev, MT_BBP(IBI, 11), 0);

		mt76x02_irq_disable(dev, MT_INT_GPTIMER);
		mt76_rmw_field(dev, MT_INT_TIMER_EN,
			       MT_INT_TIMER_EN_GP_TIMER_EN, 0);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_dfs_init_params);

व्योम mt76x02_dfs_init_detector(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा mt76x02_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;

	INIT_LIST_HEAD(&dfs_pd->sequences);
	INIT_LIST_HEAD(&dfs_pd->seq_pool);
	dev->mt76.region = NL80211_DFS_UNSET;
	dfs_pd->last_sw_check = jअगरfies;
	tasklet_setup(&dfs_pd->dfs_tasklet, mt76x02_dfs_tasklet);
पूर्ण

अटल व्योम
mt76x02_dfs_set_करोमुख्य(काष्ठा mt76x02_dev *dev,
		       क्रमागत nl80211_dfs_regions region)
अणु
	काष्ठा mt76x02_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;

	mutex_lock(&dev->mt76.mutex);
	अगर (dev->mt76.region != region) अणु
		tasklet_disable(&dfs_pd->dfs_tasklet);

		dev->ed_monitor = dev->ed_monitor_enabled &&
				  region == NL80211_DFS_ETSI;
		mt76x02_edcca_init(dev);

		dev->mt76.region = region;
		mt76x02_dfs_init_params(dev);
		tasklet_enable(&dfs_pd->dfs_tasklet);
	पूर्ण
	mutex_unlock(&dev->mt76.mutex);
पूर्ण

व्योम mt76x02_regd_notअगरier(काष्ठा wiphy *wiphy,
			   काष्ठा regulatory_request *request)
अणु
	काष्ठा ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	काष्ठा mt76x02_dev *dev = hw->priv;

	mt76x02_dfs_set_करोमुख्य(dev, request->dfs_region);
पूर्ण
