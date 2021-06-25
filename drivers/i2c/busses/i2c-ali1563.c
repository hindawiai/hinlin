<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	i2c-ali1563.c - i2c driver क्रम the ALi 1563 Southbridge
 *
 *	Copyright (C) 2004 Patrick Mochel
 *		      2005 Ruकरोlf Marek <r.marek@assembler.cz>
 *
 *	The 1563 southbridge is deceptively similar to the 1533, with a
 *	few notable exceptions. One of those happens to be the fact they
 *	upgraded the i2c core to be 2.0 compliant, and happens to be almost
 *	identical to the i2c controller found in the Intel 801 south
 *	bridges.
 *
 *	This driver is based on a mix of the 15x3, 1535, and i801 drivers,
 *	with a little help from the ALi 1563 spec.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/pci.h>
#समावेश <linux/acpi.h>

#घोषणा ALI1563_MAX_TIMEOUT	500
#घोषणा	ALI1563_SMBBA		0x80
#घोषणा ALI1563_SMB_IOEN	1
#घोषणा ALI1563_SMB_HOSTEN	2
#घोषणा ALI1563_SMB_IOSIZE	16

#घोषणा SMB_HST_STS	(ali1563_smba + 0)
#घोषणा SMB_HST_CNTL1	(ali1563_smba + 1)
#घोषणा SMB_HST_CNTL2	(ali1563_smba + 2)
#घोषणा SMB_HST_CMD	(ali1563_smba + 3)
#घोषणा SMB_HST_ADD	(ali1563_smba + 4)
#घोषणा SMB_HST_DAT0	(ali1563_smba + 5)
#घोषणा SMB_HST_DAT1	(ali1563_smba + 6)
#घोषणा SMB_BLK_DAT	(ali1563_smba + 7)

#घोषणा HST_STS_BUSY	0x01
#घोषणा HST_STS_INTR	0x02
#घोषणा HST_STS_DEVERR	0x04
#घोषणा HST_STS_BUSERR	0x08
#घोषणा HST_STS_FAIL	0x10
#घोषणा HST_STS_DONE	0x80
#घोषणा HST_STS_BAD	0x1c


#घोषणा HST_CNTL1_TIMEOUT	0x80
#घोषणा HST_CNTL1_LAST		0x40

#घोषणा HST_CNTL2_KILL		0x04
#घोषणा HST_CNTL2_START		0x40
#घोषणा HST_CNTL2_QUICK		0x00
#घोषणा HST_CNTL2_BYTE		0x01
#घोषणा HST_CNTL2_BYTE_DATA	0x02
#घोषणा HST_CNTL2_WORD_DATA	0x03
#घोषणा HST_CNTL2_BLOCK		0x05


#घोषणा HST_CNTL2_SIZEMASK	0x38

अटल काष्ठा pci_driver ali1563_pci_driver;
अटल अचिन्हित लघु ali1563_smba;

