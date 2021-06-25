<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Copyright (c) 1998 - 2002  Froकरो Looijaard <froकरोl@dds.nl>,
    Philip Edelbrock <phil@netroedge.com>, Kyथघsti Mथअlkki <kmalkki@cc.hut.fi>,
    Mark D. Studebaker <mdsxyz123@yahoo.com>
    Copyright (C) 2005 - 2008  Jean Delvare <jdelvare@suse.de>

*/

/*
   Supports the following VIA south bridges:

   Chip name          PCI ID  REV     I2C block
   VT82C596A          0x3050             no
   VT82C596B          0x3051             no
   VT82C686A          0x3057  0x30       no
   VT82C686B          0x3057  0x40       yes
   VT8231             0x8235             no?
   VT8233             0x3074             yes
   VT8233A            0x3147             yes?
   VT8235             0x3177             yes
   VT8237R            0x3227             yes
   VT8237A            0x3337             yes
   VT8237S            0x3372             yes
   VT8251             0x3287             yes
   CX700              0x8324             yes
   VX800/VX820        0x8353             yes
   VX855/VX875        0x8409             yes

   Note: we assume there can only be one device, with one SMBus पूर्णांकerface.
*/

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/ioport.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>

अटल काष्ठा pci_dev *vt596_pdev;

#घोषणा SMBBA1		0x90
#घोषणा SMBBA2		0x80
#घोषणा SMBBA3		0xD0

/* SMBus address offsets */
अटल अचिन्हित लघु vt596_smba;
#घोषणा SMBHSTSTS	(vt596_smba + 0)
#घोषणा SMBHSTCNT	(vt596_smba + 2)
#घोषणा SMBHSTCMD	(vt596_smba + 3)
#घोषणा SMBHSTADD	(vt596_smba + 4)
#घोषणा SMBHSTDAT0	(vt596_smba + 5)
#घोषणा SMBHSTDAT1	(vt596_smba + 6)
#घोषणा SMBBLKDAT	(vt596_smba + 7)

/* PCI Address Constants */

/* SMBus data in configuration space can be found in two places,
   We try to select the better one */

अटल अचिन्हित लघु SMBHSTCFG = 0xD2;

/* Other settings */
#घोषणा MAX_TIMEOUT	500

/* VT82C596 स्थिरants */
#घोषणा VT596_QUICK		0x00
#घोषणा VT596_BYTE		0x04
#घोषणा VT596_BYTE_DATA		0x08
#घोषणा VT596_WORD_DATA		0x0C
#घोषणा VT596_PROC_CALL		0x10
#घोषणा VT596_BLOCK_DATA	0x14
#घोषणा VT596_I2C_BLOCK_DATA	0x34


/* If क्रमce is set to anything dअगरferent from 0, we क्रमcibly enable the
   VT596. DANGEROUS! */
अटल bool क्रमce;
module_param(क्रमce, bool, 0);
MODULE_PARM_DESC(क्रमce, "Forcibly enable the SMBus. DANGEROUS!");

/* If क्रमce_addr is set to anything dअगरferent from 0, we क्रमcibly enable
   the VT596 at the given address. VERY DANGEROUS! */
अटल u16 क्रमce_addr;
module_param_hw(क्रमce_addr, uलघु, ioport, 0);
MODULE_PARM_DESC(क्रमce_addr,
		 "Forcibly enable the SMBus at the given address. "
		 "EXTREMELY DANGEROUS!");


अटल काष्ठा pci_driver vt596_driver;
अटल काष्ठा i2c_adapter vt596_adapter;

#घोषणा FEATURE_I2CBLOCK	(1<<0)
अटल अचिन्हित पूर्णांक vt596_features;

