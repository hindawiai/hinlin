<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  FM Driver क्रम Connectivity chip of Texas Instruments.
 *
 *  This sub-module of FM driver is common क्रम FM RX and TX
 *  functionality. This module is responsible क्रम:
 *  1) Forming group of Channel-8 commands to perक्रमm particular
 *     functionality (eg., frequency set require more than
 *     one Channel-8 command to be sent to the chip).
 *  2) Sending each Channel-8 command to the chip and पढ़ोing
 *     response back over Shared Transport.
 *  3) Managing TX and RX Queues and Tasklets.
 *  4) Handling FM Interrupt packet and taking appropriate action.
 *  5) Loading FM firmware to the chip (common, FM TX, and FM RX
 *     firmware files based on mode selection)
 *
 *  Copyright (C) 2011 Texas Instruments
 *  Author: Raja Mani <raja_mani@ti.com>
 *  Author: Manjunatha Halli <manjunatha_halli@ti.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/nospec.h>

#समावेश "fmdrv.h"
#समावेश "fmdrv_v4l2.h"
#समावेश "fmdrv_common.h"
#समावेश <linux/ti_wilink_st.h>
#समावेश "fmdrv_rx.h"
#समावेश "fmdrv_tx.h"

/* Region info */
अटल काष्ठा region_info region_configs[] = अणु
	/* Europe/US */
	अणु
	 .chanl_space = FM_CHANNEL_SPACING_200KHZ * FM_FREQ_MUL,
	 .bot_freq = 87500,	/* 87.5 MHz */
	 .top_freq = 108000,	/* 108 MHz */
	 .fm_band = 0,
	 पूर्ण,
	/* Japan */
	अणु
	 .chanl_space = FM_CHANNEL_SPACING_200KHZ * FM_FREQ_MUL,
	 .bot_freq = 76000,	/* 76 MHz */
	 .top_freq = 90000,	/* 90 MHz */
	 .fm_band = 1,
	 पूर्ण,
पूर्ण;

/* Band selection */
अटल u8 शेष_radio_region;	/* Europe/US */
module_param(शेष_radio_region, byte, 0);
MODULE_PARM_DESC(शेष_radio_region, "Region: 0=Europe/US, 1=Japan");

/* RDS buffer blocks */
अटल u32 शेष_rds_buf = 300;
module_param(शेष_rds_buf, uपूर्णांक, 0444);
MODULE_PARM_DESC(शेष_rds_buf, "RDS buffer entries");

/* Radio Nr */
अटल u32 radio_nr = -1;
module_param(radio_nr, पूर्णांक, 0444);
MODULE_PARM_DESC(radio_nr, "Radio Nr");

/* FM irq handlers क्रमward declaration */
अटल व्योम fm_irq_send_flag_अ_लोmd(काष्ठा fmdev *);
अटल व्योम fm_irq_handle_flag_अ_लोmd_resp(काष्ठा fmdev *);
अटल व्योम fm_irq_handle_hw_malfunction(काष्ठा fmdev *);
अटल व्योम fm_irq_handle_rds_start(काष्ठा fmdev *);
अटल व्योम fm_irq_send_rdsdata_अ_लोmd(काष्ठा fmdev *);
अटल व्योम fm_irq_handle_rdsdata_अ_लोmd_resp(काष्ठा fmdev *);
अटल व्योम fm_irq_handle_rds_finish(काष्ठा fmdev *);
अटल व्योम fm_irq_handle_tune_op_ended(काष्ठा fmdev *);
अटल व्योम fm_irq_handle_घातer_enb(काष्ठा fmdev *);
अटल व्योम fm_irq_handle_low_rssi_start(काष्ठा fmdev *);
अटल व्योम fm_irq_afjump_set_pi(काष्ठा fmdev *);
अटल व्योम fm_irq_handle_set_pi_resp(काष्ठा fmdev *);
अटल व्योम fm_irq_afjump_set_pimask(काष्ठा fmdev *);
अटल व्योम fm_irq_handle_set_pimask_resp(काष्ठा fmdev *);
अटल व्योम fm_irq_afjump_setfreq(काष्ठा fmdev *);
अटल व्योम fm_irq_handle_setfreq_resp(काष्ठा fmdev *);
अटल व्योम fm_irq_afjump_enableपूर्णांक(काष्ठा fmdev *);
अटल व्योम fm_irq_afjump_enableपूर्णांक_resp(काष्ठा fmdev *);
अटल व्योम fm_irq_start_afjump(काष्ठा fmdev *);
अटल व्योम fm_irq_handle_start_afjump_resp(काष्ठा fmdev *);
अटल व्योम fm_irq_afjump_rd_freq(काष्ठा fmdev *);
अटल व्योम fm_irq_afjump_rd_freq_resp(काष्ठा fmdev *);
अटल व्योम fm_irq_handle_low_rssi_finish(काष्ठा fmdev *);
अटल व्योम fm_irq_send_पूर्णांकmsk_cmd(काष्ठा fmdev *);
अटल व्योम fm_irq_handle_पूर्णांकmsk_cmd_resp(काष्ठा fmdev *);

/*
 * When FM common module receives पूर्णांकerrupt packet, following handlers
 * will be executed one after another to service the पूर्णांकerrupt(s)
 */
क्रमागत fmc_irq_handler_index अणु
	FM_SEND_FLAG_GETCMD_IDX,
	FM_HANDLE_FLAG_GETCMD_RESP_IDX,

	/* HW malfunction irq handler */
	FM_HW_MAL_FUNC_IDX,

	/* RDS threshold reached irq handler */
	FM_RDS_START_IDX,
	FM_RDS_SEND_RDS_GETCMD_IDX,
	FM_RDS_HANDLE_RDS_GETCMD_RESP_IDX,
	FM_RDS_FINISH_IDX,

	/* Tune operation ended irq handler */
	FM_HW_TUNE_OP_ENDED_IDX,

	/* TX घातer enable irq handler */
	FM_HW_POWER_ENB_IDX,

	/* Low RSSI irq handler */
	FM_LOW_RSSI_START_IDX,
	FM_AF_JUMP_SETPI_IDX,
	FM_AF_JUMP_HANDLE_SETPI_RESP_IDX,
	FM_AF_JUMP_SETPI_MASK_IDX,
	FM_AF_JUMP_HANDLE_SETPI_MASK_RESP_IDX,
	FM_AF_JUMP_SET_AF_FREQ_IDX,
	FM_AF_JUMP_HANDLE_SET_AFFREQ_RESP_IDX,
	FM_AF_JUMP_ENABLE_INT_IDX,
	FM_AF_JUMP_ENABLE_INT_RESP_IDX,
	FM_AF_JUMP_START_AFJUMP_IDX,
	FM_AF_JUMP_HANDLE_START_AFJUMP_RESP_IDX,
	FM_AF_JUMP_RD_FREQ_IDX,
	FM_AF_JUMP_RD_FREQ_RESP_IDX,
	FM_LOW_RSSI_FINISH_IDX,

	/* Interrupt process post action */
	FM_SEND_INTMSK_CMD_IDX,
	FM_HANDLE_INTMSK_CMD_RESP_IDX,
पूर्ण;

/* FM पूर्णांकerrupt handler table */
अटल पूर्णांक_handler_prototype पूर्णांक_handler_table[] = अणु
	fm_irq_send_flag_अ_लोmd,
	fm_irq_handle_flag_अ_लोmd_resp,
	fm_irq_handle_hw_malfunction,
	fm_irq_handle_rds_start, /* RDS threshold reached irq handler */
	fm_irq_send_rdsdata_अ_लोmd,
	fm_irq_handle_rdsdata_अ_लोmd_resp,
	fm_irq_handle_rds_finish,
	fm_irq_handle_tune_op_ended,
	fm_irq_handle_घातer_enb, /* TX घातer enable irq handler */
	fm_irq_handle_low_rssi_start,
	fm_irq_afjump_set_pi,
	fm_irq_handle_set_pi_resp,
	fm_irq_afjump_set_pimask,
	fm_irq_handle_set_pimask_resp,
	fm_irq_afjump_setfreq,
	fm_irq_handle_setfreq_resp,
	fm_irq_afjump_enableपूर्णांक,
	fm_irq_afjump_enableपूर्णांक_resp,
	fm_irq_start_afjump,
	fm_irq_handle_start_afjump_resp,
	fm_irq_afjump_rd_freq,
	fm_irq_afjump_rd_freq_resp,
	fm_irq_handle_low_rssi_finish,
	fm_irq_send_पूर्णांकmsk_cmd, /* Interrupt process post action */
	fm_irq_handle_पूर्णांकmsk_cmd_resp
पूर्ण;

अटल दीर्घ (*g_st_ग_लिखो) (काष्ठा sk_buff *skb);
अटल काष्ठा completion रुको_क्रम_fmdrv_reg_comp;

अटल अंतरभूत व्योम fm_irq_call(काष्ठा fmdev *fmdev)
अणु
	fmdev->irq_info.handlers[fmdev->irq_info.stage](fmdev);
पूर्ण

