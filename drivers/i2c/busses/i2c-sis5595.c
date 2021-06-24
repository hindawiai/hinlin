<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Copyright (c) 1998, 1999  Froकरो Looijaard <froकरोl@dds.nl> and
    Philip Edelbrock <phil@netroedge.com>

*/

/* Note: we assume there can only be one SIS5595 with one SMBus पूर्णांकerface */

/*
   Note: all have mfr. ID 0x1039.
   SUPPORTED		PCI ID		
	5595		0008

   Note: these chips contain a 0008 device which is incompatible with the
         5595. We recognize these by the presence of the listed
         "blacklist" PCI ID and refuse to load.

   NOT SUPPORTED	PCI ID		BLACKLIST PCI ID	
	 540		0008		0540
	 550		0008		0550
	5513		0008		5511
	5581		0008		5597
	5582		0008		5597
	5597		0008		5597
	5598		0008		5597/5598
	 630		0008		0630
	 645		0008		0645
	 646		0008		0646
	 648		0008		0648
	 650		0008		0650
	 651		0008		0651
	 730		0008		0730
	 735		0008		0735
	 745		0008		0745
	 746		0008		0746
*/

/* TO DO: 
 * Add Block Transfers (ugly, but supported by the adapter)
 * Add adapter resets
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>

अटल पूर्णांक blacklist[] = अणु
	PCI_DEVICE_ID_SI_540,
	PCI_DEVICE_ID_SI_550,
	PCI_DEVICE_ID_SI_630,
	PCI_DEVICE_ID_SI_645,
	PCI_DEVICE_ID_SI_646,
	PCI_DEVICE_ID_SI_648,
	PCI_DEVICE_ID_SI_650,
	PCI_DEVICE_ID_SI_651,
	PCI_DEVICE_ID_SI_730,
	PCI_DEVICE_ID_SI_735,
	PCI_DEVICE_ID_SI_745,
	PCI_DEVICE_ID_SI_746,
	PCI_DEVICE_ID_SI_5511,	/* 5513 chip has the 0008 device but that ID
				   shows up in other chips so we use the 5511
				   ID क्रम recognition */
	PCI_DEVICE_ID_SI_5597,
	PCI_DEVICE_ID_SI_5598,
	0,			/* terminates the list */
पूर्ण;

/* Length of ISA address segment */
#घोषणा SIS5595_EXTENT		8
/* SIS5595 SMBus रेजिस्टरs */
#घोषणा SMB_STS_LO		0x00
#घोषणा SMB_STS_HI		0x01
#घोषणा SMB_CTL_LO		0x02
#घोषणा SMB_CTL_HI		0x03
#घोषणा SMB_ADDR		0x04
#घोषणा SMB_CMD			0x05
#घोषणा SMB_PCNT		0x06
#घोषणा SMB_CNT			0x07
#घोषणा SMB_BYTE		0x08
#घोषणा SMB_DEV			0x10
#घोषणा SMB_DB0			0x11
#घोषणा SMB_DB1			0x12
#घोषणा SMB_HAA			0x13

/* PCI Address Constants */
#घोषणा SMB_INDEX		0x38
#घोषणा SMB_DAT			0x39
#घोषणा SIS5595_ENABLE_REG	0x40
#घोषणा ACPI_BASE		0x90

/* Other settings */
#घोषणा MAX_TIMEOUT		500

/* SIS5595 स्थिरants */
#घोषणा SIS5595_QUICK		0x00
#घोषणा SIS5595_BYTE		0x02
#घोषणा SIS5595_BYTE_DATA	0x04
#घोषणा SIS5595_WORD_DATA	0x06
#घोषणा SIS5595_PROC_CALL	0x08
#घोषणा SIS5595_BLOCK_DATA	0x0A

/* insmod parameters */

/* If क्रमce_addr is set to anything dअगरferent from 0, we क्रमcibly enable
   the device at the given address. */
अटल u16 क्रमce_addr;
module_param_hw(क्रमce_addr, uलघु, ioport, 0);
MODULE_PARM_DESC(क्रमce_addr, "Initialize the base address of the i2c controller");

