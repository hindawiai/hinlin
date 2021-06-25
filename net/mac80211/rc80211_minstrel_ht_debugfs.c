<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 Felix Fietkau <nbd@खोलोwrt.org>
 */
#समावेश <linux/netdevice.h>
#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/ieee80211.h>
#समावेश <linux/export.h>
#समावेश <net/mac80211.h>
#समावेश "rc80211_minstrel_ht.h"

काष्ठा minstrel_debugfs_info अणु
	माप_प्रकार len;
	अक्षर buf[];
पूर्ण;

अटल sमाप_प्रकार
minstrel_stats_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा minstrel_debugfs_info *ms;

	ms = file->निजी_data;
	वापस simple_पढ़ो_from_buffer(buf, len, ppos, ms->buf, ms->len);
पूर्ण

अटल पूर्णांक
minstrel_stats_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	kमुक्त(file->निजी_data);
	वापस 0;
पूर्ण

अटल bool
minstrel_ht_is_sample_rate(काष्ठा minstrel_ht_sta *mi, पूर्णांक idx)
अणु
	पूर्णांक type, i;

	क्रम (type = 0; type < ARRAY_SIZE(mi->sample); type++)
		क्रम (i = 0; i < MINSTREL_SAMPLE_RATES; i++)
			अगर (mi->sample[type].cur_sample_rates[i] == idx)
				वापस true;
	वापस false;
पूर्ण

अटल अक्षर *
minstrel_ht_stats_dump(काष्ठा minstrel_ht_sta *mi, पूर्णांक i, अक्षर *p)
अणु
	स्थिर काष्ठा mcs_group *mg;
	अचिन्हित पूर्णांक j, tp_max, tp_avg, eprob, tx_समय;
	अक्षर hपंचांगode = '2';
	अक्षर gimode = 'L';
	u32 gflags;

	अगर (!mi->supported[i])
		वापस p;

	mg = &minstrel_mcs_groups[i];
	gflags = mg->flags;

	अगर (gflags & IEEE80211_TX_RC_40_MHZ_WIDTH)
		hपंचांगode = '4';
	अन्यथा अगर (gflags & IEEE80211_TX_RC_80_MHZ_WIDTH)
		hपंचांगode = '8';
	अगर (gflags & IEEE80211_TX_RC_SHORT_GI)
		gimode = 'S';

	क्रम (j = 0; j < MCS_GROUP_RATES; j++) अणु
		काष्ठा minstrel_rate_stats *mrs = &mi->groups[i].rates[j];
		पूर्णांक idx = MI_RATE(i, j);
		अचिन्हित पूर्णांक duration;

		अगर (!(mi->supported[i] & BIT(j)))
			जारी;

		अगर (gflags & IEEE80211_TX_RC_MCS) अणु
			p += प्र_लिखो(p, "HT%c0  ", hपंचांगode);
			p += प्र_लिखो(p, "%cGI  ", gimode);
			p += प्र_लिखो(p, "%d  ", mg->streams);
		पूर्ण अन्यथा अगर (gflags & IEEE80211_TX_RC_VHT_MCS) अणु
			p += प्र_लिखो(p, "VHT%c0 ", hपंचांगode);
			p += प्र_लिखो(p, "%cGI ", gimode);
			p += प्र_लिखो(p, "%d  ", mg->streams);
		पूर्ण अन्यथा अगर (i == MINSTREL_OFDM_GROUP) अणु
			p += प्र_लिखो(p, "OFDM       ");
			p += प्र_लिखो(p, "1 ");
		पूर्ण अन्यथा अणु
			p += प्र_लिखो(p, "CCK    ");
			p += प्र_लिखो(p, "%cP  ", j < 4 ? 'L' : 'S');
			p += प्र_लिखो(p, "1 ");
		पूर्ण

		*(p++) = (idx == mi->max_tp_rate[0]) ? 'A' : ' ';
		*(p++) = (idx == mi->max_tp_rate[1]) ? 'B' : ' ';
		*(p++) = (idx == mi->max_tp_rate[2]) ? 'C' : ' ';
		*(p++) = (idx == mi->max_tp_rate[3]) ? 'D' : ' ';
		*(p++) = (idx == mi->max_prob_rate) ? 'P' : ' ';
		*(p++) = minstrel_ht_is_sample_rate(mi, idx) ? 'S' : ' ';

		अगर (gflags & IEEE80211_TX_RC_MCS) अणु
			p += प्र_लिखो(p, "  MCS%-2u", (mg->streams - 1) * 8 + j);
		पूर्ण अन्यथा अगर (gflags & IEEE80211_TX_RC_VHT_MCS) अणु
			p += प्र_लिखो(p, "  MCS%-1u/%1u", j, mg->streams);
		पूर्ण अन्यथा अणु
			पूर्णांक r;

			अगर (i == MINSTREL_OFDM_GROUP)
				r = minstrel_ofdm_bitrates[j % 8];
			अन्यथा
				r = minstrel_cck_bitrates[j % 4];

			p += प्र_लिखो(p, "   %2u.%1uM", r / 10, r % 10);
		पूर्ण

		p += प्र_लिखो(p, "  %3u  ", idx);

		/* tx_समय[rate(i)] in usec */
		duration = mg->duration[j];
		duration <<= mg->shअगरt;
		tx_समय = DIV_ROUND_CLOSEST(duration, 1000);
		p += प्र_लिखो(p, "%6u  ", tx_समय);

		tp_max = minstrel_ht_get_tp_avg(mi, i, j, MINSTREL_FRAC(100, 100));
		tp_avg = minstrel_ht_get_tp_avg(mi, i, j, mrs->prob_avg);
		eprob = MINSTREL_TRUNC(mrs->prob_avg * 1000);

		p += प्र_लिखो(p, "%4u.%1u    %4u.%1u     %3u.%1u"
				"     %3u   %3u %-3u   "
				"%9llu   %-9llu\n",
				tp_max / 10, tp_max % 10,
				tp_avg / 10, tp_avg % 10,
				eprob / 10, eprob % 10,
				mrs->retry_count,
				mrs->last_success,
				mrs->last_attempts,
				(अचिन्हित दीर्घ दीर्घ)mrs->succ_hist,
				(अचिन्हित दीर्घ दीर्घ)mrs->att_hist);
	पूर्ण

	वापस p;
