<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Copyright (c) 1999  Froकरो Looijaard <froकरोl@dds.nl> and
    Philip Edelbrock <phil@netroedge.com> and
    Mark D. Studebaker <mdsxyz123@yahoo.com>

*/

/*
    This is the driver क्रम the SMB Host controller on
    Acer Lअसल Inc. (ALI) M1541 and M1543C South Bridges.

    The M1543C is a South bridge क्रम desktop प्रणालीs.
    The M1533 is a South bridge क्रम portable प्रणालीs.
    They are part of the following ALI chipsets:
       "Aladdin Pro 2": Includes the M1621 Slot 1 North bridge
       with AGP and 100MHz CPU Front Side bus
       "Aladdin V": Includes the M1541 Socket 7 North bridge
       with AGP and 100MHz CPU Front Side bus
       "Aladdin IV": Includes the M1541 Socket 7 North bridge
       with host bus up to 83.3 MHz.
    For an overview of these chips see http://www.acerद_असल.com

    The M1533/M1543C devices appear as FOUR separate devices
    on the PCI bus. An output of lspci will show something similar
    to the following:

	00:02.0 USB Controller: Acer Laboratories Inc. M5237
	00:03.0 Bridge: Acer Laboratories Inc. M7101
	00:07.0 ISA bridge: Acer Laboratories Inc. M1533
	00:0f.0 IDE पूर्णांकerface: Acer Laboratories Inc. M5229

    The SMB controller is part of the 7101 device, which is an
    ACPI-compliant Power Management Unit (PMU).

    The whole 7101 device has to be enabled क्रम the SMB to work.
    You can't just enable the SMB alone.
    The SMB and the ACPI have separate I/O spaces.
    We make sure that the SMB is enabled. We leave the ACPI alone.

    This driver controls the SMB Host only.
    The SMB Slave controller on the M15X3 is not enabled.

    This driver करोes not use पूर्णांकerrupts.
*/

/* Note: we assume there can only be one ALI15X3, with one SMBus पूर्णांकerface */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>

/* ALI15X3 SMBus address offsets */
#घोषणा SMBHSTSTS	(0 + ali15x3_smba)
#घोषणा SMBHSTCNT	(1 + ali15x3_smba)
#घोषणा SMBHSTSTART	(2 + ali15x3_smba)
#घोषणा SMBHSTCMD	(7 + ali15x3_smba)
#घोषणा SMBHSTADD	(3 + ali15x3_smba)
#घोषणा SMBHSTDAT0	(4 + ali15x3_smba)
#घोषणा SMBHSTDAT1	(5 + ali15x3_smba)
#घोषणा SMBBLKDAT	(6 + ali15x3_smba)

/* PCI Address Constants */
#घोषणा SMBCOM		0x004
#घोषणा SMBBA		0x014
#घोषणा SMBATPC		0x05B	/* used to unlock xxxBA रेजिस्टरs */
#घोषणा SMBHSTCFG	0x0E0
#घोषणा SMBSLVC		0x0E1
#घोषणा SMBCLK		0x0E2
#घोषणा SMBREV		0x008

/* Other settings */
#घोषणा MAX_TIMEOUT		200	/* बार 1/100 sec */
#घोषणा ALI15X3_SMB_IOSIZE	32

/* this is what the Award 1004 BIOS sets them to on a ASUS P5A MB.
   We करोn't use these here. If the bases aren't set to some value we
   tell user to upgrade BIOS and we fail.
*/
#घोषणा ALI15X3_SMB_DEFAULTBASE	0xE800

/* ALI15X3 address lock bits */
#घोषणा ALI15X3_LOCK		0x06

/* ALI15X3 command स्थिरants */
#घोषणा ALI15X3_ABORT		0x02
#घोषणा ALI15X3_T_OUT		0x04
#घोषणा ALI15X3_QUICK		0x00
#घोषणा ALI15X3_BYTE		0x10
#घोषणा ALI15X3_BYTE_DATA	0x20
#घोषणा ALI15X3_WORD_DATA	0x30
#घोषणा ALI15X3_BLOCK_DATA	0x40
#घोषणा ALI15X3_BLOCK_CLR	0x80

