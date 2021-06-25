<शैली गुरु>
/*
 * NXP Wireless LAN device driver: commands and events
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#समावेश <यंत्र/unaligned.h>
#समावेश "decl.h"
#समावेश "ioctl.h"
#समावेश "util.h"
#समावेश "fw.h"
#समावेश "main.h"
#समावेश "wmm.h"
#समावेश "11n.h"

अटल व्योम mwअगरiex_cancel_pending_ioctl(काष्ठा mwअगरiex_adapter *adapter);

/*
 * This function initializes a command node.
 *
 * The actual allocation of the node is not करोne by this function. It only
 * initiates a node by filling it with शेष parameters. Similarly,
 * allocation of the dअगरferent buffers used (IOCTL buffer, data buffer) are
 * not करोne by this function either.
 */
अटल व्योम
mwअगरiex_init_cmd_node(काष्ठा mwअगरiex_निजी *priv,
		      काष्ठा cmd_ctrl_node *cmd_node,
		      u32 cmd_no, व्योम *data_buf, bool sync)
अणु
	cmd_node->priv = priv;
	cmd_node->cmd_no = cmd_no;

	अगर (sync) अणु
		cmd_node->रुको_q_enabled = true;
		cmd_node->cmd_रुको_q_woken = false;
		cmd_node->condition = &cmd_node->cmd_रुको_q_woken;
	पूर्ण
	cmd_node->data_buf = data_buf;
	cmd_node->cmd_skb = cmd_node->skb;
पूर्ण

/*
 * This function वापसs a command node from the मुक्त queue depending upon
 * availability.
 */
अटल काष्ठा cmd_ctrl_node *
mwअगरiex_get_cmd_node(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा cmd_ctrl_node *cmd_node;

	spin_lock_bh(&adapter->cmd_मुक्त_q_lock);
	अगर (list_empty(&adapter->cmd_मुक्त_q)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "GET_CMD_NODE: cmd node not available\n");
		spin_unlock_bh(&adapter->cmd_मुक्त_q_lock);
		वापस शून्य;
	पूर्ण
	cmd_node = list_first_entry(&adapter->cmd_मुक्त_q,
				    काष्ठा cmd_ctrl_node, list);
	list_del(&cmd_node->list);
	spin_unlock_bh(&adapter->cmd_मुक्त_q_lock);

	वापस cmd_node;
पूर्ण

/*
 * This function cleans up a command node.
 *
 * The function resets the fields including the buffer poपूर्णांकers.
 * This function करोes not try to मुक्त the buffers. They must be
 * मुक्तd beक्रमe calling this function.
 *
 * This function will however call the receive completion callback
 * in हाल a response buffer is still available beक्रमe resetting
 * the poपूर्णांकer.
 */
अटल व्योम
mwअगरiex_clean_cmd_node(काष्ठा mwअगरiex_adapter *adapter,
		       काष्ठा cmd_ctrl_node *cmd_node)
अणु
	cmd_node->cmd_no = 0;
	cmd_node->cmd_flag = 0;
	cmd_node->data_buf = शून्य;
	cmd_node->रुको_q_enabled = false;

	अगर (cmd_node->cmd_skb)
		skb_trim(cmd_node->cmd_skb, 0);

	अगर (cmd_node->resp_skb) अणु
		adapter->अगर_ops.cmdrsp_complete(adapter, cmd_node->resp_skb);
		cmd_node->resp_skb = शून्य;
	पूर्ण
पूर्ण

/*
 * This function वापसs a command to the command मुक्त queue.
 *
 * The function also calls the completion callback अगर required, beक्रमe
 * cleaning the command node and re-inserting it पूर्णांकo the मुक्त queue.
 */
अटल व्योम
mwअगरiex_insert_cmd_to_मुक्त_q(काष्ठा mwअगरiex_adapter *adapter,
			     काष्ठा cmd_ctrl_node *cmd_node)
अणु
	अगर (!cmd_node)
		वापस;

	अगर (cmd_node->रुको_q_enabled)
		mwअगरiex_complete_cmd(adapter, cmd_node);
	/* Clean the node */
	mwअगरiex_clean_cmd_node(adapter, cmd_node);

	/* Insert node पूर्णांकo cmd_मुक्त_q */
	spin_lock_bh(&adapter->cmd_मुक्त_q_lock);
	list_add_tail(&cmd_node->list, &adapter->cmd_मुक्त_q);
	spin_unlock_bh(&adapter->cmd_मुक्त_q_lock);
पूर्ण

/* This function reuses a command node. */
व्योम mwअगरiex_recycle_cmd_node(काष्ठा mwअगरiex_adapter *adapter,
			      काष्ठा cmd_ctrl_node *cmd_node)
अणु
	काष्ठा host_cmd_ds_command *host_cmd = (व्योम *)cmd_node->cmd_skb->data;

	mwअगरiex_insert_cmd_to_मुक्त_q(adapter, cmd_node);

	atomic_dec(&adapter->cmd_pending);
	mwअगरiex_dbg(adapter, CMD,
		    "cmd: FREE_CMD: cmd=%#x, cmd_pending=%d\n",
		le16_to_cpu(host_cmd->command),
		atomic_पढ़ो(&adapter->cmd_pending));
पूर्ण

/*
 * This function sends a host command to the firmware.
 *
 * The function copies the host command पूर्णांकo the driver command
 * buffer, which will be transferred to the firmware later by the
 * मुख्य thपढ़ो.
 */
अटल पूर्णांक mwअगरiex_cmd_host_cmd(काष्ठा mwअगरiex_निजी *priv,
				काष्ठा host_cmd_ds_command *cmd,
				काष्ठा mwअगरiex_ds_misc_cmd *pcmd_ptr)
अणु
	/* Copy the HOST command to command buffer */
	स_नकल(cmd, pcmd_ptr->cmd, pcmd_ptr->len);
	mwअगरiex_dbg(priv->adapter, CMD,
		    "cmd: host cmd size = %d\n", pcmd_ptr->len);
	वापस 0;
पूर्ण

/*
 * This function करोwnloads a command to the firmware.
 *
 * The function perक्रमms sanity tests, sets the command sequence
 * number and size, converts the header fields to CPU क्रमmat beक्रमe
 * sending. Afterwards, it logs the command ID and action क्रम debugging
 * and sets up the command समयout समयr.
 */
अटल पूर्णांक mwअगरiex_dnld_cmd_to_fw(काष्ठा mwअगरiex_निजी *priv,
				  काष्ठा cmd_ctrl_node *cmd_node)
अणु

	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	पूर्णांक ret;
	काष्ठा host_cmd_ds_command *host_cmd;
	uपूर्णांक16_t cmd_code;
	uपूर्णांक16_t cmd_size;

	अगर (!adapter || !cmd_node)
		वापस -1;

	host_cmd = (काष्ठा host_cmd_ds_command *) (cmd_node->cmd_skb->data);

	/* Sanity test */
	अगर (host_cmd == शून्य || host_cmd->size == 0) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "DNLD_CMD: host_cmd is null\t"
			    "or cmd size is 0, not sending\n");
		अगर (cmd_node->रुको_q_enabled)
			adapter->cmd_रुको_q.status = -1;
		mwअगरiex_recycle_cmd_node(adapter, cmd_node);
		वापस -1;
	पूर्ण

	cmd_code = le16_to_cpu(host_cmd->command);
	cmd_node->cmd_no = cmd_code;
	cmd_size = le16_to_cpu(host_cmd->size);

	अगर (adapter->hw_status == MWIFIEX_HW_STATUS_RESET &&
	    cmd_code != HostCmd_CMD_FUNC_SHUTDOWN &&
	    cmd_code != HostCmd_CMD_FUNC_INIT) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "DNLD_CMD: FW in reset state, ignore cmd %#x\n",
			cmd_code);
		mwअगरiex_recycle_cmd_node(adapter, cmd_node);
		queue_work(adapter->workqueue, &adapter->मुख्य_work);
		वापस -1;
	पूर्ण

	/* Set command sequence number */
	adapter->seq_num++;
	host_cmd->seq_num = cpu_to_le16(HostCmd_SET_SEQ_NO_BSS_INFO
					(adapter->seq_num,
					 cmd_node->priv->bss_num,
					 cmd_node->priv->bss_type));

	spin_lock_bh(&adapter->mwअगरiex_cmd_lock);
	adapter->curr_cmd = cmd_node;
	spin_unlock_bh(&adapter->mwअगरiex_cmd_lock);

	/* Adjust skb length */
	अगर (cmd_node->cmd_skb->len > cmd_size)
		/*
		 * cmd_size is less than माप(काष्ठा host_cmd_ds_command).
		 * Trim off the unused portion.
		 */
		skb_trim(cmd_node->cmd_skb, cmd_size);
	अन्यथा अगर (cmd_node->cmd_skb->len < cmd_size)
		/*
		 * cmd_size is larger than माप(काष्ठा host_cmd_ds_command)
		 * because we have appended custom IE TLV. Increase skb length
		 * accordingly.
		 */
		skb_put(cmd_node->cmd_skb, cmd_size - cmd_node->cmd_skb->len);

	mwअगरiex_dbg(adapter, CMD,
		    "cmd: DNLD_CMD: %#x, act %#x, len %d, seqno %#x\n",
		    cmd_code,
		    get_unaligned_le16((u8 *)host_cmd + S_DS_GEN),
		    cmd_size, le16_to_cpu(host_cmd->seq_num));
	mwअगरiex_dbg_dump(adapter, CMD_D, "cmd buffer:", host_cmd, cmd_size);

	अगर (adapter->अगरace_type == MWIFIEX_USB) अणु
		skb_push(cmd_node->cmd_skb, MWIFIEX_TYPE_LEN);
		put_unaligned_le32(MWIFIEX_USB_TYPE_CMD,
				   cmd_node->cmd_skb->data);
		adapter->cmd_sent = true;
		ret = adapter->अगर_ops.host_to_card(adapter,
						   MWIFIEX_USB_EP_CMD_EVENT,
						   cmd_node->cmd_skb, शून्य);
		skb_pull(cmd_node->cmd_skb, MWIFIEX_TYPE_LEN);
		अगर (ret == -EBUSY)
			cmd_node->cmd_skb = शून्य;
	पूर्ण अन्यथा अणु
		skb_push(cmd_node->cmd_skb, adapter->पूर्णांकf_hdr_len);
		ret = adapter->अगर_ops.host_to_card(adapter, MWIFIEX_TYPE_CMD,
						   cmd_node->cmd_skb, शून्य);
		skb_pull(cmd_node->cmd_skb, adapter->पूर्णांकf_hdr_len);
	पूर्ण

	अगर (ret == -1) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "DNLD_CMD: host to card failed\n");
		अगर (adapter->अगरace_type == MWIFIEX_USB)
			adapter->cmd_sent = false;
		अगर (cmd_node->रुको_q_enabled)
			adapter->cmd_रुको_q.status = -1;
		mwअगरiex_recycle_cmd_node(adapter, adapter->curr_cmd);

		spin_lock_bh(&adapter->mwअगरiex_cmd_lock);
		adapter->curr_cmd = शून्य;
		spin_unlock_bh(&adapter->mwअगरiex_cmd_lock);

		adapter->dbg.num_cmd_host_to_card_failure++;
		वापस -1;
	पूर्ण

	/* Save the last command id and action to debug log */
	adapter->dbg.last_cmd_index =
			(adapter->dbg.last_cmd_index + 1) % DBG_CMD_NUM;
	adapter->dbg.last_cmd_id[adapter->dbg.last_cmd_index] = cmd_code;
	adapter->dbg.last_cmd_act[adapter->dbg.last_cmd_index] =
			get_unaligned_le16((u8 *)host_cmd + S_DS_GEN);

	/* Setup the समयr after transmit command, except that specअगरic
	 * command might not have command response.
	 */
	अगर (cmd_code != HostCmd_CMD_FW_DUMP_EVENT)
		mod_समयr(&adapter->cmd_समयr,
			  jअगरfies + msecs_to_jअगरfies(MWIFIEX_TIMER_10S));

	/* Clear BSS_NO_BITS from HostCmd */
	cmd_code &= HostCmd_CMD_ID_MASK;

	वापस 0;
