<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2008, cozybit Inc.
 *  Copyright (C) 2003-2006, Marvell International Ltd.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/hardirq.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>

#समावेश "libertas_tf.h"

अटल स्थिर काष्ठा channel_range channel_ranges[] = अणु
	अणु LBTF_REGDOMAIN_US,		1, 12 पूर्ण,
	अणु LBTF_REGDOMAIN_CA,		1, 12 पूर्ण,
	अणु LBTF_REGDOMAIN_EU,		1, 14 पूर्ण,
	अणु LBTF_REGDOMAIN_JP,		1, 14 पूर्ण,
	अणु LBTF_REGDOMAIN_SP,		1, 14 पूर्ण,
	अणु LBTF_REGDOMAIN_FR,		1, 14 पूर्ण,
पूर्ण;

अटल u16 lbtf_region_code_to_index[MRVDRV_MAX_REGION_CODE] =
अणु
	LBTF_REGDOMAIN_US, LBTF_REGDOMAIN_CA, LBTF_REGDOMAIN_EU,
	LBTF_REGDOMAIN_SP, LBTF_REGDOMAIN_FR, LBTF_REGDOMAIN_JP,
पूर्ण;

अटल काष्ठा cmd_ctrl_node *lbtf_get_cmd_ctrl_node(काष्ठा lbtf_निजी *priv);


/**
 *  lbtf_cmd_copyback - Simple callback that copies response back पूर्णांकo command
 *
 *  @priv:	A poपूर्णांकer to काष्ठा lbtf_निजी काष्ठाure
 *  @extra:	A poपूर्णांकer to the original command काष्ठाure क्रम which
 *		'resp' is a response
 *  @resp:	A poपूर्णांकer to the command response
 *
 *  Returns: 0 on success, error on failure
 */
पूर्णांक lbtf_cmd_copyback(काष्ठा lbtf_निजी *priv, अचिन्हित दीर्घ extra,
		     काष्ठा cmd_header *resp)
अणु
	काष्ठा cmd_header *buf = (व्योम *)extra;
	uपूर्णांक16_t copy_len;

	copy_len = min(le16_to_cpu(buf->size), le16_to_cpu(resp->size));
	स_नकल(buf, resp, copy_len);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(lbtf_cmd_copyback);

#घोषणा CHAN_TO_IDX(chan) ((chan) - 1)

अटल व्योम lbtf_geo_init(काष्ठा lbtf_निजी *priv)
अणु
	स्थिर काष्ठा channel_range *range = channel_ranges;
	u8 ch;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(channel_ranges); i++)
		अगर (channel_ranges[i].regकरोमुख्य == priv->regioncode) अणु
			range = &channel_ranges[i];
			अवरोध;
		पूर्ण

	क्रम (ch = range->start; ch < range->end; ch++)
		priv->channels[CHAN_TO_IDX(ch)].flags = 0;
पूर्ण

/**
 *  lbtf_update_hw_spec: Updates the hardware details.
 *
 *  @priv:    	A poपूर्णांकer to काष्ठा lbtf_निजी काष्ठाure
 *
 *  Returns: 0 on success, error on failure
 */
