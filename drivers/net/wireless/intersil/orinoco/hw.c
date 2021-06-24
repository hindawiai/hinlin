<शैली गुरु>
/* Encapsulate basic setting changes and retrieval on Hermes hardware
 *
 * See copyright notice in मुख्य.c
 */
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/ieee80211.h>
#समावेश <linux/wireless.h>
#समावेश <net/cfg80211.h>
#समावेश "hermes.h"
#समावेश "hermes_rid.h"
#समावेश "orinoco.h"

#समावेश "hw.h"

#घोषणा SYMBOL_MAX_VER_LEN	(14)

/* Symbol firmware has a bug allocating buffers larger than this */
#घोषणा TX_NICBUF_SIZE_BUG	1585

/********************************************************************/
/* Data tables                                                      */
/********************************************************************/

/* This tables gives the actual meanings of the bitrate IDs वापसed
 * by the firmware. */
अटल स्थिर काष्ठा अणु
	पूर्णांक bitrate; /* in 100s of kilobits */
	पूर्णांक स्वतःmatic;
	u16 agere_txratectrl;
	u16 पूर्णांकersil_txratectrl;
पूर्ण bitrate_table[] = अणु
	अणु110, 1,  3, 15पूर्ण, /* Entry 0 is the शेष */
	अणु10,  0,  1,  1पूर्ण,
	अणु10,  1,  1,  1पूर्ण,
	अणु20,  0,  2,  2पूर्ण,
	अणु20,  1,  6,  3पूर्ण,
	अणु55,  0,  4,  4पूर्ण,
	अणु55,  1,  7,  7पूर्ण,
	अणु110, 0,  5,  8पूर्ण,
पूर्ण;
#घोषणा BITRATE_TABLE_SIZE ARRAY_SIZE(bitrate_table)

/* Firmware version encoding */
काष्ठा comp_id अणु
	u16 id, variant, major, minor;
पूर्ण __packed;

अटल अंतरभूत क्रमागत fwtype determine_firmware_type(काष्ठा comp_id *nic_id)
अणु
	अगर (nic_id->id < 0x8000)
		वापस FIRMWARE_TYPE_AGERE;
	अन्यथा अगर (nic_id->id == 0x8000 && nic_id->major == 0)
		वापस FIRMWARE_TYPE_SYMBOL;
	अन्यथा
		वापस FIRMWARE_TYPE_INTERSIL;
पूर्ण

/* Set priv->firmware type, determine firmware properties
 * This function can be called beक्रमe we have रेजिस्टरred with netdev,
 * so all errors go out with dev_* rather than prपूर्णांकk
 *
 * If non-शून्य stores a firmware description in fw_name.
 * If non-शून्य stores a HW version in hw_ver
 *
 * These are output via generic cfg80211 ethtool support.
 */
पूर्णांक determine_fw_capabilities(काष्ठा orinoco_निजी *priv,
			      अक्षर *fw_name, माप_प्रकार fw_name_len,
			      u32 *hw_ver)