#अगर_घोषित DEBUG
अटल व्योम vt596_dump_regs(स्थिर अक्षर *msg, u8 size)
अणु
	dev_dbg(&vt596_adapter.dev, "%s: STS=%02x CNT=%02x CMD=%02x ADD=%02x "
		"DAT=%02x,%02x\n", msg, inb_p(SMBHSTSTS), inb_p(SMBHSTCNT),
		inb_p(SMBHSTCMD), inb_p(SMBHSTADD), inb_p(SMBHSTDAT0),
		inb_p(SMBHSTDAT1));

	अगर (size == VT596_BLOCK_DATA
	 || size == VT596_I2C_BLOCK_DATA) अणु
		पूर्णांक i;

		dev_dbg(&vt596_adapter.dev, "BLK=");
		क्रम (i = 0; i < I2C_SMBUS_BLOCK_MAX / 2; i++)
			prपूर्णांकk("%02x,", inb_p(SMBBLKDAT));
		prपूर्णांकk("\n");
		dev_dbg(&vt596_adapter.dev, "    ");
		क्रम (; i < I2C_SMBUS_BLOCK_MAX - 1; i++)
			prपूर्णांकk("%02x,", inb_p(SMBBLKDAT));
		prपूर्णांकk("%02x\n", inb_p(SMBBLKDAT));
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम vt596_dump_regs(स्थिर अक्षर *msg, u8 size) अणु पूर्ण
#पूर्ण_अगर

/* Return -1 on error, 0 on success */
अटल पूर्णांक vt596_transaction(u8 size)
अणु
	पूर्णांक temp;
	पूर्णांक result = 0;
	पूर्णांक समयout = 0;

	vt596_dump_regs("Transaction (pre)", size);

	/* Make sure the SMBus host is पढ़ोy to start transmitting */
	अगर ((temp = inb_p(SMBHSTSTS)) & 0x1F) अणु
		dev_dbg(&vt596_adapter.dev, "SMBus busy (0x%02x). "
			"Resetting...\n", temp);

		outb_p(temp, SMBHSTSTS);
		अगर ((temp = inb_p(SMBHSTSTS)) & 0x1F) अणु
			dev_err(&vt596_adapter.dev, "SMBus reset failed! "
				"(0x%02x)\n", temp);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	/* Start the transaction by setting bit 6 */
	outb_p(0x40 | size, SMBHSTCNT);

	/* We will always रुको क्रम a fraction of a second */
	करो अणु
		msleep(1);
		temp = inb_p(SMBHSTSTS);
	पूर्ण जबतक ((temp & 0x01) && (++समयout < MAX_TIMEOUT));

	/* If the SMBus is still busy, we give up */
	अगर (समयout == MAX_TIMEOUT) अणु
		result = -ETIMEDOUT;
		dev_err(&vt596_adapter.dev, "SMBus timeout!\n");
	पूर्ण

	अगर (temp & 0x10) अणु
		result = -EIO;
		dev_err(&vt596_adapter.dev, "Transaction failed (0x%02x)\n",
			size);
	पूर्ण

	अगर (temp & 0x08) अणु
		result = -EIO;
		dev_err(&vt596_adapter.dev, "SMBus collision!\n");
	पूर्ण

	अगर (temp & 0x04) अणु
		result = -ENXIO;
		dev_dbg(&vt596_adapter.dev, "No response\n");
	पूर्ण

	/* Resetting status रेजिस्टर */
	अगर (temp & 0x1F)
		outb_p(temp, SMBHSTSTS);

	vt596_dump_regs("Transaction (post)", size);

	वापस result;
पूर्ण

/* Return negative त्रुटि_सं on error, 0 on success */
अटल s32 vt596_access(काष्ठा i2c_adapter *adap, u16 addr,
		अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो, u8 command,
		पूर्णांक size, जोड़ i2c_smbus_data *data)