पूर्ण

अटल पूर्णांक
minstrel_ht_stats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा minstrel_ht_sta *mi = inode->i_निजी;
	काष्ठा minstrel_debugfs_info *ms;
	अचिन्हित पूर्णांक i;
	अक्षर *p;

	ms = kदो_स्मृति(32768, GFP_KERNEL);
	अगर (!ms)
		वापस -ENOMEM;

	file->निजी_data = ms;
	p = ms->buf;

	p += प्र_लिखो(p, "\n");
	p += प्र_लिखो(p,
		     "              best    ____________rate__________    ____statistics___    _____last____    ______sum-of________\n");
	p += प्र_लिखो(p,
		     "mode guard #  rate   [name   idx airtime  max_tp]  [avg(tp) avg(prob)]  [retry|suc|att]  [#success | #attempts]\n");

	p = minstrel_ht_stats_dump(mi, MINSTREL_CCK_GROUP, p);
	क्रम (i = 0; i < MINSTREL_CCK_GROUP; i++)
		p = minstrel_ht_stats_dump(mi, i, p);
	क्रम (i++; i < ARRAY_SIZE(mi->groups); i++)
		p = minstrel_ht_stats_dump(mi, i, p);

	p += प्र_लिखो(p, "\nTotal packet count::    ideal %d      "
			"lookaround %d\n",
			max(0, (पूर्णांक) mi->total_packets - (पूर्णांक) mi->sample_packets),
			mi->sample_packets);
	अगर (mi->avg_ampdu_len)
		p += प्र_लिखो(p, "Average # of aggregated frames per A-MPDU: %d.%d\n",
			MINSTREL_TRUNC(mi->avg_ampdu_len),
			MINSTREL_TRUNC(mi->avg_ampdu_len * 10) % 10);
	ms->len = p - ms->buf;
	WARN_ON(ms->len + माप(*ms) > 32768);

	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल स्थिर काष्ठा file_operations minstrel_ht_stat_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = minstrel_ht_stats_खोलो,
	.पढ़ो = minstrel_stats_पढ़ो,
	.release = minstrel_stats_release,
	.llseek = no_llseek,
