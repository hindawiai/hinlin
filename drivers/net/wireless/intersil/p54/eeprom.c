<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * EEPROM parser code क्रम mac80211 Prism54 drivers
 *
 * Copyright (c) 2006, Michael Wu <flamingice@sourmilk.net>
 * Copyright (c) 2007-2009, Christian Lamparter <chunkeey@web.de>
 * Copyright 2008, Johannes Berg <johannes@sipsolutions.net>
 *
 * Based on:
 * - the islsm (sofपंचांगac prism54) driver, which is:
 *   Copyright 2004-2006 Jean-Baptiste Note <jbnote@gmail.com>, et al.
 * - stlc45xx driver
 *   Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
 */

#समावेश <linux/firmware.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/sort.h>
#समावेश <linux/slab.h>

#समावेश <net/mac80211.h>
#समावेश <linux/crc-ccitt.h>
#समावेश <linux/export.h>

#समावेश "p54.h"
#समावेश "eeprom.h"
#समावेश "lmac.h"

अटल काष्ठा ieee80211_rate p54_bgrates[] = अणु
	अणु .bitrate = 10, .hw_value = 0, पूर्ण,
	अणु .bitrate = 20, .hw_value = 1, .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 55, .hw_value = 2, .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 110, .hw_value = 3, .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 60, .hw_value = 4, पूर्ण,
	अणु .bitrate = 90, .hw_value = 5, पूर्ण,
	अणु .bitrate = 120, .hw_value = 6, पूर्ण,
	अणु .bitrate = 180, .hw_value = 7, पूर्ण,
	अणु .bitrate = 240, .hw_value = 8, पूर्ण,
	अणु .bitrate = 360, .hw_value = 9, पूर्ण,
	अणु .bitrate = 480, .hw_value = 10, पूर्ण,
	अणु .bitrate = 540, .hw_value = 11, पूर्ण,
पूर्ण;

अटल काष्ठा ieee80211_rate p54_arates[] = अणु
	अणु .bitrate = 60, .hw_value = 4, पूर्ण,
	अणु .bitrate = 90, .hw_value = 5, पूर्ण,
	अणु .bitrate = 120, .hw_value = 6, पूर्ण,
	अणु .bitrate = 180, .hw_value = 7, पूर्ण,
	अणु .bitrate = 240, .hw_value = 8, पूर्ण,
	अणु .bitrate = 360, .hw_value = 9, पूर्ण,
	अणु .bitrate = 480, .hw_value = 10, पूर्ण,
	अणु .bitrate = 540, .hw_value = 11, पूर्ण,
पूर्ण;

अटल काष्ठा p54_rssi_db_entry p54_rssi_शेष = अणु
	/*
	 * The शेषs are taken from usb-logs of the
	 * venकरोr driver. So, they should be safe to
	 * use in हाल we can't get a match from the
	 * rssi <-> dBm conversion database.
	 */
	.mul = 130,
	.add = -398,
पूर्ण;

#घोषणा CHAN_HAS_CAL		BIT(0)
#घोषणा CHAN_HAS_LIMIT		BIT(1)
#घोषणा CHAN_HAS_CURVE		BIT(2)
#घोषणा CHAN_HAS_ALL		(CHAN_HAS_CAL | CHAN_HAS_LIMIT | CHAN_HAS_CURVE)

काष्ठा p54_channel_entry अणु
	u16 freq;
	u16 data;
	पूर्णांक index;
	पूर्णांक max_घातer;
	क्रमागत nl80211_band band;
पूर्ण;

काष्ठा p54_channel_list अणु
	काष्ठा p54_channel_entry *channels;
	माप_प्रकार entries;
	माप_प्रकार max_entries;
	माप_प्रकार band_channel_num[NUM_NL80211_BANDS];
पूर्ण;

अटल पूर्णांक p54_get_band_from_freq(u16 freq)
अणु
	/* FIXME: sync these values with the 802.11 spec */

	अगर ((freq >= 2412) && (freq <= 2484))
		वापस NL80211_BAND_2GHZ;

	अगर ((freq >= 4920) && (freq <= 5825))
		वापस NL80211_BAND_5GHZ;

	वापस -1;
पूर्ण

अटल पूर्णांक same_band(u16 freq, u16 freq2)
अणु
	वापस p54_get_band_from_freq(freq) == p54_get_band_from_freq(freq2);
पूर्ण

अटल पूर्णांक p54_compare_channels(स्थिर व्योम *_a,
				स्थिर व्योम *_b)
अणु
	स्थिर काष्ठा p54_channel_entry *a = _a;
	स्थिर काष्ठा p54_channel_entry *b = _b;

	वापस a->freq - b->freq;
पूर्ण

अटल पूर्णांक p54_compare_rssichan(स्थिर व्योम *_a,
				स्थिर व्योम *_b)
