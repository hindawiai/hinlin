<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  Bluetooth HCI UART driver क्रम Broadcom devices
 *
 *  Copyright (C) 2015  Intel Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/property.h>
#समावेश <linux/platक्रमm_data/x86/apple.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/clk.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/tty.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dmi.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/serdev.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "btbcm.h"
#समावेश "hci_uart.h"

#घोषणा BCM_शून्य_PKT 0x00
#घोषणा BCM_शून्य_SIZE 0

#घोषणा BCM_LM_DIAG_PKT 0x07
#घोषणा BCM_LM_DIAG_SIZE 63

#घोषणा BCM_TYPE49_PKT 0x31
#घोषणा BCM_TYPE49_SIZE 0

#घोषणा BCM_TYPE52_PKT 0x34
#घोषणा BCM_TYPE52_SIZE 0

#घोषणा BCM_AUTOSUSPEND_DELAY	5000 /* शेष स्वतःsleep delay */

#घोषणा BCM_NUM_SUPPLIES 2

/**
 * काष्ठा bcm_device_data - device specअगरic data
 * @no_early_set_baudrate: Disallow set baudrate beक्रमe driver setup()
 */
काष्ठा bcm_device_data अणु
	bool	no_early_set_baudrate;
	bool	drive_rts_on_खोलो;
पूर्ण;

/**
 * काष्ठा bcm_device - device driver resources
 * @serdev_hu: HCI UART controller काष्ठा
 * @list: bcm_device_list node
 * @dev: physical UART slave
 * @name: device name logged by bt_dev_*() functions
 * @device_wakeup: BT_WAKE pin,
 *	निश्चित = Bluetooth device must wake up or reमुख्य awake,
 *	deनिश्चित = Bluetooth device may sleep when sleep criteria are met
 * @shutकरोwn: BT_REG_ON pin,
 *	घातer up or घातer करोwn Bluetooth device पूर्णांकernal regulators
 * @reset: BT_RST_N pin,
 *	active low resets the Bluetooth logic core
 * @set_device_wakeup: callback to toggle BT_WAKE pin
 *	either by accessing @device_wakeup or by calling @btlp
 * @set_shutकरोwn: callback to toggle BT_REG_ON pin
 *	either by accessing @shutकरोwn or by calling @btpu/@btpd
 * @btlp: Apple ACPI method to toggle BT_WAKE pin ("Bluetooth Low Power")
 * @btpu: Apple ACPI method to drive BT_REG_ON pin high ("Bluetooth Power Up")
 * @btpd: Apple ACPI method to drive BT_REG_ON pin low ("Bluetooth Power Down")
 * @txco_clk: बाह्यal reference frequency घड़ी used by Bluetooth device
 * @lpo_clk: बाह्यal LPO घड़ी used by Bluetooth device
 * @supplies: VBAT and VDDIO supplies used by Bluetooth device
 * @res_enabled: whether घड़ीs and supplies are prepared and enabled
 * @init_speed: शेष baudrate of Bluetooth device;
 *	the host UART is initially set to this baudrate so that
 *	it can configure the Bluetooth device क्रम @oper_speed
 * @oper_speed: preferred baudrate of Bluetooth device;
 *	set to 0 अगर @init_speed is alपढ़ोy the preferred baudrate
 * @irq: पूर्णांकerrupt triggered by HOST_WAKE_BT pin
 * @irq_active_low: whether @irq is active low
 * @hu: poपूर्णांकer to HCI UART controller काष्ठा,
 *	used to disable flow control during runसमय suspend and प्रणाली sleep
 * @is_suspended: whether flow control is currently disabled
 * @no_early_set_baudrate: करोn't set_baudrate beक्रमe setup()
 */
काष्ठा bcm_device अणु
	/* Must be the first member, hci_serdev.c expects this. */
	काष्ठा hci_uart		serdev_hu;
	काष्ठा list_head	list;

	काष्ठा device		*dev;

	स्थिर अक्षर		*name;
	काष्ठा gpio_desc	*device_wakeup;
	काष्ठा gpio_desc	*shutकरोwn;
	काष्ठा gpio_desc	*reset;
	पूर्णांक			(*set_device_wakeup)(काष्ठा bcm_device *, bool);
	पूर्णांक			(*set_shutकरोwn)(काष्ठा bcm_device *, bool);
#अगर_घोषित CONFIG_ACPI
	acpi_handle		btlp, btpu, btpd;
	पूर्णांक			gpio_count;
	पूर्णांक			gpio_पूर्णांक_idx;
#पूर्ण_अगर

	काष्ठा clk		*txco_clk;
	काष्ठा clk		*lpo_clk;
	काष्ठा regulator_bulk_data supplies[BCM_NUM_SUPPLIES];
	bool			res_enabled;

	u32			init_speed;
	u32			oper_speed;
	पूर्णांक			irq;
	bool			irq_active_low;
	bool			irq_acquired;

#अगर_घोषित CONFIG_PM
	काष्ठा hci_uart		*hu;
	bool			is_suspended;
#पूर्ण_अगर
	bool			no_early_set_baudrate;
	bool			drive_rts_on_खोलो;
	u8			pcm_पूर्णांक_params[5];
पूर्ण;

/* generic bcm uart resources */
काष्ठा bcm_data अणु
	काष्ठा sk_buff		*rx_skb;
	काष्ठा sk_buff_head	txq;

	काष्ठा bcm_device	*dev;
पूर्ण;

/* List of BCM BT UART devices */
अटल DEFINE_MUTEX(bcm_device_lock);
अटल LIST_HEAD(bcm_device_list);

अटल पूर्णांक irq_polarity = -1;
module_param(irq_polarity, पूर्णांक, 0444);
MODULE_PARM_DESC(irq_polarity, "IRQ polarity 0: active-high 1: active-low");

अटल अंतरभूत व्योम host_set_baudrate(काष्ठा hci_uart *hu, अचिन्हित पूर्णांक speed)
अणु
	अगर (hu->serdev)
		serdev_device_set_baudrate(hu->serdev, speed);
	अन्यथा
		hci_uart_set_baudrate(hu, speed);
पूर्ण