अटल काष्ठा pci_driver sis5595_driver;
अटल अचिन्हित लघु sis5595_base;
अटल काष्ठा pci_dev *sis5595_pdev;

अटल u8 sis5595_पढ़ो(u8 reg)
अणु
	outb(reg, sis5595_base + SMB_INDEX);
	वापस inb(sis5595_base + SMB_DAT);
पूर्ण

अटल व्योम sis5595_ग_लिखो(u8 reg, u8 data)
अणु
	outb(reg, sis5595_base + SMB_INDEX);
	outb(data, sis5595_base + SMB_DAT);
पूर्ण

अटल पूर्णांक sis5595_setup(काष्ठा pci_dev *SIS5595_dev)
अणु
	u16 a;
	u8 val;
	पूर्णांक *i;
	पूर्णांक retval;

	/* Look क्रम imposters */
	क्रम (i = blacklist; *i != 0; i++) अणु
		काष्ठा pci_dev *dev;
		dev = pci_get_device(PCI_VENDOR_ID_SI, *i, शून्य);
		अगर (dev) अणु
			dev_err(&SIS5595_dev->dev, "Looked for SIS5595 but found unsupported device %.4x\n", *i);
			pci_dev_put(dev);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/* Determine the address of the SMBus areas */
	pci_पढ़ो_config_word(SIS5595_dev, ACPI_BASE, &sis5595_base);
	अगर (sis5595_base == 0 && क्रमce_addr == 0) अणु
		dev_err(&SIS5595_dev->dev, "ACPI base address uninitialized - upgrade BIOS or use force_addr=0xaddr\n");
		वापस -ENODEV;
	पूर्ण

	अगर (क्रमce_addr)
		sis5595_base = क्रमce_addr & ~(SIS5595_EXTENT - 1);
	dev_dbg(&SIS5595_dev->dev, "ACPI Base address: %04x\n", sis5595_base);

	/* NB: We grab just the two SMBus रेजिस्टरs here, but this may still
	 * पूर्णांकerfere with ACPI :-(  */
	retval = acpi_check_region(sis5595_base + SMB_INDEX, 2,
				   sis5595_driver.name);
	अगर (retval)
		वापस retval;

	अगर (!request_region(sis5595_base + SMB_INDEX, 2,
			    sis5595_driver.name)) अणु
		dev_err(&SIS5595_dev->dev, "SMBus registers 0x%04x-0x%04x already in use!\n",
			sis5595_base + SMB_INDEX, sis5595_base + SMB_INDEX + 1);
		वापस -ENODEV;
	पूर्ण

	अगर (क्रमce_addr) अणु
		dev_info(&SIS5595_dev->dev, "forcing ISA address 0x%04X\n", sis5595_base);
		अगर (pci_ग_लिखो_config_word(SIS5595_dev, ACPI_BASE, sis5595_base)
		    != PCIBIOS_SUCCESSFUL)
			जाओ error;
		अगर (pci_पढ़ो_config_word(SIS5595_dev, ACPI_BASE, &a)
		    != PCIBIOS_SUCCESSFUL)
			जाओ error;
		अगर ((a & ~(SIS5595_EXTENT - 1)) != sis5595_base) अणु
			/* करोesn't work क्रम some chips! */
			dev_err(&SIS5595_dev->dev, "force address failed - not supported?\n");
			जाओ error;
		पूर्ण
	पूर्ण

	अगर (pci_पढ़ो_config_byte(SIS5595_dev, SIS5595_ENABLE_REG, &val)
	    != PCIBIOS_SUCCESSFUL)
		जाओ error;
	अगर ((val & 0x80) == 0) अणु
		dev_info(&SIS5595_dev->dev, "enabling ACPI\n");
		अगर (pci_ग_लिखो_config_byte(SIS5595_dev, SIS5595_ENABLE_REG, val | 0x80)
		    != PCIBIOS_SUCCESSFUL)
			जाओ error;
		अगर (pci_पढ़ो_config_byte(SIS5595_dev, SIS5595_ENABLE_REG, &val)
		    != PCIBIOS_SUCCESSFUL)
			जाओ error;
		अगर ((val & 0x80) == 0) अणु
			/* करोesn't work क्रम some chips? */
			dev_err(&SIS5595_dev->dev, "ACPI enable failed - not supported?\n");
			जाओ error;
		पूर्ण
	पूर्ण

	/* Everything is happy */
	वापस 0;

