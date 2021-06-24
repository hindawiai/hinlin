<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2000  Froकरो Looijaard <froकरोl@dds.nl>,
 *                      Philip Edelbrock <phil@netroedge.com>,
 *                      Mark D. Studebaker <mdsxyz123@yahoo.com>,
 *                      Dan Eaton <dan.eaton@rocketlogix.com> and
 *                      Stephen Rousset <stephen.rousset@rocketlogix.com>
*/

/*
    This is the driver क्रम the SMB Host controller on
    Acer Lअसल Inc. (ALI) M1535 South Bridge.

    The M1535 is a South bridge क्रम portable प्रणालीs.
    It is very similar to the M15x3 South bridges also produced
    by Acer Lअसल Inc.  Some of the रेजिस्टरs within the part
    have moved and some have been redefined slightly. Additionally,
    the sequencing of the SMBus transactions has been modअगरied
    to be more consistent with the sequencing recommended by
    the manufacturer and observed through testing.  These
    changes are reflected in this driver and can be identअगरied
    by comparing this driver to the i2c-ali15x3 driver.
    For an overview of these chips see http://www.acerद_असल.com

    The SMB controller is part of the 7101 device, which is an
    ACPI-compliant Power Management Unit (PMU).

    The whole 7101 device has to be enabled क्रम the SMB to work.
    You can't just enable the SMB alone.
    The SMB and the ACPI have separate I/O spaces.
    We make sure that the SMB is enabled. We leave the ACPI alone.

    This driver controls the SMB Host only.

    This driver करोes not use पूर्णांकerrupts.
*/


/* Note: we assume there can only be one ALI1535, with one SMBus पूर्णांकerface */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/i2c.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>


/* ALI1535 SMBus address offsets */
#घोषणा SMBHSTSTS	(0 + ali1535_smba)
#घोषणा SMBHSTTYP	(1 + ali1535_smba)
#घोषणा SMBHSTPORT	(2 + ali1535_smba)
#घोषणा SMBHSTCMD	(7 + ali1535_smba)
#घोषणा SMBHSTADD	(3 + ali1535_smba)
#घोषणा SMBHSTDAT0	(4 + ali1535_smba)
#घोषणा SMBHSTDAT1	(5 + ali1535_smba)
#घोषणा SMBBLKDAT	(6 + ali1535_smba)

/* PCI Address Constants */
#घोषणा SMBCOM		0x004
#घोषणा SMBREV		0x008
#घोषणा SMBCFG		0x0D1
#घोषणा SMBBA		0x0E2
#घोषणा SMBHSTCFG	0x0F0
#घोषणा SMBCLK		0x0F2

/* Other settings */
#घोषणा MAX_TIMEOUT		500	/* बार 1/100 sec */
#घोषणा ALI1535_SMB_IOSIZE	32

#घोषणा ALI1535_SMB_DEFAULTBASE	0x8040

/* ALI1535 address lock bits */
#घोषणा ALI1535_LOCK		0x06	/* dwe */

/* ALI1535 command स्थिरants */
#घोषणा ALI1535_QUICK		0x00
#घोषणा ALI1535_BYTE		0x10
#घोषणा ALI1535_BYTE_DATA	0x20
#घोषणा ALI1535_WORD_DATA	0x30
#घोषणा ALI1535_BLOCK_DATA	0x40
#घोषणा ALI1535_I2C_READ	0x60

#घोषणा	ALI1535_DEV10B_EN	0x80	/* Enable 10-bit addressing in	*/
					/*  I2C पढ़ो			*/
#घोषणा	ALI1535_T_OUT		0x08	/* Time-out Command (ग_लिखो)	*/
#घोषणा	ALI1535_A_HIGH_BIT9	0x08	/* Bit 9 of 10-bit address in	*/
					/* Alert-Response-Address	*/
					/* (पढ़ो)			*/
#घोषणा	ALI1535_KILL		0x04	/* Kill Command (ग_लिखो)		*/
#घोषणा	ALI1535_A_HIGH_BIT8	0x04	/* Bit 8 of 10-bit address in	*/
					/*  Alert-Response-Address	*/
					/*  (पढ़ो)			*/

#घोषणा	ALI1535_D_HI_MASK	0x03	/* Mask क्रम isolating bits 9-8	*/
					/*  of 10-bit address in I2C	*/
					/*  Read Command		*/

