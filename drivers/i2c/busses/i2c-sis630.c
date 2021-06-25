<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Copyright (c) 2002,2003 Alexander Malysh <amalysh@web.de>

*/

/*
   Status: beta

   Supports:
	SIS 630
	SIS 730
	SIS 964

   Notable dअगरferences between chips:
	+------------------------+--------------------+-------------------+
	|                        |     SIS630/730     |      SIS964       |
	+------------------------+--------------------+-------------------+
	| Clock                  | 14kHz/56kHz        | 55.56kHz/27.78kHz |
	| SMBus रेजिस्टरs offset | 0x80               | 0xE0              |
	| SMB_CNT                | Bit 1 = Slave Busy | Bit 1 = Bus probe |
	|         (not used yet) | Bit 3 is reserved  | Bit 3 = Last byte |
	| SMB_PCOUNT		 | Offset + 0x06      | Offset + 0x14     |
	| SMB_COUNT              | 4:0 bits           | 5:0 bits          |
	+------------------------+--------------------+-------------------+
	(Other dअगरferences करोn't affect the functions provided by the driver)

   Note: we assume there can only be one device, with one SMBus पूर्णांकerface.
*/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/ioport.h>
#समावेश <linux/i2c.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>

/* SIS964 id is defined here as we are the only file using it */
#घोषणा PCI_DEVICE_ID_SI_964	0x0964

/* SIS630/730/964 SMBus रेजिस्टरs */
#घोषणा SMB_STS			0x00	/* status */
#घोषणा SMB_CNT			0x02	/* control */
#घोषणा SMBHOST_CNT		0x03	/* host control */
#घोषणा SMB_ADDR		0x04	/* address */
#घोषणा SMB_CMD			0x05	/* command */
#घोषणा SMB_COUNT		0x07	/* byte count */
#घोषणा SMB_BYTE		0x08	/* ~0x8F data byte field */

/* SMB_STS रेजिस्टर */
#घोषणा BYTE_DONE_STS		0x10	/* Byte Done Status / Block Array */
#घोषणा SMBCOL_STS		0x04	/* Collision */
#घोषणा SMBERR_STS		0x02	/* Device error */

/* SMB_CNT रेजिस्टर */
#घोषणा MSTO_EN			0x40	/* Host Master Timeout Enable */
#घोषणा SMBCLK_SEL		0x20	/* Host master घड़ी selection */
#घोषणा SMB_PROBE		0x02	/* Bus Probe/Slave busy */
#घोषणा SMB_HOSTBUSY		0x01	/* Host Busy */

/* SMBHOST_CNT रेजिस्टर */
#घोषणा SMB_KILL		0x20	/* Kill */
#घोषणा SMB_START		0x10	/* Start */

/* रेजिस्टर count क्रम request_region
 * As we करोn't use SMB_PCOUNT, 20 is ok क्रम SiS630 and SiS964
 */
#घोषणा SIS630_SMB_IOREGION	20

/* PCI address स्थिरants */
/* acpi base address रेजिस्टर  */
#घोषणा SIS630_ACPI_BASE_REG	0x74
/* bios control रेजिस्टर */
#घोषणा SIS630_BIOS_CTL_REG	0x40

/* Other settings */
#घोषणा MAX_TIMEOUT		500

/* SIS630 स्थिरants */
#घोषणा SIS630_QUICK		0x00
#घोषणा SIS630_BYTE		0x01
#घोषणा SIS630_BYTE_DATA	0x02
#घोषणा SIS630_WORD_DATA	0x03
#घोषणा SIS630_PCALL		0x04
#घोषणा SIS630_BLOCK_DATA	0x05

अटल काष्ठा pci_driver sis630_driver;

/* insmod parameters */
अटल bool high_घड़ी;
अटल bool क्रमce;
module_param(high_घड़ी, bool, 0);
MODULE_PARM_DESC(high_घड़ी,
	"Set Host Master Clock to 56KHz (default 14KHz) (SIS630/730 only).");
module_param(क्रमce, bool, 0);
MODULE_PARM_DESC(क्रमce, "Forcibly enable the SIS630. DANGEROUS!");