/* ALI15X3 status रेजिस्टर bits */
#घोषणा ALI15X3_STS_IDLE	0x04
#घोषणा ALI15X3_STS_BUSY	0x08
#घोषणा ALI15X3_STS_DONE	0x10
#घोषणा ALI15X3_STS_DEV		0x20	/* device error */
#घोषणा ALI15X3_STS_COLL	0x40	/* collision or no response */
#घोषणा ALI15X3_STS_TERM	0x80	/* terminated by पात */
#घोषणा ALI15X3_STS_ERR		0xE0	/* all the bad error bits */


/* If क्रमce_addr is set to anything dअगरferent from 0, we क्रमcibly enable
   the device at the given address. */
अटल u16 क्रमce_addr;
module_param_hw(क्रमce_addr, uलघु, ioport, 0);
MODULE_PARM_DESC(क्रमce_addr,
		 "Initialize the base address of the i2c controller");

अटल काष्ठा pci_driver ali15x3_driver;
अटल अचिन्हित लघु ali15x3_smba;

अटल पूर्णांक ali15x3_setup(काष्ठा pci_dev *ALI15X3_dev)
अणु
	u16 a;
	अचिन्हित अक्षर temp;

	/* Check the following things:
		- SMB I/O address is initialized
		- Device is enabled
		- We can use the addresses
	*/

	/* Unlock the रेजिस्टर.
	   The data sheet says that the address रेजिस्टरs are पढ़ो-only
	   अगर the lock bits are 1, but in fact the address रेजिस्टरs
	   are zero unless you clear the lock bits.
	*/
	pci_पढ़ो_config_byte(ALI15X3_dev, SMBATPC, &temp);
	अगर (temp & ALI15X3_LOCK) अणु
		temp &= ~ALI15X3_LOCK;
		pci_ग_लिखो_config_byte(ALI15X3_dev, SMBATPC, temp);
	पूर्ण

	/* Determine the address of the SMBus area */
	pci_पढ़ो_config_word(ALI15X3_dev, SMBBA, &ali15x3_smba);
	ali15x3_smba &= (0xffff & ~(ALI15X3_SMB_IOSIZE - 1));
	अगर (ali15x3_smba == 0 && क्रमce_addr == 0) अणु
		dev_err(&ALI15X3_dev->dev, "ALI15X3_smb region uninitialized "
			"- upgrade BIOS or use force_addr=0xaddr\n");
		वापस -ENODEV;
	पूर्ण

	अगर(क्रमce_addr)
		ali15x3_smba = क्रमce_addr & ~(ALI15X3_SMB_IOSIZE - 1);

	अगर (acpi_check_region(ali15x3_smba, ALI15X3_SMB_IOSIZE,
			      ali15x3_driver.name))
		वापस -EBUSY;

	अगर (!request_region(ali15x3_smba, ALI15X3_SMB_IOSIZE,
			    ali15x3_driver.name)) अणु
		dev_err(&ALI15X3_dev->dev,
			"ALI15X3_smb region 0x%x already in use!\n",
			ali15x3_smba);
		वापस -ENODEV;
	पूर्ण

	अगर(क्रमce_addr) अणु
		dev_info(&ALI15X3_dev->dev, "forcing ISA address 0x%04X\n",
			ali15x3_smba);
		अगर (PCIBIOS_SUCCESSFUL != pci_ग_लिखो_config_word(ALI15X3_dev,
								SMBBA,
								ali15x3_smba))
			जाओ error;
		अगर (PCIBIOS_SUCCESSFUL != pci_पढ़ो_config_word(ALI15X3_dev,
								SMBBA, &a))
			जाओ error;
		अगर ((a & ~(ALI15X3_SMB_IOSIZE - 1)) != ali15x3_smba) अणु
			/* make sure it works */
			dev_err(&ALI15X3_dev->dev,
				"force address failed - not supported?\n");
			जाओ error;
		पूर्ण
	पूर्ण
	/* check अगर whole device is enabled */
	pci_पढ़ो_config_byte(ALI15X3_dev, SMBCOM, &temp);
	अगर ((temp & 1) == 0) अणु
		dev_info(&ALI15X3_dev->dev, "enabling SMBus device\n");
		pci_ग_लिखो_config_byte(ALI15X3_dev, SMBCOM, temp | 0x01);
	पूर्ण

	/* Is SMB Host controller enabled? */
	pci_पढ़ो_config_byte(ALI15X3_dev, SMBHSTCFG, &temp);
	अगर ((temp & 1) == 0) अणु
		dev_info(&ALI15X3_dev->dev, "enabling SMBus controller\n");
		pci_ग_लिखो_config_byte(ALI15X3_dev, SMBHSTCFG, temp | 0x01);
	पूर्ण

	/* set SMB घड़ी to 74KHz as recommended in data sheet */
	pci_ग_लिखो_config_byte(ALI15X3_dev, SMBCLK, 0x20);

	/*
	  The पूर्णांकerrupt routing क्रम SMB is set up in रेजिस्टर 0x77 in the
	  1533 ISA Bridge device, NOT in the 7101 device.
	  Don't bother with finding the 1533 device and पढ़ोing the रेजिस्टर.
	अगर ((....... & 0x0F) == 1)
		dev_dbg(&ALI15X3_dev->dev, "ALI15X3 using Interrupt 9 for SMBus.\n");
	*/
	pci_पढ़ो_config_byte(ALI15X3_dev, SMBREV, &temp);
	dev_dbg(&ALI15X3_dev->dev, "SMBREV = 0x%X\n", temp);
	dev_dbg(&ALI15X3_dev->dev, "iALI15X3_smba = 0x%X\n", ali15x3_smba);

	वापस 0;
