<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  Bluetooth HCI UART driver क्रम Intel devices
 *
 *  Copyright (C) 2015  Intel Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/रुको.h>
#समावेश <linux/tty.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "hci_uart.h"
#समावेश "btintel.h"

#घोषणा STATE_BOOTLOADER	0
#घोषणा STATE_DOWNLOADING	1
#घोषणा STATE_FIRMWARE_LOADED	2
#घोषणा STATE_FIRMWARE_FAILED	3
#घोषणा STATE_BOOTING		4
#घोषणा STATE_LPM_ENABLED	5
#घोषणा STATE_TX_ACTIVE		6
#घोषणा STATE_SUSPENDED		7
#घोषणा STATE_LPM_TRANSACTION	8

#घोषणा HCI_LPM_WAKE_PKT 0xf0
#घोषणा HCI_LPM_PKT 0xf1
#घोषणा HCI_LPM_MAX_SIZE 10
#घोषणा HCI_LPM_HDR_SIZE HCI_EVENT_HDR_SIZE

#घोषणा LPM_OP_TX_NOTIFY 0x00
#घोषणा LPM_OP_SUSPEND_ACK 0x02
#घोषणा LPM_OP_RESUME_ACK 0x03

#घोषणा LPM_SUSPEND_DELAY_MS 1000

काष्ठा hci_lpm_pkt अणु
	__u8 opcode;
	__u8 dlen;
	__u8 data[];
पूर्ण __packed;

काष्ठा पूर्णांकel_device अणु
	काष्ठा list_head list;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा gpio_desc *reset;
	काष्ठा hci_uart *hu;
	काष्ठा mutex hu_lock;
	पूर्णांक irq;
पूर्ण;

अटल LIST_HEAD(पूर्णांकel_device_list);
अटल DEFINE_MUTEX(पूर्णांकel_device_list_lock);

काष्ठा पूर्णांकel_data अणु
	काष्ठा sk_buff *rx_skb;
	काष्ठा sk_buff_head txq;
	काष्ठा work_काष्ठा busy_work;
	काष्ठा hci_uart *hu;
	अचिन्हित दीर्घ flags;
पूर्ण;

अटल u8 पूर्णांकel_convert_speed(अचिन्हित पूर्णांक speed)
अणु
	चयन (speed) अणु
	हाल 9600:
		वापस 0x00;
	हाल 19200:
		वापस 0x01;
	हाल 38400:
		वापस 0x02;
	हाल 57600:
		वापस 0x03;
	हाल 115200:
		वापस 0x04;
	हाल 230400:
		वापस 0x05;
	हाल 460800:
		वापस 0x06;
	हाल 921600:
		वापस 0x07;
	हाल 1843200:
		वापस 0x08;
	हाल 3250000:
		वापस 0x09;
	हाल 2000000:
		वापस 0x0a;
	हाल 3000000:
		वापस 0x0b;
	शेष:
		वापस 0xff;
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_रुको_booting(काष्ठा hci_uart *hu)
अणु
	काष्ठा पूर्णांकel_data *पूर्णांकel = hu->priv;
	पूर्णांक err;

	err = रुको_on_bit_समयout(&पूर्णांकel->flags, STATE_BOOTING,
				  TASK_INTERRUPTIBLE,
				  msecs_to_jअगरfies(1000));

	अगर (err == -EINTR) अणु
		bt_dev_err(hu->hdev, "Device boot interrupted");
		वापस -EINTR;
	पूर्ण

	अगर (err) अणु
		bt_dev_err(hu->hdev, "Device boot timeout");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक पूर्णांकel_रुको_lpm_transaction(काष्ठा hci_uart *hu)
अणु
	काष्ठा पूर्णांकel_data *पूर्णांकel = hu->priv;
	पूर्णांक err;

	err = रुको_on_bit_समयout(&पूर्णांकel->flags, STATE_LPM_TRANSACTION,
				  TASK_INTERRUPTIBLE,
				  msecs_to_jअगरfies(1000));

	अगर (err == -EINTR) अणु
		bt_dev_err(hu->hdev, "LPM transaction interrupted");
		वापस -EINTR;
	पूर्ण

	अगर (err) अणु
		bt_dev_err(hu->hdev, "LPM transaction timeout");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक पूर्णांकel_lpm_suspend(काष्ठा hci_uart *hu)
अणु
	अटल स्थिर u8 suspend[] = अणु 0x01, 0x01, 0x01 पूर्ण;
	काष्ठा पूर्णांकel_data *पूर्णांकel = hu->priv;
	काष्ठा sk_buff *skb;

	अगर (!test_bit(STATE_LPM_ENABLED, &पूर्णांकel->flags) ||
	    test_bit(STATE_SUSPENDED, &पूर्णांकel->flags))
		वापस 0;

	अगर (test_bit(STATE_TX_ACTIVE, &पूर्णांकel->flags))
		वापस -EAGAIN;

	bt_dev_dbg(hu->hdev, "Suspending");

	skb = bt_skb_alloc(माप(suspend), GFP_KERNEL);
	अगर (!skb) अणु
		bt_dev_err(hu->hdev, "Failed to alloc memory for LPM packet");
		वापस -ENOMEM;
	पूर्ण

	skb_put_data(skb, suspend, माप(suspend));
	hci_skb_pkt_type(skb) = HCI_LPM_PKT;

	set_bit(STATE_LPM_TRANSACTION, &पूर्णांकel->flags);

	/* LPM flow is a priority, enqueue packet at list head */
	skb_queue_head(&पूर्णांकel->txq, skb);
	hci_uart_tx_wakeup(hu);

	पूर्णांकel_रुको_lpm_transaction(hu);
	/* Even in हाल of failure, जारी and test the suspended flag */

	clear_bit(STATE_LPM_TRANSACTION, &पूर्णांकel->flags);

	अगर (!test_bit(STATE_SUSPENDED, &पूर्णांकel->flags)) अणु
		bt_dev_err(hu->hdev, "Device suspend error");
		वापस -EINVAL;
	पूर्ण

	bt_dev_dbg(hu->hdev, "Suspended");

	hci_uart_set_flow_control(hu, true);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_lpm_resume(काष्ठा hci_uart *hu)
