<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mac80211 - channel management
 */

#समावेश <linux/nl80211.h>
#समावेश <linux/export.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/cfg80211.h>
#समावेश "ieee80211_i.h"
#समावेश "driver-ops.h"
#समावेश "rate.h"

अटल पूर्णांक ieee80211_chanctx_num_asचिन्हित(काष्ठा ieee80211_local *local,
					  काष्ठा ieee80211_chanctx *ctx)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	पूर्णांक num = 0;

	lockdep_निश्चित_held(&local->chanctx_mtx);

	list_क्रम_each_entry(sdata, &ctx->asचिन्हित_vअगरs, asचिन्हित_chanctx_list)
		num++;

	वापस num;
पूर्ण

अटल पूर्णांक ieee80211_chanctx_num_reserved(काष्ठा ieee80211_local *local,
					  काष्ठा ieee80211_chanctx *ctx)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	पूर्णांक num = 0;

	lockdep_निश्चित_held(&local->chanctx_mtx);

	list_क्रम_each_entry(sdata, &ctx->reserved_vअगरs, reserved_chanctx_list)
		num++;

	वापस num;
पूर्ण

पूर्णांक ieee80211_chanctx_refcount(काष्ठा ieee80211_local *local,
			       काष्ठा ieee80211_chanctx *ctx)
अणु
	वापस ieee80211_chanctx_num_asचिन्हित(local, ctx) +
	       ieee80211_chanctx_num_reserved(local, ctx);
पूर्ण

अटल पूर्णांक ieee80211_num_chanctx(काष्ठा ieee80211_local *local)
अणु
	काष्ठा ieee80211_chanctx *ctx;
	पूर्णांक num = 0;

	lockdep_निश्चित_held(&local->chanctx_mtx);

	list_क्रम_each_entry(ctx, &local->chanctx_list, list)
		num++;

	वापस num;
पूर्ण

अटल bool ieee80211_can_create_new_chanctx(काष्ठा ieee80211_local *local)
अणु
	lockdep_निश्चित_held(&local->chanctx_mtx);
	वापस ieee80211_num_chanctx(local) < ieee80211_max_num_channels(local);
पूर्ण

अटल काष्ठा ieee80211_chanctx *
ieee80211_vअगर_get_chanctx(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local __maybe_unused = sdata->local;
	काष्ठा ieee80211_chanctx_conf *conf;

	conf = rcu_dereference_रक्षित(sdata->vअगर.chanctx_conf,
					 lockdep_is_held(&local->chanctx_mtx));
	अगर (!conf)
		वापस शून्य;

	वापस container_of(conf, काष्ठा ieee80211_chanctx, conf);
पूर्ण

अटल स्थिर काष्ठा cfg80211_chan_def *
ieee80211_chanctx_reserved_chandef(काष्ठा ieee80211_local *local,
				   काष्ठा ieee80211_chanctx *ctx,
				   स्थिर काष्ठा cfg80211_chan_def *compat)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;

	lockdep_निश्चित_held(&local->chanctx_mtx);

	list_क्रम_each_entry(sdata, &ctx->reserved_vअगरs,
			    reserved_chanctx_list) अणु
		अगर (!compat)
			compat = &sdata->reserved_chandef;

		compat = cfg80211_chandef_compatible(&sdata->reserved_chandef,
						     compat);
		अगर (!compat)
			अवरोध;
	पूर्ण

	वापस compat;
पूर्ण

अटल स्थिर काष्ठा cfg80211_chan_def *
ieee80211_chanctx_non_reserved_chandef(काष्ठा ieee80211_local *local,
				       काष्ठा ieee80211_chanctx *ctx,
				       स्थिर काष्ठा cfg80211_chan_def *compat)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;

	lockdep_निश्चित_held(&local->chanctx_mtx);

	list_क्रम_each_entry(sdata, &ctx->asचिन्हित_vअगरs,
			    asचिन्हित_chanctx_list) अणु
		अगर (sdata->reserved_chanctx != शून्य)
			जारी;

		अगर (!compat)
			compat = &sdata->vअगर.bss_conf.chandef;

		compat = cfg80211_chandef_compatible(
				&sdata->vअगर.bss_conf.chandef, compat);
		अगर (!compat)
			अवरोध;
	पूर्ण

	वापस compat;
पूर्ण

अटल स्थिर काष्ठा cfg80211_chan_def *
ieee80211_chanctx_combined_chandef(काष्ठा ieee80211_local *local,
				   काष्ठा ieee80211_chanctx *ctx,
				   स्थिर काष्ठा cfg80211_chan_def *compat)
अणु
	lockdep_निश्चित_held(&local->chanctx_mtx);

	compat = ieee80211_chanctx_reserved_chandef(local, ctx, compat);
	अगर (!compat)
		वापस शून्य;

	compat = ieee80211_chanctx_non_reserved_chandef(local, ctx, compat);
	अगर (!compat)
		वापस शून्य;

	वापस compat;
पूर्ण

अटल bool
ieee80211_chanctx_can_reserve_chandef(काष्ठा ieee80211_local *local,
				      काष्ठा ieee80211_chanctx *ctx,
				      स्थिर काष्ठा cfg80211_chan_def *def)
अणु
	lockdep_निश्चित_held(&local->chanctx_mtx);

	अगर (ieee80211_chanctx_combined_chandef(local, ctx, def))
		वापस true;

	अगर (!list_empty(&ctx->reserved_vअगरs) &&
	    ieee80211_chanctx_reserved_chandef(local, ctx, def))
		वापस true;

	वापस false;
पूर्ण

अटल काष्ठा ieee80211_chanctx *
ieee80211_find_reservation_chanctx(काष्ठा ieee80211_local *local,
				   स्थिर काष्ठा cfg80211_chan_def *chandef,
				   क्रमागत ieee80211_chanctx_mode mode)
अणु
	काष्ठा ieee80211_chanctx *ctx;

	lockdep_निश्चित_held(&local->chanctx_mtx);

	अगर (mode == IEEE80211_CHANCTX_EXCLUSIVE)
		वापस शून्य;

	list_क्रम_each_entry(ctx, &local->chanctx_list, list) अणु
		अगर (ctx->replace_state == IEEE80211_CHANCTX_WILL_BE_REPLACED)
			जारी;

		अगर (ctx->mode == IEEE80211_CHANCTX_EXCLUSIVE)
			जारी;

		अगर (!ieee80211_chanctx_can_reserve_chandef(local, ctx,
							   chandef))
			जारी;

		वापस ctx;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल क्रमागत nl80211_chan_width ieee80211_get_sta_bw(काष्ठा sta_info *sta)
अणु
	क्रमागत ieee80211_sta_rx_bandwidth width = ieee80211_sta_cap_rx_bw(sta);

	चयन (width) अणु
	हाल IEEE80211_STA_RX_BW_20:
		अगर (sta->sta.ht_cap.ht_supported)
			वापस NL80211_CHAN_WIDTH_20;
		अन्यथा
			वापस NL80211_CHAN_WIDTH_20_NOHT;
	हाल IEEE80211_STA_RX_BW_40:
		वापस NL80211_CHAN_WIDTH_40;
	हाल IEEE80211_STA_RX_BW_80:
		वापस NL80211_CHAN_WIDTH_80;
	हाल IEEE80211_STA_RX_BW_160:
		/*
		 * This applied क्रम both 160 and 80+80. since we use
		 * the वापसed value to consider degradation of
		 * ctx->conf.min_def, we have to make sure to take
		 * the bigger one (NL80211_CHAN_WIDTH_160).
		 * Otherwise we might try degrading even when not
		 * needed, as the max required sta_bw वापसed (80+80)
		 * might be smaller than the configured bw (160).
		 */
		वापस NL80211_CHAN_WIDTH_160;
	शेष:
		WARN_ON(1);
		वापस NL80211_CHAN_WIDTH_20;
	पूर्ण
पूर्ण

अटल क्रमागत nl80211_chan_width
ieee80211_get_max_required_bw(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	क्रमागत nl80211_chan_width max_bw = NL80211_CHAN_WIDTH_20_NOHT;
	काष्ठा sta_info *sta;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sta, &sdata->local->sta_list, list) अणु
		अगर (sdata != sta->sdata &&
		    !(sta->sdata->bss && sta->sdata->bss == sdata->bss))
			जारी;

		max_bw = max(max_bw, ieee80211_get_sta_bw(sta));
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस max_bw;
पूर्ण

अटल क्रमागत nl80211_chan_width
ieee80211_get_chanctx_max_required_bw(काष्ठा ieee80211_local *local,
				      काष्ठा ieee80211_chanctx_conf *conf)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	क्रमागत nl80211_chan_width max_bw = NL80211_CHAN_WIDTH_20_NOHT;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sdata, &local->पूर्णांकerfaces, list) अणु
		काष्ठा ieee80211_vअगर *vअगर = &sdata->vअगर;
		क्रमागत nl80211_chan_width width = NL80211_CHAN_WIDTH_20_NOHT;

		अगर (!ieee80211_sdata_running(sdata))
			जारी;

		अगर (rcu_access_poपूर्णांकer(sdata->vअगर.chanctx_conf) != conf)
			जारी;

		चयन (vअगर->type) अणु
		हाल NL80211_IFTYPE_AP:
		हाल NL80211_IFTYPE_AP_VLAN:
			width = ieee80211_get_max_required_bw(sdata);
			अवरोध;
		हाल NL80211_IFTYPE_STATION:
			/*
			 * The ap's sta->bandwidth is not set yet at this
			 * poपूर्णांक, so take the width from the chandef, but
			 * account also क्रम TDLS peers
			 */
			width = max(vअगर->bss_conf.chandef.width,
				    ieee80211_get_max_required_bw(sdata));
			अवरोध;
		हाल NL80211_IFTYPE_P2P_DEVICE:
		हाल NL80211_IFTYPE_न_अंक:
			जारी;
		हाल NL80211_IFTYPE_ADHOC:
		हाल NL80211_IFTYPE_MESH_POINT:
		हाल NL80211_IFTYPE_OCB:
			width = vअगर->bss_conf.chandef.width;
			अवरोध;
		हाल NL80211_IFTYPE_WDS:
		हाल NL80211_IFTYPE_UNSPECIFIED:
		हाल NUM_NL80211_IFTYPES:
		हाल NL80211_IFTYPE_MONITOR:
		हाल NL80211_IFTYPE_P2P_CLIENT:
		हाल NL80211_IFTYPE_P2P_GO:
			WARN_ON_ONCE(1);
		पूर्ण
		max_bw = max(max_bw, width);
	पूर्ण

	/* use the configured bandwidth in हाल of monitor पूर्णांकerface */
	sdata = rcu_dereference(local->monitor_sdata);
	अगर (sdata && rcu_access_poपूर्णांकer(sdata->vअगर.chanctx_conf) == conf)
		max_bw = max(max_bw, conf->def.width);

	rcu_पढ़ो_unlock();

	वापस max_bw;