error:
	release_region(sis5595_base + SMB_INDEX, 2);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक sis5595_transaction(काष्ठा i2c_adapter *adap)
अणु
	पूर्णांक temp;
	पूर्णांक result = 0;
	पूर्णांक समयout = 0;

	/* Make sure the SMBus host is पढ़ोy to start transmitting */
	temp = sis5595_पढ़ो(SMB_STS_LO) + (sis5595_पढ़ो(SMB_STS_HI) << 8);
	अगर (temp != 0x00) अणु
		dev_dbg(&adap->dev, "SMBus busy (%04x). Resetting...\n", temp);
		sis5595_ग_लिखो(SMB_STS_LO, temp & 0xff);
		sis5595_ग_लिखो(SMB_STS_HI, temp >> 8);
		अगर ((temp = sis5595_पढ़ो(SMB_STS_LO) + (sis5595_पढ़ो(SMB_STS_HI) << 8)) != 0x00) अणु
			dev_dbg(&adap->dev, "Failed! (%02x)\n", temp);
			वापस -EBUSY;
		पूर्ण अन्यथा अणु
			dev_dbg(&adap->dev, "Successful!\n");
		पूर्ण
	पूर्ण

	/* start the transaction by setting bit 4 */
	sis5595_ग_लिखो(SMB_CTL_LO, sis5595_पढ़ो(SMB_CTL_LO) | 0x10);

	/* We will always रुको क्रम a fraction of a second! */
	करो अणु
		msleep(1);
		temp = sis5595_पढ़ो(SMB_STS_LO);
	पूर्ण जबतक (!(temp & 0x40) && (समयout++ < MAX_TIMEOUT));

	/* If the SMBus is still busy, we give up */
	अगर (समयout > MAX_TIMEOUT) अणु
		dev_dbg(&adap->dev, "SMBus Timeout!\n");
		result = -ETIMEDOUT;
	पूर्ण

	अगर (temp & 0x10) अणु
		dev_dbg(&adap->dev, "Error: Failed bus transaction\n");
		result = -ENXIO;
	पूर्ण

	अगर (temp & 0x20) अणु
		dev_err(&adap->dev, "Bus collision! SMBus may be locked until "
			"next hard reset (or not...)\n");
		/* Clock stops and slave is stuck in mid-transmission */
		result = -EIO;
	पूर्ण

	temp = sis5595_पढ़ो(SMB_STS_LO) + (sis5595_पढ़ो(SMB_STS_HI) << 8);
	अगर (temp != 0x00) अणु
		sis5595_ग_लिखो(SMB_STS_LO, temp & 0xff);
		sis5595_ग_लिखो(SMB_STS_HI, temp >> 8);
	पूर्ण

	temp = sis5595_पढ़ो(SMB_STS_LO) + (sis5595_पढ़ो(SMB_STS_HI) << 8);
	अगर (temp != 0x00)
		dev_dbg(&adap->dev, "Failed reset at end of transaction (%02x)\n", temp);

	वापस result;
पूर्ण

/* Return negative त्रुटि_सं on error. */
अटल s32 sis5595_access(काष्ठा i2c_adapter *adap, u16 addr,
			  अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
			  u8 command, पूर्णांक size, जोड़ i2c_smbus_data *data)
