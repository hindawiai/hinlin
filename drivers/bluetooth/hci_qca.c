<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Bluetooth Software UART Qualcomm protocol
 *
 *  HCI_IBS (HCI In-Band Sleep) is Qualcomm's घातer management
 *  protocol extension to H4.
 *
 *  Copyright (C) 2007 Texas Instruments, Inc.
 *  Copyright (c) 2010, 2012, 2018 The Linux Foundation. All rights reserved.
 *
 *  Acknowledgements:
 *  This file is based on hci_ll.c, which was...
 *  Written by Ohad Ben-Cohen <ohad@bencohen.org>
 *  which was in turn based on hci_h4.c, which was written
 *  by Maxim Krasnyansky and Marcel Holपंचांगann.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/devcoredump.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/acpi.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/serdev.h>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "hci_uart.h"
#समावेश "btqca.h"

/* HCI_IBS protocol messages */
#घोषणा HCI_IBS_SLEEP_IND	0xFE
#घोषणा HCI_IBS_WAKE_IND	0xFD
#घोषणा HCI_IBS_WAKE_ACK	0xFC
#घोषणा HCI_MAX_IBS_SIZE	10

#घोषणा IBS_WAKE_RETRANS_TIMEOUT_MS	100
#घोषणा IBS_BTSOC_TX_IDLE_TIMEOUT_MS	200
#घोषणा IBS_HOST_TX_IDLE_TIMEOUT_MS	2000
#घोषणा CMD_TRANS_TIMEOUT_MS		100
#घोषणा MEMDUMP_TIMEOUT_MS		8000
#घोषणा IBS_DISABLE_SSR_TIMEOUT_MS \
	(MEMDUMP_TIMEOUT_MS + FW_DOWNLOAD_TIMEOUT_MS)
#घोषणा FW_DOWNLOAD_TIMEOUT_MS		3000

/* susclk rate */
#घोषणा SUSCLK_RATE_32KHZ	32768

/* Controller debug log header */
#घोषणा QCA_DEBUG_HANDLE	0x2EDC

/* max retry count when init fails */
#घोषणा MAX_INIT_RETRIES 3

/* Controller dump header */
#घोषणा QCA_SSR_DUMP_HANDLE		0x0108
#घोषणा QCA_DUMP_PACKET_SIZE		255
#घोषणा QCA_LAST_SEQUENCE_NUM		0xFFFF
#घोषणा QCA_CRASHBYTE_PACKET_LEN	1096
#घोषणा QCA_MEMDUMP_BYTE		0xFB

क्रमागत qca_flags अणु
	QCA_IBS_DISABLED,
	QCA_DROP_VENDOR_EVENT,
	QCA_SUSPENDING,
	QCA_MEMDUMP_COLLECTION,
	QCA_HW_ERROR_EVENT,
	QCA_SSR_TRIGGERED,
	QCA_BT_OFF,
	QCA_ROM_FW
पूर्ण;

क्रमागत qca_capabilities अणु
	QCA_CAP_WIDEBAND_SPEECH = BIT(0),
	QCA_CAP_VALID_LE_STATES = BIT(1),
पूर्ण;

/* HCI_IBS transmit side sleep protocol states */
क्रमागत tx_ibs_states अणु
	HCI_IBS_TX_ASLEEP,
	HCI_IBS_TX_WAKING,
	HCI_IBS_TX_AWAKE,
पूर्ण;

/* HCI_IBS receive side sleep protocol states */
क्रमागत rx_states अणु
	HCI_IBS_RX_ASLEEP,
	HCI_IBS_RX_AWAKE,
पूर्ण;

/* HCI_IBS transmit and receive side घड़ी state vote */
क्रमागत hci_ibs_घड़ी_state_vote अणु
	HCI_IBS_VOTE_STATS_UPDATE,
	HCI_IBS_TX_VOTE_CLOCK_ON,
	HCI_IBS_TX_VOTE_CLOCK_OFF,
	HCI_IBS_RX_VOTE_CLOCK_ON,
	HCI_IBS_RX_VOTE_CLOCK_OFF,
पूर्ण;

/* Controller memory dump states */
क्रमागत qca_memdump_states अणु
	QCA_MEMDUMP_IDLE,
	QCA_MEMDUMP_COLLECTING,
	QCA_MEMDUMP_COLLECTED,
	QCA_MEMDUMP_TIMEOUT,
पूर्ण;

काष्ठा qca_memdump_data अणु
	अक्षर *memdump_buf_head;
	अक्षर *memdump_buf_tail;
	u32 current_seq_no;
	u32 received_dump;
	u32 ram_dump_size;
पूर्ण;

काष्ठा qca_memdump_event_hdr अणु
	__u8    evt;
	__u8    plen;
	__u16   opcode;
	__u16   seq_no;
	__u8    reserved;
पूर्ण __packed;


काष्ठा qca_dump_size अणु
	u32 dump_size;
पूर्ण __packed;

काष्ठा qca_data अणु
	काष्ठा hci_uart *hu;
	काष्ठा sk_buff *rx_skb;
	काष्ठा sk_buff_head txq;
	काष्ठा sk_buff_head tx_रुको_q;	/* HCI_IBS रुको queue	*/
	काष्ठा sk_buff_head rx_memdump_q;	/* Memdump रुको queue	*/
	spinlock_t hci_ibs_lock;	/* HCI_IBS state lock	*/
	u8 tx_ibs_state;	/* HCI_IBS transmit side घातer state*/
	u8 rx_ibs_state;	/* HCI_IBS receive side घातer state */
	bool tx_vote;		/* Clock must be on क्रम TX */
	bool rx_vote;		/* Clock must be on क्रम RX */
	काष्ठा समयr_list tx_idle_समयr;
	u32 tx_idle_delay;
	काष्ठा समयr_list wake_retrans_समयr;
	u32 wake_retrans;
	काष्ठा workqueue_काष्ठा *workqueue;
	काष्ठा work_काष्ठा ws_awake_rx;
	काष्ठा work_काष्ठा ws_awake_device;
	काष्ठा work_काष्ठा ws_rx_vote_off;
	काष्ठा work_काष्ठा ws_tx_vote_off;
	काष्ठा work_काष्ठा ctrl_memdump_evt;
	काष्ठा delayed_work ctrl_memdump_समयout;
	काष्ठा qca_memdump_data *qca_memdump;
	अचिन्हित दीर्घ flags;
	काष्ठा completion drop_ev_comp;
	रुको_queue_head_t suspend_रुको_q;
	क्रमागत qca_memdump_states memdump_state;
	काष्ठा mutex hci_memdump_lock;

	/* For debugging purpose */
	u64 ibs_sent_wacks;
	u64 ibs_sent_slps;
	u64 ibs_sent_wakes;
	u64 ibs_recv_wacks;
	u64 ibs_recv_slps;
	u64 ibs_recv_wakes;
	u64 vote_last_jअगर;
	u32 vote_on_ms;
	u32 vote_off_ms;
	u64 tx_votes_on;
	u64 rx_votes_on;
	u64 tx_votes_off;
	u64 rx_votes_off;
	u64 votes_on;
	u64 votes_off;
पूर्ण;

क्रमागत qca_speed_type अणु
	QCA_INIT_SPEED = 1,
	QCA_OPER_SPEED
पूर्ण;

/*
 * Voltage regulator inक्रमmation required क्रम configuring the
 * QCA Bluetooth chipset
 */
काष्ठा qca_vreg अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक load_uA;
पूर्ण;

काष्ठा qca_device_data अणु
	क्रमागत qca_btsoc_type soc_type;
	काष्ठा qca_vreg *vregs;
	माप_प्रकार num_vregs;
	uपूर्णांक32_t capabilities;
पूर्ण;

/*
 * Platक्रमm data क्रम the QCA Bluetooth घातer driver.
 */
काष्ठा qca_घातer अणु
	काष्ठा device *dev;
	काष्ठा regulator_bulk_data *vreg_bulk;
	पूर्णांक num_vregs;
	bool vregs_on;
पूर्ण;

काष्ठा qca_serdev अणु
	काष्ठा hci_uart	 serdev_hu;
	काष्ठा gpio_desc *bt_en;
	काष्ठा clk	 *susclk;
	क्रमागत qca_btsoc_type btsoc_type;
	काष्ठा qca_घातer *bt_घातer;
	u32 init_speed;
	u32 oper_speed;
	स्थिर अक्षर *firmware_name;
पूर्ण;

अटल पूर्णांक qca_regulator_enable(काष्ठा qca_serdev *qcadev);
अटल व्योम qca_regulator_disable(काष्ठा qca_serdev *qcadev);
अटल व्योम qca_घातer_shutकरोwn(काष्ठा hci_uart *hu);
अटल पूर्णांक qca_घातer_off(काष्ठा hci_dev *hdev);
अटल व्योम qca_controller_memdump(काष्ठा work_काष्ठा *work);

अटल क्रमागत qca_btsoc_type qca_soc_type(काष्ठा hci_uart *hu)
अणु
	क्रमागत qca_btsoc_type soc_type;

	अगर (hu->serdev) अणु
		काष्ठा qca_serdev *qsd = serdev_device_get_drvdata(hu->serdev);

		soc_type = qsd->btsoc_type;
	पूर्ण अन्यथा अणु
		soc_type = QCA_ROME;
	पूर्ण

	वापस soc_type;
पूर्ण

अटल स्थिर अक्षर *qca_get_firmware_name(काष्ठा hci_uart *hu)
अणु
	अगर (hu->serdev) अणु
		काष्ठा qca_serdev *qsd = serdev_device_get_drvdata(hu->serdev);

		वापस qsd->firmware_name;
	पूर्ण अन्यथा अणु
		वापस शून्य;
	पूर्ण
पूर्ण

अटल व्योम __serial_घड़ी_on(काष्ठा tty_काष्ठा *tty)
अणु
	/* TODO: Some chipset requires to enable UART घड़ी on client
	 * side to save घातer consumption or manual work is required.
	 * Please put your code to control UART घड़ी here अगर needed
	 */
पूर्ण

अटल व्योम __serial_घड़ी_off(काष्ठा tty_काष्ठा *tty)
अणु
	/* TODO: Some chipset requires to disable UART घड़ी on client
	 * side to save घातer consumption or manual work is required.
	 * Please put your code to control UART घड़ी off here अगर needed
	 */
पूर्ण

