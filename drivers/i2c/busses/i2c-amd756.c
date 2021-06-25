<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Copyright (c) 1999-2002 Merlin Hughes <merlin@merlin.org>

    Shamelessly ripped from i2c-piix4.c:

    Copyright (c) 1998, 1999  Froकरो Looijaard <froकरोl@dds.nl> and
    Philip Edelbrock <phil@netroedge.com>

*/

/*
    2002-04-08: Added nForce support. (Csaba Halasz)
    2002-10-03: Fixed nForce PnP I/O port. (Michael Steil)
    2002-12-28: Rewritten पूर्णांकo something that resembles a Linux driver (hch)
    2003-11-29: Added back AMD8111 हटाओd by the previous reग_लिखो.
                (Philip Pokorny)
*/

/*
   Supports AMD756, AMD766, AMD768, AMD8111 and nVidia nForce
   Note: we assume there can only be one device, with one SMBus पूर्णांकerface.
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

/* AMD756 SMBus address offsets */
#घोषणा SMB_ADDR_OFFSET		0xE0
#घोषणा SMB_IOSIZE		16
#घोषणा SMB_GLOBAL_STATUS	(0x0 + amd756_ioport)
#घोषणा SMB_GLOBAL_ENABLE	(0x2 + amd756_ioport)
#घोषणा SMB_HOST_ADDRESS	(0x4 + amd756_ioport)
#घोषणा SMB_HOST_DATA		(0x6 + amd756_ioport)
#घोषणा SMB_HOST_COMMAND	(0x8 + amd756_ioport)
#घोषणा SMB_HOST_BLOCK_DATA	(0x9 + amd756_ioport)
#घोषणा SMB_HAS_DATA		(0xA + amd756_ioport)
#घोषणा SMB_HAS_DEVICE_ADDRESS	(0xC + amd756_ioport)
#घोषणा SMB_HAS_HOST_ADDRESS	(0xE + amd756_ioport)
#घोषणा SMB_SNOOP_ADDRESS	(0xF + amd756_ioport)

/* PCI Address Constants */

/* address of I/O space */
#घोषणा SMBBA		0x058		/* mh */
#घोषणा SMBBANFORCE	0x014

/* general configuration */
#घोषणा SMBGCFG		0x041		/* mh */

/* silicon revision code */
#घोषणा SMBREV		0x008

/* Other settings */
#घोषणा MAX_TIMEOUT	500

/* AMD756 स्थिरants */
#घोषणा AMD756_QUICK		0x00
#घोषणा AMD756_BYTE		0x01
#घोषणा AMD756_BYTE_DATA	0x02
#घोषणा AMD756_WORD_DATA	0x03
#घोषणा AMD756_PROCESS_CALL	0x04
#घोषणा AMD756_BLOCK_DATA	0x05

अटल काष्ठा pci_driver amd756_driver;
अटल अचिन्हित लघु amd756_ioport;

/* 
  SMBUS event = I/O 28-29 bit 11
     see E0 क्रम the status bits and enabled in E2
     
*/
#घोषणा GS_ABRT_STS	(1 << 0)
#घोषणा GS_COL_STS	(1 << 1)
#घोषणा GS_PRERR_STS	(1 << 2)
#घोषणा GS_HST_STS	(1 << 3)
#घोषणा GS_HCYC_STS	(1 << 4)
#घोषणा GS_TO_STS	(1 << 5)
#घोषणा GS_SMB_STS	(1 << 11)

#घोषणा GS_CLEAR_STS	(GS_ABRT_STS | GS_COL_STS | GS_PRERR_STS | \
			 GS_HCYC_STS | GS_TO_STS )

#घोषणा GE_CYC_TYPE_MASK	(7)
#घोषणा GE_HOST_STC		(1 << 3)
#घोषणा GE_ABORT		(1 << 5)


