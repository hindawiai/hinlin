<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Copyright (c) 2003 Mark M. Hoffman <mhoffman@lightlink.com>

*/

/*
    This module must be considered BETA unless and until
    the chipset manufacturer releases a datasheet.
    The रेजिस्टर definitions are based on the SiS630.

    This module relies on quirk_sis_96x_smbus (drivers/pci/quirks.c)
    क्रम just about every machine क्रम which users have reported.
    If this module isn't detecting your 96x south bridge, have a 
    look there.

    We assume there can only be one SiS96x with one SMBus पूर्णांकerface.
*/

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/ioport.h>
#समावेश <linux/i2c.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>

/* base address रेजिस्टर in PCI config space */
#घोषणा SIS96x_BAR 0x04

/* SiS96x SMBus रेजिस्टरs */
#घोषणा SMB_STS      0x00
#घोषणा SMB_EN       0x01
#घोषणा SMB_CNT      0x02
#घोषणा SMB_HOST_CNT 0x03
#घोषणा SMB_ADDR     0x04
#घोषणा SMB_CMD      0x05
#घोषणा SMB_PCOUNT   0x06
#घोषणा SMB_COUNT    0x07
#घोषणा SMB_BYTE     0x08
#घोषणा SMB_DEV_ADDR 0x10
#घोषणा SMB_DB0      0x11
#घोषणा SMB_DB1      0x12
#घोषणा SMB_SAA      0x13

/* रेजिस्टर count क्रम request_region */
#घोषणा SMB_IOSIZE 0x20

/* Other settings */
#घोषणा MAX_TIMEOUT 500

/* SiS96x SMBus स्थिरants */
#घोषणा SIS96x_QUICK      0x00
#घोषणा SIS96x_BYTE       0x01
#घोषणा SIS96x_BYTE_DATA  0x02
#घोषणा SIS96x_WORD_DATA  0x03
#घोषणा SIS96x_PROC_CALL  0x04
#घोषणा SIS96x_BLOCK_DATA 0x05

अटल काष्ठा pci_driver sis96x_driver;
अटल काष्ठा i2c_adapter sis96x_adapter;
अटल u16 sis96x_smbus_base;

अटल अंतरभूत u8 sis96x_पढ़ो(u8 reg)
अणु
	वापस inb(sis96x_smbus_base + reg) ;
पूर्ण

अटल अंतरभूत व्योम sis96x_ग_लिखो(u8 reg, u8 data)
अणु
	outb(data, sis96x_smbus_base + reg) ;
पूर्ण

/* Execute a SMBus transaction.
   पूर्णांक size is from SIS96x_QUICK to SIS96x_BLOCK_DATA
 */
