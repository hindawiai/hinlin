<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Initialize Owl Emulation Devices
 *
 * Copyright (C) 2016 Christian Lamparter <chunkeey@gmail.com>
 * Copyright (C) 2016 Martin Blumenstingl <martin.blumenstingl@googlemail.com>
 *
 * Some devices (like the Cisco Meraki Z1 Cloud Managed Teleworker Gateway)
 * need to be able to initialize the PCIe wअगरi device. Normally, this is करोne
 * during the early stages as a pci quirk.
 * However, this isn't possible क्रम devices which have the init code क्रम the
 * Atheros chip stored on UBI Volume on न_अंकD. Hence, this module can be used to
 * initialize the chip when the user-space is पढ़ोy to extract the init code.
 */
#समावेश <linux/module.h>
#समावेश <linux/completion.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/firmware.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ath9k_platक्रमm.h>

काष्ठा owl_ctx अणु
	काष्ठा completion eeprom_load;
पूर्ण;

#घोषणा EEPROM_खाताNAME_LEN 100

#घोषणा AR5416_EEPROM_MAGIC 0xa55a

अटल पूर्णांक ath9k_pci_fixup(काष्ठा pci_dev *pdev, स्थिर u16 *cal_data,
			   माप_प्रकार cal_len)
अणु
	व्योम __iomem *mem;
	स्थिर व्योम *cal_end = (व्योम *)cal_data + cal_len;
	स्थिर काष्ठा अणु
		u16 reg;
		u16 low_val;
		u16 high_val;
	पूर्ण __packed * data;
	u16 cmd;
	u32 bar0;
	bool swap_needed = false;

	अगर (*cal_data != AR5416_EEPROM_MAGIC) अणु
		अगर (*cal_data != swab16(AR5416_EEPROM_MAGIC)) अणु
			dev_err(&pdev->dev, "invalid calibration data\n");
			वापस -EINVAL;
		पूर्ण

		dev_dbg(&pdev->dev, "calibration data needs swapping\n");
		swap_needed = true;
	पूर्ण

	dev_info(&pdev->dev, "fixup device configuration\n");

	mem = pcim_iomap(pdev, 0, 0);
	अगर (!mem) अणु
		dev_err(&pdev->dev, "ioremap error\n");
		वापस -EINVAL;
	पूर्ण

	pci_पढ़ो_config_dword(pdev, PCI_BASE_ADDRESS_0, &bar0);
	pci_ग_लिखो_config_dword(pdev, PCI_BASE_ADDRESS_0,
			       pci_resource_start(pdev, 0));
	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &cmd);
	cmd |= PCI_COMMAND_MASTER | PCI_COMMAND_MEMORY;
	pci_ग_लिखो_config_word(pdev, PCI_COMMAND, cmd);

	/* set poपूर्णांकer to first reg address */
	क्रम (data = (स्थिर व्योम *)(cal_data + 3);
	     (स्थिर व्योम *)data <= cal_end && data->reg != (u16)~0;
	     data++) अणु
		u32 val;
		u16 reg;

		reg = data->reg;
		val = data->low_val;
		val |= ((u32)data->high_val) << 16;

		अगर (swap_needed) अणु
			reg = swab16(reg);
			val = swahb32(val);
		पूर्ण

		ioग_लिखो32(val, mem + reg);
		usleep_range(100, 120);
	पूर्ण

	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &cmd);
	cmd &= ~(PCI_COMMAND_MASTER | PCI_COMMAND_MEMORY);
	pci_ग_लिखो_config_word(pdev, PCI_COMMAND, cmd);

	pci_ग_लिखो_config_dword(pdev, PCI_BASE_ADDRESS_0, bar0);
	pcim_iounmap(pdev, mem);

	pci_disable_device(pdev);

	वापस 0;
पूर्ण