पूर्ण

/*
 * This function करोwnloads a sleep confirm command to the firmware.
 *
 * The function perक्रमms sanity tests, sets the command sequence
 * number and size, converts the header fields to CPU क्रमmat beक्रमe
 * sending.
 *
 * No responses are needed क्रम sleep confirm command.
 */
अटल पूर्णांक mwअगरiex_dnld_sleep_confirm_cmd(काष्ठा mwअगरiex_adapter *adapter)
अणु
	पूर्णांक ret;
	काष्ठा mwअगरiex_निजी *priv;
	काष्ठा mwअगरiex_opt_sleep_confirm *sleep_cfm_buf =
				(काष्ठा mwअगरiex_opt_sleep_confirm *)
						adapter->sleep_cfm->data;
	काष्ठा sk_buff *sleep_cfm_पंचांगp;

	priv = mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);

	adapter->seq_num++;
	sleep_cfm_buf->seq_num =
		cpu_to_le16(HostCmd_SET_SEQ_NO_BSS_INFO
					(adapter->seq_num, priv->bss_num,
					 priv->bss_type));

	mwअगरiex_dbg(adapter, CMD,
		    "cmd: DNLD_CMD: %#x, act %#x, len %d, seqno %#x\n",
		le16_to_cpu(sleep_cfm_buf->command),
		le16_to_cpu(sleep_cfm_buf->action),
		le16_to_cpu(sleep_cfm_buf->size),
		le16_to_cpu(sleep_cfm_buf->seq_num));
	mwअगरiex_dbg_dump(adapter, CMD_D, "SLEEP_CFM buffer: ", sleep_cfm_buf,
			 le16_to_cpu(sleep_cfm_buf->size));

	अगर (adapter->अगरace_type == MWIFIEX_USB) अणु
		sleep_cfm_पंचांगp =
			dev_alloc_skb(माप(काष्ठा mwअगरiex_opt_sleep_confirm)
				      + MWIFIEX_TYPE_LEN);
		अगर (!sleep_cfm_पंचांगp) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "SLEEP_CFM: dev_alloc_skb failed\n");
			वापस -ENOMEM;
		पूर्ण

		skb_put(sleep_cfm_पंचांगp, माप(काष्ठा mwअगरiex_opt_sleep_confirm)
			+ MWIFIEX_TYPE_LEN);
		put_unaligned_le32(MWIFIEX_USB_TYPE_CMD, sleep_cfm_पंचांगp->data);
		स_नकल(sleep_cfm_पंचांगp->data + MWIFIEX_TYPE_LEN,
		       adapter->sleep_cfm->data,
		       माप(काष्ठा mwअगरiex_opt_sleep_confirm));
		ret = adapter->अगर_ops.host_to_card(adapter,
						   MWIFIEX_USB_EP_CMD_EVENT,
						   sleep_cfm_पंचांगp, शून्य);
		अगर (ret != -EBUSY)
			dev_kमुक्त_skb_any(sleep_cfm_पंचांगp);
	पूर्ण अन्यथा अणु
		skb_push(adapter->sleep_cfm, adapter->पूर्णांकf_hdr_len);
		ret = adapter->अगर_ops.host_to_card(adapter, MWIFIEX_TYPE_CMD,
						   adapter->sleep_cfm, शून्य);
		skb_pull(adapter->sleep_cfm, adapter->पूर्णांकf_hdr_len);
	पूर्ण

	अगर (ret == -1) अणु
		mwअगरiex_dbg(adapter, ERROR, "SLEEP_CFM: failed\n");
		adapter->dbg.num_cmd_sleep_cfm_host_to_card_failure++;
		वापस -1;
	पूर्ण

	अगर (!le16_to_cpu(sleep_cfm_buf->resp_ctrl))
		/* Response is not needed क्रम sleep confirm command */
		adapter->ps_state = PS_STATE_SLEEP;
	अन्यथा
		adapter->ps_state = PS_STATE_SLEEP_CFM;

	अगर (!le16_to_cpu(sleep_cfm_buf->resp_ctrl) &&
	    (test_bit(MWIFIEX_IS_HS_CONFIGURED, &adapter->work_flags) &&
	     !adapter->sleep_period.period)) अणु
		adapter->pm_wakeup_card_req = true;
		mwअगरiex_hs_activated_event(mwअगरiex_get_priv
				(adapter, MWIFIEX_BSS_ROLE_ANY), true);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * This function allocates the command buffers and links them to
 * the command मुक्त queue.
 *
 * The driver uses a pre allocated number of command buffers, which
 * are created at driver initializations and मुक्तd at driver cleanup.
 * Every command needs to obtain a command buffer from this pool beक्रमe
 * it can be issued. The command मुक्त queue lists the command buffers
 * currently मुक्त to use, जबतक the command pending queue lists the
 * command buffers alपढ़ोy in use and aरुकोing handling. Command buffers
 * are वापसed to the मुक्त queue after use.
 */