पूर्णांक lbtf_update_hw_spec(काष्ठा lbtf_निजी *priv)
अणु
	काष्ठा cmd_ds_get_hw_spec cmd;
	पूर्णांक ret = -1;
	u32 i;

	lbtf_deb_enter(LBTF_DEB_CMD);

	स_रखो(&cmd, 0, माप(cmd));
	cmd.hdr.size = cpu_to_le16(माप(cmd));
	स_नकल(cmd.permanentaddr, priv->current_addr, ETH_ALEN);
	ret = lbtf_cmd_with_response(priv, CMD_GET_HW_SPEC, &cmd);
	अगर (ret)
		जाओ out;

	priv->fwcapinfo = le32_to_cpu(cmd.fwcapinfo);

	/* The firmware release is in an पूर्णांकeresting क्रमmat: the patch
	 * level is in the most signअगरicant nibble ... so fix that: */
	priv->fwrelease = le32_to_cpu(cmd.fwrelease);
	priv->fwrelease = (priv->fwrelease << 8) |
		(priv->fwrelease >> 24 & 0xff);

	prपूर्णांकk(KERN_INFO "libertastf: %pM, fw %u.%u.%up%u, cap 0x%08x\n",
		cmd.permanentaddr,
		priv->fwrelease >> 24 & 0xff,
		priv->fwrelease >> 16 & 0xff,
		priv->fwrelease >>  8 & 0xff,
		priv->fwrelease       & 0xff,
		priv->fwcapinfo);
	lbtf_deb_cmd("GET_HW_SPEC: hardware interface 0x%x, hardware spec 0x%04x\n",
		    cmd.hwअगरversion, cmd.version);

	/* Clamp region code to 8-bit since FW spec indicates that it should
	 * only ever be 8-bit, even though the field size is 16-bit.  Some
	 * firmware वापसs non-zero high 8 bits here.
	 */
	priv->regioncode = le16_to_cpu(cmd.regioncode) & 0xFF;

	क्रम (i = 0; i < MRVDRV_MAX_REGION_CODE; i++) अणु
		/* use the region code to search क्रम the index */
		अगर (priv->regioncode == lbtf_region_code_to_index[i])
			अवरोध;
	पूर्ण

	/* अगर it's unidentअगरied region code, use the शेष (USA) */
	अगर (i >= MRVDRV_MAX_REGION_CODE) अणु
		priv->regioncode = 0x10;
		pr_info("unidentified region code; using the default (USA)\n");
	पूर्ण

	अगर (priv->current_addr[0] == 0xff)
		स_हटाओ(priv->current_addr, cmd.permanentaddr, ETH_ALEN);

	SET_IEEE80211_PERM_ADDR(priv->hw, priv->current_addr);

	lbtf_geo_init(priv);
out:
	lbtf_deb_leave(LBTF_DEB_CMD);
	वापस ret;
पूर्ण

/**
 *  lbtf_set_channel: Set the radio channel
 *
 *  @priv:	A poपूर्णांकer to काष्ठा lbtf_निजी काष्ठाure
 *  @channel:	The desired channel, or 0 to clear a locked channel
 *
 *  Returns: 0 on success, error on failure
 */
पूर्णांक lbtf_set_channel(काष्ठा lbtf_निजी *priv, u8 channel)
अणु
	पूर्णांक ret = 0;
	काष्ठा cmd_ds_802_11_rf_channel cmd;

	lbtf_deb_enter(LBTF_DEB_CMD);

	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(CMD_OPT_802_11_RF_CHANNEL_SET);
	cmd.channel = cpu_to_le16(channel);

	ret = lbtf_cmd_with_response(priv, CMD_802_11_RF_CHANNEL, &cmd);
	lbtf_deb_leave_args(LBTF_DEB_CMD, "ret %d", ret);
	वापस ret;
पूर्ण

पूर्णांक lbtf_beacon_set(काष्ठा lbtf_निजी *priv, काष्ठा sk_buff *beacon)
अणु
	काष्ठा cmd_ds_802_11_beacon_set cmd;
	पूर्णांक size;

	lbtf_deb_enter(LBTF_DEB_CMD);

	अगर (beacon->len > MRVL_MAX_BCN_SIZE) अणु
		lbtf_deb_leave_args(LBTF_DEB_CMD, "ret %d", -1);
		वापस -1;
	पूर्ण
	size =  माप(cmd) - माप(cmd.beacon) + beacon->len;
	cmd.hdr.size = cpu_to_le16(size);
	cmd.len = cpu_to_le16(beacon->len);
	स_नकल(cmd.beacon, (u8 *) beacon->data, beacon->len);

	lbtf_cmd_async(priv, CMD_802_11_BEACON_SET, &cmd.hdr, size);

	lbtf_deb_leave_args(LBTF_DEB_CMD, "ret %d", 0);
	वापस 0;
पूर्ण

पूर्णांक lbtf_beacon_ctrl(काष्ठा lbtf_निजी *priv, bool beacon_enable,
		     पूर्णांक beacon_पूर्णांक)