अणु
	स्थिर काष्ठा p54_rssi_db_entry *a = _a;
	स्थिर काष्ठा p54_rssi_db_entry *b = _b;

	वापस a->freq - b->freq;
पूर्ण

अटल पूर्णांक p54_fill_band_bitrates(काष्ठा ieee80211_hw *dev,
				  काष्ठा ieee80211_supported_band *band_entry,
				  क्रमागत nl80211_band band)
अणु
	/* TODO: generate rate array dynamically */

	चयन (band) अणु
	हाल NL80211_BAND_2GHZ:
		band_entry->bitrates = p54_bgrates;
		band_entry->n_bitrates = ARRAY_SIZE(p54_bgrates);
		अवरोध;
	हाल NL80211_BAND_5GHZ:
		band_entry->bitrates = p54_arates;
		band_entry->n_bitrates = ARRAY_SIZE(p54_arates);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक p54_generate_band(काष्ठा ieee80211_hw *dev,
			     काष्ठा p54_channel_list *list,
			     अचिन्हित पूर्णांक *chan_num,
			     क्रमागत nl80211_band band)
अणु
	काष्ठा p54_common *priv = dev->priv;
	काष्ठा ieee80211_supported_band *पंचांगp, *old;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक ret = -ENOMEM;

	अगर ((!list->entries) || (!list->band_channel_num[band]))
		वापस -EINVAL;

	पंचांगp = kzalloc(माप(*पंचांगp), GFP_KERNEL);
	अगर (!पंचांगp)
		जाओ err_out;

	पंचांगp->channels = kसुस्मृति(list->band_channel_num[band],
				माप(काष्ठा ieee80211_channel),
				GFP_KERNEL);
	अगर (!पंचांगp->channels)
		जाओ err_out;

	ret = p54_fill_band_bitrates(dev, पंचांगp, band);
	अगर (ret)
		जाओ err_out;

	क्रम (i = 0, j = 0; (j < list->band_channel_num[band]) &&
			   (i < list->entries); i++) अणु
		काष्ठा p54_channel_entry *chan = &list->channels[i];
		काष्ठा ieee80211_channel *dest = &पंचांगp->channels[j];

		अगर (chan->band != band)
			जारी;

		अगर (chan->data != CHAN_HAS_ALL) अणु
			wiphy_err(dev->wiphy, "%s%s%s is/are missing for "
				  "channel:%d [%d MHz].\n",
				  (chan->data & CHAN_HAS_CAL ? "" :
				   " [iqauto calibration data]"),
				  (chan->data & CHAN_HAS_LIMIT ? "" :
				   " [output power limits]"),
				  (chan->data & CHAN_HAS_CURVE ? "" :
				   " [curve data]"),
				  chan->index, chan->freq);
			जारी;
		पूर्ण

		dest->band = chan->band;
		dest->center_freq = chan->freq;
		dest->max_घातer = chan->max_घातer;
		priv->survey[*chan_num].channel = &पंचांगp->channels[j];
		priv->survey[*chan_num].filled = SURVEY_INFO_NOISE_DBM |
			SURVEY_INFO_TIME |
			SURVEY_INFO_TIME_BUSY |
			SURVEY_INFO_TIME_TX;
		dest->hw_value = (*chan_num);
		j++;
		(*chan_num)++;
	पूर्ण

	अगर (j == 0) अणु
		wiphy_err(dev->wiphy, "Disabling totally damaged %d GHz band\n",
			  (band == NL80211_BAND_2GHZ) ? 2 : 5);

		ret = -ENODATA;
		जाओ err_out;
	पूर्ण

	पंचांगp->n_channels = j;
	old = priv->band_table[band];
	priv->band_table[band] = पंचांगp;
	अगर (old) अणु
		kमुक्त(old->channels);
		kमुक्त(old);
	पूर्ण

	वापस 0;

err_out:
	अगर (पंचांगp) अणु
		kमुक्त(पंचांगp->channels);
		kमुक्त(पंचांगp);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा p54_channel_entry *p54_update_channel_param(काष्ठा p54_channel_list *list,
							  u16 freq, u16 data)
