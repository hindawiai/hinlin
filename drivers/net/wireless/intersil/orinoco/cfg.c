<शैली गुरु>
/* cfg80211 support
 *
 * See copyright notice in मुख्य.c
 */
#समावेश <linux/ieee80211.h>
#समावेश <net/cfg80211.h>
#समावेश "hw.h"
#समावेश "main.h"
#समावेश "orinoco.h"

#समावेश "cfg.h"

/* Supported bitrates. Must agree with hw.c */
अटल काष्ठा ieee80211_rate orinoco_rates[] = अणु
	अणु .bitrate = 10 पूर्ण,
	अणु .bitrate = 20 पूर्ण,
	अणु .bitrate = 55 पूर्ण,
	अणु .bitrate = 110 पूर्ण,
पूर्ण;

अटल स्थिर व्योम * स्थिर orinoco_wiphy_privid = &orinoco_wiphy_privid;

/* Called after orinoco_निजी is allocated. */
व्योम orinoco_wiphy_init(काष्ठा wiphy *wiphy)
अणु
	काष्ठा orinoco_निजी *priv = wiphy_priv(wiphy);

	wiphy->privid = orinoco_wiphy_privid;

	set_wiphy_dev(wiphy, priv->dev);
पूर्ण

/* Called after firmware is initialised */
पूर्णांक orinoco_wiphy_रेजिस्टर(काष्ठा wiphy *wiphy)
अणु
	काष्ठा orinoco_निजी *priv = wiphy_priv(wiphy);
	पूर्णांक i, channels = 0;

	अगर (priv->firmware_type == FIRMWARE_TYPE_AGERE)
		wiphy->max_scan_ssids = 1;
	अन्यथा
		wiphy->max_scan_ssids = 0;

	wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION);

	/* TODO: should we set अगर we only have demo ad-hoc?
	 *       (priv->has_port3)
	 */
	अगर (priv->has_ibss)
		wiphy->पूर्णांकerface_modes |= BIT(NL80211_IFTYPE_ADHOC);

	अगर (!priv->broken_monitor || क्रमce_monitor)
		wiphy->पूर्णांकerface_modes |= BIT(NL80211_IFTYPE_MONITOR);

	priv->band.bitrates = orinoco_rates;
	priv->band.n_bitrates = ARRAY_SIZE(orinoco_rates);

	/* Only support channels allowed by the card EEPROM */
	क्रम (i = 0; i < NUM_CHANNELS; i++) अणु
		अगर (priv->channel_mask & (1 << i)) अणु
			priv->channels[i].center_freq =
				ieee80211_channel_to_frequency(i + 1,
							   NL80211_BAND_2GHZ);
			channels++;
		पूर्ण
	पूर्ण
	priv->band.channels = priv->channels;
	priv->band.n_channels = channels;

	wiphy->bands[NL80211_BAND_2GHZ] = &priv->band;
	wiphy->संकेत_type = CFG80211_SIGNAL_TYPE_MBM;

	i = 0;
	अगर (priv->has_wep) अणु
		priv->cipher_suites[i] = WLAN_CIPHER_SUITE_WEP40;
		i++;

		अगर (priv->has_big_wep) अणु
			priv->cipher_suites[i] = WLAN_CIPHER_SUITE_WEP104;
			i++;
		पूर्ण
	पूर्ण
	अगर (priv->has_wpa) अणु
		priv->cipher_suites[i] = WLAN_CIPHER_SUITE_TKIP;
		i++;
	पूर्ण
	wiphy->cipher_suites = priv->cipher_suites;
	wiphy->n_cipher_suites = i;

	wiphy->rts_threshold = priv->rts_thresh;
	अगर (!priv->has_mwo)
		wiphy->frag_threshold = priv->frag_thresh + 1;
	wiphy->retry_लघु = priv->लघु_retry_limit;
	wiphy->retry_दीर्घ = priv->दीर्घ_retry_limit;

	वापस wiphy_रेजिस्टर(wiphy);
पूर्ण

अटल पूर्णांक orinoco_change_vअगर(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			      क्रमागत nl80211_अगरtype type,
			      काष्ठा vअगर_params *params)
अणु
	काष्ठा orinoco_निजी *priv = wiphy_priv(wiphy);
	पूर्णांक err = 0;
	अचिन्हित दीर्घ lock;

	अगर (orinoco_lock(priv, &lock) != 0)
		वापस -EBUSY;

	चयन (type) अणु
	हाल NL80211_IFTYPE_ADHOC:
		अगर (!priv->has_ibss && !priv->has_port3)
			err = -EINVAL;
		अवरोध;

	हाल NL80211_IFTYPE_STATION:
		अवरोध;

	हाल NL80211_IFTYPE_MONITOR:
		अगर (priv->broken_monitor && !क्रमce_monitor) अणु
			wiphy_warn(wiphy,
				   "Monitor mode support is buggy in this firmware, not enabling\n");
			err = -EINVAL;
		पूर्ण
		अवरोध;

	शेष:
		err = -EINVAL;
	पूर्ण

	अगर (!err) अणु
		priv->iw_mode = type;
		set_port_type(priv);
		err = orinoco_commit(priv);
	पूर्ण

	orinoco_unlock(priv, &lock);

	वापस err;
