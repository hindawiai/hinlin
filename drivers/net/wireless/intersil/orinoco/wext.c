<शैली गुरु>
/* Wireless extensions support.
 *
 * See copyright notice in मुख्य.c
 */
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/wireless.h>
#समावेश <linux/ieee80211.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/iw_handler.h>
#समावेश <net/cfg80211.h>
#समावेश <net/cfg80211-wext.h>

#समावेश "hermes.h"
#समावेश "hermes_rid.h"
#समावेश "orinoco.h"

#समावेश "hw.h"
#समावेश "mic.h"
#समावेश "scan.h"
#समावेश "main.h"

#समावेश "wext.h"

#घोषणा MAX_RID_LEN 1024

/* Helper routine to record keys
 * It is called under orinoco_lock so it may not sleep */
अटल पूर्णांक orinoco_set_key(काष्ठा orinoco_निजी *priv, पूर्णांक index,
			   क्रमागत orinoco_alg alg, स्थिर u8 *key, पूर्णांक key_len,
			   स्थिर u8 *seq, पूर्णांक seq_len)
अणु
	kमुक्त_sensitive(priv->keys[index].key);
	kमुक्त_sensitive(priv->keys[index].seq);

	अगर (key_len) अणु
		priv->keys[index].key = kzalloc(key_len, GFP_ATOMIC);
		अगर (!priv->keys[index].key)
			जाओ nomem;
	पूर्ण अन्यथा
		priv->keys[index].key = शून्य;

	अगर (seq_len) अणु
		priv->keys[index].seq = kzalloc(seq_len, GFP_ATOMIC);
		अगर (!priv->keys[index].seq)
			जाओ मुक्त_key;
	पूर्ण अन्यथा
		priv->keys[index].seq = शून्य;

	priv->keys[index].key_len = key_len;
	priv->keys[index].seq_len = seq_len;

	अगर (key_len)
		स_नकल((व्योम *)priv->keys[index].key, key, key_len);
	अगर (seq_len)
		स_नकल((व्योम *)priv->keys[index].seq, seq, seq_len);

	चयन (alg) अणु
	हाल ORINOCO_ALG_TKIP:
		priv->keys[index].cipher = WLAN_CIPHER_SUITE_TKIP;
		अवरोध;

	हाल ORINOCO_ALG_WEP:
		priv->keys[index].cipher = (key_len > SMALL_KEY_SIZE) ?
			WLAN_CIPHER_SUITE_WEP104 : WLAN_CIPHER_SUITE_WEP40;
		अवरोध;

	हाल ORINOCO_ALG_NONE:
	शेष:
		priv->keys[index].cipher = 0;
		अवरोध;
	पूर्ण

	वापस 0;

मुक्त_key:
	kमुक्त(priv->keys[index].key);
	priv->keys[index].key = शून्य;

nomem:
	priv->keys[index].key_len = 0;
	priv->keys[index].seq_len = 0;
	priv->keys[index].cipher = 0;

	वापस -ENOMEM;
पूर्ण

अटल काष्ठा iw_statistics *orinoco_get_wireless_stats(काष्ठा net_device *dev)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	काष्ठा hermes *hw = &priv->hw;
	काष्ठा iw_statistics *wstats = &priv->wstats;
	पूर्णांक err;
	अचिन्हित दीर्घ flags;

	अगर (!netअगर_device_present(dev)) अणु
		prपूर्णांकk(KERN_WARNING "%s: get_wireless_stats() called while device not present\n",
		       dev->name);
		वापस शून्य; /* FIXME: Can we करो better than this? */
	पूर्ण

	/* If busy, वापस the old stats.  Returning शून्य may cause
	 * the पूर्णांकerface to disappear from /proc/net/wireless */
	अगर (orinoco_lock(priv, &flags) != 0)
		वापस wstats;

	/* We can't really रुको क्रम the tallies inquiry command to
	 * complete, so we just use the previous results and trigger
	 * a new tallies inquiry command क्रम next समय - Jean II */
	/* FIXME: Really we should रुको क्रम the inquiry to come back -
	 * as it is the stats we give करोn't make a whole lot of sense.
	 * Unक्रमtunately, it's not clear how to करो that within the
	 * wireless extensions framework: I think we're in user
	 * context, but a lock seems to be held by the समय we get in
	 * here so we're not safe to sleep here. */
	hermes_inquire(hw, HERMES_INQ_TALLIES);

	अगर (priv->iw_mode == NL80211_IFTYPE_ADHOC) अणु
		स_रखो(&wstats->qual, 0, माप(wstats->qual));
		/* If a spy address is defined, we report stats of the
		 * first spy address - Jean II */
		अगर (SPY_NUMBER(priv)) अणु
			wstats->qual.qual = priv->spy_data.spy_stat[0].qual;
			wstats->qual.level = priv->spy_data.spy_stat[0].level;
			wstats->qual.noise = priv->spy_data.spy_stat[0].noise;
			wstats->qual.updated =
				priv->spy_data.spy_stat[0].updated;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा अणु
			__le16 qual, संकेत, noise, unused;
		पूर्ण __packed cq;

		err = HERMES_READ_RECORD(hw, USER_BAP,
					 HERMES_RID_COMMSQUALITY, &cq);

		अगर (!err) अणु
			wstats->qual.qual = (पूर्णांक)le16_to_cpu(cq.qual);
			wstats->qual.level = (पूर्णांक)le16_to_cpu(cq.संकेत) - 0x95;
			wstats->qual.noise = (पूर्णांक)le16_to_cpu(cq.noise) - 0x95;
			wstats->qual.updated =
				IW_QUAL_ALL_UPDATED | IW_QUAL_DBM;
		पूर्ण
	पूर्ण

	orinoco_unlock(priv, &flags);
	वापस wstats;
पूर्ण