अटल व्योम owl_fw_cb(स्थिर काष्ठा firmware *fw, व्योम *context)
अणु
	काष्ठा pci_dev *pdev = (काष्ठा pci_dev *)context;
	काष्ठा owl_ctx *ctx = (काष्ठा owl_ctx *)pci_get_drvdata(pdev);
	काष्ठा pci_bus *bus;

	complete(&ctx->eeprom_load);

	अगर (!fw) अणु
		dev_err(&pdev->dev, "no eeprom data received.\n");
		जाओ release;
	पूर्ण

	/* also note that we are करोing *u16 operations on the file */
	अगर (fw->size > 4096 || fw->size < 0x200 || (fw->size & 1) == 1) अणु
		dev_err(&pdev->dev, "eeprom file has an invalid size.\n");
		जाओ release;
	पूर्ण

	अगर (ath9k_pci_fixup(pdev, (स्थिर u16 *)fw->data, fw->size))
		जाओ release;

	pci_lock_rescan_हटाओ();
	bus = pdev->bus;
	pci_stop_and_हटाओ_bus_device(pdev);
	/* the device should come back with the proper
	 * ProductId. But we have to initiate a rescan.
	 */
	pci_rescan_bus(bus);
	pci_unlock_rescan_हटाओ();

release:
	release_firmware(fw);
पूर्ण

अटल स्थिर अक्षर *owl_get_eeprom_name(काष्ठा pci_dev *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	अक्षर *eeprom_name;

	dev_dbg(dev, "using auto-generated eeprom filename\n");

	eeprom_name = devm_kzalloc(dev, EEPROM_खाताNAME_LEN, GFP_KERNEL);
	अगर (!eeprom_name)
		वापस शून्य;

	/* this should match the pattern used in ath9k/init.c */
	scnम_लिखो(eeprom_name, EEPROM_खाताNAME_LEN, "ath9k-eeprom-pci-%s.bin",
		  dev_name(dev));

	वापस eeprom_name;
पूर्ण

अटल पूर्णांक owl_probe(काष्ठा pci_dev *pdev,
		     स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा owl_ctx *ctx;
	स्थिर अक्षर *eeprom_name;
	पूर्णांक err = 0;

	अगर (pcim_enable_device(pdev))
		वापस -EIO;

	pcim_pin_device(pdev);

	eeprom_name = owl_get_eeprom_name(pdev);
	अगर (!eeprom_name) अणु
		dev_err(&pdev->dev, "no eeprom filename found.\n");
		वापस -ENODEV;
	पूर्ण

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	init_completion(&ctx->eeprom_load);

	pci_set_drvdata(pdev, ctx);
	err = request_firmware_noरुको(THIS_MODULE, true, eeprom_name,
				      &pdev->dev, GFP_KERNEL, pdev, owl_fw_cb);
	अगर (err)
		dev_err(&pdev->dev, "failed to request caldata (%d).\n", err);

	वापस err;
पूर्ण

अटल व्योम owl_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा owl_ctx *ctx = pci_get_drvdata(pdev);

	अगर (ctx) अणु
		रुको_क्रम_completion(&ctx->eeprom_load);
		pci_set_drvdata(pdev, शून्य);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pci_device_id owl_pci_table[] = अणु
	अणु PCI_VDEVICE(ATHEROS, 0xff1c) पूर्ण, /* PCIe */
	अणु PCI_VDEVICE(ATHEROS, 0xff1d) पूर्ण, /* PCI */
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, owl_pci_table);

अटल काष्ठा pci_driver owl_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= owl_pci_table,
	.probe		= owl_probe,
	.हटाओ		= owl_हटाओ,
पूर्ण;
module_pci_driver(owl_driver);
MODULE_AUTHOR("Christian Lamparter <chunkeey@gmail.com>");
MODULE_DESCRIPTION("External EEPROM data loader for Atheros AR500X to AR92XX");
MODULE_LICENSE("Dual BSD/GPL");