पूर्ण;

अटल अक्षर *
minstrel_ht_stats_csv_dump(काष्ठा minstrel_ht_sta *mi, पूर्णांक i, अक्षर *p)
अणु
	स्थिर काष्ठा mcs_group *mg;
	अचिन्हित पूर्णांक j, tp_max, tp_avg, eprob, tx_समय;
	अक्षर hपंचांगode = '2';
	अक्षर gimode = 'L';
	u32 gflags;

	अगर (!mi->supported[i])
		वापस p;

	mg = &minstrel_mcs_groups[i];
	gflags = mg->flags;

	अगर (gflags & IEEE80211_TX_RC_40_MHZ_WIDTH)
		hपंचांगode = '4';
	अन्यथा अगर (gflags & IEEE80211_TX_RC_80_MHZ_WIDTH)
		hपंचांगode = '8';
	अगर (gflags & IEEE80211_TX_RC_SHORT_GI)
		gimode = 'S';

	क्रम (j = 0; j < MCS_GROUP_RATES; j++) अणु
		काष्ठा minstrel_rate_stats *mrs = &mi->groups[i].rates[j];
		पूर्णांक idx = MI_RATE(i, j);
		अचिन्हित पूर्णांक duration;

		अगर (!(mi->supported[i] & BIT(j)))
			जारी;

		अगर (gflags & IEEE80211_TX_RC_MCS) अणु
			p += प्र_लिखो(p, "HT%c0,", hपंचांगode);
			p += प्र_लिखो(p, "%cGI,", gimode);
			p += प्र_लिखो(p, "%d,", mg->streams);
		पूर्ण अन्यथा अगर (gflags & IEEE80211_TX_RC_VHT_MCS) अणु
			p += प्र_लिखो(p, "VHT%c0,", hपंचांगode);
			p += प्र_लिखो(p, "%cGI,", gimode);
			p += प्र_लिखो(p, "%d,", mg->streams);
		पूर्ण अन्यथा अगर (i == MINSTREL_OFDM_GROUP) अणु
			p += प्र_लिखो(p, "OFDM,,1,");
		पूर्ण अन्यथा अणु
			p += प्र_लिखो(p, "CCK,");
			p += प्र_लिखो(p, "%cP,", j < 4 ? 'L' : 'S');
			p += प्र_लिखो(p, "1,");
		पूर्ण

		p += प्र_लिखो(p, "%s" ,((idx == mi->max_tp_rate[0]) ? "A" : ""));
		p += प्र_लिखो(p, "%s" ,((idx == mi->max_tp_rate[1]) ? "B" : ""));
		p += प्र_लिखो(p, "%s" ,((idx == mi->max_tp_rate[2]) ? "C" : ""));
		p += प्र_लिखो(p, "%s" ,((idx == mi->max_tp_rate[3]) ? "D" : ""));
		p += प्र_लिखो(p, "%s" ,((idx == mi->max_prob_rate) ? "P" : ""));
		p += प्र_लिखो(p, "%s", (minstrel_ht_is_sample_rate(mi, idx) ? "S" : ""));

		अगर (gflags & IEEE80211_TX_RC_MCS) अणु
			p += प्र_लिखो(p, ",MCS%-2u,", (mg->streams - 1) * 8 + j);
		पूर्ण अन्यथा अगर (gflags & IEEE80211_TX_RC_VHT_MCS) अणु
			p += प्र_लिखो(p, ",MCS%-1u/%1u,", j, mg->streams);
		पूर्ण अन्यथा अणु
			पूर्णांक r;

			अगर (i == MINSTREL_OFDM_GROUP)
				r = minstrel_ofdm_bitrates[j % 8];
			अन्यथा
				r = minstrel_cck_bitrates[j % 4];

			p += प्र_लिखो(p, ",%2u.%1uM,", r / 10, r % 10);
		पूर्ण

		p += प्र_लिखो(p, "%u,", idx);

		duration = mg->duration[j];
		duration <<= mg->shअगरt;
		tx_समय = DIV_ROUND_CLOSEST(duration, 1000);
		p += प्र_लिखो(p, "%u,", tx_समय);

		tp_max = minstrel_ht_get_tp_avg(mi, i, j, MINSTREL_FRAC(100, 100));
		tp_avg = minstrel_ht_get_tp_avg(mi, i, j, mrs->prob_avg);
		eprob = MINSTREL_TRUNC(mrs->prob_avg * 1000);

		p += प्र_लिखो(p, "%u.%u,%u.%u,%u.%u,%u,%u,"
				"%u,%llu,%llu,",
				tp_max / 10, tp_max % 10,
				tp_avg / 10, tp_avg % 10,
				eprob / 10, eprob % 10,
				mrs->retry_count,
				mrs->last_success,
				mrs->last_attempts,
				(अचिन्हित दीर्घ दीर्घ)mrs->succ_hist,
				(अचिन्हित दीर्घ दीर्घ)mrs->att_hist);
		p += प्र_लिखो(p, "%d,%d,%d.%d\n",
				max(0, (पूर्णांक) mi->total_packets -
				(पूर्णांक) mi->sample_packets),
				mi->sample_packets,
				MINSTREL_TRUNC(mi->avg_ampdu_len),
				MINSTREL_TRUNC(mi->avg_ampdu_len * 10) % 10);
	पूर्ण

	वापस p;
