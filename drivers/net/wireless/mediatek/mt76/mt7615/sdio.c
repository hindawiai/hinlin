<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc.
 *
 * Author: Felix Fietkau <nbd@nbd.name>
 *	   Lorenzo Bianconi <lorenzo@kernel.org>
 *	   Sean Wang <sean.wang@mediatek.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>

#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/sdio_ids.h>
#समावेश <linux/mmc/sdio_func.h>

#समावेश "mt7615.h"
#समावेश "sdio.h"
#समावेश "mac.h"
#समावेश "mcu.h"

अटल स्थिर काष्ठा sdio_device_id mt7663s_table[] = अणु
	अणु SDIO_DEVICE(SDIO_VENDOR_ID_MEDIATEK, 0x7603) पूर्ण,
	अणु पूर्ण	/* Terminating entry */
पूर्ण;

अटल u32 mt7663s_पढ़ो_whisr(काष्ठा mt76_dev *dev)
अणु
	वापस sdio_पढ़ोl(dev->sdio.func, MCR_WHISR, शून्य);
पूर्ण

u32 mt7663s_पढ़ो_pcr(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा mt76_sdio *sdio = &dev->mt76.sdio;

	वापस sdio_पढ़ोl(sdio->func, MCR_WHLPCR, शून्य);
पूर्ण

अटल u32 mt7663s_पढ़ो_mailbox(काष्ठा mt76_dev *dev, u32 offset)
अणु
	काष्ठा sdio_func *func = dev->sdio.func;
	u32 val = ~0, status;
	पूर्णांक err;

	sdio_claim_host(func);

	sdio_ग_लिखोl(func, offset, MCR_H2DSM0R, &err);
	अगर (err < 0) अणु
		dev_err(dev->dev, "failed setting address [err=%d]\n", err);
		जाओ out;
	पूर्ण

	sdio_ग_लिखोl(func, H2D_SW_INT_READ, MCR_WSICR, &err);
	अगर (err < 0) अणु
		dev_err(dev->dev, "failed setting read mode [err=%d]\n", err);
		जाओ out;
	पूर्ण

	err = पढ़ोx_poll_समयout(mt7663s_पढ़ो_whisr, dev, status,
				 status & H2D_SW_INT_READ, 0, 1000000);
	अगर (err < 0) अणु
		dev_err(dev->dev, "query whisr timeout\n");
		जाओ out;
	पूर्ण

	sdio_ग_लिखोl(func, H2D_SW_INT_READ, MCR_WHISR, &err);
	अगर (err < 0) अणु
		dev_err(dev->dev, "failed setting read mode [err=%d]\n", err);
		जाओ out;
	पूर्ण

	val = sdio_पढ़ोl(func, MCR_H2DSM0R, &err);
	अगर (err < 0) अणु
		dev_err(dev->dev, "failed reading h2dsm0r [err=%d]\n", err);
		जाओ out;
	पूर्ण

	अगर (val != offset) अणु
		dev_err(dev->dev, "register mismatch\n");
		val = ~0;
		जाओ out;
	पूर्ण

	val = sdio_पढ़ोl(func, MCR_D2HRM1R, &err);
	अगर (err < 0)
		dev_err(dev->dev, "failed reading d2hrm1r [err=%d]\n", err);

out:
	sdio_release_host(func);

	वापस val;
पूर्ण

अटल व्योम mt7663s_ग_लिखो_mailbox(काष्ठा mt76_dev *dev, u32 offset, u32 val)
अणु
	काष्ठा sdio_func *func = dev->sdio.func;
	u32 status;
	पूर्णांक err;

	sdio_claim_host(func);

	sdio_ग_लिखोl(func, offset, MCR_H2DSM0R, &err);
	अगर (err < 0) अणु
		dev_err(dev->dev, "failed setting address [err=%d]\n", err);
		जाओ out;
	पूर्ण

	sdio_ग_लिखोl(func, val, MCR_H2DSM1R, &err);
	अगर (err < 0) अणु
		dev_err(dev->dev,
			"failed setting write value [err=%d]\n", err);
		जाओ out;
	पूर्ण

	sdio_ग_लिखोl(func, H2D_SW_INT_WRITE, MCR_WSICR, &err);
	अगर (err < 0) अणु
		dev_err(dev->dev, "failed setting write mode [err=%d]\n", err);
		जाओ out;
	पूर्ण

	err = पढ़ोx_poll_समयout(mt7663s_पढ़ो_whisr, dev, status,
				 status & H2D_SW_INT_WRITE, 0, 1000000);
	अगर (err < 0) अणु
		dev_err(dev->dev, "query whisr timeout\n");
		जाओ out;
	पूर्ण

	sdio_ग_लिखोl(func, H2D_SW_INT_WRITE, MCR_WHISR, &err);
	अगर (err < 0) अणु
		dev_err(dev->dev, "failed setting write mode [err=%d]\n", err);
		जाओ out;
	पूर्ण

	val = sdio_पढ़ोl(func, MCR_H2DSM0R, &err);
	अगर (err < 0) अणु
		dev_err(dev->dev, "failed reading h2dsm0r [err=%d]\n", err);
		जाओ out;
	पूर्ण

	अगर (val != offset)
		dev_err(dev->dev, "register mismatch\n");

out:
	sdio_release_host(func);
पूर्ण

अटल u32 mt7663s_rr(काष्ठा mt76_dev *dev, u32 offset)
अणु
	अगर (test_bit(MT76_STATE_MCU_RUNNING, &dev->phy.state))
		वापस dev->mcu_ops->mcu_rr(dev, offset);
	अन्यथा
		वापस mt7663s_पढ़ो_mailbox(dev, offset);
पूर्ण

अटल व्योम mt7663s_wr(काष्ठा mt76_dev *dev, u32 offset, u32 val)
अणु
	अगर (test_bit(MT76_STATE_MCU_RUNNING, &dev->phy.state))
		dev->mcu_ops->mcu_wr(dev, offset, val);
	अन्यथा
		mt7663s_ग_लिखो_mailbox(dev, offset, val);
पूर्ण

अटल u32 mt7663s_rmw(काष्ठा mt76_dev *dev, u32 offset, u32 mask, u32 val)
अणु
	val |= mt7663s_rr(dev, offset) & ~mask;
	mt7663s_wr(dev, offset, val);

	वापस val;
पूर्ण

अटल व्योम mt7663s_ग_लिखो_copy(काष्ठा mt76_dev *dev, u32 offset,
			       स्थिर व्योम *data, पूर्णांक len)
अणु
	स्थिर u32 *val = data;
	पूर्णांक i;

	क्रम (i = 0; i < len / माप(u32); i++) अणु
		mt7663s_wr(dev, offset, val[i]);
		offset += माप(u32);
	पूर्ण
पूर्ण

अटल व्योम mt7663s_पढ़ो_copy(काष्ठा mt76_dev *dev, u32 offset,
			      व्योम *data, पूर्णांक len)
अणु
	u32 *val = data;
	पूर्णांक i;

	क्रम (i = 0; i < len / माप(u32); i++) अणु
		val[i] = mt7663s_rr(dev, offset);
		offset += माप(u32);
	पूर्ण
पूर्ण

अटल पूर्णांक mt7663s_wr_rp(काष्ठा mt76_dev *dev, u32 base,
			 स्थिर काष्ठा mt76_reg_pair *data,
			 पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		mt7663s_wr(dev, data->reg, data->value);
		data++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt7663s_rd_rp(काष्ठा mt76_dev *dev, u32 base,
			 काष्ठा mt76_reg_pair *data,
			 पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		data->value = mt7663s_rr(dev, data->reg);
		data++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mt7663s_init_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7615_dev *dev;

	dev = container_of(work, काष्ठा mt7615_dev, mcu_work);
	अगर (mt7663s_mcu_init(dev))
		वापस;

	mt7615_init_work(dev);
पूर्ण

अटल पूर्णांक mt7663s_hw_init(काष्ठा mt7615_dev *dev, काष्ठा sdio_func *func)
अणु
	u32 status, ctrl;
	पूर्णांक ret;

	sdio_claim_host(func);

	ret = sdio_enable_func(func);
	अगर (ret < 0)
		जाओ release;

	/* Get ownership from the device */
	sdio_ग_लिखोl(func, WHLPCR_INT_EN_CLR | WHLPCR_FW_OWN_REQ_CLR,
		    MCR_WHLPCR, &ret);
	अगर (ret < 0)
		जाओ disable_func;

	ret = पढ़ोx_poll_समयout(mt7663s_पढ़ो_pcr, dev, status,
				 status & WHLPCR_IS_DRIVER_OWN, 2000, 1000000);
	अगर (ret < 0) अणु
		dev_err(dev->mt76.dev, "Cannot get ownership from device");
		जाओ disable_func;
	पूर्ण

	ret = sdio_set_block_size(func, 512);
	अगर (ret < 0)
		जाओ disable_func;

	/* Enable पूर्णांकerrupt */
	sdio_ग_लिखोl(func, WHLPCR_INT_EN_SET, MCR_WHLPCR, &ret);
	अगर (ret < 0)
		जाओ disable_func;

	ctrl = WHIER_RX0_DONE_INT_EN | WHIER_TX_DONE_INT_EN;
	sdio_ग_लिखोl(func, ctrl, MCR_WHIER, &ret);
	अगर (ret < 0)
		जाओ disable_func;

	/* set WHISR as पढ़ो clear and Rx aggregation number as 16 */
	ctrl = FIELD_PREP(MAX_HIF_RX_LEN_NUM, 16);
	sdio_ग_लिखोl(func, ctrl, MCR_WHCR, &ret);
	अगर (ret < 0)
		जाओ disable_func;

	ret = sdio_claim_irq(func, mt7663s_sdio_irq);
	अगर (ret < 0)
		जाओ disable_func;

	sdio_release_host(func);

	वापस 0;

disable_func:
	sdio_disable_func(func);
release:
	sdio_release_host(func);

	वापस ret;
पूर्ण

अटल पूर्णांक mt7663s_probe(काष्ठा sdio_func *func,
			 स्थिर काष्ठा sdio_device_id *id)
अणु
	अटल स्थिर काष्ठा mt76_driver_ops drv_ops = अणु
		.txwi_size = MT_USB_TXD_SIZE,
		.drv_flags = MT_DRV_RX_DMA_HDR,
		.tx_prepare_skb = mt7663_usb_sdio_tx_prepare_skb,
		.tx_complete_skb = mt7663_usb_sdio_tx_complete_skb,
		.tx_status_data = mt7663_usb_sdio_tx_status_data,
		.rx_skb = mt7615_queue_rx_skb,
		.sta_ps = mt7615_sta_ps,
		.sta_add = mt7615_mac_sta_add,
		.sta_हटाओ = mt7615_mac_sta_हटाओ,
		.update_survey = mt7615_update_channel,
	पूर्ण;
	अटल स्थिर काष्ठा mt76_bus_ops mt7663s_ops = अणु
		.rr = mt7663s_rr,
		.rmw = mt7663s_rmw,
		.wr = mt7663s_wr,
		.ग_लिखो_copy = mt7663s_ग_लिखो_copy,
		.पढ़ो_copy = mt7663s_पढ़ो_copy,
		.wr_rp = mt7663s_wr_rp,
		.rd_rp = mt7663s_rd_rp,
		.type = MT76_BUS_SDIO,
	पूर्ण;
	काष्ठा ieee80211_ops *ops;
	काष्ठा mt7615_dev *dev;
	काष्ठा mt76_dev *mdev;
	पूर्णांक i, ret;

	ops = devm_kmemdup(&func->dev, &mt7615_ops, माप(mt7615_ops),
			   GFP_KERNEL);
	अगर (!ops)
		वापस -ENOMEM;

	mdev = mt76_alloc_device(&func->dev, माप(*dev), ops, &drv_ops);
	अगर (!mdev)
		वापस -ENOMEM;

	dev = container_of(mdev, काष्ठा mt7615_dev, mt76);

	INIT_WORK(&dev->mcu_work, mt7663s_init_work);
	dev->reg_map = mt7663_usb_sdio_reg_map;
	dev->ops = ops;
	sdio_set_drvdata(func, dev);

	ret = mt76s_init(mdev, func, &mt7663s_ops);
	अगर (ret < 0)
		जाओ error;

	ret = mt7663s_hw_init(dev, func);
	अगर (ret)
		जाओ error;

	mdev->rev = (mt76_rr(dev, MT_HW_CHIPID) << 16) |
		    (mt76_rr(dev, MT_HW_REV) & 0xff);
	dev_dbg(mdev->dev, "ASIC revision: %04x\n", mdev->rev);

	mdev->sdio.पूर्णांकr_data = devm_kदो_स्मृति(mdev->dev,
					    माप(काष्ठा mt76s_पूर्णांकr),
					    GFP_KERNEL);
	अगर (!mdev->sdio.पूर्णांकr_data) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(mdev->sdio.xmit_buf); i++) अणु
		mdev->sdio.xmit_buf[i] = devm_kदो_स्मृति(mdev->dev,
						      MT76S_XMIT_BUF_SZ,
						      GFP_KERNEL);
		अगर (!mdev->sdio.xmit_buf[i]) अणु
			ret = -ENOMEM;
			जाओ error;
		पूर्ण
	पूर्ण

	ret = mt76s_alloc_queues(&dev->mt76);
	अगर (ret)
		जाओ error;

	ret = mt76_worker_setup(mt76_hw(dev), &mdev->sdio.txrx_worker,
				mt7663s_txrx_worker, "sdio-txrx");
	अगर (ret)
		जाओ error;

	sched_set_fअगरo_low(mdev->sdio.txrx_worker.task);

	ret = mt7663_usb_sdio_रेजिस्टर_device(dev);
	अगर (ret)
		जाओ error;

	वापस 0;

error:
	mt76s_deinit(&dev->mt76);
	mt76_मुक्त_device(&dev->mt76);

	वापस ret;
पूर्ण

अटल व्योम mt7663s_हटाओ(काष्ठा sdio_func *func)
अणु
	काष्ठा mt7615_dev *dev = sdio_get_drvdata(func);

	अगर (!test_and_clear_bit(MT76_STATE_INITIALIZED, &dev->mphy.state))
		वापस;

	ieee80211_unरेजिस्टर_hw(dev->mt76.hw);
	mt76s_deinit(&dev->mt76);
	mt76_मुक्त_device(&dev->mt76);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mt7663s_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);
	काष्ठा mt7615_dev *mdev = sdio_get_drvdata(func);
	पूर्णांक err;

	अगर (!test_bit(MT76_STATE_SUSPEND, &mdev->mphy.state) &&
	    mt7615_firmware_offload(mdev)) अणु
		पूर्णांक err;

		err = mt76_connac_mcu_set_hअगर_suspend(&mdev->mt76, true);
		अगर (err < 0)
			वापस err;
	पूर्ण

	sdio_set_host_pm_flags(func, MMC_PM_KEEP_POWER);

	err = mt7615_mcu_set_fw_ctrl(mdev);
	अगर (err)
		वापस err;

	mt76_worker_disable(&mdev->mt76.sdio.txrx_worker);
	mt76_worker_disable(&mdev->mt76.sdio.status_worker);
	mt76_worker_disable(&mdev->mt76.sdio.net_worker);

	cancel_work_sync(&mdev->mt76.sdio.stat_work);
	clear_bit(MT76_READING_STATS, &mdev->mphy.state);

	mt76_tx_status_check(&mdev->mt76, शून्य, true);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7663s_resume(काष्ठा device *dev)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);
	काष्ठा mt7615_dev *mdev = sdio_get_drvdata(func);
	पूर्णांक err;

	mt76_worker_enable(&mdev->mt76.sdio.txrx_worker);
	mt76_worker_enable(&mdev->mt76.sdio.status_worker);
	mt76_worker_enable(&mdev->mt76.sdio.net_worker);

	err = mt7615_mcu_set_drv_ctrl(mdev);
	अगर (err)
		वापस err;

	अगर (!test_bit(MT76_STATE_SUSPEND, &mdev->mphy.state) &&
	    mt7615_firmware_offload(mdev))
		err = mt76_connac_mcu_set_hअगर_suspend(&mdev->mt76, false);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mt7663s_pm_ops = अणु
	.suspend = mt7663s_suspend,
	.resume = mt7663s_resume,
पूर्ण;
#पूर्ण_अगर

MODULE_DEVICE_TABLE(sdio, mt7663s_table);
MODULE_FIRMWARE(MT7663_OFFLOAD_FIRMWARE_N9);
MODULE_FIRMWARE(MT7663_OFFLOAD_ROM_PATCH);
MODULE_FIRMWARE(MT7663_FIRMWARE_N9);
MODULE_FIRMWARE(MT7663_ROM_PATCH);

अटल काष्ठा sdio_driver mt7663s_driver = अणु
	.name		= KBUILD_MODNAME,
	.probe		= mt7663s_probe,
	.हटाओ		= mt7663s_हटाओ,
	.id_table	= mt7663s_table,
#अगर_घोषित CONFIG_PM
	.drv = अणु
		.pm = &mt7663s_pm_ops,
	पूर्ण
#पूर्ण_अगर
पूर्ण;
module_sdio_driver(mt7663s_driver);

MODULE_AUTHOR("Sean Wang <sean.wang@mediatek.com>");
MODULE_AUTHOR("Lorenzo Bianconi <lorenzo@kernel.org>");
MODULE_LICENSE("Dual BSD/GPL");
