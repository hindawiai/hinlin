<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Firmware loading.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 */
#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/bitfield.h>

#समावेश "fwio.h"
#समावेश "wfx.h"
#समावेश "hwio.h"

// Addresses below are in SRAM area
#घोषणा WFX_DNLD_FIFO             0x09004000
#घोषणा     DNLD_BLOCK_SIZE           0x0400
#घोषणा     DNLD_FIFO_SIZE            0x8000 // (32 * DNLD_BLOCK_SIZE)
// Download Control Area (DCA)
#घोषणा WFX_DCA_IMAGE_SIZE        0x0900C000
#घोषणा WFX_DCA_PUT               0x0900C004
#घोषणा WFX_DCA_GET               0x0900C008
#घोषणा WFX_DCA_HOST_STATUS       0x0900C00C
#घोषणा     HOST_READY                0x87654321
#घोषणा     HOST_INFO_READ            0xA753BD99
#घोषणा     HOST_UPLOAD_PENDING       0xABCDDCBA
#घोषणा     HOST_UPLOAD_COMPLETE      0xD4C64A99
#घोषणा     HOST_OK_TO_JUMP           0x174FC882
#घोषणा WFX_DCA_NCP_STATUS        0x0900C010
#घोषणा     NCP_NOT_READY             0x12345678
#घोषणा     NCP_READY                 0x87654321
#घोषणा     NCP_INFO_READY            0xBD53EF99
#घोषणा     NCP_DOWNLOAD_PENDING      0xABCDDCBA
#घोषणा     NCP_DOWNLOAD_COMPLETE     0xCAFEFECA
#घोषणा     NCP_AUTH_OK               0xD4C64A99
#घोषणा     NCP_AUTH_FAIL             0x174FC882
#घोषणा     NCP_PUB_KEY_RDY           0x7AB41D19
#घोषणा WFX_DCA_FW_SIGNATURE      0x0900C014
#घोषणा     FW_SIGNATURE_SIZE         0x40
#घोषणा WFX_DCA_FW_HASH           0x0900C054
#घोषणा     FW_HASH_SIZE              0x08
#घोषणा WFX_DCA_FW_VERSION        0x0900C05C
#घोषणा     FW_VERSION_SIZE           0x04
#घोषणा WFX_DCA_RESERVED          0x0900C060
#घोषणा     DCA_RESERVED_SIZE         0x20
#घोषणा WFX_STATUS_INFO           0x0900C080
#घोषणा WFX_BOOTLOADER_LABEL      0x0900C084
#घोषणा     BOOTLOADER_LABEL_SIZE     0x3C
#घोषणा WFX_PTE_INFO              0x0900C0C0
#घोषणा     PTE_INFO_KEYSET_IDX       0x0D
#घोषणा     PTE_INFO_SIZE             0x10
#घोषणा WFX_ERR_INFO              0x0900C0D0
#घोषणा     ERR_INVALID_SEC_TYPE      0x05
#घोषणा     ERR_SIG_VERIF_FAILED      0x0F
#घोषणा     ERR_AES_CTRL_KEY          0x10
#घोषणा     ERR_ECC_PUB_KEY           0x11
#घोषणा     ERR_MAC_KEY               0x18

#घोषणा DCA_TIMEOUT  50 // milliseconds
#घोषणा WAKEUP_TIMEOUT 200 // milliseconds

अटल स्थिर अक्षर * स्थिर fwio_errors[] = अणु
	[ERR_INVALID_SEC_TYPE] = "Invalid section type or wrong encryption",
	[ERR_SIG_VERIF_FAILED] = "Signature verification failed",
	[ERR_AES_CTRL_KEY] = "AES control key not initialized",
	[ERR_ECC_PUB_KEY] = "ECC public key not initialized",
	[ERR_MAC_KEY] = "MAC key not initialized",
पूर्ण;

/*
 * request_firmware() allocate data using vदो_स्मृति(). It is not compatible with
 * underlying hardware that use DMA. Function below detect this हाल and
 * allocate a bounce buffer अगर necessary.
 *
 * Notice that, in करोubt, you can enable CONFIG_DEBUG_SG to ask kernel to
 * detect this problem at runसमय  (अन्यथा, kernel silently fail).
 *
 * NOTE: it may also be possible to use 'pages' from काष्ठा firmware and aव्योम
 * bounce buffer
 */
अटल पूर्णांक sram_ग_लिखो_dma_safe(काष्ठा wfx_dev *wdev, u32 addr, स्थिर u8 *buf,
			       माप_प्रकार len)
