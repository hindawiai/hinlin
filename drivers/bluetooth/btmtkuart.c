<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018 MediaTek Inc.

/*
 * Bluetooth support क्रम MediaTek serial devices
 *
 * Author: Sean Wang <sean.wang@mediatek.com>
 *
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/atomic.h>
#समावेश <linux/clk.h>
#समावेश <linux/firmware.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/serdev.h>
#समावेश <linux/skbuff.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "h4_recv.h"

#घोषणा VERSION "0.2"

#घोषणा FIRMWARE_MT7622		"mediatek/mt7622pr2h.bin"
#घोषणा FIRMWARE_MT7663		"mediatek/mt7663pr2h.bin"
#घोषणा FIRMWARE_MT7668		"mediatek/mt7668pr2h.bin"

#घोषणा MTK_STP_TLR_SIZE	2

#घोषणा BTMTKUART_TX_STATE_ACTIVE	1
#घोषणा BTMTKUART_TX_STATE_WAKEUP	2
#घोषणा BTMTKUART_TX_WAIT_VND_EVT	3
#घोषणा BTMTKUART_REQUIRED_WAKEUP	4

#घोषणा BTMTKUART_FLAG_STANDALONE_HW	 BIT(0)

क्रमागत अणु
	MTK_WMT_PATCH_DWNLD = 0x1,
	MTK_WMT_TEST = 0x2,
	MTK_WMT_WAKEUP = 0x3,
	MTK_WMT_HIF = 0x4,
	MTK_WMT_FUNC_CTRL = 0x6,
	MTK_WMT_RST = 0x7,
	MTK_WMT_SEMAPHORE = 0x17,
पूर्ण;

क्रमागत अणु
	BTMTK_WMT_INVALID,
	BTMTK_WMT_PATCH_UNDONE,
	BTMTK_WMT_PATCH_DONE,
	BTMTK_WMT_ON_UNDONE,
	BTMTK_WMT_ON_DONE,
	BTMTK_WMT_ON_PROGRESS,
पूर्ण;

काष्ठा mtk_stp_hdr अणु
	u8	prefix;
	__be16	dlen;
	u8	cs;
पूर्ण __packed;

काष्ठा bपंचांगtkuart_data अणु
	अचिन्हित पूर्णांक flags;
	स्थिर अक्षर *fwname;
पूर्ण;

काष्ठा mtk_wmt_hdr अणु
	u8	dir;
	u8	op;
	__le16	dlen;
	u8	flag;
पूर्ण __packed;

काष्ठा mtk_hci_wmt_cmd अणु
	काष्ठा mtk_wmt_hdr hdr;
	u8 data[256];
पूर्ण __packed;

काष्ठा bपंचांगtk_hci_wmt_evt अणु
	काष्ठा hci_event_hdr hhdr;
	काष्ठा mtk_wmt_hdr whdr;
पूर्ण __packed;

काष्ठा bपंचांगtk_hci_wmt_evt_funcc अणु
	काष्ठा bपंचांगtk_hci_wmt_evt hwhdr;
	__be16 status;
पूर्ण __packed;

काष्ठा bपंचांगtk_tci_sleep अणु
	u8 mode;
	__le16 duration;
	__le16 host_duration;
	u8 host_wakeup_pin;
	u8 समय_compensation;
पूर्ण __packed;

काष्ठा bपंचांगtk_hci_wmt_params अणु
	u8 op;
	u8 flag;
	u16 dlen;
	स्थिर व्योम *data;
	u32 *status;
पूर्ण;

काष्ठा bपंचांगtkuart_dev अणु
	काष्ठा hci_dev *hdev;
	काष्ठा serdev_device *serdev;

	काष्ठा clk *clk;
	काष्ठा clk *osc;
	काष्ठा regulator *vcc;
	काष्ठा gpio_desc *reset;
	काष्ठा gpio_desc *boot;
	काष्ठा pinctrl *pinctrl;
	काष्ठा pinctrl_state *pins_runसमय;
	काष्ठा pinctrl_state *pins_boot;
	speed_t	desired_speed;
	speed_t	curr_speed;

	काष्ठा work_काष्ठा tx_work;
	अचिन्हित दीर्घ tx_state;
	काष्ठा sk_buff_head txq;

	काष्ठा sk_buff *rx_skb;
	काष्ठा sk_buff *evt_skb;

	u8	stp_pad[6];
	u8	stp_cursor;
	u16	stp_dlen;

	स्थिर काष्ठा bपंचांगtkuart_data *data;
पूर्ण;

#घोषणा bपंचांगtkuart_is_standalone(bdev)	\
	((bdev)->data->flags & BTMTKUART_FLAG_STANDALONE_HW)
#घोषणा bपंचांगtkuart_is_builtin_soc(bdev)	\
	!((bdev)->data->flags & BTMTKUART_FLAG_STANDALONE_HW)

अटल पूर्णांक mtk_hci_wmt_sync(काष्ठा hci_dev *hdev,
			    काष्ठा bपंचांगtk_hci_wmt_params *wmt_params)
अणु
	काष्ठा bपंचांगtkuart_dev *bdev = hci_get_drvdata(hdev);
	काष्ठा bपंचांगtk_hci_wmt_evt_funcc *wmt_evt_funcc;
	u32 hlen, status = BTMTK_WMT_INVALID;
	काष्ठा bपंचांगtk_hci_wmt_evt *wmt_evt;
	काष्ठा mtk_hci_wmt_cmd wc;
	काष्ठा mtk_wmt_hdr *hdr;
	पूर्णांक err;

	hlen = माप(*hdr) + wmt_params->dlen;
	अगर (hlen > 255)
		वापस -EINVAL;

	hdr = (काष्ठा mtk_wmt_hdr *)&wc;
	hdr->dir = 1;
	hdr->op = wmt_params->op;
	hdr->dlen = cpu_to_le16(wmt_params->dlen + 1);
	hdr->flag = wmt_params->flag;
	स_नकल(wc.data, wmt_params->data, wmt_params->dlen);

	set_bit(BTMTKUART_TX_WAIT_VND_EVT, &bdev->tx_state);

	err = __hci_cmd_send(hdev, 0xfc6f, hlen, &wc);
	अगर (err < 0) अणु
		clear_bit(BTMTKUART_TX_WAIT_VND_EVT, &bdev->tx_state);
		वापस err;
	पूर्ण

	/* The venकरोr specअगरic WMT commands are all answered by a venकरोr
	 * specअगरic event and will not have the Command Status or Command
	 * Complete as with usual HCI command flow control.
	 *
	 * After sending the command, रुको क्रम BTMTKUART_TX_WAIT_VND_EVT
	 * state to be cleared. The driver specअगरic event receive routine
	 * will clear that state and with that indicate completion of the
	 * WMT command.
	 */
	err = रुको_on_bit_समयout(&bdev->tx_state, BTMTKUART_TX_WAIT_VND_EVT,
				  TASK_INTERRUPTIBLE, HCI_INIT_TIMEOUT);
	अगर (err == -EINTR) अणु
		bt_dev_err(hdev, "Execution of wmt command interrupted");
		clear_bit(BTMTKUART_TX_WAIT_VND_EVT, &bdev->tx_state);
		वापस err;
	पूर्ण

	अगर (err) अणु
		bt_dev_err(hdev, "Execution of wmt command timed out");
		clear_bit(BTMTKUART_TX_WAIT_VND_EVT, &bdev->tx_state);
		वापस -ETIMEDOUT;
	पूर्ण

	/* Parse and handle the वापस WMT event */
	wmt_evt = (काष्ठा bपंचांगtk_hci_wmt_evt *)bdev->evt_skb->data;
	अगर (wmt_evt->whdr.op != hdr->op) अणु
		bt_dev_err(hdev, "Wrong op received %d expected %d",
			   wmt_evt->whdr.op, hdr->op);
		err = -EIO;
		जाओ err_मुक्त_skb;
	पूर्ण

	चयन (wmt_evt->whdr.op) अणु
	हाल MTK_WMT_SEMAPHORE:
		अगर (wmt_evt->whdr.flag == 2)
			status = BTMTK_WMT_PATCH_UNDONE;
		अन्यथा
			status = BTMTK_WMT_PATCH_DONE;
		अवरोध;
	हाल MTK_WMT_FUNC_CTRL:
		wmt_evt_funcc = (काष्ठा bपंचांगtk_hci_wmt_evt_funcc *)wmt_evt;
		अगर (be16_to_cpu(wmt_evt_funcc->status) == 0x404)
			status = BTMTK_WMT_ON_DONE;
		अन्यथा अगर (be16_to_cpu(wmt_evt_funcc->status) == 0x420)
			status = BTMTK_WMT_ON_PROGRESS;
		अन्यथा
			status = BTMTK_WMT_ON_UNDONE;
		अवरोध;
	पूर्ण

	अगर (wmt_params->status)
		*wmt_params->status = status;

