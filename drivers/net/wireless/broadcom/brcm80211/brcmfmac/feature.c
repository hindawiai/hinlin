<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014 Broadcom Corporation
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/module.h>

#समावेश <brcm_hw_ids.h>
#समावेश <brcmu_wअगरi.h>
#समावेश "core.h"
#समावेश "bus.h"
#समावेश "debug.h"
#समावेश "fwil.h"
#समावेश "fwil_types.h"
#समावेश "feature.h"
#समावेश "common.h"

#घोषणा BRCMF_FW_UNSUPPORTED	23

/*
 * expand feature list to array of feature strings.
 */
#घोषणा BRCMF_FEAT_DEF(_f) \
	#_f,
अटल स्थिर अक्षर *brcmf_feat_names[] = अणु
	BRCMF_FEAT_LIST
पूर्ण;
#अघोषित BRCMF_FEAT_DEF

काष्ठा brcmf_feat_fwcap अणु
	क्रमागत brcmf_feat_id feature;
	स्थिर अक्षर * स्थिर fwcap_id;
पूर्ण;

अटल स्थिर काष्ठा brcmf_feat_fwcap brcmf_fwcap_map[] = अणु
	अणु BRCMF_FEAT_MBSS, "mbss" पूर्ण,
	अणु BRCMF_FEAT_MCHAN, "mchan" पूर्ण,
	अणु BRCMF_FEAT_P2P, "p2p" पूर्ण,
	अणु BRCMF_FEAT_MONITOR, "monitor" पूर्ण,
	अणु BRCMF_FEAT_MONITOR_FLAG, "rtap" पूर्ण,
	अणु BRCMF_FEAT_MONITOR_FMT_RADIOTAP, "rtap" पूर्ण,
	अणु BRCMF_FEAT_DOT11H, "802.11h" पूर्ण,
	अणु BRCMF_FEAT_SAE, "sae" पूर्ण,
	अणु BRCMF_FEAT_FWAUTH, "idauth" पूर्ण,
पूर्ण;

#अगर_घोषित DEBUG
/*
 * expand quirk list to array of quirk strings.
 */
#घोषणा BRCMF_QUIRK_DEF(_q) \
	#_q,
अटल स्थिर अक्षर * स्थिर brcmf_quirk_names[] = अणु
	BRCMF_QUIRK_LIST
पूर्ण;
#अघोषित BRCMF_QUIRK_DEF

/**
 * brcmf_feat_debugfs_पढ़ो() - expose feature info to debugfs.
 *
 * @seq: sequence क्रम debugfs entry.
 * @data: raw data poपूर्णांकer.
 */
अटल पूर्णांक brcmf_feat_debugfs_पढ़ो(काष्ठा seq_file *seq, व्योम *data)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(seq->निजी);
	u32 feats = bus_अगर->drvr->feat_flags;
	u32 quirks = bus_अगर->drvr->chip_quirks;
	पूर्णांक id;

	seq_म_लिखो(seq, "Features: %08x\n", feats);
	क्रम (id = 0; id < BRCMF_FEAT_LAST; id++)
		अगर (feats & BIT(id))
			seq_म_लिखो(seq, "\t%s\n", brcmf_feat_names[id]);
	seq_म_लिखो(seq, "\nQuirks:   %08x\n", quirks);
	क्रम (id = 0; id < BRCMF_FEAT_QUIRK_LAST; id++)
		अगर (quirks & BIT(id))
			seq_म_लिखो(seq, "\t%s\n", brcmf_quirk_names[id]);
	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक brcmf_feat_debugfs_पढ़ो(काष्ठा seq_file *seq, व्योम *data)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* DEBUG */

काष्ठा brcmf_feat_fwfeat अणु
	स्थिर अक्षर * स्थिर fwid;
	u32 feat_flags;
पूर्ण;

अटल स्थिर काष्ठा brcmf_feat_fwfeat brcmf_feat_fwfeat_map[] = अणु
	/* brcmfmac43602-pcie.ap.bin from linux-firmware.git commit ea1178515b88 */
	अणु "01-6cb8e269", BIT(BRCMF_FEAT_MONITOR) पूर्ण,
	/* brcmfmac4366b-pcie.bin from linux-firmware.git commit 52442afee990 */
	अणु "01-c47a91a4", BIT(BRCMF_FEAT_MONITOR) पूर्ण,
	/* brcmfmac4366b-pcie.bin from linux-firmware.git commit 211de1679a68 */
	अणु "01-801fb449", BIT(BRCMF_FEAT_MONITOR_FMT_HW_RX_HDR) पूर्ण,
	/* brcmfmac4366c-pcie.bin from linux-firmware.git commit 211de1679a68 */
	अणु "01-d2cbb8fd", BIT(BRCMF_FEAT_MONITOR_FMT_HW_RX_HDR) पूर्ण,
पूर्ण;

