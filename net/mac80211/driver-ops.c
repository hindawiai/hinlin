<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2015 Intel Deutschland GmbH
 */
#समावेश <net/mac80211.h>
#समावेश "ieee80211_i.h"
#समावेश "trace.h"
#समावेश "driver-ops.h"

पूर्णांक drv_start(काष्ठा ieee80211_local *local)
अणु
	पूर्णांक ret;

	might_sleep();

	अगर (WARN_ON(local->started))
		वापस -EALREADY;

	trace_drv_start(local);
	local->started = true;
	/* allow rx frames */
	smp_mb();
	ret = local->ops->start(&local->hw);
	trace_drv_वापस_पूर्णांक(local, ret);

	अगर (ret)
		local->started = false;

	वापस ret;
पूर्ण

व्योम drv_stop(काष्ठा ieee80211_local *local)
अणु
	might_sleep();

	अगर (WARN_ON(!local->started))
		वापस;

	trace_drv_stop(local);
	local->ops->stop(&local->hw);
	trace_drv_वापस_व्योम(local);

	/* sync away all work on the tasklet beक्रमe clearing started */
	tasklet_disable(&local->tasklet);
	tasklet_enable(&local->tasklet);

	barrier();

	local->started = false;
पूर्ण

पूर्णांक drv_add_पूर्णांकerface(काष्ठा ieee80211_local *local,
		      काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	पूर्णांक ret;

	might_sleep();

	अगर (WARN_ON(sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN ||
		    (sdata->vअगर.type == NL80211_IFTYPE_MONITOR &&
		     !ieee80211_hw_check(&local->hw, WANT_MONITOR_VIF) &&
		     !(sdata->u.mntr.flags & MONITOR_FLAG_ACTIVE))))
		वापस -EINVAL;

	trace_drv_add_पूर्णांकerface(local, sdata);
	ret = local->ops->add_पूर्णांकerface(&local->hw, &sdata->vअगर);
	trace_drv_वापस_पूर्णांक(local, ret);

	अगर (ret == 0)
		sdata->flags |= IEEE80211_SDATA_IN_DRIVER;

	वापस ret;
पूर्ण

पूर्णांक drv_change_पूर्णांकerface(काष्ठा ieee80211_local *local,
			 काष्ठा ieee80211_sub_अगर_data *sdata,
			 क्रमागत nl80211_अगरtype type, bool p2p)
अणु
	पूर्णांक ret;

	might_sleep();

	अगर (!check_sdata_in_driver(sdata))
		वापस -EIO;

	trace_drv_change_पूर्णांकerface(local, sdata, type, p2p);
	ret = local->ops->change_पूर्णांकerface(&local->hw, &sdata->vअगर, type, p2p);
	trace_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

व्योम drv_हटाओ_पूर्णांकerface(काष्ठा ieee80211_local *local,
			  काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	might_sleep();

	अगर (!check_sdata_in_driver(sdata))
		वापस;

	trace_drv_हटाओ_पूर्णांकerface(local, sdata);
	local->ops->हटाओ_पूर्णांकerface(&local->hw, &sdata->vअगर);
	sdata->flags &= ~IEEE80211_SDATA_IN_DRIVER;
	trace_drv_वापस_व्योम(local);
पूर्ण

__must_check
पूर्णांक drv_sta_state(काष्ठा ieee80211_local *local,
		  काष्ठा ieee80211_sub_अगर_data *sdata,
		  काष्ठा sta_info *sta,
		  क्रमागत ieee80211_sta_state old_state,
		  क्रमागत ieee80211_sta_state new_state)
अणु
	पूर्णांक ret = 0;

	might_sleep();

	sdata = get_bss_sdata(sdata);
	अगर (!check_sdata_in_driver(sdata))
		वापस -EIO;

	trace_drv_sta_state(local, sdata, &sta->sta, old_state, new_state);
	अगर (local->ops->sta_state) अणु
		ret = local->ops->sta_state(&local->hw, &sdata->vअगर, &sta->sta,
					    old_state, new_state);
	पूर्ण अन्यथा अगर (old_state == IEEE80211_STA_AUTH &&
		   new_state == IEEE80211_STA_ASSOC) अणु
		ret = drv_sta_add(local, sdata, &sta->sta);
		अगर (ret == 0) अणु
			sta->uploaded = true;
			अगर (rcu_access_poपूर्णांकer(sta->sta.rates))
				drv_sta_rate_tbl_update(local, sdata, &sta->sta);
		पूर्ण
	पूर्ण अन्यथा अगर (old_state == IEEE80211_STA_ASSOC &&
		   new_state == IEEE80211_STA_AUTH) अणु
		drv_sta_हटाओ(local, sdata, &sta->sta);
	पूर्ण
	trace_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

__must_check
पूर्णांक drv_sta_set_txpwr(काष्ठा ieee80211_local *local,
		      काष्ठा ieee80211_sub_अगर_data *sdata,
		      काष्ठा sta_info *sta)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	might_sleep();

	sdata = get_bss_sdata(sdata);
	अगर (!check_sdata_in_driver(sdata))
		वापस -EIO;

	trace_drv_sta_set_txpwr(local, sdata, &sta->sta);
	अगर (local->ops->sta_set_txpwr)
		ret = local->ops->sta_set_txpwr(&local->hw, &sdata->vअगर,
						&sta->sta);
	trace_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

व्योम drv_sta_rc_update(काष्ठा ieee80211_local *local,
		       काष्ठा ieee80211_sub_अगर_data *sdata,
		       काष्ठा ieee80211_sta *sta, u32 changed)
अणु
	sdata = get_bss_sdata(sdata);
	अगर (!check_sdata_in_driver(sdata))
		वापस;

	WARN_ON(changed & IEEE80211_RC_SUPP_RATES_CHANGED &&
		(sdata->vअगर.type != NL80211_IFTYPE_ADHOC &&
		 sdata->vअगर.type != NL80211_IFTYPE_MESH_POINT));

	trace_drv_sta_rc_update(local, sdata, sta, changed);
	अगर (local->ops->sta_rc_update)
		local->ops->sta_rc_update(&local->hw, &sdata->vअगर,
					  sta, changed);

	trace_drv_वापस_व्योम(local);
पूर्ण

पूर्णांक drv_conf_tx(काष्ठा ieee80211_local *local,
		काष्ठा ieee80211_sub_अगर_data *sdata, u16 ac,
		स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	might_sleep();

	अगर (!check_sdata_in_driver(sdata))
		वापस -EIO;

	अगर (params->cw_min == 0 || params->cw_min > params->cw_max) अणु
		/*
		 * If we can't configure hardware anyway, don't warn. We may
		 * never have initialized the CW parameters.
		 */
		WARN_ONCE(local->ops->conf_tx,
			  "%s: invalid CW_min/CW_max: %d/%d\n",
			  sdata->name, params->cw_min, params->cw_max);
		वापस -EINVAL;
	पूर्ण

	trace_drv_conf_tx(local, sdata, ac, params);
	अगर (local->ops->conf_tx)
		ret = local->ops->conf_tx(&local->hw, &sdata->vअगर,
					  ac, params);
	trace_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

u64 drv_get_tsf(काष्ठा ieee80211_local *local,
		काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	u64 ret = -1ULL;

	might_sleep();

	अगर (!check_sdata_in_driver(sdata))
		वापस ret;

	trace_drv_get_tsf(local, sdata);
	अगर (local->ops->get_tsf)
		ret = local->ops->get_tsf(&local->hw, &sdata->vअगर);
	trace_drv_वापस_u64(local, ret);
	वापस ret;
पूर्ण

व्योम drv_set_tsf(काष्ठा ieee80211_local *local,
		 काष्ठा ieee80211_sub_अगर_data *sdata,
		 u64 tsf)
अणु
	might_sleep();

	अगर (!check_sdata_in_driver(sdata))
		वापस;

	trace_drv_set_tsf(local, sdata, tsf);
	अगर (local->ops->set_tsf)
		local->ops->set_tsf(&local->hw, &sdata->vअगर, tsf);
	trace_drv_वापस_व्योम(local);
पूर्ण

व्योम drv_offset_tsf(काष्ठा ieee80211_local *local,
		    काष्ठा ieee80211_sub_अगर_data *sdata,
		    s64 offset)
अणु
	might_sleep();

	अगर (!check_sdata_in_driver(sdata))
		वापस;

	trace_drv_offset_tsf(local, sdata, offset);
	अगर (local->ops->offset_tsf)
		local->ops->offset_tsf(&local->hw, &sdata->vअगर, offset);
	trace_drv_वापस_व्योम(local);
पूर्ण

व्योम drv_reset_tsf(काष्ठा ieee80211_local *local,
		   काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	might_sleep();

	अगर (!check_sdata_in_driver(sdata))
		वापस;

	trace_drv_reset_tsf(local, sdata);
	अगर (local->ops->reset_tsf)
		local->ops->reset_tsf(&local->hw, &sdata->vअगर);
	trace_drv_वापस_व्योम(local);
पूर्ण

पूर्णांक drv_चयन_vअगर_chanctx(काष्ठा ieee80211_local *local,
			   काष्ठा ieee80211_vअगर_chanctx_चयन *vअगरs,
			   पूर्णांक n_vअगरs, क्रमागत ieee80211_chanctx_चयन_mode mode)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	might_sleep();

	अगर (!local->ops->चयन_vअगर_chanctx)
		वापस -EOPNOTSUPP;

	क्रम (i = 0; i < n_vअगरs; i++) अणु
		काष्ठा ieee80211_chanctx *new_ctx =
			container_of(vअगरs[i].new_ctx,
				     काष्ठा ieee80211_chanctx,
				     conf);
		काष्ठा ieee80211_chanctx *old_ctx =
			container_of(vअगरs[i].old_ctx,
				     काष्ठा ieee80211_chanctx,
				     conf);

		WARN_ON_ONCE(!old_ctx->driver_present);
		WARN_ON_ONCE((mode == CHANCTX_SWMODE_SWAP_CONTEXTS &&
			      new_ctx->driver_present) ||
			     (mode == CHANCTX_SWMODE_REASSIGN_VIF &&
			      !new_ctx->driver_present));
	पूर्ण

	trace_drv_चयन_vअगर_chanctx(local, vअगरs, n_vअगरs, mode);
	ret = local->ops->चयन_vअगर_chanctx(&local->hw,
					     vअगरs, n_vअगरs, mode);
	trace_drv_वापस_पूर्णांक(local, ret);

	अगर (!ret && mode == CHANCTX_SWMODE_SWAP_CONTEXTS) अणु
		क्रम (i = 0; i < n_vअगरs; i++) अणु
			काष्ठा ieee80211_chanctx *new_ctx =
				container_of(vअगरs[i].new_ctx,
					     काष्ठा ieee80211_chanctx,
					     conf);
			काष्ठा ieee80211_chanctx *old_ctx =
				container_of(vअगरs[i].old_ctx,
					     काष्ठा ieee80211_chanctx,
					     conf);

			new_ctx->driver_present = true;
			old_ctx->driver_present = false;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक drv_ampdu_action(काष्ठा ieee80211_local *local,
		     काष्ठा ieee80211_sub_अगर_data *sdata,
		     काष्ठा ieee80211_ampdu_params *params)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	might_sleep();

	sdata = get_bss_sdata(sdata);
	अगर (!check_sdata_in_driver(sdata))
		वापस -EIO;

	trace_drv_ampdu_action(local, sdata, params);

	अगर (local->ops->ampdu_action)
		ret = local->ops->ampdu_action(&local->hw, &sdata->vअगर, params);

	trace_drv_वापस_पूर्णांक(local, ret);

	वापस ret;
पूर्ण
