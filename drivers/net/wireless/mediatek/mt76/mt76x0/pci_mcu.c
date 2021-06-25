<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/firmware.h>

#समावेश "mt76x0.h"
#समावेश "mcu.h"

#घोषणा MT_MCU_IVB_ADDR		(MT_MCU_ILM_ADDR + 0x54000 - MT_MCU_IVB_SIZE)

अटल पूर्णांक mt76x0e_load_firmware(काष्ठा mt76x02_dev *dev)
अणु
	bool is_combo_chip = mt76_chip(&dev->mt76) != 0x7610;
	u32 val, ilm_len, dlm_len, offset = 0;
	स्थिर काष्ठा mt76x02_fw_header *hdr;
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर *firmware;
	स्थिर u8 *fw_payload;
	पूर्णांक len, err;

	अगर (is_combo_chip)
		firmware = MT7650E_FIRMWARE;
	अन्यथा
		firmware = MT7610E_FIRMWARE;

	err = request_firmware(&fw, firmware, dev->mt76.dev);
	अगर (err)
		वापस err;

	अगर (!fw || !fw->data || fw->size < माप(*hdr)) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	hdr = (स्थिर काष्ठा mt76x02_fw_header *)fw->data;

	len = माप(*hdr);
	len += le32_to_cpu(hdr->ilm_len);
	len += le32_to_cpu(hdr->dlm_len);

	अगर (fw->size != len) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	fw_payload = fw->data + माप(*hdr);

	val = le16_to_cpu(hdr->fw_ver);
	dev_info(dev->mt76.dev, "Firmware Version: %d.%d.%02d\n",
		 (val >> 12) & 0xf, (val >> 8) & 0xf, val & 0xf);

	val = le16_to_cpu(hdr->fw_ver);
	dev_dbg(dev->mt76.dev,
		"Firmware Version: %d.%d.%02d Build: %x Build time: %.16s\n",
		(val >> 12) & 0xf, (val >> 8) & 0xf, val & 0xf,
		le16_to_cpu(hdr->build_ver), hdr->build_समय);

	अगर (is_combo_chip && !mt76_poll(dev, MT_MCU_SEMAPHORE_00, 1, 1, 600)) अणु
		dev_err(dev->mt76.dev,
			"Could not get hardware semaphore for loading fw\n");
		err = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	/* upload ILM. */
	mt76_wr(dev, MT_MCU_PCIE_REMAP_BASE4, 0);
	ilm_len = le32_to_cpu(hdr->ilm_len);
	अगर (is_combo_chip) अणु
		ilm_len -= MT_MCU_IVB_SIZE;
		offset = MT_MCU_IVB_SIZE;
	पूर्ण
	dev_dbg(dev->mt76.dev, "loading FW - ILM %u\n", ilm_len);
	mt76_wr_copy(dev, MT_MCU_ILM_ADDR + offset, fw_payload + offset,
		     ilm_len);

	/* upload IVB. */
	अगर (is_combo_chip) अणु
		dev_dbg(dev->mt76.dev, "loading FW - IVB %u\n",
			MT_MCU_IVB_SIZE);
		mt76_wr_copy(dev, MT_MCU_IVB_ADDR, fw_payload, MT_MCU_IVB_SIZE);
	पूर्ण

	/* upload DLM. */
	mt76_wr(dev, MT_MCU_PCIE_REMAP_BASE4, MT_MCU_DLM_OFFSET);
	dlm_len = le32_to_cpu(hdr->dlm_len);
	dev_dbg(dev->mt76.dev, "loading FW - DLM %u\n", dlm_len);
	mt76_wr_copy(dev, MT_MCU_ILM_ADDR,
		     fw_payload + le32_to_cpu(hdr->ilm_len), dlm_len);

	/* trigger firmware */
	mt76_wr(dev, MT_MCU_PCIE_REMAP_BASE4, 0);
	अगर (is_combo_chip)
		mt76_wr(dev, MT_MCU_INT_LEVEL, 0x3);
	अन्यथा
		mt76_wr(dev, MT_MCU_RESET_CTL, 0x300);

	अगर (!mt76_poll_msec(dev, MT_MCU_COM_REG0, 1, 1, 1000)) अणु
		dev_err(dev->mt76.dev, "Firmware failed to start\n");
		err = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	mt76x02_set_ethtool_fwver(dev, hdr);
	dev_dbg(dev->mt76.dev, "Firmware running!\n");

out:
	अगर (is_combo_chip)
		mt76_wr(dev, MT_MCU_SEMAPHORE_00, 0x1);
	release_firmware(fw);

	वापस err;
पूर्ण

पूर्णांक mt76x0e_mcu_init(काष्ठा mt76x02_dev *dev)
अणु
	अटल स्थिर काष्ठा mt76_mcu_ops mt76x0e_mcu_ops = अणु
		.mcu_send_msg = mt76x02_mcu_msg_send,
		.mcu_parse_response = mt76x02_mcu_parse_response,
	पूर्ण;
	पूर्णांक err;

	dev->mt76.mcu_ops = &mt76x0e_mcu_ops;

	err = mt76x0e_load_firmware(dev);
	अगर (err < 0)
		वापस err;

	set_bit(MT76_STATE_MCU_RUNNING, &dev->mphy.state);

	वापस 0;
पूर्ण
