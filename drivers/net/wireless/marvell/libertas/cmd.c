<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file contains the handling of command.
 * It prepares command and sends it to firmware when it is पढ़ोy.
 */

#समावेश <linux/hardirq.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/export.h>

#समावेश "decl.h"
#समावेश "cfg.h"
#समावेश "cmd.h"

#घोषणा CAL_NF(nf)		((s32)(-(s32)(nf)))
#घोषणा CAL_RSSI(snr, nf)	((s32)((s32)(snr) + CAL_NF(nf)))

/**
 * lbs_cmd_copyback - Simple callback that copies response back पूर्णांकo command
 *
 * @priv:	A poपूर्णांकer to &काष्ठा lbs_निजी काष्ठाure
 * @extra:	A poपूर्णांकer to the original command काष्ठाure क्रम which
 *		'resp' is a response
 * @resp:	A poपूर्णांकer to the command response
 *
 * वापसs:	0 on success, error on failure
 */
पूर्णांक lbs_cmd_copyback(काष्ठा lbs_निजी *priv, अचिन्हित दीर्घ extra,
		     काष्ठा cmd_header *resp)
अणु
	काष्ठा cmd_header *buf = (व्योम *)extra;
	uपूर्णांक16_t copy_len;

	copy_len = min(le16_to_cpu(buf->size), le16_to_cpu(resp->size));
	स_नकल(buf, resp, copy_len);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(lbs_cmd_copyback);

/**
 *  lbs_cmd_async_callback - Simple callback that ignores the result.
 *  Use this अगर you just want to send a command to the hardware, but करोn't
 *  care क्रम the result.
 *
 *  @priv:	ignored
 *  @extra:	ignored
 *  @resp:	ignored
 *
 *  वापसs:	0 क्रम success
 */
अटल पूर्णांक lbs_cmd_async_callback(काष्ठा lbs_निजी *priv, अचिन्हित दीर्घ extra,
		     काष्ठा cmd_header *resp)
अणु
	वापस 0;
पूर्ण


/**
 *  is_command_allowed_in_ps - tests अगर a command is allowed in Power Save mode
 *
 *  @cmd:	the command ID
 *
 *  वापसs:	1 अगर allowed, 0 अगर not allowed
 */
अटल u8 is_command_allowed_in_ps(u16 cmd)
अणु
	चयन (cmd) अणु
	हाल CMD_802_11_RSSI:
		वापस 1;
	हाल CMD_802_11_HOST_SLEEP_CFG:
		वापस 1;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *  lbs_update_hw_spec - Updates the hardware details like MAC address
 *  and regulatory region
 *
 *  @priv:	A poपूर्णांकer to &काष्ठा lbs_निजी काष्ठाure
 *
 *  वापसs:	0 on success, error on failure
 */
पूर्णांक lbs_update_hw_spec(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा cmd_ds_get_hw_spec cmd;
	पूर्णांक ret = -1;
	u32 i;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.hdr.size = cpu_to_le16(माप(cmd));
	स_नकल(cmd.permanentaddr, priv->current_addr, ETH_ALEN);
	ret = lbs_cmd_with_response(priv, CMD_GET_HW_SPEC, &cmd);
	अगर (ret)
		जाओ out;

	priv->fwcapinfo = le32_to_cpu(cmd.fwcapinfo);

	/* The firmware release is in an पूर्णांकeresting क्रमmat: the patch
	 * level is in the most signअगरicant nibble ... so fix that: */
	priv->fwrelease = le32_to_cpu(cmd.fwrelease);
	priv->fwrelease = (priv->fwrelease << 8) |
		(priv->fwrelease >> 24 & 0xff);

	/* Some firmware capabilities:
	 * CF card    firmware 5.0.16p0:   cap 0x00000303
	 * USB करोngle firmware 5.110.17p2: cap 0x00000303
	 */
	netdev_info(priv->dev, "%pM, fw %u.%u.%up%u, cap 0x%08x\n",
		cmd.permanentaddr,
		priv->fwrelease >> 24 & 0xff,
		priv->fwrelease >> 16 & 0xff,
		priv->fwrelease >>  8 & 0xff,
		priv->fwrelease       & 0xff,
		priv->fwcapinfo);
	lbs_deb_cmd("GET_HW_SPEC: hardware interface 0x%x, hardware spec 0x%04x\n",
		    cmd.hwअगरversion, cmd.version);

	/* Clamp region code to 8-bit since FW spec indicates that it should
	 * only ever be 8-bit, even though the field size is 16-bit.  Some firmware
	 * वापसs non-zero high 8 bits here.
	 *
	 * Firmware version 4.0.102 used in CF8381 has region code shअगरted.  We
	 * need to check क्रम this problem and handle it properly.
	 */
	अगर (MRVL_FW_MAJOR_REV(priv->fwrelease) == MRVL_FW_V4)
		priv->regioncode = (le16_to_cpu(cmd.regioncode) >> 8) & 0xFF;
	अन्यथा
		priv->regioncode = le16_to_cpu(cmd.regioncode) & 0xFF;

	क्रम (i = 0; i < MRVDRV_MAX_REGION_CODE; i++) अणु
		/* use the region code to search क्रम the index */
		अगर (priv->regioncode == lbs_region_code_to_index[i])
			अवरोध;
	पूर्ण

	/* अगर it's unidentअगरied region code, use the शेष (USA) */
	अगर (i >= MRVDRV_MAX_REGION_CODE) अणु
		priv->regioncode = 0x10;
		netdev_info(priv->dev,
			    "unidentified region code; using the default (USA)\n");
	पूर्ण

	अगर (priv->current_addr[0] == 0xff)
		स_हटाओ(priv->current_addr, cmd.permanentaddr, ETH_ALEN);

	अगर (!priv->copied_hwaddr) अणु
		स_नकल(priv->dev->dev_addr, priv->current_addr, ETH_ALEN);
		अगर (priv->mesh_dev)
			स_नकल(priv->mesh_dev->dev_addr,
				priv->current_addr, ETH_ALEN);
		priv->copied_hwaddr = 1;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक lbs_ret_host_sleep_cfg(काष्ठा lbs_निजी *priv, अचिन्हित दीर्घ dummy,
			काष्ठा cmd_header *resp)
अणु
	अगर (priv->is_host_sleep_activated) अणु
		priv->is_host_sleep_configured = 0;
		अगर (priv->psstate == PS_STATE_FULL_POWER) अणु
			priv->is_host_sleep_activated = 0;
			wake_up_पूर्णांकerruptible(&priv->host_sleep_q);
		पूर्ण
	पूर्ण अन्यथा अणु
		priv->is_host_sleep_configured = 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक lbs_host_sleep_cfg(काष्ठा lbs_निजी *priv, uपूर्णांक32_t criteria,
		काष्ठा wol_config *p_wol_config)
अणु
	काष्ठा cmd_ds_host_sleep cmd_config;
	पूर्णांक ret;

	/*
	 * Certain firmware versions करो not support EHS_REMOVE_WAKEUP command
	 * and the card will वापस a failure.  Since we need to be
	 * able to reset the mask, in those हालs we set a 0 mask instead.
	 */
	अगर (criteria == EHS_REMOVE_WAKEUP && !priv->ehs_हटाओ_supported)
		criteria = 0;

	cmd_config.hdr.size = cpu_to_le16(माप(cmd_config));
	cmd_config.criteria = cpu_to_le32(criteria);
	cmd_config.gpio = priv->wol_gpio;
	cmd_config.gap = priv->wol_gap;

	अगर (p_wol_config != शून्य)
		स_नकल((uपूर्णांक8_t *)&cmd_config.wol_conf, (uपूर्णांक8_t *)p_wol_config,
				माप(काष्ठा wol_config));
	अन्यथा
		cmd_config.wol_conf.action = CMD_ACT_ACTION_NONE;

	ret = __lbs_cmd(priv, CMD_802_11_HOST_SLEEP_CFG, &cmd_config.hdr,
			le16_to_cpu(cmd_config.hdr.size),
			lbs_ret_host_sleep_cfg, 0);
	अगर (!ret) अणु
		अगर (p_wol_config)
			स_नकल((uपूर्णांक8_t *) p_wol_config,
					(uपूर्णांक8_t *)&cmd_config.wol_conf,
					माप(काष्ठा wol_config));
	पूर्ण अन्यथा अणु
		netdev_info(priv->dev, "HOST_SLEEP_CFG failed %d\n", ret);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lbs_host_sleep_cfg);

