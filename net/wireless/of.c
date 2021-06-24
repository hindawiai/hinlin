<शैली गुरु>
/*
 * Copyright (C) 2017 Rafaध Miधecki <rafal@milecki.pl>
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <linux/of.h>
#समावेश <net/cfg80211.h>
#समावेश "core.h"

अटल bool wiphy_freq_limits_valid_chan(काष्ठा wiphy *wiphy,
					 काष्ठा ieee80211_freq_range *freq_limits,
					 अचिन्हित पूर्णांक n_freq_limits,
					 काष्ठा ieee80211_channel *chan)
अणु
	u32 bw = MHZ_TO_KHZ(20);
	पूर्णांक i;

	क्रम (i = 0; i < n_freq_limits; i++) अणु
		काष्ठा ieee80211_freq_range *limit = &freq_limits[i];

		अगर (cfg80211_करोes_bw_fit_range(limit,
					       MHZ_TO_KHZ(chan->center_freq),
					       bw))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम wiphy_freq_limits_apply(काष्ठा wiphy *wiphy,
				    काष्ठा ieee80211_freq_range *freq_limits,
				    अचिन्हित पूर्णांक n_freq_limits)
अणु
	क्रमागत nl80211_band band;
	पूर्णांक i;

	अगर (WARN_ON(!n_freq_limits))
		वापस;

	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		काष्ठा ieee80211_supported_band *sband = wiphy->bands[band];

		अगर (!sband)
			जारी;

		क्रम (i = 0; i < sband->n_channels; i++) अणु
			काष्ठा ieee80211_channel *chan = &sband->channels[i];

			अगर (chan->flags & IEEE80211_CHAN_DISABLED)
				जारी;

			अगर (!wiphy_freq_limits_valid_chan(wiphy, freq_limits,
							  n_freq_limits,
							  chan)) अणु
				pr_debug("Disabling freq %d MHz as it's out of OF limits\n",
					 chan->center_freq);
				chan->flags |= IEEE80211_CHAN_DISABLED;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम wiphy_पढ़ो_of_freq_limits(काष्ठा wiphy *wiphy)
अणु
	काष्ठा device *dev = wiphy_dev(wiphy);
	काष्ठा device_node *np;
	काष्ठा property *prop;
	काष्ठा ieee80211_freq_range *freq_limits;
	अचिन्हित पूर्णांक n_freq_limits;
	स्थिर __be32 *p;
	पूर्णांक len, i;
	पूर्णांक err = 0;

	अगर (!dev)
		वापस;
	np = dev_of_node(dev);
	अगर (!np)
		वापस;

	prop = of_find_property(np, "ieee80211-freq-limit", &len);
	अगर (!prop)
		वापस;

	अगर (!len || len % माप(u32) || len / माप(u32) % 2) अणु
		dev_err(dev, "ieee80211-freq-limit wrong format");
		वापस;
	पूर्ण
	n_freq_limits = len / माप(u32) / 2;

	freq_limits = kसुस्मृति(n_freq_limits, माप(*freq_limits), GFP_KERNEL);
	अगर (!freq_limits) अणु
		err = -ENOMEM;
		जाओ out_kमुक्त;
	पूर्ण

	p = शून्य;
	क्रम (i = 0; i < n_freq_limits; i++) अणु
		काष्ठा ieee80211_freq_range *limit = &freq_limits[i];

		p = of_prop_next_u32(prop, p, &limit->start_freq_khz);
		अगर (!p) अणु
			err = -EINVAL;
			जाओ out_kमुक्त;
		पूर्ण

		p = of_prop_next_u32(prop, p, &limit->end_freq_khz);
		अगर (!p) अणु
			err = -EINVAL;
			जाओ out_kमुक्त;
		पूर्ण

		अगर (!limit->start_freq_khz ||
		    !limit->end_freq_khz ||
		    limit->start_freq_khz >= limit->end_freq_khz) अणु
			err = -EINVAL;
			जाओ out_kमुक्त;
		पूर्ण
	पूर्ण

	wiphy_freq_limits_apply(wiphy, freq_limits, n_freq_limits);

out_kमुक्त:
	kमुक्त(freq_limits);
	अगर (err)
		dev_err(dev, "Failed to get limits: %d\n", err);
पूर्ण
EXPORT_SYMBOL(wiphy_पढ़ो_of_freq_limits);