अटल पूर्णांक ali1563_transaction(काष्ठा i2c_adapter *a, पूर्णांक size)
अणु
	u32 data;
	पूर्णांक समयout;
	पूर्णांक status = -EIO;

	dev_dbg(&a->dev, "Transaction (pre): STS=%02x, CNTL1=%02x, "
		"CNTL2=%02x, CMD=%02x, ADD=%02x, DAT0=%02x, DAT1=%02x\n",
		inb_p(SMB_HST_STS), inb_p(SMB_HST_CNTL1), inb_p(SMB_HST_CNTL2),
		inb_p(SMB_HST_CMD), inb_p(SMB_HST_ADD), inb_p(SMB_HST_DAT0),
		inb_p(SMB_HST_DAT1));

	data = inb_p(SMB_HST_STS);
	अगर (data & HST_STS_BAD) अणु
		dev_err(&a->dev, "ali1563: Trying to reset busy device\n");
		outb_p(data | HST_STS_BAD, SMB_HST_STS);
		data = inb_p(SMB_HST_STS);
		अगर (data & HST_STS_BAD)
			वापस -EBUSY;
	पूर्ण
	outb_p(inb_p(SMB_HST_CNTL2) | HST_CNTL2_START, SMB_HST_CNTL2);

	समयout = ALI1563_MAX_TIMEOUT;
	करो अणु
		msleep(1);
	पूर्ण जबतक (((data = inb_p(SMB_HST_STS)) & HST_STS_BUSY) && --समयout);

	dev_dbg(&a->dev, "Transaction (post): STS=%02x, CNTL1=%02x, "
		"CNTL2=%02x, CMD=%02x, ADD=%02x, DAT0=%02x, DAT1=%02x\n",
		inb_p(SMB_HST_STS), inb_p(SMB_HST_CNTL1), inb_p(SMB_HST_CNTL2),
		inb_p(SMB_HST_CMD), inb_p(SMB_HST_ADD), inb_p(SMB_HST_DAT0),
		inb_p(SMB_HST_DAT1));

	अगर (समयout && !(data & HST_STS_BAD))
		वापस 0;

	अगर (!समयout) अणु
		dev_err(&a->dev, "Timeout - Trying to KILL transaction!\n");
		/* Issue 'kill' to host controller */
		outb_p(HST_CNTL2_KILL, SMB_HST_CNTL2);
		data = inb_p(SMB_HST_STS);
		status = -ETIMEDOUT;
	पूर्ण

	/* device error - no response, ignore the स्वतःdetection हाल */
	अगर (data & HST_STS_DEVERR) अणु
		अगर (size != HST_CNTL2_QUICK)
			dev_err(&a->dev, "Device error!\n");
		status = -ENXIO;
	पूर्ण
	/* bus collision */
	अगर (data & HST_STS_BUSERR) अणु
		dev_err(&a->dev, "Bus collision!\n");
		/* Issue समयout, hoping it helps */
		outb_p(HST_CNTL1_TIMEOUT, SMB_HST_CNTL1);
	पूर्ण

	अगर (data & HST_STS_FAIL) अणु
		dev_err(&a->dev, "Cleaning fail after KILL!\n");
		outb_p(0x0, SMB_HST_CNTL2);
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक ali1563_block_start(काष्ठा i2c_adapter *a)
अणु
	u32 data;
	पूर्णांक समयout;
	पूर्णांक status = -EIO;

	dev_dbg(&a->dev, "Block (pre): STS=%02x, CNTL1=%02x, "
		"CNTL2=%02x, CMD=%02x, ADD=%02x, DAT0=%02x, DAT1=%02x\n",
		inb_p(SMB_HST_STS), inb_p(SMB_HST_CNTL1), inb_p(SMB_HST_CNTL2),
		inb_p(SMB_HST_CMD), inb_p(SMB_HST_ADD), inb_p(SMB_HST_DAT0),
		inb_p(SMB_HST_DAT1));

	data = inb_p(SMB_HST_STS);
	अगर (data & HST_STS_BAD) अणु
		dev_warn(&a->dev, "ali1563: Trying to reset busy device\n");
		outb_p(data | HST_STS_BAD, SMB_HST_STS);
		data = inb_p(SMB_HST_STS);
		अगर (data & HST_STS_BAD)
			वापस -EBUSY;
	पूर्ण

	/* Clear byte-पढ़ोy bit */
	outb_p(data | HST_STS_DONE, SMB_HST_STS);

	/* Start transaction and रुको क्रम byte-पढ़ोy bit to be set */
	outb_p(inb_p(SMB_HST_CNTL2) | HST_CNTL2_START, SMB_HST_CNTL2);

	समयout = ALI1563_MAX_TIMEOUT;
	करो अणु
		msleep(1);
	पूर्ण जबतक (!((data = inb_p(SMB_HST_STS)) & HST_STS_DONE) && --समयout);

	dev_dbg(&a->dev, "Block (post): STS=%02x, CNTL1=%02x, "
		"CNTL2=%02x, CMD=%02x, ADD=%02x, DAT0=%02x, DAT1=%02x\n",
		inb_p(SMB_HST_STS), inb_p(SMB_HST_CNTL1), inb_p(SMB_HST_CNTL2),
		inb_p(SMB_HST_CMD), inb_p(SMB_HST_ADD), inb_p(SMB_HST_DAT0),
		inb_p(SMB_HST_DAT1));

	अगर (समयout && !(data & HST_STS_BAD))
		वापस 0;

	अगर (समयout == 0)
		status = -ETIMEDOUT;

	अगर (data & HST_STS_DEVERR)
		status = -ENXIO;

	dev_err(&a->dev, "SMBus Error: %s%s%s%s%s\n",
		समयout ? "" : "Timeout ",
		data & HST_STS_FAIL ? "Transaction Failed " : "",
		data & HST_STS_BUSERR ? "No response or Bus Collision " : "",
		data & HST_STS_DEVERR ? "Device Error " : "",
		!(data & HST_STS_DONE) ? "Transaction Never Finished " : "");
	वापस status;
पूर्ण

अटल पूर्णांक ali1563_block(काष्ठा i2c_adapter *a,
			 जोड़ i2c_smbus_data *data, u8 rw)