/**
 *  lbs_set_ps_mode - Sets the Power Save mode
 *
 *  @priv:	A poपूर्णांकer to &काष्ठा lbs_निजी काष्ठाure
 *  @cmd_action: The Power Save operation (PS_MODE_ACTION_ENTER_PS or
 *                         PS_MODE_ACTION_EXIT_PS)
 *  @block:	Whether to block on a response or not
 *
 *  वापसs:	0 on success, error on failure
 */
पूर्णांक lbs_set_ps_mode(काष्ठा lbs_निजी *priv, u16 cmd_action, bool block)
अणु
	काष्ठा cmd_ds_802_11_ps_mode cmd;
	पूर्णांक ret = 0;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(cmd_action);

	अगर (cmd_action == PS_MODE_ACTION_ENTER_PS) अणु
		lbs_deb_cmd("PS_MODE: action ENTER_PS\n");
		cmd.multipledtim = cpu_to_le16(1);  /* Default DTIM multiple */
	पूर्ण अन्यथा अगर (cmd_action == PS_MODE_ACTION_EXIT_PS) अणु
		lbs_deb_cmd("PS_MODE: action EXIT_PS\n");
	पूर्ण अन्यथा अणु
		/* We करोn't handle CONFIRM_SLEEP here because it needs to
		 * be fastpathed to the firmware.
		 */
		lbs_deb_cmd("PS_MODE: unknown action 0x%X\n", cmd_action);
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (block)
		ret = lbs_cmd_with_response(priv, CMD_802_11_PS_MODE, &cmd);
	अन्यथा
		lbs_cmd_async(priv, CMD_802_11_PS_MODE, &cmd.hdr, माप (cmd));

out:
	वापस ret;
पूर्ण

पूर्णांक lbs_cmd_802_11_sleep_params(काष्ठा lbs_निजी *priv, uपूर्णांक16_t cmd_action,
				काष्ठा sleep_params *sp)
अणु
	काष्ठा cmd_ds_802_11_sleep_params cmd;
	पूर्णांक ret;

	अगर (cmd_action == CMD_ACT_GET) अणु
		स_रखो(&cmd, 0, माप(cmd));
	पूर्ण अन्यथा अणु
		cmd.error = cpu_to_le16(sp->sp_error);
		cmd.offset = cpu_to_le16(sp->sp_offset);
		cmd.stableसमय = cpu_to_le16(sp->sp_stableसमय);
		cmd.calcontrol = sp->sp_calcontrol;
		cmd.बाह्यalsleepclk = sp->sp_extsleepclk;
		cmd.reserved = cpu_to_le16(sp->sp_reserved);
	पूर्ण
	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(cmd_action);

	ret = lbs_cmd_with_response(priv, CMD_802_11_SLEEP_PARAMS, &cmd);

	अगर (!ret) अणु
		lbs_deb_cmd("error 0x%x, offset 0x%x, stabletime 0x%x, "
			    "calcontrol 0x%x extsleepclk 0x%x\n",
			    le16_to_cpu(cmd.error), le16_to_cpu(cmd.offset),
			    le16_to_cpu(cmd.stableसमय), cmd.calcontrol,
			    cmd.बाह्यalsleepclk);

		sp->sp_error = le16_to_cpu(cmd.error);
		sp->sp_offset = le16_to_cpu(cmd.offset);
		sp->sp_stableसमय = le16_to_cpu(cmd.stableसमय);
		sp->sp_calcontrol = cmd.calcontrol;
		sp->sp_extsleepclk = cmd.बाह्यalsleepclk;
		sp->sp_reserved = le16_to_cpu(cmd.reserved);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक lbs_रुको_क्रम_ds_awake(काष्ठा lbs_निजी *priv)
अणु
	पूर्णांक ret = 0;

	अगर (priv->is_deep_sleep) अणु
		अगर (!रुको_event_पूर्णांकerruptible_समयout(priv->ds_awake_q,
					!priv->is_deep_sleep, (10 * HZ))) अणु
			netdev_err(priv->dev, "ds_awake_q: timer expired\n");
			ret = -1;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक lbs_set_deep_sleep(काष्ठा lbs_निजी *priv, पूर्णांक deep_sleep)
अणु
	पूर्णांक ret =  0;

	अगर (deep_sleep) अणु
		अगर (priv->is_deep_sleep != 1) अणु
			lbs_deb_cmd("deep sleep: sleep\n");
			BUG_ON(!priv->enter_deep_sleep);
			ret = priv->enter_deep_sleep(priv);
			अगर (!ret) अणु
				netअगर_stop_queue(priv->dev);
				netअगर_carrier_off(priv->dev);
			पूर्ण
		पूर्ण अन्यथा अणु
			netdev_err(priv->dev, "deep sleep: already enabled\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (priv->is_deep_sleep) अणु
			lbs_deb_cmd("deep sleep: wakeup\n");
			BUG_ON(!priv->निकास_deep_sleep);
			ret = priv->निकास_deep_sleep(priv);
			अगर (!ret) अणु
				ret = lbs_रुको_क्रम_ds_awake(priv);
				अगर (ret)
					netdev_err(priv->dev,
						   "deep sleep: wakeup failed\n");
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक lbs_ret_host_sleep_activate(काष्ठा lbs_निजी *priv,
		अचिन्हित दीर्घ dummy,
		काष्ठा cmd_header *cmd)
अणु
	priv->is_host_sleep_activated = 1;
	wake_up_पूर्णांकerruptible(&priv->host_sleep_q);

	वापस 0;
पूर्ण

पूर्णांक lbs_set_host_sleep(काष्ठा lbs_निजी *priv, पूर्णांक host_sleep)
अणु
	काष्ठा cmd_header cmd;
	पूर्णांक ret = 0;
	uपूर्णांक32_t criteria = EHS_REMOVE_WAKEUP;

	अगर (host_sleep) अणु
		अगर (priv->is_host_sleep_activated != 1) अणु
			स_रखो(&cmd, 0, माप(cmd));
			ret = lbs_host_sleep_cfg(priv, priv->wol_criteria,
					(काष्ठा wol_config *)शून्य);
			अगर (ret) अणु
				netdev_info(priv->dev,
					    "Host sleep configuration failed: %d\n",
					    ret);
				वापस ret;
			पूर्ण
			अगर (priv->psstate == PS_STATE_FULL_POWER) अणु
				ret = __lbs_cmd(priv,
						CMD_802_11_HOST_SLEEP_ACTIVATE,
						&cmd,
						माप(cmd),
						lbs_ret_host_sleep_activate, 0);
				अगर (ret)
					netdev_info(priv->dev,
						    "HOST_SLEEP_ACTIVATE failed: %d\n",
						    ret);
			पूर्ण

			अगर (!रुको_event_पूर्णांकerruptible_समयout(
						priv->host_sleep_q,
						priv->is_host_sleep_activated,
						(10 * HZ))) अणु
				netdev_err(priv->dev,
					   "host_sleep_q: timer expired\n");
				ret = -1;
			पूर्ण
		पूर्ण अन्यथा अणु
			netdev_err(priv->dev, "host sleep: already enabled\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (priv->is_host_sleep_activated)
			ret = lbs_host_sleep_cfg(priv, criteria,
					(काष्ठा wol_config *)शून्य);
	पूर्ण

	वापस ret;
पूर्ण

/**
 *  lbs_set_snmp_mib - Set an SNMP MIB value
 *
 *  @priv:	A poपूर्णांकer to &काष्ठा lbs_निजी काष्ठाure
 *  @oid:	The OID to set in the firmware
 *  @val:	Value to set the OID to
 *
 *  वापसs: 	   	0 on success, error on failure
 */
पूर्णांक lbs_set_snmp_mib(काष्ठा lbs_निजी *priv, u32 oid, u16 val)
अणु
	काष्ठा cmd_ds_802_11_snmp_mib cmd;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप (cmd));
	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);
	cmd.oid = cpu_to_le16((u16) oid);

	चयन (oid) अणु
	हाल SNMP_MIB_OID_BSS_TYPE:
		cmd.bufsize = cpu_to_le16(माप(u8));
		cmd.value[0] = val;
		अवरोध;
	हाल SNMP_MIB_OID_11D_ENABLE:
	हाल SNMP_MIB_OID_FRAG_THRESHOLD:
	हाल SNMP_MIB_OID_RTS_THRESHOLD:
	हाल SNMP_MIB_OID_SHORT_RETRY_LIMIT:
	हाल SNMP_MIB_OID_LONG_RETRY_LIMIT:
		cmd.bufsize = cpu_to_le16(माप(u16));
		*((__le16 *)(&cmd.value)) = cpu_to_le16(val);
		अवरोध;
	शेष:
		lbs_deb_cmd("SNMP_CMD: (set) unhandled OID 0x%x\n", oid);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	lbs_deb_cmd("SNMP_CMD: (set) oid 0x%x, oid size 0x%x, value 0x%x\n",
		    le16_to_cpu(cmd.oid), le16_to_cpu(cmd.bufsize), val);

	ret = lbs_cmd_with_response(priv, CMD_802_11_SNMP_MIB, &cmd);