अणु
	पूर्णांक i;
	पूर्णांक status;

	चयन (size) अणु
	हाल I2C_SMBUS_QUICK:
		size = VT596_QUICK;
		अवरोध;
	हाल I2C_SMBUS_BYTE:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			outb_p(command, SMBHSTCMD);
		size = VT596_BYTE;
		अवरोध;
	हाल I2C_SMBUS_BYTE_DATA:
		outb_p(command, SMBHSTCMD);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			outb_p(data->byte, SMBHSTDAT0);
		size = VT596_BYTE_DATA;
		अवरोध;
	हाल I2C_SMBUS_WORD_DATA:
		outb_p(command, SMBHSTCMD);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			outb_p(data->word & 0xff, SMBHSTDAT0);
			outb_p((data->word & 0xff00) >> 8, SMBHSTDAT1);
		पूर्ण
		size = VT596_WORD_DATA;
		अवरोध;
	हाल I2C_SMBUS_PROC_CALL:
		outb_p(command, SMBHSTCMD);
		outb_p(data->word & 0xff, SMBHSTDAT0);
		outb_p((data->word & 0xff00) >> 8, SMBHSTDAT1);
		size = VT596_PROC_CALL;
		अवरोध;
	हाल I2C_SMBUS_I2C_BLOCK_DATA:
		अगर (!(vt596_features & FEATURE_I2CBLOCK))
			जाओ निकास_unsupported;
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ)
			outb_p(data->block[0], SMBHSTDAT0);
		fallthrough;
	हाल I2C_SMBUS_BLOCK_DATA:
		outb_p(command, SMBHSTCMD);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			u8 len = data->block[0];
			अगर (len > I2C_SMBUS_BLOCK_MAX)
				len = I2C_SMBUS_BLOCK_MAX;
			outb_p(len, SMBHSTDAT0);
			inb_p(SMBHSTCNT);	/* Reset SMBBLKDAT */
			क्रम (i = 1; i <= len; i++)
				outb_p(data->block[i], SMBBLKDAT);
		पूर्ण
		size = (size == I2C_SMBUS_I2C_BLOCK_DATA) ?
		       VT596_I2C_BLOCK_DATA : VT596_BLOCK_DATA;
		अवरोध;
	शेष:
		जाओ निकास_unsupported;
	पूर्ण

	outb_p(((addr & 0x7f) << 1) | पढ़ो_ग_लिखो, SMBHSTADD);

	status = vt596_transaction(size);
	अगर (status)
		वापस status;

	अगर (size == VT596_PROC_CALL)
		पढ़ो_ग_लिखो = I2C_SMBUS_READ;

	अगर ((पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) || (size == VT596_QUICK))
		वापस 0;

	चयन (size) अणु
	हाल VT596_BYTE:
	हाल VT596_BYTE_DATA:
		data->byte = inb_p(SMBHSTDAT0);
		अवरोध;
	हाल VT596_WORD_DATA:
	हाल VT596_PROC_CALL:
		data->word = inb_p(SMBHSTDAT0) + (inb_p(SMBHSTDAT1) << 8);
		अवरोध;
	हाल VT596_I2C_BLOCK_DATA:
	हाल VT596_BLOCK_DATA:
		data->block[0] = inb_p(SMBHSTDAT0);
		अगर (data->block[0] > I2C_SMBUS_BLOCK_MAX)
			data->block[0] = I2C_SMBUS_BLOCK_MAX;
		inb_p(SMBHSTCNT);	/* Reset SMBBLKDAT */
		क्रम (i = 1; i <= data->block[0]; i++)
			data->block[i] = inb_p(SMBBLKDAT);
		अवरोध;
	पूर्ण
	वापस 0;

निकास_unsupported:
	dev_warn(&vt596_adapter.dev, "Unsupported transaction %d\n",
		 size);
	वापस -EOPNOTSUPP;
पूर्ण

अटल u32 vt596_func(काष्ठा i2c_adapter *adapter)
अणु
	u32 func = I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	    I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
	    I2C_SMBUS_PROC_CALL | I2C_FUNC_SMBUS_BLOCK_DATA;

	अगर (vt596_features & FEATURE_I2CBLOCK)
		func |= I2C_FUNC_SMBUS_I2C_BLOCK;
	वापस func;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm smbus_algorithm = अणु
	.smbus_xfer	= vt596_access,
	.functionality	= vt596_func,