अणु
	काष्ठा cmd_ds_802_11_beacon_control cmd;
	lbtf_deb_enter(LBTF_DEB_CMD);

	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);
	cmd.beacon_enable = cpu_to_le16(beacon_enable);
	cmd.beacon_period = cpu_to_le16(beacon_पूर्णांक);

	lbtf_cmd_async(priv, CMD_802_11_BEACON_CTRL, &cmd.hdr, माप(cmd));

	lbtf_deb_leave(LBTF_DEB_CMD);
	वापस 0;
पूर्ण

अटल व्योम lbtf_queue_cmd(काष्ठा lbtf_निजी *priv,
			  काष्ठा cmd_ctrl_node *cmdnode)
अणु
	अचिन्हित दीर्घ flags;
	lbtf_deb_enter(LBTF_DEB_HOST);

	अगर (!cmdnode) अणु
		lbtf_deb_host("QUEUE_CMD: cmdnode is NULL\n");
		जाओ qcmd_करोne;
	पूर्ण

	अगर (!cmdnode->cmdbuf->size) अणु
		lbtf_deb_host("DNLD_CMD: cmd size is zero\n");
		जाओ qcmd_करोne;
	पूर्ण

	cmdnode->result = 0;
	spin_lock_irqsave(&priv->driver_lock, flags);
	list_add_tail(&cmdnode->list, &priv->cmdpendingq);
	spin_unlock_irqrestore(&priv->driver_lock, flags);

	lbtf_deb_host("QUEUE_CMD: inserted command 0x%04x into cmdpendingq\n",
		     le16_to_cpu(cmdnode->cmdbuf->command));

qcmd_करोne:
	lbtf_deb_leave(LBTF_DEB_HOST);
पूर्ण

अटल व्योम lbtf_submit_command(काष्ठा lbtf_निजी *priv,
			       काष्ठा cmd_ctrl_node *cmdnode)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा cmd_header *cmd;
	uपूर्णांक16_t cmdsize;
	uपूर्णांक16_t command;
	पूर्णांक समयo = 5 * HZ;
	पूर्णांक ret;

	lbtf_deb_enter(LBTF_DEB_HOST);

	cmd = cmdnode->cmdbuf;

	spin_lock_irqsave(&priv->driver_lock, flags);
	priv->cur_cmd = cmdnode;
	cmdsize = le16_to_cpu(cmd->size);
	command = le16_to_cpu(cmd->command);

	lbtf_deb_cmd("DNLD_CMD: command 0x%04x, seq %d, size %d\n",
		     command, le16_to_cpu(cmd->seqnum), cmdsize);
	lbtf_deb_hex(LBTF_DEB_CMD, "DNLD_CMD", (व्योम *) cmdnode->cmdbuf, cmdsize);

	ret = priv->ops->hw_host_to_card(priv, MVMS_CMD, (u8 *)cmd, cmdsize);
	spin_unlock_irqrestore(&priv->driver_lock, flags);

	अगर (ret) अणु
		pr_info("DNLD_CMD: hw_host_to_card failed: %d\n", ret);
		/* Let the समयr kick in and retry, and potentially reset
		   the whole thing अगर the condition persists */
		समयo = HZ;
	पूर्ण

	/* Setup the समयr after transmit command */
	mod_समयr(&priv->command_समयr, jअगरfies + समयo);

	lbtf_deb_leave(LBTF_DEB_HOST);
पूर्ण

/*
 *  This function inserts command node to cmdमुक्तq
 *  after cleans it. Requires priv->driver_lock held.
 */
अटल व्योम __lbtf_cleanup_and_insert_cmd(काष्ठा lbtf_निजी *priv,
					 काष्ठा cmd_ctrl_node *cmdnode)
अणु
	lbtf_deb_enter(LBTF_DEB_HOST);

	अगर (!cmdnode)
		जाओ cl_ins_out;

	cmdnode->callback = शून्य;
	cmdnode->callback_arg = 0;

	स_रखो(cmdnode->cmdbuf, 0, LBS_CMD_BUFFER_SIZE);

	list_add_tail(&cmdnode->list, &priv->cmdमुक्तq);