अटल पूर्णांक amd756_transaction(काष्ठा i2c_adapter *adap)
अणु
	पूर्णांक temp;
	पूर्णांक result = 0;
	पूर्णांक समयout = 0;

	dev_dbg(&adap->dev, "Transaction (pre): GS=%04x, GE=%04x, ADD=%04x, "
		"DAT=%04x\n", inw_p(SMB_GLOBAL_STATUS),
		inw_p(SMB_GLOBAL_ENABLE), inw_p(SMB_HOST_ADDRESS),
		inb_p(SMB_HOST_DATA));

	/* Make sure the SMBus host is पढ़ोy to start transmitting */
	अगर ((temp = inw_p(SMB_GLOBAL_STATUS)) & (GS_HST_STS | GS_SMB_STS)) अणु
		dev_dbg(&adap->dev, "SMBus busy (%04x). Waiting...\n", temp);
		करो अणु
			msleep(1);
			temp = inw_p(SMB_GLOBAL_STATUS);
		पूर्ण जबतक ((temp & (GS_HST_STS | GS_SMB_STS)) &&
		         (समयout++ < MAX_TIMEOUT));
		/* If the SMBus is still busy, we give up */
		अगर (समयout > MAX_TIMEOUT) अणु
			dev_dbg(&adap->dev, "Busy wait timeout (%04x)\n", temp);
			जाओ पात;
		पूर्ण
		समयout = 0;
	पूर्ण

	/* start the transaction by setting the start bit */
	outw_p(inw(SMB_GLOBAL_ENABLE) | GE_HOST_STC, SMB_GLOBAL_ENABLE);

	/* We will always रुको क्रम a fraction of a second! */
	करो अणु
		msleep(1);
		temp = inw_p(SMB_GLOBAL_STATUS);
	पूर्ण जबतक ((temp & GS_HST_STS) && (समयout++ < MAX_TIMEOUT));

	/* If the SMBus is still busy, we give up */
	अगर (समयout > MAX_TIMEOUT) अणु
		dev_dbg(&adap->dev, "Completion timeout!\n");
		जाओ पात;
	पूर्ण

	अगर (temp & GS_PRERR_STS) अणु
		result = -ENXIO;
		dev_dbg(&adap->dev, "SMBus Protocol error (no response)!\n");
	पूर्ण

	अगर (temp & GS_COL_STS) अणु
		result = -EIO;
		dev_warn(&adap->dev, "SMBus collision!\n");
	पूर्ण

	अगर (temp & GS_TO_STS) अणु
		result = -ETIMEDOUT;
		dev_dbg(&adap->dev, "SMBus protocol timeout!\n");
	पूर्ण

	अगर (temp & GS_HCYC_STS)
		dev_dbg(&adap->dev, "SMBus protocol success!\n");

	outw_p(GS_CLEAR_STS, SMB_GLOBAL_STATUS);

#अगर_घोषित DEBUG
	अगर (((temp = inw_p(SMB_GLOBAL_STATUS)) & GS_CLEAR_STS) != 0x00) अणु
		dev_dbg(&adap->dev,
			"Failed reset at end of transaction (%04x)\n", temp);
	पूर्ण
#पूर्ण_अगर

	dev_dbg(&adap->dev,
		"Transaction (post): GS=%04x, GE=%04x, ADD=%04x, DAT=%04x\n",
		inw_p(SMB_GLOBAL_STATUS), inw_p(SMB_GLOBAL_ENABLE),
		inw_p(SMB_HOST_ADDRESS), inb_p(SMB_HOST_DATA));

	वापस result;

 पात:
	dev_warn(&adap->dev, "Sending abort\n");
	outw_p(inw(SMB_GLOBAL_ENABLE) | GE_ABORT, SMB_GLOBAL_ENABLE);
	msleep(100);
	outw_p(GS_CLEAR_STS, SMB_GLOBAL_STATUS);
	वापस -EIO;
पूर्ण

