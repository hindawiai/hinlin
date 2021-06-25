<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2019-2020 Linaro Limited */

#समावेश <linux/acpi.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "xhci.h"
#समावेश "xhci-trace.h"
#समावेश "xhci-pci.h"

#घोषणा RENESAS_FW_VERSION				0x6C
#घोषणा RENESAS_ROM_CONFIG				0xF0
#घोषणा RENESAS_FW_STATUS				0xF4
#घोषणा RENESAS_FW_STATUS_MSB				0xF5
#घोषणा RENESAS_ROM_STATUS				0xF6
#घोषणा RENESAS_ROM_STATUS_MSB				0xF7
#घोषणा RENESAS_DATA0					0xF8
#घोषणा RENESAS_DATA1					0xFC

#घोषणा RENESAS_FW_VERSION_FIELD			GENMASK(23, 7)
#घोषणा RENESAS_FW_VERSION_OFFSET			8

#घोषणा RENESAS_FW_STATUS_DOWNLOAD_ENABLE		BIT(0)
#घोषणा RENESAS_FW_STATUS_LOCK				BIT(1)
#घोषणा RENESAS_FW_STATUS_RESULT			GENMASK(6, 4)
  #घोषणा RENESAS_FW_STATUS_INVALID			0
  #घोषणा RENESAS_FW_STATUS_SUCCESS			BIT(4)
  #घोषणा RENESAS_FW_STATUS_ERROR			BIT(5)
#घोषणा RENESAS_FW_STATUS_SET_DATA0			BIT(8)
#घोषणा RENESAS_FW_STATUS_SET_DATA1			BIT(9)

#घोषणा RENESAS_ROM_STATUS_ACCESS			BIT(0)
#घोषणा RENESAS_ROM_STATUS_ERASE			BIT(1)
#घोषणा RENESAS_ROM_STATUS_RELOAD			BIT(2)
#घोषणा RENESAS_ROM_STATUS_RESULT			GENMASK(6, 4)
  #घोषणा RENESAS_ROM_STATUS_NO_RESULT			0
  #घोषणा RENESAS_ROM_STATUS_SUCCESS			BIT(4)
  #घोषणा RENESAS_ROM_STATUS_ERROR			BIT(5)
#घोषणा RENESAS_ROM_STATUS_SET_DATA0			BIT(8)
#घोषणा RENESAS_ROM_STATUS_SET_DATA1			BIT(9)
#घोषणा RENESAS_ROM_STATUS_ROM_EXISTS			BIT(15)

#घोषणा RENESAS_ROM_ERASE_MAGIC				0x5A65726F
#घोषणा RENESAS_ROM_WRITE_MAGIC				0x53524F4D

#घोषणा RENESAS_RETRY	10000
#घोषणा RENESAS_DELAY	10

अटल पूर्णांक renesas_fw_करोwnload_image(काष्ठा pci_dev *dev,
				     स्थिर u32 *fw, माप_प्रकार step, bool rom)