out:
	वापस ret;
पूर्ण

/**
 *  lbs_get_snmp_mib - Get an SNMP MIB value
 *
 *  @priv:	A poपूर्णांकer to &काष्ठा lbs_निजी काष्ठाure
 *  @oid:	The OID to retrieve from the firmware
 *  @out_val:	Location क्रम the वापसed value
 *
 *  वापसs:	0 on success, error on failure
 */
पूर्णांक lbs_get_snmp_mib(काष्ठा lbs_निजी *priv, u32 oid, u16 *out_val)
अणु
	काष्ठा cmd_ds_802_11_snmp_mib cmd;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप (cmd));
	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_GET);
	cmd.oid = cpu_to_le16(oid);

	ret = lbs_cmd_with_response(priv, CMD_802_11_SNMP_MIB, &cmd);
	अगर (ret)
		जाओ out;

	चयन (le16_to_cpu(cmd.bufsize)) अणु
	हाल माप(u8):
		*out_val = cmd.value[0];
		अवरोध;
	हाल माप(u16):
		*out_val = le16_to_cpu(*((__le16 *)(&cmd.value)));
		अवरोध;
	शेष:
		lbs_deb_cmd("SNMP_CMD: (get) unhandled OID 0x%x size %d\n",
		            oid, le16_to_cpu(cmd.bufsize));
		अवरोध;
	पूर्ण

out:
	वापस ret;
पूर्ण

/**
 *  lbs_get_tx_घातer - Get the min, max, and current TX घातer
 *
 *  @priv:	A poपूर्णांकer to &काष्ठा lbs_निजी काष्ठाure
 *  @curlevel:	Current घातer level in dBm
 *  @minlevel:	Minimum supported घातer level in dBm (optional)
 *  @maxlevel:	Maximum supported घातer level in dBm (optional)
 *
 *  वापसs:	0 on success, error on failure
 */
पूर्णांक lbs_get_tx_घातer(काष्ठा lbs_निजी *priv, s16 *curlevel, s16 *minlevel,
		     s16 *maxlevel)
अणु
	काष्ठा cmd_ds_802_11_rf_tx_घातer cmd;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_GET);

	ret = lbs_cmd_with_response(priv, CMD_802_11_RF_TX_POWER, &cmd);
	अगर (ret == 0) अणु
		*curlevel = le16_to_cpu(cmd.curlevel);
		अगर (minlevel)
			*minlevel = cmd.minlevel;
		अगर (maxlevel)
			*maxlevel = cmd.maxlevel;
	पूर्ण

	वापस ret;
पूर्ण

/**
 *  lbs_set_tx_घातer - Set the TX घातer
 *
 *  @priv:	A poपूर्णांकer to &काष्ठा lbs_निजी काष्ठाure
 *  @dbm:	The desired घातer level in dBm
 *
 *  वापसs: 	   	0 on success, error on failure
 */
पूर्णांक lbs_set_tx_घातer(काष्ठा lbs_निजी *priv, s16 dbm)
अणु
	काष्ठा cmd_ds_802_11_rf_tx_घातer cmd;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);
	cmd.curlevel = cpu_to_le16(dbm);

	lbs_deb_cmd("SET_RF_TX_POWER: %d dBm\n", dbm);

	ret = lbs_cmd_with_response(priv, CMD_802_11_RF_TX_POWER, &cmd);

	वापस ret;
पूर्ण

/**
 *  lbs_set_monitor_mode - Enable or disable monitor mode
 *  (only implemented on OLPC usb8388 FW)
 *
 *  @priv:	A poपूर्णांकer to &काष्ठा lbs_निजी काष्ठाure
 *  @enable:	1 to enable monitor mode, 0 to disable
 *
 *  वापसs:	0 on success, error on failure
 */
पूर्णांक lbs_set_monitor_mode(काष्ठा lbs_निजी *priv, पूर्णांक enable)
अणु
	काष्ठा cmd_ds_802_11_monitor_mode cmd;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);
	अगर (enable)
		cmd.mode = cpu_to_le16(0x1);

	lbs_deb_cmd("SET_MONITOR_MODE: %d\n", enable);

	ret = lbs_cmd_with_response(priv, CMD_802_11_MONITOR_MODE, &cmd);
	अगर (ret == 0) अणु
		priv->dev->type = enable ? ARPHRD_IEEE80211_RADIOTAP :
						ARPHRD_ETHER;
	पूर्ण

	वापस ret;
पूर्ण

/**
 *  lbs_get_channel - Get the radio channel
 *
 *  @priv:	A poपूर्णांकer to &काष्ठा lbs_निजी काष्ठाure
 *
 *  वापसs:	The channel on success, error on failure
 */