error:
	release_region(ali15x3_smba, ALI15X3_SMB_IOSIZE);
	वापस -ENODEV;
पूर्ण

/* Another पूर्णांकernally used function */
अटल पूर्णांक ali15x3_transaction(काष्ठा i2c_adapter *adap)
अणु
	पूर्णांक temp;
	पूर्णांक result = 0;
	पूर्णांक समयout = 0;

	dev_dbg(&adap->dev, "Transaction (pre): STS=%02x, CNT=%02x, CMD=%02x, "
		"ADD=%02x, DAT0=%02x, DAT1=%02x\n", inb_p(SMBHSTSTS),
		inb_p(SMBHSTCNT), inb_p(SMBHSTCMD), inb_p(SMBHSTADD),
		inb_p(SMBHSTDAT0), inb_p(SMBHSTDAT1));

	/* get status */
	temp = inb_p(SMBHSTSTS);

	/* Make sure the SMBus host is पढ़ोy to start transmitting */
	/* Check the busy bit first */
	अगर (temp & ALI15X3_STS_BUSY) अणु
	/*
	   If the host controller is still busy, it may have समयd out in the
	   previous transaction, resulting in a "SMBus Timeout" Dev.
	   I've tried the following to reset a stuck busy bit.
		1. Reset the controller with an ABORT command.
		   (this करोesn't seem to clear the controller अगर an बाह्यal
		   device is hung)
		2. Reset the controller and the other SMBus devices with a
		   T_OUT command.  (this clears the host busy bit अगर an
		   बाह्यal device is hung, but it comes back upon a new access
		   to a device)
		3. Disable and reenable the controller in SMBHSTCFG
	   Worst हाल, nothing seems to work except घातer reset.
	*/
	/* Abort - reset the host controller */
	/*
	   Try resetting entire SMB bus, including other devices -
	   This may not work either - it clears the BUSY bit but
	   then the BUSY bit may come back on when you try and use the chip again.
	   If that's the हाल you are stuck.
	*/
		dev_info(&adap->dev, "Resetting entire SMB Bus to "
			"clear busy condition (%02x)\n", temp);
		outb_p(ALI15X3_T_OUT, SMBHSTCNT);
		temp = inb_p(SMBHSTSTS);
	पूर्ण

	/* now check the error bits and the busy bit */
	अगर (temp & (ALI15X3_STS_ERR | ALI15X3_STS_BUSY)) अणु
		/* करो a clear-on-ग_लिखो */
		outb_p(0xFF, SMBHSTSTS);
		अगर ((temp = inb_p(SMBHSTSTS)) &
		    (ALI15X3_STS_ERR | ALI15X3_STS_BUSY)) अणु
			/* this is probably going to be correctable only by a घातer reset
			   as one of the bits now appears to be stuck */
			/* This may be a bus or device with electrical problems. */
			dev_err(&adap->dev, "SMBus reset failed! (0x%02x) - "
				"controller or device on bus is probably hung\n",
				temp);
			वापस -EBUSY;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* check and clear करोne bit */
		अगर (temp & ALI15X3_STS_DONE) अणु
			outb_p(temp, SMBHSTSTS);
		पूर्ण
	पूर्ण

	/* start the transaction by writing anything to the start रेजिस्टर */
	outb_p(0xFF, SMBHSTSTART);

	/* We will always रुको क्रम a fraction of a second! */
	समयout = 0;
	करो अणु
		msleep(1);
		temp = inb_p(SMBHSTSTS);
	पूर्ण जबतक ((!(temp & (ALI15X3_STS_ERR | ALI15X3_STS_DONE)))
		 && (समयout++ < MAX_TIMEOUT));

	/* If the SMBus is still busy, we give up */
	अगर (समयout > MAX_TIMEOUT) अणु
		result = -ETIMEDOUT;
		dev_err(&adap->dev, "SMBus Timeout!\n");
	पूर्ण

	अगर (temp & ALI15X3_STS_TERM) अणु
		result = -EIO;
		dev_dbg(&adap->dev, "Error: Failed bus transaction\n");
	पूर्ण

	/*
	  Unक्रमtunately the ALI SMB controller maps "no response" and "bus
	  collision" पूर्णांकo a single bit. No response is the usual हाल so करोn't
	  करो a prपूर्णांकk.
	  This means that bus collisions go unreported.
	*/
	अगर (temp & ALI15X3_STS_COLL) अणु
		result = -ENXIO;
		dev_dbg(&adap->dev,
			"Error: no response or bus collision ADD=%02x\n",
			inb_p(SMBHSTADD));
	पूर्ण

	/* haven't ever seen this */
	अगर (temp & ALI15X3_STS_DEV) अणु
		result = -EIO;
		dev_err(&adap->dev, "Error: device error\n");
	पूर्ण
	dev_dbg(&adap->dev, "Transaction (post): STS=%02x, CNT=%02x, CMD=%02x, "
		"ADD=%02x, DAT0=%02x, DAT1=%02x\n", inb_p(SMBHSTSTS),
		inb_p(SMBHSTCNT), inb_p(SMBHSTCMD), inb_p(SMBHSTADD),
		inb_p(SMBHSTDAT0), inb_p(SMBHSTDAT1));
	वापस result;
