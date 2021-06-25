<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/firmware.h>

#समावेश "mt76x02.h"
#समावेश "mt76x02_mcu.h"
#समावेश "mt76x02_usb.h"

#घोषणा MT_CMD_HDR_LEN			4

#घोषणा MT_FCE_DMA_ADDR			0x0230
#घोषणा MT_FCE_DMA_LEN			0x0234

#घोषणा MT_TX_CPU_FROM_FCE_CPU_DESC_IDX	0x09a8

अटल व्योम
mt76x02u_multiple_mcu_पढ़ोs(काष्ठा mt76_dev *dev, u8 *data, पूर्णांक len)
अणु
	काष्ठा mt76_usb *usb = &dev->usb;
	u32 reg, val;
	पूर्णांक i;

	अगर (usb->mcu.burst) अणु
		WARN_ON_ONCE(len / 4 != usb->mcu.rp_len);

		reg = usb->mcu.rp[0].reg - usb->mcu.base;
		क्रम (i = 0; i < usb->mcu.rp_len; i++) अणु
			val = get_unaligned_le32(data + 4 * i);
			usb->mcu.rp[i].reg = reg++;
			usb->mcu.rp[i].value = val;
		पूर्ण
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(len / 8 != usb->mcu.rp_len);

		क्रम (i = 0; i < usb->mcu.rp_len; i++) अणु
			reg = get_unaligned_le32(data + 8 * i) -
			      usb->mcu.base;
			val = get_unaligned_le32(data + 8 * i + 4);

			WARN_ON_ONCE(usb->mcu.rp[i].reg != reg);
			usb->mcu.rp[i].value = val;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mt76x02u_mcu_रुको_resp(काष्ठा mt76_dev *dev, u8 seq)
अणु
	काष्ठा mt76_usb *usb = &dev->usb;
	u8 *data = usb->mcu.data;
	पूर्णांक i, len, ret;
	u32 rxfce;

	क्रम (i = 0; i < 5; i++) अणु
		ret = mt76u_bulk_msg(dev, data, MCU_RESP_URB_SIZE, &len,
				     300, MT_EP_IN_CMD_RESP);
		अगर (ret == -ETIMEDOUT)
			जारी;
		अगर (ret)
			जाओ out;

		अगर (usb->mcu.rp)
			mt76x02u_multiple_mcu_पढ़ोs(dev, data + 4, len - 8);

		rxfce = get_unaligned_le32(data);
		अगर (seq == FIELD_GET(MT_RX_FCE_INFO_CMD_SEQ, rxfce) &&
		    FIELD_GET(MT_RX_FCE_INFO_EVT_TYPE, rxfce) == EVT_CMD_DONE)
			वापस 0;

		dev_err(dev->dev, "error: MCU resp evt:%lx seq:%hhx-%lx\n",
			FIELD_GET(MT_RX_FCE_INFO_EVT_TYPE, rxfce),
			seq, FIELD_GET(MT_RX_FCE_INFO_CMD_SEQ, rxfce));
	पूर्ण