/* SMBus base adress */
अटल अचिन्हित लघु smbus_base;

/* supported chips */
अटल पूर्णांक supported[] = अणु
	PCI_DEVICE_ID_SI_630,
	PCI_DEVICE_ID_SI_730,
	PCI_DEVICE_ID_SI_760,
	0 /* terminates the list */
पूर्ण;

अटल अंतरभूत u8 sis630_पढ़ो(u8 reg)
अणु
	वापस inb(smbus_base + reg);
पूर्ण

अटल अंतरभूत व्योम sis630_ग_लिखो(u8 reg, u8 data)
अणु
	outb(data, smbus_base + reg);
पूर्ण

अटल पूर्णांक sis630_transaction_start(काष्ठा i2c_adapter *adap, पूर्णांक size,
				    u8 *oldघड़ी)
अणु
	पूर्णांक temp;

	/* Make sure the SMBus host is पढ़ोy to start transmitting. */
	temp = sis630_पढ़ो(SMB_CNT);
	अगर ((temp & (SMB_PROBE | SMB_HOSTBUSY)) != 0x00) अणु
		dev_dbg(&adap->dev, "SMBus busy (%02x). Resetting...\n", temp);
		/* समाप्त smbus transaction */
		sis630_ग_लिखो(SMBHOST_CNT, SMB_KILL);

		temp = sis630_पढ़ो(SMB_CNT);
		अगर (temp & (SMB_PROBE | SMB_HOSTBUSY)) अणु
			dev_dbg(&adap->dev, "Failed! (%02x)\n", temp);
			वापस -EBUSY;
		पूर्ण अन्यथा अणु
			dev_dbg(&adap->dev, "Successful!\n");
		पूर्ण
	पूर्ण

	/* save old घड़ी, so we can prevent machine क्रम hung */
	*oldघड़ी = sis630_पढ़ो(SMB_CNT);

	dev_dbg(&adap->dev, "saved clock 0x%02x\n", *oldघड़ी);

	/* disable समयout पूर्णांकerrupt,
	 * set Host Master Clock to 56KHz अगर requested */
	अगर (high_घड़ी)
		sis630_ग_लिखो(SMB_CNT, SMBCLK_SEL);
	अन्यथा
		sis630_ग_लिखो(SMB_CNT, (*oldघड़ी & ~MSTO_EN));

	/* clear all sticky bits */
	temp = sis630_पढ़ो(SMB_STS);
	sis630_ग_लिखो(SMB_STS, temp & 0x1e);

	/* start the transaction by setting bit 4 and size */
	sis630_ग_लिखो(SMBHOST_CNT, SMB_START | (size & 0x07));

	वापस 0;
पूर्ण

अटल पूर्णांक sis630_transaction_रुको(काष्ठा i2c_adapter *adap, पूर्णांक size)
अणु
	पूर्णांक temp, result = 0, समयout = 0;

	/* We will always रुको क्रम a fraction of a second! */
	करो अणु
		msleep(1);
		temp = sis630_पढ़ो(SMB_STS);
		/* check अगर block transmitted */
		अगर (size == SIS630_BLOCK_DATA && (temp & BYTE_DONE_STS))
			अवरोध;
	पूर्ण जबतक (!(temp & 0x0e) && (समयout++ < MAX_TIMEOUT));

	/* If the SMBus is still busy, we give up */
	अगर (समयout > MAX_TIMEOUT) अणु
		dev_dbg(&adap->dev, "SMBus Timeout!\n");
		result = -ETIMEDOUT;
	पूर्ण

	अगर (temp & SMBERR_STS) अणु
		dev_dbg(&adap->dev, "Error: Failed bus transaction\n");
		result = -ENXIO;
	पूर्ण

	अगर (temp & SMBCOL_STS) अणु
		dev_err(&adap->dev, "Bus collision!\n");
		result = -EAGAIN;
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम sis630_transaction_end(काष्ठा i2c_adapter *adap, u8 oldघड़ी)
अणु
	/* clear all status "sticky" bits */
	sis630_ग_लिखो(SMB_STS, 0xFF);

	dev_dbg(&adap->dev,
		"SMB_CNT before clock restore 0x%02x\n", sis630_पढ़ो(SMB_CNT));

	/*
	 * restore old Host Master Clock अगर high_घड़ी is set
	 * and oldघड़ी was not 56KHz
	 */
	अगर (high_घड़ी && !(oldघड़ी & SMBCLK_SEL))
		sis630_ग_लिखो(SMB_CNT, sis630_पढ़ो(SMB_CNT) & ~SMBCLK_SEL);

	dev_dbg(&adap->dev,
		"SMB_CNT after clock restore 0x%02x\n", sis630_पढ़ो(SMB_CNT));
