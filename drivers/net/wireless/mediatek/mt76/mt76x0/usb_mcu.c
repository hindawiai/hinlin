<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>

#समावेश "mt76x0.h"
#समावेश "mcu.h"
#समावेश "../mt76x02_usb.h"

#घोषणा MCU_FW_URB_MAX_PAYLOAD		0x38f8
#घोषणा MCU_FW_URB_SIZE			(MCU_FW_URB_MAX_PAYLOAD + 12)

अटल पूर्णांक
mt76x0u_upload_firmware(काष्ठा mt76x02_dev *dev,
			स्थिर काष्ठा mt76x02_fw_header *hdr)
अणु
	u8 *fw_payload = (u8 *)(hdr + 1);
	u32 ilm_len, dlm_len;
	व्योम *ivb;
	पूर्णांक err;

	ivb = kmemdup(fw_payload, MT_MCU_IVB_SIZE, GFP_KERNEL);
	अगर (!ivb)
		वापस -ENOMEM;

	ilm_len = le32_to_cpu(hdr->ilm_len) - MT_MCU_IVB_SIZE;
	dev_dbg(dev->mt76.dev, "loading FW - ILM %u + IVB %u\n",
		ilm_len, MT_MCU_IVB_SIZE);
	err = mt76x02u_mcu_fw_send_data(dev, fw_payload + MT_MCU_IVB_SIZE,
					ilm_len, MCU_FW_URB_MAX_PAYLOAD,
					MT_MCU_IVB_SIZE);
	अगर (err)
		जाओ out;

	dlm_len = le32_to_cpu(hdr->dlm_len);
	dev_dbg(dev->mt76.dev, "loading FW - DLM %u\n", dlm_len);
	err = mt76x02u_mcu_fw_send_data(dev,
					fw_payload + le32_to_cpu(hdr->ilm_len),
					dlm_len, MCU_FW_URB_MAX_PAYLOAD,
					MT_MCU_DLM_OFFSET);
	अगर (err)
		जाओ out;

	err = mt76u_venकरोr_request(&dev->mt76, MT_VEND_DEV_MODE,
				   USB_सूची_OUT | USB_TYPE_VENDOR,
				   0x12, 0, ivb, MT_MCU_IVB_SIZE);
	अगर (err < 0)
		जाओ out;

	अगर (!mt76_poll_msec(dev, MT_MCU_COM_REG0, 1, 1, 1000)) अणु
		dev_err(dev->mt76.dev, "Firmware failed to start\n");
		err = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	dev_dbg(dev->mt76.dev, "Firmware running!\n");

out:
	kमुक्त(ivb);

	वापस err;
पूर्ण

अटल पूर्णांक mt76x0_get_firmware(काष्ठा mt76x02_dev *dev,
			       स्थिर काष्ठा firmware **fw)
अणु
	पूर्णांक err;

	/* try to load mt7610e fw अगर available
	 * otherwise fall back to mt7610u one
	 */
	err = firmware_request_nowarn(fw, MT7610E_FIRMWARE, dev->mt76.dev);
	अगर (err) अणु
		dev_info(dev->mt76.dev, "%s not found, switching to %s",
			 MT7610E_FIRMWARE, MT7610U_FIRMWARE);
		वापस request_firmware(fw, MT7610U_FIRMWARE,
					dev->mt76.dev);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mt76x0u_load_firmware(काष्ठा mt76x02_dev *dev)
अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर काष्ठा mt76x02_fw_header *hdr;
	पूर्णांक len, ret;
	u32 val;

	mt76_wr(dev, MT_USB_DMA_CFG, (MT_USB_DMA_CFG_RX_BULK_EN |
				      MT_USB_DMA_CFG_TX_BULK_EN));

	अगर (mt76x0_firmware_running(dev))
		वापस 0;

	ret = mt76x0_get_firmware(dev, &fw);
	अगर (ret)
		वापस ret;

	अगर (!fw || !fw->data || fw->size < माप(*hdr))
		जाओ err_inv_fw;

	hdr = (स्थिर काष्ठा mt76x02_fw_header *)fw->data;

	अगर (le32_to_cpu(hdr->ilm_len) <= MT_MCU_IVB_SIZE)
		जाओ err_inv_fw;

	len = माप(*hdr);
	len += le32_to_cpu(hdr->ilm_len);
	len += le32_to_cpu(hdr->dlm_len);

	अगर (fw->size != len)
		जाओ err_inv_fw;

	val = le16_to_cpu(hdr->fw_ver);
	dev_dbg(dev->mt76.dev,
		"Firmware Version: %d.%d.%02d Build: %x Build time: %.16s\n",
		(val >> 12) & 0xf, (val >> 8) & 0xf, val & 0xf,
		le16_to_cpu(hdr->build_ver), hdr->build_समय);

	len = le32_to_cpu(hdr->ilm_len);

	mt76_wr(dev, 0x1004, 0x2c);

	mt76_set(dev, MT_USB_DMA_CFG,
		 (MT_USB_DMA_CFG_RX_BULK_EN | MT_USB_DMA_CFG_TX_BULK_EN) |
		 FIELD_PREP(MT_USB_DMA_CFG_RX_BULK_AGG_TOUT, 0x20));
	mt76x02u_mcu_fw_reset(dev);
	usleep_range(5000, 6000);

	mt76_wr(dev, MT_FCE_PSE_CTRL, 1);

	/* FCE tx_fs_base_ptr */
	mt76_wr(dev, MT_TX_CPU_FROM_FCE_BASE_PTR, 0x400230);
	/* FCE tx_fs_max_cnt */
	mt76_wr(dev, MT_TX_CPU_FROM_FCE_MAX_COUNT, 1);
	/* FCE pdma enable */
	mt76_wr(dev, MT_FCE_PDMA_GLOBAL_CONF, 0x44);
	/* FCE skip_fs_en */
	mt76_wr(dev, MT_FCE_SKIP_FS, 3);

	val = mt76_rr(dev, MT_USB_DMA_CFG);
	val |= MT_USB_DMA_CFG_UDMA_TX_WL_DROP;
	mt76_wr(dev, MT_USB_DMA_CFG, val);
	val &= ~MT_USB_DMA_CFG_UDMA_TX_WL_DROP;
	mt76_wr(dev, MT_USB_DMA_CFG, val);

	ret = mt76x0u_upload_firmware(dev, hdr);
	release_firmware(fw);

	mt76_wr(dev, MT_FCE_PSE_CTRL, 1);

	वापस ret;

err_inv_fw:
	dev_err(dev->mt76.dev, "Invalid firmware image\n");
	release_firmware(fw);
	वापस -ENOENT;
पूर्ण

पूर्णांक mt76x0u_mcu_init(काष्ठा mt76x02_dev *dev)
अणु
	पूर्णांक ret;

	ret = mt76x0u_load_firmware(dev);
	अगर (ret < 0)
		वापस ret;

	set_bit(MT76_STATE_MCU_RUNNING, &dev->mphy.state);

	वापस 0;
पूर्ण