err_मुक्त_skb:
	kमुक्त_skb(bdev->evt_skb);
	bdev->evt_skb = शून्य;

	वापस err;
पूर्ण

अटल पूर्णांक mtk_setup_firmware(काष्ठा hci_dev *hdev, स्थिर अक्षर *fwname)
अणु
	काष्ठा bपंचांगtk_hci_wmt_params wmt_params;
	स्थिर काष्ठा firmware *fw;
	स्थिर u8 *fw_ptr;
	माप_प्रकार fw_size;
	पूर्णांक err, dlen;
	u8 flag;

	err = request_firmware(&fw, fwname, &hdev->dev);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to load firmware file (%d)", err);
		वापस err;
	पूर्ण

	fw_ptr = fw->data;
	fw_size = fw->size;

	/* The size of patch header is 30 bytes, should be skip */
	अगर (fw_size < 30) अणु
		err = -EINVAL;
		जाओ मुक्त_fw;
	पूर्ण

	fw_size -= 30;
	fw_ptr += 30;
	flag = 1;

	wmt_params.op = MTK_WMT_PATCH_DWNLD;
	wmt_params.status = शून्य;

	जबतक (fw_size > 0) अणु
		dlen = min_t(पूर्णांक, 250, fw_size);

		/* Tell device the position in sequence */
		अगर (fw_size - dlen <= 0)
			flag = 3;
		अन्यथा अगर (fw_size < fw->size - 30)
			flag = 2;

		wmt_params.flag = flag;
		wmt_params.dlen = dlen;
		wmt_params.data = fw_ptr;

		err = mtk_hci_wmt_sync(hdev, &wmt_params);
		अगर (err < 0) अणु
			bt_dev_err(hdev, "Failed to send wmt patch dwnld (%d)",
				   err);
			जाओ मुक्त_fw;
		पूर्ण

		fw_size -= dlen;
		fw_ptr += dlen;
	पूर्ण

	wmt_params.op = MTK_WMT_RST;
	wmt_params.flag = 4;
	wmt_params.dlen = 0;
	wmt_params.data = शून्य;
	wmt_params.status = शून्य;

	/* Activate funciton the firmware providing to */
	err = mtk_hci_wmt_sync(hdev, &wmt_params);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to send wmt rst (%d)", err);
		जाओ मुक्त_fw;
	पूर्ण

	/* Wait a few moments क्रम firmware activation करोne */
	usleep_range(10000, 12000);