/* serial_घड़ी_vote needs to be called with the ibs lock held */
अटल व्योम serial_घड़ी_vote(अचिन्हित दीर्घ vote, काष्ठा hci_uart *hu)
अणु
	काष्ठा qca_data *qca = hu->priv;
	अचिन्हित पूर्णांक dअगरf;

	bool old_vote = (qca->tx_vote | qca->rx_vote);
	bool new_vote;

	चयन (vote) अणु
	हाल HCI_IBS_VOTE_STATS_UPDATE:
		dअगरf = jअगरfies_to_msecs(jअगरfies - qca->vote_last_jअगर);

		अगर (old_vote)
			qca->vote_off_ms += dअगरf;
		अन्यथा
			qca->vote_on_ms += dअगरf;
		वापस;

	हाल HCI_IBS_TX_VOTE_CLOCK_ON:
		qca->tx_vote = true;
		qca->tx_votes_on++;
		अवरोध;

	हाल HCI_IBS_RX_VOTE_CLOCK_ON:
		qca->rx_vote = true;
		qca->rx_votes_on++;
		अवरोध;

	हाल HCI_IBS_TX_VOTE_CLOCK_OFF:
		qca->tx_vote = false;
		qca->tx_votes_off++;
		अवरोध;

	हाल HCI_IBS_RX_VOTE_CLOCK_OFF:
		qca->rx_vote = false;
		qca->rx_votes_off++;
		अवरोध;

	शेष:
		BT_ERR("Voting irregularity");
		वापस;
	पूर्ण

	new_vote = qca->rx_vote | qca->tx_vote;

	अगर (new_vote != old_vote) अणु
		अगर (new_vote)
			__serial_घड़ी_on(hu->tty);
		अन्यथा
			__serial_घड़ी_off(hu->tty);

		BT_DBG("Vote serial clock %s(%s)", new_vote ? "true" : "false",
		       vote ? "true" : "false");

		dअगरf = jअगरfies_to_msecs(jअगरfies - qca->vote_last_jअगर);

		अगर (new_vote) अणु
			qca->votes_on++;
			qca->vote_off_ms += dअगरf;
		पूर्ण अन्यथा अणु
			qca->votes_off++;
			qca->vote_on_ms += dअगरf;
		पूर्ण
		qca->vote_last_jअगर = jअगरfies;
	पूर्ण
पूर्ण

/* Builds and sends an HCI_IBS command packet.
 * These are very simple packets with only 1 cmd byte.
 */
अटल पूर्णांक send_hci_ibs_cmd(u8 cmd, काष्ठा hci_uart *hu)
अणु
	पूर्णांक err = 0;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा qca_data *qca = hu->priv;

	BT_DBG("hu %p send hci ibs cmd 0x%x", hu, cmd);

	skb = bt_skb_alloc(1, GFP_ATOMIC);
	अगर (!skb) अणु
		BT_ERR("Failed to allocate memory for HCI_IBS packet");
		वापस -ENOMEM;
	पूर्ण

	/* Assign HCI_IBS type */
	skb_put_u8(skb, cmd);

	skb_queue_tail(&qca->txq, skb);

	वापस err;
पूर्ण

