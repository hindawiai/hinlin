<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Texas Instruments' Bluetooth HCILL UART protocol
 *
 *  HCILL (HCI Low Level) is a Texas Instruments' घातer management
 *  protocol extension to H4.
 *
 *  Copyright (C) 2007 Texas Instruments, Inc.
 *
 *  Written by Ohad Ben-Cohen <ohad@bencohen.org>
 *
 *  Acknowledgements:
 *  This file is based on hci_h4.c, which was written
 *  by Maxim Krasnyansky and Marcel Holपंचांगann.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>

#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/poll.h>

#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/ioctl.h>
#समावेश <linux/of.h>
#समावेश <linux/serdev.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ti_wilink_st.h>
#समावेश <linux/clk.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/nvmem-consumer.h>

#समावेश "hci_uart.h"

/* Venकरोr-specअगरic HCI commands */
#घोषणा HCI_VS_WRITE_BD_ADDR			0xfc06
#घोषणा HCI_VS_UPDATE_UART_HCI_BAUDRATE		0xff36

/* HCILL commands */
#घोषणा HCILL_GO_TO_SLEEP_IND	0x30
#घोषणा HCILL_GO_TO_SLEEP_ACK	0x31
#घोषणा HCILL_WAKE_UP_IND	0x32
#घोषणा HCILL_WAKE_UP_ACK	0x33

/* HCILL states */
क्रमागत hcill_states_e अणु
	HCILL_ASLEEP,
	HCILL_ASLEEP_TO_AWAKE,
	HCILL_AWAKE,
	HCILL_AWAKE_TO_ASLEEP
पूर्ण;

काष्ठा ll_device अणु
	काष्ठा hci_uart hu;
	काष्ठा serdev_device *serdev;
	काष्ठा gpio_desc *enable_gpio;
	काष्ठा clk *ext_clk;
	bdaddr_t bdaddr;
पूर्ण;

काष्ठा ll_काष्ठा अणु
	काष्ठा sk_buff *rx_skb;
	काष्ठा sk_buff_head txq;
	spinlock_t hcill_lock;		/* HCILL state lock	*/
	अचिन्हित दीर्घ hcill_state;	/* HCILL घातer state	*/
	काष्ठा sk_buff_head tx_रुको_q;	/* HCILL रुको queue	*/
पूर्ण;

/*
 * Builds and sends an HCILL command packet.
 * These are very simple packets with only 1 cmd byte
 */
अटल पूर्णांक send_hcill_cmd(u8 cmd, काष्ठा hci_uart *hu)
अणु
	पूर्णांक err = 0;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा ll_काष्ठा *ll = hu->priv;

	BT_DBG("hu %p cmd 0x%x", hu, cmd);

	/* allocate packet */
	skb = bt_skb_alloc(1, GFP_ATOMIC);
	अगर (!skb) अणु
		BT_ERR("cannot allocate memory for HCILL packet");
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	/* prepare packet */
	skb_put_u8(skb, cmd);

	/* send packet */
	skb_queue_tail(&ll->txq, skb);
out:
	वापस err;
पूर्ण

/* Initialize protocol */
अटल पूर्णांक ll_खोलो(काष्ठा hci_uart *hu)
अणु
	काष्ठा ll_काष्ठा *ll;

	BT_DBG("hu %p", hu);

	ll = kzalloc(माप(*ll), GFP_KERNEL);
	अगर (!ll)
		वापस -ENOMEM;

	skb_queue_head_init(&ll->txq);
	skb_queue_head_init(&ll->tx_रुको_q);
	spin_lock_init(&ll->hcill_lock);

	ll->hcill_state = HCILL_AWAKE;

	hu->priv = ll;

	अगर (hu->serdev) अणु
		काष्ठा ll_device *lldev = serdev_device_get_drvdata(hu->serdev);

		अगर (!IS_ERR(lldev->ext_clk))
			clk_prepare_enable(lldev->ext_clk);
	पूर्ण

	वापस 0;
पूर्ण

/* Flush protocol data */
अटल पूर्णांक ll_flush(काष्ठा hci_uart *hu)
अणु
	काष्ठा ll_काष्ठा *ll = hu->priv;

	BT_DBG("hu %p", hu);

	skb_queue_purge(&ll->tx_रुको_q);
	skb_queue_purge(&ll->txq);

	वापस 0;