अटल पूर्णांक bcm_set_baudrate(काष्ठा hci_uart *hu, अचिन्हित पूर्णांक speed)
अणु
	काष्ठा hci_dev *hdev = hu->hdev;
	काष्ठा sk_buff *skb;
	काष्ठा bcm_update_uart_baud_rate param;

	अगर (speed > 3000000) अणु
		काष्ठा bcm_ग_लिखो_uart_घड़ी_setting घड़ी;

		घड़ी.type = BCM_UART_CLOCK_48MHZ;

		bt_dev_dbg(hdev, "Set Controller clock (%d)", घड़ी.type);

		/* This Broadcom specअगरic command changes the UART's controller
		 * घड़ी क्रम baud rate > 3000000.
		 */
		skb = __hci_cmd_sync(hdev, 0xfc45, 1, &घड़ी, HCI_INIT_TIMEOUT);
		अगर (IS_ERR(skb)) अणु
			पूर्णांक err = PTR_ERR(skb);
			bt_dev_err(hdev, "BCM: failed to write clock (%d)",
				   err);
			वापस err;
		पूर्ण

		kमुक्त_skb(skb);
	पूर्ण

	bt_dev_dbg(hdev, "Set Controller UART speed to %d bit/s", speed);

	param.zero = cpu_to_le16(0);
	param.baud_rate = cpu_to_le32(speed);

	/* This Broadcom specअगरic command changes the UART's controller baud
	 * rate.
	 */
	skb = __hci_cmd_sync(hdev, 0xfc18, माप(param), &param,
			     HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		पूर्णांक err = PTR_ERR(skb);
		bt_dev_err(hdev, "BCM: failed to write update baudrate (%d)",
			   err);
		वापस err;
	पूर्ण

	kमुक्त_skb(skb);

	वापस 0;
पूर्ण

/* bcm_device_exists should be रक्षित by bcm_device_lock */
अटल bool bcm_device_exists(काष्ठा bcm_device *device)
अणु
	काष्ठा list_head *p;

#अगर_घोषित CONFIG_PM
	/* Devices using serdev always exist */
	अगर (device && device->hu && device->hu->serdev)
		वापस true;
#पूर्ण_अगर

	list_क्रम_each(p, &bcm_device_list) अणु
		काष्ठा bcm_device *dev = list_entry(p, काष्ठा bcm_device, list);

		अगर (device == dev)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक bcm_gpio_set_घातer(काष्ठा bcm_device *dev, bool घातered)
अणु
	पूर्णांक err;

	अगर (घातered && !dev->res_enabled) अणु
		/* Intel Macs use bcm_apple_get_resources() and करोn't
		 * have regulator supplies configured.
		 */
		अगर (dev->supplies[0].supply) अणु
			err = regulator_bulk_enable(BCM_NUM_SUPPLIES,
						    dev->supplies);
			अगर (err)
				वापस err;
		पूर्ण

		/* LPO घड़ी needs to be 32.768 kHz */
		err = clk_set_rate(dev->lpo_clk, 32768);
		अगर (err) अणु
			dev_err(dev->dev, "Could not set LPO clock rate\n");
			जाओ err_regulator_disable;
		पूर्ण

		err = clk_prepare_enable(dev->lpo_clk);
		अगर (err)
			जाओ err_regulator_disable;

		err = clk_prepare_enable(dev->txco_clk);
		अगर (err)
			जाओ err_lpo_clk_disable;
	पूर्ण

	err = dev->set_shutकरोwn(dev, घातered);
	अगर (err)
		जाओ err_txco_clk_disable;

	err = dev->set_device_wakeup(dev, घातered);
	अगर (err)
		जाओ err_revert_shutकरोwn;

	अगर (!घातered && dev->res_enabled) अणु
		clk_disable_unprepare(dev->txco_clk);
		clk_disable_unprepare(dev->lpo_clk);

		/* Intel Macs use bcm_apple_get_resources() and करोn't
		 * have regulator supplies configured.
		 */
		अगर (dev->supplies[0].supply)
			regulator_bulk_disable(BCM_NUM_SUPPLIES,
					       dev->supplies);
	पूर्ण

	/* रुको क्रम device to घातer on and come out of reset */
	usleep_range(100000, 120000);

	dev->res_enabled = घातered;

	वापस 0;

err_revert_shutकरोwn:
	dev->set_shutकरोwn(dev, !घातered);
err_txco_clk_disable:
	अगर (घातered && !dev->res_enabled)
		clk_disable_unprepare(dev->txco_clk);
err_lpo_clk_disable:
	अगर (घातered && !dev->res_enabled)
		clk_disable_unprepare(dev->lpo_clk);
err_regulator_disable:
	अगर (घातered && !dev->res_enabled)
		regulator_bulk_disable(BCM_NUM_SUPPLIES, dev->supplies);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल irqवापस_t bcm_host_wake(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा bcm_device *bdev = data;

	bt_dev_dbg(bdev, "Host wake IRQ");

	pm_runसमय_get(bdev->dev);
	pm_runसमय_mark_last_busy(bdev->dev);
	pm_runसमय_put_स्वतःsuspend(bdev->dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bcm_request_irq(काष्ठा bcm_data *bcm)
अणु
	काष्ठा bcm_device *bdev = bcm->dev;
	पूर्णांक err;

	mutex_lock(&bcm_device_lock);
	अगर (!bcm_device_exists(bdev)) अणु
		err = -ENODEV;
		जाओ unlock;
	पूर्ण

	अगर (bdev->irq <= 0) अणु
		err = -EOPNOTSUPP;
		जाओ unlock;
	पूर्ण

	err = devm_request_irq(bdev->dev, bdev->irq, bcm_host_wake,
			       bdev->irq_active_low ? IRQF_TRIGGER_FALLING :
						      IRQF_TRIGGER_RISING,
			       "host_wake", bdev);
	अगर (err) अणु
		bdev->irq = err;
		जाओ unlock;
	पूर्ण

	bdev->irq_acquired = true;

	device_init_wakeup(bdev->dev, true);

	pm_runसमय_set_स्वतःsuspend_delay(bdev->dev,
					 BCM_AUTOSUSPEND_DELAY);
	pm_runसमय_use_स्वतःsuspend(bdev->dev);
	pm_runसमय_set_active(bdev->dev);
	pm_runसमय_enable(bdev->dev);

unlock:
	mutex_unlock(&bcm_device_lock);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा bcm_set_sleep_mode शेष_sleep_params = अणु
	.sleep_mode = 1,	/* 0=Disabled, 1=UART, 2=Reserved, 3=USB */
	.idle_host = 2,		/* idle threshold HOST, in 300ms */
	.idle_dev = 2,		/* idle threshold device, in 300ms */
	.bt_wake_active = 1,	/* BT_WAKE active mode: 1 = high, 0 = low */
	.host_wake_active = 0,	/* HOST_WAKE active mode: 1 = high, 0 = low */
	.allow_host_sleep = 1,	/* Allow host sleep in SCO flag */
	.combine_modes = 1,	/* Combine sleep and LPM flag */
	.tristate_control = 0,	/* Allow tri-state control of UART tx flag */
	/* Irrelevant USB flags */
	.usb_स्वतः_sleep = 0,
	.usb_resume_समयout = 0,
	.अवरोध_to_host = 0,
	.pulsed_host_wake = 1,
पूर्ण;

अटल पूर्णांक bcm_setup_sleep(काष्ठा hci_uart *hu)
अणु
	काष्ठा bcm_data *bcm = hu->priv;
	काष्ठा sk_buff *skb;
	काष्ठा bcm_set_sleep_mode sleep_params = शेष_sleep_params;

	sleep_params.host_wake_active = !bcm->dev->irq_active_low;

	skb = __hci_cmd_sync(hu->hdev, 0xfc27, माप(sleep_params),
			     &sleep_params, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		पूर्णांक err = PTR_ERR(skb);
		bt_dev_err(hu->hdev, "Sleep VSC failed (%d)", err);
		वापस err;
	पूर्ण
	kमुक्त_skb(skb);

	bt_dev_dbg(hu->hdev, "Set Sleep Parameters VSC succeeded");

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक bcm_request_irq(काष्ठा bcm_data *bcm) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक bcm_setup_sleep(काष्ठा hci_uart *hu) अणु वापस 0; पूर्ण
#पूर्ण_अगर

अटल पूर्णांक bcm_set_diag(काष्ठा hci_dev *hdev, bool enable)
अणु
	काष्ठा hci_uart *hu = hci_get_drvdata(hdev);
	काष्ठा bcm_data *bcm = hu->priv;
	काष्ठा sk_buff *skb;

	अगर (!test_bit(HCI_RUNNING, &hdev->flags))
		वापस -ENETDOWN;

	skb = bt_skb_alloc(3, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_u8(skb, BCM_LM_DIAG_PKT);
	skb_put_u8(skb, 0xf0);
	skb_put_u8(skb, enable);

	skb_queue_tail(&bcm->txq, skb);
	hci_uart_tx_wakeup(hu);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_खोलो(काष्ठा hci_uart *hu)
अणु
	काष्ठा bcm_data *bcm;
	काष्ठा list_head *p;
	पूर्णांक err;

	bt_dev_dbg(hu->hdev, "hu %p", hu);

	अगर (!hci_uart_has_flow_control(hu))
		वापस -EOPNOTSUPP;

	bcm = kzalloc(माप(*bcm), GFP_KERNEL);
	अगर (!bcm)
		वापस -ENOMEM;

	skb_queue_head_init(&bcm->txq);

	hu->priv = bcm;

	mutex_lock(&bcm_device_lock);

	अगर (hu->serdev) अणु
		bcm->dev = serdev_device_get_drvdata(hu->serdev);
		जाओ out;
	पूर्ण

	अगर (!hu->tty->dev)
		जाओ out;

	list_क्रम_each(p, &bcm_device_list) अणु
		काष्ठा bcm_device *dev = list_entry(p, काष्ठा bcm_device, list);

		/* Retrieve saved bcm_device based on parent of the
		 * platक्रमm device (saved during device probe) and
		 * parent of tty device used by hci_uart
		 */
		अगर (hu->tty->dev->parent == dev->dev->parent) अणु
			bcm->dev = dev;
#अगर_घोषित CONFIG_PM
			dev->hu = hu;
#पूर्ण_अगर
			अवरोध;
		पूर्ण
	पूर्ण

out:
	अगर (bcm->dev) अणु
		अगर (bcm->dev->drive_rts_on_खोलो)
			hci_uart_set_flow_control(hu, true);

		hu->init_speed = bcm->dev->init_speed;

		/* If oper_speed is set, ldisc/serdev will set the baudrate
		 * beक्रमe calling setup()
		 */
		अगर (!bcm->dev->no_early_set_baudrate)
			hu->oper_speed = bcm->dev->oper_speed;

		err = bcm_gpio_set_घातer(bcm->dev, true);

		अगर (bcm->dev->drive_rts_on_खोलो)
			hci_uart_set_flow_control(hu, false);

		अगर (err)
			जाओ err_unset_hu;
	पूर्ण

	mutex_unlock(&bcm_device_lock);
	वापस 0;

err_unset_hu:
#अगर_घोषित CONFIG_PM
	अगर (!hu->serdev)
		bcm->dev->hu = शून्य;
#पूर्ण_अगर
	mutex_unlock(&bcm_device_lock);
	hu->priv = शून्य;
	kमुक्त(bcm);
	वापस err;
पूर्ण

अटल पूर्णांक bcm_बंद(काष्ठा hci_uart *hu)
अणु
	काष्ठा bcm_data *bcm = hu->priv;
	काष्ठा bcm_device *bdev = शून्य;
	पूर्णांक err;

	bt_dev_dbg(hu->hdev, "hu %p", hu);

	/* Protect bcm->dev against removal of the device or driver */
	mutex_lock(&bcm_device_lock);

	अगर (hu->serdev) अणु
		bdev = serdev_device_get_drvdata(hu->serdev);
	पूर्ण अन्यथा अगर (bcm_device_exists(bcm->dev)) अणु
		bdev = bcm->dev;
#अगर_घोषित CONFIG_PM
		bdev->hu = शून्य;
#पूर्ण_अगर
	पूर्ण

	अगर (bdev) अणु
		अगर (IS_ENABLED(CONFIG_PM) && bdev->irq_acquired) अणु
			devm_मुक्त_irq(bdev->dev, bdev->irq, bdev);
			device_init_wakeup(bdev->dev, false);
			pm_runसमय_disable(bdev->dev);
		पूर्ण

		err = bcm_gpio_set_घातer(bdev, false);
		अगर (err)
			bt_dev_err(hu->hdev, "Failed to power down");
		अन्यथा
			pm_runसमय_set_suspended(bdev->dev);
	पूर्ण
	mutex_unlock(&bcm_device_lock);

	skb_queue_purge(&bcm->txq);
	kमुक्त_skb(bcm->rx_skb);
	kमुक्त(bcm);

	hu->priv = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक bcm_flush(काष्ठा hci_uart *hu)
अणु
	काष्ठा bcm_data *bcm = hu->priv;

	bt_dev_dbg(hu->hdev, "hu %p", hu);

	skb_queue_purge(&bcm->txq);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_setup(काष्ठा hci_uart *hu)
अणु
	काष्ठा bcm_data *bcm = hu->priv;
	bool fw_load_करोne = false;
	अचिन्हित पूर्णांक speed;
	पूर्णांक err;

	bt_dev_dbg(hu->hdev, "hu %p", hu);

	hu->hdev->set_diag = bcm_set_diag;
	hu->hdev->set_bdaddr = btbcm_set_bdaddr;

	err = btbcm_initialize(hu->hdev, &fw_load_करोne);
	अगर (err)
		वापस err;

	अगर (!fw_load_करोne)
		वापस 0;

	/* Init speed अगर any */
	अगर (hu->init_speed)
		speed = hu->init_speed;
	अन्यथा अगर (hu->proto->init_speed)
		speed = hu->proto->init_speed;
	अन्यथा
		speed = 0;

	अगर (speed)
		host_set_baudrate(hu, speed);

	/* Operational speed अगर any */
	अगर (hu->oper_speed)
		speed = hu->oper_speed;
	अन्यथा अगर (bcm->dev && bcm->dev->oper_speed)
		speed = bcm->dev->oper_speed;
	अन्यथा अगर (hu->proto->oper_speed)
		speed = hu->proto->oper_speed;
	अन्यथा
		speed = 0;

	अगर (speed) अणु
		err = bcm_set_baudrate(hu, speed);
		अगर (!err)
			host_set_baudrate(hu, speed);
	पूर्ण

	/* PCM parameters अगर provided */
	अगर (bcm->dev && bcm->dev->pcm_पूर्णांक_params[0] != 0xff) अणु
		काष्ठा bcm_set_pcm_पूर्णांक_params params;

		btbcm_पढ़ो_pcm_पूर्णांक_params(hu->hdev, &params);

		स_नकल(&params, bcm->dev->pcm_पूर्णांक_params, 5);
		btbcm_ग_लिखो_pcm_पूर्णांक_params(hu->hdev, &params);
	पूर्ण

	err = btbcm_finalize(hu->hdev, &fw_load_करोne);
	अगर (err)
		वापस err;

	/* Some devices ship with the controller शेष address.
	 * Allow the bootloader to set a valid address through the
	 * device tree.
	 */
	set_bit(HCI_QUIRK_USE_BDADDR_PROPERTY, &hu->hdev->quirks);

	अगर (!bcm_request_irq(bcm))
		err = bcm_setup_sleep(hu);

	वापस err;
पूर्ण

#घोषणा BCM_RECV_LM_DIAG \
	.type = BCM_LM_DIAG_PKT, \
	.hlen = BCM_LM_DIAG_SIZE, \
	.loff = 0, \
	.lsize = 0, \
	.maxlen = BCM_LM_DIAG_SIZE

#घोषणा BCM_RECV_शून्य \
	.type = BCM_शून्य_PKT, \
	.hlen = BCM_शून्य_SIZE, \
	.loff = 0, \
	.lsize = 0, \
	.maxlen = BCM_शून्य_SIZE

#घोषणा BCM_RECV_TYPE49 \
	.type = BCM_TYPE49_PKT, \
	.hlen = BCM_TYPE49_SIZE, \
	.loff = 0, \
	.lsize = 0, \
	.maxlen = BCM_TYPE49_SIZE

#घोषणा BCM_RECV_TYPE52 \
	.type = BCM_TYPE52_PKT, \
	.hlen = BCM_TYPE52_SIZE, \
	.loff = 0, \
	.lsize = 0, \
	.maxlen = BCM_TYPE52_SIZE

अटल स्थिर काष्ठा h4_recv_pkt bcm_recv_pkts[] = अणु
	अणु H4_RECV_ACL,      .recv = hci_recv_frame पूर्ण,
	अणु H4_RECV_SCO,      .recv = hci_recv_frame पूर्ण,
	अणु H4_RECV_EVENT,    .recv = hci_recv_frame पूर्ण,
	अणु H4_RECV_ISO,      .recv = hci_recv_frame पूर्ण,
	अणु BCM_RECV_LM_DIAG, .recv = hci_recv_diag  पूर्ण,
	अणु BCM_RECV_शून्य,    .recv = hci_recv_diag  पूर्ण,
	अणु BCM_RECV_TYPE49,  .recv = hci_recv_diag  पूर्ण,
	अणु BCM_RECV_TYPE52,  .recv = hci_recv_diag  पूर्ण,
पूर्ण;

अटल पूर्णांक bcm_recv(काष्ठा hci_uart *hu, स्थिर व्योम *data, पूर्णांक count)
अणु
	काष्ठा bcm_data *bcm = hu->priv;

	अगर (!test_bit(HCI_UART_REGISTERED, &hu->flags))
		वापस -EUNATCH;

	bcm->rx_skb = h4_recv_buf(hu->hdev, bcm->rx_skb, data, count,
				  bcm_recv_pkts, ARRAY_SIZE(bcm_recv_pkts));
	अगर (IS_ERR(bcm->rx_skb)) अणु
		पूर्णांक err = PTR_ERR(bcm->rx_skb);
		bt_dev_err(hu->hdev, "Frame reassembly failed (%d)", err);
		bcm->rx_skb = शून्य;
		वापस err;
	पूर्ण अन्यथा अगर (!bcm->rx_skb) अणु
		/* Delay स्वतः-suspend when receiving completed packet */
		mutex_lock(&bcm_device_lock);
		अगर (bcm->dev && bcm_device_exists(bcm->dev)) अणु
			pm_runसमय_get(bcm->dev->dev);
			pm_runसमय_mark_last_busy(bcm->dev->dev);
			pm_runसमय_put_स्वतःsuspend(bcm->dev->dev);
		पूर्ण
		mutex_unlock(&bcm_device_lock);
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक bcm_enqueue(काष्ठा hci_uart *hu, काष्ठा sk_buff *skb)
अणु
	काष्ठा bcm_data *bcm = hu->priv;

	bt_dev_dbg(hu->hdev, "hu %p skb %p", hu, skb);

	/* Prepend skb with frame type */
	स_नकल(skb_push(skb, 1), &hci_skb_pkt_type(skb), 1);
	skb_queue_tail(&bcm->txq, skb);

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *bcm_dequeue(काष्ठा hci_uart *hu)
अणु
	काष्ठा bcm_data *bcm = hu->priv;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा bcm_device *bdev = शून्य;

	mutex_lock(&bcm_device_lock);

	अगर (bcm_device_exists(bcm->dev)) अणु
		bdev = bcm->dev;
		pm_runसमय_get_sync(bdev->dev);
		/* Shall be resumed here */
	पूर्ण

	skb = skb_dequeue(&bcm->txq);

	अगर (bdev) अणु
		pm_runसमय_mark_last_busy(bdev->dev);
		pm_runसमय_put_स्वतःsuspend(bdev->dev);
	पूर्ण

	mutex_unlock(&bcm_device_lock);

	वापस skb;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक bcm_suspend_device(काष्ठा device *dev)
अणु
	काष्ठा bcm_device *bdev = dev_get_drvdata(dev);
	पूर्णांक err;

	bt_dev_dbg(bdev, "");

	अगर (!bdev->is_suspended && bdev->hu) अणु
		hci_uart_set_flow_control(bdev->hu, true);

		/* Once this वापसs, driver suspends BT via GPIO */
		bdev->is_suspended = true;
	पूर्ण

	/* Suspend the device */
	err = bdev->set_device_wakeup(bdev, false);
	अगर (err) अणु
		अगर (bdev->is_suspended && bdev->hu) अणु
			bdev->is_suspended = false;
			hci_uart_set_flow_control(bdev->hu, false);
		पूर्ण
		वापस -EBUSY;
	पूर्ण

	bt_dev_dbg(bdev, "suspend, delaying 15 ms");
	msleep(15);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_resume_device(काष्ठा device *dev)
अणु
	काष्ठा bcm_device *bdev = dev_get_drvdata(dev);
	पूर्णांक err;

	bt_dev_dbg(bdev, "");

	err = bdev->set_device_wakeup(bdev, true);
	अगर (err) अणु
		dev_err(dev, "Failed to power up\n");
		वापस err;
	पूर्ण

	bt_dev_dbg(bdev, "resume, delaying 15 ms");
	msleep(15);

	/* When this executes, the device has woken up alपढ़ोy */
	अगर (bdev->is_suspended && bdev->hu) अणु
		bdev->is_suspended = false;

		hci_uart_set_flow_control(bdev->hu, false);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
/* suspend callback */
अटल पूर्णांक bcm_suspend(काष्ठा device *dev)
अणु
	काष्ठा bcm_device *bdev = dev_get_drvdata(dev);
	पूर्णांक error;

	bt_dev_dbg(bdev, "suspend: is_suspended %d", bdev->is_suspended);

	/*
	 * When used with a device instantiated as platक्रमm_device, bcm_suspend
	 * can be called at any समय as दीर्घ as the platक्रमm device is bound,
	 * so it should use bcm_device_lock to protect access to hci_uart
	 * and device_wake-up GPIO.
	 */
	mutex_lock(&bcm_device_lock);

	अगर (!bdev->hu)
		जाओ unlock;

	अगर (pm_runसमय_active(dev))
		bcm_suspend_device(dev);

	अगर (device_may_wakeup(dev) && bdev->irq > 0) अणु
		error = enable_irq_wake(bdev->irq);
		अगर (!error)
			bt_dev_dbg(bdev, "BCM irq: enabled");
	पूर्ण

unlock:
	mutex_unlock(&bcm_device_lock);

	वापस 0;
पूर्ण

/* resume callback */
अटल पूर्णांक bcm_resume(काष्ठा device *dev)
अणु
	काष्ठा bcm_device *bdev = dev_get_drvdata(dev);
	पूर्णांक err = 0;

	bt_dev_dbg(bdev, "resume: is_suspended %d", bdev->is_suspended);

	/*
	 * When used with a device instantiated as platक्रमm_device, bcm_resume
	 * can be called at any समय as दीर्घ as platक्रमm device is bound,
	 * so it should use bcm_device_lock to protect access to hci_uart
	 * and device_wake-up GPIO.
	 */
	mutex_lock(&bcm_device_lock);

	अगर (!bdev->hu)
		जाओ unlock;

	अगर (device_may_wakeup(dev) && bdev->irq > 0) अणु
		disable_irq_wake(bdev->irq);
		bt_dev_dbg(bdev, "BCM irq: disabled");
	पूर्ण

	err = bcm_resume_device(dev);

unlock:
	mutex_unlock(&bcm_device_lock);

	अगर (!err) अणु
		pm_runसमय_disable(dev);
		pm_runसमय_set_active(dev);
		pm_runसमय_enable(dev);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

/* Some firmware reports an IRQ which करोes not work (wrong pin in fw table?) */
अटल स्थिर काष्ठा dmi_प्रणाली_id bcm_broken_irq_dmi_table[] = अणु
	अणु
		.ident = "Meegopad T08",
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR,
					"To be filled by OEM."),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "T3 MRD"),
			DMI_EXACT_MATCH(DMI_BOARD_VERSION, "V1.1"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_gpio_params first_gpio = अणु 0, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params second_gpio = अणु 1, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params third_gpio = अणु 2, 0, false पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping acpi_bcm_पूर्णांक_last_gpios[] = अणु
	अणु "device-wakeup-gpios", &first_gpio, 1 पूर्ण,
	अणु "shutdown-gpios", &second_gpio, 1 पूर्ण,
	अणु "host-wakeup-gpios", &third_gpio, 1 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping acpi_bcm_पूर्णांक_first_gpios[] = अणु
	अणु "host-wakeup-gpios", &first_gpio, 1 पूर्ण,
	अणु "device-wakeup-gpios", &second_gpio, 1 पूर्ण,
	अणु "shutdown-gpios", &third_gpio, 1 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक bcm_resource(काष्ठा acpi_resource *ares, व्योम *data)
अणु
	काष्ठा bcm_device *dev = data;
	काष्ठा acpi_resource_extended_irq *irq;
	काष्ठा acpi_resource_gpio *gpio;
	काष्ठा acpi_resource_uart_serialbus *sb;

	चयन (ares->type) अणु
	हाल ACPI_RESOURCE_TYPE_EXTENDED_IRQ:
		irq = &ares->data.extended_irq;
		अगर (irq->polarity != ACPI_ACTIVE_LOW)
			dev_info(dev->dev, "ACPI Interrupt resource is active-high, this is usually wrong, treating the IRQ as active-low\n");
		dev->irq_active_low = true;
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_GPIO:
		gpio = &ares->data.gpio;
		अगर (gpio->connection_type == ACPI_RESOURCE_GPIO_TYPE_INT) अणु
			dev->gpio_पूर्णांक_idx = dev->gpio_count;
			dev->irq_active_low = gpio->polarity == ACPI_ACTIVE_LOW;
		पूर्ण
		dev->gpio_count++;
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_SERIAL_BUS:
		sb = &ares->data.uart_serial_bus;
		अगर (sb->type == ACPI_RESOURCE_SERIAL_TYPE_UART) अणु
			dev->init_speed = sb->शेष_baud_rate;
			dev->oper_speed = 4000000;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_apple_set_device_wakeup(काष्ठा bcm_device *dev, bool awake)
अणु
	अगर (ACPI_FAILURE(acpi_execute_simple_method(dev->btlp, शून्य, !awake)))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_apple_set_shutकरोwn(काष्ठा bcm_device *dev, bool घातered)
अणु
	अगर (ACPI_FAILURE(acpi_evaluate_object(घातered ? dev->btpu : dev->btpd,
					      शून्य, शून्य, शून्य)))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_apple_get_resources(काष्ठा bcm_device *dev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev->dev);
	स्थिर जोड़ acpi_object *obj;

	अगर (!adev ||
	    ACPI_FAILURE(acpi_get_handle(adev->handle, "BTLP", &dev->btlp)) ||
	    ACPI_FAILURE(acpi_get_handle(adev->handle, "BTPU", &dev->btpu)) ||
	    ACPI_FAILURE(acpi_get_handle(adev->handle, "BTPD", &dev->btpd)))
		वापस -ENODEV;

	अगर (!acpi_dev_get_property(adev, "baud", ACPI_TYPE_BUFFER, &obj) &&
	    obj->buffer.length == 8)
		dev->init_speed = *(u64 *)obj->buffer.poपूर्णांकer;

	dev->set_device_wakeup = bcm_apple_set_device_wakeup;
	dev->set_shutकरोwn = bcm_apple_set_shutकरोwn;

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक bcm_apple_get_resources(काष्ठा bcm_device *dev)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI */

अटल पूर्णांक bcm_gpio_set_device_wakeup(काष्ठा bcm_device *dev, bool awake)
अणु
	gpiod_set_value_cansleep(dev->device_wakeup, awake);
	वापस 0;
पूर्ण

अटल पूर्णांक bcm_gpio_set_shutकरोwn(काष्ठा bcm_device *dev, bool घातered)
अणु
	gpiod_set_value_cansleep(dev->shutकरोwn, घातered);
	अगर (dev->reset)
		/*
		 * The reset line is निश्चितed on घातerकरोwn and deनिश्चितed
		 * on घातeron so the inverse of घातered is used. Notice
		 * that the GPIO line BT_RST_N needs to be specअगरied as
		 * active low in the device tree or similar प्रणाली
		 * description.
		 */
		gpiod_set_value_cansleep(dev->reset, !घातered);
	वापस 0;
पूर्ण

/* Try a bunch of names क्रम TXCO */
अटल काष्ठा clk *bcm_get_txco(काष्ठा device *dev)
अणु
	काष्ठा clk *clk;

	/* New explicit name */
	clk = devm_clk_get(dev, "txco");
	अगर (!IS_ERR(clk) || PTR_ERR(clk) == -EPROBE_DEFER)
		वापस clk;

	/* Deprecated name */
	clk = devm_clk_get(dev, "extclk");
	अगर (!IS_ERR(clk) || PTR_ERR(clk) == -EPROBE_DEFER)
		वापस clk;

	/* Original code used no name at all */
	वापस devm_clk_get(dev, शून्य);
पूर्ण

अटल पूर्णांक bcm_get_resources(काष्ठा bcm_device *dev)
अणु
	स्थिर काष्ठा dmi_प्रणाली_id *dmi_id;
	पूर्णांक err;

	dev->name = dev_name(dev->dev);

	अगर (x86_apple_machine && !bcm_apple_get_resources(dev))
		वापस 0;

	dev->txco_clk = bcm_get_txco(dev->dev);

	/* Handle deferred probing */
	अगर (dev->txco_clk == ERR_PTR(-EPROBE_DEFER))
		वापस PTR_ERR(dev->txco_clk);

	/* Ignore all other errors as beक्रमe */
	अगर (IS_ERR(dev->txco_clk))
		dev->txco_clk = शून्य;

	dev->lpo_clk = devm_clk_get(dev->dev, "lpo");
	अगर (dev->lpo_clk == ERR_PTR(-EPROBE_DEFER))
		वापस PTR_ERR(dev->lpo_clk);

	अगर (IS_ERR(dev->lpo_clk))
		dev->lpo_clk = शून्य;

	/* Check अगर we accidentally fetched the lpo घड़ी twice */
	अगर (dev->lpo_clk && clk_is_match(dev->lpo_clk, dev->txco_clk)) अणु
		devm_clk_put(dev->dev, dev->txco_clk);
		dev->txco_clk = शून्य;
	पूर्ण

	dev->device_wakeup = devm_gpiod_get_optional(dev->dev, "device-wakeup",
						     GPIOD_OUT_LOW);
	अगर (IS_ERR(dev->device_wakeup))
		वापस PTR_ERR(dev->device_wakeup);

	dev->shutकरोwn = devm_gpiod_get_optional(dev->dev, "shutdown",
						GPIOD_OUT_LOW);
	अगर (IS_ERR(dev->shutकरोwn))
		वापस PTR_ERR(dev->shutकरोwn);

	dev->reset = devm_gpiod_get_optional(dev->dev, "reset",
					     GPIOD_OUT_LOW);
	अगर (IS_ERR(dev->reset))
		वापस PTR_ERR(dev->reset);

	dev->set_device_wakeup = bcm_gpio_set_device_wakeup;
	dev->set_shutकरोwn = bcm_gpio_set_shutकरोwn;

	dev->supplies[0].supply = "vbat";
	dev->supplies[1].supply = "vddio";
	err = devm_regulator_bulk_get(dev->dev, BCM_NUM_SUPPLIES,
				      dev->supplies);
	अगर (err)
		वापस err;

	/* IRQ can be declared in ACPI table as Interrupt or GpioInt */
	अगर (dev->irq <= 0) अणु
		काष्ठा gpio_desc *gpio;

		gpio = devm_gpiod_get_optional(dev->dev, "host-wakeup",
					       GPIOD_IN);
		अगर (IS_ERR(gpio))
			वापस PTR_ERR(gpio);

		dev->irq = gpiod_to_irq(gpio);
	पूर्ण

	dmi_id = dmi_first_match(bcm_broken_irq_dmi_table);
	अगर (dmi_id) अणु
		dev_info(dev->dev, "%s: Has a broken IRQ config, disabling IRQ support / runtime-pm\n",
			 dmi_id->ident);
		dev->irq = 0;
	पूर्ण

	dev_dbg(dev->dev, "BCM irq: %d\n", dev->irq);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल पूर्णांक bcm_acpi_probe(काष्ठा bcm_device *dev)
अणु
	LIST_HEAD(resources);
	स्थिर काष्ठा acpi_gpio_mapping *gpio_mapping = acpi_bcm_पूर्णांक_last_gpios;
	काष्ठा resource_entry *entry;
	पूर्णांक ret;

	/* Retrieve UART ACPI info */
	dev->gpio_पूर्णांक_idx = -1;
	ret = acpi_dev_get_resources(ACPI_COMPANION(dev->dev),
				     &resources, bcm_resource, dev);
	अगर (ret < 0)
		वापस ret;

	resource_list_क्रम_each_entry(entry, &resources) अणु
		अगर (resource_type(entry->res) == IORESOURCE_IRQ) अणु
			dev->irq = entry->res->start;
			अवरोध;
		पूर्ण
	पूर्ण
	acpi_dev_मुक्त_resource_list(&resources);

	/* If the DSDT uses an Interrupt resource क्रम the IRQ, then there are
	 * only 2 GPIO resources, we use the irq-last mapping क्रम this, since
	 * we alपढ़ोy have an irq the 3th / last mapping will not be used.
	 */
	अगर (dev->irq)
		gpio_mapping = acpi_bcm_पूर्णांक_last_gpios;
	अन्यथा अगर (dev->gpio_पूर्णांक_idx == 0)
		gpio_mapping = acpi_bcm_पूर्णांक_first_gpios;
	अन्यथा अगर (dev->gpio_पूर्णांक_idx == 2)
		gpio_mapping = acpi_bcm_पूर्णांक_last_gpios;
	अन्यथा
		dev_warn(dev->dev, "Unexpected ACPI gpio_int_idx: %d\n",
			 dev->gpio_पूर्णांक_idx);

	/* Warn अगर our expectations are not met. */
	अगर (dev->gpio_count != (dev->irq ? 2 : 3))
		dev_warn(dev->dev, "Unexpected number of ACPI GPIOs: %d\n",
			 dev->gpio_count);

	ret = devm_acpi_dev_add_driver_gpios(dev->dev, gpio_mapping);
	अगर (ret)
		वापस ret;

	अगर (irq_polarity != -1) अणु
		dev->irq_active_low = irq_polarity;
		dev_warn(dev->dev, "Overwriting IRQ polarity to active %s by module-param\n",
			 dev->irq_active_low ? "low" : "high");
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक bcm_acpi_probe(काष्ठा bcm_device *dev)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI */

अटल पूर्णांक bcm_of_probe(काष्ठा bcm_device *bdev)
अणु
	device_property_पढ़ो_u32(bdev->dev, "max-speed", &bdev->oper_speed);
	device_property_पढ़ो_u8_array(bdev->dev, "brcm,bt-pcm-int-params",
				      bdev->pcm_पूर्णांक_params, 5);
	bdev->irq = of_irq_get_byname(bdev->dev->of_node, "host-wakeup");
	bdev->irq_active_low = irq_get_trigger_type(bdev->irq)
			     & (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_LEVEL_LOW);
	वापस 0;
पूर्ण

अटल पूर्णांक bcm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm_device *dev;
	पूर्णांक ret;

	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	dev->dev = &pdev->dev;
	dev->irq = platक्रमm_get_irq(pdev, 0);

	/* Initialize routing field to an unused value */
	dev->pcm_पूर्णांक_params[0] = 0xff;

	अगर (has_acpi_companion(&pdev->dev)) अणु
		ret = bcm_acpi_probe(dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = bcm_get_resources(dev);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, dev);

	dev_info(&pdev->dev, "%s device registered.\n", dev->name);

	/* Place this instance on the device list */
	mutex_lock(&bcm_device_lock);
	list_add_tail(&dev->list, &bcm_device_list);
	mutex_unlock(&bcm_device_lock);

	ret = bcm_gpio_set_घातer(dev, false);
	अगर (ret)
		dev_err(&pdev->dev, "Failed to power down\n");

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm_device *dev = platक्रमm_get_drvdata(pdev);

	mutex_lock(&bcm_device_lock);
	list_del(&dev->list);
	mutex_unlock(&bcm_device_lock);

	dev_info(&pdev->dev, "%s device unregistered.\n", dev->name);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hci_uart_proto bcm_proto = अणु
	.id		= HCI_UART_BCM,
	.name		= "Broadcom",
	.manufacturer	= 15,
	.init_speed	= 115200,
	.खोलो		= bcm_खोलो,
	.बंद		= bcm_बंद,
	.flush		= bcm_flush,
	.setup		= bcm_setup,
	.set_baudrate	= bcm_set_baudrate,
	.recv		= bcm_recv,
	.enqueue	= bcm_enqueue,
	.dequeue	= bcm_dequeue,
पूर्ण;

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id bcm_acpi_match[] = अणु
	अणु "BCM2E00" पूर्ण,
	अणु "BCM2E01" पूर्ण,
	अणु "BCM2E02" पूर्ण,
	अणु "BCM2E03" पूर्ण,
	अणु "BCM2E04" पूर्ण,
	अणु "BCM2E05" पूर्ण,
	अणु "BCM2E06" पूर्ण,
	अणु "BCM2E07" पूर्ण,
	अणु "BCM2E08" पूर्ण,
	अणु "BCM2E09" पूर्ण,
	अणु "BCM2E0A" पूर्ण,
	अणु "BCM2E0B" पूर्ण,
	अणु "BCM2E0C" पूर्ण,
	अणु "BCM2E0D" पूर्ण,
	अणु "BCM2E0E" पूर्ण,
	अणु "BCM2E0F" पूर्ण,
	अणु "BCM2E10" पूर्ण,
	अणु "BCM2E11" पूर्ण,
	अणु "BCM2E12" पूर्ण,
	अणु "BCM2E13" पूर्ण,
	अणु "BCM2E14" पूर्ण,
	अणु "BCM2E15" पूर्ण,
	अणु "BCM2E16" पूर्ण,
	अणु "BCM2E17" पूर्ण,
	अणु "BCM2E18" पूर्ण,
	अणु "BCM2E19" पूर्ण,
	अणु "BCM2E1A" पूर्ण,
	अणु "BCM2E1B" पूर्ण,
	अणु "BCM2E1C" पूर्ण,
	अणु "BCM2E1D" पूर्ण,
	अणु "BCM2E1F" पूर्ण,
	अणु "BCM2E20" पूर्ण,
	अणु "BCM2E21" पूर्ण,
	अणु "BCM2E22" पूर्ण,
	अणु "BCM2E23" पूर्ण,
	अणु "BCM2E24" पूर्ण,
	अणु "BCM2E25" पूर्ण,
	अणु "BCM2E26" पूर्ण,
	अणु "BCM2E27" पूर्ण,
	अणु "BCM2E28" पूर्ण,
	अणु "BCM2E29" पूर्ण,
	अणु "BCM2E2A" पूर्ण,
	अणु "BCM2E2B" पूर्ण,
	अणु "BCM2E2C" पूर्ण,
	अणु "BCM2E2D" पूर्ण,
	अणु "BCM2E2E" पूर्ण,
	अणु "BCM2E2F" पूर्ण,
	अणु "BCM2E30" पूर्ण,
	अणु "BCM2E31" पूर्ण,
	अणु "BCM2E32" पूर्ण,
	अणु "BCM2E33" पूर्ण,
	अणु "BCM2E34" पूर्ण,
	अणु "BCM2E35" पूर्ण,
	अणु "BCM2E36" पूर्ण,
	अणु "BCM2E37" पूर्ण,
	अणु "BCM2E38" पूर्ण,
	अणु "BCM2E39" पूर्ण,
	अणु "BCM2E3A" पूर्ण,
	अणु "BCM2E3B" पूर्ण,
	अणु "BCM2E3C" पूर्ण,
	अणु "BCM2E3D" पूर्ण,
	अणु "BCM2E3E" पूर्ण,
	अणु "BCM2E3F" पूर्ण,
	अणु "BCM2E40" पूर्ण,
	अणु "BCM2E41" पूर्ण,
	अणु "BCM2E42" पूर्ण,
	अणु "BCM2E43" पूर्ण,
	अणु "BCM2E44" पूर्ण,
	अणु "BCM2E45" पूर्ण,
	अणु "BCM2E46" पूर्ण,
	अणु "BCM2E47" पूर्ण,
	अणु "BCM2E48" पूर्ण,
	अणु "BCM2E49" पूर्ण,
	अणु "BCM2E4A" पूर्ण,
	अणु "BCM2E4B" पूर्ण,
	अणु "BCM2E4C" पूर्ण,
	अणु "BCM2E4D" पूर्ण,
	अणु "BCM2E4E" पूर्ण,
	अणु "BCM2E4F" पूर्ण,
	अणु "BCM2E50" पूर्ण,
	अणु "BCM2E51" पूर्ण,
	अणु "BCM2E52" पूर्ण,
	अणु "BCM2E53" पूर्ण,
	अणु "BCM2E54" पूर्ण,
	अणु "BCM2E55" पूर्ण,
	अणु "BCM2E56" पूर्ण,
	अणु "BCM2E57" पूर्ण,
	अणु "BCM2E58" पूर्ण,
	अणु "BCM2E59" पूर्ण,
	अणु "BCM2E5A" पूर्ण,
	अणु "BCM2E5B" पूर्ण,
	अणु "BCM2E5C" पूर्ण,
	अणु "BCM2E5D" पूर्ण,
	अणु "BCM2E5E" पूर्ण,
	अणु "BCM2E5F" पूर्ण,
	अणु "BCM2E60" पूर्ण,
	अणु "BCM2E61" पूर्ण,
	अणु "BCM2E62" पूर्ण,
	अणु "BCM2E63" पूर्ण,
	अणु "BCM2E64" पूर्ण,
	अणु "BCM2E65" पूर्ण,
	अणु "BCM2E66" पूर्ण,
	अणु "BCM2E67" पूर्ण,
	अणु "BCM2E68" पूर्ण,
	अणु "BCM2E69" पूर्ण,
	अणु "BCM2E6B" पूर्ण,
	अणु "BCM2E6D" पूर्ण,
	अणु "BCM2E6E" पूर्ण,
	अणु "BCM2E6F" पूर्ण,
	अणु "BCM2E70" पूर्ण,
	अणु "BCM2E71" पूर्ण,
	अणु "BCM2E72" पूर्ण,
	अणु "BCM2E73" पूर्ण,
	अणु "BCM2E74" पूर्ण,
	अणु "BCM2E75" पूर्ण,
	अणु "BCM2E76" पूर्ण,
	अणु "BCM2E77" पूर्ण,
	अणु "BCM2E78" पूर्ण,
	अणु "BCM2E79" पूर्ण,
	अणु "BCM2E7A" पूर्ण,
	अणु "BCM2E7B" पूर्ण,
	अणु "BCM2E7C" पूर्ण,
	अणु "BCM2E7D" पूर्ण,
	अणु "BCM2E7E" पूर्ण,
	अणु "BCM2E7F" पूर्ण,
	अणु "BCM2E80" पूर्ण,
	अणु "BCM2E81" पूर्ण,
	अणु "BCM2E82" पूर्ण,
	अणु "BCM2E83" पूर्ण,
	अणु "BCM2E84" पूर्ण,
	अणु "BCM2E85" पूर्ण,
	अणु "BCM2E86" पूर्ण,
	अणु "BCM2E87" पूर्ण,
	अणु "BCM2E88" पूर्ण,
	अणु "BCM2E89" पूर्ण,
	अणु "BCM2E8A" पूर्ण,
	अणु "BCM2E8B" पूर्ण,
	अणु "BCM2E8C" पूर्ण,
	अणु "BCM2E8D" पूर्ण,
	अणु "BCM2E8E" पूर्ण,
	अणु "BCM2E90" पूर्ण,
	अणु "BCM2E92" पूर्ण,
	अणु "BCM2E93" पूर्ण,
	अणु "BCM2E94" पूर्ण,
	अणु "BCM2E95" पूर्ण,
	अणु "BCM2E96" पूर्ण,
	अणु "BCM2E97" पूर्ण,
	अणु "BCM2E98" पूर्ण,
	अणु "BCM2E99" पूर्ण,
	अणु "BCM2E9A" पूर्ण,
	अणु "BCM2E9B" पूर्ण,
	अणु "BCM2E9C" पूर्ण,
	अणु "BCM2E9D" पूर्ण,
	अणु "BCM2EA0" पूर्ण,
	अणु "BCM2EA1" पूर्ण,
	अणु "BCM2EA2" पूर्ण,
	अणु "BCM2EA3" पूर्ण,
	अणु "BCM2EA4" पूर्ण,
	अणु "BCM2EA5" पूर्ण,
	अणु "BCM2EA6" पूर्ण,
	अणु "BCM2EA7" पूर्ण,
	अणु "BCM2EA8" पूर्ण,
	अणु "BCM2EA9" पूर्ण,
	अणु "BCM2EAA" पूर्ण,
	अणु "BCM2EAB" पूर्ण,
	अणु "BCM2EAC" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, bcm_acpi_match);
#पूर्ण_अगर

/* suspend and resume callbacks */
अटल स्थिर काष्ठा dev_pm_ops bcm_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(bcm_suspend, bcm_resume)
	SET_RUNTIME_PM_OPS(bcm_suspend_device, bcm_resume_device, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver bcm_driver = अणु
	.probe = bcm_probe,
	.हटाओ = bcm_हटाओ,
	.driver = अणु
		.name = "hci_bcm",
		.acpi_match_table = ACPI_PTR(bcm_acpi_match),
		.pm = &bcm_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक bcm_serdev_probe(काष्ठा serdev_device *serdev)
अणु
	काष्ठा bcm_device *bcmdev;
	स्थिर काष्ठा bcm_device_data *data;
	पूर्णांक err;

	bcmdev = devm_kzalloc(&serdev->dev, माप(*bcmdev), GFP_KERNEL);
	अगर (!bcmdev)
		वापस -ENOMEM;

	bcmdev->dev = &serdev->dev;
#अगर_घोषित CONFIG_PM
	bcmdev->hu = &bcmdev->serdev_hu;
#पूर्ण_अगर
	bcmdev->serdev_hu.serdev = serdev;
	serdev_device_set_drvdata(serdev, bcmdev);

	/* Initialize routing field to an unused value */
	bcmdev->pcm_पूर्णांक_params[0] = 0xff;

	अगर (has_acpi_companion(&serdev->dev))
		err = bcm_acpi_probe(bcmdev);
	अन्यथा
		err = bcm_of_probe(bcmdev);
	अगर (err)
		वापस err;

	err = bcm_get_resources(bcmdev);
	अगर (err)
		वापस err;

	अगर (!bcmdev->shutकरोwn) अणु
		dev_warn(&serdev->dev,
			 "No reset resource, using default baud rate\n");
		bcmdev->oper_speed = bcmdev->init_speed;
	पूर्ण

	err = bcm_gpio_set_घातer(bcmdev, false);
	अगर (err)
		dev_err(&serdev->dev, "Failed to power down\n");

	data = device_get_match_data(bcmdev->dev);
	अगर (data) अणु
		bcmdev->no_early_set_baudrate = data->no_early_set_baudrate;
		bcmdev->drive_rts_on_खोलो = data->drive_rts_on_खोलो;
	पूर्ण

	वापस hci_uart_रेजिस्टर_device(&bcmdev->serdev_hu, &bcm_proto);
पूर्ण

अटल व्योम bcm_serdev_हटाओ(काष्ठा serdev_device *serdev)
अणु
	काष्ठा bcm_device *bcmdev = serdev_device_get_drvdata(serdev);

	hci_uart_unरेजिस्टर_device(&bcmdev->serdev_hu);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल काष्ठा bcm_device_data bcm4354_device_data = अणु
	.no_early_set_baudrate = true,
पूर्ण;

अटल काष्ठा bcm_device_data bcm43438_device_data = अणु
	.drive_rts_on_खोलो = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id bcm_bluetooth_of_match[] = अणु
	अणु .compatible = "brcm,bcm20702a1" पूर्ण,
	अणु .compatible = "brcm,bcm4329-bt" पूर्ण,
	अणु .compatible = "brcm,bcm4330-bt" पूर्ण,
	अणु .compatible = "brcm,bcm4334-bt" पूर्ण,
	अणु .compatible = "brcm,bcm4345c5" पूर्ण,
	अणु .compatible = "brcm,bcm4330-bt" पूर्ण,
	अणु .compatible = "brcm,bcm43438-bt", .data = &bcm43438_device_data पूर्ण,
	अणु .compatible = "brcm,bcm43540-bt", .data = &bcm4354_device_data पूर्ण,
	अणु .compatible = "brcm,bcm4335a0" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm_bluetooth_of_match);
#पूर्ण_अगर

अटल काष्ठा serdev_device_driver bcm_serdev_driver = अणु
	.probe = bcm_serdev_probe,
	.हटाओ = bcm_serdev_हटाओ,
	.driver = अणु
		.name = "hci_uart_bcm",
		.of_match_table = of_match_ptr(bcm_bluetooth_of_match),
		.acpi_match_table = ACPI_PTR(bcm_acpi_match),
		.pm = &bcm_pm_ops,
	पूर्ण,
पूर्ण;

पूर्णांक __init bcm_init(व्योम)
अणु
	/* For now, we need to keep both platक्रमm device
	 * driver (ACPI generated) and serdev driver (DT).
	 */
	platक्रमm_driver_रेजिस्टर(&bcm_driver);
	serdev_device_driver_रेजिस्टर(&bcm_serdev_driver);

	वापस hci_uart_रेजिस्टर_proto(&bcm_proto);
पूर्ण

पूर्णांक __निकास bcm_deinit(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&bcm_driver);
	serdev_device_driver_unरेजिस्टर(&bcm_serdev_driver);

	वापस hci_uart_unरेजिस्टर_proto(&bcm_proto);
पूर्ण