अणु
	काष्ठा पूर्णांकel_data *पूर्णांकel = hu->priv;
	काष्ठा sk_buff *skb;

	अगर (!test_bit(STATE_LPM_ENABLED, &पूर्णांकel->flags) ||
	    !test_bit(STATE_SUSPENDED, &पूर्णांकel->flags))
		वापस 0;

	bt_dev_dbg(hu->hdev, "Resuming");

	hci_uart_set_flow_control(hu, false);

	skb = bt_skb_alloc(0, GFP_KERNEL);
	अगर (!skb) अणु
		bt_dev_err(hu->hdev, "Failed to alloc memory for LPM packet");
		वापस -ENOMEM;
	पूर्ण

	hci_skb_pkt_type(skb) = HCI_LPM_WAKE_PKT;

	set_bit(STATE_LPM_TRANSACTION, &पूर्णांकel->flags);

	/* LPM flow is a priority, enqueue packet at list head */
	skb_queue_head(&पूर्णांकel->txq, skb);
	hci_uart_tx_wakeup(hu);

	पूर्णांकel_रुको_lpm_transaction(hu);
	/* Even in हाल of failure, जारी and test the suspended flag */

	clear_bit(STATE_LPM_TRANSACTION, &पूर्णांकel->flags);

	अगर (test_bit(STATE_SUSPENDED, &पूर्णांकel->flags)) अणु
		bt_dev_err(hu->hdev, "Device resume error");
		वापस -EINVAL;
	पूर्ण

	bt_dev_dbg(hu->hdev, "Resumed");

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल पूर्णांक पूर्णांकel_lpm_host_wake(काष्ठा hci_uart *hu)
अणु
	अटल स्थिर u8 lpm_resume_ack[] = अणु LPM_OP_RESUME_ACK, 0x00 पूर्ण;
	काष्ठा पूर्णांकel_data *पूर्णांकel = hu->priv;
	काष्ठा sk_buff *skb;

	hci_uart_set_flow_control(hu, false);

	clear_bit(STATE_SUSPENDED, &पूर्णांकel->flags);

	skb = bt_skb_alloc(माप(lpm_resume_ack), GFP_KERNEL);
	अगर (!skb) अणु
		bt_dev_err(hu->hdev, "Failed to alloc memory for LPM packet");
		वापस -ENOMEM;
	पूर्ण

	skb_put_data(skb, lpm_resume_ack, माप(lpm_resume_ack));
	hci_skb_pkt_type(skb) = HCI_LPM_PKT;

	/* LPM flow is a priority, enqueue packet at list head */
	skb_queue_head(&पूर्णांकel->txq, skb);
	hci_uart_tx_wakeup(hu);

	bt_dev_dbg(hu->hdev, "Resumed by controller");

	वापस 0;
पूर्ण

अटल irqवापस_t पूर्णांकel_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा पूर्णांकel_device *idev = dev_id;

	dev_info(&idev->pdev->dev, "hci_intel irq\n");

	mutex_lock(&idev->hu_lock);
	अगर (idev->hu)
		पूर्णांकel_lpm_host_wake(idev->hu);
	mutex_unlock(&idev->hu_lock);

	/* Host/Controller are now LPM resumed, trigger a new delayed suspend */
	pm_runसमय_get(&idev->pdev->dev);
	pm_runसमय_mark_last_busy(&idev->pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&idev->pdev->dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक पूर्णांकel_set_घातer(काष्ठा hci_uart *hu, bool घातered)
अणु
	काष्ठा पूर्णांकel_device *idev;
	पूर्णांक err = -ENODEV;

	अगर (!hu->tty->dev)
		वापस err;

	mutex_lock(&पूर्णांकel_device_list_lock);

	list_क्रम_each_entry(idev, &पूर्णांकel_device_list, list) अणु
		/* tty device and pdev device should share the same parent
		 * which is the UART port.
		 */
		अगर (hu->tty->dev->parent != idev->pdev->dev.parent)
			जारी;

		अगर (!idev->reset) अणु
			err = -ENOTSUPP;
			अवरोध;
		पूर्ण

		BT_INFO("hu %p, Switching compatible pm device (%s) to %u",
			hu, dev_name(&idev->pdev->dev), घातered);

		gpiod_set_value(idev->reset, घातered);

		/* Provide to idev a hu reference which is used to run LPM
		 * transactions (lpm suspend/resume) from PM callbacks.
		 * hu needs to be रक्षित against concurrent removing during
		 * these PM ops.
		 */
		mutex_lock(&idev->hu_lock);
		idev->hu = घातered ? hu : शून्य;
		mutex_unlock(&idev->hu_lock);

		अगर (idev->irq < 0)
			अवरोध;

		अगर (घातered && device_can_wakeup(&idev->pdev->dev)) अणु
			err = devm_request_thपढ़ोed_irq(&idev->pdev->dev,
							idev->irq, शून्य,
							पूर्णांकel_irq,
							IRQF_ONESHOT,
							"bt-host-wake", idev);
			अगर (err) अणु
				BT_ERR("hu %p, unable to allocate irq-%d",
				       hu, idev->irq);
				अवरोध;
			पूर्ण

			device_wakeup_enable(&idev->pdev->dev);

			pm_runसमय_set_active(&idev->pdev->dev);
			pm_runसमय_use_स्वतःsuspend(&idev->pdev->dev);
			pm_runसमय_set_स्वतःsuspend_delay(&idev->pdev->dev,
							 LPM_SUSPEND_DELAY_MS);
			pm_runसमय_enable(&idev->pdev->dev);
		पूर्ण अन्यथा अगर (!घातered && device_may_wakeup(&idev->pdev->dev)) अणु
			devm_मुक्त_irq(&idev->pdev->dev, idev->irq, idev);
			device_wakeup_disable(&idev->pdev->dev);

			pm_runसमय_disable(&idev->pdev->dev);
		पूर्ण
	पूर्ण

	mutex_unlock(&पूर्णांकel_device_list_lock);

	वापस err;
पूर्ण

अटल व्योम पूर्णांकel_busy_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पूर्णांकel_data *पूर्णांकel = container_of(work, काष्ठा पूर्णांकel_data,
						busy_work);
	काष्ठा पूर्णांकel_device *idev;

	अगर (!पूर्णांकel->hu->tty->dev)
		वापस;

	/* Link is busy, delay the suspend */
	mutex_lock(&पूर्णांकel_device_list_lock);
	list_क्रम_each_entry(idev, &पूर्णांकel_device_list, list) अणु
		अगर (पूर्णांकel->hu->tty->dev->parent == idev->pdev->dev.parent) अणु
			pm_runसमय_get(&idev->pdev->dev);
			pm_runसमय_mark_last_busy(&idev->pdev->dev);
			pm_runसमय_put_स्वतःsuspend(&idev->pdev->dev);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&पूर्णांकel_device_list_lock);