अणु
	माप_प्रकार i;
	पूर्णांक err;
	u8 fw_status;
	bool data0_or_data1;
	u32 status_reg;

	अगर (rom)
		status_reg = RENESAS_ROM_STATUS_MSB;
	अन्यथा
		status_reg = RENESAS_FW_STATUS_MSB;

	/*
	 * The hardware करोes alternate between two 32-bit pages.
	 * (This is because each row of the firmware is 8 bytes).
	 *
	 * क्रम even steps we use DATA0, क्रम odd steps DATA1.
	 */
	data0_or_data1 = (step & 1) == 1;

	/* step+1. Read "Set DATAX" and confirm it is cleared. */
	क्रम (i = 0; i < RENESAS_RETRY; i++) अणु
		err = pci_पढ़ो_config_byte(dev, status_reg, &fw_status);
		अगर (err) अणु
			dev_err(&dev->dev, "Read Status failed: %d\n",
				pcibios_err_to_त्रुटि_सं(err));
			वापस pcibios_err_to_त्रुटि_सं(err);
		पूर्ण
		अगर (!(fw_status & BIT(data0_or_data1)))
			अवरोध;

		udelay(RENESAS_DELAY);
	पूर्ण
	अगर (i == RENESAS_RETRY) अणु
		dev_err(&dev->dev, "Timeout for Set DATAX step: %zd\n", step);
		वापस -ETIMEDOUT;
	पूर्ण

	/*
	 * step+2. Write FW data to "DATAX".
	 * "LSB is left" => क्रमce little endian
	 */
	err = pci_ग_लिखो_config_dword(dev, data0_or_data1 ?
				     RENESAS_DATA1 : RENESAS_DATA0,
				     (__क्रमce u32)cpu_to_le32(fw[step]));
	अगर (err) अणु
		dev_err(&dev->dev, "Write to DATAX failed: %d\n",
			pcibios_err_to_त्रुटि_सं(err));
		वापस pcibios_err_to_त्रुटि_सं(err);
	पूर्ण

	udelay(100);

	/* step+3. Set "Set DATAX". */
	err = pci_ग_लिखो_config_byte(dev, status_reg, BIT(data0_or_data1));
	अगर (err) अणु
		dev_err(&dev->dev, "Write config for DATAX failed: %d\n",
			pcibios_err_to_त्रुटि_सं(err));
		वापस pcibios_err_to_त्रुटि_सं(err);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक renesas_fw_verअगरy(स्थिर व्योम *fw_data,
			     माप_प्रकार length)
अणु
	u16 fw_version_poपूर्णांकer;
	u16 fw_version;

	/*
	 * The Firmware's Data Format is describe in
	 * "6.3 Data Format" R19UH0078EJ0500 Rev.5.00 page 124
	 */

	/*
	 * The bootrom chips of the big brother have sizes up to 64k, let's
	 * assume that's the biggest the firmware can get.
	 */
	अगर (length < 0x1000 || length >= 0x10000) अणु
		pr_err("firmware is size %zd is not (4k - 64k).",
			length);
		वापस -EINVAL;
	पूर्ण

	/* The First 2 bytes are fixed value (55aa). "LSB on Left" */
	अगर (get_unaligned_le16(fw_data) != 0x55aa) अणु
		pr_err("no valid firmware header found.");
		वापस -EINVAL;
	पूर्ण

	/* verअगरy the firmware version position and prपूर्णांक it. */
	fw_version_poपूर्णांकer = get_unaligned_le16(fw_data + 4);
	अगर (fw_version_poपूर्णांकer + 2 >= length) अणु
		pr_err("fw ver pointer is outside of the firmware image");
		वापस -EINVAL;
	पूर्ण

	fw_version = get_unaligned_le16(fw_data + fw_version_poपूर्णांकer);
	pr_err("got firmware version: %02x.", fw_version);

	वापस 0;
पूर्ण

अटल bool renesas_check_rom(काष्ठा pci_dev *pdev)
अणु
	u16 rom_status;
	पूर्णांक retval;

	/* Check अगर बाह्यal ROM exists */
	retval = pci_पढ़ो_config_word(pdev, RENESAS_ROM_STATUS, &rom_status);
	अगर (retval)
		वापस false;

	rom_status &= RENESAS_ROM_STATUS_ROM_EXISTS;
	अगर (rom_status) अणु
		dev_dbg(&pdev->dev, "External ROM exists\n");
		वापस true; /* External ROM exists */
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक renesas_check_rom_state(काष्ठा pci_dev *pdev)
अणु
	u16 rom_state;
	u32 version;
	पूर्णांक err;

	/* check FW version */
	err = pci_पढ़ो_config_dword(pdev, RENESAS_FW_VERSION, &version);
	अगर (err)
		वापस pcibios_err_to_त्रुटि_सं(err);

	version &= RENESAS_FW_VERSION_FIELD;
	version = version >> RENESAS_FW_VERSION_OFFSET;
	dev_dbg(&pdev->dev, "Found ROM version: %x\n", version);

	/*
	 * Test अगर ROM is present and loaded, अगर so we can skip everything
	 */
	err = pci_पढ़ो_config_word(pdev, RENESAS_ROM_STATUS, &rom_state);
	अगर (err)
		वापस pcibios_err_to_त्रुटि_सं(err);

	अगर (rom_state & BIT(15)) अणु
		/* ROM exists */
		dev_dbg(&pdev->dev, "ROM exists\n");

		/* Check the "Result Code" Bits (6:4) and act accordingly */
		चयन (rom_state & RENESAS_ROM_STATUS_RESULT) अणु
		हाल RENESAS_ROM_STATUS_SUCCESS:
			वापस 0;

		हाल RENESAS_ROM_STATUS_NO_RESULT: /* No result yet */
			वापस 0;

		हाल RENESAS_ROM_STATUS_ERROR: /* Error State */
		शेष: /* All other states are marked as "Reserved states" */
			dev_err(&pdev->dev, "Invalid ROM..");
			अवरोध;
		पूर्ण
	पूर्ण

	वापस -EIO;