अणु
	काष्ठा device *dev = priv->dev;
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक err;
	काष्ठा comp_id nic_id, sta_id;
	अचिन्हित पूर्णांक firmver;
	अक्षर पंचांगp[SYMBOL_MAX_VER_LEN + 1] __attribute__((aligned(2)));

	/* Get the hardware version */
	err = HERMES_READ_RECORD_PR(hw, USER_BAP, HERMES_RID_NICID, &nic_id);
	अगर (err) अणु
		dev_err(dev, "Cannot read hardware identity: error %d\n",
			err);
		वापस err;
	पूर्ण

	le16_to_cpus(&nic_id.id);
	le16_to_cpus(&nic_id.variant);
	le16_to_cpus(&nic_id.major);
	le16_to_cpus(&nic_id.minor);
	dev_info(dev, "Hardware identity %04x:%04x:%04x:%04x\n",
		 nic_id.id, nic_id.variant, nic_id.major, nic_id.minor);

	अगर (hw_ver)
		*hw_ver = (((nic_id.id & 0xff) << 24) |
			   ((nic_id.variant & 0xff) << 16) |
			   ((nic_id.major & 0xff) << 8) |
			   (nic_id.minor & 0xff));

	priv->firmware_type = determine_firmware_type(&nic_id);

	/* Get the firmware version */
	err = HERMES_READ_RECORD_PR(hw, USER_BAP, HERMES_RID_STAID, &sta_id);
	अगर (err) अणु
		dev_err(dev, "Cannot read station identity: error %d\n",
			err);
		वापस err;
	पूर्ण

	le16_to_cpus(&sta_id.id);
	le16_to_cpus(&sta_id.variant);
	le16_to_cpus(&sta_id.major);
	le16_to_cpus(&sta_id.minor);
	dev_info(dev, "Station identity  %04x:%04x:%04x:%04x\n",
		 sta_id.id, sta_id.variant, sta_id.major, sta_id.minor);

	चयन (sta_id.id) अणु
	हाल 0x15:
		dev_err(dev, "Primary firmware is active\n");
		वापस -ENODEV;
	हाल 0x14b:
		dev_err(dev, "Tertiary firmware is active\n");
		वापस -ENODEV;
	हाल 0x1f:	/* Intersil, Agere, Symbol Spectrum24 */
	हाल 0x21:	/* Symbol Spectrum24 Trilogy */
		अवरोध;
	शेष:
		dev_notice(dev, "Unknown station ID, please report\n");
		अवरोध;
	पूर्ण

	/* Default capabilities */
	priv->has_sensitivity = 1;
	priv->has_mwo = 0;
	priv->has_preamble = 0;
	priv->has_port3 = 1;
	priv->has_ibss = 1;
	priv->has_wep = 0;
	priv->has_big_wep = 0;
	priv->has_alt_txcntl = 0;
	priv->has_ext_scan = 0;
	priv->has_wpa = 0;
	priv->करो_fw_करोwnload = 0;

	/* Determine capabilities from the firmware version */
	चयन (priv->firmware_type) अणु
	हाल FIRMWARE_TYPE_AGERE:
		/* Lucent Wavelan IEEE, Lucent Orinoco, Cabletron RoamAbout,
		   ELSA, Melco, HP, IBM, Dell 1150, Compaq 110/210 */
		अगर (fw_name)
			snम_लिखो(fw_name, fw_name_len, "Lucent/Agere %d.%02d",
				 sta_id.major, sta_id.minor);

		firmver = ((अचिन्हित दीर्घ)sta_id.major << 16) | sta_id.minor;

		priv->has_ibss = (firmver >= 0x60006);
		priv->has_wep = (firmver >= 0x40020);
		priv->has_big_wep = 1; /* FIXME: this is wrong - how करो we tell
					  Gold cards from the others? */
		priv->has_mwo = (firmver >= 0x60000);
		priv->has_pm = (firmver >= 0x40020); /* Don't work in 7.52 ? */
		priv->ibss_port = 1;
		priv->has_hostscan = (firmver >= 0x8000a);
		priv->करो_fw_करोwnload = 1;
		priv->broken_monitor = (firmver >= 0x80000);
		priv->has_alt_txcntl = (firmver >= 0x90000); /* All 9.x ? */
		priv->has_ext_scan = (firmver >= 0x90000); /* All 9.x ? */
		priv->has_wpa = (firmver >= 0x9002a);
		/* Tested with Agere firmware :
		 *	1.16 ; 4.08 ; 4.52 ; 6.04 ; 6.16 ; 7.28 => Jean II
		 * Tested CableTron firmware : 4.32 => Anton */
		अवरोध;
	हाल FIRMWARE_TYPE_SYMBOL:
		/* Symbol , 3Com AirConnect, Intel, Ericsson WLAN */
		/* Intel MAC : 00:02:B3:* */
		/* 3Com MAC : 00:50:DA:* */
		स_रखो(पंचांगp, 0, माप(पंचांगp));
		/* Get the Symbol firmware version */
		err = hw->ops->पढ़ो_ltv_pr(hw, USER_BAP,
					HERMES_RID_SECONDARYVERSION_SYMBOL,
					SYMBOL_MAX_VER_LEN, शून्य, &पंचांगp);
		अगर (err) अणु
			dev_warn(dev, "Error %d reading Symbol firmware info. "
				 "Wildly guessing capabilities...\n", err);
			firmver = 0;
			पंचांगp[0] = '\0';
		पूर्ण अन्यथा अणु
			/* The firmware revision is a string, the क्रमmat is
			 * something like : "V2.20-01".
			 * Quick and dirty parsing... - Jean II
			 */
			firmver = ((पंचांगp[1] - '0') << 16)
				| ((पंचांगp[3] - '0') << 12)
				| ((पंचांगp[4] - '0') << 8)
				| ((पंचांगp[6] - '0') << 4)
				| (पंचांगp[7] - '0');

			पंचांगp[SYMBOL_MAX_VER_LEN] = '\0';
		पूर्ण

		अगर (fw_name)
			snम_लिखो(fw_name, fw_name_len, "Symbol %s", पंचांगp);

		priv->has_ibss = (firmver >= 0x20000);
		priv->has_wep = (firmver >= 0x15012);
		priv->has_big_wep = (firmver >= 0x20000);
		priv->has_pm = (firmver >= 0x20000 && firmver < 0x22000) ||
			       (firmver >= 0x29000 && firmver < 0x30000) ||
			       firmver >= 0x31000;
		priv->has_preamble = (firmver >= 0x20000);
		priv->ibss_port = 4;

		/* Symbol firmware is found on various cards, but
		 * there has been no attempt to check firmware
		 * करोwnload on non-spectrum_cs based cards.
		 *
		 * Given that the Agere firmware करोwnload works
		 * dअगरferently, we should aव्योम करोing a firmware
		 * करोwnload with the Symbol algorithm on non-spectrum
		 * cards.
		 *
		 * For now we can identअगरy a spectrum_cs based card
		 * because it has a firmware reset function.
		 */
		priv->करो_fw_करोwnload = (priv->stop_fw != शून्य);

		priv->broken_disableport = (firmver == 0x25013) ||
				(firmver >= 0x30000 && firmver <= 0x31000);
		priv->has_hostscan = (firmver >= 0x31001) ||
				     (firmver >= 0x29057 && firmver < 0x30000);
		/* Tested with Intel firmware : 0x20015 => Jean II */
		/* Tested with 3Com firmware : 0x15012 & 0x22001 => Jean II */
		अवरोध;
	हाल FIRMWARE_TYPE_INTERSIL:
		/* D-Link, Linksys, Adtron, ZoomAir, and many others...
		 * Samsung, Compaq 100/200 and Proxim are slightly
		 * dअगरferent and less well tested */
		/* D-Link MAC : 00:40:05:* */
		/* Addtron MAC : 00:90:D1:* */
		अगर (fw_name)
			snम_लिखो(fw_name, fw_name_len, "Intersil %d.%d.%d",
				 sta_id.major, sta_id.minor, sta_id.variant);

		firmver = ((अचिन्हित दीर्घ)sta_id.major << 16) |
			((अचिन्हित दीर्घ)sta_id.minor << 8) | sta_id.variant;

		priv->has_ibss = (firmver >= 0x000700); /* FIXME */
		priv->has_big_wep = priv->has_wep = (firmver >= 0x000800);
		priv->has_pm = (firmver >= 0x000700);
		priv->has_hostscan = (firmver >= 0x010301);

		अगर (firmver >= 0x000800)
			priv->ibss_port = 0;
		अन्यथा अणु
			dev_notice(dev, "Intersil firmware earlier than v0.8.x"
				   " - several features not supported\n");
			priv->ibss_port = 1;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (fw_name)
		dev_info(dev, "Firmware determined as %s\n", fw_name);

#अगर_अघोषित CONFIG_HERMES_PRISM
	अगर (priv->firmware_type == FIRMWARE_TYPE_INTERSIL) अणु
		dev_err(dev, "Support for Prism chipset is not enabled\n");
		वापस -ENODEV;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

/* Read settings from EEPROM पूर्णांकo our निजी काष्ठाure.
 * MAC address माला_लो dropped पूर्णांकo callers buffer
 * Can be called beक्रमe netdev registration.
 */