cl_ins_out:
	lbtf_deb_leave(LBTF_DEB_HOST);
पूर्ण

अटल व्योम lbtf_cleanup_and_insert_cmd(काष्ठा lbtf_निजी *priv,
	काष्ठा cmd_ctrl_node *ptempcmd)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->driver_lock, flags);
	__lbtf_cleanup_and_insert_cmd(priv, ptempcmd);
	spin_unlock_irqrestore(&priv->driver_lock, flags);
पूर्ण

व्योम lbtf_complete_command(काष्ठा lbtf_निजी *priv, काष्ठा cmd_ctrl_node *cmd,
			  पूर्णांक result)
अणु
	cmd->result = result;
	cmd->cmdरुकोqwoken = 1;
	wake_up_पूर्णांकerruptible(&cmd->cmdरुको_q);

	अगर (!cmd->callback)
		__lbtf_cleanup_and_insert_cmd(priv, cmd);
	priv->cur_cmd = शून्य;
पूर्ण

पूर्णांक lbtf_cmd_set_mac_multicast_addr(काष्ठा lbtf_निजी *priv)
अणु
	काष्ठा cmd_ds_mac_multicast_addr cmd;

	lbtf_deb_enter(LBTF_DEB_CMD);

	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);

	cmd.nr_of_adrs = cpu_to_le16((u16) priv->nr_of_multicasपंचांगacaddr);

	lbtf_deb_cmd("MULTICAST_ADR: setting %d addresses\n", cmd.nr_of_adrs);

	स_नकल(cmd.maclist, priv->multicastlist,
	       priv->nr_of_multicasपंचांगacaddr * ETH_ALEN);

	lbtf_cmd_async(priv, CMD_MAC_MULTICAST_ADR, &cmd.hdr, माप(cmd));

	lbtf_deb_leave(LBTF_DEB_CMD);
	वापस 0;
पूर्ण

व्योम lbtf_set_mode(काष्ठा lbtf_निजी *priv, क्रमागत lbtf_mode mode)
अणु
	काष्ठा cmd_ds_set_mode cmd;
	lbtf_deb_enter(LBTF_DEB_WEXT);

	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.mode = cpu_to_le16(mode);
	lbtf_deb_wext("Switching to mode: 0x%x\n", mode);
	lbtf_cmd_async(priv, CMD_802_11_SET_MODE, &cmd.hdr, माप(cmd));

	lbtf_deb_leave(LBTF_DEB_WEXT);
पूर्ण

व्योम lbtf_set_bssid(काष्ठा lbtf_निजी *priv, bool activate, स्थिर u8 *bssid)
अणु
	काष्ठा cmd_ds_set_bssid cmd;
	lbtf_deb_enter(LBTF_DEB_CMD);

	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.activate = activate ? 1 : 0;
	अगर (activate)
		स_नकल(cmd.bssid, bssid, ETH_ALEN);

	lbtf_cmd_async(priv, CMD_802_11_SET_BSSID, &cmd.hdr, माप(cmd));
	lbtf_deb_leave(LBTF_DEB_CMD);
पूर्ण

पूर्णांक lbtf_set_mac_address(काष्ठा lbtf_निजी *priv, uपूर्णांक8_t *mac_addr)
अणु
	काष्ठा cmd_ds_802_11_mac_address cmd;
	lbtf_deb_enter(LBTF_DEB_CMD);

	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);

	स_नकल(cmd.macadd, mac_addr, ETH_ALEN);

	lbtf_cmd_async(priv, CMD_802_11_MAC_ADDRESS, &cmd.hdr, माप(cmd));
	lbtf_deb_leave(LBTF_DEB_CMD);
	वापस 0;
पूर्ण