पूर्ण

/*
 * recalc the min required chan width of the channel context, which is
 * the max of min required widths of all the पूर्णांकerfaces bound to this
 * channel context.
 */
व्योम ieee80211_recalc_chanctx_min_def(काष्ठा ieee80211_local *local,
				      काष्ठा ieee80211_chanctx *ctx)
अणु
	क्रमागत nl80211_chan_width max_bw;
	काष्ठा cfg80211_chan_def min_def;

	lockdep_निश्चित_held(&local->chanctx_mtx);

	/* करोn't optimize non-20MHz based and radar_enabled confs */
	अगर (ctx->conf.def.width == NL80211_CHAN_WIDTH_5 ||
	    ctx->conf.def.width == NL80211_CHAN_WIDTH_10 ||
	    ctx->conf.def.width == NL80211_CHAN_WIDTH_1 ||
	    ctx->conf.def.width == NL80211_CHAN_WIDTH_2 ||
	    ctx->conf.def.width == NL80211_CHAN_WIDTH_4 ||
	    ctx->conf.def.width == NL80211_CHAN_WIDTH_8 ||
	    ctx->conf.def.width == NL80211_CHAN_WIDTH_16 ||
	    ctx->conf.radar_enabled) अणु
		ctx->conf.min_def = ctx->conf.def;
		वापस;
	पूर्ण

	max_bw = ieee80211_get_chanctx_max_required_bw(local, &ctx->conf);

	/* करोwngrade chandef up to max_bw */
	min_def = ctx->conf.def;
	जबतक (min_def.width > max_bw)
		ieee80211_chandef_करोwngrade(&min_def);

	अगर (cfg80211_chandef_identical(&ctx->conf.min_def, &min_def))
		वापस;

	ctx->conf.min_def = min_def;
	अगर (!ctx->driver_present)
		वापस;

	drv_change_chanctx(local, ctx, IEEE80211_CHANCTX_CHANGE_MIN_WIDTH);
पूर्ण

अटल व्योम ieee80211_chan_bw_change(काष्ठा ieee80211_local *local,
				     काष्ठा ieee80211_chanctx *ctx)
अणु
	काष्ठा sta_info *sta;
	काष्ठा ieee80211_supported_band *sband =
		local->hw.wiphy->bands[ctx->conf.def.chan->band];

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sta, &local->sta_list,
				list) अणु
		क्रमागत ieee80211_sta_rx_bandwidth new_sta_bw;

		अगर (!ieee80211_sdata_running(sta->sdata))
			जारी;

		अगर (rcu_access_poपूर्णांकer(sta->sdata->vअगर.chanctx_conf) !=
		    &ctx->conf)
			जारी;

		new_sta_bw = ieee80211_sta_cur_vht_bw(sta);
		अगर (new_sta_bw == sta->sta.bandwidth)
			जारी;

		sta->sta.bandwidth = new_sta_bw;
		rate_control_rate_update(local, sband, sta,
					 IEEE80211_RC_BW_CHANGED);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम ieee80211_change_chanctx(काष्ठा ieee80211_local *local,
				     काष्ठा ieee80211_chanctx *ctx,
				     स्थिर काष्ठा cfg80211_chan_def *chandef)
अणु
	क्रमागत nl80211_chan_width width;

	अगर (cfg80211_chandef_identical(&ctx->conf.def, chandef)) अणु
		ieee80211_recalc_chanctx_min_def(local, ctx);
		वापस;
	पूर्ण

	WARN_ON(!cfg80211_chandef_compatible(&ctx->conf.def, chandef));

	width = ctx->conf.def.width;
	ctx->conf.def = *chandef;

	/* expected to handle only 20/40/80/160 channel widths */
	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_20_NOHT:
	हाल NL80211_CHAN_WIDTH_20:
	हाल NL80211_CHAN_WIDTH_40:
	हाल NL80211_CHAN_WIDTH_80:
	हाल NL80211_CHAN_WIDTH_80P80:
	हाल NL80211_CHAN_WIDTH_160:
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

	अगर (chandef->width < width)
		ieee80211_chan_bw_change(local, ctx);

	drv_change_chanctx(local, ctx, IEEE80211_CHANCTX_CHANGE_WIDTH);
	ieee80211_recalc_chanctx_min_def(local, ctx);

	अगर (!local->use_chanctx) अणु
		local->_oper_chandef = *chandef;
		ieee80211_hw_config(local, 0);
	पूर्ण

	अगर (chandef->width > width)
		ieee80211_chan_bw_change(local, ctx);
पूर्ण

अटल काष्ठा ieee80211_chanctx *
ieee80211_find_chanctx(काष्ठा ieee80211_local *local,
		       स्थिर काष्ठा cfg80211_chan_def *chandef,
		       क्रमागत ieee80211_chanctx_mode mode)
अणु
	काष्ठा ieee80211_chanctx *ctx;

	lockdep_निश्चित_held(&local->chanctx_mtx);

	अगर (mode == IEEE80211_CHANCTX_EXCLUSIVE)
		वापस शून्य;

	list_क्रम_each_entry(ctx, &local->chanctx_list, list) अणु
		स्थिर काष्ठा cfg80211_chan_def *compat;

		अगर (ctx->replace_state != IEEE80211_CHANCTX_REPLACE_NONE)
			जारी;

		अगर (ctx->mode == IEEE80211_CHANCTX_EXCLUSIVE)
			जारी;

		compat = cfg80211_chandef_compatible(&ctx->conf.def, chandef);
		अगर (!compat)
			जारी;

		compat = ieee80211_chanctx_reserved_chandef(local, ctx,
							    compat);
		अगर (!compat)
			जारी;

		ieee80211_change_chanctx(local, ctx, compat);

		वापस ctx;
	पूर्ण

	वापस शून्य;
पूर्ण

bool ieee80211_is_radar_required(काष्ठा ieee80211_local *local)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;

	lockdep_निश्चित_held(&local->mtx);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (sdata->radar_required) अणु
			rcu_पढ़ो_unlock();
			वापस true;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस false;
पूर्ण

अटल bool
ieee80211_chanctx_radar_required(काष्ठा ieee80211_local *local,
				 काष्ठा ieee80211_chanctx *ctx)