पूर्णांक orinoco_hw_पढ़ो_card_settings(काष्ठा orinoco_निजी *priv, u8 *dev_addr)
अणु
	काष्ठा device *dev = priv->dev;
	काष्ठा hermes_idstring nickbuf;
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक len;
	पूर्णांक err;
	u16 reclen;

	/* Get the MAC address */
	err = hw->ops->पढ़ो_ltv_pr(hw, USER_BAP, HERMES_RID_CNFOWNMACADDR,
				ETH_ALEN, शून्य, dev_addr);
	अगर (err) अणु
		dev_warn(dev, "Failed to read MAC address!\n");
		जाओ out;
	पूर्ण

	dev_dbg(dev, "MAC address %pM\n", dev_addr);

	/* Get the station name */
	err = hw->ops->पढ़ो_ltv_pr(hw, USER_BAP, HERMES_RID_CNFOWNNAME,
				माप(nickbuf), &reclen, &nickbuf);
	अगर (err) अणु
		dev_err(dev, "failed to read station name\n");
		जाओ out;
	पूर्ण
	अगर (nickbuf.len)
		len = min(IW_ESSID_MAX_SIZE, (पूर्णांक)le16_to_cpu(nickbuf.len));
	अन्यथा
		len = min(IW_ESSID_MAX_SIZE, 2 * reclen);
	स_नकल(priv->nick, &nickbuf.val, len);
	priv->nick[len] = '\0';

	dev_dbg(dev, "Station name \"%s\"\n", priv->nick);

	/* Get allowed channels */
	err = hermes_पढ़ो_wordrec_pr(hw, USER_BAP, HERMES_RID_CHANNELLIST,
				  &priv->channel_mask);
	अगर (err) अणु
		dev_err(dev, "Failed to read channel list!\n");
		जाओ out;
	पूर्ण

	/* Get initial AP density */
	err = hermes_पढ़ो_wordrec_pr(hw, USER_BAP, HERMES_RID_CNFSYSTEMSCALE,
				  &priv->ap_density);
	अगर (err || priv->ap_density < 1 || priv->ap_density > 3)
		priv->has_sensitivity = 0;

	/* Get initial RTS threshold */
	err = hermes_पढ़ो_wordrec_pr(hw, USER_BAP, HERMES_RID_CNFRTSTHRESHOLD,
				  &priv->rts_thresh);
	अगर (err) अणु
		dev_err(dev, "Failed to read RTS threshold!\n");
		जाओ out;
	पूर्ण

	/* Get initial fragmentation settings */
	अगर (priv->has_mwo)
		err = hermes_पढ़ो_wordrec_pr(hw, USER_BAP,
					  HERMES_RID_CNFMWOROBUST_AGERE,
					  &priv->mwo_robust);
	अन्यथा
		err = hermes_पढ़ो_wordrec_pr(hw, USER_BAP,
					  HERMES_RID_CNFFRAGMENTATIONTHRESHOLD,
					  &priv->frag_thresh);
	अगर (err) अणु
		dev_err(dev, "Failed to read fragmentation settings!\n");
		जाओ out;
	पूर्ण

	/* Power management setup */
	अगर (priv->has_pm) अणु
		priv->pm_on = 0;
		priv->pm_mcast = 1;
		err = hermes_पढ़ो_wordrec_pr(hw, USER_BAP,
					  HERMES_RID_CNFMAXSLEEPDURATION,
					  &priv->pm_period);
		अगर (err) अणु
			dev_err(dev, "Failed to read power management "
				"period!\n");
			जाओ out;
		पूर्ण
		err = hermes_पढ़ो_wordrec_pr(hw, USER_BAP,
					  HERMES_RID_CNFPMHOLDOVERDURATION,
					  &priv->pm_समयout);
		अगर (err) अणु
			dev_err(dev, "Failed to read power management "
				"timeout!\n");
			जाओ out;
		पूर्ण
	पूर्ण

	/* Preamble setup */
	अगर (priv->has_preamble) अणु
		err = hermes_पढ़ो_wordrec_pr(hw, USER_BAP,
					  HERMES_RID_CNFPREAMBLE_SYMBOL,
					  &priv->preamble);
		अगर (err) अणु
			dev_err(dev, "Failed to read preamble setup\n");
			जाओ out;
		पूर्ण
	पूर्ण

	/* Retry settings */
	err = hermes_पढ़ो_wordrec_pr(hw, USER_BAP, HERMES_RID_SHORTRETRYLIMIT,
				  &priv->लघु_retry_limit);
	अगर (err) अणु
		dev_err(dev, "Failed to read short retry limit\n");
		जाओ out;
	पूर्ण

	err = hermes_पढ़ो_wordrec_pr(hw, USER_BAP, HERMES_RID_LONGRETRYLIMIT,
				  &priv->दीर्घ_retry_limit);
	अगर (err) अणु
		dev_err(dev, "Failed to read long retry limit\n");
		जाओ out;
	पूर्ण

	err = hermes_पढ़ो_wordrec_pr(hw, USER_BAP, HERMES_RID_MAXTRANSMITLIFETIME,
				  &priv->retry_lअगरeसमय);
	अगर (err) अणु
		dev_err(dev, "Failed to read max retry lifetime\n");
		जाओ out;
	पूर्ण

out:
	वापस err;
पूर्ण

