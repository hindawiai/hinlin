<शैली गुरु>
/*
 * Copyright (c) 2014 Redpine Signals Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#समावेश <linux/firmware.h>
#समावेश <net/rsi_91x.h>
#समावेश "rsi_sdio.h"
#समावेश "rsi_common.h"

/**
 * rsi_sdio_master_access_msword() - This function sets the AHB master access
 *				     MS word in the SDIO slave रेजिस्टरs.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 * @ms_word: ms word need to be initialized.
 *
 * Return: status: 0 on success, -1 on failure.
 */
पूर्णांक rsi_sdio_master_access_msword(काष्ठा rsi_hw *adapter, u16 ms_word)
अणु
	u8 byte;
	u8 function = 0;
	पूर्णांक status = 0;

	byte = (u8)(ms_word & 0x00FF);

	rsi_dbg(INIT_ZONE,
		"%s: MASTER_ACCESS_MSBYTE:0x%x\n", __func__, byte);

	status = rsi_sdio_ग_लिखो_रेजिस्टर(adapter,
					 function,
					 SDIO_MASTER_ACCESS_MSBYTE,
					 &byte);
	अगर (status) अणु
		rsi_dbg(ERR_ZONE,
			"%s: fail to access MASTER_ACCESS_MSBYTE\n",
			__func__);
		वापस -1;
	पूर्ण

	byte = (u8)(ms_word >> 8);

	rsi_dbg(INIT_ZONE, "%s:MASTER_ACCESS_LSBYTE:0x%x\n", __func__, byte);
	status = rsi_sdio_ग_लिखो_रेजिस्टर(adapter,
					 function,
					 SDIO_MASTER_ACCESS_LSBYTE,
					 &byte);
	वापस status;
पूर्ण

अटल व्योम rsi_rx_handler(काष्ठा rsi_hw *adapter);

व्योम rsi_sdio_rx_thपढ़ो(काष्ठा rsi_common *common)
अणु
	काष्ठा rsi_hw *adapter = common->priv;
	काष्ठा rsi_91x_sdiodev *sdev = adapter->rsi_dev;

	करो अणु
		rsi_रुको_event(&sdev->rx_thपढ़ो.event, EVENT_WAIT_FOREVER);
		rsi_reset_event(&sdev->rx_thपढ़ो.event);
		rsi_rx_handler(adapter);
	पूर्ण जबतक (!atomic_पढ़ो(&sdev->rx_thपढ़ो.thपढ़ो_करोne));

	rsi_dbg(INFO_ZONE, "%s: Terminated SDIO RX thread\n", __func__);
	atomic_inc(&sdev->rx_thपढ़ो.thपढ़ो_करोne);
	complete_and_निकास(&sdev->rx_thपढ़ो.completion, 0);
पूर्ण

/**
 * rsi_process_pkt() - This Function पढ़ोs rx_blocks रेजिस्टर and figures out
 *		       the size of the rx pkt.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 *
 * Return: 0 on success, -1 on failure.
 */
अटल पूर्णांक rsi_process_pkt(काष्ठा rsi_common *common)
अणु
	काष्ठा rsi_hw *adapter = common->priv;
	काष्ठा rsi_91x_sdiodev *dev =
		(काष्ठा rsi_91x_sdiodev *)adapter->rsi_dev;
	u8 num_blks = 0;
	u32 rcv_pkt_len = 0;
	पूर्णांक status = 0;
	u8 value = 0;

	num_blks = ((adapter->पूर्णांकerrupt_status & 1) |
			((adapter->पूर्णांकerrupt_status >> RECV_NUM_BLOCKS) << 1));

	अगर (!num_blks) अणु
		status = rsi_sdio_पढ़ो_रेजिस्टर(adapter,
						SDIO_RX_NUM_BLOCKS_REG,
						&value);
		अगर (status) अणु
			rsi_dbg(ERR_ZONE,
				"%s: Failed to read pkt length from the card:\n",
				__func__);
			वापस status;
		पूर्ण
		num_blks = value & 0x1f;
	पूर्ण

	अगर (dev->ग_लिखो_fail == 2)
		rsi_sdio_ack_पूर्णांकr(common->priv, (1 << MSDU_PKT_PENDING));

	अगर (unlikely(!num_blks)) अणु
		dev->ग_लिखो_fail = 2;
		वापस -1;
	पूर्ण

	rcv_pkt_len = (num_blks * 256);

	status = rsi_sdio_host_पूर्णांकf_पढ़ो_pkt(adapter, dev->pktbuffer,
					     rcv_pkt_len);
	अगर (status) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed to read packet from card\n",
			__func__);
		वापस status;
	पूर्ण

	status = rsi_पढ़ो_pkt(common, dev->pktbuffer, rcv_pkt_len);
	अगर (status) अणु
		rsi_dbg(ERR_ZONE, "Failed to read the packet\n");
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * rsi_init_sdio_slave_regs() - This function करोes the actual initialization
 *				of SDBUS slave रेजिस्टरs.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 *
 * Return: status: 0 on success, -1 on failure.
 */