पूर्णांक mwअगरiex_alloc_cmd_buffer(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा cmd_ctrl_node *cmd_array;
	u32 i;

	/* Allocate and initialize काष्ठा cmd_ctrl_node */
	cmd_array = kसुस्मृति(MWIFIEX_NUM_OF_CMD_BUFFER,
			    माप(काष्ठा cmd_ctrl_node), GFP_KERNEL);
	अगर (!cmd_array)
		वापस -ENOMEM;

	adapter->cmd_pool = cmd_array;

	/* Allocate and initialize command buffers */
	क्रम (i = 0; i < MWIFIEX_NUM_OF_CMD_BUFFER; i++) अणु
		cmd_array[i].skb = dev_alloc_skb(MWIFIEX_SIZE_OF_CMD_BUFFER);
		अगर (!cmd_array[i].skb) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "unable to allocate command buffer\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < MWIFIEX_NUM_OF_CMD_BUFFER; i++)
		mwअगरiex_insert_cmd_to_मुक्त_q(adapter, &cmd_array[i]);

	वापस 0;
पूर्ण

/*
 * This function मुक्तs the command buffers.
 *
 * The function calls the completion callback क्रम all the command
 * buffers that still have response buffers associated with them.
 */
व्योम mwअगरiex_मुक्त_cmd_buffer(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा cmd_ctrl_node *cmd_array;
	u32 i;

	/* Need to check अगर cmd pool is allocated or not */
	अगर (!adapter->cmd_pool) अणु
		mwअगरiex_dbg(adapter, FATAL,
			    "info: FREE_CMD_BUF: cmd_pool is null\n");
		वापस;
	पूर्ण

	cmd_array = adapter->cmd_pool;

	/* Release shared memory buffers */
	क्रम (i = 0; i < MWIFIEX_NUM_OF_CMD_BUFFER; i++) अणु
		अगर (cmd_array[i].skb) अणु
			mwअगरiex_dbg(adapter, CMD,
				    "cmd: free cmd buffer %d\n", i);
			dev_kमुक्त_skb_any(cmd_array[i].skb);
		पूर्ण
		अगर (!cmd_array[i].resp_skb)
			जारी;

		अगर (adapter->अगरace_type == MWIFIEX_USB)
			adapter->अगर_ops.cmdrsp_complete(adapter,
							cmd_array[i].resp_skb);
		अन्यथा
			dev_kमुक्त_skb_any(cmd_array[i].resp_skb);
	पूर्ण
	/* Release काष्ठा cmd_ctrl_node */
	अगर (adapter->cmd_pool) अणु
		mwअगरiex_dbg(adapter, CMD,
			    "cmd: free cmd pool\n");
		kमुक्त(adapter->cmd_pool);
		adapter->cmd_pool = शून्य;
	पूर्ण
पूर्ण

/*
 * This function handles events generated by firmware.
 *
 * Event body of events received from firmware are not used (though they are
 * saved), only the event ID is used. Some events are re-invoked by
 * the driver, with a new event body.
 *
 * After processing, the function calls the completion callback
 * क्रम cleanup.
 */
पूर्णांक mwअगरiex_process_event(काष्ठा mwअगरiex_adapter *adapter)
अणु
	पूर्णांक ret, i;
	काष्ठा mwअगरiex_निजी *priv =
		mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);
	काष्ठा sk_buff *skb = adapter->event_skb;
	u32 eventcause;
	काष्ठा mwअगरiex_rxinfo *rx_info;

	अगर ((adapter->event_cause & EVENT_ID_MASK) == EVENT_RADAR_DETECTED) अणु
		क्रम (i = 0; i < adapter->priv_num; i++) अणु
			priv = adapter->priv[i];
			अगर (priv && mwअगरiex_is_11h_active(priv)) अणु
				adapter->event_cause |=
					((priv->bss_num & 0xff) << 16) |
					((priv->bss_type & 0xff) << 24);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	eventcause = adapter->event_cause;

	/* Save the last event to debug log */
	adapter->dbg.last_event_index =
			(adapter->dbg.last_event_index + 1) % DBG_CMD_NUM;
	adapter->dbg.last_event[adapter->dbg.last_event_index] =
							(u16) eventcause;

	/* Get BSS number and corresponding priv */
	priv = mwअगरiex_get_priv_by_id(adapter, EVENT_GET_BSS_NUM(eventcause),
				      EVENT_GET_BSS_TYPE(eventcause));
	अगर (!priv)
		priv = mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);

	/* Clear BSS_NO_BITS from event */
	eventcause &= EVENT_ID_MASK;
	adapter->event_cause = eventcause;

	अगर (skb) अणु
		rx_info = MWIFIEX_SKB_RXCB(skb);
		स_रखो(rx_info, 0, माप(*rx_info));
		rx_info->bss_num = priv->bss_num;
		rx_info->bss_type = priv->bss_type;
		mwअगरiex_dbg_dump(adapter, EVT_D, "Event Buf:",
				 skb->data, skb->len);
	पूर्ण

	mwअगरiex_dbg(adapter, EVENT, "EVENT: cause: %#x\n", eventcause);

	अगर (priv->bss_role == MWIFIEX_BSS_ROLE_UAP)
		ret = mwअगरiex_process_uap_event(priv);
	अन्यथा
		ret = mwअगरiex_process_sta_event(priv);

	adapter->event_cause = 0;
	adapter->event_skb = शून्य;
	adapter->अगर_ops.event_complete(adapter, skb);

	वापस ret;
पूर्ण

/*
 * This function prepares a command and send it to the firmware.
 *
 * Preparation includes -
 *      - Sanity tests to make sure the card is still present or the FW
 *        is not reset
 *      - Getting a new command node from the command मुक्त queue
 *      - Initializing the command node क्रम शेष parameters
 *      - Fill up the non-शेष parameters and buffer poपूर्णांकers
 *      - Add the command to pending queue
 */
पूर्णांक mwअगरiex_send_cmd(काष्ठा mwअगरiex_निजी *priv, u16 cmd_no,
		     u16 cmd_action, u32 cmd_oid, व्योम *data_buf, bool sync)
अणु
	पूर्णांक ret;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा cmd_ctrl_node *cmd_node;
	काष्ठा host_cmd_ds_command *cmd_ptr;

	अगर (!adapter) अणु
		pr_err("PREP_CMD: adapter is NULL\n");
		वापस -1;
	पूर्ण

	अगर (test_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "PREP_CMD: device in suspended state\n");
		वापस -1;
	पूर्ण

	अगर (test_bit(MWIFIEX_IS_HS_ENABLING, &adapter->work_flags) &&
	    cmd_no != HostCmd_CMD_802_11_HS_CFG_ENH) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "PREP_CMD: host entering sleep state\n");
		वापस -1;
	पूर्ण

	अगर (test_bit(MWIFIEX_SURPRISE_REMOVED, &adapter->work_flags)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "PREP_CMD: card is removed\n");
		वापस -1;
	पूर्ण

	अगर (test_bit(MWIFIEX_IS_CMD_TIMEDOUT, &adapter->work_flags)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "PREP_CMD: FW is in bad state\n");
		वापस -1;
	पूर्ण

	अगर (adapter->hw_status == MWIFIEX_HW_STATUS_RESET) अणु
		अगर (cmd_no != HostCmd_CMD_FUNC_INIT) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "PREP_CMD: FW in reset state\n");
			वापस -1;
		पूर्ण
	पूर्ण
	/* We करोn't expect commands in manufacturing mode. They are cooked
	 * in application and पढ़ोy to करोwnload buffer is passed to the driver
	 */
	अगर (adapter->mfg_mode && cmd_no) अणु
		dev_dbg(adapter->dev, "Ignoring commands in manufacturing mode\n");
		वापस -1;
	पूर्ण


	/* Get a new command node */
	cmd_node = mwअगरiex_get_cmd_node(adapter);

	अगर (!cmd_node) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "PREP_CMD: no free cmd node\n");
		वापस -1;
	पूर्ण

	/* Initialize the command node */
	mwअगरiex_init_cmd_node(priv, cmd_node, cmd_no, data_buf, sync);

	अगर (!cmd_node->cmd_skb) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "PREP_CMD: no free cmd buf\n");
		वापस -1;
	पूर्ण

	skb_put_zero(cmd_node->cmd_skb, माप(काष्ठा host_cmd_ds_command));

	cmd_ptr = (काष्ठा host_cmd_ds_command *) (cmd_node->cmd_skb->data);
	cmd_ptr->command = cpu_to_le16(cmd_no);
	cmd_ptr->result = 0;

	/* Prepare command */
	अगर (cmd_no) अणु
		चयन (cmd_no) अणु
		हाल HostCmd_CMD_UAP_SYS_CONFIG:
		हाल HostCmd_CMD_UAP_BSS_START:
		हाल HostCmd_CMD_UAP_BSS_STOP:
		हाल HostCmd_CMD_UAP_STA_DEAUTH:
		हाल HOST_CMD_APCMD_SYS_RESET:
		हाल HOST_CMD_APCMD_STA_LIST:
			ret = mwअगरiex_uap_prepare_cmd(priv, cmd_no, cmd_action,
						      cmd_oid, data_buf,
						      cmd_ptr);
			अवरोध;
		शेष:
			ret = mwअगरiex_sta_prepare_cmd(priv, cmd_no, cmd_action,
						      cmd_oid, data_buf,
						      cmd_ptr);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = mwअगरiex_cmd_host_cmd(priv, cmd_ptr, data_buf);
		cmd_node->cmd_flag |= CMD_F_HOSTCMD;
	पूर्ण

	/* Return error, since the command preparation failed */
	अगर (ret) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "PREP_CMD: cmd %#x preparation failed\n",
			cmd_no);
		mwअगरiex_insert_cmd_to_मुक्त_q(adapter, cmd_node);
		वापस -1;
	पूर्ण

	/* Send command */
	अगर (cmd_no == HostCmd_CMD_802_11_SCAN ||
	    cmd_no == HostCmd_CMD_802_11_SCAN_EXT) अणु
		mwअगरiex_queue_scan_cmd(priv, cmd_node);
	पूर्ण अन्यथा अणु
		mwअगरiex_insert_cmd_to_pending_q(adapter, cmd_node);
		queue_work(adapter->workqueue, &adapter->मुख्य_work);
		अगर (cmd_node->रुको_q_enabled)
			ret = mwअगरiex_रुको_queue_complete(adapter, cmd_node);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * This function queues a command to the command pending queue.
 *
 * This in effect adds the command to the command list to be executed.
 * Exit PS command is handled specially, by placing it always to the
 * front of the command queue.
 */
