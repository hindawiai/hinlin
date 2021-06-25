<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "cmd.h"

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/etherdevice.h>

#समावेश "wl1251.h"
#समावेश "reg.h"
#समावेश "io.h"
#समावेश "ps.h"
#समावेश "acx.h"

/**
 * send command to firmware
 *
 * @wl: wl काष्ठा
 * @id: command id
 * @buf: buffer containing the command, must work with dma
 * @len: length of the buffer
 */
पूर्णांक wl1251_cmd_send(काष्ठा wl1251 *wl, u16 id, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा wl1251_cmd_header *cmd;
	अचिन्हित दीर्घ समयout;
	u32 पूर्णांकr;
	पूर्णांक ret = 0;

	cmd = buf;
	cmd->id = id;
	cmd->status = 0;

	WARN_ON(len % 4 != 0);

	wl1251_mem_ग_लिखो(wl, wl->cmd_box_addr, buf, len);

	wl1251_reg_ग_लिखो32(wl, ACX_REG_INTERRUPT_TRIG, INTR_TRIG_CMD);

	समयout = jअगरfies + msecs_to_jअगरfies(WL1251_COMMAND_TIMEOUT);

	पूर्णांकr = wl1251_reg_पढ़ो32(wl, ACX_REG_INTERRUPT_NO_CLEAR);
	जबतक (!(पूर्णांकr & WL1251_ACX_INTR_CMD_COMPLETE)) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			wl1251_error("command complete timeout");
			ret = -ETIMEDOUT;
			जाओ out;
		पूर्ण

		msleep(1);

		पूर्णांकr = wl1251_reg_पढ़ो32(wl, ACX_REG_INTERRUPT_NO_CLEAR);
	पूर्ण

	wl1251_reg_ग_लिखो32(wl, ACX_REG_INTERRUPT_ACK,
			   WL1251_ACX_INTR_CMD_COMPLETE);

out:
	वापस ret;
पूर्ण

/**
 * send test command to firmware
 *
 * @wl: wl काष्ठा
 * @buf: buffer containing the command, with all headers, must work with dma
 * @buf_len: length of the buffer
 * @answer: is answer needed
 */
पूर्णांक wl1251_cmd_test(काष्ठा wl1251 *wl, व्योम *buf, माप_प्रकार buf_len, u8 answer)
अणु
	पूर्णांक ret;

	wl1251_debug(DEBUG_CMD, "cmd test");

	ret = wl1251_cmd_send(wl, CMD_TEST, buf, buf_len);

	अगर (ret < 0) अणु
		wl1251_warning("TEST command failed");
		वापस ret;
	पूर्ण

	अगर (answer) अणु
		काष्ठा wl1251_command *cmd_answer;

		/*
		 * The test command got in, we can पढ़ो the answer.
		 * The answer would be a wl1251_command, where the
		 * parameter array contains the actual answer.
		 */
		wl1251_mem_पढ़ो(wl, wl->cmd_box_addr, buf, buf_len);

		cmd_answer = buf;

		अगर (cmd_answer->header.status != CMD_STATUS_SUCCESS)
			wl1251_error("TEST command answer error: %d",
				     cmd_answer->header.status);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * पढ़ो acx from firmware
 *
 * @wl: wl काष्ठा
 * @id: acx id
 * @buf: buffer क्रम the response, including all headers, must work with dma
 * @len: length of buf
 */
पूर्णांक wl1251_cmd_पूर्णांकerrogate(काष्ठा wl1251 *wl, u16 id, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा acx_header *acx = buf;
	पूर्णांक ret;

	wl1251_debug(DEBUG_CMD, "cmd interrogate");

	acx->id = id;

	/* payload length, करोes not include any headers */
	acx->len = len - माप(*acx);

	ret = wl1251_cmd_send(wl, CMD_INTERROGATE, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1251_error("INTERROGATE command failed");
		जाओ out;
	पूर्ण

	/* the पूर्णांकerrogate command got in, we can पढ़ो the answer */
	wl1251_mem_पढ़ो(wl, wl->cmd_box_addr, buf, len);

	acx = buf;
	अगर (acx->cmd.status != CMD_STATUS_SUCCESS)
		wl1251_error("INTERROGATE command error: %d",
			     acx->cmd.status);

out:
	वापस ret;
पूर्ण

/**
 * ग_लिखो acx value to firmware
 *
 * @wl: wl काष्ठा
 * @id: acx id
 * @buf: buffer containing acx, including all headers, must work with dma
 * @len: length of buf
 */
पूर्णांक wl1251_cmd_configure(काष्ठा wl1251 *wl, u16 id, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा acx_header *acx = buf;
	पूर्णांक ret;

	wl1251_debug(DEBUG_CMD, "cmd configure");

	acx->id = id;

	/* payload length, करोes not include any headers */
	acx->len = len - माप(*acx);

	ret = wl1251_cmd_send(wl, CMD_CONFIGURE, acx, len);
	अगर (ret < 0) अणु
		wl1251_warning("CONFIGURE command NOK");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक wl1251_cmd_vbm(काष्ठा wl1251 *wl, u8 identity,
		   व्योम *biपंचांगap, u16 biपंचांगap_len, u8 biपंचांगap_control)
अणु
	काष्ठा wl1251_cmd_vbm_update *vbm;
	पूर्णांक ret;

	wl1251_debug(DEBUG_CMD, "cmd vbm");

	vbm = kzalloc(माप(*vbm), GFP_KERNEL);
	अगर (!vbm)
		वापस -ENOMEM;

	/* Count and period will be filled by the target */
	vbm->tim.biपंचांगap_ctrl = biपंचांगap_control;
	अगर (biपंचांगap_len > PARTIAL_VBM_MAX) अणु
		wl1251_warning("cmd vbm len is %d B, truncating to %d",
			       biपंचांगap_len, PARTIAL_VBM_MAX);
		biपंचांगap_len = PARTIAL_VBM_MAX;
	पूर्ण
	स_नकल(vbm->tim.pvb_field, biपंचांगap, biपंचांगap_len);
	vbm->tim.identity = identity;
	vbm->tim.length = biपंचांगap_len + 3;

	vbm->len = cpu_to_le16(biपंचांगap_len + 5);

	ret = wl1251_cmd_send(wl, CMD_VBM, vbm, माप(*vbm));
	अगर (ret < 0) अणु
		wl1251_error("VBM command failed");
		जाओ out;
	पूर्ण

out:
	kमुक्त(vbm);
	वापस ret;
पूर्ण

पूर्णांक wl1251_cmd_data_path_rx(काष्ठा wl1251 *wl, u8 channel, bool enable)
अणु
	काष्ठा cmd_enabledisable_path *cmd;
	पूर्णांक ret;
	u16 cmd_rx;

	wl1251_debug(DEBUG_CMD, "cmd data path");

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->channel = channel;

	अगर (enable)
		cmd_rx = CMD_ENABLE_RX;
	अन्यथा
		cmd_rx = CMD_DISABLE_RX;

	ret = wl1251_cmd_send(wl, cmd_rx, cmd, माप(*cmd));
	अगर (ret < 0) अणु
		wl1251_error("rx %s cmd for channel %d failed",
			     enable ? "start" : "stop", channel);
		जाओ out;
	पूर्ण

	wl1251_debug(DEBUG_BOOT, "rx %s cmd channel %d",
		     enable ? "start" : "stop", channel);

out:
	kमुक्त(cmd);
	वापस ret;
पूर्ण

पूर्णांक wl1251_cmd_data_path_tx(काष्ठा wl1251 *wl, u8 channel, bool enable)
अणु
	काष्ठा cmd_enabledisable_path *cmd;
	पूर्णांक ret;
	u16 cmd_tx;

	wl1251_debug(DEBUG_CMD, "cmd data path");

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->channel = channel;

	अगर (enable)
		cmd_tx = CMD_ENABLE_TX;
	अन्यथा
		cmd_tx = CMD_DISABLE_TX;

	ret = wl1251_cmd_send(wl, cmd_tx, cmd, माप(*cmd));
	अगर (ret < 0)
		wl1251_error("tx %s cmd for channel %d failed",
			     enable ? "start" : "stop", channel);
	अन्यथा
		wl1251_debug(DEBUG_BOOT, "tx %s cmd channel %d",
			     enable ? "start" : "stop", channel);

	kमुक्त(cmd);
	वापस ret;
पूर्ण

पूर्णांक wl1251_cmd_join(काष्ठा wl1251 *wl, u8 bss_type, u8 channel,
		    u16 beacon_पूर्णांकerval, u8 dtim_पूर्णांकerval)
अणु
	काष्ठा cmd_join *join;
	पूर्णांक ret, i;
	u8 *bssid;

	join = kzalloc(माप(*join), GFP_KERNEL);
	अगर (!join)
		वापस -ENOMEM;

	wl1251_debug(DEBUG_CMD, "cmd join%s ch %d %d/%d",
		     bss_type == BSS_TYPE_IBSS ? " ibss" : "",
		     channel, beacon_पूर्णांकerval, dtim_पूर्णांकerval);

	/* Reverse order BSSID */
	bssid = (u8 *) &join->bssid_lsb;
	क्रम (i = 0; i < ETH_ALEN; i++)
		bssid[i] = wl->bssid[ETH_ALEN - i - 1];

	join->rx_config_options = wl->rx_config;
	join->rx_filter_options = wl->rx_filter;

	join->basic_rate_set = RATE_MASK_1MBPS | RATE_MASK_2MBPS |
		RATE_MASK_5_5MBPS | RATE_MASK_11MBPS;

	join->beacon_पूर्णांकerval = beacon_पूर्णांकerval;
	join->dtim_पूर्णांकerval = dtim_पूर्णांकerval;
	join->bss_type = bss_type;
	join->channel = channel;
	join->ctrl = JOIN_CMD_CTRL_TX_FLUSH;

	ret = wl1251_cmd_send(wl, CMD_START_JOIN, join, माप(*join));
	अगर (ret < 0) अणु
		wl1251_error("failed to initiate cmd join");
		जाओ out;
	पूर्ण

out:
	kमुक्त(join);
	वापस ret;
पूर्ण

पूर्णांक wl1251_cmd_ps_mode(काष्ठा wl1251 *wl, u8 ps_mode)
अणु
	काष्ठा wl1251_cmd_ps_params *ps_params = शून्य;
	पूर्णांक ret = 0;

	wl1251_debug(DEBUG_CMD, "cmd set ps mode");

	ps_params = kzalloc(माप(*ps_params), GFP_KERNEL);
	अगर (!ps_params)
		वापस -ENOMEM;

	ps_params->ps_mode = ps_mode;
	ps_params->send_null_data = 1;
	ps_params->retries = 5;
	ps_params->hang_over_period = 128;
	ps_params->null_data_rate = 1; /* 1 Mbps */

	ret = wl1251_cmd_send(wl, CMD_SET_PS_MODE, ps_params,
			      माप(*ps_params));
	अगर (ret < 0) अणु
		wl1251_error("cmd set_ps_mode failed");
		जाओ out;
	पूर्ण

out:
	kमुक्त(ps_params);
	वापस ret;
पूर्ण

पूर्णांक wl1251_cmd_पढ़ो_memory(काष्ठा wl1251 *wl, u32 addr, व्योम *answer,
			   माप_प्रकार len)
अणु
	काष्ठा cmd_पढ़ो_ग_लिखो_memory *cmd;
	पूर्णांक ret = 0;

	wl1251_debug(DEBUG_CMD, "cmd read memory");

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	WARN_ON(len > MAX_READ_SIZE);
	len = min_t(माप_प्रकार, len, MAX_READ_SIZE);

	cmd->addr = addr;
	cmd->size = len;

	ret = wl1251_cmd_send(wl, CMD_READ_MEMORY, cmd, माप(*cmd));
	अगर (ret < 0) अणु
		wl1251_error("read memory command failed: %d", ret);
		जाओ out;
	पूर्ण

	/* the पढ़ो command got in, we can now पढ़ो the answer */
	wl1251_mem_पढ़ो(wl, wl->cmd_box_addr, cmd, माप(*cmd));

	अगर (cmd->header.status != CMD_STATUS_SUCCESS)
		wl1251_error("error in read command result: %d",
			     cmd->header.status);

	स_नकल(answer, cmd->value, len);

out:
	kमुक्त(cmd);
	वापस ret;
पूर्ण

पूर्णांक wl1251_cmd_ढाँचा_set(काष्ठा wl1251 *wl, u16 cmd_id,
			    व्योम *buf, माप_प्रकार buf_len)
अणु
	काष्ठा wl1251_cmd_packet_ढाँचा *cmd;
	माप_प्रकार cmd_len;
	पूर्णांक ret = 0;

	wl1251_debug(DEBUG_CMD, "cmd template %d", cmd_id);

	WARN_ON(buf_len > WL1251_MAX_TEMPLATE_SIZE);
	buf_len = min_t(माप_प्रकार, buf_len, WL1251_MAX_TEMPLATE_SIZE);
	cmd_len = ALIGN(माप(*cmd) + buf_len, 4);

	cmd = kzalloc(cmd_len, GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->size = cpu_to_le16(buf_len);

	अगर (buf)
		स_नकल(cmd->data, buf, buf_len);

	ret = wl1251_cmd_send(wl, cmd_id, cmd, cmd_len);
	अगर (ret < 0) अणु
		wl1251_warning("cmd set_template failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(cmd);
	वापस ret;
पूर्ण

पूर्णांक wl1251_cmd_scan(काष्ठा wl1251 *wl, u8 *ssid, माप_प्रकार ssid_len,
		    काष्ठा ieee80211_channel *channels[],
		    अचिन्हित पूर्णांक n_channels, अचिन्हित पूर्णांक n_probes)
अणु
	काष्ठा wl1251_cmd_scan *cmd;
	पूर्णांक i, ret = 0;

	wl1251_debug(DEBUG_CMD, "cmd scan channels %d", n_channels);

	WARN_ON(n_channels > SCAN_MAX_NUM_OF_CHANNELS);

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->params.rx_config_options = cpu_to_le32(CFG_RX_ALL_GOOD);
	cmd->params.rx_filter_options = cpu_to_le32(CFG_RX_PRSP_EN |
						    CFG_RX_MGMT_EN |
						    CFG_RX_BCN_EN);
	cmd->params.scan_options = 0;
	/*
	 * Use high priority scan when not associated to prevent fw issue
	 * causing never-ending scans (someबार 20+ minutes).
	 * Note: This bug may be caused by the fw's DTIM handling.
	 */
	अगर (is_zero_ether_addr(wl->bssid))
		cmd->params.scan_options |= cpu_to_le16(WL1251_SCAN_OPT_PRIORITY_HIGH);
	cmd->params.num_channels = n_channels;
	cmd->params.num_probe_requests = n_probes;
	cmd->params.tx_rate = cpu_to_le16(1 << 1); /* 2 Mbps */
	cmd->params.tid_trigger = 0;

	क्रम (i = 0; i < n_channels; i++) अणु
		cmd->channels[i].min_duration =
			cpu_to_le32(WL1251_SCAN_MIN_DURATION);
		cmd->channels[i].max_duration =
			cpu_to_le32(WL1251_SCAN_MAX_DURATION);
		स_रखो(&cmd->channels[i].bssid_lsb, 0xff, 4);
		स_रखो(&cmd->channels[i].bssid_msb, 0xff, 2);
		cmd->channels[i].early_termination = 0;
		cmd->channels[i].tx_घातer_att = 0;
		cmd->channels[i].channel = channels[i]->hw_value;
	पूर्ण

	cmd->params.ssid_len = ssid_len;
	अगर (ssid)
		स_नकल(cmd->params.ssid, ssid, ssid_len);

	ret = wl1251_cmd_send(wl, CMD_SCAN, cmd, माप(*cmd));
	अगर (ret < 0) अणु
		wl1251_error("cmd scan failed: %d", ret);
		जाओ out;
	पूर्ण

	wl1251_mem_पढ़ो(wl, wl->cmd_box_addr, cmd, माप(*cmd));

	अगर (cmd->header.status != CMD_STATUS_SUCCESS) अणु
		wl1251_error("cmd scan status wasn't success: %d",
			     cmd->header.status);
		ret = -EIO;
		जाओ out;
	पूर्ण

out:
	kमुक्त(cmd);
	वापस ret;
पूर्ण

पूर्णांक wl1251_cmd_trigger_scan_to(काष्ठा wl1251 *wl, u32 समयout)
अणु
	काष्ठा wl1251_cmd_trigger_scan_to *cmd;
	पूर्णांक ret;

	wl1251_debug(DEBUG_CMD, "cmd trigger scan to");

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->समयout = समयout;

	ret = wl1251_cmd_send(wl, CMD_TRIGGER_SCAN_TO, cmd, माप(*cmd));
	अगर (ret < 0) अणु
		wl1251_error("cmd trigger scan to failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(cmd);
	वापस ret;
पूर्ण