पूर्ण

अटल पूर्णांक पूर्णांकel_खोलो(काष्ठा hci_uart *hu)
अणु
	काष्ठा पूर्णांकel_data *पूर्णांकel;

	BT_DBG("hu %p", hu);

	अगर (!hci_uart_has_flow_control(hu))
		वापस -EOPNOTSUPP;

	पूर्णांकel = kzalloc(माप(*पूर्णांकel), GFP_KERNEL);
	अगर (!पूर्णांकel)
		वापस -ENOMEM;

	skb_queue_head_init(&पूर्णांकel->txq);
	INIT_WORK(&पूर्णांकel->busy_work, पूर्णांकel_busy_work);

	पूर्णांकel->hu = hu;

	hu->priv = पूर्णांकel;

	अगर (!पूर्णांकel_set_घातer(hu, true))
		set_bit(STATE_BOOTING, &पूर्णांकel->flags);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_बंद(काष्ठा hci_uart *hu)
अणु
	काष्ठा पूर्णांकel_data *पूर्णांकel = hu->priv;

	BT_DBG("hu %p", hu);

	cancel_work_sync(&पूर्णांकel->busy_work);

	पूर्णांकel_set_घातer(hu, false);

	skb_queue_purge(&पूर्णांकel->txq);
	kमुक्त_skb(पूर्णांकel->rx_skb);
	kमुक्त(पूर्णांकel);

	hu->priv = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_flush(काष्ठा hci_uart *hu)
अणु
	काष्ठा पूर्णांकel_data *पूर्णांकel = hu->priv;

	BT_DBG("hu %p", hu);

	skb_queue_purge(&पूर्णांकel->txq);

	वापस 0;
पूर्ण

