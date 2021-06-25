<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  Generic Bluetooth SDIO driver
 *
 *  Copyright (C) 2007  Cambridge Silicon Radio Ltd.
 *  Copyright (C) 2007  Marcel Holपंचांगann <marcel@holपंचांगann.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>

#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/sdio_ids.h>
#समावेश <linux/mmc/sdio_func.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#घोषणा VERSION "0.1"

अटल स्थिर काष्ठा sdio_device_id btsdio_table[] = अणु
	/* Generic Bluetooth Type-A SDIO device */
	अणु SDIO_DEVICE_CLASS(SDIO_CLASS_BT_A) पूर्ण,

	/* Generic Bluetooth Type-B SDIO device */
	अणु SDIO_DEVICE_CLASS(SDIO_CLASS_BT_B) पूर्ण,

	/* Generic Bluetooth AMP controller */
	अणु SDIO_DEVICE_CLASS(SDIO_CLASS_BT_AMP) पूर्ण,

	अणु पूर्ण	/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(sdio, btsdio_table);

काष्ठा btsdio_data अणु
	काष्ठा hci_dev   *hdev;
	काष्ठा sdio_func *func;

	काष्ठा work_काष्ठा work;

	काष्ठा sk_buff_head txq;
पूर्ण;

#घोषणा REG_RDAT     0x00	/* Receiver Data */
#घोषणा REG_TDAT     0x00	/* Transmitter Data */
#घोषणा REG_PC_RRT   0x10	/* Read Packet Control */
#घोषणा REG_PC_WRT   0x11	/* Write Packet Control */
#घोषणा REG_RTC_STAT 0x12	/* Retry Control Status */
#घोषणा REG_RTC_SET  0x12	/* Retry Control Set */
#घोषणा REG_INTRD    0x13	/* Interrupt Indication */
#घोषणा REG_CL_INTRD 0x13	/* Interrupt Clear */
#घोषणा REG_EN_INTRD 0x14	/* Interrupt Enable */
#घोषणा REG_MD_STAT  0x20	/* Bluetooth Mode Status */
#घोषणा REG_MD_SET   0x20	/* Bluetooth Mode Set */