अटल पूर्णांक sis96x_transaction(पूर्णांक size)
अणु
	पूर्णांक temp;
	पूर्णांक result = 0;
	पूर्णांक समयout = 0;

	dev_dbg(&sis96x_adapter.dev, "SMBus transaction %d\n", size);

	/* Make sure the SMBus host is पढ़ोy to start transmitting */
	अगर (((temp = sis96x_पढ़ो(SMB_CNT)) & 0x03) != 0x00) अणु

		dev_dbg(&sis96x_adapter.dev, "SMBus busy (0x%02x). "
			"Resetting...\n", temp);

		/* समाप्त the transaction */
		sis96x_ग_लिखो(SMB_HOST_CNT, 0x20);

		/* check it again */
		अगर (((temp = sis96x_पढ़ो(SMB_CNT)) & 0x03) != 0x00) अणु
			dev_dbg(&sis96x_adapter.dev, "Failed (0x%02x)\n", temp);
			वापस -EBUSY;
		पूर्ण अन्यथा अणु
			dev_dbg(&sis96x_adapter.dev, "Successful\n");
		पूर्ण
	पूर्ण

	/* Turn off समयout पूर्णांकerrupts, set fast host घड़ी */
	sis96x_ग_लिखो(SMB_CNT, 0x20);

	/* clear all (sticky) status flags */
	temp = sis96x_पढ़ो(SMB_STS);
	sis96x_ग_लिखो(SMB_STS, temp & 0x1e);

	/* start the transaction by setting bit 4 and size bits */
	sis96x_ग_लिखो(SMB_HOST_CNT, 0x10 | (size & 0x07));

	/* We will always रुको क्रम a fraction of a second! */
	करो अणु
		msleep(1);
		temp = sis96x_पढ़ो(SMB_STS);
	पूर्ण जबतक (!(temp & 0x0e) && (समयout++ < MAX_TIMEOUT));

	/* If the SMBus is still busy, we give up */
	अगर (समयout > MAX_TIMEOUT) अणु
		dev_dbg(&sis96x_adapter.dev, "SMBus Timeout! (0x%02x)\n", temp);
		result = -ETIMEDOUT;
	पूर्ण

	/* device error - probably missing ACK */
	अगर (temp & 0x02) अणु
		dev_dbg(&sis96x_adapter.dev, "Failed bus transaction!\n");
		result = -ENXIO;
	पूर्ण

	/* bus collision */
	अगर (temp & 0x04) अणु
		dev_dbg(&sis96x_adapter.dev, "Bus collision!\n");
		result = -EIO;
	पूर्ण

	/* Finish up by resetting the bus */
	sis96x_ग_लिखो(SMB_STS, temp);
	अगर ((temp = sis96x_पढ़ो(SMB_STS))) अणु
		dev_dbg(&sis96x_adapter.dev, "Failed reset at "
			"end of transaction! (0x%02x)\n", temp);
	पूर्ण

	वापस result;
पूर्ण

/* Return negative त्रुटि_सं on error. */
अटल s32 sis96x_access(काष्ठा i2c_adapter * adap, u16 addr,
			 अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
			 u8 command, पूर्णांक size, जोड़ i2c_smbus_data * data)