अणु
	पूर्णांक i, len;
	पूर्णांक error = 0;

	/* Do we need this? */
	outb_p(HST_CNTL1_LAST, SMB_HST_CNTL1);

	अगर (rw == I2C_SMBUS_WRITE) अणु
		len = data->block[0];
		अगर (len < 1)
			len = 1;
		अन्यथा अगर (len > 32)
			len = 32;
		outb_p(len, SMB_HST_DAT0);
		outb_p(data->block[1], SMB_BLK_DAT);
	पूर्ण अन्यथा
		len = 32;

	outb_p(inb_p(SMB_HST_CNTL2) | HST_CNTL2_BLOCK, SMB_HST_CNTL2);

	क्रम (i = 0; i < len; i++) अणु
		अगर (rw == I2C_SMBUS_WRITE) अणु
			outb_p(data->block[i + 1], SMB_BLK_DAT);
			error = ali1563_block_start(a);
			अगर (error)
				अवरोध;
		पूर्ण अन्यथा अणु
			error = ali1563_block_start(a);
			अगर (error)
				अवरोध;
			अगर (i == 0) अणु
				len = inb_p(SMB_HST_DAT0);
				अगर (len < 1)
					len = 1;
				अन्यथा अगर (len > 32)
					len = 32;
			पूर्ण
			data->block[i+1] = inb_p(SMB_BLK_DAT);
		पूर्ण
	पूर्ण
	/* Do we need this? */
	outb_p(HST_CNTL1_LAST, SMB_HST_CNTL1);
	वापस error;
पूर्ण

अटल s32 ali1563_access(काष्ठा i2c_adapter *a, u16 addr,
			  अचिन्हित लघु flags, अक्षर rw, u8 cmd,
			  पूर्णांक size, जोड़ i2c_smbus_data *data)
अणु
	पूर्णांक error = 0;
	पूर्णांक समयout;
	u32 reg;

	क्रम (समयout = ALI1563_MAX_TIMEOUT; समयout; समयout--) अणु
		reg = inb_p(SMB_HST_STS);
		अगर (!(reg & HST_STS_BUSY))
			अवरोध;
	पूर्ण
	अगर (!समयout)
		dev_warn(&a->dev, "SMBus not idle. HST_STS = %02x\n", reg);
	outb_p(0xff, SMB_HST_STS);

	/* Map the size to what the chip understands */
	चयन (size) अणु
	हाल I2C_SMBUS_QUICK:
		size = HST_CNTL2_QUICK;
		अवरोध;
	हाल I2C_SMBUS_BYTE:
		size = HST_CNTL2_BYTE;
		अवरोध;
	हाल I2C_SMBUS_BYTE_DATA:
		size = HST_CNTL2_BYTE_DATA;
		अवरोध;
	हाल I2C_SMBUS_WORD_DATA:
		size = HST_CNTL2_WORD_DATA;
		अवरोध;
	हाल I2C_SMBUS_BLOCK_DATA:
		size = HST_CNTL2_BLOCK;
		अवरोध;
	शेष:
		dev_warn(&a->dev, "Unsupported transaction %d\n", size);
		error = -EOPNOTSUPP;
		जाओ Done;
	पूर्ण

	outb_p(((addr & 0x7f) << 1) | (rw & 0x01), SMB_HST_ADD);
	outb_p((inb_p(SMB_HST_CNTL2) & ~HST_CNTL2_SIZEMASK) |
	       (size << 3), SMB_HST_CNTL2);

	/* Write the command रेजिस्टर */

	चयन (size) अणु
	हाल HST_CNTL2_BYTE:
		अगर (rw == I2C_SMBUS_WRITE)
			/* Beware it uses DAT0 रेजिस्टर and not CMD! */
			outb_p(cmd, SMB_HST_DAT0);
		अवरोध;
	हाल HST_CNTL2_BYTE_DATA:
		outb_p(cmd, SMB_HST_CMD);
		अगर (rw == I2C_SMBUS_WRITE)
			outb_p(data->byte, SMB_HST_DAT0);
		अवरोध;
	हाल HST_CNTL2_WORD_DATA:
		outb_p(cmd, SMB_HST_CMD);
		अगर (rw == I2C_SMBUS_WRITE) अणु
			outb_p(data->word & 0xff, SMB_HST_DAT0);
			outb_p((data->word & 0xff00) >> 8, SMB_HST_DAT1);
		पूर्ण
		अवरोध;
	हाल HST_CNTL2_BLOCK:
		outb_p(cmd, SMB_HST_CMD);
		error = ali1563_block(a, data, rw);
		जाओ Done;
	पूर्ण

	error = ali1563_transaction(a, size);
	अगर (error)
		जाओ Done;

	अगर ((rw == I2C_SMBUS_WRITE) || (size == HST_CNTL2_QUICK))
		जाओ Done;

	चयन (size) अणु
	हाल HST_CNTL2_BYTE:	/* Result put in SMBHSTDAT0 */
		data->byte = inb_p(SMB_HST_DAT0);
		अवरोध;
	हाल HST_CNTL2_BYTE_DATA:
		data->byte = inb_p(SMB_HST_DAT0);
		अवरोध;
	हाल HST_CNTL2_WORD_DATA:
		data->word = inb_p(SMB_HST_DAT0) + (inb_p(SMB_HST_DAT1) << 8);
		अवरोध;
	पूर्ण