पूर्ण

अटल पूर्णांक renesas_fw_check_running(काष्ठा pci_dev *pdev)
अणु
	u8 fw_state;
	पूर्णांक err;

	/* Check अगर device has ROM and loaded, अगर so skip everything */
	err = renesas_check_rom(pdev);
	अगर (err) अणु /* we have rom */
		err = renesas_check_rom_state(pdev);
		अगर (!err)
			वापस err;
	पूर्ण

	/*
	 * Test अगर the device is actually needing the firmware. As most
	 * BIOSes will initialize the device क्रम us. If the device is
	 * initialized.
	 */
	err = pci_पढ़ो_config_byte(pdev, RENESAS_FW_STATUS, &fw_state);
	अगर (err)
		वापस pcibios_err_to_त्रुटि_सं(err);

	/*
	 * Check अगर "FW Download Lock" is locked. If it is and the FW is
	 * पढ़ोy we can simply जारी. If the FW is not पढ़ोy, we have
	 * to give up.
	 */
	अगर (fw_state & RENESAS_FW_STATUS_LOCK) अणु
		dev_dbg(&pdev->dev, "FW Download Lock is engaged.");

		अगर (fw_state & RENESAS_FW_STATUS_SUCCESS)
			वापस 0;

		dev_err(&pdev->dev,
			"FW Download Lock is set and FW is not ready. Giving Up.");
		वापस -EIO;
	पूर्ण

	/*
	 * Check अगर "FW Download Enable" is set. If someone (us?) tampered
	 * with it and it can't be reset, we have to give up too... and
	 * ask क्रम a क्रमgiveness and a reboot.
	 */
	अगर (fw_state & RENESAS_FW_STATUS_DOWNLOAD_ENABLE) अणु
		dev_err(&pdev->dev,
			"FW Download Enable is stale. Giving Up (poweroff/reboot needed).");
		वापस -EIO;
	पूर्ण

	/* Otherwise, Check the "Result Code" Bits (6:4) and act accordingly */
	चयन (fw_state & RENESAS_FW_STATUS_RESULT) अणु
	हाल 0: /* No result yet */
		dev_dbg(&pdev->dev, "FW is not ready/loaded yet.");

		/* tell the caller, that this device needs the firmware. */
		वापस 1;

	हाल RENESAS_FW_STATUS_SUCCESS: /* Success, device should be working. */
		dev_dbg(&pdev->dev, "FW is ready.");
		वापस 0;

	हाल RENESAS_FW_STATUS_ERROR: /* Error State */
		dev_err(&pdev->dev,
			"hardware is in an error state. Giving up (poweroff/reboot needed).");
		वापस -ENODEV;

	शेष: /* All other states are marked as "Reserved states" */
		dev_err(&pdev->dev,
			"hardware is in an invalid state %lx. Giving up (poweroff/reboot needed).",
			(fw_state & RENESAS_FW_STATUS_RESULT) >> 4);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक renesas_fw_करोwnload(काष्ठा pci_dev *pdev,
			       स्थिर काष्ठा firmware *fw)
