<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 MediaTek Inc.

/*
 * Bluetooth support क्रम MediaTek SDIO devices
 *
 * This file is written based on btsdio.c and bपंचांगtkuart.c.
 *
 * Author: Sean Wang <sean.wang@mediatek.com>
 *
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/atomic.h>
#समावेश <linux/firmware.h>
#समावेश <linux/init.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/skbuff.h>

#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/sdio_ids.h>
#समावेश <linux/mmc/sdio_func.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "h4_recv.h"

#घोषणा VERSION "0.1"

#घोषणा FIRMWARE_MT7663		"mediatek/mt7663pr2h.bin"
#घोषणा FIRMWARE_MT7668		"mediatek/mt7668pr2h.bin"

#घोषणा MTKBTSDIO_AUTOSUSPEND_DELAY	8000

अटल bool enable_स्वतःsuspend;

काष्ठा bपंचांगtksdio_data अणु
	स्थिर अक्षर *fwname;
पूर्ण;

अटल स्थिर काष्ठा bपंचांगtksdio_data mt7663_data = अणु
	.fwname = FIRMWARE_MT7663,
पूर्ण;

अटल स्थिर काष्ठा bपंचांगtksdio_data mt7668_data = अणु
	.fwname = FIRMWARE_MT7668,
पूर्ण;

अटल स्थिर काष्ठा sdio_device_id bपंचांगtksdio_table[] = अणु
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_MEDIATEK, SDIO_DEVICE_ID_MEDIATEK_MT7663),
	 .driver_data = (kernel_uदीर्घ_t)&mt7663_data पूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_MEDIATEK, SDIO_DEVICE_ID_MEDIATEK_MT7668),
	 .driver_data = (kernel_uदीर्घ_t)&mt7668_data पूर्ण,
	अणु पूर्ण	/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(sdio, bपंचांगtksdio_table);

#घोषणा MTK_REG_CHLPCR		0x4	/* W1S */
#घोषणा C_INT_EN_SET		BIT(0)
#घोषणा C_INT_EN_CLR		BIT(1)
#घोषणा C_FW_OWN_REQ_SET	BIT(8)  /* For ग_लिखो */
#घोषणा C_COM_DRV_OWN		BIT(8)  /* For पढ़ो */
#घोषणा C_FW_OWN_REQ_CLR	BIT(9)

#घोषणा MTK_REG_CSDIOCSR	0x8
#घोषणा SDIO_RE_INIT_EN		BIT(0)
#घोषणा SDIO_INT_CTL		BIT(2)

#घोषणा MTK_REG_CHCR		0xc
#घोषणा C_INT_CLR_CTRL		BIT(1)

/* CHISR have the same bits field definition with CHIER */
#घोषणा MTK_REG_CHISR		0x10
#घोषणा MTK_REG_CHIER		0x14
#घोषणा FW_OWN_BACK_INT		BIT(0)
#घोषणा RX_DONE_INT		BIT(1)
#घोषणा TX_EMPTY		BIT(2)
#घोषणा TX_FIFO_OVERFLOW	BIT(8)
#घोषणा RX_PKT_LEN		GENMASK(31, 16)

#घोषणा MTK_REG_CTDR		0x18

#घोषणा MTK_REG_CRDR		0x1c

#घोषणा MTK_SDIO_BLOCK_SIZE	256

#घोषणा BTMTKSDIO_TX_WAIT_VND_EVT	1

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

काष्ठा mtkbtsdio_hdr अणु
	__le16	len;
	__le16	reserved;
	u8	bt_type;
पूर्ण __packed;

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

काष्ठा bपंचांगtksdio_dev अणु
	काष्ठा hci_dev *hdev;
	काष्ठा sdio_func *func;
	काष्ठा device *dev;

	काष्ठा work_काष्ठा tx_work;
	अचिन्हित दीर्घ tx_state;
	काष्ठा sk_buff_head txq;

	काष्ठा sk_buff *evt_skb;

	स्थिर काष्ठा bपंचांगtksdio_data *data;
पूर्ण;

अटल पूर्णांक mtk_hci_wmt_sync(काष्ठा hci_dev *hdev,
			    काष्ठा bपंचांगtk_hci_wmt_params *wmt_params)
