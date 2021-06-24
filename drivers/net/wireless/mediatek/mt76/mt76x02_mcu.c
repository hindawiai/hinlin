<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/firmware.h>
#समावेश <linux/delay.h>

#समावेश "mt76x02_mcu.h"

पूर्णांक mt76x02_mcu_parse_response(काष्ठा mt76_dev *mdev, पूर्णांक cmd,
			       काष्ठा sk_buff *skb, पूर्णांक seq)
अणु
	काष्ठा mt76x02_dev *dev = container_of(mdev, काष्ठा mt76x02_dev, mt76);
	u32 *rxfce;

	अगर (!skb) अणु
		dev_err(mdev->dev, "MCU message %02x (seq %d) timed out\n",
			असल(cmd), seq);
		dev->mcu_समयout = 1;
		वापस -ETIMEDOUT;
	पूर्ण

	rxfce = (u32 *)skb->cb;
	अगर (seq != FIELD_GET(MT_RX_FCE_INFO_CMD_SEQ, *rxfce))
		वापस -EAGAIN;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_mcu_parse_response);

पूर्णांक mt76x02_mcu_msg_send(काष्ठा mt76_dev *mdev, पूर्णांक cmd, स्थिर व्योम *data,
			 पूर्णांक len, bool रुको_resp)
अणु
	काष्ठा mt76x02_dev *dev = container_of(mdev, काष्ठा mt76x02_dev, mt76);
	अचिन्हित दीर्घ expires = jअगरfies + HZ;
	काष्ठा sk_buff *skb;
	u32 tx_info;
	पूर्णांक ret;
	u8 seq;

	अगर (dev->mcu_समयout)
		वापस -EIO;

	skb = mt76_mcu_msg_alloc(mdev, data, len);
	अगर (!skb)
		वापस -ENOMEM;

	mutex_lock(&mdev->mcu.mutex);

	seq = ++mdev->mcu.msg_seq & 0xf;
	अगर (!seq)
		seq = ++mdev->mcu.msg_seq & 0xf;

	tx_info = MT_MCU_MSG_TYPE_CMD |
		  FIELD_PREP(MT_MCU_MSG_CMD_TYPE, cmd) |
		  FIELD_PREP(MT_MCU_MSG_CMD_SEQ, seq) |
		  FIELD_PREP(MT_MCU_MSG_PORT, CPU_TX_PORT) |
		  FIELD_PREP(MT_MCU_MSG_LEN, skb->len);

	ret = mt76_tx_queue_skb_raw(dev, mdev->q_mcu[MT_MCUQ_WM], skb, tx_info);
	अगर (ret)
		जाओ out;

	जबतक (रुको_resp) अणु
		skb = mt76_mcu_get_response(&dev->mt76, expires);
		ret = mt76x02_mcu_parse_response(mdev, cmd, skb, seq);
		dev_kमुक्त_skb(skb);
		अगर (ret != -EAGAIN)
			अवरोध;
	पूर्ण

out:
	mutex_unlock(&mdev->mcu.mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_mcu_msg_send);

पूर्णांक mt76x02_mcu_function_select(काष्ठा mt76x02_dev *dev, क्रमागत mcu_function func,
				u32 val)
अणु
	काष्ठा अणु
		__le32 id;
		__le32 value;
	पूर्ण __packed __aligned(4) msg = अणु
		.id = cpu_to_le32(func),
		.value = cpu_to_le32(val),
	पूर्ण;
	bool रुको = false;

	अगर (func != Q_SELECT)
		रुको = true;

	वापस mt76_mcu_send_msg(&dev->mt76, CMD_FUN_SET_OP, &msg,
				 माप(msg), रुको);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_mcu_function_select);

पूर्णांक mt76x02_mcu_set_radio_state(काष्ठा mt76x02_dev *dev, bool on)
अणु
	काष्ठा अणु
		__le32 mode;
		__le32 level;
	पूर्ण __packed __aligned(4) msg = अणु
		.mode = cpu_to_le32(on ? RADIO_ON : RADIO_OFF),
		.level = cpu_to_le32(0),
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, CMD_POWER_SAVING_OP, &msg,
				 माप(msg), false);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_mcu_set_radio_state);

पूर्णांक mt76x02_mcu_calibrate(काष्ठा mt76x02_dev *dev, पूर्णांक type, u32 param)
अणु
	काष्ठा अणु
		__le32 id;
		__le32 value;
	पूर्ण __packed __aligned(4) msg = अणु
		.id = cpu_to_le32(type),
		.value = cpu_to_le32(param),
	पूर्ण;
	bool is_mt76x2e = mt76_is_mmio(&dev->mt76) && is_mt76x2(dev);
	पूर्णांक ret;

	अगर (is_mt76x2e)
		mt76_rmw(dev, MT_MCU_COM_REG0, BIT(31), 0);

	ret = mt76_mcu_send_msg(&dev->mt76, CMD_CALIBRATION_OP, &msg,
				माप(msg), true);
	अगर (ret)
		वापस ret;

	अगर (is_mt76x2e &&
	    WARN_ON(!mt76_poll_msec(dev, MT_MCU_COM_REG0,
				    BIT(31), BIT(31), 100)))
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_mcu_calibrate);

पूर्णांक mt76x02_mcu_cleanup(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा sk_buff *skb;

	mt76_wr(dev, MT_MCU_INT_LEVEL, 1);
	usleep_range(20000, 30000);

	जबतक ((skb = skb_dequeue(&dev->mt76.mcu.res_q)) != शून्य)
		dev_kमुक्त_skb(skb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_mcu_cleanup);

व्योम mt76x02_set_ethtool_fwver(काष्ठा mt76x02_dev *dev,
			       स्थिर काष्ठा mt76x02_fw_header *h)
अणु
	u16 bld = le16_to_cpu(h->build_ver);
	u16 ver = le16_to_cpu(h->fw_ver);

	snम_लिखो(dev->mt76.hw->wiphy->fw_version,
		 माप(dev->mt76.hw->wiphy->fw_version),
		 "%d.%d.%02d-b%x",
		 (ver >> 12) & 0xf, (ver >> 8) & 0xf, ver & 0xf, bld);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_set_ethtool_fwver);