अटल व्योम qca_wq_awake_device(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qca_data *qca = container_of(work, काष्ठा qca_data,
					    ws_awake_device);
	काष्ठा hci_uart *hu = qca->hu;
	अचिन्हित दीर्घ retrans_delay;
	अचिन्हित दीर्घ flags;

	BT_DBG("hu %p wq awake device", hu);

	/* Vote क्रम serial घड़ी */
	serial_घड़ी_vote(HCI_IBS_TX_VOTE_CLOCK_ON, hu);

	spin_lock_irqsave(&qca->hci_ibs_lock, flags);

	/* Send wake indication to device */
	अगर (send_hci_ibs_cmd(HCI_IBS_WAKE_IND, hu) < 0)
		BT_ERR("Failed to send WAKE to device");

	qca->ibs_sent_wakes++;

	/* Start retransmit समयr */
	retrans_delay = msecs_to_jअगरfies(qca->wake_retrans);
	mod_समयr(&qca->wake_retrans_समयr, jअगरfies + retrans_delay);

	spin_unlock_irqrestore(&qca->hci_ibs_lock, flags);

	/* Actually send the packets */
	hci_uart_tx_wakeup(hu);
पूर्ण

अटल व्योम qca_wq_awake_rx(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qca_data *qca = container_of(work, काष्ठा qca_data,
					    ws_awake_rx);
	काष्ठा hci_uart *hu = qca->hu;
	अचिन्हित दीर्घ flags;

	BT_DBG("hu %p wq awake rx", hu);

	serial_घड़ी_vote(HCI_IBS_RX_VOTE_CLOCK_ON, hu);

	spin_lock_irqsave(&qca->hci_ibs_lock, flags);
	qca->rx_ibs_state = HCI_IBS_RX_AWAKE;

	/* Always acknowledge device wake up,
	 * sending IBS message करोesn't count as TX ON.
	 */
	अगर (send_hci_ibs_cmd(HCI_IBS_WAKE_ACK, hu) < 0)
		BT_ERR("Failed to acknowledge device wake up");

	qca->ibs_sent_wacks++;

	spin_unlock_irqrestore(&qca->hci_ibs_lock, flags);

	/* Actually send the packets */
	hci_uart_tx_wakeup(hu);
पूर्ण

अटल व्योम qca_wq_serial_rx_घड़ी_vote_off(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qca_data *qca = container_of(work, काष्ठा qca_data,
					    ws_rx_vote_off);
	काष्ठा hci_uart *hu = qca->hu;

	BT_DBG("hu %p rx clock vote off", hu);

	serial_घड़ी_vote(HCI_IBS_RX_VOTE_CLOCK_OFF, hu);
पूर्ण

अटल व्योम qca_wq_serial_tx_घड़ी_vote_off(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qca_data *qca = container_of(work, काष्ठा qca_data,
					    ws_tx_vote_off);
	काष्ठा hci_uart *hu = qca->hu;

	BT_DBG("hu %p tx clock vote off", hu);

	/* Run HCI tx handling unlocked */
	hci_uart_tx_wakeup(hu);

	/* Now that message queued to tty driver, vote क्रम tty घड़ीs off.
	 * It is up to the tty driver to pend the घड़ीs off until tx करोne.
	 */
	serial_घड़ी_vote(HCI_IBS_TX_VOTE_CLOCK_OFF, hu);
पूर्ण

अटल व्योम hci_ibs_tx_idle_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा qca_data *qca = from_समयr(qca, t, tx_idle_समयr);
	काष्ठा hci_uart *hu = qca->hu;
	अचिन्हित दीर्घ flags;

	BT_DBG("hu %p idle timeout in %d state", hu, qca->tx_ibs_state);

	spin_lock_irqsave_nested(&qca->hci_ibs_lock,
				 flags, SINGLE_DEPTH_NESTING);

	चयन (qca->tx_ibs_state) अणु
	हाल HCI_IBS_TX_AWAKE:
		/* TX_IDLE, go to SLEEP */
		अगर (send_hci_ibs_cmd(HCI_IBS_SLEEP_IND, hu) < 0) अणु
			BT_ERR("Failed to send SLEEP to device");
			अवरोध;
		पूर्ण
		qca->tx_ibs_state = HCI_IBS_TX_ASLEEP;
		qca->ibs_sent_slps++;
		queue_work(qca->workqueue, &qca->ws_tx_vote_off);
		अवरोध;

	हाल HCI_IBS_TX_ASLEEP:
	हाल HCI_IBS_TX_WAKING:
	शेष:
		BT_ERR("Spurious timeout tx state %d", qca->tx_ibs_state);
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&qca->hci_ibs_lock, flags);
पूर्ण

अटल व्योम hci_ibs_wake_retrans_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा qca_data *qca = from_समयr(qca, t, wake_retrans_समयr);
	काष्ठा hci_uart *hu = qca->hu;
	अचिन्हित दीर्घ flags, retrans_delay;
	bool retransmit = false;

	BT_DBG("hu %p wake retransmit timeout in %d state",
		hu, qca->tx_ibs_state);

	spin_lock_irqsave_nested(&qca->hci_ibs_lock,
				 flags, SINGLE_DEPTH_NESTING);

	/* Don't retransmit the HCI_IBS_WAKE_IND when suspending. */
	अगर (test_bit(QCA_SUSPENDING, &qca->flags)) अणु
		spin_unlock_irqrestore(&qca->hci_ibs_lock, flags);
		वापस;
	पूर्ण

	चयन (qca->tx_ibs_state) अणु
	हाल HCI_IBS_TX_WAKING:
		/* No WAKE_ACK, retransmit WAKE */
		retransmit = true;
		अगर (send_hci_ibs_cmd(HCI_IBS_WAKE_IND, hu) < 0) अणु
			BT_ERR("Failed to acknowledge device wake up");
			अवरोध;
		पूर्ण
		qca->ibs_sent_wakes++;
		retrans_delay = msecs_to_jअगरfies(qca->wake_retrans);
		mod_समयr(&qca->wake_retrans_समयr, jअगरfies + retrans_delay);
		अवरोध;

	हाल HCI_IBS_TX_ASLEEP:
	हाल HCI_IBS_TX_AWAKE:
	शेष:
		BT_ERR("Spurious timeout tx state %d", qca->tx_ibs_state);
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&qca->hci_ibs_lock, flags);

	अगर (retransmit)
		hci_uart_tx_wakeup(hu);
पूर्ण


अटल व्योम qca_controller_memdump_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qca_data *qca = container_of(work, काष्ठा qca_data,
					ctrl_memdump_समयout.work);
	काष्ठा hci_uart *hu = qca->hu;

	mutex_lock(&qca->hci_memdump_lock);
	अगर (test_bit(QCA_MEMDUMP_COLLECTION, &qca->flags)) अणु
		qca->memdump_state = QCA_MEMDUMP_TIMEOUT;
		अगर (!test_bit(QCA_HW_ERROR_EVENT, &qca->flags)) अणु
			/* Inject hw error event to reset the device
			 * and driver.
			 */
			hci_reset_dev(hu->hdev);
		पूर्ण
	पूर्ण

	mutex_unlock(&qca->hci_memdump_lock);
पूर्ण


/* Initialize protocol */
अटल पूर्णांक qca_खोलो(काष्ठा hci_uart *hu)
अणु
	काष्ठा qca_serdev *qcadev;
	काष्ठा qca_data *qca;

	BT_DBG("hu %p qca_open", hu);

	अगर (!hci_uart_has_flow_control(hu))
		वापस -EOPNOTSUPP;

	qca = kzalloc(माप(काष्ठा qca_data), GFP_KERNEL);
	अगर (!qca)
		वापस -ENOMEM;

	skb_queue_head_init(&qca->txq);
	skb_queue_head_init(&qca->tx_रुको_q);
	skb_queue_head_init(&qca->rx_memdump_q);
	spin_lock_init(&qca->hci_ibs_lock);
	mutex_init(&qca->hci_memdump_lock);
	qca->workqueue = alloc_ordered_workqueue("qca_wq", 0);
	अगर (!qca->workqueue) अणु
		BT_ERR("QCA Workqueue not initialized properly");
		kमुक्त(qca);
		वापस -ENOMEM;
	पूर्ण

	INIT_WORK(&qca->ws_awake_rx, qca_wq_awake_rx);
	INIT_WORK(&qca->ws_awake_device, qca_wq_awake_device);
	INIT_WORK(&qca->ws_rx_vote_off, qca_wq_serial_rx_घड़ी_vote_off);
	INIT_WORK(&qca->ws_tx_vote_off, qca_wq_serial_tx_घड़ी_vote_off);
	INIT_WORK(&qca->ctrl_memdump_evt, qca_controller_memdump);
	INIT_DELAYED_WORK(&qca->ctrl_memdump_समयout,
			  qca_controller_memdump_समयout);
	init_रुकोqueue_head(&qca->suspend_रुको_q);

	qca->hu = hu;
	init_completion(&qca->drop_ev_comp);

	/* Assume we start with both sides asleep -- extra wakes OK */
	qca->tx_ibs_state = HCI_IBS_TX_ASLEEP;
	qca->rx_ibs_state = HCI_IBS_RX_ASLEEP;

	qca->vote_last_jअगर = jअगरfies;

	hu->priv = qca;

	अगर (hu->serdev) अणु
		qcadev = serdev_device_get_drvdata(hu->serdev);

		अगर (qca_is_wcn399x(qcadev->btsoc_type))
			hu->init_speed = qcadev->init_speed;

		अगर (qcadev->oper_speed)
			hu->oper_speed = qcadev->oper_speed;
	पूर्ण

	समयr_setup(&qca->wake_retrans_समयr, hci_ibs_wake_retrans_समयout, 0);
	qca->wake_retrans = IBS_WAKE_RETRANS_TIMEOUT_MS;

	समयr_setup(&qca->tx_idle_समयr, hci_ibs_tx_idle_समयout, 0);
	qca->tx_idle_delay = IBS_HOST_TX_IDLE_TIMEOUT_MS;

	BT_DBG("HCI_UART_QCA open, tx_idle_delay=%u, wake_retrans=%u",
	       qca->tx_idle_delay, qca->wake_retrans);

	वापस 0;
पूर्ण

अटल व्योम qca_debugfs_init(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);
	काष्ठा qca_data *qca = hu->priv;
	काष्ठा dentry *ibs_dir;
	umode_t mode;

	अगर (!hdev->debugfs)
		वापस;

	ibs_dir = debugfs_create_dir("ibs", hdev->debugfs);

	/* पढ़ो only */
	mode = 0444;
	debugfs_create_u8("tx_ibs_state", mode, ibs_dir, &qca->tx_ibs_state);
	debugfs_create_u8("rx_ibs_state", mode, ibs_dir, &qca->rx_ibs_state);
	debugfs_create_u64("ibs_sent_sleeps", mode, ibs_dir,
			   &qca->ibs_sent_slps);
	debugfs_create_u64("ibs_sent_wakes", mode, ibs_dir,
			   &qca->ibs_sent_wakes);
	debugfs_create_u64("ibs_sent_wake_acks", mode, ibs_dir,
			   &qca->ibs_sent_wacks);
	debugfs_create_u64("ibs_recv_sleeps", mode, ibs_dir,
			   &qca->ibs_recv_slps);
	debugfs_create_u64("ibs_recv_wakes", mode, ibs_dir,
			   &qca->ibs_recv_wakes);
	debugfs_create_u64("ibs_recv_wake_acks", mode, ibs_dir,
			   &qca->ibs_recv_wacks);
	debugfs_create_bool("tx_vote", mode, ibs_dir, &qca->tx_vote);
	debugfs_create_u64("tx_votes_on", mode, ibs_dir, &qca->tx_votes_on);
	debugfs_create_u64("tx_votes_off", mode, ibs_dir, &qca->tx_votes_off);
	debugfs_create_bool("rx_vote", mode, ibs_dir, &qca->rx_vote);
	debugfs_create_u64("rx_votes_on", mode, ibs_dir, &qca->rx_votes_on);
	debugfs_create_u64("rx_votes_off", mode, ibs_dir, &qca->rx_votes_off);
	debugfs_create_u64("votes_on", mode, ibs_dir, &qca->votes_on);
	debugfs_create_u64("votes_off", mode, ibs_dir, &qca->votes_off);
	debugfs_create_u32("vote_on_ms", mode, ibs_dir, &qca->vote_on_ms);
	debugfs_create_u32("vote_off_ms", mode, ibs_dir, &qca->vote_off_ms);

	/* पढ़ो/ग_लिखो */
	mode = 0644;
	debugfs_create_u32("wake_retrans", mode, ibs_dir, &qca->wake_retrans);
	debugfs_create_u32("tx_idle_delay", mode, ibs_dir,
			   &qca->tx_idle_delay);
पूर्ण

/* Flush protocol data */
अटल पूर्णांक qca_flush(काष्ठा hci_uart *hu)
अणु
	काष्ठा qca_data *qca = hu->priv;

	BT_DBG("hu %p qca flush", hu);

	skb_queue_purge(&qca->tx_रुको_q);
	skb_queue_purge(&qca->txq);

	वापस 0;
पूर्ण

/* Close protocol */
अटल पूर्णांक qca_बंद(काष्ठा hci_uart *hu)
अणु
	काष्ठा qca_data *qca = hu->priv;

	BT_DBG("hu %p qca close", hu);

	serial_घड़ी_vote(HCI_IBS_VOTE_STATS_UPDATE, hu);

	skb_queue_purge(&qca->tx_रुको_q);
	skb_queue_purge(&qca->txq);
	skb_queue_purge(&qca->rx_memdump_q);
	del_समयr(&qca->tx_idle_समयr);
	del_समयr(&qca->wake_retrans_समयr);
	destroy_workqueue(qca->workqueue);
	qca->hu = शून्य;

	kमुक्त_skb(qca->rx_skb);

	hu->priv = शून्य;

	kमुक्त(qca);

	वापस 0;
पूर्ण

/* Called upon a wake-up-indication from the device.
 */
अटल व्योम device_want_to_wakeup(काष्ठा hci_uart *hu)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा qca_data *qca = hu->priv;

	BT_DBG("hu %p want to wake up", hu);

	spin_lock_irqsave(&qca->hci_ibs_lock, flags);

	qca->ibs_recv_wakes++;

	/* Don't wake the rx up when suspending. */
	अगर (test_bit(QCA_SUSPENDING, &qca->flags)) अणु
		spin_unlock_irqrestore(&qca->hci_ibs_lock, flags);
		वापस;
	पूर्ण

	चयन (qca->rx_ibs_state) अणु
	हाल HCI_IBS_RX_ASLEEP:
		/* Make sure घड़ी is on - we may have turned घड़ी off since
		 * receiving the wake up indicator awake rx घड़ी.
		 */
		queue_work(qca->workqueue, &qca->ws_awake_rx);
		spin_unlock_irqrestore(&qca->hci_ibs_lock, flags);
		वापस;

	हाल HCI_IBS_RX_AWAKE:
		/* Always acknowledge device wake up,
		 * sending IBS message करोesn't count as TX ON.
		 */
		अगर (send_hci_ibs_cmd(HCI_IBS_WAKE_ACK, hu) < 0) अणु
			BT_ERR("Failed to acknowledge device wake up");
			अवरोध;
		पूर्ण
		qca->ibs_sent_wacks++;
		अवरोध;

	शेष:
		/* Any other state is illegal */
		BT_ERR("Received HCI_IBS_WAKE_IND in rx state %d",
		       qca->rx_ibs_state);
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&qca->hci_ibs_lock, flags);

	/* Actually send the packets */
	hci_uart_tx_wakeup(hu);
पूर्ण

/* Called upon a sleep-indication from the device.
 */
अटल व्योम device_want_to_sleep(काष्ठा hci_uart *hu)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा qca_data *qca = hu->priv;

	BT_DBG("hu %p want to sleep in %d state", hu, qca->rx_ibs_state);

	spin_lock_irqsave(&qca->hci_ibs_lock, flags);

	qca->ibs_recv_slps++;

	चयन (qca->rx_ibs_state) अणु
	हाल HCI_IBS_RX_AWAKE:
		/* Update state */
		qca->rx_ibs_state = HCI_IBS_RX_ASLEEP;
		/* Vote off rx घड़ी under workqueue */
		queue_work(qca->workqueue, &qca->ws_rx_vote_off);
		अवरोध;

	हाल HCI_IBS_RX_ASLEEP:
		अवरोध;

	शेष:
		/* Any other state is illegal */
		BT_ERR("Received HCI_IBS_SLEEP_IND in rx state %d",
		       qca->rx_ibs_state);
		अवरोध;
	पूर्ण

	wake_up_पूर्णांकerruptible(&qca->suspend_रुको_q);

	spin_unlock_irqrestore(&qca->hci_ibs_lock, flags);
पूर्ण

/* Called upon wake-up-acknowledgement from the device
 */
अटल व्योम device_woke_up(काष्ठा hci_uart *hu)
अणु
	अचिन्हित दीर्घ flags, idle_delay;
	काष्ठा qca_data *qca = hu->priv;
	काष्ठा sk_buff *skb = शून्य;

	BT_DBG("hu %p woke up", hu);

	spin_lock_irqsave(&qca->hci_ibs_lock, flags);

	qca->ibs_recv_wacks++;

	/* Don't react to the wake-up-acknowledgment when suspending. */
	अगर (test_bit(QCA_SUSPENDING, &qca->flags)) अणु
		spin_unlock_irqrestore(&qca->hci_ibs_lock, flags);
		वापस;
	पूर्ण

	चयन (qca->tx_ibs_state) अणु
	हाल HCI_IBS_TX_AWAKE:
		/* Expect one अगर we send 2 WAKEs */
		BT_DBG("Received HCI_IBS_WAKE_ACK in tx state %d",
		       qca->tx_ibs_state);
		अवरोध;

	हाल HCI_IBS_TX_WAKING:
		/* Send pending packets */
		जबतक ((skb = skb_dequeue(&qca->tx_रुको_q)))
			skb_queue_tail(&qca->txq, skb);

		/* Switch समयrs and change state to HCI_IBS_TX_AWAKE */
		del_समयr(&qca->wake_retrans_समयr);
		idle_delay = msecs_to_jअगरfies(qca->tx_idle_delay);
		mod_समयr(&qca->tx_idle_समयr, jअगरfies + idle_delay);
		qca->tx_ibs_state = HCI_IBS_TX_AWAKE;
		अवरोध;

	हाल HCI_IBS_TX_ASLEEP:
	शेष:
		BT_ERR("Received HCI_IBS_WAKE_ACK in tx state %d",
		       qca->tx_ibs_state);
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&qca->hci_ibs_lock, flags);

	/* Actually send the packets */
	hci_uart_tx_wakeup(hu);
पूर्ण

/* Enqueue frame क्रम transmittion (padding, crc, etc) may be called from
 * two simultaneous tasklets.
 */