व्योम
mwअगरiex_insert_cmd_to_pending_q(काष्ठा mwअगरiex_adapter *adapter,
				काष्ठा cmd_ctrl_node *cmd_node)
अणु
	काष्ठा host_cmd_ds_command *host_cmd = शून्य;
	u16 command;
	bool add_tail = true;

	host_cmd = (काष्ठा host_cmd_ds_command *) (cmd_node->cmd_skb->data);
	अगर (!host_cmd) अणु
		mwअगरiex_dbg(adapter, ERROR, "QUEUE_CMD: host_cmd is NULL\n");
		वापस;
	पूर्ण

	command = le16_to_cpu(host_cmd->command);

	/* Exit_PS command needs to be queued in the header always. */
	अगर (command == HostCmd_CMD_802_11_PS_MODE_ENH) अणु
		काष्ठा host_cmd_ds_802_11_ps_mode_enh *pm =
						&host_cmd->params.psmode_enh;
		अगर ((le16_to_cpu(pm->action) == DIS_PS) ||
		    (le16_to_cpu(pm->action) == DIS_AUTO_PS)) अणु
			अगर (adapter->ps_state != PS_STATE_AWAKE)
				add_tail = false;
		पूर्ण
	पूर्ण

	spin_lock_bh(&adapter->cmd_pending_q_lock);
	अगर (add_tail)
		list_add_tail(&cmd_node->list, &adapter->cmd_pending_q);
	अन्यथा
		list_add(&cmd_node->list, &adapter->cmd_pending_q);
	spin_unlock_bh(&adapter->cmd_pending_q_lock);

	atomic_inc(&adapter->cmd_pending);
	mwअगरiex_dbg(adapter, CMD,
		    "cmd: QUEUE_CMD: cmd=%#x, cmd_pending=%d\n",
		command, atomic_पढ़ो(&adapter->cmd_pending));
पूर्ण

/*
 * This function executes the next command in command pending queue.
 *
 * This function will fail अगर a command is alपढ़ोy in processing stage,
 * otherwise it will dequeue the first command from the command pending
 * queue and send to the firmware.
 *
 * If the device is currently in host sleep mode, any commands, except the
 * host sleep configuration command will de-activate the host sleep. For PS
 * mode, the function will put the firmware back to sleep अगर applicable.
 */
पूर्णांक mwअगरiex_exec_next_cmd(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा mwअगरiex_निजी *priv;
	काष्ठा cmd_ctrl_node *cmd_node;
	पूर्णांक ret = 0;
	काष्ठा host_cmd_ds_command *host_cmd;

	/* Check अगर alपढ़ोy in processing */
	अगर (adapter->curr_cmd) अणु
		mwअगरiex_dbg(adapter, FATAL,
			    "EXEC_NEXT_CMD: cmd in processing\n");
		वापस -1;
	पूर्ण

	spin_lock_bh(&adapter->mwअगरiex_cmd_lock);
	/* Check अगर any command is pending */
	spin_lock_bh(&adapter->cmd_pending_q_lock);
	अगर (list_empty(&adapter->cmd_pending_q)) अणु
		spin_unlock_bh(&adapter->cmd_pending_q_lock);
		spin_unlock_bh(&adapter->mwअगरiex_cmd_lock);
		वापस 0;
	पूर्ण
	cmd_node = list_first_entry(&adapter->cmd_pending_q,
				    काष्ठा cmd_ctrl_node, list);

	host_cmd = (काष्ठा host_cmd_ds_command *) (cmd_node->cmd_skb->data);
	priv = cmd_node->priv;

	अगर (adapter->ps_state != PS_STATE_AWAKE) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: cannot send cmd in sleep state,\t"
			    "this should not happen\n", __func__);
		spin_unlock_bh(&adapter->cmd_pending_q_lock);
		spin_unlock_bh(&adapter->mwअगरiex_cmd_lock);
		वापस ret;
	पूर्ण

	list_del(&cmd_node->list);
	spin_unlock_bh(&adapter->cmd_pending_q_lock);

	spin_unlock_bh(&adapter->mwअगरiex_cmd_lock);
	ret = mwअगरiex_dnld_cmd_to_fw(priv, cmd_node);
	priv = mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);
	/* Any command sent to the firmware when host is in sleep
	 * mode should de-configure host sleep. We should skip the
	 * host sleep configuration command itself though
	 */
	अगर (priv && (host_cmd->command !=
	     cpu_to_le16(HostCmd_CMD_802_11_HS_CFG_ENH))) अणु
		अगर (adapter->hs_activated) अणु
			clear_bit(MWIFIEX_IS_HS_CONFIGURED,
				  &adapter->work_flags);
			mwअगरiex_hs_activated_event(priv, false);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * This function handles the command response.
 *
 * After processing, the function cleans the command node and माला_दो
 * it back to the command मुक्त queue.
 */
पूर्णांक mwअगरiex_process_cmdresp(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा host_cmd_ds_command *resp;
	काष्ठा mwअगरiex_निजी *priv =
		mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);
	पूर्णांक ret = 0;
	uपूर्णांक16_t orig_cmdresp_no;
	uपूर्णांक16_t cmdresp_no;
	uपूर्णांक16_t cmdresp_result;

	अगर (!adapter->curr_cmd || !adapter->curr_cmd->resp_skb) अणु
		resp = (काष्ठा host_cmd_ds_command *) adapter->upld_buf;
		mwअगरiex_dbg(adapter, ERROR,
			    "CMD_RESP: NULL curr_cmd, %#x\n",
			    le16_to_cpu(resp->command));
		वापस -1;
	पूर्ण

	resp = (काष्ठा host_cmd_ds_command *)adapter->curr_cmd->resp_skb->data;
	orig_cmdresp_no = le16_to_cpu(resp->command);
	cmdresp_no = (orig_cmdresp_no & HostCmd_CMD_ID_MASK);

	अगर (adapter->curr_cmd->cmd_no != cmdresp_no) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "cmdresp error: cmd=0x%x cmd_resp=0x%x\n",
			    adapter->curr_cmd->cmd_no, cmdresp_no);
		वापस -1;
	पूर्ण
	/* Now we got response from FW, cancel the command समयr */
	del_समयr_sync(&adapter->cmd_समयr);
	clear_bit(MWIFIEX_IS_CMD_TIMEDOUT, &adapter->work_flags);

	अगर (adapter->curr_cmd->cmd_flag & CMD_F_HOSTCMD) अणु
		/* Copy original response back to response buffer */
		काष्ठा mwअगरiex_ds_misc_cmd *hostcmd;
		uपूर्णांक16_t size = le16_to_cpu(resp->size);
		mwअगरiex_dbg(adapter, INFO,
			    "info: host cmd resp size = %d\n", size);
		size = min_t(u16, size, MWIFIEX_SIZE_OF_CMD_BUFFER);
		अगर (adapter->curr_cmd->data_buf) अणु
			hostcmd = adapter->curr_cmd->data_buf;
			hostcmd->len = size;
			स_नकल(hostcmd->cmd, resp, size);
		पूर्ण
	पूर्ण

	/* Get BSS number and corresponding priv */
	priv = mwअगरiex_get_priv_by_id(adapter,
			     HostCmd_GET_BSS_NO(le16_to_cpu(resp->seq_num)),
			     HostCmd_GET_BSS_TYPE(le16_to_cpu(resp->seq_num)));
	अगर (!priv)
		priv = mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);
	/* Clear RET_BIT from HostCmd */
	resp->command = cpu_to_le16(orig_cmdresp_no & HostCmd_CMD_ID_MASK);

	cmdresp_no = le16_to_cpu(resp->command);
	cmdresp_result = le16_to_cpu(resp->result);

	/* Save the last command response to debug log */
	adapter->dbg.last_cmd_resp_index =
			(adapter->dbg.last_cmd_resp_index + 1) % DBG_CMD_NUM;
	adapter->dbg.last_cmd_resp_id[adapter->dbg.last_cmd_resp_index] =
								orig_cmdresp_no;

	mwअगरiex_dbg(adapter, CMD,
		    "cmd: CMD_RESP: 0x%x, result %d, len %d, seqno 0x%x\n",
		    orig_cmdresp_no, cmdresp_result,
		    le16_to_cpu(resp->size), le16_to_cpu(resp->seq_num));
	mwअगरiex_dbg_dump(adapter, CMD_D, "CMD_RESP buffer:", resp,
			 le16_to_cpu(resp->size));

	अगर (!(orig_cmdresp_no & HostCmd_RET_BIT)) अणु
		mwअगरiex_dbg(adapter, ERROR, "CMD_RESP: invalid cmd resp\n");
		अगर (adapter->curr_cmd->रुको_q_enabled)
			adapter->cmd_रुको_q.status = -1;

		mwअगरiex_recycle_cmd_node(adapter, adapter->curr_cmd);
		spin_lock_bh(&adapter->mwअगरiex_cmd_lock);
		adapter->curr_cmd = शून्य;
		spin_unlock_bh(&adapter->mwअगरiex_cmd_lock);
		वापस -1;
	पूर्ण

	अगर (adapter->curr_cmd->cmd_flag & CMD_F_HOSTCMD) अणु
		adapter->curr_cmd->cmd_flag &= ~CMD_F_HOSTCMD;
		अगर ((cmdresp_result == HostCmd_RESULT_OK) &&
		    (cmdresp_no == HostCmd_CMD_802_11_HS_CFG_ENH))
			ret = mwअगरiex_ret_802_11_hs_cfg(priv, resp);
	पूर्ण अन्यथा अणु
		/* handle response */
		ret = mwअगरiex_process_sta_cmdresp(priv, cmdresp_no, resp);
	पूर्ण

	/* Check init command response */
	अगर (adapter->hw_status == MWIFIEX_HW_STATUS_INITIALIZING) अणु
		अगर (ret) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "%s: cmd %#x failed during\t"
				    "initialization\n", __func__, cmdresp_no);
			mwअगरiex_init_fw_complete(adapter);
			वापस -1;
		पूर्ण अन्यथा अगर (adapter->last_init_cmd == cmdresp_no)
			adapter->hw_status = MWIFIEX_HW_STATUS_INIT_DONE;
	पूर्ण

	अगर (adapter->curr_cmd) अणु
		अगर (adapter->curr_cmd->रुको_q_enabled)
			adapter->cmd_रुको_q.status = ret;

		mwअगरiex_recycle_cmd_node(adapter, adapter->curr_cmd);

		spin_lock_bh(&adapter->mwअगरiex_cmd_lock);
		adapter->curr_cmd = शून्य;
		spin_unlock_bh(&adapter->mwअगरiex_cmd_lock);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * This function handles the समयout of command sending.
 *
 * It will re-send the same command again.
 */
