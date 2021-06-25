<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* ioctl() (mostly Linux Wireless Extensions) routines क्रम Host AP driver */

#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/module.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/lib80211.h>

#समावेश "hostap_wlan.h"
#समावेश "hostap.h"
#समावेश "hostap_ap.h"

अटल काष्ठा iw_statistics *hostap_get_wireless_stats(काष्ठा net_device *dev)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	काष्ठा iw_statistics *wstats;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	/* Why are we करोing that ? Jean II */
	अगर (अगरace->type != HOSTAP_INTERFACE_MAIN)
		वापस शून्य;

	wstats = &local->wstats;

	wstats->status = 0;
	wstats->discard.code =
		local->comm_tallies.rx_discards_wep_undecryptable;
	wstats->discard.misc =
		local->comm_tallies.rx_fcs_errors +
		local->comm_tallies.rx_discards_no_buffer +
		local->comm_tallies.tx_discards_wrong_sa;

	wstats->discard.retries =
		local->comm_tallies.tx_retry_limit_exceeded;
	wstats->discard.fragment =
		local->comm_tallies.rx_message_in_bad_msg_fragments;

	अगर (local->iw_mode != IW_MODE_MASTER &&
	    local->iw_mode != IW_MODE_REPEAT) अणु

		अगर (prism2_update_comms_qual(dev) == 0)
			wstats->qual.updated = IW_QUAL_ALL_UPDATED |
				IW_QUAL_DBM;

		wstats->qual.qual = local->comms_qual;
		wstats->qual.level = local->avg_संकेत;
		wstats->qual.noise = local->avg_noise;
	पूर्ण अन्यथा अणु
		wstats->qual.qual = 0;
		wstats->qual.level = 0;
		wstats->qual.noise = 0;
		wstats->qual.updated = IW_QUAL_ALL_INVALID;
	पूर्ण

	वापस wstats;
पूर्ण


अटल पूर्णांक prism2_get_datarates(काष्ठा net_device *dev, u8 *rates)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	u8 buf[12];
	पूर्णांक len;
	u16 val;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	len = local->func->get_rid(dev, HFA384X_RID_SUPPORTEDDATARATES, buf,
				   माप(buf), 0);
	अगर (len < 2)
		वापस 0;

	val = le16_to_cpu(*(__le16 *) buf); /* string length */

	अगर (len - 2 < val || val > 10)
		वापस 0;

	स_नकल(rates, buf + 2, val);
	वापस val;
पूर्ण


अटल पूर्णांक prism2_get_name(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   अक्षर *name, अक्षर *extra)
अणु
	u8 rates[10];
	पूर्णांक len, i, over2 = 0;

	len = prism2_get_datarates(dev, rates);

	क्रम (i = 0; i < len; i++) अणु
		अगर (rates[i] == 0x0b || rates[i] == 0x16) अणु
			over2 = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	म_नकल(name, over2 ? "IEEE 802.11b" : "IEEE 802.11-DS");

	वापस 0;
पूर्ण