अटल पूर्णांक qca_enqueue(काष्ठा hci_uart *hu, काष्ठा sk_buff *skb)
अणु
	अचिन्हित दीर्घ flags = 0, idle_delay;
	काष्ठा qca_data *qca = hu->priv;

	BT_DBG("hu %p qca enq skb %p tx_ibs_state %d", hu, skb,
	       qca->tx_ibs_state);

	अगर (test_bit(QCA_SSR_TRIGGERED, &qca->flags)) अणु
		/* As SSR is in progress, ignore the packets */
		bt_dev_dbg(hu->hdev, "SSR is in progress");
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	/* Prepend skb with frame type */
	स_नकल(skb_push(skb, 1), &hci_skb_pkt_type(skb), 1);

	spin_lock_irqsave(&qca->hci_ibs_lock, flags);

	/* Don't go to sleep in middle of patch करोwnload or
	 * Out-Of-Band(GPIOs control) sleep is selected.
	 * Don't wake the device up when suspending.
	 */
	अगर (test_bit(QCA_IBS_DISABLED, &qca->flags) ||
	    test_bit(QCA_SUSPENDING, &qca->flags)) अणु
		skb_queue_tail(&qca->txq, skb);
		spin_unlock_irqrestore(&qca->hci_ibs_lock, flags);
		वापस 0;
	पूर्ण

	/* Act according to current state */
	चयन (qca->tx_ibs_state) अणु
	हाल HCI_IBS_TX_AWAKE:
		BT_DBG("Device awake, sending normally");
		skb_queue_tail(&qca->txq, skb);
		idle_delay = msecs_to_jअगरfies(qca->tx_idle_delay);
		mod_समयr(&qca->tx_idle_समयr, jअगरfies + idle_delay);
		अवरोध;

	हाल HCI_IBS_TX_ASLEEP:
		BT_DBG("Device asleep, waking up and queueing packet");
		/* Save packet क्रम later */
		skb_queue_tail(&qca->tx_रुको_q, skb);

		qca->tx_ibs_state = HCI_IBS_TX_WAKING;
		/* Schedule a work queue to wake up device */
		queue_work(qca->workqueue, &qca->ws_awake_device);
		अवरोध;

	हाल HCI_IBS_TX_WAKING:
		BT_DBG("Device waking up, queueing packet");
		/* Transient state; just keep packet क्रम later */
		skb_queue_tail(&qca->tx_रुको_q, skb);
		अवरोध;

	शेष:
		BT_ERR("Illegal tx state: %d (losing packet)",
		       qca->tx_ibs_state);
		kमुक्त_skb(skb);
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&qca->hci_ibs_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक qca_ibs_sleep_ind(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);

	BT_DBG("hu %p recv hci ibs cmd 0x%x", hu, HCI_IBS_SLEEP_IND);

	device_want_to_sleep(hu);

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक qca_ibs_wake_ind(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);

	BT_DBG("hu %p recv hci ibs cmd 0x%x", hu, HCI_IBS_WAKE_IND);

	device_want_to_wakeup(hu);

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक qca_ibs_wake_ack(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);

	BT_DBG("hu %p recv hci ibs cmd 0x%x", hu, HCI_IBS_WAKE_ACK);

	device_woke_up(hu);

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक qca_recv_acl_data(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	/* We receive debug logs from chip as an ACL packets.
	 * Instead of sending the data to ACL to decode the
	 * received data, we are pushing them to the above layers
	 * as a diagnostic packet.
	 */
	अगर (get_unaligned_le16(skb->data) == QCA_DEBUG_HANDLE)
		वापस hci_recv_diag(hdev, skb);

	वापस hci_recv_frame(hdev, skb);
पूर्ण

अटल व्योम qca_controller_memdump(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qca_data *qca = container_of(work, काष्ठा qca_data,
					    ctrl_memdump_evt);
	काष्ठा hci_uart *hu = qca->hu;
	काष्ठा sk_buff *skb;
	काष्ठा qca_memdump_event_hdr *cmd_hdr;
	काष्ठा qca_memdump_data *qca_memdump = qca->qca_memdump;
	काष्ठा qca_dump_size *dump;
	अक्षर *memdump_buf;
	अक्षर nullBuff[QCA_DUMP_PACKET_SIZE] = अणु 0 पूर्ण;
	u16 seq_no;
	u32 dump_size;
	u32 rx_size;
	क्रमागत qca_btsoc_type soc_type = qca_soc_type(hu);

	जबतक ((skb = skb_dequeue(&qca->rx_memdump_q))) अणु

		mutex_lock(&qca->hci_memdump_lock);
		/* Skip processing the received packets अगर समयout detected
		 * or memdump collection completed.
		 */
		अगर (qca->memdump_state == QCA_MEMDUMP_TIMEOUT ||
		    qca->memdump_state == QCA_MEMDUMP_COLLECTED) अणु
			mutex_unlock(&qca->hci_memdump_lock);
			वापस;
		पूर्ण

		अगर (!qca_memdump) अणु
			qca_memdump = kzalloc(माप(काष्ठा qca_memdump_data),
					      GFP_ATOMIC);
			अगर (!qca_memdump) अणु
				mutex_unlock(&qca->hci_memdump_lock);
				वापस;
			पूर्ण

			qca->qca_memdump = qca_memdump;
		पूर्ण

		qca->memdump_state = QCA_MEMDUMP_COLLECTING;
		cmd_hdr = (व्योम *) skb->data;
		seq_no = __le16_to_cpu(cmd_hdr->seq_no);
		skb_pull(skb, माप(काष्ठा qca_memdump_event_hdr));

		अगर (!seq_no) अणु

			/* This is the first frame of memdump packet from
			 * the controller, Disable IBS to recevie dump
			 * with out any पूर्णांकerruption, ideally समय required क्रम
			 * the controller to send the dump is 8 seconds. let us
			 * start समयr to handle this asynchronous activity.
			 */
			set_bit(QCA_IBS_DISABLED, &qca->flags);
			set_bit(QCA_MEMDUMP_COLLECTION, &qca->flags);
			dump = (व्योम *) skb->data;
			dump_size = __le32_to_cpu(dump->dump_size);
			अगर (!(dump_size)) अणु
				bt_dev_err(hu->hdev, "Rx invalid memdump size");
				kमुक्त(qca_memdump);
				kमुक्त_skb(skb);
				qca->qca_memdump = शून्य;
				mutex_unlock(&qca->hci_memdump_lock);
				वापस;
			पूर्ण

			bt_dev_info(hu->hdev, "QCA collecting dump of size:%u",
				    dump_size);
			queue_delayed_work(qca->workqueue,
					   &qca->ctrl_memdump_समयout,
					   msecs_to_jअगरfies(MEMDUMP_TIMEOUT_MS)
					  );

			skb_pull(skb, माप(dump_size));
			memdump_buf = vदो_स्मृति(dump_size);
			qca_memdump->ram_dump_size = dump_size;
			qca_memdump->memdump_buf_head = memdump_buf;
			qca_memdump->memdump_buf_tail = memdump_buf;
		पूर्ण

		memdump_buf = qca_memdump->memdump_buf_tail;

		/* If sequence no 0 is missed then there is no poपूर्णांक in
		 * accepting the other sequences.
		 */
		अगर (!memdump_buf) अणु
			bt_dev_err(hu->hdev, "QCA: Discarding other packets");
			kमुक्त(qca_memdump);
			kमुक्त_skb(skb);
			qca->qca_memdump = शून्य;
			mutex_unlock(&qca->hci_memdump_lock);
			वापस;
		पूर्ण

		/* There could be chance of missing some packets from
		 * the controller. In such हालs let us store the dummy
		 * packets in the buffer.
		 */
		/* For QCA6390, controller करोes not lost packets but
		 * sequence number field of packet someबार has error
		 * bits, so skip this checking क्रम missing packet.
		 */
		जबतक ((seq_no > qca_memdump->current_seq_no + 1) &&
		       (soc_type != QCA_QCA6390) &&
		       seq_no != QCA_LAST_SEQUENCE_NUM) अणु
			bt_dev_err(hu->hdev, "QCA controller missed packet:%d",
				   qca_memdump->current_seq_no);
			rx_size = qca_memdump->received_dump;
			rx_size += QCA_DUMP_PACKET_SIZE;
			अगर (rx_size > qca_memdump->ram_dump_size) अणु
				bt_dev_err(hu->hdev,
					   "QCA memdump received %d, no space for missed packet",
					   qca_memdump->received_dump);
				अवरोध;
			पूर्ण
			स_नकल(memdump_buf, nullBuff, QCA_DUMP_PACKET_SIZE);
			memdump_buf = memdump_buf + QCA_DUMP_PACKET_SIZE;
			qca_memdump->received_dump += QCA_DUMP_PACKET_SIZE;
			qca_memdump->current_seq_no++;
		पूर्ण

		rx_size = qca_memdump->received_dump + skb->len;
		अगर (rx_size <= qca_memdump->ram_dump_size) अणु
			अगर ((seq_no != QCA_LAST_SEQUENCE_NUM) &&
			    (seq_no != qca_memdump->current_seq_no))
				bt_dev_err(hu->hdev,
					   "QCA memdump unexpected packet %d",
					   seq_no);
			bt_dev_dbg(hu->hdev,
				   "QCA memdump packet %d with length %d",
				   seq_no, skb->len);
			स_नकल(memdump_buf, (अचिन्हित अक्षर *)skb->data,
			       skb->len);
			memdump_buf = memdump_buf + skb->len;
			qca_memdump->memdump_buf_tail = memdump_buf;
			qca_memdump->current_seq_no = seq_no + 1;
			qca_memdump->received_dump += skb->len;
		पूर्ण अन्यथा अणु
			bt_dev_err(hu->hdev,
				   "QCA memdump received %d, no space for packet %d",
				   qca_memdump->received_dump, seq_no);
		पूर्ण
		qca->qca_memdump = qca_memdump;
		kमुक्त_skb(skb);
		अगर (seq_no == QCA_LAST_SEQUENCE_NUM) अणु
			bt_dev_info(hu->hdev,
				    "QCA memdump Done, received %d, total %d",
				    qca_memdump->received_dump,
				    qca_memdump->ram_dump_size);
			memdump_buf = qca_memdump->memdump_buf_head;
			dev_coredumpv(&hu->serdev->dev, memdump_buf,
				      qca_memdump->received_dump, GFP_KERNEL);
			cancel_delayed_work(&qca->ctrl_memdump_समयout);
			kमुक्त(qca->qca_memdump);
			qca->qca_memdump = शून्य;
			qca->memdump_state = QCA_MEMDUMP_COLLECTED;
			clear_bit(QCA_MEMDUMP_COLLECTION, &qca->flags);
		पूर्ण

		mutex_unlock(&qca->hci_memdump_lock);
	पूर्ण

पूर्ण

अटल पूर्णांक qca_controller_memdump_event(काष्ठा hci_dev *hdev,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);
	काष्ठा qca_data *qca = hu->priv;

	set_bit(QCA_SSR_TRIGGERED, &qca->flags);
	skb_queue_tail(&qca->rx_memdump_q, skb);
	queue_work(qca->workqueue, &qca->ctrl_memdump_evt);

	वापस 0;
पूर्ण

अटल पूर्णांक qca_recv_event(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);
	काष्ठा qca_data *qca = hu->priv;

	अगर (test_bit(QCA_DROP_VENDOR_EVENT, &qca->flags)) अणु
		काष्ठा hci_event_hdr *hdr = (व्योम *)skb->data;

		/* For the WCN3990 the venकरोr command क्रम a baudrate change
		 * isn't sent as synchronous HCI command, because the
		 * controller sends the corresponding venकरोr event with the
		 * new baudrate. The event is received and properly decoded
		 * after changing the baudrate of the host port. It needs to
		 * be dropped, otherwise it can be misपूर्णांकerpreted as
		 * response to a later firmware करोwnload command (also a
		 * venकरोr command).
		 */

		अगर (hdr->evt == HCI_EV_VENDOR)
			complete(&qca->drop_ev_comp);

		kमुक्त_skb(skb);

		वापस 0;
	पूर्ण
	/* We receive chip memory dump as an event packet, With a dedicated
	 * handler followed by a hardware error event. When this event is
	 * received we store dump पूर्णांकo a file beक्रमe closing hci. This
	 * dump will help in triaging the issues.
	 */
	अगर ((skb->data[0] == HCI_VENDOR_PKT) &&
	    (get_unaligned_be16(skb->data + 2) == QCA_SSR_DUMP_HANDLE))
		वापस qca_controller_memdump_event(hdev, skb);

	वापस hci_recv_frame(hdev, skb);
पूर्ण

#घोषणा QCA_IBS_SLEEP_IND_EVENT \
	.type = HCI_IBS_SLEEP_IND, \
	.hlen = 0, \
	.loff = 0, \
	.lsize = 0, \
	.maxlen = HCI_MAX_IBS_SIZE

#घोषणा QCA_IBS_WAKE_IND_EVENT \
	.type = HCI_IBS_WAKE_IND, \
	.hlen = 0, \
	.loff = 0, \
	.lsize = 0, \
	.maxlen = HCI_MAX_IBS_SIZE

#घोषणा QCA_IBS_WAKE_ACK_EVENT \
	.type = HCI_IBS_WAKE_ACK, \
	.hlen = 0, \
	.loff = 0, \
	.lsize = 0, \
	.maxlen = HCI_MAX_IBS_SIZE

अटल स्थिर काष्ठा h4_recv_pkt qca_recv_pkts[] = अणु
	अणु H4_RECV_ACL,             .recv = qca_recv_acl_data पूर्ण,
	अणु H4_RECV_SCO,             .recv = hci_recv_frame    पूर्ण,
	अणु H4_RECV_EVENT,           .recv = qca_recv_event    पूर्ण,
	अणु QCA_IBS_WAKE_IND_EVENT,  .recv = qca_ibs_wake_ind  पूर्ण,
	अणु QCA_IBS_WAKE_ACK_EVENT,  .recv = qca_ibs_wake_ack  पूर्ण,
	अणु QCA_IBS_SLEEP_IND_EVENT, .recv = qca_ibs_sleep_ind पूर्ण,
पूर्ण;

अटल पूर्णांक qca_recv(काष्ठा hci_uart *hu, स्थिर व्योम *data, पूर्णांक count)
अणु
	काष्ठा qca_data *qca = hu->priv;

	अगर (!test_bit(HCI_UART_REGISTERED, &hu->flags))
		वापस -EUNATCH;

	qca->rx_skb = h4_recv_buf(hu->hdev, qca->rx_skb, data, count,
				  qca_recv_pkts, ARRAY_SIZE(qca_recv_pkts));
	अगर (IS_ERR(qca->rx_skb)) अणु
		पूर्णांक err = PTR_ERR(qca->rx_skb);
		bt_dev_err(hu->hdev, "Frame reassembly failed (%d)", err);
		qca->rx_skb = शून्य;
		वापस err;
	पूर्ण

	वापस count;
पूर्ण

अटल काष्ठा sk_buff *qca_dequeue(काष्ठा hci_uart *hu)
अणु
	काष्ठा qca_data *qca = hu->priv;

	वापस skb_dequeue(&qca->txq);
पूर्ण

अटल uपूर्णांक8_t qca_get_baudrate_value(पूर्णांक speed)
अणु
	चयन (speed) अणु
	हाल 9600:
		वापस QCA_BAUDRATE_9600;
	हाल 19200:
		वापस QCA_BAUDRATE_19200;
	हाल 38400:
		वापस QCA_BAUDRATE_38400;
	हाल 57600:
		वापस QCA_BAUDRATE_57600;
	हाल 115200:
		वापस QCA_BAUDRATE_115200;
	हाल 230400:
		वापस QCA_BAUDRATE_230400;
	हाल 460800:
		वापस QCA_BAUDRATE_460800;
	हाल 500000:
		वापस QCA_BAUDRATE_500000;
	हाल 921600:
		वापस QCA_BAUDRATE_921600;
	हाल 1000000:
		वापस QCA_BAUDRATE_1000000;
	हाल 2000000:
		वापस QCA_BAUDRATE_2000000;
	हाल 3000000:
		वापस QCA_BAUDRATE_3000000;
	हाल 3200000:
		वापस QCA_BAUDRATE_3200000;
	हाल 3500000:
		वापस QCA_BAUDRATE_3500000;
	शेष:
		वापस QCA_BAUDRATE_115200;
	पूर्ण
पूर्ण

अटल पूर्णांक qca_set_baudrate(काष्ठा hci_dev *hdev, uपूर्णांक8_t baudrate)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);
	काष्ठा qca_data *qca = hu->priv;
	काष्ठा sk_buff *skb;
	u8 cmd[] = अणु 0x01, 0x48, 0xFC, 0x01, 0x00 पूर्ण;

	अगर (baudrate > QCA_BAUDRATE_3200000)
		वापस -EINVAL;

	cmd[4] = baudrate;

	skb = bt_skb_alloc(माप(cmd), GFP_KERNEL);
	अगर (!skb) अणु
		bt_dev_err(hdev, "Failed to allocate baudrate packet");
		वापस -ENOMEM;
	पूर्ण

	/* Assign commands to change baudrate and packet type. */
	skb_put_data(skb, cmd, माप(cmd));
	hci_skb_pkt_type(skb) = HCI_COMMAND_PKT;

	skb_queue_tail(&qca->txq, skb);
	hci_uart_tx_wakeup(hu);

	/* Wait क्रम the baudrate change request to be sent */

	जबतक (!skb_queue_empty(&qca->txq))
		usleep_range(100, 200);

	अगर (hu->serdev)
		serdev_device_रुको_until_sent(hu->serdev,
		      msecs_to_jअगरfies(CMD_TRANS_TIMEOUT_MS));

	/* Give the controller समय to process the request */
	अगर (qca_is_wcn399x(qca_soc_type(hu)))
		usleep_range(1000, 10000);
	अन्यथा
		msleep(300);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम host_set_baudrate(काष्ठा hci_uart *hu, अचिन्हित पूर्णांक speed)
अणु
	अगर (hu->serdev)
		serdev_device_set_baudrate(hu->serdev, speed);
	अन्यथा
		hci_uart_set_baudrate(hu, speed);
पूर्ण

अटल पूर्णांक qca_send_घातer_pulse(काष्ठा hci_uart *hu, bool on)
अणु
	पूर्णांक ret;
	पूर्णांक समयout = msecs_to_jअगरfies(CMD_TRANS_TIMEOUT_MS);
	u8 cmd = on ? QCA_WCN3990_POWERON_PULSE : QCA_WCN3990_POWEROFF_PULSE;

	/* These घातer pulses are single byte command which are sent
	 * at required baudrate to wcn3990. On wcn3990, we have an बाह्यal
	 * circuit at Tx pin which decodes the pulse sent at specअगरic baudrate.
	 * For example, wcn3990 supports RF COEX antenna क्रम both Wi-Fi/BT
	 * and also we use the same घातer inमाला_दो to turn on and off क्रम
	 * Wi-Fi/BT. Powering up the घातer sources will not enable BT, until
	 * we send a घातer on pulse at 115200 bps. This algorithm will help to
	 * save घातer. Disabling hardware flow control is mandatory जबतक
	 * sending घातer pulses to SoC.
	 */
	bt_dev_dbg(hu->hdev, "sending power pulse %02x to controller", cmd);

	serdev_device_ग_लिखो_flush(hu->serdev);
	hci_uart_set_flow_control(hu, true);
	ret = serdev_device_ग_लिखो_buf(hu->serdev, &cmd, माप(cmd));
	अगर (ret < 0) अणु
		bt_dev_err(hu->hdev, "failed to send power pulse %02x", cmd);
		वापस ret;
	पूर्ण

	serdev_device_रुको_until_sent(hu->serdev, समयout);
	hci_uart_set_flow_control(hu, false);

	/* Give to controller समय to boot/shutकरोwn */
	अगर (on)
		msleep(100);
	अन्यथा
		usleep_range(1000, 10000);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक qca_get_speed(काष्ठा hci_uart *hu,
				  क्रमागत qca_speed_type speed_type)
अणु
	अचिन्हित पूर्णांक speed = 0;

	अगर (speed_type == QCA_INIT_SPEED) अणु
		अगर (hu->init_speed)
			speed = hu->init_speed;
		अन्यथा अगर (hu->proto->init_speed)
			speed = hu->proto->init_speed;
	पूर्ण अन्यथा अणु
		अगर (hu->oper_speed)
			speed = hu->oper_speed;
		अन्यथा अगर (hu->proto->oper_speed)
			speed = hu->proto->oper_speed;
	पूर्ण

	वापस speed;
पूर्ण

अटल पूर्णांक qca_check_speeds(काष्ठा hci_uart *hu)
अणु
	अगर (qca_is_wcn399x(qca_soc_type(hu))) अणु
		अगर (!qca_get_speed(hu, QCA_INIT_SPEED) &&
		    !qca_get_speed(hu, QCA_OPER_SPEED))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (!qca_get_speed(hu, QCA_INIT_SPEED) ||
		    !qca_get_speed(hu, QCA_OPER_SPEED))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qca_set_speed(काष्ठा hci_uart *hu, क्रमागत qca_speed_type speed_type)
अणु
	अचिन्हित पूर्णांक speed, qca_baudrate;
	काष्ठा qca_data *qca = hu->priv;
	पूर्णांक ret = 0;

	अगर (speed_type == QCA_INIT_SPEED) अणु
		speed = qca_get_speed(hu, QCA_INIT_SPEED);
		अगर (speed)
			host_set_baudrate(hu, speed);
	पूर्ण अन्यथा अणु
		क्रमागत qca_btsoc_type soc_type = qca_soc_type(hu);

		speed = qca_get_speed(hu, QCA_OPER_SPEED);
		अगर (!speed)
			वापस 0;

		/* Disable flow control क्रम wcn3990 to deनिश्चित RTS जबतक
		 * changing the baudrate of chip and host.
		 */
		अगर (qca_is_wcn399x(soc_type))
			hci_uart_set_flow_control(hu, true);

		अगर (soc_type == QCA_WCN3990) अणु
			reinit_completion(&qca->drop_ev_comp);
			set_bit(QCA_DROP_VENDOR_EVENT, &qca->flags);
		पूर्ण

		qca_baudrate = qca_get_baudrate_value(speed);
		bt_dev_dbg(hu->hdev, "Set UART speed to %d", speed);
		ret = qca_set_baudrate(hu->hdev, qca_baudrate);
		अगर (ret)
			जाओ error;

		host_set_baudrate(hu, speed);

error:
		अगर (qca_is_wcn399x(soc_type))
			hci_uart_set_flow_control(hu, false);

		अगर (soc_type == QCA_WCN3990) अणु
			/* Wait क्रम the controller to send the venकरोr event
			 * क्रम the baudrate change command.
			 */
			अगर (!रुको_क्रम_completion_समयout(&qca->drop_ev_comp,
						 msecs_to_jअगरfies(100))) अणु
				bt_dev_err(hu->hdev,
					   "Failed to change controller baudrate\n");
				ret = -ETIMEDOUT;
			पूर्ण

			clear_bit(QCA_DROP_VENDOR_EVENT, &qca->flags);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक qca_send_crashbuffer(काष्ठा hci_uart *hu)
अणु
	काष्ठा qca_data *qca = hu->priv;
	काष्ठा sk_buff *skb;

	skb = bt_skb_alloc(QCA_CRASHBYTE_PACKET_LEN, GFP_KERNEL);
	अगर (!skb) अणु
		bt_dev_err(hu->hdev, "Failed to allocate memory for skb packet");
		वापस -ENOMEM;
	पूर्ण

	/* We क्रमcefully crash the controller, by sending 0xfb byte क्रम
	 * 1024 बार. We also might have chance of losing data, To be
	 * on safer side we send 1096 bytes to the SoC.
	 */
	स_रखो(skb_put(skb, QCA_CRASHBYTE_PACKET_LEN), QCA_MEMDUMP_BYTE,
	       QCA_CRASHBYTE_PACKET_LEN);
	hci_skb_pkt_type(skb) = HCI_COMMAND_PKT;
	bt_dev_info(hu->hdev, "crash the soc to collect controller dump");
	skb_queue_tail(&qca->txq, skb);
	hci_uart_tx_wakeup(hu);

	वापस 0;
पूर्ण

अटल व्योम qca_रुको_क्रम_dump_collection(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);
	काष्ठा qca_data *qca = hu->priv;

	रुको_on_bit_समयout(&qca->flags, QCA_MEMDUMP_COLLECTION,
			    TASK_UNINTERRUPTIBLE, MEMDUMP_TIMEOUT_MS);

	clear_bit(QCA_MEMDUMP_COLLECTION, &qca->flags);
पूर्ण

अटल व्योम qca_hw_error(काष्ठा hci_dev *hdev, u8 code)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);
	काष्ठा qca_data *qca = hu->priv;

	set_bit(QCA_SSR_TRIGGERED, &qca->flags);
	set_bit(QCA_HW_ERROR_EVENT, &qca->flags);
	bt_dev_info(hdev, "mem_dump_status: %d", qca->memdump_state);

	अगर (qca->memdump_state == QCA_MEMDUMP_IDLE) अणु
		/* If hardware error event received क्रम other than QCA
		 * soc memory dump event, then we need to crash the SOC
		 * and रुको here क्रम 8 seconds to get the dump packets.
		 * This will block मुख्य thपढ़ो to be on hold until we
		 * collect dump.
		 */
		set_bit(QCA_MEMDUMP_COLLECTION, &qca->flags);
		qca_send_crashbuffer(hu);
		qca_रुको_क्रम_dump_collection(hdev);
	पूर्ण अन्यथा अगर (qca->memdump_state == QCA_MEMDUMP_COLLECTING) अणु
		/* Let us रुको here until memory dump collected or
		 * memory dump समयr expired.
		 */
		bt_dev_info(hdev, "waiting for dump to complete");
		qca_रुको_क्रम_dump_collection(hdev);
	पूर्ण

	mutex_lock(&qca->hci_memdump_lock);
	अगर (qca->memdump_state != QCA_MEMDUMP_COLLECTED) अणु
		bt_dev_err(hu->hdev, "clearing allocated memory due to memdump timeout");
		अगर (qca->qca_memdump) अणु
			vमुक्त(qca->qca_memdump->memdump_buf_head);
			kमुक्त(qca->qca_memdump);
			qca->qca_memdump = शून्य;
		पूर्ण
		qca->memdump_state = QCA_MEMDUMP_TIMEOUT;
		cancel_delayed_work(&qca->ctrl_memdump_समयout);
	पूर्ण
	mutex_unlock(&qca->hci_memdump_lock);

	अगर (qca->memdump_state == QCA_MEMDUMP_TIMEOUT ||
	    qca->memdump_state == QCA_MEMDUMP_COLLECTED) अणु
		cancel_work_sync(&qca->ctrl_memdump_evt);
		skb_queue_purge(&qca->rx_memdump_q);
	पूर्ण

	clear_bit(QCA_HW_ERROR_EVENT, &qca->flags);
