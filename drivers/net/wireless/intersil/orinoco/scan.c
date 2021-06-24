<शैली गुरु>
/* Helpers क्रम managing scan queues
 *
 * See copyright notice in मुख्य.c
 */

#समावेश <linux/gfp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/ieee80211.h>
#समावेश <net/cfg80211.h>

#समावेश "hermes.h"
#समावेश "orinoco.h"
#समावेश "main.h"

#समावेश "scan.h"

#घोषणा ZERO_DBM_OFFSET 0x95
#घोषणा MAX_SIGNAL_LEVEL 0x8A
#घोषणा MIN_SIGNAL_LEVEL 0x2F

#घोषणा SIGNAL_TO_DBM(x)					\
	(clamp_t(s32, (x), MIN_SIGNAL_LEVEL, MAX_SIGNAL_LEVEL)	\
	 - ZERO_DBM_OFFSET)
#घोषणा SIGNAL_TO_MBM(x) (SIGNAL_TO_DBM(x) * 100)

अटल पूर्णांक symbol_build_supp_rates(u8 *buf, स्थिर __le16 *rates)
अणु
	पूर्णांक i;
	u8 rate;

	buf[0] = WLAN_EID_SUPP_RATES;
	क्रम (i = 0; i < 5; i++) अणु
		rate = le16_to_cpu(rates[i]);
		/* शून्य terminated */
		अगर (rate == 0x0)
			अवरोध;
		buf[i + 2] = rate;
	पूर्ण
	buf[1] = i;

	वापस i + 2;
पूर्ण

अटल पूर्णांक prism_build_supp_rates(u8 *buf, स्थिर u8 *rates)
अणु
	पूर्णांक i;

	buf[0] = WLAN_EID_SUPP_RATES;
	क्रम (i = 0; i < 8; i++) अणु
		/* शून्य terminated */
		अगर (rates[i] == 0x0)
			अवरोध;
		buf[i + 2] = rates[i];
	पूर्ण
	buf[1] = i;

	/* We might still have another 2 rates, which need to go in
	 * extended supported rates */
	अगर (i == 8 && rates[i] > 0) अणु
		buf[10] = WLAN_EID_EXT_SUPP_RATES;
		क्रम (; i < 10; i++) अणु
			/* शून्य terminated */
			अगर (rates[i] == 0x0)
				अवरोध;
			buf[i + 2] = rates[i];
		पूर्ण
		buf[11] = i - 8;
	पूर्ण

	वापस (i < 8) ? i + 2 : i + 4;
पूर्ण

अटल व्योम orinoco_add_hostscan_result(काष्ठा orinoco_निजी *priv,
					स्थिर जोड़ hermes_scan_info *bss)
अणु
	काष्ठा wiphy *wiphy = priv_to_wiphy(priv);
	काष्ठा ieee80211_channel *channel;
	काष्ठा cfg80211_bss *cbss;
	u8 *ie;
	u8 ie_buf[46];
	u64 बारtamp;
	s32 संकेत;
	u16 capability;
	u16 beacon_पूर्णांकerval;
	पूर्णांक ie_len;
	पूर्णांक freq;
	पूर्णांक len;

	len = le16_to_cpu(bss->a.essid_len);

	/* Reस्थिरruct SSID and bitrate IEs to pass up */
	ie_buf[0] = WLAN_EID_SSID;
	ie_buf[1] = len;
	स_नकल(&ie_buf[2], bss->a.essid, len);

	ie = ie_buf + len + 2;
	ie_len = ie_buf[1] + 2;
	चयन (priv->firmware_type) अणु
	हाल FIRMWARE_TYPE_SYMBOL:
		ie_len += symbol_build_supp_rates(ie, bss->s.rates);
		अवरोध;

	हाल FIRMWARE_TYPE_INTERSIL:
		ie_len += prism_build_supp_rates(ie, bss->p.rates);
		अवरोध;

	हाल FIRMWARE_TYPE_AGERE:
	शेष:
		अवरोध;
	पूर्ण

	freq = ieee80211_channel_to_frequency(
		le16_to_cpu(bss->a.channel), NL80211_BAND_2GHZ);
	channel = ieee80211_get_channel(wiphy, freq);
	अगर (!channel) अणु
		prपूर्णांकk(KERN_DEBUG "Invalid channel designation %04X(%04X)",
			bss->a.channel, freq);
		वापस;	/* Then ignore it क्रम now */
	पूर्ण
	बारtamp = 0;
	capability = le16_to_cpu(bss->a.capabilities);
	beacon_पूर्णांकerval = le16_to_cpu(bss->a.beacon_पूर्णांकerv);
	संकेत = SIGNAL_TO_MBM(le16_to_cpu(bss->a.level));

	cbss = cfg80211_inक्रमm_bss(wiphy, channel, CFG80211_BSS_FTYPE_UNKNOWN,
				   bss->a.bssid, बारtamp, capability,
				   beacon_पूर्णांकerval, ie_buf, ie_len, संकेत,
				   GFP_KERNEL);
	cfg80211_put_bss(wiphy, cbss);
