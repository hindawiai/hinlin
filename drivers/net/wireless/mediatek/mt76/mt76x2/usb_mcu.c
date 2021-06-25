<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#समावेश <linux/firmware.h>

#समावेश "mt76x2u.h"
#समावेश "eeprom.h"
#समावेश "../mt76x02_usb.h"

#घोषणा MT_CMD_HDR_LEN			4

#घोषणा MCU_FW_URB_MAX_PAYLOAD		0x3900
#घोषणा MCU_ROM_PATCH_MAX_PAYLOAD	2048

#घोषणा MT76U_MCU_ILM_OFFSET		0x80000
#घोषणा MT76U_MCU_DLM_OFFSET		0x110000
#घोषणा MT76U_MCU_ROM_PATCH_OFFSET	0x90000

अटल व्योम mt76x2u_mcu_load_ivb(काष्ठा mt76x02_dev *dev)
अणु
	mt76u_venकरोr_request(&dev->mt76, MT_VEND_DEV_MODE,
			     USB_सूची_OUT | USB_TYPE_VENDOR,
			     0x12, 0, शून्य, 0);
पूर्ण

अटल व्योम mt76x2u_mcu_enable_patch(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा mt76_usb *usb = &dev->mt76.usb;
	अटल स्थिर u8 data[] = अणु
		0x6f, 0xfc, 0x08, 0x01,
		0x20, 0x04, 0x00, 0x00,
		0x00, 0x09, 0x00,
	पूर्ण;

	स_नकल(usb->data, data, माप(data));
	mt76u_venकरोr_request(&dev->mt76, MT_VEND_DEV_MODE,
			     USB_सूची_OUT | USB_TYPE_CLASS,
			     0x12, 0, usb->data, माप(data));
पूर्ण

अटल व्योम mt76x2u_mcu_reset_wmt(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा mt76_usb *usb = &dev->mt76.usb;
	u8 data[] = अणु
		0x6f, 0xfc, 0x05, 0x01,
		0x07, 0x01, 0x00, 0x04
	पूर्ण;

	स_नकल(usb->data, data, माप(data));
	mt76u_venकरोr_request(&dev->mt76, MT_VEND_DEV_MODE,
			     USB_सूची_OUT | USB_TYPE_CLASS,
			     0x12, 0, usb->data, माप(data));
पूर्ण

अटल पूर्णांक mt76x2u_mcu_load_rom_patch(काष्ठा mt76x02_dev *dev)
अणु
	bool rom_protect = !is_mt7612(dev);
	काष्ठा mt76x02_patch_header *hdr;
	u32 val, patch_mask, patch_reg;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक err;

	अगर (rom_protect &&
	    !mt76_poll_msec(dev, MT_MCU_SEMAPHORE_03, 1, 1, 600)) अणु
		dev_err(dev->mt76.dev,
			"could not get hardware semaphore for ROM PATCH\n");
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (mt76xx_rev(dev) >= MT76XX_REV_E3) अणु
		patch_mask = BIT(0);
		patch_reg = MT_MCU_CLOCK_CTL;
	पूर्ण अन्यथा अणु
		patch_mask = BIT(1);
		patch_reg = MT_MCU_COM_REG0;
	पूर्ण

	अगर (rom_protect && (mt76_rr(dev, patch_reg) & patch_mask)) अणु
		dev_info(dev->mt76.dev, "ROM patch already applied\n");
		वापस 0;
	पूर्ण

	err = request_firmware(&fw, MT7662_ROM_PATCH, dev->mt76.dev);
	अगर (err < 0)
		वापस err;

	अगर (!fw || !fw->data || fw->size <= माप(*hdr)) अणु
		dev_err(dev->mt76.dev, "failed to load firmware\n");
		err = -EIO;
		जाओ out;
	पूर्ण

	hdr = (काष्ठा mt76x02_patch_header *)fw->data;
	dev_info(dev->mt76.dev, "ROM patch build: %.15s\n", hdr->build_समय);

	/* enable USB_DMA_CFG */
	val = MT_USB_DMA_CFG_RX_BULK_EN |
	      MT_USB_DMA_CFG_TX_BULK_EN |
	      FIELD_PREP(MT_USB_DMA_CFG_RX_BULK_AGG_TOUT, 0x20);
	mt76_wr(dev, MT_VEND_ADDR(CFG, MT_USB_U3DMA_CFG), val);

	/* venकरोr reset */
	mt76x02u_mcu_fw_reset(dev);
	usleep_range(5000, 10000);

	/* enable FCE to send in-band cmd */
	mt76_wr(dev, MT_FCE_PSE_CTRL, 0x1);
	/* FCE tx_fs_base_ptr */
	mt76_wr(dev, MT_TX_CPU_FROM_FCE_BASE_PTR, 0x400230);
	/* FCE tx_fs_max_cnt */
	mt76_wr(dev, MT_TX_CPU_FROM_FCE_MAX_COUNT, 0x1);
	/* FCE pdma enable */
	mt76_wr(dev, MT_FCE_PDMA_GLOBAL_CONF, 0x44);
	/* FCE skip_fs_en */
	mt76_wr(dev, MT_FCE_SKIP_FS, 0x3);

	err = mt76x02u_mcu_fw_send_data(dev, fw->data + माप(*hdr),
					fw->size - माप(*hdr),
					MCU_ROM_PATCH_MAX_PAYLOAD,
					MT76U_MCU_ROM_PATCH_OFFSET);
	अगर (err < 0) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	mt76x2u_mcu_enable_patch(dev);
	mt76x2u_mcu_reset_wmt(dev);
	mdelay(20);

	अगर (!mt76_poll_msec(dev, patch_reg, patch_mask, patch_mask, 100)) अणु
		dev_err(dev->mt76.dev, "failed to load ROM patch\n");
		err = -ETIMEDOUT;
	पूर्ण

out:
	अगर (rom_protect)
		mt76_wr(dev, MT_MCU_SEMAPHORE_03, 1);
	release_firmware(fw);
	वापस err;
पूर्ण

अटल पूर्णांक mt76x2u_mcu_load_firmware(काष्ठा mt76x02_dev *dev)
अणु
	u32 val, dlm_offset = MT76U_MCU_DLM_OFFSET;
	स्थिर काष्ठा mt76x02_fw_header *hdr;
	पूर्णांक err, len, ilm_len, dlm_len;
	स्थिर काष्ठा firmware *fw;

	err = request_firmware(&fw, MT7662_FIRMWARE, dev->mt76.dev);
	अगर (err < 0)
		वापस err;

	अगर (!fw || !fw->data || fw->size < माप(*hdr)) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	hdr = (स्थिर काष्ठा mt76x02_fw_header *)fw->data;
	ilm_len = le32_to_cpu(hdr->ilm_len);
	dlm_len = le32_to_cpu(hdr->dlm_len);
	len = माप(*hdr) + ilm_len + dlm_len;
	अगर (fw->size != len) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	val = le16_to_cpu(hdr->fw_ver);
	dev_info(dev->mt76.dev, "Firmware Version: %d.%d.%02d\n",
		 (val >> 12) & 0xf, (val >> 8) & 0xf, val & 0xf);

	val = le16_to_cpu(hdr->build_ver);
	dev_info(dev->mt76.dev, "Build: %x\n", val);
	dev_info(dev->mt76.dev, "Build Time: %.16s\n", hdr->build_समय);

	/* venकरोr reset */
	mt76x02u_mcu_fw_reset(dev);
	usleep_range(5000, 10000);

	/* enable USB_DMA_CFG */
	val = MT_USB_DMA_CFG_RX_BULK_EN |
	      MT_USB_DMA_CFG_TX_BULK_EN |
	      FIELD_PREP(MT_USB_DMA_CFG_RX_BULK_AGG_TOUT, 0x20);
	mt76_wr(dev, MT_VEND_ADDR(CFG, MT_USB_U3DMA_CFG), val);
	/* enable FCE to send in-band cmd */
	mt76_wr(dev, MT_FCE_PSE_CTRL, 0x1);
	/* FCE tx_fs_base_ptr */
	mt76_wr(dev, MT_TX_CPU_FROM_FCE_BASE_PTR, 0x400230);
	/* FCE tx_fs_max_cnt */
	mt76_wr(dev, MT_TX_CPU_FROM_FCE_MAX_COUNT, 0x1);
	/* FCE pdma enable */
	mt76_wr(dev, MT_FCE_PDMA_GLOBAL_CONF, 0x44);
	/* FCE skip_fs_en */
	mt76_wr(dev, MT_FCE_SKIP_FS, 0x3);

	/* load ILM */
	err = mt76x02u_mcu_fw_send_data(dev, fw->data + माप(*hdr),
					ilm_len, MCU_FW_URB_MAX_PAYLOAD,
					MT76U_MCU_ILM_OFFSET);
	अगर (err < 0) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	/* load DLM */
	अगर (mt76xx_rev(dev) >= MT76XX_REV_E3)
		dlm_offset += 0x800;
	err = mt76x02u_mcu_fw_send_data(dev, fw->data + माप(*hdr) + ilm_len,
					dlm_len, MCU_FW_URB_MAX_PAYLOAD,
					dlm_offset);
	अगर (err < 0) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	mt76x2u_mcu_load_ivb(dev);
	अगर (!mt76_poll_msec(dev, MT_MCU_COM_REG0, 1, 1, 100)) अणु
		dev_err(dev->mt76.dev, "firmware failed to start\n");
		err = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	mt76_set(dev, MT_MCU_COM_REG0, BIT(1));
	/* enable FCE to send in-band cmd */
	mt76_wr(dev, MT_FCE_PSE_CTRL, 0x1);
	mt76x02_set_ethtool_fwver(dev, hdr);
	dev_dbg(dev->mt76.dev, "firmware running\n");

out:
	release_firmware(fw);
	वापस err;
पूर्ण

पूर्णांक mt76x2u_mcu_fw_init(काष्ठा mt76x02_dev *dev)
अणु
	पूर्णांक err;

	err = mt76x2u_mcu_load_rom_patch(dev);
	अगर (err < 0)
		वापस err;

	वापस mt76x2u_mcu_load_firmware(dev);
पूर्ण

पूर्णांक mt76x2u_mcu_init(काष्ठा mt76x02_dev *dev)
अणु
	पूर्णांक err;

	err = mt76x02_mcu_function_select(dev, Q_SELECT, 1);
	अगर (err < 0)
		वापस err;

	वापस mt76x02_mcu_set_radio_state(dev, true);
पूर्ण