Done:
	वापस error;
पूर्ण

अटल u32 ali1563_func(काष्ठा i2c_adapter *a)
अणु
	वापस I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	    I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
	    I2C_FUNC_SMBUS_BLOCK_DATA;
पूर्ण


अटल पूर्णांक ali1563_setup(काष्ठा pci_dev *dev)
अणु
	u16 ctrl;

	pci_पढ़ो_config_word(dev, ALI1563_SMBBA, &ctrl);

	/* SMB I/O Base in high 12 bits and must be aligned with the
	 * size of the I/O space. */
	ali1563_smba = ctrl & ~(ALI1563_SMB_IOSIZE - 1);
	अगर (!ali1563_smba) अणु
		dev_warn(&dev->dev, "ali1563_smba Uninitialized\n");
		जाओ Err;
	पूर्ण

	/* Check अगर device is enabled */
	अगर (!(ctrl & ALI1563_SMB_HOSTEN)) अणु
		dev_warn(&dev->dev, "Host Controller not enabled\n");
		जाओ Err;
	पूर्ण
	अगर (!(ctrl & ALI1563_SMB_IOEN)) अणु
		dev_warn(&dev->dev, "I/O space not enabled, trying manually\n");
		pci_ग_लिखो_config_word(dev, ALI1563_SMBBA,
				      ctrl | ALI1563_SMB_IOEN);
		pci_पढ़ो_config_word(dev, ALI1563_SMBBA, &ctrl);
		अगर (!(ctrl & ALI1563_SMB_IOEN)) अणु
			dev_err(&dev->dev,
				"I/O space still not enabled, giving up\n");
			जाओ Err;
		पूर्ण
	पूर्ण

	अगर (acpi_check_region(ali1563_smba, ALI1563_SMB_IOSIZE,
			      ali1563_pci_driver.name))
		जाओ Err;

	अगर (!request_region(ali1563_smba, ALI1563_SMB_IOSIZE,
			    ali1563_pci_driver.name)) अणु
		dev_err(&dev->dev, "Could not allocate I/O space at 0x%04x\n",
			ali1563_smba);
		जाओ Err;
	पूर्ण
	dev_info(&dev->dev, "Found ALi1563 SMBus at 0x%04x\n", ali1563_smba);

	वापस 0;
Err:
	वापस -ENODEV;
पूर्ण

अटल व्योम ali1563_shutकरोwn(काष्ठा pci_dev *dev)
अणु
	release_region(ali1563_smba, ALI1563_SMB_IOSIZE);
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm ali1563_algorithm = अणु
	.smbus_xfer	= ali1563_access,
	.functionality	= ali1563_func,
पूर्ण;

अटल काष्ठा i2c_adapter ali1563_adapter = अणु
	.owner	= THIS_MODULE,
	.class	= I2C_CLASS_HWMON | I2C_CLASS_SPD,
	.algo	= &ali1563_algorithm,
पूर्ण;

अटल पूर्णांक ali1563_probe(काष्ठा pci_dev *dev,
			 स्थिर काष्ठा pci_device_id *id_table)
अणु
	पूर्णांक error;

	error = ali1563_setup(dev);
	अगर (error)
		जाओ निकास;
	ali1563_adapter.dev.parent = &dev->dev;
	snम_लिखो(ali1563_adapter.name, माप(ali1563_adapter.name),
		 "SMBus ALi 1563 Adapter @ %04x", ali1563_smba);
	error = i2c_add_adapter(&ali1563_adapter);
	अगर (error)
		जाओ निकास_shutकरोwn;
	वापस 0;

निकास_shutकरोwn:
	ali1563_shutकरोwn(dev);
निकास:
	dev_warn(&dev->dev, "ALi1563 SMBus probe failed (%d)\n", error);
	वापस error;
पूर्ण

अटल व्योम ali1563_हटाओ(काष्ठा pci_dev *dev)
अणु
	i2c_del_adapter(&ali1563_adapter);
	ali1563_shutकरोwn(dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id ali1563_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_AL, PCI_DEVICE_ID_AL_M1563) पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, ali1563_id_table);

अटल काष्ठा pci_driver ali1563_pci_driver = अणु
	.name		= "ali1563_smbus",
	.id_table	= ali1563_id_table,
	.probe		= ali1563_probe,
	.हटाओ		= ali1563_हटाओ,
पूर्ण;

module_pci_driver(ali1563_pci_driver);

MODULE_LICENSE("GPL");