अटल पूर्णांक inject_cmd_complete(काष्ठा hci_dev *hdev, __u16 opcode)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा hci_event_hdr *hdr;
	काष्ठा hci_ev_cmd_complete *evt;

	skb = bt_skb_alloc(माप(*hdr) + माप(*evt) + 1, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	hdr = skb_put(skb, माप(*hdr));
	hdr->evt = HCI_EV_CMD_COMPLETE;
	hdr->plen = माप(*evt) + 1;

	evt = skb_put(skb, माप(*evt));
	evt->ncmd = 0x01;
	evt->opcode = cpu_to_le16(opcode);

	skb_put_u8(skb, 0x00);

	hci_skb_pkt_type(skb) = HCI_EVENT_PKT;

	वापस hci_recv_frame(hdev, skb);
पूर्ण

अटल पूर्णांक पूर्णांकel_set_baudrate(काष्ठा hci_uart *hu, अचिन्हित पूर्णांक speed)
अणु
	काष्ठा पूर्णांकel_data *पूर्णांकel = hu->priv;
	काष्ठा hci_dev *hdev = hu->hdev;
	u8 speed_cmd[] = अणु 0x06, 0xfc, 0x01, 0x00 पूर्ण;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	/* This can be the first command sent to the chip, check
	 * that the controller is पढ़ोy.
	 */
	err = पूर्णांकel_रुको_booting(hu);

	clear_bit(STATE_BOOTING, &पूर्णांकel->flags);

	/* In हाल of समयout, try to जारी anyway */
	अगर (err && err != -ETIMEDOUT)
		वापस err;

	bt_dev_info(hdev, "Change controller speed to %d", speed);

	speed_cmd[3] = पूर्णांकel_convert_speed(speed);
	अगर (speed_cmd[3] == 0xff) अणु
		bt_dev_err(hdev, "Unsupported speed");
		वापस -EINVAL;
	पूर्ण

	/* Device will not accept speed change अगर Intel version has not been
	 * previously requested.
	 */
	skb = __hci_cmd_sync(hdev, 0xfc05, 0, शून्य, HCI_CMD_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "Reading Intel version information failed (%ld)",
			   PTR_ERR(skb));
		वापस PTR_ERR(skb);
	पूर्ण
	kमुक्त_skb(skb);

	skb = bt_skb_alloc(माप(speed_cmd), GFP_KERNEL);
	अगर (!skb) अणु
		bt_dev_err(hdev, "Failed to alloc memory for baudrate packet");
		वापस -ENOMEM;
	पूर्ण

	skb_put_data(skb, speed_cmd, माप(speed_cmd));
	hci_skb_pkt_type(skb) = HCI_COMMAND_PKT;

	hci_uart_set_flow_control(hu, true);

	skb_queue_tail(&पूर्णांकel->txq, skb);
	hci_uart_tx_wakeup(hu);

	/* रुको 100ms to change baudrate on controller side */
	msleep(100);

	hci_uart_set_baudrate(hu, speed);
	hci_uart_set_flow_control(hu, false);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_setup(काष्ठा hci_uart *hu)
अणु
	काष्ठा पूर्णांकel_data *पूर्णांकel = hu->priv;
	काष्ठा hci_dev *hdev = hu->hdev;
	काष्ठा sk_buff *skb;
	काष्ठा पूर्णांकel_version ver;
	काष्ठा पूर्णांकel_boot_params params;
	काष्ठा पूर्णांकel_device *idev;
	स्थिर काष्ठा firmware *fw;
	अक्षर fwname[64];
	u32 boot_param;
	kसमय_प्रकार callसमय, delta, retसमय;
	अचिन्हित दीर्घ दीर्घ duration;
	अचिन्हित पूर्णांक init_speed, oper_speed;
	पूर्णांक speed_change = 0;
	पूर्णांक err;

	bt_dev_dbg(hdev, "start intel_setup");

	hu->hdev->set_diag = btपूर्णांकel_set_diag;
	hu->hdev->set_bdaddr = btपूर्णांकel_set_bdaddr;

	/* Set the शेष boot parameter to 0x0 and it is updated to
	 * SKU specअगरic boot parameter after पढ़ोing Intel_Write_Boot_Params
	 * command जबतक करोwnloading the firmware.
	 */
	boot_param = 0x00000000;

	callसमय = kसमय_get();

	अगर (hu->init_speed)
		init_speed = hu->init_speed;
	अन्यथा
		init_speed = hu->proto->init_speed;

	अगर (hu->oper_speed)
		oper_speed = hu->oper_speed;
	अन्यथा
		oper_speed = hu->proto->oper_speed;

	अगर (oper_speed && init_speed && oper_speed != init_speed)
		speed_change = 1;

	/* Check that the controller is पढ़ोy */
	err = पूर्णांकel_रुको_booting(hu);

	clear_bit(STATE_BOOTING, &पूर्णांकel->flags);

	/* In हाल of समयout, try to जारी anyway */
	अगर (err && err != -ETIMEDOUT)
		वापस err;

	set_bit(STATE_BOOTLOADER, &पूर्णांकel->flags);

	/* Read the Intel version inक्रमmation to determine अगर the device
	 * is in bootloader mode or अगर it alपढ़ोy has operational firmware
	 * loaded.
	 */
	err = btपूर्णांकel_पढ़ो_version(hdev, &ver);
	अगर (err)
		वापस err;

	/* The hardware platक्रमm number has a fixed value of 0x37 and
	 * क्रम now only accept this single value.
	 */
	अगर (ver.hw_platक्रमm != 0x37) अणु
		bt_dev_err(hdev, "Unsupported Intel hardware platform (%u)",
			   ver.hw_platक्रमm);
		वापस -EINVAL;
	पूर्ण

        /* Check क्रम supported iBT hardware variants of this firmware
         * loading method.
         *
         * This check has been put in place to ensure correct क्रमward
         * compatibility options when newer hardware variants come aदीर्घ.
         */
	चयन (ver.hw_variant) अणु
	हाल 0x0b:	/* LnP */
	हाल 0x0c:	/* WsP */
	हाल 0x12:	/* ThP */
		अवरोध;
	शेष:
		bt_dev_err(hdev, "Unsupported Intel hardware variant (%u)",
			   ver.hw_variant);
		वापस -EINVAL;
	पूर्ण

	btपूर्णांकel_version_info(hdev, &ver);

	/* The firmware variant determines अगर the device is in bootloader
	 * mode or is running operational firmware. The value 0x06 identअगरies
	 * the bootloader and the value 0x23 identअगरies the operational
	 * firmware.
	 *
	 * When the operational firmware is alपढ़ोy present, then only
	 * the check क्रम valid Bluetooth device address is needed. This
	 * determines अगर the device will be added as configured or
	 * unconfigured controller.
	 *
	 * It is not possible to use the Secure Boot Parameters in this
	 * हाल since that command is only available in bootloader mode.
	 */
	अगर (ver.fw_variant == 0x23) अणु
		clear_bit(STATE_BOOTLOADER, &पूर्णांकel->flags);
		btपूर्णांकel_check_bdaddr(hdev);
		वापस 0;
	पूर्ण

	/* If the device is not in bootloader mode, then the only possible
	 * choice is to वापस an error and पात the device initialization.
	 */
	अगर (ver.fw_variant != 0x06) अणु
		bt_dev_err(hdev, "Unsupported Intel firmware variant (%u)",
			   ver.fw_variant);
		वापस -ENODEV;
	पूर्ण

	/* Read the secure boot parameters to identअगरy the operating
	 * details of the bootloader.
	 */
	err = btपूर्णांकel_पढ़ो_boot_params(hdev, &params);
	अगर (err)
		वापस err;

	/* It is required that every single firmware fragment is acknowledged
	 * with a command complete event. If the boot parameters indicate
	 * that this bootloader करोes not send them, then पात the setup.
	 */
	अगर (params.limited_cce != 0x00) अणु
		bt_dev_err(hdev, "Unsupported Intel firmware loading method (%u)",
			   params.limited_cce);
		वापस -EINVAL;
	पूर्ण

	/* If the OTP has no valid Bluetooth device address, then there will
	 * also be no valid address क्रम the operational firmware.
	 */
	अगर (!bacmp(&params.otp_bdaddr, BDADDR_ANY)) अणु
		bt_dev_info(hdev, "No device address configured");
		set_bit(HCI_QUIRK_INVALID_BDADDR, &hdev->quirks);
	पूर्ण

	/* With this Intel bootloader only the hardware variant and device
	 * revision inक्रमmation are used to select the right firmware क्रम SfP
	 * and WsP.
	 *
	 * The firmware filename is ibt-<hw_variant>-<dev_revid>.sfi.
	 *
	 * Currently the supported hardware variants are:
	 *   11 (0x0b) क्रम iBT 3.0 (LnP/SfP)
	 *   12 (0x0c) क्रम iBT 3.5 (WsP)
	 *
	 * For ThP/JfP and क्रम future SKU's, the FW name varies based on HW
	 * variant, HW revision and FW revision, as these are dependent on CNVi
	 * and RF Combination.
	 *
	 *   18 (0x12) क्रम iBT3.5 (ThP/JfP)
	 *
	 * The firmware file name क्रम these will be
	 * ibt-<hw_variant>-<hw_revision>-<fw_revision>.sfi.
	 *
	 */
	चयन (ver.hw_variant) अणु
	हाल 0x0b:      /* SfP */
	हाल 0x0c:      /* WsP */
		snम_लिखो(fwname, माप(fwname), "intel/ibt-%u-%u.sfi",
			 ver.hw_variant, le16_to_cpu(params.dev_revid));
		अवरोध;
	हाल 0x12:      /* ThP */
		snम_लिखो(fwname, माप(fwname), "intel/ibt-%u-%u-%u.sfi",
			 ver.hw_variant, ver.hw_revision, ver.fw_revision);
		अवरोध;
	शेष:
		bt_dev_err(hdev, "Unsupported Intel hardware variant (%u)",
			   ver.hw_variant);
		वापस -EINVAL;
	पूर्ण

	err = request_firmware(&fw, fwname, &hdev->dev);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to load Intel firmware file (%d)",
			   err);
		वापस err;
	पूर्ण

	bt_dev_info(hdev, "Found device firmware: %s", fwname);

	/* Save the DDC file name क्रम later */
	चयन (ver.hw_variant) अणु
	हाल 0x0b:      /* SfP */
	हाल 0x0c:      /* WsP */
		snम_लिखो(fwname, माप(fwname), "intel/ibt-%u-%u.ddc",
			 ver.hw_variant, le16_to_cpu(params.dev_revid));
		अवरोध;
	हाल 0x12:      /* ThP */
		snम_लिखो(fwname, माप(fwname), "intel/ibt-%u-%u-%u.ddc",
			 ver.hw_variant, ver.hw_revision, ver.fw_revision);
		अवरोध;
	शेष:
		bt_dev_err(hdev, "Unsupported Intel hardware variant (%u)",
			   ver.hw_variant);
		वापस -EINVAL;
	पूर्ण

	अगर (fw->size < 644) अणु
		bt_dev_err(hdev, "Invalid size of firmware file (%zu)",
			   fw->size);
		err = -EBADF;
		जाओ करोne;
	पूर्ण

	set_bit(STATE_DOWNLOADING, &पूर्णांकel->flags);

	/* Start firmware करोwnloading and get boot parameter */
	err = btपूर्णांकel_करोwnload_firmware(hdev, &ver, fw, &boot_param);
	अगर (err < 0)
		जाओ करोne;

	set_bit(STATE_FIRMWARE_LOADED, &पूर्णांकel->flags);

	bt_dev_info(hdev, "Waiting for firmware download to complete");

	/* Beक्रमe चयनing the device पूर्णांकo operational mode and with that
	 * booting the loaded firmware, रुको क्रम the bootloader notअगरication
	 * that all fragments have been successfully received.
	 *
	 * When the event processing receives the notअगरication, then the
	 * STATE_DOWNLOADING flag will be cleared.
	 *
	 * The firmware loading should not take दीर्घer than 5 seconds
	 * and thus just समयout अगर that happens and fail the setup
	 * of this device.
	 */
	err = रुको_on_bit_समयout(&पूर्णांकel->flags, STATE_DOWNLOADING,
				  TASK_INTERRUPTIBLE,
				  msecs_to_jअगरfies(5000));
	अगर (err == -EINTR) अणु
		bt_dev_err(hdev, "Firmware loading interrupted");
		err = -EINTR;
		जाओ करोne;
	पूर्ण

	अगर (err) अणु
		bt_dev_err(hdev, "Firmware loading timeout");
		err = -ETIMEDOUT;
		जाओ करोne;
	पूर्ण

	अगर (test_bit(STATE_FIRMWARE_FAILED, &पूर्णांकel->flags)) अणु
		bt_dev_err(hdev, "Firmware loading failed");
		err = -ENOEXEC;
		जाओ करोne;
	पूर्ण

	retसमय = kसमय_get();
	delta = kसमय_sub(retसमय, callसमय);
	duration = (अचिन्हित दीर्घ दीर्घ) kसमय_प्रकारo_ns(delta) >> 10;

	bt_dev_info(hdev, "Firmware loaded in %llu usecs", duration);