पूर्णांक lbtf_set_radio_control(काष्ठा lbtf_निजी *priv)
अणु
	पूर्णांक ret = 0;
	काष्ठा cmd_ds_802_11_radio_control cmd;

	lbtf_deb_enter(LBTF_DEB_CMD);

	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);

	चयन (priv->preamble) अणु
	हाल CMD_TYPE_SHORT_PREAMBLE:
		cmd.control = cpu_to_le16(SET_SHORT_PREAMBLE);
		अवरोध;

	हाल CMD_TYPE_LONG_PREAMBLE:
		cmd.control = cpu_to_le16(SET_LONG_PREAMBLE);
		अवरोध;

	हाल CMD_TYPE_AUTO_PREAMBLE:
	शेष:
		cmd.control = cpu_to_le16(SET_AUTO_PREAMBLE);
		अवरोध;
	पूर्ण

	अगर (priv->radioon)
		cmd.control |= cpu_to_le16(TURN_ON_RF);
	अन्यथा
		cmd.control &= cpu_to_le16(~TURN_ON_RF);

	lbtf_deb_cmd("RADIO_SET: radio %d, preamble %d\n", priv->radioon,
		    priv->preamble);

	ret = lbtf_cmd_with_response(priv, CMD_802_11_RADIO_CONTROL, &cmd);

	lbtf_deb_leave_args(LBTF_DEB_CMD, "ret %d", ret);
	वापस ret;
पूर्ण

व्योम lbtf_set_mac_control(काष्ठा lbtf_निजी *priv)
अणु
	काष्ठा cmd_ds_mac_control cmd;
	lbtf_deb_enter(LBTF_DEB_CMD);

	cmd.hdr.size = cpu_to_le16(माप(cmd));
	cmd.action = cpu_to_le16(priv->mac_control);
	cmd.reserved = 0;

	lbtf_cmd_async(priv, CMD_MAC_CONTROL,
		&cmd.hdr, माप(cmd));

	lbtf_deb_leave(LBTF_DEB_CMD);
पूर्ण

/**
 *  lbtf_allocate_cmd_buffer - Allocates cmd buffer, links it to मुक्त cmd queue
 *
 *  @priv:	A poपूर्णांकer to काष्ठा lbtf_निजी काष्ठाure
 *
 *  Returns: 0 on success.
 */
पूर्णांक lbtf_allocate_cmd_buffer(काष्ठा lbtf_निजी *priv)
अणु
	पूर्णांक ret = 0;
	u32 bufsize;
	u32 i;
	काष्ठा cmd_ctrl_node *cmdarray;

	lbtf_deb_enter(LBTF_DEB_HOST);

	/* Allocate and initialize the command array */
	bufsize = माप(काष्ठा cmd_ctrl_node) * LBS_NUM_CMD_BUFFERS;
	cmdarray = kzalloc(bufsize, GFP_KERNEL);
	अगर (!cmdarray) अणु
		lbtf_deb_host("ALLOC_CMD_BUF: tempcmd_array is NULL\n");
		ret = -1;
		जाओ करोne;
	पूर्ण
	priv->cmd_array = cmdarray;

	/* Allocate and initialize each command buffer in the command array */
	क्रम (i = 0; i < LBS_NUM_CMD_BUFFERS; i++) अणु
		cmdarray[i].cmdbuf = kzalloc(LBS_CMD_BUFFER_SIZE, GFP_KERNEL);
		अगर (!cmdarray[i].cmdbuf) अणु
			lbtf_deb_host("ALLOC_CMD_BUF: ptempvirtualaddr is NULL\n");
			ret = -1;
			जाओ करोne;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < LBS_NUM_CMD_BUFFERS; i++) अणु
		init_रुकोqueue_head(&cmdarray[i].cmdरुको_q);
		lbtf_cleanup_and_insert_cmd(priv, &cmdarray[i]);
	पूर्ण

	ret = 0;

करोne:
	lbtf_deb_leave_args(LBTF_DEB_HOST, "ret %d", ret);
	वापस ret;
पूर्ण

/**
 *  lbtf_मुक्त_cmd_buffer - Frees the cmd buffer.
 *
 *  @priv:	A poपूर्णांकer to काष्ठा lbtf_निजी काष्ठाure
 *
 *  Returns: 0
 */