पूर्ण

अटल व्योम qca_cmd_समयout(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);
	काष्ठा qca_data *qca = hu->priv;

	set_bit(QCA_SSR_TRIGGERED, &qca->flags);
	अगर (qca->memdump_state == QCA_MEMDUMP_IDLE) अणु
		set_bit(QCA_MEMDUMP_COLLECTION, &qca->flags);
		qca_send_crashbuffer(hu);
		qca_रुको_क्रम_dump_collection(hdev);
	पूर्ण अन्यथा अगर (qca->memdump_state == QCA_MEMDUMP_COLLECTING) अणु
		/* Let us रुको here until memory dump collected or
		 * memory dump समयr expired.
		 */
		bt_dev_info(hdev, "waiting for dump to complete");
		qca_रुको_क्रम_dump_collection(hdev);
	पूर्ण

	mutex_lock(&qca->hci_memdump_lock);
	अगर (qca->memdump_state != QCA_MEMDUMP_COLLECTED) अणु
		qca->memdump_state = QCA_MEMDUMP_TIMEOUT;
		अगर (!test_bit(QCA_HW_ERROR_EVENT, &qca->flags)) अणु
			/* Inject hw error event to reset the device
			 * and driver.
			 */
			hci_reset_dev(hu->hdev);
		पूर्ण
	पूर्ण
	mutex_unlock(&qca->hci_memdump_lock);