करोne:
	release_firmware(fw);

	/* Check अगर there was an error and अगर is not -EALREADY which means the
	 * firmware has alपढ़ोy been loaded.
	 */
	अगर (err < 0 && err != -EALREADY)
		वापस err;

	/* We need to restore the शेष speed beक्रमe Intel reset */
	अगर (speed_change) अणु
		err = पूर्णांकel_set_baudrate(hu, init_speed);
		अगर (err)
			वापस err;
	पूर्ण

	callसमय = kसमय_get();

	set_bit(STATE_BOOTING, &पूर्णांकel->flags);

	err = btपूर्णांकel_send_पूर्णांकel_reset(hdev, boot_param);
	अगर (err)
		वापस err;

	/* The bootloader will not indicate when the device is पढ़ोy. This
	 * is करोne by the operational firmware sending bootup notअगरication.
	 *
	 * Booting पूर्णांकo operational firmware should not take दीर्घer than
	 * 1 second. However अगर that happens, then just fail the setup
	 * since something went wrong.
	 */
	bt_dev_info(hdev, "Waiting for device to boot");

	err = पूर्णांकel_रुको_booting(hu);
	अगर (err)
		वापस err;

	clear_bit(STATE_BOOTING, &पूर्णांकel->flags);

	retसमय = kसमय_get();
	delta = kसमय_sub(retसमय, callसमय);
	duration = (अचिन्हित दीर्घ दीर्घ) kसमय_प्रकारo_ns(delta) >> 10;

	bt_dev_info(hdev, "Device booted in %llu usecs", duration);

	/* Enable LPM अगर matching pdev with wakeup enabled, set TX active
	 * until further LPM TX notअगरication.
	 */
	mutex_lock(&पूर्णांकel_device_list_lock);
	list_क्रम_each_entry(idev, &पूर्णांकel_device_list, list) अणु
		अगर (!hu->tty->dev)
			अवरोध;
		अगर (hu->tty->dev->parent == idev->pdev->dev.parent) अणु
			अगर (device_may_wakeup(&idev->pdev->dev)) अणु
				set_bit(STATE_LPM_ENABLED, &पूर्णांकel->flags);
				set_bit(STATE_TX_ACTIVE, &पूर्णांकel->flags);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&पूर्णांकel_device_list_lock);

	/* Ignore errors, device can work without DDC parameters */
	btपूर्णांकel_load_ddc_config(hdev, fwname);

	skb = __hci_cmd_sync(hdev, HCI_OP_RESET, 0, शून्य, HCI_CMD_TIMEOUT);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);
	kमुक्त_skb(skb);

	अगर (speed_change) अणु
		err = पूर्णांकel_set_baudrate(hu, oper_speed);
		अगर (err)
			वापस err;
	पूर्ण

	bt_dev_info(hdev, "Setup complete");

	clear_bit(STATE_BOOTLOADER, &पूर्णांकel->flags);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_recv_event(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);
	काष्ठा पूर्णांकel_data *पूर्णांकel = hu->priv;
	काष्ठा hci_event_hdr *hdr;

	अगर (!test_bit(STATE_BOOTLOADER, &पूर्णांकel->flags) &&
	    !test_bit(STATE_BOOTING, &पूर्णांकel->flags))
		जाओ recv;

	hdr = (व्योम *)skb->data;

	/* When the firmware loading completes the device sends
	 * out a venकरोr specअगरic event indicating the result of
	 * the firmware loading.
	 */
	अगर (skb->len == 7 && hdr->evt == 0xff && hdr->plen == 0x05 &&
	    skb->data[2] == 0x06) अणु
		अगर (skb->data[3] != 0x00)
			set_bit(STATE_FIRMWARE_FAILED, &पूर्णांकel->flags);

		अगर (test_and_clear_bit(STATE_DOWNLOADING, &पूर्णांकel->flags) &&
		    test_bit(STATE_FIRMWARE_LOADED, &पूर्णांकel->flags))
			wake_up_bit(&पूर्णांकel->flags, STATE_DOWNLOADING);

	/* When चयनing to the operational firmware the device
	 * sends a venकरोr specअगरic event indicating that the bootup
	 * completed.
	 */
	पूर्ण अन्यथा अगर (skb->len == 9 && hdr->evt == 0xff && hdr->plen == 0x07 &&
		   skb->data[2] == 0x02) अणु
		अगर (test_and_clear_bit(STATE_BOOTING, &पूर्णांकel->flags))
			wake_up_bit(&पूर्णांकel->flags, STATE_BOOTING);
	पूर्ण