अणु
	पूर्णांक i;
	काष्ठा p54_channel_entry *entry = शून्य;

	/*
	 * usually all lists in the eeprom are mostly sorted.
	 * so it's very likely that the entry we are looking क्रम
	 * is right at the end of the list
	 */
	क्रम (i = list->entries; i >= 0; i--) अणु
		अगर (freq == list->channels[i].freq) अणु
			entry = &list->channels[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर ((i < 0) && (list->entries < list->max_entries)) अणु
		/* entry करोes not exist yet. Initialize a new one. */
		पूर्णांक band = p54_get_band_from_freq(freq);

		/*
		 * filter out frequencies which करोn't beदीर्घ पूर्णांकo
		 * any supported band.
		 */
		अगर (band >= 0) अणु
			i = list->entries++;
			list->band_channel_num[band]++;

			entry = &list->channels[i];
			entry->freq = freq;
			entry->band = band;
			entry->index = ieee80211_frequency_to_channel(freq);
			entry->max_घातer = 0;
			entry->data = 0;
		पूर्ण
	पूर्ण

	अगर (entry)
		entry->data |= data;

	वापस entry;
पूर्ण

अटल पूर्णांक p54_get_maxघातer(काष्ठा p54_common *priv, व्योम *data)
अणु
	चयन (priv->rxhw & PDR_SYNTH_FRONTEND_MASK) अणु
	हाल PDR_SYNTH_FRONTEND_LONGBOW: अणु
		काष्ठा pda_channel_output_limit_दीर्घbow *pda = data;
		पूर्णांक j;
		u16 rawघातer = 0;
		pda = data;
		क्रम (j = 0; j < ARRAY_SIZE(pda->poपूर्णांक); j++) अणु
			काष्ठा pda_channel_output_limit_poपूर्णांक_दीर्घbow *poपूर्णांक =
				&pda->poपूर्णांक[j];
			rawघातer = max_t(u16,
				rawघातer, le16_to_cpu(poपूर्णांक->val_qpsk));
			rawघातer = max_t(u16,
				rawघातer, le16_to_cpu(poपूर्णांक->val_bpsk));
			rawघातer = max_t(u16,
				rawघातer, le16_to_cpu(poपूर्णांक->val_16qam));
			rawघातer = max_t(u16,
				rawघातer, le16_to_cpu(poपूर्णांक->val_64qam));
		पूर्ण
		/* दीर्घbow seems to use 1/16 dBm units */
		वापस rawघातer / 16;
		पूर्ण

	हाल PDR_SYNTH_FRONTEND_DUETTE3:
	हाल PDR_SYNTH_FRONTEND_DUETTE2:
	हाल PDR_SYNTH_FRONTEND_FRISBEE:
	हाल PDR_SYNTH_FRONTEND_XBOW: अणु
		काष्ठा pda_channel_output_limit *pda = data;
		u8 rawघातer = 0;
		rawघातer = max(rawघातer, pda->val_qpsk);
		rawघातer = max(rawघातer, pda->val_bpsk);
		rawघातer = max(rawघातer, pda->val_16qam);
		rawघातer = max(rawघातer, pda->val_64qam);
		/* raw values are in 1/4 dBm units */
		वापस rawघातer / 4;
		पूर्ण

	शेष:
		वापस 20;
	पूर्ण
पूर्ण

अटल पूर्णांक p54_generate_channel_lists(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा p54_common *priv = dev->priv;
	काष्ठा p54_channel_list *list;
	अचिन्हित पूर्णांक i, j, k, max_channel_num;
	पूर्णांक ret = 0;
	u16 freq;

	अगर ((priv->iq_स्वतःcal_len != priv->curve_data->entries) ||
	    (priv->iq_स्वतःcal_len != priv->output_limit->entries))
		wiphy_err(dev->wiphy,
			  "Unsupported or damaged EEPROM detected. "
			  "You may not be able to use all channels.\n");

	max_channel_num = max_t(अचिन्हित पूर्णांक, priv->output_limit->entries,
				priv->iq_स्वतःcal_len);
	max_channel_num = max_t(अचिन्हित पूर्णांक, max_channel_num,
				priv->curve_data->entries);

	list = kzalloc(माप(*list), GFP_KERNEL);
	अगर (!list) अणु
		ret = -ENOMEM;
		जाओ मुक्त;
	पूर्ण
	priv->chan_num = max_channel_num;
	priv->survey = kसुस्मृति(max_channel_num, माप(काष्ठा survey_info),
			       GFP_KERNEL);
	अगर (!priv->survey) अणु
		ret = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	list->max_entries = max_channel_num;
	list->channels = kसुस्मृति(max_channel_num,
				 माप(काष्ठा p54_channel_entry),
				 GFP_KERNEL);
	अगर (!list->channels) अणु
		ret = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	क्रम (i = 0; i < max_channel_num; i++) अणु
		अगर (i < priv->iq_स्वतःcal_len) अणु
			freq = le16_to_cpu(priv->iq_स्वतःcal[i].freq);
			p54_update_channel_param(list, freq, CHAN_HAS_CAL);
		पूर्ण

		अगर (i < priv->output_limit->entries) अणु
			काष्ठा p54_channel_entry *पंचांगp;

			व्योम *data = (व्योम *) ((अचिन्हित दीर्घ) i *
				priv->output_limit->entry_size +
				priv->output_limit->offset +
				priv->output_limit->data);

			freq = le16_to_cpup((__le16 *) data);
			पंचांगp = p54_update_channel_param(list, freq,
						       CHAN_HAS_LIMIT);
			अगर (पंचांगp) अणु
				पंचांगp->max_घातer = p54_get_maxघातer(priv, data);
			पूर्ण
		पूर्ण

		अगर (i < priv->curve_data->entries) अणु
			freq = le16_to_cpup((__le16 *) (i *
					    priv->curve_data->entry_size +
					    priv->curve_data->offset +
					    priv->curve_data->data));

			p54_update_channel_param(list, freq, CHAN_HAS_CURVE);
		पूर्ण
	पूर्ण

	/* sort the channel list by frequency */
	sort(list->channels, list->entries, माप(काष्ठा p54_channel_entry),
	     p54_compare_channels, शून्य);

	k = 0;
	क्रम (i = 0, j = 0; i < NUM_NL80211_BANDS; i++) अणु
		अगर (p54_generate_band(dev, list, &k, i) == 0)
			j++;
	पूर्ण
	अगर (j == 0) अणु
		/* no useable band available. */
		ret = -EINVAL;
	पूर्ण

मुक्त:
	अगर (list) अणु
		kमुक्त(list->channels);
		kमुक्त(list);
	पूर्ण
	अगर (ret) अणु
		kमुक्त(priv->survey);
		priv->survey = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक p54_convert_rev0(काष्ठा ieee80211_hw *dev,
			    काष्ठा pda_pa_curve_data *curve_data)
अणु
	काष्ठा p54_common *priv = dev->priv;
	काष्ठा p54_pa_curve_data_sample *dst;
	काष्ठा pda_pa_curve_data_sample_rev0 *src;
	माप_प्रकार cd_len = माप(*curve_data) +
		(curve_data->poपूर्णांकs_per_channel*माप(*dst) + 2) *
		 curve_data->channels;
	अचिन्हित पूर्णांक i, j;
	व्योम *source, *target;

	priv->curve_data = kदो_स्मृति(माप(*priv->curve_data) + cd_len,
				   GFP_KERNEL);
	अगर (!priv->curve_data)
		वापस -ENOMEM;

	priv->curve_data->entries = curve_data->channels;
	priv->curve_data->entry_size = माप(__le16) +
		माप(*dst) * curve_data->poपूर्णांकs_per_channel;
	priv->curve_data->offset = दुरत्व(काष्ठा pda_pa_curve_data, data);
	priv->curve_data->len = cd_len;
	स_नकल(priv->curve_data->data, curve_data, माप(*curve_data));
	source = curve_data->data;
	target = ((काष्ठा pda_pa_curve_data *) priv->curve_data->data)->data;
	क्रम (i = 0; i < curve_data->channels; i++) अणु
		__le16 *freq = source;
		source += माप(__le16);
		*((__le16 *)target) = *freq;
		target += माप(__le16);
		क्रम (j = 0; j < curve_data->poपूर्णांकs_per_channel; j++) अणु
			dst = target;
			src = source;

			dst->rf_घातer = src->rf_घातer;
			dst->pa_detector = src->pa_detector;
			dst->data_64qam = src->pcv;
			/* "invent" the poपूर्णांकs क्रम the other modulations */
#घोषणा SUB(x, y) (u8)(((x) - (y)) > (x) ? 0 : (x) - (y))
			dst->data_16qam = SUB(src->pcv, 12);
			dst->data_qpsk = SUB(dst->data_16qam, 12);
			dst->data_bpsk = SUB(dst->data_qpsk, 12);
			dst->data_barker = SUB(dst->data_bpsk, 14);
#अघोषित SUB
			target += माप(*dst);
			source += माप(*src);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक p54_convert_rev1(काष्ठा ieee80211_hw *dev,
			    काष्ठा pda_pa_curve_data *curve_data)
अणु
	काष्ठा p54_common *priv = dev->priv;
	काष्ठा p54_pa_curve_data_sample *dst;
	काष्ठा pda_pa_curve_data_sample_rev1 *src;
	माप_प्रकार cd_len = माप(*curve_data) +
		(curve_data->poपूर्णांकs_per_channel*माप(*dst) + 2) *
		 curve_data->channels;
	अचिन्हित पूर्णांक i, j;
	व्योम *source, *target;

	priv->curve_data = kzalloc(cd_len + माप(*priv->curve_data),
				   GFP_KERNEL);
	अगर (!priv->curve_data)
		वापस -ENOMEM;

	priv->curve_data->entries = curve_data->channels;
	priv->curve_data->entry_size = माप(__le16) +
		माप(*dst) * curve_data->poपूर्णांकs_per_channel;
	priv->curve_data->offset = दुरत्व(काष्ठा pda_pa_curve_data, data);
	priv->curve_data->len = cd_len;
	स_नकल(priv->curve_data->data, curve_data, माप(*curve_data));
	source = curve_data->data;
	target = ((काष्ठा pda_pa_curve_data *) priv->curve_data->data)->data;
	क्रम (i = 0; i < curve_data->channels; i++) अणु
		__le16 *freq = source;
		source += माप(__le16);
		*((__le16 *)target) = *freq;
		target += माप(__le16);
		क्रम (j = 0; j < curve_data->poपूर्णांकs_per_channel; j++) अणु
			स_नकल(target, source, माप(*src));

			target += माप(*dst);
			source += माप(*src);
		पूर्ण
		source++;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *p54_rf_chips[] = अणु "INVALID-0", "Duette3", "Duette2",
	"Frisbee", "Xbow", "Longbow", "INVALID-6", "INVALID-7" पूर्ण;

अटल पूर्णांक p54_parse_rssical(काष्ठा ieee80211_hw *dev,
			     u8 *data, पूर्णांक len, u16 type)
अणु
	काष्ठा p54_common *priv = dev->priv;
	काष्ठा p54_rssi_db_entry *entry;
	माप_प्रकार db_len, entries;
	पूर्णांक offset = 0, i;

	अगर (type != PDR_RSSI_LINEAR_APPROXIMATION_EXTENDED) अणु
		entries = (type == PDR_RSSI_LINEAR_APPROXIMATION) ? 1 : 2;
		अगर (len != माप(काष्ठा pda_rssi_cal_entry) * entries) अणु
			wiphy_err(dev->wiphy, "rssical size mismatch.\n");
			जाओ err_data;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Some devices (Dell 1450 USB, Xbow 5GHz card, etc...)
		 * have an empty two byte header.
		 */
		अगर (*((__le16 *)&data[offset]) == cpu_to_le16(0))
			offset += 2;

		entries = (len - offset) /
			माप(काष्ठा pda_rssi_cal_ext_entry);

		अगर (len < offset ||
		    (len - offset) % माप(काष्ठा pda_rssi_cal_ext_entry) ||
		    entries == 0) अणु
			wiphy_err(dev->wiphy, "invalid rssi database.\n");
			जाओ err_data;
		पूर्ण
	पूर्ण

	db_len = माप(*entry) * entries;
	priv->rssi_db = kzalloc(db_len + माप(*priv->rssi_db), GFP_KERNEL);
	अगर (!priv->rssi_db)
		वापस -ENOMEM;

	priv->rssi_db->offset = 0;
	priv->rssi_db->entries = entries;
	priv->rssi_db->entry_size = माप(*entry);
	priv->rssi_db->len = db_len;

	entry = (व्योम *)((अचिन्हित दीर्घ)priv->rssi_db->data + priv->rssi_db->offset);
	अगर (type == PDR_RSSI_LINEAR_APPROXIMATION_EXTENDED) अणु
		काष्ठा pda_rssi_cal_ext_entry *cal = (व्योम *) &data[offset];

		क्रम (i = 0; i < entries; i++) अणु
			entry[i].freq = le16_to_cpu(cal[i].freq);
			entry[i].mul = (s16) le16_to_cpu(cal[i].mul);
			entry[i].add = (s16) le16_to_cpu(cal[i].add);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा pda_rssi_cal_entry *cal = (व्योम *) &data[offset];

		क्रम (i = 0; i < entries; i++) अणु
			u16 freq = 0;
			चयन (i) अणु
			हाल NL80211_BAND_2GHZ:
				freq = 2437;
				अवरोध;
			हाल NL80211_BAND_5GHZ:
				freq = 5240;
				अवरोध;
			पूर्ण

			entry[i].freq = freq;
			entry[i].mul = (s16) le16_to_cpu(cal[i].mul);
			entry[i].add = (s16) le16_to_cpu(cal[i].add);
		पूर्ण
	पूर्ण

	/* sort the list by channel frequency */
	sort(entry, entries, माप(*entry), p54_compare_rssichan, शून्य);
	वापस 0;

err_data:
	wiphy_err(dev->wiphy,
		  "rssi calibration data packing type:(%x) len:%d.\n",
		  type, len);

	prपूर्णांक_hex_dump_bytes("rssical:", DUMP_PREFIX_NONE, data, len);

	wiphy_err(dev->wiphy, "please report this issue.\n");
	वापस -EINVAL;
पूर्ण

काष्ठा p54_rssi_db_entry *p54_rssi_find(काष्ठा p54_common *priv, स्थिर u16 freq)
अणु
	काष्ठा p54_rssi_db_entry *entry;
	पूर्णांक i, found = -1;

	अगर (!priv->rssi_db)
		वापस &p54_rssi_शेष;

	entry = (व्योम *)(priv->rssi_db->data + priv->rssi_db->offset);
	क्रम (i = 0; i < priv->rssi_db->entries; i++) अणु
		अगर (!same_band(freq, entry[i].freq))
			जारी;

		अगर (found == -1) अणु
			found = i;
			जारी;
		पूर्ण

		/* nearest match */
		अगर (असल(freq - entry[i].freq) <
		    असल(freq - entry[found].freq)) अणु
			found = i;
			जारी;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	वापस found < 0 ? &p54_rssi_शेष : &entry[found];
पूर्ण

अटल व्योम p54_parse_शेष_country(काष्ठा ieee80211_hw *dev,
				      व्योम *data, पूर्णांक len)
अणु
	काष्ठा pda_country *country;

	अगर (len != माप(*country)) अणु
		wiphy_err(dev->wiphy,
			  "found possible invalid default country eeprom entry. (entry size: %d)\n",
			  len);

		prपूर्णांक_hex_dump_bytes("country:", DUMP_PREFIX_NONE,
				     data, len);

		wiphy_err(dev->wiphy, "please report this issue.\n");
		वापस;
	पूर्ण

	country = (काष्ठा pda_country *) data;
	अगर (country->flags == PDR_COUNTRY_CERT_CODE_PSEUDO)
		regulatory_hपूर्णांक(dev->wiphy, country->alpha2);
	अन्यथा अणु
		/* TODO:
		 * ग_लिखो a shared/common function that converts
		 * "Regulatory domain codes" (802.11-2007 14.8.2.2)
		 * पूर्णांकo ISO/IEC 3166-1 alpha2 क्रम regulatory_hपूर्णांक.
		 */
	पूर्ण
पूर्ण

अटल पूर्णांक p54_convert_output_limits(काष्ठा ieee80211_hw *dev,
				     u8 *data, माप_प्रकार len)
अणु
	काष्ठा p54_common *priv = dev->priv;

	अगर (len < 2)
		वापस -EINVAL;

	अगर (data[0] != 0) अणु
		wiphy_err(dev->wiphy, "unknown output power db revision:%x\n",
			  data[0]);
		वापस -EINVAL;
	पूर्ण

	अगर (2 + data[1] * माप(काष्ठा pda_channel_output_limit) > len)
		वापस -EINVAL;

	priv->output_limit = kदो_स्मृति(data[1] *
		माप(काष्ठा pda_channel_output_limit) +
		माप(*priv->output_limit), GFP_KERNEL);

	अगर (!priv->output_limit)
		वापस -ENOMEM;

	priv->output_limit->offset = 0;
	priv->output_limit->entries = data[1];
	priv->output_limit->entry_size =
		माप(काष्ठा pda_channel_output_limit);
	priv->output_limit->len = priv->output_limit->entry_size *
				  priv->output_limit->entries +
				  priv->output_limit->offset;

	स_नकल(priv->output_limit->data, &data[2],
	       data[1] * माप(काष्ठा pda_channel_output_limit));

	वापस 0;
पूर्ण

अटल काष्ठा p54_cal_database *p54_convert_db(काष्ठा pda_custom_wrapper *src,
					       माप_प्रकार total_len)
अणु
	काष्ठा p54_cal_database *dst;
	माप_प्रकार payload_len, entries, entry_size, offset;

	payload_len = le16_to_cpu(src->len);
	entries = le16_to_cpu(src->entries);
	entry_size = le16_to_cpu(src->entry_size);
	offset = le16_to_cpu(src->offset);
	अगर (((entries * entry_size + offset) != payload_len) ||
	     (payload_len + माप(*src) != total_len))
		वापस शून्य;

	dst = kदो_स्मृति(माप(*dst) + payload_len, GFP_KERNEL);
	अगर (!dst)
		वापस शून्य;

	dst->entries = entries;
	dst->entry_size = entry_size;
	dst->offset = offset;
	dst->len = payload_len;

	स_नकल(dst->data, src->data, payload_len);
	वापस dst;
पूर्ण

पूर्णांक p54_parse_eeprom(काष्ठा ieee80211_hw *dev, व्योम *eeprom, पूर्णांक len)
अणु
	काष्ठा p54_common *priv = dev->priv;
	काष्ठा eeprom_pda_wrap *wrap;
	काष्ठा pda_entry *entry;
	अचिन्हित पूर्णांक data_len, entry_len;
	व्योम *पंचांगp;
	पूर्णांक err;
	u8 *end = (u8 *)eeprom + len;
	u16 synth = 0;
	u16 crc16 = ~0;

	wrap = (काष्ठा eeprom_pda_wrap *) eeprom;
	entry = (व्योम *)wrap->data + le16_to_cpu(wrap->len);

	/* verअगरy that at least the entry length/code fits */
	जबतक ((u8 *)entry <= end - माप(*entry)) अणु
		entry_len = le16_to_cpu(entry->len);
		data_len = ((entry_len - 1) << 1);

		/* पात अगर entry exceeds whole काष्ठाure */
		अगर ((u8 *)entry + माप(*entry) + data_len > end)
			अवरोध;

		चयन (le16_to_cpu(entry->code)) अणु
		हाल PDR_MAC_ADDRESS:
			अगर (data_len != ETH_ALEN)
				अवरोध;
			SET_IEEE80211_PERM_ADDR(dev, entry->data);
			अवरोध;
		हाल PDR_PRISM_PA_CAL_OUTPUT_POWER_LIMITS:
			अगर (priv->output_limit)
				अवरोध;
			err = p54_convert_output_limits(dev, entry->data,
							data_len);
			अगर (err)
				जाओ err;
			अवरोध;
		हाल PDR_PRISM_PA_CAL_CURVE_DATA: अणु
			काष्ठा pda_pa_curve_data *curve_data =
				(काष्ठा pda_pa_curve_data *)entry->data;
			अगर (data_len < माप(*curve_data)) अणु
				err = -EINVAL;
				जाओ err;
			पूर्ण

			चयन (curve_data->cal_method_rev) अणु
			हाल 0:
				err = p54_convert_rev0(dev, curve_data);
				अवरोध;
			हाल 1:
				err = p54_convert_rev1(dev, curve_data);
				अवरोध;
			शेष:
				wiphy_err(dev->wiphy,
					  "unknown curve data revision %d\n",
					  curve_data->cal_method_rev);
				err = -ENODEV;
				अवरोध;
			पूर्ण
			अगर (err)
				जाओ err;
			पूर्ण
			अवरोध;
		हाल PDR_PRISM_ZIF_TX_IQ_CALIBRATION:
			priv->iq_स्वतःcal = kmemdup(entry->data, data_len,
						   GFP_KERNEL);
			अगर (!priv->iq_स्वतःcal) अणु
				err = -ENOMEM;
				जाओ err;
			पूर्ण

			priv->iq_स्वतःcal_len = data_len / माप(काष्ठा pda_iq_स्वतःcal_entry);
			अवरोध;
		हाल PDR_DEFAULT_COUNTRY:
			p54_parse_शेष_country(dev, entry->data, data_len);
			अवरोध;
		हाल PDR_INTERFACE_LIST:
			पंचांगp = entry->data;
			जबतक ((u8 *)पंचांगp < entry->data + data_len) अणु
				काष्ठा exp_अगर *exp_अगर = पंचांगp;
				अगर (exp_अगर->अगर_id == cpu_to_le16(IF_ID_ISL39000))
					synth = le16_to_cpu(exp_अगर->variant);
				पंचांगp += माप(*exp_अगर);
			पूर्ण
			अवरोध;
		हाल PDR_HARDWARE_PLATFORM_COMPONENT_ID:
			अगर (data_len < 2)
				अवरोध;
			priv->version = *(u8 *)(entry->data + 1);
			अवरोध;
		हाल PDR_RSSI_LINEAR_APPROXIMATION:
		हाल PDR_RSSI_LINEAR_APPROXIMATION_DUAL_BAND:
		हाल PDR_RSSI_LINEAR_APPROXIMATION_EXTENDED:
			err = p54_parse_rssical(dev, entry->data, data_len,
						le16_to_cpu(entry->code));
			अगर (err)
				जाओ err;
			अवरोध;
		हाल PDR_RSSI_LINEAR_APPROXIMATION_CUSTOMV2: अणु
			काष्ठा pda_custom_wrapper *pda = (व्योम *) entry->data;
			__le16 *src;
			u16 *dst;
			पूर्णांक i;

			अगर (priv->rssi_db || data_len < माप(*pda))
				अवरोध;

			priv->rssi_db = p54_convert_db(pda, data_len);
			अगर (!priv->rssi_db)
				अवरोध;

			src = (व्योम *) priv->rssi_db->data;
			dst = (व्योम *) priv->rssi_db->data;

			क्रम (i = 0; i < priv->rssi_db->entries; i++)
				*(dst++) = (s16) le16_to_cpu(*(src++));

			पूर्ण
			अवरोध;
		हाल PDR_PRISM_PA_CAL_OUTPUT_POWER_LIMITS_CUSTOM: अणु
			काष्ठा pda_custom_wrapper *pda = (व्योम *) entry->data;
			अगर (priv->output_limit || data_len < माप(*pda))
				अवरोध;
			priv->output_limit = p54_convert_db(pda, data_len);
			पूर्ण
			अवरोध;
		हाल PDR_PRISM_PA_CAL_CURVE_DATA_CUSTOM: अणु
			काष्ठा pda_custom_wrapper *pda = (व्योम *) entry->data;
			अगर (priv->curve_data || data_len < माप(*pda))
				अवरोध;
			priv->curve_data = p54_convert_db(pda, data_len);
			पूर्ण
			अवरोध;
		हाल PDR_END:
			crc16 = ~crc_ccitt(crc16, (u8 *) entry, माप(*entry));
			अगर (crc16 != le16_to_cpup((__le16 *)entry->data)) अणु
				wiphy_err(dev->wiphy, "eeprom failed checksum "
					 "test!\n");
				err = -ENOMSG;
				जाओ err;
			पूर्ण अन्यथा अणु
				जाओ good_eeprom;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		crc16 = crc_ccitt(crc16, (u8 *)entry, (entry_len + 1) * 2);
		entry = (व्योम *)entry + (entry_len + 1) * 2;
	पूर्ण

	wiphy_err(dev->wiphy, "unexpected end of eeprom data.\n");
	err = -ENODATA;
	जाओ err;

good_eeprom:
	अगर (!synth || !priv->iq_स्वतःcal || !priv->output_limit ||
	    !priv->curve_data) अणु
		wiphy_err(dev->wiphy,
			  "not all required entries found in eeprom!\n");
		err = -EINVAL;
		जाओ err;
	पूर्ण

	priv->rxhw = synth & PDR_SYNTH_FRONTEND_MASK;

	err = p54_generate_channel_lists(dev);
	अगर (err)
		जाओ err;

	अगर (priv->rxhw == PDR_SYNTH_FRONTEND_XBOW)
		p54_init_xbow_synth(priv);
	अगर (!(synth & PDR_SYNTH_24_GHZ_DISABLED))
		dev->wiphy->bands[NL80211_BAND_2GHZ] =
			priv->band_table[NL80211_BAND_2GHZ];
	अगर (!(synth & PDR_SYNTH_5_GHZ_DISABLED))
		dev->wiphy->bands[NL80211_BAND_5GHZ] =
			priv->band_table[NL80211_BAND_5GHZ];
	अगर ((synth & PDR_SYNTH_RX_DIV_MASK) == PDR_SYNTH_RX_DIV_SUPPORTED)
		priv->rx_भागersity_mask = 3;
	अगर ((synth & PDR_SYNTH_TX_DIV_MASK) == PDR_SYNTH_TX_DIV_SUPPORTED)
		priv->tx_भागersity_mask = 3;

	अगर (!is_valid_ether_addr(dev->wiphy->perm_addr)) अणु
		u8 perm_addr[ETH_ALEN];

		wiphy_warn(dev->wiphy,
			   "Invalid hwaddr! Using randomly generated MAC addr\n");
		eth_अक्रमom_addr(perm_addr);
		SET_IEEE80211_PERM_ADDR(dev, perm_addr);
	पूर्ण

	priv->cur_rssi = &p54_rssi_शेष;

	wiphy_info(dev->wiphy, "hwaddr %pM, MAC:isl38%02x RF:%s\n",
		   dev->wiphy->perm_addr, priv->version,
		   p54_rf_chips[priv->rxhw]);

	वापस 0;

err:
	kमुक्त(priv->iq_स्वतःcal);
	kमुक्त(priv->output_limit);
	kमुक्त(priv->curve_data);
	kमुक्त(priv->rssi_db);
	kमुक्त(priv->survey);
	priv->iq_स्वतःcal = शून्य;
	priv->output_limit = शून्य;
	priv->curve_data = शून्य;
	priv->rssi_db = शून्य;
	priv->survey = शून्य;

	wiphy_err(dev->wiphy, "eeprom parse failed!\n");
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(p54_parse_eeprom);

पूर्णांक p54_पढ़ो_eeprom(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा p54_common *priv = dev->priv;
	माप_प्रकार eeprom_size = 0x2020, offset = 0, blocksize, maxblocksize;
	पूर्णांक ret = -ENOMEM;
	व्योम *eeprom;

	maxblocksize = EEPROM_READBACK_LEN;
	अगर (priv->fw_var >= 0x509)
		maxblocksize -= 0xc;
	अन्यथा
		maxblocksize -= 0x4;

	eeprom = kzalloc(eeprom_size, GFP_KERNEL);
	अगर (unlikely(!eeprom))
		जाओ मुक्त;

	जबतक (eeprom_size) अणु
		blocksize = min(eeprom_size, maxblocksize);
		ret = p54_करोwnload_eeprom(priv, eeprom + offset,
					  offset, blocksize);
		अगर (unlikely(ret))
			जाओ मुक्त;

		offset += blocksize;
		eeprom_size -= blocksize;
	पूर्ण

	ret = p54_parse_eeprom(dev, eeprom, offset);
मुक्त:
	kमुक्त(eeprom);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(p54_पढ़ो_eeprom);