/* Can be called beक्रमe netdev registration */
पूर्णांक orinoco_hw_allocate_fid(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा device *dev = priv->dev;
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक err;

	err = hw->ops->allocate(hw, priv->nicbuf_size, &priv->txfid);
	अगर (err == -EIO && priv->nicbuf_size > TX_NICBUF_SIZE_BUG) अणु
		/* Try workaround क्रम old Symbol firmware bug */
		priv->nicbuf_size = TX_NICBUF_SIZE_BUG;
		err = hw->ops->allocate(hw, priv->nicbuf_size, &priv->txfid);

		dev_warn(dev, "Firmware ALLOC bug detected "
			 "(old Symbol firmware?). Work around %s\n",
			 err ? "failed!" : "ok.");
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक orinoco_get_bitratemode(पूर्णांक bitrate, पूर्णांक स्वतःmatic)
अणु
	पूर्णांक ratemode = -1;
	पूर्णांक i;

	अगर ((bitrate != 10) && (bitrate != 20) &&
	    (bitrate != 55) && (bitrate != 110))
		वापस ratemode;

	क्रम (i = 0; i < BITRATE_TABLE_SIZE; i++) अणु
		अगर ((bitrate_table[i].bitrate == bitrate) &&
		    (bitrate_table[i].स्वतःmatic == स्वतःmatic)) अणु
			ratemode = i;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ratemode;
पूर्ण

व्योम orinoco_get_ratemode_cfg(पूर्णांक ratemode, पूर्णांक *bitrate, पूर्णांक *स्वतःmatic)
अणु
	BUG_ON((ratemode < 0) || (ratemode >= BITRATE_TABLE_SIZE));

	*bitrate = bitrate_table[ratemode].bitrate * 100000;
	*स्वतःmatic = bitrate_table[ratemode].स्वतःmatic;
पूर्ण

पूर्णांक orinoco_hw_program_rids(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा net_device *dev = priv->ndev;
	काष्ठा wireless_dev *wdev = netdev_priv(dev);
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक err;
	काष्ठा hermes_idstring idbuf;

	/* Set the MAC address */
	err = hw->ops->ग_लिखो_ltv(hw, USER_BAP, HERMES_RID_CNFOWNMACADDR,
				 HERMES_BYTES_TO_RECLEN(ETH_ALEN),
				 dev->dev_addr);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: Error %d setting MAC address\n",
		       dev->name, err);
		वापस err;
	पूर्ण

	/* Set up the link mode */
	err = hermes_ग_लिखो_wordrec(hw, USER_BAP, HERMES_RID_CNFPORTTYPE,
				   priv->port_type);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: Error %d setting port type\n",
		       dev->name, err);
		वापस err;
	पूर्ण
	/* Set the channel/frequency */
	अगर (priv->channel != 0 && priv->iw_mode != NL80211_IFTYPE_STATION) अणु
		err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
					   HERMES_RID_CNFOWNCHANNEL,
					   priv->channel);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "%s: Error %d setting channel %d\n",
			       dev->name, err, priv->channel);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (priv->has_ibss) अणु
		u16 createibss;

		अगर ((म_माप(priv->desired_essid) == 0) && (priv->createibss)) अणु
			prपूर्णांकk(KERN_WARNING "%s: This firmware requires an "
			       "ESSID in IBSS-Ad-Hoc mode.\n", dev->name);
			/* With wvlan_cs, in this हाल, we would crash.
			 * hopefully, this driver will behave better...
			 * Jean II */
			createibss = 0;
		पूर्ण अन्यथा अणु
			createibss = priv->createibss;
		पूर्ण

		err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
					   HERMES_RID_CNFCREATEIBSS,
					   createibss);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "%s: Error %d setting CREATEIBSS\n",
			       dev->name, err);
			वापस err;
		पूर्ण
	पूर्ण

	/* Set the desired BSSID */
	err = __orinoco_hw_set_wap(priv);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: Error %d setting AP address\n",
		       dev->name, err);
		वापस err;
	पूर्ण

	/* Set the desired ESSID */
	idbuf.len = cpu_to_le16(म_माप(priv->desired_essid));
	स_नकल(&idbuf.val, priv->desired_essid, माप(idbuf.val));
	/* WinXP wants partner to configure OWNSSID even in IBSS mode. (jimc) */
	err = hw->ops->ग_लिखो_ltv(hw, USER_BAP, HERMES_RID_CNFOWNSSID,
			HERMES_BYTES_TO_RECLEN(म_माप(priv->desired_essid) + 2),
			&idbuf);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: Error %d setting OWNSSID\n",
		       dev->name, err);
		वापस err;
	पूर्ण
	err = hw->ops->ग_लिखो_ltv(hw, USER_BAP, HERMES_RID_CNFDESIREDSSID,
			HERMES_BYTES_TO_RECLEN(म_माप(priv->desired_essid) + 2),
			&idbuf);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: Error %d setting DESIREDSSID\n",
		       dev->name, err);
		वापस err;
	पूर्ण

	/* Set the station name */
	idbuf.len = cpu_to_le16(म_माप(priv->nick));
	स_नकल(&idbuf.val, priv->nick, माप(idbuf.val));
	err = hw->ops->ग_लिखो_ltv(hw, USER_BAP, HERMES_RID_CNFOWNNAME,
				 HERMES_BYTES_TO_RECLEN(म_माप(priv->nick) + 2),
				 &idbuf);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: Error %d setting nickname\n",
		       dev->name, err);
		वापस err;
	पूर्ण

	/* Set AP density */
	अगर (priv->has_sensitivity) अणु
		err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
					   HERMES_RID_CNFSYSTEMSCALE,
					   priv->ap_density);
		अगर (err) अणु
			prपूर्णांकk(KERN_WARNING "%s: Error %d setting SYSTEMSCALE. "
			       "Disabling sensitivity control\n",
			       dev->name, err);

			priv->has_sensitivity = 0;
		पूर्ण
	पूर्ण

	/* Set RTS threshold */
	err = hermes_ग_लिखो_wordrec(hw, USER_BAP, HERMES_RID_CNFRTSTHRESHOLD,
				   priv->rts_thresh);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: Error %d setting RTS threshold\n",
		       dev->name, err);
		वापस err;
	पूर्ण

	/* Set fragmentation threshold or MWO robustness */
	अगर (priv->has_mwo)
		err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
					   HERMES_RID_CNFMWOROBUST_AGERE,
					   priv->mwo_robust);
	अन्यथा
		err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
					   HERMES_RID_CNFFRAGMENTATIONTHRESHOLD,
					   priv->frag_thresh);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: Error %d setting fragmentation\n",
		       dev->name, err);
		वापस err;
	पूर्ण

	/* Set bitrate */
	err = __orinoco_hw_set_bitrate(priv);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: Error %d setting bitrate\n",
		       dev->name, err);
		वापस err;
	पूर्ण

	/* Set घातer management */
	अगर (priv->has_pm) अणु
		err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
					   HERMES_RID_CNFPMENABLED,
					   priv->pm_on);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "%s: Error %d setting up PM\n",
			       dev->name, err);
			वापस err;
		पूर्ण

		err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
					   HERMES_RID_CNFMULTICASTRECEIVE,
					   priv->pm_mcast);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "%s: Error %d setting up PM\n",
			       dev->name, err);
			वापस err;
		पूर्ण
		err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
					   HERMES_RID_CNFMAXSLEEPDURATION,
					   priv->pm_period);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "%s: Error %d setting up PM\n",
			       dev->name, err);
			वापस err;
		पूर्ण
		err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
					   HERMES_RID_CNFPMHOLDOVERDURATION,
					   priv->pm_समयout);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "%s: Error %d setting up PM\n",
			       dev->name, err);
			वापस err;
		पूर्ण
	पूर्ण

	/* Set preamble - only क्रम Symbol so far... */
	अगर (priv->has_preamble) अणु
		err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
					   HERMES_RID_CNFPREAMBLE_SYMBOL,
					   priv->preamble);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "%s: Error %d setting preamble\n",
			       dev->name, err);
			वापस err;
		पूर्ण
	पूर्ण

	/* Set up encryption */
	अगर (priv->has_wep || priv->has_wpa) अणु
		err = __orinoco_hw_setup_enc(priv);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "%s: Error %d activating encryption\n",
			       dev->name, err);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (priv->iw_mode == NL80211_IFTYPE_MONITOR) अणु
		/* Enable monitor mode */
		dev->type = ARPHRD_IEEE80211;
		err = hw->ops->cmd_रुको(hw, HERMES_CMD_TEST |
					    HERMES_TEST_MONITOR, 0, शून्य);
	पूर्ण अन्यथा अणु
		/* Disable monitor mode */
		dev->type = ARPHRD_ETHER;
		err = hw->ops->cmd_रुको(hw, HERMES_CMD_TEST |
					    HERMES_TEST_STOP, 0, शून्य);
	पूर्ण
	अगर (err)
		वापस err;

	/* Reset promiscuity / multicast*/
	priv->promiscuous = 0;
	priv->mc_count = 0;

	/* Record mode change */
	wdev->अगरtype = priv->iw_mode;

	वापस 0;
