<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2019 MediaTek Inc.
 *
 * Author: Felix Fietkau <nbd@nbd.name>
 *	   Lorenzo Bianconi <lorenzo@kernel.org>
 *	   Sean Wang <sean.wang@mediatek.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश "mt7615.h"
#समावेश "mac.h"
#समावेश "mcu.h"
#समावेश "regs.h"

अटल पूर्णांक
mt7663u_mcu_send_message(काष्ठा mt76_dev *mdev, काष्ठा sk_buff *skb,
			 पूर्णांक cmd, पूर्णांक *seq)
अणु
	काष्ठा mt7615_dev *dev = container_of(mdev, काष्ठा mt7615_dev, mt76);
	पूर्णांक ret, ep, len, pad;

	mt7615_mcu_fill_msg(dev, skb, cmd, seq);
	अगर (cmd != MCU_CMD_FW_SCATTER)
		ep = MT_EP_OUT_INBAND_CMD;
	अन्यथा
		ep = MT_EP_OUT_AC_BE;

	len = skb->len;
	put_unaligned_le32(len, skb_push(skb, माप(len)));
	pad = round_up(skb->len, 4) + 4 - skb->len;
	ret = mt76_skb_adjust_pad(skb, pad);
	अगर (ret < 0)
		जाओ out;

	ret = mt76u_bulk_msg(&dev->mt76, skb->data, skb->len, शून्य,
			     1000, ep);

out:
	dev_kमुक्त_skb(skb);

	वापस ret;
पूर्ण

पूर्णांक mt7663u_mcu_init(काष्ठा mt7615_dev *dev)
अणु
	अटल स्थिर काष्ठा mt76_mcu_ops mt7663u_mcu_ops = अणु
		.headroom = MT_USB_HDR_SIZE + माप(काष्ठा mt7615_mcu_txd),
		.tailroom = MT_USB_TAIL_SIZE,
		.mcu_skb_send_msg = mt7663u_mcu_send_message,
		.mcu_parse_response = mt7615_mcu_parse_response,
		.mcu_restart = mt7615_mcu_restart,
	पूर्ण;
	पूर्णांक ret;

	dev->mt76.mcu_ops = &mt7663u_mcu_ops,

	mt76_set(dev, MT_UDMA_TX_QSEL, MT_FW_DL_EN);
	अगर (test_and_clear_bit(MT76_STATE_POWER_OFF, &dev->mphy.state)) अणु
		mt7615_mcu_restart(&dev->mt76);
		अगर (!mt76_poll_msec(dev, MT_CONN_ON_MISC,
				    MT_TOP_MISC2_FW_PWR_ON, 0, 500))
			वापस -EIO;

		ret = mt76u_venकरोr_request(&dev->mt76, MT_VEND_POWER_ON,
					   USB_सूची_OUT | USB_TYPE_VENDOR,
					   0x0, 0x1, शून्य, 0);
		अगर (ret)
			वापस ret;

		अगर (!mt76_poll_msec(dev, MT_CONN_ON_MISC,
				    MT_TOP_MISC2_FW_PWR_ON,
				    FW_STATE_PWR_ON << 1, 500)) अणु
			dev_err(dev->mt76.dev, "Timeout for power on\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	ret = __mt7663_load_firmware(dev);
	अगर (ret)
		वापस ret;

	mt76_clear(dev, MT_UDMA_TX_QSEL, MT_FW_DL_EN);
	set_bit(MT76_STATE_MCU_RUNNING, &dev->mphy.state);

	वापस 0;
पूर्ण