अणु
	काष्ठा ieee80211_chanctx_conf *conf = &ctx->conf;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	bool required = false;

	lockdep_निश्चित_held(&local->chanctx_mtx);
	lockdep_निश्चित_held(&local->mtx);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (!ieee80211_sdata_running(sdata))
			जारी;
		अगर (rcu_access_poपूर्णांकer(sdata->vअगर.chanctx_conf) != conf)
			जारी;
		अगर (!sdata->radar_required)
			जारी;

		required = true;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस required;
पूर्ण

अटल काष्ठा ieee80211_chanctx *
ieee80211_alloc_chanctx(काष्ठा ieee80211_local *local,
			स्थिर काष्ठा cfg80211_chan_def *chandef,
			क्रमागत ieee80211_chanctx_mode mode)
अणु
	काष्ठा ieee80211_chanctx *ctx;

	lockdep_निश्चित_held(&local->chanctx_mtx);

	ctx = kzalloc(माप(*ctx) + local->hw.chanctx_data_size, GFP_KERNEL);
	अगर (!ctx)
		वापस शून्य;

	INIT_LIST_HEAD(&ctx->asचिन्हित_vअगरs);
	INIT_LIST_HEAD(&ctx->reserved_vअगरs);
	ctx->conf.def = *chandef;
	ctx->conf.rx_chains_अटल = 1;
	ctx->conf.rx_chains_dynamic = 1;
	ctx->mode = mode;
	ctx->conf.radar_enabled = false;
	ieee80211_recalc_chanctx_min_def(local, ctx);

	वापस ctx;
पूर्ण

अटल पूर्णांक ieee80211_add_chanctx(काष्ठा ieee80211_local *local,
				 काष्ठा ieee80211_chanctx *ctx)
अणु
	u32 changed;
	पूर्णांक err;

	lockdep_निश्चित_held(&local->mtx);
	lockdep_निश्चित_held(&local->chanctx_mtx);

	अगर (!local->use_chanctx)
		local->hw.conf.radar_enabled = ctx->conf.radar_enabled;

	/* turn idle off *beक्रमe* setting channel -- some drivers need that */
	changed = ieee80211_idle_off(local);
	अगर (changed)
		ieee80211_hw_config(local, changed);

	अगर (!local->use_chanctx) अणु
		local->_oper_chandef = ctx->conf.def;
		ieee80211_hw_config(local, IEEE80211_CONF_CHANGE_CHANNEL);
	पूर्ण अन्यथा अणु
		err = drv_add_chanctx(local, ctx);
		अगर (err) अणु
			ieee80211_recalc_idle(local);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा ieee80211_chanctx *
ieee80211_new_chanctx(काष्ठा ieee80211_local *local,
		      स्थिर काष्ठा cfg80211_chan_def *chandef,
		      क्रमागत ieee80211_chanctx_mode mode)
अणु
	काष्ठा ieee80211_chanctx *ctx;
	पूर्णांक err;

	lockdep_निश्चित_held(&local->mtx);
	lockdep_निश्चित_held(&local->chanctx_mtx);

	ctx = ieee80211_alloc_chanctx(local, chandef, mode);
	अगर (!ctx)
		वापस ERR_PTR(-ENOMEM);

	err = ieee80211_add_chanctx(local, ctx);
	अगर (err) अणु
		kमुक्त(ctx);
		वापस ERR_PTR(err);
	पूर्ण

	list_add_rcu(&ctx->list, &local->chanctx_list);
	वापस ctx;
पूर्ण

अटल व्योम ieee80211_del_chanctx(काष्ठा ieee80211_local *local,
				  काष्ठा ieee80211_chanctx *ctx)
अणु
	lockdep_निश्चित_held(&local->chanctx_mtx);

	अगर (!local->use_chanctx) अणु
		काष्ठा cfg80211_chan_def *chandef = &local->_oper_chandef;
		/* S1G करोesn't have 20MHz, so get the correct width क्रम the
		 * current channel.
		 */
		अगर (chandef->chan->band == NL80211_BAND_S1GHZ)
			chandef->width =
				ieee80211_s1g_channel_width(chandef->chan);
		अन्यथा
			chandef->width = NL80211_CHAN_WIDTH_20_NOHT;
		chandef->center_freq1 = chandef->chan->center_freq;
		chandef->freq1_offset = chandef->chan->freq_offset;
		chandef->center_freq2 = 0;

		/* NOTE: Disabling radar is only valid here क्रम
		 * single channel context. To be sure, check it ...
		 */
		WARN_ON(local->hw.conf.radar_enabled &&
			!list_empty(&local->chanctx_list));

		local->hw.conf.radar_enabled = false;

		ieee80211_hw_config(local, IEEE80211_CONF_CHANGE_CHANNEL);
	पूर्ण अन्यथा अणु
		drv_हटाओ_chanctx(local, ctx);
	पूर्ण

	ieee80211_recalc_idle(local);
पूर्ण

अटल व्योम ieee80211_मुक्त_chanctx(काष्ठा ieee80211_local *local,
				   काष्ठा ieee80211_chanctx *ctx)
अणु
	lockdep_निश्चित_held(&local->chanctx_mtx);

	WARN_ON_ONCE(ieee80211_chanctx_refcount(local, ctx) != 0);

	list_del_rcu(&ctx->list);
	ieee80211_del_chanctx(local, ctx);
	kमुक्त_rcu(ctx, rcu_head);
पूर्ण

व्योम ieee80211_recalc_chanctx_chantype(काष्ठा ieee80211_local *local,
				       काष्ठा ieee80211_chanctx *ctx)
अणु
	काष्ठा ieee80211_chanctx_conf *conf = &ctx->conf;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	स्थिर काष्ठा cfg80211_chan_def *compat = शून्य;
	काष्ठा sta_info *sta;

	lockdep_निश्चित_held(&local->chanctx_mtx);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sdata, &local->पूर्णांकerfaces, list) अणु

		अगर (!ieee80211_sdata_running(sdata))
			जारी;
		अगर (rcu_access_poपूर्णांकer(sdata->vअगर.chanctx_conf) != conf)
			जारी;
		अगर (sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN)
			जारी;

		अगर (!compat)
			compat = &sdata->vअगर.bss_conf.chandef;

		compat = cfg80211_chandef_compatible(
				&sdata->vअगर.bss_conf.chandef, compat);
		अगर (WARN_ON_ONCE(!compat))
			अवरोध;
	पूर्ण

	/* TDLS peers can someबार affect the chandef width */
	list_क्रम_each_entry_rcu(sta, &local->sta_list, list) अणु
		अगर (!sta->uploaded ||
		    !test_sta_flag(sta, WLAN_STA_TDLS_WIDER_BW) ||
		    !test_sta_flag(sta, WLAN_STA_AUTHORIZED) ||
		    !sta->tdls_chandef.chan)
			जारी;

		compat = cfg80211_chandef_compatible(&sta->tdls_chandef,
						     compat);
		अगर (WARN_ON_ONCE(!compat))
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (!compat)
		वापस;

	ieee80211_change_chanctx(local, ctx, compat);
पूर्ण

अटल व्योम ieee80211_recalc_radar_chanctx(काष्ठा ieee80211_local *local,
					   काष्ठा ieee80211_chanctx *chanctx)
अणु
	bool radar_enabled;

	lockdep_निश्चित_held(&local->chanctx_mtx);
	/* क्रम ieee80211_is_radar_required */
	lockdep_निश्चित_held(&local->mtx);

	radar_enabled = ieee80211_chanctx_radar_required(local, chanctx);

	अगर (radar_enabled == chanctx->conf.radar_enabled)
		वापस;

	chanctx->conf.radar_enabled = radar_enabled;

	अगर (!local->use_chanctx) अणु
		local->hw.conf.radar_enabled = chanctx->conf.radar_enabled;
		ieee80211_hw_config(local, IEEE80211_CONF_CHANGE_CHANNEL);
	पूर्ण

	drv_change_chanctx(local, chanctx, IEEE80211_CHANCTX_CHANGE_RADAR);
पूर्ण