पूर्ण

/* Close protocol */
अटल पूर्णांक ll_बंद(काष्ठा hci_uart *hu)
अणु
	काष्ठा ll_काष्ठा *ll = hu->priv;

	BT_DBG("hu %p", hu);

	skb_queue_purge(&ll->tx_रुको_q);
	skb_queue_purge(&ll->txq);

	kमुक्त_skb(ll->rx_skb);

	अगर (hu->serdev) अणु
		काष्ठा ll_device *lldev = serdev_device_get_drvdata(hu->serdev);

		gpiod_set_value_cansleep(lldev->enable_gpio, 0);

		clk_disable_unprepare(lldev->ext_clk);
	पूर्ण

	hu->priv = शून्य;

	kमुक्त(ll);

	वापस 0;
पूर्ण

/*
 * पूर्णांकernal function, which करोes common work of the device wake up process:
 * 1. places all pending packets (रुकोing in tx_रुको_q list) in txq list.
 * 2. changes पूर्णांकernal state to HCILL_AWAKE.
 * Note: assumes that hcill_lock spinlock is taken,
 * shouldn't be called otherwise!
 */
अटल व्योम __ll_करो_awake(काष्ठा ll_काष्ठा *ll)
अणु
	काष्ठा sk_buff *skb = शून्य;

	जबतक ((skb = skb_dequeue(&ll->tx_रुको_q)))
		skb_queue_tail(&ll->txq, skb);

	ll->hcill_state = HCILL_AWAKE;
पूर्ण

/*
 * Called upon a wake-up-indication from the device
 */
अटल व्योम ll_device_want_to_wakeup(काष्ठा hci_uart *hu)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ll_काष्ठा *ll = hu->priv;

	BT_DBG("hu %p", hu);

	/* lock hcill state */
	spin_lock_irqsave(&ll->hcill_lock, flags);

	चयन (ll->hcill_state) अणु
	हाल HCILL_ASLEEP_TO_AWAKE:
		/*
		 * This state means that both the host and the BRF chip
		 * have simultaneously sent a wake-up-indication packet.
		 * Traditionally, in this हाल, receiving a wake-up-indication
		 * was enough and an additional wake-up-ack wasn't needed.
		 * This has changed with the BRF6350, which करोes require an
		 * explicit wake-up-ack. Other BRF versions, which करो not
		 * require an explicit ack here, करो accept it, thus it is
		 * perfectly safe to always send one.
		 */
		BT_DBG("dual wake-up-indication");
		fallthrough;
	हाल HCILL_ASLEEP:
		/* acknowledge device wake up */
		अगर (send_hcill_cmd(HCILL_WAKE_UP_ACK, hu) < 0) अणु
			BT_ERR("cannot acknowledge device wake up");
			जाओ out;
		पूर्ण
		अवरोध;
	शेष:
		/* any other state is illegal */
		BT_ERR("received HCILL_WAKE_UP_IND in state %ld",
		       ll->hcill_state);
		अवरोध;
	पूर्ण

	/* send pending packets and change state to HCILL_AWAKE */
	__ll_करो_awake(ll);

out:
	spin_unlock_irqrestore(&ll->hcill_lock, flags);

	/* actually send the packets */
	hci_uart_tx_wakeup(hu);
पूर्ण

/*
 * Called upon a sleep-indication from the device
 */
अटल व्योम ll_device_want_to_sleep(काष्ठा hci_uart *hu)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ll_काष्ठा *ll = hu->priv;

	BT_DBG("hu %p", hu);

	/* lock hcill state */
	spin_lock_irqsave(&ll->hcill_lock, flags);

	/* sanity check */
	अगर (ll->hcill_state != HCILL_AWAKE)
		BT_ERR("ERR: HCILL_GO_TO_SLEEP_IND in state %ld",
		       ll->hcill_state);

	/* acknowledge device sleep */
	अगर (send_hcill_cmd(HCILL_GO_TO_SLEEP_ACK, hu) < 0) अणु
		BT_ERR("cannot acknowledge device sleep");
		जाओ out;
	पूर्ण

	/* update state */
	ll->hcill_state = HCILL_ASLEEP;