out:
	dev_err(dev->dev, "error: %s failed with %d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक
__mt76x02u_mcu_send_msg(काष्ठा mt76_dev *dev, काष्ठा sk_buff *skb,
			पूर्णांक cmd, bool रुको_resp)
अणु
	u8 seq = 0;
	u32 info;
	पूर्णांक ret;

	अगर (test_bit(MT76_REMOVED, &dev->phy.state)) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	अगर (रुको_resp) अणु
		seq = ++dev->mcu.msg_seq & 0xf;
		अगर (!seq)
			seq = ++dev->mcu.msg_seq & 0xf;
	पूर्ण

	info = FIELD_PREP(MT_MCU_MSG_CMD_SEQ, seq) |
	       FIELD_PREP(MT_MCU_MSG_CMD_TYPE, cmd) |
	       MT_MCU_MSG_TYPE_CMD;
	ret = mt76x02u_skb_dma_info(skb, CPU_TX_PORT, info);
	अगर (ret)
		वापस ret;

	ret = mt76u_bulk_msg(dev, skb->data, skb->len, शून्य, 500,
			     MT_EP_OUT_INBAND_CMD);
	अगर (ret)
		वापस ret;

	अगर (रुको_resp)
		ret = mt76x02u_mcu_रुको_resp(dev, seq);

out:
	consume_skb(skb);

	वापस ret;
पूर्ण

अटल पूर्णांक
mt76x02u_mcu_send_msg(काष्ठा mt76_dev *dev, पूर्णांक cmd, स्थिर व्योम *data,
		      पूर्णांक len, bool रुको_resp)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	skb = mt76_mcu_msg_alloc(dev, data, len);
	अगर (!skb)
		वापस -ENOMEM;

	mutex_lock(&dev->mcu.mutex);
	err = __mt76x02u_mcu_send_msg(dev, skb, cmd, रुको_resp);
	mutex_unlock(&dev->mcu.mutex);

	वापस err;
पूर्ण

अटल अंतरभूत व्योम skb_put_le32(काष्ठा sk_buff *skb, u32 val)
अणु
	put_unaligned_le32(val, skb_put(skb, 4));
पूर्ण

अटल पूर्णांक
mt76x02u_mcu_wr_rp(काष्ठा mt76_dev *dev, u32 base,
		   स्थिर काष्ठा mt76_reg_pair *data, पूर्णांक n)
अणु
	स्थिर पूर्णांक max_vals_per_cmd = MT_INBAND_PACKET_MAX_LEN / 8;
	स्थिर पूर्णांक CMD_RANDOM_WRITE = 12;
	काष्ठा sk_buff *skb;
	पूर्णांक cnt, i, ret;

	अगर (!n)
		वापस 0;

	cnt = min(max_vals_per_cmd, n);

	skb = alloc_skb(cnt * 8 + MT_DMA_HDR_LEN + 4, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;
	skb_reserve(skb, MT_DMA_HDR_LEN);

	क्रम (i = 0; i < cnt; i++) अणु
		skb_put_le32(skb, base + data[i].reg);
		skb_put_le32(skb, data[i].value);
	पूर्ण

	mutex_lock(&dev->mcu.mutex);
	ret = __mt76x02u_mcu_send_msg(dev, skb, CMD_RANDOM_WRITE, cnt == n);
	mutex_unlock(&dev->mcu.mutex);
	अगर (ret)
		वापस ret;

	वापस mt76x02u_mcu_wr_rp(dev, base, data + cnt, n - cnt);
पूर्ण

अटल पूर्णांक
mt76x02u_mcu_rd_rp(काष्ठा mt76_dev *dev, u32 base,
		   काष्ठा mt76_reg_pair *data, पूर्णांक n)
अणु
	स्थिर पूर्णांक CMD_RANDOM_READ = 10;
	स्थिर पूर्णांक max_vals_per_cmd = MT_INBAND_PACKET_MAX_LEN / 8;
	काष्ठा mt76_usb *usb = &dev->usb;
	काष्ठा sk_buff *skb;
	पूर्णांक cnt, i, ret;

	अगर (!n)
		वापस 0;

	cnt = min(max_vals_per_cmd, n);
	अगर (cnt != n)
		वापस -EINVAL;

	skb = alloc_skb(cnt * 8 + MT_DMA_HDR_LEN + 4, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;
	skb_reserve(skb, MT_DMA_HDR_LEN);

	क्रम (i = 0; i < cnt; i++) अणु
		skb_put_le32(skb, base + data[i].reg);
		skb_put_le32(skb, data[i].value);
	पूर्ण

	mutex_lock(&dev->mcu.mutex);

	usb->mcu.rp = data;
	usb->mcu.rp_len = n;
	usb->mcu.base = base;
	usb->mcu.burst = false;

	ret = __mt76x02u_mcu_send_msg(dev, skb, CMD_RANDOM_READ, true);

	usb->mcu.rp = शून्य;

	mutex_unlock(&dev->mcu.mutex);

	वापस ret;
पूर्ण

व्योम mt76x02u_mcu_fw_reset(काष्ठा mt76x02_dev *dev)
अणु
	mt76u_venकरोr_request(&dev->mt76, MT_VEND_DEV_MODE,
			     USB_सूची_OUT | USB_TYPE_VENDOR,
			     0x1, 0, शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02u_mcu_fw_reset);

अटल पूर्णांक
__mt76x02u_mcu_fw_send_data(काष्ठा mt76x02_dev *dev, u8 *data,
			    स्थिर व्योम *fw_data, पूर्णांक len, u32 dst_addr)
अणु
	__le32 info;
	u32 val;
	पूर्णांक err, data_len;

	info = cpu_to_le32(FIELD_PREP(MT_MCU_MSG_PORT, CPU_TX_PORT) |
			   FIELD_PREP(MT_MCU_MSG_LEN, len) |
			   MT_MCU_MSG_TYPE_CMD);

	स_नकल(data, &info, माप(info));
	स_नकल(data + माप(info), fw_data, len);
	स_रखो(data + माप(info) + len, 0, 4);

	mt76u_single_wr(&dev->mt76, MT_VEND_WRITE_FCE,
			MT_FCE_DMA_ADDR, dst_addr);
	len = roundup(len, 4);
	mt76u_single_wr(&dev->mt76, MT_VEND_WRITE_FCE,
			MT_FCE_DMA_LEN, len << 16);

	data_len = MT_CMD_HDR_LEN + len + माप(info);

	err = mt76u_bulk_msg(&dev->mt76, data, data_len, शून्य, 1000,
			     MT_EP_OUT_INBAND_CMD);
	अगर (err) अणु
		dev_err(dev->mt76.dev, "firmware upload failed: %d\n", err);
		वापस err;
	पूर्ण

	val = mt76_rr(dev, MT_TX_CPU_FROM_FCE_CPU_DESC_IDX);
	val++;
	mt76_wr(dev, MT_TX_CPU_FROM_FCE_CPU_DESC_IDX, val);

	वापस 0;
पूर्ण

पूर्णांक mt76x02u_mcu_fw_send_data(काष्ठा mt76x02_dev *dev, स्थिर व्योम *data,
			      पूर्णांक data_len, u32 max_payload, u32 offset)
अणु
	पूर्णांक len, err = 0, pos = 0, max_len = max_payload - 8;
	u8 *buf;

	buf = kदो_स्मृति(max_payload, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	जबतक (data_len > 0) अणु
		len = min_t(पूर्णांक, data_len, max_len);
		err = __mt76x02u_mcu_fw_send_data(dev, buf, data + pos,
						  len, offset + pos);
		अगर (err < 0)
			अवरोध;

		data_len -= len;
		pos += len;
		usleep_range(5000, 10000);
	पूर्ण
	kमुक्त(buf);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02u_mcu_fw_send_data);

व्योम mt76x02u_init_mcu(काष्ठा mt76_dev *dev)
अणु
	अटल स्थिर काष्ठा mt76_mcu_ops mt76x02u_mcu_ops = अणु
		.headroom = MT_CMD_HDR_LEN,
		.tailroom = 8,
		.mcu_send_msg = mt76x02u_mcu_send_msg,
		.mcu_parse_response = mt76x02_mcu_parse_response,
		.mcu_wr_rp = mt76x02u_mcu_wr_rp,
		.mcu_rd_rp = mt76x02u_mcu_rd_rp,
	पूर्ण;

	dev->mcu_ops = &mt76x02u_mcu_ops;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02u_init_mcu);

MODULE_AUTHOR("Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>");
MODULE_LICENSE("Dual BSD/GPL");