/* ALI1535 status रेजिस्टर bits */
#घोषणा ALI1535_STS_IDLE	0x04
#घोषणा ALI1535_STS_BUSY	0x08	/* host busy */
#घोषणा ALI1535_STS_DONE	0x10	/* transaction complete */
#घोषणा ALI1535_STS_DEV		0x20	/* device error */
#घोषणा ALI1535_STS_BUSERR	0x40	/* bus error    */
#घोषणा ALI1535_STS_FAIL	0x80	/* failed bus transaction */
#घोषणा ALI1535_STS_ERR		0xE0	/* all the bad error bits */

#घोषणा ALI1535_BLOCK_CLR	0x04	/* reset block data index */

/* ALI1535 device address रेजिस्टर bits */
#घोषणा	ALI1535_RD_ADDR		0x01	/* Read/Write Bit in Device	*/
					/*  Address field		*/
					/*  -> Write = 0		*/
					/*  -> Read  = 1		*/
#घोषणा	ALI1535_SMBIO_EN	0x04	/* SMB I/O Space enable		*/

अटल काष्ठा pci_driver ali1535_driver;
अटल अचिन्हित दीर्घ ali1535_smba;
अटल अचिन्हित लघु ali1535_offset;

/* Detect whether a ALI1535 can be found, and initialize it, where necessary.
   Note the dअगरferences between kernels with the old PCI BIOS पूर्णांकerface and
   newer kernels with the real PCI पूर्णांकerface. In compat.h some things are
   defined to make the transition easier. */
अटल पूर्णांक ali1535_setup(काष्ठा pci_dev *dev)
अणु
	पूर्णांक retval;
	अचिन्हित अक्षर temp;

	/* Check the following things:
		- SMB I/O address is initialized
		- Device is enabled
		- We can use the addresses
	*/

	retval = pci_enable_device(dev);
	अगर (retval) अणु
		dev_err(&dev->dev, "ALI1535_smb can't enable device\n");
		जाओ निकास;
	पूर्ण

	/* Determine the address of the SMBus area */
	pci_पढ़ो_config_word(dev, SMBBA, &ali1535_offset);
	dev_dbg(&dev->dev, "ALI1535_smb is at offset 0x%04x\n", ali1535_offset);
	ali1535_offset &= (0xffff & ~(ALI1535_SMB_IOSIZE - 1));
	अगर (ali1535_offset == 0) अणु
		dev_warn(&dev->dev,
			"ALI1535_smb region uninitialized - upgrade BIOS?\n");
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण

	अगर (pci_resource_flags(dev, 0) & IORESOURCE_IO)
		ali1535_smba = pci_resource_start(dev, 0) + ali1535_offset;
	अन्यथा
		ali1535_smba = ali1535_offset;

	retval = acpi_check_region(ali1535_smba, ALI1535_SMB_IOSIZE,
				   ali1535_driver.name);
	अगर (retval)
		जाओ निकास;

	अगर (!request_region(ali1535_smba, ALI1535_SMB_IOSIZE,
			    ali1535_driver.name)) अणु
		dev_err(&dev->dev, "ALI1535_smb region 0x%lx already in use!\n",
			ali1535_smba);
		retval = -EBUSY;
		जाओ निकास;
	पूर्ण

	/* check अगर whole device is enabled */
	pci_पढ़ो_config_byte(dev, SMBCFG, &temp);
	अगर ((temp & ALI1535_SMBIO_EN) == 0) अणु
		dev_err(&dev->dev, "SMB device not enabled - upgrade BIOS?\n");
		retval = -ENODEV;
		जाओ निकास_मुक्त;
	पूर्ण

	/* Is SMB Host controller enabled? */
	pci_पढ़ो_config_byte(dev, SMBHSTCFG, &temp);
	अगर ((temp & 1) == 0) अणु
		dev_err(&dev->dev, "SMBus controller not enabled - upgrade BIOS?\n");
		retval = -ENODEV;
		जाओ निकास_मुक्त;
	पूर्ण

	/* set SMB घड़ी to 74KHz as recommended in data sheet */
	pci_ग_लिखो_config_byte(dev, SMBCLK, 0x20);

	/*
	  The पूर्णांकerrupt routing क्रम SMB is set up in रेजिस्टर 0x77 in the
	  1533 ISA Bridge device, NOT in the 7101 device.
	  Don't bother with finding the 1533 device and पढ़ोing the रेजिस्टर.
	अगर ((....... & 0x0F) == 1)
		dev_dbg(&dev->dev, "ALI1535 using Interrupt 9 for SMBus.\n");
	*/
	pci_पढ़ो_config_byte(dev, SMBREV, &temp);
	dev_dbg(&dev->dev, "SMBREV = 0x%X\n", temp);
	dev_dbg(&dev->dev, "ALI1535_smba = 0x%lx\n", ali1535_smba);

	वापस 0;

