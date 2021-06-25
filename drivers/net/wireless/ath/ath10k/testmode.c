<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014-2017 Qualcomm Atheros, Inc.
 */

#समावेश "testmode.h"

#समावेश <net/netlink.h>
#समावेश <linux/firmware.h>

#समावेश "debug.h"
#समावेश "wmi.h"
#समावेश "hif.h"
#समावेश "hw.h"
#समावेश "core.h"

#समावेश "testmode_i.h"

अटल स्थिर काष्ठा nla_policy ath10k_पंचांग_policy[ATH10K_TM_ATTR_MAX + 1] = अणु
	[ATH10K_TM_ATTR_CMD]		= अणु .type = NLA_U32 पूर्ण,
	[ATH10K_TM_ATTR_DATA]		= अणु .type = NLA_BINARY,
					    .len = ATH10K_TM_DATA_MAX_LEN पूर्ण,
	[ATH10K_TM_ATTR_WMI_CMDID]	= अणु .type = NLA_U32 पूर्ण,
	[ATH10K_TM_ATTR_VERSION_MAJOR]	= अणु .type = NLA_U32 पूर्ण,
	[ATH10K_TM_ATTR_VERSION_MINOR]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

/* Returns true अगर callee consumes the skb and the skb should be discarded.
 * Returns false अगर skb is not used. Does not sleep.
 */
bool ath10k_पंचांग_event_wmi(काष्ठा ath10k *ar, u32 cmd_id, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *nl_skb;
	bool consumed;
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_TESTMODE,
		   "testmode event wmi cmd_id %d skb %pK skb->len %d\n",
		   cmd_id, skb, skb->len);

	ath10k_dbg_dump(ar, ATH10K_DBG_TESTMODE, शून्य, "", skb->data, skb->len);

	spin_lock_bh(&ar->data_lock);

	अगर (!ar->tesपंचांगode.utf_monitor) अणु
		consumed = false;
		जाओ out;
	पूर्ण

	/* Only tesपंचांगode.c should be handling events from utf firmware,
	 * otherwise all sort of problems will arise as mac80211 operations
	 * are not initialised.
	 */
	consumed = true;

	nl_skb = cfg80211_tesपंचांगode_alloc_event_skb(ar->hw->wiphy,
						   2 * माप(u32) + skb->len,
						   GFP_ATOMIC);
	अगर (!nl_skb) अणु
		ath10k_warn(ar,
			    "failed to allocate skb for testmode wmi event\n");
		जाओ out;
	पूर्ण

	ret = nla_put_u32(nl_skb, ATH10K_TM_ATTR_CMD, ATH10K_TM_CMD_WMI);
	अगर (ret) अणु
		ath10k_warn(ar,
			    "failed to put testmode wmi event cmd attribute: %d\n",
			    ret);
		kमुक्त_skb(nl_skb);
		जाओ out;
	पूर्ण

	ret = nla_put_u32(nl_skb, ATH10K_TM_ATTR_WMI_CMDID, cmd_id);
	अगर (ret) अणु
		ath10k_warn(ar,
			    "failed to put testmode wmi event cmd_id: %d\n",
			    ret);
		kमुक्त_skb(nl_skb);
		जाओ out;
	पूर्ण

	ret = nla_put(nl_skb, ATH10K_TM_ATTR_DATA, skb->len, skb->data);
	अगर (ret) अणु
		ath10k_warn(ar,
			    "failed to copy skb to testmode wmi event: %d\n",
			    ret);
		kमुक्त_skb(nl_skb);
		जाओ out;
	पूर्ण

	cfg80211_tesपंचांगode_event(nl_skb, GFP_ATOMIC);

out:
	spin_unlock_bh(&ar->data_lock);

	वापस consumed;
पूर्ण