अणु
	काष्ठा bपंचांगtksdio_dev *bdev = hci_get_drvdata(hdev);
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

	set_bit(BTMTKSDIO_TX_WAIT_VND_EVT, &bdev->tx_state);

	err = __hci_cmd_send(hdev, 0xfc6f, hlen, &wc);
	अगर (err < 0) अणु
		clear_bit(BTMTKSDIO_TX_WAIT_VND_EVT, &bdev->tx_state);
		वापस err;
	पूर्ण

	/* The venकरोr specअगरic WMT commands are all answered by a venकरोr
	 * specअगरic event and will not have the Command Status or Command
	 * Complete as with usual HCI command flow control.
	 *
	 * After sending the command, रुको क्रम BTMTKSDIO_TX_WAIT_VND_EVT
	 * state to be cleared. The driver specअगरic event receive routine
	 * will clear that state and with that indicate completion of the
	 * WMT command.
	 */
	err = रुको_on_bit_समयout(&bdev->tx_state, BTMTKSDIO_TX_WAIT_VND_EVT,
				  TASK_INTERRUPTIBLE, HCI_INIT_TIMEOUT);
	अगर (err == -EINTR) अणु
		bt_dev_err(hdev, "Execution of wmt command interrupted");
		clear_bit(BTMTKSDIO_TX_WAIT_VND_EVT, &bdev->tx_state);
		वापस err;
	पूर्ण

	अगर (err) अणु
		bt_dev_err(hdev, "Execution of wmt command timed out");
		clear_bit(BTMTKSDIO_TX_WAIT_VND_EVT, &bdev->tx_state);
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

अटल पूर्णांक bपंचांगtksdio_tx_packet(काष्ठा bपंचांगtksdio_dev *bdev,
			       काष्ठा sk_buff *skb)
अणु
	काष्ठा mtkbtsdio_hdr *sdio_hdr;
	पूर्णांक err;

	/* Make sure that there are enough rooms क्रम SDIO header */
	अगर (unlikely(skb_headroom(skb) < माप(*sdio_hdr))) अणु
		err = pskb_expand_head(skb, माप(*sdio_hdr), 0,
				       GFP_ATOMIC);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* Prepend MediaTek SDIO Specअगरic Header */
	skb_push(skb, माप(*sdio_hdr));

	sdio_hdr = (व्योम *)skb->data;
	sdio_hdr->len = cpu_to_le16(skb->len);
	sdio_hdr->reserved = cpu_to_le16(0);
	sdio_hdr->bt_type = hci_skb_pkt_type(skb);

	err = sdio_ग_लिखोsb(bdev->func, MTK_REG_CTDR, skb->data,
			   round_up(skb->len, MTK_SDIO_BLOCK_SIZE));
	अगर (err < 0)
		जाओ err_skb_pull;

	bdev->hdev->stat.byte_tx += skb->len;

	kमुक्त_skb(skb);

	वापस 0;

err_skb_pull:
	skb_pull(skb, माप(*sdio_hdr));

	वापस err;
पूर्ण

अटल u32 bपंचांगtksdio_drv_own_query(काष्ठा bपंचांगtksdio_dev *bdev)
अणु
	वापस sdio_पढ़ोl(bdev->func, MTK_REG_CHLPCR, शून्य);
पूर्ण

अटल व्योम bपंचांगtksdio_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bपंचांगtksdio_dev *bdev = container_of(work, काष्ठा bपंचांगtksdio_dev,
						  tx_work);
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	pm_runसमय_get_sync(bdev->dev);

	sdio_claim_host(bdev->func);

	जबतक ((skb = skb_dequeue(&bdev->txq))) अणु
		err = bपंचांगtksdio_tx_packet(bdev, skb);
		अगर (err < 0) अणु
			bdev->hdev->stat.err_tx++;
			skb_queue_head(&bdev->txq, skb);
			अवरोध;
		पूर्ण
	पूर्ण

	sdio_release_host(bdev->func);

	pm_runसमय_mark_last_busy(bdev->dev);
	pm_runसमय_put_स्वतःsuspend(bdev->dev);
पूर्ण