अटल पूर्णांक prism2_ioctl_siwencode(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  काष्ठा iw_poपूर्णांक *erq, अक्षर *keybuf)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक i;
	काष्ठा lib80211_crypt_data **crypt;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	i = erq->flags & IW_ENCODE_INDEX;
	अगर (i < 1 || i > 4)
		i = local->crypt_info.tx_keyidx;
	अन्यथा
		i--;
	अगर (i < 0 || i >= WEP_KEYS)
		वापस -EINVAL;

	crypt = &local->crypt_info.crypt[i];

	अगर (erq->flags & IW_ENCODE_DISABLED) अणु
		अगर (*crypt)
			lib80211_crypt_delayed_deinit(&local->crypt_info, crypt);
		जाओ करोne;
	पूर्ण

	अगर (*crypt != शून्य && (*crypt)->ops != शून्य &&
	    म_भेद((*crypt)->ops->name, "WEP") != 0) अणु
		/* changing to use WEP; deinit previously used algorithm */
		lib80211_crypt_delayed_deinit(&local->crypt_info, crypt);
	पूर्ण

	अगर (*crypt == शून्य) अणु
		काष्ठा lib80211_crypt_data *new_crypt;

		/* take WEP पूर्णांकo use */
		new_crypt = kzalloc(माप(काष्ठा lib80211_crypt_data),
				GFP_KERNEL);
		अगर (new_crypt == शून्य)
			वापस -ENOMEM;
		new_crypt->ops = lib80211_get_crypto_ops("WEP");
		अगर (!new_crypt->ops) अणु
			request_module("lib80211_crypt_wep");
			new_crypt->ops = lib80211_get_crypto_ops("WEP");
		पूर्ण
		अगर (new_crypt->ops && try_module_get(new_crypt->ops->owner))
			new_crypt->priv = new_crypt->ops->init(i);
		अगर (!new_crypt->ops || !new_crypt->priv) अणु
			kमुक्त(new_crypt);
			new_crypt = शून्य;

			prपूर्णांकk(KERN_WARNING "%s: could not initialize WEP: "
			       "load module hostap_crypt_wep.o\n",
			       dev->name);
			वापस -EOPNOTSUPP;
		पूर्ण
		*crypt = new_crypt;
	पूर्ण

	अगर (erq->length > 0) अणु
		पूर्णांक len = erq->length <= 5 ? 5 : 13;
		पूर्णांक first = 1, j;
		अगर (len > erq->length)
			स_रखो(keybuf + erq->length, 0, len - erq->length);
		(*crypt)->ops->set_key(keybuf, len, शून्य, (*crypt)->priv);
		क्रम (j = 0; j < WEP_KEYS; j++) अणु
			अगर (j != i && local->crypt_info.crypt[j]) अणु
				first = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (first)
			local->crypt_info.tx_keyidx = i;
	पूर्ण अन्यथा अणु
		/* No key data - just set the शेष TX key index */
		local->crypt_info.tx_keyidx = i;
	पूर्ण

 करोne:
	local->खोलो_wep = erq->flags & IW_ENCODE_OPEN;

	अगर (hostap_set_encryption(local)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: set_encryption failed\n", dev->name);
		वापस -EINVAL;
	पूर्ण

	/* Do not reset port0 अगर card is in Managed mode since resetting will
	 * generate new IEEE 802.11 authentication which may end up in looping
	 * with IEEE 802.1X. Prism2 करोcumentation seem to require port reset
	 * after WEP configuration. However, keys are apparently changed at
	 * least in Managed mode. */
	अगर (local->iw_mode != IW_MODE_INFRA && local->func->reset_port(dev)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: reset_port failed\n", dev->name);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक prism2_ioctl_giwencode(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  काष्ठा iw_poपूर्णांक *erq, अक्षर *key)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक i, len;
	u16 val;
	काष्ठा lib80211_crypt_data *crypt;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	i = erq->flags & IW_ENCODE_INDEX;
	अगर (i < 1 || i > 4)
		i = local->crypt_info.tx_keyidx;
	अन्यथा
		i--;
	अगर (i < 0 || i >= WEP_KEYS)
		वापस -EINVAL;

	crypt = local->crypt_info.crypt[i];
	erq->flags = i + 1;

	अगर (crypt == शून्य || crypt->ops == शून्य) अणु
		erq->length = 0;
		erq->flags |= IW_ENCODE_DISABLED;
		वापस 0;
	पूर्ण

	अगर (म_भेद(crypt->ops->name, "WEP") != 0) अणु
		/* only WEP is supported with wireless extensions, so just
		 * report that encryption is used */
		erq->length = 0;
		erq->flags |= IW_ENCODE_ENABLED;
		वापस 0;
	पूर्ण

	/* Reads from HFA384X_RID_CNFDEFAULTKEY* वापस bogus values, so show
	 * the keys from driver buffer */
	len = crypt->ops->get_key(key, WEP_KEY_LEN, शून्य, crypt->priv);
	erq->length = (len >= 0 ? len : 0);

	अगर (local->func->get_rid(dev, HFA384X_RID_CNFWEPFLAGS, &val, 2, 1) < 0)
	अणु
		prपूर्णांकk("CNFWEPFLAGS reading failed\n");
		वापस -EOPNOTSUPP;
	पूर्ण
	le16_to_cpus(&val);
	अगर (val & HFA384X_WEPFLAGS_PRIVACYINVOKED)
		erq->flags |= IW_ENCODE_ENABLED;
	अन्यथा
		erq->flags |= IW_ENCODE_DISABLED;
	अगर (val & HFA384X_WEPFLAGS_EXCLUDEUNENCRYPTED)
		erq->flags |= IW_ENCODE_RESTRICTED;
	अन्यथा
		erq->flags |= IW_ENCODE_OPEN;

	वापस 0;
पूर्ण


अटल पूर्णांक hostap_set_rate(काष्ठा net_device *dev)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक ret, basic_rates;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	basic_rates = local->basic_rates & local->tx_rate_control;
	अगर (!basic_rates || basic_rates != local->basic_rates) अणु
		prपूर्णांकk(KERN_INFO "%s: updating basic rate set automatically "
		       "to match with the new supported rate set\n",
		       dev->name);
		अगर (!basic_rates)
			basic_rates = local->tx_rate_control;

		local->basic_rates = basic_rates;
		अगर (hostap_set_word(dev, HFA384X_RID_CNFBASICRATES,
				    basic_rates))
			prपूर्णांकk(KERN_WARNING "%s: failed to set "
			       "cnfBasicRates\n", dev->name);
	पूर्ण

	ret = (hostap_set_word(dev, HFA384X_RID_TXRATECONTROL,
			       local->tx_rate_control) ||
	       hostap_set_word(dev, HFA384X_RID_CNFSUPPORTEDRATES,
			       local->tx_rate_control) ||
	       local->func->reset_port(dev));

	अगर (ret) अणु
		prपूर्णांकk(KERN_WARNING "%s: TXRateControl/cnfSupportedRates "
		       "setting to 0x%x failed\n",
		       dev->name, local->tx_rate_control);
	पूर्ण

	/* Update TX rate configuration क्रम all STAs based on new operational
	 * rate set. */
	hostap_update_rates(local);

	वापस ret;
पूर्ण


अटल पूर्णांक prism2_ioctl_siwrate(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				काष्ठा iw_param *rrq, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (rrq->fixed) अणु
		चयन (rrq->value) अणु
		हाल 11000000:
			local->tx_rate_control = HFA384X_RATES_11MBPS;
			अवरोध;
		हाल 5500000:
			local->tx_rate_control = HFA384X_RATES_5MBPS;
			अवरोध;
		हाल 2000000:
			local->tx_rate_control = HFA384X_RATES_2MBPS;
			अवरोध;
		हाल 1000000:
			local->tx_rate_control = HFA384X_RATES_1MBPS;
			अवरोध;
		शेष:
			local->tx_rate_control = HFA384X_RATES_1MBPS |
				HFA384X_RATES_2MBPS | HFA384X_RATES_5MBPS |
				HFA384X_RATES_11MBPS;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (rrq->value) अणु
		हाल 11000000:
			local->tx_rate_control = HFA384X_RATES_1MBPS |
				HFA384X_RATES_2MBPS | HFA384X_RATES_5MBPS |
				HFA384X_RATES_11MBPS;
			अवरोध;
		हाल 5500000:
			local->tx_rate_control = HFA384X_RATES_1MBPS |
				HFA384X_RATES_2MBPS | HFA384X_RATES_5MBPS;
			अवरोध;
		हाल 2000000:
			local->tx_rate_control = HFA384X_RATES_1MBPS |
				HFA384X_RATES_2MBPS;
			अवरोध;
		हाल 1000000:
			local->tx_rate_control = HFA384X_RATES_1MBPS;
			अवरोध;
		शेष:
			local->tx_rate_control = HFA384X_RATES_1MBPS |
				HFA384X_RATES_2MBPS | HFA384X_RATES_5MBPS |
				HFA384X_RATES_11MBPS;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस hostap_set_rate(dev);
पूर्ण


अटल पूर्णांक prism2_ioctl_giwrate(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				काष्ठा iw_param *rrq, अक्षर *extra)
अणु
	u16 val;
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक ret = 0;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (local->func->get_rid(dev, HFA384X_RID_TXRATECONTROL, &val, 2, 1) <
	    0)
		वापस -EINVAL;

	अगर ((val & 0x1) && (val > 1))
		rrq->fixed = 0;
	अन्यथा
		rrq->fixed = 1;

	अगर (local->iw_mode == IW_MODE_MASTER && local->ap != शून्य &&
	    !local->fw_tx_rate_control) अणु
		/* HFA384X_RID_CURRENTTXRATE seems to always be 2 Mbps in
		 * Host AP mode, so use the recorded TX rate of the last sent
		 * frame */
		rrq->value = local->ap->last_tx_rate > 0 ?
			local->ap->last_tx_rate * 100000 : 11000000;
		वापस 0;
	पूर्ण

	अगर (local->func->get_rid(dev, HFA384X_RID_CURRENTTXRATE, &val, 2, 1) <
	    0)
		वापस -EINVAL;

	चयन (val) अणु
	हाल HFA384X_RATES_1MBPS:
		rrq->value = 1000000;
		अवरोध;
	हाल HFA384X_RATES_2MBPS:
		rrq->value = 2000000;
		अवरोध;
	हाल HFA384X_RATES_5MBPS:
		rrq->value = 5500000;
		अवरोध;
	हाल HFA384X_RATES_11MBPS:
		rrq->value = 11000000;
		अवरोध;
	शेष:
		/* should not happen */
		rrq->value = 11000000;
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण


अटल पूर्णांक prism2_ioctl_siwsens(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				काष्ठा iw_param *sens, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	/* Set the desired AP density */
	अगर (sens->value < 1 || sens->value > 3)
		वापस -EINVAL;

	अगर (hostap_set_word(dev, HFA384X_RID_CNFSYSTEMSCALE, sens->value) ||
	    local->func->reset_port(dev))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक prism2_ioctl_giwsens(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				काष्ठा iw_param *sens, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	__le16 val;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	/* Get the current AP density */
	अगर (local->func->get_rid(dev, HFA384X_RID_CNFSYSTEMSCALE, &val, 2, 1) <
	    0)
		वापस -EINVAL;

	sens->value = le16_to_cpu(val);
	sens->fixed = 1;

	वापस 0;
पूर्ण


/* Deprecated in new wireless extension API */
अटल पूर्णांक prism2_ioctl_giwaplist(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  काष्ठा iw_poपूर्णांक *data, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	काष्ठा sockaddr *addr;
	काष्ठा iw_quality *qual;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (local->iw_mode != IW_MODE_MASTER) अणु
		prपूर्णांकk(KERN_DEBUG "SIOCGIWAPLIST is currently only supported "
		       "in Host AP mode\n");
		data->length = 0;
		वापस -EOPNOTSUPP;
	पूर्ण

	addr = kदो_स्मृति_array(IW_MAX_AP, माप(काष्ठा sockaddr), GFP_KERNEL);
	qual = kदो_स्मृति_array(IW_MAX_AP, माप(काष्ठा iw_quality), GFP_KERNEL);
	अगर (addr == शून्य || qual == शून्य) अणु
		kमुक्त(addr);
		kमुक्त(qual);
		data->length = 0;
		वापस -ENOMEM;
	पूर्ण

	data->length = prism2_ap_get_sta_qual(local, addr, qual, IW_MAX_AP, 1);

	स_नकल(extra, addr, माप(काष्ठा sockaddr) * data->length);
	data->flags = 1; /* has quality inक्रमmation */
	स_नकल(extra + माप(काष्ठा sockaddr) * data->length, qual,
	       माप(काष्ठा iw_quality) * data->length);

	kमुक्त(addr);
	kमुक्त(qual);
	वापस 0;
पूर्ण


अटल पूर्णांक prism2_ioctl_siwrts(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       काष्ठा iw_param *rts, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	__le16 val;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (rts->disabled)
		val = cpu_to_le16(2347);
	अन्यथा अगर (rts->value < 0 || rts->value > 2347)
		वापस -EINVAL;
	अन्यथा
		val = cpu_to_le16(rts->value);

	अगर (local->func->set_rid(dev, HFA384X_RID_RTSTHRESHOLD, &val, 2) ||
	    local->func->reset_port(dev))
		वापस -EINVAL;

	local->rts_threshold = rts->value;

	वापस 0;
पूर्ण

अटल पूर्णांक prism2_ioctl_giwrts(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       काष्ठा iw_param *rts, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	__le16 val;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (local->func->get_rid(dev, HFA384X_RID_RTSTHRESHOLD, &val, 2, 1) <
	    0)
		वापस -EINVAL;

	rts->value = le16_to_cpu(val);
	rts->disabled = (rts->value == 2347);
	rts->fixed = 1;

	वापस 0;
पूर्ण


अटल पूर्णांक prism2_ioctl_siwfrag(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				काष्ठा iw_param *rts, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	__le16 val;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (rts->disabled)
		val = cpu_to_le16(2346);
	अन्यथा अगर (rts->value < 256 || rts->value > 2346)
		वापस -EINVAL;
	अन्यथा
		val = cpu_to_le16(rts->value & ~0x1); /* even numbers only */

	local->fragm_threshold = rts->value & ~0x1;
	अगर (local->func->set_rid(dev, HFA384X_RID_FRAGMENTATIONTHRESHOLD, &val,
				 2)
	    || local->func->reset_port(dev))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक prism2_ioctl_giwfrag(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				काष्ठा iw_param *rts, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	__le16 val;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (local->func->get_rid(dev, HFA384X_RID_FRAGMENTATIONTHRESHOLD,
				 &val, 2, 1) < 0)
		वापस -EINVAL;

	rts->value = le16_to_cpu(val);
	rts->disabled = (rts->value == 2346);
	rts->fixed = 1;

	वापस 0;
पूर्ण


#अगर_अघोषित PRISM2_NO_STATION_MODES
अटल पूर्णांक hostap_join_ap(काष्ठा net_device *dev)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	काष्ठा hfa384x_join_request req;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	काष्ठा hfa384x_hostscan_result *entry;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	स_नकल(req.bssid, local->preferred_ap, ETH_ALEN);
	req.channel = 0;

	spin_lock_irqsave(&local->lock, flags);
	क्रम (i = 0; i < local->last_scan_results_count; i++) अणु
		अगर (!local->last_scan_results)
			अवरोध;
		entry = &local->last_scan_results[i];
		अगर (ether_addr_equal(local->preferred_ap, entry->bssid)) अणु
			req.channel = entry->chid;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&local->lock, flags);

	अगर (local->func->set_rid(dev, HFA384X_RID_JOINREQUEST, &req,
				 माप(req))) अणु
		prपूर्णांकk(KERN_DEBUG "%s: JoinRequest %pM failed\n",
		       dev->name, local->preferred_ap);
		वापस -1;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "%s: Trying to join BSSID %pM\n",
	       dev->name, local->preferred_ap);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* PRISM2_NO_STATION_MODES */


अटल पूर्णांक prism2_ioctl_siwap(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      काष्ठा sockaddr *ap_addr, अक्षर *extra)
अणु
#अगर_घोषित PRISM2_NO_STATION_MODES
	वापस -EOPNOTSUPP;
#अन्यथा /* PRISM2_NO_STATION_MODES */
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	स_नकल(local->preferred_ap, &ap_addr->sa_data, ETH_ALEN);

	अगर (local->host_roaming == 1 && local->iw_mode == IW_MODE_INFRA) अणु
		काष्ठा hfa384x_scan_request scan_req;
		स_रखो(&scan_req, 0, माप(scan_req));
		scan_req.channel_list = cpu_to_le16(0x3fff);
		scan_req.txrate = cpu_to_le16(HFA384X_RATES_1MBPS);
		अगर (local->func->set_rid(dev, HFA384X_RID_SCANREQUEST,
					 &scan_req, माप(scan_req))) अणु
			prपूर्णांकk(KERN_DEBUG "%s: ScanResults request failed - "
			       "preferred AP delayed to next unsolicited "
			       "scan\n", dev->name);
		पूर्ण
	पूर्ण अन्यथा अगर (local->host_roaming == 2 &&
		   local->iw_mode == IW_MODE_INFRA) अणु
		अगर (hostap_join_ap(dev))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_DEBUG "%s: Preferred AP (SIOCSIWAP) is used only "
		       "in Managed mode when host_roaming is enabled\n",
		       dev->name);
	पूर्ण

	वापस 0;
#पूर्ण_अगर /* PRISM2_NO_STATION_MODES */
पूर्ण

अटल पूर्णांक prism2_ioctl_giwap(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      काष्ठा sockaddr *ap_addr, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	ap_addr->sa_family = ARPHRD_ETHER;
	चयन (अगरace->type) अणु
	हाल HOSTAP_INTERFACE_AP:
		स_नकल(&ap_addr->sa_data, dev->dev_addr, ETH_ALEN);
		अवरोध;
	हाल HOSTAP_INTERFACE_STA:
		स_नकल(&ap_addr->sa_data, local->assoc_ap_addr, ETH_ALEN);
		अवरोध;
	हाल HOSTAP_INTERFACE_WDS:
		स_नकल(&ap_addr->sa_data, अगरace->u.wds.remote_addr, ETH_ALEN);
		अवरोध;
	शेष:
		अगर (local->func->get_rid(dev, HFA384X_RID_CURRENTBSSID,
					 &ap_addr->sa_data, ETH_ALEN, 1) < 0)
			वापस -EOPNOTSUPP;

		/* local->bssid is also updated in LinkStatus handler when in
		 * station mode */
		स_नकल(local->bssid, &ap_addr->sa_data, ETH_ALEN);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक prism2_ioctl_siwnickn(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_poपूर्णांक *data, अक्षर *nickname)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	स_रखो(local->name, 0, माप(local->name));
	स_नकल(local->name, nickname, data->length);
	local->name_set = 1;

	अगर (hostap_set_string(dev, HFA384X_RID_CNFOWNNAME, local->name) ||
	    local->func->reset_port(dev))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक prism2_ioctl_giwnickn(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_poपूर्णांक *data, अक्षर *nickname)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक len;
	अक्षर name[MAX_NAME_LEN + 3];
	u16 val;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	len = local->func->get_rid(dev, HFA384X_RID_CNFOWNNAME,
				   &name, MAX_NAME_LEN + 2, 0);
	val = le16_to_cpu(*(__le16 *) name);
	अगर (len > MAX_NAME_LEN + 2 || len < 0 || val > MAX_NAME_LEN)
		वापस -EOPNOTSUPP;

	name[val + 2] = '\0';
	data->length = val + 1;
	स_नकल(nickname, name + 2, val + 1);

	वापस 0;
पूर्ण


अटल पूर्णांक prism2_ioctl_siwfreq(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				काष्ठा iw_freq *freq, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	/* freq => chan. */
	अगर (freq->e == 1 &&
	    freq->m / 100000 >= freq_list[0] &&
	    freq->m / 100000 <= freq_list[FREQ_COUNT - 1]) अणु
		पूर्णांक ch;
		पूर्णांक fr = freq->m / 100000;
		क्रम (ch = 0; ch < FREQ_COUNT; ch++) अणु
			अगर (fr == freq_list[ch]) अणु
				freq->e = 0;
				freq->m = ch + 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (freq->e != 0 || freq->m < 1 || freq->m > FREQ_COUNT ||
	    !(local->channel_mask & (1 << (freq->m - 1))))
		वापस -EINVAL;

	local->channel = freq->m; /* channel is used in prism2_setup_rids() */
	अगर (hostap_set_word(dev, HFA384X_RID_CNFOWNCHANNEL, local->channel) ||
	    local->func->reset_port(dev))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक prism2_ioctl_giwfreq(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				काष्ठा iw_freq *freq, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	u16 val;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (local->func->get_rid(dev, HFA384X_RID_CURRENTCHANNEL, &val, 2, 1) <
	    0)
		वापस -EINVAL;

	le16_to_cpus(&val);
	अगर (val < 1 || val > FREQ_COUNT)
		वापस -EINVAL;

	freq->m = freq_list[val - 1] * 100000;
	freq->e = 1;

	वापस 0;
पूर्ण


अटल व्योम hostap_monitor_set_type(local_info_t *local)
अणु
	काष्ठा net_device *dev = local->ddev;

	अगर (dev == शून्य)
		वापस;

	अगर (local->monitor_type == PRISM2_MONITOR_PRISM ||
	    local->monitor_type == PRISM2_MONITOR_CAPHDR) अणु
		dev->type = ARPHRD_IEEE80211_PRISM;
	पूर्ण अन्यथा अगर (local->monitor_type == PRISM2_MONITOR_RADIOTAP) अणु
		dev->type = ARPHRD_IEEE80211_RADIOTAP;
	पूर्ण अन्यथा अणु
		dev->type = ARPHRD_IEEE80211;
	पूर्ण
पूर्ण


अटल पूर्णांक prism2_ioctl_siwessid(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_poपूर्णांक *data, अक्षर *ssid)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (अगरace->type == HOSTAP_INTERFACE_WDS)
		वापस -EOPNOTSUPP;

	अगर (data->flags == 0)
		ssid[0] = '\0'; /* ANY */

	अगर (local->iw_mode == IW_MODE_MASTER && ssid[0] == '\0') अणु
		/* Setting SSID to empty string seems to समाप्त the card in
		 * Host AP mode */
		prपूर्णांकk(KERN_DEBUG "%s: Host AP mode does not support "
		       "'Any' essid\n", dev->name);
		वापस -EINVAL;
	पूर्ण

	स_नकल(local->essid, ssid, data->length);
	local->essid[data->length] = '\0';

	अगर ((!local->fw_ap &&
	     hostap_set_string(dev, HFA384X_RID_CNFDESIREDSSID, local->essid))
	    || hostap_set_string(dev, HFA384X_RID_CNFOWNSSID, local->essid) ||
	    local->func->reset_port(dev))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक prism2_ioctl_giwessid(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_poपूर्णांक *data, अक्षर *essid)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	u16 val;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (अगरace->type == HOSTAP_INTERFACE_WDS)
		वापस -EOPNOTSUPP;

	data->flags = 1; /* active */
	अगर (local->iw_mode == IW_MODE_MASTER) अणु
		data->length = म_माप(local->essid);
		स_नकल(essid, local->essid, IW_ESSID_MAX_SIZE);
	पूर्ण अन्यथा अणु
		पूर्णांक len;
		अक्षर ssid[MAX_SSID_LEN + 2];
		स_रखो(ssid, 0, माप(ssid));
		len = local->func->get_rid(dev, HFA384X_RID_CURRENTSSID,
					   &ssid, MAX_SSID_LEN + 2, 0);
		val = le16_to_cpu(*(__le16 *) ssid);
		अगर (len > MAX_SSID_LEN + 2 || len < 0 || val > MAX_SSID_LEN) अणु
			वापस -EOPNOTSUPP;
		पूर्ण
		data->length = val;
		स_नकल(essid, ssid + 2, IW_ESSID_MAX_SIZE);
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक prism2_ioctl_giwrange(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_poपूर्णांक *data, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	काष्ठा iw_range *range = (काष्ठा iw_range *) extra;
	u8 rates[10];
	u16 val;
	पूर्णांक i, len, over2;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	data->length = माप(काष्ठा iw_range);
	स_रखो(range, 0, माप(काष्ठा iw_range));

	/* TODO: could fill num_txघातer and txघातer array with
	 * something; however, there are 128 dअगरferent values.. */

	range->txघातer_capa = IW_TXPOW_DBM;

	अगर (local->iw_mode == IW_MODE_INFRA || local->iw_mode == IW_MODE_ADHOC)
	अणु
		range->min_pmp = 1 * 1024;
		range->max_pmp = 65535 * 1024;
		range->min_pmt = 1 * 1024;
		range->max_pmt = 1000 * 1024;
		range->pmp_flags = IW_POWER_PERIOD;
		range->pmt_flags = IW_POWER_TIMEOUT;
		range->pm_capa = IW_POWER_PERIOD | IW_POWER_TIMEOUT |
			IW_POWER_UNICAST_R | IW_POWER_ALL_R;
	पूर्ण

	range->we_version_compiled = WIRELESS_EXT;
	range->we_version_source = 18;

	range->retry_capa = IW_RETRY_LIMIT;
	range->retry_flags = IW_RETRY_LIMIT;
	range->min_retry = 0;
	range->max_retry = 255;

	range->num_channels = FREQ_COUNT;

	val = 0;
	क्रम (i = 0; i < FREQ_COUNT; i++) अणु
		अगर (local->channel_mask & (1 << i)) अणु
			range->freq[val].i = i + 1;
			range->freq[val].m = freq_list[i] * 100000;
			range->freq[val].e = 1;
			val++;
		पूर्ण
		अगर (val == IW_MAX_FREQUENCIES)
			अवरोध;
	पूर्ण
	range->num_frequency = val;

	अगर (local->sta_fw_ver >= PRISM2_FW_VER(1,3,1)) अणु
		range->max_qual.qual = 70; /* what is correct max? This was not
					    * करोcumented exactly. At least
					    * 69 has been observed. */
		range->max_qual.level = 0; /* dB */
		range->max_qual.noise = 0; /* dB */

		/* What would be suitable values क्रम "average/typical" qual? */
		range->avg_qual.qual = 20;
		range->avg_qual.level = -60;
		range->avg_qual.noise = -95;
	पूर्ण अन्यथा अणु
		range->max_qual.qual = 92; /* 0 .. 92 */
		range->max_qual.level = 154; /* 27 .. 154 */
		range->max_qual.noise = 154; /* 27 .. 154 */
	पूर्ण
	range->sensitivity = 3;

	range->max_encoding_tokens = WEP_KEYS;
	range->num_encoding_sizes = 2;
	range->encoding_size[0] = 5;
	range->encoding_size[1] = 13;

	over2 = 0;
	len = prism2_get_datarates(dev, rates);
	range->num_bitrates = 0;
	क्रम (i = 0; i < len; i++) अणु
		अगर (range->num_bitrates < IW_MAX_BITRATES) अणु
			range->bitrate[range->num_bitrates] =
				rates[i] * 500000;
			range->num_bitrates++;
		पूर्ण
		अगर (rates[i] == 0x0b || rates[i] == 0x16)
			over2 = 1;
	पूर्ण
	/* estimated maximum TCP throughput values (bps) */
	range->throughput = over2 ? 5500000 : 1500000;

	range->min_rts = 0;
	range->max_rts = 2347;
	range->min_frag = 256;
	range->max_frag = 2346;

	/* Event capability (kernel + driver) */
	range->event_capa[0] = (IW_EVENT_CAPA_K_0 |
				IW_EVENT_CAPA_MASK(SIOCGIWTHRSPY) |
				IW_EVENT_CAPA_MASK(SIOCGIWAP) |
				IW_EVENT_CAPA_MASK(SIOCGIWSCAN));
	range->event_capa[1] = IW_EVENT_CAPA_K_1;
	range->event_capa[4] = (IW_EVENT_CAPA_MASK(IWEVTXDROP) |
				IW_EVENT_CAPA_MASK(IWEVCUSTOM) |
				IW_EVENT_CAPA_MASK(IWEVREGISTERED) |
				IW_EVENT_CAPA_MASK(IWEVEXPIRED));

	range->enc_capa = IW_ENC_CAPA_WPA | IW_ENC_CAPA_WPA2 |
		IW_ENC_CAPA_CIPHER_TKIP | IW_ENC_CAPA_CIPHER_CCMP;

	अगर (local->sta_fw_ver >= PRISM2_FW_VER(1,3,1))
		range->scan_capa = IW_SCAN_CAPA_ESSID;

	वापस 0;
पूर्ण


अटल पूर्णांक hostap_monitor_mode_enable(local_info_t *local)
अणु
	काष्ठा net_device *dev = local->dev;

	prपूर्णांकk(KERN_DEBUG "Enabling monitor mode\n");
	hostap_monitor_set_type(local);

	अगर (hostap_set_word(dev, HFA384X_RID_CNFPORTTYPE,
			    HFA384X_PORTTYPE_PSEUDO_IBSS)) अणु
		prपूर्णांकk(KERN_DEBUG "Port type setting for monitor mode "
		       "failed\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Host decrypt is needed to get the IV and ICV fields;
	 * however, monitor mode seems to हटाओ WEP flag from frame
	 * control field */
	अगर (hostap_set_word(dev, HFA384X_RID_CNFWEPFLAGS,
			    HFA384X_WEPFLAGS_HOSTENCRYPT |
			    HFA384X_WEPFLAGS_HOSTDECRYPT)) अणु
		prपूर्णांकk(KERN_DEBUG "WEP flags setting failed\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (local->func->reset_port(dev) ||
	    local->func->cmd(dev, HFA384X_CMDCODE_TEST |
			     (HFA384X_TEST_MONITOR << 8),
			     0, शून्य, शून्य)) अणु
		prपूर्णांकk(KERN_DEBUG "Setting monitor mode failed\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक hostap_monitor_mode_disable(local_info_t *local)
अणु
	काष्ठा net_device *dev = local->ddev;

	अगर (dev == शून्य)
		वापस -1;

	prपूर्णांकk(KERN_DEBUG "%s: Disabling monitor mode\n", dev->name);
	dev->type = ARPHRD_ETHER;

	अगर (local->func->cmd(dev, HFA384X_CMDCODE_TEST |
			     (HFA384X_TEST_STOP << 8),
			     0, शून्य, शून्य))
		वापस -1;
	वापस hostap_set_encryption(local);
पूर्ण


अटल पूर्णांक prism2_ioctl_siwmode(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				__u32 *mode, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक द्विगुन_reset = 0;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (*mode != IW_MODE_ADHOC && *mode != IW_MODE_INFRA &&
	    *mode != IW_MODE_MASTER && *mode != IW_MODE_REPEAT &&
	    *mode != IW_MODE_MONITOR)
		वापस -EOPNOTSUPP;

#अगर_घोषित PRISM2_NO_STATION_MODES
	अगर (*mode == IW_MODE_ADHOC || *mode == IW_MODE_INFRA)
		वापस -EOPNOTSUPP;
#पूर्ण_अगर /* PRISM2_NO_STATION_MODES */

	अगर (*mode == local->iw_mode)
		वापस 0;

	अगर (*mode == IW_MODE_MASTER && local->essid[0] == '\0') अणु
		prपूर्णांकk(KERN_WARNING "%s: empty SSID not allowed in Master "
		       "mode\n", dev->name);
		वापस -EINVAL;
	पूर्ण

	अगर (local->iw_mode == IW_MODE_MONITOR)
		hostap_monitor_mode_disable(local);

	अगर ((local->iw_mode == IW_MODE_ADHOC ||
	     local->iw_mode == IW_MODE_MONITOR) && *mode == IW_MODE_MASTER) अणु
		/* There seems to be a firmware bug in at least STA f/w v1.5.6
		 * that leaves beacon frames to use IBSS type when moving from
		 * IBSS to Host AP mode. Doing द्विगुन Port0 reset seems to be
		 * enough to workaround this. */
		द्विगुन_reset = 1;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "prism2: %s: operating mode changed "
	       "%d -> %d\n", dev->name, local->iw_mode, *mode);
	local->iw_mode = *mode;

	अगर (local->iw_mode == IW_MODE_MONITOR)
		hostap_monitor_mode_enable(local);
	अन्यथा अगर (local->iw_mode == IW_MODE_MASTER && !local->host_encrypt &&
		 !local->fw_encrypt_ok) अणु
		prपूर्णांकk(KERN_DEBUG "%s: defaulting to host-based encryption as "
		       "a workaround for firmware bug in Host AP mode WEP\n",
		       dev->name);
		local->host_encrypt = 1;
	पूर्ण

	अगर (hostap_set_word(dev, HFA384X_RID_CNFPORTTYPE,
			    hostap_get_porttype(local)))
		वापस -EOPNOTSUPP;

	अगर (local->func->reset_port(dev))
		वापस -EINVAL;
	अगर (द्विगुन_reset && local->func->reset_port(dev))
		वापस -EINVAL;

	अगर (local->iw_mode != IW_MODE_INFRA && local->iw_mode != IW_MODE_ADHOC)
	अणु
		/* netअगर_carrier is used only in client modes क्रम now, so make
		 * sure carrier is on when moving to non-client modes. */
		netअगर_carrier_on(local->dev);
		netअगर_carrier_on(local->ddev);
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक prism2_ioctl_giwmode(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				__u32 *mode, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	चयन (अगरace->type) अणु
	हाल HOSTAP_INTERFACE_STA:
		*mode = IW_MODE_INFRA;
		अवरोध;
	हाल HOSTAP_INTERFACE_WDS:
		*mode = IW_MODE_REPEAT;
		अवरोध;
	शेष:
		*mode = local->iw_mode;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक prism2_ioctl_siwघातer(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_param *wrq, अक्षर *extra)
अणु
#अगर_घोषित PRISM2_NO_STATION_MODES
	वापस -EOPNOTSUPP;
#अन्यथा /* PRISM2_NO_STATION_MODES */
	पूर्णांक ret = 0;

	अगर (wrq->disabled)
		वापस hostap_set_word(dev, HFA384X_RID_CNFPMENABLED, 0);

	चयन (wrq->flags & IW_POWER_MODE) अणु
	हाल IW_POWER_UNICAST_R:
		ret = hostap_set_word(dev, HFA384X_RID_CNFMULTICASTRECEIVE, 0);
		अगर (ret)
			वापस ret;
		ret = hostap_set_word(dev, HFA384X_RID_CNFPMENABLED, 1);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल IW_POWER_ALL_R:
		ret = hostap_set_word(dev, HFA384X_RID_CNFMULTICASTRECEIVE, 1);
		अगर (ret)
			वापस ret;
		ret = hostap_set_word(dev, HFA384X_RID_CNFPMENABLED, 1);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल IW_POWER_ON:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (wrq->flags & IW_POWER_TIMEOUT) अणु
		ret = hostap_set_word(dev, HFA384X_RID_CNFPMENABLED, 1);
		अगर (ret)
			वापस ret;
		ret = hostap_set_word(dev, HFA384X_RID_CNFPMHOLDOVERDURATION,
				      wrq->value / 1024);
		अगर (ret)
			वापस ret;
	पूर्ण
	अगर (wrq->flags & IW_POWER_PERIOD) अणु
		ret = hostap_set_word(dev, HFA384X_RID_CNFPMENABLED, 1);
		अगर (ret)
			वापस ret;
		ret = hostap_set_word(dev, HFA384X_RID_CNFMAXSLEEPDURATION,
				      wrq->value / 1024);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
#पूर्ण_अगर /* PRISM2_NO_STATION_MODES */
पूर्ण


अटल पूर्णांक prism2_ioctl_giwघातer(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_param *rrq, अक्षर *extra)
अणु
#अगर_घोषित PRISM2_NO_STATION_MODES
	वापस -EOPNOTSUPP;
#अन्यथा /* PRISM2_NO_STATION_MODES */
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	__le16 enable, mcast;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (local->func->get_rid(dev, HFA384X_RID_CNFPMENABLED, &enable, 2, 1)
	    < 0)
		वापस -EINVAL;

	अगर (!le16_to_cpu(enable)) अणु
		rrq->disabled = 1;
		वापस 0;
	पूर्ण

	rrq->disabled = 0;

	अगर ((rrq->flags & IW_POWER_TYPE) == IW_POWER_TIMEOUT) अणु
		__le16 समयout;
		अगर (local->func->get_rid(dev,
					 HFA384X_RID_CNFPMHOLDOVERDURATION,
					 &समयout, 2, 1) < 0)
			वापस -EINVAL;

		rrq->flags = IW_POWER_TIMEOUT;
		rrq->value = le16_to_cpu(समयout) * 1024;
	पूर्ण अन्यथा अणु
		__le16 period;
		अगर (local->func->get_rid(dev, HFA384X_RID_CNFMAXSLEEPDURATION,
					 &period, 2, 1) < 0)
			वापस -EINVAL;

		rrq->flags = IW_POWER_PERIOD;
		rrq->value = le16_to_cpu(period) * 1024;
	पूर्ण

	अगर (local->func->get_rid(dev, HFA384X_RID_CNFMULTICASTRECEIVE, &mcast,
				 2, 1) < 0)
		वापस -EINVAL;

	अगर (le16_to_cpu(mcast))
		rrq->flags |= IW_POWER_ALL_R;
	अन्यथा
		rrq->flags |= IW_POWER_UNICAST_R;

	वापस 0;
#पूर्ण_अगर /* PRISM2_NO_STATION_MODES */
पूर्ण


अटल पूर्णांक prism2_ioctl_siwretry(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_param *rrq, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (rrq->disabled)
		वापस -EINVAL;

	/* setting retry limits is not supported with the current station
	 * firmware code; simulate this with alternative retry count क्रम now */
	अगर (rrq->flags == IW_RETRY_LIMIT) अणु
		अगर (rrq->value < 0) अणु
			/* disable manual retry count setting and use firmware
			 * शेषs */
			local->manual_retry_count = -1;
			local->tx_control &= ~HFA384X_TX_CTRL_ALT_RTRY;
		पूर्ण अन्यथा अणु
			अगर (hostap_set_word(dev, HFA384X_RID_CNFALTRETRYCOUNT,
					    rrq->value)) अणु
				prपूर्णांकk(KERN_DEBUG "%s: Alternate retry count "
				       "setting to %d failed\n",
				       dev->name, rrq->value);
				वापस -EOPNOTSUPP;
			पूर्ण

			local->manual_retry_count = rrq->value;
			local->tx_control |= HFA384X_TX_CTRL_ALT_RTRY;
		पूर्ण
		वापस 0;
	पूर्ण

	वापस -EOPNOTSUPP;

#अगर 0
	/* what could be करोne, अगर firmware would support this.. */

	अगर (rrq->flags & IW_RETRY_LIMIT) अणु
		अगर (rrq->flags & IW_RETRY_LONG)
			HFA384X_RID_LONGRETRYLIMIT = rrq->value;
		अन्यथा अगर (rrq->flags & IW_RETRY_SHORT)
			HFA384X_RID_SHORTRETRYLIMIT = rrq->value;
		अन्यथा अणु
			HFA384X_RID_LONGRETRYLIMIT = rrq->value;
			HFA384X_RID_SHORTRETRYLIMIT = rrq->value;
		पूर्ण

	पूर्ण

	अगर (rrq->flags & IW_RETRY_LIFETIME) अणु
		HFA384X_RID_MAXTRANSMITLIFETIME = rrq->value / 1024;
	पूर्ण

	वापस 0;
#पूर्ण_अगर /* 0 */
पूर्ण

अटल पूर्णांक prism2_ioctl_giwretry(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_param *rrq, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	__le16 लघुretry, दीर्घretry, lअगरeसमय, altretry;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (local->func->get_rid(dev, HFA384X_RID_SHORTRETRYLIMIT, &लघुretry,
				 2, 1) < 0 ||
	    local->func->get_rid(dev, HFA384X_RID_LONGRETRYLIMIT, &दीर्घretry,
				 2, 1) < 0 ||
	    local->func->get_rid(dev, HFA384X_RID_MAXTRANSMITLIFETIME,
				 &lअगरeसमय, 2, 1) < 0)
		वापस -EINVAL;

	rrq->disabled = 0;

	अगर ((rrq->flags & IW_RETRY_TYPE) == IW_RETRY_LIFETIME) अणु
		rrq->flags = IW_RETRY_LIFETIME;
		rrq->value = le16_to_cpu(lअगरeसमय) * 1024;
	पूर्ण अन्यथा अणु
		अगर (local->manual_retry_count >= 0) अणु
			rrq->flags = IW_RETRY_LIMIT;
			अगर (local->func->get_rid(dev,
						 HFA384X_RID_CNFALTRETRYCOUNT,
						 &altretry, 2, 1) >= 0)
				rrq->value = le16_to_cpu(altretry);
			अन्यथा
				rrq->value = local->manual_retry_count;
		पूर्ण अन्यथा अगर ((rrq->flags & IW_RETRY_LONG)) अणु
			rrq->flags = IW_RETRY_LIMIT | IW_RETRY_LONG;
			rrq->value = le16_to_cpu(दीर्घretry);
		पूर्ण अन्यथा अणु
			rrq->flags = IW_RETRY_LIMIT;
			rrq->value = le16_to_cpu(लघुretry);
			अगर (लघुretry != दीर्घretry)
				rrq->flags |= IW_RETRY_SHORT;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


/* Note! This TX घातer controlling is experimental and should not be used in
 * production use. It just sets raw घातer रेजिस्टर and करोes not use any kind of
 * feedback inक्रमmation from the measured TX घातer (CR58). This is now
 * commented out to make sure that it is not used by accident. TX घातer
 * configuration will be enabled again after proper algorithm using feedback
 * has been implemented. */

#अगर_घोषित RAW_TXPOWER_SETTING
/* Map HFA386x's CR31 to and from dBm with some sort of ad hoc mapping..
 * This version assumes following mapping:
 * CR31 is 7-bit value with -64 to +63 range.
 * -64 is mapped पूर्णांकo +20dBm and +63 पूर्णांकo -43dBm.
 * This is certainly not an exact mapping क्रम every card, but at least
 * increasing dBm value should correspond to increasing TX घातer.
 */

अटल पूर्णांक prism2_txघातer_hfa386x_to_dBm(u16 val)
अणु
	चिन्हित अक्षर पंचांगp;

	अगर (val > 255)
		val = 255;

	पंचांगp = val;
	पंचांगp >>= 2;

	वापस -12 - पंचांगp;
पूर्ण

अटल u16 prism2_txघातer_dBm_to_hfa386x(पूर्णांक val)
अणु
	चिन्हित अक्षर पंचांगp;

	अगर (val > 20)
		वापस 128;
	अन्यथा अगर (val < -43)
		वापस 127;

	पंचांगp = val;
	पंचांगp = -12 - पंचांगp;
	पंचांगp <<= 2;

	वापस (अचिन्हित अक्षर) पंचांगp;
पूर्ण
#पूर्ण_अगर /* RAW_TXPOWER_SETTING */


अटल पूर्णांक prism2_ioctl_siwtxघात(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_param *rrq, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
#अगर_घोषित RAW_TXPOWER_SETTING
	अक्षर *पंचांगp;
#पूर्ण_अगर
	u16 val;
	पूर्णांक ret = 0;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (rrq->disabled) अणु
		अगर (local->txघातer_type != PRISM2_TXPOWER_OFF) अणु
			val = 0xff; /* use all standby and sleep modes */
			ret = local->func->cmd(dev, HFA384X_CMDCODE_WRITEMIF,
					       HFA386X_CR_A_D_TEST_MODES2,
					       &val, शून्य);
			prपूर्णांकk(KERN_DEBUG "%s: Turning radio off: %s\n",
			       dev->name, ret ? "failed" : "OK");
			local->txघातer_type = PRISM2_TXPOWER_OFF;
		पूर्ण
		वापस (ret ? -EOPNOTSUPP : 0);
	पूर्ण

	अगर (local->txघातer_type == PRISM2_TXPOWER_OFF) अणु
		val = 0; /* disable all standby and sleep modes */
		ret = local->func->cmd(dev, HFA384X_CMDCODE_WRITEMIF,
				       HFA386X_CR_A_D_TEST_MODES2, &val, शून्य);
		prपूर्णांकk(KERN_DEBUG "%s: Turning radio on: %s\n",
		       dev->name, ret ? "failed" : "OK");
		local->txघातer_type = PRISM2_TXPOWER_UNKNOWN;
	पूर्ण

#अगर_घोषित RAW_TXPOWER_SETTING
	अगर (!rrq->fixed && local->txघातer_type != PRISM2_TXPOWER_AUTO) अणु
		prपूर्णांकk(KERN_DEBUG "Setting ALC on\n");
		val = HFA384X_TEST_CFG_BIT_ALC;
		local->func->cmd(dev, HFA384X_CMDCODE_TEST |
				 (HFA384X_TEST_CFG_BITS << 8), 1, &val, शून्य);
		local->txघातer_type = PRISM2_TXPOWER_AUTO;
		वापस 0;
	पूर्ण

	अगर (local->txघातer_type != PRISM2_TXPOWER_FIXED) अणु
		prपूर्णांकk(KERN_DEBUG "Setting ALC off\n");
		val = HFA384X_TEST_CFG_BIT_ALC;
		local->func->cmd(dev, HFA384X_CMDCODE_TEST |
				 (HFA384X_TEST_CFG_BITS << 8), 0, &val, शून्य);
			local->txघातer_type = PRISM2_TXPOWER_FIXED;
	पूर्ण

	अगर (rrq->flags == IW_TXPOW_DBM)
		पंचांगp = "dBm";
	अन्यथा अगर (rrq->flags == IW_TXPOW_MWATT)
		पंचांगp = "mW";
	अन्यथा
		पंचांगp = "UNKNOWN";
	prपूर्णांकk(KERN_DEBUG "Setting TX power to %d %s\n", rrq->value, पंचांगp);

	अगर (rrq->flags != IW_TXPOW_DBM) अणु
		prपूर्णांकk("SIOCSIWTXPOW with mW is not supported; use dBm\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	local->txघातer = rrq->value;
	val = prism2_txघातer_dBm_to_hfa386x(local->txघातer);
	अगर (local->func->cmd(dev, HFA384X_CMDCODE_WRITEMIF,
			     HFA386X_CR_MANUAL_TX_POWER, &val, शून्य))
		ret = -EOPNOTSUPP;
#अन्यथा /* RAW_TXPOWER_SETTING */
	अगर (rrq->fixed)
		ret = -EOPNOTSUPP;
#पूर्ण_अगर /* RAW_TXPOWER_SETTING */

	वापस ret;
पूर्ण

अटल पूर्णांक prism2_ioctl_giwtxघात(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_param *rrq, अक्षर *extra)
अणु
#अगर_घोषित RAW_TXPOWER_SETTING
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	u16 resp0;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	rrq->flags = IW_TXPOW_DBM;
	rrq->disabled = 0;
	rrq->fixed = 0;

	अगर (local->txघातer_type == PRISM2_TXPOWER_AUTO) अणु
		अगर (local->func->cmd(dev, HFA384X_CMDCODE_READMIF,
				     HFA386X_CR_MANUAL_TX_POWER,
				     शून्य, &resp0) == 0) अणु
			rrq->value = prism2_txघातer_hfa386x_to_dBm(resp0);
		पूर्ण अन्यथा अणु
			/* Could not get real txघातer; guess 15 dBm */
			rrq->value = 15;
		पूर्ण
	पूर्ण अन्यथा अगर (local->txघातer_type == PRISM2_TXPOWER_OFF) अणु
		rrq->value = 0;
		rrq->disabled = 1;
	पूर्ण अन्यथा अगर (local->txघातer_type == PRISM2_TXPOWER_FIXED) अणु
		rrq->value = local->txघातer;
		rrq->fixed = 1;
	पूर्ण अन्यथा अणु
		prपूर्णांकk("SIOCGIWTXPOW - unknown txpower_type=%d\n",
		       local->txघातer_type);
	पूर्ण
	वापस 0;
#अन्यथा /* RAW_TXPOWER_SETTING */
	वापस -EOPNOTSUPP;
#पूर्ण_अगर /* RAW_TXPOWER_SETTING */
पूर्ण


#अगर_अघोषित PRISM2_NO_STATION_MODES

/* HostScan request works with and without host_roaming mode. In addition, it
 * करोes not अवरोध current association. However, it requires newer station
 * firmware version (>= 1.3.1) than scan request. */
अटल पूर्णांक prism2_request_hostscan(काष्ठा net_device *dev,
				   u8 *ssid, u8 ssid_len)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	काष्ठा hfa384x_hostscan_request scan_req;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	स_रखो(&scan_req, 0, माप(scan_req));
	scan_req.channel_list = cpu_to_le16(local->channel_mask &
					    local->scan_channel_mask);
	scan_req.txrate = cpu_to_le16(HFA384X_RATES_1MBPS);
	अगर (ssid) अणु
		अगर (ssid_len > 32)
			वापस -EINVAL;
		scan_req.target_ssid_len = cpu_to_le16(ssid_len);
		स_नकल(scan_req.target_ssid, ssid, ssid_len);
	पूर्ण

	अगर (local->func->set_rid(dev, HFA384X_RID_HOSTSCAN, &scan_req,
				 माप(scan_req))) अणु
		prपूर्णांकk(KERN_DEBUG "%s: HOSTSCAN failed\n", dev->name);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक prism2_request_scan(काष्ठा net_device *dev)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	काष्ठा hfa384x_scan_request scan_req;
	पूर्णांक ret = 0;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	स_रखो(&scan_req, 0, माप(scan_req));
	scan_req.channel_list = cpu_to_le16(local->channel_mask &
					    local->scan_channel_mask);
	scan_req.txrate = cpu_to_le16(HFA384X_RATES_1MBPS);

	/* FIX:
	 * It seems to be enough to set roaming mode क्रम a लघु moment to
	 * host-based and then setup scanrequest data and वापस the mode to
	 * firmware-based.
	 *
	 * Master mode would need to drop to Managed mode क्रम a लघु जबतक
	 * to make scanning work.. Or sweep through the dअगरferent channels and
	 * use passive scan based on beacons. */

	अगर (!local->host_roaming)
		hostap_set_word(dev, HFA384X_RID_CNFROAMINGMODE,
				HFA384X_ROAMING_HOST);

	अगर (local->func->set_rid(dev, HFA384X_RID_SCANREQUEST, &scan_req,
				 माप(scan_req))) अणु
		prपूर्णांकk(KERN_DEBUG "SCANREQUEST failed\n");
		ret = -EINVAL;
	पूर्ण

	अगर (!local->host_roaming)
		hostap_set_word(dev, HFA384X_RID_CNFROAMINGMODE,
				HFA384X_ROAMING_FIRMWARE);

	वापस ret;
पूर्ण

#अन्यथा /* !PRISM2_NO_STATION_MODES */

अटल अंतरभूत पूर्णांक prism2_request_hostscan(काष्ठा net_device *dev,
					  u8 *ssid, u8 ssid_len)
अणु
	वापस -EOPNOTSUPP;
पूर्ण


अटल अंतरभूत पूर्णांक prism2_request_scan(काष्ठा net_device *dev)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

#पूर्ण_अगर /* !PRISM2_NO_STATION_MODES */


अटल पूर्णांक prism2_ioctl_siwscan(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				काष्ठा iw_poपूर्णांक *data, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक ret;
	u8 *ssid = शून्य, ssid_len = 0;
	काष्ठा iw_scan_req *req = (काष्ठा iw_scan_req *) extra;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (data->length < माप(काष्ठा iw_scan_req))
		req = शून्य;

	अगर (local->iw_mode == IW_MODE_MASTER) अणु
		/* In master mode, we just वापस the results of our local
		 * tables, so we करोn't need to start anything...
		 * Jean II */
		data->length = 0;
		वापस 0;
	पूर्ण

	अगर (!local->dev_enabled)
		वापस -ENETDOWN;

	अगर (req && data->flags & IW_SCAN_THIS_ESSID) अणु
		ssid = req->essid;
		ssid_len = req->essid_len;

		अगर (ssid_len &&
		    ((local->iw_mode != IW_MODE_INFRA &&
		      local->iw_mode != IW_MODE_ADHOC) ||
		     (local->sta_fw_ver < PRISM2_FW_VER(1,3,1))))
			वापस -EOPNOTSUPP;
	पूर्ण

	अगर (local->sta_fw_ver >= PRISM2_FW_VER(1,3,1))
		ret = prism2_request_hostscan(dev, ssid, ssid_len);
	अन्यथा
		ret = prism2_request_scan(dev);

	अगर (ret == 0)
		local->scan_बारtamp = jअगरfies;

	/* Could inquire F101, F103 or रुको क्रम SIOCGIWSCAN and पढ़ो RID */

	वापस ret;
पूर्ण


#अगर_अघोषित PRISM2_NO_STATION_MODES
अटल अक्षर * __prism2_translate_scan(local_info_t *local,
				      काष्ठा iw_request_info *info,
				      काष्ठा hfa384x_hostscan_result *scan,
				      काष्ठा hostap_bss_info *bss,
				      अक्षर *current_ev, अक्षर *end_buf)
अणु
	पूर्णांक i, chan;
	काष्ठा iw_event iwe;
	अक्षर *current_val;
	u16 capabilities;
	u8 *pos;
	u8 *ssid, *bssid;
	माप_प्रकार ssid_len;
	अक्षर *buf;

	अगर (bss) अणु
		ssid = bss->ssid;
		ssid_len = bss->ssid_len;
		bssid = bss->bssid;
	पूर्ण अन्यथा अणु
		ssid = scan->ssid;
		ssid_len = le16_to_cpu(scan->ssid_len);
		bssid = scan->bssid;
	पूर्ण
	अगर (ssid_len > 32)
		ssid_len = 32;

	/* First entry *MUST* be the AP MAC address */
	स_रखो(&iwe, 0, माप(iwe));
	iwe.cmd = SIOCGIWAP;
	iwe.u.ap_addr.sa_family = ARPHRD_ETHER;
	स_नकल(iwe.u.ap_addr.sa_data, bssid, ETH_ALEN);
	current_ev = iwe_stream_add_event(info, current_ev, end_buf, &iwe,
					  IW_EV_ADDR_LEN);

	/* Other entries will be displayed in the order we give them */

	स_रखो(&iwe, 0, माप(iwe));
	iwe.cmd = SIOCGIWESSID;
	iwe.u.data.length = ssid_len;
	iwe.u.data.flags = 1;
	current_ev = iwe_stream_add_poपूर्णांक(info, current_ev, end_buf,
					  &iwe, ssid);

	स_रखो(&iwe, 0, माप(iwe));
	iwe.cmd = SIOCGIWMODE;
	अगर (bss) अणु
		capabilities = bss->capab_info;
	पूर्ण अन्यथा अणु
		capabilities = le16_to_cpu(scan->capability);
	पूर्ण
	अगर (capabilities & (WLAN_CAPABILITY_ESS |
			    WLAN_CAPABILITY_IBSS)) अणु
		अगर (capabilities & WLAN_CAPABILITY_ESS)
			iwe.u.mode = IW_MODE_MASTER;
		अन्यथा
			iwe.u.mode = IW_MODE_ADHOC;
		current_ev = iwe_stream_add_event(info, current_ev, end_buf,
						  &iwe, IW_EV_UINT_LEN);
	पूर्ण

	स_रखो(&iwe, 0, माप(iwe));
	iwe.cmd = SIOCGIWFREQ;
	अगर (scan) अणु
		chan = le16_to_cpu(scan->chid);
	पूर्ण अन्यथा अगर (bss) अणु
		chan = bss->chan;
	पूर्ण अन्यथा अणु
		chan = 0;
	पूर्ण

	अगर (chan > 0) अणु
		iwe.u.freq.m = freq_list[chan - 1] * 100000;
		iwe.u.freq.e = 1;
		current_ev = iwe_stream_add_event(info, current_ev, end_buf,
						  &iwe, IW_EV_FREQ_LEN);
	पूर्ण

	अगर (scan) अणु
		स_रखो(&iwe, 0, माप(iwe));
		iwe.cmd = IWEVQUAL;
		अगर (local->last_scan_type == PRISM2_HOSTSCAN) अणु
			iwe.u.qual.level = le16_to_cpu(scan->sl);
			iwe.u.qual.noise = le16_to_cpu(scan->anl);
		पूर्ण अन्यथा अणु
			iwe.u.qual.level =
				HFA384X_LEVEL_TO_dBm(le16_to_cpu(scan->sl));
			iwe.u.qual.noise =
				HFA384X_LEVEL_TO_dBm(le16_to_cpu(scan->anl));
		पूर्ण
		iwe.u.qual.updated = IW_QUAL_LEVEL_UPDATED
			| IW_QUAL_NOISE_UPDATED
			| IW_QUAL_QUAL_INVALID
			| IW_QUAL_DBM;
		current_ev = iwe_stream_add_event(info, current_ev, end_buf,
						  &iwe, IW_EV_QUAL_LEN);
	पूर्ण

	स_रखो(&iwe, 0, माप(iwe));
	iwe.cmd = SIOCGIWENCODE;
	अगर (capabilities & WLAN_CAPABILITY_PRIVACY)
		iwe.u.data.flags = IW_ENCODE_ENABLED | IW_ENCODE_NOKEY;
	अन्यथा
		iwe.u.data.flags = IW_ENCODE_DISABLED;
	iwe.u.data.length = 0;
	current_ev = iwe_stream_add_poपूर्णांक(info, current_ev, end_buf, &iwe, "");

	/* TODO: add SuppRates पूर्णांकo BSS table */
	अगर (scan) अणु
		स_रखो(&iwe, 0, माप(iwe));
		iwe.cmd = SIOCGIWRATE;
		current_val = current_ev + iwe_stream_lcp_len(info);
		pos = scan->sup_rates;
		क्रम (i = 0; i < माप(scan->sup_rates); i++) अणु
			अगर (pos[i] == 0)
				अवरोध;
			/* Bit rate given in 500 kb/s units (+ 0x80) */
			iwe.u.bitrate.value = ((pos[i] & 0x7f) * 500000);
			current_val = iwe_stream_add_value(
				info, current_ev, current_val, end_buf, &iwe,
				IW_EV_PARAM_LEN);
		पूर्ण
		/* Check अगर we added any event */
		अगर ((current_val - current_ev) > iwe_stream_lcp_len(info))
			current_ev = current_val;
	पूर्ण

	/* TODO: add BeaconInt,resp_rate,atim पूर्णांकo BSS table */
	buf = kदो_स्मृति(MAX_WPA_IE_LEN * 2 + 30, GFP_ATOMIC);
	अगर (buf && scan) अणु
		स_रखो(&iwe, 0, माप(iwe));
		iwe.cmd = IWEVCUSTOM;
		प्र_लिखो(buf, "bcn_int=%d", le16_to_cpu(scan->beacon_पूर्णांकerval));
		iwe.u.data.length = म_माप(buf);
		current_ev = iwe_stream_add_poपूर्णांक(info, current_ev, end_buf,
						  &iwe, buf);

		स_रखो(&iwe, 0, माप(iwe));
		iwe.cmd = IWEVCUSTOM;
		प्र_लिखो(buf, "resp_rate=%d", le16_to_cpu(scan->rate));
		iwe.u.data.length = म_माप(buf);
		current_ev = iwe_stream_add_poपूर्णांक(info, current_ev, end_buf,
						  &iwe, buf);

		अगर (local->last_scan_type == PRISM2_HOSTSCAN &&
		    (capabilities & WLAN_CAPABILITY_IBSS)) अणु
			स_रखो(&iwe, 0, माप(iwe));
			iwe.cmd = IWEVCUSTOM;
			प्र_लिखो(buf, "atim=%d", le16_to_cpu(scan->atim));
			iwe.u.data.length = म_माप(buf);
			current_ev = iwe_stream_add_poपूर्णांक(info, current_ev,
							  end_buf, &iwe, buf);
		पूर्ण
	पूर्ण
	kमुक्त(buf);

	अगर (bss && bss->wpa_ie_len > 0 && bss->wpa_ie_len <= MAX_WPA_IE_LEN) अणु
		स_रखो(&iwe, 0, माप(iwe));
		iwe.cmd = IWEVGENIE;
		iwe.u.data.length = bss->wpa_ie_len;
		current_ev = iwe_stream_add_poपूर्णांक(info, current_ev, end_buf,
						  &iwe, bss->wpa_ie);
	पूर्ण

	अगर (bss && bss->rsn_ie_len > 0 && bss->rsn_ie_len <= MAX_WPA_IE_LEN) अणु
		स_रखो(&iwe, 0, माप(iwe));
		iwe.cmd = IWEVGENIE;
		iwe.u.data.length = bss->rsn_ie_len;
		current_ev = iwe_stream_add_poपूर्णांक(info, current_ev, end_buf,
						  &iwe, bss->rsn_ie);
	पूर्ण

	वापस current_ev;
पूर्ण


/* Translate scan data वापसed from the card to a card independent
 * क्रमmat that the Wireless Tools will understand - Jean II */
अटल अंतरभूत पूर्णांक prism2_translate_scan(local_info_t *local,
					काष्ठा iw_request_info *info,
					अक्षर *buffer, पूर्णांक buflen)
अणु
	काष्ठा hfa384x_hostscan_result *scan;
	पूर्णांक entry;
	अक्षर *current_ev = buffer;
	अक्षर *end_buf = buffer + buflen;
	काष्ठा list_head *ptr;

	spin_lock_bh(&local->lock);

	list_क्रम_each(ptr, &local->bss_list) अणु
		काष्ठा hostap_bss_info *bss;
		bss = list_entry(ptr, काष्ठा hostap_bss_info, list);
		bss->included = 0;
	पूर्ण

	क्रम (entry = 0; entry < local->last_scan_results_count; entry++) अणु
		पूर्णांक found = 0;
		scan = &local->last_scan_results[entry];

		/* Report every SSID अगर the AP is using multiple SSIDs. If no
		 * BSS record is found (e.g., when WPA mode is disabled),
		 * report the AP once. */
		list_क्रम_each(ptr, &local->bss_list) अणु
			काष्ठा hostap_bss_info *bss;
			bss = list_entry(ptr, काष्ठा hostap_bss_info, list);
			अगर (ether_addr_equal(bss->bssid, scan->bssid)) अणु
				bss->included = 1;
				current_ev = __prism2_translate_scan(
					local, info, scan, bss, current_ev,
					end_buf);
				found++;
			पूर्ण
		पूर्ण
		अगर (!found) अणु
			current_ev = __prism2_translate_scan(
				local, info, scan, शून्य, current_ev, end_buf);
		पूर्ण
		/* Check अगर there is space क्रम one more entry */
		अगर ((end_buf - current_ev) <= IW_EV_ADDR_LEN) अणु
			/* Ask user space to try again with a bigger buffer */
			spin_unlock_bh(&local->lock);
			वापस -E2BIG;
		पूर्ण
	पूर्ण

	/* Prism2 firmware has limits (32 at least in some versions) क्रम number
	 * of BSSes in scan results. Extend this limit by using local BSS list.
	 */
	list_क्रम_each(ptr, &local->bss_list) अणु
		काष्ठा hostap_bss_info *bss;
		bss = list_entry(ptr, काष्ठा hostap_bss_info, list);
		अगर (bss->included)
			जारी;
		current_ev = __prism2_translate_scan(local, info, शून्य, bss,
						     current_ev, end_buf);
		/* Check अगर there is space क्रम one more entry */
		अगर ((end_buf - current_ev) <= IW_EV_ADDR_LEN) अणु
			/* Ask user space to try again with a bigger buffer */
			spin_unlock_bh(&local->lock);
			वापस -E2BIG;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&local->lock);

	वापस current_ev - buffer;
पूर्ण
#पूर्ण_अगर /* PRISM2_NO_STATION_MODES */


अटल अंतरभूत पूर्णांक prism2_ioctl_giwscan_sta(काष्ठा net_device *dev,
					   काष्ठा iw_request_info *info,
					   काष्ठा iw_poपूर्णांक *data, अक्षर *extra)
अणु
#अगर_घोषित PRISM2_NO_STATION_MODES
	वापस -EOPNOTSUPP;
#अन्यथा /* PRISM2_NO_STATION_MODES */
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक res;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	/* Wait until the scan is finished. We can probably करो better
	 * than that - Jean II */
	अगर (local->scan_बारtamp &&
	    समय_beक्रमe(jअगरfies, local->scan_बारtamp + 3 * HZ)) अणु
		/* Important note : we करोn't want to block the caller
		 * until results are पढ़ोy क्रम various reasons.
		 * First, managing रुको queues is complex and racy
		 * (there may be multiple simultaneous callers).
		 * Second, we grab some rtnetlink lock beक्रमe coming
		 * here (in dev_ioctl()).
		 * Third, the caller can रुको on the Wireless Event
		 * - Jean II */
		वापस -EAGAIN;
	पूर्ण
	local->scan_बारtamp = 0;

	res = prism2_translate_scan(local, info, extra, data->length);

	अगर (res >= 0) अणु
		data->length = res;
		वापस 0;
	पूर्ण अन्यथा अणु
		data->length = 0;
		वापस res;
	पूर्ण
#पूर्ण_अगर /* PRISM2_NO_STATION_MODES */
पूर्ण


अटल पूर्णांक prism2_ioctl_giwscan(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				काष्ठा iw_poपूर्णांक *data, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक res;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (local->iw_mode == IW_MODE_MASTER) अणु
		/* In MASTER mode, it करोesn't make sense to go around
		 * scanning the frequencies and make the stations we serve
		 * रुको when what the user is really पूर्णांकerested about is the
		 * list of stations and access poपूर्णांकs we are talking to.
		 * So, just extract results from our cache...
		 * Jean II */

		/* Translate to WE क्रमmat */
		res = prism2_ap_translate_scan(dev, info, extra);
		अगर (res >= 0) अणु
			prपूर्णांकk(KERN_DEBUG "Scan result translation succeeded "
			       "(length=%d)\n", res);
			data->length = res;
			वापस 0;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_DEBUG
			       "Scan result translation failed (res=%d)\n",
			       res);
			data->length = 0;
			वापस res;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Station mode */
		वापस prism2_ioctl_giwscan_sta(dev, info, data, extra);
	पूर्ण
पूर्ण


अटल स्थिर काष्ठा iw_priv_args prism2_priv[] = अणु
	अणु PRISM2_IOCTL_MONITOR,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "monitor" पूर्ण,
	अणु PRISM2_IOCTL_READMIF,
	  IW_PRIV_TYPE_BYTE | IW_PRIV_SIZE_FIXED | 1,
	  IW_PRIV_TYPE_BYTE | IW_PRIV_SIZE_FIXED | 1, "readmif" पूर्ण,
	अणु PRISM2_IOCTL_WRITEMIF,
	  IW_PRIV_TYPE_BYTE | IW_PRIV_SIZE_FIXED | 2, 0, "writemif" पूर्ण,
	अणु PRISM2_IOCTL_RESET,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "reset" पूर्ण,
	अणु PRISM2_IOCTL_INQUIRE,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "inquire" पूर्ण,
	अणु PRISM2_IOCTL_SET_RID_WORD,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 2, 0, "set_rid_word" पूर्ण,
	अणु PRISM2_IOCTL_MACCMD,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "maccmd" पूर्ण,
	अणु PRISM2_IOCTL_WDS_ADD,
	  IW_PRIV_TYPE_ADDR | IW_PRIV_SIZE_FIXED | 1, 0, "wds_add" पूर्ण,
	अणु PRISM2_IOCTL_WDS_DEL,
	  IW_PRIV_TYPE_ADDR | IW_PRIV_SIZE_FIXED | 1, 0, "wds_del" पूर्ण,
	अणु PRISM2_IOCTL_ADDMAC,
	  IW_PRIV_TYPE_ADDR | IW_PRIV_SIZE_FIXED | 1, 0, "addmac" पूर्ण,
	अणु PRISM2_IOCTL_DELMAC,
	  IW_PRIV_TYPE_ADDR | IW_PRIV_SIZE_FIXED | 1, 0, "delmac" पूर्ण,
	अणु PRISM2_IOCTL_KICKMAC,
	  IW_PRIV_TYPE_ADDR | IW_PRIV_SIZE_FIXED | 1, 0, "kickmac" पूर्ण,
	/* --- raw access to sub-ioctls --- */
	अणु PRISM2_IOCTL_PRISM2_PARAM,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 2, 0, "prism2_param" पूर्ण,
	अणु PRISM2_IOCTL_GET_PRISM2_PARAM,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getprism2_param" पूर्ण,
	/* --- sub-ioctls handlers --- */
	अणु PRISM2_IOCTL_PRISM2_PARAM,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "" पूर्ण,
	अणु PRISM2_IOCTL_GET_PRISM2_PARAM,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "" पूर्ण,
	/* --- sub-ioctls definitions --- */
	अणु PRISM2_PARAM_TXRATECTRL,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "txratectrl" पूर्ण,
	अणु PRISM2_PARAM_TXRATECTRL,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "gettxratectrl" पूर्ण,
	अणु PRISM2_PARAM_BEACON_INT,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "beacon_int" पूर्ण,
	अणु PRISM2_PARAM_BEACON_INT,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getbeacon_int" पूर्ण,
#अगर_अघोषित PRISM2_NO_STATION_MODES
	अणु PRISM2_PARAM_PSEUDO_IBSS,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "pseudo_ibss" पूर्ण,
	अणु PRISM2_PARAM_PSEUDO_IBSS,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getpseudo_ibss" पूर्ण,
#पूर्ण_अगर /* PRISM2_NO_STATION_MODES */
	अणु PRISM2_PARAM_ALC,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "alc" पूर्ण,
	अणु PRISM2_PARAM_ALC,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getalc" पूर्ण,
	अणु PRISM2_PARAM_DUMP,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "dump" पूर्ण,
	अणु PRISM2_PARAM_DUMP,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getdump" पूर्ण,
	अणु PRISM2_PARAM_OTHER_AP_POLICY,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "other_ap_policy" पूर्ण,
	अणु PRISM2_PARAM_OTHER_AP_POLICY,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getother_ap_pol" पूर्ण,
	अणु PRISM2_PARAM_AP_MAX_INACTIVITY,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "max_inactivity" पूर्ण,
	अणु PRISM2_PARAM_AP_MAX_INACTIVITY,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getmax_inactivi" पूर्ण,
	अणु PRISM2_PARAM_AP_BRIDGE_PACKETS,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "bridge_packets" पूर्ण,
	अणु PRISM2_PARAM_AP_BRIDGE_PACKETS,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getbridge_packe" पूर्ण,
	अणु PRISM2_PARAM_DTIM_PERIOD,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "dtim_period" पूर्ण,
	अणु PRISM2_PARAM_DTIM_PERIOD,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getdtim_period" पूर्ण,
	अणु PRISM2_PARAM_AP_शून्यFUNC_ACK,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "nullfunc_ack" पूर्ण,
	अणु PRISM2_PARAM_AP_शून्यFUNC_ACK,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getnullfunc_ack" पूर्ण,
	अणु PRISM2_PARAM_MAX_WDS,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "max_wds" पूर्ण,
	अणु PRISM2_PARAM_MAX_WDS,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getmax_wds" पूर्ण,
	अणु PRISM2_PARAM_AP_AUTOM_AP_WDS,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "autom_ap_wds" पूर्ण,
	अणु PRISM2_PARAM_AP_AUTOM_AP_WDS,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getautom_ap_wds" पूर्ण,
	अणु PRISM2_PARAM_AP_AUTH_ALGS,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "ap_auth_algs" पूर्ण,
	अणु PRISM2_PARAM_AP_AUTH_ALGS,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getap_auth_algs" पूर्ण,
	अणु PRISM2_PARAM_MONITOR_ALLOW_FCSERR,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "allow_fcserr" पूर्ण,
	अणु PRISM2_PARAM_MONITOR_ALLOW_FCSERR,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getallow_fcserr" पूर्ण,
	अणु PRISM2_PARAM_HOST_ENCRYPT,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "host_encrypt" पूर्ण,
	अणु PRISM2_PARAM_HOST_ENCRYPT,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "gethost_encrypt" पूर्ण,
	अणु PRISM2_PARAM_HOST_DECRYPT,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "host_decrypt" पूर्ण,
	अणु PRISM2_PARAM_HOST_DECRYPT,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "gethost_decrypt" पूर्ण,
#अगर_अघोषित PRISM2_NO_STATION_MODES
	अणु PRISM2_PARAM_HOST_ROAMING,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "host_roaming" पूर्ण,
	अणु PRISM2_PARAM_HOST_ROAMING,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "gethost_roaming" पूर्ण,
#पूर्ण_अगर /* PRISM2_NO_STATION_MODES */
	अणु PRISM2_PARAM_BCRX_STA_KEY,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "bcrx_sta_key" पूर्ण,
	अणु PRISM2_PARAM_BCRX_STA_KEY,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getbcrx_sta_key" पूर्ण,
	अणु PRISM2_PARAM_IEEE_802_1X,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "ieee_802_1x" पूर्ण,
	अणु PRISM2_PARAM_IEEE_802_1X,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getieee_802_1x" पूर्ण,
	अणु PRISM2_PARAM_ANTSEL_TX,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "antsel_tx" पूर्ण,
	अणु PRISM2_PARAM_ANTSEL_TX,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getantsel_tx" पूर्ण,
	अणु PRISM2_PARAM_ANTSEL_RX,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "antsel_rx" पूर्ण,
	अणु PRISM2_PARAM_ANTSEL_RX,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getantsel_rx" पूर्ण,
	अणु PRISM2_PARAM_MONITOR_TYPE,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "monitor_type" पूर्ण,
	अणु PRISM2_PARAM_MONITOR_TYPE,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getmonitor_type" पूर्ण,
	अणु PRISM2_PARAM_WDS_TYPE,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "wds_type" पूर्ण,
	अणु PRISM2_PARAM_WDS_TYPE,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getwds_type" पूर्ण,
	अणु PRISM2_PARAM_HOSTSCAN,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "hostscan" पूर्ण,
	अणु PRISM2_PARAM_HOSTSCAN,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "gethostscan" पूर्ण,
	अणु PRISM2_PARAM_AP_SCAN,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "ap_scan" पूर्ण,
	अणु PRISM2_PARAM_AP_SCAN,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getap_scan" पूर्ण,
	अणु PRISM2_PARAM_ENH_SEC,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "enh_sec" पूर्ण,
	अणु PRISM2_PARAM_ENH_SEC,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getenh_sec" पूर्ण,
#अगर_घोषित PRISM2_IO_DEBUG
	अणु PRISM2_PARAM_IO_DEBUG,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "io_debug" पूर्ण,
	अणु PRISM2_PARAM_IO_DEBUG,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getio_debug" पूर्ण,
#पूर्ण_अगर /* PRISM2_IO_DEBUG */
	अणु PRISM2_PARAM_BASIC_RATES,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "basic_rates" पूर्ण,
	अणु PRISM2_PARAM_BASIC_RATES,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getbasic_rates" पूर्ण,
	अणु PRISM2_PARAM_OPER_RATES,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "oper_rates" पूर्ण,
	अणु PRISM2_PARAM_OPER_RATES,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getoper_rates" पूर्ण,
	अणु PRISM2_PARAM_HOSTAPD,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "hostapd" पूर्ण,
	अणु PRISM2_PARAM_HOSTAPD,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "gethostapd" पूर्ण,
	अणु PRISM2_PARAM_HOSTAPD_STA,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "hostapd_sta" पूर्ण,
	अणु PRISM2_PARAM_HOSTAPD_STA,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "gethostapd_sta" पूर्ण,
	अणु PRISM2_PARAM_WPA,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "wpa" पूर्ण,
	अणु PRISM2_PARAM_WPA,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getwpa" पूर्ण,
	अणु PRISM2_PARAM_PRIVACY_INVOKED,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "privacy_invoked" पूर्ण,
	अणु PRISM2_PARAM_PRIVACY_INVOKED,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getprivacy_invo" पूर्ण,
	अणु PRISM2_PARAM_TKIP_COUNTERMEASURES,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "tkip_countermea" पूर्ण,
	अणु PRISM2_PARAM_TKIP_COUNTERMEASURES,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "gettkip_counter" पूर्ण,
	अणु PRISM2_PARAM_DROP_UNENCRYPTED,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "drop_unencrypte" पूर्ण,
	अणु PRISM2_PARAM_DROP_UNENCRYPTED,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getdrop_unencry" पूर्ण,
	अणु PRISM2_PARAM_SCAN_CHANNEL_MASK,
	  IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "scan_channels" पूर्ण,
	अणु PRISM2_PARAM_SCAN_CHANNEL_MASK,
	  0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, "getscan_channel" पूर्ण,
पूर्ण;


अटल पूर्णांक prism2_ioctl_priv_inquire(काष्ठा net_device *dev, पूर्णांक *i)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (local->func->cmd(dev, HFA384X_CMDCODE_INQUIRE, *i, शून्य, शून्य))
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण


अटल पूर्णांक prism2_ioctl_priv_prism2_param(काष्ठा net_device *dev,
					  काष्ठा iw_request_info *info,
					  व्योम *wrqu, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक *i = (पूर्णांक *) extra;
	पूर्णांक param = *i;
	पूर्णांक value = *(i + 1);
	पूर्णांक ret = 0;
	u16 val;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	चयन (param) अणु
	हाल PRISM2_PARAM_TXRATECTRL:
		local->fw_tx_rate_control = value;
		अवरोध;

	हाल PRISM2_PARAM_BEACON_INT:
		अगर (hostap_set_word(dev, HFA384X_RID_CNFBEACONINT, value) ||
		    local->func->reset_port(dev))
			ret = -EINVAL;
		अन्यथा
			local->beacon_पूर्णांक = value;
		अवरोध;

#अगर_अघोषित PRISM2_NO_STATION_MODES
	हाल PRISM2_PARAM_PSEUDO_IBSS:
		अगर (value == local->pseuकरो_adhoc)
			अवरोध;

		अगर (value != 0 && value != 1) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		prपूर्णांकk(KERN_DEBUG "prism2: %s: pseudo IBSS change %d -> %d\n",
		       dev->name, local->pseuकरो_adhoc, value);
		local->pseuकरो_adhoc = value;
		अगर (local->iw_mode != IW_MODE_ADHOC)
			अवरोध;

		अगर (hostap_set_word(dev, HFA384X_RID_CNFPORTTYPE,
				    hostap_get_porttype(local))) अणु
			ret = -EOPNOTSUPP;
			अवरोध;
		पूर्ण

		अगर (local->func->reset_port(dev))
			ret = -EINVAL;
		अवरोध;
#पूर्ण_अगर /* PRISM2_NO_STATION_MODES */

	हाल PRISM2_PARAM_ALC:
		prपूर्णांकk(KERN_DEBUG "%s: %s ALC\n", dev->name,
		       value == 0 ? "Disabling" : "Enabling");
		val = HFA384X_TEST_CFG_BIT_ALC;
		local->func->cmd(dev, HFA384X_CMDCODE_TEST |
				 (HFA384X_TEST_CFG_BITS << 8),
				 value == 0 ? 0 : 1, &val, शून्य);
		अवरोध;

	हाल PRISM2_PARAM_DUMP:
		local->frame_dump = value;
		अवरोध;

	हाल PRISM2_PARAM_OTHER_AP_POLICY:
		अगर (value < 0 || value > 3) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (local->ap != शून्य)
			local->ap->ap_policy = value;
		अवरोध;

	हाल PRISM2_PARAM_AP_MAX_INACTIVITY:
		अगर (value < 0 || value > 7 * 24 * 60 * 60) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (local->ap != शून्य)
			local->ap->max_inactivity = value * HZ;
		अवरोध;

	हाल PRISM2_PARAM_AP_BRIDGE_PACKETS:
		अगर (local->ap != शून्य)
			local->ap->bridge_packets = value;
		अवरोध;

	हाल PRISM2_PARAM_DTIM_PERIOD:
		अगर (value < 0 || value > 65535) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (hostap_set_word(dev, HFA384X_RID_CNFOWNDTIMPERIOD, value)
		    || local->func->reset_port(dev))
			ret = -EINVAL;
		अन्यथा
			local->dtim_period = value;
		अवरोध;

	हाल PRISM2_PARAM_AP_शून्यFUNC_ACK:
		अगर (local->ap != शून्य)
			local->ap->nullfunc_ack = value;
		अवरोध;

	हाल PRISM2_PARAM_MAX_WDS:
		local->wds_max_connections = value;
		अवरोध;

	हाल PRISM2_PARAM_AP_AUTOM_AP_WDS:
		अगर (local->ap != शून्य) अणु
			अगर (!local->ap->स्वतःm_ap_wds && value) अणु
				/* add WDS link to all APs in STA table */
				hostap_add_wds_links(local);
			पूर्ण
			local->ap->स्वतःm_ap_wds = value;
		पूर्ण
		अवरोध;

	हाल PRISM2_PARAM_AP_AUTH_ALGS:
		local->auth_algs = value;
		अगर (hostap_set_auth_algs(local))
			ret = -EINVAL;
		अवरोध;

	हाल PRISM2_PARAM_MONITOR_ALLOW_FCSERR:
		local->monitor_allow_fcserr = value;
		अवरोध;

	हाल PRISM2_PARAM_HOST_ENCRYPT:
		local->host_encrypt = value;
		अगर (hostap_set_encryption(local) ||
		    local->func->reset_port(dev))
			ret = -EINVAL;
		अवरोध;

	हाल PRISM2_PARAM_HOST_DECRYPT:
		local->host_decrypt = value;
		अगर (hostap_set_encryption(local) ||
		    local->func->reset_port(dev))
			ret = -EINVAL;
		अवरोध;

#अगर_अघोषित PRISM2_NO_STATION_MODES
	हाल PRISM2_PARAM_HOST_ROAMING:
		अगर (value < 0 || value > 2) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		local->host_roaming = value;
		अगर (hostap_set_roaming(local) || local->func->reset_port(dev))
			ret = -EINVAL;
		अवरोध;
#पूर्ण_अगर /* PRISM2_NO_STATION_MODES */

	हाल PRISM2_PARAM_BCRX_STA_KEY:
		local->bcrx_sta_key = value;
		अवरोध;

	हाल PRISM2_PARAM_IEEE_802_1X:
		local->ieee_802_1x = value;
		अवरोध;

	हाल PRISM2_PARAM_ANTSEL_TX:
		अगर (value < 0 || value > HOSTAP_ANTSEL_HIGH) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		local->antsel_tx = value;
		hostap_set_antsel(local);
		अवरोध;

	हाल PRISM2_PARAM_ANTSEL_RX:
		अगर (value < 0 || value > HOSTAP_ANTSEL_HIGH) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		local->antsel_rx = value;
		hostap_set_antsel(local);
		अवरोध;

	हाल PRISM2_PARAM_MONITOR_TYPE:
		अगर (value != PRISM2_MONITOR_80211 &&
		    value != PRISM2_MONITOR_CAPHDR &&
		    value != PRISM2_MONITOR_PRISM &&
		    value != PRISM2_MONITOR_RADIOTAP) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		local->monitor_type = value;
		अगर (local->iw_mode == IW_MODE_MONITOR)
			hostap_monitor_set_type(local);
		अवरोध;

	हाल PRISM2_PARAM_WDS_TYPE:
		local->wds_type = value;
		अवरोध;

	हाल PRISM2_PARAM_HOSTSCAN:
	अणु
		काष्ठा hfa384x_hostscan_request scan_req;
		u16 rate;

		स_रखो(&scan_req, 0, माप(scan_req));
		scan_req.channel_list = cpu_to_le16(0x3fff);
		चयन (value) अणु
		हाल 1: rate = HFA384X_RATES_1MBPS; अवरोध;
		हाल 2: rate = HFA384X_RATES_2MBPS; अवरोध;
		हाल 3: rate = HFA384X_RATES_5MBPS; अवरोध;
		हाल 4: rate = HFA384X_RATES_11MBPS; अवरोध;
		शेष: rate = HFA384X_RATES_1MBPS; अवरोध;
		पूर्ण
		scan_req.txrate = cpu_to_le16(rate);
		/* leave SSID empty to accept all SSIDs */

		अगर (local->iw_mode == IW_MODE_MASTER) अणु
			अगर (hostap_set_word(dev, HFA384X_RID_CNFPORTTYPE,
					    HFA384X_PORTTYPE_BSS) ||
			    local->func->reset_port(dev))
				prपूर्णांकk(KERN_DEBUG "Leaving Host AP mode "
				       "for HostScan failed\n");
		पूर्ण

		अगर (local->func->set_rid(dev, HFA384X_RID_HOSTSCAN, &scan_req,
					 माप(scan_req))) अणु
			prपूर्णांकk(KERN_DEBUG "HOSTSCAN failed\n");
			ret = -EINVAL;
		पूर्ण
		अगर (local->iw_mode == IW_MODE_MASTER) अणु
			रुको_queue_entry_t __रुको;
			init_रुकोqueue_entry(&__रुको, current);
			add_रुको_queue(&local->hostscan_wq, &__रुको);
			set_current_state(TASK_INTERRUPTIBLE);
			schedule_समयout(HZ);
			अगर (संकेत_pending(current))
				ret = -EINTR;
			set_current_state(TASK_RUNNING);
			हटाओ_रुको_queue(&local->hostscan_wq, &__रुको);

			अगर (hostap_set_word(dev, HFA384X_RID_CNFPORTTYPE,
					    HFA384X_PORTTYPE_HOSTAP) ||
			    local->func->reset_port(dev))
				prपूर्णांकk(KERN_DEBUG "Returning to Host AP mode "
				       "after HostScan failed\n");
		पूर्ण
		अवरोध;
	पूर्ण

	हाल PRISM2_PARAM_AP_SCAN:
		local->passive_scan_पूर्णांकerval = value;
		अगर (समयr_pending(&local->passive_scan_समयr))
			del_समयr(&local->passive_scan_समयr);
		अगर (value > 0 && value < पूर्णांक_उच्च / HZ) अणु
			local->passive_scan_समयr.expires = jअगरfies +
				local->passive_scan_पूर्णांकerval * HZ;
			add_समयr(&local->passive_scan_समयr);
		पूर्ण
		अवरोध;

	हाल PRISM2_PARAM_ENH_SEC:
		अगर (value < 0 || value > 3) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		local->enh_sec = value;
		अगर (hostap_set_word(dev, HFA384X_RID_CNFENHSECURITY,
				    local->enh_sec) ||
		    local->func->reset_port(dev)) अणु
			prपूर्णांकk(KERN_INFO "%s: cnfEnhSecurity requires STA f/w "
			       "1.6.3 or newer\n", dev->name);
			ret = -EOPNOTSUPP;
		पूर्ण
		अवरोध;

#अगर_घोषित PRISM2_IO_DEBUG
	हाल PRISM2_PARAM_IO_DEBUG:
		local->io_debug_enabled = value;
		अवरोध;
#पूर्ण_अगर /* PRISM2_IO_DEBUG */

	हाल PRISM2_PARAM_BASIC_RATES:
		अगर ((value & local->tx_rate_control) != value || value == 0) अणु
			prपूर्णांकk(KERN_INFO "%s: invalid basic rate set - basic "
			       "rates must be in supported rate set\n",
			       dev->name);
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		local->basic_rates = value;
		अगर (hostap_set_word(dev, HFA384X_RID_CNFBASICRATES,
				    local->basic_rates) ||
		    local->func->reset_port(dev))
			ret = -EINVAL;
		अवरोध;

	हाल PRISM2_PARAM_OPER_RATES:
		local->tx_rate_control = value;
		अगर (hostap_set_rate(dev))
			ret = -EINVAL;
		अवरोध;

	हाल PRISM2_PARAM_HOSTAPD:
		ret = hostap_set_hostapd(local, value, 1);
		अवरोध;

	हाल PRISM2_PARAM_HOSTAPD_STA:
		ret = hostap_set_hostapd_sta(local, value, 1);
		अवरोध;

	हाल PRISM2_PARAM_WPA:
		local->wpa = value;
		अगर (local->sta_fw_ver < PRISM2_FW_VER(1,7,0))
			ret = -EOPNOTSUPP;
		अन्यथा अगर (hostap_set_word(dev, HFA384X_RID_SSNHANDLINGMODE,
					 value ? 1 : 0))
			ret = -EINVAL;
		अवरोध;

	हाल PRISM2_PARAM_PRIVACY_INVOKED:
		local->privacy_invoked = value;
		अगर (hostap_set_encryption(local) ||
		    local->func->reset_port(dev))
			ret = -EINVAL;
		अवरोध;

	हाल PRISM2_PARAM_TKIP_COUNTERMEASURES:
		local->tkip_countermeasures = value;
		अवरोध;

	हाल PRISM2_PARAM_DROP_UNENCRYPTED:
		local->drop_unencrypted = value;
		अवरोध;

	हाल PRISM2_PARAM_SCAN_CHANNEL_MASK:
		local->scan_channel_mask = value;
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_DEBUG "%s: prism2_param: unknown param %d\n",
		       dev->name, param);
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण


अटल पूर्णांक prism2_ioctl_priv_get_prism2_param(काष्ठा net_device *dev,
					      काष्ठा iw_request_info *info,
					      व्योम *wrqu, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक *param = (पूर्णांक *) extra;
	पूर्णांक ret = 0;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	चयन (*param) अणु
	हाल PRISM2_PARAM_TXRATECTRL:
		*param = local->fw_tx_rate_control;
		अवरोध;

	हाल PRISM2_PARAM_BEACON_INT:
		*param = local->beacon_पूर्णांक;
		अवरोध;

	हाल PRISM2_PARAM_PSEUDO_IBSS:
		*param = local->pseuकरो_adhoc;
		अवरोध;

	हाल PRISM2_PARAM_ALC:
		ret = -EOPNOTSUPP; /* FIX */
		अवरोध;

	हाल PRISM2_PARAM_DUMP:
		*param = local->frame_dump;
		अवरोध;

	हाल PRISM2_PARAM_OTHER_AP_POLICY:
		अगर (local->ap != शून्य)
			*param = local->ap->ap_policy;
		अन्यथा
			ret = -EOPNOTSUPP;
		अवरोध;

	हाल PRISM2_PARAM_AP_MAX_INACTIVITY:
		अगर (local->ap != शून्य)
			*param = local->ap->max_inactivity / HZ;
		अन्यथा
			ret = -EOPNOTSUPP;
		अवरोध;

	हाल PRISM2_PARAM_AP_BRIDGE_PACKETS:
		अगर (local->ap != शून्य)
			*param = local->ap->bridge_packets;
		अन्यथा
			ret = -EOPNOTSUPP;
		अवरोध;

	हाल PRISM2_PARAM_DTIM_PERIOD:
		*param = local->dtim_period;
		अवरोध;

	हाल PRISM2_PARAM_AP_शून्यFUNC_ACK:
		अगर (local->ap != शून्य)
			*param = local->ap->nullfunc_ack;
		अन्यथा
			ret = -EOPNOTSUPP;
		अवरोध;

	हाल PRISM2_PARAM_MAX_WDS:
		*param = local->wds_max_connections;
		अवरोध;

	हाल PRISM2_PARAM_AP_AUTOM_AP_WDS:
		अगर (local->ap != शून्य)
			*param = local->ap->स्वतःm_ap_wds;
		अन्यथा
			ret = -EOPNOTSUPP;
		अवरोध;

	हाल PRISM2_PARAM_AP_AUTH_ALGS:
		*param = local->auth_algs;
		अवरोध;

	हाल PRISM2_PARAM_MONITOR_ALLOW_FCSERR:
		*param = local->monitor_allow_fcserr;
		अवरोध;

	हाल PRISM2_PARAM_HOST_ENCRYPT:
		*param = local->host_encrypt;
		अवरोध;

	हाल PRISM2_PARAM_HOST_DECRYPT:
		*param = local->host_decrypt;
		अवरोध;

	हाल PRISM2_PARAM_HOST_ROAMING:
		*param = local->host_roaming;
		अवरोध;

	हाल PRISM2_PARAM_BCRX_STA_KEY:
		*param = local->bcrx_sta_key;
		अवरोध;

	हाल PRISM2_PARAM_IEEE_802_1X:
		*param = local->ieee_802_1x;
		अवरोध;

	हाल PRISM2_PARAM_ANTSEL_TX:
		*param = local->antsel_tx;
		अवरोध;

	हाल PRISM2_PARAM_ANTSEL_RX:
		*param = local->antsel_rx;
		अवरोध;

	हाल PRISM2_PARAM_MONITOR_TYPE:
		*param = local->monitor_type;
		अवरोध;

	हाल PRISM2_PARAM_WDS_TYPE:
		*param = local->wds_type;
		अवरोध;

	हाल PRISM2_PARAM_HOSTSCAN:
		ret = -EOPNOTSUPP;
		अवरोध;

	हाल PRISM2_PARAM_AP_SCAN:
		*param = local->passive_scan_पूर्णांकerval;
		अवरोध;

	हाल PRISM2_PARAM_ENH_SEC:
		*param = local->enh_sec;
		अवरोध;

#अगर_घोषित PRISM2_IO_DEBUG
	हाल PRISM2_PARAM_IO_DEBUG:
		*param = local->io_debug_enabled;
		अवरोध;
#पूर्ण_अगर /* PRISM2_IO_DEBUG */

	हाल PRISM2_PARAM_BASIC_RATES:
		*param = local->basic_rates;
		अवरोध;

	हाल PRISM2_PARAM_OPER_RATES:
		*param = local->tx_rate_control;
		अवरोध;

	हाल PRISM2_PARAM_HOSTAPD:
		*param = local->hostapd;
		अवरोध;

	हाल PRISM2_PARAM_HOSTAPD_STA:
		*param = local->hostapd_sta;
		अवरोध;

	हाल PRISM2_PARAM_WPA:
		अगर (local->sta_fw_ver < PRISM2_FW_VER(1,7,0))
			ret = -EOPNOTSUPP;
		*param = local->wpa;
		अवरोध;

	हाल PRISM2_PARAM_PRIVACY_INVOKED:
		*param = local->privacy_invoked;
		अवरोध;

	हाल PRISM2_PARAM_TKIP_COUNTERMEASURES:
		*param = local->tkip_countermeasures;
		अवरोध;

	हाल PRISM2_PARAM_DROP_UNENCRYPTED:
		*param = local->drop_unencrypted;
		अवरोध;

	हाल PRISM2_PARAM_SCAN_CHANNEL_MASK:
		*param = local->scan_channel_mask;
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_DEBUG "%s: get_prism2_param: unknown param %d\n",
		       dev->name, *param);
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण


अटल पूर्णांक prism2_ioctl_priv_पढ़ोmअगर(काष्ठा net_device *dev,
				     काष्ठा iw_request_info *info,
				     व्योम *wrqu, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	u16 resp0;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (local->func->cmd(dev, HFA384X_CMDCODE_READMIF, *extra, शून्य,
			     &resp0))
		वापस -EOPNOTSUPP;
	अन्यथा
		*extra = resp0;

	वापस 0;
पूर्ण


अटल पूर्णांक prism2_ioctl_priv_ग_लिखोmअगर(काष्ठा net_device *dev,
				      काष्ठा iw_request_info *info,
				      व्योम *wrqu, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	u16 cr, val;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	cr = *extra;
	val = *(extra + 1);
	अगर (local->func->cmd(dev, HFA384X_CMDCODE_WRITEMIF, cr, &val, शून्य))
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण


अटल पूर्णांक prism2_ioctl_priv_monitor(काष्ठा net_device *dev, पूर्णांक *i)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक ret = 0;
	u32 mode;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	prपूर्णांकk(KERN_DEBUG "%s: process %d (%s) used deprecated iwpriv monitor "
	       "- update software to use iwconfig mode monitor\n",
	       dev->name, task_pid_nr(current), current->comm);

	/* Backward compatibility code - this can be हटाओd at some poपूर्णांक */

	अगर (*i == 0) अणु
		/* Disable monitor mode - old mode was not saved, so go to
		 * Master mode */
		mode = IW_MODE_MASTER;
		ret = prism2_ioctl_siwmode(dev, शून्य, &mode, शून्य);
	पूर्ण अन्यथा अगर (*i == 1) अणु
		/* netlink socket mode is not supported anymore since it did
		 * not separate dअगरferent devices from each other and was not
		 * best method क्रम delivering large amount of packets to
		 * user space */
		ret = -EOPNOTSUPP;
	पूर्ण अन्यथा अगर (*i == 2 || *i == 3) अणु
		चयन (*i) अणु
		हाल 2:
			local->monitor_type = PRISM2_MONITOR_80211;
			अवरोध;
		हाल 3:
			local->monitor_type = PRISM2_MONITOR_PRISM;
			अवरोध;
		पूर्ण
		mode = IW_MODE_MONITOR;
		ret = prism2_ioctl_siwmode(dev, शून्य, &mode, शून्य);
		hostap_monitor_mode_enable(local);
	पूर्ण अन्यथा
		ret = -EINVAL;

	वापस ret;
पूर्ण


अटल पूर्णांक prism2_ioctl_priv_reset(काष्ठा net_device *dev, पूर्णांक *i)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	prपूर्णांकk(KERN_DEBUG "%s: manual reset request(%d)\n", dev->name, *i);
	चयन (*i) अणु
	हाल 0:
		/* Disable and enable card */
		local->func->hw_shutकरोwn(dev, 1);
		local->func->hw_config(dev, 0);
		अवरोध;

	हाल 1:
		/* COR sreset */
		local->func->hw_reset(dev);
		अवरोध;

	हाल 2:
		/* Disable and enable port 0 */
		local->func->reset_port(dev);
		अवरोध;

	हाल 3:
		prism2_sta_deauth(local, WLAN_REASON_DEAUTH_LEAVING);
		अगर (local->func->cmd(dev, HFA384X_CMDCODE_DISABLE, 0, शून्य,
				     शून्य))
			वापस -EINVAL;
		अवरोध;

	हाल 4:
		अगर (local->func->cmd(dev, HFA384X_CMDCODE_ENABLE, 0, शून्य,
				     शून्य))
			वापस -EINVAL;
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_DEBUG "Unknown reset request %d\n", *i);
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक prism2_ioctl_priv_set_rid_word(काष्ठा net_device *dev, पूर्णांक *i)
अणु
	पूर्णांक rid = *i;
	पूर्णांक value = *(i + 1);

	prपूर्णांकk(KERN_DEBUG "%s: Set RID[0x%X] = %d\n", dev->name, rid, value);

	अगर (hostap_set_word(dev, rid, value))
		वापस -EINVAL;

	वापस 0;
पूर्ण


#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT
अटल पूर्णांक ap_mac_cmd_ioctl(local_info_t *local, पूर्णांक *cmd)
अणु
	पूर्णांक ret = 0;

	चयन (*cmd) अणु
	हाल AP_MAC_CMD_POLICY_OPEN:
		local->ap->mac_restrictions.policy = MAC_POLICY_OPEN;
		अवरोध;
	हाल AP_MAC_CMD_POLICY_ALLOW:
		local->ap->mac_restrictions.policy = MAC_POLICY_ALLOW;
		अवरोध;
	हाल AP_MAC_CMD_POLICY_DENY:
		local->ap->mac_restrictions.policy = MAC_POLICY_DENY;
		अवरोध;
	हाल AP_MAC_CMD_FLUSH:
		ap_control_flush_macs(&local->ap->mac_restrictions);
		अवरोध;
	हाल AP_MAC_CMD_KICKALL:
		ap_control_kickall(local->ap);
		hostap_deauth_all_stas(local->dev, local->ap, 0);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */


#अगर_घोषित PRISM2_DOWNLOAD_SUPPORT
अटल पूर्णांक prism2_ioctl_priv_करोwnload(local_info_t *local, काष्ठा iw_poपूर्णांक *p)
अणु
	काष्ठा prism2_करोwnload_param *param;
	पूर्णांक ret = 0;

	अगर (p->length < माप(काष्ठा prism2_करोwnload_param) ||
	    p->length > 1024 || !p->poपूर्णांकer)
		वापस -EINVAL;

	param = memdup_user(p->poपूर्णांकer, p->length);
	अगर (IS_ERR(param)) अणु
		वापस PTR_ERR(param);
	पूर्ण

	अगर (p->length < माप(काष्ठा prism2_करोwnload_param) +
	    param->num_areas * माप(काष्ठा prism2_करोwnload_area)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = local->func->करोwnload(local, param);

 out:
	kमुक्त(param);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* PRISM2_DOWNLOAD_SUPPORT */


अटल पूर्णांक prism2_set_genericelement(काष्ठा net_device *dev, u8 *elem,
				     माप_प्रकार len)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace = netdev_priv(dev);
	local_info_t *local = अगरace->local;
	u8 *buf;

	/*
	 * Add 16-bit length in the beginning of the buffer because Prism2 RID
	 * includes it.
	 */
	buf = kदो_स्मृति(len + 2, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	*((__le16 *) buf) = cpu_to_le16(len);
	स_नकल(buf + 2, elem, len);

	kमुक्त(local->generic_elem);
	local->generic_elem = buf;
	local->generic_elem_len = len + 2;

	वापस local->func->set_rid(local->dev, HFA384X_RID_GENERICELEMENT,
				    buf, len + 2);
पूर्ण


अटल पूर्णांक prism2_ioctl_siwauth(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				काष्ठा iw_param *data, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace = netdev_priv(dev);
	local_info_t *local = अगरace->local;

	चयन (data->flags & IW_AUTH_INDEX) अणु
	हाल IW_AUTH_WPA_VERSION:
	हाल IW_AUTH_CIPHER_PAIRWISE:
	हाल IW_AUTH_CIPHER_GROUP:
	हाल IW_AUTH_KEY_MGMT:
		/*
		 * Host AP driver करोes not use these parameters and allows
		 * wpa_supplicant to control them पूर्णांकernally.
		 */
		अवरोध;
	हाल IW_AUTH_TKIP_COUNTERMEASURES:
		local->tkip_countermeasures = data->value;
		अवरोध;
	हाल IW_AUTH_DROP_UNENCRYPTED:
		local->drop_unencrypted = data->value;
		अवरोध;
	हाल IW_AUTH_80211_AUTH_ALG:
		local->auth_algs = data->value;
		अवरोध;
	हाल IW_AUTH_WPA_ENABLED:
		अगर (data->value == 0) अणु
			local->wpa = 0;
			अगर (local->sta_fw_ver < PRISM2_FW_VER(1,7,0))
				अवरोध;
			prism2_set_genericelement(dev, "", 0);
			local->host_roaming = 0;
			local->privacy_invoked = 0;
			अगर (hostap_set_word(dev, HFA384X_RID_SSNHANDLINGMODE,
					    0) ||
			    hostap_set_roaming(local) ||
			    hostap_set_encryption(local) ||
			    local->func->reset_port(dev))
				वापस -EINVAL;
			अवरोध;
		पूर्ण
		अगर (local->sta_fw_ver < PRISM2_FW_VER(1,7,0))
			वापस -EOPNOTSUPP;
		local->host_roaming = 2;
		local->privacy_invoked = 1;
		local->wpa = 1;
		अगर (hostap_set_word(dev, HFA384X_RID_SSNHANDLINGMODE, 1) ||
		    hostap_set_roaming(local) ||
		    hostap_set_encryption(local) ||
		    local->func->reset_port(dev))
			वापस -EINVAL;
		अवरोध;
	हाल IW_AUTH_RX_UNENCRYPTED_EAPOL:
		local->ieee_802_1x = data->value;
		अवरोध;
	हाल IW_AUTH_PRIVACY_INVOKED:
		local->privacy_invoked = data->value;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक prism2_ioctl_giwauth(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				काष्ठा iw_param *data, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace = netdev_priv(dev);
	local_info_t *local = अगरace->local;

	चयन (data->flags & IW_AUTH_INDEX) अणु
	हाल IW_AUTH_WPA_VERSION:
	हाल IW_AUTH_CIPHER_PAIRWISE:
	हाल IW_AUTH_CIPHER_GROUP:
	हाल IW_AUTH_KEY_MGMT:
		/*
		 * Host AP driver करोes not use these parameters and allows
		 * wpa_supplicant to control them पूर्णांकernally.
		 */
		वापस -EOPNOTSUPP;
	हाल IW_AUTH_TKIP_COUNTERMEASURES:
		data->value = local->tkip_countermeasures;
		अवरोध;
	हाल IW_AUTH_DROP_UNENCRYPTED:
		data->value = local->drop_unencrypted;
		अवरोध;
	हाल IW_AUTH_80211_AUTH_ALG:
		data->value = local->auth_algs;
		अवरोध;
	हाल IW_AUTH_WPA_ENABLED:
		data->value = local->wpa;
		अवरोध;
	हाल IW_AUTH_RX_UNENCRYPTED_EAPOL:
		data->value = local->ieee_802_1x;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक prism2_ioctl_siwencodeext(काष्ठा net_device *dev,
				     काष्ठा iw_request_info *info,
				     काष्ठा iw_poपूर्णांक *erq, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace = netdev_priv(dev);
	local_info_t *local = अगरace->local;
	काष्ठा iw_encode_ext *ext = (काष्ठा iw_encode_ext *) extra;
	पूर्णांक i, ret = 0;
	काष्ठा lib80211_crypto_ops *ops;
	काष्ठा lib80211_crypt_data **crypt;
	व्योम *sta_ptr;
	u8 *addr;
	स्थिर अक्षर *alg, *module;

	i = erq->flags & IW_ENCODE_INDEX;
	अगर (i > WEP_KEYS)
		वापस -EINVAL;
	अगर (i < 1 || i > WEP_KEYS)
		i = local->crypt_info.tx_keyidx;
	अन्यथा
		i--;
	अगर (i < 0 || i >= WEP_KEYS)
		वापस -EINVAL;

	addr = ext->addr.sa_data;
	अगर (is_broadcast_ether_addr(addr)) अणु
		sta_ptr = शून्य;
		crypt = &local->crypt_info.crypt[i];
	पूर्ण अन्यथा अणु
		अगर (i != 0)
			वापस -EINVAL;
		sta_ptr = ap_crypt_get_ptrs(local->ap, addr, 0, &crypt);
		अगर (sta_ptr == शून्य) अणु
			अगर (local->iw_mode == IW_MODE_INFRA) अणु
				/*
				 * TODO: add STA entry क्रम the current AP so
				 * that unicast key can be used. For now, this
				 * is emulated by using शेष key idx 0.
				 */
				i = 0;
				crypt = &local->crypt_info.crypt[i];
			पूर्ण अन्यथा
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर ((erq->flags & IW_ENCODE_DISABLED) ||
	    ext->alg == IW_ENCODE_ALG_NONE) अणु
		अगर (*crypt)
			lib80211_crypt_delayed_deinit(&local->crypt_info, crypt);
		जाओ करोne;
	पूर्ण

	चयन (ext->alg) अणु
	हाल IW_ENCODE_ALG_WEP:
		alg = "WEP";
		module = "lib80211_crypt_wep";
		अवरोध;
	हाल IW_ENCODE_ALG_TKIP:
		alg = "TKIP";
		module = "lib80211_crypt_tkip";
		अवरोध;
	हाल IW_ENCODE_ALG_CCMP:
		alg = "CCMP";
		module = "lib80211_crypt_ccmp";
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_DEBUG "%s: unsupported algorithm %d\n",
		       local->dev->name, ext->alg);
		ret = -EOPNOTSUPP;
		जाओ करोne;
	पूर्ण

	ops = lib80211_get_crypto_ops(alg);
	अगर (ops == शून्य) अणु
		request_module(module);
		ops = lib80211_get_crypto_ops(alg);
	पूर्ण
	अगर (ops == शून्य) अणु
		prपूर्णांकk(KERN_DEBUG "%s: unknown crypto alg '%s'\n",
		       local->dev->name, alg);
		ret = -EOPNOTSUPP;
		जाओ करोne;
	पूर्ण

	अगर (sta_ptr || ext->alg != IW_ENCODE_ALG_WEP) अणु
		/*
		 * Per station encryption and other than WEP algorithms
		 * require host-based encryption, so क्रमce them on
		 * स्वतःmatically.
		 */
		local->host_decrypt = local->host_encrypt = 1;
	पूर्ण

	अगर (*crypt == शून्य || (*crypt)->ops != ops) अणु
		काष्ठा lib80211_crypt_data *new_crypt;

		lib80211_crypt_delayed_deinit(&local->crypt_info, crypt);

		new_crypt = kzalloc(माप(काष्ठा lib80211_crypt_data),
				GFP_KERNEL);
		अगर (new_crypt == शून्य) अणु
			ret = -ENOMEM;
			जाओ करोne;
		पूर्ण
		new_crypt->ops = ops;
		अगर (new_crypt->ops && try_module_get(new_crypt->ops->owner))
			new_crypt->priv = new_crypt->ops->init(i);
		अगर (new_crypt->priv == शून्य) अणु
			kमुक्त(new_crypt);
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण

		*crypt = new_crypt;
	पूर्ण

	/*
	 * TODO: अगर ext_flags करोes not have IW_ENCODE_EXT_RX_SEQ_VALID, the
	 * existing seq# should not be changed.
	 * TODO: अगर ext_flags has IW_ENCODE_EXT_TX_SEQ_VALID, next TX seq#
	 * should be changed to something अन्यथा than zero.
	 */
	अगर ((!(ext->ext_flags & IW_ENCODE_EXT_SET_TX_KEY) || ext->key_len > 0)
	    && (*crypt)->ops->set_key &&
	    (*crypt)->ops->set_key(ext->key, ext->key_len, ext->rx_seq,
				   (*crypt)->priv) < 0) अणु
		prपूर्णांकk(KERN_DEBUG "%s: key setting failed\n",
		       local->dev->name);
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (ext->ext_flags & IW_ENCODE_EXT_SET_TX_KEY) अणु
		अगर (!sta_ptr)
			local->crypt_info.tx_keyidx = i;
	पूर्ण


	अगर (sta_ptr == शून्य && ext->key_len > 0) अणु
		पूर्णांक first = 1, j;
		क्रम (j = 0; j < WEP_KEYS; j++) अणु
			अगर (j != i && local->crypt_info.crypt[j]) अणु
				first = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (first)
			local->crypt_info.tx_keyidx = i;
	पूर्ण

 करोne:
	अगर (sta_ptr)
		hostap_handle_sta_release(sta_ptr);

	local->खोलो_wep = erq->flags & IW_ENCODE_OPEN;

	/*
	 * Do not reset port0 अगर card is in Managed mode since resetting will
	 * generate new IEEE 802.11 authentication which may end up in looping
	 * with IEEE 802.1X. Prism2 करोcumentation seem to require port reset
	 * after WEP configuration. However, keys are apparently changed at
	 * least in Managed mode.
	 */
	अगर (ret == 0 &&
	    (hostap_set_encryption(local) ||
	     (local->iw_mode != IW_MODE_INFRA &&
	      local->func->reset_port(local->dev))))
		ret = -EINVAL;

	वापस ret;
पूर्ण


अटल पूर्णांक prism2_ioctl_giwencodeext(काष्ठा net_device *dev,
				     काष्ठा iw_request_info *info,
				     काष्ठा iw_poपूर्णांक *erq, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace = netdev_priv(dev);
	local_info_t *local = अगरace->local;
	काष्ठा lib80211_crypt_data **crypt;
	व्योम *sta_ptr;
	पूर्णांक max_key_len, i;
	काष्ठा iw_encode_ext *ext = (काष्ठा iw_encode_ext *) extra;
	u8 *addr;

	max_key_len = erq->length - माप(*ext);
	अगर (max_key_len < 0)
		वापस -EINVAL;

	i = erq->flags & IW_ENCODE_INDEX;
	अगर (i < 1 || i > WEP_KEYS)
		i = local->crypt_info.tx_keyidx;
	अन्यथा
		i--;

	addr = ext->addr.sa_data;
	अगर (is_broadcast_ether_addr(addr)) अणु
		sta_ptr = शून्य;
		crypt = &local->crypt_info.crypt[i];
	पूर्ण अन्यथा अणु
		i = 0;
		sta_ptr = ap_crypt_get_ptrs(local->ap, addr, 0, &crypt);
		अगर (sta_ptr == शून्य)
			वापस -EINVAL;
	पूर्ण
	erq->flags = i + 1;
	स_रखो(ext, 0, माप(*ext));

	अगर (*crypt == शून्य || (*crypt)->ops == शून्य) अणु
		ext->alg = IW_ENCODE_ALG_NONE;
		ext->key_len = 0;
		erq->flags |= IW_ENCODE_DISABLED;
	पूर्ण अन्यथा अणु
		अगर (म_भेद((*crypt)->ops->name, "WEP") == 0)
			ext->alg = IW_ENCODE_ALG_WEP;
		अन्यथा अगर (म_भेद((*crypt)->ops->name, "TKIP") == 0)
			ext->alg = IW_ENCODE_ALG_TKIP;
		अन्यथा अगर (म_भेद((*crypt)->ops->name, "CCMP") == 0)
			ext->alg = IW_ENCODE_ALG_CCMP;
		अन्यथा
			वापस -EINVAL;

		अगर ((*crypt)->ops->get_key) अणु
			ext->key_len =
				(*crypt)->ops->get_key(ext->key,
						       max_key_len,
						       ext->tx_seq,
						       (*crypt)->priv);
			अगर (ext->key_len &&
			    (ext->alg == IW_ENCODE_ALG_TKIP ||
			     ext->alg == IW_ENCODE_ALG_CCMP))
				ext->ext_flags |= IW_ENCODE_EXT_TX_SEQ_VALID;
		पूर्ण
	पूर्ण

	अगर (sta_ptr)
		hostap_handle_sta_release(sta_ptr);

	वापस 0;
पूर्ण


अटल पूर्णांक prism2_ioctl_set_encryption(local_info_t *local,
				       काष्ठा prism2_hostapd_param *param,
				       पूर्णांक param_len)
अणु
	पूर्णांक ret = 0;
	काष्ठा lib80211_crypto_ops *ops;
	काष्ठा lib80211_crypt_data **crypt;
	व्योम *sta_ptr;

	param->u.crypt.err = 0;
	param->u.crypt.alg[HOSTAP_CRYPT_ALG_NAME_LEN - 1] = '\0';

	अगर (param_len !=
	    (पूर्णांक) ((अक्षर *) param->u.crypt.key - (अक्षर *) param) +
	    param->u.crypt.key_len)
		वापस -EINVAL;

	अगर (is_broadcast_ether_addr(param->sta_addr)) अणु
		अगर (param->u.crypt.idx >= WEP_KEYS)
			वापस -EINVAL;
		sta_ptr = शून्य;
		crypt = &local->crypt_info.crypt[param->u.crypt.idx];
	पूर्ण अन्यथा अणु
		अगर (param->u.crypt.idx)
			वापस -EINVAL;
		sta_ptr = ap_crypt_get_ptrs(
			local->ap, param->sta_addr,
			(param->u.crypt.flags & HOSTAP_CRYPT_FLAG_PERMANENT),
			&crypt);

		अगर (sta_ptr == शून्य) अणु
			param->u.crypt.err = HOSTAP_CRYPT_ERR_UNKNOWN_ADDR;
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (म_भेद(param->u.crypt.alg, "none") == 0) अणु
		अगर (crypt)
			lib80211_crypt_delayed_deinit(&local->crypt_info, crypt);
		जाओ करोne;
	पूर्ण

	ops = lib80211_get_crypto_ops(param->u.crypt.alg);
	अगर (ops == शून्य && म_भेद(param->u.crypt.alg, "WEP") == 0) अणु
		request_module("lib80211_crypt_wep");
		ops = lib80211_get_crypto_ops(param->u.crypt.alg);
	पूर्ण अन्यथा अगर (ops == शून्य && म_भेद(param->u.crypt.alg, "TKIP") == 0) अणु
		request_module("lib80211_crypt_tkip");
		ops = lib80211_get_crypto_ops(param->u.crypt.alg);
	पूर्ण अन्यथा अगर (ops == शून्य && म_भेद(param->u.crypt.alg, "CCMP") == 0) अणु
		request_module("lib80211_crypt_ccmp");
		ops = lib80211_get_crypto_ops(param->u.crypt.alg);
	पूर्ण
	अगर (ops == शून्य) अणु
		prपूर्णांकk(KERN_DEBUG "%s: unknown crypto alg '%s'\n",
		       local->dev->name, param->u.crypt.alg);
		param->u.crypt.err = HOSTAP_CRYPT_ERR_UNKNOWN_ALG;
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	/* station based encryption and other than WEP algorithms require
	 * host-based encryption, so क्रमce them on स्वतःmatically */
	local->host_decrypt = local->host_encrypt = 1;

	अगर (*crypt == शून्य || (*crypt)->ops != ops) अणु
		काष्ठा lib80211_crypt_data *new_crypt;

		lib80211_crypt_delayed_deinit(&local->crypt_info, crypt);

		new_crypt = kzalloc(माप(काष्ठा lib80211_crypt_data),
				GFP_KERNEL);
		अगर (new_crypt == शून्य) अणु
			ret = -ENOMEM;
			जाओ करोne;
		पूर्ण
		new_crypt->ops = ops;
		new_crypt->priv = new_crypt->ops->init(param->u.crypt.idx);
		अगर (new_crypt->priv == शून्य) अणु
			kमुक्त(new_crypt);
			param->u.crypt.err =
				HOSTAP_CRYPT_ERR_CRYPT_INIT_FAILED;
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण

		*crypt = new_crypt;
	पूर्ण

	अगर ((!(param->u.crypt.flags & HOSTAP_CRYPT_FLAG_SET_TX_KEY) ||
	     param->u.crypt.key_len > 0) && (*crypt)->ops->set_key &&
	    (*crypt)->ops->set_key(param->u.crypt.key,
				   param->u.crypt.key_len, param->u.crypt.seq,
				   (*crypt)->priv) < 0) अणु
		prपूर्णांकk(KERN_DEBUG "%s: key setting failed\n",
		       local->dev->name);
		param->u.crypt.err = HOSTAP_CRYPT_ERR_KEY_SET_FAILED;
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (param->u.crypt.flags & HOSTAP_CRYPT_FLAG_SET_TX_KEY) अणु
		अगर (!sta_ptr)
			local->crypt_info.tx_keyidx = param->u.crypt.idx;
		अन्यथा अगर (param->u.crypt.idx) अणु
			prपूर्णांकk(KERN_DEBUG "%s: TX key idx setting failed\n",
			       local->dev->name);
			param->u.crypt.err =
				HOSTAP_CRYPT_ERR_TX_KEY_SET_FAILED;
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण
	पूर्ण

 करोne:
	अगर (sta_ptr)
		hostap_handle_sta_release(sta_ptr);

	/* Do not reset port0 अगर card is in Managed mode since resetting will
	 * generate new IEEE 802.11 authentication which may end up in looping
	 * with IEEE 802.1X. Prism2 करोcumentation seem to require port reset
	 * after WEP configuration. However, keys are apparently changed at
	 * least in Managed mode. */
	अगर (ret == 0 &&
	    (hostap_set_encryption(local) ||
	     (local->iw_mode != IW_MODE_INFRA &&
	      local->func->reset_port(local->dev)))) अणु
		param->u.crypt.err = HOSTAP_CRYPT_ERR_CARD_CONF_FAILED;
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण


अटल पूर्णांक prism2_ioctl_get_encryption(local_info_t *local,
				       काष्ठा prism2_hostapd_param *param,
				       पूर्णांक param_len)
अणु
	काष्ठा lib80211_crypt_data **crypt;
	व्योम *sta_ptr;
	पूर्णांक max_key_len;

	param->u.crypt.err = 0;

	max_key_len = param_len -
		(पूर्णांक) ((अक्षर *) param->u.crypt.key - (अक्षर *) param);
	अगर (max_key_len < 0)
		वापस -EINVAL;

	अगर (is_broadcast_ether_addr(param->sta_addr)) अणु
		sta_ptr = शून्य;
		अगर (param->u.crypt.idx >= WEP_KEYS)
			param->u.crypt.idx = local->crypt_info.tx_keyidx;
		crypt = &local->crypt_info.crypt[param->u.crypt.idx];
	पूर्ण अन्यथा अणु
		param->u.crypt.idx = 0;
		sta_ptr = ap_crypt_get_ptrs(local->ap, param->sta_addr, 0,
					    &crypt);

		अगर (sta_ptr == शून्य) अणु
			param->u.crypt.err = HOSTAP_CRYPT_ERR_UNKNOWN_ADDR;
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (*crypt == शून्य || (*crypt)->ops == शून्य) अणु
		स_नकल(param->u.crypt.alg, "none", 5);
		param->u.crypt.key_len = 0;
		param->u.crypt.idx = 0xff;
	पूर्ण अन्यथा अणु
		म_नकलन(param->u.crypt.alg, (*crypt)->ops->name,
			HOSTAP_CRYPT_ALG_NAME_LEN);
		param->u.crypt.key_len = 0;

		स_रखो(param->u.crypt.seq, 0, 8);
		अगर ((*crypt)->ops->get_key) अणु
			param->u.crypt.key_len =
				(*crypt)->ops->get_key(param->u.crypt.key,
						       max_key_len,
						       param->u.crypt.seq,
						       (*crypt)->priv);
		पूर्ण
	पूर्ण

	अगर (sta_ptr)
		hostap_handle_sta_release(sta_ptr);

	वापस 0;
पूर्ण


अटल पूर्णांक prism2_ioctl_get_rid(local_info_t *local,
				काष्ठा prism2_hostapd_param *param,
				पूर्णांक param_len)
अणु
	पूर्णांक max_len, res;

	max_len = param_len - PRISM2_HOSTAPD_RID_HDR_LEN;
	अगर (max_len < 0)
		वापस -EINVAL;

	res = local->func->get_rid(local->dev, param->u.rid.rid,
				   param->u.rid.data, param->u.rid.len, 0);
	अगर (res >= 0) अणु
		param->u.rid.len = res;
		वापस 0;
	पूर्ण

	वापस res;
पूर्ण


अटल पूर्णांक prism2_ioctl_set_rid(local_info_t *local,
				काष्ठा prism2_hostapd_param *param,
				पूर्णांक param_len)
अणु
	पूर्णांक max_len;

	max_len = param_len - PRISM2_HOSTAPD_RID_HDR_LEN;
	अगर (max_len < 0 || max_len < param->u.rid.len)
		वापस -EINVAL;

	वापस local->func->set_rid(local->dev, param->u.rid.rid,
				    param->u.rid.data, param->u.rid.len);
पूर्ण


अटल पूर्णांक prism2_ioctl_set_assoc_ap_addr(local_info_t *local,
					  काष्ठा prism2_hostapd_param *param,
					  पूर्णांक param_len)
अणु
	prपूर्णांकk(KERN_DEBUG "%ssta: associated as client with AP %pM\n",
	       local->dev->name, param->sta_addr);
	स_नकल(local->assoc_ap_addr, param->sta_addr, ETH_ALEN);
	वापस 0;
पूर्ण


अटल पूर्णांक prism2_ioctl_siwgenie(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_poपूर्णांक *data, अक्षर *extra)
अणु
	वापस prism2_set_genericelement(dev, extra, data->length);
पूर्ण


अटल पूर्णांक prism2_ioctl_giwgenie(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_poपूर्णांक *data, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace = netdev_priv(dev);
	local_info_t *local = अगरace->local;
	पूर्णांक len = local->generic_elem_len - 2;

	अगर (len <= 0 || local->generic_elem == शून्य) अणु
		data->length = 0;
		वापस 0;
	पूर्ण

	अगर (data->length < len)
		वापस -E2BIG;

	data->length = len;
	स_नकल(extra, local->generic_elem + 2, len);

	वापस 0;
पूर्ण


अटल पूर्णांक prism2_ioctl_set_generic_element(local_info_t *local,
					    काष्ठा prism2_hostapd_param *param,
					    पूर्णांक param_len)
अणु
	पूर्णांक max_len, len;

	len = param->u.generic_elem.len;
	max_len = param_len - PRISM2_HOSTAPD_GENERIC_ELEMENT_HDR_LEN;
	अगर (max_len < 0 || max_len < len)
		वापस -EINVAL;

	वापस prism2_set_genericelement(local->dev,
					 param->u.generic_elem.data, len);
पूर्ण


अटल पूर्णांक prism2_ioctl_siwmlme(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				काष्ठा iw_poपूर्णांक *data, अक्षर *extra)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace = netdev_priv(dev);
	local_info_t *local = अगरace->local;
	काष्ठा iw_mlme *mlme = (काष्ठा iw_mlme *) extra;
	__le16 reason;

	reason = cpu_to_le16(mlme->reason_code);

	चयन (mlme->cmd) अणु
	हाल IW_MLME_DEAUTH:
		वापस prism2_sta_send_mgmt(local, mlme->addr.sa_data,
					    IEEE80211_STYPE_DEAUTH,
					    (u8 *) &reason, 2);
	हाल IW_MLME_DISASSOC:
		वापस prism2_sta_send_mgmt(local, mlme->addr.sa_data,
					    IEEE80211_STYPE_DISASSOC,
					    (u8 *) &reason, 2);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण


अटल पूर्णांक prism2_ioctl_mlme(local_info_t *local,
			     काष्ठा prism2_hostapd_param *param)
अणु
	__le16 reason;

	reason = cpu_to_le16(param->u.mlme.reason_code);
	चयन (param->u.mlme.cmd) अणु
	हाल MLME_STA_DEAUTH:
		वापस prism2_sta_send_mgmt(local, param->sta_addr,
					    IEEE80211_STYPE_DEAUTH,
					    (u8 *) &reason, 2);
	हाल MLME_STA_DISASSOC:
		वापस prism2_sta_send_mgmt(local, param->sta_addr,
					    IEEE80211_STYPE_DISASSOC,
					    (u8 *) &reason, 2);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण


अटल पूर्णांक prism2_ioctl_scan_req(local_info_t *local,
				 काष्ठा prism2_hostapd_param *param)
अणु
#अगर_अघोषित PRISM2_NO_STATION_MODES
	अगर ((local->iw_mode != IW_MODE_INFRA &&
	     local->iw_mode != IW_MODE_ADHOC) ||
	    (local->sta_fw_ver < PRISM2_FW_VER(1,3,1)))
		वापस -EOPNOTSUPP;

	अगर (!local->dev_enabled)
		वापस -ENETDOWN;

	वापस prism2_request_hostscan(local->dev, param->u.scan_req.ssid,
				       param->u.scan_req.ssid_len);
#अन्यथा /* PRISM2_NO_STATION_MODES */
	वापस -EOPNOTSUPP;
#पूर्ण_अगर /* PRISM2_NO_STATION_MODES */
पूर्ण


अटल पूर्णांक prism2_ioctl_priv_hostapd(local_info_t *local, काष्ठा iw_poपूर्णांक *p)
अणु
	काष्ठा prism2_hostapd_param *param;
	पूर्णांक ret = 0;
	पूर्णांक ap_ioctl = 0;

	अगर (p->length < माप(काष्ठा prism2_hostapd_param) ||
	    p->length > PRISM2_HOSTAPD_MAX_BUF_SIZE || !p->poपूर्णांकer)
		वापस -EINVAL;

	param = memdup_user(p->poपूर्णांकer, p->length);
	अगर (IS_ERR(param)) अणु
		वापस PTR_ERR(param);
	पूर्ण

	चयन (param->cmd) अणु
	हाल PRISM2_SET_ENCRYPTION:
		ret = prism2_ioctl_set_encryption(local, param, p->length);
		अवरोध;
	हाल PRISM2_GET_ENCRYPTION:
		ret = prism2_ioctl_get_encryption(local, param, p->length);
		अवरोध;
	हाल PRISM2_HOSTAPD_GET_RID:
		ret = prism2_ioctl_get_rid(local, param, p->length);
		अवरोध;
	हाल PRISM2_HOSTAPD_SET_RID:
		ret = prism2_ioctl_set_rid(local, param, p->length);
		अवरोध;
	हाल PRISM2_HOSTAPD_SET_ASSOC_AP_ADDR:
		ret = prism2_ioctl_set_assoc_ap_addr(local, param, p->length);
		अवरोध;
	हाल PRISM2_HOSTAPD_SET_GENERIC_ELEMENT:
		ret = prism2_ioctl_set_generic_element(local, param,
						       p->length);
		अवरोध;
	हाल PRISM2_HOSTAPD_MLME:
		ret = prism2_ioctl_mlme(local, param);
		अवरोध;
	हाल PRISM2_HOSTAPD_SCAN_REQ:
		ret = prism2_ioctl_scan_req(local, param);
		अवरोध;
	शेष:
		ret = prism2_hostapd(local->ap, param);
		ap_ioctl = 1;
		अवरोध;
	पूर्ण

	अगर (ret == 1 || !ap_ioctl) अणु
		अगर (copy_to_user(p->poपूर्णांकer, param, p->length)) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण अन्यथा अगर (ap_ioctl)
			ret = 0;
	पूर्ण

 out:
	kमुक्त(param);
	वापस ret;
पूर्ण


अटल व्योम prism2_get_drvinfo(काष्ठा net_device *dev,
			       काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	strlcpy(info->driver, "hostap", माप(info->driver));
	snम_लिखो(info->fw_version, माप(info->fw_version),
		 "%d.%d.%d", (local->sta_fw_ver >> 16) & 0xff,
		 (local->sta_fw_ver >> 8) & 0xff,
		 local->sta_fw_ver & 0xff);
पूर्ण

स्थिर काष्ठा ethtool_ops prism2_ethtool_ops = अणु
	.get_drvinfo = prism2_get_drvinfo
पूर्ण;


/* Structures to export the Wireless Handlers */

अटल स्थिर iw_handler prism2_handler[] =
अणु
	(iw_handler) शून्य,				/* SIOCSIWCOMMIT */
	(iw_handler) prism2_get_name,			/* SIOCGIWNAME */
	(iw_handler) शून्य,				/* SIOCSIWNWID */
	(iw_handler) शून्य,				/* SIOCGIWNWID */
	(iw_handler) prism2_ioctl_siwfreq,		/* SIOCSIWFREQ */
	(iw_handler) prism2_ioctl_giwfreq,		/* SIOCGIWFREQ */
	(iw_handler) prism2_ioctl_siwmode,		/* SIOCSIWMODE */
	(iw_handler) prism2_ioctl_giwmode,		/* SIOCGIWMODE */
	(iw_handler) prism2_ioctl_siwsens,		/* SIOCSIWSENS */
	(iw_handler) prism2_ioctl_giwsens,		/* SIOCGIWSENS */
	(iw_handler) शून्य /* not used */,		/* SIOCSIWRANGE */
	(iw_handler) prism2_ioctl_giwrange,		/* SIOCGIWRANGE */
	(iw_handler) शून्य /* not used */,		/* SIOCSIWPRIV */
	(iw_handler) शून्य /* kernel code */,		/* SIOCGIWPRIV */
	(iw_handler) शून्य /* not used */,		/* SIOCSIWSTATS */
	(iw_handler) शून्य /* kernel code */,		/* SIOCGIWSTATS */
	iw_handler_set_spy,				/* SIOCSIWSPY */
	iw_handler_get_spy,				/* SIOCGIWSPY */
	iw_handler_set_thrspy,				/* SIOCSIWTHRSPY */
	iw_handler_get_thrspy,				/* SIOCGIWTHRSPY */
	(iw_handler) prism2_ioctl_siwap,		/* SIOCSIWAP */
	(iw_handler) prism2_ioctl_giwap,		/* SIOCGIWAP */
	(iw_handler) prism2_ioctl_siwmlme,		/* SIOCSIWMLME */
	(iw_handler) prism2_ioctl_giwaplist,		/* SIOCGIWAPLIST */
	(iw_handler) prism2_ioctl_siwscan,		/* SIOCSIWSCAN */
	(iw_handler) prism2_ioctl_giwscan,		/* SIOCGIWSCAN */
	(iw_handler) prism2_ioctl_siwessid,		/* SIOCSIWESSID */
	(iw_handler) prism2_ioctl_giwessid,		/* SIOCGIWESSID */
	(iw_handler) prism2_ioctl_siwnickn,		/* SIOCSIWNICKN */
	(iw_handler) prism2_ioctl_giwnickn,		/* SIOCGIWNICKN */
	(iw_handler) शून्य,				/* -- hole -- */
	(iw_handler) शून्य,				/* -- hole -- */
	(iw_handler) prism2_ioctl_siwrate,		/* SIOCSIWRATE */
	(iw_handler) prism2_ioctl_giwrate,		/* SIOCGIWRATE */
	(iw_handler) prism2_ioctl_siwrts,		/* SIOCSIWRTS */
	(iw_handler) prism2_ioctl_giwrts,		/* SIOCGIWRTS */
	(iw_handler) prism2_ioctl_siwfrag,		/* SIOCSIWFRAG */
	(iw_handler) prism2_ioctl_giwfrag,		/* SIOCGIWFRAG */
	(iw_handler) prism2_ioctl_siwtxघात,		/* SIOCSIWTXPOW */
	(iw_handler) prism2_ioctl_giwtxघात,		/* SIOCGIWTXPOW */
	(iw_handler) prism2_ioctl_siwretry,		/* SIOCSIWRETRY */
	(iw_handler) prism2_ioctl_giwretry,		/* SIOCGIWRETRY */
	(iw_handler) prism2_ioctl_siwencode,		/* SIOCSIWENCODE */
	(iw_handler) prism2_ioctl_giwencode,		/* SIOCGIWENCODE */
	(iw_handler) prism2_ioctl_siwघातer,		/* SIOCSIWPOWER */
	(iw_handler) prism2_ioctl_giwघातer,		/* SIOCGIWPOWER */
	(iw_handler) शून्य,				/* -- hole -- */
	(iw_handler) शून्य,				/* -- hole -- */
	(iw_handler) prism2_ioctl_siwgenie,		/* SIOCSIWGENIE */
	(iw_handler) prism2_ioctl_giwgenie,		/* SIOCGIWGENIE */
	(iw_handler) prism2_ioctl_siwauth,		/* SIOCSIWAUTH */
	(iw_handler) prism2_ioctl_giwauth,		/* SIOCGIWAUTH */
	(iw_handler) prism2_ioctl_siwencodeext,		/* SIOCSIWENCODEEXT */
	(iw_handler) prism2_ioctl_giwencodeext,		/* SIOCGIWENCODEEXT */
	(iw_handler) शून्य,				/* SIOCSIWPMKSA */
	(iw_handler) शून्य,				/* -- hole -- */
पूर्ण;

अटल स्थिर iw_handler prism2_निजी_handler[] =
अणु							/* SIOCIWFIRSTPRIV + */
	(iw_handler) prism2_ioctl_priv_prism2_param,	/* 0 */
	(iw_handler) prism2_ioctl_priv_get_prism2_param, /* 1 */
	(iw_handler) prism2_ioctl_priv_ग_लिखोmअगर,	/* 2 */
	(iw_handler) prism2_ioctl_priv_पढ़ोmअगर,		/* 3 */
पूर्ण;

स्थिर काष्ठा iw_handler_def hostap_iw_handler_def =
अणु
	.num_standard	= ARRAY_SIZE(prism2_handler),
	.num_निजी	= ARRAY_SIZE(prism2_निजी_handler),
	.num_निजी_args = ARRAY_SIZE(prism2_priv),
	.standard	= (iw_handler *) prism2_handler,
	.निजी	= (iw_handler *) prism2_निजी_handler,
	.निजी_args	= (काष्ठा iw_priv_args *) prism2_priv,
	.get_wireless_stats = hostap_get_wireless_stats,
पूर्ण;


पूर्णांक hostap_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा iwreq *wrq = (काष्ठा iwreq *) अगरr;
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;
	पूर्णांक ret = 0;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	चयन (cmd) अणु
		/* Private ioctls (iwpriv) that have not yet been converted
		 * पूर्णांकo new wireless extensions API */

	हाल PRISM2_IOCTL_INQUIRE:
		अगर (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		अन्यथा ret = prism2_ioctl_priv_inquire(dev, (पूर्णांक *) wrq->u.name);
		अवरोध;

	हाल PRISM2_IOCTL_MONITOR:
		अगर (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		अन्यथा ret = prism2_ioctl_priv_monitor(dev, (पूर्णांक *) wrq->u.name);
		अवरोध;

	हाल PRISM2_IOCTL_RESET:
		अगर (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		अन्यथा ret = prism2_ioctl_priv_reset(dev, (पूर्णांक *) wrq->u.name);
		अवरोध;

	हाल PRISM2_IOCTL_WDS_ADD:
		अगर (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		अन्यथा ret = prism2_wds_add(local, wrq->u.ap_addr.sa_data, 1);
		अवरोध;

	हाल PRISM2_IOCTL_WDS_DEL:
		अगर (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		अन्यथा ret = prism2_wds_del(local, wrq->u.ap_addr.sa_data, 1, 0);
		अवरोध;

	हाल PRISM2_IOCTL_SET_RID_WORD:
		अगर (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		अन्यथा ret = prism2_ioctl_priv_set_rid_word(dev,
							  (पूर्णांक *) wrq->u.name);
		अवरोध;

#अगर_अघोषित PRISM2_NO_KERNEL_IEEE80211_MGMT
	हाल PRISM2_IOCTL_MACCMD:
		अगर (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		अन्यथा ret = ap_mac_cmd_ioctl(local, (पूर्णांक *) wrq->u.name);
		अवरोध;

	हाल PRISM2_IOCTL_ADDMAC:
		अगर (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		अन्यथा ret = ap_control_add_mac(&local->ap->mac_restrictions,
					      wrq->u.ap_addr.sa_data);
		अवरोध;
	हाल PRISM2_IOCTL_DELMAC:
		अगर (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		अन्यथा ret = ap_control_del_mac(&local->ap->mac_restrictions,
					      wrq->u.ap_addr.sa_data);
		अवरोध;
	हाल PRISM2_IOCTL_KICKMAC:
		अगर (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		अन्यथा ret = ap_control_kick_mac(local->ap, local->dev,
					       wrq->u.ap_addr.sa_data);
		अवरोध;
#पूर्ण_अगर /* PRISM2_NO_KERNEL_IEEE80211_MGMT */


		/* Private ioctls that are not used with iwpriv;
		 * in SIOCDEVPRIVATE range */

#अगर_घोषित PRISM2_DOWNLOAD_SUPPORT
	हाल PRISM2_IOCTL_DOWNLOAD:
		अगर (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		अन्यथा ret = prism2_ioctl_priv_करोwnload(local, &wrq->u.data);
		अवरोध;
#पूर्ण_अगर /* PRISM2_DOWNLOAD_SUPPORT */

	हाल PRISM2_IOCTL_HOSTAPD:
		अगर (!capable(CAP_NET_ADMIN)) ret = -EPERM;
		अन्यथा ret = prism2_ioctl_priv_hostapd(local, &wrq->u.data);
		अवरोध;

	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