निकास_मुक्त:
	release_region(ali1535_smba, ALI1535_SMB_IOSIZE);
निकास:
	वापस retval;
पूर्ण

अटल पूर्णांक ali1535_transaction(काष्ठा i2c_adapter *adap)
अणु
	पूर्णांक temp;
	पूर्णांक result = 0;
	पूर्णांक समयout = 0;

	dev_dbg(&adap->dev, "Transaction (pre): STS=%02x, TYP=%02x, "
		"CMD=%02x, ADD=%02x, DAT0=%02x, DAT1=%02x\n",
		inb_p(SMBHSTSTS), inb_p(SMBHSTTYP), inb_p(SMBHSTCMD),
		inb_p(SMBHSTADD), inb_p(SMBHSTDAT0), inb_p(SMBHSTDAT1));

	/* get status */
	temp = inb_p(SMBHSTSTS);

	/* Make sure the SMBus host is पढ़ोy to start transmitting */
	/* Check the busy bit first */
	अगर (temp & ALI1535_STS_BUSY) अणु
		/* If the host controller is still busy, it may have समयd out
		 * in the previous transaction, resulting in a "SMBus Timeout"
		 * prपूर्णांकk.  I've tried the following to reset a stuck busy bit.
		 *   1. Reset the controller with an KILL command. (this
		 *      करोesn't seem to clear the controller अगर an बाह्यal
		 *      device is hung)
		 *   2. Reset the controller and the other SMBus devices with a
		 *      T_OUT command. (this clears the host busy bit अगर an
		 *      बाह्यal device is hung, but it comes back upon a new
		 *      access to a device)
		 *   3. Disable and reenable the controller in SMBHSTCFG. Worst
		 *      हाल, nothing seems to work except घातer reset.
		 */

		/* Try resetting entire SMB bus, including other devices - This
		 * may not work either - it clears the BUSY bit but then the
		 * BUSY bit may come back on when you try and use the chip
		 * again.  If that's the हाल you are stuck.
		 */
		dev_info(&adap->dev,
			"Resetting entire SMB Bus to clear busy condition (%02x)\n",
			temp);
		outb_p(ALI1535_T_OUT, SMBHSTTYP);
		temp = inb_p(SMBHSTSTS);
	पूर्ण

	/* now check the error bits and the busy bit */
	अगर (temp & (ALI1535_STS_ERR | ALI1535_STS_BUSY)) अणु
		/* करो a clear-on-ग_लिखो */
		outb_p(0xFF, SMBHSTSTS);
		temp = inb_p(SMBHSTSTS);
		अगर (temp & (ALI1535_STS_ERR | ALI1535_STS_BUSY)) अणु
			/* This is probably going to be correctable only by a
			 * घातer reset as one of the bits now appears to be
			 * stuck */
			/* This may be a bus or device with electrical problems. */
			dev_err(&adap->dev,
				"SMBus reset failed! (0x%02x) - controller or "
				"device on bus is probably hung\n", temp);
			वापस -EBUSY;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* check and clear करोne bit */
		अगर (temp & ALI1535_STS_DONE)
			outb_p(temp, SMBHSTSTS);
	पूर्ण

	/* start the transaction by writing anything to the start रेजिस्टर */
	outb_p(0xFF, SMBHSTPORT);

	/* We will always रुको क्रम a fraction of a second! */
	समयout = 0;
	करो अणु
		usleep_range(1000, 2000);
		temp = inb_p(SMBHSTSTS);
	पूर्ण जबतक (((temp & ALI1535_STS_BUSY) && !(temp & ALI1535_STS_IDLE))
		 && (समयout++ < MAX_TIMEOUT));

	/* If the SMBus is still busy, we give up */
	अगर (समयout > MAX_TIMEOUT) अणु
		result = -ETIMEDOUT;
		dev_err(&adap->dev, "SMBus Timeout!\n");
	पूर्ण

	अगर (temp & ALI1535_STS_FAIL) अणु
		result = -EIO;
		dev_dbg(&adap->dev, "Error: Failed bus transaction\n");
	पूर्ण

	/* Unक्रमtunately the ALI SMB controller maps "no response" and "bus
	 * collision" पूर्णांकo a single bit. No response is the usual हाल so करोn't
	 * करो a prपूर्णांकk.  This means that bus collisions go unreported.
	 */
	अगर (temp & ALI1535_STS_BUSERR) अणु
		result = -ENXIO;
		dev_dbg(&adap->dev,
			"Error: no response or bus collision ADD=%02x\n",
			inb_p(SMBHSTADD));
	पूर्ण

	/* haven't ever seen this */
	अगर (temp & ALI1535_STS_DEV) अणु
		result = -EIO;
		dev_err(&adap->dev, "Error: device error\n");
	पूर्ण

	/* check to see अगर the "command complete" indication is set */
	अगर (!(temp & ALI1535_STS_DONE)) अणु
		result = -ETIMEDOUT;
		dev_err(&adap->dev, "Error: command never completed\n");
	पूर्ण

	dev_dbg(&adap->dev, "Transaction (post): STS=%02x, TYP=%02x, "
		"CMD=%02x, ADD=%02x, DAT0=%02x, DAT1=%02x\n",
		inb_p(SMBHSTSTS), inb_p(SMBHSTTYP), inb_p(SMBHSTCMD),
		inb_p(SMBHSTADD), inb_p(SMBHSTDAT0), inb_p(SMBHSTDAT1));

	/* take consequent actions क्रम error conditions */
	अगर (!(temp & ALI1535_STS_DONE)) अणु
		/* issue "kill" to reset host controller */
		outb_p(ALI1535_KILL, SMBHSTTYP);
		outb_p(0xFF, SMBHSTSTS);
	पूर्ण अन्यथा अगर (temp & ALI1535_STS_ERR) अणु
		/* issue "timeout" to reset all devices on bus */
		outb_p(ALI1535_T_OUT, SMBHSTTYP);
		outb_p(0xFF, SMBHSTSTS);
	पूर्ण

	वापस result;