अटल व्योम brcmf_feat_firmware_overrides(काष्ठा brcmf_pub *drv)
अणु
	स्थिर काष्ठा brcmf_feat_fwfeat *e;
	u32 feat_flags = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(brcmf_feat_fwfeat_map); i++) अणु
		e = &brcmf_feat_fwfeat_map[i];
		अगर (!म_भेद(e->fwid, drv->fwver)) अणु
			feat_flags = e->feat_flags;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!feat_flags)
		वापस;

	क्रम (i = 0; i < BRCMF_FEAT_LAST; i++)
		अगर (feat_flags & BIT(i))
			brcmf_dbg(INFO, "enabling firmware feature: %s\n",
				  brcmf_feat_names[i]);
	drv->feat_flags |= feat_flags;
पूर्ण

/**
 * brcmf_feat_iovar_पूर्णांक_get() - determine feature through iovar query.
 *
 * @अगरp: पूर्णांकerface to query.
 * @id: feature id.
 * @name: iovar name.
 */
अटल व्योम brcmf_feat_iovar_पूर्णांक_get(काष्ठा brcmf_अगर *अगरp,
				     क्रमागत brcmf_feat_id id, अक्षर *name)
अणु
	u32 data;
	पूर्णांक err;

	/* we need to know firmware error */
	अगरp->fwil_fwerr = true;

	err = brcmf_fil_iovar_पूर्णांक_get(अगरp, name, &data);
	अगर (err == 0) अणु
		brcmf_dbg(INFO, "enabling feature: %s\n", brcmf_feat_names[id]);
		अगरp->drvr->feat_flags |= BIT(id);
	पूर्ण अन्यथा अणु
		brcmf_dbg(TRACE, "%s feature check failed: %d\n",
			  brcmf_feat_names[id], err);
	पूर्ण

	अगरp->fwil_fwerr = false;
पूर्ण

अटल व्योम brcmf_feat_iovar_data_set(काष्ठा brcmf_अगर *अगरp,
				      क्रमागत brcmf_feat_id id, अक्षर *name,
				      स्थिर व्योम *data, माप_प्रकार len)
अणु
	पूर्णांक err;

	/* we need to know firmware error */
	अगरp->fwil_fwerr = true;

	err = brcmf_fil_iovar_data_set(अगरp, name, data, len);
	अगर (err != -BRCMF_FW_UNSUPPORTED) अणु
		brcmf_dbg(INFO, "enabling feature: %s\n", brcmf_feat_names[id]);
		अगरp->drvr->feat_flags |= BIT(id);
	पूर्ण अन्यथा अणु
		brcmf_dbg(TRACE, "%s feature check failed: %d\n",
			  brcmf_feat_names[id], err);
	पूर्ण

	अगरp->fwil_fwerr = false;
पूर्ण

