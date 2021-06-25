<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2010 Broadcom Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <brcmu_wअगरi.h>
#समावेश <brcmu_utils.h>
#समावेश "core.h"
#समावेश "bus.h"
#समावेश "debug.h"
#समावेश "fwil.h"
#समावेश "fwil_types.h"
#समावेश "tracepoint.h"
#समावेश "common.h"
#समावेश "of.h"
#समावेश "firmware.h"
#समावेश "chip.h"

MODULE_AUTHOR("Broadcom Corporation");
MODULE_DESCRIPTION("Broadcom 802.11 wireless LAN fullmac driver.");
MODULE_LICENSE("Dual BSD/GPL");

#घोषणा BRCMF_DEFAULT_SCAN_CHANNEL_TIME	40
#घोषणा BRCMF_DEFAULT_SCAN_UNASSOC_TIME	40

/* शेष boost value क्रम RSSI_DELTA in preferred join selection */
#घोषणा BRCMF_JOIN_PREF_RSSI_BOOST	8

#घोषणा BRCMF_DEFAULT_TXGLOM_SIZE	32  /* max tx frames in glom chain */

अटल पूर्णांक brcmf_sdiod_txglomsz = BRCMF_DEFAULT_TXGLOM_SIZE;
module_param_named(txglomsz, brcmf_sdiod_txglomsz, पूर्णांक, 0);
MODULE_PARM_DESC(txglomsz, "Maximum tx packet chain size [SDIO]");

/* Debug level configuration. See debug.h क्रम bits, sysfs modअगरiable */
पूर्णांक brcmf_msg_level;
module_param_named(debug, brcmf_msg_level, पूर्णांक, 0600);
MODULE_PARM_DESC(debug, "Level of debug output");

अटल पूर्णांक brcmf_p2p_enable;
module_param_named(p2pon, brcmf_p2p_enable, पूर्णांक, 0);
MODULE_PARM_DESC(p2pon, "Enable legacy p2p management functionality");

अटल पूर्णांक brcmf_feature_disable;
module_param_named(feature_disable, brcmf_feature_disable, पूर्णांक, 0);
MODULE_PARM_DESC(feature_disable, "Disable features");

अटल अक्षर brcmf_firmware_path[BRCMF_FW_ALTPATH_LEN];
module_param_string(alternative_fw_path, brcmf_firmware_path,
		    BRCMF_FW_ALTPATH_LEN, 0400);
MODULE_PARM_DESC(alternative_fw_path, "Alternative firmware path");

अटल पूर्णांक brcmf_fcmode;
module_param_named(fcmode, brcmf_fcmode, पूर्णांक, 0);
MODULE_PARM_DESC(fcmode, "Mode of firmware signalled flow control");

अटल पूर्णांक brcmf_roamoff;
module_param_named(roamoff, brcmf_roamoff, पूर्णांक, 0400);
MODULE_PARM_DESC(roamoff, "Do not use internal roaming engine");

अटल पूर्णांक brcmf_iapp_enable;
module_param_named(iapp, brcmf_iapp_enable, पूर्णांक, 0);
MODULE_PARM_DESC(iapp, "Enable partial support for the obsoleted Inter-Access Point Protocol");

#अगर_घोषित DEBUG
/* always succeed brcmf_bus_started() */
अटल पूर्णांक brcmf_ignore_probe_fail;
module_param_named(ignore_probe_fail, brcmf_ignore_probe_fail, पूर्णांक, 0);
MODULE_PARM_DESC(ignore_probe_fail, "always succeed probe for debugging");
#पूर्ण_अगर

अटल काष्ठा brcmfmac_platक्रमm_data *brcmfmac_pdata;
काष्ठा brcmf_mp_global_t brcmf_mp_global;

