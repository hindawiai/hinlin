<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/firmware.h>
#समावेश <linux/delay.h>

#समावेश "mt76x2.h"
#समावेश "mcu.h"
#समावेश "eeprom.h"

अटल पूर्णांक
mt76pci_load_rom_patch(काष्ठा mt76x02_dev *dev)
अणु
	स्थिर काष्ठा firmware *fw = शून्य;
	काष्ठा mt76x02_patch_header *hdr;
	bool rom_protect = !is_mt7612(dev);
	पूर्णांक len, ret = 0;
	__le32 *cur;
	u32 patch_mask, patch_reg;

	अगर (rom_protect && !mt76_poll(dev, MT_MCU_SEMAPHORE_03, 1, 1, 600)) अणु
		dev_err(dev->mt76.dev,
			"Could not get hardware semaphore for ROM PATCH\n");
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
		जाओ out;
	पूर्ण

	ret = request_firmware(&fw, MT7662_ROM_PATCH, dev->mt76.dev);
	अगर (ret)
		जाओ out;

	अगर (!fw || !fw->data || fw->size <= माप(*hdr)) अणु
		ret = -EIO;
		dev_err(dev->mt76.dev, "Failed to load firmware\n");
		जाओ out;
	पूर्ण

	hdr = (काष्ठा mt76x02_patch_header *)fw->data;
	dev_info(dev->mt76.dev, "ROM patch build: %.15s\n", hdr->build_समय);

	mt76_wr(dev, MT_MCU_PCIE_REMAP_BASE4, MT_MCU_ROM_PATCH_OFFSET);

	cur = (__le32 *)(fw->data + माप(*hdr));
	len = fw->size - माप(*hdr);
	mt76_wr_copy(dev, MT_MCU_ROM_PATCH_ADDR, cur, len);

	mt76_wr(dev, MT_MCU_PCIE_REMAP_BASE4, 0);

	/* Trigger ROM */
	mt76_wr(dev, MT_MCU_INT_LEVEL, 4);

	अगर (!mt76_poll_msec(dev, patch_reg, patch_mask, patch_mask, 2000)) अणु
		dev_err(dev->mt76.dev, "Failed to load ROM patch\n");
		ret = -ETIMEDOUT;
	पूर्ण

out:
	/* release semaphore */
	अगर (rom_protect)
		mt76_wr(dev, MT_MCU_SEMAPHORE_03, 1);
	release_firmware(fw);
	वापस ret;
पूर्ण

अटल पूर्णांक
mt76pci_load_firmware(काष्ठा mt76x02_dev *dev)
अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर काष्ठा mt76x02_fw_header *hdr;
	पूर्णांक len, ret;
	__le32 *cur;
	u32 offset, val;

	ret = request_firmware(&fw, MT7662_FIRMWARE, dev->mt76.dev);
	अगर (ret)
		वापस ret;

	अगर (!fw || !fw->data || fw->size < माप(*hdr))
		जाओ error;

	hdr = (स्थिर काष्ठा mt76x02_fw_header *)fw->data;

	len = माप(*hdr);
	len += le32_to_cpu(hdr->ilm_len);
	len += le32_to_cpu(hdr->dlm_len);

	अगर (fw->size != len)
		जाओ error;

	val = le16_to_cpu(hdr->fw_ver);
	dev_info(dev->mt76.dev, "Firmware Version: %d.%d.%02d\n",
		 (val >> 12) & 0xf, (val >> 8) & 0xf, val & 0xf);

	val = le16_to_cpu(hdr->build_ver);
	dev_info(dev->mt76.dev, "Build: %x\n", val);
	dev_info(dev->mt76.dev, "Build Time: %.16s\n", hdr->build_समय);

	cur = (__le32 *)(fw->data + माप(*hdr));
	len = le32_to_cpu(hdr->ilm_len);

	mt76_wr(dev, MT_MCU_PCIE_REMAP_BASE4, MT_MCU_ILM_OFFSET);
	mt76_wr_copy(dev, MT_MCU_ILM_ADDR, cur, len);

	cur += len / माप(*cur);
	len = le32_to_cpu(hdr->dlm_len);

	अगर (mt76xx_rev(dev) >= MT76XX_REV_E3)
		offset = MT_MCU_DLM_ADDR_E3;
	अन्यथा
		offset = MT_MCU_DLM_ADDR;

	mt76_wr(dev, MT_MCU_PCIE_REMAP_BASE4, MT_MCU_DLM_OFFSET);
	mt76_wr_copy(dev, offset, cur, len);

	mt76_wr(dev, MT_MCU_PCIE_REMAP_BASE4, 0);

	val = mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_2);
	अगर (FIELD_GET(MT_EE_NIC_CONF_2_XTAL_OPTION, val) == 1)
		mt76_set(dev, MT_MCU_COM_REG0, BIT(30));

	/* trigger firmware */
	mt76_wr(dev, MT_MCU_INT_LEVEL, 2);
	अगर (!mt76_poll_msec(dev, MT_MCU_COM_REG0, 1, 1, 200)) अणु
		dev_err(dev->mt76.dev, "Firmware failed to start\n");
		release_firmware(fw);
		वापस -ETIMEDOUT;
	पूर्ण

	mt76x02_set_ethtool_fwver(dev, hdr);
	dev_info(dev->mt76.dev, "Firmware running!\n");

	release_firmware(fw);

	वापस ret;

error:
	dev_err(dev->mt76.dev, "Invalid firmware\n");
	release_firmware(fw);
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक
mt76pci_mcu_restart(काष्ठा mt76_dev *mdev)
अणु
	काष्ठा mt76x02_dev *dev;
	पूर्णांक ret;

	dev = container_of(mdev, काष्ठा mt76x02_dev, mt76);

	mt76x02_mcu_cleanup(dev);
	mt76x2_mac_reset(dev, true);

	ret = mt76pci_load_firmware(dev);
	अगर (ret)
		वापस ret;

	mt76_wr(dev, MT_WPDMA_RST_IDX, ~0);

	वापस 0;
पूर्ण

पूर्णांक mt76x2_mcu_init(काष्ठा mt76x02_dev *dev)
अणु
	अटल स्थिर काष्ठा mt76_mcu_ops mt76x2_mcu_ops = अणु
		.mcu_restart = mt76pci_mcu_restart,
		.mcu_send_msg = mt76x02_mcu_msg_send,
		.mcu_parse_response = mt76x02_mcu_parse_response,
	पूर्ण;
	पूर्णांक ret;

	dev->mt76.mcu_ops = &mt76x2_mcu_ops;

	ret = mt76pci_load_rom_patch(dev);
	अगर (ret)
		वापस ret;

	ret = mt76pci_load_firmware(dev);
	अगर (ret)
		वापस ret;

	mt76x02_mcu_function_select(dev, Q_SELECT, 1);
	वापस 0;
पूर्ण