/********************************************************************/
/* Wireless extensions                                              */
/********************************************************************/

अटल पूर्णांक orinoco_ioctl_setwap(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				काष्ठा sockaddr *ap_addr,
				अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	पूर्णांक err = -EINPROGRESS;		/* Call commit handler */
	अचिन्हित दीर्घ flags;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	/* Enable स्वतःmatic roaming - no sanity checks are needed */
	अगर (is_zero_ether_addr(ap_addr->sa_data) ||
	    is_broadcast_ether_addr(ap_addr->sa_data)) अणु
		priv->bssid_fixed = 0;
		eth_zero_addr(priv->desired_bssid);

		/* "off" means keep existing connection */
		अगर (ap_addr->sa_data[0] == 0) अणु
			__orinoco_hw_set_wap(priv);
			err = 0;
		पूर्ण
		जाओ out;
	पूर्ण

	अगर (priv->firmware_type == FIRMWARE_TYPE_AGERE) अणु
		prपूर्णांकk(KERN_WARNING "%s: Lucent/Agere firmware doesn't "
		       "support manual roaming\n",
		       dev->name);
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (priv->iw_mode != NL80211_IFTYPE_STATION) अणु
		prपूर्णांकk(KERN_WARNING "%s: Manual roaming supported only in "
		       "managed mode\n", dev->name);
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	/* Intersil firmware hangs without Desired ESSID */
	अगर (priv->firmware_type == FIRMWARE_TYPE_INTERSIL &&
	    म_माप(priv->desired_essid) == 0) अणु
		prपूर्णांकk(KERN_WARNING "%s: Desired ESSID must be set for "
		       "manual roaming\n", dev->name);
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	/* Finally, enable manual roaming */
	priv->bssid_fixed = 1;
	स_नकल(priv->desired_bssid, &ap_addr->sa_data, ETH_ALEN);

 out:
	orinoco_unlock(priv, &flags);
	वापस err;
पूर्ण

अटल पूर्णांक orinoco_ioctl_getwap(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				काष्ठा sockaddr *ap_addr,
				अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);

	पूर्णांक err = 0;
	अचिन्हित दीर्घ flags;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	ap_addr->sa_family = ARPHRD_ETHER;
	err = orinoco_hw_get_current_bssid(priv, ap_addr->sa_data);

	orinoco_unlock(priv, &flags);

	वापस err;
पूर्ण

अटल पूर्णांक orinoco_ioctl_setiwencode(काष्ठा net_device *dev,
				     काष्ठा iw_request_info *info,
				     काष्ठा iw_poपूर्णांक *erq,
				     अक्षर *keybuf)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	पूर्णांक index = (erq->flags & IW_ENCODE_INDEX) - 1;
	पूर्णांक setindex = priv->tx_key;
	क्रमागत orinoco_alg encode_alg = priv->encode_alg;
	पूर्णांक restricted = priv->wep_restrict;
	पूर्णांक err = -EINPROGRESS;		/* Call commit handler */
	अचिन्हित दीर्घ flags;

	अगर (!priv->has_wep)
		वापस -EOPNOTSUPP;

	अगर (erq->poपूर्णांकer) अणु
		/* We actually have a key to set - check its length */
		अगर (erq->length > LARGE_KEY_SIZE)
			वापस -E2BIG;

		अगर ((erq->length > SMALL_KEY_SIZE) && !priv->has_big_wep)
			वापस -E2BIG;
	पूर्ण

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	/* Clear any TKIP key we have */
	अगर ((priv->has_wpa) && (priv->encode_alg == ORINOCO_ALG_TKIP))
		(व्योम) orinoco_clear_tkip_key(priv, setindex);

	अगर (erq->length > 0) अणु
		अगर ((index < 0) || (index >= ORINOCO_MAX_KEYS))
			index = priv->tx_key;

		/* Switch on WEP अगर off */
		अगर (encode_alg != ORINOCO_ALG_WEP) अणु
			setindex = index;
			encode_alg = ORINOCO_ALG_WEP;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Important note : अगर the user करो "iwconfig eth0 enc off",
		 * we will arrive there with an index of -1. This is valid
		 * but need to be taken care off... Jean II */
		अगर ((index < 0) || (index >= ORINOCO_MAX_KEYS)) अणु
			अगर ((index != -1) || (erq->flags == 0)) अणु
				err = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Set the index : Check that the key is valid */
			अगर (priv->keys[index].key_len == 0) अणु
				err = -EINVAL;
				जाओ out;
			पूर्ण
			setindex = index;
		पूर्ण
	पूर्ण

	अगर (erq->flags & IW_ENCODE_DISABLED)
		encode_alg = ORINOCO_ALG_NONE;
	अगर (erq->flags & IW_ENCODE_OPEN)
		restricted = 0;
	अगर (erq->flags & IW_ENCODE_RESTRICTED)
		restricted = 1;

	अगर (erq->poपूर्णांकer && erq->length > 0) अणु
		err = orinoco_set_key(priv, index, ORINOCO_ALG_WEP, keybuf,
				      erq->length, शून्य, 0);
	पूर्ण
	priv->tx_key = setindex;

	/* Try fast key change अगर connected and only keys are changed */
	अगर ((priv->encode_alg == encode_alg) &&
	    (priv->wep_restrict == restricted) &&
	    netअगर_carrier_ok(dev)) अणु
		err = __orinoco_hw_setup_wepkeys(priv);
		/* No need to commit अगर successful */
		जाओ out;
	पूर्ण

	priv->encode_alg = encode_alg;
	priv->wep_restrict = restricted;

 out:
	orinoco_unlock(priv, &flags);

	वापस err;
पूर्ण

अटल पूर्णांक orinoco_ioctl_getiwencode(काष्ठा net_device *dev,
				     काष्ठा iw_request_info *info,
				     काष्ठा iw_poपूर्णांक *erq,
				     अक्षर *keybuf)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	पूर्णांक index = (erq->flags & IW_ENCODE_INDEX) - 1;
	अचिन्हित दीर्घ flags;

	अगर (!priv->has_wep)
		वापस -EOPNOTSUPP;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	अगर ((index < 0) || (index >= ORINOCO_MAX_KEYS))
		index = priv->tx_key;

	erq->flags = 0;
	अगर (!priv->encode_alg)
		erq->flags |= IW_ENCODE_DISABLED;
	erq->flags |= index + 1;

	अगर (priv->wep_restrict)
		erq->flags |= IW_ENCODE_RESTRICTED;
	अन्यथा
		erq->flags |= IW_ENCODE_OPEN;

	erq->length = priv->keys[index].key_len;

	स_नकल(keybuf, priv->keys[index].key, erq->length);

	orinoco_unlock(priv, &flags);
	वापस 0;
पूर्ण

अटल पूर्णांक orinoco_ioctl_setessid(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  काष्ठा iw_poपूर्णांक *erq,
				  अक्षर *essidbuf)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	अचिन्हित दीर्घ flags;

	/* Note : ESSID is ignored in Ad-Hoc demo mode, but we can set it
	 * anyway... - Jean II */

	/* Hum... Should not use Wireless Extension स्थिरant (may change),
	 * should use our own... - Jean II */
	अगर (erq->length > IW_ESSID_MAX_SIZE)
		वापस -E2BIG;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	/* शून्य the string (क्रम शून्य termination & ESSID = ANY) - Jean II */
	स_रखो(priv->desired_essid, 0, माप(priv->desired_essid));

	/* If not ANY, get the new ESSID */
	अगर (erq->flags)
		स_नकल(priv->desired_essid, essidbuf, erq->length);

	orinoco_unlock(priv, &flags);

	वापस -EINPROGRESS;		/* Call commit handler */
पूर्ण

अटल पूर्णांक orinoco_ioctl_getessid(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  काष्ठा iw_poपूर्णांक *erq,
				  अक्षर *essidbuf)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	पूर्णांक active;
	पूर्णांक err = 0;
	अचिन्हित दीर्घ flags;

	अगर (netअगर_running(dev)) अणु
		err = orinoco_hw_get_essid(priv, &active, essidbuf);
		अगर (err < 0)
			वापस err;
		erq->length = err;
	पूर्ण अन्यथा अणु
		अगर (orinoco_lock(priv, &flags) != 0)
			वापस -EBUSY;
		स_नकल(essidbuf, priv->desired_essid, IW_ESSID_MAX_SIZE);
		erq->length = म_माप(priv->desired_essid);
		orinoco_unlock(priv, &flags);
	पूर्ण

	erq->flags = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक orinoco_ioctl_setfreq(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_freq *frq,
				 अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	पूर्णांक chan = -1;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = -EINPROGRESS;		/* Call commit handler */

	/* In infraकाष्ठाure mode the AP sets the channel */
	अगर (priv->iw_mode == NL80211_IFTYPE_STATION)
		वापस -EBUSY;

	अगर ((frq->e == 0) && (frq->m <= 1000)) अणु
		/* Setting by channel number */
		chan = frq->m;
	पूर्ण अन्यथा अणु
		/* Setting by frequency */
		पूर्णांक denom = 1;
		पूर्णांक i;

		/* Calculate denominator to rescale to MHz */
		क्रम (i = 0; i < (6 - frq->e); i++)
			denom *= 10;

		chan = ieee80211_frequency_to_channel(frq->m / denom);
	पूर्ण

	अगर ((chan < 1) || (chan > NUM_CHANNELS) ||
	     !(priv->channel_mask & (1 << (chan - 1))))
		वापस -EINVAL;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	priv->channel = chan;
	अगर (priv->iw_mode == NL80211_IFTYPE_MONITOR) अणु
		/* Fast channel change - no commit अगर successful */
		काष्ठा hermes *hw = &priv->hw;
		err = hw->ops->cmd_रुको(hw, HERMES_CMD_TEST |
					    HERMES_TEST_SET_CHANNEL,
					chan, शून्य);
	पूर्ण
	orinoco_unlock(priv, &flags);

	वापस err;
पूर्ण

अटल पूर्णांक orinoco_ioctl_getfreq(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_freq *frq,
				 अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	पूर्णांक पंचांगp;

	/* Locking करोne in there */
	पंचांगp = orinoco_hw_get_freq(priv);
	अगर (पंचांगp < 0)
		वापस पंचांगp;

	frq->m = पंचांगp * 100000;
	frq->e = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक orinoco_ioctl_माला_लोens(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_param *srq,
				 अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	काष्ठा hermes *hw = &priv->hw;
	u16 val;
	पूर्णांक err;
	अचिन्हित दीर्घ flags;

	अगर (!priv->has_sensitivity)
		वापस -EOPNOTSUPP;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;
	err = hermes_पढ़ो_wordrec(hw, USER_BAP,
				  HERMES_RID_CNFSYSTEMSCALE, &val);
	orinoco_unlock(priv, &flags);

	अगर (err)
		वापस err;

	srq->value = val;
	srq->fixed = 0; /* स्वतः */

	वापस 0;
पूर्ण

अटल पूर्णांक orinoco_ioctl_setsens(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_param *srq,
				 अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	पूर्णांक val = srq->value;
	अचिन्हित दीर्घ flags;

	अगर (!priv->has_sensitivity)
		वापस -EOPNOTSUPP;

	अगर ((val < 1) || (val > 3))
		वापस -EINVAL;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;
	priv->ap_density = val;
	orinoco_unlock(priv, &flags);

	वापस -EINPROGRESS;		/* Call commit handler */
पूर्ण

अटल पूर्णांक orinoco_ioctl_setrate(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_param *rrq,
				 अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	पूर्णांक ratemode;
	पूर्णांक bitrate; /* 100s of kilobits */
	अचिन्हित दीर्घ flags;

	/* As the user space करोesn't know our highest rate, it uses -1
	 * to ask us to set the highest rate.  Test it using "iwconfig
	 * ethX rate स्वतः" - Jean II */
	अगर (rrq->value == -1)
		bitrate = 110;
	अन्यथा अणु
		अगर (rrq->value % 100000)
			वापस -EINVAL;
		bitrate = rrq->value / 100000;
	पूर्ण

	ratemode = orinoco_get_bitratemode(bitrate, !rrq->fixed);

	अगर (ratemode == -1)
		वापस -EINVAL;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;
	priv->bitratemode = ratemode;
	orinoco_unlock(priv, &flags);

	वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक orinoco_ioctl_getrate(काष्ठा net_device *dev,
				 काष्ठा iw_request_info *info,
				 काष्ठा iw_param *rrq,
				 अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	पूर्णांक err = 0;
	पूर्णांक bitrate, स्वतःmatic;
	अचिन्हित दीर्घ flags;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	orinoco_get_ratemode_cfg(priv->bitratemode, &bitrate, &स्वतःmatic);

	/* If the पूर्णांकerface is running we try to find more about the
	   current mode */
	अगर (netअगर_running(dev)) अणु
		पूर्णांक act_bitrate;
		पूर्णांक lerr;

		/* Ignore errors अगर we can't get the actual bitrate */
		lerr = orinoco_hw_get_act_bitrate(priv, &act_bitrate);
		अगर (!lerr)
			bitrate = act_bitrate;
	पूर्ण

	orinoco_unlock(priv, &flags);

	rrq->value = bitrate;
	rrq->fixed = !स्वतःmatic;
	rrq->disabled = 0;

	वापस err;
पूर्ण

अटल पूर्णांक orinoco_ioctl_setघातer(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  काष्ठा iw_param *prq,
				  अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	पूर्णांक err = -EINPROGRESS;		/* Call commit handler */
	अचिन्हित दीर्घ flags;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	अगर (prq->disabled) अणु
		priv->pm_on = 0;
	पूर्ण अन्यथा अणु
		चयन (prq->flags & IW_POWER_MODE) अणु
		हाल IW_POWER_UNICAST_R:
			priv->pm_mcast = 0;
			priv->pm_on = 1;
			अवरोध;
		हाल IW_POWER_ALL_R:
			priv->pm_mcast = 1;
			priv->pm_on = 1;
			अवरोध;
		हाल IW_POWER_ON:
			/* No flags : but we may have a value - Jean II */
			अवरोध;
		शेष:
			err = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (prq->flags & IW_POWER_TIMEOUT) अणु
			priv->pm_on = 1;
			priv->pm_समयout = prq->value / 1000;
		पूर्ण
		अगर (prq->flags & IW_POWER_PERIOD) अणु
			priv->pm_on = 1;
			priv->pm_period = prq->value / 1000;
		पूर्ण
		/* It's valid to not have a value अगर we are just toggling
		 * the flags... Jean II */
		अगर (!priv->pm_on) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

 out:
	orinoco_unlock(priv, &flags);

	वापस err;
पूर्ण

अटल पूर्णांक orinoco_ioctl_getघातer(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  काष्ठा iw_param *prq,
				  अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक err = 0;
	u16 enable, period, समयout, mcast;
	अचिन्हित दीर्घ flags;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	err = hermes_पढ़ो_wordrec(hw, USER_BAP,
				  HERMES_RID_CNFPMENABLED, &enable);
	अगर (err)
		जाओ out;

	err = hermes_पढ़ो_wordrec(hw, USER_BAP,
				  HERMES_RID_CNFMAXSLEEPDURATION, &period);
	अगर (err)
		जाओ out;

	err = hermes_पढ़ो_wordrec(hw, USER_BAP,
				  HERMES_RID_CNFPMHOLDOVERDURATION, &समयout);
	अगर (err)
		जाओ out;

	err = hermes_पढ़ो_wordrec(hw, USER_BAP,
				  HERMES_RID_CNFMULTICASTRECEIVE, &mcast);
	अगर (err)
		जाओ out;

	prq->disabled = !enable;
	/* Note : by शेष, display the period */
	अगर ((prq->flags & IW_POWER_TYPE) == IW_POWER_TIMEOUT) अणु
		prq->flags = IW_POWER_TIMEOUT;
		prq->value = समयout * 1000;
	पूर्ण अन्यथा अणु
		prq->flags = IW_POWER_PERIOD;
		prq->value = period * 1000;
	पूर्ण
	अगर (mcast)
		prq->flags |= IW_POWER_ALL_R;
	अन्यथा
		prq->flags |= IW_POWER_UNICAST_R;

 out:
	orinoco_unlock(priv, &flags);

	वापस err;
पूर्ण

अटल पूर्णांक orinoco_ioctl_set_encodeext(काष्ठा net_device *dev,
				       काष्ठा iw_request_info *info,
				       जोड़ iwreq_data *wrqu,
				       अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	काष्ठा iw_poपूर्णांक *encoding = &wrqu->encoding;
	काष्ठा iw_encode_ext *ext = (काष्ठा iw_encode_ext *)extra;
	पूर्णांक idx, alg = ext->alg, set_key = 1;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = -EINVAL;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	/* Determine and validate the key index */
	idx = encoding->flags & IW_ENCODE_INDEX;
	अगर (idx) अणु
		अगर ((idx < 1) || (idx > 4))
			जाओ out;
		idx--;
	पूर्ण अन्यथा
		idx = priv->tx_key;

	अगर (encoding->flags & IW_ENCODE_DISABLED)
		alg = IW_ENCODE_ALG_NONE;

	अगर (priv->has_wpa && (alg != IW_ENCODE_ALG_TKIP)) अणु
		/* Clear any TKIP TX key we had */
		(व्योम) orinoco_clear_tkip_key(priv, priv->tx_key);
	पूर्ण

	अगर (ext->ext_flags & IW_ENCODE_EXT_SET_TX_KEY) अणु
		priv->tx_key = idx;
		set_key = ((alg == IW_ENCODE_ALG_TKIP) ||
			   (ext->key_len > 0)) ? 1 : 0;
	पूर्ण

	अगर (set_key) अणु
		/* Set the requested key first */
		चयन (alg) अणु
		हाल IW_ENCODE_ALG_NONE:
			priv->encode_alg = ORINOCO_ALG_NONE;
			err = orinoco_set_key(priv, idx, ORINOCO_ALG_NONE,
					      शून्य, 0, शून्य, 0);
			अवरोध;

		हाल IW_ENCODE_ALG_WEP:
			अगर (ext->key_len <= 0)
				जाओ out;

			priv->encode_alg = ORINOCO_ALG_WEP;
			err = orinoco_set_key(priv, idx, ORINOCO_ALG_WEP,
					      ext->key, ext->key_len, शून्य, 0);
			अवरोध;

		हाल IW_ENCODE_ALG_TKIP:
		अणु
			u8 *tkip_iv = शून्य;

			अगर (!priv->has_wpa ||
			    (ext->key_len > माप(काष्ठा orinoco_tkip_key)))
				जाओ out;

			priv->encode_alg = ORINOCO_ALG_TKIP;

			अगर (ext->ext_flags & IW_ENCODE_EXT_RX_SEQ_VALID)
				tkip_iv = &ext->rx_seq[0];

			err = orinoco_set_key(priv, idx, ORINOCO_ALG_TKIP,
					      ext->key, ext->key_len, tkip_iv,
					      ORINOCO_SEQ_LEN);

			err = __orinoco_hw_set_tkip_key(priv, idx,
				 ext->ext_flags & IW_ENCODE_EXT_SET_TX_KEY,
				 priv->keys[idx].key,
				 tkip_iv, ORINOCO_SEQ_LEN, शून्य, 0);
			अगर (err)
				prपूर्णांकk(KERN_ERR "%s: Error %d setting TKIP key"
				       "\n", dev->name, err);

			जाओ out;
		पूर्ण
		शेष:
			जाओ out;
		पूर्ण
	पूर्ण
	err = -EINPROGRESS;
 out:
	orinoco_unlock(priv, &flags);

	वापस err;
पूर्ण

अटल पूर्णांक orinoco_ioctl_get_encodeext(काष्ठा net_device *dev,
				       काष्ठा iw_request_info *info,
				       जोड़ iwreq_data *wrqu,
				       अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	काष्ठा iw_poपूर्णांक *encoding = &wrqu->encoding;
	काष्ठा iw_encode_ext *ext = (काष्ठा iw_encode_ext *)extra;
	पूर्णांक idx, max_key_len;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	err = -EINVAL;
	max_key_len = encoding->length - माप(*ext);
	अगर (max_key_len < 0)
		जाओ out;

	idx = encoding->flags & IW_ENCODE_INDEX;
	अगर (idx) अणु
		अगर ((idx < 1) || (idx > 4))
			जाओ out;
		idx--;
	पूर्ण अन्यथा
		idx = priv->tx_key;

	encoding->flags = idx + 1;
	स_रखो(ext, 0, माप(*ext));

	चयन (priv->encode_alg) अणु
	हाल ORINOCO_ALG_NONE:
		ext->alg = IW_ENCODE_ALG_NONE;
		ext->key_len = 0;
		encoding->flags |= IW_ENCODE_DISABLED;
		अवरोध;
	हाल ORINOCO_ALG_WEP:
		ext->alg = IW_ENCODE_ALG_WEP;
		ext->key_len = min(priv->keys[idx].key_len, max_key_len);
		स_नकल(ext->key, priv->keys[idx].key, ext->key_len);
		encoding->flags |= IW_ENCODE_ENABLED;
		अवरोध;
	हाल ORINOCO_ALG_TKIP:
		ext->alg = IW_ENCODE_ALG_TKIP;
		ext->key_len = min(priv->keys[idx].key_len, max_key_len);
		स_नकल(ext->key, priv->keys[idx].key, ext->key_len);
		encoding->flags |= IW_ENCODE_ENABLED;
		अवरोध;
	पूर्ण

	err = 0;
 out:
	orinoco_unlock(priv, &flags);

	वापस err;
पूर्ण

अटल पूर्णांक orinoco_ioctl_set_auth(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	काष्ठा hermes *hw = &priv->hw;
	काष्ठा iw_param *param = &wrqu->param;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EINPROGRESS;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	चयन (param->flags & IW_AUTH_INDEX) अणु
	हाल IW_AUTH_WPA_VERSION:
	हाल IW_AUTH_CIPHER_PAIRWISE:
	हाल IW_AUTH_CIPHER_GROUP:
	हाल IW_AUTH_RX_UNENCRYPTED_EAPOL:
	हाल IW_AUTH_PRIVACY_INVOKED:
	हाल IW_AUTH_DROP_UNENCRYPTED:
		/*
		 * orinoco करोes not use these parameters
		 */
		अवरोध;

	हाल IW_AUTH_MFP:
		/* Management Frame Protection not supported.
		 * Only fail अगर set to required.
		 */
		अगर (param->value == IW_AUTH_MFP_REQUIRED)
			ret = -EINVAL;
		अवरोध;

	हाल IW_AUTH_KEY_MGMT:
		/* wl_lkm implies value 2 == PSK क्रम Hermes I
		 * which ties in with WEXT
		 * no other hपूर्णांकs tho :(
		 */
		priv->key_mgmt = param->value;
		अवरोध;

	हाल IW_AUTH_TKIP_COUNTERMEASURES:
		/* When countermeasures are enabled, shut करोwn the
		 * card; when disabled, re-enable the card. This must
		 * take effect immediately.
		 *
		 * TODO: Make sure that the EAPOL message is getting
		 *       out beक्रमe card disabled
		 */
		अगर (param->value) अणु
			priv->tkip_cm_active = 1;
			ret = hermes_disable_port(hw, 0);
		पूर्ण अन्यथा अणु
			priv->tkip_cm_active = 0;
			ret = hermes_enable_port(hw, 0);
		पूर्ण
		अवरोध;

	हाल IW_AUTH_80211_AUTH_ALG:
		अगर (param->value & IW_AUTH_ALG_SHARED_KEY)
			priv->wep_restrict = 1;
		अन्यथा अगर (param->value & IW_AUTH_ALG_OPEN_SYSTEM)
			priv->wep_restrict = 0;
		अन्यथा
			ret = -EINVAL;
		अवरोध;

	हाल IW_AUTH_WPA_ENABLED:
		अगर (priv->has_wpa) अणु
			priv->wpa_enabled = param->value ? 1 : 0;
		पूर्ण अन्यथा अणु
			अगर (param->value)
				ret = -EOPNOTSUPP;
			/* अन्यथा silently accept disable of WPA */
			priv->wpa_enabled = 0;
		पूर्ण
		अवरोध;

	शेष:
		ret = -EOPNOTSUPP;
	पूर्ण

	orinoco_unlock(priv, &flags);
	वापस ret;
पूर्ण

अटल पूर्णांक orinoco_ioctl_get_auth(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	काष्ठा iw_param *param = &wrqu->param;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	चयन (param->flags & IW_AUTH_INDEX) अणु
	हाल IW_AUTH_KEY_MGMT:
		param->value = priv->key_mgmt;
		अवरोध;

	हाल IW_AUTH_TKIP_COUNTERMEASURES:
		param->value = priv->tkip_cm_active;
		अवरोध;

	हाल IW_AUTH_80211_AUTH_ALG:
		अगर (priv->wep_restrict)
			param->value = IW_AUTH_ALG_SHARED_KEY;
		अन्यथा
			param->value = IW_AUTH_ALG_OPEN_SYSTEM;
		अवरोध;

	हाल IW_AUTH_WPA_ENABLED:
		param->value = priv->wpa_enabled;
		अवरोध;

	शेष:
		ret = -EOPNOTSUPP;
	पूर्ण

	orinoco_unlock(priv, &flags);
	वापस ret;
पूर्ण

अटल पूर्णांक orinoco_ioctl_set_genie(काष्ठा net_device *dev,
				   काष्ठा iw_request_info *info,
				   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	u8 *buf;
	अचिन्हित दीर्घ flags;

	/* cut off at IEEE80211_MAX_DATA_LEN */
	अगर ((wrqu->data.length > IEEE80211_MAX_DATA_LEN) ||
	    (wrqu->data.length && (extra == शून्य)))
		वापस -EINVAL;

	अगर (wrqu->data.length) अणु
		buf = kmemdup(extra, wrqu->data.length, GFP_KERNEL);
		अगर (buf == शून्य)
			वापस -ENOMEM;
	पूर्ण अन्यथा
		buf = शून्य;

	अगर (orinoco_lock(priv, &flags) != 0) अणु
		kमुक्त(buf);
		वापस -EBUSY;
	पूर्ण

	kमुक्त(priv->wpa_ie);
	priv->wpa_ie = buf;
	priv->wpa_ie_len = wrqu->data.length;

	अगर (priv->wpa_ie) अणु
		/* Looks like wl_lkm wants to check the auth alg, and
		 * somehow pass it to the firmware.
		 * Instead it just calls the key mgmt rid
		 *   - we करो this in set auth.
		 */
	पूर्ण

	orinoco_unlock(priv, &flags);
	वापस 0;
पूर्ण

अटल पूर्णांक orinoco_ioctl_get_genie(काष्ठा net_device *dev,
				   काष्ठा iw_request_info *info,
				   जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	अगर ((priv->wpa_ie_len == 0) || (priv->wpa_ie == शून्य)) अणु
		wrqu->data.length = 0;
		जाओ out;
	पूर्ण

	अगर (wrqu->data.length < priv->wpa_ie_len) अणु
		err = -E2BIG;
		जाओ out;
	पूर्ण

	wrqu->data.length = priv->wpa_ie_len;
	स_नकल(extra, priv->wpa_ie, priv->wpa_ie_len);

out:
	orinoco_unlock(priv, &flags);
	वापस err;
पूर्ण

अटल पूर्णांक orinoco_ioctl_set_mlme(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	काष्ठा iw_mlme *mlme = (काष्ठा iw_mlme *)extra;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	चयन (mlme->cmd) अणु
	हाल IW_MLME_DEAUTH:
		/* silently ignore */
		अवरोध;

	हाल IW_MLME_DISASSOC:

		ret = orinoco_hw_disassociate(priv, mlme->addr.sa_data,
					      mlme->reason_code);
		अवरोध;

	शेष:
		ret = -EOPNOTSUPP;
	पूर्ण

	orinoco_unlock(priv, &flags);
	वापस ret;
पूर्ण

अटल पूर्णांक orinoco_ioctl_reset(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       व्योम *wrqu,
			       अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (info->cmd == (SIOCIWFIRSTPRIV + 0x1)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: Forcing reset!\n", dev->name);

		/* Firmware reset */
		orinoco_reset(&priv->reset_work);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_DEBUG "%s: Force scheduling reset!\n", dev->name);

		schedule_work(&priv->reset_work);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक orinoco_ioctl_setibssport(काष्ठा net_device *dev,
				     काष्ठा iw_request_info *info,
				     व्योम *wrqu,
				     अक्षर *extra)

अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	पूर्णांक val = *((पूर्णांक *) extra);
	अचिन्हित दीर्घ flags;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	priv->ibss_port = val;

	/* Actually update the mode we are using */
	set_port_type(priv);

	orinoco_unlock(priv, &flags);
	वापस -EINPROGRESS;		/* Call commit handler */
पूर्ण

अटल पूर्णांक orinoco_ioctl_getibssport(काष्ठा net_device *dev,
				     काष्ठा iw_request_info *info,
				     व्योम *wrqu,
				     अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	पूर्णांक *val = (पूर्णांक *) extra;

	*val = priv->ibss_port;
	वापस 0;
पूर्ण

अटल पूर्णांक orinoco_ioctl_setport3(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  व्योम *wrqu,
				  अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	पूर्णांक val = *((पूर्णांक *) extra);
	पूर्णांक err = 0;
	अचिन्हित दीर्घ flags;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	चयन (val) अणु
	हाल 0: /* Try to करो IEEE ad-hoc mode */
		अगर (!priv->has_ibss) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण
		priv->prefer_port3 = 0;

		अवरोध;

	हाल 1: /* Try to करो Lucent proprietary ad-hoc mode */
		अगर (!priv->has_port3) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण
		priv->prefer_port3 = 1;
		अवरोध;

	शेष:
		err = -EINVAL;
	पूर्ण

	अगर (!err) अणु
		/* Actually update the mode we are using */
		set_port_type(priv);
		err = -EINPROGRESS;
	पूर्ण

	orinoco_unlock(priv, &flags);

	वापस err;
पूर्ण

अटल पूर्णांक orinoco_ioctl_getport3(काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info,
				  व्योम *wrqu,
				  अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	पूर्णांक *val = (पूर्णांक *) extra;

	*val = priv->prefer_port3;
	वापस 0;
पूर्ण

अटल पूर्णांक orinoco_ioctl_setpreamble(काष्ठा net_device *dev,
				     काष्ठा iw_request_info *info,
				     व्योम *wrqu,
				     अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक val;

	अगर (!priv->has_preamble)
		वापस -EOPNOTSUPP;

	/* 802.11b has recently defined some लघु preamble.
	 * Basically, the Phy header has been reduced in size.
	 * This increase perक्रमmance, especially at high rates
	 * (the preamble is transmitted at 1Mb/s), unक्रमtunately
	 * this give compatibility troubles... - Jean II */
	val = *((पूर्णांक *) extra);

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	अगर (val)
		priv->preamble = 1;
	अन्यथा
		priv->preamble = 0;

	orinoco_unlock(priv, &flags);

	वापस -EINPROGRESS;		/* Call commit handler */
पूर्ण

अटल पूर्णांक orinoco_ioctl_getpreamble(काष्ठा net_device *dev,
				     काष्ठा iw_request_info *info,
				     व्योम *wrqu,
				     अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	पूर्णांक *val = (पूर्णांक *) extra;

	अगर (!priv->has_preamble)
		वापस -EOPNOTSUPP;

	*val = priv->preamble;
	वापस 0;
पूर्ण

/* ioctl पूर्णांकerface to hermes_पढ़ो_ltv()
 * To use with iwpriv, pass the RID as the token argument, e.g.
 * iwpriv get_rid [0xfc00]
 * At least Wireless Tools 25 is required to use iwpriv.
 * For Wireless Tools 25 and 26 append "dummy" are the end. */
अटल पूर्णांक orinoco_ioctl_getrid(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				काष्ठा iw_poपूर्णांक *data,
				अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक rid = data->flags;
	u16 length;
	पूर्णांक err;
	अचिन्हित दीर्घ flags;

	/* It's a "get" function, but we don't want users to access the
	 * WEP key and other raw firmware data */
	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (rid < 0xfc00 || rid > 0xffff)
		वापस -EINVAL;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	err = hw->ops->पढ़ो_ltv(hw, USER_BAP, rid, MAX_RID_LEN, &length,
				extra);
	अगर (err)
		जाओ out;

	data->length = min_t(u16, HERMES_RECLEN_TO_BYTES(length),
			     MAX_RID_LEN);

 out:
	orinoco_unlock(priv, &flags);
	वापस err;
पूर्ण


/* Commit handler, called after set operations */
अटल पूर्णांक orinoco_ioctl_commit(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				व्योम *wrqu,
				अक्षर *extra)
अणु
	काष्ठा orinoco_निजी *priv = ndev_priv(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	अगर (!priv->खोलो)
		वापस 0;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस err;

	err = orinoco_commit(priv);

	orinoco_unlock(priv, &flags);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा iw_priv_args orinoco_privtab[] = अणु
	अणु SIOCIWFIRSTPRIV + 0x0, 0, 0, "force_reset" पूर्ण,
	अणु SIOCIWFIRSTPRIV + 0x1, 0, 0, "card_reset" पूर्ण,
	अणु SIOCIWFIRSTPRIV + 0x2, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	  0, "set_port3" पूर्ण,
	अणु SIOCIWFIRSTPRIV + 0x3, 0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	  "get_port3" पूर्ण,
	अणु SIOCIWFIRSTPRIV + 0x4, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	  0, "set_preamble" पूर्ण,
	अणु SIOCIWFIRSTPRIV + 0x5, 0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	  "get_preamble" पूर्ण,
	अणु SIOCIWFIRSTPRIV + 0x6, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	  0, "set_ibssport" पूर्ण,
	अणु SIOCIWFIRSTPRIV + 0x7, 0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	  "get_ibssport" पूर्ण,
	अणु SIOCIWFIRSTPRIV + 0x9, 0, IW_PRIV_TYPE_BYTE | MAX_RID_LEN,
	  "get_rid" पूर्ण,
पूर्ण;


/*
 * Structures to export the Wireless Handlers
 */

अटल स्थिर iw_handler	orinoco_handler[] = अणु
	IW_HANDLER(SIOCSIWCOMMIT,	(iw_handler)orinoco_ioctl_commit),
	IW_HANDLER(SIOCGIWNAME,		(iw_handler)cfg80211_wext_giwname),
	IW_HANDLER(SIOCSIWFREQ,		(iw_handler)orinoco_ioctl_setfreq),
	IW_HANDLER(SIOCGIWFREQ,		(iw_handler)orinoco_ioctl_getfreq),
	IW_HANDLER(SIOCSIWMODE,		(iw_handler)cfg80211_wext_siwmode),
	IW_HANDLER(SIOCGIWMODE,		(iw_handler)cfg80211_wext_giwmode),
	IW_HANDLER(SIOCSIWSENS,		(iw_handler)orinoco_ioctl_setsens),
	IW_HANDLER(SIOCGIWSENS,		(iw_handler)orinoco_ioctl_माला_लोens),
	IW_HANDLER(SIOCGIWRANGE,	(iw_handler)cfg80211_wext_giwrange),
	IW_HANDLER(SIOCSIWSPY,		iw_handler_set_spy),
	IW_HANDLER(SIOCGIWSPY,		iw_handler_get_spy),
	IW_HANDLER(SIOCSIWTHRSPY,	iw_handler_set_thrspy),
	IW_HANDLER(SIOCGIWTHRSPY,	iw_handler_get_thrspy),
	IW_HANDLER(SIOCSIWAP,		(iw_handler)orinoco_ioctl_setwap),
	IW_HANDLER(SIOCGIWAP,		(iw_handler)orinoco_ioctl_getwap),
	IW_HANDLER(SIOCSIWSCAN,		(iw_handler)cfg80211_wext_siwscan),
	IW_HANDLER(SIOCGIWSCAN,		(iw_handler)cfg80211_wext_giwscan),
	IW_HANDLER(SIOCSIWESSID,	(iw_handler)orinoco_ioctl_setessid),
	IW_HANDLER(SIOCGIWESSID,	(iw_handler)orinoco_ioctl_getessid),
	IW_HANDLER(SIOCSIWRATE,		(iw_handler)orinoco_ioctl_setrate),
	IW_HANDLER(SIOCGIWRATE,		(iw_handler)orinoco_ioctl_getrate),
	IW_HANDLER(SIOCSIWRTS,		(iw_handler)cfg80211_wext_siwrts),
	IW_HANDLER(SIOCGIWRTS,		(iw_handler)cfg80211_wext_giwrts),
	IW_HANDLER(SIOCSIWFRAG,		(iw_handler)cfg80211_wext_siwfrag),
	IW_HANDLER(SIOCGIWFRAG,		(iw_handler)cfg80211_wext_giwfrag),
	IW_HANDLER(SIOCGIWRETRY,	(iw_handler)cfg80211_wext_giwretry),
	IW_HANDLER(SIOCSIWENCODE,	(iw_handler)orinoco_ioctl_setiwencode),
	IW_HANDLER(SIOCGIWENCODE,	(iw_handler)orinoco_ioctl_getiwencode),
	IW_HANDLER(SIOCSIWPOWER,	(iw_handler)orinoco_ioctl_setघातer),
	IW_HANDLER(SIOCGIWPOWER,	(iw_handler)orinoco_ioctl_getघातer),
	IW_HANDLER(SIOCSIWGENIE,	orinoco_ioctl_set_genie),
	IW_HANDLER(SIOCGIWGENIE,	orinoco_ioctl_get_genie),
	IW_HANDLER(SIOCSIWMLME,		orinoco_ioctl_set_mlme),
	IW_HANDLER(SIOCSIWAUTH,		orinoco_ioctl_set_auth),
	IW_HANDLER(SIOCGIWAUTH,		orinoco_ioctl_get_auth),
	IW_HANDLER(SIOCSIWENCODEEXT,	orinoco_ioctl_set_encodeext),
	IW_HANDLER(SIOCGIWENCODEEXT,	orinoco_ioctl_get_encodeext),
पूर्ण;


/*
  Added typecasting since we no दीर्घer use iwreq_data -- Moustafa
 */
अटल स्थिर iw_handler	orinoco_निजी_handler[] = अणु
	[0] = (iw_handler)orinoco_ioctl_reset,
	[1] = (iw_handler)orinoco_ioctl_reset,
	[2] = (iw_handler)orinoco_ioctl_setport3,
	[3] = (iw_handler)orinoco_ioctl_getport3,
	[4] = (iw_handler)orinoco_ioctl_setpreamble,
	[5] = (iw_handler)orinoco_ioctl_getpreamble,
	[6] = (iw_handler)orinoco_ioctl_setibssport,
	[7] = (iw_handler)orinoco_ioctl_getibssport,
	[9] = (iw_handler)orinoco_ioctl_getrid,
पूर्ण;

स्थिर काष्ठा iw_handler_def orinoco_handler_def = अणु
	.num_standard = ARRAY_SIZE(orinoco_handler),
	.num_निजी = ARRAY_SIZE(orinoco_निजी_handler),
	.num_निजी_args = ARRAY_SIZE(orinoco_privtab),
	.standard = orinoco_handler,
	.निजी = orinoco_निजी_handler,
	.निजी_args = orinoco_privtab,
	.get_wireless_stats = orinoco_get_wireless_stats,
पूर्ण;