अटल पूर्णांक ath10k_पंचांग_cmd_get_version(काष्ठा ath10k *ar, काष्ठा nlattr *tb[])
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_TESTMODE,
		   "testmode cmd get version_major %d version_minor %d\n",
		   ATH10K_TESTMODE_VERSION_MAJOR,
		   ATH10K_TESTMODE_VERSION_MINOR);

	skb = cfg80211_tesपंचांगode_alloc_reply_skb(ar->hw->wiphy,
						nla_total_size(माप(u32)));
	अगर (!skb)
		वापस -ENOMEM;

	ret = nla_put_u32(skb, ATH10K_TM_ATTR_VERSION_MAJOR,
			  ATH10K_TESTMODE_VERSION_MAJOR);
	अगर (ret) अणु
		kमुक्त_skb(skb);
		वापस ret;
	पूर्ण

	ret = nla_put_u32(skb, ATH10K_TM_ATTR_VERSION_MINOR,
			  ATH10K_TESTMODE_VERSION_MINOR);
	अगर (ret) अणु
		kमुक्त_skb(skb);
		वापस ret;
	पूर्ण

	ret = nla_put_u32(skb, ATH10K_TM_ATTR_WMI_OP_VERSION,
			  ar->normal_mode_fw.fw_file.wmi_op_version);
	अगर (ret) अणु
		kमुक्त_skb(skb);
		वापस ret;
	पूर्ण

	वापस cfg80211_tesपंचांगode_reply(skb);
पूर्ण

अटल पूर्णांक ath10k_पंचांग_fetch_utf_firmware_api_1(काष्ठा ath10k *ar,
					      काष्ठा ath10k_fw_file *fw_file)
अणु
	अक्षर filename[100];
	पूर्णांक ret;

	snम_लिखो(filename, माप(filename), "%s/%s",
		 ar->hw_params.fw.dir, ATH10K_FW_UTF_खाता);

	/* load utf firmware image */
	ret = firmware_request_nowarn(&fw_file->firmware, filename, ar->dev);
	ath10k_dbg(ar, ATH10K_DBG_TESTMODE, "testmode fw request '%s': %d\n",
		   filename, ret);

	अगर (ret) अणु
		ath10k_warn(ar, "failed to retrieve utf firmware '%s': %d\n",
			    filename, ret);
		वापस ret;
	पूर्ण

	/* We didn't find FW UTF API 1 ("utf.bin") करोes not advertise
	 * firmware features. Do an ugly hack where we क्रमce the firmware
	 * features to match with 10.1 branch so that wmi.c will use the
	 * correct WMI पूर्णांकerface.
	 */

	fw_file->wmi_op_version = ATH10K_FW_WMI_OP_VERSION_10_1;
	fw_file->htt_op_version = ATH10K_FW_HTT_OP_VERSION_10_1;
	fw_file->firmware_data = fw_file->firmware->data;
	fw_file->firmware_len = fw_file->firmware->size;

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_पंचांग_fetch_firmware(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_fw_components *utf_mode_fw;
	पूर्णांक ret;
	अक्षर fw_name[100];
	पूर्णांक fw_api2 = 2;

	चयन (ar->hअगर.bus) अणु
	हाल ATH10K_BUS_SDIO:
	हाल ATH10K_BUS_USB:
		scnम_लिखो(fw_name, माप(fw_name), "%s-%s-%d.bin",
			  ATH10K_FW_UTF_खाता_BASE, ath10k_bus_str(ar->hअगर.bus),
			  fw_api2);
		अवरोध;
	शेष:
		scnम_लिखो(fw_name, माप(fw_name), "%s-%d.bin",
			  ATH10K_FW_UTF_खाता_BASE, fw_api2);
		अवरोध;
	पूर्ण

	ret = ath10k_core_fetch_firmware_api_n(ar, fw_name,
					       &ar->tesपंचांगode.utf_mode_fw.fw_file);
	अगर (ret == 0) अणु
		ath10k_dbg(ar, ATH10K_DBG_TESTMODE, "testmode using fw utf api 2");
		जाओ out;
	पूर्ण

	ret = ath10k_पंचांग_fetch_utf_firmware_api_1(ar, &ar->tesपंचांगode.utf_mode_fw.fw_file);
	अगर (ret) अणु
		ath10k_err(ar, "failed to fetch utf firmware binary: %d", ret);
		वापस ret;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_TESTMODE, "testmode using utf api 1");

out:
	utf_mode_fw = &ar->tesपंचांगode.utf_mode_fw;

	/* Use the same board data file as the normal firmware uses (but
	 * it's still "owned" by normal_mode_fw so we shouldn't मुक्त it.
	 */
	utf_mode_fw->board_data = ar->normal_mode_fw.board_data;
	utf_mode_fw->board_len = ar->normal_mode_fw.board_len;

	अगर (!utf_mode_fw->fw_file.otp_data) अणु
		ath10k_info(ar, "utf.bin didn't contain otp binary, taking it from the normal mode firmware");
		utf_mode_fw->fw_file.otp_data = ar->normal_mode_fw.fw_file.otp_data;
		utf_mode_fw->fw_file.otp_len = ar->normal_mode_fw.fw_file.otp_len;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_पंचांग_cmd_utf_start(काष्ठा ath10k *ar, काष्ठा nlattr *tb[])