पूर्ण

/* Return negative त्रुटि_सं on error. */
अटल s32 ali15x3_access(काष्ठा i2c_adapter * adap, u16 addr,
		   अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो, u8 command,
		   पूर्णांक size, जोड़ i2c_smbus_data * data)
अणु
	पूर्णांक i, len;
	पूर्णांक temp;
	पूर्णांक समयout;

	/* clear all the bits (clear-on-ग_लिखो) */
	outb_p(0xFF, SMBHSTSTS);
	/* make sure SMBus is idle */
	temp = inb_p(SMBHSTSTS);
	क्रम (समयout = 0;
	     (समयout < MAX_TIMEOUT) && !(temp & ALI15X3_STS_IDLE);
	     समयout++) अणु
		msleep(1);
		temp = inb_p(SMBHSTSTS);
	पूर्ण
	अगर (समयout >= MAX_TIMEOUT) अणु
		dev_err(&adap->dev, "Idle wait Timeout! STS=0x%02x\n", temp);
	पूर्ण

	चयन (size) अणु
	हाल I2C_SMBUS_QUICK:
		outb_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMBHSTADD);
		size = ALI15X3_QUICK;
		अवरोध;
	हाल I2C_SMBUS_BYTE:
		outb_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMBHSTADD);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			outb_p(command, SMBHSTCMD);
		size = ALI15X3_BYTE;
		अवरोध;
	हाल I2C_SMBUS_BYTE_DATA:
		outb_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMBHSTADD);
		outb_p(command, SMBHSTCMD);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			outb_p(data->byte, SMBHSTDAT0);
		size = ALI15X3_BYTE_DATA;
		अवरोध;
	हाल I2C_SMBUS_WORD_DATA:
		outb_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMBHSTADD);
		outb_p(command, SMBHSTCMD);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			outb_p(data->word & 0xff, SMBHSTDAT0);
			outb_p((data->word & 0xff00) >> 8, SMBHSTDAT1);
		पूर्ण
		size = ALI15X3_WORD_DATA;
		अवरोध;
	हाल I2C_SMBUS_BLOCK_DATA:
		outb_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMBHSTADD);
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
			outb_p(inb_p(SMBHSTCNT) | ALI15X3_BLOCK_CLR, SMBHSTCNT);
			क्रम (i = 1; i <= len; i++)
				outb_p(data->block[i], SMBBLKDAT);
		पूर्ण
		size = ALI15X3_BLOCK_DATA;
		अवरोध;
	शेष:
		dev_warn(&adap->dev, "Unsupported transaction %d\n", size);
		वापस -EOPNOTSUPP;
	पूर्ण

	outb_p(size, SMBHSTCNT);	/* output command */

	temp = ali15x3_transaction(adap);
	अगर (temp)
		वापस temp;

	अगर ((पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) || (size == ALI15X3_QUICK))
		वापस 0;


	चयन (size) अणु
	हाल ALI15X3_BYTE:	/* Result put in SMBHSTDAT0 */
		data->byte = inb_p(SMBHSTDAT0);
		अवरोध;
	हाल ALI15X3_BYTE_DATA:
		data->byte = inb_p(SMBHSTDAT0);
		अवरोध;
	हाल ALI15X3_WORD_DATA:
		data->word = inb_p(SMBHSTDAT0) + (inb_p(SMBHSTDAT1) << 8);
		अवरोध;
	हाल ALI15X3_BLOCK_DATA:
		len = inb_p(SMBHSTDAT0);
		अगर (len > 32)
			len = 32;
		data->block[0] = len;
		/* Reset SMBBLKDAT */
		outb_p(inb_p(SMBHSTCNT) | ALI15X3_BLOCK_CLR, SMBHSTCNT);
		क्रम (i = 1; i <= data->block[0]; i++) अणु
			data->block[i] = inb_p(SMBBLKDAT);
			dev_dbg(&adap->dev, "Blk: len=%d, i=%d, data=%02x\n",
				len, i, data->block[i]);
		पूर्ण
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल u32 ali15x3_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	    I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
	    I2C_FUNC_SMBUS_BLOCK_DATA;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm smbus_algorithm = अणु
	.smbus_xfer	= ali15x3_access,
	.functionality	= ali15x3_func,
