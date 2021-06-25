<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cfg80211 debugfs
 *
 * Copyright 2009	Luis R. Rodriguez <lrodriguez@atheros.com>
 * Copyright 2007	Johannes Berg <johannes@sipsolutions.net>
 */

#समावेश <linux/slab.h>
#समावेश "core.h"
#समावेश "debugfs.h"

#घोषणा DEBUGFS_READONLY_खाता(name, buflen, fmt, value...)		\
अटल sमाप_प्रकार name## _पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,	\
			    माप_प्रकार count, loff_t *ppos)			\
अणु									\
	काष्ठा wiphy *wiphy = file->निजी_data;			\
	अक्षर buf[buflen];						\
	पूर्णांक res;							\
									\
	res = scnम_लिखो(buf, buflen, fmt "\n", ##value);		\
	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, res);	\
पूर्ण									\
									\
अटल स्थिर काष्ठा file_operations name## _ops = अणु			\
	.पढ़ो = name## _पढ़ो,						\
	.खोलो = simple_खोलो,						\
	.llseek = generic_file_llseek,					\
पूर्ण

DEBUGFS_READONLY_खाता(rts_threshold, 20, "%d",
		      wiphy->rts_threshold);
DEBUGFS_READONLY_खाता(fragmentation_threshold, 20, "%d",
		      wiphy->frag_threshold);
DEBUGFS_READONLY_खाता(लघु_retry_limit, 20, "%d",
		      wiphy->retry_लघु);
DEBUGFS_READONLY_खाता(दीर्घ_retry_limit, 20, "%d",
		      wiphy->retry_दीर्घ);

अटल पूर्णांक ht_prपूर्णांक_chan(काष्ठा ieee80211_channel *chan,
			 अक्षर *buf, पूर्णांक buf_size, पूर्णांक offset)
अणु
	अगर (WARN_ON(offset > buf_size))
		वापस 0;

	अगर (chan->flags & IEEE80211_CHAN_DISABLED)
		वापस scnम_लिखो(buf + offset,
				 buf_size - offset,
				 "%d Disabled\n",
				 chan->center_freq);

	वापस scnम_लिखो(buf + offset,
			 buf_size - offset,
			 "%d HT40 %c%c\n",
			 chan->center_freq,
			 (chan->flags & IEEE80211_CHAN_NO_HT40MINUS) ?
				' ' : '-',
			 (chan->flags & IEEE80211_CHAN_NO_HT40PLUS) ?
				' ' : '+');
पूर्ण

अटल sमाप_प्रकार ht40allow_map_पढ़ो(काष्ठा file *file,
				  अक्षर __user *user_buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wiphy *wiphy = file->निजी_data;
	अक्षर *buf;
	अचिन्हित पूर्णांक offset = 0, buf_size = PAGE_SIZE, i, r;
	क्रमागत nl80211_band band;
	काष्ठा ieee80211_supported_band *sband;

	buf = kzalloc(buf_size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		sband = wiphy->bands[band];
		अगर (!sband)
			जारी;
		क्रम (i = 0; i < sband->n_channels; i++)
			offset += ht_prपूर्णांक_chan(&sband->channels[i],
						buf, buf_size, offset);
	पूर्ण

	r = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, offset);

	kमुक्त(buf);

	वापस r;
पूर्ण

अटल स्थिर काष्ठा file_operations ht40allow_map_ops = अणु
	.पढ़ो = ht40allow_map_पढ़ो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

#घोषणा DEBUGFS_ADD(name)						\
	debugfs_create_file(#name, 0444, phyd, &rdev->wiphy, &name## _ops)

व्योम cfg80211_debugfs_rdev_add(काष्ठा cfg80211_रेजिस्टरed_device *rdev)
अणु
	काष्ठा dentry *phyd = rdev->wiphy.debugfsdir;

	DEBUGFS_ADD(rts_threshold);
	DEBUGFS_ADD(fragmentation_threshold);
	DEBUGFS_ADD(लघु_retry_limit);
	DEBUGFS_ADD(दीर्घ_retry_limit);
	DEBUGFS_ADD(ht40allow_map);
पूर्ण