पूर्ण

/* Get tsc from the firmware */
पूर्णांक orinoco_hw_get_tkip_iv(काष्ठा orinoco_निजी *priv, पूर्णांक key, u8 *tsc)
अणु
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक err = 0;
	u8 tsc_arr[4][ORINOCO_SEQ_LEN];

	अगर ((key < 0) || (key >= 4))
		वापस -EINVAL;

	err = hw->ops->पढ़ो_ltv(hw, USER_BAP, HERMES_RID_CURRENT_TKIP_IV,
				माप(tsc_arr), शून्य, &tsc_arr);
	अगर (!err)
		स_नकल(tsc, &tsc_arr[key][0], माप(tsc_arr[0]));

	वापस err;
पूर्ण

पूर्णांक __orinoco_hw_set_bitrate(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक ratemode = priv->bitratemode;
	पूर्णांक err = 0;

	अगर (ratemode >= BITRATE_TABLE_SIZE) अणु
		prपूर्णांकk(KERN_ERR "%s: BUG: Invalid bitrate mode %d\n",
		       priv->ndev->name, ratemode);
		वापस -EINVAL;
	पूर्ण

	चयन (priv->firmware_type) अणु
	हाल FIRMWARE_TYPE_AGERE:
		err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
				HERMES_RID_CNFTXRATECONTROL,
				bitrate_table[ratemode].agere_txratectrl);
		अवरोध;
	हाल FIRMWARE_TYPE_INTERSIL:
	हाल FIRMWARE_TYPE_SYMBOL:
		err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
				HERMES_RID_CNFTXRATECONTROL,
				bitrate_table[ratemode].पूर्णांकersil_txratectrl);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक orinoco_hw_get_act_bitrate(काष्ठा orinoco_निजी *priv, पूर्णांक *bitrate)
अणु
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक i;
	पूर्णांक err = 0;
	u16 val;

	err = hermes_पढ़ो_wordrec(hw, USER_BAP,
				  HERMES_RID_CURRENTTXRATE, &val);
	अगर (err)
		वापस err;

	चयन (priv->firmware_type) अणु
	हाल FIRMWARE_TYPE_AGERE: /* Lucent style rate */
		/* Note : in Lucent firmware, the वापस value of
		 * HERMES_RID_CURRENTTXRATE is the bitrate in Mb/s,
		 * and thereक्रमe is totally dअगरferent from the
		 * encoding of HERMES_RID_CNFTXRATECONTROL.
		 * Don't क्रमget that 6Mb/s is really 5.5Mb/s */
		अगर (val == 6)
			*bitrate = 5500000;
		अन्यथा
			*bitrate = val * 1000000;
		अवरोध;
	हाल FIRMWARE_TYPE_INTERSIL: /* Intersil style rate */
	हाल FIRMWARE_TYPE_SYMBOL: /* Symbol style rate */
		क्रम (i = 0; i < BITRATE_TABLE_SIZE; i++)
			अगर (bitrate_table[i].पूर्णांकersil_txratectrl == val) अणु
				*bitrate = bitrate_table[i].bitrate * 100000;
				अवरोध;
			पूर्ण

		अगर (i >= BITRATE_TABLE_SIZE) अणु
			prपूर्णांकk(KERN_INFO "%s: Unable to determine current bitrate (0x%04hx)\n",
			       priv->ndev->name, val);
			err = -EIO;
		पूर्ण

		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस err;
पूर्ण

/* Set fixed AP address */
पूर्णांक __orinoco_hw_set_wap(काष्ठा orinoco_निजी *priv)
अणु
	पूर्णांक roaming_flag;
	पूर्णांक err = 0;
	काष्ठा hermes *hw = &priv->hw;

	चयन (priv->firmware_type) अणु
	हाल FIRMWARE_TYPE_AGERE:
		/* not supported */
		अवरोध;
	हाल FIRMWARE_TYPE_INTERSIL:
		अगर (priv->bssid_fixed)
			roaming_flag = 2;
		अन्यथा
			roaming_flag = 1;

		err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
					   HERMES_RID_CNFROAMINGMODE,
					   roaming_flag);
		अवरोध;
	हाल FIRMWARE_TYPE_SYMBOL:
		err = HERMES_WRITE_RECORD(hw, USER_BAP,
					  HERMES_RID_CNFMANDATORYBSSID_SYMBOL,
					  &priv->desired_bssid);
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