पूर्ण

/* Return negative त्रुटि_सं on error. */
अटल s32 ali1535_access(काष्ठा i2c_adapter *adap, u16 addr,
			  अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो, u8 command,
			  पूर्णांक size, जोड़ i2c_smbus_data *data)
अणु
	पूर्णांक i, len;
	पूर्णांक temp;
	पूर्णांक समयout;
	s32 result = 0;

	/* make sure SMBus is idle */
	temp = inb_p(SMBHSTSTS);
	क्रम (समयout = 0;
	     (समयout < MAX_TIMEOUT) && !(temp & ALI1535_STS_IDLE);
	     समयout++) अणु
		usleep_range(1000, 2000);
		temp = inb_p(SMBHSTSTS);
	पूर्ण
	अगर (समयout >= MAX_TIMEOUT)
		dev_warn(&adap->dev, "Idle wait Timeout! STS=0x%02x\n", temp);

	/* clear status रेजिस्टर (clear-on-ग_लिखो) */
	outb_p(0xFF, SMBHSTSTS);

	चयन (size) अणु
	हाल I2C_SMBUS_QUICK:
		outb_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMBHSTADD);
		size = ALI1535_QUICK;
		outb_p(size, SMBHSTTYP);	/* output command */
		अवरोध;
	हाल I2C_SMBUS_BYTE:
		outb_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMBHSTADD);
		size = ALI1535_BYTE;
		outb_p(size, SMBHSTTYP);	/* output command */
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			outb_p(command, SMBHSTCMD);
		अवरोध;
	हाल I2C_SMBUS_BYTE_DATA:
		outb_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMBHSTADD);
		size = ALI1535_BYTE_DATA;
		outb_p(size, SMBHSTTYP);	/* output command */
		outb_p(command, SMBHSTCMD);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			outb_p(data->byte, SMBHSTDAT0);
		अवरोध;
	हाल I2C_SMBUS_WORD_DATA:
		outb_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMBHSTADD);
		size = ALI1535_WORD_DATA;
		outb_p(size, SMBHSTTYP);	/* output command */
		outb_p(command, SMBHSTCMD);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			outb_p(data->word & 0xff, SMBHSTDAT0);
			outb_p((data->word & 0xff00) >> 8, SMBHSTDAT1);
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_BLOCK_DATA:
		outb_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMBHSTADD);
		size = ALI1535_BLOCK_DATA;
		outb_p(size, SMBHSTTYP);	/* output command */
		outb_p(command, SMBHSTCMD);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			len = data->block[0];
			अगर (len < 0) अणु
				len = 0;
				data->block[0] = len;
			पूर्ण
			अगर (len > 32) अणु
				len = 32;
				data->block[0] = len;
			पूर्ण
			outb_p(len, SMBHSTDAT0);
			/* Reset SMBBLKDAT */
			outb_p(inb_p(SMBHSTTYP) | ALI1535_BLOCK_CLR, SMBHSTTYP);
			क्रम (i = 1; i <= len; i++)
				outb_p(data->block[i], SMBBLKDAT);
		पूर्ण
		अवरोध;
	शेष:
		dev_warn(&adap->dev, "Unsupported transaction %d\n", size);
		result = -EOPNOTSUPP;
		जाओ EXIT;
	पूर्ण

	result = ali1535_transaction(adap);
	अगर (result)
		जाओ EXIT;

	अगर ((पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) || (size == ALI1535_QUICK)) अणु
		result = 0;
		जाओ EXIT;
	पूर्ण

	चयन (size) अणु
	हाल ALI1535_BYTE:	/* Result put in SMBHSTDAT0 */
		data->byte = inb_p(SMBHSTDAT0);
		अवरोध;
	हाल ALI1535_BYTE_DATA:
		data->byte = inb_p(SMBHSTDAT0);
		अवरोध;
	हाल ALI1535_WORD_DATA:
		data->word = inb_p(SMBHSTDAT0) + (inb_p(SMBHSTDAT1) << 8);
		अवरोध;
	हाल ALI1535_BLOCK_DATA:
		len = inb_p(SMBHSTDAT0);
		अगर (len > 32)
			len = 32;
		data->block[0] = len;
		/* Reset SMBBLKDAT */
		outb_p(inb_p(SMBHSTTYP) | ALI1535_BLOCK_CLR, SMBHSTTYP);
		क्रम (i = 1; i <= data->block[0]; i++) अणु
			data->block[i] = inb_p(SMBBLKDAT);
			dev_dbg(&adap->dev, "Blk: len=%d, i=%d, data=%02x\n",
				len, i, data->block[i]);
		पूर्ण
		अवरोध;
	पूर्ण