अटल पूर्णांक lbs_get_channel(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा cmd_ds_802_11_rf_channel cmd;
	पूर्णांक ret = 0;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(CMD_OPT_802_11_RF_CHANNEL_GET);

	ret = lbs_cmd_with_response(priv, CMD_802_11_RF_CHANNEL, &cmd);
	अगर (ret)
		जाओ out;

	ret = le16_to_cpu(cmd.channel);
	lbs_deb_cmd("current radio channel is %d\n", ret);

out:
	वापस ret;
पूर्ण

पूर्णांक lbs_update_channel(काष्ठा lbs_निजी *priv)
अणु
	पूर्णांक ret;

	/* the channel in f/w could be out of sync; get the current channel */
	ret = lbs_get_channel(priv);
	अगर (ret > 0) अणु
		priv->channel = ret;
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

/**
 *  lbs_set_channel - Set the radio channel
 *
 *  @priv:	A poपूर्णांकer to &काष्ठा lbs_निजी काष्ठाure
 *  @channel:	The desired channel, or 0 to clear a locked channel
 *
 *  वापसs:	0 on success, error on failure
 */
पूर्णांक lbs_set_channel(काष्ठा lbs_निजी *priv, u8 channel)
अणु
	काष्ठा cmd_ds_802_11_rf_channel cmd;
#अगर_घोषित DEBUG
	u8 old_channel = priv->channel;
#पूर्ण_अगर
	पूर्णांक ret = 0;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(CMD_OPT_802_11_RF_CHANNEL_SET);
	cmd.channel = cpu_to_le16(channel);

	ret = lbs_cmd_with_response(priv, CMD_802_11_RF_CHANNEL, &cmd);
	अगर (ret)
		जाओ out;

	priv->channel = (uपूर्णांक8_t) le16_to_cpu(cmd.channel);
	lbs_deb_cmd("channel switch from %d to %d\n", old_channel,
		priv->channel);

out:
	वापस ret;
पूर्ण

/**
 * lbs_get_rssi - Get current RSSI and noise न्यूनमान
 *
 * @priv:	A poपूर्णांकer to &काष्ठा lbs_निजी काष्ठाure
 * @rssi:	On successful वापस, संकेत level in mBm
 * @nf:		On successful वापस, Noise न्यूनमान
 *
 * वापसs:	The channel on success, error on failure
 */
पूर्णांक lbs_get_rssi(काष्ठा lbs_निजी *priv, s8 *rssi, s8 *nf)
अणु
	काष्ठा cmd_ds_802_11_rssi cmd;
	पूर्णांक ret = 0;

	BUG_ON(rssi == शून्य);
	BUG_ON(nf == शून्य);

	स_रखो(&cmd, 0, माप(cmd));
	cmd.hdr.size = cpu_to_le16(माप(cmd));
	/* Average SNR over last 8 beacons */
	cmd.n_or_snr = cpu_to_le16(8);

	ret = lbs_cmd_with_response(priv, CMD_802_11_RSSI, &cmd);
	अगर (ret == 0) अणु
		*nf = CAL_NF(le16_to_cpu(cmd.nf));
		*rssi = CAL_RSSI(le16_to_cpu(cmd.n_or_snr), le16_to_cpu(cmd.nf));
	पूर्ण

	वापस ret;
पूर्ण

/**
 *  lbs_set_11d_करोमुख्य_info - Send regulatory and 802.11d करोमुख्य inक्रमmation
 *  to the firmware
 *
 *  @priv:	poपूर्णांकer to &काष्ठा lbs_निजी
 *
 *  वापसs:	0 on success, error code on failure
*/
पूर्णांक lbs_set_11d_करोमुख्य_info(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा wiphy *wiphy = priv->wdev->wiphy;
	काष्ठा ieee80211_supported_band **bands = wiphy->bands;
	काष्ठा cmd_ds_802_11d_करोमुख्य_info cmd;
	काष्ठा mrvl_ie_करोमुख्य_param_set *करोमुख्य = &cmd.करोमुख्य;
	काष्ठा ieee80211_country_ie_triplet *t;
	क्रमागत nl80211_band band;
	काष्ठा ieee80211_channel *ch;
	u8 num_triplet = 0;
	u8 num_parsed_chan = 0;
	u8 first_channel = 0, next_chan = 0, max_pwr = 0;
	u8 i, flag = 0;
	माप_प्रकार triplet_size;
	पूर्णांक ret = 0;

	अगर (!priv->country_code[0])
		जाओ out;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);

	lbs_deb_11d("Setting country code '%c%c'\n",
		    priv->country_code[0], priv->country_code[1]);

	करोमुख्य->header.type = cpu_to_le16(TLV_TYPE_DOMAIN);

	/* Set country code */
	करोमुख्य->country_code[0] = priv->country_code[0];
	करोमुख्य->country_code[1] = priv->country_code[1];
	करोमुख्य->country_code[2] = ' ';

	/* Now set up the channel triplets; firmware is somewhat picky here
	 * and करोesn't validate channel numbers and spans; hence it would
	 * पूर्णांकerpret a triplet of (36, 4, 20) as channels 36, 37, 38, 39.  Since
	 * the last 3 aren't valid channels, the driver is responsible क्रम
	 * splitting that up पूर्णांकo 4 triplet pairs of (36, 1, 20) + (40, 1, 20)
	 * etc.
	 */
	क्रम (band = 0;
	     (band < NUM_NL80211_BANDS) && (num_triplet < MAX_11D_TRIPLETS);
	     band++) अणु

		अगर (!bands[band])
			जारी;

		क्रम (i = 0;
		     (i < bands[band]->n_channels) && (num_triplet < MAX_11D_TRIPLETS);
		     i++) अणु
			ch = &bands[band]->channels[i];
			अगर (ch->flags & IEEE80211_CHAN_DISABLED)
				जारी;

			अगर (!flag) अणु
				flag = 1;
				next_chan = first_channel = (u32) ch->hw_value;
				max_pwr = ch->max_घातer;
				num_parsed_chan = 1;
				जारी;
			पूर्ण

			अगर ((ch->hw_value == next_chan + 1) &&
					(ch->max_घातer == max_pwr)) अणु
				/* Consolidate adjacent channels */
				next_chan++;
				num_parsed_chan++;
			पूर्ण अन्यथा अणु
				/* Add this triplet */
				lbs_deb_11d("11D triplet (%d, %d, %d)\n",
					first_channel, num_parsed_chan,
					max_pwr);
				t = &करोमुख्य->triplet[num_triplet];
				t->chans.first_channel = first_channel;
				t->chans.num_channels = num_parsed_chan;
				t->chans.max_घातer = max_pwr;
				num_triplet++;
				flag = 0;
			पूर्ण
		पूर्ण

		अगर (flag) अणु
			/* Add last triplet */
			lbs_deb_11d("11D triplet (%d, %d, %d)\n", first_channel,
				num_parsed_chan, max_pwr);
			t = &करोमुख्य->triplet[num_triplet];
			t->chans.first_channel = first_channel;
			t->chans.num_channels = num_parsed_chan;
			t->chans.max_घातer = max_pwr;
			num_triplet++;
		पूर्ण
	पूर्ण

	lbs_deb_11d("# triplets %d\n", num_triplet);

	/* Set command header sizes */
	triplet_size = num_triplet * माप(काष्ठा ieee80211_country_ie_triplet);
	करोमुख्य->header.len = cpu_to_le16(माप(करोमुख्य->country_code) +
					triplet_size);

	lbs_deb_hex(LBS_DEB_11D, "802.11D domain param set",
			(u8 *) &cmd.करोमुख्य.country_code,
			le16_to_cpu(करोमुख्य->header.len));

	cmd.hdr.size = cpu_to_le16(माप(cmd.hdr) +
				   माप(cmd.action) +
				   माप(cmd.करोमुख्य.header) +
				   माप(cmd.करोमुख्य.country_code) +
				   triplet_size);

	ret = lbs_cmd_with_response(priv, CMD_802_11D_DOMAIN_INFO, &cmd);

out:
	वापस ret;
पूर्ण

/**
 *  lbs_get_reg - Read a MAC, Baseband, or RF रेजिस्टर
 *
 *  @priv:	poपूर्णांकer to &काष्ठा lbs_निजी
 *  @reg:	रेजिस्टर command, one of CMD_MAC_REG_ACCESS,
 *		CMD_BBP_REG_ACCESS, or CMD_RF_REG_ACCESS
 *  @offset:	byte offset of the रेजिस्टर to get
 *  @value:	on success, the value of the रेजिस्टर at 'offset'
 *
 *  वापसs:	0 on success, error code on failure
*/
पूर्णांक lbs_get_reg(काष्ठा lbs_निजी *priv, u16 reg, u16 offset, u32 *value)
अणु
	काष्ठा cmd_ds_reg_access cmd;
	पूर्णांक ret = 0;

	BUG_ON(value == शून्य);

	स_रखो(&cmd, 0, माप(cmd));
	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_GET);
	cmd.offset = cpu_to_le16(offset);

	अगर (reg != CMD_MAC_REG_ACCESS &&
	    reg != CMD_BBP_REG_ACCESS &&
	    reg != CMD_RF_REG_ACCESS) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = lbs_cmd_with_response(priv, reg, &cmd);
	अगर (!ret) अणु
		अगर (reg == CMD_BBP_REG_ACCESS || reg == CMD_RF_REG_ACCESS)
			*value = cmd.value.bbp_rf;
		अन्यथा अगर (reg == CMD_MAC_REG_ACCESS)
			*value = le32_to_cpu(cmd.value.mac);
	पूर्ण

