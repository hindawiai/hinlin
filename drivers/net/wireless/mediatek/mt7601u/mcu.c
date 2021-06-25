<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (c) Copyright 2002-2010, Ralink Technology, Inc.
 * Copyright (C) 2014 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/firmware.h>
#समावेश <linux/delay.h>
#समावेश <linux/usb.h>
#समावेश <linux/skbuff.h>

#समावेश "mt7601u.h"
#समावेश "dma.h"
#समावेश "mcu.h"
#समावेश "usb.h"
#समावेश "trace.h"

#घोषणा MCU_FW_URB_MAX_PAYLOAD		0x3800
#घोषणा MCU_FW_URB_SIZE			(MCU_FW_URB_MAX_PAYLOAD + 12)
#घोषणा MCU_RESP_URB_SIZE		1024

अटल अंतरभूत पूर्णांक firmware_running(काष्ठा mt7601u_dev *dev)
अणु
	वापस mt7601u_rr(dev, MT_MCU_COM_REG0) == 1;
पूर्ण

अटल अंतरभूत व्योम skb_put_le32(काष्ठा sk_buff *skb, u32 val)
अणु
	put_unaligned_le32(val, skb_put(skb, 4));
पूर्ण

अटल अंतरभूत व्योम mt7601u_dma_skb_wrap_cmd(काष्ठा sk_buff *skb,
					    u8 seq, क्रमागत mcu_cmd cmd)
अणु
	WARN_ON(mt7601u_dma_skb_wrap(skb, CPU_TX_PORT, DMA_COMMAND,
				     FIELD_PREP(MT_TXD_CMD_INFO_SEQ, seq) |
				     FIELD_PREP(MT_TXD_CMD_INFO_TYPE, cmd)));
पूर्ण

अटल अंतरभूत व्योम trace_mt_mcu_msg_send_cs(काष्ठा mt7601u_dev *dev,
					    काष्ठा sk_buff *skb, bool need_resp)
अणु
	u32 i, csum = 0;

	क्रम (i = 0; i < skb->len / 4; i++)
		csum ^= get_unaligned_le32(skb->data + i * 4);

	trace_mt_mcu_msg_send(dev, skb, csum, need_resp);
पूर्ण

अटल काष्ठा sk_buff *mt7601u_mcu_msg_alloc(स्थिर व्योम *data, पूर्णांक len)
अणु
	काष्ठा sk_buff *skb;

	WARN_ON(len % 4); /* अगर length is not भागisible by 4 we need to pad */

	skb = alloc_skb(len + MT_DMA_HDR_LEN + 4, GFP_KERNEL);
	अगर (skb) अणु
		skb_reserve(skb, MT_DMA_HDR_LEN);
		skb_put_data(skb, data, len);
	पूर्ण

	वापस skb;
पूर्ण

अटल पूर्णांक mt7601u_mcu_रुको_resp(काष्ठा mt7601u_dev *dev, u8 seq)
अणु
	काष्ठा urb *urb = dev->mcu.resp.urb;
	u32 rxfce;
	पूर्णांक urb_status, ret, i = 5;

	जबतक (i--) अणु
		अगर (!रुको_क्रम_completion_समयout(&dev->mcu.resp_cmpl,
						 msecs_to_jअगरfies(300))) अणु
			dev_warn(dev->dev, "Warning: %s retrying\n", __func__);
			जारी;
		पूर्ण

		/* Make copies of important data beक्रमe reusing the urb */
		rxfce = get_unaligned_le32(dev->mcu.resp.buf);
		urb_status = urb->status * mt7601u_urb_has_error(urb);

		ret = mt7601u_usb_submit_buf(dev, USB_सूची_IN, MT_EP_IN_CMD_RESP,
					     &dev->mcu.resp, GFP_KERNEL,
					     mt7601u_complete_urb,
					     &dev->mcu.resp_cmpl);
		अगर (ret)
			वापस ret;

		अगर (urb_status)
			dev_err(dev->dev, "Error: MCU resp urb failed:%d\n",
				urb_status);

		अगर (FIELD_GET(MT_RXD_CMD_INFO_CMD_SEQ, rxfce) == seq &&
		    FIELD_GET(MT_RXD_CMD_INFO_EVT_TYPE, rxfce) == CMD_DONE)
			वापस 0;

		dev_err(dev->dev, "Error: MCU resp evt:%lx seq:%hhx-%lx!\n",
			FIELD_GET(MT_RXD_CMD_INFO_EVT_TYPE, rxfce),
			seq, FIELD_GET(MT_RXD_CMD_INFO_CMD_SEQ, rxfce));
	पूर्ण

	dev_err(dev->dev, "Error: %s timed out\n", __func__);
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक
mt7601u_mcu_msg_send(काष्ठा mt7601u_dev *dev, काष्ठा sk_buff *skb,
		     क्रमागत mcu_cmd cmd, bool रुको_resp)