EXIT:
	वापस result;
पूर्ण


अटल u32 ali1535_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	    I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
	    I2C_FUNC_SMBUS_BLOCK_DATA;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm smbus_algorithm = अणु
	.smbus_xfer	= ali1535_access,
	.functionality	= ali1535_func,
पूर्ण;

अटल काष्ठा i2c_adapter ali1535_adapter = अणु
	.owner		= THIS_MODULE,
	.class          = I2C_CLASS_HWMON | I2C_CLASS_SPD,
	.algo		= &smbus_algorithm,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id ali1535_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_AL, PCI_DEVICE_ID_AL_M7101) पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, ali1535_ids);

अटल पूर्णांक ali1535_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	अगर (ali1535_setup(dev)) अणु
		dev_warn(&dev->dev,
			"ALI1535 not detected, module not inserted.\n");
		वापस -ENODEV;
	पूर्ण

	/* set up the sysfs linkage to our parent device */
	ali1535_adapter.dev.parent = &dev->dev;

	snम_लिखो(ali1535_adapter.name, माप(ali1535_adapter.name),
		"SMBus ALI1535 adapter at %04x", ali1535_offset);
	वापस i2c_add_adapter(&ali1535_adapter);
पूर्ण

अटल व्योम ali1535_हटाओ(काष्ठा pci_dev *dev)
अणु
	i2c_del_adapter(&ali1535_adapter);
	release_region(ali1535_smba, ALI1535_SMB_IOSIZE);
पूर्ण

अटल काष्ठा pci_driver ali1535_driver = अणु
	.name		= "ali1535_smbus",
	.id_table	= ali1535_ids,
	.probe		= ali1535_probe,
	.हटाओ		= ali1535_हटाओ,
पूर्ण;

module_pci_driver(ali1535_driver);

MODULE_AUTHOR("Frodo Looijaard <frodol@dds.nl>");
MODULE_AUTHOR("Philip Edelbrock <phil@netroedge.com>");
MODULE_AUTHOR("Mark D. Studebaker <mdsxyz123@yahoo.com>");
MODULE_AUTHOR("Dan Eaton <dan.eaton@rocketlogix.com>");
MODULE_DESCRIPTION("ALI1535 SMBus driver");
MODULE_LICENSE("GPL");