recv:
	वापस hci_recv_frame(hdev, skb);
पूर्ण

अटल व्योम पूर्णांकel_recv_lpm_notअगरy(काष्ठा hci_dev *hdev, पूर्णांक value)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);
	काष्ठा पूर्णांकel_data *पूर्णांकel = hu->priv;

	bt_dev_dbg(hdev, "TX idle notification (%d)", value);

	अगर (value) अणु
		set_bit(STATE_TX_ACTIVE, &पूर्णांकel->flags);
		schedule_work(&पूर्णांकel->busy_work);
	पूर्ण अन्यथा अणु
		clear_bit(STATE_TX_ACTIVE, &पूर्णांकel->flags);
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_recv_lpm(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_lpm_pkt *lpm = (व्योम *)skb->data;
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);
	काष्ठा पूर्णांकel_data *पूर्णांकel = hu->priv;

	चयन (lpm->opcode) अणु
	हाल LPM_OP_TX_NOTIFY:
		अगर (lpm->dlen < 1) अणु
			bt_dev_err(hu->hdev, "Invalid LPM notification packet");
			अवरोध;
		पूर्ण
		पूर्णांकel_recv_lpm_notअगरy(hdev, lpm->data[0]);
		अवरोध;
	हाल LPM_OP_SUSPEND_ACK:
		set_bit(STATE_SUSPENDED, &पूर्णांकel->flags);
		अगर (test_and_clear_bit(STATE_LPM_TRANSACTION, &पूर्णांकel->flags))
			wake_up_bit(&पूर्णांकel->flags, STATE_LPM_TRANSACTION);
		अवरोध;
	हाल LPM_OP_RESUME_ACK:
		clear_bit(STATE_SUSPENDED, &पूर्णांकel->flags);
		अगर (test_and_clear_bit(STATE_LPM_TRANSACTION, &पूर्णांकel->flags))
			wake_up_bit(&पूर्णांकel->flags, STATE_LPM_TRANSACTION);
		अवरोध;
	शेष:
		bt_dev_err(hdev, "Unknown LPM opcode (%02x)", lpm->opcode);
		अवरोध;
	पूर्ण

	kमुक्त_skb(skb);

	वापस 0;
