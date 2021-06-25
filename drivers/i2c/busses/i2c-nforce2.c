<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    SMBus driver क्रम nVidia nForce2 MCP

    Added nForce3 Pro 150  Thomas Leibold <thomas@plx.com>,
	Ported to 2.5 Patrick Dreker <patrick@dreker.de>,
    Copyright (c) 2003  Hans-Frieder Vogt <hfvogt@arcor.de>,
    Based on
    SMBus 2.0 driver क्रम AMD-8111 IO-Hub
    Copyright (c) 2002 Vojtech Pavlik

*/

/*
    SUPPORTED DEVICES		PCI ID
    nForce2 MCP			0064
    nForce2 Ultra 400 MCP	0084
    nForce3 Pro150 MCP		00D4
    nForce3 250Gb MCP		00E4
    nForce4 MCP			0052
    nForce4 MCP-04		0034
    nForce MCP51		0264
    nForce MCP55		0368
    nForce MCP61		03EB
    nForce MCP65		0446
    nForce MCP67		0542
    nForce MCP73		07D8
    nForce MCP78S		0752
    nForce MCP79		0AA2

    This driver supports the 2 SMBuses that are included in the MCP of the
    nForce2/3/4/5xx chipsets.
*/

/* Note: we assume there can only be one nForce2, with two SMBus पूर्णांकerfaces */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/ioport.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmi.h>
#समावेश <linux/acpi.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hans-Frieder Vogt <hfvogt@gmx.net>");
MODULE_DESCRIPTION("nForce2/3/4/5xx SMBus driver");


काष्ठा nक्रमce2_smbus अणु
	काष्ठा i2c_adapter adapter;
	पूर्णांक base;
	पूर्णांक size;
	पूर्णांक blockops;
	पूर्णांक can_पात;
पूर्ण;


/*
 * nVidia nForce2 SMBus control रेजिस्टर definitions
 * (Newer incarnations use standard BARs 4 and 5 instead)
 */
#घोषणा NFORCE_PCI_SMB1	0x50
#घोषणा NFORCE_PCI_SMB2	0x54


/*
 * ACPI 2.0 chapter 13 SMBus 2.0 EC रेजिस्टर model
 */
#घोषणा NVIDIA_SMB_PRTCL	(smbus->base + 0x00)	/* protocol, PEC */
#घोषणा NVIDIA_SMB_STS		(smbus->base + 0x01)	/* status */
#घोषणा NVIDIA_SMB_ADDR		(smbus->base + 0x02)	/* address */
#घोषणा NVIDIA_SMB_CMD		(smbus->base + 0x03)	/* command */
#घोषणा NVIDIA_SMB_DATA		(smbus->base + 0x04)	/* 32 data रेजिस्टरs */
#घोषणा NVIDIA_SMB_BCNT		(smbus->base + 0x24)	/* number of data
							   bytes */
#घोषणा NVIDIA_SMB_STATUS_ABRT	(smbus->base + 0x3c)	/* रेजिस्टर used to
							   check the status of
							   the पात command */
#घोषणा NVIDIA_SMB_CTRL		(smbus->base + 0x3e)	/* control रेजिस्टर */

#घोषणा NVIDIA_SMB_STATUS_ABRT_STS	0x01		/* Bit to notअगरy that
							   पात succeeded */
#घोषणा NVIDIA_SMB_CTRL_ABORT	0x20
#घोषणा NVIDIA_SMB_STS_DONE	0x80
#घोषणा NVIDIA_SMB_STS_ALRM	0x40
#घोषणा NVIDIA_SMB_STS_RES	0x20
#घोषणा NVIDIA_SMB_STS_STATUS	0x1f

#घोषणा NVIDIA_SMB_PRTCL_WRITE			0x00
#घोषणा NVIDIA_SMB_PRTCL_READ			0x01
#घोषणा NVIDIA_SMB_PRTCL_QUICK			0x02
#घोषणा NVIDIA_SMB_PRTCL_BYTE			0x04
#घोषणा NVIDIA_SMB_PRTCL_BYTE_DATA		0x06
#घोषणा NVIDIA_SMB_PRTCL_WORD_DATA		0x08
#घोषणा NVIDIA_SMB_PRTCL_BLOCK_DATA		0x0a
#घोषणा NVIDIA_SMB_PRTCL_PEC			0x80

/* Misc definitions */
#घोषणा MAX_TIMEOUT	100