अणु
	स्थिर अक्षर *ver;
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_TESTMODE, "testmode cmd utf start\n");

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state == ATH10K_STATE_UTF) अणु
		ret = -EALREADY;
		जाओ err;
	पूर्ण

	/* start utf only when the driver is not in use  */
	अगर (ar->state != ATH10K_STATE_OFF) अणु
		ret = -EBUSY;
		जाओ err;
	पूर्ण

	अगर (WARN_ON(ar->tesपंचांगode.utf_mode_fw.fw_file.firmware != शून्य)) अणु
		/* utf image is alपढ़ोy करोwnloaded, it shouldn't be */
		ret = -EEXIST;
		जाओ err;
	पूर्ण

	ret = ath10k_पंचांग_fetch_firmware(ar);
	अगर (ret) अणु
		ath10k_err(ar, "failed to fetch UTF firmware: %d", ret);
		जाओ err;
	पूर्ण

	अगर (ar->tesपंचांगode.utf_mode_fw.fw_file.codeswap_data &&
	    ar->tesपंचांगode.utf_mode_fw.fw_file.codeswap_len) अणु
		ret = ath10k_swap_code_seg_init(ar,
						&ar->tesपंचांगode.utf_mode_fw.fw_file);
		अगर (ret) अणु
			ath10k_warn(ar,
				    "failed to init utf code swap segment: %d\n",
				    ret);
			जाओ err_release_utf_mode_fw;
		पूर्ण
	पूर्ण

	spin_lock_bh(&ar->data_lock);
	ar->tesपंचांगode.utf_monitor = true;
	spin_unlock_bh(&ar->data_lock);

	ath10k_dbg(ar, ATH10K_DBG_TESTMODE, "testmode wmi version %d\n",
		   ar->tesपंचांगode.utf_mode_fw.fw_file.wmi_op_version);

	ret = ath10k_hअगर_घातer_up(ar, ATH10K_FIRMWARE_MODE_UTF);
	अगर (ret) अणु
		ath10k_err(ar, "failed to power up hif (testmode): %d\n", ret);
		ar->state = ATH10K_STATE_OFF;
		जाओ err_release_utf_mode_fw;
	पूर्ण

	ret = ath10k_core_start(ar, ATH10K_FIRMWARE_MODE_UTF,
				&ar->tesपंचांगode.utf_mode_fw);
	अगर (ret) अणु
		ath10k_err(ar, "failed to start core (testmode): %d\n", ret);
		ar->state = ATH10K_STATE_OFF;
		जाओ err_घातer_करोwn;
	पूर्ण

	ar->state = ATH10K_STATE_UTF;

	अगर (म_माप(ar->tesपंचांगode.utf_mode_fw.fw_file.fw_version) > 0)
		ver = ar->tesपंचांगode.utf_mode_fw.fw_file.fw_version;
	अन्यथा
		ver = "API 1";

	ath10k_info(ar, "UTF firmware %s started\n", ver);

	mutex_unlock(&ar->conf_mutex);

	वापस 0;

err_घातer_करोwn:
	ath10k_hअगर_घातer_करोwn(ar);

err_release_utf_mode_fw:
	अगर (ar->tesपंचांगode.utf_mode_fw.fw_file.codeswap_data &&
	    ar->tesपंचांगode.utf_mode_fw.fw_file.codeswap_len)
		ath10k_swap_code_seg_release(ar,
					     &ar->tesपंचांगode.utf_mode_fw.fw_file);

	release_firmware(ar->tesपंचांगode.utf_mode_fw.fw_file.firmware);
	ar->tesपंचांगode.utf_mode_fw.fw_file.firmware = शून्य;

err:
	mutex_unlock(&ar->conf_mutex);

	वापस ret;
पूर्ण