पूर्ण

#घोषणा INTEL_RECV_LPM \
	.type = HCI_LPM_PKT, \
	.hlen = HCI_LPM_HDR_SIZE, \
	.loff = 1, \
	.lsize = 1, \
	.maxlen = HCI_LPM_MAX_SIZE

अटल स्थिर काष्ठा h4_recv_pkt पूर्णांकel_recv_pkts[] = अणु
	अणु H4_RECV_ACL,    .recv = hci_recv_frame   पूर्ण,
	अणु H4_RECV_SCO,    .recv = hci_recv_frame   पूर्ण,
	अणु H4_RECV_EVENT,  .recv = पूर्णांकel_recv_event पूर्ण,
	अणु INTEL_RECV_LPM, .recv = पूर्णांकel_recv_lpm   पूर्ण,
पूर्ण;

अटल पूर्णांक पूर्णांकel_recv(काष्ठा hci_uart *hu, स्थिर व्योम *data, पूर्णांक count)
अणु
	काष्ठा पूर्णांकel_data *पूर्णांकel = hu->priv;

	अगर (!test_bit(HCI_UART_REGISTERED, &hu->flags))
		वापस -EUNATCH;

	पूर्णांकel->rx_skb = h4_recv_buf(hu->hdev, पूर्णांकel->rx_skb, data, count,
				    पूर्णांकel_recv_pkts,
				    ARRAY_SIZE(पूर्णांकel_recv_pkts));
	अगर (IS_ERR(पूर्णांकel->rx_skb)) अणु
		पूर्णांक err = PTR_ERR(पूर्णांकel->rx_skb);
		bt_dev_err(hu->hdev, "Frame reassembly failed (%d)", err);
		पूर्णांकel->rx_skb = शून्य;
		वापस err;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक पूर्णांकel_enqueue(काष्ठा hci_uart *hu, काष्ठा sk_buff *skb)
अणु
	काष्ठा पूर्णांकel_data *पूर्णांकel = hu->priv;
	काष्ठा पूर्णांकel_device *idev;

	BT_DBG("hu %p skb %p", hu, skb);

	अगर (!hu->tty->dev)
		जाओ out_enqueue;

	/* Be sure our controller is resumed and potential LPM transaction
	 * completed beक्रमe enqueuing any packet.
	 */
	mutex_lock(&पूर्णांकel_device_list_lock);
	list_क्रम_each_entry(idev, &पूर्णांकel_device_list, list) अणु
		अगर (hu->tty->dev->parent == idev->pdev->dev.parent) अणु
			pm_runसमय_get_sync(&idev->pdev->dev);
			pm_runसमय_mark_last_busy(&idev->pdev->dev);
			pm_runसमय_put_स्वतःsuspend(&idev->pdev->dev);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&पूर्णांकel_device_list_lock);
out_enqueue:
	skb_queue_tail(&पूर्णांकel->txq, skb);

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *पूर्णांकel_dequeue(काष्ठा hci_uart *hu)
अणु
	काष्ठा पूर्णांकel_data *पूर्णांकel = hu->priv;
	काष्ठा sk_buff *skb;

	skb = skb_dequeue(&पूर्णांकel->txq);
	अगर (!skb)
		वापस skb;

	अगर (test_bit(STATE_BOOTLOADER, &पूर्णांकel->flags) &&
	    (hci_skb_pkt_type(skb) == HCI_COMMAND_PKT)) अणु
		काष्ठा hci_command_hdr *cmd = (व्योम *)skb->data;
		__u16 opcode = le16_to_cpu(cmd->opcode);

		/* When the 0xfc01 command is issued to boot पूर्णांकo
		 * the operational firmware, it will actually not
		 * send a command complete event. To keep the flow
		 * control working inject that event here.
		 */
		अगर (opcode == 0xfc01)
			inject_cmd_complete(hu->hdev, opcode);
	पूर्ण

	/* Prepend skb with frame type */
	स_नकल(skb_push(skb, 1), &hci_skb_pkt_type(skb), 1);

	वापस skb;
पूर्ण