अटल पूर्णांक btsdio_tx_packet(काष्ठा btsdio_data *data, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	BT_DBG("%s", data->hdev->name);

	/* Prepend Type-A header */
	skb_push(skb, 4);
	skb->data[0] = (skb->len & 0x0000ff);
	skb->data[1] = (skb->len & 0x00ff00) >> 8;
	skb->data[2] = (skb->len & 0xff0000) >> 16;
	skb->data[3] = hci_skb_pkt_type(skb);

	err = sdio_ग_लिखोsb(data->func, REG_TDAT, skb->data, skb->len);
	अगर (err < 0) अणु
		skb_pull(skb, 4);
		sdio_ग_लिखोb(data->func, 0x01, REG_PC_WRT, शून्य);
		वापस err;
	पूर्ण

	data->hdev->stat.byte_tx += skb->len;

	kमुक्त_skb(skb);

	वापस 0;
पूर्ण

अटल व्योम btsdio_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा btsdio_data *data = container_of(work, काष्ठा btsdio_data, work);
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	BT_DBG("%s", data->hdev->name);

	sdio_claim_host(data->func);

	जबतक ((skb = skb_dequeue(&data->txq))) अणु
		err = btsdio_tx_packet(data, skb);
		अगर (err < 0) अणु
			data->hdev->stat.err_tx++;
			skb_queue_head(&data->txq, skb);
			अवरोध;
		पूर्ण
	पूर्ण

	sdio_release_host(data->func);
पूर्ण

अटल पूर्णांक btsdio_rx_packet(काष्ठा btsdio_data *data)
अणु
	u8 hdr[4] __attribute__ ((aligned(4)));
	काष्ठा sk_buff *skb;
	पूर्णांक err, len;

	BT_DBG("%s", data->hdev->name);

	err = sdio_पढ़ोsb(data->func, hdr, REG_RDAT, 4);
	अगर (err < 0)
		वापस err;

	len = hdr[0] | (hdr[1] << 8) | (hdr[2] << 16);
	अगर (len < 4 || len > 65543)
		वापस -EILSEQ;

	skb = bt_skb_alloc(len - 4, GFP_KERNEL);
	अगर (!skb) अणु
		/* Out of memory. Prepare a पढ़ो retry and just
		 * वापस with the expectation that the next समय
		 * we're called we'll have more memory.
		 */
		वापस -ENOMEM;
	पूर्ण

	skb_put(skb, len - 4);

	err = sdio_पढ़ोsb(data->func, skb->data, REG_RDAT, len - 4);
	अगर (err < 0) अणु
		kमुक्त_skb(skb);
		वापस err;
	पूर्ण

	data->hdev->stat.byte_rx += len;

	चयन (hdr[3]) अणु
	हाल HCI_EVENT_PKT:
	हाल HCI_ACLDATA_PKT:
	हाल HCI_SCODATA_PKT:
	हाल HCI_ISODATA_PKT:
		hci_skb_pkt_type(skb) = hdr[3];
		err = hci_recv_frame(data->hdev, skb);
		अगर (err < 0)
			वापस err;
		अवरोध;
	शेष:
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	sdio_ग_लिखोb(data->func, 0x00, REG_PC_RRT, शून्य);

	वापस 0;
पूर्ण

अटल व्योम btsdio_पूर्णांकerrupt(काष्ठा sdio_func *func)
अणु
	काष्ठा btsdio_data *data = sdio_get_drvdata(func);
	पूर्णांक पूर्णांकrd;

	BT_DBG("%s", data->hdev->name);

	पूर्णांकrd = sdio_पढ़ोb(func, REG_INTRD, शून्य);
	अगर (पूर्णांकrd & 0x01) अणु
		sdio_ग_लिखोb(func, 0x01, REG_CL_INTRD, शून्य);

		अगर (btsdio_rx_packet(data) < 0) अणु
			data->hdev->stat.err_rx++;
			sdio_ग_लिखोb(data->func, 0x01, REG_PC_RRT, शून्य);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक btsdio_खोलो(काष्ठा hci_dev *hdev)
अणु
	काष्ठा btsdio_data *data = hci_get_drvdata(hdev);
	पूर्णांक err;

	BT_DBG("%s", hdev->name);

	sdio_claim_host(data->func);

	err = sdio_enable_func(data->func);
	अगर (err < 0)
		जाओ release;

	err = sdio_claim_irq(data->func, btsdio_पूर्णांकerrupt);
	अगर (err < 0) अणु
		sdio_disable_func(data->func);
		जाओ release;
	पूर्ण

	अगर (data->func->class == SDIO_CLASS_BT_B)
		sdio_ग_लिखोb(data->func, 0x00, REG_MD_SET, शून्य);

	sdio_ग_लिखोb(data->func, 0x01, REG_EN_INTRD, शून्य);

release:
	sdio_release_host(data->func);

	वापस err;
पूर्ण

अटल पूर्णांक btsdio_बंद(काष्ठा hci_dev *hdev)
अणु
	काष्ठा btsdio_data *data = hci_get_drvdata(hdev);

	BT_DBG("%s", hdev->name);

	sdio_claim_host(data->func);

	sdio_ग_लिखोb(data->func, 0x00, REG_EN_INTRD, शून्य);

	sdio_release_irq(data->func);
	sdio_disable_func(data->func);

	sdio_release_host(data->func);

	वापस 0;
पूर्ण

अटल पूर्णांक btsdio_flush(काष्ठा hci_dev *hdev)
अणु
	काष्ठा btsdio_data *data = hci_get_drvdata(hdev);

	BT_DBG("%s", hdev->name);

	skb_queue_purge(&data->txq);

	वापस 0;
पूर्ण

अटल पूर्णांक btsdio_send_frame(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा btsdio_data *data = hci_get_drvdata(hdev);

	BT_DBG("%s", hdev->name);

	चयन (hci_skb_pkt_type(skb)) अणु
	हाल HCI_COMMAND_PKT:
		hdev->stat.cmd_tx++;
		अवरोध;

	हाल HCI_ACLDATA_PKT:
		hdev->stat.acl_tx++;
		अवरोध;

	हाल HCI_SCODATA_PKT:
		hdev->stat.sco_tx++;
		अवरोध;

	शेष:
		वापस -EILSEQ;
	पूर्ण

	skb_queue_tail(&data->txq, skb);

	schedule_work(&data->work);

	वापस 0;
पूर्ण

अटल पूर्णांक btsdio_probe(काष्ठा sdio_func *func,
				स्थिर काष्ठा sdio_device_id *id)
अणु
	काष्ठा btsdio_data *data;
	काष्ठा hci_dev *hdev;
	काष्ठा sdio_func_tuple *tuple = func->tuples;
	पूर्णांक err;

	BT_DBG("func %p id %p class 0x%04x", func, id, func->class);

	जबतक (tuple) अणु
		BT_DBG("code 0x%x size %d", tuple->code, tuple->size);
		tuple = tuple->next;
	पूर्ण

	/* Broadcom devices soldered onto the PCB (non-removable) use an
	 * UART connection क्रम Bluetooth, ignore the BT SDIO पूर्णांकerface.
	 */
	अगर (func->venकरोr == SDIO_VENDOR_ID_BROADCOM &&
	    !mmc_card_is_removable(func->card->host)) अणु
		चयन (func->device) अणु
		हाल SDIO_DEVICE_ID_BROADCOM_43341:
		हाल SDIO_DEVICE_ID_BROADCOM_43430:
		हाल SDIO_DEVICE_ID_BROADCOM_4356:
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	data = devm_kzalloc(&func->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->func = func;

	INIT_WORK(&data->work, btsdio_work);

	skb_queue_head_init(&data->txq);

	hdev = hci_alloc_dev();
	अगर (!hdev)
		वापस -ENOMEM;

	hdev->bus = HCI_SDIO;
	hci_set_drvdata(hdev, data);

	अगर (id->class == SDIO_CLASS_BT_AMP)
		hdev->dev_type = HCI_AMP;
	अन्यथा
		hdev->dev_type = HCI_PRIMARY;

	data->hdev = hdev;

	SET_HCIDEV_DEV(hdev, &func->dev);

	hdev->खोलो     = btsdio_खोलो;
	hdev->बंद    = btsdio_बंद;
	hdev->flush    = btsdio_flush;
	hdev->send     = btsdio_send_frame;

	अगर (func->venकरोr == 0x0104 && func->device == 0x00c5)
		set_bit(HCI_QUIRK_RESET_ON_CLOSE, &hdev->quirks);

	err = hci_रेजिस्टर_dev(hdev);
	अगर (err < 0) अणु
		hci_मुक्त_dev(hdev);
		वापस err;
	पूर्ण

	sdio_set_drvdata(func, data);

	वापस 0;
पूर्ण

अटल व्योम btsdio_हटाओ(काष्ठा sdio_func *func)
अणु
	काष्ठा btsdio_data *data = sdio_get_drvdata(func);
	काष्ठा hci_dev *hdev;

	BT_DBG("func %p", func);

	अगर (!data)
		वापस;

	hdev = data->hdev;

	sdio_set_drvdata(func, शून्य);

	hci_unरेजिस्टर_dev(hdev);

	hci_मुक्त_dev(hdev);
पूर्ण

अटल काष्ठा sdio_driver btsdio_driver = अणु
	.name		= "btsdio",
	.probe		= btsdio_probe,
	.हटाओ		= btsdio_हटाओ,
	.id_table	= btsdio_table,
पूर्ण;

module_sdio_driver(btsdio_driver);

MODULE_AUTHOR("Marcel Holtmann <marcel@holtmann.org>");
MODULE_DESCRIPTION("Generic Bluetooth SDIO driver ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