पूर्ण

अटल पूर्णांक
minstrel_ht_stats_csv_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा minstrel_ht_sta *mi = inode->i_निजी;
	काष्ठा minstrel_debugfs_info *ms;
	अचिन्हित पूर्णांक i;
	अक्षर *p;

	ms = kदो_स्मृति(32768, GFP_KERNEL);
	अगर (!ms)
		वापस -ENOMEM;

	file->निजी_data = ms;

	p = ms->buf;

	p = minstrel_ht_stats_csv_dump(mi, MINSTREL_CCK_GROUP, p);
	क्रम (i = 0; i < MINSTREL_CCK_GROUP; i++)
		p = minstrel_ht_stats_csv_dump(mi, i, p);
	क्रम (i++; i < ARRAY_SIZE(mi->groups); i++)
		p = minstrel_ht_stats_csv_dump(mi, i, p);

	ms->len = p - ms->buf;
	WARN_ON(ms->len + माप(*ms) > 32768);

	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल स्थिर काष्ठा file_operations minstrel_ht_stat_csv_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = minstrel_ht_stats_csv_खोलो,
	.पढ़ो = minstrel_stats_पढ़ो,
	.release = minstrel_stats_release,
	.llseek = no_llseek,
पूर्ण;

व्योम
minstrel_ht_add_sta_debugfs(व्योम *priv, व्योम *priv_sta, काष्ठा dentry *dir)
अणु
	debugfs_create_file("rc_stats", 0444, dir, priv_sta,
			    &minstrel_ht_stat_fops);
	debugfs_create_file("rc_stats_csv", 0444, dir, priv_sta,
			    &minstrel_ht_stat_csv_fops);
पूर्ण