अटल पूर्णांक bपंचांगtksdio_recv_event(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा bपंचांगtksdio_dev *bdev = hci_get_drvdata(hdev);
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
	अगर (test_bit(BTMTKSDIO_TX_WAIT_VND_EVT, &bdev->tx_state)) अणु
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
		अगर (test_and_clear_bit(BTMTKSDIO_TX_WAIT_VND_EVT,
				       &bdev->tx_state)) अणु
			/* Barrier to sync with other CPUs */
			smp_mb__after_atomic();
			wake_up_bit(&bdev->tx_state, BTMTKSDIO_TX_WAIT_VND_EVT);
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
	अणु H4_RECV_EVENT,    .recv = bपंचांगtksdio_recv_event पूर्ण,
पूर्ण;

अटल पूर्णांक bपंचांगtksdio_rx_packet(काष्ठा bपंचांगtksdio_dev *bdev, u16 rx_size)
अणु
	स्थिर काष्ठा h4_recv_pkt *pkts = mtk_recv_pkts;
	पूर्णांक pkts_count = ARRAY_SIZE(mtk_recv_pkts);
	काष्ठा mtkbtsdio_hdr *sdio_hdr;
	पूर्णांक err, i, pad_size;
	काष्ठा sk_buff *skb;
	u16 dlen;

	अगर (rx_size < माप(*sdio_hdr))
		वापस -EILSEQ;

	/* A SDIO packet is exactly containing a Bluetooth packet */
	skb = bt_skb_alloc(rx_size, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, rx_size);

	err = sdio_पढ़ोsb(bdev->func, skb->data, MTK_REG_CRDR, rx_size);
	अगर (err < 0)
		जाओ err_kमुक्त_skb;

	sdio_hdr = (व्योम *)skb->data;

	/* We assume the शेष error as -EILSEQ simply to make the error path
	 * be cleaner.
	 */
	err = -EILSEQ;

	अगर (rx_size != le16_to_cpu(sdio_hdr->len)) अणु
		bt_dev_err(bdev->hdev, "Rx size in sdio header is mismatched ");
		जाओ err_kमुक्त_skb;
	पूर्ण

	hci_skb_pkt_type(skb) = sdio_hdr->bt_type;

	/* Remove MediaTek SDIO header */
	skb_pull(skb, माप(*sdio_hdr));

	/* We have to dig पूर्णांकo the packet to get payload size and then know how
	 * many padding bytes at the tail, these padding bytes should be हटाओd
	 * beक्रमe the packet is indicated to the core layer.
	 */
	क्रम (i = 0; i < pkts_count; i++) अणु
		अगर (sdio_hdr->bt_type == (&pkts[i])->type)
			अवरोध;
	पूर्ण

	अगर (i >= pkts_count) अणु
		bt_dev_err(bdev->hdev, "Invalid bt type 0x%02x",
			   sdio_hdr->bt_type);
		जाओ err_kमुक्त_skb;
	पूर्ण

	/* Reमुख्यing bytes cannot hold a header*/
	अगर (skb->len < (&pkts[i])->hlen) अणु
		bt_dev_err(bdev->hdev, "The size of bt header is mismatched");
		जाओ err_kमुक्त_skb;
	पूर्ण

	चयन ((&pkts[i])->lsize) अणु
	हाल 1:
		dlen = skb->data[(&pkts[i])->loff];
		अवरोध;
	हाल 2:
		dlen = get_unaligned_le16(skb->data +
						  (&pkts[i])->loff);
		अवरोध;
	शेष:
		जाओ err_kमुक्त_skb;
	पूर्ण

	pad_size = skb->len - (&pkts[i])->hlen -  dlen;

	/* Reमुख्यing bytes cannot hold a payload */
	अगर (pad_size < 0) अणु
		bt_dev_err(bdev->hdev, "The size of bt payload is mismatched");
		जाओ err_kमुक्त_skb;
	पूर्ण

	/* Remove padding bytes */
	skb_trim(skb, skb->len - pad_size);

	/* Complete frame */
	(&pkts[i])->recv(bdev->hdev, skb);

	bdev->hdev->stat.byte_rx += rx_size;

	वापस 0;

err_kमुक्त_skb:
	kमुक्त_skb(skb);

	वापस err;
पूर्ण

अटल व्योम bपंचांगtksdio_पूर्णांकerrupt(काष्ठा sdio_func *func)
अणु
	काष्ठा bपंचांगtksdio_dev *bdev = sdio_get_drvdata(func);
	u32 पूर्णांक_status;
	u16 rx_size;

	/* It is required that the host माला_लो ownership from the device beक्रमe
	 * accessing any रेजिस्टर, however, अगर SDIO host is not being released,
	 * a potential deadlock probably happens in a circular रुको between SDIO
	 * IRQ work and PM runसमय work. So, we have to explicitly release SDIO
	 * host here and claim again after the PM runसमय work is all करोne.
	 */
	sdio_release_host(bdev->func);

	pm_runसमय_get_sync(bdev->dev);

	sdio_claim_host(bdev->func);

	/* Disable पूर्णांकerrupt */
	sdio_ग_लिखोl(func, C_INT_EN_CLR, MTK_REG_CHLPCR, शून्य);

	पूर्णांक_status = sdio_पढ़ोl(func, MTK_REG_CHISR, शून्य);

	/* Ack an पूर्णांकerrupt as soon as possible beक्रमe any operation on
	 * hardware.
	 *
	 * Note that we करोn't ack any status during operations to aव्योम race
	 * condition between the host and the device such as it's possible to
	 * mistakenly ack RX_DONE क्रम the next packet and then cause पूर्णांकerrupts
	 * not be उठाओd again but there is still pending data in the hardware
	 * FIFO.
	 */
	sdio_ग_लिखोl(func, पूर्णांक_status, MTK_REG_CHISR, शून्य);

	अगर (unlikely(!पूर्णांक_status))
		bt_dev_err(bdev->hdev, "CHISR is 0");

	अगर (पूर्णांक_status & FW_OWN_BACK_INT)
		bt_dev_dbg(bdev->hdev, "Get fw own back");

	अगर (पूर्णांक_status & TX_EMPTY)
		schedule_work(&bdev->tx_work);
	अन्यथा अगर (unlikely(पूर्णांक_status & TX_FIFO_OVERFLOW))
		bt_dev_warn(bdev->hdev, "Tx fifo overflow");

	अगर (पूर्णांक_status & RX_DONE_INT) अणु
		rx_size = (पूर्णांक_status & RX_PKT_LEN) >> 16;

		अगर (bपंचांगtksdio_rx_packet(bdev, rx_size) < 0)
			bdev->hdev->stat.err_rx++;
	पूर्ण

	/* Enable पूर्णांकerrupt */
	sdio_ग_लिखोl(func, C_INT_EN_SET, MTK_REG_CHLPCR, शून्य);

	pm_runसमय_mark_last_busy(bdev->dev);
	pm_runसमय_put_स्वतःsuspend(bdev->dev);
पूर्ण

अटल पूर्णांक bपंचांगtksdio_खोलो(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bपंचांगtksdio_dev *bdev = hci_get_drvdata(hdev);
	पूर्णांक err;
	u32 status;

	sdio_claim_host(bdev->func);

	err = sdio_enable_func(bdev->func);
	अगर (err < 0)
		जाओ err_release_host;

	/* Get ownership from the device */
	sdio_ग_लिखोl(bdev->func, C_FW_OWN_REQ_CLR, MTK_REG_CHLPCR, &err);
	अगर (err < 0)
		जाओ err_disable_func;

	err = पढ़ोx_poll_समयout(bपंचांगtksdio_drv_own_query, bdev, status,
				 status & C_COM_DRV_OWN, 2000, 1000000);
	अगर (err < 0) अणु
		bt_dev_err(bdev->hdev, "Cannot get ownership from device");
		जाओ err_disable_func;
	पूर्ण

	/* Disable पूर्णांकerrupt & mask out all पूर्णांकerrupt sources */
	sdio_ग_लिखोl(bdev->func, C_INT_EN_CLR, MTK_REG_CHLPCR, &err);
	अगर (err < 0)
		जाओ err_disable_func;

	sdio_ग_लिखोl(bdev->func, 0, MTK_REG_CHIER, &err);
	अगर (err < 0)
		जाओ err_disable_func;

	err = sdio_claim_irq(bdev->func, bपंचांगtksdio_पूर्णांकerrupt);
	अगर (err < 0)
		जाओ err_disable_func;

	err = sdio_set_block_size(bdev->func, MTK_SDIO_BLOCK_SIZE);
	अगर (err < 0)
		जाओ err_release_irq;

	/* SDIO CMD 5 allows the SDIO device back to idle state an
	 * synchronous पूर्णांकerrupt is supported in SDIO 4-bit mode
	 */
	sdio_ग_लिखोl(bdev->func, SDIO_INT_CTL | SDIO_RE_INIT_EN,
		    MTK_REG_CSDIOCSR, &err);
	अगर (err < 0)
		जाओ err_release_irq;

	/* Setup ग_लिखो-1-clear क्रम CHISR रेजिस्टर */
	sdio_ग_लिखोl(bdev->func, C_INT_CLR_CTRL, MTK_REG_CHCR, &err);
	अगर (err < 0)
		जाओ err_release_irq;

	/* Setup पूर्णांकerrupt sources */
	sdio_ग_लिखोl(bdev->func, RX_DONE_INT | TX_EMPTY | TX_FIFO_OVERFLOW,
		    MTK_REG_CHIER, &err);
	अगर (err < 0)
		जाओ err_release_irq;

	/* Enable पूर्णांकerrupt */
	sdio_ग_लिखोl(bdev->func, C_INT_EN_SET, MTK_REG_CHLPCR, &err);
	अगर (err < 0)
		जाओ err_release_irq;

	sdio_release_host(bdev->func);

	वापस 0;

err_release_irq:
	sdio_release_irq(bdev->func);

err_disable_func:
	sdio_disable_func(bdev->func);

err_release_host:
	sdio_release_host(bdev->func);

	वापस err;
पूर्ण

अटल पूर्णांक bपंचांगtksdio_बंद(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bपंचांगtksdio_dev *bdev = hci_get_drvdata(hdev);
	u32 status;
	पूर्णांक err;

	sdio_claim_host(bdev->func);

	/* Disable पूर्णांकerrupt */
	sdio_ग_लिखोl(bdev->func, C_INT_EN_CLR, MTK_REG_CHLPCR, शून्य);

	sdio_release_irq(bdev->func);

	/* Return ownership to the device */
	sdio_ग_लिखोl(bdev->func, C_FW_OWN_REQ_SET, MTK_REG_CHLPCR, शून्य);

	err = पढ़ोx_poll_समयout(bपंचांगtksdio_drv_own_query, bdev, status,
				 !(status & C_COM_DRV_OWN), 2000, 1000000);
	अगर (err < 0)
		bt_dev_err(bdev->hdev, "Cannot return ownership to device");

	sdio_disable_func(bdev->func);

	sdio_release_host(bdev->func);

	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगtksdio_flush(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bपंचांगtksdio_dev *bdev = hci_get_drvdata(hdev);

	skb_queue_purge(&bdev->txq);

	cancel_work_sync(&bdev->tx_work);

	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगtksdio_func_query(काष्ठा hci_dev *hdev)
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

अटल पूर्णांक mtk_setup_firmware(काष्ठा hci_dev *hdev, स्थिर अक्षर *fwname)
अणु
	काष्ठा bपंचांगtk_hci_wmt_params wmt_params;
	स्थिर काष्ठा firmware *fw;
	स्थिर u8 *fw_ptr;
	माप_प्रकार fw_size;
	पूर्णांक err, dlen;
	u8 flag, param;

	err = request_firmware(&fw, fwname, &hdev->dev);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to load firmware file (%d)", err);
		वापस err;
	पूर्ण

	/* Power on data RAM the firmware relies on. */
	param = 1;
	wmt_params.op = MTK_WMT_FUNC_CTRL;
	wmt_params.flag = 3;
	wmt_params.dlen = माप(param);
	wmt_params.data = &param;
	wmt_params.status = शून्य;

	err = mtk_hci_wmt_sync(hdev, &wmt_params);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to power on data RAM (%d)", err);
		जाओ मुक्त_fw;
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

अटल पूर्णांक bपंचांगtksdio_setup(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bपंचांगtksdio_dev *bdev = hci_get_drvdata(hdev);
	काष्ठा bपंचांगtk_hci_wmt_params wmt_params;
	kसमय_प्रकार callसमय, delta, retसमय;
	काष्ठा bपंचांगtk_tci_sleep tci_sleep;
	अचिन्हित दीर्घ दीर्घ duration;
	काष्ठा sk_buff *skb;
	पूर्णांक err, status;
	u8 param = 0x1;

	callसमय = kसमय_get();

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
	err = पढ़ोx_poll_समयout(bपंचांगtksdio_func_query, hdev, status,
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

	pm_runसमय_set_स्वतःsuspend_delay(bdev->dev,
					 MTKBTSDIO_AUTOSUSPEND_DELAY);
	pm_runसमय_use_स्वतःsuspend(bdev->dev);

	err = pm_runसमय_set_active(bdev->dev);
	अगर (err < 0)
		वापस err;

	/* Default क्रमbid runसमय स्वतः suspend, that can be allowed by
	 * enable_स्वतःsuspend flag or the PM runसमय entry under sysfs.
	 */
	pm_runसमय_क्रमbid(bdev->dev);
	pm_runसमय_enable(bdev->dev);

	अगर (enable_स्वतःsuspend)
		pm_runसमय_allow(bdev->dev);

	bt_dev_info(hdev, "Device setup in %llu usecs", duration);

	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगtksdio_shutकरोwn(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bपंचांगtksdio_dev *bdev = hci_get_drvdata(hdev);
	काष्ठा bपंचांगtk_hci_wmt_params wmt_params;
	u8 param = 0x0;
	पूर्णांक err;

	/* Get back the state to be consistent with the state
	 * in bपंचांगtksdio_setup.
	 */
	pm_runसमय_get_sync(bdev->dev);

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

	pm_runसमय_put_noidle(bdev->dev);
	pm_runसमय_disable(bdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगtksdio_send_frame(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा bपंचांगtksdio_dev *bdev = hci_get_drvdata(hdev);

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

	skb_queue_tail(&bdev->txq, skb);

	schedule_work(&bdev->tx_work);

	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगtksdio_probe(काष्ठा sdio_func *func,
			   स्थिर काष्ठा sdio_device_id *id)
अणु
	काष्ठा bपंचांगtksdio_dev *bdev;
	काष्ठा hci_dev *hdev;
	पूर्णांक err;

	bdev = devm_kzalloc(&func->dev, माप(*bdev), GFP_KERNEL);
	अगर (!bdev)
		वापस -ENOMEM;

	bdev->data = (व्योम *)id->driver_data;
	अगर (!bdev->data)
		वापस -ENODEV;

	bdev->dev = &func->dev;
	bdev->func = func;

	INIT_WORK(&bdev->tx_work, bपंचांगtksdio_tx_work);
	skb_queue_head_init(&bdev->txq);

	/* Initialize and रेजिस्टर HCI device */
	hdev = hci_alloc_dev();
	अगर (!hdev) अणु
		dev_err(&func->dev, "Can't allocate HCI device\n");
		वापस -ENOMEM;
	पूर्ण

	bdev->hdev = hdev;

	hdev->bus = HCI_SDIO;
	hci_set_drvdata(hdev, bdev);

	hdev->खोलो     = bपंचांगtksdio_खोलो;
	hdev->बंद    = bपंचांगtksdio_बंद;
	hdev->flush    = bपंचांगtksdio_flush;
	hdev->setup    = bपंचांगtksdio_setup;
	hdev->shutकरोwn = bपंचांगtksdio_shutकरोwn;
	hdev->send     = bपंचांगtksdio_send_frame;
	SET_HCIDEV_DEV(hdev, &func->dev);

	hdev->manufacturer = 70;
	set_bit(HCI_QUIRK_NON_PERSISTENT_SETUP, &hdev->quirks);

	err = hci_रेजिस्टर_dev(hdev);
	अगर (err < 0) अणु
		dev_err(&func->dev, "Can't register HCI device\n");
		hci_मुक्त_dev(hdev);
		वापस err;
	पूर्ण

	sdio_set_drvdata(func, bdev);

	/* pm_runसमय_enable would be करोne after the firmware is being
	 * करोwnloaded because the core layer probably alपढ़ोy enables
	 * runसमय PM क्रम this func such as the हाल host->caps &
	 * MMC_CAP_POWER_OFF_CARD.
	 */
	अगर (pm_runसमय_enabled(bdev->dev))
		pm_runसमय_disable(bdev->dev);

	/* As explaination in drivers/mmc/core/sdio_bus.c tells us:
	 * Unbound SDIO functions are always suspended.
	 * During probe, the function is set active and the usage count
	 * is incremented.  If the driver supports runसमय PM,
	 * it should call pm_runसमय_put_noidle() in its probe routine and
	 * pm_runसमय_get_noresume() in its हटाओ routine.
	 *
	 * So, put a pm_runसमय_put_noidle here !
	 */
	pm_runसमय_put_noidle(bdev->dev);

	वापस 0;
पूर्ण

अटल व्योम bपंचांगtksdio_हटाओ(काष्ठा sdio_func *func)
अणु
	काष्ठा bपंचांगtksdio_dev *bdev = sdio_get_drvdata(func);
	काष्ठा hci_dev *hdev;

	अगर (!bdev)
		वापस;

	/* Be consistent the state in bपंचांगtksdio_probe */
	pm_runसमय_get_noresume(bdev->dev);

	hdev = bdev->hdev;

	sdio_set_drvdata(func, शून्य);
	hci_unरेजिस्टर_dev(hdev);
	hci_मुक्त_dev(hdev);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक bपंचांगtksdio_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);
	काष्ठा bपंचांगtksdio_dev *bdev;
	u32 status;
	पूर्णांक err;

	bdev = sdio_get_drvdata(func);
	अगर (!bdev)
		वापस 0;

	sdio_claim_host(bdev->func);

	sdio_ग_लिखोl(bdev->func, C_FW_OWN_REQ_SET, MTK_REG_CHLPCR, &err);
	अगर (err < 0)
		जाओ out;

	err = पढ़ोx_poll_समयout(bपंचांगtksdio_drv_own_query, bdev, status,
				 !(status & C_COM_DRV_OWN), 2000, 1000000);
out:
	bt_dev_info(bdev->hdev, "status (%d) return ownership to device", err);

	sdio_release_host(bdev->func);

	वापस err;
पूर्ण

अटल पूर्णांक bपंचांगtksdio_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);
	काष्ठा bपंचांगtksdio_dev *bdev;
	u32 status;
	पूर्णांक err;

	bdev = sdio_get_drvdata(func);
	अगर (!bdev)
		वापस 0;

	sdio_claim_host(bdev->func);

	sdio_ग_लिखोl(bdev->func, C_FW_OWN_REQ_CLR, MTK_REG_CHLPCR, &err);
	अगर (err < 0)
		जाओ out;

	err = पढ़ोx_poll_समयout(bपंचांगtksdio_drv_own_query, bdev, status,
				 status & C_COM_DRV_OWN, 2000, 1000000);
out:
	bt_dev_info(bdev->hdev, "status (%d) get ownership from device", err);

	sdio_release_host(bdev->func);

	वापस err;
पूर्ण

अटल UNIVERSAL_DEV_PM_OPS(bपंचांगtksdio_pm_ops, bपंचांगtksdio_runसमय_suspend,
			    bपंचांगtksdio_runसमय_resume, शून्य);
#घोषणा BTMTKSDIO_PM_OPS (&bपंचांगtksdio_pm_ops)
#अन्यथा	/* CONFIG_PM */
#घोषणा BTMTKSDIO_PM_OPS शून्य
#पूर्ण_अगर	/* CONFIG_PM */

अटल काष्ठा sdio_driver bपंचांगtksdio_driver = अणु
	.name		= "btmtksdio",
	.probe		= bपंचांगtksdio_probe,
	.हटाओ		= bपंचांगtksdio_हटाओ,
	.id_table	= bपंचांगtksdio_table,
	.drv = अणु
		.owner = THIS_MODULE,
		.pm = BTMTKSDIO_PM_OPS,
	पूर्ण
पूर्ण;

module_sdio_driver(bपंचांगtksdio_driver);

module_param(enable_स्वतःsuspend, bool, 0644);
MODULE_PARM_DESC(enable_स्वतःsuspend, "Enable autosuspend by default");

MODULE_AUTHOR("Sean Wang <sean.wang@mediatek.com>");
MODULE_DESCRIPTION("MediaTek Bluetooth SDIO driver ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(FIRMWARE_MT7663);
MODULE_FIRMWARE(FIRMWARE_MT7668);