व्योम
mwअगरiex_cmd_समयout_func(काष्ठा समयr_list *t)
अणु
	काष्ठा mwअगरiex_adapter *adapter = from_समयr(adapter, t, cmd_समयr);
	काष्ठा cmd_ctrl_node *cmd_node;

	set_bit(MWIFIEX_IS_CMD_TIMEDOUT, &adapter->work_flags);
	अगर (!adapter->curr_cmd) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "cmd: empty curr_cmd\n");
		वापस;
	पूर्ण
	cmd_node = adapter->curr_cmd;
	अगर (cmd_node) अणु
		adapter->dbg.समयout_cmd_id =
			adapter->dbg.last_cmd_id[adapter->dbg.last_cmd_index];
		adapter->dbg.समयout_cmd_act =
			adapter->dbg.last_cmd_act[adapter->dbg.last_cmd_index];
		mwअगरiex_dbg(adapter, MSG,
			    "%s: Timeout cmd id = %#x, act = %#x\n", __func__,
			    adapter->dbg.समयout_cmd_id,
			    adapter->dbg.समयout_cmd_act);

		mwअगरiex_dbg(adapter, MSG,
			    "num_data_h2c_failure = %d\n",
			    adapter->dbg.num_tx_host_to_card_failure);
		mwअगरiex_dbg(adapter, MSG,
			    "num_cmd_h2c_failure = %d\n",
			    adapter->dbg.num_cmd_host_to_card_failure);

		mwअगरiex_dbg(adapter, MSG,
			    "is_cmd_timedout = %d\n",
			    test_bit(MWIFIEX_IS_CMD_TIMEDOUT,
				     &adapter->work_flags));
		mwअगरiex_dbg(adapter, MSG,
			    "num_tx_timeout = %d\n",
			    adapter->dbg.num_tx_समयout);

		mwअगरiex_dbg(adapter, MSG,
			    "last_cmd_index = %d\n",
			    adapter->dbg.last_cmd_index);
		mwअगरiex_dbg(adapter, MSG,
			    "last_cmd_id: %*ph\n",
			    (पूर्णांक)माप(adapter->dbg.last_cmd_id),
			    adapter->dbg.last_cmd_id);
		mwअगरiex_dbg(adapter, MSG,
			    "last_cmd_act: %*ph\n",
			    (पूर्णांक)माप(adapter->dbg.last_cmd_act),
			    adapter->dbg.last_cmd_act);

		mwअगरiex_dbg(adapter, MSG,
			    "last_cmd_resp_index = %d\n",
			    adapter->dbg.last_cmd_resp_index);
		mwअगरiex_dbg(adapter, MSG,
			    "last_cmd_resp_id: %*ph\n",
			    (पूर्णांक)माप(adapter->dbg.last_cmd_resp_id),
			    adapter->dbg.last_cmd_resp_id);

		mwअगरiex_dbg(adapter, MSG,
			    "last_event_index = %d\n",
			    adapter->dbg.last_event_index);
		mwअगरiex_dbg(adapter, MSG,
			    "last_event: %*ph\n",
			    (पूर्णांक)माप(adapter->dbg.last_event),
			    adapter->dbg.last_event);

		mwअगरiex_dbg(adapter, MSG,
			    "data_sent=%d cmd_sent=%d\n",
			    adapter->data_sent, adapter->cmd_sent);

		mwअगरiex_dbg(adapter, MSG,
			    "ps_mode=%d ps_state=%d\n",
			    adapter->ps_mode, adapter->ps_state);

		अगर (cmd_node->रुको_q_enabled) अणु
			adapter->cmd_रुको_q.status = -ETIMEDOUT;
			mwअगरiex_cancel_pending_ioctl(adapter);
		पूर्ण
	पूर्ण
	अगर (adapter->hw_status == MWIFIEX_HW_STATUS_INITIALIZING) अणु
		mwअगरiex_init_fw_complete(adapter);
		वापस;
	पूर्ण

	अगर (adapter->अगर_ops.device_dump)
		adapter->अगर_ops.device_dump(adapter);

	अगर (adapter->अगर_ops.card_reset)
		adapter->अगर_ops.card_reset(adapter);
पूर्ण