पूर्ण

व्योम orinoco_add_extscan_result(काष्ठा orinoco_निजी *priv,
				काष्ठा agere_ext_scan_info *bss,
				माप_प्रकार len)
अणु
	काष्ठा wiphy *wiphy = priv_to_wiphy(priv);
	काष्ठा ieee80211_channel *channel;
	काष्ठा cfg80211_bss *cbss;
	स्थिर u8 *ie;
	u64 बारtamp;
	s32 संकेत;
	u16 capability;
	u16 beacon_पूर्णांकerval;
	माप_प्रकार ie_len;
	पूर्णांक chan, freq;

	ie_len = len - माप(*bss);
	ie = cfg80211_find_ie(WLAN_EID_DS_PARAMS, bss->data, ie_len);
	chan = ie ? ie[2] : 0;
	freq = ieee80211_channel_to_frequency(chan, NL80211_BAND_2GHZ);
	channel = ieee80211_get_channel(wiphy, freq);

	बारtamp = le64_to_cpu(bss->बारtamp);
	capability = le16_to_cpu(bss->capabilities);
	beacon_पूर्णांकerval = le16_to_cpu(bss->beacon_पूर्णांकerval);
	ie = bss->data;
	संकेत = SIGNAL_TO_MBM(bss->level);

	cbss = cfg80211_inक्रमm_bss(wiphy, channel, CFG80211_BSS_FTYPE_UNKNOWN,
				   bss->bssid, बारtamp, capability,
				   beacon_पूर्णांकerval, ie, ie_len, संकेत,
				   GFP_KERNEL);
	cfg80211_put_bss(wiphy, cbss);
पूर्ण

व्योम orinoco_add_hostscan_results(काष्ठा orinoco_निजी *priv,
				  अचिन्हित अक्षर *buf,
				  माप_प्रकार len)
अणु
	पूर्णांक offset;		/* In the scan data */
	माप_प्रकार atom_len;
	bool पात = false;

	चयन (priv->firmware_type) अणु
	हाल FIRMWARE_TYPE_AGERE:
		atom_len = माप(काष्ठा agere_scan_apinfo);
		offset = 0;
		अवरोध;

	हाल FIRMWARE_TYPE_SYMBOL:
		/* Lack of करोcumentation necessitates this hack.
		 * Dअगरferent firmwares have 68 or 76 byte दीर्घ atoms.
		 * We try modulo first.  If the length भागides by both,
		 * we check what would be the channel in the second
		 * frame क्रम a 68-byte atom.  76-byte atoms have 0 there.
		 * Valid channel cannot be 0.  */
		अगर (len % 76)
			atom_len = 68;
		अन्यथा अगर (len % 68)
			atom_len = 76;
		अन्यथा अगर (len >= 1292 && buf[68] == 0)
			atom_len = 76;
		अन्यथा
			atom_len = 68;
		offset = 0;
		अवरोध;

	हाल FIRMWARE_TYPE_INTERSIL:
		offset = 4;
		अगर (priv->has_hostscan) अणु
			atom_len = le16_to_cpup((__le16 *)buf);
			/* Sanity check क्रम atom_len */
			अगर (atom_len < माप(काष्ठा prism2_scan_apinfo)) अणु
				prपूर्णांकk(KERN_ERR "%s: Invalid atom_len in scan "
				       "data: %zu\n", priv->ndev->name,
				       atom_len);
				पात = true;
				जाओ scan_पात;
			पूर्ण
		पूर्ण अन्यथा
			atom_len = दुरत्व(काष्ठा prism2_scan_apinfo, atim);
		अवरोध;

	शेष:
		पात = true;
		जाओ scan_पात;
	पूर्ण

	/* Check that we got an whole number of atoms */
	अगर ((len - offset) % atom_len) अणु
		prपूर्णांकk(KERN_ERR "%s: Unexpected scan data length %zu, "
		       "atom_len %zu, offset %d\n", priv->ndev->name, len,
		       atom_len, offset);
		पात = true;
		जाओ scan_पात;
	पूर्ण

	/* Process the entries one by one */
	क्रम (; offset + atom_len <= len; offset += atom_len) अणु
		जोड़ hermes_scan_info *atom;

		atom = (जोड़ hermes_scan_info *) (buf + offset);

		orinoco_add_hostscan_result(priv, atom);
	पूर्ण

 scan_पात:
	अगर (priv->scan_request) अणु
		काष्ठा cfg80211_scan_info info = अणु
			.पातed = पात,
		पूर्ण;

		cfg80211_scan_करोne(priv->scan_request, &info);
		priv->scan_request = शून्य;
	पूर्ण
पूर्ण

व्योम orinoco_scan_करोne(काष्ठा orinoco_निजी *priv, bool पात)
अणु
	अगर (priv->scan_request) अणु
		काष्ठा cfg80211_scan_info info = अणु
			.पातed = पात,
		पूर्ण;

		cfg80211_scan_करोne(priv->scan_request, &info);
		priv->scan_request = शून्य;
	पूर्ण
पूर्ण