पूर्णांक rsi_init_sdio_slave_regs(काष्ठा rsi_hw *adapter)
अणु
	काष्ठा rsi_91x_sdiodev *dev =
		(काष्ठा rsi_91x_sdiodev *)adapter->rsi_dev;
	u8 function = 0;
	u8 byte;
	पूर्णांक status = 0;

	अगर (dev->next_पढ़ो_delay) अणु
		byte = dev->next_पढ़ो_delay;
		status = rsi_sdio_ग_लिखो_रेजिस्टर(adapter,
						 function,
						 SDIO_NXT_RD_DELAY2,
						 &byte);
		अगर (status) अणु
			rsi_dbg(ERR_ZONE,
				"%s: Failed to write SDIO_NXT_RD_DELAY2\n",
				__func__);
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (dev->sdio_high_speed_enable) अणु
		rsi_dbg(INIT_ZONE, "%s: Enabling SDIO High speed\n", __func__);
		byte = 0x3;

		status = rsi_sdio_ग_लिखो_रेजिस्टर(adapter,
						 function,
						 SDIO_REG_HIGH_SPEED,
						 &byte);
		अगर (status) अणु
			rsi_dbg(ERR_ZONE,
				"%s: Failed to enable SDIO high speed\n",
				__func__);
			वापस -1;
		पूर्ण
	पूर्ण

	/* This tells SDIO FIFO when to start पढ़ो to host */
	rsi_dbg(INIT_ZONE, "%s: Initializing SDIO read start level\n", __func__);
	byte = 0x24;

	status = rsi_sdio_ग_लिखो_रेजिस्टर(adapter,
					 function,
					 SDIO_READ_START_LVL,
					 &byte);
	अगर (status) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Failed to write SDIO_READ_START_LVL\n", __func__);
		वापस -1;
	पूर्ण

	rsi_dbg(INIT_ZONE, "%s: Initializing FIFO ctrl registers\n", __func__);
	byte = (128 - 32);

	status = rsi_sdio_ग_लिखो_रेजिस्टर(adapter,
					 function,
					 SDIO_READ_FIFO_CTL,
					 &byte);
	अगर (status) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Failed to write SDIO_READ_FIFO_CTL\n", __func__);
		वापस -1;
	पूर्ण

	byte = 32;
	status = rsi_sdio_ग_लिखो_रेजिस्टर(adapter,
					 function,
					 SDIO_WRITE_FIFO_CTL,
					 &byte);
	अगर (status) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Failed to write SDIO_WRITE_FIFO_CTL\n", __func__);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * rsi_rx_handler() - Read and process SDIO पूर्णांकerrupts.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 *
 * Return: None.
 */
अटल व्योम rsi_rx_handler(काष्ठा rsi_hw *adapter)
अणु
	काष्ठा rsi_common *common = adapter->priv;
	काष्ठा rsi_91x_sdiodev *dev =
		(काष्ठा rsi_91x_sdiodev *)adapter->rsi_dev;
	पूर्णांक status;
	u8 isr_status = 0;
	u8 fw_status = 0;

	dev->rx_info.sdio_पूर्णांक_counter++;

	करो अणु
		mutex_lock(&common->rx_lock);
		status = rsi_sdio_पढ़ो_रेजिस्टर(common->priv,
						RSI_FN1_INT_REGISTER,
						&isr_status);
		अगर (status) अणु
			rsi_dbg(ERR_ZONE,
				"%s: Failed to Read Intr Status Register\n",
				__func__);
			mutex_unlock(&common->rx_lock);
			वापस;
		पूर्ण
		adapter->पूर्णांकerrupt_status = isr_status;

		अगर (isr_status == 0) अणु
			rsi_set_event(&common->tx_thपढ़ो.event);
			dev->rx_info.sdio_पूर्णांकr_status_zero++;
			mutex_unlock(&common->rx_lock);
			वापस;
		पूर्ण

		rsi_dbg(ISR_ZONE, "%s: Intr_status = %x %d %d\n",
			__func__, isr_status, (1 << MSDU_PKT_PENDING),
			(1 << FW_ASSERT_IND));

		अगर (isr_status & BIT(PKT_BUFF_AVAILABLE)) अणु
			status = rsi_sdio_check_buffer_status(adapter, 0);
			अगर (status < 0)
				rsi_dbg(ERR_ZONE,
					"%s: Failed to check buffer status\n",
					__func__);
			rsi_sdio_ack_पूर्णांकr(common->priv,
					  BIT(PKT_BUFF_AVAILABLE));
			rsi_set_event(&common->tx_thपढ़ो.event);

			rsi_dbg(ISR_ZONE, "%s: ==> BUFFER_AVAILABLE <==\n",
				__func__);
			dev->buff_status_updated = true;

			isr_status &= ~BIT(PKT_BUFF_AVAILABLE);
		पूर्ण

		अगर (isr_status & BIT(FW_ASSERT_IND)) अणु
			rsi_dbg(ERR_ZONE, "%s: ==> FIRMWARE Assert <==\n",
				__func__);
			status = rsi_sdio_पढ़ो_रेजिस्टर(common->priv,
							SDIO_FW_STATUS_REG,
							&fw_status);
			अगर (status) अणु
				rsi_dbg(ERR_ZONE,
					"%s: Failed to read f/w reg\n",
					__func__);
			पूर्ण अन्यथा अणु
				rsi_dbg(ERR_ZONE,
					"%s: Firmware Status is 0x%x\n",
					__func__, fw_status);
				rsi_sdio_ack_पूर्णांकr(common->priv,
						  BIT(FW_ASSERT_IND));
			पूर्ण

			common->fsm_state = FSM_CARD_NOT_READY;

			isr_status &= ~BIT(FW_ASSERT_IND);
		पूर्ण

		अगर (isr_status & BIT(MSDU_PKT_PENDING)) अणु
			rsi_dbg(ISR_ZONE, "Pkt pending interrupt\n");
			dev->rx_info.total_sdio_msdu_pending_पूर्णांकr++;

			status = rsi_process_pkt(common);
			अगर (status) अणु
				rsi_dbg(ERR_ZONE, "%s: Failed to read pkt\n",
					__func__);
				mutex_unlock(&common->rx_lock);
				वापस;
			पूर्ण

			isr_status &= ~BIT(MSDU_PKT_PENDING);
		पूर्ण

		अगर (isr_status) अणु
			rsi_sdio_ack_पूर्णांकr(common->priv, isr_status);
			dev->rx_info.total_sdio_unknown_पूर्णांकr++;
			isr_status = 0;
			rsi_dbg(ISR_ZONE, "Unknown Interrupt %x\n",
				isr_status);
		पूर्ण

		mutex_unlock(&common->rx_lock);
	पूर्ण जबतक (1);