/* Return negative त्रुटि_सं on error. */
अटल s32 amd756_access(काष्ठा i2c_adapter * adap, u16 addr,
		  अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
		  u8 command, पूर्णांक size, जोड़ i2c_smbus_data * data)
अणु
	पूर्णांक i, len;
	पूर्णांक status;

	चयन (size) अणु
	हाल I2C_SMBUS_QUICK:
		outw_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMB_HOST_ADDRESS);
		size = AMD756_QUICK;
		अवरोध;
	हाल I2C_SMBUS_BYTE:
		outw_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMB_HOST_ADDRESS);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			outb_p(command, SMB_HOST_DATA);
		size = AMD756_BYTE;
		अवरोध;
	हाल I2C_SMBUS_BYTE_DATA:
		outw_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMB_HOST_ADDRESS);
		outb_p(command, SMB_HOST_COMMAND);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			outw_p(data->byte, SMB_HOST_DATA);
		size = AMD756_BYTE_DATA;
		अवरोध;
	हाल I2C_SMBUS_WORD_DATA:
		outw_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMB_HOST_ADDRESS);
		outb_p(command, SMB_HOST_COMMAND);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			outw_p(data->word, SMB_HOST_DATA);	/* TODO: endian???? */
		size = AMD756_WORD_DATA;
		अवरोध;
	हाल I2C_SMBUS_BLOCK_DATA:
		outw_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMB_HOST_ADDRESS);
		outb_p(command, SMB_HOST_COMMAND);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			len = data->block[0];
			अगर (len < 0)
				len = 0;
			अगर (len > 32)
				len = 32;
			outw_p(len, SMB_HOST_DATA);
			/* i = inw_p(SMBHSTCNT); Reset SMBBLKDAT */
			क्रम (i = 1; i <= len; i++)
				outb_p(data->block[i],
				       SMB_HOST_BLOCK_DATA);
		पूर्ण
		size = AMD756_BLOCK_DATA;
		अवरोध;
	शेष:
		dev_warn(&adap->dev, "Unsupported transaction %d\n", size);
		वापस -EOPNOTSUPP;
	पूर्ण

	/* How about enabling पूर्णांकerrupts... */
	outw_p(size & GE_CYC_TYPE_MASK, SMB_GLOBAL_ENABLE);

	status = amd756_transaction(adap);
	अगर (status)
		वापस status;

	अगर ((पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) || (size == AMD756_QUICK))
		वापस 0;


	चयन (size) अणु
	हाल AMD756_BYTE:
		data->byte = inw_p(SMB_HOST_DATA);
		अवरोध;
	हाल AMD756_BYTE_DATA:
		data->byte = inw_p(SMB_HOST_DATA);
		अवरोध;
	हाल AMD756_WORD_DATA:
		data->word = inw_p(SMB_HOST_DATA);	/* TODO: endian???? */
		अवरोध;
	हाल AMD756_BLOCK_DATA:
		data->block[0] = inw_p(SMB_HOST_DATA) & 0x3f;
		अगर(data->block[0] > 32)
			data->block[0] = 32;
		/* i = inw_p(SMBHSTCNT); Reset SMBBLKDAT */
		क्रम (i = 1; i <= data->block[0]; i++)
			data->block[i] = inb_p(SMB_HOST_BLOCK_DATA);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 amd756_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	    I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
	    I2C_FUNC_SMBUS_BLOCK_DATA;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm smbus_algorithm = अणु
	.smbus_xfer	= amd756_access,
	.functionality	= amd756_func,
पूर्ण;

काष्ठा i2c_adapter amd756_smbus = अणु
	.owner		= THIS_MODULE,
	.class          = I2C_CLASS_HWMON | I2C_CLASS_SPD,
	.algo		= &smbus_algorithm,
पूर्ण;