/* Continue next function in पूर्णांकerrupt handler table */
अटल अंतरभूत व्योम fm_irq_call_stage(काष्ठा fmdev *fmdev, u8 stage)
अणु
	fmdev->irq_info.stage = stage;
	fm_irq_call(fmdev);
पूर्ण

अटल अंतरभूत व्योम fm_irq_समयout_stage(काष्ठा fmdev *fmdev, u8 stage)
अणु
	fmdev->irq_info.stage = stage;
	mod_समयr(&fmdev->irq_info.समयr, jअगरfies + FM_DRV_TX_TIMEOUT);
पूर्ण

#अगर_घोषित FM_DUMP_TXRX_PKT
 /* To dump outgoing FM Channel-8 packets */
अंतरभूत व्योम dump_tx_skb_data(काष्ठा sk_buff *skb)
अणु
	पूर्णांक len, len_org;
	u8 index;
	काष्ठा fm_cmd_msg_hdr *cmd_hdr;

	cmd_hdr = (काष्ठा fm_cmd_msg_hdr *)skb->data;
	prपूर्णांकk(KERN_INFO "<<%shdr:%02x len:%02x opcode:%02x type:%s dlen:%02x",
	       fm_cb(skb)->completion ? " " : "*", cmd_hdr->hdr,
	       cmd_hdr->len, cmd_hdr->op,
	       cmd_hdr->rd_wr ? "RD" : "WR", cmd_hdr->dlen);

	len_org = skb->len - FM_CMD_MSG_HDR_SIZE;
	अगर (len_org > 0) अणु
		prपूर्णांकk(KERN_CONT "\n   data(%d): ", cmd_hdr->dlen);
		len = min(len_org, 14);
		क्रम (index = 0; index < len; index++)
			prपूर्णांकk(KERN_CONT "%x ",
			       skb->data[FM_CMD_MSG_HDR_SIZE + index]);
		prपूर्णांकk(KERN_CONT "%s", (len_org > 14) ? ".." : "");
	पूर्ण
	prपूर्णांकk(KERN_CONT "\n");
पूर्ण

 /* To dump incoming FM Channel-8 packets */
अंतरभूत व्योम dump_rx_skb_data(काष्ठा sk_buff *skb)
अणु
	पूर्णांक len, len_org;
	u8 index;
	काष्ठा fm_event_msg_hdr *evt_hdr;

	evt_hdr = (काष्ठा fm_event_msg_hdr *)skb->data;
	prपूर्णांकk(KERN_INFO ">> hdr:%02x len:%02x sts:%02x numhci:%02x opcode:%02x type:%s dlen:%02x",
	       evt_hdr->hdr, evt_hdr->len,
	       evt_hdr->status, evt_hdr->num_fm_hci_cmds, evt_hdr->op,
	       (evt_hdr->rd_wr) ? "RD" : "WR", evt_hdr->dlen);

	len_org = skb->len - FM_EVT_MSG_HDR_SIZE;
	अगर (len_org > 0) अणु
		prपूर्णांकk(KERN_CONT "\n   data(%d): ", evt_hdr->dlen);
		len = min(len_org, 14);
		क्रम (index = 0; index < len; index++)
			prपूर्णांकk(KERN_CONT "%x ",
			       skb->data[FM_EVT_MSG_HDR_SIZE + index]);
		prपूर्णांकk(KERN_CONT "%s", (len_org > 14) ? ".." : "");
	पूर्ण
	prपूर्णांकk(KERN_CONT "\n");
पूर्ण
#पूर्ण_अगर

व्योम fmc_update_region_info(काष्ठा fmdev *fmdev, u8 region_to_set)
अणु
	fmdev->rx.region = region_configs[region_to_set];
पूर्ण

/*
 * FM common sub-module will schedule this tasklet whenever it receives
 * FM packet from ST driver.
 */
अटल व्योम recv_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा fmdev *fmdev;
	काष्ठा fm_irq *irq_info;
	काष्ठा fm_event_msg_hdr *evt_hdr;
	काष्ठा sk_buff *skb;
	u8 num_fm_hci_cmds;
	अचिन्हित दीर्घ flags;

	fmdev = from_tasklet(fmdev, t, tx_task);
	irq_info = &fmdev->irq_info;
	/* Process all packets in the RX queue */
	जबतक ((skb = skb_dequeue(&fmdev->rx_q))) अणु
		अगर (skb->len < माप(काष्ठा fm_event_msg_hdr)) अणु
			fmerr("skb(%p) has only %d bytes, at least need %zu bytes to decode\n",
			      skb,
			      skb->len, माप(काष्ठा fm_event_msg_hdr));
			kमुक्त_skb(skb);
			जारी;
		पूर्ण

		evt_hdr = (व्योम *)skb->data;
		num_fm_hci_cmds = evt_hdr->num_fm_hci_cmds;

		/* FM पूर्णांकerrupt packet? */
		अगर (evt_hdr->op == FM_INTERRUPT) अणु
			/* FM पूर्णांकerrupt handler started alपढ़ोy? */
			अगर (!test_bit(FM_INTTASK_RUNNING, &fmdev->flag)) अणु
				set_bit(FM_INTTASK_RUNNING, &fmdev->flag);
				अगर (irq_info->stage != 0) अणु
					fmerr("Inval stage resetting to zero\n");
					irq_info->stage = 0;
				पूर्ण

				/*
				 * Execute first function in पूर्णांकerrupt handler
				 * table.
				 */
				irq_info->handlers[irq_info->stage](fmdev);
			पूर्ण अन्यथा अणु
				set_bit(FM_INTTASK_SCHEDULE_PENDING, &fmdev->flag);
			पूर्ण
			kमुक्त_skb(skb);
		पूर्ण
		/* Anyone रुकोing क्रम this with completion handler? */
		अन्यथा अगर (evt_hdr->op == fmdev->pre_op && fmdev->resp_comp != शून्य) अणु

			spin_lock_irqsave(&fmdev->resp_skb_lock, flags);
			fmdev->resp_skb = skb;
			spin_unlock_irqrestore(&fmdev->resp_skb_lock, flags);
			complete(fmdev->resp_comp);

			fmdev->resp_comp = शून्य;
			atomic_set(&fmdev->tx_cnt, 1);
		पूर्ण
		/* Is this क्रम पूर्णांकerrupt handler? */
		अन्यथा अगर (evt_hdr->op == fmdev->pre_op && fmdev->resp_comp == शून्य) अणु
			अगर (fmdev->resp_skb != शून्य)
				fmerr("Response SKB ptr not NULL\n");

			spin_lock_irqsave(&fmdev->resp_skb_lock, flags);
			fmdev->resp_skb = skb;
			spin_unlock_irqrestore(&fmdev->resp_skb_lock, flags);

			/* Execute पूर्णांकerrupt handler where state index poपूर्णांकs */
			irq_info->handlers[irq_info->stage](fmdev);

			kमुक्त_skb(skb);
			atomic_set(&fmdev->tx_cnt, 1);
		पूर्ण अन्यथा अणु
			fmerr("Nobody claimed SKB(%p),purging\n", skb);
		पूर्ण

		/*
		 * Check flow control field. If Num_FM_HCI_Commands field is
		 * not zero, schedule FM TX tasklet.
		 */
		अगर (num_fm_hci_cmds && atomic_पढ़ो(&fmdev->tx_cnt))
			अगर (!skb_queue_empty(&fmdev->tx_q))
				tasklet_schedule(&fmdev->tx_task);
	पूर्ण
पूर्ण

/* FM send tasklet: is scheduled when FM packet has to be sent to chip */
अटल व्योम send_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा fmdev *fmdev;
	काष्ठा sk_buff *skb;
	पूर्णांक len;

	fmdev = from_tasklet(fmdev, t, tx_task);

	अगर (!atomic_पढ़ो(&fmdev->tx_cnt))
		वापस;

	/* Check, is there any समयout happened to last transmitted packet */
	अगर ((jअगरfies - fmdev->last_tx_jअगरfies) > FM_DRV_TX_TIMEOUT) अणु
		fmerr("TX timeout occurred\n");
		atomic_set(&fmdev->tx_cnt, 1);
	पूर्ण

	/* Send queued FM TX packets */
	skb = skb_dequeue(&fmdev->tx_q);
	अगर (!skb)
		वापस;

	atomic_dec(&fmdev->tx_cnt);
	fmdev->pre_op = fm_cb(skb)->fm_op;

	अगर (fmdev->resp_comp != शून्य)
		fmerr("Response completion handler is not NULL\n");

	fmdev->resp_comp = fm_cb(skb)->completion;

	/* Write FM packet to ST driver */
	len = g_st_ग_लिखो(skb);
	अगर (len < 0) अणु
		kमुक्त_skb(skb);
		fmdev->resp_comp = शून्य;
		fmerr("TX tasklet failed to send skb(%p)\n", skb);
		atomic_set(&fmdev->tx_cnt, 1);
	पूर्ण अन्यथा अणु
		fmdev->last_tx_jअगरfies = jअगरfies;
	पूर्ण
पूर्ण

/*
 * Queues FM Channel-8 packet to FM TX queue and schedules FM TX tasklet क्रम
 * transmission
 */