व्योम
mwअगरiex_cancel_pending_scan_cmd(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा cmd_ctrl_node *cmd_node = शून्य, *पंचांगp_node;

	/* Cancel all pending scan command */
	spin_lock_bh(&adapter->scan_pending_q_lock);
	list_क्रम_each_entry_safe(cmd_node, पंचांगp_node,
				 &adapter->scan_pending_q, list) अणु
		list_del(&cmd_node->list);
		cmd_node->रुको_q_enabled = false;
		mwअगरiex_insert_cmd_to_मुक्त_q(adapter, cmd_node);
	पूर्ण
	spin_unlock_bh(&adapter->scan_pending_q_lock);
पूर्ण

/*
 * This function cancels all the pending commands.
 *
 * The current command, all commands in command pending queue and all scan
 * commands in scan pending queue are cancelled. All the completion callbacks
 * are called with failure status to ensure cleanup.
 */
व्योम
mwअगरiex_cancel_all_pending_cmd(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा cmd_ctrl_node *cmd_node = शून्य, *पंचांगp_node;

	spin_lock_bh(&adapter->mwअगरiex_cmd_lock);
	/* Cancel current cmd */
	अगर ((adapter->curr_cmd) && (adapter->curr_cmd->रुको_q_enabled)) अणु
		adapter->cmd_रुको_q.status = -1;
		mwअगरiex_complete_cmd(adapter, adapter->curr_cmd);
		adapter->curr_cmd->रुको_q_enabled = false;
		/* no recycle probably रुको क्रम response */
	पूर्ण
	/* Cancel all pending command */
	spin_lock_bh(&adapter->cmd_pending_q_lock);
	list_क्रम_each_entry_safe(cmd_node, पंचांगp_node,
				 &adapter->cmd_pending_q, list) अणु
		list_del(&cmd_node->list);

		अगर (cmd_node->रुको_q_enabled)
			adapter->cmd_रुको_q.status = -1;
		mwअगरiex_recycle_cmd_node(adapter, cmd_node);
	पूर्ण
	spin_unlock_bh(&adapter->cmd_pending_q_lock);
	spin_unlock_bh(&adapter->mwअगरiex_cmd_lock);

	mwअगरiex_cancel_scan(adapter);
पूर्ण

/*
 * This function cancels all pending commands that matches with
 * the given IOCTL request.
 *
 * Both the current command buffer and the pending command queue are
 * searched क्रम matching IOCTL request. The completion callback of
 * the matched command is called with failure status to ensure cleanup.
 * In हाल of scan commands, all pending commands in scan pending queue
 * are cancelled.
 */
अटल व्योम
mwअगरiex_cancel_pending_ioctl(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा cmd_ctrl_node *cmd_node = शून्य;

	अगर ((adapter->curr_cmd) &&
	    (adapter->curr_cmd->रुको_q_enabled)) अणु
		spin_lock_bh(&adapter->mwअगरiex_cmd_lock);
		cmd_node = adapter->curr_cmd;
		/* setting curr_cmd to शून्य is quite dangerous, because
		 * mwअगरiex_process_cmdresp checks curr_cmd to be != शून्य
		 * at the beginning then relies on it and dereferences
		 * it at will
		 * this probably works since mwअगरiex_cmd_समयout_func
		 * is the only caller of this function and responses
		 * at that poपूर्णांक
		 */
		adapter->curr_cmd = शून्य;
		spin_unlock_bh(&adapter->mwअगरiex_cmd_lock);

		mwअगरiex_recycle_cmd_node(adapter, cmd_node);
	पूर्ण

	mwअगरiex_cancel_scan(adapter);
पूर्ण

/*
 * This function sends the sleep confirm command to firmware, अगर
 * possible.
 *
 * The sleep confirm command cannot be issued अगर command response,
 * data response or event response is aरुकोing handling, or अगर we
 * are in the middle of sending a command, or expecting a command
 * response.
 */
व्योम
mwअगरiex_check_ps_cond(काष्ठा mwअगरiex_adapter *adapter)
अणु
	अगर (!adapter->cmd_sent && !atomic_पढ़ो(&adapter->tx_hw_pending) &&
	    !adapter->curr_cmd && !IS_CARD_RX_RCVD(adapter))
		mwअगरiex_dnld_sleep_confirm_cmd(adapter);
	अन्यथा
		mwअगरiex_dbg(adapter, CMD,
			    "cmd: Delay Sleep Confirm (%s%s%s%s)\n",
			    (adapter->cmd_sent) ? "D" : "",
			    atomic_पढ़ो(&adapter->tx_hw_pending) ? "T" : "",
			    (adapter->curr_cmd) ? "C" : "",
			    (IS_CARD_RX_RCVD(adapter)) ? "R" : "");
पूर्ण

/*
 * This function sends a Host Sleep activated event to applications.
 *
 * This event is generated by the driver, with a blank event body.
 */
व्योम
mwअगरiex_hs_activated_event(काष्ठा mwअगरiex_निजी *priv, u8 activated)
अणु
	अगर (activated) अणु
		अगर (test_bit(MWIFIEX_IS_HS_CONFIGURED,
			     &priv->adapter->work_flags)) अणु
			priv->adapter->hs_activated = true;
			mwअगरiex_update_rxreor_flags(priv->adapter,
						    RXREOR_FORCE_NO_DROP);
			mwअगरiex_dbg(priv->adapter, EVENT,
				    "event: hs_activated\n");
			priv->adapter->hs_activate_रुको_q_woken = true;
			wake_up_पूर्णांकerruptible(
				&priv->adapter->hs_activate_रुको_q);
		पूर्ण अन्यथा अणु
			mwअगरiex_dbg(priv->adapter, EVENT,
				    "event: HS not configured\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		mwअगरiex_dbg(priv->adapter, EVENT,
			    "event: hs_deactivated\n");
		priv->adapter->hs_activated = false;
	पूर्ण
पूर्ण

/*
 * This function handles the command response of a Host Sleep configuration
 * command.
 *
 * Handling includes changing the header fields पूर्णांकo CPU क्रमmat
 * and setting the current host sleep activation status in driver.
 *
 * In हाल host sleep status change, the function generates an event to
 * notअगरy the applications.
 */
पूर्णांक mwअगरiex_ret_802_11_hs_cfg(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा host_cmd_ds_command *resp)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा host_cmd_ds_802_11_hs_cfg_enh *phs_cfg =
		&resp->params.opt_hs_cfg;
	uपूर्णांक32_t conditions = le32_to_cpu(phs_cfg->params.hs_config.conditions);

	अगर (phs_cfg->action == cpu_to_le16(HS_ACTIVATE) &&
	    adapter->अगरace_type != MWIFIEX_USB) अणु
		mwअगरiex_hs_activated_event(priv, true);
		वापस 0;
	पूर्ण अन्यथा अणु
		mwअगरiex_dbg(adapter, CMD,
			    "cmd: CMD_RESP: HS_CFG cmd reply\t"
			    " result=%#x, conditions=0x%x gpio=0x%x gap=0x%x\n",
			    resp->result, conditions,
			    phs_cfg->params.hs_config.gpio,
			    phs_cfg->params.hs_config.gap);
	पूर्ण
	अगर (conditions != HS_CFG_CANCEL) अणु
		set_bit(MWIFIEX_IS_HS_CONFIGURED, &adapter->work_flags);
		अगर (adapter->अगरace_type == MWIFIEX_USB)
			mwअगरiex_hs_activated_event(priv, true);
	पूर्ण अन्यथा अणु
		clear_bit(MWIFIEX_IS_HS_CONFIGURED, &adapter->work_flags);
		अगर (adapter->hs_activated)
			mwअगरiex_hs_activated_event(priv, false);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function wakes up the adapter and generates a Host Sleep
 * cancel event on receiving the घातer up पूर्णांकerrupt.
 */
व्योम
mwअगरiex_process_hs_config(काष्ठा mwअगरiex_adapter *adapter)
अणु
	mwअगरiex_dbg(adapter, INFO,
		    "info: %s: auto cancelling host sleep\t"
		    "since there is interrupt from the firmware\n",
		    __func__);

	adapter->अगर_ops.wakeup(adapter);
	adapter->hs_activated = false;
	clear_bit(MWIFIEX_IS_HS_CONFIGURED, &adapter->work_flags);
	clear_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags);
	mwअगरiex_hs_activated_event(mwअगरiex_get_priv(adapter,
						    MWIFIEX_BSS_ROLE_ANY),
				   false);
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_process_hs_config);

/*
 * This function handles the command response of a sleep confirm command.
 *
 * The function sets the card state to SLEEP अगर the response indicates success.
 */
व्योम
mwअगरiex_process_sleep_confirm_resp(काष्ठा mwअगरiex_adapter *adapter,
				   u8 *pbuf, u32 upld_len)
अणु
	काष्ठा host_cmd_ds_command *cmd = (काष्ठा host_cmd_ds_command *) pbuf;
	काष्ठा mwअगरiex_निजी *priv =
		mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);
	uपूर्णांक16_t result = le16_to_cpu(cmd->result);
	uपूर्णांक16_t command = le16_to_cpu(cmd->command);
	uपूर्णांक16_t seq_num = le16_to_cpu(cmd->seq_num);

	अगर (!upld_len) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: cmd size is 0\n", __func__);
		वापस;
	पूर्ण

	mwअगरiex_dbg(adapter, CMD,
		    "cmd: CMD_RESP: 0x%x, result %d, len %d, seqno 0x%x\n",
		    command, result, le16_to_cpu(cmd->size), seq_num);

	/* Get BSS number and corresponding priv */
	priv = mwअगरiex_get_priv_by_id(adapter, HostCmd_GET_BSS_NO(seq_num),
				      HostCmd_GET_BSS_TYPE(seq_num));
	अगर (!priv)
		priv = mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);

	/* Update sequence number */
	seq_num = HostCmd_GET_SEQ_NO(seq_num);
	/* Clear RET_BIT from HostCmd */
	command &= HostCmd_CMD_ID_MASK;

	अगर (command != HostCmd_CMD_802_11_PS_MODE_ENH) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: rcvd unexpected resp for cmd %#x, result = %x\n",
			    __func__, command, result);
		वापस;
	पूर्ण

	अगर (result) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: sleep confirm cmd failed\n",
			    __func__);
		adapter->pm_wakeup_card_req = false;
		adapter->ps_state = PS_STATE_AWAKE;
		वापस;
	पूर्ण
	adapter->pm_wakeup_card_req = true;
	अगर (test_bit(MWIFIEX_IS_HS_CONFIGURED, &adapter->work_flags))
		mwअगरiex_hs_activated_event(mwअगरiex_get_priv
						(adapter, MWIFIEX_BSS_ROLE_ANY),
					   true);
	adapter->ps_state = PS_STATE_SLEEP;
	cmd->command = cpu_to_le16(command);
	cmd->seq_num = cpu_to_le16(seq_num);
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_process_sleep_confirm_resp);

/*
 * This function prepares an enhanced घातer mode command.
 *
 * This function can be used to disable घातer save or to configure
 * घातer save with स्वतः PS or STA PS or स्वतः deep sleep.
 *
 * Preparation includes -
 *      - Setting command ID, action and proper size
 *      - Setting Power Save biपंचांगap, PS parameters TLV, PS mode TLV,
 *        स्वतः deep sleep TLV (as required)
 *      - Ensuring correct endian-ness
 */
पूर्णांक mwअगरiex_cmd_enh_घातer_mode(काष्ठा mwअगरiex_निजी *priv,
			       काष्ठा host_cmd_ds_command *cmd,
			       u16 cmd_action, uपूर्णांक16_t ps_biपंचांगap,
			       काष्ठा mwअगरiex_ds_स्वतः_ds *स्वतः_ds)