#घोषणा MAX_CAPS_BUFFER_SIZE	768
अटल व्योम brcmf_feat_firmware_capabilities(काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	अक्षर caps[MAX_CAPS_BUFFER_SIZE];
	क्रमागत brcmf_feat_id id;
	पूर्णांक i, err;

	err = brcmf_fil_iovar_data_get(अगरp, "cap", caps, माप(caps));
	अगर (err) अणु
		bphy_err(drvr, "could not get firmware cap (%d)\n", err);
		वापस;
	पूर्ण

	brcmf_dbg(INFO, "[ %s]\n", caps);

	क्रम (i = 0; i < ARRAY_SIZE(brcmf_fwcap_map); i++) अणु
		अगर (strnstr(caps, brcmf_fwcap_map[i].fwcap_id, माप(caps))) अणु
			id = brcmf_fwcap_map[i].feature;
			brcmf_dbg(INFO, "enabling feature: %s\n",
				  brcmf_feat_names[id]);
			अगरp->drvr->feat_flags |= BIT(id);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * brcmf_feat_fwcap_debugfs_पढ़ो() - expose firmware capabilities to debugfs.
 *
 * @seq: sequence क्रम debugfs entry.
 * @data: raw data poपूर्णांकer.
 */
अटल पूर्णांक brcmf_feat_fwcap_debugfs_पढ़ो(काष्ठा seq_file *seq, व्योम *data)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(seq->निजी);
	काष्ठा brcmf_pub *drvr = bus_अगर->drvr;
	काष्ठा brcmf_अगर *अगरp = brcmf_get_अगरp(drvr, 0);
	अक्षर caps[MAX_CAPS_BUFFER_SIZE + 1] = अणु पूर्ण;
	अक्षर *पंचांगp;
	पूर्णांक err;

	err = brcmf_fil_iovar_data_get(अगरp, "cap", caps, माप(caps));
	अगर (err) अणु
		bphy_err(drvr, "could not get firmware cap (%d)\n", err);
		वापस err;
	पूर्ण

	/* Put every capability in a new line */
	क्रम (पंचांगp = caps; *पंचांगp; पंचांगp++) अणु
		अगर (*पंचांगp == ' ')
			*पंचांगp = '\n';
	पूर्ण

	/* Usually there is a space at the end of capabilities string */
	seq_म_लिखो(seq, "%s", caps);
	/* So make sure we करोn't prपूर्णांक two line अवरोधs */
	अगर (पंचांगp > caps && *(पंचांगp - 1) != '\n')
		seq_म_लिखो(seq, "\n");

	वापस 0;
पूर्ण

व्योम brcmf_feat_attach(काष्ठा brcmf_pub *drvr)
अणु
	काष्ठा brcmf_अगर *अगरp = brcmf_get_अगरp(drvr, 0);
	काष्ठा brcmf_pno_macaddr_le pfn_mac;
	काष्ठा brcmf_gscan_config gscan_cfg;
	u32 wowl_cap;
	s32 err;

	brcmf_feat_firmware_capabilities(अगरp);
	स_रखो(&gscan_cfg, 0, माप(gscan_cfg));
	अगर (drvr->bus_अगर->chip != BRCM_CC_43430_CHIP_ID &&
	    drvr->bus_अगर->chip != BRCM_CC_4345_CHIP_ID)
		brcmf_feat_iovar_data_set(अगरp, BRCMF_FEAT_GSCAN,
					  "pfn_gscan_cfg",
					  &gscan_cfg, माप(gscan_cfg));
	brcmf_feat_iovar_पूर्णांक_get(अगरp, BRCMF_FEAT_PNO, "pfn");
	अगर (drvr->bus_अगर->wowl_supported)
		brcmf_feat_iovar_पूर्णांक_get(अगरp, BRCMF_FEAT_WOWL, "wowl");
	अगर (brcmf_feat_is_enabled(अगरp, BRCMF_FEAT_WOWL)) अणु
		err = brcmf_fil_iovar_पूर्णांक_get(अगरp, "wowl_cap", &wowl_cap);
		अगर (!err) अणु
			अगरp->drvr->feat_flags |= BIT(BRCMF_FEAT_WOWL_ARP_ND);
			अगर (wowl_cap & BRCMF_WOWL_PFN_FOUND)
				अगरp->drvr->feat_flags |=
					BIT(BRCMF_FEAT_WOWL_ND);
			अगर (wowl_cap & BRCMF_WOWL_GTK_FAILURE)
				अगरp->drvr->feat_flags |=
					BIT(BRCMF_FEAT_WOWL_GTK);
		पूर्ण
	पूर्ण
	/* MBSS करोes not work क्रम all chips */
	चयन (drvr->bus_अगर->chip) अणु
	हाल BRCM_CC_4330_CHIP_ID:
	हाल BRCM_CC_43362_CHIP_ID:
		अगरp->drvr->feat_flags &= ~BIT(BRCMF_FEAT_MBSS);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	brcmf_feat_iovar_पूर्णांक_get(अगरp, BRCMF_FEAT_RSDB, "rsdb_mode");
	brcmf_feat_iovar_पूर्णांक_get(अगरp, BRCMF_FEAT_TDLS, "tdls_enable");
	brcmf_feat_iovar_पूर्णांक_get(अगरp, BRCMF_FEAT_MFP, "mfp");

	pfn_mac.version = BRCMF_PFN_MACADDR_CFG_VER;
	err = brcmf_fil_iovar_data_get(अगरp, "pfn_macaddr", &pfn_mac,
				       माप(pfn_mac));
	अगर (!err)
		अगरp->drvr->feat_flags |= BIT(BRCMF_FEAT_SCAN_RANDOM_MAC);

	brcmf_feat_iovar_पूर्णांक_get(अगरp, BRCMF_FEAT_FWSUP, "sup_wpa");

	अगर (drvr->settings->feature_disable) अणु
		brcmf_dbg(INFO, "Features: 0x%02x, disable: 0x%02x\n",
			  अगरp->drvr->feat_flags,
			  drvr->settings->feature_disable);
		अगरp->drvr->feat_flags &= ~drvr->settings->feature_disable;
	पूर्ण

	brcmf_feat_firmware_overrides(drvr);

	/* set chip related quirks */
	चयन (drvr->bus_अगर->chip) अणु
	हाल BRCM_CC_43236_CHIP_ID:
		drvr->chip_quirks |= BIT(BRCMF_FEAT_QUIRK_AUTO_AUTH);
		अवरोध;
	हाल BRCM_CC_4329_CHIP_ID:
		drvr->chip_quirks |= BIT(BRCMF_FEAT_QUIRK_NEED_MPC);
		अवरोध;
	शेष:
		/* no quirks */
		अवरोध;
	पूर्ण
पूर्ण

व्योम brcmf_feat_debugfs_create(काष्ठा brcmf_pub *drvr)
अणु
	brcmf_debugfs_add_entry(drvr, "features", brcmf_feat_debugfs_पढ़ो);
	brcmf_debugfs_add_entry(drvr, "fwcap", brcmf_feat_fwcap_debugfs_पढ़ो);
पूर्ण

bool brcmf_feat_is_enabled(काष्ठा brcmf_अगर *अगरp, क्रमागत brcmf_feat_id id)
अणु
	वापस (अगरp->drvr->feat_flags & BIT(id));
पूर्ण

bool brcmf_feat_is_quirk_enabled(काष्ठा brcmf_अगर *अगरp,
				 क्रमागत brcmf_feat_quirk quirk)
अणु
	वापस (अगरp->drvr->chip_quirks & BIT(quirk));
पूर्ण