पूर्ण

अटल bool qca_prevent_wake(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);
	bool wakeup;

	/* UART driver handles the पूर्णांकerrupt from BT SoC.So we need to use
	 * device handle of UART driver to get the status of device may wakeup.
	 */
	wakeup = device_may_wakeup(hu->serdev->ctrl->dev.parent);
	bt_dev_dbg(hu->hdev, "wakeup status : %d", wakeup);

	वापस !wakeup;
पूर्ण

अटल पूर्णांक qca_wcn3990_init(काष्ठा hci_uart *hu)
अणु
	काष्ठा qca_serdev *qcadev;
	पूर्णांक ret;

	/* Check क्रम vregs status, may be hci करोwn has turned
	 * off the voltage regulator.
	 */
	qcadev = serdev_device_get_drvdata(hu->serdev);
	अगर (!qcadev->bt_घातer->vregs_on) अणु
		serdev_device_बंद(hu->serdev);
		ret = qca_regulator_enable(qcadev);
		अगर (ret)
			वापस ret;

		ret = serdev_device_खोलो(hu->serdev);
		अगर (ret) अणु
			bt_dev_err(hu->hdev, "failed to open port");
			वापस ret;
		पूर्ण
	पूर्ण

	/* Forcefully enable wcn3990 to enter in to boot mode. */
	host_set_baudrate(hu, 2400);
	ret = qca_send_घातer_pulse(hu, false);
	अगर (ret)
		वापस ret;

	qca_set_speed(hu, QCA_INIT_SPEED);
	ret = qca_send_घातer_pulse(hu, true);
	अगर (ret)
		वापस ret;

	/* Now the device is in पढ़ोy state to communicate with host.
	 * To sync host with device we need to reखोलो port.
	 * Without this, we will have RTS and CTS synchronization
	 * issues.
	 */
	serdev_device_बंद(hu->serdev);
	ret = serdev_device_खोलो(hu->serdev);
	अगर (ret) अणु
		bt_dev_err(hu->hdev, "failed to open port");
		वापस ret;
	पूर्ण

	hci_uart_set_flow_control(hu, false);

	वापस 0;
पूर्ण

अटल पूर्णांक qca_घातer_on(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);
	क्रमागत qca_btsoc_type soc_type = qca_soc_type(hu);
	काष्ठा qca_serdev *qcadev;
	काष्ठा qca_data *qca = hu->priv;
	पूर्णांक ret = 0;

	/* Non-serdev device usually is घातered by बाह्यal घातer
	 * and करोn't need additional action in driver क्रम घातer on
	 */
	अगर (!hu->serdev)
		वापस 0;

	अगर (qca_is_wcn399x(soc_type)) अणु
		ret = qca_wcn3990_init(hu);
	पूर्ण अन्यथा अणु
		qcadev = serdev_device_get_drvdata(hu->serdev);
		अगर (qcadev->bt_en) अणु
			gpiod_set_value_cansleep(qcadev->bt_en, 1);
			/* Controller needs समय to bootup. */
			msleep(150);
		पूर्ण
	पूर्ण

	clear_bit(QCA_BT_OFF, &qca->flags);
	वापस ret;
पूर्ण

अटल पूर्णांक qca_setup(काष्ठा hci_uart *hu)
अणु
	काष्ठा hci_dev *hdev = hu->hdev;
	काष्ठा qca_data *qca = hu->priv;
	अचिन्हित पूर्णांक speed, qca_baudrate = QCA_BAUDRATE_115200;
	अचिन्हित पूर्णांक retries = 0;
	क्रमागत qca_btsoc_type soc_type = qca_soc_type(hu);
	स्थिर अक्षर *firmware_name = qca_get_firmware_name(hu);
	पूर्णांक ret;
	काष्ठा qca_btsoc_version ver;

	ret = qca_check_speeds(hu);
	अगर (ret)
		वापस ret;

	clear_bit(QCA_ROM_FW, &qca->flags);
	/* Patch करोwnloading has to be करोne without IBS mode */
	set_bit(QCA_IBS_DISABLED, &qca->flags);

	/* Enable controller to करो both LE scan and BR/EDR inquiry
	 * simultaneously.
	 */
	set_bit(HCI_QUIRK_SIMULTANEOUS_DISCOVERY, &hdev->quirks);

	bt_dev_info(hdev, "setting up %s",
		qca_is_wcn399x(soc_type) ? "wcn399x" : "ROME/QCA6390");

	qca->memdump_state = QCA_MEMDUMP_IDLE;