अणु
	पूर्णांक status;

	चयन (size) अणु
	हाल I2C_SMBUS_QUICK:
		sis5595_ग_लिखो(SMB_ADDR, ((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01));
		size = SIS5595_QUICK;
		अवरोध;
	हाल I2C_SMBUS_BYTE:
		sis5595_ग_लिखो(SMB_ADDR, ((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01));
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			sis5595_ग_लिखो(SMB_CMD, command);
		size = SIS5595_BYTE;
		अवरोध;
	हाल I2C_SMBUS_BYTE_DATA:
		sis5595_ग_लिखो(SMB_ADDR, ((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01));
		sis5595_ग_लिखो(SMB_CMD, command);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			sis5595_ग_लिखो(SMB_BYTE, data->byte);
		size = SIS5595_BYTE_DATA;
		अवरोध;
	हाल I2C_SMBUS_PROC_CALL:
	हाल I2C_SMBUS_WORD_DATA:
		sis5595_ग_लिखो(SMB_ADDR, ((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01));
		sis5595_ग_लिखो(SMB_CMD, command);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			sis5595_ग_लिखो(SMB_BYTE, data->word & 0xff);
			sis5595_ग_लिखो(SMB_BYTE + 1,
				      (data->word & 0xff00) >> 8);
		पूर्ण
		size = (size == I2C_SMBUS_PROC_CALL) ? SIS5595_PROC_CALL : SIS5595_WORD_DATA;
		अवरोध;
	शेष:
		dev_warn(&adap->dev, "Unsupported transaction %d\n", size);
		वापस -EOPNOTSUPP;
	पूर्ण

	sis5595_ग_लिखो(SMB_CTL_LO, ((size & 0x0E)));

	status = sis5595_transaction(adap);
	अगर (status)
		वापस status;

	अगर ((size != SIS5595_PROC_CALL) &&
	    ((पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) || (size == SIS5595_QUICK)))
		वापस 0;


	चयन (size) अणु
	हाल SIS5595_BYTE:
	हाल SIS5595_BYTE_DATA:
		data->byte = sis5595_पढ़ो(SMB_BYTE);
		अवरोध;
	हाल SIS5595_WORD_DATA:
	हाल SIS5595_PROC_CALL:
		data->word = sis5595_पढ़ो(SMB_BYTE) + (sis5595_पढ़ो(SMB_BYTE + 1) << 8);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल u32 sis5595_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	    I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
	    I2C_FUNC_SMBUS_PROC_CALL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm smbus_algorithm = अणु
	.smbus_xfer	= sis5595_access,
	.functionality	= sis5595_func,
पूर्ण;

अटल काष्ठा i2c_adapter sis5595_adapter = अणु
	.owner		= THIS_MODULE,
	.class          = I2C_CLASS_HWMON | I2C_CLASS_SPD,
	.algo		= &smbus_algorithm,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id sis5595_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_503) पूर्ण, 
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE (pci, sis5595_ids);

अटल पूर्णांक sis5595_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक err;

	अगर (sis5595_setup(dev)) अणु
		dev_err(&dev->dev, "SIS5595 not detected, module not inserted.\n");
		वापस -ENODEV;
	पूर्ण

	/* set up the sysfs linkage to our parent device */
	sis5595_adapter.dev.parent = &dev->dev;

	snम_लिखो(sis5595_adapter.name, माप(sis5595_adapter.name),
		 "SMBus SIS5595 adapter at %04x", sis5595_base + SMB_INDEX);
	err = i2c_add_adapter(&sis5595_adapter);
	अगर (err) अणु
		release_region(sis5595_base + SMB_INDEX, 2);
		वापस err;
	पूर्ण

	/* Always वापस failure here.  This is to allow other drivers to bind
	 * to this pci device.  We करोn't really want to have control over the
	 * pci device, we only wanted to पढ़ो as few रेजिस्टर values from it.
	 */
	sis5595_pdev =  pci_dev_get(dev);
	वापस -ENODEV;
पूर्ण

अटल काष्ठा pci_driver sis5595_driver = अणु
	.name		= "sis5595_smbus",
	.id_table	= sis5595_ids,
	.probe		= sis5595_probe,
पूर्ण;

अटल पूर्णांक __init i2c_sis5595_init(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&sis5595_driver);
पूर्ण

अटल व्योम __निकास i2c_sis5595_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&sis5595_driver);
	अगर (sis5595_pdev) अणु
		i2c_del_adapter(&sis5595_adapter);
		release_region(sis5595_base + SMB_INDEX, 2);
		pci_dev_put(sis5595_pdev);
		sis5595_pdev = शून्य;
	पूर्ण
पूर्ण

MODULE_AUTHOR("Frodo Looijaard <frodol@dds.nl>");
MODULE_DESCRIPTION("SIS5595 SMBus driver");
MODULE_LICENSE("GPL");

module_init(i2c_sis5595_init);
module_निकास(i2c_sis5595_निकास);