/* Change the WEP keys and/or the current keys.  Can be called
 * either from __orinoco_hw_setup_enc() or directly from
 * orinoco_ioctl_setiwencode().  In the later हाल the association
 * with the AP is not broken (अगर the firmware can handle it),
 * which is needed क्रम 802.1x implementations. */
पूर्णांक __orinoco_hw_setup_wepkeys(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक err = 0;
	पूर्णांक i;

	चयन (priv->firmware_type) अणु
	हाल FIRMWARE_TYPE_AGERE:
	अणु
		काष्ठा orinoco_key keys[ORINOCO_MAX_KEYS];

		स_रखो(&keys, 0, माप(keys));
		क्रम (i = 0; i < ORINOCO_MAX_KEYS; i++) अणु
			पूर्णांक len = min(priv->keys[i].key_len,
				      ORINOCO_MAX_KEY_SIZE);
			स_नकल(&keys[i].data, priv->keys[i].key, len);
			अगर (len > SMALL_KEY_SIZE)
				keys[i].len = cpu_to_le16(LARGE_KEY_SIZE);
			अन्यथा अगर (len > 0)
				keys[i].len = cpu_to_le16(SMALL_KEY_SIZE);
			अन्यथा
				keys[i].len = cpu_to_le16(0);
		पूर्ण

		err = HERMES_WRITE_RECORD(hw, USER_BAP,
					  HERMES_RID_CNFWEPKEYS_AGERE,
					  &keys);
		अगर (err)
			वापस err;
		err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
					   HERMES_RID_CNFTXKEY_AGERE,
					   priv->tx_key);
		अगर (err)
			वापस err;
		अवरोध;
	पूर्ण
	हाल FIRMWARE_TYPE_INTERSIL:
	हाल FIRMWARE_TYPE_SYMBOL:
		अणु
			पूर्णांक keylen;

			/* Force unअगरorm key length to work around
			 * firmware bugs */
			keylen = priv->keys[priv->tx_key].key_len;

			अगर (keylen > LARGE_KEY_SIZE) अणु
				prपूर्णांकk(KERN_ERR "%s: BUG: Key %d has oversize length %d.\n",
				       priv->ndev->name, priv->tx_key, keylen);
				वापस -E2BIG;
			पूर्ण अन्यथा अगर (keylen > SMALL_KEY_SIZE)
				keylen = LARGE_KEY_SIZE;
			अन्यथा अगर (keylen > 0)
				keylen = SMALL_KEY_SIZE;
			अन्यथा
				keylen = 0;

			/* Write all 4 keys */
			क्रम (i = 0; i < ORINOCO_MAX_KEYS; i++) अणु
				u8 key[LARGE_KEY_SIZE] = अणु 0 पूर्ण;

				स_नकल(key, priv->keys[i].key,
				       priv->keys[i].key_len);

				err = hw->ops->ग_लिखो_ltv(hw, USER_BAP,
						HERMES_RID_CNFDEFAULTKEY0 + i,
						HERMES_BYTES_TO_RECLEN(keylen),
						key);
				अगर (err)
					वापस err;
			पूर्ण

			/* Write the index of the key used in transmission */
			err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
						HERMES_RID_CNFWEPDEFAULTKEYID,
						priv->tx_key);
			अगर (err)
				वापस err;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __orinoco_hw_setup_enc(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक err = 0;
	पूर्णांक master_wep_flag;
	पूर्णांक auth_flag;
	पूर्णांक enc_flag;

	/* Setup WEP keys */
	अगर (priv->encode_alg == ORINOCO_ALG_WEP)
		__orinoco_hw_setup_wepkeys(priv);

	अगर (priv->wep_restrict)
		auth_flag = HERMES_AUTH_SHARED_KEY;
	अन्यथा
		auth_flag = HERMES_AUTH_OPEN;

	अगर (priv->wpa_enabled)
		enc_flag = 2;
	अन्यथा अगर (priv->encode_alg == ORINOCO_ALG_WEP)
		enc_flag = 1;
	अन्यथा
		enc_flag = 0;

	चयन (priv->firmware_type) अणु
	हाल FIRMWARE_TYPE_AGERE: /* Agere style WEP */
		अगर (priv->encode_alg == ORINOCO_ALG_WEP) अणु
			/* Enable the shared-key authentication. */
			err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
					HERMES_RID_CNFAUTHENTICATION_AGERE,
					auth_flag);
		पूर्ण
		err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
					   HERMES_RID_CNFWEPENABLED_AGERE,
					   enc_flag);
		अगर (err)
			वापस err;

		अगर (priv->has_wpa) अणु
			/* Set WPA key management */
			err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
				  HERMES_RID_CNFSETWPAAUTHMGMTSUITE_AGERE,
				  priv->key_mgmt);
			अगर (err)
				वापस err;
		पूर्ण

		अवरोध;

	हाल FIRMWARE_TYPE_INTERSIL: /* Intersil style WEP */
	हाल FIRMWARE_TYPE_SYMBOL: /* Symbol style WEP */
		अगर (priv->encode_alg == ORINOCO_ALG_WEP) अणु
			अगर (priv->wep_restrict ||
			    (priv->firmware_type == FIRMWARE_TYPE_SYMBOL))
				master_wep_flag = HERMES_WEP_PRIVACY_INVOKED |
						  HERMES_WEP_EXCL_UNENCRYPTED;
			अन्यथा
				master_wep_flag = HERMES_WEP_PRIVACY_INVOKED;

			err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
						   HERMES_RID_CNFAUTHENTICATION,
						   auth_flag);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा
			master_wep_flag = 0;

		अगर (priv->iw_mode == NL80211_IFTYPE_MONITOR)
			master_wep_flag |= HERMES_WEP_HOST_DECRYPT;

		/* Master WEP setting : on/off */
		err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
					   HERMES_RID_CNFWEPFLAGS_INTERSIL,
					   master_wep_flag);
		अगर (err)
			वापस err;

		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* key must be 32 bytes, including the tx and rx MIC keys.
 * rsc must be शून्य or up to 8 bytes
 * tsc must be शून्य or up to 8 bytes
 */