मुक्त_fw:
	release_firmware(fw);
	वापस err;
पूर्ण

अटल पूर्णांक bपंचांगtkuart_recv_event(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा bपंचांगtkuart_dev *bdev = hci_get_drvdata(hdev);
	काष्ठा hci_event_hdr *hdr = (व्योम *)skb->data;
	पूर्णांक err;

	/* Fix up the venकरोr event id with 0xff क्रम venकरोr specअगरic instead
	 * of 0xe4 so that event send via monitoring socket can be parsed
	 * properly.
	 */
	अगर (hdr->evt == 0xe4)
		hdr->evt = HCI_EV_VENDOR;

	/* When someone रुकोs क्रम the WMT event, the skb is being cloned
	 * and being processed the events from there then.
	 */
	अगर (test_bit(BTMTKUART_TX_WAIT_VND_EVT, &bdev->tx_state)) अणु
		bdev->evt_skb = skb_clone(skb, GFP_KERNEL);
		अगर (!bdev->evt_skb) अणु
			err = -ENOMEM;
			जाओ err_out;
		पूर्ण
	पूर्ण

	err = hci_recv_frame(hdev, skb);
	अगर (err < 0)
		जाओ err_मुक्त_skb;

	अगर (hdr->evt == HCI_EV_VENDOR) अणु
		अगर (test_and_clear_bit(BTMTKUART_TX_WAIT_VND_EVT,
				       &bdev->tx_state)) अणु
			/* Barrier to sync with other CPUs */
			smp_mb__after_atomic();
			wake_up_bit(&bdev->tx_state, BTMTKUART_TX_WAIT_VND_EVT);
		पूर्ण
	पूर्ण

	वापस 0;

err_मुक्त_skb:
	kमुक्त_skb(bdev->evt_skb);
	bdev->evt_skb = शून्य;

err_out:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा h4_recv_pkt mtk_recv_pkts[] = अणु
	अणु H4_RECV_ACL,      .recv = hci_recv_frame पूर्ण,
	अणु H4_RECV_SCO,      .recv = hci_recv_frame पूर्ण,
	अणु H4_RECV_EVENT,    .recv = bपंचांगtkuart_recv_event पूर्ण,
पूर्ण;

अटल व्योम bपंचांगtkuart_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bपंचांगtkuart_dev *bdev = container_of(work, काष्ठा bपंचांगtkuart_dev,
						   tx_work);
	काष्ठा serdev_device *serdev = bdev->serdev;
	काष्ठा hci_dev *hdev = bdev->hdev;

	जबतक (1) अणु
		clear_bit(BTMTKUART_TX_STATE_WAKEUP, &bdev->tx_state);

		जबतक (1) अणु
			काष्ठा sk_buff *skb = skb_dequeue(&bdev->txq);
			पूर्णांक len;

			अगर (!skb)
				अवरोध;

			len = serdev_device_ग_लिखो_buf(serdev, skb->data,
						      skb->len);
			hdev->stat.byte_tx += len;

			skb_pull(skb, len);
			अगर (skb->len > 0) अणु
				skb_queue_head(&bdev->txq, skb);
				अवरोध;
			पूर्ण

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
			पूर्ण

			kमुक्त_skb(skb);
		पूर्ण

		अगर (!test_bit(BTMTKUART_TX_STATE_WAKEUP, &bdev->tx_state))
			अवरोध;
	पूर्ण

	clear_bit(BTMTKUART_TX_STATE_ACTIVE, &bdev->tx_state);
पूर्ण

अटल व्योम bपंचांगtkuart_tx_wakeup(काष्ठा bपंचांगtkuart_dev *bdev)
अणु
	अगर (test_and_set_bit(BTMTKUART_TX_STATE_ACTIVE, &bdev->tx_state))
		set_bit(BTMTKUART_TX_STATE_WAKEUP, &bdev->tx_state);

	schedule_work(&bdev->tx_work);
पूर्ण

अटल स्थिर अचिन्हित अक्षर *
mtk_stp_split(काष्ठा bपंचांगtkuart_dev *bdev, स्थिर अचिन्हित अक्षर *data, पूर्णांक count,
	      पूर्णांक *sz_h4)
अणु
	काष्ठा mtk_stp_hdr *shdr;

	/* The cursor is reset when all the data of STP is consumed out */
	अगर (!bdev->stp_dlen && bdev->stp_cursor >= 6)
		bdev->stp_cursor = 0;

	/* Filling pad until all STP info is obtained */
	जबतक (bdev->stp_cursor < 6 && count > 0) अणु
		bdev->stp_pad[bdev->stp_cursor] = *data;
		bdev->stp_cursor++;
		data++;
		count--;
	पूर्ण

	/* Retrieve STP info and have a sanity check */
	अगर (!bdev->stp_dlen && bdev->stp_cursor >= 6) अणु
		shdr = (काष्ठा mtk_stp_hdr *)&bdev->stp_pad[2];
		bdev->stp_dlen = be16_to_cpu(shdr->dlen) & 0x0fff;

		/* Resync STP when unexpected data is being पढ़ो */
		अगर (shdr->prefix != 0x80 || bdev->stp_dlen > 2048) अणु
			bt_dev_err(bdev->hdev, "stp format unexpect (%d, %d)",
				   shdr->prefix, bdev->stp_dlen);
			bdev->stp_cursor = 2;
			bdev->stp_dlen = 0;
		पूर्ण
	पूर्ण

	/* Directly quit when there's no data found क्रम H4 can process */
	अगर (count <= 0)
		वापस शून्य;

	/* Tranlate to how much the size of data H4 can handle so far */
	*sz_h4 = min_t(पूर्णांक, count, bdev->stp_dlen);

	/* Update the reमुख्यing size of STP packet */
	bdev->stp_dlen -= *sz_h4;

	/* Data poपूर्णांकs to STP payload which can be handled by H4 */
	वापस data;
पूर्ण

अटल पूर्णांक bपंचांगtkuart_recv(काष्ठा hci_dev *hdev, स्थिर u8 *data, माप_प्रकार count)
अणु
	काष्ठा bपंचांगtkuart_dev *bdev = hci_get_drvdata(hdev);
	स्थिर अचिन्हित अक्षर *p_left = data, *p_h4;
	पूर्णांक sz_left = count, sz_h4, adv;
	पूर्णांक err;

	जबतक (sz_left > 0) अणु
		/*  The serial data received from MT7622 BT controller is
		 *  at all समय padded around with the STP header and tailer.
		 *
		 *  A full STP packet is looking like
		 *   -----------------------------------
		 *  | STP header  |  H:4   | STP tailer |
		 *   -----------------------------------
		 *  but it करोesn't guarantee to contain a full H:4 packet which
		 *  means that it's possible क्रम multiple STP packets क्रमms a
		 *  full H:4 packet that means extra STP header + length करोesn't
		 *  indicate a full H:4 frame, things can fragment. Whose length
		 *  recorded in STP header just shows up the most length the
		 *  H:4 engine can handle currently.
		 */

		p_h4 = mtk_stp_split(bdev, p_left, sz_left, &sz_h4);
		अगर (!p_h4)
			अवरोध;

		adv = p_h4 - p_left;
		sz_left -= adv;
		p_left += adv;

		bdev->rx_skb = h4_recv_buf(bdev->hdev, bdev->rx_skb, p_h4,
					   sz_h4, mtk_recv_pkts,
					   ARRAY_SIZE(mtk_recv_pkts));
		अगर (IS_ERR(bdev->rx_skb)) अणु
			err = PTR_ERR(bdev->rx_skb);
			bt_dev_err(bdev->hdev,
				   "Frame reassembly failed (%d)", err);
			bdev->rx_skb = शून्य;
			वापस err;
		पूर्ण

		sz_left -= sz_h4;
		p_left += sz_h4;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगtkuart_receive_buf(काष्ठा serdev_device *serdev, स्थिर u8 *data,
				 माप_प्रकार count)
अणु
	काष्ठा bपंचांगtkuart_dev *bdev = serdev_device_get_drvdata(serdev);
	पूर्णांक err;

	err = bपंचांगtkuart_recv(bdev->hdev, data, count);
	अगर (err < 0)
		वापस err;

	bdev->hdev->stat.byte_rx += count;

	वापस count;
पूर्ण

अटल व्योम bपंचांगtkuart_ग_लिखो_wakeup(काष्ठा serdev_device *serdev)
अणु
	काष्ठा bपंचांगtkuart_dev *bdev = serdev_device_get_drvdata(serdev);

	bपंचांगtkuart_tx_wakeup(bdev);
पूर्ण

अटल स्थिर काष्ठा serdev_device_ops bपंचांगtkuart_client_ops = अणु
	.receive_buf = bपंचांगtkuart_receive_buf,
	.ग_लिखो_wakeup = bपंचांगtkuart_ग_लिखो_wakeup,
पूर्ण;

अटल पूर्णांक bपंचांगtkuart_खोलो(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bपंचांगtkuart_dev *bdev = hci_get_drvdata(hdev);
	काष्ठा device *dev;
	पूर्णांक err;

	err = serdev_device_खोलो(bdev->serdev);
	अगर (err) अणु
		bt_dev_err(hdev, "Unable to open UART device %s",
			   dev_name(&bdev->serdev->dev));
		जाओ err_खोलो;
	पूर्ण

	अगर (bपंचांगtkuart_is_standalone(bdev)) अणु
		अगर (bdev->curr_speed != bdev->desired_speed)
			err = serdev_device_set_baudrate(bdev->serdev,
							 115200);
		अन्यथा
			err = serdev_device_set_baudrate(bdev->serdev,
							 bdev->desired_speed);

		अगर (err < 0) अणु
			bt_dev_err(hdev, "Unable to set baudrate UART device %s",
				   dev_name(&bdev->serdev->dev));
			जाओ  err_serdev_बंद;
		पूर्ण

		serdev_device_set_flow_control(bdev->serdev, false);
	पूर्ण

	bdev->stp_cursor = 2;
	bdev->stp_dlen = 0;

	dev = &bdev->serdev->dev;

	/* Enable the घातer करोमुख्य and घड़ी the device requires */
	pm_runसमय_enable(dev);
	err = pm_runसमय_get_sync(dev);
	अगर (err < 0) अणु
		pm_runसमय_put_noidle(dev);
		जाओ err_disable_rpm;
	पूर्ण

	err = clk_prepare_enable(bdev->clk);
	अगर (err < 0)
		जाओ err_put_rpm;

	वापस 0;

err_put_rpm:
	pm_runसमय_put_sync(dev);
err_disable_rpm:
	pm_runसमय_disable(dev);
err_serdev_बंद:
	serdev_device_बंद(bdev->serdev);
err_खोलो:
	वापस err;
पूर्ण

अटल पूर्णांक bपंचांगtkuart_बंद(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bपंचांगtkuart_dev *bdev = hci_get_drvdata(hdev);
	काष्ठा device *dev = &bdev->serdev->dev;

	/* Shutकरोwn the घड़ी and घातer करोमुख्य the device requires */
	clk_disable_unprepare(bdev->clk);
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);

	serdev_device_बंद(bdev->serdev);

	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगtkuart_flush(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bपंचांगtkuart_dev *bdev = hci_get_drvdata(hdev);

	/* Flush any pending अक्षरacters */
	serdev_device_ग_लिखो_flush(bdev->serdev);
	skb_queue_purge(&bdev->txq);

	cancel_work_sync(&bdev->tx_work);

	kमुक्त_skb(bdev->rx_skb);
	bdev->rx_skb = शून्य;

	bdev->stp_cursor = 2;
	bdev->stp_dlen = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगtkuart_func_query(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bपंचांगtk_hci_wmt_params wmt_params;
	पूर्णांक status, err;
	u8 param = 0;

	/* Query whether the function is enabled */
	wmt_params.op = MTK_WMT_FUNC_CTRL;
	wmt_params.flag = 4;
	wmt_params.dlen = माप(param);
	wmt_params.data = &param;
	wmt_params.status = &status;

	err = mtk_hci_wmt_sync(hdev, &wmt_params);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to query function status (%d)", err);
		वापस err;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक bपंचांगtkuart_change_baudrate(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bपंचांगtkuart_dev *bdev = hci_get_drvdata(hdev);
	काष्ठा bपंचांगtk_hci_wmt_params wmt_params;
	__le32 baudrate;
	u8 param;
	पूर्णांक err;

	/* Indicate the device to enter the probe state the host is
	 * पढ़ोy to change a new baudrate.
	 */
	baudrate = cpu_to_le32(bdev->desired_speed);
	wmt_params.op = MTK_WMT_HIF;
	wmt_params.flag = 1;
	wmt_params.dlen = 4;
	wmt_params.data = &baudrate;
	wmt_params.status = शून्य;

	err = mtk_hci_wmt_sync(hdev, &wmt_params);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to device baudrate (%d)", err);
		वापस err;
	पूर्ण

	err = serdev_device_set_baudrate(bdev->serdev,
					 bdev->desired_speed);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to set up host baudrate (%d)",
			   err);
		वापस err;
	पूर्ण

	serdev_device_set_flow_control(bdev->serdev, false);

	/* Send a dummy byte 0xff to activate the new baudrate */
	param = 0xff;
	err = serdev_device_ग_लिखो_buf(bdev->serdev, &param, माप(param));
	अगर (err < 0 || err < माप(param))
		वापस err;

	serdev_device_रुको_until_sent(bdev->serdev, 0);

	/* Wait some समय क्रम the device changing baudrate करोne */
	usleep_range(20000, 22000);

	/* Test the new baudrate */
	wmt_params.op = MTK_WMT_TEST;
	wmt_params.flag = 7;
	wmt_params.dlen = 0;
	wmt_params.data = शून्य;
	wmt_params.status = शून्य;

	err = mtk_hci_wmt_sync(hdev, &wmt_params);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to test new baudrate (%d)",
			   err);
		वापस err;
	पूर्ण

	bdev->curr_speed = bdev->desired_speed;

	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगtkuart_setup(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bपंचांगtkuart_dev *bdev = hci_get_drvdata(hdev);
	काष्ठा bपंचांगtk_hci_wmt_params wmt_params;
	kसमय_प्रकार callसमय, delta, retसमय;
	काष्ठा bपंचांगtk_tci_sleep tci_sleep;
	अचिन्हित दीर्घ दीर्घ duration;
	काष्ठा sk_buff *skb;
	पूर्णांक err, status;
	u8 param = 0x1;

	callसमय = kसमय_get();

	/* Wakeup MCUSYS is required क्रम certain devices beक्रमe we start to
	 * करो any setups.
	 */
	अगर (test_bit(BTMTKUART_REQUIRED_WAKEUP, &bdev->tx_state)) अणु
		wmt_params.op = MTK_WMT_WAKEUP;
		wmt_params.flag = 3;
		wmt_params.dlen = 0;
		wmt_params.data = शून्य;
		wmt_params.status = शून्य;

		err = mtk_hci_wmt_sync(hdev, &wmt_params);
		अगर (err < 0) अणु
			bt_dev_err(hdev, "Failed to wakeup the chip (%d)", err);
			वापस err;
		पूर्ण

		clear_bit(BTMTKUART_REQUIRED_WAKEUP, &bdev->tx_state);
	पूर्ण

	अगर (bपंचांगtkuart_is_standalone(bdev))
		bपंचांगtkuart_change_baudrate(hdev);

	/* Query whether the firmware is alपढ़ोy करोwnload */
	wmt_params.op = MTK_WMT_SEMAPHORE;
	wmt_params.flag = 1;
	wmt_params.dlen = 0;
	wmt_params.data = शून्य;
	wmt_params.status = &status;

	err = mtk_hci_wmt_sync(hdev, &wmt_params);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to query firmware status (%d)", err);
		वापस err;
	पूर्ण

	अगर (status == BTMTK_WMT_PATCH_DONE) अणु
		bt_dev_info(hdev, "Firmware already downloaded");
		जाओ ignore_setup_fw;
	पूर्ण

	/* Setup a firmware which the device definitely requires */
	err = mtk_setup_firmware(hdev, bdev->data->fwname);
	अगर (err < 0)
		वापस err;

ignore_setup_fw:
	/* Query whether the device is alपढ़ोy enabled */
	err = पढ़ोx_poll_समयout(bपंचांगtkuart_func_query, hdev, status,
				 status < 0 || status != BTMTK_WMT_ON_PROGRESS,
				 2000, 5000000);
	/* -ETIMEDOUT happens */
	अगर (err < 0)
		वापस err;

	/* The other errors happen in btusb_mtk_func_query */
	अगर (status < 0)
		वापस status;

	अगर (status == BTMTK_WMT_ON_DONE) अणु
		bt_dev_info(hdev, "function already on");
		जाओ ignore_func_on;
	पूर्ण

	/* Enable Bluetooth protocol */
	wmt_params.op = MTK_WMT_FUNC_CTRL;
	wmt_params.flag = 0;
	wmt_params.dlen = माप(param);
	wmt_params.data = &param;
	wmt_params.status = शून्य;

	err = mtk_hci_wmt_sync(hdev, &wmt_params);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to send wmt func ctrl (%d)", err);
		वापस err;
	पूर्ण

ignore_func_on:
	/* Apply the low घातer environment setup */
	tci_sleep.mode = 0x5;
	tci_sleep.duration = cpu_to_le16(0x640);
	tci_sleep.host_duration = cpu_to_le16(0x640);
	tci_sleep.host_wakeup_pin = 0;
	tci_sleep.समय_compensation = 0;

	skb = __hci_cmd_sync(hdev, 0xfc7a, माप(tci_sleep), &tci_sleep,
			     HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		err = PTR_ERR(skb);
		bt_dev_err(hdev, "Failed to apply low power setting (%d)", err);
		वापस err;
	पूर्ण
	kमुक्त_skb(skb);

	retसमय = kसमय_get();
	delta = kसमय_sub(retसमय, callसमय);
	duration = (अचिन्हित दीर्घ दीर्घ)kसमय_प्रकारo_ns(delta) >> 10;

	bt_dev_info(hdev, "Device setup in %llu usecs", duration);

	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगtkuart_shutकरोwn(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bपंचांगtk_hci_wmt_params wmt_params;
	u8 param = 0x0;
	पूर्णांक err;

	/* Disable the device */
	wmt_params.op = MTK_WMT_FUNC_CTRL;
	wmt_params.flag = 0;
	wmt_params.dlen = माप(param);
	wmt_params.data = &param;
	wmt_params.status = शून्य;

	err = mtk_hci_wmt_sync(hdev, &wmt_params);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to send wmt func ctrl (%d)", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगtkuart_send_frame(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा bपंचांगtkuart_dev *bdev = hci_get_drvdata(hdev);
	काष्ठा mtk_stp_hdr *shdr;
	पूर्णांक err, dlen, type = 0;

	/* Prepend skb with frame type */
	स_नकल(skb_push(skb, 1), &hci_skb_pkt_type(skb), 1);

	/* Make sure that there is enough rooms क्रम STP header and trailer */
	अगर (unlikely(skb_headroom(skb) < माप(*shdr)) ||
	    (skb_tailroom(skb) < MTK_STP_TLR_SIZE)) अणु
		err = pskb_expand_head(skb, माप(*shdr), MTK_STP_TLR_SIZE,
				       GFP_ATOMIC);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* Add the STP header */
	dlen = skb->len;
	shdr = skb_push(skb, माप(*shdr));
	shdr->prefix = 0x80;
	shdr->dlen = cpu_to_be16((dlen & 0x0fff) | (type << 12));
	shdr->cs = 0;		/* MT7622 करोesn't care about checksum value */

	/* Add the STP trailer */
	skb_put_zero(skb, MTK_STP_TLR_SIZE);

	skb_queue_tail(&bdev->txq, skb);

	bपंचांगtkuart_tx_wakeup(bdev);
	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगtkuart_parse_dt(काष्ठा serdev_device *serdev)
अणु
	काष्ठा bपंचांगtkuart_dev *bdev = serdev_device_get_drvdata(serdev);
	काष्ठा device_node *node = serdev->dev.of_node;
	u32 speed = 921600;
	पूर्णांक err;

	अगर (bपंचांगtkuart_is_standalone(bdev)) अणु
		of_property_पढ़ो_u32(node, "current-speed", &speed);

		bdev->desired_speed = speed;

		bdev->vcc = devm_regulator_get(&serdev->dev, "vcc");
		अगर (IS_ERR(bdev->vcc)) अणु
			err = PTR_ERR(bdev->vcc);
			वापस err;
		पूर्ण

		bdev->osc = devm_clk_get_optional(&serdev->dev, "osc");
		अगर (IS_ERR(bdev->osc)) अणु
			err = PTR_ERR(bdev->osc);
			वापस err;
		पूर्ण

		bdev->boot = devm_gpiod_get_optional(&serdev->dev, "boot",
						     GPIOD_OUT_LOW);
		अगर (IS_ERR(bdev->boot)) अणु
			err = PTR_ERR(bdev->boot);
			वापस err;
		पूर्ण

		bdev->pinctrl = devm_pinctrl_get(&serdev->dev);
		अगर (IS_ERR(bdev->pinctrl)) अणु
			err = PTR_ERR(bdev->pinctrl);
			वापस err;
		पूर्ण

		bdev->pins_boot = pinctrl_lookup_state(bdev->pinctrl,
						       "default");
		अगर (IS_ERR(bdev->pins_boot) && !bdev->boot) अणु
			err = PTR_ERR(bdev->pins_boot);
			dev_err(&serdev->dev,
				"Should assign RXD to LOW at boot stage\n");
			वापस err;
		पूर्ण

		bdev->pins_runसमय = pinctrl_lookup_state(bdev->pinctrl,
							  "runtime");
		अगर (IS_ERR(bdev->pins_runसमय)) अणु
			err = PTR_ERR(bdev->pins_runसमय);
			वापस err;
		पूर्ण

		bdev->reset = devm_gpiod_get_optional(&serdev->dev, "reset",
						      GPIOD_OUT_LOW);
		अगर (IS_ERR(bdev->reset)) अणु
			err = PTR_ERR(bdev->reset);
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अगर (bपंचांगtkuart_is_builtin_soc(bdev)) अणु
		bdev->clk = devm_clk_get(&serdev->dev, "ref");
		अगर (IS_ERR(bdev->clk))
			वापस PTR_ERR(bdev->clk);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगtkuart_probe(काष्ठा serdev_device *serdev)
अणु
	काष्ठा bपंचांगtkuart_dev *bdev;
	काष्ठा hci_dev *hdev;
	पूर्णांक err;

	bdev = devm_kzalloc(&serdev->dev, माप(*bdev), GFP_KERNEL);
	अगर (!bdev)
		वापस -ENOMEM;

	bdev->data = of_device_get_match_data(&serdev->dev);
	अगर (!bdev->data)
		वापस -ENODEV;

	bdev->serdev = serdev;
	serdev_device_set_drvdata(serdev, bdev);

	serdev_device_set_client_ops(serdev, &bपंचांगtkuart_client_ops);

	err = bपंचांगtkuart_parse_dt(serdev);
	अगर (err < 0)
		वापस err;

	INIT_WORK(&bdev->tx_work, bपंचांगtkuart_tx_work);
	skb_queue_head_init(&bdev->txq);

	/* Initialize and रेजिस्टर HCI device */
	hdev = hci_alloc_dev();
	अगर (!hdev) अणु
		dev_err(&serdev->dev, "Can't allocate HCI device\n");
		वापस -ENOMEM;
	पूर्ण

	bdev->hdev = hdev;

	hdev->bus = HCI_UART;
	hci_set_drvdata(hdev, bdev);

	hdev->खोलो     = bपंचांगtkuart_खोलो;
	hdev->बंद    = bपंचांगtkuart_बंद;
	hdev->flush    = bपंचांगtkuart_flush;
	hdev->setup    = bपंचांगtkuart_setup;
	hdev->shutकरोwn = bपंचांगtkuart_shutकरोwn;
	hdev->send     = bपंचांगtkuart_send_frame;
	SET_HCIDEV_DEV(hdev, &serdev->dev);

	hdev->manufacturer = 70;
	set_bit(HCI_QUIRK_NON_PERSISTENT_SETUP, &hdev->quirks);

	अगर (bपंचांगtkuart_is_standalone(bdev)) अणु
		err = clk_prepare_enable(bdev->osc);
		अगर (err < 0)
			जाओ err_hci_मुक्त_dev;

		अगर (bdev->boot) अणु
			gpiod_set_value_cansleep(bdev->boot, 1);
		पूर्ण अन्यथा अणु
			/* Switch to the specअगरic pin state क्रम the booting
			 * requires.
			 */
			pinctrl_select_state(bdev->pinctrl, bdev->pins_boot);
		पूर्ण

		/* Power on */
		err = regulator_enable(bdev->vcc);
		अगर (err < 0)
			जाओ err_clk_disable_unprepare;

		/* Reset अगर the reset-gpios is available otherwise the board
		 * -level design should be guaranteed.
		 */
		अगर (bdev->reset) अणु
			gpiod_set_value_cansleep(bdev->reset, 1);
			usleep_range(1000, 2000);
			gpiod_set_value_cansleep(bdev->reset, 0);
		पूर्ण

		/* Wait some समय until device got पढ़ोy and चयन to the pin
		 * mode the device requires क्रम UART transfers.
		 */
		msleep(50);

		अगर (bdev->boot)
			devm_gpiod_put(&serdev->dev, bdev->boot);

		pinctrl_select_state(bdev->pinctrl, bdev->pins_runसमय);

		/* A standalone device करोesn't depends on घातer करोमुख्य on SoC,
		 * so mark it as no callbacks.
		 */
		pm_runसमय_no_callbacks(&serdev->dev);

		set_bit(BTMTKUART_REQUIRED_WAKEUP, &bdev->tx_state);
	पूर्ण

	err = hci_रेजिस्टर_dev(hdev);
	अगर (err < 0) अणु
		dev_err(&serdev->dev, "Can't register HCI device\n");
		जाओ err_regulator_disable;
	पूर्ण

	वापस 0;

err_regulator_disable:
	अगर (bपंचांगtkuart_is_standalone(bdev))
		regulator_disable(bdev->vcc);
err_clk_disable_unprepare:
	अगर (bपंचांगtkuart_is_standalone(bdev))
		clk_disable_unprepare(bdev->osc);
err_hci_मुक्त_dev:
	hci_मुक्त_dev(hdev);

	वापस err;
पूर्ण

अटल व्योम bपंचांगtkuart_हटाओ(काष्ठा serdev_device *serdev)
अणु
	काष्ठा bपंचांगtkuart_dev *bdev = serdev_device_get_drvdata(serdev);
	काष्ठा hci_dev *hdev = bdev->hdev;

	अगर (bपंचांगtkuart_is_standalone(bdev)) अणु
		regulator_disable(bdev->vcc);
		clk_disable_unprepare(bdev->osc);
	पूर्ण

	hci_unरेजिस्टर_dev(hdev);
	hci_मुक्त_dev(hdev);
पूर्ण

अटल स्थिर काष्ठा bपंचांगtkuart_data mt7622_data = अणु
	.fwname = FIRMWARE_MT7622,
पूर्ण;

अटल स्थिर काष्ठा bपंचांगtkuart_data mt7663_data = अणु
	.flags = BTMTKUART_FLAG_STANDALONE_HW,
	.fwname = FIRMWARE_MT7663,
पूर्ण;

अटल स्थिर काष्ठा bपंचांगtkuart_data mt7668_data = अणु
	.flags = BTMTKUART_FLAG_STANDALONE_HW,
	.fwname = FIRMWARE_MT7668,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id mtk_of_match_table[] = अणु
	अणु .compatible = "mediatek,mt7622-bluetooth", .data = &mt7622_dataपूर्ण,
	अणु .compatible = "mediatek,mt7663u-bluetooth", .data = &mt7663_dataपूर्ण,
	अणु .compatible = "mediatek,mt7668u-bluetooth", .data = &mt7668_dataपूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_of_match_table);
#पूर्ण_अगर

अटल काष्ठा serdev_device_driver bपंचांगtkuart_driver = अणु
	.probe = bपंचांगtkuart_probe,
	.हटाओ = bपंचांगtkuart_हटाओ,
	.driver = अणु
		.name = "btmtkuart",
		.of_match_table = of_match_ptr(mtk_of_match_table),
	पूर्ण,
पूर्ण;

module_serdev_device_driver(bपंचांगtkuart_driver);

MODULE_AUTHOR("Sean Wang <sean.wang@mediatek.com>");
MODULE_DESCRIPTION("MediaTek Bluetooth Serial driver ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(FIRMWARE_MT7622);
MODULE_FIRMWARE(FIRMWARE_MT7663);
MODULE_FIRMWARE(FIRMWARE_MT7668);