पूर्ण

अटल पूर्णांक orinoco_scan(काष्ठा wiphy *wiphy,
			काष्ठा cfg80211_scan_request *request)
अणु
	काष्ठा orinoco_निजी *priv = wiphy_priv(wiphy);
	पूर्णांक err;

	अगर (!request)
		वापस -EINVAL;

	अगर (priv->scan_request && priv->scan_request != request)
		वापस -EBUSY;

	priv->scan_request = request;

	err = orinoco_hw_trigger_scan(priv, request->ssids);
	/* On error the we aren't processing the request */
	अगर (err)
		priv->scan_request = शून्य;

	वापस err;
पूर्ण

अटल पूर्णांक orinoco_set_monitor_channel(काष्ठा wiphy *wiphy,
				       काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा orinoco_निजी *priv = wiphy_priv(wiphy);
	पूर्णांक err = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक channel;

	अगर (!chandef->chan)
		वापस -EINVAL;

	अगर (cfg80211_get_chandef_type(chandef) != NL80211_CHAN_NO_HT)
		वापस -EINVAL;

	अगर (chandef->chan->band != NL80211_BAND_2GHZ)
		वापस -EINVAL;

	channel = ieee80211_frequency_to_channel(chandef->chan->center_freq);

	अगर ((channel < 1) || (channel > NUM_CHANNELS) ||
	     !(priv->channel_mask & (1 << (channel - 1))))
		वापस -EINVAL;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	priv->channel = channel;
	अगर (priv->iw_mode == NL80211_IFTYPE_MONITOR) अणु
		/* Fast channel change - no commit अगर successful */
		काष्ठा hermes *hw = &priv->hw;
		err = hw->ops->cmd_रुको(hw, HERMES_CMD_TEST |
					    HERMES_TEST_SET_CHANNEL,
					channel, शून्य);
	पूर्ण
	orinoco_unlock(priv, &flags);

	वापस err;
पूर्ण

अटल पूर्णांक orinoco_set_wiphy_params(काष्ठा wiphy *wiphy, u32 changed)
अणु
	काष्ठा orinoco_निजी *priv = wiphy_priv(wiphy);
	पूर्णांक frag_value = -1;
	पूर्णांक rts_value = -1;
	पूर्णांक err = 0;

	अगर (changed & WIPHY_PARAM_RETRY_SHORT) अणु
		/* Setting लघु retry not supported */
		err = -EINVAL;
	पूर्ण

	अगर (changed & WIPHY_PARAM_RETRY_LONG) अणु
		/* Setting दीर्घ retry not supported */
		err = -EINVAL;
	पूर्ण

	अगर (changed & WIPHY_PARAM_FRAG_THRESHOLD) अणु
		/* Set fragmentation */
		अगर (priv->has_mwo) अणु
			अगर (wiphy->frag_threshold == -1)
				frag_value = 0;
			अन्यथा अणु
				prपूर्णांकk(KERN_WARNING "%s: Fixed fragmentation "
				       "is not supported on this firmware. "
				       "Using MWO robust instead.\n",
				       priv->ndev->name);
				frag_value = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (wiphy->frag_threshold == -1)
				frag_value = 2346;
			अन्यथा अगर ((wiphy->frag_threshold < 257) ||
				 (wiphy->frag_threshold > 2347))
				err = -EINVAL;
			अन्यथा
				/* cfg80211 value is 257-2347 (odd only)
				 * orinoco rid has range 256-2346 (even only) */
				frag_value = wiphy->frag_threshold & ~0x1;
		पूर्ण
	पूर्ण

	अगर (changed & WIPHY_PARAM_RTS_THRESHOLD) अणु
		/* Set RTS.
		 *
		 * Prism करोcumentation suggests शेष of 2432,
		 * and a range of 0-3000.
		 *
		 * Current implementation uses 2347 as the शेष and
		 * the upper limit.
		 */

		अगर (wiphy->rts_threshold == -1)
			rts_value = 2347;
		अन्यथा अगर (wiphy->rts_threshold > 2347)
			err = -EINVAL;
		अन्यथा
			rts_value = wiphy->rts_threshold;
	पूर्ण

	अगर (!err) अणु
		अचिन्हित दीर्घ flags;

		अगर (orinoco_lock(priv, &flags) != 0)
			वापस -EBUSY;

		अगर (frag_value >= 0) अणु
			अगर (priv->has_mwo)
				priv->mwo_robust = frag_value;
			अन्यथा
				priv->frag_thresh = frag_value;
		पूर्ण
		अगर (rts_value >= 0)
			priv->rts_thresh = rts_value;

		err = orinoco_commit(priv);

		orinoco_unlock(priv, &flags);
	पूर्ण

	वापस err;
पूर्ण

स्थिर काष्ठा cfg80211_ops orinoco_cfg_ops = अणु
	.change_भव_पूर्णांकf = orinoco_change_vअगर,
	.set_monitor_channel = orinoco_set_monitor_channel,
	.scan = orinoco_scan,
	.set_wiphy_params = orinoco_set_wiphy_params,
पूर्ण;