पूर्ण;

अटल काष्ठा i2c_adapter ali15x3_adapter = अणु
	.owner		= THIS_MODULE,
	.class          = I2C_CLASS_HWMON | I2C_CLASS_SPD,
	.algo		= &smbus_algorithm,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id ali15x3_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_AL, PCI_DEVICE_ID_AL_M7101) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE (pci, ali15x3_ids);

अटल पूर्णांक ali15x3_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	अगर (ali15x3_setup(dev)) अणु
		dev_err(&dev->dev,
			"ALI15X3 not detected, module not inserted.\n");
		वापस -ENODEV;
	पूर्ण

	/* set up the sysfs linkage to our parent device */
	ali15x3_adapter.dev.parent = &dev->dev;

	snम_लिखो(ali15x3_adapter.name, माप(ali15x3_adapter.name),
		"SMBus ALI15X3 adapter at %04x", ali15x3_smba);
	वापस i2c_add_adapter(&ali15x3_adapter);
पूर्ण

अटल व्योम ali15x3_हटाओ(काष्ठा pci_dev *dev)
अणु
	i2c_del_adapter(&ali15x3_adapter);
	release_region(ali15x3_smba, ALI15X3_SMB_IOSIZE);
पूर्ण

अटल काष्ठा pci_driver ali15x3_driver = अणु
	.name		= "ali15x3_smbus",
	.id_table	= ali15x3_ids,
	.probe		= ali15x3_probe,
	.हटाओ		= ali15x3_हटाओ,
पूर्ण;

module_pci_driver(ali15x3_driver);

MODULE_AUTHOR("Frodo Looijaard <frodol@dds.nl>");
MODULE_AUTHOR("Philip Edelbrock <phil@netroedge.com>");
MODULE_AUTHOR("Mark D. Studebaker <mdsxyz123@yahoo.com>");
MODULE_DESCRIPTION("ALI15X3 SMBus driver");
MODULE_LICENSE("GPL");