retry:
	ret = qca_घातer_on(hdev);
	अगर (ret)
		जाओ out;

	clear_bit(QCA_SSR_TRIGGERED, &qca->flags);

	अगर (qca_is_wcn399x(soc_type)) अणु
		set_bit(HCI_QUIRK_USE_BDADDR_PROPERTY, &hdev->quirks);

		ret = qca_पढ़ो_soc_version(hdev, &ver, soc_type);
		अगर (ret)
			जाओ out;
	पूर्ण अन्यथा अणु
		qca_set_speed(hu, QCA_INIT_SPEED);
	पूर्ण

	/* Setup user speed अगर needed */
	speed = qca_get_speed(hu, QCA_OPER_SPEED);
	अगर (speed) अणु
		ret = qca_set_speed(hu, QCA_OPER_SPEED);
		अगर (ret)
			जाओ out;

		qca_baudrate = qca_get_baudrate_value(speed);
	पूर्ण

	अगर (!qca_is_wcn399x(soc_type)) अणु
		/* Get QCA version inक्रमmation */
		ret = qca_पढ़ो_soc_version(hdev, &ver, soc_type);
		अगर (ret)
			जाओ out;
	पूर्ण

	/* Setup patch / NVM configurations */
	ret = qca_uart_setup(hdev, qca_baudrate, soc_type, ver,
			firmware_name);
	अगर (!ret) अणु
		clear_bit(QCA_IBS_DISABLED, &qca->flags);
		qca_debugfs_init(hdev);
		hu->hdev->hw_error = qca_hw_error;
		hu->hdev->cmd_समयout = qca_cmd_समयout;
		hu->hdev->prevent_wake = qca_prevent_wake;
	पूर्ण अन्यथा अगर (ret == -ENOENT) अणु
		/* No patch/nvm-config found, run with original fw/config */
		set_bit(QCA_ROM_FW, &qca->flags);
		ret = 0;
	पूर्ण अन्यथा अगर (ret == -EAGAIN) अणु
		/*
		 * Userspace firmware loader will वापस -EAGAIN in हाल no
		 * patch/nvm-config is found, so run with original fw/config.
		 */
		set_bit(QCA_ROM_FW, &qca->flags);
		ret = 0;
	पूर्ण

out:
	अगर (ret && retries < MAX_INIT_RETRIES) अणु
		bt_dev_warn(hdev, "Retry BT power ON:%d", retries);
		qca_घातer_shutकरोwn(hu);
		अगर (hu->serdev) अणु
			serdev_device_बंद(hu->serdev);
			ret = serdev_device_खोलो(hu->serdev);
			अगर (ret) अणु
				bt_dev_err(hdev, "failed to open port");
				वापस ret;
			पूर्ण
		पूर्ण
		retries++;
		जाओ retry;
	पूर्ण

	/* Setup bdaddr */
	अगर (soc_type == QCA_ROME)
		hu->hdev->set_bdaddr = qca_set_bdaddr_rome;
	अन्यथा
		hu->hdev->set_bdaddr = qca_set_bdaddr;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hci_uart_proto qca_proto = अणु
	.id		= HCI_UART_QCA,
	.name		= "QCA",
	.manufacturer	= 29,
	.init_speed	= 115200,
	.oper_speed	= 3000000,
	.खोलो		= qca_खोलो,
	.बंद		= qca_बंद,
	.flush		= qca_flush,
	.setup		= qca_setup,
	.recv		= qca_recv,
	.enqueue	= qca_enqueue,
	.dequeue	= qca_dequeue,
पूर्ण;

अटल स्थिर काष्ठा qca_device_data qca_soc_data_wcn3990 = अणु
	.soc_type = QCA_WCN3990,
	.vregs = (काष्ठा qca_vreg []) अणु
		अणु "vddio", 15000  पूर्ण,
		अणु "vddxo", 80000  पूर्ण,
		अणु "vddrf", 300000 पूर्ण,
		अणु "vddch0", 450000 पूर्ण,
	पूर्ण,
	.num_vregs = 4,
पूर्ण;

अटल स्थिर काष्ठा qca_device_data qca_soc_data_wcn3991 = अणु
	.soc_type = QCA_WCN3991,
	.vregs = (काष्ठा qca_vreg []) अणु
		अणु "vddio", 15000  पूर्ण,
		अणु "vddxo", 80000  पूर्ण,
		अणु "vddrf", 300000 पूर्ण,
		अणु "vddch0", 450000 पूर्ण,
	पूर्ण,
	.num_vregs = 4,
	.capabilities = QCA_CAP_WIDEBAND_SPEECH | QCA_CAP_VALID_LE_STATES,
पूर्ण;

अटल स्थिर काष्ठा qca_device_data qca_soc_data_wcn3998 = अणु
	.soc_type = QCA_WCN3998,
	.vregs = (काष्ठा qca_vreg []) अणु
		अणु "vddio", 10000  पूर्ण,
		अणु "vddxo", 80000  पूर्ण,
		अणु "vddrf", 300000 पूर्ण,
		अणु "vddch0", 450000 पूर्ण,
	पूर्ण,
	.num_vregs = 4,
पूर्ण;

अटल स्थिर काष्ठा qca_device_data qca_soc_data_qca6390 = अणु
	.soc_type = QCA_QCA6390,
	.num_vregs = 0,
पूर्ण;

अटल व्योम qca_घातer_shutकरोwn(काष्ठा hci_uart *hu)
अणु
	काष्ठा qca_serdev *qcadev;
	काष्ठा qca_data *qca = hu->priv;
	अचिन्हित दीर्घ flags;
	क्रमागत qca_btsoc_type soc_type = qca_soc_type(hu);

	qcadev = serdev_device_get_drvdata(hu->serdev);

	/* From this poपूर्णांक we go पूर्णांकo घातer off state. But serial port is
	 * still खोलो, stop queueing the IBS data and flush all the buffered
	 * data in skb's.
	 */
	spin_lock_irqsave(&qca->hci_ibs_lock, flags);
	set_bit(QCA_IBS_DISABLED, &qca->flags);
	qca_flush(hu);
	spin_unlock_irqrestore(&qca->hci_ibs_lock, flags);

	/* Non-serdev device usually is घातered by बाह्यal घातer
	 * and करोn't need additional action in driver क्रम घातer करोwn
	 */
	अगर (!hu->serdev)
		वापस;

	अगर (qca_is_wcn399x(soc_type)) अणु
		host_set_baudrate(hu, 2400);
		qca_send_घातer_pulse(hu, false);
		qca_regulator_disable(qcadev);
	पूर्ण अन्यथा अगर (qcadev->bt_en) अणु
		gpiod_set_value_cansleep(qcadev->bt_en, 0);
	पूर्ण

	set_bit(QCA_BT_OFF, &qca->flags);
पूर्ण

अटल पूर्णांक qca_घातer_off(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);
	काष्ठा qca_data *qca = hu->priv;
	क्रमागत qca_btsoc_type soc_type = qca_soc_type(hu);

	hu->hdev->hw_error = शून्य;
	hu->hdev->cmd_समयout = शून्य;

	/* Stop sending shutकरोwn command अगर soc crashes. */
	अगर (soc_type != QCA_ROME
		&& qca->memdump_state == QCA_MEMDUMP_IDLE) अणु
		qca_send_pre_shutकरोwn_cmd(hdev);
		usleep_range(8000, 10000);
	पूर्ण

	qca_घातer_shutकरोwn(hu);
	वापस 0;
पूर्ण

अटल पूर्णांक qca_regulator_enable(काष्ठा qca_serdev *qcadev)
अणु
	काष्ठा qca_घातer *घातer = qcadev->bt_घातer;
	पूर्णांक ret;

	/* Alपढ़ोy enabled */
	अगर (घातer->vregs_on)
		वापस 0;

	BT_DBG("enabling %d regulators)", घातer->num_vregs);

	ret = regulator_bulk_enable(घातer->num_vregs, घातer->vreg_bulk);
	अगर (ret)
		वापस ret;

	घातer->vregs_on = true;

	ret = clk_prepare_enable(qcadev->susclk);
	अगर (ret)
		qca_regulator_disable(qcadev);

	वापस ret;
पूर्ण

अटल व्योम qca_regulator_disable(काष्ठा qca_serdev *qcadev)
अणु
	काष्ठा qca_घातer *घातer;

	अगर (!qcadev)
		वापस;

	घातer = qcadev->bt_घातer;

	/* Alपढ़ोy disabled? */
	अगर (!घातer->vregs_on)
		वापस;

	regulator_bulk_disable(घातer->num_vregs, घातer->vreg_bulk);
	घातer->vregs_on = false;

	clk_disable_unprepare(qcadev->susclk);
पूर्ण

अटल पूर्णांक qca_init_regulators(काष्ठा qca_घातer *qca,
				स्थिर काष्ठा qca_vreg *vregs, माप_प्रकार num_vregs)
अणु
	काष्ठा regulator_bulk_data *bulk;
	पूर्णांक ret;
	पूर्णांक i;

	bulk = devm_kसुस्मृति(qca->dev, num_vregs, माप(*bulk), GFP_KERNEL);
	अगर (!bulk)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_vregs; i++)
		bulk[i].supply = vregs[i].name;

	ret = devm_regulator_bulk_get(qca->dev, num_vregs, bulk);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < num_vregs; i++) अणु
		ret = regulator_set_load(bulk[i].consumer, vregs[i].load_uA);
		अगर (ret)
			वापस ret;
	पूर्ण

	qca->vreg_bulk = bulk;
	qca->num_vregs = num_vregs;

	वापस 0;
पूर्ण

अटल पूर्णांक qca_serdev_probe(काष्ठा serdev_device *serdev)
अणु
	काष्ठा qca_serdev *qcadev;
	काष्ठा hci_dev *hdev;
	स्थिर काष्ठा qca_device_data *data;
	पूर्णांक err;
	bool घातer_ctrl_enabled = true;

	qcadev = devm_kzalloc(&serdev->dev, माप(*qcadev), GFP_KERNEL);
	अगर (!qcadev)
		वापस -ENOMEM;

	qcadev->serdev_hu.serdev = serdev;
	data = device_get_match_data(&serdev->dev);
	serdev_device_set_drvdata(serdev, qcadev);
	device_property_पढ़ो_string(&serdev->dev, "firmware-name",
					 &qcadev->firmware_name);
	device_property_पढ़ो_u32(&serdev->dev, "max-speed",
				 &qcadev->oper_speed);
	अगर (!qcadev->oper_speed)
		BT_DBG("UART will pick default operating speed");

	अगर (data && qca_is_wcn399x(data->soc_type)) अणु
		qcadev->btsoc_type = data->soc_type;
		qcadev->bt_घातer = devm_kzalloc(&serdev->dev,
						माप(काष्ठा qca_घातer),
						GFP_KERNEL);
		अगर (!qcadev->bt_घातer)
			वापस -ENOMEM;

		qcadev->bt_घातer->dev = &serdev->dev;
		err = qca_init_regulators(qcadev->bt_घातer, data->vregs,
					  data->num_vregs);
		अगर (err) अणु
			BT_ERR("Failed to init regulators:%d", err);
			वापस err;
		पूर्ण

		qcadev->bt_घातer->vregs_on = false;

		qcadev->susclk = devm_clk_get_optional(&serdev->dev, शून्य);
		अगर (IS_ERR(qcadev->susclk)) अणु
			dev_err(&serdev->dev, "failed to acquire clk\n");
			वापस PTR_ERR(qcadev->susclk);
		पूर्ण

		err = hci_uart_रेजिस्टर_device(&qcadev->serdev_hu, &qca_proto);
		अगर (err) अणु
			BT_ERR("wcn3990 serdev registration failed");
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (data)
			qcadev->btsoc_type = data->soc_type;
		अन्यथा
			qcadev->btsoc_type = QCA_ROME;

		qcadev->bt_en = devm_gpiod_get_optional(&serdev->dev, "enable",
					       GPIOD_OUT_LOW);
		अगर (!qcadev->bt_en) अणु
			dev_warn(&serdev->dev, "failed to acquire enable gpio\n");
			घातer_ctrl_enabled = false;
		पूर्ण

		qcadev->susclk = devm_clk_get_optional(&serdev->dev, शून्य);
		अगर (IS_ERR(qcadev->susclk)) अणु
			dev_warn(&serdev->dev, "failed to acquire clk\n");
			वापस PTR_ERR(qcadev->susclk);
		पूर्ण
		err = clk_set_rate(qcadev->susclk, SUSCLK_RATE_32KHZ);
		अगर (err)
			वापस err;

		err = clk_prepare_enable(qcadev->susclk);
		अगर (err)
			वापस err;

		err = hci_uart_रेजिस्टर_device(&qcadev->serdev_hu, &qca_proto);
		अगर (err) अणु
			BT_ERR("Rome serdev registration failed");
			clk_disable_unprepare(qcadev->susclk);
			वापस err;
		पूर्ण
	पूर्ण

	hdev = qcadev->serdev_hu.hdev;

	अगर (घातer_ctrl_enabled) अणु
		set_bit(HCI_QUIRK_NON_PERSISTENT_SETUP, &hdev->quirks);
		hdev->shutकरोwn = qca_घातer_off;
	पूर्ण

	अगर (data) अणु
		/* Wideband speech support must be set per driver since it can't
		 * be queried via hci. Same with the valid le states quirk.
		 */
		अगर (data->capabilities & QCA_CAP_WIDEBAND_SPEECH)
			set_bit(HCI_QUIRK_WIDEBAND_SPEECH_SUPPORTED,
				&hdev->quirks);

		अगर (data->capabilities & QCA_CAP_VALID_LE_STATES)
			set_bit(HCI_QUIRK_VALID_LE_STATES, &hdev->quirks);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qca_serdev_हटाओ(काष्ठा serdev_device *serdev)