पूर्णांक lbtf_मुक्त_cmd_buffer(काष्ठा lbtf_निजी *priv)
अणु
	काष्ठा cmd_ctrl_node *cmdarray;
	अचिन्हित पूर्णांक i;

	lbtf_deb_enter(LBTF_DEB_HOST);

	/* need to check अगर cmd array is allocated or not */
	अगर (priv->cmd_array == शून्य) अणु
		lbtf_deb_host("FREE_CMD_BUF: cmd_array is NULL\n");
		जाओ करोne;
	पूर्ण

	cmdarray = priv->cmd_array;

	/* Release shared memory buffers */
	क्रम (i = 0; i < LBS_NUM_CMD_BUFFERS; i++) अणु
		kमुक्त(cmdarray[i].cmdbuf);
		cmdarray[i].cmdbuf = शून्य;
	पूर्ण

	/* Release cmd_ctrl_node */
	kमुक्त(priv->cmd_array);
	priv->cmd_array = शून्य;

करोne:
	lbtf_deb_leave(LBTF_DEB_HOST);
	वापस 0;
पूर्ण

/**
 *  lbtf_get_cmd_ctrl_node - Gets मुक्त cmd node from मुक्त cmd queue.
 *
 *  @priv:		A poपूर्णांकer to काष्ठा lbtf_निजी काष्ठाure
 *
 *  Returns: poपूर्णांकer to a काष्ठा cmd_ctrl_node or शून्य अगर none available.
 */
अटल काष्ठा cmd_ctrl_node *lbtf_get_cmd_ctrl_node(काष्ठा lbtf_निजी *priv)
अणु
	काष्ठा cmd_ctrl_node *tempnode;
	अचिन्हित दीर्घ flags;

	lbtf_deb_enter(LBTF_DEB_HOST);

	अगर (!priv)
		वापस शून्य;

	spin_lock_irqsave(&priv->driver_lock, flags);

	अगर (!list_empty(&priv->cmdमुक्तq)) अणु
		tempnode = list_first_entry(&priv->cmdमुक्तq,
					    काष्ठा cmd_ctrl_node, list);
		list_del(&tempnode->list);
	पूर्ण अन्यथा अणु
		lbtf_deb_host("GET_CMD_NODE: cmd_ctrl_node is not available\n");
		tempnode = शून्य;
	पूर्ण

	spin_unlock_irqrestore(&priv->driver_lock, flags);

	lbtf_deb_leave(LBTF_DEB_HOST);
	वापस tempnode;
पूर्ण

/**
 *  lbtf_execute_next_command: execute next command in cmd pending queue.
 *
 *  @priv:     A poपूर्णांकer to काष्ठा lbtf_निजी काष्ठाure
 *
 *  Returns: 0 on success.
 */
पूर्णांक lbtf_execute_next_command(काष्ठा lbtf_निजी *priv)
अणु
	काष्ठा cmd_ctrl_node *cmdnode = शून्य;
	काष्ठा cmd_header *cmd;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	/* Debug group is lbtf_deb_THREAD and not lbtf_deb_HOST, because the
	 * only caller to us is lbtf_thपढ़ो() and we get even when a
	 * data packet is received */
	lbtf_deb_enter(LBTF_DEB_THREAD);

	spin_lock_irqsave(&priv->driver_lock, flags);

	अगर (priv->cur_cmd) अणु
		pr_alert("EXEC_NEXT_CMD: already processing command!\n");
		spin_unlock_irqrestore(&priv->driver_lock, flags);
		ret = -1;
		जाओ करोne;
	पूर्ण

	अगर (!list_empty(&priv->cmdpendingq)) अणु
		cmdnode = list_first_entry(&priv->cmdpendingq,
					   काष्ठा cmd_ctrl_node, list);
	पूर्ण

	अगर (cmdnode) अणु
		cmd = cmdnode->cmdbuf;

		list_del(&cmdnode->list);
		lbtf_deb_host("EXEC_NEXT_CMD: sending command 0x%04x\n",
			    le16_to_cpu(cmd->command));
		spin_unlock_irqrestore(&priv->driver_lock, flags);
		lbtf_submit_command(priv, cmdnode);
	पूर्ण अन्यथा
		spin_unlock_irqrestore(&priv->driver_lock, flags);

	ret = 0;
करोne:
	lbtf_deb_leave(LBTF_DEB_THREAD);
	वापस ret;
पूर्ण

