<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2002-2005, Instant802 Networks, Inc.
 * Copyright 2005, Devicescape Software, Inc.
 * Copyright (c) 2006 Jiri Benc <jbenc@suse.cz>
 */

#अगर_अघोषित IEEE80211_RATE_H
#घोषणा IEEE80211_RATE_H

#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <net/mac80211.h>
#समावेश "ieee80211_i.h"
#समावेश "sta_info.h"
#समावेश "driver-ops.h"

काष्ठा rate_control_ref अणु
	स्थिर काष्ठा rate_control_ops *ops;
	व्योम *priv;
पूर्ण;

व्योम rate_control_get_rate(काष्ठा ieee80211_sub_अगर_data *sdata,
			   काष्ठा sta_info *sta,
			   काष्ठा ieee80211_tx_rate_control *txrc);

व्योम rate_control_tx_status(काष्ठा ieee80211_local *local,
			    काष्ठा ieee80211_supported_band *sband,
			    काष्ठा ieee80211_tx_status *st);

व्योम rate_control_rate_init(काष्ठा sta_info *sta);
व्योम rate_control_rate_update(काष्ठा ieee80211_local *local,
				    काष्ठा ieee80211_supported_band *sband,
				    काष्ठा sta_info *sta, u32 changed);

अटल अंतरभूत व्योम *rate_control_alloc_sta(काष्ठा rate_control_ref *ref,
					   काष्ठा sta_info *sta, gfp_t gfp)
अणु
	spin_lock_init(&sta->rate_ctrl_lock);
	वापस ref->ops->alloc_sta(ref->priv, &sta->sta, gfp);
पूर्ण

अटल अंतरभूत व्योम rate_control_मुक्त_sta(काष्ठा sta_info *sta)
अणु
	काष्ठा rate_control_ref *ref = sta->rate_ctrl;
	काष्ठा ieee80211_sta *ista = &sta->sta;
	व्योम *priv_sta = sta->rate_ctrl_priv;

	ref->ops->मुक्त_sta(ref->priv, ista, priv_sta);
पूर्ण

अटल अंतरभूत व्योम rate_control_add_sta_debugfs(काष्ठा sta_info *sta)
अणु
#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	काष्ठा rate_control_ref *ref = sta->rate_ctrl;
	अगर (ref && sta->debugfs_dir && ref->ops->add_sta_debugfs)
		ref->ops->add_sta_debugfs(ref->priv, sta->rate_ctrl_priv,
					  sta->debugfs_dir);
#पूर्ण_अगर
पूर्ण

बाह्य स्थिर काष्ठा file_operations rcname_ops;

अटल अंतरभूत व्योम rate_control_add_debugfs(काष्ठा ieee80211_local *local)
अणु
#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	काष्ठा dentry *debugfsdir;

	अगर (!local->rate_ctrl)
		वापस;

	अगर (!local->rate_ctrl->ops->add_debugfs)
		वापस;

	debugfsdir = debugfs_create_dir("rc", local->hw.wiphy->debugfsdir);
	local->debugfs.rcdir = debugfsdir;
	debugfs_create_file("name", 0400, debugfsdir,
			    local->rate_ctrl, &rcname_ops);

	local->rate_ctrl->ops->add_debugfs(&local->hw, local->rate_ctrl->priv,
					   debugfsdir);
#पूर्ण_अगर
पूर्ण

व्योम ieee80211_check_rate_mask(काष्ठा ieee80211_sub_अगर_data *sdata);

/* Get a reference to the rate control algorithm. If `name' is शून्य, get the
 * first available algorithm. */
पूर्णांक ieee80211_init_rate_ctrl_alg(काष्ठा ieee80211_local *local,
				 स्थिर अक्षर *name);
व्योम rate_control_deinitialize(काष्ठा ieee80211_local *local);


/* Rate control algorithms */
#अगर_घोषित CONFIG_MAC80211_RC_MINSTREL
पूर्णांक rc80211_minstrel_init(व्योम);
व्योम rc80211_minstrel_निकास(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक rc80211_minstrel_init(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम rc80211_minstrel_निकास(व्योम)
अणु
पूर्ण
#पूर्ण_अगर


#पूर्ण_अगर /* IEEE80211_RATE_H */