अणु
	काष्ठा host_cmd_ds_802_11_ps_mode_enh *psmode_enh =
		&cmd->params.psmode_enh;
	u8 *tlv;
	u16 cmd_size = 0;

	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_PS_MODE_ENH);
	अगर (cmd_action == DIS_AUTO_PS) अणु
		psmode_enh->action = cpu_to_le16(DIS_AUTO_PS);
		psmode_enh->params.ps_biपंचांगap = cpu_to_le16(ps_biपंचांगap);
		cmd->size = cpu_to_le16(S_DS_GEN + माप(psmode_enh->action) +
					माप(psmode_enh->params.ps_biपंचांगap));
	पूर्ण अन्यथा अगर (cmd_action == GET_PS) अणु
		psmode_enh->action = cpu_to_le16(GET_PS);
		psmode_enh->params.ps_biपंचांगap = cpu_to_le16(ps_biपंचांगap);
		cmd->size = cpu_to_le16(S_DS_GEN + माप(psmode_enh->action) +
					माप(psmode_enh->params.ps_biपंचांगap));
	पूर्ण अन्यथा अगर (cmd_action == EN_AUTO_PS) अणु
		psmode_enh->action = cpu_to_le16(EN_AUTO_PS);
		psmode_enh->params.ps_biपंचांगap = cpu_to_le16(ps_biपंचांगap);
		cmd_size = S_DS_GEN + माप(psmode_enh->action) +
					माप(psmode_enh->params.ps_biपंचांगap);
		tlv = (u8 *) cmd + cmd_size;
		अगर (ps_biपंचांगap & BITMAP_STA_PS) अणु
			काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
			काष्ठा mwअगरiex_ie_types_ps_param *ps_tlv =
				(काष्ठा mwअगरiex_ie_types_ps_param *) tlv;
			काष्ठा mwअगरiex_ps_param *ps_mode = &ps_tlv->param;
			ps_tlv->header.type = cpu_to_le16(TLV_TYPE_PS_PARAM);
			ps_tlv->header.len = cpu_to_le16(माप(*ps_tlv) -
					माप(काष्ठा mwअगरiex_ie_types_header));
			cmd_size += माप(*ps_tlv);
			tlv += माप(*ps_tlv);
			mwअगरiex_dbg(priv->adapter, CMD,
				    "cmd: PS Command: Enter PS\n");
			ps_mode->null_pkt_पूर्णांकerval =
					cpu_to_le16(adapter->null_pkt_पूर्णांकerval);
			ps_mode->multiple_dtims =
					cpu_to_le16(adapter->multiple_dtim);
			ps_mode->bcn_miss_समयout =
					cpu_to_le16(adapter->bcn_miss_समय_out);
			ps_mode->local_listen_पूर्णांकerval =
				cpu_to_le16(adapter->local_listen_पूर्णांकerval);
			ps_mode->adhoc_wake_period =
				cpu_to_le16(adapter->adhoc_awake_period);
			ps_mode->delay_to_ps =
					cpu_to_le16(adapter->delay_to_ps);
			ps_mode->mode = cpu_to_le16(adapter->enhanced_ps_mode);

		पूर्ण
		अगर (ps_biपंचांगap & BITMAP_AUTO_DS) अणु
			काष्ठा mwअगरiex_ie_types_स्वतः_ds_param *स्वतः_ds_tlv =
				(काष्ठा mwअगरiex_ie_types_स्वतः_ds_param *) tlv;
			u16 idleसमय = 0;

			स्वतः_ds_tlv->header.type =
				cpu_to_le16(TLV_TYPE_AUTO_DS_PARAM);
			स्वतः_ds_tlv->header.len =
				cpu_to_le16(माप(*स्वतः_ds_tlv) -
					माप(काष्ठा mwअगरiex_ie_types_header));
			cmd_size += माप(*स्वतः_ds_tlv);
			tlv += माप(*स्वतः_ds_tlv);
			अगर (स्वतः_ds)
				idleसमय = स्वतः_ds->idle_समय;
			mwअगरiex_dbg(priv->adapter, CMD,
				    "cmd: PS Command: Enter Auto Deep Sleep\n");
			स्वतः_ds_tlv->deep_sleep_समयout = cpu_to_le16(idleसमय);
		पूर्ण
		cmd->size = cpu_to_le16(cmd_size);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This function handles the command response of an enhanced घातer mode
 * command.
 *
 * Handling includes changing the header fields पूर्णांकo CPU क्रमmat
 * and setting the current enhanced घातer mode in driver.
 */
पूर्णांक mwअगरiex_ret_enh_घातer_mode(काष्ठा mwअगरiex_निजी *priv,
			       काष्ठा host_cmd_ds_command *resp,
			       काष्ठा mwअगरiex_ds_pm_cfg *pm_cfg)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा host_cmd_ds_802_11_ps_mode_enh *ps_mode =
		&resp->params.psmode_enh;
	uपूर्णांक16_t action = le16_to_cpu(ps_mode->action);
	uपूर्णांक16_t ps_biपंचांगap = le16_to_cpu(ps_mode->params.ps_biपंचांगap);
	uपूर्णांक16_t स्वतः_ps_biपंचांगap =
		le16_to_cpu(ps_mode->params.ps_biपंचांगap);

	mwअगरiex_dbg(adapter, INFO,
		    "info: %s: PS_MODE cmd reply result=%#x action=%#X\n",
		    __func__, resp->result, action);
	अगर (action == EN_AUTO_PS) अणु
		अगर (स्वतः_ps_biपंचांगap & BITMAP_AUTO_DS) अणु
			mwअगरiex_dbg(adapter, CMD,
				    "cmd: Enabled auto deep sleep\n");
			priv->adapter->is_deep_sleep = true;
		पूर्ण
		अगर (स्वतः_ps_biपंचांगap & BITMAP_STA_PS) अणु
			mwअगरiex_dbg(adapter, CMD,
				    "cmd: Enabled STA power save\n");
			अगर (adapter->sleep_period.period)
				mwअगरiex_dbg(adapter, CMD,
					    "cmd: set to uapsd/pps mode\n");
		पूर्ण
	पूर्ण अन्यथा अगर (action == DIS_AUTO_PS) अणु
		अगर (ps_biपंचांगap & BITMAP_AUTO_DS) अणु
			priv->adapter->is_deep_sleep = false;
			mwअगरiex_dbg(adapter, CMD,
				    "cmd: Disabled auto deep sleep\n");
		पूर्ण
		अगर (ps_biपंचांगap & BITMAP_STA_PS) अणु
			mwअगरiex_dbg(adapter, CMD,
				    "cmd: Disabled STA power save\n");
			अगर (adapter->sleep_period.period) अणु
				adapter->delay_null_pkt = false;
				adapter->tx_lock_flag = false;
				adapter->pps_uapsd_mode = false;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (action == GET_PS) अणु
		अगर (ps_biपंचांगap & BITMAP_STA_PS)
			adapter->ps_mode = MWIFIEX_802_11_POWER_MODE_PSP;
		अन्यथा
			adapter->ps_mode = MWIFIEX_802_11_POWER_MODE_CAM;

		mwअगरiex_dbg(adapter, CMD,
			    "cmd: ps_bitmap=%#x\n", ps_biपंचांगap);

		अगर (pm_cfg) अणु
			/* This section is क्रम get घातer save mode */
			अगर (ps_biपंचांगap & BITMAP_STA_PS)
				pm_cfg->param.ps_mode = 1;
			अन्यथा
				pm_cfg->param.ps_mode = 0;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This function prepares command to get hardware specअगरications.
 *
 * Preparation includes -
 *      - Setting command ID, action and proper size
 *      - Setting permanent address parameter
 *      - Ensuring correct endian-ness
 */
पूर्णांक mwअगरiex_cmd_get_hw_spec(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा host_cmd_ds_command *cmd)
अणु
	काष्ठा host_cmd_ds_get_hw_spec *hw_spec = &cmd->params.hw_spec;

	cmd->command = cpu_to_le16(HostCmd_CMD_GET_HW_SPEC);
	cmd->size =
		cpu_to_le16(माप(काष्ठा host_cmd_ds_get_hw_spec) + S_DS_GEN);
	स_नकल(hw_spec->permanent_addr, priv->curr_addr, ETH_ALEN);

	वापस 0;
पूर्ण

/*
 * This function handles the command response of get hardware
 * specअगरications.
 *
 * Handling includes changing the header fields पूर्णांकo CPU क्रमmat
 * and saving/updating the following parameters in driver -
 *      - Firmware capability inक्रमmation
 *      - Firmware band settings
 *      - Ad-hoc start band and channel
 *      - Ad-hoc 11n activation status
 *      - Firmware release number
 *      - Number of antennas
 *      - Hardware address
 *      - Hardware पूर्णांकerface version
 *      - Firmware version
 *      - Region code
 *      - 11n capabilities
 *      - MCS support fields
 *      - MP end port
 */