अटल पूर्णांक ieee80211_assign_vअगर_chanctx(काष्ठा ieee80211_sub_अगर_data *sdata,
					काष्ठा ieee80211_chanctx *new_ctx)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_chanctx_conf *conf;
	काष्ठा ieee80211_chanctx *curr_ctx = शून्य;
	पूर्णांक ret = 0;

	अगर (WARN_ON(sdata->vअगर.type == NL80211_IFTYPE_न_अंक))
		वापस -ENOTSUPP;

	conf = rcu_dereference_रक्षित(sdata->vअगर.chanctx_conf,
					 lockdep_is_held(&local->chanctx_mtx));

	अगर (conf) अणु
		curr_ctx = container_of(conf, काष्ठा ieee80211_chanctx, conf);

		drv_unassign_vअगर_chanctx(local, sdata, curr_ctx);
		conf = शून्य;
		list_del(&sdata->asचिन्हित_chanctx_list);
	पूर्ण

	अगर (new_ctx) अणु
		ret = drv_assign_vअगर_chanctx(local, sdata, new_ctx);
		अगर (ret)
			जाओ out;

		conf = &new_ctx->conf;
		list_add(&sdata->asचिन्हित_chanctx_list,
			 &new_ctx->asचिन्हित_vअगरs);
	पूर्ण

out:
	rcu_assign_poपूर्णांकer(sdata->vअगर.chanctx_conf, conf);

	sdata->vअगर.bss_conf.idle = !conf;

	अगर (curr_ctx && ieee80211_chanctx_num_asचिन्हित(local, curr_ctx) > 0) अणु
		ieee80211_recalc_chanctx_chantype(local, curr_ctx);
		ieee80211_recalc_smps_chanctx(local, curr_ctx);
		ieee80211_recalc_radar_chanctx(local, curr_ctx);
		ieee80211_recalc_chanctx_min_def(local, curr_ctx);
	पूर्ण

	अगर (new_ctx && ieee80211_chanctx_num_asचिन्हित(local, new_ctx) > 0) अणु
		ieee80211_recalc_txघातer(sdata, false);
		ieee80211_recalc_chanctx_min_def(local, new_ctx);
	पूर्ण

	अगर (sdata->vअगर.type != NL80211_IFTYPE_P2P_DEVICE &&
	    sdata->vअगर.type != NL80211_IFTYPE_MONITOR)
		ieee80211_bss_info_change_notअगरy(sdata,
						 BSS_CHANGED_IDLE);

	ieee80211_check_fast_xmit_अगरace(sdata);

	वापस ret;
पूर्ण

व्योम ieee80211_recalc_smps_chanctx(काष्ठा ieee80211_local *local,
				   काष्ठा ieee80211_chanctx *chanctx)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	u8 rx_chains_अटल, rx_chains_dynamic;

	lockdep_निश्चित_held(&local->chanctx_mtx);

	rx_chains_अटल = 1;
	rx_chains_dynamic = 1;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sdata, &local->पूर्णांकerfaces, list) अणु
		u8 needed_अटल, needed_dynamic;

		अगर (!ieee80211_sdata_running(sdata))
			जारी;

		अगर (rcu_access_poपूर्णांकer(sdata->vअगर.chanctx_conf) !=
						&chanctx->conf)
			जारी;

		चयन (sdata->vअगर.type) अणु
		हाल NL80211_IFTYPE_P2P_DEVICE:
		हाल NL80211_IFTYPE_न_अंक:
			जारी;
		हाल NL80211_IFTYPE_STATION:
			अगर (!sdata->u.mgd.associated)
				जारी;
			अवरोध;
		हाल NL80211_IFTYPE_AP_VLAN:
			जारी;
		हाल NL80211_IFTYPE_AP:
		हाल NL80211_IFTYPE_ADHOC:
		हाल NL80211_IFTYPE_MESH_POINT:
		हाल NL80211_IFTYPE_OCB:
			अवरोध;
		शेष:
			WARN_ON_ONCE(1);
		पूर्ण

		चयन (sdata->smps_mode) अणु
		शेष:
			WARN_ONCE(1, "Invalid SMPS mode %d\n",
				  sdata->smps_mode);
			fallthrough;
		हाल IEEE80211_SMPS_OFF:
			needed_अटल = sdata->needed_rx_chains;
			needed_dynamic = sdata->needed_rx_chains;
			अवरोध;
		हाल IEEE80211_SMPS_DYNAMIC:
			needed_अटल = 1;
			needed_dynamic = sdata->needed_rx_chains;
			अवरोध;
		हाल IEEE80211_SMPS_STATIC:
			needed_अटल = 1;
			needed_dynamic = 1;
			अवरोध;
		पूर्ण

		rx_chains_अटल = max(rx_chains_अटल, needed_अटल);
		rx_chains_dynamic = max(rx_chains_dynamic, needed_dynamic);
	पूर्ण

	/* Disable SMPS क्रम the monitor पूर्णांकerface */
	sdata = rcu_dereference(local->monitor_sdata);
	अगर (sdata &&
	    rcu_access_poपूर्णांकer(sdata->vअगर.chanctx_conf) == &chanctx->conf)
		rx_chains_dynamic = rx_chains_अटल = local->rx_chains;

	rcu_पढ़ो_unlock();

	अगर (!local->use_chanctx) अणु
		अगर (rx_chains_अटल > 1)
			local->smps_mode = IEEE80211_SMPS_OFF;
		अन्यथा अगर (rx_chains_dynamic > 1)
			local->smps_mode = IEEE80211_SMPS_DYNAMIC;
		अन्यथा
			local->smps_mode = IEEE80211_SMPS_STATIC;
		ieee80211_hw_config(local, 0);
	पूर्ण

	अगर (rx_chains_अटल == chanctx->conf.rx_chains_अटल &&
	    rx_chains_dynamic == chanctx->conf.rx_chains_dynamic)
		वापस;

	chanctx->conf.rx_chains_अटल = rx_chains_अटल;
	chanctx->conf.rx_chains_dynamic = rx_chains_dynamic;
	drv_change_chanctx(local, chanctx, IEEE80211_CHANCTX_CHANGE_RX_CHAINS);
पूर्ण

अटल व्योम
__ieee80211_vअगर_copy_chanctx_to_vlans(काष्ठा ieee80211_sub_अगर_data *sdata,
				      bool clear)
अणु
	काष्ठा ieee80211_local *local __maybe_unused = sdata->local;
	काष्ठा ieee80211_sub_अगर_data *vlan;
	काष्ठा ieee80211_chanctx_conf *conf;

	अगर (WARN_ON(sdata->vअगर.type != NL80211_IFTYPE_AP))
		वापस;

	lockdep_निश्चित_held(&local->mtx);

	/* Check that conf exists, even when clearing this function
	 * must be called with the AP's channel context still there
	 * as it would otherwise cause VLANs to have an invalid
	 * channel context poपूर्णांकer क्रम a जबतक, possibly poपूर्णांकing
	 * to a channel context that has alपढ़ोy been मुक्तd.
	 */
	conf = rcu_dereference_रक्षित(sdata->vअगर.chanctx_conf,
					 lockdep_is_held(&local->chanctx_mtx));
	WARN_ON(!conf);

	अगर (clear)
		conf = शून्य;

	list_क्रम_each_entry(vlan, &sdata->u.ap.vlans, u.vlan.list)
		rcu_assign_poपूर्णांकer(vlan->vअगर.chanctx_conf, conf);
पूर्ण

व्योम ieee80211_vअगर_copy_chanctx_to_vlans(काष्ठा ieee80211_sub_अगर_data *sdata,
					 bool clear)
अणु
	काष्ठा ieee80211_local *local = sdata->local;

	mutex_lock(&local->chanctx_mtx);

	__ieee80211_vअगर_copy_chanctx_to_vlans(sdata, clear);

	mutex_unlock(&local->chanctx_mtx);
पूर्ण