अणु
	स्थिर u32 *fw_data = (स्थिर u32 *)fw->data;
	माप_प्रकार i;
	पूर्णांक err;
	u8 fw_status;

	/*
	 * For more inक्रमmation and the big picture: please look at the
	 * "Firmware Download Sequence" in "7.1 FW Download Interface"
	 * of R19UH0078EJ0500 Rev.5.00 page 131
	 */

	/*
	 * 0. Set "FW Download Enable" bit in the
	 * "FW Download Control & Status Register" at 0xF4
	 */
	err = pci_ग_लिखो_config_byte(pdev, RENESAS_FW_STATUS,
				    RENESAS_FW_STATUS_DOWNLOAD_ENABLE);
	अगर (err)
		वापस pcibios_err_to_त्रुटि_सं(err);

	/* 1 - 10 follow one step after the other. */
	क्रम (i = 0; i < fw->size / 4; i++) अणु
		err = renesas_fw_करोwnload_image(pdev, fw_data, i, false);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"Firmware Download Step %zd failed at position %zd bytes with (%d).",
				i, i * 4, err);
			वापस err;
		पूर्ण
	पूर्ण

	/*
	 * This sequence जारीs until the last data is written to
	 * "DATA0" or "DATA1". Naturally, we रुको until "SET DATA0/1"
	 * is cleared by the hardware beक्रमehand.
	 */
	क्रम (i = 0; i < RENESAS_RETRY; i++) अणु
		err = pci_पढ़ो_config_byte(pdev, RENESAS_FW_STATUS_MSB,
					   &fw_status);
		अगर (err)
			वापस pcibios_err_to_त्रुटि_सं(err);
		अगर (!(fw_status & (BIT(0) | BIT(1))))
			अवरोध;

		udelay(RENESAS_DELAY);
	पूर्ण
	अगर (i == RENESAS_RETRY)
		dev_warn(&pdev->dev, "Final Firmware Download step timed out.");

	/*
	 * 11. After finishing writing the last data of FW, the
	 * System Software must clear "FW Download Enable"
	 */
	err = pci_ग_लिखो_config_byte(pdev, RENESAS_FW_STATUS, 0);
	अगर (err)
		वापस pcibios_err_to_त्रुटि_सं(err);

	/* 12. Read "Result Code" and confirm it is good. */
	क्रम (i = 0; i < RENESAS_RETRY; i++) अणु
		err = pci_पढ़ो_config_byte(pdev, RENESAS_FW_STATUS, &fw_status);
		अगर (err)
			वापस pcibios_err_to_त्रुटि_सं(err);
		अगर (fw_status & RENESAS_FW_STATUS_SUCCESS)
			अवरोध;

		udelay(RENESAS_DELAY);
	पूर्ण
	अगर (i == RENESAS_RETRY) अणु
		/* Timed out / Error - let's see अगर we can fix this */
		err = renesas_fw_check_running(pdev);
		चयन (err) अणु
		हाल 0: /*
			 * we shouldn't end up here.
			 * maybe it took a little bit दीर्घer.
			 * But all should be well?
			 */
			अवरोध;

		हाल 1: /* (No result yet! */
			dev_err(&pdev->dev, "FW Load timedout");
			वापस -ETIMEDOUT;

		शेष:
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम renesas_rom_erase(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक retval, i;
	u8 status;

	dev_dbg(&pdev->dev, "Performing ROM Erase...\n");
	retval = pci_ग_लिखो_config_dword(pdev, RENESAS_DATA0,
					RENESAS_ROM_ERASE_MAGIC);
	अगर (retval) अणु
		dev_err(&pdev->dev, "ROM erase, magic word write failed: %d\n",
			pcibios_err_to_त्रुटि_सं(retval));
		वापस;
	पूर्ण

	retval = pci_पढ़ो_config_byte(pdev, RENESAS_ROM_STATUS, &status);
	अगर (retval) अणु
		dev_err(&pdev->dev, "ROM status read failed: %d\n",
			pcibios_err_to_त्रुटि_सं(retval));
		वापस;
	पूर्ण
	status |= RENESAS_ROM_STATUS_ERASE;
	retval = pci_ग_लिखो_config_byte(pdev, RENESAS_ROM_STATUS, status);
	अगर (retval) अणु
		dev_err(&pdev->dev, "ROM erase set word write failed\n");
		वापस;
	पूर्ण

	/* sleep a bit जबतक ROM is erased */
	msleep(20);

	क्रम (i = 0; i < RENESAS_RETRY; i++) अणु
		retval = pci_पढ़ो_config_byte(pdev, RENESAS_ROM_STATUS,
					      &status);
		status &= RENESAS_ROM_STATUS_ERASE;
		अगर (!status)
			अवरोध;

		mdelay(RENESAS_DELAY);
	पूर्ण

	अगर (i == RENESAS_RETRY)
		dev_dbg(&pdev->dev, "Chip erase timedout: %x\n", status);

	dev_dbg(&pdev->dev, "ROM Erase... Done success\n");
पूर्ण

अटल bool renesas_setup_rom(काष्ठा pci_dev *pdev, स्थिर काष्ठा firmware *fw)
अणु
	स्थिर u32 *fw_data = (स्थिर u32 *)fw->data;
	पूर्णांक err, i;
	u8 status;

	/* 2. Write magic word to Data0 */
	err = pci_ग_लिखो_config_dword(pdev, RENESAS_DATA0,
				     RENESAS_ROM_WRITE_MAGIC);
	अगर (err)
		वापस false;

	/* 3. Set External ROM access */
	err = pci_ग_लिखो_config_byte(pdev, RENESAS_ROM_STATUS,
				    RENESAS_ROM_STATUS_ACCESS);
	अगर (err)
		जाओ हटाओ_bypass;

	/* 4. Check the result */
	err = pci_पढ़ो_config_byte(pdev, RENESAS_ROM_STATUS, &status);
	अगर (err)
		जाओ हटाओ_bypass;
	status &= GENMASK(6, 4);
	अगर (status) अणु
		dev_err(&pdev->dev,
			"setting external rom failed: %x\n", status);
		जाओ हटाओ_bypass;
	पूर्ण

	/* 5 to 16 Write FW to DATA0/1 जबतक checking SetData0/1 */
	क्रम (i = 0; i < fw->size / 4; i++) अणु
		err = renesas_fw_करोwnload_image(pdev, fw_data, i, true);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"ROM Download Step %d failed at position %d bytes with (%d)\n",
				 i, i * 4, err);
			जाओ हटाओ_bypass;
		पूर्ण
	पूर्ण

	/*
	 * रुको till DATA0/1 is cleared
	 */
	क्रम (i = 0; i < RENESAS_RETRY; i++) अणु
		err = pci_पढ़ो_config_byte(pdev, RENESAS_ROM_STATUS_MSB,
					   &status);
		अगर (err)
			जाओ हटाओ_bypass;
		अगर (!(status & (BIT(0) | BIT(1))))
			अवरोध;

		udelay(RENESAS_DELAY);
	पूर्ण
	अगर (i == RENESAS_RETRY) अणु
		dev_err(&pdev->dev, "Final Firmware ROM Download step timed out\n");
		जाओ हटाओ_bypass;
	पूर्ण

	/* 17. Remove bypass */
	err = pci_ग_लिखो_config_byte(pdev, RENESAS_ROM_STATUS, 0);
	अगर (err)
		वापस false;

	udelay(10);

	/* 18. check result */
	क्रम (i = 0; i < RENESAS_RETRY; i++) अणु
		err = pci_पढ़ो_config_byte(pdev, RENESAS_ROM_STATUS, &status);
		अगर (err) अणु
			dev_err(&pdev->dev, "Read ROM status failed:%d\n",
				pcibios_err_to_त्रुटि_सं(err));
			वापस false;
		पूर्ण
		status &= RENESAS_ROM_STATUS_RESULT;
		अगर (status ==  RENESAS_ROM_STATUS_SUCCESS) अणु
			dev_dbg(&pdev->dev, "Download ROM success\n");
			अवरोध;
		पूर्ण
		udelay(RENESAS_DELAY);
	पूर्ण
	अगर (i == RENESAS_RETRY) अणु /* Timed out */
		dev_err(&pdev->dev,
			"Download to external ROM TO: %x\n", status);
		वापस false;
	पूर्ण

	dev_dbg(&pdev->dev, "Download to external ROM succeeded\n");

	/* Last step set Reload */
	err = pci_ग_लिखो_config_byte(pdev, RENESAS_ROM_STATUS,
				    RENESAS_ROM_STATUS_RELOAD);
	अगर (err) अणु
		dev_err(&pdev->dev, "Set ROM execute failed: %d\n",
			pcibios_err_to_त्रुटि_सं(err));
		वापस false;
	पूर्ण

	/*
	 * रुको till Reload is cleared
	 */
	क्रम (i = 0; i < RENESAS_RETRY; i++) अणु
		err = pci_पढ़ो_config_byte(pdev, RENESAS_ROM_STATUS, &status);
		अगर (err)
			वापस false;
		अगर (!(status & RENESAS_ROM_STATUS_RELOAD))
			अवरोध;

		udelay(RENESAS_DELAY);
	पूर्ण
	अगर (i == RENESAS_RETRY) अणु
		dev_err(&pdev->dev, "ROM Exec timed out: %x\n", status);
		वापस false;
	पूर्ण

	वापस true;