व्योम brcmf_c_set_joinpref_शेष(काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_join_pref_params join_pref_params[2];
	पूर्णांक err;

	/* Setup join_pref to select target by RSSI (boost on 5GHz) */
	join_pref_params[0].type = BRCMF_JOIN_PREF_RSSI_DELTA;
	join_pref_params[0].len = 2;
	join_pref_params[0].rssi_gain = BRCMF_JOIN_PREF_RSSI_BOOST;
	join_pref_params[0].band = WLC_BAND_5G;

	join_pref_params[1].type = BRCMF_JOIN_PREF_RSSI;
	join_pref_params[1].len = 2;
	join_pref_params[1].rssi_gain = 0;
	join_pref_params[1].band = 0;
	err = brcmf_fil_iovar_data_set(अगरp, "join_pref", join_pref_params,
				       माप(join_pref_params));
	अगर (err)
		bphy_err(drvr, "Set join_pref error (%d)\n", err);
पूर्ण

अटल पूर्णांक brcmf_c_करोwnload(काष्ठा brcmf_अगर *अगरp, u16 flag,
			    काष्ठा brcmf_dload_data_le *dload_buf,
			    u32 len)
अणु
	s32 err;

	flag |= (DLOAD_HANDLER_VER << DLOAD_FLAG_VER_SHIFT);
	dload_buf->flag = cpu_to_le16(flag);
	dload_buf->dload_type = cpu_to_le16(DL_TYPE_CLM);
	dload_buf->len = cpu_to_le32(len);
	dload_buf->crc = cpu_to_le32(0);
	len = माप(*dload_buf) + len - 1;

	err = brcmf_fil_iovar_data_set(अगरp, "clmload", dload_buf, len);

	वापस err;
पूर्ण

अटल पूर्णांक brcmf_c_process_clm_blob(काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_bus *bus = drvr->bus_अगर;
	काष्ठा brcmf_dload_data_le *chunk_buf;
	स्थिर काष्ठा firmware *clm = शून्य;
	u8 clm_name[BRCMF_FW_NAME_LEN];
	u32 chunk_len;
	u32 datalen;
	u32 cumulative_len;
	u16 dl_flag = DL_BEGIN;
	u32 status;
	s32 err;

	brcmf_dbg(TRACE, "Enter\n");

	स_रखो(clm_name, 0, माप(clm_name));
	err = brcmf_bus_get_fwname(bus, ".clm_blob", clm_name);
	अगर (err) अणु
		bphy_err(drvr, "get CLM blob file name failed (%d)\n", err);
		वापस err;
	पूर्ण

	err = firmware_request_nowarn(&clm, clm_name, bus->dev);
	अगर (err) अणु
		brcmf_info("no clm_blob available (err=%d), device may have limited channels available\n",
			   err);
		वापस 0;
	पूर्ण

	chunk_buf = kzalloc(माप(*chunk_buf) + MAX_CHUNK_LEN - 1, GFP_KERNEL);
	अगर (!chunk_buf) अणु
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण

	datalen = clm->size;
	cumulative_len = 0;
	करो अणु
		अगर (datalen > MAX_CHUNK_LEN) अणु
			chunk_len = MAX_CHUNK_LEN;
		पूर्ण अन्यथा अणु
			chunk_len = datalen;
			dl_flag |= DL_END;
		पूर्ण
		स_नकल(chunk_buf->data, clm->data + cumulative_len, chunk_len);

		err = brcmf_c_करोwnload(अगरp, dl_flag, chunk_buf, chunk_len);

		dl_flag &= ~DL_BEGIN;

		cumulative_len += chunk_len;
		datalen -= chunk_len;
	पूर्ण जबतक ((datalen > 0) && (err == 0));

	अगर (err) अणु
		bphy_err(drvr, "clmload (%zu byte file) failed (%d)\n",
			 clm->size, err);
		/* Retrieve clmload_status and prपूर्णांक */
		err = brcmf_fil_iovar_पूर्णांक_get(अगरp, "clmload_status", &status);
		अगर (err)
			bphy_err(drvr, "get clmload_status failed (%d)\n", err);
		अन्यथा
			brcmf_dbg(INFO, "clmload_status=%d\n", status);
		err = -EIO;
	पूर्ण

	kमुक्त(chunk_buf);
करोne:
	release_firmware(clm);
	वापस err;
पूर्ण

पूर्णांक brcmf_c_preinit_dcmds(काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	s8 evenपंचांगask[BRCMF_EVENTING_MASK_LEN];
	u8 buf[BRCMF_DCMD_SMLEN];
	काष्ठा brcmf_bus *bus;
	काष्ठा brcmf_rev_info_le revinfo;
	काष्ठा brcmf_rev_info *ri;
	अक्षर *clmver;
	अक्षर *ptr;
	s32 err;

	/* retreive mac address */
	err = brcmf_fil_iovar_data_get(अगरp, "cur_etheraddr", अगरp->mac_addr,
				       माप(अगरp->mac_addr));
	अगर (err < 0) अणु
		bphy_err(drvr, "Retrieving cur_etheraddr failed, %d\n", err);
		जाओ करोne;
	पूर्ण
	स_नकल(अगरp->drvr->mac, अगरp->mac_addr, माप(अगरp->drvr->mac));
	स_नकल(अगरp->drvr->wiphy->perm_addr, अगरp->drvr->mac, ETH_ALEN);

	bus = अगरp->drvr->bus_अगर;
	ri = &अगरp->drvr->revinfo;

	err = brcmf_fil_cmd_data_get(अगरp, BRCMF_C_GET_REVINFO,
				     &revinfo, माप(revinfo));
	अगर (err < 0) अणु
		bphy_err(drvr, "retrieving revision info failed, %d\n", err);
		strlcpy(ri->chipname, "UNKNOWN", माप(ri->chipname));
	पूर्ण अन्यथा अणु
		ri->venकरोrid = le32_to_cpu(revinfo.venकरोrid);
		ri->deviceid = le32_to_cpu(revinfo.deviceid);
		ri->radiorev = le32_to_cpu(revinfo.radiorev);
		ri->corerev = le32_to_cpu(revinfo.corerev);
		ri->boardid = le32_to_cpu(revinfo.boardid);
		ri->boardvenकरोr = le32_to_cpu(revinfo.boardvenकरोr);
		ri->boardrev = le32_to_cpu(revinfo.boardrev);
		ri->driverrev = le32_to_cpu(revinfo.driverrev);
		ri->ucoderev = le32_to_cpu(revinfo.ucoderev);
		ri->bus = le32_to_cpu(revinfo.bus);
		ri->phytype = le32_to_cpu(revinfo.phytype);
		ri->phyrev = le32_to_cpu(revinfo.phyrev);
		ri->anarev = le32_to_cpu(revinfo.anarev);
		ri->chippkg = le32_to_cpu(revinfo.chippkg);
		ri->nvramrev = le32_to_cpu(revinfo.nvramrev);

		/* use revinfo अगर not known yet */
		अगर (!bus->chip) अणु
			bus->chip = le32_to_cpu(revinfo.chipnum);
			bus->chiprev = le32_to_cpu(revinfo.chiprev);
		पूर्ण
	पूर्ण
	ri->result = err;

	अगर (bus->chip)
		brcmf_chip_name(bus->chip, bus->chiprev,
				ri->chipname, माप(ri->chipname));

	/* Do any CLM करोwnloading */
	err = brcmf_c_process_clm_blob(अगरp);
	अगर (err < 0) अणु
		bphy_err(drvr, "download CLM blob file failed, %d\n", err);
		जाओ करोne;
	पूर्ण

	/* query क्रम 'ver' to get version info from firmware */
	स_रखो(buf, 0, माप(buf));
	err = brcmf_fil_iovar_data_get(अगरp, "ver", buf, माप(buf));
	अगर (err < 0) अणु
		bphy_err(drvr, "Retrieving version information failed, %d\n",
			 err);
		जाओ करोne;
	पूर्ण
	ptr = (अक्षर *)buf;
	strsep(&ptr, "\n");

	/* Prपूर्णांक fw version info */
	brcmf_info("Firmware: %s %s\n", ri->chipname, buf);

	/* locate firmware version number क्रम ethtool */
	ptr = म_खोजप(buf, ' ') + 1;
	strlcpy(अगरp->drvr->fwver, ptr, माप(अगरp->drvr->fwver));

	/* Query क्रम 'clmver' to get CLM version info from firmware */
	स_रखो(buf, 0, माप(buf));
	err = brcmf_fil_iovar_data_get(अगरp, "clmver", buf, माप(buf));
	अगर (err) अणु
		brcmf_dbg(TRACE, "retrieving clmver failed, %d\n", err);
	पूर्ण अन्यथा अणु
		clmver = (अक्षर *)buf;
		/* store CLM version क्रम adding it to revinfo debugfs file */
		स_नकल(अगरp->drvr->clmver, clmver, माप(अगरp->drvr->clmver));

		/* Replace all newline/linefeed अक्षरacters with space
		 * अक्षरacter
		 */
		strreplace(clmver, '\n', ' ');

		brcmf_dbg(INFO, "CLM version = %s\n", clmver);
	पूर्ण

	/* set mpc */
	err = brcmf_fil_iovar_पूर्णांक_set(अगरp, "mpc", 1);
	अगर (err) अणु
		bphy_err(drvr, "failed setting mpc\n");
		जाओ करोne;
	पूर्ण

	brcmf_c_set_joinpref_शेष(अगरp);

	/* Setup event_msgs, enable E_IF */
	err = brcmf_fil_iovar_data_get(अगरp, "event_msgs", evenपंचांगask,
				       BRCMF_EVENTING_MASK_LEN);
	अगर (err) अणु
		bphy_err(drvr, "Get event_msgs error (%d)\n", err);
		जाओ करोne;
	पूर्ण
	setbit(evenपंचांगask, BRCMF_E_IF);
	err = brcmf_fil_iovar_data_set(अगरp, "event_msgs", evenपंचांगask,
				       BRCMF_EVENTING_MASK_LEN);
	अगर (err) अणु
		bphy_err(drvr, "Set event_msgs error (%d)\n", err);
		जाओ करोne;
	पूर्ण

	/* Setup शेष scan channel समय */
	err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_SCAN_CHANNEL_TIME,
				    BRCMF_DEFAULT_SCAN_CHANNEL_TIME);
	अगर (err) अणु
		bphy_err(drvr, "BRCMF_C_SET_SCAN_CHANNEL_TIME error (%d)\n",
			 err);
		जाओ करोne;
	पूर्ण

	/* Setup शेष scan unassoc समय */
	err = brcmf_fil_cmd_पूर्णांक_set(अगरp, BRCMF_C_SET_SCAN_UNASSOC_TIME,
				    BRCMF_DEFAULT_SCAN_UNASSOC_TIME);
	अगर (err) अणु
		bphy_err(drvr, "BRCMF_C_SET_SCAN_UNASSOC_TIME error (%d)\n",
			 err);
		जाओ करोne;
	पूर्ण

	/* Enable tx beamक्रमming, errors can be ignored (not supported) */
	(व्योम)brcmf_fil_iovar_पूर्णांक_set(अगरp, "txbf", 1);
करोne:
	वापस err;
पूर्ण

#अगर_अघोषित CONFIG_BRCM_TRACING
व्योम __brcmf_err(काष्ठा brcmf_bus *bus, स्थिर अक्षर *func, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;
	अगर (bus)
		dev_err(bus->dev, "%s: %pV", func, &vaf);
	अन्यथा
		pr_err("%s: %pV", func, &vaf);

	बहु_पूर्ण(args);
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_BRCM_TRACING) || defined(CONFIG_BRCMDBG)
व्योम __brcmf_dbg(u32 level, स्थिर अक्षर *func, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf = अणु
		.fmt = fmt,
	पूर्ण;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.va = &args;
	अगर (brcmf_msg_level & level)
		pr_debug("%s %pV", func, &vaf);
	trace_brcmf_dbg(level, func, &vaf);
	बहु_पूर्ण(args);
पूर्ण
#पूर्ण_अगर

अटल व्योम brcmf_mp_attach(व्योम)
अणु
	/* If module param firmware path is set then this will always be used,
	 * अगर not set then अगर available use the platक्रमm data version. To make
	 * sure it माला_लो initialized at all, always copy the module param version
	 */
	strlcpy(brcmf_mp_global.firmware_path, brcmf_firmware_path,
		BRCMF_FW_ALTPATH_LEN);
	अगर ((brcmfmac_pdata) && (brcmfmac_pdata->fw_alternative_path) &&
	    (brcmf_mp_global.firmware_path[0] == '\0')) अणु
		strlcpy(brcmf_mp_global.firmware_path,
			brcmfmac_pdata->fw_alternative_path,
			BRCMF_FW_ALTPATH_LEN);
	पूर्ण
पूर्ण

काष्ठा brcmf_mp_device *brcmf_get_module_param(काष्ठा device *dev,
					       क्रमागत brcmf_bus_type bus_type,
					       u32 chip, u32 chiprev)
अणु
	काष्ठा brcmf_mp_device *settings;
	काष्ठा brcmfmac_pd_device *device_pd;
	bool found;
	पूर्णांक i;

	brcmf_dbg(INFO, "Enter, bus=%d, chip=%d, rev=%d\n", bus_type, chip,
		  chiprev);
	settings = kzalloc(माप(*settings), GFP_ATOMIC);
	अगर (!settings)
		वापस शून्य;

	/* start by using the module paramaters */
	settings->p2p_enable = !!brcmf_p2p_enable;
	settings->feature_disable = brcmf_feature_disable;
	settings->fcmode = brcmf_fcmode;
	settings->roamoff = !!brcmf_roamoff;
	settings->iapp = !!brcmf_iapp_enable;
#अगर_घोषित DEBUG
	settings->ignore_probe_fail = !!brcmf_ignore_probe_fail;
#पूर्ण_अगर

	अगर (bus_type == BRCMF_BUSTYPE_SDIO)
		settings->bus.sdio.txglomsz = brcmf_sdiod_txglomsz;

	/* See अगर there is any device specअगरic platक्रमm data configured */
	found = false;
	अगर (brcmfmac_pdata) अणु
		क्रम (i = 0; i < brcmfmac_pdata->device_count; i++) अणु
			device_pd = &brcmfmac_pdata->devices[i];
			अगर ((device_pd->bus_type == bus_type) &&
			    (device_pd->id == chip) &&
			    ((device_pd->rev == chiprev) ||
			     (device_pd->rev == -1))) अणु
				brcmf_dbg(INFO, "Platform data for device found\n");
				settings->country_codes =
						device_pd->country_codes;
				अगर (device_pd->bus_type == BRCMF_BUSTYPE_SDIO)
					स_नकल(&settings->bus.sdio,
					       &device_pd->bus.sdio,
					       माप(settings->bus.sdio));
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!found) अणु
		/* No platक्रमm data क्रम this device, try OF and DMI data */
		brcmf_dmi_probe(settings, chip, chiprev);
		brcmf_of_probe(dev, bus_type, settings);
	पूर्ण
	वापस settings;
पूर्ण

व्योम brcmf_release_module_param(काष्ठा brcmf_mp_device *module_param)
अणु
	kमुक्त(module_param);
पूर्ण

अटल पूर्णांक __init brcmf_common_pd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	brcmf_dbg(INFO, "Enter\n");

	brcmfmac_pdata = dev_get_platdata(&pdev->dev);

	अगर (brcmfmac_pdata->घातer_on)
		brcmfmac_pdata->घातer_on();

	वापस 0;
पूर्ण

अटल पूर्णांक brcmf_common_pd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	brcmf_dbg(INFO, "Enter\n");

	अगर (brcmfmac_pdata->घातer_off)
		brcmfmac_pdata->घातer_off();

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver brcmf_pd = अणु
	.हटाओ		= brcmf_common_pd_हटाओ,
	.driver		= अणु
		.name	= BRCMFMAC_PDATA_NAME,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init brcmfmac_module_init(व्योम)
अणु
	पूर्णांक err;

	/* Get the platक्रमm data (अगर available) क्रम our devices */
	err = platक्रमm_driver_probe(&brcmf_pd, brcmf_common_pd_probe);
	अगर (err == -ENODEV)
		brcmf_dbg(INFO, "No platform data available.\n");

	/* Initialize global module paramaters */
	brcmf_mp_attach();

	/* Continue the initialization by रेजिस्टरing the dअगरferent busses */
	err = brcmf_core_init();
	अगर (err) अणु
		अगर (brcmfmac_pdata)
			platक्रमm_driver_unरेजिस्टर(&brcmf_pd);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम __निकास brcmfmac_module_निकास(व्योम)
अणु
	brcmf_core_निकास();
	अगर (brcmfmac_pdata)
		platक्रमm_driver_unरेजिस्टर(&brcmf_pd);
पूर्ण

module_init(brcmfmac_module_init);
module_निकास(brcmfmac_module_निकास);