/* We disable the second SMBus channel on these boards */
अटल स्थिर काष्ठा dmi_प्रणाली_id nक्रमce2_dmi_blacklist2[] = अणु
	अणु
		.ident = "DFI Lanparty NF4 Expert",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "DFI Corp,LTD"),
			DMI_MATCH(DMI_BOARD_NAME, "LP UT NF4 Expert"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा pci_driver nक्रमce2_driver;

/* For multiplexing support, we need a global reference to the 1st
   SMBus channel */
#अगर IS_ENABLED(CONFIG_I2C_NFORCE2_S4985)
काष्ठा i2c_adapter *nक्रमce2_smbus;
EXPORT_SYMBOL_GPL(nक्रमce2_smbus);

अटल व्योम nक्रमce2_set_reference(काष्ठा i2c_adapter *adap)
अणु
	nक्रमce2_smbus = adap;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम nक्रमce2_set_reference(काष्ठा i2c_adapter *adap) अणु पूर्ण
#पूर्ण_अगर

अटल व्योम nक्रमce2_पात(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा nक्रमce2_smbus *smbus = adap->algo_data;
	पूर्णांक समयout = 0;
	अचिन्हित अक्षर temp;

	dev_dbg(&adap->dev, "Aborting current transaction\n");

	outb_p(NVIDIA_SMB_CTRL_ABORT, NVIDIA_SMB_CTRL);
	करो अणु
		msleep(1);
		temp = inb_p(NVIDIA_SMB_STATUS_ABRT);
	पूर्ण जबतक (!(temp & NVIDIA_SMB_STATUS_ABRT_STS) &&
			(समयout++ < MAX_TIMEOUT));
	अगर (!(temp & NVIDIA_SMB_STATUS_ABRT_STS))
		dev_err(&adap->dev, "Can't reset the smbus\n");
	outb_p(NVIDIA_SMB_STATUS_ABRT_STS, NVIDIA_SMB_STATUS_ABRT);
पूर्ण

अटल पूर्णांक nक्रमce2_check_status(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा nक्रमce2_smbus *smbus = adap->algo_data;
	पूर्णांक समयout = 0;
	अचिन्हित अक्षर temp;

	करो अणु
		msleep(1);
		temp = inb_p(NVIDIA_SMB_STS);
	पूर्ण जबतक ((!temp) && (समयout++ < MAX_TIMEOUT));

	अगर (समयout > MAX_TIMEOUT) अणु
		dev_dbg(&adap->dev, "SMBus Timeout!\n");
		अगर (smbus->can_पात)
			nक्रमce2_पात(adap);
		वापस -ETIMEDOUT;
	पूर्ण
	अगर (!(temp & NVIDIA_SMB_STS_DONE) || (temp & NVIDIA_SMB_STS_STATUS)) अणु
		dev_dbg(&adap->dev, "Transaction failed (0x%02x)!\n", temp);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/* Return negative त्रुटि_सं on error */
अटल s32 nक्रमce2_access(काष्ठा i2c_adapter *adap, u16 addr,
		अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
		u8 command, पूर्णांक size, जोड़ i2c_smbus_data *data)
अणु
	काष्ठा nक्रमce2_smbus *smbus = adap->algo_data;
	अचिन्हित अक्षर protocol, pec;
	u8 len;
	पूर्णांक i, status;

	protocol = (पढ़ो_ग_लिखो == I2C_SMBUS_READ) ? NVIDIA_SMB_PRTCL_READ :
		NVIDIA_SMB_PRTCL_WRITE;
	pec = (flags & I2C_CLIENT_PEC) ? NVIDIA_SMB_PRTCL_PEC : 0;

	चयन (size) अणु
	हाल I2C_SMBUS_QUICK:
		protocol |= NVIDIA_SMB_PRTCL_QUICK;
		पढ़ो_ग_लिखो = I2C_SMBUS_WRITE;
		अवरोध;

	हाल I2C_SMBUS_BYTE:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			outb_p(command, NVIDIA_SMB_CMD);
		protocol |= NVIDIA_SMB_PRTCL_BYTE;
		अवरोध;

	हाल I2C_SMBUS_BYTE_DATA:
		outb_p(command, NVIDIA_SMB_CMD);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			outb_p(data->byte, NVIDIA_SMB_DATA);
		protocol |= NVIDIA_SMB_PRTCL_BYTE_DATA;
		अवरोध;

	हाल I2C_SMBUS_WORD_DATA:
		outb_p(command, NVIDIA_SMB_CMD);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			outb_p(data->word, NVIDIA_SMB_DATA);
			outb_p(data->word >> 8, NVIDIA_SMB_DATA + 1);
		पूर्ण
		protocol |= NVIDIA_SMB_PRTCL_WORD_DATA | pec;
		अवरोध;

	हाल I2C_SMBUS_BLOCK_DATA:
		outb_p(command, NVIDIA_SMB_CMD);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			len = data->block[0];
			अगर ((len == 0) || (len > I2C_SMBUS_BLOCK_MAX)) अणु
				dev_err(&adap->dev,
					"Transaction failed (requested block size: %d)\n",
					len);
				वापस -EINVAL;
			पूर्ण
			outb_p(len, NVIDIA_SMB_BCNT);
			क्रम (i = 0; i < I2C_SMBUS_BLOCK_MAX; i++)
				outb_p(data->block[i + 1],
				       NVIDIA_SMB_DATA + i);
		पूर्ण
		protocol |= NVIDIA_SMB_PRTCL_BLOCK_DATA | pec;
		अवरोध;

	शेष:
		dev_err(&adap->dev, "Unsupported transaction %d\n", size);
		वापस -EOPNOTSUPP;
	पूर्ण

	outb_p((addr & 0x7f) << 1, NVIDIA_SMB_ADDR);
	outb_p(protocol, NVIDIA_SMB_PRTCL);

	status = nक्रमce2_check_status(adap);
	अगर (status)
		वापस status;

	अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
		वापस 0;

	चयन (size) अणु
	हाल I2C_SMBUS_BYTE:
	हाल I2C_SMBUS_BYTE_DATA:
		data->byte = inb_p(NVIDIA_SMB_DATA);
		अवरोध;

	हाल I2C_SMBUS_WORD_DATA:
		data->word = inb_p(NVIDIA_SMB_DATA) |
			     (inb_p(NVIDIA_SMB_DATA + 1) << 8);
		अवरोध;

	हाल I2C_SMBUS_BLOCK_DATA:
		len = inb_p(NVIDIA_SMB_BCNT);
		अगर ((len <= 0) || (len > I2C_SMBUS_BLOCK_MAX)) अणु
			dev_err(&adap->dev,
				"Transaction failed (received block size: 0x%02x)\n",
				len);
			वापस -EPROTO;
		पूर्ण
		क्रम (i = 0; i < len; i++)
			data->block[i + 1] = inb_p(NVIDIA_SMB_DATA + i);
		data->block[0] = len;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण


अटल u32 nक्रमce2_func(काष्ठा i2c_adapter *adapter)
अणु
	/* other functionality might be possible, but is not tested */
	वापस I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	       I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
	       I2C_FUNC_SMBUS_PEC |
	       (((काष्ठा nक्रमce2_smbus *)adapter->algo_data)->blockops ?
		I2C_FUNC_SMBUS_BLOCK_DATA : 0);
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm smbus_algorithm = अणु
	.smbus_xfer	= nक्रमce2_access,
	.functionality	= nक्रमce2_func,
पूर्ण;


अटल स्थिर काष्ठा pci_device_id nक्रमce2_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE2_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE2S_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE3_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE3S_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE4_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_MCP04_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_MCP51_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_MCP55_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_MCP61_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_MCP65_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_MCP67_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_MCP73_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_MCP78S_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFORCE_MCP79_SMBUS) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, nक्रमce2_ids);


अटल पूर्णांक nक्रमce2_probe_smb(काष्ठा pci_dev *dev, पूर्णांक bar, पूर्णांक alt_reg,
			     काष्ठा nक्रमce2_smbus *smbus, स्थिर अक्षर *name)
अणु
	पूर्णांक error;

	smbus->base = pci_resource_start(dev, bar);
	अगर (smbus->base) अणु
		smbus->size = pci_resource_len(dev, bar);
	पूर्ण अन्यथा अणु
		/* Older incarnations of the device used non-standard BARs */
		u16 iobase;

		अगर (pci_पढ़ो_config_word(dev, alt_reg, &iobase)
		    != PCIBIOS_SUCCESSFUL) अणु
			dev_err(&dev->dev, "Error reading PCI config for %s\n",
				name);
			वापस -EIO;
		पूर्ण

		smbus->base = iobase & PCI_BASE_ADDRESS_IO_MASK;
		smbus->size = 64;
	पूर्ण

	error = acpi_check_region(smbus->base, smbus->size,
				  nक्रमce2_driver.name);
	अगर (error)
		वापस error;

	अगर (!request_region(smbus->base, smbus->size, nक्रमce2_driver.name)) अणु
		dev_err(&smbus->adapter.dev, "Error requesting region %02x .. %02X for %s\n",
			smbus->base, smbus->base+smbus->size-1, name);
		वापस -EBUSY;
	पूर्ण
	smbus->adapter.owner = THIS_MODULE;
	smbus->adapter.class = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	smbus->adapter.algo = &smbus_algorithm;
	smbus->adapter.algo_data = smbus;
	smbus->adapter.dev.parent = &dev->dev;
	snम_लिखो(smbus->adapter.name, माप(smbus->adapter.name),
		"SMBus nForce2 adapter at %04x", smbus->base);

	error = i2c_add_adapter(&smbus->adapter);
	अगर (error) अणु
		release_region(smbus->base, smbus->size);
		वापस error;
	पूर्ण
	dev_info(&smbus->adapter.dev, "nForce2 SMBus adapter at %#x\n",
		smbus->base);
	वापस 0;
पूर्ण


अटल पूर्णांक nक्रमce2_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा nक्रमce2_smbus *smbuses;
	पूर्णांक res1, res2;

	/* we support 2 SMBus adapters */
	smbuses = kसुस्मृति(2, माप(काष्ठा nक्रमce2_smbus), GFP_KERNEL);
	अगर (!smbuses)
		वापस -ENOMEM;
	pci_set_drvdata(dev, smbuses);

	चयन (dev->device) अणु
	हाल PCI_DEVICE_ID_NVIDIA_NFORCE2_SMBUS:
	हाल PCI_DEVICE_ID_NVIDIA_NFORCE_MCP51_SMBUS:
	हाल PCI_DEVICE_ID_NVIDIA_NFORCE_MCP55_SMBUS:
		smbuses[0].blockops = 1;
		smbuses[1].blockops = 1;
		smbuses[0].can_पात = 1;
		smbuses[1].can_पात = 1;
	पूर्ण

	/* SMBus adapter 1 */
	res1 = nक्रमce2_probe_smb(dev, 4, NFORCE_PCI_SMB1, &smbuses[0], "SMB1");
	अगर (res1 < 0)
		smbuses[0].base = 0;	/* to have a check value */

	/* SMBus adapter 2 */
	अगर (dmi_check_प्रणाली(nक्रमce2_dmi_blacklist2)) अणु
		dev_err(&dev->dev, "Disabling SMB2 for safety reasons.\n");
		res2 = -EPERM;
		smbuses[1].base = 0;
	पूर्ण अन्यथा अणु
		res2 = nक्रमce2_probe_smb(dev, 5, NFORCE_PCI_SMB2, &smbuses[1],
					 "SMB2");
		अगर (res2 < 0)
			smbuses[1].base = 0;	/* to have a check value */
	पूर्ण

	अगर ((res1 < 0) && (res2 < 0)) अणु
		/* we did not find even one of the SMBuses, so we give up */
		kमुक्त(smbuses);
		वापस -ENODEV;
	पूर्ण

	nक्रमce2_set_reference(&smbuses[0].adapter);
	वापस 0;
पूर्ण


अटल व्योम nक्रमce2_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा nक्रमce2_smbus *smbuses = pci_get_drvdata(dev);

	nक्रमce2_set_reference(शून्य);
	अगर (smbuses[0].base) अणु
		i2c_del_adapter(&smbuses[0].adapter);
		release_region(smbuses[0].base, smbuses[0].size);
	पूर्ण
	अगर (smbuses[1].base) अणु
		i2c_del_adapter(&smbuses[1].adapter);
		release_region(smbuses[1].base, smbuses[1].size);
	पूर्ण
	kमुक्त(smbuses);
पूर्ण

अटल काष्ठा pci_driver nक्रमce2_driver = अणु
	.name		= "nForce2_smbus",
	.id_table	= nक्रमce2_ids,
	.probe		= nक्रमce2_probe,
	.हटाओ		= nक्रमce2_हटाओ,
पूर्ण;

module_pci_driver(nक्रमce2_driver);