out:
	वापस ret;
पूर्ण

/**
 *  lbs_set_reg - Write a MAC, Baseband, or RF रेजिस्टर
 *
 *  @priv:	poपूर्णांकer to &काष्ठा lbs_निजी
 *  @reg:	रेजिस्टर command, one of CMD_MAC_REG_ACCESS,
 *		CMD_BBP_REG_ACCESS, or CMD_RF_REG_ACCESS
 *  @offset:	byte offset of the रेजिस्टर to set
 *  @value:	the value to ग_लिखो to the रेजिस्टर at 'offset'
 *
 *  वापसs:	0 on success, error code on failure
*/
पूर्णांक lbs_set_reg(काष्ठा lbs_निजी *priv, u16 reg, u16 offset, u32 value)
अणु
	काष्ठा cmd_ds_reg_access cmd;
	पूर्णांक ret = 0;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);
	cmd.offset = cpu_to_le16(offset);

	अगर (reg == CMD_BBP_REG_ACCESS || reg == CMD_RF_REG_ACCESS)
		cmd.value.bbp_rf = (u8) (value & 0xFF);
	अन्यथा अगर (reg == CMD_MAC_REG_ACCESS)
		cmd.value.mac = cpu_to_le32(value);
	अन्यथा अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = lbs_cmd_with_response(priv, reg, &cmd);

out:
	वापस ret;
पूर्ण

अटल व्योम lbs_queue_cmd(काष्ठा lbs_निजी *priv,
			  काष्ठा cmd_ctrl_node *cmdnode)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक addtail = 1;

	अगर (!cmdnode) अणु
		lbs_deb_host("QUEUE_CMD: cmdnode is NULL\n");
		वापस;
	पूर्ण
	अगर (!cmdnode->cmdbuf->size) अणु
		lbs_deb_host("DNLD_CMD: cmd size is zero\n");
		वापस;
	पूर्ण
	cmdnode->result = 0;

	/* Exit_PS command needs to be queued in the header always. */
	अगर (le16_to_cpu(cmdnode->cmdbuf->command) == CMD_802_11_PS_MODE) अणु
		काष्ठा cmd_ds_802_11_ps_mode *psm = (व्योम *)cmdnode->cmdbuf;

		अगर (psm->action == cpu_to_le16(PS_MODE_ACTION_EXIT_PS)) अणु
			अगर (priv->psstate != PS_STATE_FULL_POWER)
				addtail = 0;
		पूर्ण
	पूर्ण

	अगर (le16_to_cpu(cmdnode->cmdbuf->command) == CMD_802_11_WAKEUP_CONFIRM)
		addtail = 0;

	spin_lock_irqsave(&priv->driver_lock, flags);

	अगर (addtail)
		list_add_tail(&cmdnode->list, &priv->cmdpendingq);
	अन्यथा
		list_add(&cmdnode->list, &priv->cmdpendingq);

	spin_unlock_irqrestore(&priv->driver_lock, flags);

	lbs_deb_host("QUEUE_CMD: inserted command 0x%04x into cmdpendingq\n",
		     le16_to_cpu(cmdnode->cmdbuf->command));
पूर्ण

अटल व्योम lbs_submit_command(काष्ठा lbs_निजी *priv,
			       काष्ठा cmd_ctrl_node *cmdnode)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा cmd_header *cmd;
	uपूर्णांक16_t cmdsize;
	uपूर्णांक16_t command;
	पूर्णांक समयo = 3 * HZ;
	पूर्णांक ret;

	cmd = cmdnode->cmdbuf;

	spin_lock_irqsave(&priv->driver_lock, flags);
	priv->seqnum++;
	cmd->seqnum = cpu_to_le16(priv->seqnum);
	priv->cur_cmd = cmdnode;
	spin_unlock_irqrestore(&priv->driver_lock, flags);

	cmdsize = le16_to_cpu(cmd->size);
	command = le16_to_cpu(cmd->command);

	/* These commands take दीर्घer */
	अगर (command == CMD_802_11_SCAN || command == CMD_802_11_ASSOCIATE)
		समयo = 5 * HZ;

	lbs_deb_cmd("DNLD_CMD: command 0x%04x, seq %d, size %d\n",
		     command, le16_to_cpu(cmd->seqnum), cmdsize);
	lbs_deb_hex(LBS_DEB_CMD, "DNLD_CMD", (व्योम *) cmdnode->cmdbuf, cmdsize);

	ret = priv->hw_host_to_card(priv, MVMS_CMD, (u8 *) cmd, cmdsize);

	अगर (ret) अणु
		netdev_info(priv->dev, "DNLD_CMD: hw_host_to_card failed: %d\n",
			    ret);
		/* Reset dnld state machine, report failure */
		priv->dnld_sent = DNLD_RES_RECEIVED;
		lbs_complete_command(priv, cmdnode, ret);
	पूर्ण

	अगर (command == CMD_802_11_DEEP_SLEEP) अणु
		अगर (priv->is_स्वतः_deep_sleep_enabled) अणु
			priv->wakeup_dev_required = 1;
			priv->dnld_sent = 0;
		पूर्ण
		priv->is_deep_sleep = 1;
		lbs_complete_command(priv, cmdnode, 0);
	पूर्ण अन्यथा अणु
		/* Setup the समयr after transmit command */
		mod_समयr(&priv->command_समयr, jअगरfies + समयo);
	पूर्ण
पूर्ण

/*
 *  This function inserts command node to cmdमुक्तq
 *  after cleans it. Requires priv->driver_lock held.
 */
अटल व्योम __lbs_cleanup_and_insert_cmd(काष्ठा lbs_निजी *priv,
					 काष्ठा cmd_ctrl_node *cmdnode)
अणु
	अगर (!cmdnode)
		वापस;

	cmdnode->callback = शून्य;
	cmdnode->callback_arg = 0;

	स_रखो(cmdnode->cmdbuf, 0, LBS_CMD_BUFFER_SIZE);

	list_add_tail(&cmdnode->list, &priv->cmdमुक्तq);
