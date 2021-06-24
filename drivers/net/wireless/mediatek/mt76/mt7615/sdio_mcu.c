<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2020 MediaTek Inc.
 *
 * Author: Felix Fietkau <nbd@nbd.name>
 *	   Lorenzo Bianconi <lorenzo@kernel.org>
 *	   Sean Wang <sean.wang@mediatek.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/module.h>
#समावेश <linux/iopoll.h>

#समावेश "mt7615.h"
#समावेश "mac.h"
#समावेश "mcu.h"
#समावेश "regs.h"
#समावेश "sdio.h"

अटल पूर्णांक mt7663s_mcu_init_sched(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा mt76_sdio *sdio = &dev->mt76.sdio;
	u32 txdwcnt;

	sdio->sched.pse_data_quota = mt76_get_field(dev, MT_PSE_PG_HIF0_GROUP,
						    MT_HIF0_MIN_QUOTA);
	sdio->sched.pse_mcu_quota = mt76_get_field(dev, MT_PSE_PG_HIF1_GROUP,
						   MT_HIF1_MIN_QUOTA);
	sdio->sched.ple_data_quota = mt76_get_field(dev, MT_PLE_PG_HIF0_GROUP,
						    MT_HIF0_MIN_QUOTA);
	txdwcnt = mt76_get_field(dev, MT_PP_TXDWCNT,
				 MT_PP_TXDWCNT_TX1_ADD_DW_CNT);
	sdio->sched.deficit = txdwcnt << 2;

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7663s_mcu_send_message(काष्ठा mt76_dev *mdev, काष्ठा sk_buff *skb,
			 पूर्णांक cmd, पूर्णांक *seq)
अणु
	काष्ठा mt7615_dev *dev = container_of(mdev, काष्ठा mt7615_dev, mt76);
	पूर्णांक ret;

	mt7615_mcu_fill_msg(dev, skb, cmd, seq);
	ret = mt76_tx_queue_skb_raw(dev, mdev->q_mcu[MT_MCUQ_WM], skb, 0);
	अगर (ret)
		वापस ret;

	mt76_queue_kick(dev, mdev->q_mcu[MT_MCUQ_WM]);

	वापस ret;
पूर्ण

अटल पूर्णांक __mt7663s_mcu_drv_pmctrl(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा sdio_func *func = dev->mt76.sdio.func;
	काष्ठा mt76_phy *mphy = &dev->mt76.phy;
	u32 status;
	पूर्णांक ret;

	sdio_claim_host(func);

	sdio_ग_लिखोl(func, WHLPCR_FW_OWN_REQ_CLR, MCR_WHLPCR, शून्य);

	ret = पढ़ोx_poll_समयout(mt7663s_पढ़ो_pcr, dev, status,
				 status & WHLPCR_IS_DRIVER_OWN, 2000, 1000000);
	अगर (ret < 0) अणु
		dev_err(dev->mt76.dev, "Cannot get ownership from device");
		set_bit(MT76_STATE_PM, &mphy->state);
		sdio_release_host(func);

		वापस ret;
	पूर्ण

	sdio_release_host(func);
	dev->pm.last_activity = jअगरfies;

	वापस 0;
पूर्ण

अटल पूर्णांक mt7663s_mcu_drv_pmctrl(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा mt76_phy *mphy = &dev->mt76.phy;

	अगर (test_and_clear_bit(MT76_STATE_PM, &mphy->state))
		वापस __mt7663s_mcu_drv_pmctrl(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7663s_mcu_fw_pmctrl(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा sdio_func *func = dev->mt76.sdio.func;
	काष्ठा mt76_phy *mphy = &dev->mt76.phy;
	u32 status;
	पूर्णांक ret;

	अगर (test_and_set_bit(MT76_STATE_PM, &mphy->state))
		वापस 0;

	sdio_claim_host(func);

	sdio_ग_लिखोl(func, WHLPCR_FW_OWN_REQ_SET, MCR_WHLPCR, शून्य);

	ret = पढ़ोx_poll_समयout(mt7663s_पढ़ो_pcr, dev, status,
				 !(status & WHLPCR_IS_DRIVER_OWN), 2000, 1000000);
	अगर (ret < 0) अणु
		dev_err(dev->mt76.dev, "Cannot set ownership to device");
		clear_bit(MT76_STATE_PM, &mphy->state);
	पूर्ण

	sdio_release_host(func);

	वापस ret;
पूर्ण

पूर्णांक mt7663s_mcu_init(काष्ठा mt7615_dev *dev)
अणु
	अटल स्थिर काष्ठा mt76_mcu_ops mt7663s_mcu_ops = अणु
		.headroom = माप(काष्ठा mt7615_mcu_txd),
		.tailroom = MT_USB_TAIL_SIZE,
		.mcu_skb_send_msg = mt7663s_mcu_send_message,
		.mcu_parse_response = mt7615_mcu_parse_response,
		.mcu_restart = mt7615_mcu_restart,
		.mcu_rr = mt7615_mcu_reg_rr,
		.mcu_wr = mt7615_mcu_reg_wr,
	पूर्ण;
	काष्ठा mt7615_mcu_ops *mcu_ops;
	पूर्णांक ret;

	ret = __mt7663s_mcu_drv_pmctrl(dev);
	अगर (ret)
		वापस ret;

	dev->mt76.mcu_ops = &mt7663s_mcu_ops,

	ret = mt76_get_field(dev, MT_CONN_ON_MISC, MT_TOP_MISC2_FW_N9_RDY);
	अगर (ret) अणु
		mt7615_mcu_restart(&dev->mt76);
		अगर (!mt76_poll_msec(dev, MT_CONN_ON_MISC,
				    MT_TOP_MISC2_FW_N9_RDY, 0, 500))
			वापस -EIO;
	पूर्ण

	ret = __mt7663_load_firmware(dev);
	अगर (ret)
		वापस ret;

	mcu_ops = devm_kmemdup(dev->mt76.dev, dev->mcu_ops, माप(*mcu_ops),
			       GFP_KERNEL);
	अगर (!mcu_ops)
		वापस -ENOMEM;

	mcu_ops->set_drv_ctrl = mt7663s_mcu_drv_pmctrl;
	mcu_ops->set_fw_ctrl = mt7663s_mcu_fw_pmctrl;
	dev->mcu_ops = mcu_ops;

	ret = mt7663s_mcu_init_sched(dev);
	अगर (ret)
		वापस ret;

	set_bit(MT76_STATE_MCU_RUNNING, &dev->mphy.state);

	वापस 0;
पूर्ण