क्रमागत chiptype अणु AMD756, AMD766, AMD768, NFORCE, AMD8111 पूर्ण;
अटल स्थिर अक्षर* chipname[] = अणु
	"AMD756", "AMD766", "AMD768",
	"nVidia nForce", "AMD8111",
पूर्ण;

अटल स्थिर काष्ठा pci_device_id amd756_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_VIPER_740B),
	  .driver_data = AMD756 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_VIPER_7413),
	  .driver_data = AMD766 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_OPUS_7443),
	  .driver_data = AMD768 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_8111_SMBUS),
	  .driver_data = AMD8111 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_SMBUS),
	  .driver_data = NFORCE पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE (pci, amd756_ids);

अटल पूर्णांक amd756_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक nक्रमce = (id->driver_data == NFORCE);
	पूर्णांक error;
	u8 temp;
	
	अगर (amd756_ioport) अणु
		dev_err(&pdev->dev, "Only one device supported "
		       "(you have a strange motherboard, btw)\n");
		वापस -ENODEV;
	पूर्ण

	अगर (nक्रमce) अणु
		अगर (PCI_FUNC(pdev->devfn) != 1)
			वापस -ENODEV;

		pci_पढ़ो_config_word(pdev, SMBBANFORCE, &amd756_ioport);
		amd756_ioport &= 0xfffc;
	पूर्ण अन्यथा अणु /* amd */
		अगर (PCI_FUNC(pdev->devfn) != 3)
			वापस -ENODEV;

		pci_पढ़ो_config_byte(pdev, SMBGCFG, &temp);
		अगर ((temp & 128) == 0) अणु
			dev_err(&pdev->dev,
				"Error: SMBus controller I/O not enabled!\n");
			वापस -ENODEV;
		पूर्ण

		/* Determine the address of the SMBus areas */
		/* Technically it is a dword but... */
		pci_पढ़ो_config_word(pdev, SMBBA, &amd756_ioport);
		amd756_ioport &= 0xff00;
		amd756_ioport += SMB_ADDR_OFFSET;
	पूर्ण

	error = acpi_check_region(amd756_ioport, SMB_IOSIZE,
				  amd756_driver.name);
	अगर (error)
		वापस -ENODEV;

	अगर (!request_region(amd756_ioport, SMB_IOSIZE, amd756_driver.name)) अणु
		dev_err(&pdev->dev, "SMB region 0x%x already in use!\n",
			amd756_ioport);
		वापस -ENODEV;
	पूर्ण

	pci_पढ़ो_config_byte(pdev, SMBREV, &temp);
	dev_dbg(&pdev->dev, "SMBREV = 0x%X\n", temp);
	dev_dbg(&pdev->dev, "AMD756_smba = 0x%X\n", amd756_ioport);

	/* set up the sysfs linkage to our parent device */
	amd756_smbus.dev.parent = &pdev->dev;

	snम_लिखो(amd756_smbus.name, माप(amd756_smbus.name),
		 "SMBus %s adapter at %04x", chipname[id->driver_data],
		 amd756_ioport);

	error = i2c_add_adapter(&amd756_smbus);
	अगर (error)
		जाओ out_err;

	वापस 0;

 out_err:
	release_region(amd756_ioport, SMB_IOSIZE);
	वापस error;
पूर्ण

अटल व्योम amd756_हटाओ(काष्ठा pci_dev *dev)
अणु
	i2c_del_adapter(&amd756_smbus);
	release_region(amd756_ioport, SMB_IOSIZE);
पूर्ण

अटल काष्ठा pci_driver amd756_driver = अणु
	.name		= "amd756_smbus",
	.id_table	= amd756_ids,
	.probe		= amd756_probe,
	.हटाओ		= amd756_हटाओ,
पूर्ण;

module_pci_driver(amd756_driver);

MODULE_AUTHOR("Merlin Hughes <merlin@merlin.org>");
MODULE_DESCRIPTION("AMD756/766/768/8111 and nVidia nForce SMBus driver");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(amd756_smbus);
