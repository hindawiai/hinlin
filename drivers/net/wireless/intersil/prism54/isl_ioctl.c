<शैली गुरु>
/*
 *  Copyright (C) 2002 Intersil Americas Inc.
 *            (C) 2003,2004 Aurelien Alleaume <slts@मुक्त.fr>
 *            (C) 2003 Herbert Valerio Riedel <hvr@gnu.org>
 *            (C) 2003 Luis R. Rodriguez <mcgrof@ruslug.rutgers.edu>
 *
 *  This program is मुक्त software; you can redistribute it and/or modअगरy
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License क्रम more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  aदीर्घ with this program; अगर not, see <http://www.gnu.org/licenses/>.
 *
 */

#समावेश <linux/capability.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/etherdevice.h>

#समावेश <linux/uaccess.h>

#समावेश "prismcompat.h"
#समावेश "isl_ioctl.h"
#समावेश "islpci_mgt.h"
#समावेश "isl_oid.h"		/* additional types and defs क्रम isl38xx fw */
#समावेश "oid_mgt.h"

#समावेश <net/iw_handler.h>	/* New driver API */

#घोषणा KEY_SIZE_WEP104 13	/* 104/128-bit WEP keys */
#घोषणा KEY_SIZE_WEP40  5	/* 40/64-bit WEP keys */
/* KEY_SIZE_TKIP should match isl_oid.h, काष्ठा obj_key.key[] size */
#घोषणा KEY_SIZE_TKIP   32	/* TKIP keys */

अटल व्योम prism54_wpa_bss_ie_add(islpci_निजी *priv, u8 *bssid,
				u8 *wpa_ie, माप_प्रकार wpa_ie_len);
अटल माप_प्रकार prism54_wpa_bss_ie_get(islpci_निजी *priv, u8 *bssid, u8 *wpa_ie);
अटल पूर्णांक prism54_set_wpa(काष्ठा net_device *, काष्ठा iw_request_info *,
				__u32 *, अक्षर *);

/* In 500 kbps */
अटल स्थिर अचिन्हित अक्षर scan_rate_list[] = अणु 2, 4, 11, 22,
						12, 18, 24, 36,
						48, 72, 96, 108 पूर्ण;

/**
 * prism54_mib_mode_helper - MIB change mode helper function
 * @priv: the &काष्ठा islpci_निजी object to modअगरy
 * @iw_mode: new mode (%IW_MODE_*)
 *
 *  This is a helper function, hence it करोes not lock. Make sure
 *  caller deals with locking *अगर* necessary. This function sets the
 *  mode-dependent mib values and करोes the mapping of the Linux
 *  Wireless API modes to Device firmware modes. It also checks क्रम
 *  correct valid Linux wireless modes.
 */