पूर्ण

अटल व्योम lbs_cleanup_and_insert_cmd(काष्ठा lbs_निजी *priv,
	काष्ठा cmd_ctrl_node *ptempcmd)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->driver_lock, flags);
	__lbs_cleanup_and_insert_cmd(priv, ptempcmd);
	spin_unlock_irqrestore(&priv->driver_lock, flags);
पूर्ण

व्योम __lbs_complete_command(काष्ठा lbs_निजी *priv, काष्ठा cmd_ctrl_node *cmd,
			    पूर्णांक result)
अणु
	/*
	 * Normally, commands are हटाओd from cmdpendingq beक्रमe being
	 * submitted. However, we can arrive here on alternative codepaths
	 * where the command is still pending. Make sure the command really
	 * isn't part of a list at this poपूर्णांक.
	 */
	list_del_init(&cmd->list);

	cmd->result = result;
	cmd->cmdरुकोqwoken = 1;
	wake_up(&cmd->cmdरुको_q);

	अगर (!cmd->callback || cmd->callback == lbs_cmd_async_callback)
		__lbs_cleanup_and_insert_cmd(priv, cmd);
	priv->cur_cmd = शून्य;
	wake_up(&priv->रुकोq);
पूर्ण

व्योम lbs_complete_command(काष्ठा lbs_निजी *priv, काष्ठा cmd_ctrl_node *cmd,
			  पूर्णांक result)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&priv->driver_lock, flags);
	__lbs_complete_command(priv, cmd, result);
	spin_unlock_irqrestore(&priv->driver_lock, flags);
पूर्ण

पूर्णांक lbs_set_radio(काष्ठा lbs_निजी *priv, u8 preamble, u8 radio_on)
अणु
	काष्ठा cmd_ds_802_11_radio_control cmd;
	पूर्णांक ret = -EINVAL;

	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);
	cmd.control = 0;

	/* Only v8 and below support setting the preamble */
	अगर (priv->fwrelease < 0x09000000) अणु
		चयन (preamble) अणु
		हाल RADIO_PREAMBLE_SHORT:
		हाल RADIO_PREAMBLE_AUTO:
		हाल RADIO_PREAMBLE_LONG:
			cmd.control = cpu_to_le16(preamble);
			अवरोध;
		शेष:
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (radio_on)
		cmd.control |= cpu_to_le16(0x1);
	अन्यथा अणु
		cmd.control &= cpu_to_le16(~0x1);
		priv->txघातer_cur = 0;
	पूर्ण

	lbs_deb_cmd("RADIO_CONTROL: radio %s, preamble %d\n",
		    radio_on ? "ON" : "OFF", preamble);

	priv->radio_on = radio_on;

	ret = lbs_cmd_with_response(priv, CMD_802_11_RADIO_CONTROL, &cmd);

out:
	वापस ret;
पूर्ण