अणु
	पूर्णांक ret;
	स्थिर u8 *पंचांगp;

	अगर (!virt_addr_valid(buf)) अणु
		पंचांगp = kmemdup(buf, len, GFP_KERNEL);
		अगर (!पंचांगp)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		पंचांगp = buf;
	पूर्ण
	ret = sram_buf_ग_लिखो(wdev, addr, पंचांगp, len);
	अगर (पंचांगp != buf)
		kमुक्त(पंचांगp);
	वापस ret;
पूर्ण

अटल पूर्णांक get_firmware(काष्ठा wfx_dev *wdev, u32 keyset_chip,
			स्थिर काष्ठा firmware **fw, पूर्णांक *file_offset)
अणु
	पूर्णांक keyset_file;
	अक्षर filename[256];
	स्थिर अक्षर *data;
	पूर्णांक ret;

	snम_लिखो(filename, माप(filename), "%s_%02X.sec",
		 wdev->pdata.file_fw, keyset_chip);
	ret = firmware_request_nowarn(fw, filename, wdev->dev);
	अगर (ret) अणु
		dev_info(wdev->dev, "can't load %s, falling back to %s.sec\n",
			 filename, wdev->pdata.file_fw);
		snम_लिखो(filename, माप(filename), "%s.sec",
			 wdev->pdata.file_fw);
		ret = request_firmware(fw, filename, wdev->dev);
		अगर (ret) अणु
			dev_err(wdev->dev, "can't load %s\n", filename);
			*fw = शून्य;
			वापस ret;
		पूर्ण
	पूर्ण

	data = (*fw)->data;
	अगर (स_भेद(data, "KEYSET", 6) != 0) अणु
		// Legacy firmware क्रमmat
		*file_offset = 0;
		keyset_file = 0x90;
	पूर्ण अन्यथा अणु
		*file_offset = 8;
		keyset_file = (hex_to_bin(data[6]) * 16) | hex_to_bin(data[7]);
		अगर (keyset_file < 0) अणु
			dev_err(wdev->dev, "%s corrupted\n", filename);
			release_firmware(*fw);
			*fw = शून्य;
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (keyset_file != keyset_chip) अणु
		dev_err(wdev->dev, "firmware keyset is incompatible with chip (file: 0x%02X, chip: 0x%02X)\n",
			keyset_file, keyset_chip);
		release_firmware(*fw);
		*fw = शून्य;
		वापस -ENODEV;
	पूर्ण
	wdev->keyset = keyset_file;
	वापस 0;
पूर्ण

अटल पूर्णांक रुको_ncp_status(काष्ठा wfx_dev *wdev, u32 status)
अणु
	kसमय_प्रकार now, start;
	u32 reg;
	पूर्णांक ret;

	start = kसमय_get();
	क्रम (;;) अणु
		ret = sram_reg_पढ़ो(wdev, WFX_DCA_NCP_STATUS, &reg);
		अगर (ret < 0)
			वापस -EIO;
		now = kसमय_get();
		अगर (reg == status)
			अवरोध;
		अगर (kसमय_after(now, kसमय_add_ms(start, DCA_TIMEOUT)))
			वापस -ETIMEDOUT;
	पूर्ण
	अगर (kसमय_compare(now, start))
		dev_dbg(wdev->dev, "chip answer after %lldus\n",
			kसमय_us_delta(now, start));
	अन्यथा
		dev_dbg(wdev->dev, "chip answer immediately\n");
	वापस 0;
पूर्ण

अटल पूर्णांक upload_firmware(काष्ठा wfx_dev *wdev, स्थिर u8 *data, माप_प्रकार len)
अणु
	पूर्णांक ret;
	u32 offs, bytes_करोne = 0;
	kसमय_प्रकार now, start;

	अगर (len % DNLD_BLOCK_SIZE) अणु
		dev_err(wdev->dev, "firmware size is not aligned. Buffer overrun will occur\n");
		वापस -EIO;
	पूर्ण
	offs = 0;
	जबतक (offs < len) अणु
		start = kसमय_get();
		क्रम (;;) अणु
			now = kसमय_get();
			अगर (offs + DNLD_BLOCK_SIZE - bytes_करोne < DNLD_FIFO_SIZE)
				अवरोध;
			अगर (kसमय_after(now, kसमय_add_ms(start, DCA_TIMEOUT)))
				वापस -ETIMEDOUT;
			ret = sram_reg_पढ़ो(wdev, WFX_DCA_GET, &bytes_करोne);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		अगर (kसमय_compare(now, start))
			dev_dbg(wdev->dev, "answer after %lldus\n",
				kसमय_us_delta(now, start));

		ret = sram_ग_लिखो_dma_safe(wdev, WFX_DNLD_FIFO +
					  (offs % DNLD_FIFO_SIZE),
					  data + offs, DNLD_BLOCK_SIZE);
		अगर (ret < 0)
			वापस ret;

		// WFx seems to not support writing 0 in this रेजिस्टर during
		// first loop
		offs += DNLD_BLOCK_SIZE;
		ret = sram_reg_ग_लिखो(wdev, WFX_DCA_PUT, offs);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम prपूर्णांक_boot_status(काष्ठा wfx_dev *wdev)