पूर्ण;

अटल काष्ठा i2c_adapter vt596_adapter = अणु
	.owner		= THIS_MODULE,
	.class		= I2C_CLASS_HWMON | I2C_CLASS_SPD,
	.algo		= &smbus_algorithm,
पूर्ण;

अटल पूर्णांक vt596_probe(काष्ठा pci_dev *pdev,
		       स्थिर काष्ठा pci_device_id *id)
अणु
	अचिन्हित अक्षर temp;
	पूर्णांक error;

	/* Determine the address of the SMBus areas */
	अगर (क्रमce_addr) अणु
		vt596_smba = क्रमce_addr & 0xfff0;
		क्रमce = 0;
		जाओ found;
	पूर्ण

	अगर ((pci_पढ़ो_config_word(pdev, id->driver_data, &vt596_smba)) ||
	    !(vt596_smba & 0x0001)) अणु
		/* try 2nd address and config reg. क्रम 596 */
		अगर (id->device == PCI_DEVICE_ID_VIA_82C596_3 &&
		    !pci_पढ़ो_config_word(pdev, SMBBA2, &vt596_smba) &&
		    (vt596_smba & 0x0001)) अणु
			SMBHSTCFG = 0x84;
		पूर्ण अन्यथा अणु
			/* no matches at all */
			dev_err(&pdev->dev, "Cannot configure "
				"SMBus I/O Base address\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	vt596_smba &= 0xfff0;
	अगर (vt596_smba == 0) अणु
		dev_err(&pdev->dev, "SMBus base address "
			"uninitialized - upgrade BIOS or use "
			"force_addr=0xaddr\n");
		वापस -ENODEV;
	पूर्ण

found:
	error = acpi_check_region(vt596_smba, 8, vt596_driver.name);
	अगर (error)
		वापस -ENODEV;

	अगर (!request_region(vt596_smba, 8, vt596_driver.name)) अणु
		dev_err(&pdev->dev, "SMBus region 0x%x already in use!\n",
			vt596_smba);
		वापस -ENODEV;
	पूर्ण

	pci_पढ़ो_config_byte(pdev, SMBHSTCFG, &temp);
	/* If क्रमce_addr is set, we program the new address here. Just to make
	   sure, we disable the VT596 first. */
	अगर (क्रमce_addr) अणु
		pci_ग_लिखो_config_byte(pdev, SMBHSTCFG, temp & 0xfe);
		pci_ग_लिखो_config_word(pdev, id->driver_data, vt596_smba);
		pci_ग_लिखो_config_byte(pdev, SMBHSTCFG, temp | 0x01);
		dev_warn(&pdev->dev, "WARNING: SMBus interface set to new "
			 "address 0x%04x!\n", vt596_smba);
	पूर्ण अन्यथा अगर (!(temp & 0x01)) अणु
		अगर (क्रमce) अणु
			/* NOTE: This assumes I/O space and other allocations
			 * WERE करोne by the Bios!  Don't complain अगर your
			 * hardware करोes weird things after enabling this.
			 * :') Check क्रम Bios updates beक्रमe resorting to
			 * this.
			 */
			pci_ग_लिखो_config_byte(pdev, SMBHSTCFG, temp | 0x01);
			dev_info(&pdev->dev, "Enabling SMBus device\n");
		पूर्ण अन्यथा अणु
			dev_err(&pdev->dev, "SMBUS: Error: Host SMBus "
				"controller not enabled! - upgrade BIOS or "
				"use force=1\n");
			error = -ENODEV;
			जाओ release_region;
		पूर्ण
	पूर्ण

	dev_dbg(&pdev->dev, "VT596_smba = 0x%X\n", vt596_smba);

	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_VIA_CX700:
	हाल PCI_DEVICE_ID_VIA_VX800:
	हाल PCI_DEVICE_ID_VIA_VX855:
	हाल PCI_DEVICE_ID_VIA_VX900:
	हाल PCI_DEVICE_ID_VIA_8251:
	हाल PCI_DEVICE_ID_VIA_8237:
	हाल PCI_DEVICE_ID_VIA_8237A:
	हाल PCI_DEVICE_ID_VIA_8237S:
	हाल PCI_DEVICE_ID_VIA_8235:
	हाल PCI_DEVICE_ID_VIA_8233A:
	हाल PCI_DEVICE_ID_VIA_8233_0:
		vt596_features |= FEATURE_I2CBLOCK;
		अवरोध;
	हाल PCI_DEVICE_ID_VIA_82C686_4:
		/* The VT82C686B (rev 0x40) करोes support I2C block
		   transactions, but the VT82C686A (rev 0x30) करोesn't */
		अगर (pdev->revision >= 0x40)
			vt596_features |= FEATURE_I2CBLOCK;
		अवरोध;
	पूर्ण

	vt596_adapter.dev.parent = &pdev->dev;
	snम_लिखो(vt596_adapter.name, माप(vt596_adapter.name),
		 "SMBus Via Pro adapter at %04x", vt596_smba);

	vt596_pdev = pci_dev_get(pdev);
	error = i2c_add_adapter(&vt596_adapter);
	अगर (error) अणु
		pci_dev_put(vt596_pdev);
		vt596_pdev = शून्य;
		जाओ release_region;
	पूर्ण

	/* Always वापस failure here.  This is to allow other drivers to bind
	 * to this pci device.  We करोn't really want to have control over the
	 * pci device, we only wanted to पढ़ो as few रेजिस्टर values from it.
	 */
	वापस -ENODEV;

release_region:
	release_region(vt596_smba, 8);
	वापस error;
पूर्ण

अटल स्थिर काष्ठा pci_device_id vt596_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_82C596_3),
	  .driver_data = SMBBA1 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_82C596B_3),
	  .driver_data = SMBBA1 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_82C686_4),
	  .driver_data = SMBBA1 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8233_0),
	  .driver_data = SMBBA3 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8233A),
	  .driver_data = SMBBA3 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8235),
	  .driver_data = SMBBA3 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8237),
	  .driver_data = SMBBA3 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8237A),
	  .driver_data = SMBBA3 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8237S),
	  .driver_data = SMBBA3 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8231_4),
	  .driver_data = SMBBA1 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8251),
	  .driver_data = SMBBA3 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_CX700),
	  .driver_data = SMBBA3 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_VX800),
	  .driver_data = SMBBA3 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_VX855),
	  .driver_data = SMBBA3 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_VX900),
	  .driver_data = SMBBA3 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, vt596_ids);

अटल काष्ठा pci_driver vt596_driver = अणु
	.name		= "vt596_smbus",
	.id_table	= vt596_ids,
	.probe		= vt596_probe,
पूर्ण;

अटल पूर्णांक __init i2c_vt596_init(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&vt596_driver);
पूर्ण


अटल व्योम __निकास i2c_vt596_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&vt596_driver);
	अगर (vt596_pdev != शून्य) अणु
		i2c_del_adapter(&vt596_adapter);
		release_region(vt596_smba, 8);
		pci_dev_put(vt596_pdev);
		vt596_pdev = शून्य;
	पूर्ण
पूर्ण

MODULE_AUTHOR("Kyosti Malkki <kmalkki@cc.hut.fi>");
MODULE_AUTHOR("Mark D. Studebaker <mdsxyz123@yahoo.com>");
MODULE_AUTHOR("Jean Delvare <jdelvare@suse.de>");
MODULE_DESCRIPTION("vt82c596 SMBus driver");
MODULE_LICENSE("GPL");

module_init(i2c_vt596_init);
module_निकास(i2c_vt596_निकास);