अटल काष्ठा cmd_ctrl_node *__lbtf_cmd_async(काष्ठा lbtf_निजी *priv,
	uपूर्णांक16_t command, काष्ठा cmd_header *in_cmd, पूर्णांक in_cmd_size,
	पूर्णांक (*callback)(काष्ठा lbtf_निजी *, अचिन्हित दीर्घ,
			काष्ठा cmd_header *),
	अचिन्हित दीर्घ callback_arg)
अणु
	काष्ठा cmd_ctrl_node *cmdnode;

	lbtf_deb_enter(LBTF_DEB_HOST);

	अगर (priv->surpriseहटाओd) अणु
		lbtf_deb_host("PREP_CMD: card removed\n");
		cmdnode = ERR_PTR(-ENOENT);
		जाओ करोne;
	पूर्ण

	cmdnode = lbtf_get_cmd_ctrl_node(priv);
	अगर (cmdnode == शून्य) अणु
		lbtf_deb_host("PREP_CMD: cmdnode is NULL\n");

		/* Wake up मुख्य thपढ़ो to execute next command */
		queue_work(lbtf_wq, &priv->cmd_work);
		cmdnode = ERR_PTR(-ENOBUFS);
		जाओ करोne;
	पूर्ण

	cmdnode->callback = callback;
	cmdnode->callback_arg = callback_arg;

	/* Copy the incoming command to the buffer */
	स_नकल(cmdnode->cmdbuf, in_cmd, in_cmd_size);

	/* Set sequence number, clean result, move to buffer */
	priv->seqnum++;
	cmdnode->cmdbuf->command = cpu_to_le16(command);
	cmdnode->cmdbuf->size    = cpu_to_le16(in_cmd_size);
	cmdnode->cmdbuf->seqnum  = cpu_to_le16(priv->seqnum);
	cmdnode->cmdbuf->result  = 0;

	lbtf_deb_host("PREP_CMD: command 0x%04x\n", command);

	cmdnode->cmdरुकोqwoken = 0;
	lbtf_queue_cmd(priv, cmdnode);
	queue_work(lbtf_wq, &priv->cmd_work);

 करोne:
	lbtf_deb_leave_args(LBTF_DEB_HOST, "ret %p", cmdnode);
	वापस cmdnode;
पूर्ण

व्योम lbtf_cmd_async(काष्ठा lbtf_निजी *priv, uपूर्णांक16_t command,
	काष्ठा cmd_header *in_cmd, पूर्णांक in_cmd_size)
अणु
	lbtf_deb_enter(LBTF_DEB_CMD);
	__lbtf_cmd_async(priv, command, in_cmd, in_cmd_size, शून्य, 0);
	lbtf_deb_leave(LBTF_DEB_CMD);
पूर्ण

पूर्णांक __lbtf_cmd(काष्ठा lbtf_निजी *priv, uपूर्णांक16_t command,
	      काष्ठा cmd_header *in_cmd, पूर्णांक in_cmd_size,
	      पूर्णांक (*callback)(काष्ठा lbtf_निजी *,
			      अचिन्हित दीर्घ, काष्ठा cmd_header *),
	      अचिन्हित दीर्घ callback_arg)
अणु
	काष्ठा cmd_ctrl_node *cmdnode;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	lbtf_deb_enter(LBTF_DEB_HOST);

	cmdnode = __lbtf_cmd_async(priv, command, in_cmd, in_cmd_size,
				  callback, callback_arg);
	अगर (IS_ERR(cmdnode)) अणु
		ret = PTR_ERR(cmdnode);
		जाओ करोne;
	पूर्ण

	might_sleep();
	ret = रुको_event_पूर्णांकerruptible(cmdnode->cmdरुको_q,
				       cmdnode->cmdरुकोqwoken);
	अगर (ret) अणु
		pr_info("PREP_CMD: command 0x%04x interrupted by signal: %d\n",
			    command, ret);
		जाओ करोne;
	पूर्ण

	spin_lock_irqsave(&priv->driver_lock, flags);
	ret = cmdnode->result;
	अगर (ret)
		pr_info("PREP_CMD: command 0x%04x failed: %d\n",
			    command, ret);

	__lbtf_cleanup_and_insert_cmd(priv, cmdnode);
	spin_unlock_irqrestore(&priv->driver_lock, flags);