अटल व्योम __ath10k_पंचांग_cmd_utf_stop(काष्ठा ath10k *ar)
अणु
	lockdep_निश्चित_held(&ar->conf_mutex);

	ath10k_core_stop(ar);
	ath10k_hअगर_घातer_करोwn(ar);

	spin_lock_bh(&ar->data_lock);

	ar->tesपंचांगode.utf_monitor = false;

	spin_unlock_bh(&ar->data_lock);

	अगर (ar->tesपंचांगode.utf_mode_fw.fw_file.codeswap_data &&
	    ar->tesपंचांगode.utf_mode_fw.fw_file.codeswap_len)
		ath10k_swap_code_seg_release(ar,
					     &ar->tesपंचांगode.utf_mode_fw.fw_file);

	release_firmware(ar->tesपंचांगode.utf_mode_fw.fw_file.firmware);
	ar->tesपंचांगode.utf_mode_fw.fw_file.firmware = शून्य;

	ar->state = ATH10K_STATE_OFF;
पूर्ण

अटल पूर्णांक ath10k_पंचांग_cmd_utf_stop(काष्ठा ath10k *ar, काष्ठा nlattr *tb[])
अणु
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_TESTMODE, "testmode cmd utf stop\n");

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state != ATH10K_STATE_UTF) अणु
		ret = -ENETDOWN;
		जाओ out;
	पूर्ण

	__ath10k_पंचांग_cmd_utf_stop(ar);

	ret = 0;

	ath10k_info(ar, "UTF firmware stopped\n");

out:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_पंचांग_cmd_wmi(काष्ठा ath10k *ar, काष्ठा nlattr *tb[])
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक ret, buf_len;
	u32 cmd_id;
	व्योम *buf;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state != ATH10K_STATE_UTF) अणु
		ret = -ENETDOWN;
		जाओ out;
	पूर्ण

	अगर (!tb[ATH10K_TM_ATTR_DATA]) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!tb[ATH10K_TM_ATTR_WMI_CMDID]) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	buf = nla_data(tb[ATH10K_TM_ATTR_DATA]);
	buf_len = nla_len(tb[ATH10K_TM_ATTR_DATA]);
	cmd_id = nla_get_u32(tb[ATH10K_TM_ATTR_WMI_CMDID]);

	ath10k_dbg(ar, ATH10K_DBG_TESTMODE,
		   "testmode cmd wmi cmd_id %d buf %pK buf_len %d\n",
		   cmd_id, buf, buf_len);

	ath10k_dbg_dump(ar, ATH10K_DBG_TESTMODE, शून्य, "", buf, buf_len);

	skb = ath10k_wmi_alloc_skb(ar, buf_len);
	अगर (!skb) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	स_नकल(skb->data, buf, buf_len);

	ret = ath10k_wmi_cmd_send(ar, skb, cmd_id);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to transmit wmi command (testmode): %d\n",
			    ret);
		जाओ out;
	पूर्ण

	ret = 0;

out:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

पूर्णांक ath10k_पंचांग_cmd(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		  व्योम *data, पूर्णांक len)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा nlattr *tb[ATH10K_TM_ATTR_MAX + 1];
	पूर्णांक ret;

	ret = nla_parse_deprecated(tb, ATH10K_TM_ATTR_MAX, data, len,
				   ath10k_पंचांग_policy, शून्य);
	अगर (ret)
		वापस ret;

	अगर (!tb[ATH10K_TM_ATTR_CMD])
		वापस -EINVAL;

	चयन (nla_get_u32(tb[ATH10K_TM_ATTR_CMD])) अणु
	हाल ATH10K_TM_CMD_GET_VERSION:
		वापस ath10k_पंचांग_cmd_get_version(ar, tb);
	हाल ATH10K_TM_CMD_UTF_START:
		वापस ath10k_पंचांग_cmd_utf_start(ar, tb);
	हाल ATH10K_TM_CMD_UTF_STOP:
		वापस ath10k_पंचांग_cmd_utf_stop(ar, tb);
	हाल ATH10K_TM_CMD_WMI:
		वापस ath10k_पंचांग_cmd_wmi(ar, tb);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

व्योम ath10k_tesपंचांगode_destroy(काष्ठा ath10k *ar)
अणु
	mutex_lock(&ar->conf_mutex);

	अगर (ar->state != ATH10K_STATE_UTF) अणु
		/* utf firmware is not running, nothing to करो */
		जाओ out;
	पूर्ण

	__ath10k_पंचांग_cmd_utf_stop(ar);

out:
	mutex_unlock(&ar->conf_mutex);
पूर्ण