अणु
	काष्ठा usb_device *usb_dev = mt7601u_to_usb_dev(dev);
	अचिन्हित cmd_pipe = usb_sndbulkpipe(usb_dev,
					    dev->out_eps[MT_EP_OUT_INBAND_CMD]);
	पूर्णांक sent, ret;
	u8 seq = 0;

	अगर (test_bit(MT7601U_STATE_REMOVED, &dev->state)) अणु
		consume_skb(skb);
		वापस 0;
	पूर्ण

	mutex_lock(&dev->mcu.mutex);

	अगर (रुको_resp)
		जबतक (!seq)
			seq = ++dev->mcu.msg_seq & 0xf;

	mt7601u_dma_skb_wrap_cmd(skb, seq, cmd);

	अगर (dev->mcu.resp_cmpl.करोne)
		dev_err(dev->dev, "Error: MCU response pre-completed!\n");

	trace_mt_mcu_msg_send_cs(dev, skb, रुको_resp);
	trace_mt_submit_urb_sync(dev, cmd_pipe, skb->len);
	ret = usb_bulk_msg(usb_dev, cmd_pipe, skb->data, skb->len, &sent, 500);
	अगर (ret) अणु
		dev_err(dev->dev, "Error: send MCU cmd failed:%d\n", ret);
		जाओ out;
	पूर्ण
	अगर (sent != skb->len)
		dev_err(dev->dev, "Error: %s sent != skb->len\n", __func__);

	अगर (रुको_resp)
		ret = mt7601u_mcu_रुको_resp(dev, seq);
out:
	mutex_unlock(&dev->mcu.mutex);

	consume_skb(skb);

	वापस ret;
पूर्ण

अटल पूर्णांक mt7601u_mcu_function_select(काष्ठा mt7601u_dev *dev,
				       क्रमागत mcu_function func, u32 val)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा अणु
		__le32 id;
		__le32 value;
	पूर्ण __packed __aligned(4) msg = अणु
		.id = cpu_to_le32(func),
		.value = cpu_to_le32(val),
	पूर्ण;

	skb = mt7601u_mcu_msg_alloc(&msg, माप(msg));
	अगर (!skb)
		वापस -ENOMEM;
	वापस mt7601u_mcu_msg_send(dev, skb, CMD_FUN_SET_OP, func == 5);
पूर्ण

पूर्णांक mt7601u_mcu_tssi_पढ़ो_kick(काष्ठा mt7601u_dev *dev, पूर्णांक use_hvga)
अणु
	पूर्णांक ret;

	अगर (!test_bit(MT7601U_STATE_MCU_RUNNING, &dev->state))
		वापस 0;

	ret = mt7601u_mcu_function_select(dev, ATOMIC_TSSI_SETTING,
					  use_hvga);
	अगर (ret) अणु
		dev_warn(dev->dev, "Warning: MCU TSSI read kick failed\n");
		वापस ret;
	पूर्ण

	dev->tssi_पढ़ो_trig = true;

	वापस 0;
पूर्ण

पूर्णांक
mt7601u_mcu_calibrate(काष्ठा mt7601u_dev *dev, क्रमागत mcu_calibrate cal, u32 val)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा अणु
		__le32 id;
		__le32 value;
	पूर्ण __packed __aligned(4) msg = अणु
		.id = cpu_to_le32(cal),
		.value = cpu_to_le32(val),
	पूर्ण;

	skb = mt7601u_mcu_msg_alloc(&msg, माप(msg));
	अगर (!skb)
		वापस -ENOMEM;
	वापस mt7601u_mcu_msg_send(dev, skb, CMD_CALIBRATION_OP, true);
पूर्ण

पूर्णांक mt7601u_ग_लिखो_reg_pairs(काष्ठा mt7601u_dev *dev, u32 base,
			    स्थिर काष्ठा mt76_reg_pair *data, पूर्णांक n)