अणु
	u32 reg;

	sram_reg_पढ़ो(wdev, WFX_STATUS_INFO, &reg);
	अगर (reg == 0x12345678)
		वापस;
	sram_reg_पढ़ो(wdev, WFX_ERR_INFO, &reg);
	अगर (reg < ARRAY_SIZE(fwio_errors) && fwio_errors[reg])
		dev_info(wdev->dev, "secure boot: %s\n", fwio_errors[reg]);
	अन्यथा
		dev_info(wdev->dev, "secure boot: Error %#02x\n", reg);
पूर्ण

अटल पूर्णांक load_firmware_secure(काष्ठा wfx_dev *wdev)
अणु
	स्थिर काष्ठा firmware *fw = शून्य;
	पूर्णांक header_size;
	पूर्णांक fw_offset;
	kसमय_प्रकार start;
	u8 *buf;
	पूर्णांक ret;

	BUILD_BUG_ON(PTE_INFO_SIZE > BOOTLOADER_LABEL_SIZE);
	buf = kदो_स्मृति(BOOTLOADER_LABEL_SIZE + 1, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	sram_reg_ग_लिखो(wdev, WFX_DCA_HOST_STATUS, HOST_READY);
	ret = रुको_ncp_status(wdev, NCP_INFO_READY);
	अगर (ret)
		जाओ error;

	sram_buf_पढ़ो(wdev, WFX_BOOTLOADER_LABEL, buf, BOOTLOADER_LABEL_SIZE);
	buf[BOOTLOADER_LABEL_SIZE] = 0;
	dev_dbg(wdev->dev, "bootloader: \"%s\"\n", buf);

	sram_buf_पढ़ो(wdev, WFX_PTE_INFO, buf, PTE_INFO_SIZE);
	ret = get_firmware(wdev, buf[PTE_INFO_KEYSET_IDX], &fw, &fw_offset);
	अगर (ret)
		जाओ error;
	header_size = fw_offset + FW_SIGNATURE_SIZE + FW_HASH_SIZE;

	sram_reg_ग_लिखो(wdev, WFX_DCA_HOST_STATUS, HOST_INFO_READ);
	ret = रुको_ncp_status(wdev, NCP_READY);
	अगर (ret)
		जाओ error;

	sram_reg_ग_लिखो(wdev, WFX_DNLD_FIFO, 0xFFFFFFFF); // Fअगरo init
	sram_ग_लिखो_dma_safe(wdev, WFX_DCA_FW_VERSION, "\x01\x00\x00\x00",
			    FW_VERSION_SIZE);
	sram_ग_लिखो_dma_safe(wdev, WFX_DCA_FW_SIGNATURE, fw->data + fw_offset,
			    FW_SIGNATURE_SIZE);
	sram_ग_लिखो_dma_safe(wdev, WFX_DCA_FW_HASH,
			    fw->data + fw_offset + FW_SIGNATURE_SIZE,
			    FW_HASH_SIZE);
	sram_reg_ग_लिखो(wdev, WFX_DCA_IMAGE_SIZE, fw->size - header_size);
	sram_reg_ग_लिखो(wdev, WFX_DCA_HOST_STATUS, HOST_UPLOAD_PENDING);
	ret = रुको_ncp_status(wdev, NCP_DOWNLOAD_PENDING);
	अगर (ret)
		जाओ error;

	start = kसमय_get();
	ret = upload_firmware(wdev, fw->data + header_size,
			      fw->size - header_size);
	अगर (ret)
		जाओ error;
	dev_dbg(wdev->dev, "firmware load after %lldus\n",
		kसमय_us_delta(kसमय_get(), start));

	sram_reg_ग_लिखो(wdev, WFX_DCA_HOST_STATUS, HOST_UPLOAD_COMPLETE);
	ret = रुको_ncp_status(wdev, NCP_AUTH_OK);
	// Legacy ROM support
	अगर (ret < 0)
		ret = रुको_ncp_status(wdev, NCP_PUB_KEY_RDY);
	अगर (ret < 0)
		जाओ error;
	sram_reg_ग_लिखो(wdev, WFX_DCA_HOST_STATUS, HOST_OK_TO_JUMP);

error:
	kमुक्त(buf);
	अगर (fw)
		release_firmware(fw);
	अगर (ret)
		prपूर्णांक_boot_status(wdev);
	वापस ret;
पूर्ण

अटल पूर्णांक init_gpr(काष्ठा wfx_dev *wdev)
अणु
	पूर्णांक ret, i;
	अटल स्थिर काष्ठा अणु
		पूर्णांक index;
		u32 value;
	पूर्ण gpr_init[] = अणु
		अणु 0x07, 0x208775 पूर्ण,
		अणु 0x08, 0x2EC020 पूर्ण,
		अणु 0x09, 0x3C3C3C पूर्ण,
		अणु 0x0B, 0x322C44 पूर्ण,
		अणु 0x0C, 0xA06497 पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(gpr_init); i++) अणु
		ret = igpr_reg_ग_लिखो(wdev, gpr_init[i].index,
				     gpr_init[i].value);
		अगर (ret < 0)
			वापस ret;
		dev_dbg(wdev->dev, "  index %02x: %08x\n",
			gpr_init[i].index, gpr_init[i].value);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक wfx_init_device(काष्ठा wfx_dev *wdev)