out:
	spin_unlock_irqrestore(&ll->hcill_lock, flags);

	/* actually send the sleep ack packet */
	hci_uart_tx_wakeup(hu);
पूर्ण

/*
 * Called upon wake-up-acknowledgement from the device
 */
अटल व्योम ll_device_woke_up(काष्ठा hci_uart *hu)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ll_काष्ठा *ll = hu->priv;

	BT_DBG("hu %p", hu);

	/* lock hcill state */
	spin_lock_irqsave(&ll->hcill_lock, flags);

	/* sanity check */
	अगर (ll->hcill_state != HCILL_ASLEEP_TO_AWAKE)
		BT_ERR("received HCILL_WAKE_UP_ACK in state %ld",
		       ll->hcill_state);

	/* send pending packets and change state to HCILL_AWAKE */
	__ll_करो_awake(ll);

	spin_unlock_irqrestore(&ll->hcill_lock, flags);

	/* actually send the packets */
	hci_uart_tx_wakeup(hu);
पूर्ण

/* Enqueue frame क्रम transmittion (padding, crc, etc) */
/* may be called from two simultaneous tasklets */
अटल पूर्णांक ll_enqueue(काष्ठा hci_uart *hu, काष्ठा sk_buff *skb)
अणु
	अचिन्हित दीर्घ flags = 0;
	काष्ठा ll_काष्ठा *ll = hu->priv;

	BT_DBG("hu %p skb %p", hu, skb);

	/* Prepend skb with frame type */
	स_नकल(skb_push(skb, 1), &hci_skb_pkt_type(skb), 1);

	/* lock hcill state */
	spin_lock_irqsave(&ll->hcill_lock, flags);

	/* act according to current state */
	चयन (ll->hcill_state) अणु
	हाल HCILL_AWAKE:
		BT_DBG("device awake, sending normally");
		skb_queue_tail(&ll->txq, skb);
		अवरोध;
	हाल HCILL_ASLEEP:
		BT_DBG("device asleep, waking up and queueing packet");
		/* save packet क्रम later */
		skb_queue_tail(&ll->tx_रुको_q, skb);
		/* awake device */
		अगर (send_hcill_cmd(HCILL_WAKE_UP_IND, hu) < 0) अणु
			BT_ERR("cannot wake up device");
			अवरोध;
		पूर्ण
		ll->hcill_state = HCILL_ASLEEP_TO_AWAKE;
		अवरोध;
	हाल HCILL_ASLEEP_TO_AWAKE:
		BT_DBG("device waking up, queueing packet");
		/* transient state; just keep packet क्रम later */
		skb_queue_tail(&ll->tx_रुको_q, skb);
		अवरोध;
	शेष:
		BT_ERR("illegal hcill state: %ld (losing packet)",
		       ll->hcill_state);
		kमुक्त_skb(skb);
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&ll->hcill_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ll_recv_frame(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);
	काष्ठा ll_काष्ठा *ll = hu->priv;

	चयन (hci_skb_pkt_type(skb)) अणु
	हाल HCILL_GO_TO_SLEEP_IND:
		BT_DBG("HCILL_GO_TO_SLEEP_IND packet");
		ll_device_want_to_sleep(hu);
		अवरोध;
	हाल HCILL_GO_TO_SLEEP_ACK:
		/* shouldn't happen */
		bt_dev_err(hdev, "received HCILL_GO_TO_SLEEP_ACK in state %ld",
			   ll->hcill_state);
		अवरोध;
	हाल HCILL_WAKE_UP_IND:
		BT_DBG("HCILL_WAKE_UP_IND packet");
		ll_device_want_to_wakeup(hu);
		अवरोध;
	हाल HCILL_WAKE_UP_ACK:
		BT_DBG("HCILL_WAKE_UP_ACK packet");
		ll_device_woke_up(hu);
		अवरोध;
	पूर्ण

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

#घोषणा LL_RECV_SLEEP_IND \
	.type = HCILL_GO_TO_SLEEP_IND, \
	.hlen = 0, \
	.loff = 0, \
	.lsize = 0, \
	.maxlen = 0

#घोषणा LL_RECV_SLEEP_ACK \
	.type = HCILL_GO_TO_SLEEP_ACK, \
	.hlen = 0, \
	.loff = 0, \
	.lsize = 0, \
	.maxlen = 0