अटल पूर्णांक fm_send_cmd(काष्ठा fmdev *fmdev, u8 fm_op, u16 type,	व्योम *payload,
		पूर्णांक payload_len, काष्ठा completion *रुको_completion)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा fm_cmd_msg_hdr *hdr;
	पूर्णांक size;

	अगर (fm_op >= FM_INTERRUPT) अणु
		fmerr("Invalid fm opcode - %d\n", fm_op);
		वापस -EINVAL;
	पूर्ण
	अगर (test_bit(FM_FW_DW_INPROGRESS, &fmdev->flag) && payload == शून्य) अणु
		fmerr("Payload data is NULL during fw download\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!test_bit(FM_FW_DW_INPROGRESS, &fmdev->flag))
		size =
		    FM_CMD_MSG_HDR_SIZE + ((payload == शून्य) ? 0 : payload_len);
	अन्यथा
		size = payload_len;

	skb = alloc_skb(size, GFP_ATOMIC);
	अगर (!skb) अणु
		fmerr("No memory to create new SKB\n");
		वापस -ENOMEM;
	पूर्ण
	/*
	 * Don't fill FM header info क्रम the commands which come from
	 * FM firmware file.
	 */
	अगर (!test_bit(FM_FW_DW_INPROGRESS, &fmdev->flag) ||
			test_bit(FM_INTTASK_RUNNING, &fmdev->flag)) अणु
		/* Fill command header info */
		hdr = skb_put(skb, FM_CMD_MSG_HDR_SIZE);
		hdr->hdr = FM_PKT_LOGICAL_CHAN_NUMBER;	/* 0x08 */

		/* 3 (fm_opcode,rd_wr,dlen) + payload len) */
		hdr->len = ((payload == शून्य) ? 0 : payload_len) + 3;

		/* FM opcode */
		hdr->op = fm_op;

		/* पढ़ो/ग_लिखो type */
		hdr->rd_wr = type;
		hdr->dlen = payload_len;
		fm_cb(skb)->fm_op = fm_op;

		/*
		 * If firmware करोwnload has finished and the command is
		 * not a पढ़ो command then payload is != शून्य - a ग_लिखो
		 * command with u16 payload - convert to be16
		 */
		अगर (payload != शून्य)
			*(__be16 *)payload = cpu_to_be16(*(u16 *)payload);

	पूर्ण अन्यथा अगर (payload != शून्य) अणु
		fm_cb(skb)->fm_op = *((u8 *)payload + 2);
	पूर्ण
	अगर (payload != शून्य)
		skb_put_data(skb, payload, payload_len);

	fm_cb(skb)->completion = रुको_completion;
	skb_queue_tail(&fmdev->tx_q, skb);
	tasklet_schedule(&fmdev->tx_task);

	वापस 0;
पूर्ण

/* Sends FM Channel-8 command to the chip and रुकोs क्रम the response */
पूर्णांक fmc_send_cmd(काष्ठा fmdev *fmdev, u8 fm_op, u16 type, व्योम *payload,
		अचिन्हित पूर्णांक payload_len, व्योम *response, पूर्णांक *response_len)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा fm_event_msg_hdr *evt_hdr;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	init_completion(&fmdev->मुख्यtask_comp);
	ret = fm_send_cmd(fmdev, fm_op, type, payload, payload_len,
			    &fmdev->मुख्यtask_comp);
	अगर (ret)
		वापस ret;

	अगर (!रुको_क्रम_completion_समयout(&fmdev->मुख्यtask_comp,
					 FM_DRV_TX_TIMEOUT)) अणु
		fmerr("Timeout(%d sec),didn't get regcompletion signal from RX tasklet\n",
			   jअगरfies_to_msecs(FM_DRV_TX_TIMEOUT) / 1000);
		वापस -ETIMEDOUT;
	पूर्ण
	अगर (!fmdev->resp_skb) अणु
		fmerr("Response SKB is missing\n");
		वापस -EFAULT;
	पूर्ण
	spin_lock_irqsave(&fmdev->resp_skb_lock, flags);
	skb = fmdev->resp_skb;
	fmdev->resp_skb = शून्य;
	spin_unlock_irqrestore(&fmdev->resp_skb_lock, flags);

	evt_hdr = (व्योम *)skb->data;
	अगर (evt_hdr->status != 0) अणु
		fmerr("Received event pkt status(%d) is not zero\n",
			   evt_hdr->status);
		kमुक्त_skb(skb);
		वापस -EIO;
	पूर्ण
	/* Send response data to caller */
	अगर (response != शून्य && response_len != शून्य && evt_hdr->dlen &&
	    evt_hdr->dlen <= payload_len) अणु
		/* Skip header info and copy only response data */
		skb_pull(skb, माप(काष्ठा fm_event_msg_hdr));
		स_नकल(response, skb->data, evt_hdr->dlen);
		*response_len = evt_hdr->dlen;
	पूर्ण अन्यथा अगर (response_len != शून्य && evt_hdr->dlen == 0) अणु
		*response_len = 0;
	पूर्ण
	kमुक्त_skb(skb);

	वापस 0;
पूर्ण

/* --- Helper functions used in FM पूर्णांकerrupt handlers ---*/
अटल अंतरभूत पूर्णांक check_cmdresp_status(काष्ठा fmdev *fmdev,
		काष्ठा sk_buff **skb)
अणु
	काष्ठा fm_event_msg_hdr *fm_evt_hdr;
	अचिन्हित दीर्घ flags;

	del_समयr(&fmdev->irq_info.समयr);

	spin_lock_irqsave(&fmdev->resp_skb_lock, flags);
	*skb = fmdev->resp_skb;
	fmdev->resp_skb = शून्य;
	spin_unlock_irqrestore(&fmdev->resp_skb_lock, flags);

	fm_evt_hdr = (व्योम *)(*skb)->data;
	अगर (fm_evt_hdr->status != 0) अणु
		fmerr("irq: opcode %x response status is not zero Initiating irq recovery process\n",
				fm_evt_hdr->op);

		mod_समयr(&fmdev->irq_info.समयr, jअगरfies + FM_DRV_TX_TIMEOUT);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम fm_irq_common_cmd_resp_helper(काष्ठा fmdev *fmdev, u8 stage)
अणु
	काष्ठा sk_buff *skb;

	अगर (!check_cmdresp_status(fmdev, &skb))
		fm_irq_call_stage(fmdev, stage);
पूर्ण

/*
 * Interrupt process समयout handler.
 * One of the irq handler did not get proper response from the chip. So take
 * recovery action here. FM पूर्णांकerrupts are disabled in the beginning of
 * पूर्णांकerrupt process. Thereक्रमe reset stage index to re-enable शेष
 * पूर्णांकerrupts. So that next पूर्णांकerrupt will be processed as usual.
 */
अटल व्योम पूर्णांक_समयout_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा fmdev *fmdev;
	काष्ठा fm_irq *fmirq;

	fmdbg("irq: timeout,trying to re-enable fm interrupts\n");
	fmdev = from_समयr(fmdev, t, irq_info.समयr);
	fmirq = &fmdev->irq_info;
	fmirq->retry++;

	अगर (fmirq->retry > FM_IRQ_TIMEOUT_RETRY_MAX) अणु
		/* Stop recovery action (पूर्णांकerrupt reenable process) and
		 * reset stage index & retry count values */
		fmirq->stage = 0;
		fmirq->retry = 0;
		fmerr("Recovery action failed duringirq processing, max retry reached\n");
		वापस;
	पूर्ण
	fm_irq_call_stage(fmdev, FM_SEND_INTMSK_CMD_IDX);
पूर्ण

/* --------- FM पूर्णांकerrupt handlers ------------*/
अटल व्योम fm_irq_send_flag_अ_लोmd(काष्ठा fmdev *fmdev)
अणु
	u16 flag;

	/* Send FLAG_GET command , to know the source of पूर्णांकerrupt */
	अगर (!fm_send_cmd(fmdev, FLAG_GET, REG_RD, शून्य, माप(flag), शून्य))
		fm_irq_समयout_stage(fmdev, FM_HANDLE_FLAG_GETCMD_RESP_IDX);
पूर्ण

अटल व्योम fm_irq_handle_flag_अ_लोmd_resp(काष्ठा fmdev *fmdev)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा fm_event_msg_hdr *fm_evt_hdr;

	अगर (check_cmdresp_status(fmdev, &skb))
		वापस;

	fm_evt_hdr = (व्योम *)skb->data;
	अगर (fm_evt_hdr->dlen > माप(fmdev->irq_info.flag))
		वापस;

	/* Skip header info and copy only response data */
	skb_pull(skb, माप(काष्ठा fm_event_msg_hdr));
	स_नकल(&fmdev->irq_info.flag, skb->data, fm_evt_hdr->dlen);

	fmdev->irq_info.flag = be16_to_cpu((__क्रमce __be16)fmdev->irq_info.flag);
	fmdbg("irq: flag register(0x%x)\n", fmdev->irq_info.flag);

	/* Continue next function in पूर्णांकerrupt handler table */
	fm_irq_call_stage(fmdev, FM_HW_MAL_FUNC_IDX);
पूर्ण

अटल व्योम fm_irq_handle_hw_malfunction(काष्ठा fmdev *fmdev)
अणु
	अगर (fmdev->irq_info.flag & FM_MAL_EVENT & fmdev->irq_info.mask)
		fmerr("irq: HW MAL int received - do nothing\n");

	/* Continue next function in पूर्णांकerrupt handler table */
	fm_irq_call_stage(fmdev, FM_RDS_START_IDX);
पूर्ण

अटल व्योम fm_irq_handle_rds_start(काष्ठा fmdev *fmdev)
अणु
	अगर (fmdev->irq_info.flag & FM_RDS_EVENT & fmdev->irq_info.mask) अणु
		fmdbg("irq: rds threshold reached\n");
		fmdev->irq_info.stage = FM_RDS_SEND_RDS_GETCMD_IDX;
	पूर्ण अन्यथा अणु
		/* Continue next function in पूर्णांकerrupt handler table */
		fmdev->irq_info.stage = FM_HW_TUNE_OP_ENDED_IDX;
	पूर्ण

	fm_irq_call(fmdev);
पूर्ण

अटल व्योम fm_irq_send_rdsdata_अ_लोmd(काष्ठा fmdev *fmdev)
अणु
	/* Send the command to पढ़ो RDS data from the chip */
	अगर (!fm_send_cmd(fmdev, RDS_DATA_GET, REG_RD, शून्य,
			    (FM_RX_RDS_FIFO_THRESHOLD * 3), शून्य))
		fm_irq_समयout_stage(fmdev, FM_RDS_HANDLE_RDS_GETCMD_RESP_IDX);
पूर्ण

/* Keeps track of current RX channel AF (Alternate Frequency) */
अटल व्योम fm_rx_update_af_cache(काष्ठा fmdev *fmdev, u8 af)
अणु
	काष्ठा tuned_station_info *stat_info = &fmdev->rx.stat_info;
	u8 reg_idx = fmdev->rx.region.fm_band;
	u8 index;
	u32 freq;

	/* First AF indicates the number of AF follows. Reset the list */
	अगर ((af >= FM_RDS_1_AF_FOLLOWS) && (af <= FM_RDS_25_AF_FOLLOWS)) अणु
		fmdev->rx.stat_info.af_list_max = (af - FM_RDS_1_AF_FOLLOWS + 1);
		fmdev->rx.stat_info.afcache_size = 0;
		fmdbg("No of expected AF : %d\n", fmdev->rx.stat_info.af_list_max);
		वापस;
	पूर्ण

	अगर (af < FM_RDS_MIN_AF)
		वापस;
	अगर (reg_idx == FM_BAND_EUROPE_US && af > FM_RDS_MAX_AF)
		वापस;
	अगर (reg_idx == FM_BAND_JAPAN && af > FM_RDS_MAX_AF_JAPAN)
		वापस;

	freq = fmdev->rx.region.bot_freq + (af * 100);
	अगर (freq == fmdev->rx.freq) अणु
		fmdbg("Current freq(%d) is matching with received AF(%d)\n",
				fmdev->rx.freq, freq);
		वापस;
	पूर्ण
	/* Do check in AF cache */
	क्रम (index = 0; index < stat_info->afcache_size; index++) अणु
		अगर (stat_info->af_cache[index] == freq)
			अवरोध;
	पूर्ण
	/* Reached the limit of the list - ignore the next AF */
	अगर (index == stat_info->af_list_max) अणु
		fmdbg("AF cache is full\n");
		वापस;
	पूर्ण
	/*
	 * If we reached the end of the list then this AF is not
	 * in the list - add it.
	 */
	अगर (index == stat_info->afcache_size) अणु
		fmdbg("Storing AF %d to cache index %d\n", freq, index);
		stat_info->af_cache[index] = freq;
		stat_info->afcache_size++;
	पूर्ण
पूर्ण

/*
 * Converts RDS buffer data from big endian क्रमmat
 * to little endian क्रमmat.
 */
अटल व्योम fm_rdsparse_swapbytes(काष्ठा fmdev *fmdev,
		काष्ठा fm_rdsdata_क्रमmat *rds_क्रमmat)
अणु
	u8 index = 0;
	u8 *rds_buff;

	/*
	 * Since in Orca the 2 RDS Data bytes are in little endian and
	 * in Dolphin they are in big endian, the parsing of the RDS data
	 * is chip dependent
	 */
	अगर (fmdev->asci_id != 0x6350) अणु
		rds_buff = &rds_क्रमmat->data.groupdatabuff.buff[0];
		जबतक (index + 1 < FM_RX_RDS_INFO_FIELD_MAX) अणु
			swap(rds_buff[index], rds_buff[index + 1]);
			index += 2;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम fm_irq_handle_rdsdata_अ_लोmd_resp(काष्ठा fmdev *fmdev)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा fm_rdsdata_क्रमmat rds_fmt;
	काष्ठा fm_rds *rds = &fmdev->rx.rds;
	अचिन्हित दीर्घ group_idx, flags;
	u8 *rds_data, meta_data, पंचांगpbuf[FM_RDS_BLK_SIZE];
	u8 type, blk_idx, idx;
	u16 cur_picode;
	u32 rds_len;

	अगर (check_cmdresp_status(fmdev, &skb))
		वापस;

	/* Skip header info */
	skb_pull(skb, माप(काष्ठा fm_event_msg_hdr));
	rds_data = skb->data;
	rds_len = skb->len;

	/* Parse the RDS data */
	जबतक (rds_len >= FM_RDS_BLK_SIZE) अणु
		meta_data = rds_data[2];
		/* Get the type: 0=A, 1=B, 2=C, 3=C', 4=D, 5=E */
		type = (meta_data & 0x07);

		/* Transक्रमm the blk type पूर्णांकo index sequence (0, 1, 2, 3, 4) */
		blk_idx = (type <= FM_RDS_BLOCK_C ? type : (type - 1));
		fmdbg("Block index:%d(%s)\n", blk_idx,
			   (meta_data & FM_RDS_STATUS_ERR_MASK) ? "Bad" : "Ok");

		अगर ((meta_data & FM_RDS_STATUS_ERR_MASK) != 0)
			अवरोध;

		अगर (blk_idx > FM_RDS_BLK_IDX_D) अणु
			fmdbg("Block sequence mismatch\n");
			rds->last_blk_idx = -1;
			अवरोध;
		पूर्ण

		/* Skip checkword (control) byte and copy only data byte */
		idx = array_index_nospec(blk_idx * (FM_RDS_BLK_SIZE - 1),
					 FM_RX_RDS_INFO_FIELD_MAX - (FM_RDS_BLK_SIZE - 1));

		स_नकल(&rds_fmt.data.groupdatabuff.buff[idx], rds_data,
		       FM_RDS_BLK_SIZE - 1);

		rds->last_blk_idx = blk_idx;

		/* If completed a whole group then handle it */
		अगर (blk_idx == FM_RDS_BLK_IDX_D) अणु
			fmdbg("Good block received\n");
			fm_rdsparse_swapbytes(fmdev, &rds_fmt);

			/*
			 * Extract PI code and store in local cache.
			 * We need this during AF चयन processing.
			 */
			cur_picode = be16_to_cpu((__क्रमce __be16)rds_fmt.data.groupgeneral.pidata);
			अगर (fmdev->rx.stat_info.picode != cur_picode)
				fmdev->rx.stat_info.picode = cur_picode;

			fmdbg("picode:%d\n", cur_picode);

			group_idx = (rds_fmt.data.groupgeneral.blk_b[0] >> 3);
			fmdbg("(fmdrv):Group:%ld%s\n", group_idx/2,
					(group_idx % 2) ? "B" : "A");

			group_idx = 1 << (rds_fmt.data.groupgeneral.blk_b[0] >> 3);
			अगर (group_idx == FM_RDS_GROUP_TYPE_MASK_0A) अणु
				fm_rx_update_af_cache(fmdev, rds_fmt.data.group0A.af[0]);
				fm_rx_update_af_cache(fmdev, rds_fmt.data.group0A.af[1]);
			पूर्ण
		पूर्ण
		rds_len -= FM_RDS_BLK_SIZE;
		rds_data += FM_RDS_BLK_SIZE;
	पूर्ण

	/* Copy raw rds data to पूर्णांकernal rds buffer */
	rds_data = skb->data;
	rds_len = skb->len;

	spin_lock_irqsave(&fmdev->rds_buff_lock, flags);
	जबतक (rds_len > 0) अणु
		/*
		 * Fill RDS buffer as per V4L2 specअगरication.
		 * Store control byte
		 */
		type = (rds_data[2] & 0x07);
		blk_idx = (type <= FM_RDS_BLOCK_C ? type : (type - 1));
		पंचांगpbuf[2] = blk_idx;	/* Offset name */
		पंचांगpbuf[2] |= blk_idx << 3;	/* Received offset */

		/* Store data byte */
		पंचांगpbuf[0] = rds_data[0];
		पंचांगpbuf[1] = rds_data[1];

		स_नकल(&rds->buff[rds->wr_idx], &पंचांगpbuf, FM_RDS_BLK_SIZE);
		rds->wr_idx = (rds->wr_idx + FM_RDS_BLK_SIZE) % rds->buf_size;

		/* Check क्रम overflow & start over */
		अगर (rds->wr_idx == rds->rd_idx) अणु
			fmdbg("RDS buffer overflow\n");
			rds->wr_idx = 0;
			rds->rd_idx = 0;
			अवरोध;
		पूर्ण
		rds_len -= FM_RDS_BLK_SIZE;
		rds_data += FM_RDS_BLK_SIZE;
	पूर्ण
	spin_unlock_irqrestore(&fmdev->rds_buff_lock, flags);

	/* Wakeup पढ़ो queue */
	अगर (rds->wr_idx != rds->rd_idx)
		wake_up_पूर्णांकerruptible(&rds->पढ़ो_queue);

	fm_irq_call_stage(fmdev, FM_RDS_FINISH_IDX);
पूर्ण

अटल व्योम fm_irq_handle_rds_finish(काष्ठा fmdev *fmdev)
अणु
	fm_irq_call_stage(fmdev, FM_HW_TUNE_OP_ENDED_IDX);
पूर्ण

अटल व्योम fm_irq_handle_tune_op_ended(काष्ठा fmdev *fmdev)
अणु
	अगर (fmdev->irq_info.flag & (FM_FR_EVENT | FM_BL_EVENT) & fmdev->
	    irq_info.mask) अणु
		fmdbg("irq: tune ended/bandlimit reached\n");
		अगर (test_and_clear_bit(FM_AF_SWITCH_INPROGRESS, &fmdev->flag)) अणु
			fmdev->irq_info.stage = FM_AF_JUMP_RD_FREQ_IDX;
		पूर्ण अन्यथा अणु
			complete(&fmdev->मुख्यtask_comp);
			fmdev->irq_info.stage = FM_HW_POWER_ENB_IDX;
		पूर्ण
	पूर्ण अन्यथा
		fmdev->irq_info.stage = FM_HW_POWER_ENB_IDX;

	fm_irq_call(fmdev);
पूर्ण

अटल व्योम fm_irq_handle_घातer_enb(काष्ठा fmdev *fmdev)
अणु
	अगर (fmdev->irq_info.flag & FM_POW_ENB_EVENT) अणु
		fmdbg("irq: Power Enabled/Disabled\n");
		complete(&fmdev->मुख्यtask_comp);
	पूर्ण

	fm_irq_call_stage(fmdev, FM_LOW_RSSI_START_IDX);
पूर्ण

अटल व्योम fm_irq_handle_low_rssi_start(काष्ठा fmdev *fmdev)
अणु
	अगर ((fmdev->rx.af_mode == FM_RX_RDS_AF_SWITCH_MODE_ON) &&
	    (fmdev->irq_info.flag & FM_LEV_EVENT & fmdev->irq_info.mask) &&
	    (fmdev->rx.freq != FM_UNDEFINED_FREQ) &&
	    (fmdev->rx.stat_info.afcache_size != 0)) अणु
		fmdbg("irq: rssi level has fallen below threshold level\n");

		/* Disable further low RSSI पूर्णांकerrupts */
		fmdev->irq_info.mask &= ~FM_LEV_EVENT;

		fmdev->rx.afjump_idx = 0;
		fmdev->rx.freq_beक्रमe_jump = fmdev->rx.freq;
		fmdev->irq_info.stage = FM_AF_JUMP_SETPI_IDX;
	पूर्ण अन्यथा अणु
		/* Continue next function in पूर्णांकerrupt handler table */
		fmdev->irq_info.stage = FM_SEND_INTMSK_CMD_IDX;
	पूर्ण

	fm_irq_call(fmdev);
पूर्ण

अटल व्योम fm_irq_afjump_set_pi(काष्ठा fmdev *fmdev)
अणु
	u16 payload;

	/* Set PI code - must be updated अगर the AF list is not empty */
	payload = fmdev->rx.stat_info.picode;
	अगर (!fm_send_cmd(fmdev, RDS_PI_SET, REG_WR, &payload, माप(payload), शून्य))
		fm_irq_समयout_stage(fmdev, FM_AF_JUMP_HANDLE_SETPI_RESP_IDX);
पूर्ण

अटल व्योम fm_irq_handle_set_pi_resp(काष्ठा fmdev *fmdev)
अणु
	fm_irq_common_cmd_resp_helper(fmdev, FM_AF_JUMP_SETPI_MASK_IDX);
पूर्ण

/*
 * Set PI mask.
 * 0xFFFF = Enable PI code matching
 * 0x0000 = Disable PI code matching
 */
अटल व्योम fm_irq_afjump_set_pimask(काष्ठा fmdev *fmdev)
अणु
	u16 payload;

	payload = 0x0000;
	अगर (!fm_send_cmd(fmdev, RDS_PI_MASK_SET, REG_WR, &payload, माप(payload), शून्य))
		fm_irq_समयout_stage(fmdev, FM_AF_JUMP_HANDLE_SETPI_MASK_RESP_IDX);
पूर्ण

अटल व्योम fm_irq_handle_set_pimask_resp(काष्ठा fmdev *fmdev)
अणु
	fm_irq_common_cmd_resp_helper(fmdev, FM_AF_JUMP_SET_AF_FREQ_IDX);
पूर्ण

अटल व्योम fm_irq_afjump_setfreq(काष्ठा fmdev *fmdev)
अणु
	u16 frq_index;
	u16 payload;

	fmdbg("Switch to %d KHz\n", fmdev->rx.stat_info.af_cache[fmdev->rx.afjump_idx]);
	frq_index = (fmdev->rx.stat_info.af_cache[fmdev->rx.afjump_idx] -
	     fmdev->rx.region.bot_freq) / FM_FREQ_MUL;

	payload = frq_index;
	अगर (!fm_send_cmd(fmdev, AF_FREQ_SET, REG_WR, &payload, माप(payload), शून्य))
		fm_irq_समयout_stage(fmdev, FM_AF_JUMP_HANDLE_SET_AFFREQ_RESP_IDX);
पूर्ण

अटल व्योम fm_irq_handle_setfreq_resp(काष्ठा fmdev *fmdev)
अणु
	fm_irq_common_cmd_resp_helper(fmdev, FM_AF_JUMP_ENABLE_INT_IDX);
पूर्ण

अटल व्योम fm_irq_afjump_enableपूर्णांक(काष्ठा fmdev *fmdev)
अणु
	u16 payload;

	/* Enable FR (tuning operation ended) पूर्णांकerrupt */
	payload = FM_FR_EVENT;
	अगर (!fm_send_cmd(fmdev, INT_MASK_SET, REG_WR, &payload, माप(payload), शून्य))
		fm_irq_समयout_stage(fmdev, FM_AF_JUMP_ENABLE_INT_RESP_IDX);
पूर्ण

अटल व्योम fm_irq_afjump_enableपूर्णांक_resp(काष्ठा fmdev *fmdev)
अणु
	fm_irq_common_cmd_resp_helper(fmdev, FM_AF_JUMP_START_AFJUMP_IDX);
पूर्ण

अटल व्योम fm_irq_start_afjump(काष्ठा fmdev *fmdev)
अणु
	u16 payload;

	payload = FM_TUNER_AF_JUMP_MODE;
	अगर (!fm_send_cmd(fmdev, TUNER_MODE_SET, REG_WR, &payload,
			माप(payload), शून्य))
		fm_irq_समयout_stage(fmdev, FM_AF_JUMP_HANDLE_START_AFJUMP_RESP_IDX);
पूर्ण

अटल व्योम fm_irq_handle_start_afjump_resp(काष्ठा fmdev *fmdev)
अणु
	काष्ठा sk_buff *skb;

	अगर (check_cmdresp_status(fmdev, &skb))
		वापस;

	fmdev->irq_info.stage = FM_SEND_FLAG_GETCMD_IDX;
	set_bit(FM_AF_SWITCH_INPROGRESS, &fmdev->flag);
	clear_bit(FM_INTTASK_RUNNING, &fmdev->flag);
पूर्ण

अटल व्योम fm_irq_afjump_rd_freq(काष्ठा fmdev *fmdev)
अणु
	u16 payload;

	अगर (!fm_send_cmd(fmdev, FREQ_SET, REG_RD, शून्य, माप(payload), शून्य))
		fm_irq_समयout_stage(fmdev, FM_AF_JUMP_RD_FREQ_RESP_IDX);
पूर्ण

अटल व्योम fm_irq_afjump_rd_freq_resp(काष्ठा fmdev *fmdev)
अणु
	काष्ठा sk_buff *skb;
	u16 पढ़ो_freq;
	u32 curr_freq, jumped_freq;

	अगर (check_cmdresp_status(fmdev, &skb))
		वापस;

	/* Skip header info and copy only response data */
	skb_pull(skb, माप(काष्ठा fm_event_msg_hdr));
	स_नकल(&पढ़ो_freq, skb->data, माप(पढ़ो_freq));
	पढ़ो_freq = be16_to_cpu((__क्रमce __be16)पढ़ो_freq);
	curr_freq = fmdev->rx.region.bot_freq + ((u32)पढ़ो_freq * FM_FREQ_MUL);

	jumped_freq = fmdev->rx.stat_info.af_cache[fmdev->rx.afjump_idx];

	/* If the frequency was changed the jump succeeded */
	अगर ((curr_freq != fmdev->rx.freq_beक्रमe_jump) && (curr_freq == jumped_freq)) अणु
		fmdbg("Successfully switched to alternate freq %d\n", curr_freq);
		fmdev->rx.freq = curr_freq;
		fm_rx_reset_rds_cache(fmdev);

		/* AF feature is on, enable low level RSSI पूर्णांकerrupt */
		अगर (fmdev->rx.af_mode == FM_RX_RDS_AF_SWITCH_MODE_ON)
			fmdev->irq_info.mask |= FM_LEV_EVENT;

		fmdev->irq_info.stage = FM_LOW_RSSI_FINISH_IDX;
	पूर्ण अन्यथा अणु		/* jump to the next freq in the AF list */
		fmdev->rx.afjump_idx++;

		/* If we reached the end of the list - stop searching */
		अगर (fmdev->rx.afjump_idx >= fmdev->rx.stat_info.afcache_size) अणु
			fmdbg("AF switch processing failed\n");
			fmdev->irq_info.stage = FM_LOW_RSSI_FINISH_IDX;
		पूर्ण अन्यथा अणु	/* AF List is not over - try next one */

			fmdbg("Trying next freq in AF cache\n");
			fmdev->irq_info.stage = FM_AF_JUMP_SETPI_IDX;
		पूर्ण
	पूर्ण
	fm_irq_call(fmdev);
पूर्ण

अटल व्योम fm_irq_handle_low_rssi_finish(काष्ठा fmdev *fmdev)
अणु
	fm_irq_call_stage(fmdev, FM_SEND_INTMSK_CMD_IDX);
पूर्ण

अटल व्योम fm_irq_send_पूर्णांकmsk_cmd(काष्ठा fmdev *fmdev)
अणु
	u16 payload;

	/* Re-enable FM पूर्णांकerrupts */
	payload = fmdev->irq_info.mask;

	अगर (!fm_send_cmd(fmdev, INT_MASK_SET, REG_WR, &payload,
			माप(payload), शून्य))
		fm_irq_समयout_stage(fmdev, FM_HANDLE_INTMSK_CMD_RESP_IDX);
पूर्ण

अटल व्योम fm_irq_handle_पूर्णांकmsk_cmd_resp(काष्ठा fmdev *fmdev)
अणु
	काष्ठा sk_buff *skb;

	अगर (check_cmdresp_status(fmdev, &skb))
		वापस;
	/*
	 * This is last function in पूर्णांकerrupt table to be executed.
	 * So, reset stage index to 0.
	 */
	fmdev->irq_info.stage = FM_SEND_FLAG_GETCMD_IDX;

	/* Start processing any pending पूर्णांकerrupt */
	अगर (test_and_clear_bit(FM_INTTASK_SCHEDULE_PENDING, &fmdev->flag))
		fmdev->irq_info.handlers[fmdev->irq_info.stage](fmdev);
	अन्यथा
		clear_bit(FM_INTTASK_RUNNING, &fmdev->flag);
पूर्ण

/* Returns availability of RDS data in पूर्णांकernal buffer */
पूर्णांक fmc_is_rds_data_available(काष्ठा fmdev *fmdev, काष्ठा file *file,
				काष्ठा poll_table_काष्ठा *pts)
अणु
	poll_रुको(file, &fmdev->rx.rds.पढ़ो_queue, pts);
	अगर (fmdev->rx.rds.rd_idx != fmdev->rx.rds.wr_idx)
		वापस 0;

	वापस -EAGAIN;
पूर्ण

/* Copies RDS data from पूर्णांकernal buffer to user buffer */
पूर्णांक fmc_transfer_rds_from_पूर्णांकernal_buff(काष्ठा fmdev *fmdev, काष्ठा file *file,
		u8 __user *buf, माप_प्रकार count)
अणु
	u32 block_count;
	u8 पंचांगpbuf[FM_RDS_BLK_SIZE];
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (fmdev->rx.rds.wr_idx == fmdev->rx.rds.rd_idx) अणु
		अगर (file->f_flags & O_NONBLOCK)
			वापस -EWOULDBLOCK;

		ret = रुको_event_पूर्णांकerruptible(fmdev->rx.rds.पढ़ो_queue,
				(fmdev->rx.rds.wr_idx != fmdev->rx.rds.rd_idx));
		अगर (ret)
			वापस -EINTR;
	पूर्ण

	/* Calculate block count from byte count */
	count /= FM_RDS_BLK_SIZE;
	block_count = 0;
	ret = 0;

	जबतक (block_count < count) अणु
		spin_lock_irqsave(&fmdev->rds_buff_lock, flags);

		अगर (fmdev->rx.rds.wr_idx == fmdev->rx.rds.rd_idx) अणु
			spin_unlock_irqrestore(&fmdev->rds_buff_lock, flags);
			अवरोध;
		पूर्ण
		स_नकल(पंचांगpbuf, &fmdev->rx.rds.buff[fmdev->rx.rds.rd_idx],
					FM_RDS_BLK_SIZE);
		fmdev->rx.rds.rd_idx += FM_RDS_BLK_SIZE;
		अगर (fmdev->rx.rds.rd_idx >= fmdev->rx.rds.buf_size)
			fmdev->rx.rds.rd_idx = 0;

		spin_unlock_irqrestore(&fmdev->rds_buff_lock, flags);

		अगर (copy_to_user(buf, पंचांगpbuf, FM_RDS_BLK_SIZE))
			अवरोध;

		block_count++;
		buf += FM_RDS_BLK_SIZE;
		ret += FM_RDS_BLK_SIZE;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक fmc_set_freq(काष्ठा fmdev *fmdev, u32 freq_to_set)
अणु
	चयन (fmdev->curr_fmmode) अणु
	हाल FM_MODE_RX:
		वापस fm_rx_set_freq(fmdev, freq_to_set);

	हाल FM_MODE_TX:
		वापस fm_tx_set_freq(fmdev, freq_to_set);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक fmc_get_freq(काष्ठा fmdev *fmdev, u32 *cur_tuned_frq)
अणु
	अगर (fmdev->rx.freq == FM_UNDEFINED_FREQ) अणु
		fmerr("RX frequency is not set\n");
		वापस -EPERM;
	पूर्ण
	अगर (cur_tuned_frq == शून्य) अणु
		fmerr("Invalid memory\n");
		वापस -ENOMEM;
	पूर्ण

	चयन (fmdev->curr_fmmode) अणु
	हाल FM_MODE_RX:
		*cur_tuned_frq = fmdev->rx.freq;
		वापस 0;

	हाल FM_MODE_TX:
		*cur_tuned_frq = 0;	/* TODO : Change this later */
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण

पूर्ण

पूर्णांक fmc_set_region(काष्ठा fmdev *fmdev, u8 region_to_set)
अणु
	चयन (fmdev->curr_fmmode) अणु
	हाल FM_MODE_RX:
		वापस fm_rx_set_region(fmdev, region_to_set);

	हाल FM_MODE_TX:
		वापस fm_tx_set_region(fmdev, region_to_set);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक fmc_set_mute_mode(काष्ठा fmdev *fmdev, u8 mute_mode_toset)
अणु
	चयन (fmdev->curr_fmmode) अणु
	हाल FM_MODE_RX:
		वापस fm_rx_set_mute_mode(fmdev, mute_mode_toset);

	हाल FM_MODE_TX:
		वापस fm_tx_set_mute_mode(fmdev, mute_mode_toset);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक fmc_set_stereo_mono(काष्ठा fmdev *fmdev, u16 mode)
अणु
	चयन (fmdev->curr_fmmode) अणु
	हाल FM_MODE_RX:
		वापस fm_rx_set_stereo_mono(fmdev, mode);

	हाल FM_MODE_TX:
		वापस fm_tx_set_stereo_mono(fmdev, mode);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक fmc_set_rds_mode(काष्ठा fmdev *fmdev, u8 rds_en_dis)
अणु
	चयन (fmdev->curr_fmmode) अणु
	हाल FM_MODE_RX:
		वापस fm_rx_set_rds_mode(fmdev, rds_en_dis);

	हाल FM_MODE_TX:
		वापस fm_tx_set_rds_mode(fmdev, rds_en_dis);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* Sends घातer off command to the chip */
अटल पूर्णांक fm_घातer_करोwn(काष्ठा fmdev *fmdev)
अणु
	u16 payload;
	पूर्णांक ret;

	अगर (!test_bit(FM_CORE_READY, &fmdev->flag)) अणु
		fmerr("FM core is not ready\n");
		वापस -EPERM;
	पूर्ण
	अगर (fmdev->curr_fmmode == FM_MODE_OFF) अणु
		fmdbg("FM chip is already in OFF state\n");
		वापस 0;
	पूर्ण

	payload = 0x0;
	ret = fmc_send_cmd(fmdev, FM_POWER_MODE, REG_WR, &payload,
		माप(payload), शून्य, शून्य);
	अगर (ret < 0)
		वापस ret;

	वापस fmc_release(fmdev);
पूर्ण

/* Reads init command from FM firmware file and loads to the chip */
अटल पूर्णांक fm_करोwnload_firmware(काष्ठा fmdev *fmdev, स्थिर u8 *fw_name)
अणु
	स्थिर काष्ठा firmware *fw_entry;
	काष्ठा bts_header *fw_header;
	काष्ठा bts_action *action;
	काष्ठा bts_action_delay *delay;
	u8 *fw_data;
	पूर्णांक ret, fw_len, cmd_cnt;

	cmd_cnt = 0;
	set_bit(FM_FW_DW_INPROGRESS, &fmdev->flag);

	ret = request_firmware(&fw_entry, fw_name,
				&fmdev->radio_dev->dev);
	अगर (ret < 0) अणु
		fmerr("Unable to read firmware(%s) content\n", fw_name);
		वापस ret;
	पूर्ण
	fmdbg("Firmware(%s) length : %zu bytes\n", fw_name, fw_entry->size);

	fw_data = (व्योम *)fw_entry->data;
	fw_len = fw_entry->size;

	fw_header = (काष्ठा bts_header *)fw_data;
	अगर (fw_header->magic != FM_FW_खाता_HEADER_MAGIC) अणु
		fmerr("%s not a legal TI firmware file\n", fw_name);
		ret = -EINVAL;
		जाओ rel_fw;
	पूर्ण
	fmdbg("FW(%s) magic number : 0x%x\n", fw_name, fw_header->magic);

	/* Skip file header info , we alपढ़ोy verअगरied it */
	fw_data += माप(काष्ठा bts_header);
	fw_len -= माप(काष्ठा bts_header);

	जबतक (fw_data && fw_len > 0) अणु
		action = (काष्ठा bts_action *)fw_data;

		चयन (action->type) अणु
		हाल ACTION_SEND_COMMAND:	/* Send */
			ret = fmc_send_cmd(fmdev, 0, 0, action->data,
					   action->size, शून्य, शून्य);
			अगर (ret)
				जाओ rel_fw;

			cmd_cnt++;
			अवरोध;

		हाल ACTION_DELAY:	/* Delay */
			delay = (काष्ठा bts_action_delay *)action->data;
			mdelay(delay->msec);
			अवरोध;
		पूर्ण

		fw_data += (माप(काष्ठा bts_action) + (action->size));
		fw_len -= (माप(काष्ठा bts_action) + (action->size));
	पूर्ण
	fmdbg("Firmware commands(%d) loaded to chip\n", cmd_cnt);
rel_fw:
	release_firmware(fw_entry);
	clear_bit(FM_FW_DW_INPROGRESS, &fmdev->flag);

	वापस ret;
पूर्ण

/* Loads शेष RX configuration to the chip */
अटल पूर्णांक load_शेष_rx_configuration(काष्ठा fmdev *fmdev)
अणु
	पूर्णांक ret;

	ret = fm_rx_set_volume(fmdev, FM_DEFAULT_RX_VOLUME);
	अगर (ret < 0)
		वापस ret;

	वापस fm_rx_set_rssi_threshold(fmdev, FM_DEFAULT_RSSI_THRESHOLD);
पूर्ण

/* Does FM घातer on sequence */
अटल पूर्णांक fm_घातer_up(काष्ठा fmdev *fmdev, u8 mode)
अणु
	u16 payload;
	__be16 asic_id = 0, asic_ver = 0;
	पूर्णांक resp_len, ret;
	u8 fw_name[50];

	अगर (mode >= FM_MODE_ENTRY_MAX) अणु
		fmerr("Invalid firmware download option\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Initialize FM common module. FM GPIO toggling is
	 * taken care in Shared Transport driver.
	 */
	ret = fmc_prepare(fmdev);
	अगर (ret < 0) अणु
		fmerr("Unable to prepare FM Common\n");
		वापस ret;
	पूर्ण

	payload = FM_ENABLE;
	अगर (fmc_send_cmd(fmdev, FM_POWER_MODE, REG_WR, &payload,
			माप(payload), शून्य, शून्य))
		जाओ rel;

	/* Allow the chip to settle करोwn in Channel-8 mode */
	msleep(20);

	अगर (fmc_send_cmd(fmdev, ASIC_ID_GET, REG_RD, शून्य,
			माप(asic_id), &asic_id, &resp_len))
		जाओ rel;

	अगर (fmc_send_cmd(fmdev, ASIC_VER_GET, REG_RD, शून्य,
			माप(asic_ver), &asic_ver, &resp_len))
		जाओ rel;

	fmdbg("ASIC ID: 0x%x , ASIC Version: %d\n",
		be16_to_cpu(asic_id), be16_to_cpu(asic_ver));

	प्र_लिखो(fw_name, "%s_%x.%d.bts", FM_FMC_FW_खाता_START,
		be16_to_cpu(asic_id), be16_to_cpu(asic_ver));

	ret = fm_करोwnload_firmware(fmdev, fw_name);
	अगर (ret < 0) अणु
		fmdbg("Failed to download firmware file %s\n", fw_name);
		जाओ rel;
	पूर्ण
	प्र_लिखो(fw_name, "%s_%x.%d.bts", (mode == FM_MODE_RX) ?
			FM_RX_FW_खाता_START : FM_TX_FW_खाता_START,
			be16_to_cpu(asic_id), be16_to_cpu(asic_ver));

	ret = fm_करोwnload_firmware(fmdev, fw_name);
	अगर (ret < 0) अणु
		fmdbg("Failed to download firmware file %s\n", fw_name);
		जाओ rel;
	पूर्ण अन्यथा
		वापस ret;
rel:
	वापस fmc_release(fmdev);
पूर्ण

/* Set FM Modes(TX, RX, OFF) */
पूर्णांक fmc_set_mode(काष्ठा fmdev *fmdev, u8 fm_mode)
अणु
	पूर्णांक ret = 0;

	अगर (fm_mode >= FM_MODE_ENTRY_MAX) अणु
		fmerr("Invalid FM mode\n");
		वापस -EINVAL;
	पूर्ण
	अगर (fmdev->curr_fmmode == fm_mode) अणु
		fmdbg("Already fm is in mode(%d)\n", fm_mode);
		वापस ret;
	पूर्ण

	चयन (fm_mode) अणु
	हाल FM_MODE_OFF:	/* OFF Mode */
		ret = fm_घातer_करोwn(fmdev);
		अगर (ret < 0) अणु
			fmerr("Failed to set OFF mode\n");
			वापस ret;
		पूर्ण
		अवरोध;

	हाल FM_MODE_TX:	/* TX Mode */
	हाल FM_MODE_RX:	/* RX Mode */
		/* Power करोwn beक्रमe चयनing to TX or RX mode */
		अगर (fmdev->curr_fmmode != FM_MODE_OFF) अणु
			ret = fm_घातer_करोwn(fmdev);
			अगर (ret < 0) अणु
				fmerr("Failed to set OFF mode\n");
				वापस ret;
			पूर्ण
			msleep(30);
		पूर्ण
		ret = fm_घातer_up(fmdev, fm_mode);
		अगर (ret < 0) अणु
			fmerr("Failed to load firmware\n");
			वापस ret;
		पूर्ण
	पूर्ण
	fmdev->curr_fmmode = fm_mode;

	/* Set शेष configuration */
	अगर (fmdev->curr_fmmode == FM_MODE_RX) अणु
		fmdbg("Loading default rx configuration..\n");
		ret = load_शेष_rx_configuration(fmdev);
		अगर (ret < 0)
			fmerr("Failed to load default values\n");
	पूर्ण

	वापस ret;
पूर्ण

/* Returns current FM mode (TX, RX, OFF) */
पूर्णांक fmc_get_mode(काष्ठा fmdev *fmdev, u8 *fmmode)
अणु
	अगर (!test_bit(FM_CORE_READY, &fmdev->flag)) अणु
		fmerr("FM core is not ready\n");
		वापस -EPERM;
	पूर्ण
	अगर (fmmode == शून्य) अणु
		fmerr("Invalid memory\n");
		वापस -ENOMEM;
	पूर्ण

	*fmmode = fmdev->curr_fmmode;
	वापस 0;
पूर्ण

/* Called by ST layer when FM packet is available */
अटल दीर्घ fm_st_receive(व्योम *arg, काष्ठा sk_buff *skb)
अणु
	काष्ठा fmdev *fmdev;

	fmdev = (काष्ठा fmdev *)arg;

	अगर (skb == शून्य) अणु
		fmerr("Invalid SKB received from ST\n");
		वापस -EFAULT;
	पूर्ण

	अगर (skb->cb[0] != FM_PKT_LOGICAL_CHAN_NUMBER) अणु
		fmerr("Received SKB (%p) is not FM Channel 8 pkt\n", skb);
		वापस -EINVAL;
	पूर्ण

	स_नकल(skb_push(skb, 1), &skb->cb[0], 1);
	skb_queue_tail(&fmdev->rx_q, skb);
	tasklet_schedule(&fmdev->rx_task);

	वापस 0;
पूर्ण

/*
 * Called by ST layer to indicate protocol registration completion
 * status.
 */
अटल व्योम fm_st_reg_comp_cb(व्योम *arg, पूर्णांक data)
अणु
	काष्ठा fmdev *fmdev;

	fmdev = (काष्ठा fmdev *)arg;
	fmdev->streg_cbdata = data;
	complete(&रुको_क्रम_fmdrv_reg_comp);
पूर्ण

/*
 * This function will be called from FM V4L2 खोलो function.
 * Register with ST driver and initialize driver data.
 */
पूर्णांक fmc_prepare(काष्ठा fmdev *fmdev)
अणु
	अटल काष्ठा st_proto_s fm_st_proto;
	पूर्णांक ret;

	अगर (test_bit(FM_CORE_READY, &fmdev->flag)) अणु
		fmdbg("FM Core is already up\n");
		वापस 0;
	पूर्ण

	स_रखो(&fm_st_proto, 0, माप(fm_st_proto));
	fm_st_proto.recv = fm_st_receive;
	fm_st_proto.match_packet = शून्य;
	fm_st_proto.reg_complete_cb = fm_st_reg_comp_cb;
	fm_st_proto.ग_लिखो = शून्य; /* TI ST driver will fill ग_लिखो poपूर्णांकer */
	fm_st_proto.priv_data = fmdev;
	fm_st_proto.chnl_id = 0x08;
	fm_st_proto.max_frame_size = 0xff;
	fm_st_proto.hdr_len = 1;
	fm_st_proto.offset_len_in_hdr = 0;
	fm_st_proto.len_size = 1;
	fm_st_proto.reserve = 1;

	ret = st_रेजिस्टर(&fm_st_proto);
	अगर (ret == -EINPROGRESS) अणु
		init_completion(&रुको_क्रम_fmdrv_reg_comp);
		fmdev->streg_cbdata = -EINPROGRESS;
		fmdbg("%s waiting for ST reg completion signal\n", __func__);

		अगर (!रुको_क्रम_completion_समयout(&रुको_क्रम_fmdrv_reg_comp,
						 FM_ST_REG_TIMEOUT)) अणु
			fmerr("Timeout(%d sec), didn't get reg completion signal from ST\n",
					jअगरfies_to_msecs(FM_ST_REG_TIMEOUT) / 1000);
			वापस -ETIMEDOUT;
		पूर्ण
		अगर (fmdev->streg_cbdata != 0) अणु
			fmerr("ST reg comp CB called with error status %d\n",
			      fmdev->streg_cbdata);
			वापस -EAGAIN;
		पूर्ण

		ret = 0;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		fmerr("st_register failed %d\n", ret);
		वापस -EAGAIN;
	पूर्ण

	अगर (fm_st_proto.ग_लिखो != शून्य) अणु
		g_st_ग_लिखो = fm_st_proto.ग_लिखो;
	पूर्ण अन्यथा अणु
		fmerr("Failed to get ST write func pointer\n");
		ret = st_unरेजिस्टर(&fm_st_proto);
		अगर (ret < 0)
			fmerr("st_unregister failed %d\n", ret);
		वापस -EAGAIN;
	पूर्ण

	spin_lock_init(&fmdev->rds_buff_lock);
	spin_lock_init(&fmdev->resp_skb_lock);

	/* Initialize TX queue and TX tasklet */
	skb_queue_head_init(&fmdev->tx_q);
	tasklet_setup(&fmdev->tx_task, send_tasklet);

	/* Initialize RX Queue and RX tasklet */
	skb_queue_head_init(&fmdev->rx_q);
	tasklet_setup(&fmdev->rx_task, recv_tasklet);

	fmdev->irq_info.stage = 0;
	atomic_set(&fmdev->tx_cnt, 1);
	fmdev->resp_comp = शून्य;

	समयr_setup(&fmdev->irq_info.समयr, पूर्णांक_समयout_handler, 0);
	/*TODO: add FM_STIC_EVENT later */
	fmdev->irq_info.mask = FM_MAL_EVENT;

	/* Region info */
	fmdev->rx.region = region_configs[शेष_radio_region];

	fmdev->rx.mute_mode = FM_MUTE_OFF;
	fmdev->rx.rf_depend_mute = FM_RX_RF_DEPENDENT_MUTE_OFF;
	fmdev->rx.rds.flag = FM_RDS_DISABLE;
	fmdev->rx.freq = FM_UNDEFINED_FREQ;
	fmdev->rx.rds_mode = FM_RDS_SYSTEM_RDS;
	fmdev->rx.af_mode = FM_RX_RDS_AF_SWITCH_MODE_OFF;
	fmdev->irq_info.retry = 0;

	fm_rx_reset_rds_cache(fmdev);
	init_रुकोqueue_head(&fmdev->rx.rds.पढ़ो_queue);

	fm_rx_reset_station_info(fmdev);
	set_bit(FM_CORE_READY, &fmdev->flag);

	वापस ret;
पूर्ण

/*
 * This function will be called from FM V4L2 release function.
 * Unरेजिस्टर from ST driver.
 */
पूर्णांक fmc_release(काष्ठा fmdev *fmdev)
अणु
	अटल काष्ठा st_proto_s fm_st_proto;
	पूर्णांक ret;

	अगर (!test_bit(FM_CORE_READY, &fmdev->flag)) अणु
		fmdbg("FM Core is already down\n");
		वापस 0;
	पूर्ण
	/* Service pending पढ़ो */
	wake_up_पूर्णांकerruptible(&fmdev->rx.rds.पढ़ो_queue);

	tasklet_समाप्त(&fmdev->tx_task);
	tasklet_समाप्त(&fmdev->rx_task);

	skb_queue_purge(&fmdev->tx_q);
	skb_queue_purge(&fmdev->rx_q);

	fmdev->resp_comp = शून्य;
	fmdev->rx.freq = 0;

	स_रखो(&fm_st_proto, 0, माप(fm_st_proto));
	fm_st_proto.chnl_id = 0x08;

	ret = st_unरेजिस्टर(&fm_st_proto);

	अगर (ret < 0)
		fmerr("Failed to de-register FM from ST %d\n", ret);
	अन्यथा
		fmdbg("Successfully unregistered from ST\n");

	clear_bit(FM_CORE_READY, &fmdev->flag);
	वापस ret;
पूर्ण

/*
 * Module init function. Ask FM V4L module to रेजिस्टर video device.
 * Allocate memory क्रम FM driver context and RX RDS buffer.
 */
अटल पूर्णांक __init fm_drv_init(व्योम)
अणु
	काष्ठा fmdev *fmdev = शून्य;
	पूर्णांक ret = -ENOMEM;

	fmdbg("FM driver version %s\n", FM_DRV_VERSION);

	fmdev = kzalloc(माप(काष्ठा fmdev), GFP_KERNEL);
	अगर (शून्य == fmdev) अणु
		fmerr("Can't allocate operation structure memory\n");
		वापस ret;
	पूर्ण
	fmdev->rx.rds.buf_size = शेष_rds_buf * FM_RDS_BLK_SIZE;
	fmdev->rx.rds.buff = kzalloc(fmdev->rx.rds.buf_size, GFP_KERNEL);
	अगर (शून्य == fmdev->rx.rds.buff) अणु
		fmerr("Can't allocate rds ring buffer\n");
		जाओ rel_dev;
	पूर्ण

	ret = fm_v4l2_init_video_device(fmdev, radio_nr);
	अगर (ret < 0)
		जाओ rel_rdsbuf;

	fmdev->irq_info.handlers = पूर्णांक_handler_table;
	fmdev->curr_fmmode = FM_MODE_OFF;
	fmdev->tx_data.pwr_lvl = FM_PWR_LVL_DEF;
	fmdev->tx_data.preemph = FM_TX_PREEMPH_50US;
	वापस ret;

rel_rdsbuf:
	kमुक्त(fmdev->rx.rds.buff);
rel_dev:
	kमुक्त(fmdev);

	वापस ret;
पूर्ण

/* Module निकास function. Ask FM V4L module to unरेजिस्टर video device */
अटल व्योम __निकास fm_drv_निकास(व्योम)
अणु
	काष्ठा fmdev *fmdev = शून्य;

	fmdev = fm_v4l2_deinit_video_device();
	अगर (fmdev != शून्य) अणु
		kमुक्त(fmdev->rx.rds.buff);
		kमुक्त(fmdev);
	पूर्ण
पूर्ण

module_init(fm_drv_init);
module_निकास(fm_drv_निकास);

/* ------------- Module Info ------------- */
MODULE_AUTHOR("Manjunatha Halli <manjunatha_halli@ti.com>");
MODULE_DESCRIPTION("FM Driver for TI's Connectivity chip. " FM_DRV_VERSION);
MODULE_VERSION(FM_DRV_VERSION);
MODULE_LICENSE("GPL");