करोne:
	lbtf_deb_leave_args(LBTF_DEB_HOST, "ret %d", ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__lbtf_cmd);

/* Call holding driver_lock */
व्योम lbtf_cmd_response_rx(काष्ठा lbtf_निजी *priv)
अणु
	priv->cmd_response_rxed = 1;
	queue_work(lbtf_wq, &priv->cmd_work);
पूर्ण
EXPORT_SYMBOL_GPL(lbtf_cmd_response_rx);

पूर्णांक lbtf_process_rx_command(काष्ठा lbtf_निजी *priv)
अणु
	uपूर्णांक16_t respcmd, curcmd;
	काष्ठा cmd_header *resp;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	uपूर्णांक16_t result;

	lbtf_deb_enter(LBTF_DEB_CMD);

	mutex_lock(&priv->lock);
	spin_lock_irqsave(&priv->driver_lock, flags);

	अगर (!priv->cur_cmd) अणु
		ret = -1;
		spin_unlock_irqrestore(&priv->driver_lock, flags);
		जाओ करोne;
	पूर्ण

	resp = (व्योम *)priv->cmd_resp_buff;
	curcmd = le16_to_cpu(priv->cur_cmd->cmdbuf->command);
	respcmd = le16_to_cpu(resp->command);
	result = le16_to_cpu(resp->result);

	lbtf_deb_cmd("libertastf: cmd response 0x%04x, seq %d, size %d\n",
		     respcmd, le16_to_cpu(resp->seqnum),
		     le16_to_cpu(resp->size));

	अगर (resp->seqnum != priv->cur_cmd->cmdbuf->seqnum) अणु
		spin_unlock_irqrestore(&priv->driver_lock, flags);
		ret = -1;
		जाओ करोne;
	पूर्ण
	अगर (respcmd != CMD_RET(curcmd)) अणु
		spin_unlock_irqrestore(&priv->driver_lock, flags);
		ret = -1;
		जाओ करोne;
	पूर्ण

	अगर (resp->result == cpu_to_le16(0x0004)) अणु
		/* 0x0004 means -EAGAIN. Drop the response, let it समय out
		   and be resubmitted */
		spin_unlock_irqrestore(&priv->driver_lock, flags);
		ret = -1;
		जाओ करोne;
	पूर्ण

	/* Now we got response from FW, cancel the command समयr */
	del_समयr(&priv->command_समयr);
	priv->cmd_समयd_out = 0;
	अगर (priv->nr_retries)
		priv->nr_retries = 0;

	/* If the command is not successful, cleanup and वापस failure */
	अगर ((result != 0 || !(respcmd & 0x8000))) अणु
		/*
		 * Handling errors here
		 */
		चयन (respcmd) अणु
		हाल CMD_RET(CMD_GET_HW_SPEC):
		हाल CMD_RET(CMD_802_11_RESET):
			pr_info("libertastf: reset failed\n");
			अवरोध;

		पूर्ण
		lbtf_complete_command(priv, priv->cur_cmd, result);
		spin_unlock_irqrestore(&priv->driver_lock, flags);

		ret = -1;
		जाओ करोne;
	पूर्ण

	spin_unlock_irqrestore(&priv->driver_lock, flags);

	अगर (priv->cur_cmd && priv->cur_cmd->callback) अणु
		ret = priv->cur_cmd->callback(priv, priv->cur_cmd->callback_arg,
				resp);
	पूर्ण
	spin_lock_irqsave(&priv->driver_lock, flags);

	अगर (priv->cur_cmd) अणु
		/* Clean up and Put current command back to cmdमुक्तq */
		lbtf_complete_command(priv, priv->cur_cmd, result);
	पूर्ण
	spin_unlock_irqrestore(&priv->driver_lock, flags);

करोne:
	mutex_unlock(&priv->lock);
	lbtf_deb_leave_args(LBTF_DEB_CMD, "ret %d", ret);
	वापस ret;
पूर्ण