पूर्णांक mwअगरiex_ret_get_hw_spec(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा host_cmd_ds_command *resp)
अणु
	काष्ठा host_cmd_ds_get_hw_spec *hw_spec = &resp->params.hw_spec;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा mwअगरiex_ie_types_header *tlv;
	काष्ठा hw_spec_api_rev *api_rev;
	काष्ठा hw_spec_max_conn *max_conn;
	u16 resp_size, api_id;
	पूर्णांक i, left_len, parsed_len = 0;

	adapter->fw_cap_info = le32_to_cpu(hw_spec->fw_cap_info);

	अगर (IS_SUPPORT_MULTI_BANDS(adapter))
		adapter->fw_bands = (u8) GET_FW_DEFAULT_BANDS(adapter);
	अन्यथा
		adapter->fw_bands = BAND_B;

	adapter->config_bands = adapter->fw_bands;

	अगर (adapter->fw_bands & BAND_A) अणु
		अगर (adapter->fw_bands & BAND_GN) अणु
			adapter->config_bands |= BAND_AN;
			adapter->fw_bands |= BAND_AN;
		पूर्ण
		अगर (adapter->fw_bands & BAND_AN) अणु
			adapter->adhoc_start_band = BAND_A | BAND_AN;
			adapter->adhoc_11n_enabled = true;
		पूर्ण अन्यथा अणु
			adapter->adhoc_start_band = BAND_A;
		पूर्ण
		priv->adhoc_channel = DEFAULT_AD_HOC_CHANNEL_A;
	पूर्ण अन्यथा अगर (adapter->fw_bands & BAND_GN) अणु
		adapter->adhoc_start_band = BAND_G | BAND_B | BAND_GN;
		priv->adhoc_channel = DEFAULT_AD_HOC_CHANNEL;
		adapter->adhoc_11n_enabled = true;
	पूर्ण अन्यथा अगर (adapter->fw_bands & BAND_G) अणु
		adapter->adhoc_start_band = BAND_G | BAND_B;
		priv->adhoc_channel = DEFAULT_AD_HOC_CHANNEL;
	पूर्ण अन्यथा अगर (adapter->fw_bands & BAND_B) अणु
		adapter->adhoc_start_band = BAND_B;
		priv->adhoc_channel = DEFAULT_AD_HOC_CHANNEL;
	पूर्ण

	adapter->fw_release_number = le32_to_cpu(hw_spec->fw_release_number);
	adapter->fw_api_ver = (adapter->fw_release_number >> 16) & 0xff;
	adapter->number_of_antenna =
			le16_to_cpu(hw_spec->number_of_antenna) & 0xf;

	अगर (le32_to_cpu(hw_spec->करोt_11ac_dev_cap)) अणु
		adapter->is_hw_11ac_capable = true;

		/* Copy 11AC cap */
		adapter->hw_करोt_11ac_dev_cap =
					le32_to_cpu(hw_spec->करोt_11ac_dev_cap);
		adapter->usr_करोt_11ac_dev_cap_bg = adapter->hw_करोt_11ac_dev_cap
					& ~MWIFIEX_DEF_11AC_CAP_BF_RESET_MASK;
		adapter->usr_करोt_11ac_dev_cap_a = adapter->hw_करोt_11ac_dev_cap
					& ~MWIFIEX_DEF_11AC_CAP_BF_RESET_MASK;

		/* Copy 11AC mcs */
		adapter->hw_करोt_11ac_mcs_support =
				le32_to_cpu(hw_spec->करोt_11ac_mcs_support);
		adapter->usr_करोt_11ac_mcs_support =
					adapter->hw_करोt_11ac_mcs_support;
	पूर्ण अन्यथा अणु
		adapter->is_hw_11ac_capable = false;
	पूर्ण

	resp_size = le16_to_cpu(resp->size) - S_DS_GEN;
	अगर (resp_size > माप(काष्ठा host_cmd_ds_get_hw_spec)) अणु
		/* we have variable HW SPEC inक्रमmation */
		left_len = resp_size - माप(काष्ठा host_cmd_ds_get_hw_spec);
		जबतक (left_len > माप(काष्ठा mwअगरiex_ie_types_header)) अणु
			tlv = (व्योम *)&hw_spec->tlvs + parsed_len;
			चयन (le16_to_cpu(tlv->type)) अणु
			हाल TLV_TYPE_API_REV:
				api_rev = (काष्ठा hw_spec_api_rev *)tlv;
				api_id = le16_to_cpu(api_rev->api_id);
				चयन (api_id) अणु
				हाल KEY_API_VER_ID:
					adapter->key_api_major_ver =
							api_rev->major_ver;
					adapter->key_api_minor_ver =
							api_rev->minor_ver;
					mwअगरiex_dbg(adapter, INFO,
						    "key_api v%d.%d\n",
						    adapter->key_api_major_ver,
						    adapter->key_api_minor_ver);
					अवरोध;
				हाल FW_API_VER_ID:
					adapter->fw_api_ver =
							api_rev->major_ver;
					mwअगरiex_dbg(adapter, INFO,
						    "Firmware api version %d.%d\n",
						    adapter->fw_api_ver,
						    api_rev->minor_ver);
					अवरोध;
				हाल UAP_FW_API_VER_ID:
					mwअगरiex_dbg(adapter, INFO,
						    "uAP api version %d.%d\n",
						    api_rev->major_ver,
						    api_rev->minor_ver);
					अवरोध;
				हाल CHANRPT_API_VER_ID:
					mwअगरiex_dbg(adapter, INFO,
						    "channel report api version %d.%d\n",
						    api_rev->major_ver,
						    api_rev->minor_ver);
					अवरोध;
				शेष:
					mwअगरiex_dbg(adapter, FATAL,
						    "Unknown api_id: %d\n",
						    api_id);
					अवरोध;
				पूर्ण
				अवरोध;
			हाल TLV_TYPE_MAX_CONN:
				max_conn = (काष्ठा hw_spec_max_conn *)tlv;
				adapter->max_p2p_conn = max_conn->max_p2p_conn;
				adapter->max_sta_conn = max_conn->max_sta_conn;
				mwअगरiex_dbg(adapter, INFO,
					    "max p2p connections: %u\n",
					    adapter->max_p2p_conn);
				mwअगरiex_dbg(adapter, INFO,
					    "max sta connections: %u\n",
					    adapter->max_sta_conn);
				अवरोध;
			शेष:
				mwअगरiex_dbg(adapter, FATAL,
					    "Unknown GET_HW_SPEC TLV type: %#x\n",
					    le16_to_cpu(tlv->type));
				अवरोध;
			पूर्ण
			parsed_len += le16_to_cpu(tlv->len) +
				      माप(काष्ठा mwअगरiex_ie_types_header);
			left_len -= le16_to_cpu(tlv->len) +
				      माप(काष्ठा mwअगरiex_ie_types_header);
		पूर्ण
	पूर्ण

	mwअगरiex_dbg(adapter, INFO,
		    "info: GET_HW_SPEC: fw_release_number- %#x\n",
		    adapter->fw_release_number);
	mwअगरiex_dbg(adapter, INFO,
		    "info: GET_HW_SPEC: permanent addr: %pM\n",
		    hw_spec->permanent_addr);
	mwअगरiex_dbg(adapter, INFO,
		    "info: GET_HW_SPEC: hw_if_version=%#x version=%#x\n",
		    le16_to_cpu(hw_spec->hw_अगर_version),
		    le16_to_cpu(hw_spec->version));

	ether_addr_copy(priv->adapter->perm_addr, hw_spec->permanent_addr);
	adapter->region_code = le16_to_cpu(hw_spec->region_code);

	क्रम (i = 0; i < MWIFIEX_MAX_REGION_CODE; i++)
		/* Use the region code to search क्रम the index */
		अगर (adapter->region_code == region_code_index[i])
			अवरोध;

	/* If it's unidentअगरied region code, use the शेष (world) */
	अगर (i >= MWIFIEX_MAX_REGION_CODE) अणु
		adapter->region_code = 0x00;
		mwअगरiex_dbg(adapter, WARN,
			    "cmd: unknown region code, use default (USA)\n");
	पूर्ण

	adapter->hw_करोt_11n_dev_cap = le32_to_cpu(hw_spec->करोt_11n_dev_cap);
	adapter->hw_dev_mcs_support = hw_spec->dev_mcs_support;
	adapter->user_dev_mcs_support = adapter->hw_dev_mcs_support;

	अगर (adapter->अगर_ops.update_mp_end_port)
		adapter->अगर_ops.update_mp_end_port(adapter,
					le16_to_cpu(hw_spec->mp_end_port));

	अगर (adapter->fw_api_ver == MWIFIEX_FW_V15)
		adapter->scan_chan_gap_enabled = true;

	वापस 0;
पूर्ण

/* This function handles the command response of hs wakeup reason
 * command.
 */
पूर्णांक mwअगरiex_ret_wakeup_reason(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा host_cmd_ds_command *resp,
			      काष्ठा host_cmd_ds_wakeup_reason *wakeup_reason)
अणु
	wakeup_reason->wakeup_reason =
		resp->params.hs_wakeup_reason.wakeup_reason;

	वापस 0;
पूर्ण