पूर्ण

/* This function is used to पढ़ो buffer status रेजिस्टर and
 * set relevant fields in rsi_91x_sdiodev काष्ठा.
 */
पूर्णांक rsi_sdio_check_buffer_status(काष्ठा rsi_hw *adapter, u8 q_num)
अणु
	काष्ठा rsi_common *common = adapter->priv;
	काष्ठा rsi_91x_sdiodev *dev =
		(काष्ठा rsi_91x_sdiodev *)adapter->rsi_dev;
	u8 buf_status = 0;
	पूर्णांक status = 0;
	अटल पूर्णांक counter = 4;

	अगर (!dev->buff_status_updated && counter) अणु
		counter--;
		जाओ out;
	पूर्ण

	dev->buff_status_updated = false;
	status = rsi_sdio_पढ़ो_रेजिस्टर(common->priv,
					RSI_DEVICE_BUFFER_STATUS_REGISTER,
					&buf_status);

	अगर (status) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Failed to read status register\n", __func__);
		वापस -1;
	पूर्ण

	अगर (buf_status & (BIT(PKT_MGMT_BUFF_FULL))) अणु
		अगर (!dev->rx_info.mgmt_buffer_full)
			dev->rx_info.mgmt_buf_full_counter++;
		dev->rx_info.mgmt_buffer_full = true;
	पूर्ण अन्यथा अणु
		dev->rx_info.mgmt_buffer_full = false;
	पूर्ण

	अगर (buf_status & (BIT(PKT_BUFF_FULL))) अणु
		अगर (!dev->rx_info.buffer_full)
			dev->rx_info.buf_full_counter++;
		dev->rx_info.buffer_full = true;
	पूर्ण अन्यथा अणु
		dev->rx_info.buffer_full = false;
	पूर्ण

	अगर (buf_status & (BIT(PKT_BUFF_SEMI_FULL))) अणु
		अगर (!dev->rx_info.semi_buffer_full)
			dev->rx_info.buf_semi_full_counter++;
		dev->rx_info.semi_buffer_full = true;
	पूर्ण अन्यथा अणु
		dev->rx_info.semi_buffer_full = false;
	पूर्ण

	अगर (dev->rx_info.mgmt_buffer_full || dev->rx_info.buf_full_counter)
		counter = 1;
	अन्यथा
		counter = 4;

out:
	अगर ((q_num == MGMT_SOFT_Q) && (dev->rx_info.mgmt_buffer_full))
		वापस QUEUE_FULL;

	अगर ((q_num < MGMT_SOFT_Q) && (dev->rx_info.buffer_full))
		वापस QUEUE_FULL;

	वापस QUEUE_NOT_FULL;
पूर्ण

/**
 * rsi_sdio_determine_event_समयout() - This Function determines the event
 *					समयout duration.
 * @adapter: Poपूर्णांकer to the adapter काष्ठाure.
 *
 * Return: समयout duration is वापसed.
 */
पूर्णांक rsi_sdio_determine_event_समयout(काष्ठा rsi_hw *adapter)
अणु
	काष्ठा rsi_91x_sdiodev *dev =
		(काष्ठा rsi_91x_sdiodev *)adapter->rsi_dev;

	/* Once buffer full is seen, event समयout to occur every 2 msecs */
	अगर (dev->rx_info.buffer_full)
		वापस 2;

	वापस EVENT_WAIT_FOREVER;
पूर्ण