पूर्णांक __orinoco_hw_set_tkip_key(काष्ठा orinoco_निजी *priv, पूर्णांक key_idx,
			      पूर्णांक set_tx, स्थिर u8 *key, स्थिर u8 *rsc,
			      माप_प्रकार rsc_len, स्थिर u8 *tsc, माप_प्रकार tsc_len)
अणु
	काष्ठा अणु
		__le16 idx;
		u8 rsc[ORINOCO_SEQ_LEN];
		u8 key[TKIP_KEYLEN];
		u8 tx_mic[MIC_KEYLEN];
		u8 rx_mic[MIC_KEYLEN];
		u8 tsc[ORINOCO_SEQ_LEN];
	पूर्ण __packed buf;
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक ret;
	पूर्णांक err;
	पूर्णांक k;
	u16 xmitting;

	key_idx &= 0x3;

	अगर (set_tx)
		key_idx |= 0x8000;

	buf.idx = cpu_to_le16(key_idx);
	स_नकल(buf.key, key,
	       माप(buf.key) + माप(buf.tx_mic) + माप(buf.rx_mic));

	अगर (rsc_len > माप(buf.rsc))
		rsc_len = माप(buf.rsc);

	अगर (tsc_len > माप(buf.tsc))
		tsc_len = माप(buf.tsc);

	स_रखो(buf.rsc, 0, माप(buf.rsc));
	स_रखो(buf.tsc, 0, माप(buf.tsc));

	अगर (rsc != शून्य)
		स_नकल(buf.rsc, rsc, rsc_len);

	अगर (tsc != शून्य)
		स_नकल(buf.tsc, tsc, tsc_len);
	अन्यथा
		buf.tsc[4] = 0x10;

	/* Wait up to 100ms क्रम tx queue to empty */
	क्रम (k = 100; k > 0; k--) अणु
		udelay(1000);
		ret = hermes_पढ़ो_wordrec(hw, USER_BAP, HERMES_RID_TXQUEUEEMPTY,
					  &xmitting);
		अगर (ret || !xmitting)
			अवरोध;
	पूर्ण

	अगर (k == 0)
		ret = -ETIMEDOUT;

	err = HERMES_WRITE_RECORD(hw, USER_BAP,
				  HERMES_RID_CNFADDDEFAULTTKIPKEY_AGERE,
				  &buf);

	वापस ret ? ret : err;
पूर्ण

पूर्णांक orinoco_clear_tkip_key(काष्ठा orinoco_निजी *priv, पूर्णांक key_idx)
अणु
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक err;

	err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
				   HERMES_RID_CNFREMDEFAULTTKIPKEY_AGERE,
				   key_idx);
	अगर (err)
		prपूर्णांकk(KERN_WARNING "%s: Error %d clearing TKIP key %d\n",
		       priv->ndev->name, err, key_idx);
	वापस err;
पूर्ण

पूर्णांक __orinoco_hw_set_multicast_list(काष्ठा orinoco_निजी *priv,
				    काष्ठा net_device *dev,
				    पूर्णांक mc_count, पूर्णांक promisc)
अणु
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक err = 0;

	अगर (promisc != priv->promiscuous) अणु
		err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
					   HERMES_RID_CNFPROMISCUOUSMODE,
					   promisc);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "%s: Error %d setting PROMISCUOUSMODE to 1.\n",
			       priv->ndev->name, err);
		पूर्ण अन्यथा
			priv->promiscuous = promisc;
	पूर्ण

	/* If we're not in promiscuous mode, then we need to set the
	 * group address अगर either we want to multicast, or अगर we were
	 * multicasting and want to stop */
	अगर (!promisc && (mc_count || priv->mc_count)) अणु
		काष्ठा netdev_hw_addr *ha;
		काष्ठा hermes_multicast mclist;
		पूर्णांक i = 0;

		netdev_क्रम_each_mc_addr(ha, dev) अणु
			अगर (i == mc_count)
				अवरोध;
			स_नकल(mclist.addr[i++], ha->addr, ETH_ALEN);
		पूर्ण

		err = hw->ops->ग_लिखो_ltv(hw, USER_BAP,
				   HERMES_RID_CNFGROUPADDRESSES,
				   HERMES_BYTES_TO_RECLEN(mc_count * ETH_ALEN),
				   &mclist);
		अगर (err)
			prपूर्णांकk(KERN_ERR "%s: Error %d setting multicast list.\n",
			       priv->ndev->name, err);
		अन्यथा
			priv->mc_count = mc_count;
	पूर्ण
	वापस err;
पूर्ण

/* Return : < 0 -> error code ; >= 0 -> length */
पूर्णांक orinoco_hw_get_essid(काष्ठा orinoco_निजी *priv, पूर्णांक *active,
			 अक्षर buf[IW_ESSID_MAX_SIZE + 1])
अणु
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक err = 0;
	काष्ठा hermes_idstring essidbuf;
	अक्षर *p = (अक्षर *)(&essidbuf.val);
	पूर्णांक len;
	अचिन्हित दीर्घ flags;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	अगर (म_माप(priv->desired_essid) > 0) अणु
		/* We पढ़ो the desired SSID from the hardware rather
		   than from priv->desired_essid, just in हाल the
		   firmware is allowed to change it on us. I'm not
		   sure about this */
		/* My guess is that the OWNSSID should always be whatever
		 * we set to the card, whereas CURRENT_SSID is the one that
		 * may change... - Jean II */
		u16 rid;

		*active = 1;

		rid = (priv->port_type == 3) ? HERMES_RID_CNFOWNSSID :
			HERMES_RID_CNFDESIREDSSID;

		err = hw->ops->पढ़ो_ltv(hw, USER_BAP, rid, माप(essidbuf),
					शून्य, &essidbuf);
		अगर (err)
			जाओ fail_unlock;
	पूर्ण अन्यथा अणु
		*active = 0;

		err = hw->ops->पढ़ो_ltv(hw, USER_BAP, HERMES_RID_CURRENTSSID,
					माप(essidbuf), शून्य, &essidbuf);
		अगर (err)
			जाओ fail_unlock;
	पूर्ण

	len = le16_to_cpu(essidbuf.len);
	BUG_ON(len > IW_ESSID_MAX_SIZE);

	स_रखो(buf, 0, IW_ESSID_MAX_SIZE);
	स_नकल(buf, p, len);
	err = len;

 fail_unlock:
	orinoco_unlock(priv, &flags);

	वापस err;