#घोषणा LL_RECV_WAKE_IND \
	.type = HCILL_WAKE_UP_IND, \
	.hlen = 0, \
	.loff = 0, \
	.lsize = 0, \
	.maxlen = 0

#घोषणा LL_RECV_WAKE_ACK \
	.type = HCILL_WAKE_UP_ACK, \
	.hlen = 0, \
	.loff = 0, \
	.lsize = 0, \
	.maxlen = 0

अटल स्थिर काष्ठा h4_recv_pkt ll_recv_pkts[] = अणु
	अणु H4_RECV_ACL,       .recv = hci_recv_frame पूर्ण,
	अणु H4_RECV_SCO,       .recv = hci_recv_frame पूर्ण,
	अणु H4_RECV_EVENT,     .recv = hci_recv_frame पूर्ण,
	अणु LL_RECV_SLEEP_IND, .recv = ll_recv_frame  पूर्ण,
	अणु LL_RECV_SLEEP_ACK, .recv = ll_recv_frame  पूर्ण,
	अणु LL_RECV_WAKE_IND,  .recv = ll_recv_frame  पूर्ण,
	अणु LL_RECV_WAKE_ACK,  .recv = ll_recv_frame  पूर्ण,
पूर्ण;

/* Recv data */
अटल पूर्णांक ll_recv(काष्ठा hci_uart *hu, स्थिर व्योम *data, पूर्णांक count)
अणु
	काष्ठा ll_काष्ठा *ll = hu->priv;

	अगर (!test_bit(HCI_UART_REGISTERED, &hu->flags))
		वापस -EUNATCH;

	ll->rx_skb = h4_recv_buf(hu->hdev, ll->rx_skb, data, count,
				 ll_recv_pkts, ARRAY_SIZE(ll_recv_pkts));
	अगर (IS_ERR(ll->rx_skb)) अणु
		पूर्णांक err = PTR_ERR(ll->rx_skb);
		bt_dev_err(hu->hdev, "Frame reassembly failed (%d)", err);
		ll->rx_skb = शून्य;
		वापस err;
	पूर्ण

	वापस count;
पूर्ण

अटल काष्ठा sk_buff *ll_dequeue(काष्ठा hci_uart *hu)
अणु
	काष्ठा ll_काष्ठा *ll = hu->priv;

	वापस skb_dequeue(&ll->txq);
पूर्ण

#अगर IS_ENABLED(CONFIG_SERIAL_DEV_BUS)
अटल पूर्णांक पढ़ो_local_version(काष्ठा hci_dev *hdev)
अणु
	पूर्णांक err = 0;
	अचिन्हित लघु version = 0;
	काष्ठा sk_buff *skb;
	काष्ठा hci_rp_पढ़ो_local_version *ver;

	skb = __hci_cmd_sync(hdev, HCI_OP_READ_LOCAL_VERSION, 0, शून्य,
			     HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "Reading TI version information failed (%ld)",
			   PTR_ERR(skb));
		वापस PTR_ERR(skb);
	पूर्ण
	अगर (skb->len != माप(*ver)) अणु
		err = -EILSEQ;
		जाओ out;
	पूर्ण

	ver = (काष्ठा hci_rp_पढ़ो_local_version *)skb->data;
	अगर (le16_to_cpu(ver->manufacturer) != 13) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	version = le16_to_cpu(ver->lmp_subver);

out:
	अगर (err)
		bt_dev_err(hdev, "Failed to read TI version info: %d", err);
	kमुक्त_skb(skb);
	वापस err ? err : version;
पूर्ण

अटल पूर्णांक send_command_from_firmware(काष्ठा ll_device *lldev,
				      काष्ठा hci_command *cmd)