पूर्ण

अटल पूर्णांक sis630_transaction(काष्ठा i2c_adapter *adap, पूर्णांक size)
अणु
	पूर्णांक result = 0;
	u8 oldघड़ी = 0;

	result = sis630_transaction_start(adap, size, &oldघड़ी);
	अगर (!result) अणु
		result = sis630_transaction_रुको(adap, size);
		sis630_transaction_end(adap, oldघड़ी);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक sis630_block_data(काष्ठा i2c_adapter *adap,
			     जोड़ i2c_smbus_data *data, पूर्णांक पढ़ो_ग_लिखो)
अणु
	पूर्णांक i, len = 0, rc = 0;
	u8 oldघड़ी = 0;

	अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
		len = data->block[0];
		अगर (len < 0)
			len = 0;
		अन्यथा अगर (len > 32)
			len = 32;
		sis630_ग_लिखो(SMB_COUNT, len);
		क्रम (i = 1; i <= len; i++) अणु
			dev_dbg(&adap->dev,
				"set data 0x%02x\n", data->block[i]);
			/* set data */
			sis630_ग_लिखो(SMB_BYTE + (i - 1) % 8, data->block[i]);
			अगर (i == 8 || (len < 8 && i == len)) अणु
				dev_dbg(&adap->dev,
					"start trans len=%d i=%d\n", len, i);
				/* first transaction */
				rc = sis630_transaction_start(adap,
						SIS630_BLOCK_DATA, &oldघड़ी);
				अगर (rc)
					वापस rc;
			पूर्ण अन्यथा अगर ((i - 1) % 8 == 7 || i == len) अणु
				dev_dbg(&adap->dev,
					"trans_wait len=%d i=%d\n", len, i);
				अगर (i > 8) अणु
					dev_dbg(&adap->dev,
						"clear smbary_sts"
						" len=%d i=%d\n", len, i);
					/*
					   If this is not first transaction,
					   we must clear sticky bit.
					   clear SMBARY_STS
					*/
					sis630_ग_लिखो(SMB_STS, BYTE_DONE_STS);
				पूर्ण
				rc = sis630_transaction_रुको(adap,
						SIS630_BLOCK_DATA);
				अगर (rc) अणु
					dev_dbg(&adap->dev,
						"trans_wait failed\n");
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* पढ़ो request */
		data->block[0] = len = 0;
		rc = sis630_transaction_start(adap,
				SIS630_BLOCK_DATA, &oldघड़ी);
		अगर (rc)
			वापस rc;
		करो अणु
			rc = sis630_transaction_रुको(adap, SIS630_BLOCK_DATA);
			अगर (rc) अणु
				dev_dbg(&adap->dev, "trans_wait failed\n");
				अवरोध;
			पूर्ण
			/* अगर this first transaction then पढ़ो byte count */
			अगर (len == 0)
				data->block[0] = sis630_पढ़ो(SMB_COUNT);

			/* just to be sure */
			अगर (data->block[0] > 32)
				data->block[0] = 32;

			dev_dbg(&adap->dev,
				"block data read len=0x%x\n", data->block[0]);

			क्रम (i = 0; i < 8 && len < data->block[0]; i++, len++) अणु
				dev_dbg(&adap->dev,
					"read i=%d len=%d\n", i, len);
				data->block[len + 1] = sis630_पढ़ो(SMB_BYTE +
								   i);
			पूर्ण

			dev_dbg(&adap->dev,
				"clear smbary_sts len=%d i=%d\n", len, i);

			/* clear SMBARY_STS */
			sis630_ग_लिखो(SMB_STS, BYTE_DONE_STS);
		पूर्ण जबतक (len < data->block[0]);
	पूर्ण

	sis630_transaction_end(adap, oldघड़ी);

	वापस rc;