अटल स्थिर काष्ठा hci_uart_proto पूर्णांकel_proto = अणु
	.id		= HCI_UART_INTEL,
	.name		= "Intel",
	.manufacturer	= 2,
	.init_speed	= 115200,
	.oper_speed	= 3000000,
	.खोलो		= पूर्णांकel_खोलो,
	.बंद		= पूर्णांकel_बंद,
	.flush		= पूर्णांकel_flush,
	.setup		= पूर्णांकel_setup,
	.set_baudrate	= पूर्णांकel_set_baudrate,
	.recv		= पूर्णांकel_recv,
	.enqueue	= पूर्णांकel_enqueue,
	.dequeue	= पूर्णांकel_dequeue,
पूर्ण;

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id पूर्णांकel_acpi_match[] = अणु
	अणु "INT33E1", 0 पूर्ण,
	अणु "INT33E3", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, पूर्णांकel_acpi_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक पूर्णांकel_suspend_device(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_device *idev = dev_get_drvdata(dev);

	mutex_lock(&idev->hu_lock);
	अगर (idev->hu)
		पूर्णांकel_lpm_suspend(idev->hu);
	mutex_unlock(&idev->hu_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_resume_device(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_device *idev = dev_get_drvdata(dev);

	mutex_lock(&idev->hu_lock);
	अगर (idev->hu)
		पूर्णांकel_lpm_resume(idev->hu);
	mutex_unlock(&idev->hu_lock);

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक पूर्णांकel_suspend(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_device *idev = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(idev->irq);

	वापस पूर्णांकel_suspend_device(dev);
पूर्ण

अटल पूर्णांक पूर्णांकel_resume(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_device *idev = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(idev->irq);

	वापस पूर्णांकel_resume_device(dev);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops पूर्णांकel_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(पूर्णांकel_suspend, पूर्णांकel_resume)
	SET_RUNTIME_PM_OPS(पूर्णांकel_suspend_device, पूर्णांकel_resume_device, शून्य)
पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_params reset_gpios = अणु 0, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params host_wake_gpios = अणु 1, 0, false पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping acpi_hci_पूर्णांकel_gpios[] = अणु
	अणु "reset-gpios", &reset_gpios, 1, ACPI_GPIO_QUIRK_ONLY_GPIOIO पूर्ण,
	अणु "host-wake-gpios", &host_wake_gpios, 1, ACPI_GPIO_QUIRK_ONLY_GPIOIO पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक पूर्णांकel_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_device *idev;
	पूर्णांक ret;

	idev = devm_kzalloc(&pdev->dev, माप(*idev), GFP_KERNEL);
	अगर (!idev)
		वापस -ENOMEM;

	mutex_init(&idev->hu_lock);

	idev->pdev = pdev;

	ret = devm_acpi_dev_add_driver_gpios(&pdev->dev, acpi_hci_पूर्णांकel_gpios);
	अगर (ret)
		dev_dbg(&pdev->dev, "Unable to add GPIO mapping table\n");

	idev->reset = devm_gpiod_get(&pdev->dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(idev->reset)) अणु
		dev_err(&pdev->dev, "Unable to retrieve gpio\n");
		वापस PTR_ERR(idev->reset);
	पूर्ण

	idev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (idev->irq < 0) अणु
		काष्ठा gpio_desc *host_wake;

		dev_err(&pdev->dev, "No IRQ, falling back to gpio-irq\n");

		host_wake = devm_gpiod_get(&pdev->dev, "host-wake", GPIOD_IN);
		अगर (IS_ERR(host_wake)) अणु
			dev_err(&pdev->dev, "Unable to retrieve IRQ\n");
			जाओ no_irq;
		पूर्ण

		idev->irq = gpiod_to_irq(host_wake);
		अगर (idev->irq < 0) अणु
			dev_err(&pdev->dev, "No corresponding irq for gpio\n");
			जाओ no_irq;
		पूर्ण
	पूर्ण

	/* Only enable wake-up/irq when controller is घातered */
	device_set_wakeup_capable(&pdev->dev, true);
	device_wakeup_disable(&pdev->dev);

no_irq:
	platक्रमm_set_drvdata(pdev, idev);

	/* Place this instance on the device list */
	mutex_lock(&पूर्णांकel_device_list_lock);
	list_add_tail(&idev->list, &पूर्णांकel_device_list);
	mutex_unlock(&पूर्णांकel_device_list_lock);

	dev_info(&pdev->dev, "registered, gpio(%d)/irq(%d).\n",
		 desc_to_gpio(idev->reset), idev->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_device *idev = platक्रमm_get_drvdata(pdev);

	device_wakeup_disable(&pdev->dev);

	mutex_lock(&पूर्णांकel_device_list_lock);
	list_del(&idev->list);
	mutex_unlock(&पूर्णांकel_device_list_lock);

	dev_info(&pdev->dev, "unregistered.\n");

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver पूर्णांकel_driver = अणु
	.probe = पूर्णांकel_probe,
	.हटाओ = पूर्णांकel_हटाओ,
	.driver = अणु
		.name = "hci_intel",
		.acpi_match_table = ACPI_PTR(पूर्णांकel_acpi_match),
		.pm = &पूर्णांकel_pm_ops,
	पूर्ण,
पूर्ण;

पूर्णांक __init पूर्णांकel_init(व्योम)
अणु
	platक्रमm_driver_रेजिस्टर(&पूर्णांकel_driver);

	वापस hci_uart_रेजिस्टर_proto(&पूर्णांकel_proto);
पूर्ण

पूर्णांक __निकास पूर्णांकel_deinit(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&पूर्णांकel_driver);

	वापस hci_uart_unरेजिस्टर_proto(&पूर्णांकel_proto);
पूर्ण