अणु
	पूर्णांक status;

	चयन (size) अणु
	हाल I2C_SMBUS_QUICK:
		sis96x_ग_लिखो(SMB_ADDR, ((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01));
		size = SIS96x_QUICK;
		अवरोध;

	हाल I2C_SMBUS_BYTE:
		sis96x_ग_लिखो(SMB_ADDR, ((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01));
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			sis96x_ग_लिखो(SMB_CMD, command);
		size = SIS96x_BYTE;
		अवरोध;

	हाल I2C_SMBUS_BYTE_DATA:
		sis96x_ग_लिखो(SMB_ADDR, ((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01));
		sis96x_ग_लिखो(SMB_CMD, command);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			sis96x_ग_लिखो(SMB_BYTE, data->byte);
		size = SIS96x_BYTE_DATA;
		अवरोध;

	हाल I2C_SMBUS_PROC_CALL:
	हाल I2C_SMBUS_WORD_DATA:
		sis96x_ग_लिखो(SMB_ADDR, ((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01));
		sis96x_ग_लिखो(SMB_CMD, command);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			sis96x_ग_लिखो(SMB_BYTE, data->word & 0xff);
			sis96x_ग_लिखो(SMB_BYTE + 1, (data->word & 0xff00) >> 8);
		पूर्ण
		size = (size == I2C_SMBUS_PROC_CALL ? 
			SIS96x_PROC_CALL : SIS96x_WORD_DATA);
		अवरोध;

	शेष:
		dev_warn(&adap->dev, "Unsupported transaction %d\n", size);
		वापस -EOPNOTSUPP;
	पूर्ण

	status = sis96x_transaction(size);
	अगर (status)
		वापस status;

	अगर ((size != SIS96x_PROC_CALL) &&
		((पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) || (size == SIS96x_QUICK)))
		वापस 0;

	चयन (size) अणु
	हाल SIS96x_BYTE:
	हाल SIS96x_BYTE_DATA:
		data->byte = sis96x_पढ़ो(SMB_BYTE);
		अवरोध;

	हाल SIS96x_WORD_DATA:
	हाल SIS96x_PROC_CALL:
		data->word = sis96x_पढ़ो(SMB_BYTE) +
				(sis96x_पढ़ो(SMB_BYTE + 1) << 8);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल u32 sis96x_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	    I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
	    I2C_FUNC_SMBUS_PROC_CALL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm smbus_algorithm = अणु
	.smbus_xfer	= sis96x_access,
	.functionality	= sis96x_func,
पूर्ण;

अटल काष्ठा i2c_adapter sis96x_adapter = अणु
	.owner		= THIS_MODULE,
	.class		= I2C_CLASS_HWMON | I2C_CLASS_SPD,
	.algo		= &smbus_algorithm,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id sis96x_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_SMBUS) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE (pci, sis96x_ids);

अटल पूर्णांक sis96x_probe(काष्ठा pci_dev *dev,
				स्थिर काष्ठा pci_device_id *id)
अणु
	u16 ww = 0;
	पूर्णांक retval;

	अगर (sis96x_smbus_base) अणु
		dev_err(&dev->dev, "Only one device supported.\n");
		वापस -EBUSY;
	पूर्ण

	pci_पढ़ो_config_word(dev, PCI_CLASS_DEVICE, &ww);
	अगर (PCI_CLASS_SERIAL_SMBUS != ww) अणु
		dev_err(&dev->dev, "Unsupported device class 0x%04x!\n", ww);
		वापस -ENODEV;
	पूर्ण

	sis96x_smbus_base = pci_resource_start(dev, SIS96x_BAR);
	अगर (!sis96x_smbus_base) अणु
		dev_err(&dev->dev, "SiS96x SMBus base address "
			"not initialized!\n");
		वापस -EINVAL;
	पूर्ण
	dev_info(&dev->dev, "SiS96x SMBus base address: 0x%04x\n",
			sis96x_smbus_base);

	retval = acpi_check_resource_conflict(&dev->resource[SIS96x_BAR]);
	अगर (retval)
		वापस -ENODEV;

	/* Everything is happy, let's grab the memory and set things up. */
	अगर (!request_region(sis96x_smbus_base, SMB_IOSIZE,
			    sis96x_driver.name)) अणु
		dev_err(&dev->dev, "SMBus registers 0x%04x-0x%04x "
			"already in use!\n", sis96x_smbus_base,
			sis96x_smbus_base + SMB_IOSIZE - 1);

		sis96x_smbus_base = 0;
		वापस -EINVAL;
	पूर्ण

	/* set up the sysfs linkage to our parent device */
	sis96x_adapter.dev.parent = &dev->dev;

	snम_लिखो(sis96x_adapter.name, माप(sis96x_adapter.name),
		"SiS96x SMBus adapter at 0x%04x", sis96x_smbus_base);

	अगर ((retval = i2c_add_adapter(&sis96x_adapter))) अणु
		dev_err(&dev->dev, "Couldn't register adapter!\n");
		release_region(sis96x_smbus_base, SMB_IOSIZE);
		sis96x_smbus_base = 0;
	पूर्ण

	वापस retval;
पूर्ण

अटल व्योम sis96x_हटाओ(काष्ठा pci_dev *dev)
अणु
	अगर (sis96x_smbus_base) अणु
		i2c_del_adapter(&sis96x_adapter);
		release_region(sis96x_smbus_base, SMB_IOSIZE);
		sis96x_smbus_base = 0;
	पूर्ण
पूर्ण

अटल काष्ठा pci_driver sis96x_driver = अणु
	.name		= "sis96x_smbus",
	.id_table	= sis96x_ids,
	.probe		= sis96x_probe,
	.हटाओ		= sis96x_हटाओ,
पूर्ण;

module_pci_driver(sis96x_driver);

MODULE_AUTHOR("Mark M. Hoffman <mhoffman@lightlink.com>");
MODULE_DESCRIPTION("SiS96x SMBus driver");
MODULE_LICENSE("GPL");