पूर्ण

पूर्णांक orinoco_hw_get_freq(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक err = 0;
	u16 channel;
	पूर्णांक freq = 0;
	अचिन्हित दीर्घ flags;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	err = hermes_पढ़ो_wordrec(hw, USER_BAP, HERMES_RID_CURRENTCHANNEL,
				  &channel);
	अगर (err)
		जाओ out;

	/* Intersil firmware 1.3.5 वापसs 0 when the पूर्णांकerface is करोwn */
	अगर (channel == 0) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण

	अगर ((channel < 1) || (channel > NUM_CHANNELS)) अणु
		prपूर्णांकk(KERN_WARNING "%s: Channel out of range (%d)!\n",
		       priv->ndev->name, channel);
		err = -EBUSY;
		जाओ out;

	पूर्ण
	freq = ieee80211_channel_to_frequency(channel, NL80211_BAND_2GHZ);

 out:
	orinoco_unlock(priv, &flags);

	अगर (err > 0)
		err = -EBUSY;
	वापस err ? err : freq;
पूर्ण

पूर्णांक orinoco_hw_get_bitratelist(काष्ठा orinoco_निजी *priv,
			       पूर्णांक *numrates, s32 *rates, पूर्णांक max)
अणु
	काष्ठा hermes *hw = &priv->hw;
	काष्ठा hermes_idstring list;
	अचिन्हित अक्षर *p = (अचिन्हित अक्षर *)&list.val;
	पूर्णांक err = 0;
	पूर्णांक num;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	err = hw->ops->पढ़ो_ltv(hw, USER_BAP, HERMES_RID_SUPPORTEDDATARATES,
				माप(list), शून्य, &list);
	orinoco_unlock(priv, &flags);

	अगर (err)
		वापस err;

	num = le16_to_cpu(list.len);
	*numrates = num;
	num = min(num, max);

	क्रम (i = 0; i < num; i++)
		rates[i] = (p[i] & 0x7f) * 500000; /* convert to bps */

	वापस 0;
पूर्ण

पूर्णांक orinoco_hw_trigger_scan(काष्ठा orinoco_निजी *priv,
			    स्थिर काष्ठा cfg80211_ssid *ssid)
अणु
	काष्ठा net_device *dev = priv->ndev;
	काष्ठा hermes *hw = &priv->hw;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	अगर (orinoco_lock(priv, &flags) != 0)
		वापस -EBUSY;

	/* Scanning with port 0 disabled would fail */
	अगर (!netअगर_running(dev)) अणु
		err = -ENETDOWN;
		जाओ out;
	पूर्ण

	/* In monitor mode, the scan results are always empty.
	 * Probe responses are passed to the driver as received
	 * frames and could be processed in software. */
	अगर (priv->iw_mode == NL80211_IFTYPE_MONITOR) अणु
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (priv->has_hostscan) अणु
		चयन (priv->firmware_type) अणु
		हाल FIRMWARE_TYPE_SYMBOL:
			err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
						HERMES_RID_CNFHOSTSCAN_SYMBOL,
						HERMES_HOSTSCAN_SYMBOL_ONCE |
						HERMES_HOSTSCAN_SYMBOL_BCAST);
			अवरोध;
		हाल FIRMWARE_TYPE_INTERSIL: अणु
			__le16 req[3];

			req[0] = cpu_to_le16(0x3fff);	/* All channels */
			req[1] = cpu_to_le16(0x0001);	/* rate 1 Mbps */
			req[2] = 0;			/* Any ESSID */
			err = HERMES_WRITE_RECORD(hw, USER_BAP,
						  HERMES_RID_CNFHOSTSCAN, &req);
			अवरोध;
		पूर्ण
		हाल FIRMWARE_TYPE_AGERE:
			अगर (ssid->ssid_len > 0) अणु
				काष्ठा hermes_idstring idbuf;
				माप_प्रकार len = ssid->ssid_len;

				idbuf.len = cpu_to_le16(len);
				स_नकल(idbuf.val, ssid->ssid, len);

				err = hw->ops->ग_लिखो_ltv(hw, USER_BAP,
					       HERMES_RID_CNFSCANSSID_AGERE,
					       HERMES_BYTES_TO_RECLEN(len + 2),
					       &idbuf);
			पूर्ण अन्यथा
				err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
						   HERMES_RID_CNFSCANSSID_AGERE,
						   0);	/* Any ESSID */
			अगर (err)
				अवरोध;

			अगर (priv->has_ext_scan) अणु
				err = hermes_ग_लिखो_wordrec(hw, USER_BAP,
						HERMES_RID_CNFSCANCHANNELS2GHZ,
						0x7FFF);
				अगर (err)
					जाओ out;

				err = hermes_inquire(hw,
						     HERMES_INQ_CHANNELINFO);
			पूर्ण अन्यथा
				err = hermes_inquire(hw, HERMES_INQ_SCAN);

			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		err = hermes_inquire(hw, HERMES_INQ_SCAN);

 out:
	orinoco_unlock(priv, &flags);

	वापस err;
पूर्ण

/* Disassociate from node with BSSID addr */
पूर्णांक orinoco_hw_disassociate(काष्ठा orinoco_निजी *priv,
			    u8 *addr, u16 reason_code)
अणु
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक err;

	काष्ठा अणु
		u8 addr[ETH_ALEN];
		__le16 reason_code;
	पूर्ण __packed buf;

	/* Currently only supported by WPA enabled Agere fw */
	अगर (!priv->has_wpa)
		वापस -EOPNOTSUPP;

	स_नकल(buf.addr, addr, ETH_ALEN);
	buf.reason_code = cpu_to_le16(reason_code);
	err = HERMES_WRITE_RECORD(hw, USER_BAP,
				  HERMES_RID_CNFDISASSOCIATE,
				  &buf);
	वापस err;
पूर्ण

पूर्णांक orinoco_hw_get_current_bssid(काष्ठा orinoco_निजी *priv,
				 u8 *addr)
अणु
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक err;

	err = hw->ops->पढ़ो_ltv(hw, USER_BAP, HERMES_RID_CURRENTBSSID,
				ETH_ALEN, शून्य, addr);

	वापस err;
पूर्ण