अणु
	काष्ठा sk_buff *skb;

	अगर (cmd->opcode == HCI_VS_UPDATE_UART_HCI_BAUDRATE) अणु
		/* ignore remote change
		 * baud rate HCI VS command
		 */
		bt_dev_warn(lldev->hu.hdev,
			    "change remote baud rate command in firmware");
		वापस 0;
	पूर्ण
	अगर (cmd->prefix != 1)
		bt_dev_dbg(lldev->hu.hdev, "command type %d", cmd->prefix);

	skb = __hci_cmd_sync(lldev->hu.hdev, cmd->opcode, cmd->plen,
			     &cmd->speed, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(lldev->hu.hdev, "send command failed");
		वापस PTR_ERR(skb);
	पूर्ण
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

/**
 * करोwnload_firmware -
 *	पूर्णांकernal function which parses through the .bts firmware
 *	script file पूर्णांकreprets SEND, DELAY actions only as of now
 */
अटल पूर्णांक करोwnload_firmware(काष्ठा ll_device *lldev)
अणु
	अचिन्हित लघु chip, min_ver, maj_ver;
	पूर्णांक version, err, len;
	अचिन्हित अक्षर *ptr, *action_ptr;
	अचिन्हित अक्षर bts_scr_name[40];	/* 40 अक्षर दीर्घ bts scr name? */
	स्थिर काष्ठा firmware *fw;
	काष्ठा hci_command *cmd;

	version = पढ़ो_local_version(lldev->hu.hdev);
	अगर (version < 0)
		वापस version;

	chip = (version & 0x7C00) >> 10;
	min_ver = (version & 0x007F);
	maj_ver = (version & 0x0380) >> 7;
	अगर (version & 0x8000)
		maj_ver |= 0x0008;

	snम_लिखो(bts_scr_name, माप(bts_scr_name),
		 "ti-connectivity/TIInit_%d.%d.%d.bts",
		 chip, maj_ver, min_ver);

	err = request_firmware(&fw, bts_scr_name, &lldev->serdev->dev);
	अगर (err || !fw->data || !fw->size) अणु
		bt_dev_err(lldev->hu.hdev, "request_firmware failed(errno %d) for %s",
			   err, bts_scr_name);
		वापस -EINVAL;
	पूर्ण
	ptr = (व्योम *)fw->data;
	len = fw->size;
	/* bts_header to हटाओ out magic number and
	 * version
	 */
	ptr += माप(काष्ठा bts_header);
	len -= माप(काष्ठा bts_header);

	जबतक (len > 0 && ptr) अणु
		bt_dev_dbg(lldev->hu.hdev, " action size %d, type %d ",
			   ((काष्ठा bts_action *)ptr)->size,
			   ((काष्ठा bts_action *)ptr)->type);

		action_ptr = &(((काष्ठा bts_action *)ptr)->data[0]);

		चयन (((काष्ठा bts_action *)ptr)->type) अणु
		हाल ACTION_SEND_COMMAND:	/* action send */
			bt_dev_dbg(lldev->hu.hdev, "S");
			cmd = (काष्ठा hci_command *)action_ptr;
			err = send_command_from_firmware(lldev, cmd);
			अगर (err)
				जाओ out_rel_fw;
			अवरोध;
		हाल ACTION_WAIT_EVENT:  /* रुको */
			/* no need to रुको as command was synchronous */
			bt_dev_dbg(lldev->hu.hdev, "W");
			अवरोध;
		हाल ACTION_DELAY:	/* sleep */
			bt_dev_info(lldev->hu.hdev, "sleep command in scr");
			msleep(((काष्ठा bts_action_delay *)action_ptr)->msec);
			अवरोध;
		पूर्ण
		len -= (माप(काष्ठा bts_action) +
			((काष्ठा bts_action *)ptr)->size);
		ptr += माप(काष्ठा bts_action) +
			((काष्ठा bts_action *)ptr)->size;
	पूर्ण

out_rel_fw:
	/* fw करोwnload complete */
	release_firmware(fw);
	वापस err;
पूर्ण

अटल पूर्णांक ll_set_bdaddr(काष्ठा hci_dev *hdev, स्थिर bdaddr_t *bdaddr)
अणु
	bdaddr_t bdaddr_swapped;
	काष्ठा sk_buff *skb;

	/* HCI_VS_WRITE_BD_ADDR (at least on a CC2560A chip) expects the BD
	 * address to be MSB first, but bdaddr_t has the convention of being
	 * LSB first.
	 */
	baswap(&bdaddr_swapped, bdaddr);
	skb = __hci_cmd_sync(hdev, HCI_VS_WRITE_BD_ADDR, माप(bdaddr_t),
			     &bdaddr_swapped, HCI_INIT_TIMEOUT);
	अगर (!IS_ERR(skb))
		kमुक्त_skb(skb);

	वापस PTR_ERR_OR_ZERO(skb);
पूर्ण

अटल पूर्णांक ll_setup(काष्ठा hci_uart *hu)
अणु
	पूर्णांक err, retry = 3;
	काष्ठा ll_device *lldev;
	काष्ठा serdev_device *serdev = hu->serdev;
	u32 speed;

	अगर (!serdev)
		वापस 0;

	lldev = serdev_device_get_drvdata(serdev);

	hu->hdev->set_bdaddr = ll_set_bdaddr;

	serdev_device_set_flow_control(serdev, true);

	करो अणु
		/* Reset the Bluetooth device */
		gpiod_set_value_cansleep(lldev->enable_gpio, 0);
		msleep(5);
		gpiod_set_value_cansleep(lldev->enable_gpio, 1);
		mdelay(100);
		err = serdev_device_रुको_क्रम_cts(serdev, true, 200);
		अगर (err) अणु
			bt_dev_err(hu->hdev, "Failed to get CTS");
			वापस err;
		पूर्ण

		err = करोwnload_firmware(lldev);
		अगर (!err)
			अवरोध;

		/* Toggle BT_EN and retry */
		bt_dev_err(hu->hdev, "download firmware failed, retrying...");
	पूर्ण जबतक (retry--);

	अगर (err)
		वापस err;

	/* Set BD address अगर one was specअगरied at probe */
	अगर (!bacmp(&lldev->bdaddr, BDADDR_NONE)) अणु
		/* This means that there was an error getting the BD address
		 * during probe, so mark the device as having a bad address.
		 */
		set_bit(HCI_QUIRK_INVALID_BDADDR, &hu->hdev->quirks);
	पूर्ण अन्यथा अगर (bacmp(&lldev->bdaddr, BDADDR_ANY)) अणु
		err = ll_set_bdaddr(hu->hdev, &lldev->bdaddr);
		अगर (err)
			set_bit(HCI_QUIRK_INVALID_BDADDR, &hu->hdev->quirks);
	पूर्ण

	/* Operational speed अगर any */
	अगर (hu->oper_speed)
		speed = hu->oper_speed;
	अन्यथा अगर (hu->proto->oper_speed)
		speed = hu->proto->oper_speed;
	अन्यथा
		speed = 0;

	अगर (speed) अणु
		__le32 speed_le = cpu_to_le32(speed);
		काष्ठा sk_buff *skb;

		skb = __hci_cmd_sync(hu->hdev, HCI_VS_UPDATE_UART_HCI_BAUDRATE,
				     माप(speed_le), &speed_le,
				     HCI_INIT_TIMEOUT);
		अगर (!IS_ERR(skb)) अणु
			kमुक्त_skb(skb);
			serdev_device_set_baudrate(serdev, speed);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hci_uart_proto llp;

अटल पूर्णांक hci_ti_probe(काष्ठा serdev_device *serdev)
अणु
	काष्ठा hci_uart *hu;
	काष्ठा ll_device *lldev;
	काष्ठा nvmem_cell *bdaddr_cell;
	u32 max_speed = 3000000;

	lldev = devm_kzalloc(&serdev->dev, माप(काष्ठा ll_device), GFP_KERNEL);
	अगर (!lldev)
		वापस -ENOMEM;
	hu = &lldev->hu;

	serdev_device_set_drvdata(serdev, lldev);
	lldev->serdev = hu->serdev = serdev;

	lldev->enable_gpio = devm_gpiod_get_optional(&serdev->dev,
						     "enable",
						     GPIOD_OUT_LOW);
	अगर (IS_ERR(lldev->enable_gpio))
		वापस PTR_ERR(lldev->enable_gpio);

	lldev->ext_clk = devm_clk_get(&serdev->dev, "ext_clock");
	अगर (IS_ERR(lldev->ext_clk) && PTR_ERR(lldev->ext_clk) != -ENOENT)
		वापस PTR_ERR(lldev->ext_clk);

	of_property_पढ़ो_u32(serdev->dev.of_node, "max-speed", &max_speed);
	hci_uart_set_speeds(hu, 115200, max_speed);

	/* optional BD address from nvram */
	bdaddr_cell = nvmem_cell_get(&serdev->dev, "bd-address");
	अगर (IS_ERR(bdaddr_cell)) अणु
		पूर्णांक err = PTR_ERR(bdaddr_cell);

		अगर (err == -EPROBE_DEFER)
			वापस err;

		/* ENOENT means there is no matching nvmem cell and ENOSYS
		 * means that nvmem is not enabled in the kernel configuration.
		 */
		अगर (err != -ENOENT && err != -ENOSYS) अणु
			/* If there was some other error, give userspace a
			 * chance to fix the problem instead of failing to load
			 * the driver. Using BDADDR_NONE as a flag that is
			 * tested later in the setup function.
			 */
			dev_warn(&serdev->dev,
				 "Failed to get \"bd-address\" nvmem cell (%d)\n",
				 err);
			bacpy(&lldev->bdaddr, BDADDR_NONE);
		पूर्ण
	पूर्ण अन्यथा अणु
		bdaddr_t *bdaddr;
		माप_प्रकार len;

		bdaddr = nvmem_cell_पढ़ो(bdaddr_cell, &len);
		nvmem_cell_put(bdaddr_cell);
		अगर (IS_ERR(bdaddr)) अणु
			dev_err(&serdev->dev, "Failed to read nvmem bd-address\n");
			वापस PTR_ERR(bdaddr);
		पूर्ण
		अगर (len != माप(bdaddr_t)) अणु
			dev_err(&serdev->dev, "Invalid nvmem bd-address length\n");
			kमुक्त(bdaddr);
			वापस -EINVAL;
		पूर्ण

		/* As per the device tree bindings, the value from nvmem is
		 * expected to be MSB first, but in the kernel it is expected
		 * that bdaddr_t is LSB first.
		 */
		baswap(&lldev->bdaddr, bdaddr);
		kमुक्त(bdaddr);
	पूर्ण

	वापस hci_uart_रेजिस्टर_device(hu, &llp);
पूर्ण

अटल व्योम hci_ti_हटाओ(काष्ठा serdev_device *serdev)
अणु
	काष्ठा ll_device *lldev = serdev_device_get_drvdata(serdev);

	hci_uart_unरेजिस्टर_device(&lldev->hu);
पूर्ण

अटल स्थिर काष्ठा of_device_id hci_ti_of_match[] = अणु
	अणु .compatible = "ti,cc2560" पूर्ण,
	अणु .compatible = "ti,wl1271-st" पूर्ण,
	अणु .compatible = "ti,wl1273-st" पूर्ण,
	अणु .compatible = "ti,wl1281-st" पूर्ण,
	अणु .compatible = "ti,wl1283-st" पूर्ण,
	अणु .compatible = "ti,wl1285-st" पूर्ण,
	अणु .compatible = "ti,wl1801-st" पूर्ण,
	अणु .compatible = "ti,wl1805-st" पूर्ण,
	अणु .compatible = "ti,wl1807-st" पूर्ण,
	अणु .compatible = "ti,wl1831-st" पूर्ण,
	अणु .compatible = "ti,wl1835-st" पूर्ण,
	अणु .compatible = "ti,wl1837-st" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hci_ti_of_match);

अटल काष्ठा serdev_device_driver hci_ti_drv = अणु
	.driver		= अणु
		.name	= "hci-ti",
		.of_match_table = of_match_ptr(hci_ti_of_match),
	पूर्ण,
	.probe	= hci_ti_probe,
	.हटाओ	= hci_ti_हटाओ,
पूर्ण;
#अन्यथा
#घोषणा ll_setup शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा hci_uart_proto llp = अणु
	.id		= HCI_UART_LL,
	.name		= "LL",
	.setup		= ll_setup,
	.खोलो		= ll_खोलो,
	.बंद		= ll_बंद,
	.recv		= ll_recv,
	.enqueue	= ll_enqueue,
	.dequeue	= ll_dequeue,
	.flush		= ll_flush,
पूर्ण;

पूर्णांक __init ll_init(व्योम)
अणु
	serdev_device_driver_रेजिस्टर(&hci_ti_drv);

	वापस hci_uart_रेजिस्टर_proto(&llp);
पूर्ण

पूर्णांक __निकास ll_deinit(व्योम)
अणु
	serdev_device_driver_unरेजिस्टर(&hci_ti_drv);

	वापस hci_uart_unरेजिस्टर_proto(&llp);
पूर्ण