अणु
	काष्ठा qca_serdev *qcadev = serdev_device_get_drvdata(serdev);
	काष्ठा qca_घातer *घातer = qcadev->bt_घातer;

	अगर (qca_is_wcn399x(qcadev->btsoc_type) && घातer->vregs_on)
		qca_घातer_shutकरोwn(&qcadev->serdev_hu);
	अन्यथा अगर (qcadev->susclk)
		clk_disable_unprepare(qcadev->susclk);

	hci_uart_unरेजिस्टर_device(&qcadev->serdev_hu);
पूर्ण

अटल व्योम qca_serdev_shutकरोwn(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	पूर्णांक समयout = msecs_to_jअगरfies(CMD_TRANS_TIMEOUT_MS);
	काष्ठा serdev_device *serdev = to_serdev_device(dev);
	काष्ठा qca_serdev *qcadev = serdev_device_get_drvdata(serdev);
	स्थिर u8 ibs_wake_cmd[] = अणु 0xFD पूर्ण;
	स्थिर u8 edl_reset_soc_cmd[] = अणु 0x01, 0x00, 0xFC, 0x01, 0x05 पूर्ण;

	अगर (qcadev->btsoc_type == QCA_QCA6390) अणु
		serdev_device_ग_लिखो_flush(serdev);
		ret = serdev_device_ग_लिखो_buf(serdev, ibs_wake_cmd,
					      माप(ibs_wake_cmd));
		अगर (ret < 0) अणु
			BT_ERR("QCA send IBS_WAKE_IND error: %d", ret);
			वापस;
		पूर्ण
		serdev_device_रुको_until_sent(serdev, समयout);
		usleep_range(8000, 10000);

		serdev_device_ग_लिखो_flush(serdev);
		ret = serdev_device_ग_लिखो_buf(serdev, edl_reset_soc_cmd,
					      माप(edl_reset_soc_cmd));
		अगर (ret < 0) अणु
			BT_ERR("QCA send EDL_RESET_REQ error: %d", ret);
			वापस;
		पूर्ण
		serdev_device_रुको_until_sent(serdev, समयout);
		usleep_range(8000, 10000);
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused qca_suspend(काष्ठा device *dev)
अणु
	काष्ठा serdev_device *serdev = to_serdev_device(dev);
	काष्ठा qca_serdev *qcadev = serdev_device_get_drvdata(serdev);
	काष्ठा hci_uart *hu = &qcadev->serdev_hu;
	काष्ठा qca_data *qca = hu->priv;
	अचिन्हित दीर्घ flags;
	bool tx_pending = false;
	पूर्णांक ret = 0;
	u8 cmd;
	u32 रुको_समयout = 0;

	set_bit(QCA_SUSPENDING, &qca->flags);

	/* अगर BT SoC is running with शेष firmware then it करोes not
	 * support in-band sleep
	 */
	अगर (test_bit(QCA_ROM_FW, &qca->flags))
		वापस 0;

	/* During SSR after memory dump collection, controller will be
	 * घातered off and then घातered on.If controller is घातered off
	 * during SSR then we should रुको until SSR is completed.
	 */
	अगर (test_bit(QCA_BT_OFF, &qca->flags) &&
	    !test_bit(QCA_SSR_TRIGGERED, &qca->flags))
		वापस 0;

	अगर (test_bit(QCA_IBS_DISABLED, &qca->flags) ||
	    test_bit(QCA_SSR_TRIGGERED, &qca->flags)) अणु
		रुको_समयout = test_bit(QCA_SSR_TRIGGERED, &qca->flags) ?
					IBS_DISABLE_SSR_TIMEOUT_MS :
					FW_DOWNLOAD_TIMEOUT_MS;

		/* QCA_IBS_DISABLED flag is set to true, During FW करोwnload
		 * and during memory dump collection. It is reset to false,
		 * After FW करोwnload complete.
		 */
		रुको_on_bit_समयout(&qca->flags, QCA_IBS_DISABLED,
			    TASK_UNINTERRUPTIBLE, msecs_to_jअगरfies(रुको_समयout));

		अगर (test_bit(QCA_IBS_DISABLED, &qca->flags)) अणु
			bt_dev_err(hu->hdev, "SSR or FW download time out");
			ret = -ETIMEDOUT;
			जाओ error;
		पूर्ण
	पूर्ण

	cancel_work_sync(&qca->ws_awake_device);
	cancel_work_sync(&qca->ws_awake_rx);

	spin_lock_irqsave_nested(&qca->hci_ibs_lock,
				 flags, SINGLE_DEPTH_NESTING);

	चयन (qca->tx_ibs_state) अणु
	हाल HCI_IBS_TX_WAKING:
		del_समयr(&qca->wake_retrans_समयr);
		fallthrough;
	हाल HCI_IBS_TX_AWAKE:
		del_समयr(&qca->tx_idle_समयr);

		serdev_device_ग_लिखो_flush(hu->serdev);
		cmd = HCI_IBS_SLEEP_IND;
		ret = serdev_device_ग_लिखो_buf(hu->serdev, &cmd, माप(cmd));

		अगर (ret < 0) अणु
			BT_ERR("Failed to send SLEEP to device");
			अवरोध;
		पूर्ण

		qca->tx_ibs_state = HCI_IBS_TX_ASLEEP;
		qca->ibs_sent_slps++;
		tx_pending = true;
		अवरोध;

	हाल HCI_IBS_TX_ASLEEP:
		अवरोध;

	शेष:
		BT_ERR("Spurious tx state %d", qca->tx_ibs_state);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&qca->hci_ibs_lock, flags);

	अगर (ret < 0)
		जाओ error;

	अगर (tx_pending) अणु
		serdev_device_रुको_until_sent(hu->serdev,
					      msecs_to_jअगरfies(CMD_TRANS_TIMEOUT_MS));
		serial_घड़ी_vote(HCI_IBS_TX_VOTE_CLOCK_OFF, hu);
	पूर्ण

	/* Wait क्रम HCI_IBS_SLEEP_IND sent by device to indicate its Tx is going
	 * to sleep, so that the packet करोes not wake the प्रणाली later.
	 */
	ret = रुको_event_पूर्णांकerruptible_समयout(qca->suspend_रुको_q,
			qca->rx_ibs_state == HCI_IBS_RX_ASLEEP,
			msecs_to_jअगरfies(IBS_BTSOC_TX_IDLE_TIMEOUT_MS));
	अगर (ret == 0) अणु
		ret = -ETIMEDOUT;
		जाओ error;
	पूर्ण

	वापस 0;

error:
	clear_bit(QCA_SUSPENDING, &qca->flags);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused qca_resume(काष्ठा device *dev)
अणु
	काष्ठा serdev_device *serdev = to_serdev_device(dev);
	काष्ठा qca_serdev *qcadev = serdev_device_get_drvdata(serdev);
	काष्ठा hci_uart *hu = &qcadev->serdev_hu;
	काष्ठा qca_data *qca = hu->priv;

	clear_bit(QCA_SUSPENDING, &qca->flags);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(qca_pm_ops, qca_suspend, qca_resume);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id qca_bluetooth_of_match[] = अणु
	अणु .compatible = "qcom,qca6174-bt" पूर्ण,
	अणु .compatible = "qcom,qca6390-bt", .data = &qca_soc_data_qca6390पूर्ण,
	अणु .compatible = "qcom,qca9377-bt" पूर्ण,
	अणु .compatible = "qcom,wcn3990-bt", .data = &qca_soc_data_wcn3990पूर्ण,
	अणु .compatible = "qcom,wcn3991-bt", .data = &qca_soc_data_wcn3991पूर्ण,
	अणु .compatible = "qcom,wcn3998-bt", .data = &qca_soc_data_wcn3998पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qca_bluetooth_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id qca_bluetooth_acpi_match[] = अणु
	अणु "QCOM6390", (kernel_uदीर्घ_t)&qca_soc_data_qca6390 पूर्ण,
	अणु "DLA16390", (kernel_uदीर्घ_t)&qca_soc_data_qca6390 पूर्ण,
	अणु "DLB16390", (kernel_uदीर्घ_t)&qca_soc_data_qca6390 पूर्ण,
	अणु "DLB26390", (kernel_uदीर्घ_t)&qca_soc_data_qca6390 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, qca_bluetooth_acpi_match);
#पूर्ण_अगर


अटल काष्ठा serdev_device_driver qca_serdev_driver = अणु
	.probe = qca_serdev_probe,
	.हटाओ = qca_serdev_हटाओ,
	.driver = अणु
		.name = "hci_uart_qca",
		.of_match_table = of_match_ptr(qca_bluetooth_of_match),
		.acpi_match_table = ACPI_PTR(qca_bluetooth_acpi_match),
		.shutकरोwn = qca_serdev_shutकरोwn,
		.pm = &qca_pm_ops,
	पूर्ण,
पूर्ण;

पूर्णांक __init qca_init(व्योम)
अणु
	serdev_device_driver_रेजिस्टर(&qca_serdev_driver);

	वापस hci_uart_रेजिस्टर_proto(&qca_proto);
पूर्ण

पूर्णांक __निकास qca_deinit(व्योम)
अणु
	serdev_device_driver_unरेजिस्टर(&qca_serdev_driver);

	वापस hci_uart_unरेजिस्टर_proto(&qca_proto);
पूर्ण