अटल पूर्णांक
prism54_mib_mode_helper(islpci_निजी *priv, u32 iw_mode)
अणु
	u32 config = INL_CONFIG_MANUALRUN;
	u32 mode, bsstype;

	/* For now, just catch early the Repeater and Secondary modes here */
	अगर (iw_mode == IW_MODE_REPEAT || iw_mode == IW_MODE_SECOND) अणु
		prपूर्णांकk(KERN_DEBUG
		       "%s(): Sorry, Repeater mode and Secondary mode "
		       "are not yet supported by this driver.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	priv->iw_mode = iw_mode;

	चयन (iw_mode) अणु
	हाल IW_MODE_AUTO:
		mode = INL_MODE_CLIENT;
		bsstype = DOT11_BSSTYPE_ANY;
		अवरोध;
	हाल IW_MODE_ADHOC:
		mode = INL_MODE_CLIENT;
		bsstype = DOT11_BSSTYPE_IBSS;
		अवरोध;
	हाल IW_MODE_INFRA:
		mode = INL_MODE_CLIENT;
		bsstype = DOT11_BSSTYPE_INFRA;
		अवरोध;
	हाल IW_MODE_MASTER:
		mode = INL_MODE_AP;
		bsstype = DOT11_BSSTYPE_INFRA;
		अवरोध;
	हाल IW_MODE_MONITOR:
		mode = INL_MODE_PROMISCUOUS;
		bsstype = DOT11_BSSTYPE_ANY;
		config |= INL_CONFIG_RXANNEX;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (init_wds)
		config |= INL_CONFIG_WDS;
	mgt_set(priv, DOT11_OID_BSSTYPE, &bsstype);
	mgt_set(priv, OID_INL_CONFIG, &config);
	mgt_set(priv, OID_INL_MODE, &mode);

	वापस 0;
पूर्ण

/*
 * prism54_mib_init - fill MIB cache with शेषs
 *
 *  this function initializes the काष्ठा given as @mib with शेषs,
 *  of which many are retrieved from the global module parameter
 *  variables.
 */
व्योम
prism54_mib_init(islpci_निजी *priv)
अणु
	u32 channel, authen, wep, filter, करोt1x, mlme, conक्रमmance, घातer, mode;
	काष्ठा obj_buffer psm_buffer = अणु
		.size = PSM_BUFFER_SIZE,
		.addr = priv->device_psm_buffer
	पूर्ण;

	channel = CARD_DEFAULT_CHANNEL;
	authen = CARD_DEFAULT_AUTHEN;
	wep = CARD_DEFAULT_WEP;
	filter = CARD_DEFAULT_FILTER; /* (0) Do not filter un-encrypted data */
	करोt1x = CARD_DEFAULT_DOT1X;
	mlme = CARD_DEFAULT_MLME_MODE;
	conक्रमmance = CARD_DEFAULT_CONFORMANCE;
	घातer = 127;
	mode = CARD_DEFAULT_IW_MODE;

	mgt_set(priv, DOT11_OID_CHANNEL, &channel);
	mgt_set(priv, DOT11_OID_AUTHENABLE, &authen);
	mgt_set(priv, DOT11_OID_PRIVACYINVOKED, &wep);
	mgt_set(priv, DOT11_OID_PSMBUFFER, &psm_buffer);
	mgt_set(priv, DOT11_OID_EXUNENCRYPTED, &filter);
	mgt_set(priv, DOT11_OID_DOT1XENABLE, &करोt1x);
	mgt_set(priv, DOT11_OID_MLMEAUTOLEVEL, &mlme);
	mgt_set(priv, OID_INL_DOT11D_CONFORMANCE, &conक्रमmance);
	mgt_set(priv, OID_INL_OUTPUTPOWER, &घातer);

	/* This sets all of the mode-dependent values */
	prism54_mib_mode_helper(priv, mode);
पूर्ण

/* this will be executed outside of atomic context thanks to
 * schedule_work(), thus we can as well use sleeping semaphore
 * locking */
व्योम
prism54_update_stats(काष्ठा work_काष्ठा *work)
अणु
	islpci_निजी *priv = container_of(work, islpci_निजी, stats_work);
	अक्षर *data;
	काष्ठा obj_bss bss, *bss2;
	जोड़ oid_res_t r;

	mutex_lock(&priv->stats_lock);

/* Noise न्यूनमान.
 * I'm not sure अगर the unit is dBm.
 * Note : If we are not connected, this value seems to be irrelevant. */

	mgt_get_request(priv, DOT11_OID_NOISEFLOOR, 0, शून्य, &r);
	priv->local_iwstatistics.qual.noise = r.u;

/* Get the rssi of the link. To करो this we need to retrieve a bss. */

	/* First get the MAC address of the AP we are associated with. */
	mgt_get_request(priv, DOT11_OID_BSSID, 0, शून्य, &r);
	data = r.ptr;

	/* copy this MAC to the bss */
	स_नकल(bss.address, data, ETH_ALEN);
	kमुक्त(data);

	/* now ask क्रम the corresponding bss */
	mgt_get_request(priv, DOT11_OID_BSSFIND, 0, (व्योम *) &bss, &r);
	bss2 = r.ptr;
	/* report the rssi and use it to calculate
	 *  link quality through a संकेत-noise
	 *  ratio */
	priv->local_iwstatistics.qual.level = bss2->rssi;
	priv->local_iwstatistics.qual.qual =
	    bss2->rssi - priv->iwstatistics.qual.noise;

	kमुक्त(bss2);

	/* report that the stats are new */
	priv->local_iwstatistics.qual.updated = 0x7;

/* Rx : unable to decrypt the MPDU */
	mgt_get_request(priv, DOT11_OID_PRIVRXFAILED, 0, शून्य, &r);
	priv->local_iwstatistics.discard.code = r.u;

/* Tx : Max MAC retries num reached */
	mgt_get_request(priv, DOT11_OID_MPDUTXFAILED, 0, शून्य, &r);
	priv->local_iwstatistics.discard.retries = r.u;

	mutex_unlock(&priv->stats_lock);
पूर्ण

काष्ठा iw_statistics *
prism54_get_wireless_stats(काष्ठा net_device *ndev)
अणु
	islpci_निजी *priv = netdev_priv(ndev);

	/* If the stats are being updated वापस old data */
	अगर (mutex_trylock(&priv->stats_lock)) अणु
		स_नकल(&priv->iwstatistics, &priv->local_iwstatistics,
		       माप (काष्ठा iw_statistics));
		/* They won't be marked updated क्रम the next समय */
		priv->local_iwstatistics.qual.updated = 0;
		mutex_unlock(&priv->stats_lock);
	पूर्ण अन्यथा
		priv->iwstatistics.qual.updated = 0;

	/* Update our wireless stats, but करो not schedule to often
	 * (max 1 HZ) */
	अगर ((priv->stats_बारtamp == 0) ||
	    समय_after(jअगरfies, priv->stats_बारtamp + 1 * HZ)) अणु
		schedule_work(&priv->stats_work);
		priv->stats_बारtamp = jअगरfies;
	पूर्ण

	वापस &priv->iwstatistics;
पूर्ण

अटल पूर्णांक
prism54_commit(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
	       अक्षर *cwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);

	/* simply re-set the last set SSID, this should commit most stuff */

	/* Commit in Monitor mode is not necessary, also setting essid
	 * in Monitor mode करोes not make sense and isn't allowed क्रम this
	 * device's firmware */
	अगर (priv->iw_mode != IW_MODE_MONITOR)
		वापस mgt_set_request(priv, DOT11_OID_SSID, 0, शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक
prism54_get_name(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		 अक्षर *cwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	अक्षर *capabilities;
	जोड़ oid_res_t r;
	पूर्णांक rvalue;

	अगर (islpci_get_state(priv) < PRV_STATE_INIT) अणु
		म_नकलन(cwrq, "NOT READY!", IFNAMSIZ);
		वापस 0;
	पूर्ण
	rvalue = mgt_get_request(priv, OID_INL_PHYCAPABILITIES, 0, शून्य, &r);

	चयन (r.u) अणु
	हाल INL_PHYCAP_5000MHZ:
		capabilities = "IEEE 802.11a/b/g";
		अवरोध;
	हाल INL_PHYCAP_FAA:
		capabilities = "IEEE 802.11b/g - FAA Support";
		अवरोध;
	हाल INL_PHYCAP_2400MHZ:
	शेष:
		capabilities = "IEEE 802.11b/g";	/* Default */
		अवरोध;
	पूर्ण
	म_नकलन(cwrq, capabilities, IFNAMSIZ);
	वापस rvalue;
पूर्ण

अटल पूर्णांक
prism54_set_freq(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		 काष्ठा iw_freq *fwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	पूर्णांक rvalue;
	u32 c;

	अगर (fwrq->m < 1000)
		/* we have a channel number */
		c = fwrq->m;
	अन्यथा
		c = (fwrq->e == 1) ? channel_of_freq(fwrq->m / 100000) : 0;

	rvalue = c ? mgt_set_request(priv, DOT11_OID_CHANNEL, 0, &c) : -EINVAL;

	/* Call commit handler */
	वापस (rvalue ? rvalue : -EINPROGRESS);
पूर्ण

अटल पूर्णांक
prism54_get_freq(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		 काष्ठा iw_freq *fwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	जोड़ oid_res_t r;
	पूर्णांक rvalue;

	rvalue = mgt_get_request(priv, DOT11_OID_CHANNEL, 0, शून्य, &r);
	fwrq->i = r.u;
	rvalue |= mgt_get_request(priv, DOT11_OID_FREQUENCY, 0, शून्य, &r);
	fwrq->m = r.u;
	fwrq->e = 3;

	वापस rvalue;
पूर्ण

अटल पूर्णांक
prism54_set_mode(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		 __u32 * uwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	u32 mlmeस्वतःlevel = CARD_DEFAULT_MLME_MODE;

	/* Let's see अगर the user passed a valid Linux Wireless mode */
	अगर (*uwrq > IW_MODE_MONITOR || *uwrq < IW_MODE_AUTO) अणु
		prपूर्णांकk(KERN_DEBUG
		       "%s: %s() You passed a non-valid init_mode.\n",
		       priv->ndev->name, __func__);
		वापस -EINVAL;
	पूर्ण

	करोwn_ग_लिखो(&priv->mib_sem);

	अगर (prism54_mib_mode_helper(priv, *uwrq)) अणु
		up_ग_लिखो(&priv->mib_sem);
		वापस -EOPNOTSUPP;
	पूर्ण

	/* the ACL code needs an पूर्णांकermediate mlmeस्वतःlevel. The wpa stuff an
	 * extended one.
	 */
	अगर ((*uwrq == IW_MODE_MASTER) && (priv->acl.policy != MAC_POLICY_OPEN))
		mlmeस्वतःlevel = DOT11_MLME_INTERMEDIATE;
	अगर (priv->wpa)
		mlmeस्वतःlevel = DOT11_MLME_EXTENDED;

	mgt_set(priv, DOT11_OID_MLMEAUTOLEVEL, &mlmeस्वतःlevel);

	अगर (mgt_commit(priv)) अणु
		up_ग_लिखो(&priv->mib_sem);
		वापस -EIO;
	पूर्ण
	priv->ndev->type = (priv->iw_mode == IW_MODE_MONITOR)
	    ? priv->monitor_type : ARPHRD_ETHER;
	up_ग_लिखो(&priv->mib_sem);

	वापस 0;
पूर्ण

/* Use mib cache */
अटल पूर्णांक
prism54_get_mode(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		 __u32 * uwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);

	BUG_ON((priv->iw_mode < IW_MODE_AUTO) || (priv->iw_mode >
						  IW_MODE_MONITOR));
	*uwrq = priv->iw_mode;

	वापस 0;
पूर्ण

/* we use DOT11_OID_EDTHRESHOLD. From what I guess the card will not try to
 * emit data अगर (sensitivity > rssi - noise) (in dBm).
 * prism54_set_sens करोes not seem to work.
 */

अटल पूर्णांक
prism54_set_sens(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		 काष्ठा iw_param *vwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	u32 sens;

	/* by शेष  the card sets this to 20. */
	sens = vwrq->disabled ? 20 : vwrq->value;

	वापस mgt_set_request(priv, DOT11_OID_EDTHRESHOLD, 0, &sens);
पूर्ण

अटल पूर्णांक
prism54_get_sens(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		 काष्ठा iw_param *vwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	जोड़ oid_res_t r;
	पूर्णांक rvalue;

	rvalue = mgt_get_request(priv, DOT11_OID_EDTHRESHOLD, 0, शून्य, &r);

	vwrq->value = r.u;
	vwrq->disabled = (vwrq->value == 0);
	vwrq->fixed = 1;

	वापस rvalue;
पूर्ण

अटल पूर्णांक
prism54_get_range(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		  काष्ठा iw_poपूर्णांक *dwrq, अक्षर *extra)
अणु
	काष्ठा iw_range *range = (काष्ठा iw_range *) extra;
	islpci_निजी *priv = netdev_priv(ndev);
	u8 *data;
	पूर्णांक i, m, rvalue;
	काष्ठा obj_frequencies *freq;
	जोड़ oid_res_t r;

	स_रखो(range, 0, माप (काष्ठा iw_range));
	dwrq->length = माप (काष्ठा iw_range);

	/* set the wireless extension version number */
	range->we_version_source = SUPPORTED_WIRELESS_EXT;
	range->we_version_compiled = WIRELESS_EXT;

	/* Now the encoding capabilities */
	range->num_encoding_sizes = 3;
	/* 64(40) bits WEP */
	range->encoding_size[0] = 5;
	/* 128(104) bits WEP */
	range->encoding_size[1] = 13;
	/* 256 bits क्रम WPA-PSK */
	range->encoding_size[2] = 32;
	/* 4 keys are allowed */
	range->max_encoding_tokens = 4;

	/* we करोn't know the quality range... */
	range->max_qual.level = 0;
	range->max_qual.noise = 0;
	range->max_qual.qual = 0;
	/* these value describe an average quality. Needs more tweaking... */
	range->avg_qual.level = -80;	/* -80 dBm */
	range->avg_qual.noise = 0;	/* करोn't know what to put here */
	range->avg_qual.qual = 0;

	range->sensitivity = 200;

	/* retry limit capabilities */
	range->retry_capa = IW_RETRY_LIMIT | IW_RETRY_LIFETIME;
	range->retry_flags = IW_RETRY_LIMIT;
	range->r_समय_flags = IW_RETRY_LIFETIME;

	/* I करोn't know the range. Put stupid things here */
	range->min_retry = 1;
	range->max_retry = 65535;
	range->min_r_समय = 1024;
	range->max_r_समय = 65535 * 1024;

	/* txघातer is supported in dBm's */
	range->txघातer_capa = IW_TXPOW_DBM;

	/* Event capability (kernel + driver) */
	range->event_capa[0] = (IW_EVENT_CAPA_K_0 |
	IW_EVENT_CAPA_MASK(SIOCGIWTHRSPY) |
	IW_EVENT_CAPA_MASK(SIOCGIWAP));
	range->event_capa[1] = IW_EVENT_CAPA_K_1;
	range->event_capa[4] = IW_EVENT_CAPA_MASK(IWEVCUSTOM);

	range->enc_capa = IW_ENC_CAPA_WPA | IW_ENC_CAPA_WPA2 |
		IW_ENC_CAPA_CIPHER_TKIP;

	अगर (islpci_get_state(priv) < PRV_STATE_INIT)
		वापस 0;

	/* Request the device क्रम the supported frequencies
	 * not really relevant since some devices will report the 5 GHz band
	 * frequencies even अगर they करोn't support them.
	 */
	rvalue =
	    mgt_get_request(priv, DOT11_OID_SUPPORTEDFREQUENCIES, 0, शून्य, &r);
	freq = r.ptr;

	range->num_channels = freq->nr;
	range->num_frequency = freq->nr;

	m = min(IW_MAX_FREQUENCIES, (पूर्णांक) freq->nr);
	क्रम (i = 0; i < m; i++) अणु
		range->freq[i].m = freq->mhz[i];
		range->freq[i].e = 6;
		range->freq[i].i = channel_of_freq(freq->mhz[i]);
	पूर्ण
	kमुक्त(freq);

	rvalue |= mgt_get_request(priv, DOT11_OID_SUPPORTEDRATES, 0, शून्य, &r);
	data = r.ptr;

	/* We got an array of अक्षर. It is शून्य terminated. */
	i = 0;
	जबतक ((i < IW_MAX_BITRATES) && (*data != 0)) अणु
		/*       the result must be in bps. The card gives us 500Kbps */
		range->bitrate[i] = *data * 500000;
		i++;
		data++;
	पूर्ण
	range->num_bitrates = i;
	kमुक्त(r.ptr);

	वापस rvalue;
पूर्ण

/* Set AP address*/

अटल पूर्णांक
prism54_set_wap(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		काष्ठा sockaddr *awrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	अक्षर bssid[6];
	पूर्णांक rvalue;

	अगर (awrq->sa_family != ARPHRD_ETHER)
		वापस -EINVAL;

	/* prepare the काष्ठाure क्रम the set object */
	स_नकल(&bssid[0], awrq->sa_data, ETH_ALEN);

	/* set the bssid -- करोes this make sense when in AP mode? */
	rvalue = mgt_set_request(priv, DOT11_OID_BSSID, 0, &bssid);

	वापस (rvalue ? rvalue : -EINPROGRESS);	/* Call commit handler */
पूर्ण

/* get AP address*/

अटल पूर्णांक
prism54_get_wap(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		काष्ठा sockaddr *awrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	जोड़ oid_res_t r;
	पूर्णांक rvalue;

	rvalue = mgt_get_request(priv, DOT11_OID_BSSID, 0, शून्य, &r);
	स_नकल(awrq->sa_data, r.ptr, ETH_ALEN);
	awrq->sa_family = ARPHRD_ETHER;
	kमुक्त(r.ptr);

	वापस rvalue;
पूर्ण

अटल पूर्णांक
prism54_set_scan(काष्ठा net_device *dev, काष्ठा iw_request_info *info,
		 काष्ठा iw_param *vwrq, अक्षर *extra)
अणु
	/* hehe the device करोes this स्वतःmagicaly */
	वापस 0;
पूर्ण

/* a little helper that will translate our data पूर्णांकo a card independent
 * क्रमmat that the Wireless Tools will understand. This was inspired by
 * the "Aironet driver for 4500 and 4800 series cards" (GPL)
 */

अटल अक्षर *
prism54_translate_bss(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		      अक्षर *current_ev, अक्षर *end_buf, काष्ठा obj_bss *bss,
		      अक्षर noise)
अणु
	काष्ठा iw_event iwe;	/* Temporary buffer */
	लघु cap;
	islpci_निजी *priv = netdev_priv(ndev);
	u8 wpa_ie[MAX_WPA_IE_LEN];
	माप_प्रकार wpa_ie_len;

	/* The first entry must be the MAC address */
	स_नकल(iwe.u.ap_addr.sa_data, bss->address, ETH_ALEN);
	iwe.u.ap_addr.sa_family = ARPHRD_ETHER;
	iwe.cmd = SIOCGIWAP;
	current_ev = iwe_stream_add_event(info, current_ev, end_buf,
					  &iwe, IW_EV_ADDR_LEN);

	/* The following entries will be displayed in the same order we give them */

	/* The ESSID. */
	iwe.u.data.length = bss->ssid.length;
	iwe.u.data.flags = 1;
	iwe.cmd = SIOCGIWESSID;
	current_ev = iwe_stream_add_poपूर्णांक(info, current_ev, end_buf,
					  &iwe, bss->ssid.octets);

	/* Capabilities */
#घोषणा CAP_ESS 0x01
#घोषणा CAP_IBSS 0x02
#घोषणा CAP_CRYPT 0x10

	/* Mode */
	cap = bss->capinfo;
	iwe.u.mode = 0;
	अगर (cap & CAP_ESS)
		iwe.u.mode = IW_MODE_MASTER;
	अन्यथा अगर (cap & CAP_IBSS)
		iwe.u.mode = IW_MODE_ADHOC;
	iwe.cmd = SIOCGIWMODE;
	अगर (iwe.u.mode)
		current_ev = iwe_stream_add_event(info, current_ev, end_buf,
						  &iwe, IW_EV_UINT_LEN);

	/* Encryption capability */
	अगर (cap & CAP_CRYPT)
		iwe.u.data.flags = IW_ENCODE_ENABLED | IW_ENCODE_NOKEY;
	अन्यथा
		iwe.u.data.flags = IW_ENCODE_DISABLED;
	iwe.u.data.length = 0;
	iwe.cmd = SIOCGIWENCODE;
	current_ev = iwe_stream_add_poपूर्णांक(info, current_ev, end_buf,
					  &iwe, शून्य);

	/* Add frequency. (लघु) bss->channel is the frequency in MHz */
	iwe.u.freq.m = bss->channel;
	iwe.u.freq.e = 6;
	iwe.cmd = SIOCGIWFREQ;
	current_ev = iwe_stream_add_event(info, current_ev, end_buf,
					  &iwe, IW_EV_FREQ_LEN);

	/* Add quality statistics */
	iwe.u.qual.level = bss->rssi;
	iwe.u.qual.noise = noise;
	/* करो a simple SNR क्रम quality */
	iwe.u.qual.qual = bss->rssi - noise;
	iwe.cmd = IWEVQUAL;
	current_ev = iwe_stream_add_event(info, current_ev, end_buf,
					  &iwe, IW_EV_QUAL_LEN);

	/* Add WPA/RSN Inक्रमmation Element, अगर any */
	wpa_ie_len = prism54_wpa_bss_ie_get(priv, bss->address, wpa_ie);
	अगर (wpa_ie_len > 0) अणु
		iwe.cmd = IWEVGENIE;
		iwe.u.data.length = min_t(माप_प्रकार, wpa_ie_len, MAX_WPA_IE_LEN);
		current_ev = iwe_stream_add_poपूर्णांक(info, current_ev, end_buf,
						  &iwe, wpa_ie);
	पूर्ण
	/* Do the bitrates */
	अणु
		अक्षर *current_val = current_ev + iwe_stream_lcp_len(info);
		पूर्णांक i;
		पूर्णांक mask;

		iwe.cmd = SIOCGIWRATE;
		/* Those two flags are ignored... */
		iwe.u.bitrate.fixed = iwe.u.bitrate.disabled = 0;

		/* Parse the biपंचांगask */
		mask = 0x1;
		क्रम(i = 0; i < माप(scan_rate_list); i++) अणु
			अगर(bss->rates & mask) अणु
				iwe.u.bitrate.value = (scan_rate_list[i] * 500000);
				current_val = iwe_stream_add_value(
					info, current_ev, current_val,
					end_buf, &iwe, IW_EV_PARAM_LEN);
			पूर्ण
			mask <<= 1;
		पूर्ण
		/* Check अगर we added any event */
		अगर ((current_val - current_ev) > iwe_stream_lcp_len(info))
			current_ev = current_val;
	पूर्ण

	वापस current_ev;
पूर्ण

अटल पूर्णांक
prism54_get_scan(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		 काष्ठा iw_poपूर्णांक *dwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	पूर्णांक i, rvalue;
	काष्ठा obj_bsslist *bsslist;
	u32 noise = 0;
	अक्षर *current_ev = extra;
	जोड़ oid_res_t r;

	अगर (islpci_get_state(priv) < PRV_STATE_INIT) अणु
		/* device is not पढ़ोy, fail gently */
		dwrq->length = 0;
		वापस 0;
	पूर्ण

	/* first get the noise value. We will use it to report the link quality */
	rvalue = mgt_get_request(priv, DOT11_OID_NOISEFLOOR, 0, शून्य, &r);
	noise = r.u;

	/* Ask the device क्रम a list of known bss.
	* The old API, using SIOCGIWAPLIST, had a hard limit of IW_MAX_AP=64.
	* The new API, using SIOCGIWSCAN, is only limited by the buffer size.
	* WE-14->WE-16, the buffer is limited to IW_SCAN_MAX_DATA bytes.
	* Starting with WE-17, the buffer can be as big as needed.
	* But the device won't repport anything अगर you change the value
	* of IWMAX_BSS=24. */

	rvalue |= mgt_get_request(priv, DOT11_OID_BSSLIST, 0, शून्य, &r);
	bsslist = r.ptr;

	/* ok now, scan the list and translate its info */
	क्रम (i = 0; i < (पूर्णांक) bsslist->nr; i++) अणु
		current_ev = prism54_translate_bss(ndev, info, current_ev,
						   extra + dwrq->length,
						   &(bsslist->bsslist[i]),
						   noise);

		/* Check अगर there is space क्रम one more entry */
		अगर((extra + dwrq->length - current_ev) <= IW_EV_ADDR_LEN) अणु
			/* Ask user space to try again with a bigger buffer */
			rvalue = -E2BIG;
			अवरोध;
		पूर्ण
	पूर्ण

	kमुक्त(bsslist);
	dwrq->length = (current_ev - extra);
	dwrq->flags = 0;	/* toकरो */

	वापस rvalue;
पूर्ण

अटल पूर्णांक
prism54_set_essid(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		  काष्ठा iw_poपूर्णांक *dwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	काष्ठा obj_ssid essid;

	स_रखो(essid.octets, 0, 33);

	/* Check अगर we were asked क्रम `any' */
	अगर (dwrq->flags && dwrq->length) अणु
		अगर (dwrq->length > 32)
			वापस -E2BIG;
		essid.length = dwrq->length;
		स_नकल(essid.octets, extra, dwrq->length);
	पूर्ण अन्यथा
		essid.length = 0;

	अगर (priv->iw_mode != IW_MODE_MONITOR)
		वापस mgt_set_request(priv, DOT11_OID_SSID, 0, &essid);

	/* If in monitor mode, just save to mib */
	mgt_set(priv, DOT11_OID_SSID, &essid);
	वापस 0;

पूर्ण

अटल पूर्णांक
prism54_get_essid(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		  काष्ठा iw_poपूर्णांक *dwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	काष्ठा obj_ssid *essid;
	जोड़ oid_res_t r;
	पूर्णांक rvalue;

	rvalue = mgt_get_request(priv, DOT11_OID_SSID, 0, शून्य, &r);
	essid = r.ptr;

	अगर (essid->length) अणु
		dwrq->flags = 1;	/* set ESSID to ON क्रम Wireless Extensions */
		/* अगर it is too big, trunk it */
		dwrq->length = min((u8)IW_ESSID_MAX_SIZE, essid->length);
	पूर्ण अन्यथा अणु
		dwrq->flags = 0;
		dwrq->length = 0;
	पूर्ण
	essid->octets[dwrq->length] = '\0';
	स_नकल(extra, essid->octets, dwrq->length);
	kमुक्त(essid);

	वापस rvalue;
पूर्ण

/* Provides no functionality, just completes the ioctl. In essence this is a
 * just a cosmetic ioctl.
 */
अटल पूर्णांक
prism54_set_nick(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		 काष्ठा iw_poपूर्णांक *dwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);

	अगर (dwrq->length > IW_ESSID_MAX_SIZE)
		वापस -E2BIG;

	करोwn_ग_लिखो(&priv->mib_sem);
	स_रखो(priv->nickname, 0, माप (priv->nickname));
	स_नकल(priv->nickname, extra, dwrq->length);
	up_ग_लिखो(&priv->mib_sem);

	वापस 0;
पूर्ण

अटल पूर्णांक
prism54_get_nick(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		 काष्ठा iw_poपूर्णांक *dwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);

	dwrq->length = 0;

	करोwn_पढ़ो(&priv->mib_sem);
	dwrq->length = म_माप(priv->nickname);
	स_नकल(extra, priv->nickname, dwrq->length);
	up_पढ़ो(&priv->mib_sem);

	वापस 0;
पूर्ण

/* Set the allowed Bitrates */

अटल पूर्णांक
prism54_set_rate(काष्ठा net_device *ndev,
		 काष्ठा iw_request_info *info,
		 काष्ठा iw_param *vwrq, अक्षर *extra)
अणु

	islpci_निजी *priv = netdev_priv(ndev);
	u32 rate, profile;
	अक्षर *data;
	पूर्णांक ret, i;
	जोड़ oid_res_t r;

	अगर (vwrq->value == -1) अणु
		/* स्वतः mode. No limit. */
		profile = 1;
		वापस mgt_set_request(priv, DOT11_OID_PROखाताS, 0, &profile);
	पूर्ण

	ret = mgt_get_request(priv, DOT11_OID_SUPPORTEDRATES, 0, शून्य, &r);
	अगर (ret) अणु
		kमुक्त(r.ptr);
		वापस ret;
	पूर्ण

	rate = (u32) (vwrq->value / 500000);
	data = r.ptr;
	i = 0;

	जबतक (data[i]) अणु
		अगर (rate && (data[i] == rate)) अणु
			अवरोध;
		पूर्ण
		अगर (vwrq->value == i) अणु
			अवरोध;
		पूर्ण
		data[i] |= 0x80;
		i++;
	पूर्ण

	अगर (!data[i]) अणु
		kमुक्त(r.ptr);
		वापस -EINVAL;
	पूर्ण

	data[i] |= 0x80;
	data[i + 1] = 0;

	/* Now, check अगर we want a fixed or स्वतः value */
	अगर (vwrq->fixed) अणु
		data[0] = data[i];
		data[1] = 0;
	पूर्ण

/*
	i = 0;
	prपूर्णांकk("prism54 rate: ");
	जबतक(data[i]) अणु
		prपूर्णांकk("%u ", data[i]);
		i++;
	पूर्ण
	prपूर्णांकk("0\n");
*/
	profile = -1;
	ret = mgt_set_request(priv, DOT11_OID_PROखाताS, 0, &profile);
	ret |= mgt_set_request(priv, DOT11_OID_EXTENDEDRATES, 0, data);
	ret |= mgt_set_request(priv, DOT11_OID_RATES, 0, data);

	kमुक्त(r.ptr);

	वापस ret;
पूर्ण

/* Get the current bit rate */
अटल पूर्णांक
prism54_get_rate(काष्ठा net_device *ndev,
		 काष्ठा iw_request_info *info,
		 काष्ठा iw_param *vwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	पूर्णांक rvalue;
	अक्षर *data;
	जोड़ oid_res_t r;

	/* Get the current bit rate */
	अगर ((rvalue = mgt_get_request(priv, GEN_OID_LINKSTATE, 0, शून्य, &r)))
		वापस rvalue;
	vwrq->value = r.u * 500000;

	/* request the device क्रम the enabled rates */
	rvalue = mgt_get_request(priv, DOT11_OID_RATES, 0, शून्य, &r);
	अगर (rvalue) अणु
		kमुक्त(r.ptr);
		वापस rvalue;
	पूर्ण
	data = r.ptr;
	vwrq->fixed = (data[0] != 0) && (data[1] == 0);
	kमुक्त(r.ptr);

	वापस 0;
पूर्ण

अटल पूर्णांक
prism54_set_rts(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		काष्ठा iw_param *vwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);

	वापस mgt_set_request(priv, DOT11_OID_RTSTHRESH, 0, &vwrq->value);
पूर्ण

अटल पूर्णांक
prism54_get_rts(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		काष्ठा iw_param *vwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	जोड़ oid_res_t r;
	पूर्णांक rvalue;

	/* get the rts threshold */
	rvalue = mgt_get_request(priv, DOT11_OID_RTSTHRESH, 0, शून्य, &r);
	vwrq->value = r.u;

	वापस rvalue;
पूर्ण

अटल पूर्णांक
prism54_set_frag(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		 काष्ठा iw_param *vwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);

	वापस mgt_set_request(priv, DOT11_OID_FRAGTHRESH, 0, &vwrq->value);
पूर्ण

अटल पूर्णांक
prism54_get_frag(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		 काष्ठा iw_param *vwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	जोड़ oid_res_t r;
	पूर्णांक rvalue;

	rvalue = mgt_get_request(priv, DOT11_OID_FRAGTHRESH, 0, शून्य, &r);
	vwrq->value = r.u;

	वापस rvalue;
पूर्ण

/* Here we have (min,max) = max retries क्रम (small frames, big frames). Where
 * big frame <=>  bigger than the rts threshold
 * small frame <=>  smaller than the rts threshold
 * This is not really the behavior expected by the wireless tool but it seems
 * to be a common behavior in other drivers.
 */

अटल पूर्णांक
prism54_set_retry(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		  काष्ठा iw_param *vwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	u32 slimit = 0, llimit = 0;	/* लघु and दीर्घ limit */
	u32 lअगरeसमय = 0;
	पूर्णांक rvalue = 0;

	अगर (vwrq->disabled)
		/* we cannot disable this feature */
		वापस -EINVAL;

	अगर (vwrq->flags & IW_RETRY_LIMIT) अणु
		अगर (vwrq->flags & IW_RETRY_SHORT)
			slimit = vwrq->value;
		अन्यथा अगर (vwrq->flags & IW_RETRY_LONG)
			llimit = vwrq->value;
		अन्यथा अणु
			/* we are asked to set both */
			slimit = vwrq->value;
			llimit = vwrq->value;
		पूर्ण
	पूर्ण
	अगर (vwrq->flags & IW_RETRY_LIFETIME)
		/* Wireless tools use us unit जबतक the device uses 1024 us unit */
		lअगरeसमय = vwrq->value / 1024;

	/* now set what is requested */
	अगर (slimit)
		rvalue =
		    mgt_set_request(priv, DOT11_OID_SHORTRETRIES, 0, &slimit);
	अगर (llimit)
		rvalue |=
		    mgt_set_request(priv, DOT11_OID_LONGRETRIES, 0, &llimit);
	अगर (lअगरeसमय)
		rvalue |=
		    mgt_set_request(priv, DOT11_OID_MAXTXLIFETIME, 0,
				    &lअगरeसमय);
	वापस rvalue;
पूर्ण

अटल पूर्णांक
prism54_get_retry(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		  काष्ठा iw_param *vwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	जोड़ oid_res_t r;
	पूर्णांक rvalue = 0;
	vwrq->disabled = 0;	/* It cannot be disabled */

	अगर ((vwrq->flags & IW_RETRY_TYPE) == IW_RETRY_LIFETIME) अणु
		/* we are asked क्रम the lअगरe समय */
		rvalue =
		    mgt_get_request(priv, DOT11_OID_MAXTXLIFETIME, 0, शून्य, &r);
		vwrq->value = r.u * 1024;
		vwrq->flags = IW_RETRY_LIFETIME;
	पूर्ण अन्यथा अगर ((vwrq->flags & IW_RETRY_LONG)) अणु
		/* we are asked क्रम the दीर्घ retry limit */
		rvalue |=
		    mgt_get_request(priv, DOT11_OID_LONGRETRIES, 0, शून्य, &r);
		vwrq->value = r.u;
		vwrq->flags = IW_RETRY_LIMIT | IW_RETRY_LONG;
	पूर्ण अन्यथा अणु
		/* शेष. get the  लघु retry limit */
		rvalue |=
		    mgt_get_request(priv, DOT11_OID_SHORTRETRIES, 0, शून्य, &r);
		vwrq->value = r.u;
		vwrq->flags = IW_RETRY_LIMIT | IW_RETRY_SHORT;
	पूर्ण

	वापस rvalue;
पूर्ण

अटल पूर्णांक
prism54_set_encode(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		   काष्ठा iw_poपूर्णांक *dwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	पूर्णांक rvalue = 0, क्रमce = 0;
	पूर्णांक authen = DOT11_AUTH_OS, invoke = 0, exunencrypt = 0;
	जोड़ oid_res_t r;

	/* with the new API, it's impossible to get a शून्य poपूर्णांकer.
	 * New version of iwconfig set the IW_ENCODE_NOKEY flag
	 * when no key is given, but older versions करोn't. */

	अगर (dwrq->length > 0) अणु
		/* we have a key to set */
		पूर्णांक index = (dwrq->flags & IW_ENCODE_INDEX) - 1;
		पूर्णांक current_index;
		काष्ठा obj_key key = अणु DOT11_PRIV_WEP, 0, "" पूर्ण;

		/* get the current key index */
		rvalue = mgt_get_request(priv, DOT11_OID_DEFKEYID, 0, शून्य, &r);
		current_index = r.u;
		/* Verअगरy that the key is not marked as invalid */
		अगर (!(dwrq->flags & IW_ENCODE_NOKEY)) अणु
			अगर (dwrq->length > KEY_SIZE_TKIP) अणु
				/* User-provided key data too big */
				वापस -EINVAL;
			पूर्ण
			अगर (dwrq->length > KEY_SIZE_WEP104) अणु
				/* WPA-PSK TKIP */
				key.type = DOT11_PRIV_TKIP;
				key.length = KEY_SIZE_TKIP;
			पूर्ण अन्यथा अगर (dwrq->length > KEY_SIZE_WEP40) अणु
				/* WEP 104/128 */
				key.length = KEY_SIZE_WEP104;
			पूर्ण अन्यथा अणु
				/* WEP 40/64 */
				key.length = KEY_SIZE_WEP40;
			पूर्ण
			स_रखो(key.key, 0, माप (key.key));
			स_नकल(key.key, extra, dwrq->length);

			अगर ((index < 0) || (index > 3))
				/* no index provided use the current one */
				index = current_index;

			/* now send the key to the card  */
			rvalue |=
			    mgt_set_request(priv, DOT11_OID_DEFKEYX, index,
					    &key);
		पूर्ण
		/*
		 * If a valid key is set, encryption should be enabled
		 * (user may turn it off later).
		 * This is also how "iwconfig ethX key on" works
		 */
		अगर ((index == current_index) && (key.length > 0))
			क्रमce = 1;
	पूर्ण अन्यथा अणु
		पूर्णांक index = (dwrq->flags & IW_ENCODE_INDEX) - 1;
		अगर ((index >= 0) && (index <= 3)) अणु
			/* we want to set the key index */
			rvalue |=
			    mgt_set_request(priv, DOT11_OID_DEFKEYID, 0,
					    &index);
		पूर्ण अन्यथा अणु
			अगर (!(dwrq->flags & IW_ENCODE_MODE)) अणु
				/* we cannot करो anything. Complain. */
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण
	/* now पढ़ो the flags */
	अगर (dwrq->flags & IW_ENCODE_DISABLED) अणु
		/* Encoding disabled,
		 * authen = DOT11_AUTH_OS;
		 * invoke = 0;
		 * exunencrypt = 0; */
	पूर्ण
	अगर (dwrq->flags & IW_ENCODE_OPEN)
		/* Encode but accept non-encoded packets. No auth */
		invoke = 1;
	अगर ((dwrq->flags & IW_ENCODE_RESTRICTED) || क्रमce) अणु
		/* Refuse non-encoded packets. Auth */
		authen = DOT11_AUTH_BOTH;
		invoke = 1;
		exunencrypt = 1;
	पूर्ण
	/* करो the change अगर requested  */
	अगर ((dwrq->flags & IW_ENCODE_MODE) || क्रमce) अणु
		rvalue |=
		    mgt_set_request(priv, DOT11_OID_AUTHENABLE, 0, &authen);
		rvalue |=
		    mgt_set_request(priv, DOT11_OID_PRIVACYINVOKED, 0, &invoke);
		rvalue |=
		    mgt_set_request(priv, DOT11_OID_EXUNENCRYPTED, 0,
				    &exunencrypt);
	पूर्ण
	वापस rvalue;
पूर्ण

अटल पूर्णांक
prism54_get_encode(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		   काष्ठा iw_poपूर्णांक *dwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	काष्ठा obj_key *key;
	u32 devindex, index = (dwrq->flags & IW_ENCODE_INDEX) - 1;
	u32 authen = 0, invoke = 0, exunencrypt = 0;
	पूर्णांक rvalue;
	जोड़ oid_res_t r;

	/* first get the flags */
	rvalue = mgt_get_request(priv, DOT11_OID_AUTHENABLE, 0, शून्य, &r);
	authen = r.u;
	rvalue |= mgt_get_request(priv, DOT11_OID_PRIVACYINVOKED, 0, शून्य, &r);
	invoke = r.u;
	rvalue |= mgt_get_request(priv, DOT11_OID_EXUNENCRYPTED, 0, शून्य, &r);
	exunencrypt = r.u;

	अगर (invoke && (authen == DOT11_AUTH_BOTH) && exunencrypt)
		dwrq->flags = IW_ENCODE_RESTRICTED;
	अन्यथा अगर ((authen == DOT11_AUTH_OS) && !exunencrypt) अणु
		अगर (invoke)
			dwrq->flags = IW_ENCODE_OPEN;
		अन्यथा
			dwrq->flags = IW_ENCODE_DISABLED;
	पूर्ण अन्यथा
		/* The card should not work in this state */
		dwrq->flags = 0;

	/* get the current device key index */
	rvalue |= mgt_get_request(priv, DOT11_OID_DEFKEYID, 0, शून्य, &r);
	devindex = r.u;
	/* Now get the key, वापस it */
	अगर (index == -1 || index > 3)
		/* no index provided, use the current one */
		index = devindex;
	rvalue |= mgt_get_request(priv, DOT11_OID_DEFKEYX, index, शून्य, &r);
	key = r.ptr;
	dwrq->length = key->length;
	स_नकल(extra, key->key, dwrq->length);
	kमुक्त(key);
	/* वापस the used key index */
	dwrq->flags |= devindex + 1;

	वापस rvalue;
पूर्ण

अटल पूर्णांक
prism54_get_txघातer(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		    काष्ठा iw_param *vwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	जोड़ oid_res_t r;
	पूर्णांक rvalue;

	rvalue = mgt_get_request(priv, OID_INL_OUTPUTPOWER, 0, शून्य, &r);
	/* पूर्णांकersil firmware operates in 0.25 dBm (1/4 dBm) */
	vwrq->value = (s32) r.u / 4;
	vwrq->fixed = 1;
	/* radio is not turned of
	 * btw: how is possible to turn off only the radio
	 */
	vwrq->disabled = 0;

	वापस rvalue;
पूर्ण

अटल पूर्णांक
prism54_set_txघातer(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		    काष्ठा iw_param *vwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	s32 u = vwrq->value;

	/* पूर्णांकersil firmware operates in 0.25 dBm (1/4) */
	u *= 4;
	अगर (vwrq->disabled) अणु
		/* करोn't know how to disable radio */
		prपूर्णांकk(KERN_DEBUG
		       "%s: %s() disabling radio is not yet supported.\n",
		       priv->ndev->name, __func__);
		वापस -ENOTSUPP;
	पूर्ण अन्यथा अगर (vwrq->fixed)
		/* currently only fixed value is supported */
		वापस mgt_set_request(priv, OID_INL_OUTPUTPOWER, 0, &u);
	अन्यथा अणु
		prपूर्णांकk(KERN_DEBUG
		       "%s: %s() auto power will be implemented later.\n",
		       priv->ndev->name, __func__);
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक prism54_set_genie(काष्ठा net_device *ndev,
			     काष्ठा iw_request_info *info,
			     काष्ठा iw_poपूर्णांक *data, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	पूर्णांक alen, ret = 0;
	काष्ठा obj_attachment *attach;

	अगर (data->length > MAX_WPA_IE_LEN ||
	    (data->length && extra == शून्य))
		वापस -EINVAL;

	स_नकल(priv->wpa_ie, extra, data->length);
	priv->wpa_ie_len = data->length;

	alen = माप(*attach) + priv->wpa_ie_len;
	attach = kzalloc(alen, GFP_KERNEL);
	अगर (attach == शून्य)
		वापस -ENOMEM;

#घोषणा WLAN_FC_TYPE_MGMT 0
#घोषणा WLAN_FC_STYPE_ASSOC_REQ 0
#घोषणा WLAN_FC_STYPE_REASSOC_REQ 2

	/* Note: endianness is covered by mgt_set_varlen */
	attach->type = (WLAN_FC_TYPE_MGMT << 2) |
               (WLAN_FC_STYPE_ASSOC_REQ << 4);
	attach->id = -1;
	attach->size = priv->wpa_ie_len;
	स_नकल(attach->data, extra, priv->wpa_ie_len);

	ret = mgt_set_varlen(priv, DOT11_OID_ATTACHMENT, attach,
		priv->wpa_ie_len);
	अगर (ret == 0) अणु
		attach->type = (WLAN_FC_TYPE_MGMT << 2) |
			(WLAN_FC_STYPE_REASSOC_REQ << 4);

		ret = mgt_set_varlen(priv, DOT11_OID_ATTACHMENT, attach,
			priv->wpa_ie_len);
		अगर (ret == 0)
			prपूर्णांकk(KERN_DEBUG "%s: WPA IE Attachment was set\n",
				ndev->name);
	पूर्ण

	kमुक्त(attach);
	वापस ret;
पूर्ण


अटल पूर्णांक prism54_get_genie(काष्ठा net_device *ndev,
			     काष्ठा iw_request_info *info,
			     काष्ठा iw_poपूर्णांक *data, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	पूर्णांक len = priv->wpa_ie_len;

	अगर (len <= 0) अणु
		data->length = 0;
		वापस 0;
	पूर्ण

	अगर (data->length < len)
		वापस -E2BIG;

	data->length = len;
	स_नकल(extra, priv->wpa_ie, len);

	वापस 0;
पूर्ण

अटल पूर्णांक prism54_set_auth(काष्ठा net_device *ndev,
			       काष्ठा iw_request_info *info,
			       जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	काष्ठा iw_param *param = &wrqu->param;
	u32 mlmelevel = 0, authen = 0, करोt1x = 0;
	u32 exunencrypt = 0, privinvoked = 0, wpa = 0;
	u32 old_wpa;
	पूर्णांक ret = 0;
	जोड़ oid_res_t r;

	अगर (islpci_get_state(priv) < PRV_STATE_INIT)
		वापस 0;

	/* first get the flags */
	करोwn_ग_लिखो(&priv->mib_sem);
	wpa = old_wpa = priv->wpa;
	up_ग_लिखो(&priv->mib_sem);
	ret = mgt_get_request(priv, DOT11_OID_AUTHENABLE, 0, शून्य, &r);
	authen = r.u;
	ret = mgt_get_request(priv, DOT11_OID_PRIVACYINVOKED, 0, शून्य, &r);
	privinvoked = r.u;
	ret = mgt_get_request(priv, DOT11_OID_EXUNENCRYPTED, 0, शून्य, &r);
	exunencrypt = r.u;
	ret = mgt_get_request(priv, DOT11_OID_DOT1XENABLE, 0, शून्य, &r);
	करोt1x = r.u;
	ret = mgt_get_request(priv, DOT11_OID_MLMEAUTOLEVEL, 0, शून्य, &r);
	mlmelevel = r.u;

	अगर (ret < 0)
		जाओ out;

	चयन (param->flags & IW_AUTH_INDEX) अणु
	हाल IW_AUTH_CIPHER_PAIRWISE:
	हाल IW_AUTH_CIPHER_GROUP:
	हाल IW_AUTH_KEY_MGMT:
		अवरोध;

	हाल IW_AUTH_WPA_ENABLED:
		/* Do the same thing as IW_AUTH_WPA_VERSION */
		अगर (param->value) अणु
			wpa = 1;
			privinvoked = 1; /* For privacy invoked */
			exunencrypt = 1; /* Filter out all unencrypted frames */
			करोt1x = 0x01; /* To enable eap filter */
			mlmelevel = DOT11_MLME_EXTENDED;
			authen = DOT11_AUTH_OS; /* Only WEP uses _SK and _BOTH */
		पूर्ण अन्यथा अणु
			wpa = 0;
			privinvoked = 0;
			exunencrypt = 0; /* Do not filter un-encrypted data */
			करोt1x = 0;
			mlmelevel = DOT11_MLME_AUTO;
		पूर्ण
		अवरोध;

	हाल IW_AUTH_WPA_VERSION:
		अगर (param->value & IW_AUTH_WPA_VERSION_DISABLED) अणु
			wpa = 0;
			privinvoked = 0;
			exunencrypt = 0; /* Do not filter un-encrypted data */
			करोt1x = 0;
			mlmelevel = DOT11_MLME_AUTO;
		पूर्ण अन्यथा अणु
			अगर (param->value & IW_AUTH_WPA_VERSION_WPA)
				wpa = 1;
			अन्यथा अगर (param->value & IW_AUTH_WPA_VERSION_WPA2)
				wpa = 2;
			privinvoked = 1; /* For privacy invoked */
			exunencrypt = 1; /* Filter out all unencrypted frames */
			करोt1x = 0x01; /* To enable eap filter */
			mlmelevel = DOT11_MLME_EXTENDED;
			authen = DOT11_AUTH_OS; /* Only WEP uses _SK and _BOTH */
		पूर्ण
		अवरोध;

	हाल IW_AUTH_RX_UNENCRYPTED_EAPOL:
		/* करोt1x should be the opposite of RX_UNENCRYPTED_EAPOL;
		 * turn off करोt1x when allowing receipt of unencrypted EAPOL
		 * frames, turn on करोt1x when receipt should be disallowed
		 */
		करोt1x = param->value ? 0 : 0x01;
		अवरोध;

	हाल IW_AUTH_PRIVACY_INVOKED:
		privinvoked = param->value ? 1 : 0;
		अवरोध;

	हाल IW_AUTH_DROP_UNENCRYPTED:
		exunencrypt = param->value ? 1 : 0;
		अवरोध;

	हाल IW_AUTH_80211_AUTH_ALG:
		अगर (param->value & IW_AUTH_ALG_SHARED_KEY) अणु
			/* Only WEP uses _SK and _BOTH */
			अगर (wpa > 0) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			authen = DOT11_AUTH_SK;
		पूर्ण अन्यथा अगर (param->value & IW_AUTH_ALG_OPEN_SYSTEM) अणु
			authen = DOT11_AUTH_OS;
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Set all the values */
	करोwn_ग_लिखो(&priv->mib_sem);
	priv->wpa = wpa;
	up_ग_लिखो(&priv->mib_sem);
	mgt_set_request(priv, DOT11_OID_AUTHENABLE, 0, &authen);
	mgt_set_request(priv, DOT11_OID_PRIVACYINVOKED, 0, &privinvoked);
	mgt_set_request(priv, DOT11_OID_EXUNENCRYPTED, 0, &exunencrypt);
	mgt_set_request(priv, DOT11_OID_DOT1XENABLE, 0, &करोt1x);
	mgt_set_request(priv, DOT11_OID_MLMEAUTOLEVEL, 0, &mlmelevel);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक prism54_get_auth(काष्ठा net_device *ndev,
			    काष्ठा iw_request_info *info,
			    जोड़ iwreq_data *wrqu, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	काष्ठा iw_param *param = &wrqu->param;
	u32 wpa = 0;
	पूर्णांक ret = 0;
	जोड़ oid_res_t r;

	अगर (islpci_get_state(priv) < PRV_STATE_INIT)
		वापस 0;

	/* first get the flags */
	करोwn_ग_लिखो(&priv->mib_sem);
	wpa = priv->wpa;
	up_ग_लिखो(&priv->mib_sem);

	चयन (param->flags & IW_AUTH_INDEX) अणु
	हाल IW_AUTH_CIPHER_PAIRWISE:
	हाल IW_AUTH_CIPHER_GROUP:
	हाल IW_AUTH_KEY_MGMT:
		/*
		 * wpa_supplicant will control these पूर्णांकernally
		 */
		ret = -EOPNOTSUPP;
		अवरोध;

	हाल IW_AUTH_WPA_VERSION:
		चयन (wpa) अणु
		हाल 1:
			param->value = IW_AUTH_WPA_VERSION_WPA;
			अवरोध;
		हाल 2:
			param->value = IW_AUTH_WPA_VERSION_WPA2;
			अवरोध;
		हाल 0:
		शेष:
			param->value = IW_AUTH_WPA_VERSION_DISABLED;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल IW_AUTH_DROP_UNENCRYPTED:
		ret = mgt_get_request(priv, DOT11_OID_EXUNENCRYPTED, 0, शून्य, &r);
		अगर (ret >= 0)
			param->value = r.u > 0 ? 1 : 0;
		अवरोध;

	हाल IW_AUTH_80211_AUTH_ALG:
		ret = mgt_get_request(priv, DOT11_OID_AUTHENABLE, 0, शून्य, &r);
		अगर (ret >= 0) अणु
			चयन (r.u) अणु
			हाल DOT11_AUTH_OS:
				param->value = IW_AUTH_ALG_OPEN_SYSTEM;
				अवरोध;
			हाल DOT11_AUTH_BOTH:
			हाल DOT11_AUTH_SK:
				param->value = IW_AUTH_ALG_SHARED_KEY;
				अवरोध;
			हाल DOT11_AUTH_NONE:
			शेष:
				param->value = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल IW_AUTH_WPA_ENABLED:
		param->value = wpa > 0 ? 1 : 0;
		अवरोध;

	हाल IW_AUTH_RX_UNENCRYPTED_EAPOL:
		ret = mgt_get_request(priv, DOT11_OID_DOT1XENABLE, 0, शून्य, &r);
		अगर (ret >= 0)
			param->value = r.u > 0 ? 1 : 0;
		अवरोध;

	हाल IW_AUTH_PRIVACY_INVOKED:
		ret = mgt_get_request(priv, DOT11_OID_PRIVACYINVOKED, 0, शून्य, &r);
		अगर (ret >= 0)
			param->value = r.u > 0 ? 1 : 0;
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक prism54_set_encodeext(काष्ठा net_device *ndev,
				 काष्ठा iw_request_info *info,
				 जोड़ iwreq_data *wrqu,
				 अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	काष्ठा iw_poपूर्णांक *encoding = &wrqu->encoding;
	काष्ठा iw_encode_ext *ext = (काष्ठा iw_encode_ext *)extra;
	पूर्णांक idx, alg = ext->alg, set_key = 1;
	जोड़ oid_res_t r;
	पूर्णांक authen = DOT11_AUTH_OS, invoke = 0, exunencrypt = 0;
	पूर्णांक ret = 0;

	अगर (islpci_get_state(priv) < PRV_STATE_INIT)
		वापस 0;

	/* Determine and validate the key index */
	idx = (encoding->flags & IW_ENCODE_INDEX) - 1;
	अगर (idx) अणु
		अगर (idx < 0 || idx > 3)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		ret = mgt_get_request(priv, DOT11_OID_DEFKEYID, 0, शून्य, &r);
		अगर (ret < 0)
			जाओ out;
		idx = r.u;
	पूर्ण

	अगर (encoding->flags & IW_ENCODE_DISABLED)
		alg = IW_ENCODE_ALG_NONE;

	अगर (ext->ext_flags & IW_ENCODE_EXT_SET_TX_KEY) अणु
		/* Only set transmit key index here, actual
		 * key is set below अगर needed.
		 */
		ret = mgt_set_request(priv, DOT11_OID_DEFKEYID, 0, &idx);
		set_key = ext->key_len > 0 ? 1 : 0;
	पूर्ण

	अगर (set_key) अणु
		काष्ठा obj_key key = अणु DOT11_PRIV_WEP, 0, "" पूर्ण;
		चयन (alg) अणु
		हाल IW_ENCODE_ALG_NONE:
			अवरोध;
		हाल IW_ENCODE_ALG_WEP:
			अगर (ext->key_len > KEY_SIZE_WEP104) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			अगर (ext->key_len > KEY_SIZE_WEP40)
				key.length = KEY_SIZE_WEP104;
			अन्यथा
				key.length = KEY_SIZE_WEP40;
			अवरोध;
		हाल IW_ENCODE_ALG_TKIP:
			अगर (ext->key_len > KEY_SIZE_TKIP) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			key.type = DOT11_PRIV_TKIP;
			key.length = KEY_SIZE_TKIP;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		अगर (key.length) अणु
			स_रखो(key.key, 0, माप(key.key));
			स_नकल(key.key, ext->key, ext->key_len);
			ret = mgt_set_request(priv, DOT11_OID_DEFKEYX, idx,
					    &key);
			अगर (ret < 0)
				जाओ out;
		पूर्ण
	पूर्ण

	/* Read the flags */
	अगर (encoding->flags & IW_ENCODE_DISABLED) अणु
		/* Encoding disabled,
		 * authen = DOT11_AUTH_OS;
		 * invoke = 0;
		 * exunencrypt = 0; */
	पूर्ण
	अगर (encoding->flags & IW_ENCODE_OPEN) अणु
		/* Encode but accept non-encoded packets. No auth */
		invoke = 1;
	पूर्ण
	अगर (encoding->flags & IW_ENCODE_RESTRICTED) अणु
		/* Refuse non-encoded packets. Auth */
		authen = DOT11_AUTH_BOTH;
		invoke = 1;
		exunencrypt = 1;
	पूर्ण

	/* करो the change अगर requested  */
	अगर (encoding->flags & IW_ENCODE_MODE) अणु
		ret = mgt_set_request(priv, DOT11_OID_AUTHENABLE, 0,
				      &authen);
		ret = mgt_set_request(priv, DOT11_OID_PRIVACYINVOKED, 0,
				      &invoke);
		ret = mgt_set_request(priv, DOT11_OID_EXUNENCRYPTED, 0,
				      &exunencrypt);
	पूर्ण

out:
	वापस ret;
पूर्ण


अटल पूर्णांक prism54_get_encodeext(काष्ठा net_device *ndev,
				 काष्ठा iw_request_info *info,
				 जोड़ iwreq_data *wrqu,
				 अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	काष्ठा iw_poपूर्णांक *encoding = &wrqu->encoding;
	काष्ठा iw_encode_ext *ext = (काष्ठा iw_encode_ext *)extra;
	पूर्णांक idx, max_key_len;
	जोड़ oid_res_t r;
	पूर्णांक authen = DOT11_AUTH_OS, invoke = 0, exunencrypt = 0, wpa = 0;
	पूर्णांक ret = 0;

	अगर (islpci_get_state(priv) < PRV_STATE_INIT)
		वापस 0;

	/* first get the flags */
	ret = mgt_get_request(priv, DOT11_OID_AUTHENABLE, 0, शून्य, &r);
	authen = r.u;
	ret = mgt_get_request(priv, DOT11_OID_PRIVACYINVOKED, 0, शून्य, &r);
	invoke = r.u;
	ret = mgt_get_request(priv, DOT11_OID_EXUNENCRYPTED, 0, शून्य, &r);
	exunencrypt = r.u;
	अगर (ret < 0)
		जाओ out;

	max_key_len = encoding->length - माप(*ext);
	अगर (max_key_len < 0)
		वापस -EINVAL;

	idx = (encoding->flags & IW_ENCODE_INDEX) - 1;
	अगर (idx) अणु
		अगर (idx < 0 || idx > 3)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		ret = mgt_get_request(priv, DOT11_OID_DEFKEYID, 0, शून्य, &r);
		अगर (ret < 0)
			जाओ out;
		idx = r.u;
	पूर्ण

	encoding->flags = idx + 1;
	स_रखो(ext, 0, माप(*ext));

	चयन (authen) अणु
	हाल DOT11_AUTH_BOTH:
	हाल DOT11_AUTH_SK:
		wrqu->encoding.flags |= IW_ENCODE_RESTRICTED;
		fallthrough;
	हाल DOT11_AUTH_OS:
	शेष:
		wrqu->encoding.flags |= IW_ENCODE_OPEN;
		अवरोध;
	पूर्ण

	करोwn_ग_लिखो(&priv->mib_sem);
	wpa = priv->wpa;
	up_ग_लिखो(&priv->mib_sem);

	अगर (authen == DOT11_AUTH_OS && !exunencrypt && !invoke && !wpa) अणु
		/* No encryption */
		ext->alg = IW_ENCODE_ALG_NONE;
		ext->key_len = 0;
		wrqu->encoding.flags |= IW_ENCODE_DISABLED;
	पूर्ण अन्यथा अणु
		काष्ठा obj_key *key;

		ret = mgt_get_request(priv, DOT11_OID_DEFKEYX, idx, शून्य, &r);
		अगर (ret < 0)
			जाओ out;
		key = r.ptr;
		अगर (max_key_len < key->length) अणु
			ret = -E2BIG;
			जाओ out;
		पूर्ण
		स_नकल(ext->key, key->key, key->length);
		ext->key_len = key->length;

		चयन (key->type) अणु
		हाल DOT11_PRIV_TKIP:
			ext->alg = IW_ENCODE_ALG_TKIP;
			अवरोध;
		शेष:
		हाल DOT11_PRIV_WEP:
			ext->alg = IW_ENCODE_ALG_WEP;
			अवरोध;
		पूर्ण
		wrqu->encoding.flags |= IW_ENCODE_ENABLED;
	पूर्ण

out:
	वापस ret;
पूर्ण


अटल पूर्णांक
prism54_reset(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
	      __u32 * uwrq, अक्षर *extra)
अणु
	islpci_reset(netdev_priv(ndev), 0);

	वापस 0;
पूर्ण

अटल पूर्णांक
prism54_get_oid(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		काष्ठा iw_poपूर्णांक *dwrq, अक्षर *extra)
अणु
	जोड़ oid_res_t r;
	पूर्णांक rvalue;
	क्रमागत oid_num_t n = dwrq->flags;

	rvalue = mgt_get_request(netdev_priv(ndev), n, 0, शून्य, &r);
	dwrq->length = mgt_response_to_str(n, &r, extra);
	अगर ((isl_oid[n].flags & OID_FLAG_TYPE) != OID_TYPE_U32)
		kमुक्त(r.ptr);
	वापस rvalue;
पूर्ण

अटल पूर्णांक
prism54_set_u32(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		__u32 * uwrq, अक्षर *extra)
अणु
	u32 oid = uwrq[0], u = uwrq[1];

	वापस mgt_set_request(netdev_priv(ndev), oid, 0, &u);
पूर्ण

अटल पूर्णांक
prism54_set_raw(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		काष्ठा iw_poपूर्णांक *dwrq, अक्षर *extra)
अणु
	u32 oid = dwrq->flags;

	वापस mgt_set_request(netdev_priv(ndev), oid, 0, extra);
पूर्ण

व्योम
prism54_acl_init(काष्ठा islpci_acl *acl)
अणु
	mutex_init(&acl->lock);
	INIT_LIST_HEAD(&acl->mac_list);
	acl->size = 0;
	acl->policy = MAC_POLICY_OPEN;
पूर्ण

अटल व्योम
prism54_clear_mac(काष्ठा islpci_acl *acl)
अणु
	काष्ठा list_head *ptr, *next;
	काष्ठा mac_entry *entry;

	mutex_lock(&acl->lock);

	अगर (acl->size == 0) अणु
		mutex_unlock(&acl->lock);
		वापस;
	पूर्ण

	क्रम (ptr = acl->mac_list.next, next = ptr->next;
	     ptr != &acl->mac_list; ptr = next, next = ptr->next) अणु
		entry = list_entry(ptr, काष्ठा mac_entry, _list);
		list_del(ptr);
		kमुक्त(entry);
	पूर्ण
	acl->size = 0;
	mutex_unlock(&acl->lock);
पूर्ण

व्योम
prism54_acl_clean(काष्ठा islpci_acl *acl)
अणु
	prism54_clear_mac(acl);
पूर्ण

अटल पूर्णांक
prism54_add_mac(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		काष्ठा sockaddr *awrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	काष्ठा islpci_acl *acl = &priv->acl;
	काष्ठा mac_entry *entry;
	काष्ठा sockaddr *addr = (काष्ठा sockaddr *) extra;

	अगर (addr->sa_family != ARPHRD_ETHER)
		वापस -EOPNOTSUPP;

	entry = kदो_स्मृति(माप (काष्ठा mac_entry), GFP_KERNEL);
	अगर (entry == शून्य)
		वापस -ENOMEM;

	स_नकल(entry->addr, addr->sa_data, ETH_ALEN);

	अगर (mutex_lock_पूर्णांकerruptible(&acl->lock)) अणु
		kमुक्त(entry);
		वापस -ERESTARTSYS;
	पूर्ण
	list_add_tail(&entry->_list, &acl->mac_list);
	acl->size++;
	mutex_unlock(&acl->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक
prism54_del_mac(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		काष्ठा sockaddr *awrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	काष्ठा islpci_acl *acl = &priv->acl;
	काष्ठा mac_entry *entry;
	काष्ठा sockaddr *addr = (काष्ठा sockaddr *) extra;

	अगर (addr->sa_family != ARPHRD_ETHER)
		वापस -EOPNOTSUPP;

	अगर (mutex_lock_पूर्णांकerruptible(&acl->lock))
		वापस -ERESTARTSYS;
	list_क्रम_each_entry(entry, &acl->mac_list, _list) अणु
		अगर (ether_addr_equal(entry->addr, addr->sa_data)) अणु
			list_del(&entry->_list);
			acl->size--;
			kमुक्त(entry);
			mutex_unlock(&acl->lock);
			वापस 0;
		पूर्ण
	पूर्ण
	mutex_unlock(&acl->lock);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
prism54_get_mac(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		काष्ठा iw_poपूर्णांक *dwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	काष्ठा islpci_acl *acl = &priv->acl;
	काष्ठा mac_entry *entry;
	काष्ठा sockaddr *dst = (काष्ठा sockaddr *) extra;

	dwrq->length = 0;

	अगर (mutex_lock_पूर्णांकerruptible(&acl->lock))
		वापस -ERESTARTSYS;

	list_क्रम_each_entry(entry, &acl->mac_list, _list) अणु
		स_नकल(dst->sa_data, entry->addr, ETH_ALEN);
		dst->sa_family = ARPHRD_ETHER;
		dwrq->length++;
		dst++;
	पूर्ण
	mutex_unlock(&acl->lock);
	वापस 0;
पूर्ण

/* Setting policy also clears the MAC acl, even अगर we करोn't change the शेष
 * policy
 */

अटल पूर्णांक
prism54_set_policy(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		   __u32 * uwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	काष्ठा islpci_acl *acl = &priv->acl;
	u32 mlmeस्वतःlevel;

	prism54_clear_mac(acl);

	अगर ((*uwrq < MAC_POLICY_OPEN) || (*uwrq > MAC_POLICY_REJECT))
		वापस -EINVAL;

	करोwn_ग_लिखो(&priv->mib_sem);

	acl->policy = *uwrq;

	/* the ACL code needs an पूर्णांकermediate mlmeस्वतःlevel */
	अगर ((priv->iw_mode == IW_MODE_MASTER) &&
	    (acl->policy != MAC_POLICY_OPEN))
		mlmeस्वतःlevel = DOT11_MLME_INTERMEDIATE;
	अन्यथा
		mlmeस्वतःlevel = CARD_DEFAULT_MLME_MODE;
	अगर (priv->wpa)
		mlmeस्वतःlevel = DOT11_MLME_EXTENDED;
	mgt_set(priv, DOT11_OID_MLMEAUTOLEVEL, &mlmeस्वतःlevel);
	/* restart the card with our new policy */
	अगर (mgt_commit(priv)) अणु
		up_ग_लिखो(&priv->mib_sem);
		वापस -EIO;
	पूर्ण
	up_ग_लिखो(&priv->mib_sem);

	वापस 0;
पूर्ण

अटल पूर्णांक
prism54_get_policy(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		   __u32 * uwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	काष्ठा islpci_acl *acl = &priv->acl;

	*uwrq = acl->policy;

	वापस 0;
पूर्ण

/* Return 1 only अगर client should be accepted. */

अटल पूर्णांक
prism54_mac_accept(काष्ठा islpci_acl *acl, अक्षर *mac)
अणु
	काष्ठा mac_entry *entry;
	पूर्णांक res = 0;

	अगर (mutex_lock_पूर्णांकerruptible(&acl->lock))
		वापस -ERESTARTSYS;

	अगर (acl->policy == MAC_POLICY_OPEN) अणु
		mutex_unlock(&acl->lock);
		वापस 1;
	पूर्ण

	list_क्रम_each_entry(entry, &acl->mac_list, _list) अणु
		अगर (स_भेद(entry->addr, mac, ETH_ALEN) == 0) अणु
			res = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	res = (acl->policy == MAC_POLICY_ACCEPT) ? !res : res;
	mutex_unlock(&acl->lock);

	वापस res;
पूर्ण

अटल पूर्णांक
prism54_kick_all(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		 काष्ठा iw_poपूर्णांक *dwrq, अक्षर *extra)
अणु
	काष्ठा obj_mlme *mlme;
	पूर्णांक rvalue;

	mlme = kदो_स्मृति(माप (काष्ठा obj_mlme), GFP_KERNEL);
	अगर (mlme == शून्य)
		वापस -ENOMEM;

	/* Tell the card to kick every client */
	mlme->id = 0;
	rvalue =
	    mgt_set_request(netdev_priv(ndev), DOT11_OID_DISASSOCIATE, 0, mlme);
	kमुक्त(mlme);

	वापस rvalue;
पूर्ण

अटल पूर्णांक
prism54_kick_mac(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		 काष्ठा sockaddr *awrq, अक्षर *extra)
अणु
	काष्ठा obj_mlme *mlme;
	काष्ठा sockaddr *addr = (काष्ठा sockaddr *) extra;
	पूर्णांक rvalue;

	अगर (addr->sa_family != ARPHRD_ETHER)
		वापस -EOPNOTSUPP;

	mlme = kदो_स्मृति(माप (काष्ठा obj_mlme), GFP_KERNEL);
	अगर (mlme == शून्य)
		वापस -ENOMEM;

	/* Tell the card to only kick the corresponding bastard */
	स_नकल(mlme->address, addr->sa_data, ETH_ALEN);
	mlme->id = -1;
	rvalue =
	    mgt_set_request(netdev_priv(ndev), DOT11_OID_DISASSOCIATE, 0, mlme);

	kमुक्त(mlme);

	वापस rvalue;
पूर्ण

/* Translate a TRAP oid पूर्णांकo a wireless event. Called in islpci_mgt_receive. */

अटल व्योम
क्रमmat_event(islpci_निजी *priv, अक्षर *dest, स्थिर अक्षर *str,
	     स्थिर काष्ठा obj_mlme *mlme, u16 *length, पूर्णांक error)
अणु
	पूर्णांक n = snम_लिखो(dest, IW_CUSTOM_MAX,
			 "%s %s %pM %s (%2.2X)",
			 str,
			 ((priv->iw_mode == IW_MODE_MASTER) ? "from" : "to"),
			 mlme->address,
			 (error ? (mlme->code ? " : REJECTED " : " : ACCEPTED ")
			  : ""), mlme->code);
	WARN_ON(n >= IW_CUSTOM_MAX);
	*length = n;
पूर्ण

अटल व्योम
send_क्रमmatted_event(islpci_निजी *priv, स्थिर अक्षर *str,
		     स्थिर काष्ठा obj_mlme *mlme, पूर्णांक error)
अणु
	जोड़ iwreq_data wrqu;
	अक्षर *memptr;

	memptr = kदो_स्मृति(IW_CUSTOM_MAX, GFP_KERNEL);
	अगर (!memptr)
		वापस;
	wrqu.data.poपूर्णांकer = memptr;
	wrqu.data.length = 0;
	क्रमmat_event(priv, memptr, str, mlme, &wrqu.data.length,
		     error);
	wireless_send_event(priv->ndev, IWEVCUSTOM, &wrqu, memptr);
	kमुक्त(memptr);
पूर्ण

अटल व्योम
send_simple_event(islpci_निजी *priv, स्थिर अक्षर *str)
अणु
	जोड़ iwreq_data wrqu;
	अक्षर *memptr;
	पूर्णांक n = म_माप(str);

	memptr = kदो_स्मृति(IW_CUSTOM_MAX, GFP_KERNEL);
	अगर (!memptr)
		वापस;
	BUG_ON(n >= IW_CUSTOM_MAX);
	wrqu.data.poपूर्णांकer = memptr;
	wrqu.data.length = n;
	म_नकल(memptr, str);
	wireless_send_event(priv->ndev, IWEVCUSTOM, &wrqu, memptr);
	kमुक्त(memptr);
पूर्ण

अटल व्योम
link_changed(काष्ठा net_device *ndev, u32 bitrate)
अणु
	islpci_निजी *priv = netdev_priv(ndev);

	अगर (bitrate) अणु
		netअगर_carrier_on(ndev);
		अगर (priv->iw_mode == IW_MODE_INFRA) अणु
			जोड़ iwreq_data uwrq;
			prism54_get_wap(ndev, शून्य, (काष्ठा sockaddr *) &uwrq,
					शून्य);
			wireless_send_event(ndev, SIOCGIWAP, &uwrq, शून्य);
		पूर्ण अन्यथा
			send_simple_event(netdev_priv(ndev),
					  "Link established");
	पूर्ण अन्यथा अणु
		netअगर_carrier_off(ndev);
		send_simple_event(netdev_priv(ndev), "Link lost");
	पूर्ण
पूर्ण

/* Beacon/ProbeResp payload header */
काष्ठा ieee80211_beacon_phdr अणु
	u8 बारtamp[8];
	u16 beacon_पूर्णांक;
	u16 capab_info;
पूर्ण __packed;

#घोषणा WLAN_EID_GENERIC 0xdd
अटल u8 wpa_oid[4] = अणु 0x00, 0x50, 0xf2, 1 पूर्ण;

अटल व्योम
prism54_wpa_bss_ie_add(islpci_निजी *priv, u8 *bssid,
		       u8 *wpa_ie, माप_प्रकार wpa_ie_len)
अणु
	काष्ठा list_head *ptr;
	काष्ठा islpci_bss_wpa_ie *bss = शून्य;

	अगर (wpa_ie_len > MAX_WPA_IE_LEN)
		wpa_ie_len = MAX_WPA_IE_LEN;

	mutex_lock(&priv->wpa_lock);

	/* try to use existing entry */
	list_क्रम_each(ptr, &priv->bss_wpa_list) अणु
		bss = list_entry(ptr, काष्ठा islpci_bss_wpa_ie, list);
		अगर (स_भेद(bss->bssid, bssid, ETH_ALEN) == 0) अणु
			list_move(&bss->list, &priv->bss_wpa_list);
			अवरोध;
		पूर्ण
		bss = शून्य;
	पूर्ण

	अगर (bss == शून्य) अणु
		/* add a new BSS entry; अगर max number of entries is alपढ़ोy
		 * reached, replace the least recently updated */
		अगर (priv->num_bss_wpa >= MAX_BSS_WPA_IE_COUNT) अणु
			bss = list_entry(priv->bss_wpa_list.prev,
					 काष्ठा islpci_bss_wpa_ie, list);
			list_del(&bss->list);
		पूर्ण अन्यथा अणु
			bss = kzalloc(माप (*bss), GFP_ATOMIC);
			अगर (bss != शून्य)
				priv->num_bss_wpa++;
		पूर्ण
		अगर (bss != शून्य) अणु
			स_नकल(bss->bssid, bssid, ETH_ALEN);
			list_add(&bss->list, &priv->bss_wpa_list);
		पूर्ण
	पूर्ण

	अगर (bss != शून्य) अणु
		स_नकल(bss->wpa_ie, wpa_ie, wpa_ie_len);
		bss->wpa_ie_len = wpa_ie_len;
		bss->last_update = jअगरfies;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_DEBUG "Failed to add BSS WPA entry for "
		       "%pM\n", bssid);
	पूर्ण

	/* expire old entries from WPA list */
	जबतक (priv->num_bss_wpa > 0) अणु
		bss = list_entry(priv->bss_wpa_list.prev,
				 काष्ठा islpci_bss_wpa_ie, list);
		अगर (!समय_after(jअगरfies, bss->last_update + 60 * HZ))
			अवरोध;

		list_del(&bss->list);
		priv->num_bss_wpa--;
		kमुक्त(bss);
	पूर्ण

	mutex_unlock(&priv->wpa_lock);
पूर्ण

अटल माप_प्रकार
prism54_wpa_bss_ie_get(islpci_निजी *priv, u8 *bssid, u8 *wpa_ie)
अणु
	काष्ठा list_head *ptr;
	काष्ठा islpci_bss_wpa_ie *bss = शून्य;
	माप_प्रकार len = 0;

	mutex_lock(&priv->wpa_lock);

	list_क्रम_each(ptr, &priv->bss_wpa_list) अणु
		bss = list_entry(ptr, काष्ठा islpci_bss_wpa_ie, list);
		अगर (स_भेद(bss->bssid, bssid, ETH_ALEN) == 0)
			अवरोध;
		bss = शून्य;
	पूर्ण
	अगर (bss) अणु
		len = bss->wpa_ie_len;
		स_नकल(wpa_ie, bss->wpa_ie, len);
	पूर्ण
	mutex_unlock(&priv->wpa_lock);

	वापस len;
पूर्ण

व्योम
prism54_wpa_bss_ie_init(islpci_निजी *priv)
अणु
	INIT_LIST_HEAD(&priv->bss_wpa_list);
	mutex_init(&priv->wpa_lock);
पूर्ण

व्योम
prism54_wpa_bss_ie_clean(islpci_निजी *priv)
अणु
	काष्ठा islpci_bss_wpa_ie *bss, *n;

	list_क्रम_each_entry_safe(bss, n, &priv->bss_wpa_list, list) अणु
		kमुक्त(bss);
	पूर्ण
पूर्ण

अटल व्योम
prism54_process_bss_data(islpci_निजी *priv, u32 oid, u8 *addr,
			 u8 *payload, माप_प्रकार len)
अणु
	काष्ठा ieee80211_beacon_phdr *hdr;
	u8 *pos, *end;

	अगर (!priv->wpa)
		वापस;

	hdr = (काष्ठा ieee80211_beacon_phdr *) payload;
	pos = (u8 *) (hdr + 1);
	end = payload + len;
	जबतक (pos < end) अणु
		अगर (pos + 2 + pos[1] > end) अणु
			prपूर्णांकk(KERN_DEBUG "Parsing Beacon/ProbeResp failed "
			       "for %pM\n", addr);
			वापस;
		पूर्ण
		अगर (pos[0] == WLAN_EID_GENERIC && pos[1] >= 4 &&
		    स_भेद(pos + 2, wpa_oid, 4) == 0) अणु
			prism54_wpa_bss_ie_add(priv, addr, pos, pos[1] + 2);
			वापस;
		पूर्ण
		pos += 2 + pos[1];
	पूर्ण
पूर्ण

अटल व्योम
handle_request(islpci_निजी *priv, काष्ठा obj_mlme *mlme, क्रमागत oid_num_t oid)
अणु
	अगर (((mlme->state == DOT11_STATE_AUTHING) ||
	     (mlme->state == DOT11_STATE_ASSOCING))
	    && mgt_mlme_answer(priv)) अणु
		/* Someone is requesting auth and we must respond. Just send back
		 * the trap with error code set accordingly.
		 */
		mlme->code = prism54_mac_accept(&priv->acl,
						mlme->address) ? 0 : 1;
		mgt_set_request(priv, oid, 0, mlme);
	पूर्ण
पूर्ण

अटल पूर्णांक
prism54_process_trap_helper(islpci_निजी *priv, क्रमागत oid_num_t oid,
			    अक्षर *data)
अणु
	काष्ठा obj_mlme *mlme = (काष्ठा obj_mlme *) data;
	काष्ठा obj_mlmeex *mlmeex = (काष्ठा obj_mlmeex *) data;
	काष्ठा obj_mlmeex *confirm;
	u8 wpa_ie[MAX_WPA_IE_LEN];
	पूर्णांक wpa_ie_len;
	माप_प्रकार len = 0; /* u16, better? */
	u8 *payload = शून्य, *pos = शून्य;
	पूर्णांक ret;

	/* I think all trapable objects are listed here.
	 * Some oids have a EX version. The dअगरference is that they are emitted
	 * in DOT11_MLME_EXTENDED mode (set with DOT11_OID_MLMEAUTOLEVEL)
	 * with more info.
	 * The few events alपढ़ोy defined by the wireless tools are not really
	 * suited. We use the more flexible custom event facility.
	 */

	अगर (oid >= DOT11_OID_BEACON) अणु
		len = mlmeex->size;
		payload = pos = mlmeex->data;
	पूर्ण

	/* I fear prism54_process_bss_data won't work with big endian data */
	अगर ((oid == DOT11_OID_BEACON) || (oid == DOT11_OID_PROBE))
		prism54_process_bss_data(priv, oid, mlmeex->address,
					 payload, len);

	mgt_le_to_cpu(isl_oid[oid].flags & OID_FLAG_TYPE, (व्योम *) mlme);

	चयन (oid) अणु

	हाल GEN_OID_LINKSTATE:
		link_changed(priv->ndev, (u32) *data);
		अवरोध;

	हाल DOT11_OID_MICFAILURE:
		send_simple_event(priv, "Mic failure");
		अवरोध;

	हाल DOT11_OID_DEAUTHENTICATE:
		send_क्रमmatted_event(priv, "DeAuthenticate request", mlme, 0);
		अवरोध;

	हाल DOT11_OID_AUTHENTICATE:
		handle_request(priv, mlme, oid);
		send_क्रमmatted_event(priv, "Authenticate request", mlme, 1);
		अवरोध;

	हाल DOT11_OID_DISASSOCIATE:
		send_क्रमmatted_event(priv, "Disassociate request", mlme, 0);
		अवरोध;

	हाल DOT11_OID_ASSOCIATE:
		handle_request(priv, mlme, oid);
		send_क्रमmatted_event(priv, "Associate request", mlme, 1);
		अवरोध;

	हाल DOT11_OID_REASSOCIATE:
		handle_request(priv, mlme, oid);
		send_क्रमmatted_event(priv, "ReAssociate request", mlme, 1);
		अवरोध;

	हाल DOT11_OID_BEACON:
		send_क्रमmatted_event(priv,
				     "Received a beacon from an unknown AP",
				     mlme, 0);
		अवरोध;

	हाल DOT11_OID_PROBE:
		/* we received a probe from a client. */
		send_क्रमmatted_event(priv, "Received a probe from client", mlme,
				     0);
		अवरोध;

		/* Note : "mlme" is actually a "struct obj_mlmeex *" here, but this
		 * is backward compatible layout-wise with "struct obj_mlme".
		 */

	हाल DOT11_OID_DEAUTHENTICATEEX:
		send_क्रमmatted_event(priv, "DeAuthenticate request", mlme, 0);
		अवरोध;

	हाल DOT11_OID_AUTHENTICATEEX:
		handle_request(priv, mlme, oid);
		send_क्रमmatted_event(priv, "Authenticate request (ex)", mlme, 1);

		अगर (priv->iw_mode != IW_MODE_MASTER
				&& mlmeex->state != DOT11_STATE_AUTHING)
			अवरोध;

		confirm = kदो_स्मृति(माप(काष्ठा obj_mlmeex) + 6, GFP_ATOMIC);

		अगर (!confirm)
			अवरोध;

		स_नकल(&confirm->address, mlmeex->address, ETH_ALEN);
		prपूर्णांकk(KERN_DEBUG "Authenticate from: address:\t%pM\n",
		       mlmeex->address);
		confirm->id = -1; /* or mlmeex->id ? */
		confirm->state = 0; /* not used */
		confirm->code = 0;
		confirm->size = 6;
		confirm->data[0] = 0x00;
		confirm->data[1] = 0x00;
		confirm->data[2] = 0x02;
		confirm->data[3] = 0x00;
		confirm->data[4] = 0x00;
		confirm->data[5] = 0x00;

		ret = mgt_set_varlen(priv, DOT11_OID_ASSOCIATEEX, confirm, 6);

		kमुक्त(confirm);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल DOT11_OID_DISASSOCIATEEX:
		send_क्रमmatted_event(priv, "Disassociate request (ex)", mlme, 0);
		अवरोध;

	हाल DOT11_OID_ASSOCIATEEX:
		handle_request(priv, mlme, oid);
		send_क्रमmatted_event(priv, "Associate request (ex)", mlme, 1);

		अगर (priv->iw_mode != IW_MODE_MASTER
				&& mlmeex->state != DOT11_STATE_ASSOCING)
			अवरोध;

		confirm = kदो_स्मृति(माप(काष्ठा obj_mlmeex), GFP_ATOMIC);

		अगर (!confirm)
			अवरोध;

		स_नकल(&confirm->address, mlmeex->address, ETH_ALEN);

		confirm->id = ((काष्ठा obj_mlmeex *)mlme)->id;
		confirm->state = 0; /* not used */
		confirm->code = 0;

		wpa_ie_len = prism54_wpa_bss_ie_get(priv, mlmeex->address, wpa_ie);

		अगर (!wpa_ie_len) अणु
			prपूर्णांकk(KERN_DEBUG "No WPA IE found from address:\t%pM\n",
			       mlmeex->address);
			kमुक्त(confirm);
			अवरोध;
		पूर्ण

		confirm->size = wpa_ie_len;
		स_नकल(&confirm->data, wpa_ie, wpa_ie_len);

		mgt_set_varlen(priv, oid, confirm, wpa_ie_len);

		kमुक्त(confirm);

		अवरोध;

	हाल DOT11_OID_REASSOCIATEEX:
		handle_request(priv, mlme, oid);
		send_क्रमmatted_event(priv, "Reassociate request (ex)", mlme, 1);

		अगर (priv->iw_mode != IW_MODE_MASTER
				&& mlmeex->state != DOT11_STATE_ASSOCING)
			अवरोध;

		confirm = kदो_स्मृति(माप(काष्ठा obj_mlmeex), GFP_ATOMIC);

		अगर (!confirm)
			अवरोध;

		स_नकल(&confirm->address, mlmeex->address, ETH_ALEN);

		confirm->id = mlmeex->id;
		confirm->state = 0; /* not used */
		confirm->code = 0;

		wpa_ie_len = prism54_wpa_bss_ie_get(priv, mlmeex->address, wpa_ie);

		अगर (!wpa_ie_len) अणु
			prपूर्णांकk(KERN_DEBUG "No WPA IE found from address:\t%pM\n",
			       mlmeex->address);
			kमुक्त(confirm);
			अवरोध;
		पूर्ण

		confirm->size = wpa_ie_len;
		स_नकल(&confirm->data, wpa_ie, wpa_ie_len);

		mgt_set_varlen(priv, oid, confirm, wpa_ie_len);

		kमुक्त(confirm);

		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Process a device trap.  This is called via schedule_work(), outside of
 * पूर्णांकerrupt context, no locks held.
 */
व्योम
prism54_process_trap(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा islpci_mgmtframe *frame =
		container_of(work, काष्ठा islpci_mgmtframe, ws);
	काष्ठा net_device *ndev = frame->ndev;
	क्रमागत oid_num_t n = mgt_oidtonum(frame->header->oid);

	अगर (n != OID_NUM_LAST)
		prism54_process_trap_helper(netdev_priv(ndev), n, frame->data);
	islpci_mgt_release(frame);
पूर्ण

पूर्णांक
prism54_set_mac_address(काष्ठा net_device *ndev, व्योम *addr)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	पूर्णांक ret;

	अगर (ndev->addr_len != 6)
		वापस -EINVAL;
	ret = mgt_set_request(priv, GEN_OID_MACADDRESS, 0,
			      &((काष्ठा sockaddr *) addr)->sa_data);
	अगर (!ret)
		स_नकल(priv->ndev->dev_addr,
		       &((काष्ठा sockaddr *) addr)->sa_data, ETH_ALEN);

	वापस ret;
पूर्ण

#घोषणा PRISM54_SET_WPA			SIOCIWFIRSTPRIV+12

अटल पूर्णांक
prism54_set_wpa(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		__u32 * uwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	u32 mlme, authen, करोt1x, filter, wep;

	अगर (islpci_get_state(priv) < PRV_STATE_INIT)
		वापस 0;

	wep = 1; /* For privacy invoked */
	filter = 1; /* Filter out all unencrypted frames */
	करोt1x = 0x01; /* To enable eap filter */
	mlme = DOT11_MLME_EXTENDED;
	authen = DOT11_AUTH_OS; /* Only WEP uses _SK and _BOTH */

	करोwn_ग_लिखो(&priv->mib_sem);
	priv->wpa = *uwrq;

	चयन (priv->wpa) अणु
		शेष:
		हाल 0: /* Clears/disables WPA and मित्रs */
			wep = 0;
			filter = 0; /* Do not filter un-encrypted data */
			करोt1x = 0;
			mlme = DOT11_MLME_AUTO;
			prपूर्णांकk("%s: Disabling WPA\n", ndev->name);
			अवरोध;
		हाल 2:
		हाल 1: /* WPA */
			prपूर्णांकk("%s: Enabling WPA\n", ndev->name);
			अवरोध;
	पूर्ण
	up_ग_लिखो(&priv->mib_sem);

	mgt_set_request(priv, DOT11_OID_AUTHENABLE, 0, &authen);
	mgt_set_request(priv, DOT11_OID_PRIVACYINVOKED, 0, &wep);
	mgt_set_request(priv, DOT11_OID_EXUNENCRYPTED, 0, &filter);
	mgt_set_request(priv, DOT11_OID_DOT1XENABLE, 0, &करोt1x);
	mgt_set_request(priv, DOT11_OID_MLMEAUTOLEVEL, 0, &mlme);

	वापस 0;
पूर्ण

अटल पूर्णांक
prism54_get_wpa(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		__u32 * uwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	*uwrq = priv->wpa;
	वापस 0;
पूर्ण

अटल पूर्णांक
prism54_set_prismhdr(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		     __u32 * uwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	priv->monitor_type =
	    (*uwrq ? ARPHRD_IEEE80211_PRISM : ARPHRD_IEEE80211);
	अगर (priv->iw_mode == IW_MODE_MONITOR)
		priv->ndev->type = priv->monitor_type;

	वापस 0;
पूर्ण

अटल पूर्णांक
prism54_get_prismhdr(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		     __u32 * uwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	*uwrq = (priv->monitor_type == ARPHRD_IEEE80211_PRISM);
	वापस 0;
पूर्ण

अटल पूर्णांक
prism54_debug_oid(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		  __u32 * uwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);

	priv->priv_oid = *uwrq;
	prपूर्णांकk("%s: oid 0x%08X\n", ndev->name, *uwrq);

	वापस 0;
पूर्ण

अटल पूर्णांक
prism54_debug_get_oid(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		      काष्ठा iw_poपूर्णांक *data, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	काष्ठा islpci_mgmtframe *response;
	पूर्णांक ret = -EIO;

	prपूर्णांकk("%s: get_oid 0x%08X\n", ndev->name, priv->priv_oid);
	data->length = 0;

	अगर (islpci_get_state(priv) >= PRV_STATE_INIT) अणु
		ret =
		    islpci_mgt_transaction(priv->ndev, PIMFOR_OP_GET,
					   priv->priv_oid, extra, 256,
					   &response);
		prपूर्णांकk("%s: ret: %i\n", ndev->name, ret);
		अगर (ret || !response
		    || response->header->operation == PIMFOR_OP_ERROR) अणु
			अगर (response) अणु
				islpci_mgt_release(response);
			पूर्ण
			prपूर्णांकk("%s: EIO\n", ndev->name);
			ret = -EIO;
		पूर्ण
		अगर (!ret) अणु
			data->length = response->header->length;
			स_नकल(extra, response->data, data->length);
			islpci_mgt_release(response);
			prपूर्णांकk("%s: len: %i\n", ndev->name, data->length);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
prism54_debug_set_oid(काष्ठा net_device *ndev, काष्ठा iw_request_info *info,
		      काष्ठा iw_poपूर्णांक *data, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	काष्ठा islpci_mgmtframe *response;
	पूर्णांक ret = 0, response_op = PIMFOR_OP_ERROR;

	prपूर्णांकk("%s: set_oid 0x%08X\tlen: %d\n", ndev->name, priv->priv_oid,
	       data->length);

	अगर (islpci_get_state(priv) >= PRV_STATE_INIT) अणु
		ret =
		    islpci_mgt_transaction(priv->ndev, PIMFOR_OP_SET,
					   priv->priv_oid, extra, data->length,
					   &response);
		prपूर्णांकk("%s: ret: %i\n", ndev->name, ret);
		अगर (ret || !response
		    || response->header->operation == PIMFOR_OP_ERROR) अणु
			अगर (response) अणु
				islpci_mgt_release(response);
			पूर्ण
			prपूर्णांकk("%s: EIO\n", ndev->name);
			ret = -EIO;
		पूर्ण
		अगर (!ret) अणु
			response_op = response->header->operation;
			prपूर्णांकk("%s: response_op: %i\n", ndev->name,
			       response_op);
			islpci_mgt_release(response);
		पूर्ण
	पूर्ण

	वापस (ret ? ret : -EINPROGRESS);
पूर्ण

अटल पूर्णांक
prism54_set_spy(काष्ठा net_device *ndev,
		काष्ठा iw_request_info *info,
		जोड़ iwreq_data *uwrq, अक्षर *extra)
अणु
	islpci_निजी *priv = netdev_priv(ndev);
	u32 u;
	क्रमागत oid_num_t oid = OID_INL_CONFIG;

	करोwn_ग_लिखो(&priv->mib_sem);
	mgt_get(priv, OID_INL_CONFIG, &u);

	अगर ((uwrq->data.length == 0) && (priv->spy_data.spy_number > 0))
		/* disable spy */
		u &= ~INL_CONFIG_RXANNEX;
	अन्यथा अगर ((uwrq->data.length > 0) && (priv->spy_data.spy_number == 0))
		/* enable spy */
		u |= INL_CONFIG_RXANNEX;

	mgt_set(priv, OID_INL_CONFIG, &u);
	mgt_commit_list(priv, &oid, 1);
	up_ग_लिखो(&priv->mib_sem);

	वापस iw_handler_set_spy(ndev, info, uwrq, extra);
पूर्ण

अटल स्थिर iw_handler prism54_handler[] = अणु
	(iw_handler) prism54_commit,	/* SIOCSIWCOMMIT */
	(iw_handler) prism54_get_name,	/* SIOCGIWNAME */
	(iw_handler) शून्य,	/* SIOCSIWNWID */
	(iw_handler) शून्य,	/* SIOCGIWNWID */
	(iw_handler) prism54_set_freq,	/* SIOCSIWFREQ */
	(iw_handler) prism54_get_freq,	/* SIOCGIWFREQ */
	(iw_handler) prism54_set_mode,	/* SIOCSIWMODE */
	(iw_handler) prism54_get_mode,	/* SIOCGIWMODE */
	(iw_handler) prism54_set_sens,	/* SIOCSIWSENS */
	(iw_handler) prism54_get_sens,	/* SIOCGIWSENS */
	(iw_handler) शून्य,	/* SIOCSIWRANGE */
	(iw_handler) prism54_get_range,	/* SIOCGIWRANGE */
	(iw_handler) शून्य,	/* SIOCSIWPRIV */
	(iw_handler) शून्य,	/* SIOCGIWPRIV */
	(iw_handler) शून्य,	/* SIOCSIWSTATS */
	(iw_handler) शून्य,	/* SIOCGIWSTATS */
	prism54_set_spy,	/* SIOCSIWSPY */
	iw_handler_get_spy,	/* SIOCGIWSPY */
	iw_handler_set_thrspy,	/* SIOCSIWTHRSPY */
	iw_handler_get_thrspy,	/* SIOCGIWTHRSPY */
	(iw_handler) prism54_set_wap,	/* SIOCSIWAP */
	(iw_handler) prism54_get_wap,	/* SIOCGIWAP */
	(iw_handler) शून्य,	/* -- hole -- */
	(iw_handler) शून्य,	/* SIOCGIWAPLIST deprecated */
	(iw_handler) prism54_set_scan,	/* SIOCSIWSCAN */
	(iw_handler) prism54_get_scan,	/* SIOCGIWSCAN */
	(iw_handler) prism54_set_essid,	/* SIOCSIWESSID */
	(iw_handler) prism54_get_essid,	/* SIOCGIWESSID */
	(iw_handler) prism54_set_nick,	/* SIOCSIWNICKN */
	(iw_handler) prism54_get_nick,	/* SIOCGIWNICKN */
	(iw_handler) शून्य,	/* -- hole -- */
	(iw_handler) शून्य,	/* -- hole -- */
	(iw_handler) prism54_set_rate,	/* SIOCSIWRATE */
	(iw_handler) prism54_get_rate,	/* SIOCGIWRATE */
	(iw_handler) prism54_set_rts,	/* SIOCSIWRTS */
	(iw_handler) prism54_get_rts,	/* SIOCGIWRTS */
	(iw_handler) prism54_set_frag,	/* SIOCSIWFRAG */
	(iw_handler) prism54_get_frag,	/* SIOCGIWFRAG */
	(iw_handler) prism54_set_txघातer,	/* SIOCSIWTXPOW */
	(iw_handler) prism54_get_txघातer,	/* SIOCGIWTXPOW */
	(iw_handler) prism54_set_retry,	/* SIOCSIWRETRY */
	(iw_handler) prism54_get_retry,	/* SIOCGIWRETRY */
	(iw_handler) prism54_set_encode,	/* SIOCSIWENCODE */
	(iw_handler) prism54_get_encode,	/* SIOCGIWENCODE */
	(iw_handler) शून्य,	/* SIOCSIWPOWER */
	(iw_handler) शून्य,	/* SIOCGIWPOWER */
	शून्य,			/* -- hole -- */
	शून्य,			/* -- hole -- */
	(iw_handler) prism54_set_genie,	/* SIOCSIWGENIE */
	(iw_handler) prism54_get_genie,	/* SIOCGIWGENIE */
	(iw_handler) prism54_set_auth,	/* SIOCSIWAUTH */
	(iw_handler) prism54_get_auth,	/* SIOCGIWAUTH */
	(iw_handler) prism54_set_encodeext, /* SIOCSIWENCODEEXT */
	(iw_handler) prism54_get_encodeext, /* SIOCGIWENCODEEXT */
	शून्य,			/* SIOCSIWPMKSA */
पूर्ण;

/* The low order bit identअगरy a SET (0) or a GET (1) ioctl.  */

#घोषणा PRISM54_RESET		SIOCIWFIRSTPRIV
#घोषणा PRISM54_GET_POLICY	SIOCIWFIRSTPRIV+1
#घोषणा PRISM54_SET_POLICY	SIOCIWFIRSTPRIV+2
#घोषणा PRISM54_GET_MAC		SIOCIWFIRSTPRIV+3
#घोषणा PRISM54_ADD_MAC		SIOCIWFIRSTPRIV+4

#घोषणा PRISM54_DEL_MAC		SIOCIWFIRSTPRIV+6

#घोषणा PRISM54_KICK_MAC	SIOCIWFIRSTPRIV+8

#घोषणा PRISM54_KICK_ALL	SIOCIWFIRSTPRIV+10

#घोषणा PRISM54_GET_WPA		SIOCIWFIRSTPRIV+11
#घोषणा PRISM54_SET_WPA		SIOCIWFIRSTPRIV+12

#घोषणा PRISM54_DBG_OID		SIOCIWFIRSTPRIV+14
#घोषणा PRISM54_DBG_GET_OID	SIOCIWFIRSTPRIV+15
#घोषणा PRISM54_DBG_SET_OID	SIOCIWFIRSTPRIV+16

#घोषणा PRISM54_GET_OID		SIOCIWFIRSTPRIV+17
#घोषणा PRISM54_SET_OID_U32	SIOCIWFIRSTPRIV+18
#घोषणा	PRISM54_SET_OID_STR	SIOCIWFIRSTPRIV+20
#घोषणा	PRISM54_SET_OID_ADDR	SIOCIWFIRSTPRIV+22

#घोषणा PRISM54_GET_PRISMHDR	SIOCIWFIRSTPRIV+23
#घोषणा PRISM54_SET_PRISMHDR	SIOCIWFIRSTPRIV+24

#घोषणा IWPRIV_SET_U32(n,x)	अणु n, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "s_"x पूर्ण
#घोषणा IWPRIV_SET_SSID(n,x)	अणु n, IW_PRIV_TYPE_CHAR | IW_PRIV_SIZE_FIXED | 1, 0, "s_"x पूर्ण
#घोषणा IWPRIV_SET_ADDR(n,x)	अणु n, IW_PRIV_TYPE_ADDR | IW_PRIV_SIZE_FIXED | 1, 0, "s_"x पूर्ण
#घोषणा IWPRIV_GET(n,x)	अणु n, 0, IW_PRIV_TYPE_CHAR | IW_PRIV_SIZE_FIXED | PRIV_STR_SIZE, "g_"x पूर्ण

#घोषणा IWPRIV_U32(n,x)		IWPRIV_SET_U32(n,x), IWPRIV_GET(n,x)
#घोषणा IWPRIV_SSID(n,x)	IWPRIV_SET_SSID(n,x), IWPRIV_GET(n,x)
#घोषणा IWPRIV_ADDR(n,x)	IWPRIV_SET_ADDR(n,x), IWPRIV_GET(n,x)

/* Note : limited to 128 निजी ioctls (wireless tools 26) */

अटल स्थिर काष्ठा iw_priv_args prism54_निजी_args[] = अणु
/*अणु cmd, set_args, get_args, name पूर्ण */
	अणुPRISM54_RESET, 0, 0, "reset"पूर्ण,
	अणुPRISM54_GET_PRISMHDR, 0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	 "get_prismhdr"पूर्ण,
	अणुPRISM54_SET_PRISMHDR, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0,
	 "set_prismhdr"पूर्ण,
	अणुPRISM54_GET_POLICY, 0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	 "getPolicy"पूर्ण,
	अणुPRISM54_SET_POLICY, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0,
	 "setPolicy"पूर्ण,
	अणुPRISM54_GET_MAC, 0, IW_PRIV_TYPE_ADDR | 64, "getMac"पूर्ण,
	अणुPRISM54_ADD_MAC, IW_PRIV_TYPE_ADDR | IW_PRIV_SIZE_FIXED | 1, 0,
	 "addMac"पूर्ण,
	अणुPRISM54_DEL_MAC, IW_PRIV_TYPE_ADDR | IW_PRIV_SIZE_FIXED | 1, 0,
	 "delMac"पूर्ण,
	अणुPRISM54_KICK_MAC, IW_PRIV_TYPE_ADDR | IW_PRIV_SIZE_FIXED | 1, 0,
	 "kickMac"पूर्ण,
	अणुPRISM54_KICK_ALL, 0, 0, "kickAll"पूर्ण,
	अणुPRISM54_GET_WPA, 0, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1,
	 "get_wpa"पूर्ण,
	अणुPRISM54_SET_WPA, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0,
	 "set_wpa"पूर्ण,
	अणुPRISM54_DBG_OID, IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0,
	 "dbg_oid"पूर्ण,
	अणुPRISM54_DBG_GET_OID, 0, IW_PRIV_TYPE_BYTE | 256, "dbg_get_oid"पूर्ण,
	अणुPRISM54_DBG_SET_OID, IW_PRIV_TYPE_BYTE | 256, 0, "dbg_set_oid"पूर्ण,
	/* --- sub-ioctls handlers --- */
	अणुPRISM54_GET_OID,
	 0, IW_PRIV_TYPE_CHAR | IW_PRIV_SIZE_FIXED | PRIV_STR_SIZE, ""पूर्ण,
	अणुPRISM54_SET_OID_U32,
	 IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, ""पूर्ण,
	अणुPRISM54_SET_OID_STR,
	 IW_PRIV_TYPE_CHAR | IW_PRIV_SIZE_FIXED | 1, 0, ""पूर्ण,
	अणुPRISM54_SET_OID_ADDR,
	 IW_PRIV_TYPE_ADDR | IW_PRIV_SIZE_FIXED | 1, 0, ""पूर्ण,
	/* --- sub-ioctls definitions --- */
	IWPRIV_ADDR(GEN_OID_MACADDRESS, "addr"),
	IWPRIV_GET(GEN_OID_LINKSTATE, "linkstate"),
	IWPRIV_U32(DOT11_OID_BSSTYPE, "bsstype"),
	IWPRIV_ADDR(DOT11_OID_BSSID, "bssid"),
	IWPRIV_U32(DOT11_OID_STATE, "state"),
	IWPRIV_U32(DOT11_OID_AID, "aid"),

	IWPRIV_SSID(DOT11_OID_SSIDOVERRIDE, "ssidoverride"),

	IWPRIV_U32(DOT11_OID_MEDIUMLIMIT, "medlimit"),
	IWPRIV_U32(DOT11_OID_BEACONPERIOD, "beacon"),
	IWPRIV_U32(DOT11_OID_DTIMPERIOD, "dtimperiod"),

	IWPRIV_U32(DOT11_OID_AUTHENABLE, "authenable"),
	IWPRIV_U32(DOT11_OID_PRIVACYINVOKED, "privinvok"),
	IWPRIV_U32(DOT11_OID_EXUNENCRYPTED, "exunencrypt"),

	IWPRIV_U32(DOT11_OID_REKEYTHRESHOLD, "rekeythresh"),

	IWPRIV_U32(DOT11_OID_MAXTXLIFETIME, "maxtxlife"),
	IWPRIV_U32(DOT11_OID_MAXRXLIFETIME, "maxrxlife"),
	IWPRIV_U32(DOT11_OID_ALOFT_FIXEDRATE, "fixedrate"),
	IWPRIV_U32(DOT11_OID_MAXFRAMEBURST, "frameburst"),
	IWPRIV_U32(DOT11_OID_PSM, "psm"),

	IWPRIV_U32(DOT11_OID_BRIDGELOCAL, "bridge"),
	IWPRIV_U32(DOT11_OID_CLIENTS, "clients"),
	IWPRIV_U32(DOT11_OID_CLIENTSASSOCIATED, "clientassoc"),
	IWPRIV_U32(DOT11_OID_DOT1XENABLE, "dot1xenable"),
	IWPRIV_U32(DOT11_OID_ANTENNARX, "rxant"),
	IWPRIV_U32(DOT11_OID_ANTENNATX, "txant"),
	IWPRIV_U32(DOT11_OID_ANTENNADIVERSITY, "antdivers"),
	IWPRIV_U32(DOT11_OID_EDTHRESHOLD, "edthresh"),
	IWPRIV_U32(DOT11_OID_PREAMBLESETTINGS, "preamble"),
	IWPRIV_GET(DOT11_OID_RATES, "rates"),
	IWPRIV_U32(DOT11_OID_OUTPUTPOWER, ".11outpower"),
	IWPRIV_GET(DOT11_OID_SUPPORTEDRATES, "supprates"),
	IWPRIV_GET(DOT11_OID_SUPPORTEDFREQUENCIES, "suppfreq"),

	IWPRIV_U32(DOT11_OID_NOISEFLOOR, "noisefloor"),
	IWPRIV_GET(DOT11_OID_FREQUENCYACTIVITY, "freqactivity"),
	IWPRIV_U32(DOT11_OID_NONERPPROTECTION, "nonerpprotec"),
	IWPRIV_U32(DOT11_OID_PROखाताS, "profile"),
	IWPRIV_GET(DOT11_OID_EXTENDEDRATES, "extrates"),
	IWPRIV_U32(DOT11_OID_MLMEAUTOLEVEL, "mlmelevel"),

	IWPRIV_GET(DOT11_OID_BSSS, "bsss"),
	IWPRIV_GET(DOT11_OID_BSSLIST, "bsslist"),
	IWPRIV_U32(OID_INL_MODE, "mode"),
	IWPRIV_U32(OID_INL_CONFIG, "config"),
	IWPRIV_U32(OID_INL_DOT11D_CONFORMANCE, ".11dconform"),
	IWPRIV_GET(OID_INL_PHYCAPABILITIES, "phycapa"),
	IWPRIV_U32(OID_INL_OUTPUTPOWER, "outpower"),
पूर्ण;

अटल स्थिर iw_handler prism54_निजी_handler[] = अणु
	(iw_handler) prism54_reset,
	(iw_handler) prism54_get_policy,
	(iw_handler) prism54_set_policy,
	(iw_handler) prism54_get_mac,
	(iw_handler) prism54_add_mac,
	(iw_handler) शून्य,
	(iw_handler) prism54_del_mac,
	(iw_handler) शून्य,
	(iw_handler) prism54_kick_mac,
	(iw_handler) शून्य,
	(iw_handler) prism54_kick_all,
	(iw_handler) prism54_get_wpa,
	(iw_handler) prism54_set_wpa,
	(iw_handler) शून्य,
	(iw_handler) prism54_debug_oid,
	(iw_handler) prism54_debug_get_oid,
	(iw_handler) prism54_debug_set_oid,
	(iw_handler) prism54_get_oid,
	(iw_handler) prism54_set_u32,
	(iw_handler) शून्य,
	(iw_handler) prism54_set_raw,
	(iw_handler) शून्य,
	(iw_handler) prism54_set_raw,
	(iw_handler) prism54_get_prismhdr,
	(iw_handler) prism54_set_prismhdr,
पूर्ण;

स्थिर काष्ठा iw_handler_def prism54_handler_def = अणु
	.num_standard = ARRAY_SIZE(prism54_handler),
	.num_निजी = ARRAY_SIZE(prism54_निजी_handler),
	.num_निजी_args = ARRAY_SIZE(prism54_निजी_args),
	.standard = (iw_handler *) prism54_handler,
	.निजी = (iw_handler *) prism54_निजी_handler,
	.निजी_args = (काष्ठा iw_priv_args *) prism54_निजी_args,
	.get_wireless_stats = prism54_get_wireless_stats,
पूर्ण;