पूर्ण

/* Return negative त्रुटि_सं on error. */
अटल s32 sis630_access(काष्ठा i2c_adapter *adap, u16 addr,
			 अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
			 u8 command, पूर्णांक size, जोड़ i2c_smbus_data *data)
अणु
	पूर्णांक status;

	चयन (size) अणु
	हाल I2C_SMBUS_QUICK:
		sis630_ग_लिखो(SMB_ADDR,
			     ((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01));
		size = SIS630_QUICK;
		अवरोध;
	हाल I2C_SMBUS_BYTE:
		sis630_ग_लिखो(SMB_ADDR,
			     ((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01));
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			sis630_ग_लिखो(SMB_CMD, command);
		size = SIS630_BYTE;
		अवरोध;
	हाल I2C_SMBUS_BYTE_DATA:
		sis630_ग_लिखो(SMB_ADDR,
			     ((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01));
		sis630_ग_लिखो(SMB_CMD, command);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			sis630_ग_लिखो(SMB_BYTE, data->byte);
		size = SIS630_BYTE_DATA;
		अवरोध;
	हाल I2C_SMBUS_PROC_CALL:
	हाल I2C_SMBUS_WORD_DATA:
		sis630_ग_लिखो(SMB_ADDR,
			     ((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01));
		sis630_ग_लिखो(SMB_CMD, command);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			sis630_ग_लिखो(SMB_BYTE, data->word & 0xff);
			sis630_ग_लिखो(SMB_BYTE + 1, (data->word & 0xff00) >> 8);
		पूर्ण
		size = (size == I2C_SMBUS_PROC_CALL ?
			SIS630_PCALL : SIS630_WORD_DATA);
		अवरोध;
	हाल I2C_SMBUS_BLOCK_DATA:
		sis630_ग_लिखो(SMB_ADDR,
			     ((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01));
		sis630_ग_लिखो(SMB_CMD, command);
		size = SIS630_BLOCK_DATA;
		वापस sis630_block_data(adap, data, पढ़ो_ग_लिखो);
	शेष:
		dev_warn(&adap->dev, "Unsupported transaction %d\n", size);
		वापस -EOPNOTSUPP;
	पूर्ण

	status = sis630_transaction(adap, size);
	अगर (status)
		वापस status;

	अगर ((size != SIS630_PCALL) &&
		((पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) || (size == SIS630_QUICK))) अणु
		वापस 0;
	पूर्ण

	चयन (size) अणु
	हाल SIS630_BYTE:
	हाल SIS630_BYTE_DATA:
		data->byte = sis630_पढ़ो(SMB_BYTE);
		अवरोध;
	हाल SIS630_PCALL:
	हाल SIS630_WORD_DATA:
		data->word = sis630_पढ़ो(SMB_BYTE) +
			     (sis630_पढ़ो(SMB_BYTE + 1) << 8);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 sis630_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
		I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
		I2C_FUNC_SMBUS_PROC_CALL | I2C_FUNC_SMBUS_BLOCK_DATA;
पूर्ण

अटल पूर्णांक sis630_setup(काष्ठा pci_dev *sis630_dev)
अणु
	अचिन्हित अक्षर b;
	काष्ठा pci_dev *dummy = शून्य;
	पूर्णांक retval, i;
	/* acpi base address */
	अचिन्हित लघु acpi_base;

	/* check क्रम supported SiS devices */
	क्रम (i = 0; supported[i] > 0; i++) अणु
		dummy = pci_get_device(PCI_VENDOR_ID_SI, supported[i], dummy);
		अगर (dummy)
			अवरोध; /* found */
	पूर्ण

	अगर (dummy) अणु
		pci_dev_put(dummy);
	पूर्ण अन्यथा अगर (क्रमce) अणु
		dev_err(&sis630_dev->dev,
			"WARNING: Can't detect SIS630 compatible device, but "
			"loading because of force option enabled\n");
	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण

	/*
	   Enable ACPI first , so we can accsess reg 74-75
	   in acpi io space and पढ़ो acpi base addr
	*/
	अगर (pci_पढ़ो_config_byte(sis630_dev, SIS630_BIOS_CTL_REG, &b)) अणु
		dev_err(&sis630_dev->dev, "Error: Can't read bios ctl reg\n");
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण
	/* अगर ACPI alपढ़ोy enabled , करो nothing */
	अगर (!(b & 0x80) &&
	    pci_ग_लिखो_config_byte(sis630_dev, SIS630_BIOS_CTL_REG, b | 0x80)) अणु
		dev_err(&sis630_dev->dev, "Error: Can't enable ACPI\n");
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण

	/* Determine the ACPI base address */
	अगर (pci_पढ़ो_config_word(sis630_dev,
				 SIS630_ACPI_BASE_REG, &acpi_base)) अणु
		dev_err(&sis630_dev->dev,
			"Error: Can't determine ACPI base address\n");
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण

	dev_dbg(&sis630_dev->dev, "ACPI base at 0x%04hx\n", acpi_base);

	अगर (supported[i] == PCI_DEVICE_ID_SI_760)
		smbus_base = acpi_base + 0xE0;
	अन्यथा
		smbus_base = acpi_base + 0x80;

	dev_dbg(&sis630_dev->dev, "SMBus base at 0x%04hx\n", smbus_base);

	retval = acpi_check_region(smbus_base + SMB_STS, SIS630_SMB_IOREGION,
				   sis630_driver.name);
	अगर (retval)
		जाओ निकास;

	/* Everything is happy, let's grab the memory and set things up. */
	अगर (!request_region(smbus_base + SMB_STS, SIS630_SMB_IOREGION,
			    sis630_driver.name)) अणु
		dev_err(&sis630_dev->dev,
			"I/O Region 0x%04x-0x%04x for SMBus already in use.\n",
			smbus_base + SMB_STS,
			smbus_base + SMB_STS + SIS630_SMB_IOREGION - 1);
		retval = -EBUSY;
		जाओ निकास;
	पूर्ण

	retval = 0;

निकास:
	अगर (retval)
		smbus_base = 0;
	वापस retval;
पूर्ण


अटल स्थिर काष्ठा i2c_algorithm smbus_algorithm = अणु
	.smbus_xfer	= sis630_access,
	.functionality	= sis630_func,
पूर्ण;

अटल काष्ठा i2c_adapter sis630_adapter = अणु
	.owner		= THIS_MODULE,
	.class		= I2C_CLASS_HWMON | I2C_CLASS_SPD,
	.algo		= &smbus_algorithm,
	.retries	= 3
पूर्ण;

अटल स्थिर काष्ठा pci_device_id sis630_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_503) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_LPC) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_964) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, sis630_ids);

अटल पूर्णांक sis630_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	अगर (sis630_setup(dev)) अणु
		dev_err(&dev->dev,
			"SIS630 compatible bus not detected, "
			"module not inserted.\n");
		वापस -ENODEV;
	पूर्ण

	/* set up the sysfs linkage to our parent device */
	sis630_adapter.dev.parent = &dev->dev;

	snम_लिखो(sis630_adapter.name, माप(sis630_adapter.name),
		 "SMBus SIS630 adapter at %04x", smbus_base + SMB_STS);

	वापस i2c_add_adapter(&sis630_adapter);
पूर्ण

अटल व्योम sis630_हटाओ(काष्ठा pci_dev *dev)
अणु
	अगर (smbus_base) अणु
		i2c_del_adapter(&sis630_adapter);
		release_region(smbus_base + SMB_STS, SIS630_SMB_IOREGION);
		smbus_base = 0;
	पूर्ण
पूर्ण


अटल काष्ठा pci_driver sis630_driver = अणु
	.name		= "sis630_smbus",
	.id_table	= sis630_ids,
	.probe		= sis630_probe,
	.हटाओ		= sis630_हटाओ,
पूर्ण;

module_pci_driver(sis630_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexander Malysh <amalysh@web.de>");
MODULE_DESCRIPTION("SIS630 SMBus driver");