हटाओ_bypass:
	pci_ग_लिखो_config_byte(pdev, RENESAS_ROM_STATUS, 0);
	वापस false;
पूर्ण

अटल पूर्णांक renesas_load_fw(काष्ठा pci_dev *pdev, स्थिर काष्ठा firmware *fw)
अणु
	पूर्णांक err = 0;
	bool rom;

	/* Check अगर the device has बाह्यal ROM */
	rom = renesas_check_rom(pdev);
	अगर (rom) अणु
		/* perक्रमm chip erase first */
		renesas_rom_erase(pdev);

		/* lets try loading fw on ROM first */
		rom = renesas_setup_rom(pdev, fw);
		अगर (!rom) अणु
			dev_dbg(&pdev->dev,
				"ROM load failed, falling back on FW load\n");
		पूर्ण अन्यथा अणु
			dev_dbg(&pdev->dev,
				"ROM load success\n");
			जाओ निकास;
		पूर्ण
	पूर्ण

	err = renesas_fw_करोwnload(pdev, fw);

निकास:
	अगर (err)
		dev_err(&pdev->dev, "firmware failed to download (%d).", err);
	वापस err;
पूर्ण

पूर्णांक renesas_xhci_check_request_fw(काष्ठा pci_dev *pdev,
				  स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा xhci_driver_data *driver_data =
			(काष्ठा xhci_driver_data *)id->driver_data;
	स्थिर अक्षर *fw_name = driver_data->firmware;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक err;

	err = renesas_fw_check_running(pdev);
	/* Continue ahead, अगर the firmware is alपढ़ोy running. */
	अगर (err == 0)
		वापस 0;

	अगर (err != 1)
		वापस err;

	pci_dev_get(pdev);
	err = request_firmware(&fw, fw_name, &pdev->dev);
	pci_dev_put(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "request_firmware failed: %d\n", err);
		वापस err;
	पूर्ण

	err = renesas_fw_verअगरy(fw->data, fw->size);
	अगर (err)
		जाओ निकास;

	err = renesas_load_fw(pdev, fw);
निकास:
	release_firmware(fw);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(renesas_xhci_check_request_fw);

व्योम renesas_xhci_pci_निकास(काष्ठा pci_dev *dev)
अणु
पूर्ण
EXPORT_SYMBOL_GPL(renesas_xhci_pci_निकास);

MODULE_LICENSE("GPL v2");