व्योम lbs_set_mac_control(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा cmd_ds_mac_control cmd;

	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(priv->mac_control);
	cmd.reserved = 0;

	lbs_cmd_async(priv, CMD_MAC_CONTROL, &cmd.hdr, माप(cmd));
पूर्ण

पूर्णांक lbs_set_mac_control_sync(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा cmd_ds_mac_control cmd;
	पूर्णांक ret = 0;

	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(priv->mac_control);
	cmd.reserved = 0;
	ret = lbs_cmd_with_response(priv, CMD_MAC_CONTROL, &cmd);

	वापस ret;
पूर्ण

/**
 *  lbs_allocate_cmd_buffer - allocates the command buffer and links
 *  it to command मुक्त queue
 *
 *  @priv:	A poपूर्णांकer to &काष्ठा lbs_निजी काष्ठाure
 *
 *  वापसs:	0 क्रम success or -1 on error
 */
पूर्णांक lbs_allocate_cmd_buffer(काष्ठा lbs_निजी *priv)
अणु
	पूर्णांक ret = 0;
	u32 bufsize;
	u32 i;
	काष्ठा cmd_ctrl_node *cmdarray;

	/* Allocate and initialize the command array */
	bufsize = माप(काष्ठा cmd_ctrl_node) * LBS_NUM_CMD_BUFFERS;
	अगर (!(cmdarray = kzalloc(bufsize, GFP_KERNEL))) अणु
		lbs_deb_host("ALLOC_CMD_BUF: tempcmd_array is NULL\n");
		ret = -1;
		जाओ करोne;
	पूर्ण
	priv->cmd_array = cmdarray;

	/* Allocate and initialize each command buffer in the command array */
	क्रम (i = 0; i < LBS_NUM_CMD_BUFFERS; i++) अणु
		cmdarray[i].cmdbuf = kzalloc(LBS_CMD_BUFFER_SIZE, GFP_KERNEL);
		अगर (!cmdarray[i].cmdbuf) अणु
			lbs_deb_host("ALLOC_CMD_BUF: ptempvirtualaddr is NULL\n");
			ret = -1;
			जाओ करोne;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < LBS_NUM_CMD_BUFFERS; i++) अणु
		init_रुकोqueue_head(&cmdarray[i].cmdरुको_q);
		lbs_cleanup_and_insert_cmd(priv, &cmdarray[i]);
	पूर्ण
	ret = 0;

करोne:
	वापस ret;
पूर्ण

/**
 *  lbs_मुक्त_cmd_buffer - मुक्त the command buffer
 *
 *  @priv:	A poपूर्णांकer to &काष्ठा lbs_निजी काष्ठाure
 *
 *  वापसs:	0 क्रम success
 */
पूर्णांक lbs_मुक्त_cmd_buffer(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा cmd_ctrl_node *cmdarray;
	अचिन्हित पूर्णांक i;

	/* need to check अगर cmd array is allocated or not */
	अगर (priv->cmd_array == शून्य) अणु
		lbs_deb_host("FREE_CMD_BUF: cmd_array is NULL\n");
		जाओ करोne;
	पूर्ण

	cmdarray = priv->cmd_array;

	/* Release shared memory buffers */
	क्रम (i = 0; i < LBS_NUM_CMD_BUFFERS; i++) अणु
		अगर (cmdarray[i].cmdbuf) अणु
			kमुक्त(cmdarray[i].cmdbuf);
			cmdarray[i].cmdbuf = शून्य;
		पूर्ण
	पूर्ण

	/* Release cmd_ctrl_node */
	अगर (priv->cmd_array) अणु
		kमुक्त(priv->cmd_array);
		priv->cmd_array = शून्य;
	पूर्ण

करोne:
	वापस 0;
पूर्ण

/**
 *  lbs_get_मुक्त_cmd_node - माला_लो a मुक्त command node अगर available in
 *  command मुक्त queue
 *
 *  @priv:	A poपूर्णांकer to &काष्ठा lbs_निजी काष्ठाure
 *
 *  वापसs:	A poपूर्णांकer to &cmd_ctrl_node काष्ठाure on success
 *		or %शून्य on error
 */
अटल काष्ठा cmd_ctrl_node *lbs_get_मुक्त_cmd_node(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा cmd_ctrl_node *tempnode;
	अचिन्हित दीर्घ flags;

	अगर (!priv)
		वापस शून्य;

	spin_lock_irqsave(&priv->driver_lock, flags);

	अगर (!list_empty(&priv->cmdमुक्तq)) अणु
		tempnode = list_first_entry(&priv->cmdमुक्तq,
					    काष्ठा cmd_ctrl_node, list);
		list_del_init(&tempnode->list);
	पूर्ण अन्यथा अणु
		lbs_deb_host("GET_CMD_NODE: cmd_ctrl_node is not available\n");
		tempnode = शून्य;
	पूर्ण

	spin_unlock_irqrestore(&priv->driver_lock, flags);

	वापस tempnode;
पूर्ण

/**
 *  lbs_execute_next_command - execute next command in command
 *  pending queue. Will put firmware back to PS mode अगर applicable.
 *
 *  @priv:	A poपूर्णांकer to &काष्ठा lbs_निजी काष्ठाure
 *
 *  वापसs:	0 on success or -1 on error
 */
पूर्णांक lbs_execute_next_command(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा cmd_ctrl_node *cmdnode = शून्य;
	काष्ठा cmd_header *cmd;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	/* Debug group is LBS_DEB_THREAD and not LBS_DEB_HOST, because the
	 * only caller to us is lbs_thपढ़ो() and we get even when a
	 * data packet is received */
	spin_lock_irqsave(&priv->driver_lock, flags);

	अगर (priv->cur_cmd) अणु
		netdev_alert(priv->dev,
			     "EXEC_NEXT_CMD: already processing command!\n");
		spin_unlock_irqrestore(&priv->driver_lock, flags);
		ret = -1;
		जाओ करोne;
	पूर्ण

	अगर (!list_empty(&priv->cmdpendingq)) अणु
		cmdnode = list_first_entry(&priv->cmdpendingq,
					   काष्ठा cmd_ctrl_node, list);
	पूर्ण

	spin_unlock_irqrestore(&priv->driver_lock, flags);

	अगर (cmdnode) अणु
		cmd = cmdnode->cmdbuf;

		अगर (is_command_allowed_in_ps(le16_to_cpu(cmd->command))) अणु
			अगर ((priv->psstate == PS_STATE_SLEEP) ||
			    (priv->psstate == PS_STATE_PRE_SLEEP)) अणु
				lbs_deb_host(
				       "EXEC_NEXT_CMD: cannot send cmd 0x%04x in psstate %d\n",
				       le16_to_cpu(cmd->command),
				       priv->psstate);
				ret = -1;
				जाओ करोne;
			पूर्ण
			lbs_deb_host("EXEC_NEXT_CMD: OK to send command "
				     "0x%04x in psstate %d\n",
				     le16_to_cpu(cmd->command), priv->psstate);
		पूर्ण अन्यथा अगर (priv->psstate != PS_STATE_FULL_POWER) अणु
			/*
			 * 1. Non-PS command:
			 * Queue it. set needtowakeup to TRUE अगर current state
			 * is SLEEP, otherwise call send EXIT_PS.
			 * 2. PS command but not EXIT_PS:
			 * Ignore it.
			 * 3. PS command EXIT_PS:
			 * Set needtowakeup to TRUE अगर current state is SLEEP,
			 * otherwise send this command करोwn to firmware
			 * immediately.
			 */
			अगर (cmd->command != cpu_to_le16(CMD_802_11_PS_MODE)) अणु
				/*  Prepare to send Exit PS,
				 *  this non PS command will be sent later */
				अगर ((priv->psstate == PS_STATE_SLEEP)
				    || (priv->psstate == PS_STATE_PRE_SLEEP)
				    ) अणु
					/* w/ new scheme, it will not reach here.
					   since it is blocked in मुख्य_thपढ़ो. */
					priv->needtowakeup = 1;
				पूर्ण अन्यथा अणु
					lbs_set_ps_mode(priv,
							PS_MODE_ACTION_EXIT_PS,
							false);
				पूर्ण

				ret = 0;
				जाओ करोne;
			पूर्ण अन्यथा अणु
				/*
				 * PS command. Ignore it अगर it is not Exit_PS.
				 * otherwise send it करोwn immediately.
				 */
				काष्ठा cmd_ds_802_11_ps_mode *psm = (व्योम *)cmd;

				lbs_deb_host(
				       "EXEC_NEXT_CMD: PS cmd, action 0x%02x\n",
				       psm->action);
				अगर (psm->action !=
				    cpu_to_le16(PS_MODE_ACTION_EXIT_PS)) अणु
					lbs_deb_host(
					       "EXEC_NEXT_CMD: ignore ENTER_PS cmd\n");
					lbs_complete_command(priv, cmdnode, 0);

					ret = 0;
					जाओ करोne;
				पूर्ण

				अगर ((priv->psstate == PS_STATE_SLEEP) ||
				    (priv->psstate == PS_STATE_PRE_SLEEP)) अणु
					lbs_deb_host(
					       "EXEC_NEXT_CMD: ignore EXIT_PS cmd in sleep\n");
					lbs_complete_command(priv, cmdnode, 0);
					priv->needtowakeup = 1;

					ret = 0;
					जाओ करोne;
				पूर्ण

				lbs_deb_host(
				       "EXEC_NEXT_CMD: sending EXIT_PS\n");
			पूर्ण
		पूर्ण
		spin_lock_irqsave(&priv->driver_lock, flags);
		list_del_init(&cmdnode->list);
		spin_unlock_irqrestore(&priv->driver_lock, flags);
		lbs_deb_host("EXEC_NEXT_CMD: sending command 0x%04x\n",
			    le16_to_cpu(cmd->command));
		lbs_submit_command(priv, cmdnode);
	पूर्ण अन्यथा अणु
		/*
		 * check अगर in घातer save mode, अगर yes, put the device back
		 * to PS mode
		 */
		अगर ((priv->psmode != LBS802_11POWERMODECAM) &&
		    (priv->psstate == PS_STATE_FULL_POWER) &&
		    (priv->connect_status == LBS_CONNECTED)) अणु
			lbs_deb_host(
				"EXEC_NEXT_CMD: cmdpendingq empty, go back to PS_SLEEP");
			lbs_set_ps_mode(priv, PS_MODE_ACTION_ENTER_PS,
					false);
		पूर्ण
	पूर्ण

	ret = 0;
करोne:
	वापस ret;
पूर्ण

अटल व्योम lbs_send_confirmsleep(काष्ठा lbs_निजी *priv)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	lbs_deb_hex(LBS_DEB_HOST, "sleep confirm", (u8 *) &confirm_sleep,
		माप(confirm_sleep));

	ret = priv->hw_host_to_card(priv, MVMS_CMD, (u8 *) &confirm_sleep,
		माप(confirm_sleep));
	अगर (ret) अणु
		netdev_alert(priv->dev, "confirm_sleep failed\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(&priv->driver_lock, flags);

	/* We करोn't get a response on the sleep-confirmation */
	priv->dnld_sent = DNLD_RES_RECEIVED;

	अगर (priv->is_host_sleep_configured) अणु
		priv->is_host_sleep_activated = 1;
		wake_up_पूर्णांकerruptible(&priv->host_sleep_q);
	पूर्ण

	/* If nothing to करो, go back to sleep (?) */
	अगर (!kfअगरo_len(&priv->event_fअगरo) && !priv->resp_len[priv->resp_idx])
		priv->psstate = PS_STATE_SLEEP;

	spin_unlock_irqrestore(&priv->driver_lock, flags);
पूर्ण

/**
 * lbs_ps_confirm_sleep - checks condition and prepares to
 * send sleep confirm command to firmware अगर ok
 *
 * @priv:	A poपूर्णांकer to &काष्ठा lbs_निजी काष्ठाure
 *
 * वापसs:	n/a
 */
व्योम lbs_ps_confirm_sleep(काष्ठा lbs_निजी *priv)
अणु
	अचिन्हित दीर्घ flags =0;
	पूर्णांक allowed = 1;

	spin_lock_irqsave(&priv->driver_lock, flags);
	अगर (priv->dnld_sent) अणु
		allowed = 0;
		lbs_deb_host("dnld_sent was set\n");
	पूर्ण

	/* In-progress command? */
	अगर (priv->cur_cmd) अणु
		allowed = 0;
		lbs_deb_host("cur_cmd was set\n");
	पूर्ण

	/* Pending events or command responses? */
	अगर (kfअगरo_len(&priv->event_fअगरo) || priv->resp_len[priv->resp_idx]) अणु
		allowed = 0;
		lbs_deb_host("pending events or command responses\n");
	पूर्ण
	spin_unlock_irqrestore(&priv->driver_lock, flags);

	अगर (allowed) अणु
		lbs_deb_host("sending lbs_ps_confirm_sleep\n");
		lbs_send_confirmsleep(priv);
	पूर्ण अन्यथा अणु
		lbs_deb_host("sleep confirm has been delayed\n");
	पूर्ण
पूर्ण


/**
 * lbs_set_tpc_cfg - Configures the transmission घातer control functionality
 *
 * @priv:	A poपूर्णांकer to &काष्ठा lbs_निजी काष्ठाure
 * @enable:	Transmission घातer control enable
 * @p0:		Power level when link quality is good (dBm).
 * @p1:		Power level when link quality is fair (dBm).
 * @p2:		Power level when link quality is poor (dBm).
 * @usesnr:	Use Signal to Noise Ratio in TPC
 *
 * वापसs:	0 on success
 */
पूर्णांक lbs_set_tpc_cfg(काष्ठा lbs_निजी *priv, पूर्णांक enable, पूर्णांक8_t p0, पूर्णांक8_t p1,
		पूर्णांक8_t p2, पूर्णांक usesnr)
अणु
	काष्ठा cmd_ds_802_11_tpc_cfg cmd;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);
	cmd.enable = !!enable;
	cmd.usesnr = !!usesnr;
	cmd.P0 = p0;
	cmd.P1 = p1;
	cmd.P2 = p2;

	ret = lbs_cmd_with_response(priv, CMD_802_11_TPC_CFG, &cmd);

	वापस ret;
पूर्ण

/**
 * lbs_set_घातer_adapt_cfg - Configures the घातer adaptation settings
 *
 * @priv:	A poपूर्णांकer to &काष्ठा lbs_निजी काष्ठाure
 * @enable:	Power adaptation enable
 * @p0:		Power level क्रम 1, 2, 5.5 and 11 Mbps (dBm).
 * @p1:		Power level क्रम 6, 9, 12, 18, 22, 24 and 36 Mbps (dBm).
 * @p2:		Power level क्रम 48 and 54 Mbps (dBm).
 *
 * वापसs:	0 on Success
 */

पूर्णांक lbs_set_घातer_adapt_cfg(काष्ठा lbs_निजी *priv, पूर्णांक enable, पूर्णांक8_t p0,
		पूर्णांक8_t p1, पूर्णांक8_t p2)
अणु
	काष्ठा cmd_ds_802_11_pa_cfg cmd;
	पूर्णांक ret;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);
	cmd.enable = !!enable;
	cmd.P0 = p0;
	cmd.P1 = p1;
	cmd.P2 = p2;

	ret = lbs_cmd_with_response(priv, CMD_802_11_PA_CFG , &cmd);

	वापस ret;
पूर्ण


काष्ठा cmd_ctrl_node *__lbs_cmd_async(काष्ठा lbs_निजी *priv,
	uपूर्णांक16_t command, काष्ठा cmd_header *in_cmd, पूर्णांक in_cmd_size,
	पूर्णांक (*callback)(काष्ठा lbs_निजी *, अचिन्हित दीर्घ, काष्ठा cmd_header *),
	अचिन्हित दीर्घ callback_arg)
अणु
	काष्ठा cmd_ctrl_node *cmdnode;

	अगर (priv->surpriseहटाओd) अणु
		lbs_deb_host("PREP_CMD: card removed\n");
		cmdnode = ERR_PTR(-ENOENT);
		जाओ करोne;
	पूर्ण

	/* No commands are allowed in Deep Sleep until we toggle the GPIO
	 * to wake up the card and it has संकेतed that it's पढ़ोy.
	 */
	अगर (!priv->is_स्वतः_deep_sleep_enabled) अणु
		अगर (priv->is_deep_sleep) अणु
			lbs_deb_cmd("command not allowed in deep sleep\n");
			cmdnode = ERR_PTR(-EBUSY);
			जाओ करोne;
		पूर्ण
	पूर्ण

	cmdnode = lbs_get_मुक्त_cmd_node(priv);
	अगर (cmdnode == शून्य) अणु
		lbs_deb_host("PREP_CMD: cmdnode is NULL\n");

		/* Wake up मुख्य thपढ़ो to execute next command */
		wake_up(&priv->रुकोq);
		cmdnode = ERR_PTR(-ENOBUFS);
		जाओ करोne;
	पूर्ण

	cmdnode->callback = callback;
	cmdnode->callback_arg = callback_arg;

	/* Copy the incoming command to the buffer */
	स_नकल(cmdnode->cmdbuf, in_cmd, in_cmd_size);

	/* Set command, clean result, move to buffer */
	cmdnode->cmdbuf->command = cpu_to_le16(command);
	cmdnode->cmdbuf->size    = cpu_to_le16(in_cmd_size);
	cmdnode->cmdbuf->result  = 0;

	lbs_deb_host("PREP_CMD: command 0x%04x\n", command);

	cmdnode->cmdरुकोqwoken = 0;
	lbs_queue_cmd(priv, cmdnode);
	wake_up(&priv->रुकोq);

 करोne:
	वापस cmdnode;
पूर्ण

व्योम lbs_cmd_async(काष्ठा lbs_निजी *priv, uपूर्णांक16_t command,
	काष्ठा cmd_header *in_cmd, पूर्णांक in_cmd_size)
अणु
	__lbs_cmd_async(priv, command, in_cmd, in_cmd_size,
		lbs_cmd_async_callback, 0);
पूर्ण

पूर्णांक __lbs_cmd(काष्ठा lbs_निजी *priv, uपूर्णांक16_t command,
	      काष्ठा cmd_header *in_cmd, पूर्णांक in_cmd_size,
	      पूर्णांक (*callback)(काष्ठा lbs_निजी *, अचिन्हित दीर्घ, काष्ठा cmd_header *),
	      अचिन्हित दीर्घ callback_arg)
अणु
	काष्ठा cmd_ctrl_node *cmdnode;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	cmdnode = __lbs_cmd_async(priv, command, in_cmd, in_cmd_size,
				  callback, callback_arg);
	अगर (IS_ERR(cmdnode)) अणु
		ret = PTR_ERR(cmdnode);
		जाओ करोne;
	पूर्ण

	might_sleep();

	/*
	 * Be careful with संकेतs here. A संकेत may be received as the प्रणाली
	 * goes पूर्णांकo suspend or resume. We करो not want this to पूर्णांकerrupt the
	 * command, so we perक्रमm an unपूर्णांकerruptible sleep.
	 */
	रुको_event(cmdnode->cmdरुको_q, cmdnode->cmdरुकोqwoken);

	spin_lock_irqsave(&priv->driver_lock, flags);
	ret = cmdnode->result;
	अगर (ret)
		netdev_info(priv->dev, "PREP_CMD: command 0x%04x failed: %d\n",
			    command, ret);

	__lbs_cleanup_and_insert_cmd(priv, cmdnode);
	spin_unlock_irqrestore(&priv->driver_lock, flags);

करोne:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__lbs_cmd);