अणु
	पूर्णांक ret;
	पूर्णांक hw_revision, hw_type;
	पूर्णांक wakeup_समयout = 50; // ms
	kसमय_प्रकार now, start;
	u32 reg;

	reg = CFG_सूचीECT_ACCESS_MODE | CFG_CPU_RESET | CFG_BYTE_ORDER_ABCD;
	अगर (wdev->pdata.use_rising_clk)
		reg |= CFG_CLK_RISE_EDGE;
	ret = config_reg_ग_लिखो(wdev, reg);
	अगर (ret < 0) अणु
		dev_err(wdev->dev, "bus returned an error during first write access. Host configuration error?\n");
		वापस -EIO;
	पूर्ण

	ret = config_reg_पढ़ो(wdev, &reg);
	अगर (ret < 0) अणु
		dev_err(wdev->dev, "bus returned an error during first read access. Bus configuration error?\n");
		वापस -EIO;
	पूर्ण
	अगर (reg == 0 || reg == ~0) अणु
		dev_err(wdev->dev, "chip mute. Bus configuration error or chip wasn't reset?\n");
		वापस -EIO;
	पूर्ण
	dev_dbg(wdev->dev, "initial config register value: %08x\n", reg);

	hw_revision = FIELD_GET(CFG_DEVICE_ID_MAJOR, reg);
	अगर (hw_revision == 0) अणु
		dev_err(wdev->dev, "bad hardware revision number: %d\n",
			hw_revision);
		वापस -ENODEV;
	पूर्ण
	hw_type = FIELD_GET(CFG_DEVICE_ID_TYPE, reg);
	अगर (hw_type == 1) अणु
		dev_notice(wdev->dev, "development hardware detected\n");
		wakeup_समयout = 2000;
	पूर्ण

	ret = init_gpr(wdev);
	अगर (ret < 0)
		वापस ret;

	ret = control_reg_ग_लिखो(wdev, CTRL_WLAN_WAKEUP);
	अगर (ret < 0)
		वापस -EIO;
	start = kसमय_get();
	क्रम (;;) अणु
		ret = control_reg_पढ़ो(wdev, &reg);
		now = kसमय_get();
		अगर (reg & CTRL_WLAN_READY)
			अवरोध;
		अगर (kसमय_after(now, kसमय_add_ms(start, wakeup_समयout))) अणु
			dev_err(wdev->dev, "chip didn't wake up. Chip wasn't reset?\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण
	dev_dbg(wdev->dev, "chip wake up after %lldus\n",
		kसमय_us_delta(now, start));

	ret = config_reg_ग_लिखो_bits(wdev, CFG_CPU_RESET, 0);
	अगर (ret < 0)
		वापस ret;
	ret = load_firmware_secure(wdev);
	अगर (ret < 0)
		वापस ret;
	वापस config_reg_ग_लिखो_bits(wdev,
				     CFG_सूचीECT_ACCESS_MODE |
				     CFG_IRQ_ENABLE_DATA |
				     CFG_IRQ_ENABLE_WRDY,
				     CFG_IRQ_ENABLE_DATA);
पूर्ण