अणु
	स्थिर पूर्णांक max_vals_per_cmd = INBAND_PACKET_MAX_LEN / 8;
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

	ret = mt7601u_mcu_msg_send(dev, skb, CMD_RANDOM_WRITE, cnt == n);
	अगर (ret)
		वापस ret;

	वापस mt7601u_ग_लिखो_reg_pairs(dev, base, data + cnt, n - cnt);
पूर्ण

पूर्णांक mt7601u_burst_ग_लिखो_regs(काष्ठा mt7601u_dev *dev, u32 offset,
			     स्थिर u32 *data, पूर्णांक n)
अणु
	स्थिर पूर्णांक max_regs_per_cmd = INBAND_PACKET_MAX_LEN / 4 - 1;
	काष्ठा sk_buff *skb;
	पूर्णांक cnt, i, ret;

	अगर (!n)
		वापस 0;

	cnt = min(max_regs_per_cmd, n);

	skb = alloc_skb(cnt * 4 + MT_DMA_HDR_LEN + 4, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;
	skb_reserve(skb, MT_DMA_HDR_LEN);

	skb_put_le32(skb, MT_MCU_MEMMAP_WLAN + offset);
	क्रम (i = 0; i < cnt; i++)
		skb_put_le32(skb, data[i]);

	ret = mt7601u_mcu_msg_send(dev, skb, CMD_BURST_WRITE, cnt == n);
	अगर (ret)
		वापस ret;

	वापस mt7601u_burst_ग_लिखो_regs(dev, offset + cnt * 4,
					data + cnt, n - cnt);
पूर्ण

काष्ठा mt76_fw_header अणु
	__le32 ilm_len;
	__le32 dlm_len;
	__le16 build_ver;
	__le16 fw_ver;
	u8 pad[4];
	अक्षर build_समय[16];
पूर्ण;

काष्ठा mt76_fw अणु
	काष्ठा mt76_fw_header hdr;
	u8 ivb[MT_MCU_IVB_SIZE];
	u8 ilm[];
पूर्ण;

अटल पूर्णांक __mt7601u_dma_fw(काष्ठा mt7601u_dev *dev,
			    स्थिर काष्ठा mt7601u_dma_buf *dma_buf,
			    स्थिर व्योम *data, u32 len, u32 dst_addr)
अणु
	DECLARE_COMPLETION_ONSTACK(cmpl);
	काष्ठा mt7601u_dma_buf buf = *dma_buf; /* we need to fake length */
	__le32 reg;
	u32 val;
	पूर्णांक ret;

	reg = cpu_to_le32(FIELD_PREP(MT_TXD_INFO_TYPE, DMA_PACKET) |
			  FIELD_PREP(MT_TXD_INFO_D_PORT, CPU_TX_PORT) |
			  FIELD_PREP(MT_TXD_INFO_LEN, len));
	स_नकल(buf.buf, &reg, माप(reg));
	स_नकल(buf.buf + माप(reg), data, len);
	स_रखो(buf.buf + माप(reg) + len, 0, 8);

	ret = mt7601u_venकरोr_single_wr(dev, MT_VEND_WRITE_FCE,
				       MT_FCE_DMA_ADDR, dst_addr);
	अगर (ret)
		वापस ret;
	len = roundup(len, 4);
	ret = mt7601u_venकरोr_single_wr(dev, MT_VEND_WRITE_FCE,
				       MT_FCE_DMA_LEN, len << 16);
	अगर (ret)
		वापस ret;

	buf.len = MT_DMA_HDR_LEN + len + 4;
	ret = mt7601u_usb_submit_buf(dev, USB_सूची_OUT, MT_EP_OUT_INBAND_CMD,
				     &buf, GFP_KERNEL,
				     mt7601u_complete_urb, &cmpl);
	अगर (ret)
		वापस ret;

	अगर (!रुको_क्रम_completion_समयout(&cmpl, msecs_to_jअगरfies(1000))) अणु
		dev_err(dev->dev, "Error: firmware upload timed out\n");
		usb_समाप्त_urb(buf.urb);
		वापस -ETIMEDOUT;
	पूर्ण
	अगर (mt7601u_urb_has_error(buf.urb)) अणु
		dev_err(dev->dev, "Error: firmware upload urb failed:%d\n",
			buf.urb->status);
		वापस buf.urb->status;
	पूर्ण

	val = mt7601u_rr(dev, MT_TX_CPU_FROM_FCE_CPU_DESC_IDX);
	val++;
	mt7601u_wr(dev, MT_TX_CPU_FROM_FCE_CPU_DESC_IDX, val);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7601u_dma_fw(काष्ठा mt7601u_dev *dev, काष्ठा mt7601u_dma_buf *dma_buf,
	       स्थिर व्योम *data, पूर्णांक len, u32 dst_addr)
अणु
	पूर्णांक n, ret;

	अगर (len == 0)
		वापस 0;

	n = min(MCU_FW_URB_MAX_PAYLOAD, len);
	ret = __mt7601u_dma_fw(dev, dma_buf, data, n, dst_addr);
	अगर (ret)
		वापस ret;

	अगर (!mt76_poll_msec(dev, MT_MCU_COM_REG1, BIT(31), BIT(31), 500))
		वापस -ETIMEDOUT;

	वापस mt7601u_dma_fw(dev, dma_buf, data + n, len - n, dst_addr + n);
पूर्ण

अटल पूर्णांक
mt7601u_upload_firmware(काष्ठा mt7601u_dev *dev, स्थिर काष्ठा mt76_fw *fw)
अणु
	काष्ठा mt7601u_dma_buf dma_buf;
	व्योम *ivb;
	u32 ilm_len, dlm_len;
	पूर्णांक i, ret;

	ivb = kmemdup(fw->ivb, माप(fw->ivb), GFP_KERNEL);
	अगर (!ivb)
		वापस -ENOMEM;
	अगर (mt7601u_usb_alloc_buf(dev, MCU_FW_URB_SIZE, &dma_buf)) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	ilm_len = le32_to_cpu(fw->hdr.ilm_len) - माप(fw->ivb);
	dev_dbg(dev->dev, "loading FW - ILM %u + IVB %zu\n",
		ilm_len, माप(fw->ivb));
	ret = mt7601u_dma_fw(dev, &dma_buf, fw->ilm, ilm_len, माप(fw->ivb));
	अगर (ret)
		जाओ error;

	dlm_len = le32_to_cpu(fw->hdr.dlm_len);
	dev_dbg(dev->dev, "loading FW - DLM %u\n", dlm_len);
	ret = mt7601u_dma_fw(dev, &dma_buf, fw->ilm + ilm_len,
			     dlm_len, MT_MCU_DLM_OFFSET);
	अगर (ret)
		जाओ error;

	ret = mt7601u_venकरोr_request(dev, MT_VEND_DEV_MODE, USB_सूची_OUT,
				     0x12, 0, ivb, माप(fw->ivb));
	अगर (ret < 0)
		जाओ error;
	ret = 0;

	क्रम (i = 100; i && !firmware_running(dev); i--)
		msleep(10);
	अगर (!i) अणु
		ret = -ETIMEDOUT;
		जाओ error;
	पूर्ण

	dev_dbg(dev->dev, "Firmware running!\n");
error:
	kमुक्त(ivb);
	mt7601u_usb_मुक्त_buf(dev, &dma_buf);

	वापस ret;
पूर्ण

अटल पूर्णांक mt7601u_load_firmware(काष्ठा mt7601u_dev *dev)
अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर काष्ठा mt76_fw_header *hdr;
	पूर्णांक len, ret;
	u32 val;

	mt7601u_wr(dev, MT_USB_DMA_CFG, (MT_USB_DMA_CFG_RX_BULK_EN |
					 MT_USB_DMA_CFG_TX_BULK_EN));

	अगर (firmware_running(dev))
		वापस firmware_request_cache(dev->dev, MT7601U_FIRMWARE);

	ret = request_firmware(&fw, MT7601U_FIRMWARE, dev->dev);
	अगर (ret)
		वापस ret;

	अगर (!fw || !fw->data || fw->size < माप(*hdr))
		जाओ err_inv_fw;

	hdr = (स्थिर काष्ठा mt76_fw_header *) fw->data;

	अगर (le32_to_cpu(hdr->ilm_len) <= MT_MCU_IVB_SIZE)
		जाओ err_inv_fw;

	len = माप(*hdr);
	len += le32_to_cpu(hdr->ilm_len);
	len += le32_to_cpu(hdr->dlm_len);

	अगर (fw->size != len)
		जाओ err_inv_fw;

	val = le16_to_cpu(hdr->fw_ver);
	dev_info(dev->dev,
		 "Firmware Version: %d.%d.%02d Build: %x Build time: %.16s\n",
		 (val >> 12) & 0xf, (val >> 8) & 0xf, val & 0xf,
		 le16_to_cpu(hdr->build_ver), hdr->build_समय);

	len = le32_to_cpu(hdr->ilm_len);

	mt7601u_wr(dev, 0x94c, 0);
	mt7601u_wr(dev, MT_FCE_PSE_CTRL, 0);

	mt7601u_venकरोr_reset(dev);
	msleep(5);

	mt7601u_wr(dev, 0xa44, 0);
	mt7601u_wr(dev, 0x230, 0x84210);
	mt7601u_wr(dev, 0x400, 0x80c00);
	mt7601u_wr(dev, 0x800, 1);

	mt7601u_rmw(dev, MT_PBF_CFG, 0, (MT_PBF_CFG_TX0Q_EN |
					 MT_PBF_CFG_TX1Q_EN |
					 MT_PBF_CFG_TX2Q_EN |
					 MT_PBF_CFG_TX3Q_EN));

	mt7601u_wr(dev, MT_FCE_PSE_CTRL, 1);

	mt7601u_wr(dev, MT_USB_DMA_CFG, (MT_USB_DMA_CFG_RX_BULK_EN |
					 MT_USB_DMA_CFG_TX_BULK_EN));
	val = mt76_set(dev, MT_USB_DMA_CFG, MT_USB_DMA_CFG_TX_CLR);
	val &= ~MT_USB_DMA_CFG_TX_CLR;
	mt7601u_wr(dev, MT_USB_DMA_CFG, val);

	/* FCE tx_fs_base_ptr */
	mt7601u_wr(dev, MT_TX_CPU_FROM_FCE_BASE_PTR, 0x400230);
	/* FCE tx_fs_max_cnt */
	mt7601u_wr(dev, MT_TX_CPU_FROM_FCE_MAX_COUNT, 1);
	/* FCE pdma enable */
	mt7601u_wr(dev, MT_FCE_PDMA_GLOBAL_CONF, 0x44);
	/* FCE skip_fs_en */
	mt7601u_wr(dev, MT_FCE_SKIP_FS, 3);

	ret = mt7601u_upload_firmware(dev, (स्थिर काष्ठा mt76_fw *)fw->data);

	release_firmware(fw);

	वापस ret;

err_inv_fw:
	dev_err(dev->dev, "Invalid firmware image\n");
	release_firmware(fw);
	वापस -ENOENT;
पूर्ण

पूर्णांक mt7601u_mcu_init(काष्ठा mt7601u_dev *dev)
अणु
	पूर्णांक ret;

	mutex_init(&dev->mcu.mutex);

	ret = mt7601u_load_firmware(dev);
	अगर (ret)
		वापस ret;

	set_bit(MT7601U_STATE_MCU_RUNNING, &dev->state);

	वापस 0;
पूर्ण

पूर्णांक mt7601u_mcu_cmd_init(काष्ठा mt7601u_dev *dev)
अणु
	पूर्णांक ret;

	ret = mt7601u_mcu_function_select(dev, Q_SELECT, 1);
	अगर (ret)
		वापस ret;

	init_completion(&dev->mcu.resp_cmpl);
	अगर (mt7601u_usb_alloc_buf(dev, MCU_RESP_URB_SIZE, &dev->mcu.resp)) अणु
		mt7601u_usb_मुक्त_buf(dev, &dev->mcu.resp);
		वापस -ENOMEM;
	पूर्ण

	ret = mt7601u_usb_submit_buf(dev, USB_सूची_IN, MT_EP_IN_CMD_RESP,
				     &dev->mcu.resp, GFP_KERNEL,
				     mt7601u_complete_urb, &dev->mcu.resp_cmpl);
	अगर (ret) अणु
		mt7601u_usb_मुक्त_buf(dev, &dev->mcu.resp);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम mt7601u_mcu_cmd_deinit(काष्ठा mt7601u_dev *dev)
अणु
	usb_समाप्त_urb(dev->mcu.resp.urb);
	mt7601u_usb_मुक्त_buf(dev, &dev->mcu.resp);
पूर्ण