पूर्णांक ieee80211_vअगर_unreserve_chanctx(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_chanctx *ctx = sdata->reserved_chanctx;

	lockdep_निश्चित_held(&sdata->local->chanctx_mtx);

	अगर (WARN_ON(!ctx))
		वापस -EINVAL;

	list_del(&sdata->reserved_chanctx_list);
	sdata->reserved_chanctx = शून्य;

	अगर (ieee80211_chanctx_refcount(sdata->local, ctx) == 0) अणु
		अगर (ctx->replace_state == IEEE80211_CHANCTX_REPLACES_OTHER) अणु
			अगर (WARN_ON(!ctx->replace_ctx))
				वापस -EINVAL;

			WARN_ON(ctx->replace_ctx->replace_state !=
			        IEEE80211_CHANCTX_WILL_BE_REPLACED);
			WARN_ON(ctx->replace_ctx->replace_ctx != ctx);

			ctx->replace_ctx->replace_ctx = शून्य;
			ctx->replace_ctx->replace_state =
					IEEE80211_CHANCTX_REPLACE_NONE;

			list_del_rcu(&ctx->list);
			kमुक्त_rcu(ctx, rcu_head);
		पूर्ण अन्यथा अणु
			ieee80211_मुक्त_chanctx(sdata->local, ctx);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ieee80211_vअगर_reserve_chanctx(काष्ठा ieee80211_sub_अगर_data *sdata,
				  स्थिर काष्ठा cfg80211_chan_def *chandef,
				  क्रमागत ieee80211_chanctx_mode mode,
				  bool radar_required)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_chanctx *new_ctx, *curr_ctx, *ctx;

	lockdep_निश्चित_held(&local->chanctx_mtx);

	curr_ctx = ieee80211_vअगर_get_chanctx(sdata);
	अगर (curr_ctx && local->use_chanctx && !local->ops->चयन_vअगर_chanctx)
		वापस -ENOTSUPP;

	new_ctx = ieee80211_find_reservation_chanctx(local, chandef, mode);
	अगर (!new_ctx) अणु
		अगर (ieee80211_can_create_new_chanctx(local)) अणु
			new_ctx = ieee80211_new_chanctx(local, chandef, mode);
			अगर (IS_ERR(new_ctx))
				वापस PTR_ERR(new_ctx);
		पूर्ण अन्यथा अणु
			अगर (!curr_ctx ||
			    (curr_ctx->replace_state ==
			     IEEE80211_CHANCTX_WILL_BE_REPLACED) ||
			    !list_empty(&curr_ctx->reserved_vअगरs)) अणु
				/*
				 * Another vअगर alपढ़ोy requested this context
				 * क्रम a reservation. Find another one hoping
				 * all vअगरs asचिन्हित to it will also चयन
				 * soon enough.
				 *
				 * TODO: This needs a little more work as some
				 * हालs (more than 2 chanctx capable devices)
				 * may fail which could otherwise succeed
				 * provided some channel context juggling was
				 * perक्रमmed.
				 *
				 * Consider ctx1..3, vअगर1..6, each ctx has 2
				 * vअगरs. vअगर1 and vअगर2 from ctx1 request new
				 * dअगरferent chandefs starting 2 in-place
				 * reserations with ctx4 and ctx5 replacing
				 * ctx1 and ctx2 respectively. Next vअगर5 and
				 * vअगर6 from ctx3 reserve ctx4. If vअगर3 and
				 * vअगर4 reमुख्य on ctx2 as they are then this
				 * fails unless `replace_ctx` from ctx5 is
				 * replaced with ctx3.
				 */
				list_क्रम_each_entry(ctx, &local->chanctx_list,
						    list) अणु
					अगर (ctx->replace_state !=
					    IEEE80211_CHANCTX_REPLACE_NONE)
						जारी;

					अगर (!list_empty(&ctx->reserved_vअगरs))
						जारी;

					curr_ctx = ctx;
					अवरोध;
				पूर्ण
			पूर्ण

			/*
			 * If that's true then all available contexts alपढ़ोy
			 * have reservations and cannot be used.
			 */
			अगर (!curr_ctx ||
			    (curr_ctx->replace_state ==
			     IEEE80211_CHANCTX_WILL_BE_REPLACED) ||
			    !list_empty(&curr_ctx->reserved_vअगरs))
				वापस -EBUSY;

			new_ctx = ieee80211_alloc_chanctx(local, chandef, mode);
			अगर (!new_ctx)
				वापस -ENOMEM;

			new_ctx->replace_ctx = curr_ctx;
			new_ctx->replace_state =
					IEEE80211_CHANCTX_REPLACES_OTHER;

			curr_ctx->replace_ctx = new_ctx;
			curr_ctx->replace_state =
					IEEE80211_CHANCTX_WILL_BE_REPLACED;

			list_add_rcu(&new_ctx->list, &local->chanctx_list);
		पूर्ण
	पूर्ण

	list_add(&sdata->reserved_chanctx_list, &new_ctx->reserved_vअगरs);
	sdata->reserved_chanctx = new_ctx;
	sdata->reserved_chandef = *chandef;
	sdata->reserved_radar_required = radar_required;
	sdata->reserved_पढ़ोy = false;

	वापस 0;
पूर्ण

अटल व्योम
ieee80211_vअगर_chanctx_reservation_complete(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_OCB:
		ieee80211_queue_work(&sdata->local->hw,
				     &sdata->csa_finalize_work);
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		ieee80211_queue_work(&sdata->local->hw,
				     &sdata->u.mgd.chचयन_work);
		अवरोध;
	हाल NL80211_IFTYPE_UNSPECIFIED:
	हाल NL80211_IFTYPE_AP_VLAN:
	हाल NL80211_IFTYPE_WDS:
	हाल NL80211_IFTYPE_MONITOR:
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_P2P_GO:
	हाल NL80211_IFTYPE_P2P_DEVICE:
	हाल NL80211_IFTYPE_न_अंक:
	हाल NUM_NL80211_IFTYPES:
		WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
ieee80211_vअगर_update_chandef(काष्ठा ieee80211_sub_अगर_data *sdata,
			     स्थिर काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा ieee80211_sub_अगर_data *vlan;

	sdata->vअगर.bss_conf.chandef = *chandef;

	अगर (sdata->vअगर.type != NL80211_IFTYPE_AP)
		वापस;

	list_क्रम_each_entry(vlan, &sdata->u.ap.vlans, u.vlan.list)
		vlan->vअगर.bss_conf.chandef = *chandef;
पूर्ण

अटल पूर्णांक
ieee80211_vअगर_use_reserved_reassign(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_vअगर_chanctx_चयन vअगर_chsw[1] = अणुपूर्ण;
	काष्ठा ieee80211_chanctx *old_ctx, *new_ctx;
	स्थिर काष्ठा cfg80211_chan_def *chandef;
	u32 changed = 0;
	पूर्णांक err;

	lockdep_निश्चित_held(&local->mtx);
	lockdep_निश्चित_held(&local->chanctx_mtx);

	new_ctx = sdata->reserved_chanctx;
	old_ctx = ieee80211_vअगर_get_chanctx(sdata);

	अगर (WARN_ON(!sdata->reserved_पढ़ोy))
		वापस -EBUSY;

	अगर (WARN_ON(!new_ctx))
		वापस -EINVAL;

	अगर (WARN_ON(!old_ctx))
		वापस -EINVAL;

	अगर (WARN_ON(new_ctx->replace_state ==
		    IEEE80211_CHANCTX_REPLACES_OTHER))
		वापस -EINVAL;

	chandef = ieee80211_chanctx_non_reserved_chandef(local, new_ctx,
				&sdata->reserved_chandef);
	अगर (WARN_ON(!chandef))
		वापस -EINVAL;

	अगर (old_ctx->conf.def.width > new_ctx->conf.def.width)
		ieee80211_chan_bw_change(local, new_ctx);

	ieee80211_change_chanctx(local, new_ctx, chandef);

	अगर (old_ctx->conf.def.width < new_ctx->conf.def.width)
		ieee80211_chan_bw_change(local, new_ctx);

	vअगर_chsw[0].vअगर = &sdata->vअगर;
	vअगर_chsw[0].old_ctx = &old_ctx->conf;
	vअगर_chsw[0].new_ctx = &new_ctx->conf;

	list_del(&sdata->reserved_chanctx_list);
	sdata->reserved_chanctx = शून्य;

	err = drv_चयन_vअगर_chanctx(local, vअगर_chsw, 1,
				     CHANCTX_SWMODE_REASSIGN_VIF);
	अगर (err) अणु
		अगर (ieee80211_chanctx_refcount(local, new_ctx) == 0)
			ieee80211_मुक्त_chanctx(local, new_ctx);

		जाओ out;
	पूर्ण

	list_move(&sdata->asचिन्हित_chanctx_list, &new_ctx->asचिन्हित_vअगरs);
	rcu_assign_poपूर्णांकer(sdata->vअगर.chanctx_conf, &new_ctx->conf);

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP)
		__ieee80211_vअगर_copy_chanctx_to_vlans(sdata, false);

	ieee80211_check_fast_xmit_अगरace(sdata);

	अगर (ieee80211_chanctx_refcount(local, old_ctx) == 0)
		ieee80211_मुक्त_chanctx(local, old_ctx);

	अगर (sdata->vअगर.bss_conf.chandef.width != sdata->reserved_chandef.width)
		changed = BSS_CHANGED_BANDWIDTH;

	ieee80211_vअगर_update_chandef(sdata, &sdata->reserved_chandef);

	ieee80211_recalc_smps_chanctx(local, new_ctx);
	ieee80211_recalc_radar_chanctx(local, new_ctx);
	ieee80211_recalc_chanctx_min_def(local, new_ctx);

	अगर (changed)
		ieee80211_bss_info_change_notअगरy(sdata, changed);

out:
	ieee80211_vअगर_chanctx_reservation_complete(sdata);
	वापस err;
पूर्ण

अटल पूर्णांक
ieee80211_vअगर_use_reserved_assign(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_chanctx *old_ctx, *new_ctx;
	स्थिर काष्ठा cfg80211_chan_def *chandef;
	पूर्णांक err;

	old_ctx = ieee80211_vअगर_get_chanctx(sdata);
	new_ctx = sdata->reserved_chanctx;

	अगर (WARN_ON(!sdata->reserved_पढ़ोy))
		वापस -EINVAL;

	अगर (WARN_ON(old_ctx))
		वापस -EINVAL;

	अगर (WARN_ON(!new_ctx))
		वापस -EINVAL;

	अगर (WARN_ON(new_ctx->replace_state ==
		    IEEE80211_CHANCTX_REPLACES_OTHER))
		वापस -EINVAL;

	chandef = ieee80211_chanctx_non_reserved_chandef(local, new_ctx,
				&sdata->reserved_chandef);
	अगर (WARN_ON(!chandef))
		वापस -EINVAL;

	ieee80211_change_chanctx(local, new_ctx, chandef);

	list_del(&sdata->reserved_chanctx_list);
	sdata->reserved_chanctx = शून्य;

	err = ieee80211_assign_vअगर_chanctx(sdata, new_ctx);
	अगर (err) अणु
		अगर (ieee80211_chanctx_refcount(local, new_ctx) == 0)
			ieee80211_मुक्त_chanctx(local, new_ctx);

		जाओ out;
	पूर्ण

out:
	ieee80211_vअगर_chanctx_reservation_complete(sdata);
	वापस err;
पूर्ण

अटल bool
ieee80211_vअगर_has_in_place_reservation(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_chanctx *old_ctx, *new_ctx;

	lockdep_निश्चित_held(&sdata->local->chanctx_mtx);

	new_ctx = sdata->reserved_chanctx;
	old_ctx = ieee80211_vअगर_get_chanctx(sdata);

	अगर (!old_ctx)
		वापस false;

	अगर (WARN_ON(!new_ctx))
		वापस false;

	अगर (old_ctx->replace_state != IEEE80211_CHANCTX_WILL_BE_REPLACED)
		वापस false;

	अगर (new_ctx->replace_state != IEEE80211_CHANCTX_REPLACES_OTHER)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक ieee80211_chsw_चयन_hwconf(काष्ठा ieee80211_local *local,
					काष्ठा ieee80211_chanctx *new_ctx)
अणु
	स्थिर काष्ठा cfg80211_chan_def *chandef;

	lockdep_निश्चित_held(&local->mtx);
	lockdep_निश्चित_held(&local->chanctx_mtx);

	chandef = ieee80211_chanctx_reserved_chandef(local, new_ctx, शून्य);
	अगर (WARN_ON(!chandef))
		वापस -EINVAL;

	local->hw.conf.radar_enabled = new_ctx->conf.radar_enabled;
	local->_oper_chandef = *chandef;
	ieee80211_hw_config(local, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_chsw_चयन_vअगरs(काष्ठा ieee80211_local *local,
				      पूर्णांक n_vअगरs)
अणु
	काष्ठा ieee80211_vअगर_chanctx_चयन *vअगर_chsw;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा ieee80211_chanctx *ctx, *old_ctx;
	पूर्णांक i, err;

	lockdep_निश्चित_held(&local->mtx);
	lockdep_निश्चित_held(&local->chanctx_mtx);

	vअगर_chsw = kसुस्मृति(n_vअगरs, माप(vअगर_chsw[0]), GFP_KERNEL);
	अगर (!vअगर_chsw)
		वापस -ENOMEM;

	i = 0;
	list_क्रम_each_entry(ctx, &local->chanctx_list, list) अणु
		अगर (ctx->replace_state != IEEE80211_CHANCTX_REPLACES_OTHER)
			जारी;

		अगर (WARN_ON(!ctx->replace_ctx)) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		list_क्रम_each_entry(sdata, &ctx->reserved_vअगरs,
				    reserved_chanctx_list) अणु
			अगर (!ieee80211_vअगर_has_in_place_reservation(
					sdata))
				जारी;

			old_ctx = ieee80211_vअगर_get_chanctx(sdata);
			vअगर_chsw[i].vअगर = &sdata->vअगर;
			vअगर_chsw[i].old_ctx = &old_ctx->conf;
			vअगर_chsw[i].new_ctx = &ctx->conf;

			i++;
		पूर्ण
	पूर्ण

	err = drv_चयन_vअगर_chanctx(local, vअगर_chsw, n_vअगरs,
				     CHANCTX_SWMODE_SWAP_CONTEXTS);

out:
	kमुक्त(vअगर_chsw);
	वापस err;
पूर्ण

अटल पूर्णांक ieee80211_chsw_चयन_ctxs(काष्ठा ieee80211_local *local)
अणु
	काष्ठा ieee80211_chanctx *ctx;
	पूर्णांक err;

	lockdep_निश्चित_held(&local->mtx);
	lockdep_निश्चित_held(&local->chanctx_mtx);

	list_क्रम_each_entry(ctx, &local->chanctx_list, list) अणु
		अगर (ctx->replace_state != IEEE80211_CHANCTX_REPLACES_OTHER)
			जारी;

		अगर (!list_empty(&ctx->replace_ctx->asचिन्हित_vअगरs))
			जारी;

		ieee80211_del_chanctx(local, ctx->replace_ctx);
		err = ieee80211_add_chanctx(local, ctx);
		अगर (err)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	WARN_ON(ieee80211_add_chanctx(local, ctx));
	list_क्रम_each_entry_जारी_reverse(ctx, &local->chanctx_list, list) अणु
		अगर (ctx->replace_state != IEEE80211_CHANCTX_REPLACES_OTHER)
			जारी;

		अगर (!list_empty(&ctx->replace_ctx->asचिन्हित_vअगरs))
			जारी;

		ieee80211_del_chanctx(local, ctx);
		WARN_ON(ieee80211_add_chanctx(local, ctx->replace_ctx));
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ieee80211_vअगर_use_reserved_चयन(काष्ठा ieee80211_local *local)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata, *sdata_पंचांगp;
	काष्ठा ieee80211_chanctx *ctx, *ctx_पंचांगp, *old_ctx;
	काष्ठा ieee80211_chanctx *new_ctx = शून्य;
	पूर्णांक err, n_asचिन्हित, n_reserved, n_पढ़ोy;
	पूर्णांक n_ctx = 0, n_vअगरs_चयन = 0, n_vअगरs_assign = 0, n_vअगरs_ctxless = 0;

	lockdep_निश्चित_held(&local->mtx);
	lockdep_निश्चित_held(&local->chanctx_mtx);

	/*
	 * If there are 2 independent pairs of channel contexts perक्रमming
	 * cross-चयन of their vअगरs this code will still रुको until both are
	 * पढ़ोy even though it could be possible to चयन one beक्रमe the
	 * other is पढ़ोy.
	 *
	 * For practical reasons and code simplicity just करो a single huge
	 * चयन.
	 */

	/*
	 * Verअगरy अगर the reservation is still feasible.
	 *  - अगर it's not then disconnect
	 *  - अगर it is but not all vअगरs necessary are पढ़ोy then defer
	 */

	list_क्रम_each_entry(ctx, &local->chanctx_list, list) अणु
		अगर (ctx->replace_state != IEEE80211_CHANCTX_REPLACES_OTHER)
			जारी;

		अगर (WARN_ON(!ctx->replace_ctx)) अणु
			err = -EINVAL;
			जाओ err;
		पूर्ण

		अगर (!local->use_chanctx)
			new_ctx = ctx;

		n_ctx++;

		n_asचिन्हित = 0;
		n_reserved = 0;
		n_पढ़ोy = 0;

		list_क्रम_each_entry(sdata, &ctx->replace_ctx->asचिन्हित_vअगरs,
				    asचिन्हित_chanctx_list) अणु
			n_asचिन्हित++;
			अगर (sdata->reserved_chanctx) अणु
				n_reserved++;
				अगर (sdata->reserved_पढ़ोy)
					n_पढ़ोy++;
			पूर्ण
		पूर्ण

		अगर (n_asचिन्हित != n_reserved) अणु
			अगर (n_पढ़ोy == n_reserved) अणु
				wiphy_info(local->hw.wiphy,
					   "channel context reservation cannot be finalized because some interfaces aren't switching\n");
				err = -EBUSY;
				जाओ err;
			पूर्ण

			वापस -EAGAIN;
		पूर्ण

		ctx->conf.radar_enabled = false;
		list_क्रम_each_entry(sdata, &ctx->reserved_vअगरs,
				    reserved_chanctx_list) अणु
			अगर (ieee80211_vअगर_has_in_place_reservation(sdata) &&
			    !sdata->reserved_पढ़ोy)
				वापस -EAGAIN;

			old_ctx = ieee80211_vअगर_get_chanctx(sdata);
			अगर (old_ctx) अणु
				अगर (old_ctx->replace_state ==
				    IEEE80211_CHANCTX_WILL_BE_REPLACED)
					n_vअगरs_चयन++;
				अन्यथा
					n_vअगरs_assign++;
			पूर्ण अन्यथा अणु
				n_vअगरs_ctxless++;
			पूर्ण

			अगर (sdata->reserved_radar_required)
				ctx->conf.radar_enabled = true;
		पूर्ण
	पूर्ण

	अगर (WARN_ON(n_ctx == 0) ||
	    WARN_ON(n_vअगरs_चयन == 0 &&
		    n_vअगरs_assign == 0 &&
		    n_vअगरs_ctxless == 0) ||
	    WARN_ON(n_ctx > 1 && !local->use_chanctx) ||
	    WARN_ON(!new_ctx && !local->use_chanctx)) अणु
		err = -EINVAL;
		जाओ err;
	पूर्ण

	/*
	 * All necessary vअगरs are पढ़ोy. Perक्रमm the चयन now depending on
	 * reservations and driver capabilities.
	 */

	अगर (local->use_chanctx) अणु
		अगर (n_vअगरs_चयन > 0) अणु
			err = ieee80211_chsw_चयन_vअगरs(local, n_vअगरs_चयन);
			अगर (err)
				जाओ err;
		पूर्ण

		अगर (n_vअगरs_assign > 0 || n_vअगरs_ctxless > 0) अणु
			err = ieee80211_chsw_चयन_ctxs(local);
			अगर (err)
				जाओ err;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = ieee80211_chsw_चयन_hwconf(local, new_ctx);
		अगर (err)
			जाओ err;
	पूर्ण

	/*
	 * Update all काष्ठाures, values and poपूर्णांकers to poपूर्णांक to new channel
	 * context(s).
	 */
	list_क्रम_each_entry(ctx, &local->chanctx_list, list) अणु
		अगर (ctx->replace_state != IEEE80211_CHANCTX_REPLACES_OTHER)
			जारी;

		अगर (WARN_ON(!ctx->replace_ctx)) अणु
			err = -EINVAL;
			जाओ err;
		पूर्ण

		list_क्रम_each_entry(sdata, &ctx->reserved_vअगरs,
				    reserved_chanctx_list) अणु
			u32 changed = 0;

			अगर (!ieee80211_vअगर_has_in_place_reservation(sdata))
				जारी;

			rcu_assign_poपूर्णांकer(sdata->vअगर.chanctx_conf, &ctx->conf);

			अगर (sdata->vअगर.type == NL80211_IFTYPE_AP)
				__ieee80211_vअगर_copy_chanctx_to_vlans(sdata,
								      false);

			ieee80211_check_fast_xmit_अगरace(sdata);

			sdata->radar_required = sdata->reserved_radar_required;

			अगर (sdata->vअगर.bss_conf.chandef.width !=
			    sdata->reserved_chandef.width)
				changed = BSS_CHANGED_BANDWIDTH;

			ieee80211_vअगर_update_chandef(sdata, &sdata->reserved_chandef);
			अगर (changed)
				ieee80211_bss_info_change_notअगरy(sdata,
								 changed);

			ieee80211_recalc_txघातer(sdata, false);
		पूर्ण

		ieee80211_recalc_chanctx_chantype(local, ctx);
		ieee80211_recalc_smps_chanctx(local, ctx);
		ieee80211_recalc_radar_chanctx(local, ctx);
		ieee80211_recalc_chanctx_min_def(local, ctx);
		ieee80211_chan_bw_change(local, ctx);

		list_क्रम_each_entry_safe(sdata, sdata_पंचांगp, &ctx->reserved_vअगरs,
					 reserved_chanctx_list) अणु
			अगर (ieee80211_vअगर_get_chanctx(sdata) != ctx)
				जारी;

			list_del(&sdata->reserved_chanctx_list);
			list_move(&sdata->asचिन्हित_chanctx_list,
				  &ctx->asचिन्हित_vअगरs);
			sdata->reserved_chanctx = शून्य;

			ieee80211_vअगर_chanctx_reservation_complete(sdata);
		पूर्ण

		/*
		 * This context might have been a dependency क्रम an alपढ़ोy
		 * पढ़ोy re-assign reservation पूर्णांकerface that was deferred. Do
		 * not propagate error to the caller though. The in-place
		 * reservation क्रम originally requested पूर्णांकerface has alपढ़ोy
		 * succeeded at this poपूर्णांक.
		 */
		list_क्रम_each_entry_safe(sdata, sdata_पंचांगp, &ctx->reserved_vअगरs,
					 reserved_chanctx_list) अणु
			अगर (WARN_ON(ieee80211_vअगर_has_in_place_reservation(
					sdata)))
				जारी;

			अगर (WARN_ON(sdata->reserved_chanctx != ctx))
				जारी;

			अगर (!sdata->reserved_पढ़ोy)
				जारी;

			अगर (ieee80211_vअगर_get_chanctx(sdata))
				err = ieee80211_vअगर_use_reserved_reassign(
						sdata);
			अन्यथा
				err = ieee80211_vअगर_use_reserved_assign(sdata);

			अगर (err) अणु
				sdata_info(sdata,
					   "failed to finalize (re-)assign reservation (err=%d)\n",
					   err);
				ieee80211_vअगर_unreserve_chanctx(sdata);
				cfg80211_stop_अगरace(local->hw.wiphy,
						    &sdata->wdev,
						    GFP_KERNEL);
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Finally मुक्त old contexts
	 */

	list_क्रम_each_entry_safe(ctx, ctx_पंचांगp, &local->chanctx_list, list) अणु
		अगर (ctx->replace_state != IEEE80211_CHANCTX_WILL_BE_REPLACED)
			जारी;

		ctx->replace_ctx->replace_ctx = शून्य;
		ctx->replace_ctx->replace_state =
				IEEE80211_CHANCTX_REPLACE_NONE;

		list_del_rcu(&ctx->list);
		kमुक्त_rcu(ctx, rcu_head);
	पूर्ण

	वापस 0;

err:
	list_क्रम_each_entry(ctx, &local->chanctx_list, list) अणु
		अगर (ctx->replace_state != IEEE80211_CHANCTX_REPLACES_OTHER)
			जारी;

		list_क्रम_each_entry_safe(sdata, sdata_पंचांगp, &ctx->reserved_vअगरs,
					 reserved_chanctx_list) अणु
			ieee80211_vअगर_unreserve_chanctx(sdata);
			ieee80211_vअगर_chanctx_reservation_complete(sdata);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम __ieee80211_vअगर_release_channel(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_chanctx_conf *conf;
	काष्ठा ieee80211_chanctx *ctx;
	bool use_reserved_चयन = false;

	lockdep_निश्चित_held(&local->chanctx_mtx);

	conf = rcu_dereference_रक्षित(sdata->vअगर.chanctx_conf,
					 lockdep_is_held(&local->chanctx_mtx));
	अगर (!conf)
		वापस;

	ctx = container_of(conf, काष्ठा ieee80211_chanctx, conf);

	अगर (sdata->reserved_chanctx) अणु
		अगर (sdata->reserved_chanctx->replace_state ==
		    IEEE80211_CHANCTX_REPLACES_OTHER &&
		    ieee80211_chanctx_num_reserved(local,
						   sdata->reserved_chanctx) > 1)
			use_reserved_चयन = true;

		ieee80211_vअगर_unreserve_chanctx(sdata);
	पूर्ण

	ieee80211_assign_vअगर_chanctx(sdata, शून्य);
	अगर (ieee80211_chanctx_refcount(local, ctx) == 0)
		ieee80211_मुक्त_chanctx(local, ctx);

	sdata->radar_required = false;

	/* Unreserving may पढ़ोy an in-place reservation. */
	अगर (use_reserved_चयन)
		ieee80211_vअगर_use_reserved_चयन(local);
पूर्ण

पूर्णांक ieee80211_vअगर_use_channel(काष्ठा ieee80211_sub_अगर_data *sdata,
			      स्थिर काष्ठा cfg80211_chan_def *chandef,
			      क्रमागत ieee80211_chanctx_mode mode)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_chanctx *ctx;
	u8 radar_detect_width = 0;
	पूर्णांक ret;

	lockdep_निश्चित_held(&local->mtx);

	WARN_ON(sdata->dev && netअगर_carrier_ok(sdata->dev));

	mutex_lock(&local->chanctx_mtx);

	ret = cfg80211_chandef_dfs_required(local->hw.wiphy,
					    chandef,
					    sdata->wdev.अगरtype);
	अगर (ret < 0)
		जाओ out;
	अगर (ret > 0)
		radar_detect_width = BIT(chandef->width);

	sdata->radar_required = ret;

	ret = ieee80211_check_combinations(sdata, chandef, mode,
					   radar_detect_width);
	अगर (ret < 0)
		जाओ out;

	__ieee80211_vअगर_release_channel(sdata);

	ctx = ieee80211_find_chanctx(local, chandef, mode);
	अगर (!ctx)
		ctx = ieee80211_new_chanctx(local, chandef, mode);
	अगर (IS_ERR(ctx)) अणु
		ret = PTR_ERR(ctx);
		जाओ out;
	पूर्ण

	ieee80211_vअगर_update_chandef(sdata, chandef);

	ret = ieee80211_assign_vअगर_chanctx(sdata, ctx);
	अगर (ret) अणु
		/* अगर assign fails refcount stays the same */
		अगर (ieee80211_chanctx_refcount(local, ctx) == 0)
			ieee80211_मुक्त_chanctx(local, ctx);
		जाओ out;
	पूर्ण

	ieee80211_recalc_smps_chanctx(local, ctx);
	ieee80211_recalc_radar_chanctx(local, ctx);
 out:
	अगर (ret)
		sdata->radar_required = false;

	mutex_unlock(&local->chanctx_mtx);
	वापस ret;
पूर्ण

पूर्णांक ieee80211_vअगर_use_reserved_context(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_chanctx *new_ctx;
	काष्ठा ieee80211_chanctx *old_ctx;
	पूर्णांक err;

	lockdep_निश्चित_held(&local->mtx);
	lockdep_निश्चित_held(&local->chanctx_mtx);

	new_ctx = sdata->reserved_chanctx;
	old_ctx = ieee80211_vअगर_get_chanctx(sdata);

	अगर (WARN_ON(!new_ctx))
		वापस -EINVAL;

	अगर (WARN_ON(new_ctx->replace_state ==
		    IEEE80211_CHANCTX_WILL_BE_REPLACED))
		वापस -EINVAL;

	अगर (WARN_ON(sdata->reserved_पढ़ोy))
		वापस -EINVAL;

	sdata->reserved_पढ़ोy = true;

	अगर (new_ctx->replace_state == IEEE80211_CHANCTX_REPLACE_NONE) अणु
		अगर (old_ctx)
			err = ieee80211_vअगर_use_reserved_reassign(sdata);
		अन्यथा
			err = ieee80211_vअगर_use_reserved_assign(sdata);

		अगर (err)
			वापस err;
	पूर्ण

	/*
	 * In-place reservation may need to be finalized now either अगर:
	 *  a) sdata is taking part in the swapping itself and is the last one
	 *  b) sdata has चयनed with a re-assign reservation to an existing
	 *     context पढ़ोying in-place चयनing of old_ctx
	 *
	 * In हाल of (b) करो not propagate the error up because the requested
	 * sdata alपढ़ोy चयनed successfully. Just spill an extra warning.
	 * The ieee80211_vअगर_use_reserved_चयन() alपढ़ोy stops all necessary
	 * पूर्णांकerfaces upon failure.
	 */
	अगर ((old_ctx &&
	     old_ctx->replace_state == IEEE80211_CHANCTX_WILL_BE_REPLACED) ||
	    new_ctx->replace_state == IEEE80211_CHANCTX_REPLACES_OTHER) अणु
		err = ieee80211_vअगर_use_reserved_चयन(local);
		अगर (err && err != -EAGAIN) अणु
			अगर (new_ctx->replace_state ==
			    IEEE80211_CHANCTX_REPLACES_OTHER)
				वापस err;

			wiphy_info(local->hw.wiphy,
				   "depending in-place reservation failed (err=%d)\n",
				   err);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ieee80211_vअगर_change_bandwidth(काष्ठा ieee80211_sub_अगर_data *sdata,
				   स्थिर काष्ठा cfg80211_chan_def *chandef,
				   u32 *changed)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_chanctx_conf *conf;
	काष्ठा ieee80211_chanctx *ctx;
	स्थिर काष्ठा cfg80211_chan_def *compat;
	पूर्णांक ret;

	अगर (!cfg80211_chandef_usable(sdata->local->hw.wiphy, chandef,
				     IEEE80211_CHAN_DISABLED))
		वापस -EINVAL;

	mutex_lock(&local->chanctx_mtx);
	अगर (cfg80211_chandef_identical(chandef, &sdata->vअगर.bss_conf.chandef)) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	अगर (chandef->width == NL80211_CHAN_WIDTH_20_NOHT ||
	    sdata->vअगर.bss_conf.chandef.width == NL80211_CHAN_WIDTH_20_NOHT) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	conf = rcu_dereference_रक्षित(sdata->vअगर.chanctx_conf,
					 lockdep_is_held(&local->chanctx_mtx));
	अगर (!conf) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ctx = container_of(conf, काष्ठा ieee80211_chanctx, conf);

	compat = cfg80211_chandef_compatible(&conf->def, chandef);
	अगर (!compat) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	चयन (ctx->replace_state) अणु
	हाल IEEE80211_CHANCTX_REPLACE_NONE:
		अगर (!ieee80211_chanctx_reserved_chandef(local, ctx, compat)) अणु
			ret = -EBUSY;
			जाओ out;
		पूर्ण
		अवरोध;
	हाल IEEE80211_CHANCTX_WILL_BE_REPLACED:
		/* TODO: Perhaps the bandwidth change could be treated as a
		 * reservation itself? */
		ret = -EBUSY;
		जाओ out;
	हाल IEEE80211_CHANCTX_REPLACES_OTHER:
		/* channel context that is going to replace another channel
		 * context करोesn't really exist and shouldn't be asचिन्हित
		 * anywhere yet */
		WARN_ON(1);
		अवरोध;
	पूर्ण

	ieee80211_vअगर_update_chandef(sdata, chandef);

	ieee80211_recalc_chanctx_chantype(local, ctx);

	*changed |= BSS_CHANGED_BANDWIDTH;
	ret = 0;
 out:
	mutex_unlock(&local->chanctx_mtx);
	वापस ret;
पूर्ण

व्योम ieee80211_vअगर_release_channel(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	WARN_ON(sdata->dev && netअगर_carrier_ok(sdata->dev));

	lockdep_निश्चित_held(&sdata->local->mtx);

	mutex_lock(&sdata->local->chanctx_mtx);
	__ieee80211_vअगर_release_channel(sdata);
	mutex_unlock(&sdata->local->chanctx_mtx);
पूर्ण

व्योम ieee80211_vअगर_vlan_copy_chanctx(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_sub_अगर_data *ap;
	काष्ठा ieee80211_chanctx_conf *conf;

	अगर (WARN_ON(sdata->vअगर.type != NL80211_IFTYPE_AP_VLAN || !sdata->bss))
		वापस;

	ap = container_of(sdata->bss, काष्ठा ieee80211_sub_अगर_data, u.ap);

	mutex_lock(&local->chanctx_mtx);

	conf = rcu_dereference_रक्षित(ap->vअगर.chanctx_conf,
					 lockdep_is_held(&local->chanctx_mtx));
	rcu_assign_poपूर्णांकer(sdata->vअगर.chanctx_conf, conf);
	mutex_unlock(&local->chanctx_mtx);
पूर्ण

व्योम ieee80211_iter_chan_contexts_atomic(
	काष्ठा ieee80211_hw *hw,
	व्योम (*iter)(काष्ठा ieee80211_hw *hw,
		     काष्ठा ieee80211_chanctx_conf *chanctx_conf,
		     व्योम *data),
	व्योम *iter_data)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा ieee80211_chanctx *ctx;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(ctx, &local->chanctx_list, list)
		अगर (ctx->driver_present)
			iter(hw, &ctx->conf, iter_data);
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(ieee80211_iter_chan_contexts_atomic);
